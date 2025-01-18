/**
 * @file    UART_STM32F1xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of UART on STM32F1xx
 * @version 1.0
 * @date    2024-10-22
 */

#ifndef __UART_STM32F1xx_H
#define __UART_STM32F1xx_H

#include <stdarg.h>

/* clang-format off */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/*****************************************************************************
 * @defgroup UART Public Marco. 
 * @{
 */

#define UART_INIT_OK         0
#define UART_INIT_FAIL       1
#define UART_INIT_DMA_FAIL   2
#define UART_INIT_MEM_FAIL   3
#define UART_INITED          4

#define UART_DEINIT_OK       0
#define UART_DEINIT_FAIL     1
#define UART_DEINIT_DMA_FAIL 2
#define UART_NO_INIT         3

/**
 * @}
 */

/*****************************************************************************
 * @defgroup USART1 Functions
 * @{
 */

#if USART1_ENABLE

extern UART_HandleTypeDef usart1_handle;
uint8_t usart1_init(uint32_t baud_rate);
uint8_t usart1_deinit(void);

#  if USART1_RX_DMA
#    define USART1_RX_DMA_IRQHandler                                           \
      CSP_DMA_CHANNEL_IRQ(USART1_RX_DMA_NUMBER, USART1_RX_DMA_CHANNEL)
#  endif /* USART1_RX_DMA */

#  if USART1_TX_DMA
#    define USART1_TX_DMA_IRQHandler                                           \
      CSP_DMA_CHANNEL_IRQ(USART1_TX_DMA_NUMBER, USART1_TX_DMA_CHANNEL)
#  endif /* USART1_TX_DMA */

#endif /* USART1_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup USART2 Functions
 * @{
 */

#if USART2_ENABLE

extern UART_HandleTypeDef usart2_handle;
uint8_t usart2_init(uint32_t baud_rate);
uint8_t usart2_deinit(void);

#  if USART2_RX_DMA
#    define USART2_RX_DMA_IRQHandler                                           \
      CSP_DMA_CHANNEL_IRQ(USART2_RX_DMA_NUMBER, USART2_RX_DMA_CHANNEL)
#  endif /* USART2_RX_DMA */

#  if USART2_TX_DMA
#    define USART2_TX_DMA_IRQHandler                                           \
      CSP_DMA_CHANNEL_IRQ(USART2_TX_DMA_NUMBER, USART2_TX_DMA_CHANNEL)
#  endif /* USART2_TX_DMA */

#endif /* USART2_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup USART3 Functions
 * @{
 */

#if USART3_ENABLE

extern UART_HandleTypeDef usart3_handle;
uint8_t usart3_init(uint32_t baud_rate);
uint8_t usart3_deinit(void);

#  if USART3_RX_DMA
#    define USART3_RX_DMA_IRQHandler                                           \
      CSP_DMA_CHANNEL_IRQ(USART3_RX_DMA_NUMBER, USART3_RX_DMA_CHANNEL)
#  endif /* USART3_RX_DMA */

#  if USART3_TX_DMA
#    define USART3_TX_DMA_IRQHandler                                           \
      CSP_DMA_CHANNEL_IRQ(USART3_TX_DMA_NUMBER, USART3_TX_DMA_CHANNEL)
#  endif /* USART3_TX_DMA */

#endif /* USART3_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup UART4 Functions
 * @{
 */

#if UART4_ENABLE

extern UART_HandleTypeDef uart4_handle;
uint8_t uart4_init(uint32_t baud_rate);
uint8_t uart4_deinit(void);

#  if UART4_RX_DMA
#    define UART4_RX_DMA_IRQHandler                                            \
      CSP_DMA_CHANNEL_IRQ(UART4_RX_DMA_NUMBER, UART4_RX_DMA_CHANNEL)
#  endif /* UART4_RX_DMA */

#  if UART4_TX_DMA
#    define UART4_TX_DMA_IRQHandler                                            \
      CSP_DMA_CHANNEL_IRQ(UART4_TX_DMA_NUMBER, UART4_TX_DMA_CHANNEL)
#  endif /* UART4_TX_DMA */

#endif /* UART4_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup UART5 Functions
 * @{
 */

#if UART5_ENABLE

extern UART_HandleTypeDef uart5_handle;
uint8_t uart5_init(uint32_t baud_rate);
uint8_t uart5_deinit(void);

#endif /* UART5_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup Public uart function.
 * @{
 */

int uart_printf(UART_HandleTypeDef *huart, const char *__format, ...);
int uart_scanf(UART_HandleTypeDef *huart, const char *__format, ...);

uint32_t uart_dmarx_read(UART_HandleTypeDef *huart, void *buf, size_t len);
uint8_t uart_dmarx_resize_fifo(UART_HandleTypeDef *huart, uint32_t buf_size,
                               uint32_t fifo_size);
uint32_t uart_dmarx_get_buf_size(UART_HandleTypeDef *huart);
uint32_t uart_dmarx_get_fifo_size(UART_HandleTypeDef *huart);

uint32_t uart_dmatx_write(UART_HandleTypeDef *huart, const void *data,
                          size_t len);
uint32_t uart_dmatx_send(UART_HandleTypeDef *huart);
uint8_t uart_dmatx_resize_buf(UART_HandleTypeDef *huart, uint32_t size);
uint32_t uart_damtx_get_buf_szie(UART_HandleTypeDef *huart);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __UART_STM32F1xx_H */
