/**
 * @file    UART_STM32F1xx.c
 * @author  Deadline039
 * @brief   Chip Support Package of USART on STM32F1xx
 * @version 1.0
 * @date    2024-10-22
 */

#include "CSP_Config.h"

#include "UART_STM32F1xx.h"

#include "./ring_fifo/ring_fifo.h"
#include <stdio.h>
#include <string.h>

/*****************************************************************************
 * @defgroup Private types and variables of UART.
 * @{
 */

/* The buf of `uart_pirntf` and `uart_scanf`. */
static char uart_buffer[256];

/**
 * @brief Send buf of UART.
 */
typedef struct {
    uint8_t *send_buf; /*!< Send data buf.                                  */
    uint32_t head_ptr; /*!< Pointer of send buf to control the length of DMA
                            transfer.                                       */
    size_t buf_size;   /*!< The size of buffer. Prevent overflow.           */
} uart_tx_buf_t;

/**
 * @brief Receive fifo of UART.
 */
typedef struct {
    ring_fifo_t *rx_fifo; /*!< Receive fifo.                 */
    uint8_t *rx_fifo_buf; /*!< The storage area of fifo.     */
    uint8_t *recv_buf;    /*!< Data buf of DMA to transfer.  */
    uint32_t head_ptr;    /*!< Pointer of receive buf to
                               control the DMA receive.      */
    uint32_t buf_size;    /*!< Size of `rece_buf`.           */
    uint32_t fifo_size;   /*!< Size of `rx_fifo_buf`.        */
} uart_rx_fifo_t;

/**
 * @}
 */

/*****************************************************************************
 * @defgroup Private functions.
 * @{
 */

static void uart_dmarx_halfdone_callback(UART_HandleTypeDef *huart);
static void uart_dmarx_done_callback(UART_HandleTypeDef *huart);
void uart_dmarx_idle_callback(UART_HandleTypeDef *huart);

/**
 * @}
 */

/*****************************************************************************
 * @defgroup USART1 Functions
 * @{
 */

#if USART1_ENABLE

UART_HandleTypeDef usart1_handle = {.Instance = USART1,
                                    .Init = {.WordLength = UART_WORDLENGTH_8B,
                                             .StopBits = UART_STOPBITS_1,
                                             .Parity = UART_PARITY_NONE}};

#if USART1_RX_DMA

static DMA_HandleTypeDef usart1_dmarx_handle = {
    .Instance = CSP_DMA_CHANNEL(USART1_RX_DMA_NUMBER, USART1_RX_DMA_CHANNEL),
    .Init = {.Direction = DMA_PERIPH_TO_MEMORY,
             .MemDataAlignment = DMA_MDATAALIGN_BYTE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_CIRCULAR,
             .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
             .PeriphInc = DMA_PINC_DISABLE,
             .Priority = CSP_DMA_PRIORITY(USART1_RX_DMA_PRIORITY)}};

static uart_rx_fifo_t usart1_rx_fifo = {.buf_size = USART1_RX_DMA_BUF_SIZE,
                                        .fifo_size = USART1_RX_DMA_FIFO_SIZE};

#endif /* USART1_RX_DMA */

#if USART1_TX_DMA

static DMA_HandleTypeDef usart1_dmatx_handle = {
    .Instance = CSP_DMA_CHANNEL(USART1_TX_DMA_NUMBER, USART1_TX_DMA_CHANNEL),
    .Init = {.Direction = DMA_MEMORY_TO_PERIPH,
             .MemDataAlignment = DMA_MDATAALIGN_BYTE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
             .PeriphInc = DMA_PINC_DISABLE,
             .Priority = CSP_DMA_PRIORITY(USART1_TX_DMA_PRIORITY)}};

static uart_tx_buf_t usart1_tx_buf = {.buf_size = USART1_TX_DMA_BUF_SIZE};

#endif /* USART1_TX_DMA */

/**
 * @brief USART1 initialization
 *
 * @param baud_rate Baud rate.
 * @return USART1 init status.
 * @retval - 0: `UART_INIT_OK`:       Success.
 * @retval - 1: `UART_INIT_FAIL`:     UART init failed.
 * @retval - 2: `UART_INIT_DMA_FAIL`: UART DMA init failed.
 * @retval - 3: `UART_INIT_MEM_FAIL`: UART buffer memory init failed (It will
 *                                    dynamic allocate memory when using DMA).
 * @retval - 4: `UART_INITED`:        This uart is inited.
 */
uint8_t usart1_init(uint32_t baud_rate) {
    if (__HAL_RCC_USART1_IS_CLK_ENABLED()) {
        return UART_INITED;
    }

    GPIO_InitTypeDef gpio_init_struct = {.Pull = GPIO_PULLUP,
                                         .Speed = GPIO_SPEED_FREQ_HIGH};
    usart1_handle.Init.BaudRate = baud_rate;

    USART1_AFIO_REMAP();
#if USART1_TX_ENABLE
    usart1_handle.Init.Mode |= UART_MODE_TX;

    CSP_GPIO_CLK_ENABLE(USART1_TX_PORT);
    gpio_init_struct.Pin = USART1_TX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART1_TX_PORT), &gpio_init_struct);
#endif /* USART1_TX_ENABLE */

#if USART1_RX_ENABLE
    usart1_handle.Init.Mode |= UART_MODE_RX;

    CSP_GPIO_CLK_ENABLE(USART1_RX_PORT);
    gpio_init_struct.Pin = USART1_RX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART1_RX_PORT), &gpio_init_struct);
#endif /* USART1_RX_ENABLE */

#if USART1_CTS_ENABLE
    usart1_handle.Init.HwFlowCtl |= UART_HWCONTROL_CTS;

    CSP_GPIO_CLK_ENABLE(USART1_CTS_PORT);
    gpio_init_struct.Pin = USART1_CTS_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART1_CTS_PORT), &gpio_init_struct);
#endif /* USART1_USART1_CTS */

#if USART1_RTS_ENABLE
    usart1_handle.Init.HwFlowCtl |= UART_HWCONTROL_RTS;

    CSP_GPIO_CLK_ENABLE(USART1_RTS_PORT);
    gpio_init_struct.Pin = USART1_RTS_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART1_RTS_PORT), &gpio_init_struct);
#endif /* USART1_RTS_ENABLE */

    __HAL_RCC_USART1_CLK_ENABLE();

    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_SetPriority(USART1_IRQn, USART1_IT_PRIORITY, USART1_IT_SUB);

#if USART1_RX_DMA
    usart1_rx_fifo.head_ptr = 0;

    usart1_rx_fifo.recv_buf = CSP_MALLOC(usart1_rx_fifo.buf_size);
    if (usart1_rx_fifo.recv_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    usart1_rx_fifo.rx_fifo_buf = CSP_MALLOC(usart1_rx_fifo.fifo_size);
    if (usart1_rx_fifo.rx_fifo_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    usart1_rx_fifo.rx_fifo = ring_fifo_init(
        usart1_rx_fifo.rx_fifo_buf, usart1_rx_fifo.fifo_size, RF_TYPE_STREAM);
    if (usart1_rx_fifo.rx_fifo == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    CSP_DMA_CLK_ENABLE(USART1_RX_DMA_NUMBER);
    if (HAL_DMA_Init(&usart1_dmarx_handle) != HAL_OK) {
        return UART_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&usart1_handle, hdmarx, usart1_dmarx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(USART1_RX_DMA_NUMBER, USART1_RX_DMA_CHANNEL),
        USART1_RX_DMA_IT_PRIORITY, USART1_RX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART1_RX_DMA_NUMBER, USART1_RX_DMA_CHANNEL));

#endif /* USART1_RX_DMA */

#if USART1_TX_DMA
    usart1_tx_buf.send_buf = CSP_MALLOC(usart1_tx_buf.buf_size);
    if (usart1_tx_buf.send_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    CSP_DMA_CLK_ENABLE(USART1_TX_DMA_NUMBER);
    if (HAL_DMA_Init(&usart1_dmatx_handle) != HAL_OK) {
        return UART_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&usart1_handle, hdmatx, usart1_dmatx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(USART1_TX_DMA_NUMBER, USART1_TX_DMA_CHANNEL),
        USART1_TX_DMA_IT_PRIORITY, USART1_TX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART1_TX_DMA_NUMBER, USART1_TX_DMA_CHANNEL));
#endif /* USART1_TX_DMA */

    if (HAL_UART_Init(&usart1_handle) != HAL_OK) {
        return UART_INIT_FAIL;
    }

#if USART1_RX_DMA
    __HAL_UART_ENABLE_IT(&usart1_handle, UART_IT_IDLE);
    __HAL_UART_CLEAR_IDLEFLAG(&usart1_handle);

    HAL_UART_Receive_DMA(&usart1_handle, usart1_rx_fifo.recv_buf,
                         usart1_rx_fifo.buf_size);

#if USE_HAL_UART_REGISTER_CALLBACKS
    HAL_UART_RegisterCallback(&usart1_handle, HAL_UART_RX_HALFCOMPLETE_CB_ID,
                              uart_dmarx_halfdone_callback);
    HAL_UART_RegisterCallback(&usart1_handle, HAL_UART_RX_COMPLETE_CB_ID,
                              uart_dmarx_done_callback);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
#endif /* USART1_RX_DMA */
    return UART_INIT_OK;
}

/**
 * @brief USART1 ISR
 *
 */
void USART1_IRQHandler(void) {
    if (__HAL_UART_GET_FLAG(&usart1_handle, UART_FLAG_IDLE)) {
        __HAL_UART_CLEAR_IDLEFLAG(&usart1_handle);
        uart_dmarx_idle_callback(&usart1_handle);
    }

    HAL_UART_IRQHandler(&usart1_handle);
}

#if USART1_RX_DMA

/**
 * @brief USART1 Rx DMA ISR
 *
 */
void USART1_RX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&usart1_dmarx_handle);
}

#endif /* USART1_RX_DMA */

#if USART1_TX_DMA

/**
 * @brief USART1 Rx DMA ISR
 *
 */
void USART1_TX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&usart1_dmatx_handle);
}

#endif /* USART1_TX_DMA */

/**
 * @brief USART1 deinitialization.
 *
 * @return UART deinit status.
 * @retval - 0: `UART_DEINIT_OK`:       Success.
 * @retval - 1: `UART_DEINIT_FAIL`:     UART deinit failed.
 * @retval - 2: `UART_DEINIT_DMA_FAIL`: UART DMA deinit failed.
 * @retval - 3: `UART_NO_INIT`:         UART is not init.
 */
uint8_t usart1_deinit(void) {
    if (__HAL_RCC_USART1_IS_CLK_DISABLED()) {
        return UART_NO_INIT;
    }

    __HAL_RCC_USART1_CLK_DISABLE();

#if USART1_TX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART1_TX_PORT), USART1_TX_PIN);
#endif /* USART1_TX_ENABLE */

#if USART1_RX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART1_RX_PORT), USART1_RX_PIN);
#endif /* USART1_RX_ENABLE */

#if USART1_CTS_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART1_CTS_PORT), USART1_CTS_PIN);
#endif /* USART1_USART1_CTS */

#if USART1_RTS_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART1_RTS_PORT), USART1_RTS_PIN);
#endif /* USART1_RTS_ENABLE */
    HAL_NVIC_DisableIRQ(USART1_IRQn);

#if USART1_RX_DMA

    HAL_DMA_Abort(&usart1_dmarx_handle);
    CSP_FREE(usart1_rx_fifo.recv_buf);
    CSP_FREE(usart1_rx_fifo.rx_fifo_buf);
    ring_fifo_destroy(usart1_rx_fifo.rx_fifo);

    if (HAL_DMA_DeInit(&usart1_dmarx_handle) != HAL_OK) {
        return UART_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART1_RX_DMA_NUMBER, USART1_RX_DMA_CHANNEL));

#if USE_HAL_UART_REGISTER_CALLBACKS
    HAL_UART_UnRegisterCallback(&usart1_handle, HAL_UART_RX_HALFCOMPLETE_CB_ID);
    HAL_UART_UnRegisterCallback(&usart1_handle, HAL_UART_RX_COMPLETE_CB_ID);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
    usart1_handle.hdmarx = NULL;

#endif /* USART1_RX_DMA */

#if USART1_TX_DMA
    HAL_DMA_Abort(&usart1_dmatx_handle);
    CSP_FREE(usart1_tx_buf.send_buf);

    if (HAL_DMA_DeInit(&usart1_dmatx_handle) != HAL_OK) {
        return UART_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART1_TX_DMA_NUMBER, USART1_TX_DMA_CHANNEL));

    usart1_handle.hdmatx = NULL;
#endif /* USART1_TX_DMA */

    if (HAL_UART_DeInit(&usart1_handle) != HAL_OK) {
        return UART_DEINIT_FAIL;
    }

    return UART_DEINIT_OK;
}

#endif /* USART1_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup USART2 Functions
 * @{
 */

#if USART2_ENABLE

UART_HandleTypeDef usart2_handle = {.Instance = USART2,
                                    .Init = {.WordLength = UART_WORDLENGTH_8B,
                                             .StopBits = UART_STOPBITS_1,
                                             .Parity = UART_PARITY_NONE}};

#if USART2_RX_DMA

static DMA_HandleTypeDef usart2_dmarx_handle = {
    .Instance = CSP_DMA_CHANNEL(USART2_RX_DMA_NUMBER, USART2_RX_DMA_CHANNEL),
    .Init = {.Direction = DMA_PERIPH_TO_MEMORY,
             .MemDataAlignment = DMA_MDATAALIGN_BYTE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_CIRCULAR,
             .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
             .PeriphInc = DMA_PINC_DISABLE,
             .Priority = CSP_DMA_PRIORITY(USART2_RX_DMA_PRIORITY)}};

static uart_rx_fifo_t usart2_rx_fifo = {.buf_size = USART2_RX_DMA_BUF_SIZE,
                                        .fifo_size = USART2_RX_DMA_FIFO_SIZE};

#endif /* USART2_RX_DMA */

#if USART2_TX_DMA

static DMA_HandleTypeDef usart2_dmatx_handle = {
    .Instance = CSP_DMA_CHANNEL(USART2_TX_DMA_NUMBER, USART2_TX_DMA_CHANNEL),
    .Init = {.Direction = DMA_MEMORY_TO_PERIPH,
             .MemDataAlignment = DMA_MDATAALIGN_BYTE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
             .PeriphInc = DMA_PINC_DISABLE,
             .Priority = CSP_DMA_PRIORITY(USART2_TX_DMA_PRIORITY)}};

static uart_tx_buf_t usart2_tx_buf = {.buf_size = USART2_TX_DMA_BUF_SIZE};

#endif /* USART2_TX_DMA */

/**
 * @brief USART2 initialization
 *
 * @param baud_rate Baud rate.
 * @return USART2 init status.
 * @retval - 0: `UART_INIT_OK`:       Success.
 * @retval - 1: `UART_INIT_FAIL`:     UART init failed.
 * @retval - 2: `UART_INIT_DMA_FAIL`: UART DMA init failed.
 * @retval - 3: `UART_INIT_MEM_FAIL`: UART buffer memory init failed (It will
 *                                    dynamic allocate memory when using DMA).
 * @retval - 4: `UART_INITED`:        This uart is inited.
 */
uint8_t usart2_init(uint32_t baud_rate) {
    if (__HAL_RCC_USART2_IS_CLK_ENABLED()) {
        return UART_INITED;
    }

    GPIO_InitTypeDef gpio_init_struct = {.Pull = GPIO_PULLUP,
                                         .Speed = GPIO_SPEED_FREQ_HIGH};
    usart2_handle.Init.BaudRate = baud_rate;

    USART2_AFIO_REMAP();
#if USART2_TX_ENABLE
    usart2_handle.Init.Mode |= UART_MODE_TX;

    CSP_GPIO_CLK_ENABLE(USART2_TX_PORT);
    gpio_init_struct.Pin = USART2_TX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART2_TX_PORT), &gpio_init_struct);
#endif /* USART2_TX_ENABLE */

#if USART2_RX_ENABLE
    usart2_handle.Init.Mode |= UART_MODE_RX;

    CSP_GPIO_CLK_ENABLE(USART2_RX_PORT);
    gpio_init_struct.Pin = USART2_RX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART2_RX_PORT), &gpio_init_struct);
#endif /* USART2_RX_ENABLE */

#if USART2_CTS_ENABLE
    usart2_handle.Init.HwFlowCtl |= UART_HWCONTROL_CTS;

    CSP_GPIO_CLK_ENABLE(USART2_CTS_PORT);
    gpio_init_struct.Pin = USART2_CTS_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART2_CTS_PORT), &gpio_init_struct);
#endif /* USART2_USART2_CTS */

#if USART2_RTS_ENABLE
    usart2_handle.Init.HwFlowCtl |= UART_HWCONTROL_RTS;

    CSP_GPIO_CLK_ENABLE(USART2_RTS_PORT);
    gpio_init_struct.Pin = USART2_RTS_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART2_RTS_PORT), &gpio_init_struct);
#endif /* USART2_RTS_ENABLE */

    __HAL_RCC_USART2_CLK_ENABLE();

    HAL_NVIC_EnableIRQ(USART2_IRQn);
    HAL_NVIC_SetPriority(USART2_IRQn, USART2_IT_PRIORITY, USART2_IT_SUB);

#if USART2_RX_DMA
    usart2_rx_fifo.head_ptr = 0;

    usart2_rx_fifo.recv_buf = CSP_MALLOC(usart2_rx_fifo.buf_size);
    if (usart2_rx_fifo.recv_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    usart2_rx_fifo.rx_fifo_buf = CSP_MALLOC(usart2_rx_fifo.fifo_size);
    if (usart2_rx_fifo.rx_fifo_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    usart2_rx_fifo.rx_fifo = ring_fifo_init(
        usart2_rx_fifo.rx_fifo_buf, usart2_rx_fifo.fifo_size, RF_TYPE_STREAM);
    if (usart2_rx_fifo.rx_fifo == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    CSP_DMA_CLK_ENABLE(USART2_RX_DMA_NUMBER);
    if (HAL_DMA_Init(&usart2_dmarx_handle) != HAL_OK) {
        return UART_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&usart2_handle, hdmarx, usart2_dmarx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(USART2_RX_DMA_NUMBER, USART2_RX_DMA_CHANNEL),
        USART2_RX_DMA_IT_PRIORITY, USART2_RX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART2_RX_DMA_NUMBER, USART2_RX_DMA_CHANNEL));

#endif /* USART2_RX_DMA */

#if USART2_TX_DMA
    usart2_tx_buf.send_buf = CSP_MALLOC(usart2_tx_buf.buf_size);
    if (usart2_tx_buf.send_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    CSP_DMA_CLK_ENABLE(USART2_TX_DMA_NUMBER);
    if (HAL_DMA_Init(&usart2_dmatx_handle) != HAL_OK) {
        return UART_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&usart2_handle, hdmatx, usart2_dmatx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(USART2_TX_DMA_NUMBER, USART2_TX_DMA_CHANNEL),
        USART2_TX_DMA_IT_PRIORITY, USART2_TX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART2_TX_DMA_NUMBER, USART2_TX_DMA_CHANNEL));
#endif /* USART2_TX_DMA */

    if (HAL_UART_Init(&usart2_handle) != HAL_OK) {
        return UART_INIT_FAIL;
    }

#if USART2_RX_DMA
    __HAL_UART_ENABLE_IT(&usart2_handle, UART_IT_IDLE);
    __HAL_UART_CLEAR_IDLEFLAG(&usart2_handle);

    HAL_UART_Receive_DMA(&usart2_handle, usart2_rx_fifo.recv_buf,
                         usart2_rx_fifo.buf_size);

#if USE_HAL_UART_REGISTER_CALLBACKS
    HAL_UART_RegisterCallback(&usart2_handle, HAL_UART_RX_HALFCOMPLETE_CB_ID,
                              uart_dmarx_halfdone_callback);
    HAL_UART_RegisterCallback(&usart2_handle, HAL_UART_RX_COMPLETE_CB_ID,
                              uart_dmarx_done_callback);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
#endif /* USART2_RX_DMA */
    return UART_INIT_OK;
}

/**
 * @brief USART2 ISR
 *
 */
void USART2_IRQHandler(void) {
    if (__HAL_UART_GET_FLAG(&usart2_handle, UART_FLAG_IDLE)) {
        __HAL_UART_CLEAR_IDLEFLAG(&usart2_handle);
        uart_dmarx_idle_callback(&usart2_handle);
    }

    HAL_UART_IRQHandler(&usart2_handle);
}

#if USART2_RX_DMA

/**
 * @brief USART2 Rx DMA ISR
 *
 */
void USART2_RX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&usart2_dmarx_handle);
}

#endif /* USART2_RX_DMA */

#if USART2_TX_DMA

/**
 * @brief USART2 Rx DMA ISR
 *
 */
void USART2_TX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&usart2_dmatx_handle);
}

#endif /* USART2_TX_DMA */

/**
 * @brief USART2 deinitialization.
 *
 * @return UART deinit status.
 * @retval - 0: `UART_DEINIT_OK`:       Success.
 * @retval - 1: `UART_DEINIT_FAIL`:     UART deinit failed.
 * @retval - 2: `UART_DEINIT_DMA_FAIL`: UART DMA deinit failed.
 * @retval - 3: `UART_NO_INIT`:         UART is not init.
 */
uint8_t usart2_deinit(void) {
    if (__HAL_RCC_USART2_IS_CLK_DISABLED()) {
        return UART_NO_INIT;
    }

    __HAL_RCC_USART2_CLK_DISABLE();

#if USART2_TX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART2_TX_PORT), USART2_TX_PIN);
#endif /* USART2_TX_ENABLE */

#if USART2_RX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART2_RX_PORT), USART2_RX_PIN);
#endif /* USART2_RX_ENABLE */

#if USART2_CTS_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART2_CTS_PORT), USART2_CTS_PIN);
#endif /* USART2_USART2_CTS */

#if USART2_RTS_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART2_RTS_PORT), USART2_RTS_PIN);
#endif /* USART2_RTS_ENABLE */
    HAL_NVIC_DisableIRQ(USART2_IRQn);

#if USART2_RX_DMA

    HAL_DMA_Abort(&usart2_dmarx_handle);
    CSP_FREE(usart2_rx_fifo.recv_buf);
    CSP_FREE(usart2_rx_fifo.rx_fifo_buf);
    ring_fifo_destroy(usart2_rx_fifo.rx_fifo);

    if (HAL_DMA_DeInit(&usart2_dmarx_handle) != HAL_OK) {
        return UART_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART2_RX_DMA_NUMBER, USART2_RX_DMA_CHANNEL));

#if USE_HAL_UART_REGISTER_CALLBACKS
    HAL_UART_UnRegisterCallback(&usart2_handle, HAL_UART_RX_HALFCOMPLETE_CB_ID);
    HAL_UART_UnRegisterCallback(&usart2_handle, HAL_UART_RX_COMPLETE_CB_ID);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
    usart2_handle.hdmarx = NULL;

#endif /* USART2_RX_DMA */

#if USART2_TX_DMA
    HAL_DMA_Abort(&usart2_dmatx_handle);
    CSP_FREE(usart2_tx_buf.send_buf);

    if (HAL_DMA_DeInit(&usart2_dmatx_handle) != HAL_OK) {
        return UART_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART2_TX_DMA_NUMBER, USART2_TX_DMA_CHANNEL));

    usart2_handle.hdmatx = NULL;
#endif /* USART2_TX_DMA */

    if (HAL_UART_DeInit(&usart2_handle) != HAL_OK) {
        return UART_DEINIT_FAIL;
    }

    return UART_DEINIT_OK;
}

#endif /* USART2_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup USART3 Functions
 * @{
 */

#if USART3_ENABLE

UART_HandleTypeDef usart3_handle = {.Instance = USART3,
                                    .Init = {.WordLength = UART_WORDLENGTH_8B,
                                             .StopBits = UART_STOPBITS_1,
                                             .Parity = UART_PARITY_NONE}};

#if USART3_RX_DMA

static DMA_HandleTypeDef usart3_dmarx_handle = {
    .Instance = CSP_DMA_CHANNEL(USART3_RX_DMA_NUMBER, USART3_RX_DMA_CHANNEL),
    .Init = {.Direction = DMA_PERIPH_TO_MEMORY,
             .MemDataAlignment = DMA_MDATAALIGN_BYTE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_CIRCULAR,
             .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
             .PeriphInc = DMA_PINC_DISABLE,
             .Priority = CSP_DMA_PRIORITY(USART3_RX_DMA_PRIORITY)}};

static uart_rx_fifo_t usart3_rx_fifo = {.buf_size = USART3_RX_DMA_BUF_SIZE,
                                        .fifo_size = USART3_RX_DMA_FIFO_SIZE};

#endif /* USART3_RX_DMA */

#if USART3_TX_DMA

static DMA_HandleTypeDef usart3_dmatx_handle = {
    .Instance = CSP_DMA_CHANNEL(USART3_TX_DMA_NUMBER, USART3_TX_DMA_CHANNEL),
    .Init = {.Direction = DMA_MEMORY_TO_PERIPH,
             .MemDataAlignment = DMA_MDATAALIGN_BYTE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
             .PeriphInc = DMA_PINC_DISABLE,
             .Priority = CSP_DMA_PRIORITY(USART3_TX_DMA_PRIORITY)}};

static uart_tx_buf_t usart3_tx_buf = {.buf_size = USART3_TX_DMA_BUF_SIZE};

#endif /* USART3_TX_DMA */

/**
 * @brief USART3 initialization
 *
 * @param baud_rate Baud rate.
 * @return USART3 init status.
 * @retval - 0: `UART_INIT_OK`:       Success.
 * @retval - 1: `UART_INIT_FAIL`:     UART init failed.
 * @retval - 2: `UART_INIT_DMA_FAIL`: UART DMA init failed.
 * @retval - 3: `UART_INIT_MEM_FAIL`: UART buffer memory init failed (It will
 *                                    dynamic allocate memory when using DMA).
 * @retval - 4: `UART_INITED`:        This uart is inited.
 */
uint8_t usart3_init(uint32_t baud_rate) {
    if (__HAL_RCC_USART3_IS_CLK_ENABLED()) {
        return UART_INITED;
    }

    GPIO_InitTypeDef gpio_init_struct = {
        .Pull = GPIO_PULLUP,
        .Speed = GPIO_SPEED_FREQ_HIGH,
    };
    usart3_handle.Init.BaudRate = baud_rate;

    USART3_AFIO_REMAP();
#if USART3_TX_ENABLE
    usart3_handle.Init.Mode |= UART_MODE_TX;

    CSP_GPIO_CLK_ENABLE(USART3_TX_PORT);
    gpio_init_struct.Pin = USART3_TX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART3_TX_PORT), &gpio_init_struct);
#endif /* USART3_TX_ENABLE */

#if USART3_RX_ENABLE
    usart3_handle.Init.Mode |= UART_MODE_RX;

    CSP_GPIO_CLK_ENABLE(USART3_RX_PORT);
    gpio_init_struct.Pin = USART3_RX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART3_RX_PORT), &gpio_init_struct);
#endif /* USART3_RX_ENABLE */

#if USART3_CTS_ENABLE
    usart3_handle.Init.HwFlowCtl |= UART_HWCONTROL_CTS;

    CSP_GPIO_CLK_ENABLE(USART3_CTS_PORT);
    gpio_init_struct.Pin = USART3_CTS_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART3_CTS_PORT), &gpio_init_struct);
#endif /* USART3_USART3_CTS */

#if USART3_RTS_ENABLE
    usart3_handle.Init.HwFlowCtl |= UART_HWCONTROL_RTS;

    CSP_GPIO_CLK_ENABLE(USART3_RTS_PORT);
    gpio_init_struct.Pin = USART3_RTS_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(CSP_GPIO_PORT(USART3_RTS_PORT), &gpio_init_struct);
#endif /* USART3_RTS_ENABLE */

    __HAL_RCC_USART3_CLK_ENABLE();

    HAL_NVIC_EnableIRQ(USART3_IRQn);
    HAL_NVIC_SetPriority(USART3_IRQn, USART3_IT_PRIORITY, USART3_IT_SUB);

#if USART3_RX_DMA
    usart3_rx_fifo.head_ptr = 0;

    usart3_rx_fifo.recv_buf = CSP_MALLOC(usart3_rx_fifo.buf_size);
    if (usart3_rx_fifo.recv_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    usart3_rx_fifo.rx_fifo_buf = CSP_MALLOC(usart3_rx_fifo.fifo_size);
    if (usart3_rx_fifo.rx_fifo_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    usart3_rx_fifo.rx_fifo = ring_fifo_init(
        usart3_rx_fifo.rx_fifo_buf, usart3_rx_fifo.fifo_size, RF_TYPE_STREAM);
    if (usart3_rx_fifo.rx_fifo == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    CSP_DMA_CLK_ENABLE(USART3_RX_DMA_NUMBER);
    if (HAL_DMA_Init(&usart3_dmarx_handle) != HAL_OK) {
        return UART_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&usart3_handle, hdmarx, usart3_dmarx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(USART3_RX_DMA_NUMBER, USART3_RX_DMA_CHANNEL),
        USART3_RX_DMA_IT_PRIORITY, USART3_RX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART3_RX_DMA_NUMBER, USART3_RX_DMA_CHANNEL));
#endif /* USART3_RX_DMA */

#if USART3_TX_DMA
    usart3_tx_buf.send_buf = CSP_MALLOC(usart3_tx_buf.buf_size);
    if (usart3_tx_buf.send_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    CSP_DMA_CLK_ENABLE(USART3_TX_DMA_NUMBER);
    if (HAL_DMA_Init(&usart3_dmatx_handle) != HAL_OK) {
        return UART_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&usart3_handle, hdmatx, usart3_dmatx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(USART3_TX_DMA_NUMBER, USART3_TX_DMA_CHANNEL),
        USART3_TX_DMA_IT_PRIORITY, USART3_TX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART3_TX_DMA_NUMBER, USART3_TX_DMA_CHANNEL));
#endif /* USART3_TX_DMA */

    if (HAL_UART_Init(&usart3_handle) != HAL_OK) {
        return UART_INIT_FAIL;
    }

#if USART3_RX_DMA
    __HAL_UART_ENABLE_IT(&usart3_handle, UART_IT_IDLE);
    __HAL_UART_CLEAR_IDLEFLAG(&usart3_handle);

    HAL_UART_Receive_DMA(&usart3_handle, usart3_rx_fifo.recv_buf,
                         usart3_rx_fifo.buf_size);

#if USE_HAL_UART_REGISTER_CALLBACKS
    HAL_UART_RegisterCallback(&usart3_handle, HAL_UART_RX_HALFCOMPLETE_CB_ID,
                              uart_dmarx_halfdone_callback);
    HAL_UART_RegisterCallback(&usart3_handle, HAL_UART_RX_COMPLETE_CB_ID,
                              uart_dmarx_done_callback);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
#endif /* USART3_RX_DMA */
    return UART_INIT_OK;
}

/**
 * @brief USART3 ISR
 *
 */
void USART3_IRQHandler(void) {
    if (__HAL_UART_GET_FLAG(&usart3_handle, UART_FLAG_IDLE)) {
        __HAL_UART_CLEAR_IDLEFLAG(&usart3_handle);
        uart_dmarx_idle_callback(&usart3_handle);
    }

    HAL_UART_IRQHandler(&usart3_handle);
}

#if USART3_RX_DMA

/**
 * @brief USART3 Rx DMA ISR
 *
 */
void USART3_RX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&usart3_dmarx_handle);
}

#endif /* USART3_RX_DMA */

#if USART3_TX_DMA

/**
 * @brief USART3 Rx DMA ISR
 *
 */
void USART3_TX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&usart3_dmatx_handle);
}

#endif /* USART3_TX_DMA */

/**
 * @brief USART3 deinitialization.
 *
 * @return UART deinit status.
 * @retval - 0: `UART_DEINIT_OK`:       Success.
 * @retval - 1: `UART_DEINIT_FAIL`:     UART deinit failed.
 * @retval - 2: `UART_DEINIT_DMA_FAIL`: UART DMA deinit failed.
 * @retval - 3: `UART_NO_INIT`:         UART is not init.
 */
uint8_t usart3_deinit(void) {
    if (__HAL_RCC_USART3_IS_CLK_DISABLED()) {
        return UART_NO_INIT;
    }

    __HAL_RCC_USART3_CLK_DISABLE();

#if USART3_TX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART3_TX_PORT), USART3_TX_PIN);
#endif /* USART3_TX_ENABLE */

#if USART3_RX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART3_RX_PORT), USART3_RX_PIN);
#endif /* USART3_RX_ENABLE */

#if USART3_CTS_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART3_CTS_PORT), USART3_CTS_PIN);
#endif /* USART3_USART3_CTS */

#if USART3_RTS_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(USART3_RTS_PORT), USART3_RTS_PIN);
#endif /* USART3_RTS_ENABLE */
    HAL_NVIC_DisableIRQ(USART3_IRQn);

#if USART3_RX_DMA

    HAL_DMA_Abort(&usart3_dmarx_handle);
    CSP_FREE(usart3_rx_fifo.recv_buf);
    CSP_FREE(usart3_rx_fifo.rx_fifo_buf);
    ring_fifo_destroy(usart3_rx_fifo.rx_fifo);

    if (HAL_DMA_DeInit(&usart3_dmarx_handle) != HAL_OK) {
        return UART_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART3_RX_DMA_NUMBER, USART3_RX_DMA_CHANNEL));

#if USE_HAL_UART_REGISTER_CALLBACKS
    HAL_UART_UnRegisterCallback(&usart3_handle, HAL_UART_RX_HALFCOMPLETE_CB_ID);
    HAL_UART_UnRegisterCallback(&usart3_handle, HAL_UART_RX_COMPLETE_CB_ID);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
    usart3_handle.hdmarx = NULL;

#endif /* USART3_RX_DMA */

#if USART3_TX_DMA
    HAL_DMA_Abort(&usart3_dmatx_handle);
    CSP_FREE(usart3_tx_buf.send_buf);

    if (HAL_DMA_DeInit(&usart3_dmatx_handle) != HAL_OK) {
        return UART_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(USART3_TX_DMA_NUMBER, USART3_TX_DMA_CHANNEL));

    usart3_handle.hdmatx = NULL;
#endif /* USART3_TX_DMA */

    if (HAL_UART_DeInit(&usart3_handle) != HAL_OK) {
        return UART_DEINIT_FAIL;
    }

    return UART_DEINIT_OK;
}

#endif /* USART3_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup UART4 Functions
 * @{
 */

#if UART4_ENABLE

UART_HandleTypeDef uart4_handle = {.Instance = UART4,
                                   .Init = {.WordLength = UART_WORDLENGTH_8B,
                                            .StopBits = UART_STOPBITS_1,
                                            .Parity = UART_PARITY_NONE}};

#if UART4_RX_DMA

static DMA_HandleTypeDef uart4_dmarx_handle = {
    .Instance = CSP_DMA_CHANNEL(UART4_RX_DMA_NUMBER, UART4_RX_DMA_CHANNEL),
    .Init = {.Direction = DMA_PERIPH_TO_MEMORY,
             .MemDataAlignment = DMA_MDATAALIGN_BYTE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_CIRCULAR,
             .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
             .PeriphInc = DMA_PINC_DISABLE,
             .Priority = CSP_DMA_PRIORITY(UART4_RX_DMA_PRIORITY)}};

static uart_rx_fifo_t uart4_rx_fifo = {.buf_size = UART4_RX_DMA_BUF_SIZE,
                                       .fifo_size = UART4_RX_DMA_FIFO_SIZE};

#endif /* UART4_RX_DMA */

#if UART4_TX_DMA

static DMA_HandleTypeDef uart4_dmatx_handle = {
    .Instance = CSP_DMA_CHANNEL(UART4_TX_DMA_NUMBER, UART4_TX_DMA_CHANNEL),
    .Init = {.Direction = DMA_MEMORY_TO_PERIPH,
             .MemDataAlignment = DMA_MDATAALIGN_BYTE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
             .PeriphInc = DMA_PINC_DISABLE,
             .Priority = CSP_DMA_PRIORITY(UART4_TX_DMA_PRIORITY)}};

static uart_tx_buf_t uart4_tx_buf = {.buf_size = UART4_TX_DMA_BUF_SIZE};

#endif /* UART4_TX_DMA */

/**
 * @brief UART4 initialization
 *
 * @param baud_rate Baud rate.
 * @return UART4 init status.
 * @retval - 0: `UART_INIT_OK`:       Success.
 * @retval - 1: `UART_INIT_FAIL`:     UART init failed.
 * @retval - 2: `UART_INIT_DMA_FAIL`: UART DMA init failed.
 * @retval - 3: `UART_INIT_MEM_FAIL`: UART buffer memory init failed (It will
 *                                    dynamic allocate memory when using DMA).
 * @retval - 4: `UART_INITED`:        This uart is inited.
 */
uint8_t uart4_init(uint32_t baud_rate) {
    if (__HAL_RCC_UART4_IS_CLK_ENABLED()) {
        return UART_INITED;
    }

    GPIO_InitTypeDef gpio_init_struct = {.Pull = GPIO_PULLUP,
                                         .Speed = GPIO_SPEED_FREQ_HIGH};
    uart4_handle.Init.BaudRate = baud_rate;
#if UART4_TX_ENABLE
    uart4_handle.Init.Mode |= UART_MODE_TX;

    CSP_GPIO_CLK_ENABLE(UART4_TX_PORT);
    gpio_init_struct.Pin = UART4_TX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(CSP_GPIO_PORT(UART4_TX_PORT), &gpio_init_struct);
#endif /* UART4_TX_ENABLE */

#if UART4_RX_ENABLE
    uart4_handle.Init.Mode |= UART_MODE_RX;

    CSP_GPIO_CLK_ENABLE(UART4_RX_PORT);
    gpio_init_struct.Pin = UART4_RX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    HAL_GPIO_Init(CSP_GPIO_PORT(UART4_RX_PORT), &gpio_init_struct);
#endif /* UART4_RX_ENABLE */

    __HAL_RCC_UART4_CLK_ENABLE();

    HAL_NVIC_EnableIRQ(UART4_IRQn);
    HAL_NVIC_SetPriority(UART4_IRQn, UART4_IT_PRIORITY, UART4_IT_SUB);

#if UART4_RX_DMA
    uart4_rx_fifo.head_ptr = 0;

    uart4_rx_fifo.recv_buf = CSP_MALLOC(uart4_rx_fifo.buf_size);
    if (uart4_rx_fifo.recv_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    uart4_rx_fifo.rx_fifo_buf = CSP_MALLOC(uart4_rx_fifo.fifo_size);
    if (uart4_rx_fifo.rx_fifo_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    uart4_rx_fifo.rx_fifo = ring_fifo_init(
        uart4_rx_fifo.rx_fifo_buf, uart4_rx_fifo.fifo_size, RF_TYPE_STREAM);
    if (uart4_rx_fifo.rx_fifo == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    CSP_DMA_CLK_ENABLE(UART4_RX_DMA_NUMBER);
    if (HAL_DMA_Init(&uart4_dmarx_handle) != HAL_OK) {
        return UART_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&uart4_handle, hdmarx, uart4_dmarx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(UART4_RX_DMA_NUMBER, UART4_RX_DMA_CHANNEL),
        UART4_RX_DMA_IT_PRIORITY, UART4_RX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(UART4_RX_DMA_NUMBER, UART4_RX_DMA_CHANNEL));

#endif /* UART4_RX_DMA */

#if UART4_TX_DMA
    uart4_tx_buf.send_buf = CSP_MALLOC(uart4_tx_buf.buf_size);
    if (uart4_tx_buf.send_buf == NULL) {
        return UART_INIT_MEM_FAIL;
    }

    CSP_DMA_CLK_ENABLE(UART4_TX_DMA_NUMBER);
    if (HAL_DMA_Init(&uart4_dmatx_handle) != HAL_OK) {
        return UART_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&uart4_handle, hdmatx, uart4_dmatx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(UART4_TX_DMA_NUMBER, UART4_TX_DMA_CHANNEL),
        UART4_TX_DMA_IT_PRIORITY, UART4_TX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(UART4_TX_DMA_NUMBER, UART4_TX_DMA_CHANNEL));
#endif /* UART4_TX_DMA */

    if (HAL_UART_Init(&uart4_handle) != HAL_OK) {
        return UART_INIT_FAIL;
    }

#if UART4_RX_DMA
    __HAL_UART_ENABLE_IT(&uart4_handle, UART_IT_IDLE);
    __HAL_UART_CLEAR_IDLEFLAG(&uart4_handle);

    HAL_UART_Receive_DMA(&uart4_handle, uart4_rx_fifo.recv_buf,
                         uart4_rx_fifo.buf_size);

#if USE_HAL_UART_REGISTER_CALLBACKS
    HAL_UART_RegisterCallback(&uart4_handle, HAL_UART_RX_HALFCOMPLETE_CB_ID,
                              uart_dmarx_halfdone_callback);
    HAL_UART_RegisterCallback(&uart4_handle, HAL_UART_RX_COMPLETE_CB_ID,
                              uart_dmarx_done_callback);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
#endif /* UART4_RX_DMA */
    return UART_INIT_OK;
}

/**
 * @brief UART4 ISR
 *
 */
void UART4_IRQHandler(void) {
    if (__HAL_UART_GET_FLAG(&uart4_handle, UART_FLAG_IDLE)) {
        __HAL_UART_CLEAR_IDLEFLAG(&uart4_handle);
        uart_dmarx_idle_callback(&uart4_handle);
    }

    HAL_UART_IRQHandler(&uart4_handle);
}

#if UART4_RX_DMA

/**
 * @brief UART4 Rx DMA ISR
 *
 */
void UART4_RX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&uart4_dmarx_handle);
}

#endif /* UART4_RX_DMA */

#if UART4_TX_DMA

/**
 * @brief UART4 Rx DMA ISR
 *
 */
void UART4_TX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&uart4_dmatx_handle);
}

#endif /* UART4_TX_DMA */

/**
 * @brief UART4 deinitialization.
 *
 * @return UART deinit status.
 * @retval - 0: `UART_DEINIT_OK`:       Success.
 * @retval - 1: `UART_DEINIT_FAIL`:     UART deinit failed.
 * @retval - 2: `UART_DEINIT_DMA_FAIL`: UART DMA deinit failed.
 * @retval - 3: `UART_NO_INIT`:         UART is not init.
 */
uint8_t uart4_deinit(void) {
    if (__HAL_RCC_UART4_IS_CLK_DISABLED()) {
        return UART_NO_INIT;
    }

    __HAL_RCC_UART4_CLK_DISABLE();

#if UART4_TX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(UART4_TX_PORT), UART4_TX_PIN);
#endif /* UART4_TX_ENABLE */

#if UART4_RX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(UART4_RX_PORT), UART4_RX_PIN);
#endif /* UART4_RX_ENABLE */

#if UART4_RX_DMA

    HAL_DMA_Abort(&uart4_dmarx_handle);
    CSP_FREE(uart4_rx_fifo.recv_buf);
    CSP_FREE(uart4_rx_fifo.rx_fifo_buf);
    ring_fifo_destroy(uart4_rx_fifo.rx_fifo);

    if (HAL_DMA_DeInit(&uart4_dmarx_handle) != HAL_OK) {
        return UART_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(UART4_RX_DMA_NUMBER, UART4_RX_DMA_CHANNEL));

#if USE_HAL_UART_REGISTER_CALLBACKS
    HAL_UART_UnRegisterCallback(&uart4_handle, HAL_UART_RX_HALFCOMPLETE_CB_ID);
    HAL_UART_UnRegisterCallback(&uart4_handle, HAL_UART_RX_COMPLETE_CB_ID);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
    uart4_handle.hdmarx = NULL;

#endif /* UART4_RX_DMA */

#if UART4_TX_DMA
    HAL_DMA_Abort(&uart4_dmatx_handle);
    CSP_FREE(uart4_tx_buf.send_buf);

    if (HAL_DMA_DeInit(&uart4_dmatx_handle) != HAL_OK) {
        return UART_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(UART4_TX_DMA_NUMBER, UART4_TX_DMA_CHANNEL));

    uart4_handle.hdmatx = NULL;
#endif /* UART4_TX_DMA */

    if (HAL_UART_DeInit(&uart4_handle) != HAL_OK) {
        return UART_DEINIT_FAIL;
    }

    return UART_DEINIT_OK;
}

#endif /* UART4_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup UART5 Functions
 * @{
 */

#if UART5_ENABLE

UART_HandleTypeDef uart5_handle = {.Instance = UART5,
                                   .Init = {.WordLength = UART_WORDLENGTH_8B,
                                            .StopBits = UART_STOPBITS_1,
                                            .Parity = UART_PARITY_NONE}};

/**
 * @brief UART5 initialization
 *
 * @param baud_rate Baud rate.
 * @return UART5 init status.
 * @retval - 0: `UART_INIT_OK`:       Success.
 * @retval - 1: `UART_INIT_FAIL`:     UART init failed.
 * @retval - 4: `UART_INITED`:        This uart is inited.
 */
uint8_t uart5_init(uint32_t baud_rate) {
    if (__HAL_RCC_UART5_IS_CLK_ENABLED()) {
        return UART_INITED;
    }

    GPIO_InitTypeDef gpio_init_struct = {.Pull = GPIO_PULLUP,
                                         .Speed = GPIO_SPEED_FREQ_HIGH};
    uart5_handle.Init.BaudRate = baud_rate;
#if UART5_TX_ENABLE
    uart5_handle.Init.Mode |= UART_MODE_TX;

    CSP_GPIO_CLK_ENABLE(UART5_TX_PORT);
    gpio_init_struct.Pin = UART5_TX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(CSP_GPIO_PORT(UART5_TX_PORT), &gpio_init_struct);
#endif /* UART5_TX_ENABLE */

#if UART5_RX_ENABLE
    uart5_handle.Init.Mode |= UART_MODE_RX;

    CSP_GPIO_CLK_ENABLE(UART5_RX_PORT);
    gpio_init_struct.Pin = UART5_RX_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    HAL_GPIO_Init(CSP_GPIO_PORT(UART5_RX_PORT), &gpio_init_struct);
#endif /* UART5_RX_ENABLE */

    __HAL_RCC_UART5_CLK_ENABLE();

    HAL_NVIC_EnableIRQ(UART5_IRQn);
    HAL_NVIC_SetPriority(UART5_IRQn, UART5_IT_PRIORITY, UART5_IT_SUB);

    if (HAL_UART_Init(&uart5_handle) != HAL_OK) {
        return UART_INIT_FAIL;
    }

    return UART_INIT_OK;
}

/**
 * @brief UART5 ISR
 *
 */
void UART5_IRQHandler(void) {
    if (__HAL_UART_GET_FLAG(&uart5_handle, UART_FLAG_IDLE)) {
        __HAL_UART_CLEAR_IDLEFLAG(&uart5_handle);
        uart_dmarx_idle_callback(&uart5_handle);
    }

    HAL_UART_IRQHandler(&uart5_handle);
}

/**
 * @brief UART5 deinitialization.
 *
 * @return UART deinit status.
 * @retval - 0: `UART_DEINIT_OK`:       Success.
 * @retval - 1: `UART_DEINIT_FAIL`:     UART deinit failed.
 * @retval - 2: `UART_DEINIT_DMA_FAIL`: UART DMA deinit failed.
 * @retval - 3: `UART_NO_INIT`:         UART is not init.
 */
uint8_t uart5_deinit(void) {
    if (__HAL_RCC_UART5_IS_CLK_DISABLED()) {
        return UART_NO_INIT;
    }

    __HAL_RCC_UART5_CLK_DISABLE();

#if UART5_TX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(UART5_TX_PORT), UART5_TX_PIN);
#endif /* UART5_TX_ENABLE */

#if UART5_RX_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(UART5_RX_PORT), UART5_RX_PIN);
#endif /* UART5_RX_ENABLE */

    if (HAL_UART_DeInit(&uart5_handle) != HAL_OK) {
        return UART_DEINIT_FAIL;
    }

    return UART_DEINIT_OK;
}

#endif /* UART5_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup Public UART functions.
 * @{
 */

/**
 * @brief Formatted print to the UART.
 *
 * @param huart The handle of UART.
 * @param __format The string with format.
 * @return The number of characters that would have been written in the
 *         array, not counting the terminating null character.
 */
int uart_printf(UART_HandleTypeDef *huart, const char *__format, ...) {
    int res;
    uint16_t len;
    va_list ap;

    if (((huart->gState) & HAL_UART_STATE_READY) == 0) {
        /* The UART is not inited. */
        return 0;
    }

    /* Wait for last transfer end. */
    while (__HAL_UART_GET_FLAG(huart, UART_FLAG_TC) == RESET)
        ;

    va_start(ap, __format);
    res = vsnprintf(uart_buffer, sizeof(uart_buffer), __format, ap);
    va_end(ap);

    len = strlen(uart_buffer);

    if (huart->hdmatx != NULL) {
        HAL_UART_Transmit_DMA(huart, (uint8_t *)uart_buffer, len);
    } else {
        HAL_UART_Transmit(huart, (uint8_t *)uart_buffer, len, 1000);
    }

    return res;
}

/**
 * @brief Formatted receive from the UART.
 *
 * @param huart The handle of UART.
 * @param __format The string with format.
 * @return The value of the macro EOF if an input failure occurs before any
 *         conversion. Otherwise, the scanf function returns the number of
 *         input items assigned, which can be fewer than provided for, or
 *         even zero, in the event of an early matching failure.
 */
int uart_scanf(UART_HandleTypeDef *huart, const char *__format, ...) {
    uint16_t str_len = 0;
    int res;
    va_list ap;

    if (((huart->gState) & HAL_UART_STATE_READY) == 0) {
        /* The UART is not inited. */
        return 0;
    }

    if (huart->hdmarx != NULL) {
        while (str_len == 0) {
            str_len = uart_dmarx_read(huart, uart_buffer, sizeof(uart_buffer));
        }
    } else {
        HAL_UARTEx_ReceiveToIdle(huart, (uint8_t *)uart_buffer,
                                 sizeof(uart_buffer), &str_len, 0xFFFF);
    }

    va_start(ap, __format);
    res = vsscanf((char *)uart_buffer, __format, ap);
    va_end(ap);

    return res;
}

/**
 * @}
 */

/*****************************************************************************
 * @defgroup Public UART DMA Rx functions.
 * @{
 */

/**
 * @brief Identify the UART receive fifo by handle.
 *
 * @param huart The handle of UART
 * @return The point of UART rx fifo.
 */
static inline uart_rx_fifo_t *uart_rx_identify(UART_HandleTypeDef *huart) {

    switch ((uintptr_t)huart->Instance) {
#if USART1_RX_DMA
        case USART1_BASE: {
            return &usart1_rx_fifo;
        }
#endif /* USART1_RX_DMA */

#if USART2_RX_DMA
        case USART2_BASE: {
            return &usart2_rx_fifo;
        }
#endif /* USART2_RX_DMA */
#if USART3_RX_DMA
        case USART3_BASE: {
            return &usart3_rx_fifo;
        }
#endif /* USART3_RX_DMA */

#if UART4_RX_DMA
        case UART4_BASE: {
            return &uart4_rx_fifo;
        }
#endif /* UART4_RX_DMA */

#if UART5_RX_DMA
        case UART5_BASE: {
            return &uart5_rx_fifo;
        }
#endif /* UART5_RX_DMA */

#if USART6_RX_DMA
        case USART6_BASE: {
            return &usart6_rx_fifo;
        }
#endif /* USART6_RX_DMA */

#if UART7_RX_DMA
        case UART7_BASE: {
            return &uart7_rx_fifo;
        }
#endif /* UART7_RX_DMA */

#if UART8_RX_DMA
        case UART8_BASE: {
            return &uart8_rx_fifo;
        }
#endif /* UART8_RX_DMA */

#if UART9_RX_DMA
        case UART9_BASE: {
            return &uart9_rx_fifo;
        }
#endif /* UART9_RX_DMA */

#if UART10_RX_DMA
        case UART10_BASE: {
            return &uart10_rx_fifo;
        }
#endif /* UART10_RX_DMA */

        default: {
        } break;
    }

    return NULL;
}

/**
 * @brief UART received idle callback.
 *
 * @param huart The handle of UART
 */
void uart_dmarx_idle_callback(UART_HandleTypeDef *huart) {
    uart_rx_fifo_t *uart_rx_fifo = uart_rx_identify(huart);
    if (uart_rx_fifo == NULL) {
        return;
    }

    uint32_t tail_ptr;
    uint32_t copy, offset;

    /**
     * +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
     * |     head_ptr          tail_ptr         |
     * |         |                 |            |
     * |         v                 v            |
     * | --------*******************----------- |
     * +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
     */

    /* Received */
    tail_ptr = huart->RxXferSize - __HAL_DMA_GET_COUNTER(huart->hdmarx);

    offset = (uart_rx_fifo->head_ptr) % (uint32_t)(huart->RxXferSize);
    copy = tail_ptr - offset;
    uart_rx_fifo->head_ptr += copy;

    ring_fifo_write(uart_rx_fifo->rx_fifo, huart->pRxBuffPtr + offset, copy);
}

/**
 * @brief UART DMA half overflow callback.
 *
 * @param huart The handle of UART
 */
void uart_dmarx_halfdone_callback(UART_HandleTypeDef *huart) {
    uart_rx_fifo_t *uart_rx_fifo = uart_rx_identify(huart);
    if (uart_rx_fifo == NULL) {
        return;
    }

    uint32_t tail_ptr;
    uint32_t offset, copy;

    /**
     * +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
     * |                  half                  |
     * |     head_ptr   tail_ptr                |
     * |         |          |                   |
     * |         v          v                   |
     * | --------*******************----------- |
     * +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
     */

    tail_ptr = (huart->RxXferSize >> 1) + (huart->RxXferSize & 1);

    offset = (uart_rx_fifo->head_ptr) % (uint32_t)(huart->RxXferSize);
    copy = tail_ptr - offset;
    uart_rx_fifo->head_ptr += copy;

    ring_fifo_write(uart_rx_fifo->rx_fifo, huart->pRxBuffPtr + offset, copy);
}

/**
 * @brief UART DMA overflow callback.
 *
 * @param huart The handle of UART
 */
void uart_dmarx_done_callback(UART_HandleTypeDef *huart) {
    uart_rx_fifo_t *uart_rx_fifo = uart_rx_identify(huart);
    if (uart_rx_fifo == NULL) {
        return;
    }

    uint32_t tail_ptr;
    uint32_t offset, copy;

    /**
     * +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
     * |                  half                  |
     * |                    | head_ptr tail_ptr |
     * |                    |    |            | |
     * |                    v    v            v |
     * | ------------------------************** |
     * +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
     */

    tail_ptr = huart->RxXferSize;

    offset = (uart_rx_fifo->head_ptr) % (uint32_t)(huart->RxXferSize);
    copy = tail_ptr - offset;
    uart_rx_fifo->head_ptr += copy;

    ring_fifo_write(uart_rx_fifo->rx_fifo, huart->pRxBuffPtr + offset, copy);

    if (huart->hdmarx->Init.Mode != DMA_CIRCULAR) {
        /* Reopen the DMA receive. */
        while (HAL_UART_Receive_DMA(huart, huart->pRxBuffPtr,
                                    huart->RxXferSize) != HAL_OK) {
            __HAL_UNLOCK(huart);
        }
    }
}

/**
 * @brief Read from UART Receive fifo.
 *
 * @param huart The handle of UART
 * @param[out] buf The data buf which receive the data from the fifo.
 * @param buf_size The size of buf.
 * @return The length that be received.
 */
uint32_t uart_dmarx_read(UART_HandleTypeDef *huart, void *buf,
                         size_t buf_size) {
    if ((buf == NULL) || (buf_size == 0)) {
        return 0;
    }
    uart_rx_fifo_t *uart_rx_fifo = uart_rx_identify(huart);

    if (uart_rx_fifo == NULL) {
        return 0;
    }

    return ring_fifo_read(uart_rx_fifo->rx_fifo, buf, buf_size);
}

/**
 * @brief Resize the receive buf and fifo of UART.
 *
 * @param huart The handle of UART
 * @param buf_size New buf size
 * @param fifo_size New fifo size
 * @return Resize message:
 * @retval - 0: Succeess
 * @retval - 1: This uart not enable DMA Rx.
 * @retval - 2: This UART is enabled.
 * @retval - 3: Parameter Error, size can't be 0.
 * @warning Must be disabled the UART before resize!
 *          You should call `u(s)artx_deinit()` before call this function,
 *          than call `u(s)artx_init()` to using new size.
 *          It may allocated fail when reinitialize uart.
 */
uint8_t uart_dmarx_resize_fifo(UART_HandleTypeDef *huart, uint32_t buf_size,
                               uint32_t fifo_size) {
    if ((buf_size == 0) || (fifo_size == 0)) {
        return 3;
    }

    uart_rx_fifo_t *uart_rx_fifo = uart_rx_identify(huart);
    if (uart_rx_fifo == NULL) {
        return 1;
    }

    if (huart->hdmatx != NULL) {
        return 2;
    }

    uart_rx_fifo->buf_size = buf_size;
    uart_rx_fifo->fifo_size = fifo_size;
    return 0;
}

/**
 * @brief Get the buffer size of UART DMA Rx.
 *
 * @param huart The handle of UART.
 * @return The buffer size of UART.
 */
uint32_t uart_dmarx_get_buf_size(UART_HandleTypeDef *huart) {
    uart_rx_fifo_t *uart_rx_fifo = uart_rx_identify(huart);
    if (uart_rx_fifo == NULL) {
        return 0;
    }

    return uart_rx_fifo->buf_size;
}

/**
 * @brief Get the fifo size of UART DMA Rx.
 *
 * @param huart The handle of UART.
 * @return The buffer size of UART.
 */
uint32_t uart_dmarx_get_fifo_size(UART_HandleTypeDef *huart) {
    uart_rx_fifo_t *uart_rx_fifo = uart_rx_identify(huart);
    if (uart_rx_fifo == NULL) {
        return 0;
    }

    return uart_rx_fifo->fifo_size;
}
/**
 * @}
 */

/*****************************************************************************
 * @defgroup Public UART DMA Tx functions.
 * @{
 */

/**
 * @brief Identify the UART transmit buffer by handle.
 *
 * @param huart The handle of UART
 * @return The point of UART tx buffer.
 */
static inline uart_tx_buf_t *uart_tx_identify(UART_HandleTypeDef *huart) {
    switch ((uintptr_t)(huart->Instance)) {

#if USART1_TX_DMA
        case USART1_BASE: {
            return &usart1_tx_buf;
        }
#endif /* USART1_TX_DMA */

#if USART2_TX_DMA
        case USART2_BASE: {
            return &usart2_tx_buf;
        }
#endif /* USART2_TX_DMA */

#if USART3_TX_DMA
        case USART3_BASE: {
            return &usart3_tx_buf;
        }
#endif /* USART3_TX_DMA */

#if UART4_TX_DMA
        case UART4_BASE: {
            return &uart4_tx_buf;
        }
#endif /* UART4_TX_DMA */

#if UART5_TX_DMA
        case UART5_BASE: {
            return &uart5_tx_buf;
        }
#endif /* UART5_TX_DMA */

#if USART6_TX_DMA
        case USART6_BASE: {
            return &usart6_tx_buf;
        }
#endif /* USART6_TX_DMA */

#if UART7_TX_DMA
        case UART7_BASE: {
            return &uart7_tx_buf;
        }
#endif /* UART7_TX_DMA */

#if UART8_TX_DMA
        case UART8_BASE: {
            return &uart8_tx_buf;
        }
#endif /* UART8_TX_DMA */

#if UART9_TX_DMA
        case UART9_BASE: {
            return &uart9_tx_buf;
        }
#endif /* UART9_TX_DMA */

#if UART10_TX_DMA
        case UART10_BASE: {
            return &uart10_tx_buf;
        }
#endif /* UART10_TX_DMA */

        default: {
        } break;
    }

    return NULL;
}

/**
 * @brief Write the transmit data to the buffer.
 *
 * @param huart The handle of UART.
 * @param data The data will be write.
 * @param len The data length will be written.
 * @return The length that be written.
 */
uint32_t uart_dmatx_write(UART_HandleTypeDef *huart, const void *data,
                          size_t len) {
    if ((data == NULL) || (len == 0)) {
        return 0;
    }

    uart_tx_buf_t *send_tx_buf = uart_tx_identify(huart);
    if (send_tx_buf == NULL) {
        return 0;
    }

    /* Get the remain length of buffer. */
    uint32_t buf_remain = send_tx_buf->buf_size - send_tx_buf->head_ptr;

    /* Prevent overflow. */
    if (buf_remain < len) {
        memcpy(send_tx_buf->send_buf + send_tx_buf->head_ptr, data, buf_remain);
        send_tx_buf->head_ptr += buf_remain;
        return buf_remain;
    } else {
        memcpy(send_tx_buf->send_buf + send_tx_buf->head_ptr, data, len);
        send_tx_buf->head_ptr += len;
        return len;
    }
}

/**
 * @brief Transmit the data in the buf.
 *
 * @param huart The handle of UART.
 * @return The length which is succeed transmitted.
 * @note If you want transmit data, using `uart_dmatx_write` before.
 *       If you have huge continous data to transmit, we recommand use
 *       `HAL_UART_Transmit_DMA()`.
 */
uint32_t uart_dmatx_send(UART_HandleTypeDef *huart) {
    uart_tx_buf_t *send_tx_buf = uart_tx_identify(huart);
    if (send_tx_buf == NULL) {
        return 0;
    }

    if (huart->hdmatx == NULL) {
        return 0;
    }

    uint32_t len = send_tx_buf->head_ptr;
    if (len == 0) {
        return 0;
    }

    /* Wait for last transfer end. */
    while (__HAL_UART_GET_FLAG(huart, UART_FLAG_TC) == RESET)
        ;

    HAL_UART_Transmit_DMA(huart, send_tx_buf->send_buf, (uint16_t)len);
    send_tx_buf->head_ptr = 0;
    return len;
}

/**
 * @brief Resize the send buf of UART.
 *
 * @param huart The handle of UART
 * @param size New size
 * @return Resize message:
 * @retval - 0: Succeess
 * @retval - 1: This uart not enable DMA Tx.
 * @retval - 2: No free memory to allocate.
 * @retval - 3: This uart is busy now.
 * @retval - 4: Parameter error, size can't be 0.
 */
uint8_t uart_dmatx_resize_buf(UART_HandleTypeDef *huart, uint32_t size) {
    if (size == 0) {
        return 4;
    }

    uart_tx_buf_t *send_tx_buf = uart_tx_identify(huart);
    if (send_tx_buf == NULL) {
        return 1;
    }

    if ((huart->gState) & (HAL_UART_STATE_BUSY_TX | HAL_UART_STATE_BUSY) &
        ~HAL_UART_STATE_READY) {
        /* The UART is busy. */
        return 3;
    }

    /* The UART is uninitialized, just adjust the size. */
    if (huart->hdmatx == NULL) {
        send_tx_buf->buf_size = size;
        return 0;
    }

    uint8_t *new_ptr = CSP_REALLOC(send_tx_buf->send_buf, size);

    if (new_ptr == NULL) {
        return 2;
    }

    send_tx_buf->send_buf = new_ptr;
    send_tx_buf->buf_size = size;

    return 0;
}

/**
 * @brief Get the buffer size of UART DMA Tx.
 *
 * @param huart The handle of UART.
 * @return The size of UART DMA Tx buf.
 */
uint32_t uart_damtx_get_buf_szie(UART_HandleTypeDef *huart) {
    uart_tx_buf_t *uart_tx_buf = uart_tx_identify(huart);

    if (uart_tx_buf == NULL) {
        return 0;
    }

    return uart_tx_buf->buf_size;
}

/**
 * @}
 */

/*****************************************************************************
 * @defgroup UART interrupt callbacks.
 * @{
 */

/**
 * @brief UART error callbacks.
 *
 * @param huart The handle of UART.
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
    __IO uint32_t error_code = 0x00U;

    error_code = HAL_UART_GetError(huart);
    if (HAL_UART_ERROR_NONE == error_code) {
        return;
    }

    switch (error_code) {
        case HAL_UART_ERROR_PE: {
            __HAL_UART_CLEAR_PEFLAG(huart);
        } break;

        case HAL_UART_ERROR_NE: {
            __HAL_UART_CLEAR_NEFLAG(huart);
        } break;

        case HAL_UART_ERROR_FE: {
            __HAL_UART_CLEAR_FEFLAG(huart);
        } break;

        case HAL_UART_ERROR_ORE: {
            __HAL_UART_CLEAR_OREFLAG(huart);
        } break;

        case HAL_UART_ERROR_DMA: {
        } break;

        default: {
        } break;
    }

    if (NULL != huart->hdmarx) {
        while (
            HAL_UART_Receive_DMA(huart, huart->pRxBuffPtr, huart->RxXferSize)) {
            __HAL_UNLOCK(huart);
        }
    } else {
        /* Reset the receive pointer to buffer init address.
         * Init addr = current addr - received count,
         * received count = buffer size - free count. */
        while (HAL_UART_Receive_IT(
            huart, huart->pRxBuffPtr - (huart->RxXferSize - huart->RxXferCount),
            huart->RxXferSize)) {
            __HAL_UNLOCK(huart);
        }
    }
}

#if USE_HAL_UART_REGISTER_CALLBACKS == 0

/**
 * @brief Rx Transfer completed callbacks.
 *
 * @param huart The handle of UART.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->hdmarx != NULL) {
        uart_dmarx_done_callback(huart);
    }
}

/**
 * @brief Rx Half Transfer completed callbacks.
 *
 * @param huart The handle of UART.
 */
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->hdmarx != NULL) {
        uart_dmarx_halfdone_callback(huart);
    }
}

#endif /* USE_HAL_UART_REGISTER_CALLBACKS == 0 */

/**
 * @}
 */
