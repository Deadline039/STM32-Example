/**
 ******************************************************************************
 * @file    usbd_cdc_if_template.h
 * @author  MCD Application Team
 * @brief   Header for usbd_cdc_if_template.c file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CDC_IF_TEMPLATE_H
#define __USBD_CDC_IF_TEMPLATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

extern USBD_CDC_ItfTypeDef USBD_CDC_fops;

/* Exported macro ------------------------------------------------------------*/

#define USB_CDC_TX_BUF_SIZE 200
#define USB_CDC_RX_BUF_SIZE 200

/* Exported functions ------------------------------------------------------- */

void usb_cdc_tramsmit(uint8_t *data, uint32_t len);
int usb_cdc_scanf(const char *__fmt, ...);
int usb_cdc_printf(const char *__fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* __USBD_CDC_IF_TEMPLATE_H */
