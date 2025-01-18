/**
 * @file        lcd.h
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

#ifndef __LCD_H
#define __LCD_H

#include <CSP_Config.h>

#include "../core/core_delay.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 是否使用 FSMC 外设. 对于 STM32F103, 100Pin 以上的芯片才支持
 * 不使用 FSMC 时按照正点原子 F103 Mini 板的 IO 编译;
 * 使用 FSMC 时按照正点原子 F103 精英板的 IO 编译.
 * 要使用其他 IO 自行修改 */
#define LCD_USE_FSMC 0

/*****************************************************************************
 * @defgroup LCD RST/WR/RD/BL/CS/RS 引脚 定义
 * @{
 */

#if LCD_USE_FSMC == 1

/* LCD_D0 ~ D15, 由于引脚太多就不在这里定义了, 直接在 lcd_init 里面修改.
 * 所以在移植的时候, 除了改这 6 个 IO 口, 还得改 lcd_init 里面的 D0 ~ D15 所在的
 * IO 口. */

/* RESET 和系统复位脚共用 所以这里不用定义 RESET 引脚 */
// #define LCD_RST_GPIO_PORT X
// #define LCD_RST_GPIO_PIN  GPIO_PIN_X

#define LCD_WR_GPIO_PORT D
#define LCD_WR_GPIO_PIN  GPIO_PIN_5

#define LCD_RD_GPIO_PORT D
#define LCD_RD_GPIO_PIN  GPIO_PIN_4

#define LCD_BL_GPIO_PORT B
#define LCD_BL_GPIO_PIN  GPIO_PIN_0

/* LCD_CS (需要根据 LCD_FSMC_NEX 设置正确的 IO 口) */
#define LCD_CS_GPIO_PORT G
#define LCD_CS_GPIO_PIN  GPIO_PIN_12

/* LCD_RS (需要根据 LCD_FSMC_AX 设置正确的 IO 口) 引脚 定义 */
#define LCD_RS_GPIO_PORT G
#define LCD_RS_GPIO_PIN  GPIO_PIN_0

/**
 * FSMC 相关参数 定义
 * 注意:我们默认是通过 FSMC 块 1 来连接 LCD, 块 1 有 4 个片选: FSMC_NE1 ~ 4
 *
 * 修改 LCD_FSMC_NEx, 对应的 LCD_CS_GPIO 相关设置也得改
 * 修改 LCD_FSMC_Ax , 对应的 LCD_RS_GPIO 相关设置也得改
 */

/* 使用 FSMC_NEx 接 LCD_CS, 取值范围只能是: 1 ~ 4 */
#define LCD_FSMC_NEX     4
#define LCD_FSMC_NSBANK  FSMC_NORSRAM_BANK4

/* 使用 FSMC_Ax 接 LCD_RS, 取值范围是: 0 ~ 25 */
#define LCD_FSMC_AX      10

/* BCR 寄存器 */
#define LCD_FSMC_BCRX    FSMC_Bank1->BTCR[(LCD_FSMC_NEX - 1) * 2]
/* BTR 寄存器 */
#define LCD_FSMC_BTRX    FSMC_Bank1->BTCR[(LCD_FSMC_NEX - 1) * 2 + 1]
/* BWTR 寄存器 */
#define LCD_FSMC_BWTRX   FSMC_Bank1E->[(LCD_FSMC_NEX - 1) * 2]

#else /* LCD_USE_FSMC */

/* RESET 和系统复位脚共用 所以这里不用定义 RESET 引脚 */
// #define LCD_RST_GPIO_PORT X
// #define LCD_RST_GPIO_PIN  GPIO_PIN_X

#define LCD_BL_GPIO_PORT   C
#define LCD_BL_GPIO_PIN    GPIO_PIN_10

#define LCD_WR_GPIO_PORT   C
#define LCD_WR_GPIO_PIN    GPIO_PIN_7

#define LCD_RD_GPIO_PORT   C
#define LCD_RD_GPIO_PIN    GPIO_PIN_6

/* LCD_CS */
#define LCD_CS_GPIO_PORT   C
#define LCD_CS_GPIO_PIN    GPIO_PIN_9

/* LCD_RS */
#define LCD_RS_GPIO_PORT   C
#define LCD_RS_GPIO_PIN    GPIO_PIN_8

/* LCD_DATA 引脚, PB 端口的 16 个 IO 都需要用 */
#define LCD_DATA_GPIO_PORT B
#define LCD_DATA_GPIO_PIN  GPIO_PIN_All

/* LCD 端口控制函数定义, 利用操作寄存器的方式控制IO引脚提高屏幕的刷新率 */

/* 设置 WR 引脚 */
#define LCD_WR(x)                                                              \
    (CSP_GPIO_PORT(LCD_WR_GPIO_PORT)->BSRR = LCD_WR_GPIO_PIN << (16 * (!x)))
/* 设置 RD 引脚 */
#define LCD_RD(x)                                                              \
    (CSP_GPIO_PORT(LCD_RD_GPIO_PORT)->BSRR = LCD_RD_GPIO_PIN << (16 * (!x)))
/* 设置 CS 引脚 */
#define LCD_CS(x)                                                              \
    (CSP_GPIO_PORT(LCD_CS_GPIO_PORT)->BSRR = LCD_CS_GPIO_PIN << (16 * (!x)))
/* 设置 RS 引脚 */
#define LCD_RS(x)                                                              \
    (CSP_GPIO_PORT(LCD_RS_GPIO_PORT)->BSRR = LCD_RS_GPIO_PIN << (16 * (!x)))

/* 写 B0 ~ B15 引脚 */
#define LCD_DATA_OUT(x) (CSP_GPIO_PORT(LCD_DATA_GPIO_PORT)->ODR = x)
/* 读 B0 ~ B15 引脚 */
#define LCD_DATA_IN     (CSP_GPIO_PORT(LCD_DATA_GPIO_PORT)->IDR)

#endif /* LCD_USE_FSMC */

/* 设置 BL 引脚 */
#define LCD_BL(x)                                                              \
    (CSP_GPIO_PORT(LCD_BL_GPIO_PORT)->BSRR = LCD_BL_GPIO_PIN << (16 * (!x)))

/**
 * @}
 */

/*****************************************************************************
 * @defgroup LCD 参数控制
 * @{
 */

/**
 * @brief LCD 参数结构体
 */
typedef struct {
    uint16_t width;   /*!< LCD 宽度 */
    uint16_t height;  /*!< LCD 高度 */
    uint16_t id;      /*!< LCD ID */
    uint16_t wramcmd; /*!< 开始写 gram 指令 */
    uint16_t setxcmd; /*!< 设置 x 坐标指令 */
    uint16_t setycmd; /*!< 设置 y 坐标指令 */
    uint8_t dir;      /*!< 横屏还是竖屏控制: 0-竖屏; 1-横屏. */
} lcd_dev_t;

extern lcd_dev_t lcddev; /* 管理 LCD 参数 */

/* LCD 的画笔颜色和背景色 */
extern uint32_t g_point_color; /* 默认红色 */
extern uint32_t g_back_color;  /* 背景颜色, 默认为白色 */

#if LCD_USE_FSMC == 1

/**
 * @brief LCD 地址结构体
 *
 */
typedef struct {
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_RAM;
} LCD_TypeDef;

/**
 * LCD_BASE 的详细解算方法:
 * 我们一般使用 FSMC 的块 1 (BANK1) 来驱动 TFTLCD 液晶屏 (MCU 屏),
 * 块 1 地址范围总大小为 256MB, 均分成 4 块:存储块 1 (FSMC_NE1) 地址范围: 0X6000
 * 0000 ~ 0X63FF FFFF 存储块 2 (FSMC_NE2) 地址范围: 0X6400 0000 ~ 0X67FF FFFF
 * 存储块 3 (FSMC_NE3) 地址范围: 0X6800 0000 ~ 0X6BFF FFFF
 * 存储块 4 (FSMC_NE4) 地址范围: 0X6C00 0000 ~ 0X6FFF FFFF
 *
 * 我们需要根据硬件连接方式选择合适的片选 (连接 LCD_CS) 和地址线 (连接 LCD_RS)
 * 开发板使用 FSMC_NE4 连接 LCD_CS, FSMC_A6 连接 LCD_RS , 16
 * 位数据线, 计算方法如下: 首先 FSMC_NE4 的基地址为: 0X6C00 0000; NEx 的基址为
 * (x=1/2/3/4): 0X6000 0000 + (0X400 0000 * (x - 1)) FSMC_A6 对应地址值:
 *  2^6 * 2 = 0X80; FSMC_Ay 对应的地址为 (y = 0 ~ 25): 2^y * 2
 *
 * LCD->LCD_REG, 对应 LCD_RS = 0 (LCD 寄存器); LCD->LCD_RAM, 对应 LCD_RS = 1
 * (LCD 数据) 则 LCD->LCD_RAM 的地址为:  0X6C00 0000 + 2^6 * 2 = 0X6C00 0080
 *    LCD->LCD_REG 的地址可以为 LCD->LCD_RAM 之外的任意地址.
 * 由于我们使用结构体管理 LCD_REG 和 LCD_RAM (REG 在前, RAM 在后, 均为 16
 * 位数据宽度) 因此 结构体的基地址 (LCD_BASE) = LCD_RAM - 2 = 0X6C00 0080 -2
 *
 * 更加通用的计算公式为 ((片选脚 FSMC_NEx) x=1/2/3/4,
 * (RS 接地址线 FSMC_Ay, y=0~25):
 * LCD_BASE = (0X6000 0000 + (0X400 0000 * (x - 1))) | (2 ^ y * 2 -2)
 * 等效于 (使用移位操作)
 * LCD_BASE = (0X6000 0000 + (0X400 0000 * (x - 1))) | ((1 << y) * 2 * - 2)
 */
#define LCD_BASE                                                               \
    (uint32_t)((0X60000000 + (0X4000000 * (LCD_FSMC_NEX - 1))) |               \
               (((1 << LCD_FSMC_AX) * 2) - 2))

#define LCD ((LCD_TypeDef *)LCD_BASE)

#endif /* LCD_USE_FSMC */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup LCD 扫描方向和颜色
 * @{
 */

/* 扫描方向定义 */
#define L2R_U2D             0 /* 从左到右, 从上到下 */
#define L2R_D2U             1 /* 从左到右, 从下到上 */
#define R2L_U2D             2 /* 从右到左, 从上到下 */
#define R2L_D2U             3 /* 从右到左, 从下到上 */

#define U2D_L2R             4 /* 从上到下, 从左到右 */
#define U2D_R2L             5 /* 从上到下, 从右到左 */
#define D2U_L2R             6 /* 从下到上, 从左到右 */
#define D2U_R2L             7 /* 从下到上, 从右到左 */

#define DFT_SCAN_DIR        L2R_U2D /* 默认的扫描方向 */

/* 常用画笔颜色 */
#define WHITE               0xFFFF /* 白色 */
#define BLACK               0x0000 /* 黑色 */
#define RED                 0xF800 /* 红色 */
#define GREEN               0x07E0 /* 绿色 */
#define BLUE                0x001F /* 蓝色 */
#define MAGENTA             0xF81F /* 品红色 / 紫红色 = BLUE + RED */
#define YELLOW              0xFFE0 /* 黄色 = GREEN + RED */
#define CYAN                0x07FF /* 青色 = GREEN + BLUE */

/* 非常用颜色 */
#define BROWN               0xBC40 /* 棕色 */
#define BRRED               0xFC07 /* 棕红色 */
#define GRAY                0x8430 /* 灰色 */
#define DARKBLUE            0x01CF /* 深蓝色 */
#define LIGHTBLUE           0x7D7C /* 浅蓝色 */
#define GRAYBLUE            0x5458 /* 灰蓝色 */
#define LIGHTGREEN          0x841F /* 浅绿色 */
#define LGRAY               0xC618 /* 浅灰色 (PANNEL), 窗体背景色 */
#define LGRAYBLUE           0xA651 /* 浅灰蓝色 (中间层颜色) */
#define LBBLUE              0x2B12 /* 浅棕蓝色 (选择条目的反色) */

/******************************************************************************************/
/* SSD1963 相关配置参数 (一般不用改) */

/* LCD 分辨率设置 */
#define SSD_HOR_RESOLUTION  800 /* LCD 水平分辨率 */
#define SSD_VER_RESOLUTION  480 /* LCD 垂直分辨率 */

/* LCD 驱动参数设置 */
#define SSD_HOR_PULSE_WIDTH 1   /* 水平脉宽 */
#define SSD_HOR_BACK_PORCH  46  /* 水平前廊 */
#define SSD_HOR_FRONT_PORCH 210 /* 水平后廊 */

#define SSD_VER_PULSE_WIDTH 1  /* 垂直脉宽 */
#define SSD_VER_BACK_PORCH  23 /* 垂直前廊 */
#define SSD_VER_FRONT_PORCH 22 /* 垂直前廊 */

/* 如下几个参数, 自动计算 */
#define SSD_HT              (SSD_HOR_RESOLUTION + SSD_HOR_BACK_PORCH + SSD_HOR_FRONT_PORCH)
#define SSD_HPS             (SSD_HOR_BACK_PORCH)
#define SSD_VT              (SSD_VER_RESOLUTION + SSD_VER_BACK_PORCH + SSD_VER_FRONT_PORCH)
#define SSD_VPS             (SSD_VER_BACK_PORCH)

/**
 * @}
 */

/*****************************************************************************
 * @defgroup LCD 公开接口
 * @{
 */

#if LCD_USE_FSMC == 1

void lcd_wr_data(volatile uint16_t data);
/* 为了兼容不使用 FSMC 的情况 */
#define lcd_wr_xdata lcd_wr_data

#else /* LCD_USE_FSMC */

#define lcd_wr_data(data)                                                      \
    {                                                                          \
        LCD_RS(1);                                                             \
        LCD_CS(0);                                                             \
        LCD_DATA_OUT(data);                                                    \
        LCD_WR(0);                                                             \
        LCD_WR(1);                                                             \
        LCD_CS(1);                                                             \
    }
void lcd_wr_xdata(uint16_t data);

#endif /* LCD_USE_FSMC */

void lcd_wr_regno(volatile uint16_t regno);
void lcd_write_reg(uint16_t regno, uint16_t data);

void lcd_init(void);
void lcd_display_on(void);
void lcd_display_off(void);
void lcd_scan_dir(uint8_t dir);
void lcd_display_dir(uint8_t dir);
void lcd_ssd_backlight_set(uint8_t pwm);

void lcd_write_ram_prepare(void);
void lcd_set_cursor(uint16_t x, uint16_t y);
uint32_t lcd_read_point(uint16_t x, uint16_t y);
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color);

void lcd_clear(uint16_t color);
void lcd_fill_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color);
void lcd_set_window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
              uint32_t color);
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                    uint16_t *color);
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                   uint16_t color);
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                        uint16_t color);

void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode,
                   uint16_t color);
void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len,
                  uint8_t size, uint16_t color);
void lcd_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len,
                   uint8_t size, uint8_t mode, uint16_t color);
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                     uint8_t size, char *p, uint16_t color);
void lcd_show_string_no_overlap(uint16_t x, uint16_t y, uint16_t width,
                                uint16_t height, uint8_t size, char *p,
                                uint16_t color);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LCD_H */
