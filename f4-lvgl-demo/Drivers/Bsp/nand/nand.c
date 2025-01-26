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

#include "nand.h"

#include "../core/core_delay.h"

/* NAND FLASH 句柄 */
NAND_HandleTypeDef g_nand_handle;
/* nand 重要参数结构体 */
nand_dev_t nand_dev;

/**
 * @brief 初始化 NAND FLASH
 *
 */
uint8_t nand_init(void) {
    FMC_NAND_PCC_TimingTypeDef comspacetiming, attspacetiming;

    g_nand_handle.Instance = FMC_NAND_DEVICE;
    /* NAND 挂在 BANK3 上 */
    g_nand_handle.Init.NandBank = FMC_NAND_BANK3;
    g_nand_handle.Init.Waitfeature = FMC_NAND_PCC_WAIT_FEATURE_DISABLE;
    g_nand_handle.Init.MemoryDataWidth = FMC_NAND_PCC_MEM_BUS_WIDTH_8;
    g_nand_handle.Init.EccComputation = FMC_NAND_ECC_DISABLE;
    g_nand_handle.Init.ECCPageSize = FMC_NAND_ECC_PAGE_SIZE_2048BYTE;
    g_nand_handle.Init.TCLRSetupTime = 0;
    g_nand_handle.Init.TARSetupTime = 1;

    comspacetiming.SetupTime = 2;
    comspacetiming.WaitSetupTime = 3;
    comspacetiming.HoldSetupTime = 2;
    comspacetiming.HiZSetupTime = 1;

    attspacetiming.SetupTime = 2;
    attspacetiming.WaitSetupTime = 3;
    attspacetiming.HoldSetupTime = 2;
    attspacetiming.HiZSetupTime = 1;

    HAL_NAND_Init(&g_nand_handle, &comspacetiming, &attspacetiming);
    nand_reset();
    delay_ms(100);
    nand_dev.id = nand_readid();
    /* 设置为 MODE4, 高速模式 */
    nand_modeset(4);

    if (nand_dev.id == MT29F16G08ABABA) {
        nand_dev.page_totalsize = 4320;
        nand_dev.page_mainsize = 4096;
        nand_dev.page_sparesize = 224;
        nand_dev.block_pagenum = 128;
        nand_dev.plane_blocknum = 2048;
        nand_dev.block_totalnum = 4096;
    } else if (nand_dev.id == MT29F4G08ABADA) {
        nand_dev.page_totalsize = 2112;
        nand_dev.page_mainsize = 2048;
        nand_dev.page_sparesize = 64;
        nand_dev.block_pagenum = 64;
        nand_dev.plane_blocknum = 2048;
        nand_dev.block_totalnum = 4096;
    } else {
        return 1;
    }

    return 0;
}

/**
 * @brief NAND FALSH 底层驱动, 引脚配置, 时钟使能
 *
 * @param hnand nand 句柄
 */
void HAL_NAND_MspInit(NAND_HandleTypeDef *hnand) {
    UNUSED(hnand);

    GPIO_InitTypeDef gpio_init_struct;

    __HAL_RCC_FMC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    CSP_GPIO_CLK_ENABLE(NAND_RB_GPIO_PORT);

    gpio_init_struct.Pin = NAND_RB_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(CSP_GPIO_PORT(NAND_RB_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = GPIO_PIN_9;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_NOPULL;
    gpio_init_struct.Speed = GPIO_SPEED_HIGH;
    gpio_init_struct.Alternate = GPIO_AF12_FMC;

    HAL_GPIO_Init(GPIOG, &gpio_init_struct);

    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
                           GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14 |
                           GPIO_PIN_15;
    gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &gpio_init_struct);

    gpio_init_struct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    HAL_GPIO_Init(GPIOE, &gpio_init_struct);
}

/**
 * @brief 设置 NAND 速度模式
 *
 * @param mode 0 ~ 5, 表示速度模式
 */
uint8_t nand_modeset(uint8_t mode) {
    /* 发送设置特性命令 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_FEATURE;
    /* 地址为 0x01, 设置 mode */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = 0x01;
    /* P1 参数, 设置 mode */
    *(volatile uint8_t *)NAND_ADDRESS = mode;
    *(volatile uint8_t *)NAND_ADDRESS = 0;
    *(volatile uint8_t *)NAND_ADDRESS = 0;
    *(volatile uint8_t *)NAND_ADDRESS = 0;

    if (nand_wait_for_ready() == NSTA_READY) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief 读取 NAND FLASH 的 ID
 *
 * @retval NAND FLASH 的 ID 值
 * @note 不同的 NAND 略有不同, 请根据自己所使用的 NAND FALSH 数据手册来编写函数
 */
uint32_t nand_readid(void) {
    uint8_t deviceid[5];
    uint32_t id;
    /* 发送读取 ID 命令 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = nand_readID;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = 0x00;

    /* ID 一共有 5 个字节 */
    deviceid[0] = *(volatile uint8_t *)NAND_ADDRESS;
    deviceid[1] = *(volatile uint8_t *)NAND_ADDRESS;
    deviceid[2] = *(volatile uint8_t *)NAND_ADDRESS;
    deviceid[3] = *(volatile uint8_t *)NAND_ADDRESS;
    deviceid[4] = *(volatile uint8_t *)NAND_ADDRESS;

    /* 镁光的 NAND FLASH 的 ID 一共 5 个字节, 但是为了方便我们只取 4
       个字节组成一个 32 位的 ID 值 根据 NAND FLASH 的数据手册, 只要是镁光的
       NAND FLASH, 那么一个字节 ID 的第一个字节都是 0x2C 所以我们就可以抛弃这个
       0x2C, 只取后面四字节的 ID 值。*/
    id = ((uint32_t)deviceid[1]) << 24 | ((uint32_t)deviceid[2]) << 16 |
         ((uint32_t)deviceid[3]) << 8 | deviceid[4];

    return id;
}

/**
 * @brief 读 NAND 状态
 *
 * @return NAND 状态值
 * @retval - bit[0]:    0: 成功; 1: 错误 (编程/擦除/READ)
 * @retval - bit[6]:    0: Busy; 1: Ready
 */
uint8_t nand_readstatus(void) {
    volatile uint8_t data = 0;

    /* 发送读状态命令 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_READSTA;
    /* 等待 tWHR, 再读取状态寄存器 */
    nand_delay(NAND_TWHR_DELAY);
    /* 读取状态值 */
    data = *(volatile uint8_t *)NAND_ADDRESS;

    return data;
}

/**
 * @brief 等待 NAND 准备好
 *
 * @retval - `NSTA_TIMEOUT`: 等待超时了
 * @retval - `NSTA_READY`:   已经准备好
 */
uint8_t nand_wait_for_ready(void) {
    uint8_t status = 0;
    volatile uint32_t time = 0;

    while (1) {
        /* 等待 ready */
        status = nand_readstatus();

        if (status & NSTA_READY) {
            break;
        }

        time++;

        if (time >= 0x1FFFFFFF) {
            return NSTA_TIMEOUT;
        }
    }

    return NSTA_READY;
}

/**
 * @brief 复位 NAND
 *
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t nand_reset(void) {
    /* 复位 NAND */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_RESET;

    if (nand_wait_for_ready() == NSTA_READY) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief 等待 RB 信号为某个电平
 *
 * @param rb 等待 RB 为 0 或 1
 * @retval - 0: 成功
 * @retval - 1: 超时
 */
uint8_t nand_waitrb(volatile uint8_t rb) {
    volatile uint32_t time = 0;

    while (time < 0x1FFFFFF) {
        time++;

        if (NAND_RB == rb) {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief NAND 延时
 *
 * @param i 等待的时间
 * @note  一个 i++ 至少需要 4ns
 */
void nand_delay(volatile uint32_t i) {
    while (i > 0) {
        i--;
    }
}

/**
 * @brief 读取 NAND Flash 的指定页指定列的数据 (main 区和 spare
 * 区都可以使用此函数)
 *
 * @param pagenum 要读取的页地址,
 *                范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param colnum 要读取的列开始地址 (也就是页内地址),
 *               范围: `0 ~ (page_totalsize-1)`
 * @param[out] pbuffer 指向数据存储区
 * @param numbyte_to_read 读取字节数 (不能跨页读)
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t nand_readpage(uint32_t pagenum, uint16_t colnum, uint8_t *pbuffer,
                      uint16_t numbyte_to_read) {
    volatile uint16_t i = 0;
    uint8_t res = 0;
    /* 需要计算的 ECC 个数, 每 NAND_ECC_SECTOR_SIZE 字节计算一个 ecc */
    uint8_t eccnum = 0;
    /* 第一个 ECC 值所属的地址范围 */
    uint8_t eccstart = 0;
    uint8_t errsta = 0;
    uint8_t *p;

    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_AREA_A;
    /* 发送地址 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)colnum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(colnum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)pagenum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(pagenum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(pagenum >> 16);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_AREA_TRUE1;

    /* 下面两行代码是等待 R/B 引脚变为低电平, 其实主要起延时作用的, 等待 NAND
       操作 R/B 引脚。因为我们是通过 将 STM32 的 NWAIT 引脚 (NAND 的 R/B 引脚)
       配置为普通 IO, 代码中通过读取 NWAIT 引脚的电平来判断 NAND 是否准备
       就绪的。这个也就是模拟的方法, 所以在速度很快的时候有可能 NAND
       还没来得及操作 R/B 引脚来表示 NAND 的忙 闲状态, 结果我们就读取了 R/B
       引脚, 这个时候肯定会出错的, 事实上确实是会出错! 大家也可以将下面两行
       代码换成延时函数, 只不过这里我们为了效率所以没有用延时函数。 */
    res = nand_waitrb(0);

    if (res) {
        return NSTA_TIMEOUT;
    }

    /* 下面 2 行代码是真正判断 NAND 是否准备好的 */
    res = nand_waitrb(1);

    if (res) {
        return NSTA_TIMEOUT;
    }

    if (numbyte_to_read % NAND_ECC_SECTOR_SIZE) {
        /* 不是 NAND_ECC_SECTOR_SIZE 的整数倍, 不进行 ECC 校验 */

        /* 读取 NAND FLASH 中的值 */
        for (i = 0; i < numbyte_to_read; i++) {
            *(volatile uint8_t *)pbuffer++ = *(volatile uint8_t *)NAND_ADDRESS;
        }
    } else {
        /* 得到 ecc 计算次数 */
        eccnum = numbyte_to_read / NAND_ECC_SECTOR_SIZE;
        eccstart = colnum / NAND_ECC_SECTOR_SIZE;
        p = pbuffer;

        for (res = 0; res < eccnum; res++) {
            /* 使能 ECC 校验 */
            FMC_Bank2_3->PCR3 |= 1U << 6;

            for (i = 0; i < NAND_ECC_SECTOR_SIZE; i++) {
                /* 读取 NAND_ECC_SECTOR_SIZE 个数据 */
                *(volatile uint8_t *)pbuffer++ =
                    *(volatile uint8_t *)NAND_ADDRESS;
            }

            /* 等待 FIFO 空 */
            while (!(FMC_Bank2_3->SR3 & (1U << 6)))
                ;

            /* 读取硬件计算后的 ECC 值 */
            nand_dev.ecc_hdbuf[res + eccstart] = FMC_Bank2_3->ECCR3;
            /* 禁止 ECC 校验 */
            FMC_Bank2_3->PCR3 &= ~(1U << 6);
        }

        /* 从 spare 区的 0x10 位置开始读取之前存储的 ecc 值 */
        i = nand_dev.page_mainsize + 0x10 + eccstart * 4;
        /* 等待 tRHW */
        nand_delay(NAND_TRHW_DELAY);
        /* 随机读指令 */
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = 0x05;
        /* 发送地址 */
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)i;
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(i >> 8);
        /* 开始读数据 */
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = 0xE0;

        /* 等待 tWHR */
        nand_delay(NAND_TWHR_DELAY);
        pbuffer = (uint8_t *)&nand_dev.ecc_rdbuf[eccstart];

        /* 读取保存的 ECC 值 */
        for (i = 0; i < 4 * eccnum; i++) {
            *(volatile uint8_t *)pbuffer++ = *(volatile uint8_t *)NAND_ADDRESS;
        }

        /* 检验 ECC */
        for (i = 0; i < eccnum; i++) {
            /* 不相等, 需要校正 */
            if (nand_dev.ecc_rdbuf[i + eccstart] !=
                nand_dev.ecc_hdbuf[i + eccstart]) {
                NAND_DEBUG("err hd,rd: 0x%x,0x%x\r\n",
                           nand_dev.ecc_hdbuf[i + eccstart],
                           nand_dev.ecc_rdbuf[i + eccstart]);
                NAND_DEBUG("eccnum,eccstart: %u, %u\r\n", eccnum, eccstart);
                NAND_DEBUG("PageNum,ColNum: %u, %u\r\n", pagenum, colnum);
                res = nand_ecc_correction(
                    p + NAND_ECC_SECTOR_SIZE * i,
                    nand_dev.ecc_rdbuf[i + eccstart],
                    nand_dev.ecc_hdbuf[i + eccstart]); /* ECC 校验 */

                if (res) {
                    /* 标记 2BIT 及以上 ECC 错误 */
                    errsta = NSTA_ECC2BITERR;
                } else {
                    /* 标记 1BIT ECC 错误 */
                    errsta = NSTA_ECC1BITERR;
                }
            }
        }
    }

    if (nand_wait_for_ready() != NSTA_READY) {
        errsta = NSTA_ERROR;
    }

    return errsta;
}

/**
 * @brief 读取 NAND Flash 的指定页指定列的数据 (main 区和 spare
 * 区都可以使用此函数), 并对比 (FTL 管理时需要)
 *
 * @param pagenum 要读取的页地址,
 *                范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param colnum 要读取的列开始地址 (也就是页内地址),
 *               范围: `0 ~ (page_totalsize-1)`
 * @param cmpval 要对比的值, 以 uint32_t 为单位
 * @param numbyte_to_read 读取字数 (以 4 字节为单位, 不能跨页读)
 * @param numbyte_equal 从初始位置持续与 cmpval 值相同的数据个数
 * @retval - 0:   成功
 * @retval - 其他: 失败
 *
 */
uint8_t nand_readpagecomp(uint32_t pagenum, uint16_t colnum, uint32_t cmpval,
                          uint16_t numbyte_to_read, uint16_t *numbyte_equal) {
    uint16_t i = 0;
    uint8_t res = 0;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_AREA_A;
    /* 发送地址 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)colnum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(colnum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)pagenum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(pagenum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(pagenum >> 16);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_AREA_TRUE1;

    /**
     * 下面两行代码是等待 R/B 引脚变为低电平, 其实主要起延时作用的, 等待 NAND
     * 操作 R/B 引脚。因为我们是通过 将 STM32 的 NWAIT 引脚 (NAND 的 R/B 引脚)
     * 配置为普通 IO, 代码中通过读取 NWAIT 引脚的电平来判断 NAND 是否准备
     * 就绪的。这个也就是模拟的方法, 所以在速度很快的时候有可能 NAND
     * 还没来得及操作 R/B 引脚来表示 NAND 的忙 闲状态, 结果我们就读取了 R/B
     * 引脚, 这个时候肯定会出错的, 事实上确实是会出错! 大家也可以将下面两行
     * 代码换成延时函数, 只不过这里我们为了效率所以没有用延时函数。
     */
    res = nand_waitrb(0);

    if (res) {
        return NSTA_TIMEOUT;
    }

    /* 下面 2 行代码是真正判断 NAND 是否准备好的 */
    res = nand_waitrb(1);

    if (res) {
        return NSTA_TIMEOUT;
    }

    for (i = 0; i < numbyte_to_read; i++) {
        /* 如果有任何一个值, 与 cmpval 不相等, 则退出. */
        if (*(volatile uint32_t *)NAND_ADDRESS != cmpval) {
            break;
        }
    }

    *numbyte_equal = i;

    if (nand_wait_for_ready() != NSTA_READY) {
        return NSTA_ERROR;
    }

    return 0;
}

/**
 * @brief 在 NAND 一页中写入指定个字节的数据 (main 区和 spare
 * 区都可以使用此函数)
 *
 * @param pagenum 要读取的页地址,
 *                范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param colnum 要读取的列开始地址 (也就是页内地址),
 *               范围: `0 ~ (page_totalsize-1)`
 * @param pbuffer 指向数据存储区
 * @param numbyte_to_write 要写入的字节数, 该值不能超过该页剩余字节数!!!
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t nand_writepage(uint32_t pagenum, uint16_t colnum, uint8_t *pbuffer,
                       uint16_t numbyte_to_write) {
    volatile uint16_t i = 0;
    uint8_t res = 0;
    /* 需要计算的 ECC 个数, 每 NAND_ECC_SECTOR_SIZE 字节计算一个 ecc */
    uint8_t eccnum = 0;
    /* 第一个 ECC 值所属的地址范围 */
    uint8_t eccstart = 0;

    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_WRITE0;
    /* 发送地址 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)colnum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(colnum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)pagenum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(pagenum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(pagenum >> 16);
    nand_delay(NAND_TADL_DELAY);

    if (numbyte_to_write % NAND_ECC_SECTOR_SIZE) {
        /* 不是 NAND_ECC_SECTOR_SIZE 的整数倍, 不进行 ECC 校验 */
        for (i = 0; i < numbyte_to_write; i++) {
            /* 写入数据 */
            *(volatile uint8_t *)NAND_ADDRESS = *(volatile uint8_t *)pbuffer++;
        }
    } else {
        /* 得到 ecc 计算次数 */
        eccnum = numbyte_to_write / NAND_ECC_SECTOR_SIZE;
        eccstart = colnum / NAND_ECC_SECTOR_SIZE;

        for (res = 0; res < eccnum; res++) {
            /* 使能 ECC 校验 */
            FMC_Bank2_3->PCR3 |= 1U << 6;

            /* 写入 NAND_ECC_SECTOR_SIZE 个数据 */
            for (i = 0; i < NAND_ECC_SECTOR_SIZE; i++) {
                *(volatile uint8_t *)NAND_ADDRESS =
                    *(volatile uint8_t *)pbuffer++;
            }
            /* 等待 FIFO 空 */
            while (!(FMC_Bank2_3->SR3 & (1U << 6)))
                ;

            /* 读取硬件计算后的 ECC 值 */
            nand_dev.ecc_hdbuf[res + eccstart] = FMC_Bank2_3->ECCR3;

            /* 禁止 ECC 校验 */
            FMC_Bank2_3->PCR3 &= ~(1U << 6);
        }

        /* 计算写入 ECC 的 spare 区地址 */
        i = nand_dev.page_mainsize + 0x10 + eccstart * 4;
        /* 等待 tADL */
        nand_delay(NAND_TADL_DELAY);
        /* 随机写指令 */
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = 0x85;

        /* 发送地址 */
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)i;
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(i >> 8);
        /* 等待 tADL */
        nand_delay(NAND_TADL_DELAY);
        pbuffer = (uint8_t *)&nand_dev.ecc_hdbuf[eccstart];

        /* 写入 ECC */
        for (i = 0; i < eccnum; i++) {
            for (res = 0; res < 4; res++) {
                *(volatile uint8_t *)NAND_ADDRESS =
                    *(volatile uint8_t *)pbuffer++;
            }
        }
    }
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_WRITE_TURE1;
    /* 等待 tPROG */
    delay_us(NAND_TPROG_DELAY);

    if (nand_wait_for_ready() != NSTA_READY) {
        return NSTA_ERROR;
    }

    return 0;
}

/**
 * @brief 在 NAND 一页中的指定地址开始, 写入指定长度的恒定数字
 *
 * @param pagenum 要读取的页地址,
 *                范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param colnum 要读取的列开始地址 (也就是页内地址),
 *               范围: `0 ~ (page_totalsize-1)`
 * @param cval 要写入的指定常数
 * @param numbyte_to_write 要写入的字节数 (以 4 字节为单位)
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t nand_write_pageconst(uint32_t pagenum, uint16_t colnum, uint32_t cval,
                             uint16_t numbyte_to_write) {
    uint16_t i = 0;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_WRITE0;
    /* 发送地址 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)colnum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(colnum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)pagenum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(pagenum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(pagenum >> 16);

    nand_delay(NAND_TADL_DELAY);

    for (i = 0; i < numbyte_to_write; i++) {
        /* 写入数据, 每次写 4 字节 */
        *(volatile uint32_t *)NAND_ADDRESS = cval;
    }

    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_WRITE_TURE1;
    /* 等待 tPROG */
    delay_us(NAND_TPROG_DELAY);

    if (nand_wait_for_ready() != NSTA_READY) {
        return NSTA_ERROR;
    }

    return 0;
}

/**
 * @brief 将一页数据拷贝到另一页, 不写入新数据
 *
 * @param source_pagenum 源页地址,
 *                       范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param dest_pagenum 目的页地址
 *                     范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @retval - 0:   成功
 * @retval - 其他: 失败
 * @note 源页和目的页要在同一个 Plane 内!
 */
uint8_t nand_copypage_withoutwrite(uint32_t source_pagenum,
                                   uint32_t dest_pagenum) {
    uint8_t res = 0;
    uint16_t source_block = 0, dest_block = 0;
    /* 判断源页和目的页是否在同一个 plane 中 */
    source_block = source_pagenum / nand_dev.block_pagenum;
    dest_block = dest_pagenum / nand_dev.block_pagenum;

    if ((source_block % 2) != (dest_block % 2)) {
        /* 不在同一个 plane 内 */
        return NSTA_ERROR;
    }

    /* 发送命令 0x00 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_MOVEDATA_CMD0;
    /* 发送源页地址 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)0;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)0;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)source_pagenum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) =
        (uint8_t)(source_pagenum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) =
        (uint8_t)(source_pagenum >> 16);
    /* 发送命令 0x35 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_MOVEDATA_CMD1;
    /**
     *   下面两行代码是等待 R/B 引脚变为低电平, 其实主要起延时作用的, 等待 NAND
     * 操作 R/B 引脚。因为我们是通过 将 STM32 的 NWAIT 引脚 (NAND 的 R/B 引脚)
     * 配置为普通 IO, 代码中通过读取 NWAIT 引脚的电平来判断 NAND 是否准备
     *   就绪的。这个也就是模拟的方法, 所以在速度很快的时候有可能 NAND
     * 还没来得及操作 R/B 引脚来表示 NAND 的忙 闲状态, 结果我们就读取了 R/B
     * 引脚, 这个时候肯定会出错的, 事实上确实是会出错! 大家也可以将下面两行
     *   代码换成延时函数, 只不过这里我们为了效率所以没有用延时函数。
     */
    res = nand_waitrb(0);

    if (res) {
        return NSTA_TIMEOUT;
    }
    /* 下面 2 行代码是真正判断 NAND 是否准备好的 */
    res = nand_waitrb(1);

    if (res) {
        return NSTA_TIMEOUT;
    }

    /* 发送命令 0x85 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_MOVEDATA_CMD2;
    /* 发送目的页地址 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)0;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)0;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)dest_pagenum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) =
        (uint8_t)(dest_pagenum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) =
        (uint8_t)(dest_pagenum >> 16);
    /* 发送命令 0x10 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_MOVEDATA_CMD3;
    delay_us(NAND_TPROG_DELAY);

    if (nand_wait_for_ready() != NSTA_READY) {
        return NSTA_ERROR;
    }

    return 0;
}

/**
 * @brief 将一页数据拷贝到另一页, 并且可以写入数据
 *
 * @param source_pagenum 源页地址,
 *                       范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param dest_pagenum 目的页地址
 *                     范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param colnum 要读取的列开始地址 (也就是页内地址),
 *               范围: `0 ~ (page_totalsize - 1)`
 * @param pbuffer 要写入的数据
 * @param numbyte_to_write 要写入的数据个数
 * @retval - 0:   成功
 * @retval - 其他: 失败
 * @note 源页和目的页要在同一个 Plane 内!
 */
uint8_t nand_copypage_withwrite(uint32_t source_pagenum, uint32_t dest_pagenum,
                                uint16_t colnum, uint8_t *pbuffer,
                                uint16_t numbyte_to_write) {
    uint8_t res = 0;
    volatile uint16_t i = 0;
    uint16_t source_block = 0, dest_block = 0;
    /* 需要计算的 ECC 个数, 每 NAND_ECC_SECTOR_SIZE 字节计算一个 ecc */
    uint8_t eccnum = 0;
    /* 第一个 ECC 值所属的地址范围 */
    uint8_t eccstart = 0;
    /* 判断源页和目的页是否在同一个 plane 中 */
    source_block = source_pagenum / nand_dev.block_pagenum;
    dest_block = dest_pagenum / nand_dev.block_pagenum;

    if ((source_block % 2) != (dest_block % 2)) {
        /* 不在同一个 plane 内 */
        return NSTA_ERROR;
    }

    /* 发送命令 0x00 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_MOVEDATA_CMD0;
    /* 发送源页地址 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)0;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)0;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)source_pagenum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) =
        (uint8_t)(source_pagenum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) =
        (uint8_t)(source_pagenum >> 16);
    /* 发送命令 0x35 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_MOVEDATA_CMD1;

    /**
     * 下面两行代码是等待 R/B 引脚变为低电平, 其实主要起延时作用的, 等待 NAND
     * 操作 R/B 引脚。因为我们是通过 将 STM32 的 NWAIT 引脚 (NAND 的 R/B 引脚)
     * 配置为普通 IO, 代码中通过读取 NWAIT 引脚的电平来判断 NAND 是否准备
     * 就绪的。这个也就是模拟的方法, 所以在速度很快的时候有可能 NAND
     * 还没来得及操作 R/B 引脚来表示 NAND 的忙 闲状态, 结果我们就读取了 R/B
     * 引脚, 这个时候肯定会出错的, 事实上确实是会出错! 大家也可以将下面两行
     * 代码换成延时函数, 只不过这里我们为了效率所以没有用延时函数。
     */
    res = nand_waitrb(0);

    if (res) {
        return NSTA_TIMEOUT;
    }

    /* 下面 2 行代码是真正判断 NAND 是否准备好的 */
    res = nand_waitrb(1);

    if (res) {
        return NSTA_TIMEOUT;
    }
    /* 发送命令 0x85 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_MOVEDATA_CMD2;
    /* 发送目的页地址 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)colnum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(colnum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)dest_pagenum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) =
        (uint8_t)(dest_pagenum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) =
        (uint8_t)(dest_pagenum >> 16);
    /* 发送页内列地址 */
    nand_delay(NAND_TADL_DELAY);

    /* 不是 NAND_ECC_SECTOR_SIZE 的整数倍, 不进行 ECC 校验 */
    if (numbyte_to_write % NAND_ECC_SECTOR_SIZE) {
        for (i = 0; i < numbyte_to_write; i++) {
            /* 写入数据 */
            *(volatile uint8_t *)NAND_ADDRESS = *(volatile uint8_t *)pbuffer++;
        }
    } else {
        /* 得到 ecc 计算次数 */
        eccnum = numbyte_to_write / NAND_ECC_SECTOR_SIZE;
        eccstart = colnum / NAND_ECC_SECTOR_SIZE;

        for (res = 0; res < eccnum; res++) {
            /* 使能 ECC 校验 */
            FMC_Bank2_3->PCR3 |= 1U << 6;

            /* 写入 NAND_ECC_SECTOR_SIZE 个数据 */
            for (i = 0; i < NAND_ECC_SECTOR_SIZE; i++) {
                *(volatile uint8_t *)NAND_ADDRESS =
                    *(volatile uint8_t *)pbuffer++;
            }

            /* 等待 FIFO 空 */
            while (!(FMC_Bank2_3->SR3 & (1 << 6)))
                ;

            /* 读取硬件计算后的 ECC 值 */
            nand_dev.ecc_hdbuf[res + eccstart] = FMC_Bank2_3->ECCR3;

            /* 禁止 ECC 校验 */
            FMC_Bank2_3->PCR3 &= ~(1U << 6);
        }

        /* 计算写入 ECC 的 spare 区地址 */
        i = nand_dev.page_mainsize + 0x10 + eccstart * 4;
        nand_delay(NAND_TADL_DELAY);
        /* 随机写指令 */
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = 0x85;
        /* 发送地址 */
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)i;
        *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(i >> 8);
        nand_delay(NAND_TADL_DELAY);

        /* 写入 ECC */
        pbuffer = (uint8_t *)&nand_dev.ecc_hdbuf[eccstart];

        for (i = 0; i < eccnum; i++) {
            for (res = 0; res < 4; res++) {
                *(volatile uint8_t *)NAND_ADDRESS =
                    *(volatile uint8_t *)pbuffer++;
            }
        }
    }

    /* 发送命令 0x10 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_MOVEDATA_CMD3;
    delay_us(NAND_TPROG_DELAY);

    if (nand_wait_for_ready() != NSTA_READY) {
        return NSTA_ERROR;
    }

    return 0;
}

/**
 * @brief 读取 spare 区中的数据
 *
 * @param pagenum 要写入的页地址,
 *                范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param colnum 要写入的 spare 区地址 (`spare`区中哪个地址),
 *               范围: `0 ~ (page_sparesize - 1)`
 * @param pbuffer 接收数据缓冲区
 * @param numbyte_to_read 要读取的字节数 (不大于`page_sparesize`)
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t nand_readspare(uint32_t pagenum, uint16_t colnum, uint8_t *pbuffer,
                       uint16_t numbyte_to_read) {
    uint8_t temp = 0;
    uint8_t remainbyte = 0;
    remainbyte = nand_dev.page_sparesize - colnum;

    if (numbyte_to_read > remainbyte) {
        /* 确保要写入的字节数不大于 spare 剩余的大小 */
        numbyte_to_read = remainbyte;
    }

    temp = nand_readpage(pagenum, colnum + nand_dev.page_mainsize, pbuffer,
                         numbyte_to_read);
    return temp;
}

/**
 * @brief 向 spare 区中写数据
 *
 * @param pagenum 要写入的页地址
 *                范围: `0 ~ (block_pagenum * block_totalnum - 1)`
 * @param colnum 要写入的 spare 区地址 (`spare`区中哪个地址),
 *               范围: `0 ~ (page_sparesize - 1)`
 * @param pbuffer 要写入的数据首地址
 * @param numbyte_to_read 要读取的字节数 (不大于`page_sparesize`)
 * @retval - 0:   成功
 * @retval - 其他: 失败
 */
uint8_t nand_writespare(uint32_t pagenum, uint16_t colnum, uint8_t *pbuffer,
                        uint16_t numbyte_to_write) {
    uint8_t temp = 0;
    uint8_t remainbyte = 0;

    remainbyte = nand_dev.page_sparesize - colnum;

    if (numbyte_to_write > remainbyte) {
        /* 确保要读取的字节数不大于 spare 剩余的大小 */
        numbyte_to_write = remainbyte;
    }

    temp = nand_writepage(pagenum, colnum + nand_dev.page_mainsize, pbuffer,
                          numbyte_to_write);
    return temp;
}

/**
 * @brief 擦除一个块
 *
 * @param blocknum 要擦除的 block 编号
 *                 范围: `0 - (block_totalnum - 1)`
 * @retval - 0:   擦除成功
 * @retval - 其他: 擦除失败
 */
uint8_t nand_eraseblock(uint32_t blocknum) {
    if (nand_dev.id == MT29F16G08ABABA) {
        /* 将块地址转换为页地址 */
        blocknum <<= 7;
    } else if (nand_dev.id == MT29F4G08ABADA) {
        blocknum <<= 6;
    }

    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_ERASE0;
    /* 发送块地址 */
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)blocknum;
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(blocknum >> 8);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_ADDR) = (uint8_t)(blocknum >> 16);
    *(volatile uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_ERASE1;

    /* 等待擦除成功 */
    delay_ms(NAND_TBERS_DELAY);

    if (nand_wait_for_ready() != NSTA_READY) {
        return NSTA_ERROR;
    }

    return 0;
}

/**
 * @brief 全片擦除 NAND FLASH
 *
 */
void nand_erasechip(void) {
    uint8_t status;
    uint16_t i = 0;

    for (i = 0; i < nand_dev.block_totalnum; i++) {
        status = nand_eraseblock(i);

        if (status) {
            NAND_DEBUG("Erase %d block fail!!, Error code: %x\r\n", i, status);
        }
    }
}

/**
 * @brief 获取 ECC 的奇数位/偶数位
 *
 * @param oe 0: 偶数位; 1: 奇数位
 * @param eccval 输入的 ecc 值
 * @retval 计算后的 ecc 值 (最多 16 位)
 */
uint16_t nand_ecc_get_oe(uint8_t oe, uint32_t eccval) {
    uint8_t i;
    uint16_t ecctemp = 0;

    for (i = 0; i < 24; i++) {
        if ((i % 2) == oe) {
            if ((eccval >> i) & 0x01) {
                ecctemp += 1U << (i >> 1);
            }
        }
    }

    return ecctemp;
}

/**
 * @brief ECC 校正函数
 *
 * @param data_buf 数据缓存区
 * @param eccrd 读取出来, 原来保存的 ECC 值
 * @param ecccl 读取数据时, 硬件计算的 ECC 值
 * @retval - 0:   错误已修正
 * @retval - 其他: ECC 错误 (有大于 2 个 bit 的错误, 无法恢复)
 */
uint8_t nand_ecc_correction(uint8_t *data_buf, uint32_t eccrd, uint32_t ecccl) {
    uint16_t eccrdo, eccrde, eccclo, ecccle;
    uint16_t eccchk = 0;
    uint16_t errorpos = 0;
    uint32_t bytepos = 0;
    eccrdo = nand_ecc_get_oe(1, eccrd);
    eccrde = nand_ecc_get_oe(0, eccrd);
    eccclo = nand_ecc_get_oe(1, ecccl);
    ecccle = nand_ecc_get_oe(0, ecccl);
    eccchk = eccrdo ^ eccrde ^ eccclo ^ ecccle;

    if (eccchk == 0xFFF) {
        /* 全 1, 说明只有 1bit ECC 错误 */
        errorpos = eccrdo ^ eccclo;
        NAND_DEBUG("errorpos: %d\r\n", errorpos);
        bytepos = errorpos / 8;
        data_buf[bytepos] ^= 1U << (errorpos % 8);
    } else {
        /* 不是全 1, 说明至少有 2bit ECC 错误, 无法修复 */
        NAND_DEBUG("2bit ecc error or more\r\n");
        return 1;
    }

    return 0;
}
