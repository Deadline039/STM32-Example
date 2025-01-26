/**
 * @file        touch.h
 * @author      正点原子团队 (ALIENTEK)
 * @version     V1.1
 * @date        2022-04-20
 * @brief       触摸屏 驱动代码
 * @copyright   2020-2032, 广州市星翼电子科技有限公司
 * @note        支持电阻 / 电容式触摸屏触摸屏驱动
 *              支持 ADS7843/7846/UH7843/7846/XPT2046/TSC2046/
 *              GT9147/GT9271/FT5206 等
 *
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2022-04-20   1.0         Alientek    第一次发布
 * 2023-06-07   1.1         Alientek    1. 新增对 ST7796 3.5 寸屏 GT1151 的支持
 *                                      2. 新增对 ILI9806 4.3 寸屏 GT1151 的支持
 * 2025-01-12   1.2         Deadline039 抽离其他电阻屏代码到独立的文件, 方便管理
 */

#include "touch.h"
#include "../core/core_delay.h"
#include "../lcd/lcd.h"
#include <stdio.h>
#include <string.h>

#include "ct_iic.h"
#include "ft5206.h"
#include "gt9xxx.h"
#include "rt_spi.h"

void tp_adjust(void);
uint8_t tp_scan(uint8_t mode);
uint8_t tp_init(void);

tp_dev_t tp_dev = {.init = tp_init, .adjust = tp_adjust, .scan = tp_scan};

/*****************************************************************************
 * @defgroup 触摸屏校准数据保存
 * @{
 */

#if TP_SAVE_ADJ_DATA
#include "../at24cxx/at24cxx.h"
extern at24cxx_handle_t at24c02_handle;
#endif /* TP_SAVE_ADJ_DATA */

/**
 * @brief 保存校准参数
 *
 * @param data 写入的数据
 * @param len 写入长度
 * @note 参数默认保存在 EEPROM 芯片里面 (24C02), 起始地址为
 *       `TP_SAVE_ADJ_ADDR`. 占用大小为 13 字节
 *       可以修改或者重定向此函数以支持其他存储芯片
 */
__weak void tp_save_adjust_data(const uint8_t *data, uint16_t len) {
#if TP_SAVE_ADJ_DATA
    at24cxx_write(&at24c02_handle, TP_SAVE_ADJ_ADDR, data, len);
#endif /* TP_SAVE_ADJ_DATA */
}

/**
 * @brief 获取保存在 EEPROM 里面的校准值
 *
 * @param[out] data 读取数据的缓冲区
 * @param len 读取长度
 * @note 参数默认保存在 EEPROM 芯片里面 (24C02), 起始地址为
 *       `TP_SAVE_ADJ_ADDR`. 占用大小为 13 字节
 *       可以修改或者重定向此函数以支持其他存储芯片
 */
__weak void tp_read_adjust_data(uint8_t *data, uint16_t len) {
#if TP_SAVE_ADJ_DATA
    at24cxx_read(&at24c02_handle, TP_SAVE_ADJ_ADDR, data, len);
#endif /* TP_SAVE_ADJ_DATA */
}

/**
 * @}
 */

/*****************************************************************************
 * @defgroup 触摸屏校准
 * @{
 */

/**
 * @brief 画一个校准用的触摸点 (十字架)
 *
 * @param x x 坐标
 * @param x y 坐标
 * @param color 颜色
 */
static void tp_draw_touch_point(uint16_t x, uint16_t y, uint16_t color) {
    lcd_draw_line(x - 12, y, x + 13, y, color); /* 横线 */
    lcd_draw_line(x, y - 12, x, y + 13, color); /* 竖线 */
    lcd_draw_point(x + 1, y + 1, color);
    lcd_draw_point(x - 1, y + 1, color);
    lcd_draw_point(x + 1, y - 1, color);
    lcd_draw_point(x - 1, y - 1, color);
    lcd_draw_circle(x, y, 6, color); /* 画中心圈 */
}

/**
 * @brief 画一个大点 (2 * 2 的点)
 *
 * @param x x 坐标
 * @param x y 坐标
 * @param color 颜色
 */
void tp_draw_big_point(uint16_t x, uint16_t y, uint16_t color) {
    lcd_draw_point(x, y, color); /* 中心点 */
    lcd_draw_point(x + 1, y, color);
    lcd_draw_point(x, y + 1, color);
    lcd_draw_point(x + 1, y + 1, color);
}

/* 提示字符串 */
char *const TP_REMIND_MSG_TBL =
    "Please use the stylus click the cross on the screen. The cross will "
    "always move until the screen adjustment is completed. ";

/**
 * @brief 提示校准结果 (各个参数)
 *
 * @param xy 5 个物理坐标值
 * @param px x 方向的比例因子 (约接近 1 越好)
 * @param py y 方向的比例因子 (约接近 1 越好)
 */
static void tp_adjust_info_show(uint16_t xy[5][2], double px, double py) {
    uint8_t i;
    char sbuf[20];

    for (i = 0; i < 5; i++) {
        /* 显示 5 个物理坐标值 */
        sprintf(sbuf, "x% d:% d", i + 1, xy[i][0]);
        lcd_show_string(40, 160 + (i * 20), lcddev.width, lcddev.height, 16,
                        sbuf, RED);
        sprintf(sbuf, "y% d:% d", i + 1, xy[i][1]);
        lcd_show_string(40 + 80, 160 + (i * 20), lcddev.width, lcddev.height,
                        16, sbuf, RED);
    }

    /* 显示 X/Y 方向的比例因子 */
    lcd_fill(40, 160 + (i * 20), lcddev.width - 1, 16,
             WHITE); /* 清除之前的 px,py 显示 */
    sprintf(sbuf, "px:%0.2f", px);
    sbuf[7] = 0; /* 添加结束符 */
    lcd_show_string(40, 160 + (i * 20), lcddev.width, lcddev.height, 16, sbuf,
                    RED);
    sprintf(sbuf, "py:%0.2f", py);
    sbuf[7] = 0; /* 添加结束符 */
    lcd_show_string(40 + 80, 160 + (i * 20), lcddev.width, lcddev.height, 16,
                    sbuf, RED);
}

/**
 * @brief 触摸屏校准代码
 *
 * @note 使用五点校准法 (具体原理请百度)
 *       本函数得到`x 轴 /y 轴`比例因子`xfac/yfac`及物理中心坐标值`(xc,yc)`
 *       等 4 个参数.
 *       我们规定: 物理坐标即 AD 采集到的坐标值, 范围是 0 ~ 4095.
 *       逻辑坐标即 LCD 屏幕的坐标, 范围为 LCD 屏幕的分辨率.
 */
void tp_adjust(void) {
    if (tp_dev.touchtype & (1 << 7)) {
        /* 电容屏, 不需要校准 */
        return;
    }

    uint16_t pxy[5][2]; /* 物理坐标缓存值 */
    uint8_t cnt = 0;
    short s1, s2, s3, s4; /* 4 个点的坐标差值 */
    double px, py; /* X,Y 轴物理坐标比例,用于判定是否校准成功 */
    uint16_t outtime = 0;
    cnt = 0;

    lcd_clear(WHITE); /* 清屏 */

    /* 显示提示信息 */
    lcd_show_string(40, 40, 160, 100, 16, TP_REMIND_MSG_TBL, RED);
    tp_draw_touch_point(20, 20, RED); /* 画点 1 */
    tp_dev.sta = 0;                   /* 消除触发信号 */

    while (1) {
        /* 如果连续 10 秒钟没有按下,则自动退出 */
        tp_dev.scan(1); /* 扫描物理坐标 */

        if ((tp_dev.sta & 0xc000) == TP_CATH_PRES) {
            /* 按键按下了一次 (此时按键松开了.) */
            outtime = 0;
            tp_dev.sta &= ~TP_CATH_PRES; /* 标记按键已经被处理过了. */

            pxy[cnt][0] = tp_dev.x[0]; /* 保存 X 物理坐标 */
            pxy[cnt][1] = tp_dev.y[0]; /* 保存 Y 物理坐标 */
            cnt++;

            switch (cnt) {
                case 1:
                    /* 清除点 1 */
                    tp_draw_touch_point(20, 20, WHITE);
                    /* 画点 2 */
                    tp_draw_touch_point(lcddev.width - 20, 20, RED);
                    break;

                case 2:
                    /* 清除点 2 */
                    tp_draw_touch_point(lcddev.width - 20, 20, WHITE);
                    /* 画点 3 */
                    tp_draw_touch_point(20, lcddev.height - 20, RED);
                    break;

                case 3:
                    /* 清除点 3 */
                    tp_draw_touch_point(20, lcddev.height - 20, WHITE);
                    /* 画点 4 */
                    tp_draw_touch_point(lcddev.width - 20, lcddev.height - 20,
                                        RED);
                    break;

                case 4:
                    lcd_clear(WHITE); /* 画第五个点了,直接清屏 */
                                      /* 画点 5 */
                    tp_draw_touch_point(lcddev.width / 2, lcddev.height / 2,
                                        RED);
                    break;

                case 5: /* 全部 5 个点已经得到 */
                    s1 = pxy[1][0] - pxy[0][0]; /* 第 2 个点和第 1 个点的 X
                                                   轴物理坐标差值 (AD 值) */
                    s3 = pxy[3][0] - pxy[2][0]; /* 第 4 个点和第 3 个点的 X
                                                   轴物理坐标差值 (AD 值) */
                    s2 = pxy[3][1] - pxy[1][1]; /* 第 4 个点和第 2 个点的 Y
                                                   轴物理坐标差值 (AD 值) */
                    s4 = pxy[2][1] - pxy[0][1]; /* 第 3 个点和第 1 个点的 Y
                                                   轴物理坐标差值 (AD 值) */

                    px = (double)s1 / s3; /* X 轴比例因子 */
                    py = (double)s2 / s4; /* Y 轴比例因子 */

                    if (px < 0) {
                        px = -px; /* 负数改正数 */
                    }
                    if (py < 0) {
                        py = -py; /* 负数改正数 */
                    }

                    if (px < 0.95 || px > 1.05 || py < 0.95 ||
                        py > 1.05 || /* 比例不合格 */
                        abs(s1) > 4095 || abs(s2) > 4095 || abs(s3) > 4095 ||
                        abs(s4) > 4095 || /* 差值不合格,大于坐标范围 */
                        abs(s1) == 0 || abs(s2) == 0 || abs(s3) == 0 ||
                        abs(s4) == 0 /* 差值不合格,等于 0 */
                    ) {
                        cnt = 0;
                        /* 清除点 5 */
                        tp_draw_touch_point(lcddev.width / 2, lcddev.height / 2,
                                            WHITE);
                        /* 重新画点 1 */
                        tp_draw_touch_point(20, 20, RED);
                        /* 显示当前信息,方便找问题 */
                        tp_adjust_info_show(pxy, px, py);
                        continue;
                    }

                    tp_dev.adj_data.xfac =
                        (float)(s1 + s3) / (2 * (lcddev.width - 40));
                    tp_dev.adj_data.yfac =
                        (float)(s2 + s4) / (2 * (lcddev.height - 40));

                    tp_dev.adj_data.xc = pxy[4][0]; /* X 轴,物理中心坐标 */
                    tp_dev.adj_data.yc = pxy[4][1]; /* Y 轴,物理中心坐标 */

                    lcd_clear(WHITE); /* 清屏 */

                    /* 校正完成 */
                    lcd_show_string(35, 110, lcddev.width, lcddev.height, 16,
                                    "Touch Screen Adjust OK!", BLUE);
                    delay_ms(1000);
                    tp_dev.adj_data.adj_flag = 0x0A;
                    tp_save_adjust_data(&tp_dev.adj_data,
                                        sizeof(tp_dev.adj_data));

                    lcd_clear(WHITE); /* 清屏 */

                    /* 校正完成 */
                    return;

                default:
                    break;
            }
        }

        delay_ms(10);
        outtime++;

        if (outtime > 1000) {
            tp_read_adjust_data(&tp_dev.adj_data, sizeof(tp_dev.adj_data));
            break;
        }
    }
}

/**
 * @}
 */

/*****************************************************************************
 * @defgroup 触摸屏其他函数
 * @{
 */

/**
 * @brief 触摸屏初始化
 *
 * @return 是否校准过
 * @retval - 0: 没有进行校准
 * @retval - 1: 进行校准
 */
uint8_t tp_init(void) {
    GPIO_InitTypeDef gpio_init_struct;

    tp_dev.touchtype = 0; /* 默认设置 (电阻屏 & 竖屏) */
    tp_dev.touchtype |= lcddev.dir & 0X01; /* 根据 LCD 判定是横屏还是竖屏 */

    switch (lcddev.id) {
        case 0x7796:
            /* 3.5 寸屏有两种,一种屏幕 ID 为 0x5510 带电阻触摸屏;
             * 一种屏幕 ID  为 0x7796 带 GT 型号的电容触摸屏 */

            if (gt9xxx_init() == 0) {
                /* 初始化 GT 系列触摸屏成功,即当前 3.5 寸屏为电容触摸屏 */

                tp_dev.scan = gt9xxx_scan; /* 扫描函数指向 GT9147 触摸屏扫描 */
                tp_dev.touchtype |= 0X80; /* 电容屏 */
                return 0;
            }
            break;

        case 0X5510:
        case 0X4342:
        case 0X1018:
        case 0X4384:
        case 0X9806:
            /* 电容触摸屏, 4.3 寸 / 10.1 寸屏 */
            gt9xxx_init();
            tp_dev.scan = gt9xxx_scan; /* 扫描函数指向 GT9147 触摸屏扫描 */
            tp_dev.touchtype |= 0X80; /* 电容屏 */
            return 0;

        case 0X1963:
        case 0X7084:
        case 0X7016:
            /* SSD1963 7 寸屏或者 7 寸 800*480/1024*600 RGB 屏 */
            if (!ft5206_init()) {
                /* 触摸 IC 是 FT 系列的就执行 ft5206_init
                 * 函数以及使用 ft5206_scan 扫描函数 */
                tp_dev.scan = ft5206_scan; /* 扫描函数指向 FT5206 触摸屏扫描 */
            } else {
                /* 触摸 IC 是 GT 系列的就执行 gt9xxx_init 函数以及使用
                 * gt9xxx_scan 扫描函数 */
                gt9xxx_init();
                tp_dev.scan = gt9xxx_scan; /* 扫描函数指向 GT9147 触摸屏扫描 */
            }
            tp_dev.touchtype |= 0X80; /* 电容屏 */
            return 0;

        default:
            break;
    }

    CSP_GPIO_CLK_ENABLE(TP_PEN_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(TP_CS_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(TP_MISO_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(TP_MOSI_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(TP_CLK_GPIO_PORT);

    gpio_init_struct.Pin = TP_PEN_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;            /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; /* 高速 */
    HAL_GPIO_Init(CSP_GPIO_PORT(TP_PEN_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = TP_MISO_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(TP_MISO_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = TP_MOSI_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;        /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; /* 高速 */
    HAL_GPIO_Init(CSP_GPIO_PORT(TP_MOSI_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = TP_CLK_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(TP_CLK_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = TP_CS_GPIO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(TP_CS_GPIO_PORT), &gpio_init_struct);

    tp_read_xy(&tp_dev.x[0], &tp_dev.y[0]); /* 第一次读取初始化 */

    tp_read_adjust_data(&tp_dev.adj_data, sizeof(tp_dev.adj_data));
    if (tp_dev.adj_data.adj_flag == 0x0A) {
        return 0; /* 已经校准 */
    } else {
        /* 未校准 */
        lcd_clear(WHITE); /* 清屏 */
        tp_adjust();      /* 屏幕校准 */
    }
    tp_read_adjust_data(&tp_dev.adj_data, sizeof(tp_dev.adj_data));

    return 1;
}

/**
 * @}
 */
