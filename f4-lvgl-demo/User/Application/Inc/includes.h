/**
 * @file    includes.h
 * @author  Deadline039
 * @brief   Include files
 * @version 1.0
 * @date    2024-04-03
 */

#ifndef __INCLUDES_H
#define __INCLUDES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************
 * @defgroup Include files.
 * @{
 */

#include "bsp.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"

#include "ui.h"

#include "ff.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#include "usbd_conf.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage_if.h"

/**
 * @}
 */

/*****************************************************************************
 * @defgroup Public variables.
 * @{
 */

extern at24cxx_handle_t at24c02_handle;

extern TaskHandle_t usb_app_handle;
extern TaskHandle_t gui_task_handle;

/**
 * @}
 */

/*****************************************************************************
 * @defgroup Public functions.
 * @{
 */

void freertos_start(void);
void at24c02_dev_init(void);

uint8_t usb_detect_msc(void);
void usb_app(void *pvParameters);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCLUDES_H */
