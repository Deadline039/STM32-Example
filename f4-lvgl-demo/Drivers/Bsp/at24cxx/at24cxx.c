/**
 * @file    at24cxx.c
 * @author  Deadline039
 * @brief   AT24CXX系列芯片驱动
 * @version 1.0
 * @date    2024-09-03
 */

#include "at24cxx.h"

static I2C_HandleTypeDef *at24cxx_hi2c;

/**
 * @brief I2C 读取一字节
 *
 * @param dev_address 设备地址
 * @param data_address 数据地址
 * @return 读到的字节
 */
uint8_t i2c_read_byte(uint16_t dev_address, uint16_t data_address) {
    uint8_t data;
    HAL_I2C_Mem_Read(at24cxx_hi2c, dev_address, data_address,
                     I2C_MEMADD_SIZE_8BIT, &data, 1, 0xF);
    return data;
}

/**
 * @brief I2C 写入一字节
 *
 * @param dev_address 设备地址
 * @param data_address 数据地址
 * @param data 写入的数据
 */
void i2c_write_byte(uint16_t dev_address, uint16_t data_address, uint8_t data) {
    HAL_I2C_Mem_Write(at24cxx_hi2c, dev_address, data_address,
                      I2C_MEMADD_SIZE_8BIT, &data, 1, 0xF);

    /* Check if the Devices is ready for a new operation */
    while (HAL_I2C_IsDeviceReady(at24cxx_hi2c, dev_address, 0xF, 0xF) != HAL_OK)
        ;

    /* Wait for the end of the transfer */
    while (HAL_I2C_GetState(at24cxx_hi2c) != HAL_I2C_STATE_READY)
        ;
}

/**
 * @brief 初始化 AT24Cxx 芯片
 *
 * @param hi2c I2C 句柄
 * @return 芯片是否正常工作
 */
bool at24cxx_init(I2C_HandleTypeDef *hi2c) {
    at24cxx_hi2c = hi2c;
    return at24cxx_check();
}

/**
 * @brief 检查AT24Cxx芯片
 *
 * @return 是否正常工作
 *  @note 检测原理: 在器件的末地址写如0X55, 然后再读取. 如果读取值为0X55
 *        则表示检测正常. 否则, 则表示检测失败.
 */
bool at24cxx_check(void) {
    uint8_t temp = at24cxx_read_byte(AT24CXX_TYPE);
    if (temp == 0x55) {
        return true;
    }

    at24cxx_write_byte(AT24CXX_TYPE, 0x55);
    temp = at24cxx_read_byte(AT24CXX_TYPE);

    if (temp == 0x55) {
        return true;
    }

    return false;
}

/**
 * @brief 读取一字节数据
 *
 * @param address 地址
 * @return 数据
 */
uint8_t at24cxx_read_byte(uint16_t address) {
    if (AT24CXX_TYPE >= AT24C16) {
        /**
         * 小于 2 Kbyte 寻址是: 数据地址8bit + 设备地址3bit
         * 地址组合思路:
         *      先按照芯片容量, 决定A2, A1, A0是否需要, 需要置1,
         *      与定义的设备地址按位与, 得到设备地址的值1
         *      数据地址高8位与芯片容量按位与,
         *      超出芯片容量的位置0, 得到设备地址的值2
         *      再将两个值按位或, 即可得到芯片的设备地址
         */
        uint16_t dev_address = (AT24CXX_ADDRESS & (~(AT24CXX_TYPE >> 8) << 1)) |
                               ((AT24CXX_TYPE & address) >> 8 << 1);
        return i2c_read_byte(dev_address, (address & 0xFF));
    }
    return i2c_read_byte(AT24CXX_ADDRESS, address & 0xFF);
}

/**
 * @brief 写入一字节数据
 *
 * @param address 数据地址
 * @param byte 数据内容
 */
void at24cxx_write_byte(uint16_t address, uint8_t byte) {
    if (AT24CXX_TYPE >= AT24C16) {
        /**
         * 小于 2 Kbyte 寻址是: 数据地址8bit + 设备地址3bit
         * 地址组合思路:
         *      先按照芯片容量, 决定A2, A1, A0是否需要, 需要置1,
         *      与定义的设备地址按位与, 得到设备地址的值1
         *      数据地址高8位与芯片容量按位与,
         *      超出芯片容量的位置0, 得到设备地址的值2
         *      再将两个值按位或, 即可得到芯片的设备地址
         */
        uint16_t dev_address = (AT24CXX_ADDRESS & (~(AT24CXX_TYPE >> 8) << 1)) |
                               ((AT24CXX_TYPE & address) >> 8 << 1);
        i2c_write_byte(dev_address, (address & 0xFF), byte);
    }
    i2c_write_byte(AT24CXX_ADDRESS, address, byte);
}

/**
 * @brief 读取n字节数据
 *
 * @param address 数据起始地址
 * @param[out] data_buf 数据接收缓冲区
 * @param data_len 要读取的数据长度
 */
void at24cxx_read(uint16_t address, uint8_t *data_buf, uint16_t data_len) {
    for (size_t i = 0; i < data_len; ++i) {
        data_buf[i] = at24cxx_read_byte(address + i);
    }
}

/**
 * @brief 写入n字节数据
 *
 * @param address 数据起始地址
 * @param data_buf 数据接收缓冲区
 * @param data_len 要读取的数据长度
 */
void at24cxx_write(uint16_t address, uint8_t *data_buf, uint16_t data_len) {
    for (size_t i = 0; i < data_len; ++i) {
        at24cxx_write_byte(address + i, data_buf[i]);
    }
}
