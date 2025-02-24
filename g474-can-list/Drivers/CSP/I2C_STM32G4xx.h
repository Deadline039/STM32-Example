
/**
 * @file    I2C_STM32G4xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of I2C on STM32G4xx
 * @version 1.0
 * @date    2025-02-05
 * @note    Generate Automatically.
 */

#ifndef __I2C_STM32G4XX_H
#define __I2C_STM32G4XX_H

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

#if (I2C1_SCL_ID == 0)
#  define I2C1_SCL_AF GPIO_AF4_I2C1
#  if (defined(STM32G471xx) || defined(STM32G473xx) || defined(STM32G483xx))
#    error "PA13 can not be configured as I2C1 SCL on STM32G471xx, STM32G473xx, STM32G483xx! "
#  endif  /* (defined(STM32G471xx) || defined(STM32G473xx) || defined(STM32G483xx)) */
#elif (I2C1_SCL_ID == 1)
#  define I2C1_SCL_AF GPIO_AF4_I2C1
#elif (I2C1_SCL_ID == 2)
#  define I2C1_SCL_AF GPIO_AF4_I2C1
#elif (I2C1_SCL_ID == 3)
#  define I2C1_SCL_AF GPIO_AF4_I2C1
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PB6 can not be configured as I2C1 SCL on STM32G431xx, STM32G441xx, STM32G474xx, STM32G484xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* I2C1_SCL_ID */

#if (I2C1_SDA_ID == 0)
#  define I2C1_SDA_AF GPIO_AF4_I2C1
#elif (I2C1_SDA_ID == 1)
#  define I2C1_SDA_AF GPIO_AF4_I2C1
#elif (I2C1_SDA_ID == 2)
#  define I2C1_SDA_AF GPIO_AF4_I2C1
#endif  /* I2C1_SDA_ID */

extern I2C_HandleTypeDef i2c1_handle;

uint8_t i2c1_init(uint32_t timing, uint32_t address,
                  uint32_t address_mode);
uint8_t i2c1_deinit(void); 

#  if I2C1_RX_DMA
#    define I2C1_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(I2C1_RX_DMA_NUMBER, I2C1_RX_DMA_CHANNEL)
#    define I2C1_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C1_RX_DMA_NUMBER, I2C1_RX_DMA_CHANNEL)
#  endif /* I2C1_RX_DMA */

#  if I2C1_TX_DMA
#    define I2C1_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(I2C1_TX_DMA_NUMBER, I2C1_TX_DMA_CHANNEL)
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

#if (I2C2_SCL_ID == 0)
#  define I2C2_SCL_AF GPIO_AF4_I2C2
#elif (I2C2_SCL_ID == 1)
#  define I2C2_SCL_AF GPIO_AF4_I2C2
#  if (defined(STM32GBK1CB))
#    error "PC4 can not be configured as I2C2 SCL on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (I2C2_SCL_ID == 2)
#  define I2C2_SCL_AF GPIO_AF4_I2C2
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PF6 can not be configured as I2C2 SCL on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* I2C2_SCL_ID */

#if (I2C2_SDA_ID == 0)
#  define I2C2_SDA_AF GPIO_AF4_I2C2
#  if (defined(STM32G471xx) || defined(STM32G473xx) || defined(STM32G483xx))
#    error "PA8 can not be configured as I2C2 SDA on STM32G471xx, STM32G473xx, STM32G483xx! "
#  endif  /* (defined(STM32G471xx) || defined(STM32G473xx) || defined(STM32G483xx)) */
#elif (I2C2_SDA_ID == 1)
#  define I2C2_SDA_AF GPIO_AF4_I2C2
#elif (I2C2_SDA_ID == 2)
#  define I2C2_SDA_AF GPIO_AF4_I2C2
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PA10 can not be configured as I2C2 SDA on STM32G431xx, STM32G441xx, STM32G474xx, STM32G484xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* I2C2_SDA_ID */

extern I2C_HandleTypeDef i2c2_handle;

uint8_t i2c2_init(uint32_t timing, uint32_t address,
                  uint32_t address_mode);
uint8_t i2c2_deinit(void); 

#  if I2C2_RX_DMA
#    define I2C2_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(I2C2_RX_DMA_NUMBER, I2C2_RX_DMA_CHANNEL)
#    define I2C2_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C2_RX_DMA_NUMBER, I2C2_RX_DMA_CHANNEL)
#  endif /* I2C2_RX_DMA */

#  if I2C2_TX_DMA
#    define I2C2_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(I2C2_TX_DMA_NUMBER, I2C2_TX_DMA_CHANNEL)
#    define I2C2_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C2_TX_DMA_NUMBER, I2C2_TX_DMA_CHANNEL)
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

#if (I2C3_SCL_ID == 0)
#  define I2C3_SCL_AF GPIO_AF2_I2C3
#  if (defined(STM32G471xx) || defined(STM32G473xx) || defined(STM32G483xx))
#    error "PA8 can not be configured as I2C3 SCL on STM32G471xx, STM32G473xx, STM32G483xx! "
#  endif  /* (defined(STM32G471xx) || defined(STM32G473xx) || defined(STM32G483xx)) */
#elif (I2C3_SCL_ID == 1)
#  define I2C3_SCL_AF GPIO_AF8_I2C3
#  if (defined(STM32GBK1CB))
#    error "PC8 can not be configured as I2C3 SCL on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (I2C3_SCL_ID == 2)
#  define I2C3_SCL_AF GPIO_AF2_I2C3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PA10 can not be configured as I2C3 SCL on STM32G431xx, STM32G441xx, STM32G474xx, STM32G484xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C3_SCL_ID == 3)
#  define I2C3_SCL_AF GPIO_AF4_I2C3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PF3 can not be configured as I2C3 SCL on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C3_SCL_ID == 4)
#  define I2C3_SCL_AF GPIO_AF4_I2C3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PG7 can not be configured as I2C3 SCL on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* I2C3_SCL_ID */

#if (I2C3_SDA_ID == 0)
#  define I2C3_SDA_AF GPIO_AF8_I2C3
#elif (I2C3_SDA_ID == 1)
#  define I2C3_SDA_AF GPIO_AF8_I2C3
#  if (defined(STM32GBK1CB))
#    error "PC9 can not be configured as I2C3 SDA on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (I2C3_SDA_ID == 2)
#  define I2C3_SDA_AF GPIO_AF8_I2C3
#  if (defined(STM32GBK1CB))
#    error "PC11 can not be configured as I2C3 SDA on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#elif (I2C3_SDA_ID == 3)
#  define I2C3_SDA_AF GPIO_AF4_I2C3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PF4 can not be configured as I2C3 SDA on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C3_SDA_ID == 4)
#  define I2C3_SDA_AF GPIO_AF4_I2C3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PG8 can not be configured as I2C3 SDA on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* I2C3_SDA_ID */

extern I2C_HandleTypeDef i2c3_handle;

uint8_t i2c3_init(uint32_t timing, uint32_t address,
                  uint32_t address_mode);
uint8_t i2c3_deinit(void); 

#  if I2C3_RX_DMA
#    define I2C3_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(I2C3_RX_DMA_NUMBER, I2C3_RX_DMA_CHANNEL)
#    define I2C3_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C3_RX_DMA_NUMBER, I2C3_RX_DMA_CHANNEL)
#  endif /* I2C3_RX_DMA */

#  if I2C3_TX_DMA
#    define I2C3_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(I2C3_TX_DMA_NUMBER, I2C3_TX_DMA_CHANNEL)
#    define I2C3_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C3_TX_DMA_NUMBER, I2C3_TX_DMA_CHANNEL)
#  endif /* I2C3_TX_DMA */

#endif /* I2C3_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup I2C4 Functions
 * @{
 */

#if I2C4_ENABLE

#if (I2C4_SCL_ID == 0)
#  define I2C4_SCL_AF GPIO_AF3_I2C4
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PB6 can not be configured as I2C4 SCL on STM32G431xx, STM32G441xx, STM32G474xx, STM32G484xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C4_SCL_ID == 1)
#  define I2C4_SCL_AF GPIO_AF8_I2C4
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PC6 can not be configured as I2C4 SCL on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C4_SCL_ID == 2)
#  define I2C4_SCL_AF GPIO_AF4_I2C4
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PF14 can not be configured as I2C4 SCL on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C4_SCL_ID == 3)
#  define I2C4_SCL_AF GPIO_AF4_I2C4
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PG3 can not be configured as I2C4 SCL on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C4_SCL_ID == 4)
#  define I2C4_SCL_AF GPIO_AF3_I2C4
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G473xx) || defined(STM32G483xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PA13 can not be configured as I2C4 SCL on STM32G431xx, STM32G441xx, STM32G471xx, STM32G473xx, STM32G483xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G473xx) || defined(STM32G483xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* I2C4_SCL_ID */

#if (I2C4_SDA_ID == 0)
#  define I2C4_SDA_AF GPIO_AF3_I2C4
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PB7 can not be configured as I2C4 SDA on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C4_SDA_ID == 1)
#  define I2C4_SDA_AF GPIO_AF8_I2C4
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PC7 can not be configured as I2C4 SDA on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C4_SDA_ID == 2)
#  define I2C4_SDA_AF GPIO_AF4_I2C4
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PF15 can not be configured as I2C4 SDA on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (I2C4_SDA_ID == 3)
#  define I2C4_SDA_AF GPIO_AF4_I2C4
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PG4 can not be configured as I2C4 SDA on STM32G431xx, STM32G441xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* I2C4_SDA_ID */

extern I2C_HandleTypeDef i2c4_handle;

uint8_t i2c4_init(uint32_t timing, uint32_t address,
                  uint32_t address_mode);
uint8_t i2c4_deinit(void); 

#  if I2C4_RX_DMA
#    define I2C4_RX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(I2C4_RX_DMA_NUMBER, I2C4_RX_DMA_CHANNEL)
#    define I2C4_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C4_RX_DMA_NUMBER, I2C4_RX_DMA_CHANNEL)
#  endif /* I2C4_RX_DMA */

#  if I2C4_TX_DMA
#    define I2C4_TX_DMA_IRQn                                                  \
      CSP_DMA_CHANNEL_IRQn(I2C4_TX_DMA_NUMBER, I2C4_TX_DMA_CHANNEL)
#    define I2C4_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(I2C4_TX_DMA_NUMBER, I2C4_TX_DMA_CHANNEL)
#  endif /* I2C4_TX_DMA */

#endif /* I2C4_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __I2C_STM32G4XX_H */  
