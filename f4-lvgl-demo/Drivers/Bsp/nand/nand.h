/**
 * @file        nand.c
 * @author      正点原子团队 (ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       NAND FLASH 驱动代码
 * @copyright   2020-2032, 广州市星翼电子科技有限公司
 *
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2022-04-20   1.0         Alientek    第一次发布
 */

#ifndef __NAND_H
#define __NAND_H

#include <CSP_Config.h>

#include "ftl.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NAND_DEBUG(...)                                                        \
    do {                                                                       \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
    } while (0)

/*****************************************************************************
 * @defgroup RB 引脚定义
 * @{
 */

/* 引脚 定义 */

#define NAND_RB_GPIO_PORT D
#define NAND_RB_GPIO_PIN  GPIO_PIN_6

#define NAND_RB                                                                \
    HAL_GPIO_ReadPin(CSP_GPIO_PORT(NAND_RB_GPIO_PORT), NAND_RB_GPIO_PIN)

/**
 * @}
 */

/*****************************************************************************
 * @defgroup NAND Flash 参数定义
 * @{
 */

/* 定义 NAND FLASH 的最大的 PAGE 大小（不包括 SPARE 区）, 默认 4096 字节 */
#define NAND_MAX_PAGE_SIZE   4096
/* 执行 ECC 计算的单元大小, 默认 512 字节 */
#define NAND_ECC_SECTOR_SIZE 512

/* NAND FLASH 操作相关延时函数 */

/* tADL 等待延迟, 最少 70ns */
#define NAND_TADL_DELAY      30
/* tWHR 等待延迟, 最少 60ns */
#define NAND_TWHR_DELAY      25
/* tRHW 等待延迟, 最少 100ns */
#define NAND_TRHW_DELAY      35
/* tPROG 等待延迟, 典型值 200us, 最大需要 700us */
#define NAND_TPROG_DELAY     200
/* tBERS 等待延迟, 典型值 3.5ms, 最大需要 10ms */
#define NAND_TBERS_DELAY     4

/**
 * @brief NAND Flash 设备信息
 */
typedef struct {
    uint16_t page_totalsize; /*!< 每页总大小, main 区和 spare 区总和 */
    uint16_t page_mainsize;  /*!< 每页的 main 区大小 */
    uint16_t page_sparesize; /*!< 每页的 spare 区大小 */
    uint8_t block_pagenum;   /*!< 每个块包含的页数量 */
    uint16_t plane_blocknum; /*!< 每个 plane 包含的块数量 */
    uint16_t block_totalnum; /*!< 总的块数量 */
    uint16_t good_blocknum;  /*!< 好块数量 */
    uint16_t valid_blocknum; /*!< 有效块数量 (供文件系统使用的好块数量) */
    uint32_t id;             /*!< ID */
    uint16_t *lut;     /*!< LUT 表, 用作逻辑块 - 物理块转换 */
    uint32_t ecc_hard; /*!< 硬件计算出来的 ECC 值 */
    /*!< ECC 硬件计算值缓冲区 */
    uint32_t ecc_hdbuf[NAND_MAX_PAGE_SIZE / NAND_ECC_SECTOR_SIZE];
    /*!< ECC 读取的值缓冲区 */
    uint32_t ecc_rdbuf[NAND_MAX_PAGE_SIZE / NAND_ECC_SECTOR_SIZE];
} nand_dev_t;

extern nand_dev_t nand_dev;

/* nand flash 的访问地址, 接 NCE3, 地址为：0X8000 0000 */
#define NAND_ADDRESS       0X80000000

/**
 * @}
 */

/*****************************************************************************
 * @defgroup NAND Flash 指令定义
 * @{
 */

#define NAND_CMD           1 << 16 /* 发送命令 */
#define NAND_ADDR          1 << 17 /* 发送地址 */

/* NAND FLASH 命令 */
#define nand_readID        0X90 /* 读 ID 指令 */
#define NAND_FEATURE       0XEF /* 设置特性指令 */
#define NAND_RESET         0XFF /* 复位 NAND */
#define NAND_READSTA       0X70 /* 读状态 */
#define NAND_AREA_A        0X00
#define NAND_AREA_TRUE1    0X30
#define NAND_WRITE0        0X80
#define NAND_WRITE_TURE1   0X10
#define NAND_ERASE0        0X60
#define NAND_ERASE1        0XD0
#define NAND_MOVEDATA_CMD0 0X00
#define NAND_MOVEDATA_CMD1 0X35
#define NAND_MOVEDATA_CMD2 0X85
#define NAND_MOVEDATA_CMD3 0X10

/* NAND FLASH 状态 */
#define NSTA_READY         0X40 /* nand 已经准备好 */
#define NSTA_ERROR         0X01 /* nand 错误 */
#define NSTA_TIMEOUT       0X02 /* 超时 */
#define NSTA_ECC1BITERR    0X03 /* ECC 1bit 错误 */
#define NSTA_ECC2BITERR    0X04 /* ECC 2bit 以上错误 */

/* NAND FLASH 型号和对应的 ID 号 */
#define MT29F4G08ABADA     0XDC909556 /* MT29F4G08ABADA */
#define MT29F16G08ABABA    0X48002689 /* MT29F16G08ABABA */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup NAND Flash 公开接口
 * @{
 */

uint8_t nand_init(void);
uint8_t nand_modeset(uint8_t mode);
uint32_t nand_readid(void);
uint8_t nand_readstatus(void);
uint8_t nand_wait_for_ready(void);
uint8_t nand_reset(void);
uint8_t nand_waitrb(volatile uint8_t rb);
void nand_delay(volatile uint32_t i);
uint8_t nand_readpage(uint32_t pagenum, uint16_t colnum, uint8_t *pbuffer,
                      uint16_t numbyte_to_read);
uint8_t nand_readpagecomp(uint32_t pagenum, uint16_t colnum, uint32_t cmpval,
                          uint16_t numbyte_to_read, uint16_t *numbyte_equal);
uint8_t nand_writepage(uint32_t pagenum, uint16_t colnum, uint8_t *pbuffer,
                       uint16_t numbyte_to_write);
uint8_t nand_write_pageconst(uint32_t pagenum, uint16_t colnum, uint32_t cval,
                             uint16_t numbyte_to_write);
uint8_t nand_copypage_withoutwrite(uint32_t source_pagenum,
                                   uint32_t dest_pagenum);
uint8_t nand_copypage_withwrite(uint32_t source_pagenum, uint32_t dest_pagenum,
                                uint16_t colnum, uint8_t *pbuffer,
                                uint16_t numbyte_to_write);
uint8_t nand_readspare(uint32_t pagenum, uint16_t colnum, uint8_t *pbuffer,
                       uint16_t numbyte_to_read);
uint8_t nand_writespare(uint32_t pagenum, uint16_t colnum, uint8_t *pbuffer,
                        uint16_t numbyte_to_write);
uint8_t nand_eraseblock(uint32_t blocknum);
void nand_erasechip(void);

uint16_t nand_ecc_get_oe(uint8_t oe, uint32_t eccval);
uint8_t nand_ecc_correction(uint8_t *data_buf, uint32_t eccrd, uint32_t ecccl);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NAND_H */