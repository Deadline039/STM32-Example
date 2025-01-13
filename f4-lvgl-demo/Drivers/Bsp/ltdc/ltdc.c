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

#include "../lcd/lcd.h"

LTDC_HandleTypeDef g_ltdc_handle;   /* LTDC 句柄 */
DMA2D_HandleTypeDef g_dma2d_handle; /* DMA2D 句柄 */

/* 定义最大屏分辨率时, LTDC 所需的帧缓存数组大小 */

#if (__ARMCC_VERSION >= 6010050) /* 使用 AC6 编译器 */

/* 根据不同的颜色格式, 定义帧缓存数组 */
#if (LTDC_PIXFORMAT == LTDC_PIXFORMAT_ARGB8888 ||                              \
     LTDC_PIXFORMAT == LTDC_PIXFORMAT_RGB888)
uint32_t ltdc_lcd_framebuf[LTDC_LCD_FRAME_MAX_WIDTH][LTDC_LCD_FRAME_MAX_HEIGHT]
    __attribute__((section(".bss.ARM.__at_0XC0000000")));
#else  /* LTDC_PIXFORMAT */
uint16_t ltdc_lcd_framebuf[LTDC_LCD_FRAME_MAX_WIDTH][LTDC_LCD_FRAME_MAX_HEIGHT]
    __attribute__((section(".bss.ARM.__at_0XC0000000")));
#endif /* LTDC_PIXFORMAT */

#else /* 使用 AC5 编译器时 */

/* 根据不同的颜色格式, 定义帧缓存数组 */
#if (LTDC_PIXFORMAT == LTDC_PIXFORMAT_ARGB8888 ||                              \
     LTDC_PIXFORMAT == LTDC_PIXFORMAT_RGB888)
uint32_t ltdc_lcd_framebuf[LTDC_LCD_FRAME_MAX_WIDTH][LTDC_LCD_FRAME_MAX_HEIGHT]
    __attribute__((at(LTDC_FRAME_BUF_ADDR)));
#else  /* LTDC_PIXFORMAT */
uint16_t ltdc_lcd_framebuf[LTDC_LCD_FRAME_MAX_WIDTH][LTDC_LCD_FRAME_MAX_HEIGHT]
    __attribute__((at(LTDC_FRAME_BUF_ADDR)));
#endif /* LTDC_PIXFORMAT */

#endif /* __ARMCC_VERSION */

/* LTDC LCD 帧缓存数组指针, 必须指向对应大小的内存区域 */
static uint32_t *g_ltdc_framebuf[2];

/* 管理 LCD LTDC 的重要参数 */
ltdc_dev_t lcdltdc;

/**
 * @brief LTDC 开关
 *
 * @param sw 开关状态
 *  @arg - 1: 打开
 *  @arg - 0: 关闭
 */
void ltdc_switch(uint8_t sw) {
    if (sw) {
        __HAL_LTDC_ENABLE(&g_ltdc_handle);
    } else {
        __HAL_LTDC_DISABLE(&g_ltdc_handle);
    }
}

/**
 * @brief LTDC 开关指定层
 *
 * @param layerx 指定层
 *  @arg - 0: 第一层
 *  @arg - 1: 第二层
 * @param sw 开关状态
 *  @arg - 1: 打开
 *  @arg - 0: 关闭
 */
void ltdc_layer_switch(uint8_t layerx, uint8_t sw) {
    if (sw) {
        __HAL_LTDC_LAYER_ENABLE(&g_ltdc_handle, layerx);
    } else {
        __HAL_LTDC_LAYER_DISABLE(&g_ltdc_handle, layerx);
    }

    __HAL_LTDC_RELOAD_CONFIG(&g_ltdc_handle);
}

/**
 * @brief LTDC 选择层
 *
 * @param layerx 指定层
 *  @arg - 0: 第一层
 *  @arg - 1: 第二层
 */
void ltdc_select_layer(uint8_t layerx) {
    lcdltdc.activelayer = layerx;
}

/**
 * @brief LTDC 显示方向设置
 *
 * @param dir 方向
 *  @arg - 0: 竖屏
 *  @arg - 1: 横屏
 */
void ltdc_display_dir(uint8_t dir) {
    lcdltdc.dir = dir; /* 显示方向 */

    if (dir == 0) {
        /* 竖屏 */
        lcdltdc.width = lcdltdc.pheight;
        lcdltdc.height = lcdltdc.pwidth;
    } else if (dir == 1) {
        lcdltdc.width = lcdltdc.pwidth;
        lcdltdc.height = lcdltdc.pheight;
    }
}

/**
 * @brief LTDC 画点函数
 *
 * @param x 写入 x 坐标
 * @param y 写入 y 坐标
 * @param color 颜色值
 */
void ltdc_draw_point(uint16_t x, uint16_t y, uint32_t color) {

#if (LTDC_PIXFORMAT == LTDC_PIXFORMAT_ARGB8888 ||                              \
     LTDC_PIXFORMAT == LTDC_PIXFORMAT_RGB888)
    if (lcdltdc.dir) {
        /* 横屏 */
        *(uint32_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
                      lcdltdc.pixsize * (lcdltdc.pwidth * y + x)) = color;
    } else {
        /* 竖屏 */
        *(uint32_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
                      lcdltdc.pixsize *
                          (lcdltdc.pwidth * (lcdltdc.pheight - x - 1) + y)) =
            color;
    }

#else  /* LTDC_PIXFORMAT */

    if (lcdltdc.dir) {
        /* 横屏 */
        *(uint16_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
                      lcdltdc.pixsize * (lcdltdc.pwidth * y + x)) = color;
    } else {
        /* 竖屏 */
        *(uint16_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
                      lcdltdc.pixsize *
                          (lcdltdc.pwidth * (lcdltdc.pheight - x - 1) + y)) =
            color;
    }
#endif /* LTDC_PIXFORMAT */
}

/**
 * @brief LTDC 读点函数
 *
 * @param x 读取点的 x 坐标
 * @param y 读取点的 y 坐标
 * @return 颜色值
 */
uint32_t ltdc_read_point(uint16_t x, uint16_t y) {

#if (LTDC_PIXFORMAT == LTDC_PIXFORMAT_ARGB8888 ||                              \
     LTDC_PIXFORMAT == LTDC_PIXFORMAT_RGB888)
    if (lcdltdc.dir) {
        /* 横屏 */
        return *(uint32_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
                             lcdltdc.pixsize * (lcdltdc.pwidth * y + x));
    } else {
        /* 竖屏 */
        return *(
            uint32_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
                        lcdltdc.pixsize *
                            (lcdltdc.pwidth * (lcdltdc.pheight - x - 1) + y));
    }

#else /* LTDC_PIXFORMAT */

    if (lcdltdc.dir) {
        /* 横屏 */
        return *(uint16_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
                             lcdltdc.pixsize * (lcdltdc.pwidth * y + x));
    } else {
        /* 竖屏 */
        return *(
            uint16_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
                        lcdltdc.pixsize *
                            (lcdltdc.pwidth * (lcdltdc.pheight - x - 1) + y));
    }

#endif /* LTDC_PIXFORMAT */
}

/**
 * @brief LTDC 填充矩形, DMA2D 填充
 *
 * @param sx 起始 x 坐标
 * @param sy 起始 y 坐标
 * @param ex 结束 x 坐标
 * @param ey 结束 y 坐标
 * @param color 填充的颜色
 * @note `(sx, sy), (ex, ey)`: 填充矩形对角坐标, 区域大小为:
 *       `(ex - sx + 1) * (ey - sy + 1)`
 * @attention 起始坐标不能大于`lcddev.width - 1`;
 *            结束坐标不能大于`lcddev.height - 1`
 */
void ltdc_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
               uint32_t color) {
    /* 以 LCD 面板为基准的坐标系, 不随横竖屏变化而变化 */
    uint32_t psx, psy, pex, pey;
    uint32_t timeout = 0;
    uint16_t offline;
    uint32_t addr;

    /* 坐标系转换 */
    if (lcdltdc.dir) {
        /* 横屏 */
        psx = sx;
        psy = sy;
        pex = ex;
        pey = ey;
    } else {
        /* 竖屏 */
        if (ex >= lcdltdc.pheight) {
            ex = lcdltdc.pheight - 1; /* 限制范围 */
        }
        if (sx >= lcdltdc.pheight) {
            sx = lcdltdc.pheight - 1; /* 限制范围 */
        }

        psx = sy;
        psy = lcdltdc.pheight - ex - 1;
        pex = ey;
        pey = lcdltdc.pheight - sx - 1;
    }

    offline = lcdltdc.pwidth - (pex - psx + 1);
    addr = ((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
            lcdltdc.pixsize * (lcdltdc.pwidth * psy + psx));

    __HAL_RCC_DMA2D_CLK_ENABLE();   /* 使能 DM2D 时钟 */
    DMA2D->CR &= ~(DMA2D_CR_START); /* 先停止 DMA2D */
    DMA2D->CR = DMA2D_R2M;          /* 寄存器到存储器模式 */
    DMA2D->OPFCCR = LTDC_PIXFORMAT; /* 设置颜色格式 */
    DMA2D->OOR = offline;           /* 设置行偏移  */
    DMA2D->OMAR = addr;             /* 输出存储器地址 */
    DMA2D->NLR = (pey - psy + 1) | ((pex - psx + 1) << 16); /* 设定行数寄存器 */
    DMA2D->OCOLR = color;        /* 设定输出颜色寄存器 */
    DMA2D->CR |= DMA2D_CR_START; /* 启动 DMA2D */

    while ((DMA2D->ISR & (DMA2D_FLAG_TC)) == 0) {
        /* 等待传输完成 */
        timeout++;
        if (timeout > 0X1FFFFF) {
            break; /* 超时退出 */
        }
    }
    DMA2D->IFCR |= DMA2D_FLAG_TC; /* 清除传输完成标志 */
}

/**
 * @brief 在指定区域内填充指定颜色块, DMA2D 填充
 *
 * @param sx 起始 x 坐标
 * @param sy 起始 y 坐标
 * @param ex 结束 x 坐标
 * @param ey 结束 y 坐标
 * @param color 填充的颜色数组首地址
 * @note 此函数仅支持 uint16_t, RGB565 格式的颜色数组填充.
 *       `(sx, sy), (ex, ey)`: 填充矩形对角坐标, 区域大小为:
 *       `(ex - sx + 1) * (ey - sy + 1)`
 * @attention 起始坐标不能大于`lcddev.width - 1`;
 *            结束坐标不能大于`lcddev.height - 1`
 */
void ltdc_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                     uint16_t *color) {
    /* 以 LCD 面板为基准的坐标系, 不随横竖屏变化而变化 */
    uint32_t psx, psy, pex, pey;
    uint32_t timeout = 0;
    uint16_t offline;
    uint32_t addr;

    /* 坐标系转换 */
    if (lcdltdc.dir) {
        /* 横屏 */
        psx = sx;
        psy = sy;
        pex = ex;
        pey = ey;
    } else {
        /* 竖屏 */
        psx = sy;
        psy = lcdltdc.pheight - ex - 1;
        pex = ey;
        pey = lcdltdc.pheight - sx - 1;
    }

    offline = lcdltdc.pwidth - (pex - psx + 1);
    addr = ((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] +
            lcdltdc.pixsize * (lcdltdc.pwidth * psy + psx));

    RCC->AHB1ENR |= 1 << 23; /* 使能 DM2D 时钟 */

    DMA2D->CR = 0 << 16;             /* 存储器到存储器模式 */
    DMA2D->FGPFCCR = LTDC_PIXFORMAT; /* 设置颜色格式 */
    DMA2D->FGOR = 0;                 /* 前景层行偏移为 0 */
    DMA2D->OOR = offline;            /* 设置行偏移 */
    DMA2D->CR &= ~(1 << 0);          /* 先停止 DMA2D */
    DMA2D->FGMAR = (uint32_t)color;  /* 源地址 */
    DMA2D->OMAR = addr;              /* 输出存储器地址 */
    DMA2D->NLR = (pey - psy + 1) | ((pex - psx + 1) << 16); /* 设定行数寄存器 */
    DMA2D->CR |= 1 << 0;                                    /* 启动 DMA2D */

    while ((DMA2D->ISR & (1 << 1)) == 0) {
        /* 等待传输完成 */
        timeout++;

        if (timeout > 0X1FFFFF) {
            break; /* 超时退出 */
        }
    }

    DMA2D->IFCR |= 1 << 1; /* 清除传输完成标志 */
}

/**
 * @brief LTCD 清屏
 *
 * @param color 颜色值
 */
void ltdc_clear(uint32_t color) {
    ltdc_fill(0, 0, lcdltdc.width - 1, lcdltdc.height - 1, color);
}

/**
 * @brief LTDC 时钟 (Fdclk) 设置函数
 *
 * @param pllsain SAI 时钟倍频系数 N, 取值范围: 50 ~ 432.
 * @param pllsair SAI 时钟的分频系数 R, 取值范围: 2 ~ 7
 * @param pllsaidivr LCD 时钟分频系数.
 *                   取值范围:0 ~ 3, 对应分频 2^(pllsaidivr + 1)
 * @return 操作状态
 * @retval 0: 成功; 其他: 失败.
 *
 * @note Fvco  = Fin * pllsain;
 *       Fdclk = Fvco /pllsair/ 2 * 2^pllsaidivr
 *             = Fin * pllsain / pllsair / 2 * 2^pllsaidivr
 *       其中: Fvco: VCO 频率
 *            Fin: 输入时钟频率一般为 1Mhz (来自系统时钟 PLLM 分频后的时钟,
 *                 见时钟树图)
 *       假设: 外部晶振为 25M, pllm = 25 的时候, Fin = 1Mhz.
 *       例如: 要得到 33M 的 LTDC 时钟, 则可以设置:
 *            pllsain = 396, pllsair = 3, pllsaidivr = 1
 *            Fdclk= 1 * 396 / 3 / 2 * 2^1 = 396 / 12 = 33Mhz
 */
uint8_t ltdc_clk_set(uint32_t pllsain, uint32_t pllsair, uint32_t pllsaidivr) {
    RCC_PeriphCLKInitTypeDef periphclk_initure;

    /* LTDC 输出像素时钟, 需要根据自己所使用的 LCD 数据手册来配置!*/

    /* LTDC 时钟 */
    periphclk_initure.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    periphclk_initure.PLLSAI.PLLSAIN = pllsain;
    periphclk_initure.PLLSAI.PLLSAIR = pllsair;
    periphclk_initure.PLLSAIDivR = pllsaidivr;

    if (HAL_RCCEx_PeriphCLKConfig(&periphclk_initure) == HAL_OK) {
        /* 配置像素时钟 */
        return 0; /* 成功 */
    } else {
        return 1; /* 失败 */
    }
}

/**
 * @brief LTDC 层窗口设置, 窗口以 LCD 面板坐标系为基准
 *
 * @param layerx 指定层
 *  @arg - 0: 第一层
 *  @arg - 1: 第二层
 * @param sx 起始 x 坐标
 * @param sy 起始 y 坐标
 * @param width 宽度
 * @param height 高度
 * @note 此函数必须在`ltdc_layer_parameter_config`之后再设置.
 *       另外, 当设置的窗口值不等于面板的尺寸时, GRAM 的操作 (读 / 写点函数),
 *       也要根据窗口的宽高来进行修改, 否则显示不正常 (本例程就未做修改).
 */
void ltdc_layer_window_config(uint8_t layerx, uint16_t sx, uint16_t sy,
                              uint16_t width, uint16_t height) {
    /* 设置窗口的位置 */
    HAL_LTDC_SetWindowPosition(&g_ltdc_handle, sx, sy, layerx);
    /* 设置窗口大小 */
    HAL_LTDC_SetWindowSize(&g_ltdc_handle, width, height, layerx);
}

/**
 * @brief LTDC 层基本参数设置
 *
 * @param layerx 指定层
 *  @arg - 0: 第一层
 *  @arg - 1: 第二层
 * @param bufaddr 层颜色帧缓存起始地址
 * @param pixformat 颜色格式
 *  @arg - 0: ARGB8888
 *  @arg - 1: RGB888
 *  @arg - 2: RGB565
 *  @arg - 3: ARGB1555
 *  @arg - 4: ARGB4444
 *  @arg - 5: L8
 *  @arg - 6: AL44
 *  @arg - 7: AL88
 * @param alpha 层颜色 Alpha 值
 *  @arg 0: 全透明; 255: 不透明
 * @param alpha0 默认颜色 Alpha 值
 *  @arg 0: 全透明; 255: 不透明
 * @param bfac1 混合系数 1
 *  @arg - 4(100): 恒定的 Alpha;
 *  @arg - 6(110): 像素 Alpha * 恒定 Alpha
 * @param bfac2 混合系数 2
 *  @arg - 5(101): 恒定的 Alpha;
 *  @arg - 7(111): 像素 Alpha * 恒定 Alpha
 * @param bkcolor 层默认颜色, 32 位, RGB888 格式. 使用RGB565时低 24 位有效.
 * @note 此函数必须在`ltdc_layer_window_config`之后再设置.
 */
void ltdc_layer_parameter_config(uint8_t layerx, uint32_t bufaddr,
                                 uint8_t pixformat, uint8_t alpha,
                                 uint8_t alpha0, uint8_t bfac1, uint8_t bfac2,
                                 uint32_t bkcolor) {
    LTDC_LayerCfgTypeDef playercfg;

    playercfg.WindowX0 = 0;               /* 窗口起始 X 坐标 */
    playercfg.WindowY0 = 0;               /* 窗口起始 Y 坐标 */
    playercfg.WindowX1 = lcdltdc.pwidth;  /* 窗口终止 X 坐标 */
    playercfg.WindowY1 = lcdltdc.pheight; /* 窗口终止 Y 坐标 */
    playercfg.PixelFormat = pixformat;    /* 像素格式 */
    playercfg.Alpha = alpha; /* Alpha 值设置, 0~255, 255 为完全不透明 */
    playercfg.Alpha0 = alpha0;                        /* 默认 Alpha 值 */
    playercfg.BlendingFactor1 = (uint32_t)bfac1 << 8; /* 设置层混合系数 */
    playercfg.BlendingFactor2 = (uint32_t)bfac2; /* 设置层混合系数 */
    playercfg.FBStartAdress = bufaddr; /* 设置层颜色帧缓存起始地址 */
    playercfg.ImageWidth = lcdltdc.pwidth; /* 设置颜色帧缓冲区的宽度 */
    playercfg.ImageHeight = lcdltdc.pheight; /* 设置颜色帧缓冲区的高度 */

    /* 背景颜色红色部分 */
    playercfg.Backcolor.Red = (uint8_t)(bkcolor & 0X00FF0000) >> 16;
    /* 背景颜色绿色部分 */
    playercfg.Backcolor.Green = (uint8_t)(bkcolor & 0X0000FF00) >> 8;
    /* 背景颜色蓝色部分 */
    playercfg.Backcolor.Blue = (uint8_t)bkcolor & 0X000000FF;
    /* 设置所选中的层 */
    HAL_LTDC_ConfigLayer(&g_ltdc_handle, &playercfg, layerx);
}

/**
 * @brief LTDC 读取面板 ID
 *
 * @return 读到的数据
 * @retval - 0: 非法;
 * @retval - 其他: LCD ID
 * @note 利用 LCD RGB 线的最高位 (R7, G7, B7) 来识别面板 ID
 *       PG6 = R7 (M0); PI2 = G7 (M1); PI7 = B7 (M2);
 *       M2:M1:M0
 *       0 :0 :0    4.3  寸 480  * 272 RGB 屏, ID = 0X4342
 *       0 :0 :1    7    寸 800  * 480 RGB 屏, ID = 0X7084
 *       0 :1 :0    7    寸 1024 * 600 RGB 屏, ID = 0X7016
 *       0 :1 :1    7    寸 1280 * 800 RGB 屏, ID = 0X7018
 *       1 :0 :0    4.3  寸 800  * 480 RGB 屏, ID = 0X4384
 *       1 :0 :1    10.1 寸 1280 * 800 RGB 屏, ID = 0X1018
 */
uint16_t ltdc_panelid_read(void) {
    uint8_t idx = 0;

    GPIO_InitTypeDef gpio_init_struct;

    __HAL_RCC_GPIOG_CLK_ENABLE(); /* 使能 GPIOG 时钟 */
    __HAL_RCC_GPIOI_CLK_ENABLE(); /* 使能 GPIOI 时钟 */

    gpio_init_struct.Pin = GPIO_PIN_6;        /* PG6 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;  /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;      /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_HIGH; /* 高速 */
    HAL_GPIO_Init(GPIOG, &gpio_init_struct);  /* 初始化 */

    gpio_init_struct.Pin = GPIO_PIN_2 | GPIO_PIN_7; /* PI2, 7 */
    HAL_GPIO_Init(GPIOI, &gpio_init_struct);        /* 初始化 */

    idx = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6);       /* 读取 M0 */
    idx |= HAL_GPIO_ReadPin(GPIOI, GPIO_PIN_2) << 1; /* 读取 M1 */
    idx |= HAL_GPIO_ReadPin(GPIOI, GPIO_PIN_7) << 2; /* 读取 M2 */

    switch (idx) {
        case 0:
            return 0X4342; /*  4.3 寸屏, 480*272 分辨率 */

        case 1:
            return 0X7084; /*  7  寸屏, 800*480 分辨率 */

        case 2:
            return 0X7016; /*  7  寸屏, 1024*600 分辨率 */

        case 3:
            return 0X7018; /*  7  寸屏, 1280*800 分辨率 */

        case 4:
            return 0X4384; /*  4.3 寸屏, 800*480 分辨率 */

        case 5:
            return 0X1018; /* 10.1 寸屏, 1280*800 分辨率 */

        default:
            return 0;
    }
}

/**
 * @brief LTDC 初始化函数
 *
 */
void ltdc_init(void) {
    uint16_t ltdcid = 0;

    /* 读取 LCD 面板 ID */
    ltdcid = ltdc_panelid_read();

    switch (ltdcid) {

        case 0X4342: {
            lcdltdc.pwidth = 480;  /* 面板宽度, 单位:像素 */
            lcdltdc.pheight = 272; /* 面板高度, 单位:像素 */
            lcdltdc.hsw = 1;       /* 水平同步宽度 */
            lcdltdc.vsw = 1;       /* 垂直同步宽度 */
            lcdltdc.hbp = 40;      /* 水平后廊 */
            lcdltdc.vbp = 8;       /* 垂直后廊 */
            lcdltdc.hfp = 5;       /* 水平前廊 */
            lcdltdc.vfp = 8;       /* 垂直前廊 */
            ltdc_clk_set(288, 4, RCC_PLLSAIDIVR_8); /* 设置像素时钟 9Mhz */
        } break;

        case 0X7084: {
            lcdltdc.pwidth = 800;  /* 面板宽度, 单位:像素 */
            lcdltdc.pheight = 480; /* 面板高度, 单位:像素 */
            lcdltdc.hsw = 1;       /* 水平同步宽度 */
            lcdltdc.vsw = 1;       /* 垂直同步宽度 */
            lcdltdc.hbp = 46;      /* 水平后廊 */
            lcdltdc.vbp = 23;      /* 垂直后廊 */
            lcdltdc.hfp = 210;     /* 水平前廊 */
            lcdltdc.vfp = 22;      /* 垂直前廊 */

            /* 设置像素时 33M (如果开双显, 需要降低 DCLK 到 18.75Mhz,
             * 300/4/4 才会比较好) */
            ltdc_clk_set(396, 3, RCC_PLLSAIDIVR_4);
        } break;

        case 0X7016: {
            lcdltdc.pwidth = 1024; /* 面板宽度, 单位:像素 */
            lcdltdc.pheight = 600; /* 面板高度, 单位:像素 */
            lcdltdc.hsw = 20;      /* 水平同步宽度 */
            lcdltdc.vsw = 3;       /* 垂直同步宽度 */
            lcdltdc.hbp = 140;     /* 水平后廊 */
            lcdltdc.vbp = 20;      /* 垂直后廊 */
            lcdltdc.hfp = 160;     /* 水平前廊 */
            lcdltdc.vfp = 12;      /* 垂直前廊 */
            ltdc_clk_set(360, 2, RCC_PLLSAIDIVR_4); /* 设置像素时钟 45Mhz  */
        } break;

        case 0X7018: {
            lcdltdc.pwidth = 1280; /* 面板宽度, 单位:像素 */
            lcdltdc.pheight = 800; /* 面板高度, 单位:像素 */
            /* 其他参数待定.*/
        } break;

        case 0X4384: {
            lcdltdc.pwidth = 800;  /* 面板宽度, 单位:像素 */
            lcdltdc.pheight = 480; /* 面板高度, 单位:像素 */
            lcdltdc.hbp = 88;      /* 水平后廊 */
            lcdltdc.hfp = 40;      /* 水平前廊 */
            lcdltdc.hsw = 48;      /* 水平同步宽度 */
            lcdltdc.vbp = 32;      /* 垂直后廊 */
            lcdltdc.vfp = 13;      /* 垂直前廊 */
            lcdltdc.vsw = 3;       /* 垂直同步宽度 */
            ltdc_clk_set(396, 3, RCC_PLLSAIDIVR_4); /* 设置像素时钟 33M */
        } break;

        case 0X1018: {
            /* 10.1 寸 1280*800 RGB 屏 */
            lcdltdc.pwidth = 1280; /* 面板宽度, 单位:像素 */
            lcdltdc.pheight = 800; /* 面板高度, 单位:像素 */
            lcdltdc.hbp = 140;     /* 水平后廊 */
            lcdltdc.hfp = 10;      /* 水平前廊 */
            lcdltdc.hsw = 10;      /* 水平同步宽度 */
            lcdltdc.vbp = 10;      /* 垂直后廊 */
            lcdltdc.vfp = 10;      /* 垂直前廊 */
            lcdltdc.vsw = 3;       /* 垂直同步宽度 */
            ltdc_clk_set(360, 2, RCC_PLLSAIDIVR_4); /* 设置像素时钟  45Mhz */
        } break;

        default:
            break;
    }

    lcddev.width = lcdltdc.pwidth;   /* 设置 lcddev 的宽度参数 */
    lcddev.height = lcdltdc.pheight; /* 设置 lcddev 的宽度参数 */

#if (LTDC_PIXFORMAT == LTDC_PIXFORMAT_ARGB8888 ||                              \
     LTDC_PIXFORMAT == LTDC_PIXFORMAT_RGB888)

    g_ltdc_framebuf[0] = (uint32_t *)&ltdc_lcd_framebuf;
    lcdltdc.pixsize = 4; /* 每个像素占 4 个字节 */

#else /* LTDC_PIXFORMAT */

    g_ltdc_framebuf[0] = (uint32_t *)&ltdc_lcd_framebuf;
    // g_ltdc_framebuf [1] = (uint32_t*)&ltdc_lcd_framebuf1;
    lcdltdc.pixsize = 2; /* 每个像素占 2 个字节 */

#endif /* LTDC_PIXFORMAT */

    /* LTDC 配置 */
    g_ltdc_handle.Instance = LTDC;
    g_ltdc_handle.Init.HSPolarity = LTDC_HSPOLARITY_AL; /* 水平同步极性 */
    g_ltdc_handle.Init.VSPolarity = LTDC_VSPOLARITY_AL; /* 垂直同步极性 */
    g_ltdc_handle.Init.DEPolarity = LTDC_DEPOLARITY_AL; /* 数据使能极性 */
    g_ltdc_handle.State = HAL_LTDC_STATE_RESET;

    if (ltdcid == 0X1018) {
        g_ltdc_handle.Init.PCPolarity = LTDC_PCPOLARITY_IIPC; /* 像素时钟极性 */
    } else {
        g_ltdc_handle.Init.PCPolarity = LTDC_PCPOLARITY_IPC; /* 像素时钟极性 */
    }

    g_ltdc_handle.Init.HorizontalSync = lcdltdc.hsw - 1; /* 水平同步宽度 */
    g_ltdc_handle.Init.VerticalSync = lcdltdc.vsw - 1; /* 垂直同步宽度 */
    g_ltdc_handle.Init.AccumulatedHBP =
        lcdltdc.hsw + lcdltdc.hbp - 1; /* 水平同步后沿宽度 */
    g_ltdc_handle.Init.AccumulatedVBP =
        lcdltdc.vsw + lcdltdc.vbp - 1; /* 垂直同步后沿高度 */
    g_ltdc_handle.Init.AccumulatedActiveW =
        lcdltdc.hsw + lcdltdc.hbp + lcdltdc.pwidth - 1; /* 有效宽度 */
    g_ltdc_handle.Init.AccumulatedActiveH =
        lcdltdc.vsw + lcdltdc.vbp + lcdltdc.pheight - 1; /* 有效高度 */

    /* 总宽度 */
    g_ltdc_handle.Init.TotalWidth =
        lcdltdc.hsw + lcdltdc.hbp + lcdltdc.pwidth + lcdltdc.hfp - 1;
    /* 总高度 */
    g_ltdc_handle.Init.TotalHeigh =
        lcdltdc.vsw + lcdltdc.vbp + lcdltdc.pheight + lcdltdc.vfp - 1;

    g_ltdc_handle.Init.Backcolor.Red = 0;   /* 屏幕背景层红色部分 */
    g_ltdc_handle.Init.Backcolor.Green = 0; /* 屏幕背景层绿色部分 */
    g_ltdc_handle.Init.Backcolor.Blue = 0;  /* 屏幕背景色蓝色部分 */
    HAL_LTDC_Init(&g_ltdc_handle);

    /* 层配置 */
    ltdc_layer_parameter_config(0, (uint32_t)g_ltdc_framebuf[0], LTDC_PIXFORMAT,
                                255, 0, 6, 7, 0X000000); /* 第一层参数配置 */
    ltdc_layer_window_config(
        0, 0, 0, lcdltdc.pwidth,
        lcdltdc
            .pheight); /* 层窗口配置, 以 LCD 面板坐标系为基准, 不要随便修改!*/

    // ltdc_layer_parameter_config(1, (uint32_t)g_ltdc_framebuf[1],
    //                             LTDC_PIXFORMAT,
    //                             127, 0, 6, 7, 0X000000);
    // /* 层窗口配置, 以 LCD 面板坐标系为基准, 不要随便修改! */
    // ltdc_layer_window_config(1, 0, 0, lcdltdc.pwidth, lcdltdc.pheight);
    // ltdc_display_dir(0); /* 默认竖屏 */

    ltdc_select_layer(0);   /* 选择第 1 层 */
    LTDC_BL(1);             /* 点亮背光 */
    ltdc_clear(0XFFFFFFFF); /* 清屏 */
}

/**
 * @brief LTDC 底层 IO 初始化和时钟使能
 *
 * @param hltdc LTDC 句柄
 */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc) {
    if (hltdc->Instance != LTDC) {
        return;
    }

    GPIO_InitTypeDef gpio_init_struct;

    __HAL_RCC_LTDC_CLK_ENABLE();  /* 使能 LTDC 时钟 */
    __HAL_RCC_DMA2D_CLK_ENABLE(); /* 使能 DMA2D 时钟 */

    /* 以下是 LTDC 信号控制引脚 BL/DE/VSYNC/HSYNC/CLK 等的配置 */
    CSP_GPIO_CLK_ENABLE(LTDC_BL_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LTDC_DE_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LTDC_VSYNC_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LTDC_HSYNC_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(LTDC_CLK_GPIO_PORT);
    __HAL_RCC_GPIOH_CLK_ENABLE(); /* GPIOH 时钟使能 */

    gpio_init_struct.Pin = LTDC_BL_GPIO_PIN; /* LTDC_BL 引脚模式设置 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP; /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;         /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_HIGH;    /* 高速 */
    HAL_GPIO_Init(CSP_GPIO_PORT(LTDC_BL_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LTDC_DE_GPIO_PIN; /* LTDC_DE 引脚模式设置 */
    gpio_init_struct.Mode = GPIO_MODE_AF_PP; /* 复用 */
    gpio_init_struct.Alternate = GPIO_AF14_LTDC; /* 复用为 LTDC */
    HAL_GPIO_Init(CSP_GPIO_PORT(LTDC_DE_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LTDC_VSYNC_GPIO_PIN; /* LTDC_VSYNC 引脚模式设置 */
    HAL_GPIO_Init(CSP_GPIO_PORT(LTDC_VSYNC_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LTDC_HSYNC_GPIO_PIN; /* LTDC_HSYNC 引脚模式设置 */
    HAL_GPIO_Init(CSP_GPIO_PORT(LTDC_HSYNC_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = LTDC_CLK_GPIO_PIN; /* LTDC_CLK 引脚模式设置 */
    HAL_GPIO_Init(CSP_GPIO_PORT(LTDC_CLK_GPIO_PORT), &gpio_init_struct);

    /* 初始化 PG6, 11 */
    gpio_init_struct.Pin = GPIO_PIN_6 | GPIO_PIN_11;
    HAL_GPIO_Init(GPIOG, &gpio_init_struct);

    /* 初始化 PH9, 10, 11, 12, 13, 14, 15 */
    gpio_init_struct.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
                           GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
                           GPIO_PIN_15;
    HAL_GPIO_Init(GPIOH, &gpio_init_struct);

    /* 初始化 PI0, 1, 2, 4, 5, 6, 7 */
    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 |
                           GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOI, &gpio_init_struct);
}
