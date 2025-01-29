/**
 * @file    SPI_STM32F4xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of SPI on STM32F4xx
 * @version 1.0
 * @date    2024-10-22
 */

#ifndef __SPI_STM32F4XX_H
#define __SPI_STM32F4XX_H

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

#  if (SPI1_MISO == 1)
#    if defined(STM32F410Tx)
// SPI1 MISO available on pin: PB4
#      if (SPI1_MISO_PORT_ID != 2)
#        error "Only PB4 can be configured as SPI1 MISO on selected device!"
#      endif
#    endif
#  endif

#  if (SPI1_MOSI == 1)
#    if defined(STM32F410Tx)
// SPI1 MOSI available on pin: PB5
#      if (SPI1_MOSI_PORT_ID != 2)
#        error "Only PB5 can be configured as SPI1 MOSI on selected device!"
#      endif
#    endif
#  endif

#  if (SPI1_NSS == 1)
#    if defined(STM32F410Tx)
// SPI1 NSS available on pin: PA15
#      if ((SPI1_NSS_PORT_ID != 0) && (SPI1_NSS_PORT_ID != 2)
#        error "Only PA15 can be configured as SPI1 NSS on selected device!"
#      endif
#    endif
#  endif

extern SPI_HandleTypeDef spi1_handle;

uint8_t spi1_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit);
uint8_t spi1_deinit(void);

#  if SPI1_RX_DMA
#    define SPI1_RX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI1_RX_DMA_NUMBER, SPI1_RX_DMA_STREAM)
#  endif /* SPI1_RX_DMA */

#  if SPI1_TX_DMA
#    define SPI1_TX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI1_TX_DMA_NUMBER, SPI1_TX_DMA_STREAM)
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

#  if (SPI2_MISO == 1)
#    if defined(STM32F401xC) || defined(STM32F401xE) ||                        \
        defined(STM32F411xE) || defined(STM32F446xx)
// PI2 as SPI2 MISO not available on STM32F401xx, STM32F411xx and STM32F446xx
#      if (SPI2_MISO_PORT_ID == 3)
#        error "PI2 can not be configured as SPI2 MISO on selected device!"
#      endif
#    elif defined(STM32F410Cx)
// SPI2 MISO available on pin: PB14
#      if (SPI2_MISO_PORT_ID != 1)
#        error "Only PB14 can be configured as SPI2 MISO on selected device!"
#      endif
#    elif defined(STM32F410Rx)
// SPI2 MISO available on pins: PB14, PC2
#      if ((SPI2_MISO_PORT_ID != 1) && (SPI2_MISO_PORT_ID != 2))
#        error                                                                 \
            "Only PB14 and PC2 can be configured as SPI2 MISO on selected device!"
#      endif
#    elif defined(STM32F413xx) || defined(STM32F423xx)
// SPI2 MISO available on pins: PB14, PC2, PA12
#      if ((SPI2_MISO_PORT_ID != 1) && (SPI2_MISO_PORT_ID != 2) &&             \
           (SPI2_MISO_PORT_ID != 4))
#        error                                                                 \
            "Only PB14, PC2, PA12 can be configured as SPI2 MISO on selected device!"
#      endif
#    endif
#  endif

#  if (SPI2_MOSI == 1)
#    if defined(STM32F401xC) || defined(STM32F401xE) ||                        \
        defined(STM32F411xE) || defined(STM32F446xx)
// PI3 as SPI2 MOSI not available on STM32F401xx, STM32F411xx and STM32F446xx
#      if (SPI2_MOSI_PORT_ID == 3)
#        error "PI3 can not be configured as SPI2 MOSI on selected device!"
#      endif
#    elif defined(STM32F410Cx)
// SPI2 MOSI available on pin: PB15
#      if (SPI2_MOSI_PORT_ID != 1)
#        error "Only PB15 can be configured as SPI2 MOSI on selected device!"
#      endif
#    elif defined(STM32F410Rx)
// SPI2 MOSI available on pins: PB15, PC3
#      if ((SPI2_MOSI_PORT_ID != 1) && (SPI2_MOSI_PORT_ID != 2))
#        error                                                                 \
            "Only PB15 and PC3 can be configured as SPI2 MOSI on selected device!"
#      endif
#    elif defined(STM32F413xx) || defined(STM32F423xx)
// SPI2 MOSI available on pins: PB15, PC3, PA10
#      if ((SPI2_MOSI_PORT_ID != 1) && (SPI2_MOSI_PORT_ID != 2) &&             \
           (SPI2_MOSI_PORT_ID != 4))
#        error                                                                 \
            "Only PB15, PC3, PA10 can be configured as SPI2 MOSI on selected device!"
#      endif
#    endif
#  endif

#  if defined(STM32F410Cx)
// SPI2 SCK available on pins: PB10, PB13
#    if (SPI2_SCK_PORT_ID > 1)
#      error                                                                   \
          "Only PB10 and PB13 can be configured as SPI2 SCK on selected device!"
#    endif
#  elif defined(STM32F410Rx)
// SPI2 SCK available on pins: PB10, PB13, PC7
#    if (SPI2_SCK_PORT_ID > 2)
#      error                                                                   \
          "Only PB10, PB13 and PC7 can be configured as SPI2 SCK on selected device!"
#    endif
#  elif !defined(STM32F411xE) && !defined(STM32F446xx)
// PC7 as SPI2 SCK only available on STM32F411xx and STM32F446xx
#    if (SPI2_SCK_PORT_ID == 2)
#      error "PC7 can not be configured as SPI2 SCK on selected device!"
#    endif
#  elif defined(STM32F405xx) || defined(STM32F407xx) ||                        \
      defined(STM32F415xx) || defined(STM32F417xx)
// PD3 as SPI2 SCK not available on STM32F405xx, STM32F407xx, STM32F415xx and
// STM32F417xx
#    if (SPI2_SCK_PORT_ID == 3)
#      error "PD3 can not be configured as SPI2 SCK on selected device!"
#    endif
#  elif defined(STM32F446xx)
// PI1 as SPI2 SCK not available on STM32F446xx
#    if (SPI2_SCK_PORT_ID == 1)
#      error "PI1 can not be configured as SPI2 SCK on selected device!"
#    endif
#  elif defined(STM32F413xx) || defined(STM32F423xx)
// PI1 as SPI2 SCK not available on STM32F413xx, STM32F423xx
#    if (SPI2_SCK_PORT_ID == 4)
#      error "PI1 can not be configured as SPI2 SCK on selected device!"
#    endif
#  endif

#  if (SPI2_NSS == 1)
#    if defined(STM32F401xC) || defined(STM32F401xE) ||                        \
        defined(STM32F411xE) || defined(STM32F446xx)
// PI0 as SPI2 NSS not available on STM32F401xx, STM32F411xx and STM32F446xx
#      if (SPI2_NSS_PORT_ID == 3)
#        error "PI0 can not be configured as SPI2 NSS on selected device!"
#      endif
#    elif defined(STM32F410Cx) || defined(STM32F410Rx)
// SPI2 NSS available on pins: PB9, PB12
#      if (SPI2_NSS_PORT_ID > 2)
#        error                                                                 \
            "Only PB9 and PB12 can be configured as SPI2 NSS on selected device!"
#      endif
#    elif defined(STM32F413xx) || defined(STM32F423xx)
// PI0 as SPI2 NSS not available on STM32F413xx, STM32F423xx
#      if (SPI2_NSS_PORT_ID == 3)
#        error "PI0 can not be configured as SPI2 NSS on selected device!"
#      endif
#    endif
#  endif

extern SPI_HandleTypeDef spi2_handle;

uint8_t spi2_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit);
uint8_t spi2_deinit(void);

#  if SPI2_RX_DMA
#    define SPI2_RX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI2_RX_DMA_NUMBER, SPI2_RX_DMA_STREAM)
#  endif /* SPI2_RX_DMA */

#  if SPI2_TX_DMA
#    define SPI2_TX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI2_TX_DMA_NUMBER, SPI2_TX_DMA_STREAM)
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

#  if (SPI3_MOSI == 1)
#    if defined(STM32F405xx) || defined(STM32F407xx) ||                        \
        defined(STM32F415xx) || defined(STM32F417xx)
// PD6 as SPI3 MOSI not available on STM32F405xx, STM32F407xx, STM32F415xx and
// STM32F417xx
#      if (SPI3_MOSI_PORT_ID == 3)
#        error "PD6 can not be configured as SPI3 MOSI on selected device!"
#      endif
#    endif

#    if (defined(STM32F413xx) || defined(STM32F423xx)) &&                      \
        (SPI3_MOSI_PORT_ID == 3)
#      define SPI3_MOSI_GPIO_AF GPIO_AF5_SPI3
#    else
#      define SPI3_MOSI_GPIO_AF GPIO_AF6_SPI3
#    endif
#  endif

#  if !defined(STM32F411xE) && !defined(STM32F412Cx) &&                        \
      !defined(STM32F412Rx) && !defined(STM32F412Vx) &&                        \
      !defined(STM32F412Zx) && !defined(STM32F413xx) && !defined(STM32F423xx)
// PB12 as SPI3 SCK not available on STM32F411xx, STM32F412xx, STM32F413xx and
// STM32F423xx
#    if (SPI3_SCK_PORT_ID == 1)
#      error "PB12 can not be configured as SPI3 SCK on selected device!"
#    endif
#  endif

#  if (defined(STM32F413xx) || defined(STM32F423xx)) && (SPI3_SCK_PORT_ID == 1)
#    define SPI3_SCK_GPIO_AF GPIO_AF7_SPI3
#  else
#    define SPI3_SCK_GPIO_AF GPIO_AF6_SPI3
#  endif

extern SPI_HandleTypeDef spi3_handle;

uint8_t spi3_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit);
uint8_t spi3_deinit(void);

#  if SPI3_RX_DMA
#    define SPI3_RX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI3_RX_DMA_NUMBER, SPI3_RX_DMA_STREAM)
#  endif /* SPI3_RX_DMA */

#  if SPI3_TX_DMA
#    define SPI3_TX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI3_TX_DMA_NUMBER, SPI3_TX_DMA_STREAM)
#  endif /* SPI3_TX_DMA */

#endif /* SPI3_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup SPI4 Functions
 * @{
 */

#if SPI4_ENABLE

#  if (SPI4_MISO == 1)
#    ifndef STM32F411xE
// PA11 as SPI4 MISO only available on STM32F411xx
#      if (SPI4_MISO_PORT_ID == 1)
#        error "PA11 can not be configured as SPI4 MISO on selected device!"
#      endif
#    endif

#    if (defined(STM32F413xx) || defined(STM32F423xx)) &&                      \
        (SPI4_MISO_PORT_ID == 1)
#      define SPI4_MISO_GPIO_AF GPIO_AF6_SPI4
#    else
#      define SPI4_MISO_GPIO_AF GPIO_AF5_SPI4
#    endif
#  endif

#  if (SPI4_MOSI == 1)
#    ifndef STM32F411xE
// PA1 as SPI4 MOSI only available on STM32F411xx
#      if (SPI4_MOSI_PORT_ID == 1)
#        error "PA1 can not be configured as SPI4 MOSI on selected device!"
#      endif
#    endif
#  endif

#  ifndef STM32F411xE
// PB13 as SPI4 SCK only available on STM32F411xx
#    if (SPI4_SCK_PORT_ID == 0)
#      error "PB13 can not be configured as SPI4 SCK on selected device!"
#    endif
#  endif
#  if (defined(STM32F413xx) || defined(STM32F423xx)) && (SPI4_SCK_PORT_ID == 0)
#    define SPI4_SCK_GPIO_AF GPIO_AF6_SPI4
#  else
#    define SPI4_SCK_GPIO_AF GPIO_AF5_SPI4
#  endif

#  if (SPI4_NSS == 1)
#    ifndef STM32F411xE
// PB12 as SPI4 NSS only available on STM32F411xx
#      if (SPI4_NSS_PORT_ID == 1)
#        error "PB12 can not be configured as SPI4 NSS on selected device!"
#      endif
#    endif

#    if (defined(STM32F413xx) || defined(STM32F423xx)) &&                      \
        (SPI4_NSS_PORT_ID == 1)
#      define SPI4_NSS_GPIO_AF GPIO_AF6_SPI4
#    else
#      define SPI4_NSS_GPIO_AF GPIO_AF5_SPI4
#    endif
#  endif

extern SPI_HandleTypeDef spi4_handle;

uint8_t spi4_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit);
uint8_t spi4_deinit(void);

#  if SPI4_RX_DMA
#    define SPI4_RX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI4_RX_DMA_NUMBER, SPI4_RX_DMA_STREAM)
#  endif /* SPI4_RX_DMA */

#  if SPI4_TX_DMA
#    define SPI4_TX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI4_TX_DMA_NUMBER, SPI4_TX_DMA_STREAM)
#  endif /* SPI4_TX_DMA */

#endif /* SPI4_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup SPI5 Functions
 * @{
 */

#if SPI5_ENABLE

#  if (SPI5_MISO == 1)
#    if defined(STM32F410Cx) || defined(STM32F410Rx)
// SPI5 MISO available on pin: PA12
#      if (SPI5_MISO_PORT_ID != 1)
#        error "Only PA12 can be configured as SPI5 MISO on selected device!"
#      endif
#    elif !defined(STM32F411xE)
// PA12 as SPI5 MISO only available on STM32F411xx
#      if (SPI5_MISO_PORT_ID == 1)
#        error "PA12 can not be configured as SPI5 MISO on selected device!"
#      endif

// PE5 as SPI5 MISO only available on STM32F411xx
#      if (SPI5_MISO_PORT_ID == 2)
#        error "PE5 can not be configured as SPI5 MISO on selected device!"
#      endif

// PE13 as SPI5 MISO only available on STM32F411xx
#      if (SPI5_MISO_PORT_ID == 3)
#        error "PE13 can not be configured as SPI5 MISO on selected device!"
#      endif
#    else
// PF8 as SPI5 MISO only available on STM32F427xx, STM32F429xx, STM32F437xx and
// STM32F439xx
#      if (SPI5_MISO_PORT_ID == 4)
#        error "PF8 can not be configured as SPI5 MISO on selected device!"
#      endif

// PH7 as SPI5 MISO only available on STM32F427xx, STM32F429xx, STM32F437xx and
// STM32F439xx
#      if (SPI5_MISO_PORT_ID == 5)
#        error "PH7 can not be configured as SPI5 MISO on selected device!"
#      endif
#    endif

#    if defined(STM32F410Tx) || defined(STM32F410Cx) ||                        \
        defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx)
#      define SPI5_MISO_GPIO_AF GPIO_AF6_SPI5
#    else
#      define SPI5_MISO_GPIO_AF GPIO_AF5_SPI5
#    endif
#  endif

#  if (SPI5_MOSI == 1)
#    if defined(STM32F410Cx) || defined(STM32F410Rx)
// SPI5 MOSI available on pins: PA10, PB8
#      if ((SPI5_MOSI_PORT_ID != 1) && (SPI5_MOSI_PORT_ID != 2))
#        error                                                                 \
            "Only PA10 and PB8 can be configured as SPI5 MOSI on selected device!"
#      endif
#    elif !defined(STM32F411xE)
// PA10 as SPI5 MOSI only available on STM32F411xx
#      if (SPI5_MOSI_PORT_ID == 1)
#        error "PA10 can not be configured as SPI5 MOSI on selected device!"
#      endif

// PB8 as SPI5 MOSI only available on STM32F411xx
#      if (SPI5_MOSI_PORT_ID == 2)
#        error "PB8 can not be configured as SPI5 MOSI on selected device!"
#      endif

// PE6 as SPI5 MOSI only available on STM32F411xx
#      if (SPI5_MOSI_PORT_ID == 3)
#        error "PE6 can not be configured as SPI5 MOSI on selected device!"
#      endif

// PE14 as SPI5 MOSI only available on STM32F411xx
#      if (SPI5_MOSI_PORT_ID == 4)
#        error "PE14 can not be configured as SPI5 MOSI on selected device!"
#      endif
#    else
// PF9 as SPI5 MOSI only available on STM32F427xx, STM32F429xx, STM32F437xx and
// STM32F439xx
#      if (SPI5_MOSI_PORT_ID == 5)
#        error "PF9 can not be configured as SPI5 MOSI on selected device!"
#      endif

// PF11 as SPI5 MOSI only available on STM32F427xx, STM32F429xx, STM32F437xx and
// STM32F439xx
#      if (SPI5_MOSI_PORT_ID == 6)
#        error "PF11 can not be configured as SPI5 MOSI on selected device!"
#      endif
#    endif

#    if defined(STM32F410Tx) || defined(STM32F410Cx) ||                        \
        defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx)
#      define SPI5_MOSI_GPIO_AF GPIO_AF6_SPI5
#    else
#      define SPI5_MOSI_GPIO_AF GPIO_AF5_SPI5
#    endif
#  endif

#  if defined(STM32F410Cx) || defined(STM32F410Rx)
// SPI5 SCK available on pin: PB0
#    if (SPI5_SCK_PORT_ID != 0)
#      error "Only PB0 can be configured as SPI5 SCK on selected device!"
#    endif
#  elif !defined(STM32F411xE)
// PB0 as SPI5 SCK only available on STM32F411xx
#    if (SPI5_SCK_PORT_ID == 0)
#      error "PB0 can not be configured as SPI5 SCK on selected device!"
#    endif

// PE2 as SPI5 SCK only available on STM32F411xx
#    if (SPI5_SCK_PORT_ID == 1)
#      error "PE2 can not be configured as SPI5 SCK on selected device!"
#    endif

// PE12 as SPI5 SCK only available on STM32F411xx
#    if (SPI5_SCK_PORT_ID == 2)
#      error "PE12 can not be configured as SPI5 SCK on selected device!"
#    endif
#  else
// PF7 as SPI5 SCK only available on STM32F427xx, STM32F429xx, STM32F437xx and
// STM32F439xx
#    if (SPI5_SCK_PORT_ID == 3)
#      error "PF7 can not be configured as SPI5 SCK on selected device!"
#    endif

// PH6 as SPI5 SCK only available on STM32F427xx, STM32F429xx, STM32F437xx and
// STM32F439xx
#    if (SPI5_SCK_PORT_ID == 4)
#      error "PH6 can not be configured as SPI5 SCK on selected device!"
#    endif
#  endif

#  if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) ||  \
      defined(STM32F413xx) || defined(STM32F423xx)
#    define SPI5_SCK_GPIO_AF GPIO_AF6_SPI5
#  else
#    define SPI5_SCK_GPIO_AF GPIO_AF5_SPI5
#  endif

#  if (SPI5_NSS == 1)
#    if defined(STM32F410Cx) || defined(STM32F410Rx)
// SPI5 NSS available on pin: PB1
#      if ((SPI5_NSS_PORT_ID != 0) && (SPI5_NSS_PORT_ID != 1))
#        error "Only PB1 can be configured as SPI5 NSS on selected device!"
#      endif
#    elif !defined(STM32F411xE)
// PB1 as SPI5 NSS only available on STM32F411xx
#      if (SPI5_NSS_PORT_ID == 1)
#        error "PB1 can not be configured as SPI5 NSS on selected device!"
#      endif

// PE4 as SPI5 NSS only available on STM32F411xx
#      if (SPI5_NSS_PORT_ID == 2)
#        error "PE4 can not be configured as SPI5 NSS on selected device!"
#      endif

// PE11 as SPI5 NSS only available on STM32F411xx
#      if (SPI5_NSS_PORT_ID == 3)
#        error "PE11 can not be configured as SPI5 NSS on selected device!"
#      endif
#    else
// PF6 as SPI5 NSS only available on STM32F427xx, STM32F429xx, STM32F437xx and
// STM32F439xx
#      if (SPI5_NSS_PORT_ID == 4)
#        error "PF6 can not be configured as SPI5 NSS on selected device!"
#      endif

// PH5 as SPI5 NSS only available on STM32F427xx, STM32F429xx, STM32F437xx and
// STM32F439xx
#      if (SPI5_NSS_PORT_ID == 5)
#        error "PH5 can not be configured as SPI5 NSS on selected device!"
#      endif
#    endif

#    if defined(STM32F413xx) || defined(STM32F423xx)
#      define SPI5_NSS_GPIO_AF GPIO_AF6_SPI5
#    else
#      define SPI5_NSS_GPIO_AF GPIO_AF5_SPI5
#    endif
#  endif

extern SPI_HandleTypeDef spi5_handle;

uint8_t spi5_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit);
uint8_t spi5_deinit(void);

#  if SPI5_RX_DMA
#    define SPI5_RX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI5_RX_DMA_NUMBER, SPI5_RX_DMA_STREAM)
#  endif /* SPI5_RX_DMA */

#  if SPI5_TX_DMA
#    define SPI5_TX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI5_TX_DMA_NUMBER, SPI5_TX_DMA_STREAM)
#  endif /* SPI5_TX_DMA */

#endif /* SPI5_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup SPI6 Functions
 * @{
 */

#if SPI6_ENABLE

#  if (defined(STM32F413xx) && defined(STM32F423xx))
#    error "SPI6 not available for STM32F413xx or STM32F423xx!"
#  endif

extern SPI_HandleTypeDef spi6_handle;

uint8_t spi6_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit);
uint8_t spi6_deinit(void);

#  if SPI6_RX_DMA
#    define SPI6_RX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI6_RX_DMA_NUMBER, SPI6_RX_DMA_STREAM)
#  endif /* SPI6_RX_DMA */

#  if SPI6_TX_DMA
#    define SPI6_TX_DMA_IRQHandler                                             \
      CSP_DMA_STREAM_IRQ(SPI6_TX_DMA_NUMBER, SPI6_TX_DMA_STREAM)
#  endif /* SPI6_TX_DMA */

#endif /* SPI6_ENABLE */

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

#endif /* __SPI_STM32F4XX_H */
