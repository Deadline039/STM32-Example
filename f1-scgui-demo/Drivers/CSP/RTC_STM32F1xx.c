
/**
 * @file    RTC_STM32F1xx.c
 * @author  Deadline039
 * @brief   Chip Support Package of RTC on STM32F1xx
 * @version 1.0
 * @date    2024-08-30
 */

#include "CSP_Config.h"

#include "RTC_STM32F1xx.h"

RTC_HandleTypeDef rtc_handle;

#define RTC_USE_LSE 0x8800 /* Configuration to use external clock. */
#define RTC_USE_LSI 0x8801 /* Configuration to use internal clock. */

/**
 * @brief RTC initialization.
 *
 * @return RTC init status:
 * @retval - 0: `RTC_INIT_OK`:      Success.
 * @retval - 1: `RTC_INIT_FAIL`:    RTC init failed.
 * @retval - 2: `RTC_INIT_RESET`:   RTC clock is reseted.
 * @retval - 3: `RTC_INITED`:       RTC is inited.
 */
uint8_t rtc_init(void) {
    if (HAL_RTC_GetState(&rtc_handle) != HAL_RTC_STATE_RESET) {
        return RTC_INITED;
    }

    uint16_t bkp_flag = 0;

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();

    bkp_flag = HAL_RTCEx_BKUPRead(&rtc_handle, RTC_BKP_DR1);

    rtc_handle.Instance = RTC;
    rtc_handle.Init.AsynchPrediv = 0x7FFF;
    rtc_handle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;

    if (HAL_RTC_Init(&rtc_handle) != HAL_OK) {
        return RTC_INIT_FAIL;
    }

    if ((bkp_flag != RTC_USE_LSE) && (bkp_flag != RTC_USE_LSI)) {
        time_t init_time = 0;
        rtc_set_time_t(&init_time);
        return RTC_INIT_RESET;
    }

    return RTC_INIT_OK;
}

/**
 * @brief RTC deinit
 *
 * @return RTC deinit status:
 * @retval - 0: `RTC_DEINIT_OK`:    Success.
 * @retval - 1: `RTC_DEINIT_FAIL`:  RTC deinit failed.
 * @retval - 3: `RTC_NO_INIT`:      RTC is not init.
 */
uint8_t rtc_deinit(void) {
    if (HAL_RTC_GetState(&rtc_handle) == HAL_RTC_STATE_RESET) {
        return RTC_NO_INIT;
    }

    if (HAL_RTC_DeInit(&rtc_handle) != HAL_OK) {
        return RTC_DEINIT_FAIL;
    }

    return RTC_DEINIT_OK;
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc) {
    uint16_t retry = 200;

    __HAL_RCC_RTC_ENABLE();
    HAL_PWR_EnableBkUpAccess();

    RCC_OscInitTypeDef rcc_osc_initstruct;
    RCC_PeriphCLKInitTypeDef rcc_periphclk_initstruct;

    RCC->BDCR |= 1 << 0; /* Open external low speed clock. */

    while (retry && ((RCC->BDCR & 0X02) == 0)) {
        /* Wait LSE ready. */
        retry--;
        HAL_Delay(5);
    }

    if (retry == 0) {
        /* External clock startup failed, use interal clock. */
        rcc_osc_initstruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
        rcc_osc_initstruct.LSEState = RCC_LSI_ON;
        rcc_osc_initstruct.PLL.PLLState = RCC_PLL_NONE;
        HAL_RCC_OscConfig(&rcc_osc_initstruct);

        rcc_periphclk_initstruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
        rcc_periphclk_initstruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
        HAL_RCCEx_PeriphCLKConfig(&rcc_periphclk_initstruct);
        HAL_RTCEx_BKUPWrite(hrtc, RTC_BKP_DR1, RTC_USE_LSI);
    } else {
        rcc_osc_initstruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
        rcc_osc_initstruct.LSEState = RCC_LSE_ON;
        rcc_osc_initstruct.PLL.PLLState = RCC_PLL_NONE;
        HAL_RCC_OscConfig(&rcc_osc_initstruct);

        rcc_periphclk_initstruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
        rcc_periphclk_initstruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
        HAL_RCCEx_PeriphCLKConfig(&rcc_periphclk_initstruct);
        HAL_RTCEx_BKUPWrite(hrtc, RTC_BKP_DR1, RTC_USE_LSE);
    }

#if RTC_IT_ENABLE
    HAL_NVIC_SetPriority(RTC_IRQn, RTC_IT_PRIORITY, RTC_IT_SUB);
    HAL_NVIC_EnableIRQ(RTC_IRQn);
#endif /* RTC_IT_ENABLE */

#if RTC_ALARM_IT_ENABLE
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, RTC_ALARM_IT_PRIORITY,
                         RTC_ALARM_IT_SUB);
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
#endif /* RTC_ALARM_IT_ENABLE */
}

/**
 * @brief RTC low level deinitialization.
 *
 * @param hrtc The handle of RTC.
 */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc) {
    UNUSED(hrtc);

    __HAL_RCC_RTC_DISABLE();

#if RTC_IT_ENABLE
    HAL_NVIC_DisableIRQ(RTC_IRQn);
#endif /* RTC_IT_ENABLE */

#if RTC_ALARM_IT_ENABLE
    HAL_NVIC_DisableIRQ(RTC_Alarm_IRQn);
#endif /* RTC_ALARM_IT_ENABLE */
}

#if RTC_IT_ENABLE

/**
 * @brief RTC global ISR.
 *
 */
void RTC_IRQHandler(void) {
    HAL_RTCEx_RTCIRQHandler(&rtc_handle);
}

#endif /* RTC_IT_ENABLE */

#if RTC_ALARM_IT_ENABLE

/**
 * @brief RTC alarm ISR.
 *
 */
void RTC_Alarm_IRQHandler(void) {
    HAL_RTC_AlarmIRQHandler(&rtc_handle);
}

#endif /* RTC_ALARM_IT_ENABLE */

/**
 * @brief Get the week day of specific date.
 *
 * @param year Year
 * @param month Month
 * @param day Day
 * @return Weekday:
 * @retval - 0:     Sunday
 * @retval - 1 ~ 6: Monday to Saturday.
 * @note Use Kim Larsen calculation formula. You can
 *       see: https://www.cnblogs.com/fengbohello/p/3264300.html
 */
uint8_t rtc_get_week(uint16_t year, uint8_t month, uint8_t day) {
    uint8_t week = 0;

    if (month < 3) {
        month += 12;
        --year;
    }

    week = (day + 1 + 2 * month + 3 * (month + 1) / 5 + year + (year >> 2) -
            year / 100 + year / 400) %
           7;
    return week;
}

/**
 * @brief Get now timestamp (Unix timestamp).
 *
 * @return Unix timestamp.
 */
time_t rtc_get_time_t(void) {
    return time(NULL);
}

/**
 * @brief Get now time with time structure.
 *
 * @return The now time.
 */
struct tm *rtc_get_time(void) {
    time_t time_seconds = time(NULL);
    return localtime(&time_seconds);
}

/**
 * @brief Set time by timestamp.
 *
 * @param _time Now time timestamp.
 */
void rtc_set_time_t(const time_t *_time) {
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();

    RTC->CRL |= 1 << 4; /* Allow RTC configuration. */

    RTC->CNTL = *_time & 0xffff;
    RTC->CNTH = *_time >> 16;

    RTC->CRL &= ~(1 << 4); /* Update configuration. */

    /* Wait Operation finished. */
    while (!__HAL_RTC_ALARM_GET_FLAG(&rtc_handle, RTC_FLAG_RTOFF))
        ;
}

/**
 * @brief Set time by time structure.
 *
 * @param _tm Now time structure.
 */
void rtc_set_time(struct tm *_tm) {
    time_t now_time;
    now_time = mktime(_tm);
    rtc_set_time_t(&now_time);
}

/**
 * @brief Get alarm timestamp.
 *
 * @return Alarm timestamp.
 */
time_t rtc_get_alarm_t(void) {
    return (time_t)((RTC->ALRH << 16) | (RTC->ALRL & 0xffff));
}

/**
 * @brief Get alarm time.
 *
 * @return Alarm time.
 */
struct tm *rtc_get_alarm(void) {
    time_t alarm_time = rtc_get_alarm_t();
    return localtime(&alarm_time);
}

/**
 * @brief Set alarm by timestamp.
 *
 * @param _time Alarm time.
 */
void rtc_set_alarm_t(const time_t *_time) {
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();

    RTC->CRL |= 1 << 4; /* Allow RTC Configuration. */

    RTC->ALRL = *_time & 0xffff;
    RTC->ALRH = *_time >> 16;

    RTC->CRL &= ~(1 << 4); /* Update configuration. */

    /* Wait Operation finished. */
    while (!__HAL_RTC_ALARM_GET_FLAG(&rtc_handle, RTC_FLAG_RTOFF))
        ;
    /* Enable the RTC alarm interrupt. */
    __HAL_RTC_ALARM_CLEAR_FLAG(&rtc_handle, RTC_FLAG_ALRAF);
    __HAL_RTC_ALARM_ENABLE_IT(&rtc_handle, RTC_IT_ALRA);

    __HAL_RTC_ALARM_EXTI_ENABLE_IT();
    __HAL_RTC_ALARM_EXTI_ENABLE_RISING_EDGE();
}

/**
 * @brief Set alarm by time struct.
 *
 * @param _tm Alarm time.
 */
void rtc_set_alarm(struct tm *_tm) {
    time_t alarm_time;
    alarm_time = mktime(_tm);
    rtc_set_alarm_t(&alarm_time);
}

/**
 * @brief Redefine the C library time funciton.
 *
 * @param[out] _time The timestamp to receive.
 * @return Now timestamp.
 */
time_t time(time_t *_time) {
    if (_time != NULL) {
        *_time = ((RTC->CNTH << 16) | (RTC->CNTL & 0xffff));
    }
    return (RTC->CNTH << 16) | (RTC->CNTL & 0xffff);
}
