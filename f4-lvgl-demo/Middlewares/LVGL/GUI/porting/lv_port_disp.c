/**
 * @file lv_port_disp.c
 *
 */

/* Copy this file as "lv_port_disp.c" and set this value to "1" to enable
 * content*/
#if 1

/*********************
 *      INCLUDES
 *********************/

#include "lv_port_disp.h"
#include <lvgl.h>

#include <bsp.h>

/*********************
 *      DEFINES
 *********************/

/* 使用外部 sram 为1, 否则为0 */
#define USE_SRAM        0

/**
 * LVGL 需要一个缓冲区用来绘制小部件
 * 随后, 这个缓冲区的内容会通过显示设备的 `flush_cb`(显示设备刷新函数)
 * 复制到显示设备上 这个缓冲区的大小需要大于显示设备一行的大小
 *
 * 这里有3中缓冲配置:
 * 1. 单缓冲区:
 *      LVGL 会将显示设备的内容绘制到这里, 并将他写入显示设备.
 *
 * 2. 双缓冲区:
 *      LVGL 会将显示设备的内容绘制到其中一个缓冲区, 并将他写入显示设备.
 *      需要使用 DMA 将要显示在显示设备的内容写入缓冲区.
 *      当数据从第一个缓冲区发送时, 它将使 LVGL 能够将屏幕的下一部分绘制到
 *      另一个缓冲区. 这样使得渲染和刷新可以并行执行.
 *
 * 3. 全尺寸双缓冲区
 *      设置两个屏幕大小的全尺寸缓冲区, 并且设置 disp_drv.full_refresh = 1.
 *      这样, LVGL将始终以`flush_cb`的形式提供整个渲染屏幕,
 *      您只需更改帧缓冲区的地址.
 */
#define LV_BUF_MODE     1

/* 使用 DMA2D 中断, 仅限 RGB 屏, 使用 MCU 屏不要打开此宏定义 */
#define LV_USE_DMA2D_IT 0

/* 可选: GPU 接口
 * 如果你的 MCU 有硬件加速器 (GPU) 那么你可以使用它来为内存填充颜色 */
#define LV_USE_GPU      0

#define MY_DISP_HOR_RES (800) /* 屏幕宽度 */
#define MY_DISP_VER_RES (480) /* 屏幕高度 */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/* 显示设备初始化函数 */
static void disp_init(void);
/* 显示设备刷新函数 */
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                       lv_color_t *color_p);
#if LV_USE_GPU
/* GPU 填充函数 (使用GPU时, 需要实现) */
static void gpu_fill(lv_disp_drv_t *disp_drv, lv_color_t *dest_buf,
                     lv_coord_t dest_width, const lv_area_t *fill_area,
                     lv_color_t color);
#endif /* LV_USE_GPU */

/**********************
 *  STATIC VARIABLES
 **********************/

#if LV_USE_DMA2D_IT
static volatile uint8_t lv_gpu_state;
#endif /* LV_USE_DMA2D_IT */

static lv_disp_drv_t disp_drv; /* 显示设备的描述符 */

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @brief LCD 加速绘制函数
 *
 * @param sx 起始 x 坐标
 * @param sy 起始 y 坐标
 * @param ex 终点 x 坐标
 * @param ey 终点 y 坐标
 * @param color 填充的颜色数组首地址
 * @note 区域大小为:`(ex - sx + 1) * (ey - sy + 1)`
 */
void lcd_draw_fast_rgb_color(int16_t sx, int16_t sy, int16_t ex, int16_t ey,
                             uint16_t *color) {
    uint16_t w = ex - sx + 1;
    uint16_t h = ey - sy + 1;

    lcd_set_window(sx, sy, w, h);
    uint32_t draw_size = w * h;
    lcd_write_ram_prepare();

    for (uint32_t i = 0; i < draw_size; i++) {
        lcd_wr_data(color[i]);
    }
}

/**
 * @brief 初始化并注册显示设备
 *
 */
void lv_port_disp_init(void) {
    /*-------------------------
     * 初始化显示设备
     * -----------------------*/
    disp_init();

    static lv_disp_draw_buf_t draw_buf_dsc;

    /*-----------------------------
     * 创建一个绘图缓冲区
     *----------------------------*/

#if LV_BUF_MODE == 1

    /* 单缓冲区示例 */
#if USE_SRAM
    /* 设置缓冲区的大小为屏幕的全尺寸大小 */
    static lv_color_t buf_1 =
        mymalloc(SRAMEX, MY_DISP_HOR_RES * MY_DISP_VER_RES);

    /* 初始化显示缓冲区 */
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL,
                          MY_DISP_HOR_RES * MY_DISP_VER_RES);
#else  /* USE_SRAM */
    /* 设置缓冲区的大小为 10 行屏幕的大小 */
    static lv_color_t buf_1[MY_DISP_HOR_RES * 10];
    /* 初始化显示缓冲区 */
    lv_disp_draw_buf_init(&draw_buf_dsc, buf_1, NULL, MY_DISP_HOR_RES * 10);
#endif /* USE_SRAM */

#elif LV_BUF_MODE == 2

    /* 双缓冲区示例, 设置缓冲区的大小为 10 行屏幕的大小 */
    static lv_color_t buf_2_1[MY_DISP_HOR_RES * 10];
    /* 设置另一个缓冲区的大小为 10 行屏幕的大小 */
    static lv_color_t buf_2_2[MY_DISP_HOR_RES * 10];
    /* 初始化显示缓冲区 */
    lv_disp_draw_buf_init(&draw_buf_dsc, buf_2_1, buf_2_2,
                          MY_DISP_HOR_RES * 10);

#elif LV_BUF_MODE == 3

    /* 全尺寸双缓冲区, 占用空间非常恐怖, 把它放在外部 SDRAM 中.
     * 并且在下面设置 disp_drv.full_refresh = 1 */
#if (__ARMCC_VERSION >= 6010050) /* 使用 AC6 编译器 */
    /**
     * 外部 SDRAM 地址: 0xC0000000 为起始地址, 预留 1280 * 800 * 4 byte 空间作为
     * RGB LCD 的显示缓冲区. 最大尺寸 1280 * 800, 最大色深 RGB888 (uint32_t)
     * 根据实际情况裁剪.
     */

    /* 设置一个全尺寸的缓冲区 */
    static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES]
        __attribute__((section(".bss.ARM.__at_0xC03A9800")));
    /* 设置另一个全尺寸的缓冲区 */
    static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES]
        __attribute__((section(".bss.ARM.__at_0xC0753000")));

#else /* 使用 AC5 编译器 */

    /* 设置一个全尺寸的缓冲区 */
    static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES]
        __attribute__((at(0xC03A9800)));
    /* 设置另一个全尺寸的缓冲区 */
    static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES]
        __attribute__((at(0xC0753000)));

#endif /* __ARMCC_VERSION */

    /* 初始化显示缓冲区 */
    lv_disp_draw_buf_init(&draw_buf_dsc, buf_3_1, buf_3_2,
                          MY_DISP_HOR_RES * MY_DISP_VER_RES);

#else /* LV_BUF_MODE */
#error "Unknow LV_BUF_MODE! "
#endif /* LV_BUF_MODE */

    /*-----------------------------------
     * 在 LVGL 中注册显示设备
     *----------------------------------*/

    lv_disp_drv_init(&disp_drv); /* 初始化为默认值 */

    /* 建立访问显示设备的函数  */

    /* 设置显示设备的分辨率
     * 这里为了适配正点原子的多款屏幕, 采用了动态获取的方式,
     * 在实际项目中, 通常所使用的屏幕大小是固定的, 因此可以直接设置为屏幕的大小
     */
    disp_drv.hor_res = lcddev.width;
    disp_drv.ver_res = lcddev.height;

    /* 用来将缓冲区的内容复制到显示设备 */
    disp_drv.flush_cb = disp_flush;

    /* 设置显示缓冲区 */
    disp_drv.draw_buf = &draw_buf_dsc;

#if LV_BUF_MODE == 3
    /* 全尺寸双缓冲区示例 */
    disp_drv.full_refresh = 1;
#endif /* LV_BUF_MODE == 3 */

    /* 如果您有GPU, 请使用颜色填充内存阵列
     * 注意, 你可以在 lv_conf.h 中使能 LVGL 内置支持的 GPUs
     * 但如果你有不同的 GPU, 那么可以使用这个回调函数.  */
    // disp_drv.gpu_fill_cb = gpu_fill;

    /* 注册显示设备 */
    lv_disp_drv_register(&disp_drv);
}

#if LV_USE_DMA2D_IT

/**
 * @brief DMA2D 中断服务函数
 *
 */
void DMA2D_IRQHandler(void) {
    HAL_DMA2D_IRQHandler(&dma2d_handle);
}

/**
 * @brief DMA2D 中断传输完成回调
 *
 * @param hdma2d
 */
static void dma2d_cplt_callback(DMA2D_HandleTypeDef *hdma2d) {
    UNUSED(hdma2d);
    /* 刷新显示设备 */
    if (lv_gpu_state == 1) {
        lv_gpu_state = 0;
        lv_disp_flush_ready(&disp_drv);
    }
}
#endif /* LV_USE_DMA2D_IT */

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * @brief 初始化显示设备和必要的外围设备
 *
 */
static void disp_init(void) {
    lcd_init();         /* 初始化 LCD */
    lcd_display_dir(1); /* 设置横屏 */

#if LV_USE_DMA2D_IT
    /* 打开 DMA2D 中断 */
    HAL_NVIC_SetPriority(DMA2D_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(DMA2D_IRQn);

    HAL_DMA2D_RegisterCallback(&dma2d_handle, HAL_DMA2D_TRANSFERCOMPLETE_CB_ID,
                               dma2d_cplt_callback);
#endif /* LV_USE_DMA2D_IT */
}

/**
 * @brief 将内部缓冲区的内容刷新到显示屏上的特定区域
 *
 * @param disp_drv 显示设备
 * @param area 要刷新的区域, 包含了填充矩形的对角坐标
 * @param color_p 颜色数组
 * @note 可以使用 DMA 或者任何硬件在后台加速执行这个操作
 *       但是, 需要在刷新完成后调用函数`lv_disp_flush_ready()`
 */
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                       lv_color_t *color_p) {
#if LV_USE_DMA2D_IT
    uint32_t off_line_src = lcddev.width - (area->x2 - area->x1 + 1);
    uint32_t addr =
        LTDC_FRAME_BUF_ADDR + 2 * (lcddev.width * area->y1 + area->x1);
    /* 中断传输, 内存到内存 */
    DMA2D->CR = 0x00000000UL | (1 << 9);
    /* 源地址 */
    DMA2D->FGMAR = (uint32_t)(uint16_t *)(color_p);
    /* 目标地址 */
    DMA2D->OMAR = (uint32_t)addr;
    /* 输入偏移 */
    DMA2D->FGOR = 0;
    /* 输出偏移 */
    DMA2D->OOR = off_line_src;

    /* 前景层和输出区域都采用的 RGB565 颜色格式 */
    DMA2D->FGPFCCR = DMA2D_OUTPUT_RGB565;
    DMA2D->OPFCCR = DMA2D_OUTPUT_RGB565;
    /* 多少行 */
    DMA2D->NLR = (area->y2 - area->y1 + 1) | ((area->x2 - area->x1 + 1) << 16);

    /* 开启中断 */
    DMA2D->CR |= DMA2D_IT_TC | DMA2D_IT_TE | DMA2D_IT_CE;
    /* 启动传输 */
    DMA2D->CR |= DMA2D_CR_START;
    lv_gpu_state = 1;
#else  /* LV_USE_DMA2D_IT */
    /* 在指定区域内填充指定颜色块 */
    lcd_color_fill(area->x1, area->y1, area->x2, area->y2, (uint16_t *)color_p);
    /* MCU 屏幕可以使用下面的方式加速 */
    // lcd_draw_fast_rgb_color(area->x1,area->y1,area->x2,area->y2,(uint16_t*)color_p);

    /* 重要!!! 通知图形库, 已经刷新完毕了 */
    lv_disp_flush_ready(disp_drv);
#endif /* LV_USE_DMA2D_IT */
}

#if LV_USE_GPU
/**
 * @brief 使用 GPU 进行颜色填充
 *
 * @param disp_drv 显示设备
 * @param dest_buf 目标缓冲区
 * @param dest_width 目标缓冲区的宽度
 * @param fill_area 填充的区域
 * @param color 颜色数组
 * @note 如有 MCU 有硬件加速器 (GPU), 那么可以用它来为内存进行颜色填充
 */
static void gpu_fill(lv_disp_drv_t *disp_drv, lv_color_t *dest_buf,
                     lv_coord_t dest_width, const lv_area_t *fill_area,
                     lv_color_t color) {
    /* It's an example code which should be done by your GPU */
    int32_t x, y;
    dest_buf += dest_width * fill_area->y1; /* Go to the first line */

    for (y = fill_area->y1; y <= fill_area->y2; y++) {
        for (x = fill_area->x1; x <= fill_area->x2; x++) {
            dest_buf[x] = color;
        }
        dest_buf += dest_width; /* Go to the next line */
    }
}

#endif /* LV_USE_GPU */

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
