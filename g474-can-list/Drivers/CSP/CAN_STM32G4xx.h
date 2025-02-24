
/**
 * @file    CAN_STM32G4xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of CAN on STM32G4xx
 * @version 1.0
 * @date    2025-02-05
 * @note    The calculation formula of CAN rate reference to NXP
 *          Application Note: CAN Bit Timing Requirements (AN1798)
 *          https://www.nxp.com/docs/en/application-note/AN1798.pdf
 *          This formula is calculation the legacy CAN, we will support 
 *          FDCAN in the feature.
 *
 *          This code is generate automatically.
 */

#ifndef __CAN_STM32G4XX_H
#define __CAN_STM32G4XX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************
 * @defgroup Public Marco of CAN.
 * @{
 */

#define CAN_INIT_OK             0
#define CAN_INIT_RATE_ERR       1
#define CAN_INIT_FILTER_FAIL    2
#define CAN_INIT_FAIL           3
#define CAN_INIT_START_FAIL     4
#define CAN_INIT_NOTIFY_FAIL    5
#define CAN_INITED              6

#define CAN_DEINIT_OK           0
#define CAN_DEINIT_FAIL         1
#define CAN_NO_INIT             2

/* Wait for can tx mailbox empty times. */
#define CAN_SEND_TIMEOUT        100

/**
 * @}
 */


/*****************************************************************************
 * @defgroup Public type and variables of CAN.
 * @{
 */

/**
 * @brief Select which CAN will be used.
 */
typedef enum {
    can1_selected = 0U, /*!< Select CAN1 */
    can2_selected,      /*!< Select CAN2 */
    can3_selected       /*!< Select CAN3 */
} can_selected_t;

/**
 * @}
 */

/*****************************************************************************
 * @defgroup FDCAN1 Functions
 * @{
 */

#if FDCAN1_ENABLE

#if (FDCAN1_TX_ID == 0)
#  define FDCAN1_TX_AF GPIO_AF9_FDCAN1
#elif (FDCAN1_TX_ID == 1)
#  define FDCAN1_TX_AF GPIO_AF9_FDCAN1
#elif (FDCAN1_TX_ID == 2)
#  define FDCAN1_TX_AF GPIO_AF9_FDCAN1
#  if (defined(STM32GBK1CB))
#    error "PD1 can not be configured as FDCAN1 TX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* FDCAN1_TX_ID */

#if (FDCAN1_RX_ID == 0)
#  define FDCAN1_RX_AF GPIO_AF9_FDCAN1
#elif (FDCAN1_RX_ID == 1)
#  define FDCAN1_RX_AF GPIO_AF9_FDCAN1
#elif (FDCAN1_RX_ID == 2)
#  define FDCAN1_RX_AF GPIO_AF9_FDCAN1
#  if (defined(STM32GBK1CB))
#    error "PD0 can not be configured as FDCAN1 RX on STM32GBK1CB! "
#  endif  /* (defined(STM32GBK1CB)) */
#endif  /* FDCAN1_RX_ID */

extern FDCAN_HandleTypeDef fdcan1_handle;

uint8_t fdcan1_init(uint32_t baud_rate, uint32_t fd_mode, uint32_t prop_delay);
uint8_t fdcan1_deinit(void); 

/* Compatibility with CAN Classic. */
#define can1_handle fdcan1_handle
#define can1_init(baud_rate, prop_delay)                                       \
    do {                                                                       \
        fdcan1_init(baud_rate, FDCAN_FRAME_CLASSIC, prop_delay);               \
    } while (0)
#define can1_deinit fdcan1_deinit

#endif /* FDCAN1_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup FDCAN2 Functions
 * @{
 */

#if FDCAN2_ENABLE

#if (FDCAN2_TX_ID == 0)
#  define FDCAN2_TX_AF GPIO_AF9_FDCAN2
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB))
#    error "PB6 can not be configured as FDCAN2 TX on STM32G431xx, STM32G441xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB)) */
#elif (FDCAN2_TX_ID == 1)
#  define FDCAN2_TX_AF GPIO_AF9_FDCAN2
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB))
#    error "PB13 can not be configured as FDCAN2 TX on STM32G431xx, STM32G441xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB)) */
#endif  /* FDCAN2_TX_ID */

#if (FDCAN2_RX_ID == 0)
#  define FDCAN2_RX_AF GPIO_AF9_FDCAN2
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB))
#    error "PB5 can not be configured as FDCAN2 RX on STM32G431xx, STM32G441xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB)) */
#elif (FDCAN2_RX_ID == 1)
#  define FDCAN2_RX_AF GPIO_AF9_FDCAN2
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB))
#    error "PB12 can not be configured as FDCAN2 RX on STM32G431xx, STM32G441xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32GBK1CB)) */
#endif  /* FDCAN2_RX_ID */

extern FDCAN_HandleTypeDef fdcan2_handle;

uint8_t fdcan2_init(uint32_t baud_rate, uint32_t fd_mode, uint32_t prop_delay);
uint8_t fdcan2_deinit(void); 

/* Compatibility with CAN Classic. */
#define can2_handle fdcan2_handle
#define can2_init(baud_rate, prop_delay)                                       \
    do {                                                                       \
        fdcan2_init(baud_rate, FDCAN_FRAME_CLASSIC, prop_delay);               \
    } while (0)
#define can2_deinit fdcan2_deinit

#endif /* FDCAN2_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup FDCAN3 Functions
 * @{
 */

#if FDCAN3_ENABLE

#if (FDCAN3_TX_ID == 0)
#  define FDCAN3_TX_AF GPIO_AF11_FDCAN3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PA15 can not be configured as FDCAN3 TX on STM32G431xx, STM32G441xx, STM32G471xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (FDCAN3_TX_ID == 1)
#  define FDCAN3_TX_AF GPIO_AF11_FDCAN3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PB4 can not be configured as FDCAN3 TX on STM32G431xx, STM32G441xx, STM32G471xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* FDCAN3_TX_ID */

#if (FDCAN3_RX_ID == 0)
#  define FDCAN3_RX_AF GPIO_AF11_FDCAN3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PA8 can not be configured as FDCAN3 RX on STM32G431xx, STM32G441xx, STM32G471xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#elif (FDCAN3_RX_ID == 1)
#  define FDCAN3_RX_AF GPIO_AF11_FDCAN3
#  if (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB))
#    error "PB3 can not be configured as FDCAN3 RX on STM32G431xx, STM32G441xx, STM32G471xx, STM32G491xx, STM32G4A1xx, STM32GBK1CB! "
#  endif  /* (defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx) || defined(STM32GBK1CB)) */
#endif  /* FDCAN3_RX_ID */

extern FDCAN_HandleTypeDef fdcan3_handle;

uint8_t fdcan3_init(uint32_t baud_rate, uint32_t fd_mode, uint32_t prop_delay);
uint8_t fdcan3_deinit(void); 

/* Compatibility with CAN Classic. */
#define can3_handle fdcan3_handle
#define can3_init(baud_rate, prop_delay)                                       \
    do {                                                                       \
        fdcan3_init(baud_rate, FDCAN_FRAME_CLASSIC, prop_delay);               \
    } while (0)
#define can3_deinit fdcan3_deinit

#endif /* FDCAN3_ENABLE */

/**
 * @}
 */


/*****************************************************************************
 * @defgroup Public functions of CAN.
 * @{
 */

/* Compatibility with CAN Classic. */
#define can_send_message fdcan_send_message
#define can_send_remote  fdcan_send_remote
#define CAN_ID_STD       FDCAN_STANDARD_ID
#define CAN_ID_EXT       FDCAN_EXTENDED_ID
#define CAN_RTR_DATA     FDCAN_DATA_FRAME
#define CAN_RTR_REMOTE   FDCAN_REMOTE_FRAME

uint8_t can_rate_calc(uint32_t baud_rate, uint32_t prop_delay,
                      uint32_t base_freq, uint32_t *prescale, uint32_t *tsjw,
                      uint32_t *tseg1, uint32_t *tseg2);

FDCAN_HandleTypeDef *fdcan_get_handle(can_selected_t can_selected);
uint8_t fdcan_send_message(can_selected_t can_selected, uint32_t can_ide,
                           uint32_t id, uint8_t len, const uint8_t *msg);
uint8_t fdcan_send_remote(can_selected_t can_selected, uint32_t can_ide,
                          uint32_t id, uint8_t len, const uint8_t *msg);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CAN_STM32G4XX_H */
