/**
 * @file        sdram.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       SDRAM 驱动代码
 * @copyright   2020-2032, 广州市星翼电子科技有限公司
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2022-04-20   1.0         Alientek    第一次发布
 */

#ifndef __SDRAM_H
#define __SDRAM_H

#include <CSP_Config.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern SDRAM_HandleTypeDef g_sdram_handle;

#define BANK5_SDRAM_ADDR                         ((uint32_t)(0XC0000000))

/* SDRAM配置参数 */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

void sdram_init(void);
uint8_t sdram_send_cmd(uint8_t bankx, uint8_t cmd, uint8_t refresh,
                       uint16_t regval);
void fmc_sdram_write_buffer(uint8_t *pbuf, uint32_t addr, uint32_t n);
void fmc_sdram_read_buffer(uint8_t *pbuf, uint32_t addr, uint32_t n);
void sdram_initialization_sequence(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SDRAM_H */
