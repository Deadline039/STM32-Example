/**
 * @file    I2C_STM32F1xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of I2C on STM32F1xx
 * @version 1.0
 * @date    2024-10-22
 */

#ifndef __I2C_STM32F1xx_H
#define __I2C_STM32F1xx_H

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
      CSP_DMA_CHANNEL_IRQ(I2C1_RX_DMA_NUMBER, I2C1_RX_DMA_CHANNEL)
#  endif /* I2C1_RX_DMA */

#  if I2C1_TX_DMA
#    define I2C1_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C1_TX_DMA_NUMBER, I2C1_TX_DMA_CHANNEL)
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

extern I2C_HandleTypeDef i2c2_handle;

uint8_t i2c2_init(uint32_t clock_speed, uint32_t address,
                  uint32_t address_mode);
uint8_t i2c2_deinit(void);

#  if I2C2_RX_DMA
#    define I2C2_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C2_RX_DMA_NUMBER, I2C2_RX_DMA_CHANNEL)
#  endif /* I2C2_RX_DMA */

#  if I2C2_TX_DMA
#    define I2C2_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C2_TX_DMA_NUMBER, I2C2_TX_DMA_CHANNEL)
#  endif /* I2C2_TX_DMA */

#endif /* I2C2_ENABLE */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __I2C_STM32F7XX_H */
