/**
 * @file    UART_STM32F4xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of UART on STM32F4xx
 * @version 1.0
 * @date    2024-10-22
 */

#ifndef __UART_STM32F4XX_H
#define __UART_STM32F4XX_H

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

#  if (USART1_TX == 1)
#    if defined(STM32F410Tx)
// USART1 TX available on pins: PA15, PB6
#      if ((USART1_TX_ID != 2) && (USART1_TX_ID != 3))
#        error                                                                 \
            "Only PA15 and PB6 can be configured as USART TX on selected device!"
#      endif
#    elif !defined(STM32F411xE)
// PA15 as USART1 TX only available on STM32F411xx
#      if (USART1_TX_ID == 2)
#        error "PA15 can not be configured as USART1 TX on selected device!"
#      endif
#    endif

#  endif

#  if (USART1_RX == 1)
#    if defined(STM32F410Tx)
// USART1 RX available on pins: PB3, PB7
#      if ((USART1_RX_ID != 2) && (USART1_RX_ID != 3))
#        error                                                                 \
            "Only PB3 and PB7 can be configured as USART1 RX on selected device!"
#      endif
#    elif !defined(STM32F411xE)
// PB3 as USART1 RX only available on STM32F411xx
#      if (USART1_RX_ID == 2)
#        error "PB3 can not be configured as USART1 RX on selected device!"
#      endif
#    endif
#  endif

#  if (USART1_RTS == 1)
#    if defined(STM32F410Tx)
// USART1 CTS pin is not available
#      error "USART1 CTS pin is not available on selected device!"
#    endif
#  endif

extern UART_HandleTypeDef usart1_handle;
uint8_t usart1_init(uint32_t baud_rate);
uint8_t usart1_deinit(void);

#  if USART1_RX_DMA
#    define USART1_RX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(USART1_RX_DMA_NUMBER, USART1_RX_DMA_STREAM)
#  endif /* USART1_RX_DMA */

#  if USART1_TX_DMA
#    define USART1_TX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(USART1_TX_DMA_NUMBER, USART1_TX_DMA_STREAM)
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

#  if (USART2_TX == 1)
#    if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
// USART2 TX available on pin: PA2
#      if (USART2_TX_ID != 1)
#        error "Only PA2 can be configured as USART2 TX on selected device!"
#      endif
#    endif
#  endif

#  if (USART2_RX == 1)
#    if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
// USART2 RX available on pin: PA3
#      if (USART2_RX_ID != 1)
#        error "Only PA3 can be configured as USART2 RX on selected device!"
#      endif
#    endif
#  endif

#  if (USART2_RTS == 1)
#    if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
// USART2 CTS available on pin: PA0
#      if ((USART2_CTS_ID != 0) && (USART2_CTS_ID != 1))
#        error "Only PA0 can be configured as USART2 CTS on selected device!"
#      endif
#    endif
#  endif

#  if (USART2_CTS == 1)
#    if defined(STM32F410Tx)
// USART2 RTS is not available
#      error "USART2 RTS pin is not available on selected device!"
#    elif defined(STM32F410Cx) || defined(STM32F410Rx)
// USART2 RTS available on pin: PA1
#      if ((USART2_RTS_ID != 0) && (USART2_RTS_ID != 1))
#        error "Only PA1 can be configured as USART2 RTS on selected device!"
#      endif
#    endif
#  endif

extern UART_HandleTypeDef usart2_handle;
uint8_t usart2_init(uint32_t baud_rate);
uint8_t usart2_deinit(void);

#  if USART2_RX_DMA
#    define USART2_RX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(USART2_RX_DMA_NUMBER, USART2_RX_DMA_STREAM)
#  endif /* USART2_RX_DMA */

#  if USART2_TX_DMA
#    define USART2_TX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(USART2_TX_DMA_NUMBER, USART2_TX_DMA_STREAM)
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

#  if (USART3_CTS == 1)
#    if (USART3_CTS_ID == 1) &&                                                \
        (defined(STM32F413xx) || defined(STM32F423xx) ||                       \
         defined(STM32F412Zx) || defined(STM32F412Vx) ||                       \
         defined(STM32F412Rx) || defined(STM32F412Cx))
#      define USART3_CTS_GPIO_AF GPIO_AF8_USART3
#    else
#      define USART3_CTS_GPIO_AF GPIO_AF7_USART3
#    endif
#  endif

extern UART_HandleTypeDef usart3_handle;
uint8_t usart3_init(uint32_t baud_rate);
uint8_t usart3_deinit(void);

#  if USART3_RX_DMA
#    define USART3_RX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(USART3_RX_DMA_NUMBER, USART3_RX_DMA_STREAM)
#  endif /* USART3_RX_DMA */

#  if USART3_TX_DMA
#    define USART3_TX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(USART3_TX_DMA_NUMBER, USART3_TX_DMA_STREAM)
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

#  if (UART4_TX == 1)
#    if defined(STM32F413xx) || defined(STM32F423xx)
// UART4 TX available on pins: PA0, PD10, PA12, PD1
#      if ((UART4_TX_ID == 2))
#        error "PC10 can not be configured as UART4 TX on selected device!"
#      endif
#    else
// UART4 TX available on pins: PA0, PC10
#      if ((UART4_TX_ID != 1) && (UART4_TX_ID != 2))
#        error                                                                 \
            "PD10, PA12, PD1 can not be configured as UART4 TX on selected device!"
#      endif
#    endif
#    if ((UART4_TX_ID == 4) || (UART4_TX_ID == 5)) &&                  \
        (defined(STM32F413xx) || defined(STM32F423xx))
#      define UART4_TX_GPIO_AF GPIO_AF11_UART4
#    else
#      define UART4_TX_GPIO_AF GPIO_AF8_UART4
#    endif
#  endif

#  if (UART4_RX == 1)
#    if !defined(STM32F413xx) && !defined(STM32F423xx)
// UART4 RX available on pins: PA1, PC11
#      if ((UART4_TX_ID != 1) && (UART4_TX_ID != 2))
#        error "PA11, PD0 can not be configured as UART4 RX on selected device!"
#      endif
#    endif
#    if ((UART4_RX_ID == 3) || (UART4_RX_ID == 4)) &&                  \
        (defined(STM32F413xx) || defined(STM32F423xx))
#      define UART4_RX_GPIO_AF GPIO_AF11_UART4
#    else
#      define UART4_RX_GPIO_AF GPIO_AF8_UART4
#    endif
#  endif

extern UART_HandleTypeDef uart4_handle;
uint8_t uart4_init(uint32_t baud_rate);
uint8_t uart4_deinit(void);

#  if UART4_RX_DMA
#    define UART4_RX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART4_RX_DMA_NUMBER, UART4_RX_DMA_STREAM)
#  endif /* UART4_RX_DMA */

#  if UART4_TX_DMA
#    define UART4_TX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART4_TX_DMA_NUMBER, UART4_TX_DMA_STREAM)
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

#  if (UART5_TX == 1)
#    if !defined(STM32F413xx) && !defined(STM32F423xx)
// UART5 TX available on pins: PC12
#      if ((UART5_TX_ID != 1))
#        error                                                                 \
            "PB6, PB9, PB13 can not be configured as UART5 TX on selected device!"
#      endif
#    endif

#    if ((UART5_TX_ID == 2) || (UART5_TX_ID == 3) ||                   \
         (UART5_TX_ID == 4)) &&                                            \
        (defined(STM32F413xx) || defined(STM32F423xx))
#      define UART5_TX_GPIO_AF GPIO_AF11_UART5
#    else
#      define UART5_TX_GPIO_AF GPIO_AF8_UART5
#    endif
#  endif

#  if (UART5_RX == 1)
#    if !defined(STM32F413xx) && !defined(STM32F423xx)
// UART5 RX available on pins: PD2
#      if ((UART5_RX_ID != 1))
#        error                                                                 \
            "PB5, PB8, PB12 can not be configured as UART5 RX on selected device!"
#      endif
#    endif

#    if ((UART5_RX_ID == 2) || (UART5_RX_ID == 3) ||                   \
         (UART5_RX_ID == 4)) &&                                            \
        (defined(STM32F413xx) || defined(STM32F423xx))
#      define UART5_RX_GPIO_AF GPIO_AF11_UART5
#    else
#      define UART5_RX_GPIO_AF GPIO_AF8_UART5
#    endif
#  endif

extern UART_HandleTypeDef uart5_handle;
uint8_t uart5_init(uint32_t baud_rate);
uint8_t uart5_deinit(void);

#  if UART5_RX_DMA
#    define UART5_RX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART5_RX_DMA_NUMBER, UART5_RX_DMA_STREAM)
#  endif /* UART5_RX_DMA */

#  if UART5_TX_DMA
#    define UART5_TX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART5_TX_DMA_NUMBER, UART5_TX_DMA_STREAM)
#  endif /* UART5_TX_DMA */

#endif /* UART5_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup USART6 Functions
 * @{
 */

#if USART6_ENABLE

#  if (USART6_TX == 1)
#    if defined(STM32F410Cx) || defined(STM32F412Cx)
// USART6 TX available on pin: PA11
#      if ((USART6_TX_ID != 1)
#        error "Only PA11 can be configured as USART6 TX on selected device!"
#      endif
#    elif defined(STM32F410Rx) || defined(STM32F412Rx) || defined(STM32F412Vx)
// USART6 TX available on pins: PA11, PC6
#      if ((USART6_TX_ID != 1) && (USART6_TX_ID != 2))
#        error                                                                 \
            "Only PA11 and PC6 can be configured as USART6 TX on selected device!"
#      endif
#    elif defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
// PG14 as USART6 TX not available on STM32F401xx and STM32F411xx
#      if (USART6_TX_ID == 3)
#        error "PG14 can not be configured as USART6 TX on selected device!"
#      endif
#    elif defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
// USART6 TX available on pins: PA11, PC6, PG14
#    else
// PA11 as USART6 TX only available on STM32F401xx and STM32F411xx
#      if (USART6_TX_ID == 1)
#        error "PA11 can not be configured as USART6 TX on selected device!"
#      endif
#    endif
#  endif

#  if (USART6_RX == 1)
#    if defined(STM32F410Cx) || defined(STM32F412Cx)
// USART6 RX available on pin: PA12
#      if ((USART6_RX_ID != 1)
#        error "Only PA12 can be configured as USART6 RX on selected device!"
#      endif
#    elif defined(STM32F410Rx) || defined(STM32F412Rx) || defined(STM32F412Vx)
// USART6 RX available on pins: PA12, PC7
#      if ((USART6_RX_ID != 1) && (USART6_RX_ID != 2))
#        error                                                                 \
            "Only PA12 and PC7 can be configured as USART6 RX on selected device!"
#      endif
#    elif defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
// PG9 as USART6 RX not available on STM32F401xx and STM32F411xx
#      if (USART6_RX_ID == 3)
#        error "PG9 can not be configured as USART6 RX on selected device!"
#      endif
#    elif defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
// USART6 RX available on pins: PA12, PC7, PG9
#    else
// PA12 as USART6 RX only available on STM32F401xx and STM32F411xx
#      if (USART6_RX_ID == 1)
#        error "PA12 can not be configured as USART6 RX on selected device!"
#      endif
#    endif
#  endif

#  if (USART6_CK == 1)
#    if defined(STM32F410Cx)
// USART6 CK pin is not available
#      error "USART2 CK pin is not available on selected device!"
#    elif defined(STM32F410Rx)
// USART6 CK available on pin: PC8
#      if ((USART6_CK_ID != 0) && (USART6_CK_ID != 1)
#        error "Only PC8 can be configured as USART6 CK on selected device!"
#      endif
#    elif defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
// PG7 as USART6 CK not available on STM32F401xx and STM32F411xx
#      if (USART6_CK_ID == 2)
#        error "PG7 can not be configured as USART6 CK on selected device!"
#      endif
#    endif
#  endif

#  if (USART6_RTS == 1)
#    if defined(STM32F401xC) || defined(STM32F401xE) ||                        \
        defined(STM32F411xE) || defined(STM32F410Cx) || defined(STM32F410Rx)
#      error "CTS line not available on selected device!"
#    endif
#  endif

#  if (USART6_CTS == 1)
#    if defined(STM32F401xC) || defined(STM32F401xE) ||                        \
        defined(STM32F411xE) || defined(STM32F410Cx) || defined(STM32F410Rx)
#      error "RTS line not available on selected device!"
#    endif
#  endif

extern UART_HandleTypeDef usart6_handle;
uint8_t usart6_init(uint32_t baud_rate);
uint8_t usart6_deinit(void);

#  if USART6_RX_DMA
#    define USART6_RX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(USART6_RX_DMA_NUMBER, USART6_RX_DMA_STREAM)
#  endif /* USART6_RX_DMA */

#  if USART6_TX_DMA
#    define USART6_TX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(USART6_TX_DMA_NUMBER, USART6_TX_DMA_STREAM)
#  endif /* USART6_TX_DMA */

#endif /* USART6_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup UART7 Functions
 * @{
 */

#if UART7_ENABLE

#  if (UART7_TX == 1)
#    if !defined(STM32F413xx) && !defined(STM32F423xx)
// UART7 TX available on pins: PF7, PE8
#      if ((UART7_TX_ID == 3) || (UART7_TX_ID == 3))
#        error "PA15, PB4 can not be configured as UART7 TX on selected device!"
#      endif
#    endif
#  endif

#  if (UART7_RX == 1)
#    if !defined(STM32F413xx) && !defined(STM32F423xx)
// UART7 RX available on pins: PF6, PE7
#      if ((UART7_RX_ID == 3) || (UART7_RX_ID == 3))
#        error "PA8, PB3 can not be configured as UART7 RX on selected device!"
#      endif
#    endif
#  endif

extern UART_HandleTypeDef uart7_handle;
uint8_t uart7_init(uint32_t baud_rate);
uint8_t uart7_deinit(void);

#  if UART7_RX_DMA
#    define UART7_RX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART7_RX_DMA_NUMBER, UART7_RX_DMA_STREAM)
#  endif /* UART7_RX_DMA */

#  if UART7_TX_DMA
#    define UART7_TX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART7_TX_DMA_NUMBER, UART7_TX_DMA_STREAM)
#  endif /* UART7_TX_DMA */

#endif /* UART7_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup UART8 Functions
 * @{
 */

#if UART8_ENABLE

#  if (UART8_TX == 1)
#    if !defined(STM32F413xx) && !defined(STM32F423xx)
// UART8 TX available on pins: PE1
#      if ((UART8_TX_ID == 2))
#        error "PF9 can not be configured as UART8 TX on selected device!"
#      endif
#    endif
#  endif

#  if (UART8_RX == 1)
#    if !defined(STM32F413xx) && !defined(STM32F423xx)
// UART8 RX available on pins: PE0
#      if ((UART8_RX_ID == 2))
#        error "PF8 can not be configured as UART8 RX on selected device!"
#      endif
#    endif
#  endif

extern UART_HandleTypeDef uart8_handle;
uint8_t uart8_init(uint32_t baud_rate);
uint8_t uart8_deinit(void);

#  if UART8_RX_DMA
#    define UART8_RX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART8_RX_DMA_NUMBER, UART8_RX_DMA_STREAM)
#  endif /* UART8_RX_DMA */

#  if UART8_TX_DMA
#    define UART8_TX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART8_TX_DMA_NUMBER, UART8_TX_DMA_STREAM)
#  endif /* UART8_TX_DMA */

#endif /* UART8_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup UART9 Functions
 * @{
 */

#if UART9_ENABLE

extern UART_HandleTypeDef uart9_handle;
uint8_t uart9_init(uint32_t baud_rate);
uint8_t uart9_deinit(void);

#  if UART9_RX_DMA
#    define UART9_RX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART9_RX_DMA_NUMBER, UART9_RX_DMA_STREAM)
#  endif /* UART9_RX_DMA */

#  if UART9_TX_DMA
#    define UART9_TX_DMA_IRQHandler                                            \
      CSP_DMA_STREAM_IRQ(UART9_TX_DMA_NUMBER, UART9_TX_DMA_STREAM)
#  endif /* UART9_TX_DMA */

#endif /* UART9_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup UART10 Functions
 * @{
 */

#if UART10_ENABLE

extern UART_HandleTypeDef uart10_handle;
uint8_t uart10_init(uint32_t baud_rate);
uint8_t uart10_deinit(void);

#  if UART10_RX_DMA
#    define UART10_RX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(UART10_RX_DMA_NUMBER, UART10_RX_DMA_STREAM)
#  endif /* UART10_RX_DMA */

#  if UART10_TX_DMA
#    define UART10_TX_DMA_IRQHandler                                           \
      CSP_DMA_STREAM_IRQ(UART10_TX_DMA_NUMBER, UART10_TX_DMA_STREAM)
#  endif /* UART10_TX_DMA */

#endif /* UART10_ENABLE */

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

#endif /* __UART_STM32F4XX_H */
