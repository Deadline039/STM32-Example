/**
 * @file        ftl.h
 * @author      正点原子团队 (ALIENTEK)
 * @version     1.0
 * @date        2022-4-20
 * @brief       NAND FLASH FTL 层算法代码
 * @copyright   2020-2032, 广州市星翼电子科技有限公司
 *
 *****************************************************************************
 * 每个块, 第一个 page 的 spare 区, 前四个字节的含义:
 *  byte[1]:    表示该块是否是坏块. 0xFF, 正常块; 其他值, 坏块.
 *  byte[2]:    表示该块是否被用过. 0xFF, 没有写过数据; 0xCC, 写过数据了.
 *  byte[3:4]:  表示该块所属的逻辑块编号.
 * 每个 page,spare 区 16 字节以后的字节含义:
 *  第 16 字节开始, 后续每 4 个字节用于存储一个大小为 NAND_ECC_SECTOR_SIZE
 *  的扇区 ECC 值, 用于 ECC 校验
 *
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2022-04-20   1.0         Alientek    第一次发布
 */

#ifndef __FTL_H
#define __FTL_H

#include <CSP_Config.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * 坏块搜索控制
 * 如果设置为 1, 将在 ftl_format 的时候, 搜寻坏块, 耗时久 (512M, 3 分钟以上),
 * 且会导致 RGB 屏乱闪
 */
#define FTL_USE_BAD_BLOCK_SEARCH 0 /* 定义是否使用坏块搜索 */

uint8_t ftl_init(void);
void ftl_badblock_mark(uint32_t blocknum);
uint8_t ftl_check_badblock(uint32_t blocknum);
uint8_t ftl_used_blockmark(uint32_t blocknum);
uint32_t ftl_find_unused_block(uint32_t sblock, uint8_t flag);
uint32_t ftl_find_same_plane_unused_block(uint32_t sblock);
uint8_t ftl_copy_and_write_to_block(uint32_t source_pagenum, uint16_t colnum,
                                    uint8_t *pbuffer,
                                    uint32_t numbyte_to_write);
uint16_t ftl_lbn_to_pbn(uint32_t lbnnum);
uint8_t ftl_write_sectors(uint8_t *pbuffer, uint32_t sectorno,
                          uint16_t sectorsize, uint32_t sectorcount);
uint8_t ftl_read_sectors(uint8_t *pbuffer, uint32_t sectorno,
                         uint16_t sectorsize, uint32_t sectorcount);
uint8_t ftl_create_lut(uint8_t mode);
uint8_t ftl_blockcompare(uint32_t blockx, uint32_t cmpval);
uint32_t ftl_search_badblock(void);
uint8_t ftl_format(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FTL_H */
