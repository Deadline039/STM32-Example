/**
 * @file    sdio_sdcard.c
 * @author  Deadline039
 * @brief   SD 卡读写操作
 * @version 1.0
 * @date    2024-04-18
 */

#include "sdio_sdcard.h"

static SD_HandleTypeDef sdcard_handle = {0};
HAL_SD_CardInfoTypeDef g_sdcard_info = {0};

/**
 * @brief SD 卡初始化
 *
 * @return SD 卡初始化状态
 * @retval - `SD_OPERATE_OK`           SD 卡初始化成功
 * @retval - `SD_INIT_ERROR`           SD 卡初始化错误
 * @retval - `SD_CONFIG_WIDEBUS_ERROR` 使能宽总线错误
 */
sdcard_status_t sdcard_init(void) {
    uint8_t sd_error;

    sdcard_handle.Instance = SDIO;

    sdcard_handle.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
    sdcard_handle.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
    sdcard_handle.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
    sdcard_handle.Init.BusWide = SDIO_BUS_WIDE_1B;
    sdcard_handle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
    sdcard_handle.Init.ClockDiv = SDIO_INIT_CLK_DIV;

    HAL_SD_DeInit(&sdcard_handle);
    sd_error = HAL_SD_Init(&sdcard_handle);

    if (sd_error != HAL_OK) {
        return SD_INIT_ERROR;
    }

    HAL_SD_GetCardInfo(&sdcard_handle, &g_sdcard_info);

    sd_error = HAL_SD_ConfigWideBusOperation(&sdcard_handle, SDIO_BUS_WIDE_4B);
    if (sd_error != HAL_OK) {
        return SD_CONFIG_WIDEBUS_ERROR;
    }

    return SD_OPERATE_OK;
}

/**
 * @brief SD卡底层初始化
 *
 * @param hsd SDIO 句柄
 */
void HAL_SD_MspInit(SD_HandleTypeDef *hsd) {
    if (hsd->Instance != SDIO) {
        return;
    }
    GPIO_InitTypeDef gpio_initure;

    __HAL_RCC_SDIO_CLK_ENABLE();
    SD_D0_GPIO_ENABLE();
    SD_D1_GPIO_ENABLE();
    SD_D2_GPIO_ENABLE();
    SD_D3_GPIO_ENABLE();
    SD_CLK_GPIO_ENABLE();
    SD_CMD_GPIO_ENABLE();

    gpio_initure.Mode = GPIO_MODE_AF_PP;
    gpio_initure.Pull = GPIO_PULLUP;
    gpio_initure.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_initure.Alternate = GPIO_AF12_SDIO;

    gpio_initure.Pin = SD_D0_GPIO_PIN;
    HAL_GPIO_Init(SD_D0_GPIO_PORT, &gpio_initure);

    gpio_initure.Pin = SD_D1_GPIO_PIN;
    HAL_GPIO_Init(SD_D1_GPIO_PORT, &gpio_initure);

    gpio_initure.Pin = SD_D2_GPIO_PIN;
    HAL_GPIO_Init(SD_D2_GPIO_PORT, &gpio_initure);

    gpio_initure.Pin = SD_D3_GPIO_PIN;
    HAL_GPIO_Init(SD_D3_GPIO_PORT, &gpio_initure);

    gpio_initure.Pin = SD_CLK_GPIO_PIN;
    HAL_GPIO_Init(SD_CLK_GPIO_PORT, &gpio_initure);

    gpio_initure.Pin = SD_CMD_GPIO_PIN;
    HAL_GPIO_Init(SD_CMD_GPIO_PORT, &gpio_initure);
}

/**
 * @brief SD卡获取信息
 *
 * @param[out] card_info SD卡初始化
 */
void sdcard_get_info(HAL_SD_CardInfoTypeDef *card_info) {
    HAL_SD_GetCardInfo(&sdcard_handle, card_info);
}

/**
 * @brief SD 卡获取状态
 *
 * @return SD 卡状态
 * @retval - `SD_TRANSFER_OK`:   SD 传输完成, 可以继续下一次传输
 * @retval - `SD_TRANSFER_BUSY`: SD 卡正忙, 不可以进行下一次传输
 */
sdcard_status_t sdcard_get_state(void) {
    if (HAL_SD_GetCardState(&sdcard_handle) == HAL_SD_CARD_TRANSFER) {
        return SD_TRANSFER_OK;
    } else {
        return SD_TRANSFER_BUSY;
    }
}

/**
 * @brief 读 SD 卡 (fatfs/usb 调用)
 *
 * @param[out] pbuf 数据缓存区
 * @param addr 扇区地址
 * @param count 扇区个数
 * @return 读取状态
 * @retval - `SD_OPERATE_OK`:    SD 卡读取成功
 * @retval - `SD_TRANSFER_BUSY`: SD 卡正忙
 */
sdcard_status_t sdcard_read_disk(uint8_t *pbuf, uint32_t addr, uint32_t count) {
    uint32_t timeout = SD_TIMEOUT;

    /* 关闭所有中断, 读取时不允许打断 */
    __disable_irq();
    HAL_SD_ReadBlocks(&sdcard_handle, pbuf, addr, count, SD_TIMEOUT);

    while (sdcard_get_state() != SD_TRANSFER_OK) {
        --timeout;
        if (timeout == 0) {
            return SD_TRANSFER_BUSY;
        }
    }
    /* 打开所有中断 */
    __enable_irq();
    return SD_OPERATE_OK;
}

/**
 * @brief 写 SD 卡 (fatfs/usb 调用)
 *
 * @param pbuf 数据缓存区
 * @param addr 扇区地址
 * @param count 扇区个数
 * @return 写入状态
 * @retval - `SD_OPERATE_OK`:    SD 卡写入成功
 * @retval - `SD_TRANSFER_BUSY`: SD 卡正忙
 */
sdcard_status_t sdcard_write_disk(uint8_t *pbuf, uint32_t addr,
                                  uint32_t count) {
    uint32_t timeout = SD_TIMEOUT;

    /* 关闭所有中断, 读取时不允许打断 */
    __disable_irq();
    HAL_SD_WriteBlocks(&sdcard_handle, pbuf, addr, count, SD_TIMEOUT);

    while (sdcard_get_state() != SD_TRANSFER_OK) {
        --timeout;
        if (timeout == 0) {
            return SD_TRANSFER_BUSY;
        }
    }
    /* 打开所有中断 */
    __enable_irq();
    return SD_OPERATE_OK;
}
