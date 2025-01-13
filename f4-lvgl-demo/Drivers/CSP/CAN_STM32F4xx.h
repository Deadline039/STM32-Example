/**
 * @file    CAN_STM32F4xx.h
 * @author  Deadline039
 * @brief   Chip Support Package of CAN on STM32F4xx
 * @version 1.0
 * @date    2024-10-22
 * @note    The calculation formula of CAN rate reference to NXP
 *          Application Note: CAN Bit Timing Requirements (AN1798)
 *          https://www.nxp.com/docs/en/application-note/AN1798.pdf
 */

#ifndef __CAN_STM32F4XX_H
#define __CAN_STM32F4XX_H

/* clang-format off */

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
#define CAN_INIT_MEM_FAIL       3
#define CAN_INIT_FAIL           4
#define CAN_INIT_START_FAIL     5
#define CAN_INIT_NOTIFY_FAIL    6
#define CAN_INITED              7

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
 * @defgroup CAN1 Functions.
 * @{
 */

#if CAN1_ENABLE

#  if defined(STM32F413xx) || defined(STM32F423xx)
/* CAN1_RX available on pins: PA11, PB8, PD0, PG0 */
#    if (CAN1_RX_PORT_ID == 3)
#      error                                                                   \
          "Only PA11, PB8, PD0, PG0 can be configured as CAN1 RX on selected device!"
#    endif
/* CAN1_TX available on pins: PA12, PB9, PD1, PG1 */
#    if (CAN1_TX_PORT_ID == 3)
#      error                                                                   \
          "Only PA12, PB9, PD1, PG1 can be configured as CAN1 TX on selected device!"
#    endif
#  endif

#  if (CAN1_RX_PORT_ID == 1) &&                                                \
      (defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || \
       defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx))
#    define CAN1_RX_GPIO_AF GPIO_AF8_CAN1
#  else
#    define CAN1_RX_GPIO_AF GPIO_AF9_CAN1
#  endif

#  if (CAN1_TX_PORT_ID == 1) &&                                                \
      (defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || \
       defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx))
#    define CAN1_TX_GPIO_AF GPIO_AF8_CAN1
#  else
#    define CAN1_TX_GPIO_AF GPIO_AF9_CAN1
#  endif

extern CAN_HandleTypeDef can1_handle;
uint8_t can1_init(uint32_t baud_rate, uint32_t prop_delay);
uint8_t can1_deinit(void);

#endif /* CAN1_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup CAN2 Functions.
 * @{
 */

#if CAN2_ENABLE

#  if !CAN1_ENABLE
#    error "You must enable CAN1 before you can use CAN2. "
#  endif /* !CAN1_ENABLE */

extern CAN_HandleTypeDef can2_handle;
uint8_t can2_init(uint32_t baud_rate, uint32_t prop_delay);
uint8_t can2_deinit(void);

#endif /* CAN2_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup CAN2 Functions.
 * @{
 */

#if CAN3_ENABLE

extern CAN_HandleTypeDef can3_handle;
uint8_t can3_init(uint32_t baud_rate, uint32_t prop_delay);
uint8_t can3_deinit(void);

#endif /* CAN3_ENABLE */

/**
 * @}
 */

/* clang-format on */

/*****************************************************************************
 * @defgroup Public functions of CAN.
 * @{
 */

uint8_t can_rate_calc(uint32_t baud_rate, uint32_t prop_delay,
                      uint32_t base_freq, uint32_t *prescale, uint32_t *tsjw,
                      uint32_t *tseg1, uint32_t *tseg2);

CAN_HandleTypeDef *can_get_handle(can_selected_t can_select);
uint8_t can_send_message(can_selected_t can_selected, uint32_t can_ide,
                         uint32_t id, uint8_t len, const uint8_t *msg);
uint8_t can_send_remote(can_selected_t can_selected, uint32_t can_ide,
                        uint32_t id, uint8_t len, const uint8_t *msg);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CAN_STM32F4XX_H */