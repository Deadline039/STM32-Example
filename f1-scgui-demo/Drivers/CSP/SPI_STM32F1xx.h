/**
 * @file    SPI_STM32F1xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of SPI on STM32F1xx
 * @version 1.0
 * @date    2024-10-22
 */

#ifndef __SPI_STM32F1xx_H
#define __SPI_STM32F1xx_H

/* clang-format off */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************
 * @defgroup SPI Public Marco. 
 * @{
 */

#define SPI_INIT_OK         0
#define SPI_INIT_FAIL       1
#define SPI_INIT_DMA_FAIL   2
#define SPI_INITED          3

#define SPI_DEINIT_OK       0
#define SPI_DEINIT_FAIL     1
#define SPI_DEINIT_DMA_FAIL 2
#define SPI_NO_INIT         3

/**
 * @}
 */

/**
 * @brief SPI Clock Mode select.
 */
typedef enum {
  SPI_CLK_MODE0, /*!< Mode 0: CPOL=0; CPHA=0 */
  SPI_CLK_MODE1, /*!< Mode 1: CPOL=0; CPHA=1 */
  SPI_CLK_MODE2, /*!< Mode 2: CPOL=1; CPHA=0 */
  SPI_CLK_MODE3  /*!< Mode 3: CPOL=1; CPHA=1 */
} spi_clk_mode_t;

/*****************************************************************************
 * @defgroup SPI1 Functions
 * @{
 */

#if SPI1_ENABLE

extern SPI_HandleTypeDef spi1_handle;

uint8_t spi1_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit);
uint8_t spi1_deinit(void);

#  if SPI1_RX_DMA
#    define SPI1_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(SPI1_RX_DMA_NUMBER, SPI1_RX_DMA_CHANNEL)
#  endif /* SPI1_RX_DMA */

#  if SPI1_TX_DMA
#    define SPI1_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(SPI1_TX_DMA_NUMBER, SPI1_TX_DMA_CHANNEL)
#  endif /* SPI1_TX_DMA */

#endif /* SPI1_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup SPI2 Functions
 * @{
 */

#if SPI2_ENABLE

extern SPI_HandleTypeDef spi2_handle;

uint8_t spi2_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit);
uint8_t spi2_deinit(void);

#  if SPI2_RX_DMA
#    define SPI2_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(SPI2_RX_DMA_NUMBER, SPI2_RX_DMA_CHANNEL)
#  endif /* SPI2_RX_DMA */

#  if SPI2_TX_DMA
#    define SPI2_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(SPI2_TX_DMA_NUMBER, SPI2_TX_DMA_CHANNEL)
#  endif /* SPI2_TX_DMA */

#endif /* SPI2_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup SPI3 Functions
 * @{
 */

#if SPI3_ENABLE

extern SPI_HandleTypeDef spi3_handle;

uint8_t spi3_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit);
uint8_t spi3_deinit(void);

#  if SPI3_RX_DMA
#    define SPI3_RX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(SPI3_RX_DMA_NUMBER, SPI3_RX_DMA_CHANNEL)
#  endif /* SPI3_RX_DMA */

#  if SPI3_TX_DMA
#    define SPI3_TX_DMA_IRQHandler                                             \
      CSP_DMA_CHANNEL_IRQ(SPI3_TX_DMA_NUMBER, SPI3_TX_DMA_CHANNEL)
#  endif /* SPI3_TX_DMA */

#endif /* SPI3_ENABLE */

/**
 * @}
 */


/*****************************************************************************
 * @defgroup SPI Public Functions
 * @{
 */

uint8_t spi_rw_one_byte(SPI_HandleTypeDef *hspi, uint8_t byte);
uint16_t spi_rw_two_byte(SPI_HandleTypeDef *hspi, uint16_t tx_data);

uint8_t spi_change_speed(SPI_HandleTypeDef *hspi, uint8_t speed);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SPI_STM32F1xx_H */
