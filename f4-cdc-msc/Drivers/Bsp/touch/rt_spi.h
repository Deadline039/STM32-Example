/**
 * @file    rt_spi.c
 * @author  Deadline039
 * @brief   其他电阻屏驱动
 * @version 1.0
 * @date    2025-01-12
 * @warning 私有头文件, 不可以被其他文件包含!
 *
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2025-01-12   1.0         Deadline039 第一次发布
 */

/* 电阻触摸屏控制引脚 */
#define TP_PEN                                                                 \
    HAL_GPIO_ReadPin(CSP_GPIO_PORT(TP_PEN_GPIO_PORT), TP_PEN_GPIO_PIN)
#define TP_MISO                                                                \
    HAL_GPIO_ReadPin(CSP_GPIO_PORT(TP_MISO_GPIO_PORT), TP_MISO_GPIO_PIN)
#define TP_MOSI(x)                                                             \
    x ? HAL_GPIO_WritePin(CSP_GPIO_PORT(TP_MOSI_GPIO_PORT), TP_MOSI_GPIO_PIN,  \
                          GPIO_PIN_SET)                                        \
      : HAL_GPIO_WritePin(CSP_GPIO_PORT(TP_MOSI_GPIO_PORT), TP_MOSI_GPIO_PIN,  \
                          GPIO_PIN_RESET);
#define TP_CLK(x)                                                              \
    x ? HAL_GPIO_WritePin(CSP_GPIO_PORT(TP_CLK_GPIO_PORT), TP_CLK_GPIO_PIN,    \
                          GPIO_PIN_SET)                                        \
      : HAL_GPIO_WritePin(CSP_GPIO_PORT(TP_CLK_GPIO_PORT), TP_CLK_GPIO_PIN,    \
                          GPIO_PIN_RESET);

#define TP_CS(x)                                                               \
    x ? HAL_GPIO_WritePin(CSP_GPIO_PORT(TP_CS_GPIO_PORT), TP_CS_GPIO_PIN,      \
                          GPIO_PIN_SET)                                        \
      : HAL_GPIO_WritePin(CSP_GPIO_PORT(TP_CS_GPIO_PORT), TP_CS_GPIO_PIN,      \
                          GPIO_PIN_RESET);

/**
 * @brief 向触摸屏 IC 写入 1 byte 数据
 *
 * @param data 要写入的数据
 */
void tp_write_byte(uint8_t data) {
    uint8_t count = 0;

    for (count = 0; count < 8; count++) {
        if (data & 0x80) {
            TP_MOSI(1);
        } else {
            TP_MOSI(0);
        }

        data <<= 1;
        TP_CLK(0);
        delay_us(1);
        TP_CLK(1); /* 上升沿有效 */
    }
}

/**
 * @brief 从触摸屏 IC 读取 adc 值
 *
 * @param cmd 指令
 * @return 读取到的数据, ADC 值 (12bit)
 */
uint16_t tp_read_ad(uint8_t cmd) {
    uint8_t count = 0;
    uint16_t num = 0;
    TP_CLK(0);          /* 先拉低时钟 */
    TP_MOSI(0);         /* 拉低数据线 */
    TP_CS(0);           /* 选中触摸屏 IC */
    tp_write_byte(cmd); /* 发送命令字 */
    delay_us(6);        /* ADS7846 的转换时间最长为 6 us */
    TP_CLK(0);
    delay_us(1);
    TP_CLK(1); /* 给 1 个时钟, 清除 BUSY */
    delay_us(1);
    TP_CLK(0);

    for (count = 0; count < 16; count++) {
        /* 读出 16 位数据,只有高 12 位有效 */
        num <<= 1;
        TP_CLK(0); /* 下降沿有效 */
        delay_us(1);
        TP_CLK(1);

        if (TP_MISO) {
            num++;
        }
    }

    num >>= 4; /* 只有高 12 位有效. */
    TP_CS(1);  /* 释放片选 */
    return num;
}

/* 电阻触摸驱动芯片数据采集, 滤波用参数 */
#define TP_READ_TIMES 5 /* 读取次数 */
#define TP_LOST_VAL   1 /* 丢弃值 */

/**
 * @brief 读取一个坐标值 (x 或者 y)
 *
 * @param cmd 指令
 *   @arg `0xD0`: 读取 X 轴坐标 (竖屏状态, 横屏状态和 Y 对调.)
 *   @arg `0x90`: 读取 Y 轴坐标 (竖屏状态, 横屏状态和 X 对调.)
 * @return 读取到的数据 (滤波后的), ADC 值 (12bit)
 * @note 连续读取`TP_READ_TIMES 次数据,对这些数据升序排列,
 *       然后去掉最低和最高`TP_LOST_VAL`个数.
 *       取平均值设置时需满足: `TP_READ_TIMES > 2 * TP_LOST_VAL`的条件
 */
uint16_t tp_read_xoy(uint8_t cmd) {
    uint16_t i, j;
    uint16_t buf[TP_READ_TIMES];
    uint16_t sum = 0;
    uint16_t temp;

    for (i = 0; i < TP_READ_TIMES; i++) {
        /* 先读取 TP_READ_TIMES 次数据 */
        buf[i] = tp_read_ad(cmd);
    }

    for (i = 0; i < TP_READ_TIMES - 1; i++) {
        /* 对数据进行排序 */

        for (j = i + 1; j < TP_READ_TIMES; j++) {
            if (buf[i] > buf[j]) {
                /* 升序排列 */
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }

    sum = 0;

    for (i = TP_LOST_VAL; i < TP_READ_TIMES - TP_LOST_VAL; i++) {
        /* 去掉两端的丢弃值 */
        sum += buf[i]; /* 累加去掉丢弃值以后的数据. */
    }

    temp = sum / (TP_READ_TIMES - 2 * TP_LOST_VAL); /* 取平均值 */
    return temp;
}

/**
 * @brief 读取 x, y 坐标
 *
 * @param[out] x 读取到的 x 坐标值
 * @param[out] y 读取到的 y 坐标值
 */
void tp_read_xy(uint16_t *x, uint16_t *y) {
    uint16_t xval, yval;

    if (tp_dev.touchtype & 0X01) {
        /* X, Y 方向与屏幕相反 */
        xval = tp_read_xoy(0X90); /* 读取 X 轴坐标 AD 值, 并进行方向变换 */
        yval = tp_read_xoy(0XD0); /* 读取 Y 轴坐标 AD 值 */
    } else {
        /* X,Y 方向与屏幕相同 */
        xval = tp_read_xoy(0XD0); /* 读取 X 轴坐标 AD 值 */
        yval = tp_read_xoy(0X90); /* 读取 Y 轴坐标 AD 值 */
    }

    *x = xval;
    *y = yval;
}

/* 连续两次读取 X, Y 坐标的数据误差最大允许值 */
#define TP_ERR_RANGE 50 /* 误差范围 */

/**
 * @brief 连续读取 2 次触摸 IC 数据,并滤波
 *
 * @param[out] x 读取到的 x 坐标值
 * @param[out] y 读取到的 y 坐标值
 * @return 读取状态
 * @retval 0: 失败; 1: 成功
 * @note 连续 2 次读取触摸屏 IC, 且这两次的偏差不能超过`TP_ERR_RANGE`.
 *       满足条件, 则认为读数正确; 否则读数错误. 该函数能大大提高准确度.
 */
uint8_t tp_read_xy2(uint16_t *x, uint16_t *y) {
    uint16_t x1, y1;
    uint16_t x2, y2;

    tp_read_xy(&x1, &y1); /* 读取第一次数据 */
    tp_read_xy(&x2, &y2); /* 读取第二次数据 */

    /* 前后两次采样在 +-TP_ERR_RANGE 内 */
    if (((x2 <= x1 && x1 < x2 + TP_ERR_RANGE) ||
         (x1 <= x2 && x2 < x1 + TP_ERR_RANGE)) &&
        ((y2 <= y1 && y1 < y2 + TP_ERR_RANGE) ||
         (y1 <= y2 && y2 < y1 + TP_ERR_RANGE))) {
        *x = (x1 + x2) / 2;
        *y = (y1 + y2) / 2;
        return 1;
    }

    return 0;
}

/**
 * @brief 触摸按键扫描
 *
 * @param mode 坐标模式
 *   @arg - 0: 屏幕坐标
 *   @arg - 1: 物理坐标 (校准等特殊场合用)
 * @return 是否有触摸
 * @retval - 0: 触屏无触摸
 * @retval - 1: 触屏有触摸
 */
uint8_t tp_scan(uint8_t mode) {
    if (TP_PEN == 0) {
        /* 有按键按下 */
        if (mode) {
            /* 读取物理坐标,无需转换 */
            tp_read_xy2(&tp_dev.x[0], &tp_dev.y[0]);
        } else if (tp_read_xy2(&tp_dev.x[0], &tp_dev.y[0])) {
            /* 读取屏幕坐标,需要转换 */

            /* 将 X 轴物理坐标转换成逻辑坐标 (即对应 LCD 屏幕上面的 X 坐标值) */
            tp_dev.x[0] = (signed short)(tp_dev.x[0] - tp_dev.adj_data.xc) /
                              (int16_t)tp_dev.adj_data.xfac +
                          lcddev.width / 2;

            /* 将 Y 轴物理坐标转换成逻辑坐标 (即对应 LCD 屏幕上面的 Y 坐标值) */
            tp_dev.y[0] = (signed short)(tp_dev.y[0] - tp_dev.adj_data.yc) /
                              (int16_t)tp_dev.adj_data.yfac +
                          lcddev.height / 2;
        }

        if ((tp_dev.sta & TP_PRES_DOWN) == 0) {
            /* 之前没有被按下 */
            tp_dev.sta = TP_PRES_DOWN | TP_CATH_PRES; /* 按键按下 */

            /* 记录第一次按下时的坐标 */
            tp_dev.x[CT_MAX_TOUCH - 1] = tp_dev.x[0];
            tp_dev.y[CT_MAX_TOUCH - 1] = tp_dev.y[0];
        }
    } else {
        if (tp_dev.sta & TP_PRES_DOWN) {
            /* 之前是被按下的 */
            tp_dev.sta &= ~TP_PRES_DOWN; /* 标记按键松开 */
        } else {
            /* 之前就没有被按下 */
            tp_dev.x[CT_MAX_TOUCH - 1] = 0;
            tp_dev.y[CT_MAX_TOUCH - 1] = 0;
            tp_dev.x[0] = 0xFFFF;
            tp_dev.y[0] = 0xFFFF;
        }
    }
    /* 返回当前的触屏状态 */
    return tp_dev.sta & TP_PRES_DOWN;
}
