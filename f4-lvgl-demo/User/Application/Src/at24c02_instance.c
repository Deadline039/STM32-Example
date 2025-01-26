/**
 * @file    at24c02_instance.c
 * @author  Deadline039
 * @brief   AT24Cxx 系列芯片实例
 * @version 0.1
 * @date    2025-01-26
 */

#include "includes.h"

at24cxx_handle_t at24c02_handle;

/**
 * @brief 初始化 AT24C02
 *
 */
void at24c02_instance_init(void) {
    at24cxx_init(&at24c02_handle, &i2c2_handle, AT24C02, AT24CXX_ADDRESS_A000);
}