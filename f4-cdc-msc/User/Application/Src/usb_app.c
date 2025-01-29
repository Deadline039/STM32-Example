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

/**
 * @brief USB 程序任务
 *
 * @param pvparameters 启动参数
 */
void usb_app(void *pvParameters) {
    UNUSED(pvParameters);

    uint8_t last_usb_state_reg = 0;
    uint8_t last_usb_dev_state = 0;
    uint8_t times = 0;

    lcd_init();
    lcd_display_dir(1);

    uint32_t disp_x = lcddev.width / 2;
    uint32_t disp_y = lcddev.height / 2;

    sdcard_init();

    USBD_Init(&usbd_device, &USBD_Desc, DEVICE_FS);
    USBD_RegisterClass(&usbd_device, &USBD_MC);
    USBD_Start(&usbd_device);

    lcd_clear(WHITE);
    lcd_show_string(disp_x - 80, disp_y - 20, 200, 24, 16,
                    "USB MSC & CDC composite. ", BLACK);

    while (1) {
        if (last_usb_state_reg != g_usb_msc_state) {
            lcd_fill(disp_x - 80, disp_y, disp_x + 100, disp_y + 16 * 4, WHITE);
            if (g_usb_msc_state & (1 << 0)) {
                lcd_show_string(disp_x - 80, disp_y, 100, 16, 16,
                                "USB Writing...", RED);
            }

            if (g_usb_msc_state & (1 << 1)) {
                lcd_show_string(disp_x - 80, disp_y + 16, 100, 16, 16,
                                "USB Reading...", BLUE);
            }

            if (g_usb_msc_state & (1 << 2)) {
                lcd_show_string(disp_x - 80, disp_y + 16 * 2, 100, 16, 16,
                                "USB Write Error. ", RED);
            }

            if (g_usb_msc_state & (1 << 3)) {
                lcd_show_string(disp_x - 80, disp_y + 16 * 3, 100, 16, 16,
                                "USB Read Error. ", RED);
            }

            last_usb_state_reg = g_usb_msc_state;
        }

        if (last_usb_dev_state != g_usb_dev_state) {
            if (g_usb_dev_state) {
                lcd_show_string(disp_x - 80, disp_y - 40, 100, 16, 16,
                                "USB Connected.    ", BLACK);
            } else {
                lcd_show_string(disp_x - 80, disp_y - 40, 100, 16, 16,
                                "USB Disconnected. ", BLACK);
            }

            last_usb_dev_state = g_usb_dev_state;
        }

        delay_ms(1);

        ++times;

        if (times % 50 == 0) {
            /* 每 50ms 更新一次设备状态 */
            g_usb_msc_state = 0;
        }
    }
}
