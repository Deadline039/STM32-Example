/**
 * @file        sdram.c
 * @author      正点原子团队 (ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       SDRAM 驱动代码
 * @copyright   2020-2032, 广州市星翼电子科技有限公司
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2022-04-20   1.0         Alientek    第一次发布
 */

#include "sdram.h"

#include "../core/core_delay.h"

SDRAM_HandleTypeDef sdram_handle; /* SDRAM 句柄 */

/**
 * @brief 初始化 SDRAM
 *
 */
void sdram_init(void) {
    FMC_SDRAM_TimingTypeDef sdram_timing;

    sdram_handle.Instance = FMC_SDRAM_DEVICE;
    sdram_handle.Init.SDBank = FMC_SDRAM_BANK1;
    /* 列数量 */
    sdram_handle.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
    /* 行数量 */
    sdram_handle.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
    /* 数据宽度为 16 位 */
    sdram_handle.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
    /* 一共 4 个 BANK */
    sdram_handle.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    /* CAS 为 3 */
    sdram_handle.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
    /* 失能写保护 */
    sdram_handle.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;

    /* SDRAM 时钟 = HCLK / 2 */
    sdram_handle.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
    /* 使能突发 */
    sdram_handle.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
    /* 读通道延时 */
    sdram_handle.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
    /* 加载模式寄存器到激活时间的延迟为 2 个时钟周期 */
    sdram_timing.LoadToActiveDelay = 2;
    /* 退出自刷新延迟为 7 个时钟周期 */
    sdram_timing.ExitSelfRefreshDelay = 7;
    /* 自刷新时间为 6 个时钟周期 */
    sdram_timing.SelfRefreshTime = 6;
    /* 行循环延迟为 6 个时钟周期 */
    sdram_timing.RowCycleDelay = 6;
    /* 恢复延迟为 2 个时钟周期 */
    sdram_timing.WriteRecoveryTime = 2;
    /* 行预充电延迟为 2 个时钟周期 */
    sdram_timing.RPDelay = 2;
    /* 行到列延迟为 2 个时钟周期 */
    sdram_timing.RCDDelay = 2;
    HAL_SDRAM_Init(&sdram_handle, &sdram_timing);

    /* 发送 SDRAM 初始化序列 */
    sdram_initialization_sequence();

    /**
     * 刷新频率计数器 (以 SDCLK 频率计数), 计算方法:
     * COUNT = SDRAM 刷新周期 / 行数 - 20 = SDRAM 刷新周期 (us) * SDCLK 频率
     * (Mhz)/ 行数 我们使用的 SDRAM 刷新周期为 64ms, SDCLK = 180 / 2 = 90 Mhz,
     * 行数为 8192 (2^13). 所以, COUNT = 64 * 1000 * 96 / 8192 - 20 = 705
     */
    HAL_SDRAM_ProgramRefreshRate(&sdram_handle, 705);
}

/**
 * @brief 发送 SDRAM 初始化序列
 *
 */
void sdram_initialization_sequence(void) {
    uint32_t temp = 0;

    /* SDRAM 控制器初始化完成以后还需要按照如下顺序初始化 SDRAM */
    sdram_send_cmd(0, FMC_SDRAM_CMD_CLK_ENABLE, 1, 0); /* 时钟配置使能 */
    delay_us(500);                                     /* 至少延时 500us */

    /* 对所有存储区预充电 */
    sdram_send_cmd(0, FMC_SDRAM_CMD_PALL, 1, 0);
    /* 设置自刷新次数 */
    sdram_send_cmd(0, FMC_SDRAM_CMD_AUTOREFRESH_MODE, 8, 0);

    /* 配置模式寄存器,SDRAM 的 bit0~bit2 为指定突发访问的长度,
     * bit3 为指定突发访问的类型,bit4~bit6 为 CAS 值,bit7 和 bit8 为运行模式
     * bit9 为指定的写突发模式,bit10 和 bit11 位保留位 */
    temp =
        /* 设置突发长度: 1 (可以是 1, 2, 4, 8) */
        (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 |
        /* 设置突发类型: 连续 (可以是连续 / 交错) */
        SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
        /* 设置 CAS 值: 3 (可以是 2/3) */
        SDRAM_MODEREG_CAS_LATENCY_3 |
        /* 设置操作模式: 0, 标准模式 */
        SDRAM_MODEREG_OPERATING_MODE_STANDARD |
        /* 设置突发写模式: 1 , 单点访问 */
        SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    /* 设置 SDRAM 的模式寄存器 */
    sdram_send_cmd(0, FMC_SDRAM_CMD_LOAD_MODE, 1, temp);
}

/**
 * @brief SDRAM 底层驱动
 *
 * @param hsdram SDRAM 句柄
 */
void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram) {
    if (hsdram->Instance != FMC_SDRAM_DEVICE) {
        return;
    }

    GPIO_InitTypeDef gpio_init_struct;

    __HAL_RCC_FMC_CLK_ENABLE();   /* 使能 FMC 时钟 */
    __HAL_RCC_GPIOC_CLK_ENABLE(); /* 使能 GPIOC 时钟 */
    __HAL_RCC_GPIOD_CLK_ENABLE(); /* 使能 GPIOD 时钟 */
    __HAL_RCC_GPIOE_CLK_ENABLE(); /* 使能 GPIOE 时钟 */
    __HAL_RCC_GPIOF_CLK_ENABLE(); /* 使能 GPIOF 时钟 */
    __HAL_RCC_GPIOG_CLK_ENABLE(); /* 使能 GPIOG 时钟 */

    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;    /* 推挽复用 */
    gpio_init_struct.Pull = GPIO_PULLUP;        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_HIGH;   /* 高速 */
    gpio_init_struct.Alternate = GPIO_AF12_FMC; /* 复用为 FMC */
    HAL_GPIO_Init(GPIOC, &gpio_init_struct);    /* 初始化 PC0,2,3 */

    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 |
                           GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOD, &gpio_init_struct); /* 初始化 PD0,1,8,9,10,14,15 */

    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 |
                           GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
                           GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
                           GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE,
                  &gpio_init_struct); /* 初始化 PE0,1,7,8,9,10,11,12,13,14,15 */

    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                           GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 |
                           GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF,
                  &gpio_init_struct); /* 初始化 PF0,1,2,3,4,5,11,12,13,14,15 */

    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 |
                           GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOG, &gpio_init_struct); /* 初始化 PG0,1,2,4,5,8,15 */
}

/**
 * @brief 向 SDRAM 发送命令
 *
 * @param bankx 指定发送块
 *  @arg - 0: 向 BANK5 上面的 SDRAM 发送指令
 *  @arg - 1: 向 BANK6 上面的 SDRAM 发送指令
 * @param cmd 指令
 *  @arg - 0: 正常模式
 *  @arg - 1: 时钟配置使能
 *  @arg - 2: 预充电所有存储区
 *  @arg - 3: 自动刷新
 *  @arg - 4: 加载模式寄存器
 *  @arg - 5: 自刷新
 *  @arg - 6: 掉电)
 * @param refresh 自刷新次数
 * @param regval 要写入的模式寄存器的值
 * @return 是否成功. 0-正常; 1-失败.
 */
uint8_t sdram_send_cmd(uint8_t bankx, uint8_t cmd, uint8_t refresh,
                       uint16_t regval) {
    uint32_t target_bank = 0;
    FMC_SDRAM_CommandTypeDef command;

    if (bankx == 0) {
        target_bank = FMC_SDRAM_CMD_TARGET_BANK1;
    } else if (bankx == 1) {
        target_bank = FMC_SDRAM_CMD_TARGET_BANK2;
    }

    command.CommandMode = cmd;               /* 命令 */
    command.CommandTarget = target_bank;     /* 目标 SDRAM 存储区域 */
    command.AutoRefreshNumber = refresh;     /* 自刷新次数 */
    command.ModeRegisterDefinition = regval; /* 要写入模式寄存器的值 */

    if (HAL_SDRAM_SendCommand(&sdram_handle, &command, 0X1000) == HAL_OK) {
        /* 向 SDRAM 发送命令 */
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief 在指定地址 (`addr + BANK5_SDRAM_ADDR`) 开始, 连续写入 n 个字节
 *
 * @param pbuf 写入的数据
 * @param addr 要写入的地址
 * @param n 要写入的字节数
 */
void fmc_sdram_write_buffer(uint8_t *pbuf, uint32_t addr, uint32_t n) {
    for (; n != 0; n--) {
        *(volatile uint8_t *)(BANK5_SDRAM_ADDR + addr) = *pbuf;
        addr++;
        pbuf++;
    }
}

/**
 * @brief 在指定地址 (`addr + BANK5_SDRAM_ADDR`) 开始,连续读取 n 个字节
 *
 * @param[out] pbuf 缓冲区指针
 * @param addr 要读取的地址
 * @param n 要读取的字节数
 */
void fmc_sdram_read_buffer(uint8_t *pbuf, uint32_t addr, uint32_t n) {
    for (; n != 0; n--) {
        *pbuf++ = *(volatile uint8_t *)(BANK5_SDRAM_ADDR + addr);
        addr++;
    }
}
