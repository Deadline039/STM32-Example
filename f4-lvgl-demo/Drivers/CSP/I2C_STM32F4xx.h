/**
 * @file    I2C_STM32F4xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of I2C on STM32F4xx
 * @version 1.0
 * @date    2024-10-22
 */

#ifndef __I2C_STM32F4XX_H
#define __I2C_STM32F4XX_H

/* clang-format off */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************
 * @defgroup I2C Public Marco. 
 * @{
 */

#define I2C_INIT_OK         0
#define I2C_INIT_FAIL       1
#define I2C_INIT_DMA_FAIL   2
#define I2C_INITED          3

#define I2C_DEINIT_OK       0
#define I2C_DEINIT_FAIL     1
#define I2C_DEINIT_DMA_FAIL 2
#define I2C_NO_INIT         3

/**
 * @}
 */

/*****************************************************************************
 * @defgroup I2C1 Functions
 * @{
 */

#if I2C1_ENABLE

extern I2C_HandleTypeDef i2c1_handle;

uint8_t i2c1_init(uint32_t clock_speed, uint32_t address,
                  uint32_t address_mode);
uint8_t i2c1_deinit(void);

#  if I2C1_RX_DMA
#    define I2C1_RX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(I2C1_RX_DMA_NUMBER, I2C1_RX_DMA_STREAM)
#  endif /* I2C1_RX_DMA */

#  if I2C1_TX_DMA
#    define I2C1_TX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(I2C1_TX_DMA_NUMBER, I2C1_TX_DMA_STREAM)
#  endif /* I2C1_TX_DMA */

#endif /* I2C1_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup I2C2 Functions
 * @{
 */

#if I2C2_ENABLE

#  if (!defined(STM32F401xC)) && (!defined(STM32F401xE)) &&                    \
      (!defined(STM32F411xE)) && (!defined(STM32F446xx))
/* SDA available on pins: PB11, PF0, PH5 */
#    if (I2C2_SDA_PORT_ID != 2 && I2C2_SDA_PORT_ID != 0 &&                     \
         I2C2_SDA_PORT_ID != 1)
#      error                                                                   \
          "Only PB11, PF0 and PH5 can be configured as I2C2 SDA on selected device!"
#    endif
#  endif

#  if defined(STM32F410Rx) || defined(STM32F410Cx) || defined(STM32F410Tx)
/* SCL available on pin: PB10 */
#    if (I2C2_SCL_PORT_ID != 2)
#      error "Only PB10 can be configured as I2C2 SCL on selected device!"
#    endif

#    if defined(STM32F410Rx)
/* SDA available on pin: PB3 */
#      if (I2C2_SDA_PORT_ID != 3)
#        error "Only PB3 can be configured as I2C2 SDA on selected device!"
#      endif
#    endif

#    if defined(STM32F410Cx)
/* SDA available on pins: PB3, PB9 */
#      if ((I2C2_SDA_PORT_ID != 3) && (I2C2_SDA_PORT_ID != 4))
#        error                                                                 \
            "Only PB3 and PB9 can be configured as I2C2 SDA on selected device!"
#      endif
#    endif

#    if defined(STM32F410Tx)
/* SDA available on pins: PB3, PB9, PB11 */
#      if ((I2C2_SDA_PORT_ID != 2) && (I2C2_SDA_PORT_ID != 3) &&               \
           (I2C2_SDA_PORT_ID != 4))
#        error                                                                 \
            "Only PB3, PB9 and PB11 can be configured as I2C2 SDA on selected device!"
#      endif
#    endif

#  endif

#  if defined(STM32F411xE)
/* SDA available on pins: PB3, PB9, PB11 */
#    if (I2C2_SDA_PORT_ID != 3 && I2C2_SDA_PORT_ID != 4 &&                     \
         I2C2_SDA_PORT_ID != 2)
#      error                                                                   \
          "Only PB3, PB9 and PB11 can be configured as I2C2 SDA on selected device!"
#    endif
#  endif

#  if defined(STM32F401xC) || defined(STM32F401xE)
/* SDA available on pin: PB3 */
#    if (I2C2_SDA_PORT_ID != 3)
#      error "Only PB3 can be configured as I2C2 SDA on selected device!"
#    endif
#  endif

#  if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
/* SCL available on pin:  PB10 */
#    if (I2C2_SCL_PORT_ID != 2)
#      error "Only PB10 can be configured as I2C2 SCL on selected device!"
#    endif
#  endif

#  if defined(STM32F446xx)
/* SDA available on pins: PB3, PB11, PF0 */
#    if (I2C2_SDA_PORT_ID != 3 && I2C2_SDA_PORT_ID != 2 &&                     \
         I2C2_SDA_PORT_ID != 0)
#      error                                                                   \
          "Only PB3, PB11 and PF0 can be configured as I2C2 SDA on selected device!"
#    endif
/* SCL available on pin:  PB10, PF1 */
#    if (I2C2_SCL_PORT_ID != 2 && I2C2_SCL_PORT_ID != 0)
#      error                                                                   \
          "Only PB10 and PF1 can be configured as I2C2 SCL on selected device!"
#    endif
#  endif

#  if defined(STM32F413xx) || defined(STM32F423xx)
/* SDA available on pins: PB3, PB9, PB11, PF0 */
#    if (I2C2_SDA_PORT_ID == 1)
#      error                                                                   \
          "Only PB3, PB9, PB11 and PF0 can be configured as I2C2 SDA on selected device!"
#    endif
/* SCL available on pin:  PF1, PB10 */
#    if (I2C2_SCL_PORT_ID == 1)
#      error                                                                   \
          "Only PB10 and PF1 can be configured as I2C2 SCL on selected device!"
#    endif
#  endif
#  if (!defined(STM32F401xC)) && (!defined(STM32F401xE)) &&                    \
      (!defined(STM32F411xE)) && (!defined(STM32F446xx))
/* SDA available on pins: PB11, PF0, PH5 */
#    if (I2C2_SDA_PORT_ID != 2 && I2C2_SDA_PORT_ID != 0 &&                     \
         I2C2_SDA_PORT_ID != 1)
#      error                                                                   \
          "Only PB11, PF0 and PH5 can be configured as I2C2 SDA on selected device!"
#    endif
#  endif

#  if defined(STM32F410Rx) || defined(STM32F410Cx) || defined(STM32F410Tx)
/* SCL available on pin: PB10 */
#    if (I2C2_SCL_PORT_ID != 2)
#      error "Only PB10 can be configured as I2C2 SCL on selected device!"
#    endif

#    if defined(STM32F410Rx)
/* SDA available on pin: PB3 */
#      if (I2C2_SDA_PORT_ID != 3)
#        error "Only PB3 can be configured as I2C2 SDA on selected device!"
#      endif
#    endif

#    if defined(STM32F410Cx)
/* SDA available on pins: PB3, PB9 */
#      if ((I2C2_SDA_PORT_ID != 3) && (I2C2_SDA_PORT_ID != 4))
#        error                                                                 \
            "Only PB3 and PB9 can be configured as I2C2 SDA on selected device!"
#      endif
#    endif

#    if defined(STM32F410Tx)
/* SDA available on pins: PB3, PB9, PB11 */
#      if ((I2C2_SDA_PORT_ID != 2) && (I2C2_SDA_PORT_ID != 3) &&               \
           (I2C2_SDA_PORT_ID != 4))
#        error                                                                 \
            "Only PB3, PB9 and PB11 can be configured as I2C2 SDA on selected device!"
#      endif
#    endif

#  endif

#  if defined(STM32F411xE)
/* SDA available on pins: PB3, PB9, PB11 */
#    if (I2C2_SDA_PORT_ID != 3 && I2C2_SDA_PORT_ID != 4 &&                     \
         I2C2_SDA_PORT_ID != 2)
#      error                                                                   \
          "Only PB3, PB9 and PB11 can be configured as I2C2 SDA on selected device!"
#    endif
#  endif

#  if defined(STM32F401xC) || defined(STM32F401xE)
/* SDA available on pin: PB3 */
#    if (I2C2_SDA_PORT_ID != 3)
#      error "Only PB3 can be configured as I2C2 SDA on selected device!"
#    endif
#  endif

#  if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
/* SCL available on pin:  PB10 */
#    if (I2C2_SCL_PORT_ID != 2)
#      error "Only PB10 can be configured as I2C2 SCL on selected device!"
#    endif
#  endif

#  if defined(STM32F446xx)
/* SDA available on pins: PB3, PB11, PF0 */
#    if (I2C2_SDA_PORT_ID != 3 && I2C2_SDA_PORT_ID != 2 &&                     \
         I2C2_SDA_PORT_ID != 0)
#      error                                                                   \
          "Only PB3, PB11 and PF0 can be configured as I2C2 SDA on selected device!"
#    endif
/* SCL available on pin:  PB10, PF1 */
#    if (I2C2_SCL_PORT_ID != 2 && I2C2_SCL_PORT_ID != 0)
#      error                                                                   \
          "Only PB10 and PF1 can be configured as I2C2 SCL on selected device!"
#    endif
#  endif

#  if defined(STM32F413xx) || defined(STM32F423xx)
/* SDA available on pins: PB3, PB9, PB11, PF0 */
#    if (I2C2_SDA_PORT_ID == 1)
#      error                                                                   \
          "Only PB3, PB9, PB11 and PF0 can be configured as I2C2 SDA on selected device!"
#    endif
/* SCL available on pin:  PF1, PB10 */
#    if (I2C2_SCL_PORT_ID == 1)
#      error                                                                   \
          "Only PB10 and PF1 can be configured as I2C2 SCL on selected device!"
#    endif
#  endif

#  if defined(STM32F446xx)
/* SDA available on pins: PB3, PB11, PF0 */
#    if (I2C2_SDA_PORT_ID != 3 && I2C2_SDA_PORT_ID != 2 &&                     \
         I2C2_SDA_PORT_ID != 0)
#      error                                                                   \
          "Only PB3, PB11 and PF0 can be configured as I2C2 SDA on selected device!"
#    endif
/* SCL available on pin:  PB10, PF1 */
#    if (I2C2_SCL_PORT_ID != 2 && I2C2_SCL_PORT_ID != 0)
#      error                                                                   \
          "Only PB10 and PF1 can be configured as I2C2 SCL on selected device!"
#    endif
#  endif

#  if defined(STM32F413xx) || defined(STM32F423xx)
/* SDA available on pins: PB3, PB9, PB11, PF0 */
#    if (I2C2_SDA_PORT_ID == 1)
#      error                                                                   \
          "Only PB3, PB9, PB11 and PF0 can be configured as I2C2 SDA on selected device!"
#    endif
/* SCL available on pin:  PF1, PB10 */
#    if (I2C2_SCL_PORT_ID == 1)
#      error                                                                   \
          "Only PB10 and PF1 can be configured as I2C2 SCL on selected device!"
#    endif
#  endif

#  if ((defined(STM32F413xx) || defined(STM32F423xx)) &&                       \
       ((I2C2_SDA_PORT_ID == 3) || (I2C2_SDA_PORT_ID == 4)))
#    define I2C2_SDA_GPIO_AF GPIO_AF9_I2C2
#  else
#    define I2C2_SDA_GPIO_AF GPIO_AF4_I2C2
#  endif

extern I2C_HandleTypeDef i2c2_handle;

uint8_t i2c2_init(uint32_t clock_speed, uint32_t address,
                  uint32_t address_mode);
uint8_t i2c2_deinit(void);

#  if I2C2_RX_DMA
#    define I2C2_RX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(I2C2_RX_DMA_NUMBER, I2C2_RX_DMA_STREAM)
#  endif /* I2C2_RX_DMA */

#  if I2C2_TX_DMA
#    define I2C2_TX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(I2C2_TX_DMA_NUMBER, I2C2_TX_DMA_STREAM)
#  endif /* I2C2_TX_DMA */

#endif /* I2C2_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup I2C3 Functions
 * @{
 */

#if I2C3_ENABLE

#  if (!defined(STM32F401xC)) && (!defined(STM32F401xE)) &&                    \
      (!defined(STM32F411xE)) && (!defined(STM32F446xx))
/* SDA available on pins: PC9, PH8 */
#    if (I2C3_SDA_PORT_ID != 1 && I2C3_SDA_PORT_ID != 0)
#      error                                                                   \
          "Only PC9 and PH8 can be configured as I2C3 SDA on selected device!"
#    endif
#  endif

#  if defined(STM32F411xE)
/* SDA available on pins: PB4, PB8, PC9 */
#    if (I2C3_SDA_PORT_ID != 2 && I2C3_SDA_PORT_ID != 3 &&                     \
         I2C3_SDA_PORT_ID != 1)
#      error                                                                   \
          "Only PB4, PB8 and PC9 can be configured as I2C3 SDA on selected device!"
#    endif
#  endif

#  if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F446xx)
/* SDA available on pins: PB4, PC9 */
#    if (I2C3_SDA_PORT_ID != 2 && I2C3_SDA_PORT_ID != 1)
#      error                                                                   \
          "Only PB4 and PC9 can be configured as I2C3 SDA on selected device!"
#    endif
#  endif

#  if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) ||  \
      defined(STM32F446xx)
/* SCL available on pin:  PA8 */
#    if (I2C3_SCL_PORT_ID != 1)
#      error "Only PA8 can be configured as I2C3 SCL on selected device!"
#    endif
#  endif

#  if defined(STM32F413xx) || defined(STM32F423xx)
/* SDA available on pins: PB3, PB9, PB11, PF0 */
#    if (I2C3_SDA_PORT_ID == 0)
#      error                                                                   \
          "Only PB4, PB8, PC9 can be configured as I2C3 SDA on selected device!"
#    endif
/* SCL available on pin:  PA8 */
#    if (I2C3_SCL_PORT_ID != 1)
#      error "Only PA8 can be configured as I2C3 SCL on selected device!"
#    endif
#  endif

#  if ((defined(STM32F413xx) || defined(STM32F423xx)) &&                       \
       ((I2C3_SDA_PORT_ID == 2) || (I2C3_SDA_PORT_ID == 3)))
#    define I2C3_SDA_GPIO_AF GPIO_AF9_I2C3
#  else
#    define I2C3_SDA_GPIO_AF GPIO_AF4_I2C3
#  endif

extern I2C_HandleTypeDef i2c3_handle;

uint8_t i2c3_init(uint32_t clock_speed, uint32_t address,
                  uint32_t address_mode);
uint8_t i2c3_deinit(void);

#  if I2C3_RX_DMA
#    define I2C3_RX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(I2C3_RX_DMA_NUMBER, I2C3_RX_DMA_STREAM)
#  endif /* I2C3_RX_DMA */

#  if I2C3_TX_DMA
#    define I2C3_TX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(I2C3_TX_DMA_NUMBER, I2C3_TX_DMA_STREAM)
#  endif /* I2C3_TX_DMA */

/**
 * @}
 */

#endif /* I2C3_ENABLE */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __I2C_STM32F4XX_H */
