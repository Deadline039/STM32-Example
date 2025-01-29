/**
 * @file        touch.h
 * @author      正点原子团队 (ALIENTEK)
 * @version     V1.2
 * @date        2022-04-20
 * @brief       触摸屏 驱动代码
 * @note        支持电阻 / 电容式触摸屏触摸屏驱动
 *              支持 ADS7843/7846/UH7843/7846/XPT2046/TSC2046/
 *              GT9147/GT9271/FT5206 等
 * @copyright   2020-2032, 广州市星翼电子科技有限公司
 *
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2022-04-20   1.0         Alientek    第一次发布
 * 2023-06-07   1.1         Alientek    1. 新增对 ST7796 3.5 寸屏 GT1151 的支持
 *                                      2. 新增对 ILI9806 4.3 寸屏 GT1151 的支持
 * 2025-01-12   1.2         Deadline039 抽离其他电阻屏代码到独立的文件, 方便管理
 */

#ifndef __TOUCH_H
#define __TOUCH_H

#include <CSP_Config.h>

/*****************************************************************************
 * @defgroup 电阻触摸屏驱动 IC TP_PEN/TP_CS/TP_MISO/TP_MOSI/T_SCK 引脚 定义
 * @note 正点原子电阻触摸屏的 SPI 引脚并不是接在 STM32 的 SPI 外设上,
 *       所以这里使用软件 SPI
 * @{
 */

#define TP_PEN_GPIO_PORT  H
#define TP_PEN_GPIO_PIN   GPIO_PIN_7

#define TP_CS_GPIO_PORT   I
#define TP_CS_GPIO_PIN    GPIO_PIN_8

#define TP_MISO_GPIO_PORT G
#define TP_MISO_GPIO_PIN  GPIO_PIN_3

#define TP_MOSI_GPIO_PORT I
#define TP_MOSI_GPIO_PIN  GPIO_PIN_3

#define TP_CLK_GPIO_PORT  H
#define TP_CLK_GPIO_PIN   GPIO_PIN_6

/**
 * @}
 */

/*****************************************************************************
 * @defgroup 触摸屏参数
 * @{
 */

#define TP_PRES_DOWN      0x8000 /* 触屏被按下 */
#define TP_CATH_PRES      0x4000 /* 有按键按下了 */
#define CT_MAX_TOUCH      10     /* 电容屏支持的点数 */

/**
 * 是否存储校准数据, 需要外部 ROM 支持. 当然存储到 STM32 的内部 Flash
 * 也是可以的.
 * 默认存储到 AT24C02 中,
 * 可以到`tp_save_adjust_data`和`tp_get_adjust_data`中修改.
 */
#define TP_SAVE_ADJ_DATA  1
/* 保存校准值的位置 */
#define TP_SAVE_ADJ_ADDR  40

/**
 * @brief 5 点校准触摸屏校准参数 (电容屏不需要校准)
 */
typedef struct __attribute__((packed)) {
    float xfac;       /*!< 5 点校准法 x 方向比例因子 */
    float yfac;       /*!< 5 点校准法 y 方向比例因子 */
    short xc;         /*!< 中心 X 坐标物理值 (AD 值) */
    short yc;         /*!< 中心 Y 坐标物理值 (AD 值) */
    uint8_t adj_flag; /*!< 校准标识位, 校准过为 0x0A */
} tp_adj_data_t;

/**
 * @brief 触摸屏参数
 */
typedef struct {
    /**
     * @brief 初始化触摸屏控制器
     *
     * @return 是否校准过
     * @retval - 0: 没有进行校准
     * @retval - 1: 进行校准
     */
    uint8_t (*init)(void);

    /**
     * @brief 扫描触摸屏
     *
     * @param mode 扫描模式
     *  @arg - 0: 屏幕扫描
     *  @arg - 1: 物理坐标
     * @return 是否有触摸
     * @retval - 0: 触屏无触摸
     * @retval - 1: 触屏有触摸
     */
    uint8_t (*scan)(uint8_t /* mode */);

    /**
     * @brief 触摸屏校准 (只有电阻屏需要)
     *
     */
    void (*adjust)(void);

    /* 电容屏支持多点触控, 最多有 10 组坐标.
     * 电阻屏中 x[0], y[0]代表此次扫描时的点坐标;
     * x[9], y[9]代表第一次按下时的坐标.  */
    uint16_t x[CT_MAX_TOUCH]; /*!< x坐标 */
    uint16_t y[CT_MAX_TOUCH]; /*!< y坐标 */

    /*!< 笔的状态
     *   bit[15]:     0: 松开; 1: 按下
     *   bit[14]:     0: 没有按键按下; 1: 有按键按下
     *   bit[13:10]:  保留
     *   bit[9:0]:    电容触摸屏按下的点数 */
    uint16_t sta;

    tp_adj_data_t adj_data; /*!< 触摸屏校准参数 */

    /*!< 新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
     * bit[7]:      0: 电阻屏; 1: 电容屏
     * bit[6:1]:    保留.
     * bit[0]:      0: 竖屏 (适合左右为 X 坐标, 上下为 Y 坐标的 TP)
     *              1: 横屏 (适合左右为 Y 坐标, 上下为 X 坐标的 TP)
     */
    uint8_t touchtype;
} tp_dev_t;

/* 触屏控制器在 touch.c 里面定义 */
extern tp_dev_t tp_dev;

/**
 * @}
 */

/*****************************************************************************
 * @defgroup 公开接口
 * @{
 */

uint8_t tp_init(void);
void tp_adjust(void);
void tp_save_adjust_data(const uint8_t *data, uint16_t len);
void tp_read_adjust_data(uint8_t *data, uint16_t len);
void tp_draw_big_point(uint16_t x, uint16_t y, uint16_t color);

/**
 * @}
 */

#endif /* __TOUCH_H */
