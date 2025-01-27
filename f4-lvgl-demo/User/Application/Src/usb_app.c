/**
 * @file    usb_app.c
 * @author  Deadline039
 * @brief   USB 程序
 * @version 1.0
 * @date    2025-01-27
 */

#include "includes.h"

static USBD_HandleTypeDef usbd_device;
TaskHandle_t usb_app_handle;

/**
 * @brief USB 程序任务
 *
 */
void usb_app(void *pvParameters) {
    UNUSED(pvParameters);

    USBD_Init(&usbd_device, &MSC_Desc, DEVICE_FS); /* 初始化USB */
    USBD_RegisterClass(&usbd_device, &USBD_MSC);   /* 添加类 */
    USBD_MSC_RegisterStorage(&usbd_device,
                             &USBD_DISK_fops); /* 为MSC类添加回调函数 */
    USBD_Start(&usbd_device);                  /* 开启USB */

    while (1)
        ;
}