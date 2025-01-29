/**
 * @file    usb_app.c
 * @author  Deadline039
 * @brief   USB 程序
 * @version 1.0
 * @date    2025-01-27
 */

#include "includes.h"

USBD_HandleTypeDef usbd_device;
TaskHandle_t usb_app_handle;

/* 是否使用 MSC 设备 */
uint8_t g_usb_app_use_msc;

/**
 * @brief 检测是否按下 KEY0, 如果按下持续 3 秒以上会启用 MSC 设备
 *
 * @return 是否持续按下 KEY0
 */
uint8_t usb_detect_msc(void) {
    key_press_t key;
    uint32_t start_time = HAL_GetTick();

    USBD_Init(&usbd_device, &USBD_Desc, DEVICE_FS);
    USBD_RegisterClass(&usbd_device, USBD_CDC_CLASS);
    USBD_CDC_RegisterInterface(&usbd_device, &USBD_CDC_fops);

    USBD_Start(&usbd_device);

    do {
        key = key_scan(1);
        if (key != KEY0_PRESS) {
            LED0_OFF();
            return 0;
        }
        LED0_ON();
    } while (HAL_GetTick() - start_time < 3000);

    if (g_usb_dev_state) {
        return 1;
    }

    LED0_OFF();
    return 0;
}

/**
 * @brief USB 程序任务
 *
 * @param pvparameters 启动参数
 */
void usb_app(void *pvParameters) {
    UNUSED(pvParameters);

    LED0_OFF();
    LED1_OFF();

    uint8_t last_usb_state_reg = 0;
    uint32_t last_usb_dev_state = 0;
    uint8_t times = 0;

    lcd_init();
    lcd_display_dir(1);

    uint32_t disp_x = lcddev.width / 2 - 200;
    uint32_t disp_y = lcddev.height / 2 - 20;

    USBD_Stop(&usbd_device);
    lcd_clear(WHITE);
    lcd_show_string(disp_x - 20, disp_y - 20, 400, 16, 16,
                    "Entering USB storage mode, waitting 3 seconds. ", BLACK);

    delay_ms(3000);

    sdcard_init();
    USBD_Init(&usbd_device, &USBD_Desc, DEVICE_FS);
    USBD_RegisterClass(&usbd_device, USBD_MSC_CLASS);
    USBD_MSC_RegisterStorage(&usbd_device, &USBD_DISK_fops);

    USBD_Start(&usbd_device);

    lcd_clear(WHITE);
    lcd_show_string(disp_x - 20, disp_y - 20, 400, 24, 16,
                    "Now is USB storage mode. ", BLACK);

    while (1) {
        if (last_usb_state_reg != g_usb_msc_state) {
            lcd_fill(disp_x - 20, disp_y, disp_x + 200, disp_y + 16 * 4, WHITE);
            if (g_usb_msc_state & (1 << 0)) {
                lcd_show_string(disp_x - 20, disp_y, 200, 16, 16,
                                "USB Writing...", RED);
            }

            if (g_usb_msc_state & (1 << 1)) {
                lcd_show_string(disp_x - 20, disp_y + 16, 200, 16, 16,
                                "USB Reading...", BLUE);
            }

            if (g_usb_msc_state & (1 << 2)) {
                lcd_show_string(disp_x - 20, disp_y + 16 * 2, 200, 16, 16,
                                "USB Write Error. ", RED);
            }

            if (g_usb_msc_state & (1 << 3)) {
                lcd_show_string(disp_x - 20, disp_y + 16 * 3, 200, 16, 16,
                                "USB Read Error. ", RED);
            }

            last_usb_state_reg = g_usb_msc_state;
        }

        if (last_usb_dev_state != g_usb_dev_state) {
            if (g_usb_dev_state) {
                lcd_show_string(disp_x - 20, disp_y - 40, 200, 16, 16,
                                "USB Connected.    ", BLACK);
            } else {
                lcd_show_string(disp_x - 20, disp_y - 40, 200, 16, 16,
                                "USB Disconnected. ", BLACK);
            }

            last_usb_dev_state = g_usb_dev_state;
        }

        delay_ms(1);

        ++times;

        if (times > 50) {
            /* 每 50ms 更新一次设备状态 */
            times = 0;
            g_usb_msc_state = 0;
        }
    }
}
