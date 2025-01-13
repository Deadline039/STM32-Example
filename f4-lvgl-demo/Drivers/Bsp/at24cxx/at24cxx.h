/**
 * @file    at24cxx.h
 * @author  Deadline039
 * @brief   AT24Cxx系列芯片驱动
 * @version 1.0
 * @date    2024-09-03
 */

#ifndef __AT24CXX_H
#define __AT24CXX_H

#include <CSP_Config.h>

#include <stdbool.h>

#define AT24C01            0x007FU
#define AT24C02            0x00FFU
#define AT24C04            0x01FFU
#define AT24C08            0x03FFU
#define AT24C16            0x07FFU
#define AT24C32            0x0FFFU
#define AT24C64            0x1FFFU
#define AT24C128           0x3FFFU
#define AT24C256           0x7FFFU

/* 定义使用的芯片, Mini板是AT24C02 */
#define AT24CXX_TYPE       AT24C02

/**
 * A0 A1 A2引脚电平, 用于定义地址.
 * 对于AT24C16以下型号:
 *    对于24C01/02,
 *       24C32/64, 其器件地址格式(8bit)为: 1  0  1  0  A2  A1  A0  R/W
 *    对于24C04,    其器件地址格式(8bit)为: 1  0  1  0  A2  A1  a8  R/W
 *    对于24C08,    其器件地址格式(8bit)为: 1  0  1  0  A2  a9  a8  R/W
 *    对于24C16,    其器件地址格式(8bit)为: 1  0  1  0  a10 a9  a8  R/W
 *    R/W      : 读/写控制位 0,表示写; 1,表示读;
 *    A0/A1/A2 : 对应器件的1,2,3引脚, 如果芯片对应的引脚位置为数据地址, 则无用
 *    a8/a9/a10: 对应存储整列的高位地址,
 * 11bit地址最多可以表示2048个位置,可以寻址24C16及以内的型号
 * 对于AT24C128/256, A2必须为0
 */
#define AT24CXX_ADDRESS_A0 0
#define AT24CXX_ADDRESS_A1 0
#define AT24CXX_ADDRESS_A2 0

#define AT24CXX_ADDRESS                                                        \
    ((0x0A << 4) | (AT24CXX_ADDRESS_A2 << 3) | (AT24CXX_ADDRESS_A1 << 2) |     \
     (AT24CXX_ADDRESS_A0 << 1))

bool at24cxx_init(I2C_HandleTypeDef *hi2c);

bool at24cxx_check(void);

uint8_t at24cxx_read_byte(uint16_t address);
void at24cxx_write_byte(uint16_t address, uint8_t byte);

void at24cxx_read(uint16_t address, uint8_t *data_buf, uint16_t data_len);
void at24cxx_write(uint16_t address, uint8_t *data_buf, uint16_t data_len);

uint8_t at24cxx_read_byte(uint16_t address);
void at24cxx_write_byte(uint16_t address, uint8_t byte);

void at24cxx_read(uint16_t address, uint8_t *data_buf, uint16_t data_len);
void at24cxx_write(uint16_t address, uint8_t *data_buf, uint16_t data_len);

#endif /* __AT24CXX_H */
