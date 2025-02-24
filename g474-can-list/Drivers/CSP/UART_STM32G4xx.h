
/**
 * @file    UART_STM32G4xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of UART on STM32G4xx
 * @version 1.0
 * @date    2025-02-05
 * @note    Generate Automatically.
 */

#ifndef __UART_STM32G4xx_H
#define __UART_STM32G4xx_H

#include <stdarg.h>

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
 * @defgroup LPUART1 Functions
 * @{
 */

#if LPUART1_ENABLE

#if (LPUART1_TX_ID == 0)
#elif (LPUART1_TX_ID == 1)
#  define LPUART1_TX_AF GPIO_AF12_LPUART1
#elif (LPUART1_TX_ID == 2)
#  define LPUART1_TX_AF GPIO_AF8_LPUART1
#elif (LPUART1_TX_ID == 3)
#  define LPUART1_TX_AF GPIO_AF8_LPUART1
#elif (LPUART1_TX_ID == 4)
#  define LPUART1_TX_AF GPIO_AF8_LPUART1
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PG7 can not be configured as LPUART1 TX on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* LPUART1_TX_ID */

#if (LPUART1_RX_ID == 0)
#elif (LPUART1_RX_ID == 1)
#  define LPUART1_RX_AF GPIO_AF12_LPUART1
#elif (LPUART1_RX_ID == 2)
#  define LPUART1_RX_AF GPIO_AF8_LPUART1
#elif (LPUART1_RX_ID == 3)
#  define LPUART1_RX_AF GPIO_AF8_LPUART1
#elif (LPUART1_RX_ID == 4)
#  define LPUART1_RX_AF GPIO_AF8_LPUART1
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PG8 can not be configured as LPUART1 RX on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* LPUART1_RX_ID */

#if (LPUART1_CTS_ID == 0)
#elif (LPUART1_CTS_ID == 1)
#  define LPUART1_CTS_AF GPIO_AF12_LPUART1
#elif (LPUART1_CTS_ID == 2)
#  define LPUART1_CTS_AF GPIO_AF8_LPUART1
#elif (LPUART1_CTS_ID == 3)
#  define LPUART1_CTS_AF GPIO_AF8_LPUART1
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PG5 can not be configured as LPUART1 CTS on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* LPUART1_CTS_ID */

#if (LPUART1_RTS_ID == 0)
#elif (LPUART1_RTS_ID == 1)
#  define LPUART1_RTS_AF GPIO_AF12_LPUART1
#elif (LPUART1_RTS_ID == 2)
#  define LPUART1_RTS_AF GPIO_AF8_LPUART1
#elif (LPUART1_RTS_ID == 3)
#  define LPUART1_RTS_AF GPIO_AF8_LPUART1
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PG6 can not be configured as LPUART1 RTS on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* LPUART1_RTS_ID */

extern UART_HandleTypeDef lpuart1_handle;

uint8_t lpuart1_init(uint32_t baud_rate);
uint8_t lpuart1_deinit(void); 

#  if LPUART1_RX_DMA
#    define LPUART1_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(LPUART1_RX_DMA_NUMBER, LPUART1_RX_DMA_CHANNEL)
#    define LPUART1_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(LPUART1_RX_DMA_NUMBER, LPUART1_RX_DMA_CHANNEL)
#  endif /* LPUART1_RX_DMA */

#  if LPUART1_TX_DMA
#    define LPUART1_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(LPUART1_TX_DMA_NUMBER, LPUART1_TX_DMA_CHANNEL)
#    define LPUART1_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(LPUART1_TX_DMA_NUMBER, LPUART1_TX_DMA_CHANNEL)
#  endif /* LPUART1_TX_DMA */

#endif /* LPUART1_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup USART1 Functions
 * @{
 */

#if USART1_ENABLE

#if (USART1_TX_ID == 0)
#elif (USART1_TX_ID == 1)
#  define USART1_TX_AF GPIO_AF7_USART1
#elif (USART1_TX_ID == 2)
#  define USART1_TX_AF GPIO_AF7_USART1
#elif (USART1_TX_ID == 3)
#  define USART1_TX_AF GPIO_AF7_USART1
#  if (defined(STM32GBK1CB))
#    error "PC4 can not be configured as USART1 TX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (USART1_TX_ID == 4)
#  define USART1_TX_AF GPIO_AF7_USART1
#  if (defined(STM32GBK1CB))
#    error "PE0 can not be configured as USART1 TX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (USART1_TX_ID == 5)
#  define USART1_TX_AF GPIO_AF7_USART1
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PG9 can not be configured as USART1 TX on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* USART1_TX_ID */

#if (USART1_RX_ID == 0)
#elif (USART1_RX_ID == 1)
#  define USART1_RX_AF GPIO_AF7_USART1
#elif (USART1_RX_ID == 2)
#  define USART1_RX_AF GPIO_AF7_USART1
#elif (USART1_RX_ID == 3)
#  define USART1_RX_AF GPIO_AF7_USART1
#elif (USART1_RX_ID == 4)
#  define USART1_RX_AF GPIO_AF7_USART1
#  if (defined(STM32GBK1CB))
#    error "PE1 can not be configured as USART1 RX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* USART1_RX_ID */

#if (USART1_CTS_ID == 0)
#elif (USART1_CTS_ID == 1)
#  define USART1_CTS_AF GPIO_AF7_USART1
#endif  /* USART1_CTS_ID */

#if (USART1_RTS_ID == 0)
#elif (USART1_RTS_ID == 1)
#  define USART1_RTS_AF GPIO_AF7_USART1
#endif  /* USART1_RTS_ID */

extern UART_HandleTypeDef usart1_handle;

uint8_t usart1_init(uint32_t baud_rate);
uint8_t usart1_deinit(void); 

#  if USART1_RX_DMA
#    define USART1_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(USART1_RX_DMA_NUMBER, USART1_RX_DMA_CHANNEL)
#    define USART1_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(USART1_RX_DMA_NUMBER, USART1_RX_DMA_CHANNEL)
#  endif /* USART1_RX_DMA */

#  if USART1_TX_DMA
#    define USART1_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(USART1_TX_DMA_NUMBER, USART1_TX_DMA_CHANNEL)
#    define USART1_TX_DMA_IRQHandler                                             \
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

#if (USART2_TX_ID == 0)
#elif (USART2_TX_ID == 1)
#  define USART2_TX_AF GPIO_AF7_USART2
#elif (USART2_TX_ID == 2)
#  define USART2_TX_AF GPIO_AF7_USART2
#elif (USART2_TX_ID == 3)
#  define USART2_TX_AF GPIO_AF7_USART2
#elif (USART2_TX_ID == 4)
#  define USART2_TX_AF GPIO_AF7_USART2
#  if (defined(STM32GBK1CB))
#    error "PD5 can not be configured as USART2 TX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* USART2_TX_ID */

#if (USART2_RX_ID == 0)
#elif (USART2_RX_ID == 1)
#  define USART2_RX_AF GPIO_AF7_USART2
#elif (USART2_RX_ID == 2)
#  define USART2_RX_AF GPIO_AF7_USART2
#elif (USART2_RX_ID == 3)
#  define USART2_RX_AF GPIO_AF7_USART2
#elif (USART2_RX_ID == 4)
#  define USART2_RX_AF GPIO_AF7_USART2
#  if (defined(STM32GBK1CB))
#    error "PD6 can not be configured as USART2 RX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* USART2_RX_ID */

#if (USART2_CTS_ID == 0)
#elif (USART2_CTS_ID == 1)
#  define USART2_CTS_AF GPIO_AF7_USART2
#elif (USART2_CTS_ID == 2)
#  define USART2_CTS_AF GPIO_AF7_USART2
#  if (defined(STM32GBK1CB))
#    error "PD3 can not be configured as USART2 CTS on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* USART2_CTS_ID */

#if (USART2_RTS_ID == 0)
#elif (USART2_RTS_ID == 1)
#  define USART2_RTS_AF GPIO_AF7_USART2
#elif (USART2_RTS_ID == 2)
#  define USART2_RTS_AF GPIO_AF7_USART2
#  if (defined(STM32GBK1CB))
#    error "PD4 can not be configured as USART2 RTS on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* USART2_RTS_ID */

extern UART_HandleTypeDef usart2_handle;

uint8_t usart2_init(uint32_t baud_rate);
uint8_t usart2_deinit(void); 

#  if USART2_RX_DMA
#    define USART2_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(USART2_RX_DMA_NUMBER, USART2_RX_DMA_CHANNEL)
#    define USART2_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(USART2_RX_DMA_NUMBER, USART2_RX_DMA_CHANNEL)
#  endif /* USART2_RX_DMA */

#  if USART2_TX_DMA
#    define USART2_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(USART2_TX_DMA_NUMBER, USART2_TX_DMA_CHANNEL)
#    define USART2_TX_DMA_IRQHandler                                             \
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

#if (USART3_TX_ID == 0)
#elif (USART3_TX_ID == 1)
#  define USART3_TX_AF GPIO_AF7_USART3
#elif (USART3_TX_ID == 2)
#  define USART3_TX_AF GPIO_AF7_USART3
#elif (USART3_TX_ID == 3)
#  define USART3_TX_AF GPIO_AF7_USART3
#  if (defined(STM32GBK1CB))
#    error "PC10 can not be configured as USART3 TX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (USART3_TX_ID == 4)
#  define USART3_TX_AF GPIO_AF7_USART3
#  if (defined(STM32GBK1CB))
#    error "PD8 can not be configured as USART3 TX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* USART3_TX_ID */

#if (USART3_RX_ID == 0)
#elif (USART3_RX_ID == 1)
#  define USART3_RX_AF GPIO_AF7_USART3
#elif (USART3_RX_ID == 2)
#  define USART3_RX_AF GPIO_AF7_USART3
#elif (USART3_RX_ID == 3)
#  define USART3_RX_AF GPIO_AF7_USART3
#  if (defined(STM32GBK1CB))
#    error "PC11 can not be configured as USART3 RX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (USART3_RX_ID == 4)
#  define USART3_RX_AF GPIO_AF7_USART3
#  if (defined(STM32GBK1CB))
#    error "PD9 can not be configured as USART3 RX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (USART3_RX_ID == 5)
#  define USART3_RX_AF GPIO_AF7_USART3
#  if (defined(STM32GBK1CB))
#    error "PE15 can not be configured as USART3 RX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* USART3_RX_ID */

#if (USART3_CTS_ID == 0)
#elif (USART3_CTS_ID == 1)
#  define USART3_CTS_AF GPIO_AF7_USART3
#elif (USART3_CTS_ID == 2)
#  define USART3_CTS_AF GPIO_AF7_USART3
#elif (USART3_CTS_ID == 3)
#  define USART3_CTS_AF GPIO_AF7_USART3
#  if (defined(STM32GBK1CB))
#    error "PD11 can not be configured as USART3 CTS on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* USART3_CTS_ID */

#if (USART3_RTS_ID == 0)
#elif (USART3_RTS_ID == 1)
#  define USART3_RTS_AF GPIO_AF7_USART3
#elif (USART3_RTS_ID == 2)
#  define USART3_RTS_AF GPIO_AF7_USART3
#  if (defined(STM32GBK1CB))
#    error "PD12 can not be configured as USART3 RTS on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (USART3_RTS_ID == 3)
#  define USART3_RTS_AF GPIO_AF7_USART3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PF6 can not be configured as USART3 RTS on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* USART3_RTS_ID */

extern UART_HandleTypeDef usart3_handle;

uint8_t usart3_init(uint32_t baud_rate);
uint8_t usart3_deinit(void); 

#  if USART3_RX_DMA
#    define USART3_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(USART3_RX_DMA_NUMBER, USART3_RX_DMA_CHANNEL)
#    define USART3_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(USART3_RX_DMA_NUMBER, USART3_RX_DMA_CHANNEL)
#  endif /* USART3_RX_DMA */

#  if USART3_TX_DMA
#    define USART3_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(USART3_TX_DMA_NUMBER, USART3_TX_DMA_CHANNEL)
#    define USART3_TX_DMA_IRQHandler                                             \
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

#if (UART4_TX_ID == 0)
#elif (UART4_TX_ID == 1)
#  define UART4_TX_AF GPIO_AF5_UART4
#  if (defined(STM32GBK1CB))
#    error "PC10 can not be configured as UART4 TX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* UART4_TX_ID */

#if (UART4_RX_ID == 0)
#elif (UART4_RX_ID == 1)
#  define UART4_RX_AF GPIO_AF5_UART4
#  if (defined(STM32GBK1CB))
#    error "PC11 can not be configured as UART4 RX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* UART4_RX_ID */

#if (UART4_CTS_ID == 0)
#elif (UART4_CTS_ID == 1)
#  define UART4_CTS_AF GPIO_AF14_UART4
#  if (defined(STM32GBK1CB))
#    error "PB7 can not be configured as UART4 CTS on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* UART4_CTS_ID */

#if (UART4_RTS_ID == 0)
#elif (UART4_RTS_ID == 1)
#  define UART4_RTS_AF GPIO_AF8_UART4
#  if (defined(STM32GBK1CB))
#    error "PA15 can not be configured as UART4 RTS on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* UART4_RTS_ID */

extern UART_HandleTypeDef uart4_handle;

uint8_t uart4_init(uint32_t baud_rate);
uint8_t uart4_deinit(void); 

#  if UART4_RX_DMA
#    define UART4_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(UART4_RX_DMA_NUMBER, UART4_RX_DMA_CHANNEL)
#    define UART4_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(UART4_RX_DMA_NUMBER, UART4_RX_DMA_CHANNEL)
#  endif /* UART4_RX_DMA */

#  if UART4_TX_DMA
#    define UART4_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(UART4_TX_DMA_NUMBER, UART4_TX_DMA_CHANNEL)
#    define UART4_TX_DMA_IRQHandler                                             \
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

#if (UART5_TX_ID == 0)
#elif (UART5_TX_ID == 1)
#  define UART5_TX_AF GPIO_AF5_UART5
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB))
#    error "PC12 can not be configured as UART5 TX on STM32G431xx, STM32G441xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB)) */
#endif  /* UART5_TX_ID */

#if (UART5_RX_ID == 0)
#elif (UART5_RX_ID == 1)
#  define UART5_RX_AF GPIO_AF5_UART5
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB))
#    error "PD2 can not be configured as UART5 RX on STM32G431xx, STM32G441xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB)) */
#endif  /* UART5_RX_ID */

#if (UART5_CTS_ID == 0)
#elif (UART5_CTS_ID == 1)
#  define UART5_CTS_AF GPIO_AF14_UART5
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB))
#    error "PB5 can not be configured as UART5 CTS on STM32G431xx, STM32G441xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB)) */
#endif  /* UART5_CTS_ID */

#if (UART5_RTS_ID == 0)
#elif (UART5_RTS_ID == 1)
#  define UART5_RTS_AF GPIO_AF8_UART5
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB))
#    error "PB4 can not be configured as UART5 RTS on STM32G431xx, STM32G441xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB)) */
#endif  /* UART5_RTS_ID */

extern UART_HandleTypeDef uart5_handle;

uint8_t uart5_init(uint32_t baud_rate);
uint8_t uart5_deinit(void); 

#  if UART5_RX_DMA
#    define UART5_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(UART5_RX_DMA_NUMBER, UART5_RX_DMA_CHANNEL)
#    define UART5_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(UART5_RX_DMA_NUMBER, UART5_RX_DMA_CHANNEL)
#  endif /* UART5_RX_DMA */

#  if UART5_TX_DMA
#    define UART5_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(UART5_TX_DMA_NUMBER, UART5_TX_DMA_CHANNEL)
#    define UART5_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(UART5_TX_DMA_NUMBER, UART5_TX_DMA_CHANNEL)
#  endif /* UART5_TX_DMA */

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

#endif /* __UART_STM32G4xx_H */
