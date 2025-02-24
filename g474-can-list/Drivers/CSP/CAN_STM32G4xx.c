
/**
 * @file    CAN_STM32G4xx.c
 * @author  Deadline039
 * @brief   Chip Support Package of FDCAN on STM32G4xx
 * @version 1.0
 * @date    2025-02-05
 * @note    We will support FDCAN in the feature.
 *          Generate Automatically. 
 */

#include <CSP_Config.h>

#include "CAN_STM32G4xx.h"

#include <math.h>

/*****************************************************************************
 * @defgroup FDCAN1 Functions.
 * @{
 */
 
#if FDCAN1_ENABLE

FDCAN_HandleTypeDef fdcan1_handle = {
    .Instance = FDCAN1,
    .Init = {.FrameFormat = FDCAN_FRAME_CLASSIC,
             .Mode = FDCAN_MODE_NORMAL,
             .AutoRetransmission = ENABLE,
             .TransmitPause = DISABLE,
             .ProtocolException = ENABLE,
             .TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION}};

/**
 * @brief FDCAN1 initialization
 *
 * @param baud_rate Baud rate. Unit: Kbps.
 * @param fd_mode FDCAN frame format mode, this value can ref
 *                `FDCAN_frame_format`
 * @param prop_delay The propagation delay of bus, include cable and can
 *                   transceiver. Unit: ns.
 * @return CAN init status.
 * @retval - 0: `CAN_INIT_OK`:           Success.
 * @retval - 1: `CAN_INIT_RATE_ERR`:     Can not satisfied this baudrate in this
 *                                       condition.
 * @retval - 2: `CAN_INIT_FILTER_FAIL`:  CAN Filter init failed.
 * @retval - 3: `CAN_INIT_FAIL`:         CAN hardware init failed.
 * @retval - 4: `CAN_INIT_START_FAIL`:   CAN start failed.
 * @retval - 5: `CAN_INIT_NOTIFY_FAIL`:  Enable CAN receive notify failed.
 * @retval - 6: `CAN_INITED`:            This can is inited.
 * @attention Only support CAN Classic, we will support FDCAN in the feature.'
 */
uint8_t fdcan1_init(uint32_t baud_rate, uint32_t fd_mode, uint32_t prop_delay) {
    if (HAL_FDCAN_GetState(&fdcan1_handle) != HAL_FDCAN_STATE_RESET) {
        return CAN_INITED;
    }

    uint32_t prescale, tbs1, tbs2, tsjw;
    if (can_rate_calc(baud_rate * 1000, prop_delay, HAL_RCC_GetPCLK1Freq(),
                      &prescale, &tsjw, &tbs1, &tbs2) == 1) {
        return CAN_INIT_RATE_ERR;
    }

    fdcan1_handle.Init.FrameFormat = fd_mode;
    fdcan1_handle.Init.NominalPrescaler = prescale;
    fdcan1_handle.Init.NominalTimeSeg1 = tbs1;
    fdcan1_handle.Init.NominalTimeSeg2 = tbs2;
    fdcan1_handle.Init.NominalSyncJumpWidth = tsjw;

    if (HAL_FDCAN_Init(&fdcan1_handle) != HAL_OK) {
        return CAN_INIT_FAIL;
    }

    FDCAN_FilterTypeDef fdcan_filter_config;

    fdcan_filter_config.IdType = FDCAN_STANDARD_ID;
    fdcan_filter_config.FilterIndex = 1;
    fdcan_filter_config.FilterConfig = FDCAN_FILTER_MASK;
    fdcan_filter_config.FilterID1 = 0x000;
    fdcan_filter_config.FilterID2 = 0x000;
    fdcan_filter_config.FilterType = FDCAN_FILTER_TO_RXFIFO0;

    if (HAL_FDCAN_ConfigFilter(&fdcan1_handle, &fdcan_filter_config) !=
        HAL_OK) {
        return CAN_INIT_FILTER_FAIL;
    }

    fdcan_filter_config.IdType = FDCAN_EXTENDED_ID;
    fdcan_filter_config.FilterIndex = 2;
    fdcan_filter_config.FilterConfig = FDCAN_FILTER_MASK;
    fdcan_filter_config.FilterID1 = 0x00000000;
    fdcan_filter_config.FilterID2 = 0x00000000;
    fdcan_filter_config.FilterType = FDCAN_FILTER_TO_RXFIFO0;

    if (HAL_FDCAN_ConfigFilter(&fdcan1_handle, &fdcan_filter_config) !=
        HAL_OK) {
        return CAN_INIT_FILTER_FAIL;
    }

    if (HAL_FDCAN_ActivateNotification(&fdcan1_handle,
                                       FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
                                       FDCAN_TX_BUFFER0) != HAL_OK) {
        return CAN_INIT_NOTIFY_FAIL;
    }

    if (HAL_FDCAN_Start(&fdcan1_handle) != HAL_OK) {
        return CAN_INIT_START_FAIL;
    }

    return CAN_INIT_OK;
}

#if FDCAN1_IT0_IT_ENABLE

/**
 * @brief FDCAN1 Interrupt 0 ISR.
 *
 */
void FDCAN1_IT0_IRQHandler(void) {
    HAL_FDCAN_IRQHandler(&fdcan1_handle);
}

#endif /* FDCAN1_IT0_IT_ENABLE */

#if FDCAN1_IT1_IT_ENABLE

/**
 * @brief FDCAN1 Interrupt 1 ISR.
 *
 */
void FDCAN1_IT1_IRQHandler(void) {
    HAL_FDCAN_IRQHandler(&fdcan1_handle);
}

/**
 * @brief FDCAN1 deinitialization.
 *
 * @return Deinit status.
 * @retval - 0: `CAN_DEINIT_OK`:   Success.
 * @retval - 1: `CAN_DEINIT_FAIL`: CAN hardware deinit failed.
 * @retval - 2: `CAN_NO_INIT`:     This can is no init.
 */
uint8_t fdcan1_deinit(void) {
    if (HAL_FDCAN_GetState(&fdcan1_handle) == HAL_FDCAN_STATE_RESET) {
        return CAN_NO_INIT;
    }

    if (HAL_FDCAN_Stop(&fdcan1_handle) != HAL_OK) {
        return CAN_DEINIT_FAIL;
    }

    if (HAL_FDCAN_DeInit(&fdcan1_handle) != HAL_OK) {
        return CAN_DEINIT_FAIL;
    }

    return CAN_DEINIT_OK;
}

#endif /* FDCAN1_IT1_IT_ENABLE */

#endif /* FDCAN1_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup FDCAN2 Functions.
 * @{
 */
 
#if FDCAN2_ENABLE

FDCAN_HandleTypeDef fdcan2_handle = {
    .Instance = FDCAN2,
    .Init = {.FrameFormat = FDCAN_FRAME_CLASSIC,
             .Mode = FDCAN_MODE_NORMAL,
             .AutoRetransmission = ENABLE,
             .TransmitPause = DISABLE,
             .ProtocolException = ENABLE,
             .TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION}};

/**
 * @brief FDCAN2 initialization
 *
 * @param baud_rate Baud rate. Unit: Kbps.
 * @param fd_mode FDCAN frame format mode, this value can ref
 *                `FDCAN_frame_format`
 * @param prop_delay The propagation delay of bus, include cable and can
 *                   transceiver. Unit: ns.
 * @return CAN init status.
 * @retval - 0: `CAN_INIT_OK`:           Success.
 * @retval - 1: `CAN_INIT_RATE_ERR`:     Can not satisfied this baudrate in this
 *                                       condition.
 * @retval - 2: `CAN_INIT_FILTER_FAIL`:  CAN Filter init failed.
 * @retval - 3: `CAN_INIT_FAIL`:         CAN hardware init failed.
 * @retval - 4: `CAN_INIT_START_FAIL`:   CAN start failed.
 * @retval - 5: `CAN_INIT_NOTIFY_FAIL`:  Enable CAN receive notify failed.
 * @retval - 6: `CAN_INITED`:            This can is inited.
 * @attention Only support CAN Classic, we will support FDCAN in the feature.'
 */
uint8_t fdcan2_init(uint32_t baud_rate, uint32_t fd_mode, uint32_t prop_delay) {
    if (HAL_FDCAN_GetState(&fdcan2_handle) != HAL_FDCAN_STATE_RESET) {
        return CAN_INITED;
    }

    uint32_t prescale, tbs1, tbs2, tsjw;
    if (can_rate_calc(baud_rate * 1000, prop_delay, HAL_RCC_GetPCLK1Freq(),
                      &prescale, &tsjw, &tbs1, &tbs2) == 1) {
        return CAN_INIT_RATE_ERR;
    }

    fdcan2_handle.Init.FrameFormat = fd_mode;
    fdcan2_handle.Init.NominalPrescaler = prescale;
    fdcan2_handle.Init.NominalTimeSeg1 = tbs1;
    fdcan2_handle.Init.NominalTimeSeg2 = tbs2;
    fdcan2_handle.Init.NominalSyncJumpWidth = tsjw;

    if (HAL_FDCAN_Init(&fdcan2_handle) != HAL_OK) {
        return CAN_INIT_FAIL;
    }

    FDCAN_FilterTypeDef fdcan_filter_config;

    fdcan_filter_config.IdType = FDCAN_STANDARD_ID;
    fdcan_filter_config.FilterIndex = 1;
    fdcan_filter_config.FilterConfig = FDCAN_FILTER_MASK;
    fdcan_filter_config.FilterID1 = 0x000;
    fdcan_filter_config.FilterID2 = 0x000;
    fdcan_filter_config.FilterType = FDCAN_FILTER_TO_RXFIFO0;

    if (HAL_FDCAN_ConfigFilter(&fdcan2_handle, &fdcan_filter_config) !=
        HAL_OK) {
        return CAN_INIT_FILTER_FAIL;
    }

    fdcan_filter_config.IdType = FDCAN_EXTENDED_ID;
    fdcan_filter_config.FilterIndex = 2;
    fdcan_filter_config.FilterConfig = FDCAN_FILTER_MASK;
    fdcan_filter_config.FilterID1 = 0x00000000;
    fdcan_filter_config.FilterID2 = 0x00000000;
    fdcan_filter_config.FilterType = FDCAN_FILTER_TO_RXFIFO0;

    if (HAL_FDCAN_ConfigFilter(&fdcan2_handle, &fdcan_filter_config) !=
        HAL_OK) {
        return CAN_INIT_FILTER_FAIL;
    }

    if (HAL_FDCAN_ActivateNotification(&fdcan2_handle,
                                       FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
                                       FDCAN_TX_BUFFER0) != HAL_OK) {
        return CAN_INIT_NOTIFY_FAIL;
    }

    if (HAL_FDCAN_Start(&fdcan2_handle) != HAL_OK) {
        return CAN_INIT_START_FAIL;
    }

    return CAN_INIT_OK;
}

#if FDCAN2_IT0_IT_ENABLE

/**
 * @brief FDCAN2 Interrupt 0 ISR.
 *
 */
void FDCAN2_IT0_IRQHandler(void) {
    HAL_FDCAN_IRQHandler(&fdcan2_handle);
}

#endif /* FDCAN2_IT0_IT_ENABLE */

#if FDCAN2_IT1_IT_ENABLE

/**
 * @brief FDCAN2 Interrupt 1 ISR.
 *
 */
void FDCAN2_IT1_IRQHandler(void) {
    HAL_FDCAN_IRQHandler(&fdcan2_handle);
}

/**
 * @brief FDCAN2 deinitialization.
 *
 * @return Deinit status.
 * @retval - 0: `CAN_DEINIT_OK`:   Success.
 * @retval - 1: `CAN_DEINIT_FAIL`: CAN hardware deinit failed.
 * @retval - 2: `CAN_NO_INIT`:     This can is no init.
 */
uint8_t fdcan2_deinit(void) {
    if (HAL_FDCAN_GetState(&fdcan2_handle) == HAL_FDCAN_STATE_RESET) {
        return CAN_NO_INIT;
    }

    if (HAL_FDCAN_Stop(&fdcan2_handle) != HAL_OK) {
        return CAN_DEINIT_FAIL;
    }

    if (HAL_FDCAN_DeInit(&fdcan2_handle) != HAL_OK) {
        return CAN_DEINIT_FAIL;
    }

    return CAN_DEINIT_OK;
}

#endif /* FDCAN2_IT1_IT_ENABLE */

#endif /* FDCAN2_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup FDCAN3 Functions.
 * @{
 */
 
#if FDCAN3_ENABLE

FDCAN_HandleTypeDef fdcan3_handle = {
    .Instance = FDCAN3,
    .Init = {.FrameFormat = FDCAN_FRAME_CLASSIC,
             .Mode = FDCAN_MODE_NORMAL,
             .AutoRetransmission = ENABLE,
             .TransmitPause = DISABLE,
             .ProtocolException = ENABLE,
             .TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION}};

/**
 * @brief FDCAN3 initialization
 *
 * @param baud_rate Baud rate. Unit: Kbps.
 * @param fd_mode FDCAN frame format mode, this value can ref
 *                `FDCAN_frame_format`
 * @param prop_delay The propagation delay of bus, include cable and can
 *                   transceiver. Unit: ns.
 * @return CAN init status.
 * @retval - 0: `CAN_INIT_OK`:           Success.
 * @retval - 1: `CAN_INIT_RATE_ERR`:     Can not satisfied this baudrate in this
 *                                       condition.
 * @retval - 2: `CAN_INIT_FILTER_FAIL`:  CAN Filter init failed.
 * @retval - 3: `CAN_INIT_FAIL`:         CAN hardware init failed.
 * @retval - 4: `CAN_INIT_START_FAIL`:   CAN start failed.
 * @retval - 5: `CAN_INIT_NOTIFY_FAIL`:  Enable CAN receive notify failed.
 * @retval - 6: `CAN_INITED`:            This can is inited.
 * @attention Only support CAN Classic, we will support FDCAN in the feature.'
 */
uint8_t fdcan3_init(uint32_t baud_rate, uint32_t fd_mode, uint32_t prop_delay) {
    if (HAL_FDCAN_GetState(&fdcan3_handle) != HAL_FDCAN_STATE_RESET) {
        return CAN_INITED;
    }

    uint32_t prescale, tbs1, tbs2, tsjw;
    if (can_rate_calc(baud_rate * 1000, prop_delay, HAL_RCC_GetPCLK1Freq(),
                      &prescale, &tsjw, &tbs1, &tbs2) == 1) {
        return CAN_INIT_RATE_ERR;
    }

    fdcan3_handle.Init.FrameFormat = fd_mode;
    fdcan3_handle.Init.NominalPrescaler = prescale;
    fdcan3_handle.Init.NominalTimeSeg1 = tbs1;
    fdcan3_handle.Init.NominalTimeSeg2 = tbs2;
    fdcan3_handle.Init.NominalSyncJumpWidth = tsjw;

    if (HAL_FDCAN_Init(&fdcan3_handle) != HAL_OK) {
        return CAN_INIT_FAIL;
    }

    FDCAN_FilterTypeDef fdcan_filter_config;

    fdcan_filter_config.IdType = FDCAN_STANDARD_ID;
    fdcan_filter_config.FilterIndex = 1;
    fdcan_filter_config.FilterConfig = FDCAN_FILTER_MASK;
    fdcan_filter_config.FilterID1 = 0x000;
    fdcan_filter_config.FilterID2 = 0x000;
    fdcan_filter_config.FilterType = FDCAN_FILTER_TO_RXFIFO0;

    if (HAL_FDCAN_ConfigFilter(&fdcan3_handle, &fdcan_filter_config) !=
        HAL_OK) {
        return CAN_INIT_FILTER_FAIL;
    }

    fdcan_filter_config.IdType = FDCAN_EXTENDED_ID;
    fdcan_filter_config.FilterIndex = 2;
    fdcan_filter_config.FilterConfig = FDCAN_FILTER_MASK;
    fdcan_filter_config.FilterID1 = 0x00000000;
    fdcan_filter_config.FilterID2 = 0x00000000;
    fdcan_filter_config.FilterType = FDCAN_FILTER_TO_RXFIFO0;

    if (HAL_FDCAN_ConfigFilter(&fdcan3_handle, &fdcan_filter_config) !=
        HAL_OK) {
        return CAN_INIT_FILTER_FAIL;
    }

    if (HAL_FDCAN_ActivateNotification(&fdcan3_handle,
                                       FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
                                       FDCAN_TX_BUFFER0) != HAL_OK) {
        return CAN_INIT_NOTIFY_FAIL;
    }

    if (HAL_FDCAN_Start(&fdcan3_handle) != HAL_OK) {
        return CAN_INIT_START_FAIL;
    }

    return CAN_INIT_OK;
}

#if FDCAN3_IT0_IT_ENABLE

/**
 * @brief FDCAN3 Interrupt 0 ISR.
 *
 */
void FDCAN3_IT0_IRQHandler(void) {
    HAL_FDCAN_IRQHandler(&fdcan3_handle);
}

#endif /* FDCAN3_IT0_IT_ENABLE */

#if FDCAN3_IT1_IT_ENABLE

/**
 * @brief FDCAN3 Interrupt 1 ISR.
 *
 */
void FDCAN3_IT1_IRQHandler(void) {
    HAL_FDCAN_IRQHandler(&fdcan3_handle);
}

/**
 * @brief FDCAN3 deinitialization.
 *
 * @return Deinit status.
 * @retval - 0: `CAN_DEINIT_OK`:   Success.
 * @retval - 1: `CAN_DEINIT_FAIL`: CAN hardware deinit failed.
 * @retval - 2: `CAN_NO_INIT`:     This can is no init.
 */
uint8_t fdcan3_deinit(void) {
    if (HAL_FDCAN_GetState(&fdcan3_handle) == HAL_FDCAN_STATE_RESET) {
        return CAN_NO_INIT;
    }

    if (HAL_FDCAN_Stop(&fdcan3_handle) != HAL_OK) {
        return CAN_DEINIT_FAIL;
    }

    if (HAL_FDCAN_DeInit(&fdcan3_handle) != HAL_OK) {
        return CAN_DEINIT_FAIL;
    }

    return CAN_DEINIT_OK;
}

#endif /* FDCAN3_IT1_IT_ENABLE */

#endif /* FDCAN3_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup Public functions of CAN.
 * @{
 */

static uint32_t fdcan_clk_enabled = 0;

/**
 * @brief FDCAN Low level initialization.
 *
 * @param hfdcan The handle of FDCAN.
 */
void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef *hfdcan) {
    GPIO_InitTypeDef gpio_init_struct = {.Mode = GPIO_MODE_AF_PP,
                                         .Pull = GPIO_PULLUP,
                                         .Speed = GPIO_SPEED_FREQ_VERY_HIGH};
    RCC_PeriphCLKInitTypeDef periph_clk_init = {0};

#if FDCAN1_ENABLE
    if (hfdcan->Instance == FDCAN1) {
        periph_clk_init.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        periph_clk_init.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
        HAL_RCCEx_PeriphCLKConfig(&periph_clk_init);

        ++fdcan_clk_enabled;
        if (fdcan_clk_enabled == 1) {
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        CSP_GPIO_CLK_ENABLE(FDCAN1_TX_PORT);
        gpio_init_struct.Pin = FDCAN1_TX_PIN;
        gpio_init_struct.Alternate = FDCAN1_TX_AF;
        HAL_GPIO_Init(CSP_GPIO_PORT(FDCAN1_TX_PORT), &gpio_init_struct);

        CSP_GPIO_CLK_ENABLE(FDCAN1_RX_PORT);
        gpio_init_struct.Pin = FDCAN1_RX_PIN;
        gpio_init_struct.Alternate = FDCAN1_RX_AF;
        HAL_GPIO_Init(CSP_GPIO_PORT(FDCAN1_RX_PORT), &gpio_init_struct);

#if FDCAN1_IT0_IT_ENABLE
        HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, FDCAN1_IT0_IT_PRIORITY,
                             FDCAN1_IT0_IT_SUB);
        HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
#endif /* FDCAN1_IT0_IT_ENABLE */

#if FDCAN1_IT1_IT_ENABLE
        HAL_NVIC_SetPriority(FDCAN1_IT1_IRQn, FDCAN1_IT1_IT_PRIORITY,
                             FDCAN1_IT1_IT_SUB);
        HAL_NVIC_EnableIRQ(FDCAN1_IT1_IRQn);
#endif /* FDCAN1_IT1_IT_ENABLE */
    }
#endif /* FDCAN1_ENABLE */

#if FDCAN2_ENABLE
    if (hfdcan->Instance == FDCAN2) {
        periph_clk_init.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        periph_clk_init.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
        HAL_RCCEx_PeriphCLKConfig(&periph_clk_init);

        ++fdcan_clk_enabled;
        if (fdcan_clk_enabled == 1) {
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        CSP_GPIO_CLK_ENABLE(FDCAN2_TX_PORT);
        gpio_init_struct.Pin = FDCAN2_TX_PIN;
        gpio_init_struct.Alternate = FDCAN2_TX_AF;
        HAL_GPIO_Init(CSP_GPIO_PORT(FDCAN2_TX_PORT), &gpio_init_struct);

        CSP_GPIO_CLK_ENABLE(FDCAN2_RX_PORT);
        gpio_init_struct.Pin = FDCAN2_RX_PIN;
        gpio_init_struct.Alternate = FDCAN2_RX_AF;
        HAL_GPIO_Init(CSP_GPIO_PORT(FDCAN2_RX_PORT), &gpio_init_struct);

#if FDCAN2_IT0_IT_ENABLE
        HAL_NVIC_SetPriority(FDCAN2_IT0_IRQn, FDCAN2_IT0_IT_PRIORITY,
                             FDCAN2_IT0_IT_SUB);
        HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
#endif /* FDCAN2_IT0_IT_ENABLE */

#if FDCAN2_IT1_IT_ENABLE
        HAL_NVIC_SetPriority(FDCAN2_IT1_IRQn, FDCAN2_IT1_IT_PRIORITY,
                             FDCAN2_IT1_IT_SUB);
        HAL_NVIC_EnableIRQ(FDCAN2_IT1_IRQn);
#endif /* FDCAN2_IT1_IT_ENABLE */
    }
#endif /* FDCAN2_ENABLE */

#if FDCAN3_ENABLE
    if (hfdcan->Instance == FDCAN3) {
        periph_clk_init.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        periph_clk_init.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
        HAL_RCCEx_PeriphCLKConfig(&periph_clk_init);

        ++fdcan_clk_enabled;
        if (fdcan_clk_enabled == 1) {
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        CSP_GPIO_CLK_ENABLE(FDCAN3_TX_PORT);
        gpio_init_struct.Pin = FDCAN3_TX_PIN;
        gpio_init_struct.Alternate = FDCAN3_TX_AF;
        HAL_GPIO_Init(CSP_GPIO_PORT(FDCAN3_TX_PORT), &gpio_init_struct);

        CSP_GPIO_CLK_ENABLE(FDCAN3_RX_PORT);
        gpio_init_struct.Pin = FDCAN3_RX_PIN;
        gpio_init_struct.Alternate = FDCAN3_RX_AF;
        HAL_GPIO_Init(CSP_GPIO_PORT(FDCAN3_RX_PORT), &gpio_init_struct);

#if FDCAN3_IT0_IT_ENABLE
        HAL_NVIC_SetPriority(FDCAN3_IT0_IRQn, FDCAN3_IT0_IT_PRIORITY,
                             FDCAN3_IT0_IT_SUB);
        HAL_NVIC_EnableIRQ(FDCAN3_IT0_IRQn);
#endif /* FDCAN3_IT0_IT_ENABLE */

#if FDCAN3_IT1_IT_ENABLE
        HAL_NVIC_SetPriority(FDCAN3_IT1_IRQn, FDCAN3_IT1_IT_PRIORITY,
                             FDCAN3_IT1_IT_SUB);
        HAL_NVIC_EnableIRQ(FDCAN3_IT1_IRQn);
#endif /* FDCAN3_IT1_IT_ENABLE */
    }
#endif /* FDCAN3_ENABLE */

}

/**
 * @brief FDCAN Low level deinitialization.
 *
 * @param hfdcan The handle of FDCAN.
 */
void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef *hfdcan) {

#if FDCAN1_ENABLE
    if (hfdcan->Instance == FDCAN1) {
        --fdcan_clk_enabled;
        if (fdcan_clk_enabled == 0) {
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        HAL_GPIO_DeInit(CSP_GPIO_PORT(FDCAN1_RX_PORT), FDCAN1_RX_PIN);
        HAL_GPIO_DeInit(CSP_GPIO_PORT(FDCAN1_TX_PORT), FDCAN1_TX_PIN);
        
#if FDCAN1_IT0_IT_ENABLE
        HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
#endif /* FDCAN1_IT0_IT_ENABLE */

#if FDCAN1_IT1_IT_ENABLE
        HAL_NVIC_DisableIRQ(FDCAN1_IT1_IRQn);
#endif /* FDCAN1_IT1_IT_ENABLE */
    }
#endif /* FDCAN1_ENABLE */

#if FDCAN2_ENABLE
    if (hfdcan->Instance == FDCAN2) {
        --fdcan_clk_enabled;
        if (fdcan_clk_enabled == 0) {
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        HAL_GPIO_DeInit(CSP_GPIO_PORT(FDCAN2_RX_PORT), FDCAN2_RX_PIN);
        HAL_GPIO_DeInit(CSP_GPIO_PORT(FDCAN2_TX_PORT), FDCAN2_TX_PIN);
        
#if FDCAN2_IT0_IT_ENABLE
        HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);
#endif /* FDCAN2_IT0_IT_ENABLE */

#if FDCAN2_IT1_IT_ENABLE
        HAL_NVIC_DisableIRQ(FDCAN2_IT1_IRQn);
#endif /* FDCAN2_IT1_IT_ENABLE */
    }
#endif /* FDCAN2_ENABLE */

#if FDCAN3_ENABLE
    if (hfdcan->Instance == FDCAN3) {
        --fdcan_clk_enabled;
        if (fdcan_clk_enabled == 0) {
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        HAL_GPIO_DeInit(CSP_GPIO_PORT(FDCAN3_RX_PORT), FDCAN3_RX_PIN);
        HAL_GPIO_DeInit(CSP_GPIO_PORT(FDCAN3_TX_PORT), FDCAN3_TX_PIN);
        
#if FDCAN3_IT0_IT_ENABLE
        HAL_NVIC_DisableIRQ(FDCAN3_IT0_IRQn);
#endif /* FDCAN3_IT0_IT_ENABLE */

#if FDCAN3_IT1_IT_ENABLE
        HAL_NVIC_DisableIRQ(FDCAN3_IT1_IRQn);
#endif /* FDCAN3_IT1_IT_ENABLE */
    }
#endif /* FDCAN3_ENABLE */

}

/**
 * @brief Calcuate parameters of specific CAN Classic baudrate.
 *
 * @param[in] baud_rate CAN band rate. Unit: bps.
 * @param[in] prop_delay The propagation delay of bus, include cable and can
 *                       transceiver. Unit: ns.
 * @param[in] base_freq Base frequency of peripherals. Unit: Hz.
 * @param[out] prescale The prescale of `base_freq`.
 * @param[out] tsjw Syncronisation Jump Width
 * @param[out] tseg1 Time of segment 1.
 * @param[out] tseg2 Time of segment 2.
 * @return Calcuate status.
 * @retval - 0: No error;
 * @retval - 1: Can not satisfied this baudrate in this condition.
 * @note Only support CAN classic, we will support FDCAN in the feature.
 */
uint8_t can_rate_calc(uint32_t baud_rate, uint32_t prop_delay,
                      uint32_t base_freq, uint32_t *prescale, uint32_t *tsjw,
                      uint32_t *tseg1, uint32_t *tseg2) {

    /*## step 1: determine minimum permissible time for the prop_seg
                 segment. #################################################*/
    uint32_t t_prop_seg = 2 * prop_delay;

    /*## step 2: choose can system clock frequency. #######################*/
    uint32_t f_div;
    *prescale = 0;

    while (1) {
        ++(*prescale);
        f_div = base_freq / (*prescale);

        if (f_div / baud_rate > 25) {
            continue;
        }

        if (f_div / baud_rate < 8) {
            /* cannot divide this baudrate. */
            return 1;
        }

        if (f_div % baud_rate != 0) {
            continue;
        } else {
            break;
        }
    }

    /*## step 3: calculate prop_seg duration. ##########################*/
    uint32_t tq_per_bit = f_div / baud_rate;
    uint32_t prop_seg =
        (uint32_t)ceilf((float)(t_prop_seg * f_div) / 1000000000.0f);

    /*## step 4: determine phase_seg1, phase_seg2 */
    uint32_t tq_remain = tq_per_bit - prop_seg - 1;
    if (tq_remain < 3) {
        /* frequency division is from small to large, which means that if
         * the condition is met, the frequency division coefficient must be
         * the highest. if even the highest frequency cannot meet this
         * condition, then there is no other way. */
        return 1;
    }

    if (tq_remain == 3) {
        /* if the remaining number is equal to 3, than phase_seg1 = 1 and
         * phase_seg2 = 2 */
        *tseg1 = 1;
        *tseg2 = 2;
    } else {
        /* if the remain number is an odd number greater than 3, than add
         * one to the prop_seg (also subtract one to the remain number)*/
        tq_remain = (tq_remain % 2 == 0) ? (tq_remain) : (tq_remain - 1);

        /* divide the remaining number by to and assign the result to
         * phase_seg1 and phase_seg2. */
        *tseg1 = tq_remain / 2;
        *tseg2 = tq_remain - *tseg1;
    }

    *tseg1 += prop_seg;

    if (*tseg2 > 128) {
        /* STM32G4 CAN BS2 range: 2-128 */
        *tseg2 = 128;
        *tseg1 = tq_remain - *tseg2;
    }
    if (*tseg1 > 256) {
        /* STM32G4 CAN BS1 range: 2-256 */
        return 1;
    }

    /*## step 5: determine trjw (also called tsjw) #########################*/
    /* rjw is the smaller of 4 and phase_seg1. */
    *tsjw = (*tseg1 > 4) ? (4) : (*tseg1);

    /*## skip step 6: calculate required oscillator. #######################*/
    return 0;
}

/**
 * @brief Get the FDCAN handle with specificd CAN.
 *
 * @param can_selected Specific which can will to get.
 * @return The handle of FDCAN. return NULL which the FDCAN doesn't exist.
 */
FDCAN_HandleTypeDef *fdcan_get_handle(can_selected_t can_selected) {
    switch (can_selected) {

#if FDCAN1_ENABLE
        case can1_selected:
            return &fdcan1_handle;
#endif /* CAN1_ENABLE */

#if FDCAN2_ENABLE
        case can2_selected:
            return &fdcan2_handle;
#endif /* CAN2_ENABLE */

#if FDCAN3_ENABLE
        case can3_selected:
            return &fdcan3_handle;
#endif /* CAN3_ENABLE */

        default:
            return NULL;
    }
}

/**
 * @brief FDCAN Send message.
 *
 * @param can_selected Specific which CAN to send message.
 * @param can_ide Specific standard ID or Extend ID.
 * @param id Specific message id.
 * @param len Specific message length.
 * @param msg Specific message content.
 * @return Send status.
 * @retval - 0: Success.
 * @retval - 1: Send error.
 * @retval - 2: Timeout.
 * @retval - 3: Parameter invalid.
 * @retval - 4: This CAN is not initialized.
 */
uint8_t fdcan_send_message(can_selected_t can_selected, uint32_t can_ide,
                           uint32_t id, uint8_t len, const uint8_t *msg) {
    FDCAN_HandleTypeDef *fdcan_handle = fdcan_get_handle(can_selected);
    if (fdcan_handle == NULL) {
        return 3;
    }

    switch (len) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            break;

        case 12: {
            len = 0x9;
        } break;

        case 16: {
            len = 0xA;
        } break;

        case 20: {
            len = 0xB;
        } break;

        case 24: {
            len = 0xC;
        } break;

        case 32: {
            len = 0xD;
        } break;

        case 48: {
            len = 0xE;
        } break;

        case 64: {
            len = 0xF;
        } break;

        default:
            return 3;
    }

    if (HAL_FDCAN_GetState(fdcan_handle) == HAL_FDCAN_STATE_RESET) {
        return 4;
    }

    uint16_t wait_time = 0;

    static FDCAN_TxHeaderTypeDef tx_header;
    tx_header.IdType = can_ide;
    tx_header.DataLength = len;
    tx_header.Identifier = id;
    tx_header.TxFrameType = FDCAN_DATA_FRAME;

    while (HAL_FDCAN_GetTxFifoFreeLevel(fdcan_handle) == 0) {
        /* Wait to all mailbox is empty. */
        ++wait_time;
        if (wait_time > CAN_SEND_TIMEOUT) {
            return 2;
        }
    }

    if (HAL_FDCAN_AddMessageToTxFifoQ(fdcan_handle, &tx_header, msg) !=
        HAL_OK) {
        return 1;
    }
    return 0;
}

/**
 * @brief FDCAN Send Remote message.
 *
 * @param can_selected Specific which CAN to send message.
 * @param can_ide Specific standard ID or Extend ID.
 * @param id Specific message id.
 * @param len Specific message length.
 * @param msg Specific message content.
 * @return Send status.
 * @retval - 0: Success.
 * @retval - 1: Send error.
 * @retval - 2: Timeout.
 * @retval - 3: Parameter invalid.
 * @retval - 4: This CAN is not initialized.
 */
uint8_t fdcan_send_remote(can_selected_t can_selected, uint32_t can_ide,
                          uint32_t id, uint8_t len, const uint8_t *msg) {
    FDCAN_HandleTypeDef *fdcan_handle = fdcan_get_handle(can_selected);
    if (fdcan_handle == NULL) {
        return 3;
    }

    switch (len) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            break;

        case 12: {
            len = 0x9;
        } break;

        case 16: {
            len = 0xA;
        } break;

        case 20: {
            len = 0xB;
        } break;

        case 24: {
            len = 0xC;
        } break;

        case 32: {
            len = 0xD;
        } break;

        case 48: {
            len = 0xE;
        } break;

        case 64: {
            len = 0xF;
        } break;

        default:
            return 3;
    }

    if (HAL_FDCAN_GetState(fdcan_handle) == HAL_FDCAN_STATE_RESET) {
        return 4;
    }

    uint16_t wait_time = 0;

    static FDCAN_TxHeaderTypeDef tx_header;
    tx_header.IdType = can_ide;
    tx_header.DataLength = len;
    tx_header.Identifier = id;
    tx_header.TxFrameType = FDCAN_REMOTE_FRAME;

    while (HAL_FDCAN_GetTxFifoFreeLevel(fdcan_handle) == 0) {
        /* Wait to all mailbox is empty. */
        ++wait_time;
        if (wait_time > CAN_SEND_TIMEOUT) {
            return 2;
        }
    }

    if (HAL_FDCAN_AddMessageToTxFifoQ(fdcan_handle, &tx_header, msg) !=
        HAL_OK) {
        return 1;
    }
    return 0;
}

/**
 * @}
 */
