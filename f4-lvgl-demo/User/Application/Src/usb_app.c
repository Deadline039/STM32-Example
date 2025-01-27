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
 */
void usb_app(void *pvParameters) {
    UNUSED(pvParameters);
    int a;
    float b;

    sdcard_init();

    USBD_Init(&usbd_device, &FS_Desc, DEVICE_FS);

    USBD_RegisterClass(&usbd_device, &USBD_MC);
    USBD_Start(&usbd_device);

    while (1) {
        if (g_usb_device_state == 1) {
            usb_cdc_scanf("%d %f", &a, &b);
            usb_cdc_printf("a = %d, b = %f", a, b);
        }
    }
}
