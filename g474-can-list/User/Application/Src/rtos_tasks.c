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

static TaskHandle_t task3_handle;
void task3(void *pvParameters);

/*****************************************************************************/

/**
 * @brief FreeRTOS start up.
 *
 */
void freertos_start(void) {
    xTaskCreate(start_task, "start_task", 128, NULL, 2, &start_task_handle);
    vTaskStartScheduler();
}

/**
 * @brief Start up task.
 *
 * @param pvParameters Start parameters.
 */
void start_task(void *pvParameters) {
    UNUSED(pvParameters);

    can_list_add_can(can1_selected, 2, 3);
    can_list_add_can(can2_selected, 2, 3);
    can_list_add_can(can3_selected, 2, 3);

    printf("Welcome to CAN list demo! \n"
           "Press WKUP to send from CAN1, id is 0x01 with standard id; \n"
           "Press KEY0 to send from CAN1, id is 0x11 with Extended id; \n"
           "Press KEY1 to send from CAN2, id is 0x02 with standard id; \n"
           "Press KEY2 to send from CAN3, id is 0x03 with Extended id. \n"
           "------------------------------------------------------------\n"
           "Send data id with 3 or 10 can call different function. Regradless "
           "standard ID or extended ID.\n");

    taskENTER_CRITICAL();

    xTaskCreate(task1, "task1", 128, NULL, 2, &task1_handle);
    xTaskCreate(task3, "task3", 128, NULL, 2, &task3_handle);

    vTaskDelete(start_task_handle);
    taskEXIT_CRITICAL();
}

/**
 * @brief Task1: Blink.
 *
 * @param pvParameters Start parameters.
 */
void task1(void *pvParameters) {
    UNUSED(pvParameters);

    LED0_OFF();
    LED1_ON();

    while (1) {
        LED0_TOGGLE();
        LED1_TOGGLE();
        vTaskDelay(1000);
    }
}

/**
 * @brief CAN ID = 3, Std ID callback function.
 * 
 * @param node_obj Node data.
 * @param rx_header CAN message rx header.
 * @param can_msg CAN message data.
 */
static void can_rx_callback_std_3(void *node_obj, can_rx_header_t *rx_header,
                                  uint8_t *can_msg) {
    UNUSED(node_obj);

    printf("Func: std_3, ID Type: Std ID, ID: %u, data: "
           "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",
           rx_header->id, can_msg[0], can_msg[1], can_msg[2], can_msg[3],
           can_msg[4], can_msg[5], can_msg[6], can_msg[7]);
}

/**
 * @brief CAN ID = 10, standard ID callback function.
 * 
 * @param node_obj Node data.
 * @param rx_header CAN message rx header.
 * @param can_msg CAN message data.
 */
static void can_rx_callback_std_10(void *node_obj, can_rx_header_t *rx_header,
                                   uint8_t *can_msg) {
    UNUSED(node_obj);

    printf("Func: std_10, ID Type: Std ID, ID: %u, data: "
           "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",
           rx_header->id, can_msg[0], can_msg[1], can_msg[2], can_msg[3],
           can_msg[4], can_msg[5], can_msg[6], can_msg[7]);
}

/**
 * @brief CAN ID = 3, Ext ID callback function.
 * 
 * @param node_obj Node data.
 * @param rx_header CAN message rx header.
 * @param can_msg CAN message data.
 */
static void can_rx_callback_ext_3(void *node_obj, can_rx_header_t *rx_header,
                                  uint8_t *can_msg) {
    UNUSED(node_obj);

    printf("Func: ext_3, ID Type: Ext ID, ID: %u, data: "
           "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",
           rx_header->id, can_msg[0], can_msg[1], can_msg[2], can_msg[3],
           can_msg[4], can_msg[5], can_msg[6], can_msg[7]);
}

/**
 * @brief CAN ID = 10, Ext ID callback function.
 * 
 * @param node_obj Node data.
 * @param rx_header CAN message rx header.
 * @param can_msg CAN message data.
 */
static void can_rx_callback_ext_10(void *node_obj, can_rx_header_t *rx_header,
                                   uint8_t *can_msg) {
    UNUSED(node_obj);

    printf("Func: ext_10, ID Type: Ext ID, ID: %u, data: "
           "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",
           rx_header->id, can_msg[0], can_msg[1], can_msg[2], can_msg[3],
           can_msg[4], can_msg[5], can_msg[6], can_msg[7]);
}

/**
 * @brief Task3: Scan the key and print which key pressed.
 *
 * @param pvParameters Start parameters.
 */
void task3(void *pvParameters) {
    UNUSED(pvParameters);

    can_selected_t can_select = can1_selected;

    can_list_add_new_node(can_select, NULL, 3, 0xFF, CAN_ID_STD,
                          can_rx_callback_std_3);
    can_list_add_new_node(can_select, NULL, 10, 0xFF, CAN_ID_STD,
                          can_rx_callback_std_10);

    can_list_add_new_node(can_select, NULL, 3, 0xFF, CAN_ID_EXT,
                          can_rx_callback_ext_3);
    can_list_add_new_node(can_select, NULL, 10, 0xFF, CAN_ID_EXT,
                          can_rx_callback_ext_10);

    const uint8_t tx_data[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    key_press_t key = KEY_NO_PRESS;

    while (1) {
        key = key_scan(0);
        switch (key) {
            case WKUP_PRESS: {
                fdcan_send_message(can1_selected, FDCAN_STANDARD_ID, 0x01, 8,
                                   tx_data);
            } break;

            case KEY0_PRESS: {
                fdcan_send_message(can1_selected, FDCAN_EXTENDED_ID, 0x11, 8,
                                   tx_data);
            } break;

            case KEY1_PRESS: {
                fdcan_send_message(can2_selected, FDCAN_STANDARD_ID, 0x02, 8,
                                   tx_data);
            } break;

            case KEY2_PRESS: {
                fdcan_send_message(can3_selected, FDCAN_EXTENDED_ID, 0x03, 8,
                                   tx_data);
            } break;

            default: {
            } break;
        }

        vTaskDelay(10);
    }
}
