/**
 * @file    rtos_tasks.c
 * @author  Deadline039
 * @brief   RTOS tasks.
 * @version 1.0
 * @date    2024-01-31
 */

#include "includes.h"

static TaskHandle_t start_task_handle;
void start_task(void *pvParameters);

static TaskHandle_t usb_cdc_task_handle;
void usb_cdc_task(void *pvParameters);

/*****************************************************************************/

/**
 * @brief FreeRTOS start up.
 *
 */
void freertos_start(void) {
    xTaskCreate(start_task, "start_task", 512, NULL, 2, &start_task_handle);
    vTaskStartScheduler();
}

/**
 * @brief Start up task.
 *
 * @param pvParameters Start parameters.
 */
void start_task(void *pvParameters) {
    UNUSED(pvParameters);

    at24c02_dev_init();
    xTaskCreate(usb_cdc_task, "usb_cdc_task", 128, NULL, 2, &usb_cdc_task_handle);
    xTaskCreate(usb_app, "usb_app", 1024, NULL, 2, &usb_app_handle);
    vTaskDelete(start_task_handle);
}

/**
 * @brief USB CDC polling task.
 *
 * @param pvParameters Start parameters.
 */
void usb_cdc_task(void *pvParameters) {
    UNUSED(pvParameters);
    int a;
    float b;

    while (1) {
        usb_cdc_scanf("%d %f", &a, &b);
        usb_cdc_printf("a = %d, b = %f\n", a, b);
    }
}