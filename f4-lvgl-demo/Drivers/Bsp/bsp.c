/**
 * @file    bsp.c
 * @author  Deadline039
 * @brief   Bsp layer initialize.
 * @version 1.0
 * @date    2024-09-18
 */

#include "bsp.h"

/**
 * @brief Bsp layer initiallize.
 *
 */
void bsp_init(void) {
    HAL_Init();
    system_clock_config();
    delay_init(180);
    usart1_init(115200);
    i2c2_init(250000, 0x00, I2C_ADDRESSINGMODE_7BIT);
    spi5_init(SPI_MODE_MASTER, SPI_CLK_MODE3, SPI_DATASIZE_8BIT,
              SPI_FIRSTBIT_MSB);
    led_init();
    key_init();
    sdram_init();
}

#ifdef USE_FULL_ASSERT

#include <stdio.h>

/**
 * @brief HAL assert failed.
 *
 * @param file File name.
 * @param line Line.
 */
void assert_failed(uint8_t *file, uint32_t line) {
    fprintf(stderr, "HAL assert failed. In file: %s, line: %d\r\n", file, line);
}

#endif /* USE_FULL_ASSERT */