/**
 * @file    sdio_sdcard.h
 * @author  Deadline039
 * @brief   SD 卡读写操作
 * @version 0.1
 * @date    2024-04-18
 */

#ifndef __SDIO_SDCARD_H
#define __SDIO_SDCARD_H

#include <CSP_Config.h>

/* SDIO的信号线: SDIO_D0 ~ SDIO_D3/SDIO_CLK/SDIO_CMD 引脚定义 */
#define SD_D0_GPIO_PORT      GPIOC
#define SD_D0_GPIO_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
#define SD_D0_GPIO_PIN       GPIO_PIN_8

#define SD_D1_GPIO_PORT      GPIOC
#define SD_D1_GPIO_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
#define SD_D1_GPIO_PIN       GPIO_PIN_9

#define SD_D2_GPIO_PORT      GPIOC
#define SD_D2_GPIO_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
#define SD_D2_GPIO_PIN       GPIO_PIN_10

#define SD_D3_GPIO_PORT      GPIOC
#define SD_D3_GPIO_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
#define SD_D3_GPIO_PIN       GPIO_PIN_11

#define SD_CLK_GPIO_PORT     GPIOC
#define SD_CLK_GPIO_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
#define SD_CLK_GPIO_PIN      GPIO_PIN_12

#define SD_CMD_GPIO_PORT     GPIOD
#define SD_CMD_GPIO_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()
#define SD_CMD_GPIO_PIN      GPIO_PIN_2

#define SD_TIMEOUT           ((uint32_t)100000000) /* 超时时间 */

/* 根据 SD_HandleTypeDef 定义的宏, 用于快速计算容量 */
#define SD_TOTAL_SIZE_BYTE(__Handle__)                                         \
    (((uint64_t)((__Handle__)->SdCard.LogBlockNbr) *                           \
      ((__Handle__)->SdCard.LogBlockSize)) >>                                  \
     0)
#define SD_TOTAL_SIZE_KB(__Handle__)                                           \
    (((uint64_t)((__Handle__)->SdCard.LogBlockNbr) *                           \
      ((__Handle__)->SdCard.LogBlockSize)) >>                                  \
     10)
#define SD_TOTAL_SIZE_MB(__Handle__)                                           \
    (((uint64_t)((__Handle__)->SdCard.LogBlockNbr) *                           \
      ((__Handle__)->SdCard.LogBlockSize)) >>                                  \
     20)
#define SD_TOTAL_SIZE_GB(__Handle__)                                           \
    (((uint64_t)((__Handle__)->SdCard.LogBlockNbr) *                           \
      ((__Handle__)->SdCard.LogBlockSize)) >>                                  \
     30)

/**
 * SD传输时钟分频,由于HAL库运行效率低,很容易产生上溢(读SD卡时)/下溢错误(写SD卡时)
 * 使用4bit模式时,需降低SDIO时钟频率,将该宏改为 1,SDIO时钟频率:
 *      48/(SDIO_TRANSF_CLK_DIV + 2) = 16M * 4bit = 64Mbps
 * 使用1bit模式时,该宏SDIO_TRANSF_CLK_DIV改为 0,SDIO时钟频率:
 *      48/(SDIO_TRANSF_CLK_DIV + 2) = 24M * 1bit = 24Mbps
 */
#define SDIO_TRANSF_CLK_DIV 1

/**
 * @brief SD卡操作状态
 */
typedef enum {
    SD_OPERATE_OK = 0x0U,    /*!< SD卡操作成功 */
    SD_INIT_ERROR,           /*!< SD卡初始化错误 */
    SD_CONFIG_WIDEBUS_ERROR, /*!< 使能宽总线错误 */
    SD_TRANSFER_OK,          /*!< SD传输完成,可以继续下一次传输 */
    SD_TRANSFER_BUSY         /*!< SD卡正忙,不可以进行下一次传输 */
} sdcard_status_t;

/* 公开SD卡信息 */
extern HAL_SD_CardInfoTypeDef g_sdcard_info;

sdcard_status_t sdcard_init(void);
void sdcard_get_info(HAL_SD_CardInfoTypeDef *card_info);
sdcard_status_t sdcard_get_state(void);
sdcard_status_t sdcard_read_disk(uint8_t *pbuf, uint32_t addr, uint32_t count);
sdcard_status_t sdcard_write_disk(uint8_t *pbuf, uint32_t addr, uint32_t count);

#endif /* __SDIO_SDCARD_H */
