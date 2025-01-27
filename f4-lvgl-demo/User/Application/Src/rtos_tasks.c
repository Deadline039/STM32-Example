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

static TaskHandle_t task1_handle;
void task1(void *pvParameters);

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

    taskENTER_CRITICAL();

    // xTaskCreate(task1, "task1", 512, NULL, 2, &task1_handle);
    xTaskCreate(usb_app, "usb_app", 512, NULL, 2, &usb_app_handle);

    vTaskDelete(start_task_handle);
    taskEXIT_CRITICAL();
}

void action_toggle_led0(lv_event_t *e) {
    UNUSED(e);
    LED0_TOGGLE();
}

void action_toggle_led1(lv_event_t *e) {
    UNUSED(e);
    LED1_TOGGLE();
}

/**
 * @brief Task1: Blink.
 *
 * @param pvParameters Start parameters.
 */
void task1(void *pvParameters) {
    UNUSED(pvParameters);
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    ui_init();

    while (1) {
        lv_timer_handler();
        ui_tick();
        vTaskDelay(5);
    }
}
