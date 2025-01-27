/**
 ******************************************************************************
 * @file    usbd_cdc_if_template.c
 * @author  MCD Application Team
 * @brief   Generic media access Layer.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2015 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_interface.h"

#include <stdarg.h>
#include <stdio.h>

/** @addtogroup STM32_USB_DEVICE_LIBRARY
 * @{
 */

/** @defgroup USBD_CDC
 * @brief usbd core module
 * @{
 */

/** @defgroup USBD_CDC_Private_variables.
 * @{
 */

static uint8_t usb_cdc_tx_buffer[USB_CDC_TX_BUF_SIZE];
static uint8_t usb_cdc_rx_buffer[USB_CDC_RX_BUF_SIZE];

/* 发送状态标识位, 1 为发送完毕 */
static uint8_t usb_cdc_tx_cplt = 1;
/* 接收状态标志位, 1 为接收到数据 */
static uint8_t usb_cdc_rx_sta;

/* USB handler declaration */
extern USBD_HandleTypeDef usbd_device;

/**
 * @}
 */

/** @defgroup USBD_CDC_Private_Defines
 * @{
 */
/**
 * @}
 */

/** @defgroup USBD_CDC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup USBD_CDC_Private_FunctionPrototypes
 * @{
 */

static int8_t USB_CDC_Init(void);
static int8_t USB_CDC_DeInit(void);
static int8_t USB_CDC_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t USB_CDC_Receive(uint8_t *pbuf, uint32_t *Len);
static int8_t USB_CDC_TransmitCplt(uint8_t *pbuf, uint32_t *Len, uint8_t epnum);

USBD_CDC_ItfTypeDef USBD_CDC_fops = {USB_CDC_Init, USB_CDC_DeInit,
                                     USB_CDC_Control, USB_CDC_Receive,
                                     USB_CDC_TransmitCplt};

USBD_CDC_LineCodingTypeDef linecoding = {
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* nb. of bits 8*/
};

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  USB_CDC_Init
 *         Initializes the CDC media low layer
 * @param  None
 * @retval Result of the operation: USBD_OK if all operations are OK else
 *         USBD_FAIL
 */
static int8_t USB_CDC_Init(void) {
    USBD_CDC_SetRxBuffer(&usbd_device, usb_cdc_rx_buffer);
    return USBD_OK;
}

/**
 * @brief  USB_CDC_DeInit
 *         DeInitializes the CDC media low layer
 * @param  None
 * @retval Result of the operation: USBD_OK if all operations are OK else
 *         USBD_FAIL
 */
static int8_t USB_CDC_DeInit(void) {
    return USBD_OK;
}

/**
 * @brief  USB_CDC_Control
 *         Manage the CDC class requests
 * @param  Cmd: Command code
 * @param  Buf: Buffer containing command data (request parameters)
 * @param  Len: Number of data to be sent (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else
 *         USBD_FAIL
 */
static int8_t USB_CDC_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length) {
    UNUSED(length);

    switch (cmd) {
        case CDC_SEND_ENCAPSULATED_COMMAND:
            /* Add your code here */
            break;

        case CDC_GET_ENCAPSULATED_RESPONSE:
            /* Add your code here */
            break;

        case CDC_SET_COMM_FEATURE:
            /* Add your code here */
            break;

        case CDC_GET_COMM_FEATURE:
            /* Add your code here */
            break;

        case CDC_CLEAR_COMM_FEATURE:
            /* Add your code here */
            break;

        case CDC_SET_LINE_CODING:
            linecoding.bitrate = (uint32_t)(pbuf[0] | (pbuf[1] << 8) |
                                            (pbuf[2] << 16) | (pbuf[3] << 24));
            linecoding.format = pbuf[4];
            linecoding.paritytype = pbuf[5];
            linecoding.datatype = pbuf[6];

            /* Add your code here */
            break;

        case CDC_GET_LINE_CODING:
            pbuf[0] = (uint8_t)(linecoding.bitrate);
            pbuf[1] = (uint8_t)(linecoding.bitrate >> 8);
            pbuf[2] = (uint8_t)(linecoding.bitrate >> 16);
            pbuf[3] = (uint8_t)(linecoding.bitrate >> 24);
            pbuf[4] = linecoding.format;
            pbuf[5] = linecoding.paritytype;
            pbuf[6] = linecoding.datatype;

            /* Add your code here */
            break;

        case CDC_SET_CONTROL_LINE_STATE:
            /* Add your code here */
            break;

        case CDC_SEND_BREAK:
            /* Add your code here */
            break;

        default:
            break;
    }

    return (0);
}

/**
 * @brief  USB_CDC_Receive
 *         Data received over USB OUT endpoint are sent over CDC interface
 *         through this function.
 *
 *         @note
 *         This function will issue a NAK packet on any OUT packet received on
 *         USB endpoint until exiting this function. If you exit this function
 *         before transfer is complete on CDC interface (ie. using DMA
 * controller) it will result in receiving more data while previous ones are
 * still not sent.
 *
 * @param  Buf: Buffer of data to be received
 * @param  Len: Number of data received (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else
 *         USBD_FAIL
 */
static int8_t USB_CDC_Receive(uint8_t *Buf, uint32_t *Len) {
    UNUSED(Buf);
    UNUSED(Len);

    USBD_CDC_ReceivePacket(&usbd_device);
    usb_cdc_rx_sta = 1;

    return (0);
}

static uint8_t *rx_buf;

/**
 * @brief  USB_CDC_TransmitCplt
 *         Data transmitted callback
 *
 * @note
 * This function is IN transfer complete callback used to inform user
 * that the submitted Data is successfully sent over USB.
 *
 * @param  Buf: Buffer of data to be received
 * @param  Len: Number of data received (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else
 *         USBD_FAIL
 */
static int8_t USB_CDC_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum) {
    UNUSED(Len);
    UNUSED(epnum);

    rx_buf = Buf;

    usb_cdc_tx_cplt = 1;

    return (0);
}

/**
 * @brief 发送数据到 USB 虚拟串口
 *
 * @param data 发送的数据
 * @param len 发送长度
 */
void usb_cdc_tramsmit(uint8_t *data, uint32_t len) {
    USBD_CDC_SetTxBuffer(&usbd_device, data, len);
    USBD_CDC_TransmitPacket(&usbd_device);
    usb_cdc_tx_cplt = 0;
}

/**
 * @brief 从 USB 虚拟串口格式化输入
 *
 * @param __fmt 格式字符串
 * @return 成功写入的变量个数
 */
int usb_cdc_scanf(const char *__fmt, ...) {
    int res;
    va_list ap;

    while (usb_cdc_rx_sta == 0)
        ;

    va_start(ap, __fmt);
    res = vsscanf((const char *)rx_buf, __fmt, ap);
    va_end(ap);

    usb_cdc_rx_sta = 0;

    return res;
}

/**
 * @brief 从 USB 虚拟串口格式化输出
 *
 * @param __fmt 格式化字符串
 * @return 成功写入的字符串长度, 不包括`\0`
 */
int usb_cdc_printf(const char *__fmt, ...) {
    int len;
    va_list ap;

    while (usb_cdc_tx_cplt == 0)
        ;

    va_start(ap, __fmt);
    len = vsnprintf((char *)usb_cdc_tx_buffer, sizeof(usb_cdc_tx_buffer), __fmt,
                    ap);
    va_end(ap);

    usb_cdc_tramsmit(usb_cdc_tx_buffer, len);

    return len;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
