/**
 * @file        lcd.c
 * @author      正点原子团队 (ALIENTEK)
 * @version     1.3
 * @date        2023-05-31
 * @brief       2.8 寸 / 3.5 寸 / 4.3 寸 / 7 寸 TFTLCD (MCU 屏) 驱动代码
 *              支持驱动 IC 型号包括:
 *              ILI9341/NT35310/NT35510/SSD1963/ST7789/ST7796/ILI9806 等
 * @copyright   2020-2032, 广州市星翼电子科技有限公司
 *
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2020-04-21   1.0         Alientek    第一次发布
 * 2020-05-14   1.1         Alientek    1. 新增对 ST7789 IC 的支持
 *                                      2. 简化部分代码, 避免长判定
 * 2023-05-31   1.2         Alientek    1. 新增对 ST7796 和 ILI9806 支持
 * 2025-01-16   1.3         Deadline039 1. 添加 FSMC 宏开关, 以同时兼容
 *                                         迷你板和精英板
 */
#include "lcd.h"

#include "lcd_ex.h"
#include "lcdfont.h"

#if LCD_USE_FSMC == 1
static SRAM_HandleTypeDef sram_handle;
#endif /* LCD_USE_FSMC */

/* LCD 的画笔颜色和背景色 */
uint32_t g_point_color = 0xFF000000; /* 画笔颜色 */
uint32_t g_back_color = 0xFFFFFFFF;  /* 背景色 */

/* 管理 LCD 重要参数 */
lcd_dev_t lcddev;

/**
 * @brief LCD 延时函数, 仅用于部分在 mdk -O1 时间优化时需要设置的地方
 *
 * @param i 延时的数值
 */
static void lcd_opt_delay(uint32_t i) {
    while (i--) {
        /* 避免被优化 */
        __asm volatile("");
    }
}

#if LCD_USE_FSMC == 1 /* LCD_USE_FSMC */

/**
 * @brief LCD 写数据
 *
 * @param data 要写入的数据
 */
void lcd_wr_data(volatile uint16_t data) {
    data = data; /* 使用 - O2 优化的时候, 必须插入的延时 */
    LCD->LCD_RAM = data;
}

/**
 * @brief LCD 写寄存器编号 / 地址函数
 *
 * @param regno 寄存器编号 / 地址
 */
void lcd_wr_regno(volatile uint16_t regno) {
    regno = regno; /* 使用 - O2 优化的时候, 必须插入的延时 */
    LCD->LCD_REG = regno; /* 写入要写的寄存器序号 */
}

/**
 * @brief LCD 写寄存器
 *
 * @param regno 寄存器编号 / 地址
 * @param data 要写入的数据
 */
void lcd_write_reg(uint16_t regno, uint16_t data) {
    LCD->LCD_REG = regno; /* 写入要写的寄存器序号 */
    LCD->LCD_RAM = data;  /* 写入数据 */
}

/**
 * @brief LCD 读数据
 *
 * @return 读取到的数据
 */
static uint16_t lcd_rd_data(void) {
    volatile uint16_t ram; /* 防止被优化 */

    ram = LCD->LCD_RAM;

    return ram;
}

/**
 * @brief 准备写 GRAM
 *
 */
void lcd_write_ram_prepare(void) {
    LCD->LCD_REG = lcddev.wramcmd;
}

#else /* LCD_USE_FSMC */

/**
 * @brief LCD 写入数据
 *
 * @param data 写入的数据
 * @note 该函数与`lcd_wr_data`的功能一模一样,
 *       `lcd_wr_data`是用空间换时间, 该函数则是时间换空间
 *       该函数用于LCD初始化, 仅在`lcd_ex.c`里面调用, 以节
 *       省代码空间.
 */
void lcd_wr_xdata(uint16_t data) {
    LCD_RS(1);
    LCD_CS(0);
    LCD_DATA_OUT(data);
    LCD_WR(0);
    LCD_WR(1);
    LCD_CS(1);
}

/**
 * @brief LCD 写寄存器编号 / 地址函数
 *
 * @param regno 寄存器编号 / 地址
 */
__attribute__((always_inline)) void lcd_wr_regno(volatile uint16_t regno) {
    LCD_RS(0); /* RS = 0,表示写寄存器 */
    LCD_CS(0);
    LCD_DATA_OUT(regno); /* 写入要写的寄存器序号 */
    LCD_WR(0);
    LCD_WR(1);
    LCD_CS(1);
}

/**
 * @brief LCD 写寄存器
 *
 * @param regno 寄存器编号 / 地址
 * @param data 要写入的数据
 */
void lcd_write_reg(uint16_t regno, uint16_t data) {
    lcd_wr_regno(regno);
    lcd_wr_data(data);
}

/**
 * @brief LCD 读数据
 *
 * @return 读取到的数据
 */
static uint16_t lcd_rd_data(void) {
    volatile uint16_t ram; /* 防止被优化 */

    GPIO_InitTypeDef gpio_init_struct;
    /* LCD_DATA 引脚模式设置, 上拉输入, 准备接收数据 */
    gpio_init_struct.Pin = LCD_DATA_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_DATA_GPIO_PORT), &gpio_init_struct);

    LCD_RS(1); /* RS = 1, 表示操作数据 */
    LCD_CS(0);
    LCD_RD(0);
    lcd_opt_delay(2);
    ram = LCD_DATA_IN; /* 读取数据 */
    LCD_RD(1);
    LCD_CS(1);

    /* LCD_DATA 引脚模式设置, 推挽输出, 恢复输出状态 */
    gpio_init_struct.Pin = LCD_DATA_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_DATA_GPIO_PORT), &gpio_init_struct);

    return ram;
}

/**
 * @brief 准备写 GRAM
 *
 */
void lcd_write_ram_prepare(void) {
    lcd_wr_regno(lcddev.wramcmd);
}

#endif /* LCD_USE_FSMC */

/**
 * @brief 读取个某点的颜色值
 *
 * @param x x 坐标
 * @param y y 坐标
 * @retval 此点的颜色 (32 位颜色, 方便兼容 LTDC)
 */
uint32_t lcd_read_point(uint16_t x, uint16_t y) {
    uint16_t r = 0, g = 0, b = 0;

    if (x >= lcddev.width || y >= lcddev.height) {
        return 0; /* 超过了范围, 直接返回 */
    }

    lcd_set_cursor(x, y); /* 设置坐标 */

    if (lcddev.id == 0X5510) {
        lcd_wr_regno(0X2E00); /* 5510 发送读 GRAM 指令 */
    } else {
        /* 9341/5310/1963/7789/7796/9806 等发送读 GRAM 指令 */
        lcd_wr_regno(0X2E);
    }

    r = lcd_rd_data(); /* 假读 (dummy read) */

    if (lcddev.id == 0x1963) {
        return r; /* 1963 直接读就可以 */
    }

    lcd_opt_delay(2);
    r = lcd_rd_data(); /* 实际坐标颜色 */

    if (lcddev.id == 0x7796) {
        /* 7796 一次读取一个像素值 */
        return r;
    }

    /* 9341/5310/5510/7789/9806 要分 2 次读出 */
    lcd_opt_delay(2);
    b = lcd_rd_data();
    /* 对于 9341/5310/5510/7789/9806, 第一次读取的是 RG 的值, R
     * 在前, G 在后, 各占 8 位 */
    g = r & 0xFF;
    g <<= 8;
    /* ILI9341/NT35310/NT35510/ST7789/ILI9806 需要公式转换一下 */
    return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));
}

/**
 * @brief LCD 开启显示
 *
 */
void lcd_display_on(void) {
    if (lcddev.id == 0X5510) {
        lcd_wr_regno(0X2900); /* 开启显示 */
    } else {
        /* 9341/5310/1963/7789/7796/9806 等发送开启显示指令 */
        lcd_wr_regno(0X29); /* 开启显示 */
    }
}

/**
 * @brief LCD 关闭显示
 *
 */
void lcd_display_off(void) {
    if (lcddev.id == 0X5510) {
        lcd_wr_regno(0X2800); /* 关闭显示 */
    } else {
        /* 9341/5310/1963/7789/7796/9806 等发送关闭显示指令 */
        lcd_wr_regno(0X28); /* 关闭显示 */
    }
}

/**
 * @brief 设置光标位置 (对 RGB 屏无效)
 *
 * @param x x 坐标
 * @param y y 坐标
 */
void lcd_set_cursor(uint16_t x, uint16_t y) {
    if (lcddev.id == 0x1963) {
        if (lcddev.dir == 0) {
            /* 竖屏模式, x 坐标需要变换 */
            x = lcddev.width - 1 - x;
            lcd_wr_regno(lcddev.setxcmd);
            lcd_wr_data(0);
            lcd_wr_data(0);
            lcd_wr_data(x >> 8);
            lcd_wr_data(x & 0xFF);
        } else {
            /* 横屏模式 */
            lcd_wr_regno(lcddev.setxcmd);
            lcd_wr_data(x >> 8);
            lcd_wr_data(x & 0xFF);
            lcd_wr_data((lcddev.width - 1) >> 8);
            lcd_wr_data((lcddev.width - 1) & 0xFF);
        }

        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_data(y & 0xFF);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_data((lcddev.height - 1) & 0xFF);
    } else if (lcddev.id == 0x5510) {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(x >> 8);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(x & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(y & 0xFF);
    } else {
        /* 9341/5310/7789/7796/9806 等 设置坐标 */
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(x >> 8);
        lcd_wr_data(x & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_data(y & 0xFF);
    }
}

/**
 * @brief 设置 LCD 的自动扫描方向 (对 RGB 屏无效)
 *
 * @param dir 0~7, 代表 8 个方向 (具体定义见 lcd.h)
 * @note 9341/5310/5510/1963/7789/7796/9806 等 IC 已经实际测试
 * @attention 其他函数可能会受到此函数设置的影响 (尤其是 9341),
 *            所以, 一般设置为 L2R_U2D 即可.
 *             如果设置为其他扫描方式, 可能导致显示不正常.
 */
void lcd_scan_dir(uint8_t dir) {
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;
    static const uint8_t dir_table[8] = {6, 7, 4, 5, 1, 0, 3, 2};

    if (dir > 8) {
        return;
    }

    /* 横屏时, 对 1963 不改变扫描方向!竖屏时 1963 改变方向 (这里仅用于 1963
     * 的特殊处理, 对其他驱动 IC 无效) */
    if ((lcddev.dir == 1 && lcddev.id != 0x1963) ||
        (lcddev.dir == 0 && lcddev.id == 0x1963)) {
        dir = dir_table[dir];
    }

    /* 根据扫描方式 设置 0x36/0x3600 寄存器 bit 5, 6, 7 位的值 */
    switch (dir) {
        case L2R_U2D: /* 从左到右, 从上到下 */
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;

        case L2R_D2U: /* 从左到右, 从下到上 */
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;

        case R2L_U2D: /* 从右到左, 从上到下 */
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;

        case R2L_D2U: /* 从右到左, 从下到上 */
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;

        case U2D_L2R: /* 从上到下, 从左到右 */
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;

        case U2D_R2L: /* 从上到下, 从右到左 */
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;

        case D2U_L2R: /* 从下到上, 从左到右 */
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;

        case D2U_R2L: /* 从下到上, 从右到左 */
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;

        default:
            break;
    }

    dirreg = 0x36; /* 对绝大部分驱动 IC, 由 0x36 寄存器控制 */

    if (lcddev.id == 0x5510) {
        dirreg = 0x3600; /* 对于 5510, 和其他驱动 ic 的寄存器有差异 */
    }

    /* 9341 & 7789 & 7796 要设置 BGR 位 */
    if (lcddev.id == 0x9341 || lcddev.id == 0x7789 || lcddev.id == 0x7796) {
        regval |= 0x08;
    }

    lcd_write_reg(dirreg, regval);

    /* 1963 不做坐标处理 */
    if (lcddev.id != 0x1963) {
        /* 交换 X, Y */
        if (regval & 0x20) {
            if (lcddev.width < lcddev.height) {

                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        } else {
            if (lcddev.width > lcddev.height) {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
    }

    /* 设置显示区域 (开窗) 大小 */
    if (lcddev.id == 0x5510) {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setxcmd + 2);
        lcd_wr_data((lcddev.width - 1) >> 8);
        lcd_wr_regno(lcddev.setxcmd + 3);
        lcd_wr_data((lcddev.width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setycmd + 2);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_regno(lcddev.setycmd + 3);
        lcd_wr_data((lcddev.height - 1) & 0xFF);
    } else {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(0);
        lcd_wr_data(0);
        lcd_wr_data((lcddev.width - 1) >> 8);
        lcd_wr_data((lcddev.width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(0);
        lcd_wr_data(0);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_data((lcddev.height - 1) & 0xFF);
    }
}

/**
 * @brief 画点
 *
 * @param x x 坐标
 * @param y y 坐标
 * @param color 点的颜色 (32 位颜色, 方便兼容 LTDC)
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color) {
    lcd_set_cursor(x, y);    /* 设置光标位置  */
    lcd_write_ram_prepare(); /* 开始写入 GRAM */
#if LCD_USE_FSMC == 1
    LCD->LCD_RAM = color;
#else  /* LCD_USE_FSMC */
    lcd_wr_data(color);
#endif /* LCD_USE_FSMC */
}

/**
 * @brief SSD1963 背光亮度设置函数
 *
 * @param pwm 背光等级, 0~100. 越大越亮.
 */
void lcd_ssd_backlight_set(uint8_t pwm) {
    lcd_wr_regno(0xBE);                          /* 配置 PWM 输出 */
    lcd_wr_data(0x05);                           /* 1 设置 PWM 频率 */
    lcd_wr_data((uint16_t)((float)pwm * 2.55f)); /* 2 设置 PWM 占空比 */
    lcd_wr_data(0x01);                           /* 3 设置 C */
    lcd_wr_data(0xFF);                           /* 4 设置 D */
    lcd_wr_data(0x00);                           /* 5 设置 E */
    lcd_wr_data(0x00);                           /* 6 设置 F */
}

/**
 * @brief 设置 LCD 显示方向
 *
 * @param dir 0, 竖屏;1, 横屏
 */
void lcd_display_dir(uint8_t dir) {
    lcddev.dir = dir; /* 竖屏 / 横屏 */

    if (dir == 0) {
        /* 竖屏 */
        lcddev.width = 240;
        lcddev.height = 320;

        if (lcddev.id == 0x5510) {
            lcddev.wramcmd = 0x2C00;
            lcddev.setxcmd = 0x2A00;
            lcddev.setycmd = 0x2B00;
            lcddev.width = 480;
            lcddev.height = 800;
        } else if (lcddev.id == 0x1963) {
            lcddev.wramcmd = 0x2C; /* 设置写入 GRAM 的指令 */
            lcddev.setxcmd = 0x2B; /* 设置写 X 坐标指令 */
            lcddev.setycmd = 0x2A; /* 设置写 Y 坐标指令 */
            lcddev.width = 480;    /* 设置宽度 480 */
            lcddev.height = 800;   /* 设置高度 800 */
        } else {
            /* 其他 IC, 包括: 9341/5310/7789/7796/9806 等 IC */
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310 || lcddev.id == 0x7796) {
            /* 如果是 5310/7796 则表示是 320*480 分辨率 */
            lcddev.width = 320;
            lcddev.height = 480;
        }

        if (lcddev.id == 0X9806) {
            /* 如果是 9806 则表示是 480*800 分辨率 */
            lcddev.width = 480;
            lcddev.height = 800;
        }
    } else {
        /* 横屏 */
        lcddev.width = 320;  /* 默认宽度 */
        lcddev.height = 240; /* 默认高度 */

        if (lcddev.id == 0x5510) {
            lcddev.wramcmd = 0x2C00;
            lcddev.setxcmd = 0x2A00;
            lcddev.setycmd = 0x2B00;
            lcddev.width = 800;
            lcddev.height = 480;
        } else if (lcddev.id == 0x1963 || lcddev.id == 0x9806) {
            lcddev.wramcmd = 0x2C; /* 设置写入 GRAM 的指令 */
            lcddev.setxcmd = 0x2A; /* 设置写 X 坐标指令 */
            lcddev.setycmd = 0x2B; /* 设置写 Y 坐标指令 */
            lcddev.width = 800;    /* 设置宽度 800 */
            lcddev.height = 480;   /* 设置高度 480 */
        } else {
            /* 其他 IC, 包括:9341/5310/7789/7796 等 IC */
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310 || lcddev.id == 0x7796) {
            /* 如果是 5310/7796 则表示是 320*480 分辨率 */
            lcddev.width = 480;
            lcddev.height = 320;
        }
    }

    lcd_scan_dir(DFT_SCAN_DIR); /* 默认扫描方向 */
}

/**
 * @brief 设置窗口 (对 RGB 屏无效), 并自动设置画点坐标到窗口左上角(sx, sy).
 *
 * @param sx 窗口起始 x 坐标 (左上角)
 * @param sy 窗口起始 y 坐标 (左上角)
 * @param width 窗口宽度, 必须大于 0!!
 * @param height 窗口高度, 必须大于 0!!
 * @note 窗体大小: `width * height`
 */
void lcd_set_window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height) {
    uint16_t twidth, theight;
    twidth = sx + width - 1;
    theight = sy + height - 1;

    if (lcddev.id == 0x1963 && lcddev.dir != 1) {
        /* 1963 竖屏特殊处理 */
        sx = lcddev.width - width - sx;
        height = sy + height - 1;
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(sx >> 8);
        lcd_wr_data(sx & 0xFF);
        lcd_wr_data((sx + width - 1) >> 8);
        lcd_wr_data((sx + width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(sy >> 8);
        lcd_wr_data(sy & 0xFF);
        lcd_wr_data(height >> 8);
        lcd_wr_data(height & 0xFF);
    } else if (lcddev.id == 0x5510) {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(sx >> 8);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(sx & 0xFF);
        lcd_wr_regno(lcddev.setxcmd + 2);
        lcd_wr_data(twidth >> 8);
        lcd_wr_regno(lcddev.setxcmd + 3);
        lcd_wr_data(twidth & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(sy >> 8);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(sy & 0xFF);
        lcd_wr_regno(lcddev.setycmd + 2);
        lcd_wr_data(theight >> 8);
        lcd_wr_regno(lcddev.setycmd + 3);
        lcd_wr_data(theight & 0xFF);
    } else {
        /* 9341/5310/7789/1963/7796/9806 横屏 等 设置窗口 */
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(sx >> 8);
        lcd_wr_data(sx & 0xFF);
        lcd_wr_data(twidth >> 8);
        lcd_wr_data(twidth & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(sy >> 8);
        lcd_wr_data(sy & 0xFF);
        lcd_wr_data(theight >> 8);
        lcd_wr_data(theight & 0xFF);
    }
}

#if LCD_USE_FSMC == 1

/**
 * @brief SRAM 底层驱动, 时钟使能, 引脚分配
 *
 * @param hsram SRAM 句柄
 */
void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram) {
    UNUSED(hsram);

    GPIO_InitTypeDef gpio_init_struct;

    __HAL_RCC_FSMC_CLK_ENABLE();  /* 使能FSMC时钟 */
    __HAL_RCC_GPIOD_CLK_ENABLE(); /* 使能GPIOD时钟 */
    __HAL_RCC_GPIOE_CLK_ENABLE(); /* 使能GPIOE时钟 */

    /* 初始化PD0,1,8,9,10,14,15 */
    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 |
                           GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;       /* 推挽复用 */
    gpio_init_struct.Pull = GPIO_PULLUP;           /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */
    HAL_GPIO_Init(GPIOD, &gpio_init_struct);       /* 初始化 */

    /* 初始化PE7,8,9,10,11,12,13,14,15 */
    gpio_init_struct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                           GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
                           GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &gpio_init_struct);
}
#endif /* LCD_USE_FSMC */

/**
 * @brief 初始化 LCD
 *
 * @note 该初始化函数可以初始化各种型号的 LCD (详见本 .c 文件最前面的描述)
 */
void lcd_init(void) {
    GPIO_InitTypeDef gpio_init_struct;

#if LCD_USE_FSMC == 1
    FSMC_NORSRAM_TimingTypeDef fsmc_read_handle;
    FSMC_NORSRAM_TimingTypeDef fsmc_write_handle;
    CSP_GPIO_CLK_ENABLE(LCD_CS_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LCD_WR_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LCD_RD_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LCD_RS_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LCD_BL_GPIO_PORT);

    gpio_init_struct.Pin = LCD_CS_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;       /* 推挽复用 */
    gpio_init_struct.Pull = GPIO_PULLUP;           /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_CS_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LCD_WR_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_WR_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LCD_RD_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_RD_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LCD_RS_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_RS_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP; /* 推挽输出 */
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_BL_GPIO_PORT), &gpio_init_struct);

    sram_handle.Instance = FSMC_NORSRAM_DEVICE;
    sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

    sram_handle.Init.NSBank = LCD_FSMC_NSBANK;
    /* 地址/数据线不复用 */
    sram_handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
    /* 16位数据宽度 */
    sram_handle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
    /* 是否使能突发访问,仅对同步突发存储器有效,此处未用到 */
    sram_handle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
    /* 等待信号的极性,仅在突发模式访问下有用 */
    sram_handle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
    /* 存储器是在等待周期之前的一个时钟周期还是等待周期期间使能 NWAIT */
    sram_handle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
    /* 存储器写使能 */
    sram_handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
    /* 等待使能位,此处未用到 */
    sram_handle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
    /* 读写使用不同的时序 */
    sram_handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;
    /* 是否使能同步传输模式下的等待信号,此处未用到 */
    sram_handle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
    /* 禁止突发写 */
    sram_handle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;

    /* FSMC读时序控制寄存器 */

    /* 地址建立时间(ADDSET)为1个HCLK 1/72M = 13.9ns (实际 > 200ns) */
    fsmc_read_handle.AddressSetupTime = 0;
    /* 地址保持时间(ADDHLD) 模式A是没有用到 */
    fsmc_read_handle.AddressHoldTime = 1;
    /* 因为液晶驱动IC的读数据的时候, 速度不能太快,尤其是个别奇葩芯片 *
     * 数据保存时间(DATAST)为16个HCLK = 13.9 * 16 = 222.4ns */
    fsmc_read_handle.DataSetupTime = 15;
    fsmc_read_handle.AccessMode = FSMC_ACCESS_MODE_A; /* 模式A */
    fsmc_read_handle.CLKDivision = 2;
    fsmc_read_handle.DataLatency = 2;

    /* FSMC写时序控制寄存器 */

    /* 地址建立时间(ADDSET)为1个HCLK = 13.9ns */
    fsmc_write_handle.AddressSetupTime = 0;
    /* 地址保持时间(ADDHLD) 模式A是没有用到 */
    fsmc_write_handle.AddressHoldTime = 1;
    /* 数据保存时间(DATAST)为2个HCLK = 13.9 * 2 = 27.8ns (实际 > 200ns) */
    fsmc_write_handle.DataSetupTime = 1;
    /* 某些液晶驱动IC的写信号脉宽, 最少也得50ns */
    fsmc_write_handle.AccessMode = FSMC_ACCESS_MODE_A;
    fsmc_write_handle.BusTurnAroundDuration = 0;
    HAL_SRAM_Init(&sram_handle, &fsmc_read_handle, &fsmc_write_handle);

    delay_ms(50);
#else  /* LCD_USE_FSMC */

    /* 禁止JTAG, 使能SWD, 释放PB3,PB4两个引脚做普通IO用 */
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();

    CSP_GPIO_CLK_ENABLE(LCD_CS_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LCD_WR_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LCD_RD_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LCD_RS_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LCD_BL_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LCD_DATA_GPIO_PORT);

    gpio_init_struct.Pin = LCD_CS_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;   /* 推挽复用 */
    gpio_init_struct.Pull = GPIO_PULLUP;           /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_CS_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LCD_WR_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_WR_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LCD_RD_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_RD_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LCD_RS_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_RS_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_BL_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LCD_DATA_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(LCD_DATA_GPIO_PORT), &gpio_init_struct);

    LCD_WR(1);            /* WR 默认高电平 */
    LCD_RD(1);            /* RD 默认高电平 */
    LCD_CS(1);            /* CS 默认高电平 */
    LCD_RS(1);            /* RS 默认高电平 */
    LCD_DATA_OUT(0XFFFF); /* DATA 默认高电平 */

    lcd_opt_delay(0X1FFFF);
#endif /* LCD_USE_FSMC */

    /* 尝试 9341 ID 的读取 */
    lcd_wr_regno(0xD3);
    lcddev.id = lcd_rd_data(); /* dummy read */
    lcddev.id = lcd_rd_data(); /* 读到 0x00 */
    lcddev.id = lcd_rd_data(); /* 读取 93 */
    lcddev.id <<= 8;
    lcddev.id |= lcd_rd_data(); /* 读取 41 */

    if (lcddev.id != 0x9341) {
        /* 不是 9341 , 尝试看看是不是 ST7789 */
        lcd_wr_regno(0x04);
        lcddev.id = lcd_rd_data(); /* dummy read */
        lcddev.id = lcd_rd_data(); /* 读到 0x85 */
        lcddev.id = lcd_rd_data(); /* 读取 0x85 */
        lcddev.id <<= 8;
        lcddev.id |= lcd_rd_data(); /* 读取 0x52 */

        if (lcddev.id == 0x8552) {
            /* 将 8552 的 ID 转换成 7789 */
            lcddev.id = 0x7789;
        }

        if (lcddev.id != 0x7789) {
            /* 也不是 ST7789, 尝试是不是 NT35310 */
            lcd_wr_regno(0xD4);
            lcddev.id = lcd_rd_data(); /* dummy read */
            lcddev.id = lcd_rd_data(); /* 读回 0x01 */
            lcddev.id = lcd_rd_data(); /* 读回 0x53 */
            lcddev.id <<= 8;
            lcddev.id |= lcd_rd_data(); /* 这里读回 0x10 */

            if (lcddev.id != 0x5310) {
                /* 也不是 NT35310, 尝试看看是不是 ST7796 */
                lcd_wr_regno(0XD3);
                lcddev.id = lcd_rd_data(); /* dummy read */
                lcddev.id = lcd_rd_data(); /* 读到 0X00 */
                lcddev.id = lcd_rd_data(); /* 读取 0X77 */
                lcddev.id <<= 8;
                lcddev.id |= lcd_rd_data(); /* 读取 0X96 */

                if (lcddev.id != 0x7796) {
                    /* 也不是 ST7796, 尝试看看是不是 NT35510 */
                    /* 发送密钥 (厂家提供) */
                    lcd_write_reg(0xF000, 0x0055);
                    lcd_write_reg(0xF001, 0x00AA);
                    lcd_write_reg(0xF002, 0x0052);
                    lcd_write_reg(0xF003, 0x0008);
                    lcd_write_reg(0xF004, 0x0001);

                    lcd_wr_regno(0xC500);      /* 读取 ID 低八位 */
                    lcddev.id = lcd_rd_data(); /* 读回 0x80 */
                    lcddev.id <<= 8;

                    lcd_wr_regno(0xC501);       /* 读取 ID 高八位 */
                    lcddev.id |= lcd_rd_data(); /* 读回 0x00 */
                    /* 等待 5ms, 因为 0XC501 指令对 1963
                     * 来说就是软件复位指令, 等待 5ms 让 1963 复位完成再操作
                     */
                    delay_ms(5);

                    if (lcddev.id != 0x5510) {
                        /* 也不是 NT5510, 尝试看看是不是 ILI9806 */
                        lcd_wr_regno(0XD3);
                        lcddev.id = lcd_rd_data(); /* dummy read */
                        lcddev.id = lcd_rd_data(); /* 读回 0X00 */
                        lcddev.id = lcd_rd_data(); /* 读回 0X98 */
                        lcddev.id <<= 8;
                        lcddev.id |= lcd_rd_data(); /* 读回 0X06 */

                        if (lcddev.id != 0x9806) {
                            /* 也不是 ILI9806, 尝试看看是不是 SSD1963 */
                            lcd_wr_regno(0xA1);
                            lcddev.id = lcd_rd_data();
                            lcddev.id = lcd_rd_data(); /* 读回 0x57 */
                            lcddev.id <<= 8;
                            lcddev.id |= lcd_rd_data(); /* 读回 0x61 */

                            if (lcddev.id == 0x5761) {
                                /* SSD1963 读回的 ID 是
                                 * 5761H, 为方便区分, 我们强制设置为 1963 */
                                lcddev.id = 0x1963;
                            }
                        }
                    }
                }
            }
        }
    }

    switch (lcddev.id) {
        case 0x7789:
            lcd_ex_st7789_reginit(); /* 执行 ST7789 初始化 */
            break;

        case 0x9341:
            lcd_ex_ili9341_reginit(); /* 执行 ILI9341 初始化 */
            break;
        case 0x5310:
            lcd_ex_nt35310_reginit(); /* 执行 NT35310 初始化 */
            break;

        case 0x7796:
            lcd_ex_st7796_reginit(); /* 执行 ST7796 初始化 */
            break;

        case 0x5510:
            lcd_ex_nt35510_reginit(); /* 执行 NT35510 初始化 */
            break;

        case 0x9806:
            lcd_ex_ili9806_reginit(); /* 执行 ILI9806 初始化 */
            break;

        case 0x1963:
            lcd_ex_ssd1963_reginit();   /* 执行 SSD1963 初始化 */
            lcd_ssd_backlight_set(100); /* 背光设置为最亮 */
            break;

        default:
            /* 未知的 LCD */
            return;
    }

    lcd_display_dir(0); /* 默认为竖屏 */
    LCD_BL(1);          /* 点亮背光 */
    lcd_clear(WHITE);
}

/**
 * @brief 清屏函数
 *
 * @param color 要清屏的颜色
 */
void lcd_clear(uint16_t color) {
    uint32_t index = 0;
    uint32_t totalpoint = lcddev.width;

    totalpoint *= lcddev.height;  /* 得到总点数 */
    lcd_set_cursor(0x00, 0x0000); /* 设置光标位置 */
    lcd_write_ram_prepare();      /* 开始写入 GRAM */

#if LCD_USE_FSMC
    for (index = 0; index < totalpoint; index++) {
        LCD->LCD_RAM = color;
    }
#else  /* LCD_USE_FSMC */
    /* 为了提高写入速度, 将lcd_wr_data函数进行拆分, 避免重复设置
     * RS, CS的操作, 从而提升速度, 从51帧提高到78帧左右, 提高50%
     * 测试条件: -O2优化, 纯刷屏
     * 在有速度要求的时候, 可以继续优化: lcd_fill, lcd_color_fill,
     * lcd_set_cursor 和 lcd_draw_point 等函数, 大家可以自行优化
     */
    LCD_RS(1); /* RS=1,表示写数据 */
    LCD_CS(0);

    for (index = 0; index < totalpoint; index++) {
        LCD_DATA_OUT(color); /* 写入要写的数据 */
        LCD_WR(0);
        LCD_WR(1);
    }

    LCD_CS(1);
#endif /* LCD_USE_FSMC */
}

/**
 * @brief 在指定区域内填充单个颜色
 *
 * @param sx 起始 x 坐标
 * @param sy 起始 y 坐标
 * @param ex 终点 x 坐标
 * @param ey 终点 y 坐标
 * @param color 要填充的颜色
 * @note 区域大小为:`(ex - sx + 1) * (ey - sy + 1)`
 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
              uint32_t color) {
    uint16_t i, j;
    uint16_t xlen = 0;

    xlen = ex - sx + 1;

    for (i = sy; i <= ey; i++) {
        lcd_set_cursor(sx, i);   /* 设置光标位置 */
        lcd_write_ram_prepare(); /* 开始写入 GRAM */

        for (j = 0; j < xlen; j++) {
#if LCD_USE_FSMC
            LCD->LCD_RAM = color;
#else  /* LCD_USE_FSMC */
            lcd_wr_data(color);
#endif /* LCD_USE_FSMC */
        }
    }
}

/**
 * @brief 在指定区域内填充指定颜色块
 *
 * @param sx 起始 x 坐标
 * @param sy 起始 y 坐标
 * @param ex 终点 x 坐标
 * @param ey 终点 y 坐标
 * @param color 填充的颜色数组首地址
 * @note 区域大小为:`(ex - sx + 1) * (ey - sy + 1)`
 */
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                    uint16_t *color) {
    uint16_t height, width;
    uint16_t i, j;

    width = ex - sx + 1;  /* 得到填充的宽度 */
    height = ey - sy + 1; /* 高度 */

    for (i = 0; i < height; i++) {
        lcd_set_cursor(sx, sy + i); /* 设置光标位置 */
        lcd_write_ram_prepare();    /* 开始写入 GRAM */

        for (j = 0; j < width; j++) {
#if LCD_USE_FSMC
            LCD->LCD_RAM = color[i * width + j];
#else  /* LCD_USE_FSMC */
            lcd_wr_data(color[i * width + j]);
#endif /* LCD_USE_FSMC */
        }
    }
}

/**
 * @brief 画线
 *
 * @param x1 起点 x 坐标
 * @param y1 起点 y 坐标
 * @param x2 终点 x 坐标
 * @param y2 终点 y 坐标
 * @param color 线的颜色
 */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                   uint16_t color) {
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;
    delta_x = x2 - x1; /* 计算坐标增量 */
    delta_y = y2 - y1;
    row = x1;
    col = y1;

    if (delta_x > 0) {
        incx = 1; /* 设置单步方向 */
    } else if (delta_x == 0) {
        incx = 0; /* 垂直线 */
    } else {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0) {
        incy = 1;
    } else if (delta_y == 0) {
        incy = 0; /* 水平线 */
    } else {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y) {
        distance = delta_x; /* 选取基本增量坐标轴 */
    } else {
        distance = delta_y;
    }

    for (t = 0; t <= distance + 1; t++) /* 画线输出 */
    {
        lcd_draw_point(row, col, color); /* 画点 */
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance) {
            xerr -= distance;
            row += incx;
        }

        if (yerr > distance) {
            yerr -= distance;
            col += incy;
        }
    }
}

/**
 * @brief 画水平线
 *
 * @param x 起点 x 坐标
 * @param y 起点 x 坐标
 * @param len 线长度
 * @param color 矩形的颜色
 */
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color) {
    if ((len == 0) || (x > lcddev.width) || (y > lcddev.height)) {
        return;
    }

    lcd_fill(x, y, x + len - 1, y, color);
}

/**
 * @brief 画矩形
 *
 * @param x1 起点 x 坐标
 * @param y1 起点 y 坐标
 * @param x2 终点 x 坐标
 * @param y2 终点 y 坐标
 * @param color 矩形的颜色
 */
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                        uint16_t color) {
    lcd_draw_line(x1, y1, x2, y1, color);
    lcd_draw_line(x1, y1, x1, y2, color);
    lcd_draw_line(x1, y2, x2, y2, color);
    lcd_draw_line(x2, y1, x2, y2, color);
}

/**
 * @brief 画圆
 *
 * @param x 圆心 x 坐标
 * @param y 圆心 y 坐标
 * @param r 半径
 * @param color 圆的颜色
 */
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color) {
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1); /* 判断下个点位置的标志 */

    while (a <= b) {
        lcd_draw_point(x0 + a, y0 - b, color); /* 5 */
        lcd_draw_point(x0 + b, y0 - a, color); /* 0 */
        lcd_draw_point(x0 + b, y0 + a, color); /* 4 */
        lcd_draw_point(x0 + a, y0 + b, color); /* 6 */
        lcd_draw_point(x0 - a, y0 + b, color); /* 1 */
        lcd_draw_point(x0 - b, y0 + a, color);
        lcd_draw_point(x0 - a, y0 - b, color); /* 2 */
        lcd_draw_point(x0 - b, y0 - a, color); /* 7 */
        a++;

        /* 使用 Bresenham 算法画圆 */
        if (di < 0) {
            di += 4 * a + 6;
        } else {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

/**
 * @brief 填充实心圆
 *
 * @param x 圆心 x 坐标
 * @param y 圆心 y 坐标
 * @param r 半径
 * @param color 圆的颜色
 */
void lcd_fill_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
    uint32_t i;
    uint32_t imax = ((uint32_t)r * 707) / 1000 + 1;
    uint32_t sqmax = (uint32_t)r * (uint32_t)r + (uint32_t)r / 2;
    uint32_t xr = r;

    lcd_draw_hline(x - r, y, 2 * r, color);

    for (i = 1; i <= imax; i++) {
        if ((i * i + xr * xr) > sqmax) {
            /* draw lines from outside */
            if (xr > imax) {
                lcd_draw_hline(x - i + 1, y + xr, 2 * (i - 1), color);
                lcd_draw_hline(x - i + 1, y - xr, 2 * (i - 1), color);
            }

            xr--;
        }

        /* draw lines from inside (center) */
        lcd_draw_hline(x - xr, y + i, 2 * xr, color);
        lcd_draw_hline(x - xr, y - i, 2 * xr, color);
    }
}

/**
 * @brief 在指定位置显示一个字符
 *
 * @param x x 坐标
 * @param y y 坐标
 * @param chr 要显示的字符 ' ' --> '~'
 * @param size 字体大小 12/16/24/32
 * @param mode 叠加方式 (1); 非叠加方式 (0);
 * @param color 字符的颜色;
 */
void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode,
                   uint16_t color) {
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = 0;
    uint8_t *pfont = 0;

    /* 得到字体一个字符对应点阵集所占的字节数 */
    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);
    chr = chr - ' '; /* 得到偏移后的值 (ASCII 字库是从空格开始取模) */

    switch (size) {
        case 12:
            pfont = (uint8_t *)asc2_1206[(uint8_t)chr]; /* 调用 1206 字体 */
            break;

        case 16:
            pfont = (uint8_t *)asc2_1608[(uint8_t)chr]; /* 调用 1608 字体 */
            break;

        case 24:
            pfont = (uint8_t *)asc2_2412[(uint8_t)chr]; /* 调用 2412 字体 */
            break;

        case 32:
            pfont = (uint8_t *)asc2_3216[(uint8_t)chr]; /* 调用 3216 字体 */
            break;

        default:
            return;
    }

    for (t = 0; t < csize; t++) {
        temp = pfont[t]; /* 获取字符的点阵数据 */

        for (t1 = 0; t1 < 8; t1++) /* 一个字节 8 个点 */
        {
            if (temp & 0x80) {
                /* 有效点, 需要显示 */
                lcd_draw_point(x, y, color); /* 画点出来, 要显示这个点 */
            } else if (mode == 0) {
                /* 无效点, 不显示 */
                /* 画背景色, 相当于这个点不显示 (注意背景色由全局变量控制) */
                lcd_draw_point(x, y, g_back_color);
            }

            temp <<= 1; /* 移位, 以便获取下一个位的状态 */
            y++;

            if (y >= lcddev.height) {
                return; /* 超区域了 */
            }

            if ((y - y0) == size) {
                /* 显示完一列了?*/
                y = y0; /* y 坐标复位 */
                x++;    /* x 坐标递增 */

                if (x >= lcddev.width) {
                    return; /* x 坐标超区域了 */
                }

                break;
            }
        }
    }
}

/**
 * @brief 幂函数, m^n
 *
 * @param m 底数
 * @param n 指数
 * @retval m 的 n 次方
 */
static uint32_t lcd_pow(uint8_t m, uint8_t n) {
    uint32_t result = 1;

    while (n--) {
        result *= m;
    }

    return result;
}

/**
 * @brief 显示 len 个数字
 *
 * @param x x 坐标
 * @param y y 坐标
 * @param num 数值 (0 ~ 2^32)
 * @param len 显示数字的位数
 * @param size 选择字体 12/16/24/32
 * @param color 数字的颜色;
 */
void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len,
                  uint8_t size, uint16_t color) {
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++) {
        /* 按总显示位数循环 */
        temp = (num / lcd_pow(10, len - t - 1)) % 10; /* 获取对应位的数字 */

        if (enshow == 0 && t < (len - 1)) {
            /* 没有使能显示, 且还有位要显示 */
            if (temp == 0) {
                /* 显示空格, 占位 */
                lcd_show_char(x + (size / 2) * t, y, ' ', size, 0, color);
                continue; /* 继续下个一位 */
            } else {
                enshow = 1; /* 使能显示 */
            }
        }

        lcd_show_char(x + (size / 2) * t, y, temp + '0', size, 0, color);
    }
}

/**
 * @brief 扩展显示 len 个数字 (高位是 0 也显示)
 *
 * @param x x 坐标
 * @param y y 坐标
 * @param num 数值 (0 ~ 2^32)
 * @param len 显示数字的位数
 * @param size 选择字体 12/16/24/32
 * @param mode 显示模式
 *             bit[7]:   0, 不填充;1, 填充 0.
 *             bit[6:1]: 保留
 *             bit[0]:   0, 非叠加显示;1, 叠加显示.
 * @param color 数字的颜色;
 */
void lcd_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len,
                   uint8_t size, uint8_t mode, uint16_t color) {
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++) {
        /* 按总显示位数循环 */
        temp = (num / lcd_pow(10, len - t - 1)) % 10; /* 获取对应位的数字 */

        if (enshow == 0 && t < (len - 1)) {
            /* 没有使能显示, 且还有位要显示 */
            if (temp == 0) {
                if (mode & 0X80) {
                    /* 高位需要填充 0 */
                    /* 用 0 占位 */
                    lcd_show_char(x + (size / 2) * t, y, '0', size, mode & 0X01,
                                  color);
                } else {
                    /* 用空格占位 */
                    lcd_show_char(x + (size / 2) * t, y, ' ', size, mode & 0X01,
                                  color);
                }

                continue;
            } else {
                enshow = 1; /* 使能显示 */
            }
        }

        lcd_show_char(x + (size / 2) * t, y, temp + '0', size, mode & 0X01,
                      color);
    }
}

/**
 * @brief 显示字符串
 *
 * @param x 起始 x 坐标
 * @param y 起始 y 坐标
 * @param width 区域宽度
 * @param height 区域高度
 * @param size 选择字体 12/16/24/32
 * @param p 字符串首地址
 * @param color 字符串的颜色
 */
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                     uint8_t size, char *p, uint16_t color) {
    uint8_t x0 = x;
    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' ')) {
        /* 判断是不是非法字符!*/
        if (x >= width) {
            x = x0;
            y += size;
        }

        if (y >= height) {
            break; /* 退出 */
        }

        lcd_show_char(x, y, *p, size, 0, color);
        x += size / 2;
        p++;
    }
}

/**
 * @brief 非重叠方式显示字符串
 *
 * @param x 起始 x 坐标
 * @param y 起始 y 坐标
 * @param width 区域宽度
 * @param height 区域高度
 * @param size 选择字体 12/16/24/32
 * @param p 字符串首地址
 * @param color 字符串的颜色
 */
void lcd_show_string_no_overlap(uint16_t x, uint16_t y, uint16_t width,
                                uint16_t height, uint8_t size, char *p,
                                uint16_t color) {
    uint8_t x0 = x;
    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' ')) {
        /* 判断是不是非法字符!*/
        if (x >= width) {
            x = x0;
            y += size;
        }

        if (y >= height) {
            break; /* 退出 */
        }

        lcd_show_char(x, y, *p, size, 1, color);
        x += size / 2;
        p++;
    }
}
