/**
 * @file        ltdc.h
 * @author      正点原子团队 (ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       LTDC 驱动代码
 * @copyright   2020-2032, 广州市星翼电子科技有限公司
 *
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2022-04-20   1.0         Alientek    第一次发布
 */

#ifndef __LTDC_H
#define __LTDC_H

#include <CSP_Config.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define LTDC_LCD_FRAME_MAX_WIDTH  1200
#define LTDC_LCD_FRAME_MAX_HEIGHT 800

/*****************************************************************************
 * @defgroup LTDC 参数控制
 * @{
 */

/**
 * @brief LTDC 设备参数结构体
 */
typedef struct {
    uint32_t pwidth; /*!< LTDC 面板的宽度, 固定参数, 不随显示方向改变. */
    uint32_t pheight; /*!< LTDC 面板的高度,固定参数,不随显示方向改变 */
    uint16_t hsw;        /*!< 水平同步宽度 */
    uint16_t vsw;        /*!< 垂直同步宽度 */
    uint16_t hbp;        /*!< 水平后廊 */
    uint16_t vbp;        /*!< 垂直后廊 */
    uint16_t hfp;        /*!< 水平前廊 */
    uint16_t vfp;        /*!< 垂直前廊  */
    uint8_t activelayer; /*!< 当前层编号 0/1 */
    uint8_t dir;         /*!< 屏幕方向. 0-竖屏; 1-横屏 */
    uint16_t width;      /*!< LTDC 宽度 */
    uint16_t height;     /*!< LTDC 高度 */
    uint32_t pixsize;    /*!< 每个像素所占字节数 */
} ltdc_dev_t;

/* 管理 LCD LTDC 参数 */
extern ltdc_dev_t lcdltdc;

extern LTDC_HandleTypeDef g_ltdc_handle;   /* LTDC 句柄 */
extern DMA2D_HandleTypeDef g_dma2d_handle; /* DMA2D 句柄 */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup LTDC_BL/DE/VSYNC/HSYNC/CLK 引脚 定义
 * @note LTDC_R3 ~ R7, G2 ~ G7, B3 ~ B7, 由于引脚太多就不在这里定义了. 直接在
 *       ltcd_init 里面修改. 所以在移植的时候, 除了改这几个 IO 口, 还得改
 *       ltcd_init 里面引脚.
 * @{
 */

/* BL 和 MCU 屏背光脚共用 所以这里不用定义 BL 引脚 */
#define LTDC_BL_GPIO_PORT       B
#define LTDC_BL_GPIO_PIN        GPIO_PIN_5

#define LTDC_DE_GPIO_PORT       F
#define LTDC_DE_GPIO_PIN        GPIO_PIN_10

#define LTDC_VSYNC_GPIO_PORT    I
#define LTDC_VSYNC_GPIO_PIN     GPIO_PIN_9

#define LTDC_HSYNC_GPIO_PORT    I
#define LTDC_HSYNC_GPIO_PIN     GPIO_PIN_10

#define LTDC_CLK_GPIO_PORT      G
#define LTDC_CLK_GPIO_PIN       GPIO_PIN_7

/* 定义默认背景层颜色 */
#define LTDC_BACKLAYERCOLOR     0X00000000

/* LTDC 帧缓冲区首地址, 这里定义在 SDRAM 里面. AC6需要修改 ltdc.c 中的代码 */
#define LTDC_FRAME_BUF_ADDR     0XC0000000

#define LTDC_PIXFORMAT_ARGB8888 0X00 /* ARGB8888 格式 */
#define LTDC_PIXFORMAT_RGB888   0X01 /* RGB888 格式 */
#define LTDC_PIXFORMAT_RGB565   0X02 /* RGB565 格式 */
#define LTDC_PIXFORMAT_ARGB1555 0X03 /* ARGB1555 格式 */
#define LTDC_PIXFORMAT_ARGB4444 0X04 /* ARGB4444 格式 */
#define LTDC_PIXFORMAT_L8       0X05 /* L8 格式 */
#define LTDC_PIXFORMAT_AL44     0X06 /* AL44 格式 */
#define LTDC_PIXFORMAT_AL88     0X07 /* AL88 格式 */

/* LTDC 背光控制 */
#define LTDC_BL(X)                                                             \
    X ? HAL_GPIO_WritePin(CSP_GPIO_PORT(LTDC_BL_GPIO_PORT), LTDC_BL_GPIO_PIN,  \
                          GPIO_PIN_SET)                                        \
      : HAL_GPIO_WritePin(CSP_GPIO_PORT(LTDC_BL_GPIO_PORT), LTDC_BL_GPIO_PIN,  \
                          GPIO_PIN_RESET);

void ltdc_switch(uint8_t sw);
void ltdc_layer_switch(uint8_t layerx, uint8_t sw);
void ltdc_select_layer(uint8_t layerx);
void ltdc_display_dir(uint8_t dir);
void ltdc_draw_point(uint16_t x, uint16_t y, uint32_t color);
uint32_t ltdc_read_point(uint16_t x, uint16_t y);
void ltdc_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
               uint32_t color);
void ltdc_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                     uint16_t *color);
void ltdc_clear(uint32_t color);
uint8_t ltdc_clk_set(uint32_t pllsain, uint32_t pllsair, uint32_t pllsaidivr);
void ltdc_layer_window_config(uint8_t layerx, uint16_t sx, uint16_t sy,
                              uint16_t width, uint16_t height);
void ltdc_layer_parameter_config(uint8_t layerx, uint32_t bufaddr,
                                 uint8_t pixformat, uint8_t alpha,
                                 uint8_t alpha0, uint8_t bfac1, uint8_t bfac2,
                                 uint32_t bkcolor);
uint16_t ltdc_panelid_read(void);
void ltdc_init(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LTDC_H */
