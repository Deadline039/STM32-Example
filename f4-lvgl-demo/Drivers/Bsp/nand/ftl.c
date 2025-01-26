/**
 * @file        ftl.c
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

#include "ftl.h"
#include "nand.h"

#include <string.h>

/**
 * @brief FTL 层初始化
 *
 * @return 是否初始化成功
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t ftl_init(void) {
    uint8_t temp;

    if (nand_init()) {
        return 1;
    }

    if (nand_dev.lut) {
        CSP_FREE(nand_dev.lut);
    }

    /* 给 LUT 表申请内存 */
    nand_dev.lut = CSP_MALLOC((nand_dev.block_totalnum) * 2);
    memset(nand_dev.lut, 0, nand_dev.block_totalnum * 2); /* 全部清零 */

    if (!nand_dev.lut) {
        return 1; /* 内存申请失败  */
    }

    temp = ftl_create_lut(1);

    if (temp) {
        NAND_DEBUG("Format nand flash...\r\n");
        temp = ftl_format(); /* 格式化 NAND */

        if (temp) {
            NAND_DEBUG("Format failed!\r\n");
            return 2;
        }
    } else {
        /* 创建 LUT 表成功 */
        NAND_DEBUG("Total block num: %d\r\n", nand_dev.block_totalnum);
        NAND_DEBUG("Good block num: %d\r\n", nand_dev.good_blocknum);
        NAND_DEBUG("Valid block num: %d\r\n", nand_dev.valid_blocknum);
    }

    return 0;
}

/**
 * @brief 标记某一个块为坏块
 *
 * @param block_num 块编号, 范围: `0 ~ (block_totalnum - 1)`
 */
void ftl_badblock_mark(uint32_t block_num) {
    /* 坏块标记 mark, 任意值都 OK, 只要不是 0xFF. 这里写前 4 个字节, 方便
     * ftl_find_unused_block 函数检查坏块. (不检查备份区, 以提高速度) */
    uint32_t temp = 0xAAAAAAAA;

    /* 在第一个 page 的 spare 区, 第一个字节做坏块标记 (前 4 个字节都写) */
    nand_writespare(block_num * nand_dev.block_pagenum, 0, (uint8_t *)&temp, 4);
    /* 在第二个 page 的 spare 区, 第一个字节做坏块标记 (备份用) */
    nand_writespare(block_num * nand_dev.block_pagenum + 1, 0, (uint8_t *)&temp,
                    4);
}

/**
 * @brief 检查某一块是否是坏块
 *
 * @param block_num 块编号, 范围: `0 ~ (block_totalnum - 1)`
 * @return 是否为好块
 * @retval - 0:   好块
 * @retval - 其他: 坏块
 */
uint8_t ftl_check_badblock(uint32_t block_num) {
    uint8_t flag = 0;

    /* 读取坏块标志 */
    nand_readspare(block_num * nand_dev.block_pagenum, 0, &flag, 1);

    if (flag == 0xFF) {
        /* 好块, 读取备份区坏块标记 */
        nand_readspare(block_num * nand_dev.block_pagenum + 1, 0, &flag, 1);

        if (flag == 0xFF) {
            return 0; /* 好块 */
        }

        else {
            return 1; /* 坏块 */
        }
    }

    return 2;
}

/**
 * @brief 标记某一个块已经使用
 *
 * @param block_num 块编号, 范围: `0 ~ (block_totalnum - 1)`
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t ftl_used_blockmark(uint32_t block_num) {
    uint8_t usedflag = 0xCC;
    uint8_t temp = 0;
    /* 写入块已经被使用标志 */
    temp = nand_writespare(block_num * nand_dev.block_pagenum, 1,
                           (uint8_t *)&usedflag, 1);

    return temp;
}

/**
 * @brief 从给定的块开始找到往前找到一个未被使用的块 (指定奇数 / 偶数)
 *
 * @param sblock 开始块, 范围: `0 ~ (block_totalnum - 1)`
 * @param odd 是否为奇数块
 *  @arg - 0: 偶数块
 *  @arg - 1: 奇数块
 * @retval - 0xFFFFFFFF: 失败
 * @retval - 其他值:      未使用块号
 */
uint32_t ftl_find_unused_block(uint32_t sblock, uint8_t odd) {
    uint32_t temp = 0;
    uint32_t block_num = 0;

    for (block_num = sblock + 1; block_num > 0; block_num--) {
        if (((block_num - 1) % 2) == odd) {
            /* 奇偶合格, 才检测 *
             * 读块是否被使用标记 */
            nand_readspare((block_num - 1) * nand_dev.block_pagenum, 0,
                           (uint8_t *)&temp, 4);
            if (temp == 0xFFFFFFFF) {
                return (block_num - 1); /* 找到一个空块, 返回块编号 */
            }
        }
    }

    return 0xFFFFFFFF; /* 未找到空余块 */
}

/**
 * @brief 查找与给定块在同一个 plane 内的未使用的块
 *
 * @param sblock 给定块, 范围: `0 ~ (block_totalnum - 1)`
 * @retval - 0xFFFFFFFF: 失败
 * @retval - 其他值:      未使用块号
 */
uint32_t ftl_find_same_plane_unused_block(uint32_t sblock) {
    static uint32_t curblock = 0xFFFFFFFF;
    uint32_t unused_block = 0;

    if (curblock > (nand_dev.block_totalnum - 1)) {
        /* 超出范围了, 强制从最后一个块开始 */
        curblock = nand_dev.block_totalnum - 1;
    }

    /* 从当前块, 开始, 向前查找空余块  */
    unused_block = ftl_find_unused_block(curblock, sblock % 2);

    if (unused_block == 0xFFFFFFFF && curblock < (nand_dev.block_totalnum - 1)) {
        /* 未找到, 且不是从最末尾开始找的 */
        curblock = nand_dev.block_totalnum - 1; /* 强制从最后一个块开始 */
        unused_block = ftl_find_unused_block(
            curblock, sblock % 2); /* 从最末尾开始, 重新找一遍 */
    }

    if (unused_block == 0xFFFFFFFF) {
        return 0xFFFFFFFF; /* 找不到空闲 block */
    }

    curblock =
        unused_block; /* 当前块号等于未使用块编号. 下次则从此处开始查找 */

    return unused_block; /* 返回找到的空闲 block */
}

/**
 * @brief 将一个块的数据拷贝到另一块, 并且可以写入数据
 * @param source_pagenum 要写入数据的页地址,
 *                       范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param colnum 要写入的列开始地址 (也就是页内地址),
 *               范围: `0 ~ (page_totalsize - 1)`
 * @param pbuffer 要写入的数据
 * @param numbyte_to_write 要写入的字节数, 该值不能超过块内剩余容量大小
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t ftl_copy_and_write_to_block(uint32_t source_pagenum, uint16_t colnum,
                                    uint8_t *pbuffer,
                                    uint32_t numbyte_to_write) {
    uint16_t i = 0, temp = 0, wrlen;
    uint32_t source_block = 0, pageoffset = 0;
    uint32_t unused_block = 0;
    /* 获得页所在的块号 */
    source_block = source_pagenum / nand_dev.block_pagenum;
    /* 获得页在所在块内的偏移 */
    pageoffset = source_pagenum % nand_dev.block_pagenum;

retry:
    /* 查找与源块在一个 plane 的未使用块 */
    unused_block = ftl_find_same_plane_unused_block(source_block);

    if (unused_block > nand_dev.block_totalnum) {
        return 1; /* 当找到的空余块号大于块总数量的话肯定是出错了 */
    }

    for (i = 0; i < nand_dev.block_pagenum; ++i) {
        /* 将一个块的数据复制到找到的未使用块中 */
        if (i >= pageoffset && numbyte_to_write) {
            /* 数据要写入到当前页 */
            if (numbyte_to_write > (nand_dev.page_mainsize - colnum)) {
                /* 要写入的数据, 超过了当前页的剩余数据 */
                wrlen = nand_dev.page_mainsize -
                        colnum; /* 写入长度等于当前页剩余数据长度 */
            } else {
                wrlen = numbyte_to_write; /* 写入全部数据 */
            }

            temp = nand_copypage_withwrite(
                source_block * nand_dev.block_pagenum + i,
                unused_block * nand_dev.block_pagenum + i, colnum, pbuffer,
                wrlen);
            colnum = 0;                /* 列地址归零 */
            pbuffer += wrlen;          /* 写地址偏移 */
            numbyte_to_write -= wrlen; /* 写入数据减少 */
        } else {
            /* 无数据写入, 直接拷贝即可 */
            temp = nand_copypage_withoutwrite(
                source_block * nand_dev.block_pagenum + i,
                unused_block * nand_dev.block_pagenum + i);
        }

        if (temp) {
            /* 返回值非零, 当坏块处理 */
            ftl_badblock_mark(unused_block); /* 标记为坏块 */
            ftl_create_lut(1);               /* 重建 LUT 表 */
            goto retry;
        }
    }

    if (i == nand_dev.block_pagenum) {
        /* 拷贝完成 */
        ftl_used_blockmark(unused_block); /* 标记块已经使用 */
        nand_eraseblock(source_block);    /* 擦除源块 */
        for (i = 0; i < nand_dev.block_totalnum; ++i) {
            /* 修正 LUT 表, 用 unused_block 替换 source_block */
            if (nand_dev.lut[i] == source_block) {
                nand_dev.lut[i] = unused_block;
                break;
            }
        }
    }

    return 0;
}

/**
 * @brief 逻辑块号转换为物理块号
 *
 * @param lbnnum 逻辑块编号
 * @return 物理块编号
 */
uint16_t ftl_lbn_to_pbn(uint32_t lbnnum) {
    uint16_t pbnno = 0;

    /* 当逻辑块号大于有效块数的时候返回 0xFFFF */
    if (lbnnum > nand_dev.valid_blocknum) {
        return 0xFFFF;
    }

    pbnno = nand_dev.lut[lbnnum];

    return pbnno;
}

/**
 * @brief 写扇区 (支持多扇区写), FATFS 文件系统使用
 * @param pbuffer 要写入的数据
 * @param sector_no 起始扇区号
 * @param sector_size 扇区大小
 *                    (不能大于`NAND_ECC_SECTOR_SIZE`定义的大小, 否则会出错)
 * @param sector_count : 要写入的扇区数量
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t ftl_write_sectors(uint8_t *pbuffer, uint32_t sector_no,
                          uint16_t sector_size, uint32_t sector_count) {
    uint8_t flag = 0;
    uint16_t temp;
    uint32_t i = 0;
    uint16_t wsecs;                 /* 写页大小 */
    uint32_t wlen;                  /* 写入长度 */
    uint32_t lbnno;                 /* 逻辑块号 */
    uint32_t pbnno;                 /* 物理块号 */
    uint32_t phypageno;             /* 物理页号 */
    uint32_t pageoffset;            /* 页内偏移地址 */
    uint32_t blockoffset;           /* 块内偏移地址 */
    uint32_t markdpbn = 0xFFFFFFFF; /* 标记了的物理块编号 */

    for (i = 0; i < sector_count; ++i) {
        /* 根据逻辑扇区号和扇区大小计算出逻辑块号 */
        lbnno = (sector_no + i) / (nand_dev.block_pagenum *
                                   (nand_dev.page_mainsize / sector_size));
        pbnno = ftl_lbn_to_pbn(lbnno); /* 将逻辑块转换为物理块 */

        if (pbnno >= nand_dev.block_totalnum) {
            return 1; /* 物理块号大于 NAND FLASH 的总块数, 则失败. */
        }

        /* 计算块内偏移 */
        blockoffset =
            ((sector_no + i) % (nand_dev.block_pagenum *
                                (nand_dev.page_mainsize / sector_size))) *
            sector_size;
        phypageno = pbnno * nand_dev.block_pagenum +
                    blockoffset / nand_dev.page_mainsize; /* 计算出物理页号 */
        /* 计算出页内偏移地址  */
        pageoffset = blockoffset % nand_dev.page_mainsize;
        temp = nand_dev.page_mainsize - pageoffset; /* page 内剩余字节数 */
        temp /= sector_size;      /* 可以连续写入的 sector 数  */
        wsecs = sector_count - i; /* 还剩多少个 sector 要写 */

        if (wsecs >= temp) {
            wsecs = temp; /* 大于可连续写入的 sector 数, 则写入 temp 个扇区 */
        }

        wlen = wsecs * sector_size; /* 每次写 wsecs 个 sector */

        /* 读出写入大小的内容判断是否全为 0xFF */
        flag = nand_readpagecomp(
            phypageno, pageoffset, 0xFFFFFFFF, wlen / 4,
            &temp); /* 读一个 wlen/4 大小个数据, 并与 0xFFFFFFFF 对比 */

        if (flag) {
            return 2; /* 读写错误, 坏块 */
        }
        if (temp == (wlen / 4)) {
            flag = nand_writepage(phypageno, pageoffset, pbuffer,
                                  wlen); /* 全为 0xFF, 可以直接写数据 */
        } else {
            flag = 1; /* 不全是 0xFF, 则另作处理 */
        }
        if (flag == 0 && (markdpbn != pbnno)) {
            /* 全是 0xFF, 且写入成功, 且标记了的物理块与当前物理块不同 */

            flag = ftl_used_blockmark(pbnno); /* 标记此块已经使用 */
            markdpbn = pbnno; /* 标记完成, 标记块 = 当前块, 防止重复标记 */
        }
        if (flag) {
            /* 不全为 0xFF / 标记失败, 将数据写到另一个块 */

            /* 计算整个 block 还剩下多少个 sector 可以写入 */
            temp = ((uint32_t)nand_dev.block_pagenum * nand_dev.page_mainsize -
                    blockoffset) /
                   sector_size;
            wsecs = sector_count - i; /* 还剩多少个 sector 要写 */

            if (wsecs >= temp) {
                /* 大于可连续写入的 sector 数, 则写入 temp 个扇区 */
                wsecs = temp;
            }

            wlen = wsecs * sector_size; /* 每次写 wsecs 个 sector */
            /* 拷贝到另外一个 block, 并写入数据 */
            flag = ftl_copy_and_write_to_block(phypageno, pageoffset, pbuffer,
                                               wlen);
            if (flag) {
                return 3; /* 失败 */
            }
        }

        i += wsecs - 1;
        pbuffer += wlen; /* 数据缓冲区指针偏移 */
    }

    return 0;
}

/**
 * @brief 读扇区 (支持多扇区读), FATFS 文件系统使用
 *
 * @param[out] pbuffer 数据缓存区
 * @param sector_no 起始扇区号
 * @param sector_size 扇区大小
 * @param sector_count 要写入的扇区数量
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t ftl_read_sectors(uint8_t *pbuffer, uint32_t sector_no,
                         uint16_t sector_size, uint32_t sector_count) {
    uint8_t flag = 0;
    uint16_t rsecs; /* 单次读取页数 */
    uint32_t i = 0;
    uint32_t lbnno;       /* 逻辑块号 */
    uint32_t pbnno;       /* 物理块号 */
    uint32_t phypageno;   /* 物理页号 */
    uint32_t pageoffset;  /* 页内偏移地址 */
    uint32_t blockoffset; /* 块内偏移地址 */

    for (i = 0; i < sector_count; ++i) {
        /* 根据逻辑扇区号和扇区大小计算出逻辑块号 */
        lbnno = (sector_no + i) / (nand_dev.block_pagenum *
                                   (nand_dev.page_mainsize / sector_size));
        pbnno = ftl_lbn_to_pbn(lbnno); /* 将逻辑块转换为物理块 */

        if (pbnno >= nand_dev.block_totalnum) {
            return 1; /* 物理块号大于 NAND FLASH 的总块数, 则失败. */
        }

        /* 计算块内偏移 */
        blockoffset =
            ((sector_no + i) % (nand_dev.block_pagenum *
                                (nand_dev.page_mainsize / sector_size))) *
            sector_size;
        /* 计算出物理页号 */
        phypageno = pbnno * nand_dev.block_pagenum +
                    blockoffset / nand_dev.page_mainsize;
        /* 计算出页内偏移地址 */
        pageoffset = blockoffset % nand_dev.page_mainsize;
        /* 计算一次最多可以读取多少页 */
        rsecs = (nand_dev.page_mainsize - pageoffset) / sector_size;

        if (rsecs > (sector_count - i)) {
            rsecs = sector_count - i; /* 最多不能超过 sector_count - i */
        }
        /* 读取数据 */
        flag =
            nand_readpage(phypageno, pageoffset, pbuffer, rsecs * sector_size);

        if (flag == NSTA_ECC1BITERR) {
            /* 对于 1bit ecc 错误, 可能为坏块 *
             * 重读数据, 再次确认 */
            flag = nand_readpage(phypageno, pageoffset, pbuffer,
                                 rsecs * sector_size);

            if (flag == NSTA_ECC1BITERR) {
                /* 搬运数据 */
                ftl_copy_and_write_to_block(phypageno, pageoffset, pbuffer,
                                            rsecs * sector_size);
                /* 全 1 检查, 确认是否为坏块 */
                flag = ftl_blockcompare(phypageno / nand_dev.block_pagenum,
                                        0xFFFFFFFF);

                if (flag == 0) {
                    /* 全 0 检查, 确认是否为坏块 */
                    flag = ftl_blockcompare(phypageno / nand_dev.block_pagenum,
                                            0x00);
                    /* 检测完成后, 擦除这个块 */
                    nand_eraseblock(phypageno / nand_dev.block_pagenum);
                }

                if (flag) {
                    /* 全 0 / 全 1 检查出错, 肯定是坏块了. */
                    ftl_badblock_mark(phypageno / nand_dev.block_pagenum);
                    ftl_create_lut(1); /* 重建 LUT 表 */
                }

                flag = 0;
            }
        }

        if (flag == NSTA_ECC2BITERR) {
            flag = 0; /* 2bit ecc 错误, 不处理 (可能是初次写入数据导致的) */
        }
        if (flag) {
            return 2; /* 失败 */
        }

        pbuffer += sector_size * rsecs; /* 数据缓冲区指针偏移 */
        i += rsecs - 1;
    }

    return 0;
}

/**
 * @brief 重新创建 LUT 表
 *
 * @param mode 是否检查备份区坏块
 *  @arg - 0: 仅检查第一个坏块标记
 *  @arg - 1: 两个坏块标记都要检查 (备份区也要检查)
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t ftl_create_lut(uint8_t mode) {
    uint32_t i;
    uint8_t buf[4];
    uint32_t lbnnum = 0; /* 逻辑块号 */

    for (i = 0; i < nand_dev.block_totalnum; ++i) {
        /* 复位 LUT 表, 初始化为无效值, 也就是 0xFFFF */
        nand_dev.lut[i] = 0xFFFF;
    }

    nand_dev.good_blocknum = 0;
    for (i = 0; i < nand_dev.block_totalnum; ++i) {
        /* 读取 4 个字节 */
        nand_readspare(i * nand_dev.block_pagenum, 0, buf, 4);

        if (buf[0] == 0xFF && mode) {
            /* 好块, 且需要检查 2 次坏块标记 */
            nand_readspare(i * nand_dev.block_pagenum + 1, 0, buf, 1);
        }

        if (buf[0] == 0xFF) {
            /* 是好块 */
            lbnnum = ((uint16_t)buf[3] << 8) + buf[2]; /* 得到逻辑块编号 */
            if (lbnnum < nand_dev.block_totalnum) {
                /* 逻辑块号肯定小于总的块数量 *
                 * 更新 LUT 表, 写 LBNnum 对应的物理块编号 */
                nand_dev.lut[lbnnum] = i;
            }
            nand_dev.good_blocknum++;
        } else {
            NAND_DEBUG("bad block index: %u\r\n", i);
        }
    }

    /* LUT 表建立完成以后检查有效块个数 */
    for (i = 0; i < nand_dev.block_totalnum; ++i) {
        if (nand_dev.lut[i] >= nand_dev.block_totalnum) {
            nand_dev.valid_blocknum = i;
            break;
        }
    }

    if (nand_dev.valid_blocknum < 100) {
        return 2; /* 有效块数小于 100, 有问题. 需要重新格式化 */
    }

    return 0; /* LUT 表创建完成 */
}

/**
 * @brief FTL 整个 Block 与某个数据对比
 * @param blockx block 编号
 * @param cmpval 要与之对比的值
 * @retval - 0: 检查成功, 全部相等
 * @retval - 1: 检查失败, 有不相等的情况
 */
uint8_t ftl_blockcompare(uint32_t blockx, uint32_t cmpval) {
    uint8_t res;
    uint16_t i, j, k;

    for (i = 0; i < 3; ++i) {
        /* 允许 3 次机会 */
        for (j = 0; j < nand_dev.block_pagenum; j++) {
            /* 检查一个 page, 并与 0xFFFFFFFF 对比 */
            nand_readpagecomp(blockx * nand_dev.block_pagenum, 0, cmpval,
                              nand_dev.page_mainsize / 4, &k);

            if (k != (nand_dev.page_mainsize / 4)) {
                break;
            }
        }

        if (j == nand_dev.block_pagenum) {
            return 0; /* 检查合格, 直接退出 */
        }

        res = nand_eraseblock(blockx);

        if (res) {
            NAND_DEBUG("error erase block: %d\r\n", i);
        } else {
            if (cmpval != 0xFFFFFFFF) {
                /* 不是判断全 1, 则需要重写数据 */
                for (k = 0; k < nand_dev.block_pagenum; k++) {
                    /* 写 PAGE */
                    nand_write_pageconst(blockx * nand_dev.block_pagenum + k, 0,
                                         0, nand_dev.page_mainsize / 4);
                }
            }
        }
    }

    NAND_DEBUG("bad block checked: %u\r\n", blockx);

    return 1;
}

/**
 * @brief FTL 初始化时, 搜寻所有坏块, 使用: 擦 - 写 - 读 方式
 *
 * @return 好块的数量
 * @note  512M 的 NAND , 需要约 3 分钟时间, 来完成检测
 *        对于 RGB 屏, 由于频繁读写 NAND, 会引起屏幕乱闪
 */
uint32_t ftl_search_badblock(void) {
    uint8_t *blktbl;
    uint8_t res;
    uint32_t i, j;
    uint32_t good_block = 0;

    /* 申请 block 坏块表内存, 对应项: 0, 好块; 1, 坏块; */
    blktbl = CSP_MALLOC(nand_dev.block_totalnum);

    nand_erasechip(); /* 全片擦除 */

    for (i = 0; i < nand_dev.block_totalnum; ++i) {
        /* 第一阶段检查, 检查全 1 */
        res = ftl_blockcompare(i, 0xFFFFFFFF); /* 全 1 检查 */

        if (res) {
            blktbl[i] = 1; /* 坏块  */
        } else {
            blktbl[i] = 0; /* 好块 */

            for (j = 0; j < nand_dev.block_pagenum; j++) {
                /* 写 block 为全 0, 为后面的检查准备 */
                nand_write_pageconst(i * nand_dev.block_pagenum + j, 0, 0,
                                     nand_dev.page_mainsize / 4);
            }
        }
    }

    for (i = 0; i < nand_dev.block_totalnum; ++i) {
        /* 第二阶段检查, 检查全 0 */
        if (blktbl[i] == 0) {
            /* 在第一阶段, 没有被标记坏块的, 才可能是好块 */
            res = ftl_blockcompare(i, 0); /* 全 0 检查 */

            if (res) {
                blktbl[i] = 1; /* 标记坏块 */
            } else {
                good_block++;
            }
        }
    }

    nand_erasechip(); /* 全片擦除 */

    for (i = 0; i < nand_dev.block_totalnum; ++i) {
        /* 第三阶段检查, 标记坏块 */
        if (blktbl[i]) {
            ftl_badblock_mark(i); /* 是坏块 */
        }
    }

    return good_block; /* 返回好块的数量 */
}

/**
 * @brief 格式化 NAND 重建 LUT 表
 *
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t ftl_format(void) {
    uint8_t temp;
    uint32_t i, n;
    uint32_t good_block = 0;
    nand_dev.good_blocknum = 0;

#if FTL_USE_BAD_BLOCK_SEARCH == 1 /* 使用擦 - 写 - 读的方式, 检测坏块 */
    nand_dev.good_blocknum = ftl_search_badblock(); /* 搜寻坏块. 耗时很久 */
#else /* 直接使用 NAND FLASH 的出厂坏块标志 (其他块, 默认是好块) */

    for (i = 0; i < nand_dev.block_totalnum; ++i) {
        temp = ftl_check_badblock(i); /* 检查一个块是否为坏块 */

        if (temp == 0) {
            /* 好块 */
            temp = nand_eraseblock(i);

            if (temp) {
                /* 擦除失败, 认为坏块 */
                NAND_DEBUG("Bad block: %u\r\n", i);
                ftl_badblock_mark(i); /* 标记是坏块 */
            } else {
                nand_dev.good_blocknum++; /* 好块数量加一 */
            }
        }
    }
#endif /* FLT_USE_BAD_BLOCK_SEARCH */

    NAND_DEBUG("good_blocknum: %u\r\n", nand_dev.good_blocknum);

    if (nand_dev.good_blocknum < 100) {
        return 1; /* 如果好块的数量少于 100, 则 NAND Flash 报废 */
    }

    /* 93% 的好块用于存储数据 */
    good_block = (nand_dev.good_blocknum * 93) / 100;

    n = 0;

    for (i = 0; i < nand_dev.block_totalnum; ++i) {
        /* 在好块中标记上逻辑块信息 */
        temp = ftl_check_badblock(i); /* 检查一个块是否为坏块 */

        if (temp == 0) {
            /* 好块, 写入逻辑块编号 */
            nand_writespare(i * nand_dev.block_pagenum, 2, (uint8_t *)&n, 2);

            n++; /* 逻辑块编号加 1 */

            if (n == good_block) {
                break; /* 全部标记完了 */
            }
        }
    }
    if (ftl_create_lut(1)) {
        return 2; /* 重建 LUT 表失败 */
    }

    return 0;
}
