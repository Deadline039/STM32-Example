/**
 * @file        gt9xxx.h
 * @author      正点原子团队 (ALIENTEK)
 * @version     V1.1
 * @date        2022-04-20
 * @brief       4.3 寸电容触摸屏 - GT9xxx 驱动代码
 * @note        GT 系列电容触摸屏 IC 通用驱动,本代码支持:
 *              GT9147/GT917S/GT968/GT1151/GT9271 等多种驱动 IC, 这些驱动 IC 仅
 *              ID 不一样,具体代码基本不需要做任何修改即可通过本代码直接驱动
 * @warning     私有头文件, 不可以被其他文件包含
 * @copyright   2020-2032, 广州市星翼电子科技有限公司
 *
 *****************************************************************************
 * Change Logs:
 * Date         Version     Author      Notes
 * 2022-04-20   1.0         Alientek    第一次发布
 * 2023-06-07   1.1         Alientek    1. 新增对 ST7796 3.5 寸屏,
 *                                         ILI9806 4.3 寸屏 GT1151 的支持
 *                                      2. gt9xxx_init 函数中增加触摸 IC 判定,
 *                                         不属于特定触摸 IC 就返回 1 初始化失败
 */

/* 注意:除了 GT9271 支持 10 点触摸之外,其他触摸芯片只支持 5 点触摸 */
uint8_t g_gt_tnum = 5; /* 默认支持的触摸屏点数 (5 点触摸) */

/*****************************************************************************
 * @defgroup GT9xxx IO 与寄存器定义 (不包括 I2C 引脚)
 * @{
 */

#define GT9XXX_RST_GPIO_PORT I
#define GT9XXX_RST_GPIO_PIN  GPIO_PIN_8

#define GT9XXX_INT_GPIO_PORT H
#define GT9XXX_INT_GPIO_PIN  GPIO_PIN_7

#define GT9XXX_RST(x)                                                          \
    x ? HAL_GPIO_WritePin(CSP_GPIO_PORT(GT9XXX_RST_GPIO_PORT),                 \
                          GT9XXX_RST_GPIO_PIN, GPIO_PIN_SET)                   \
      : HAL_GPIO_WritePin(CSP_GPIO_PORT(GT9XXX_RST_GPIO_PORT),                 \
                          GT9XXX_RST_GPIO_PIN, GPIO_PIN_RESET);

#define GT9XXX_INT                                                             \
    HAL_GPIO_ReadPin(CSP_GPIO_PORT(GT9XXX_INT_GPIO_PORT), GT9XXX_INT_GPIO_PIN)

/* IIC 读写命令 */
#define GT9XXX_CMD_WR    0X28 /* 写命令 */
#define GT9XXX_CMD_RD    0X29 /* 读命令 */

/* GT9XXX 部分寄存器定义  */
#define GT9XXX_CTRL_REG  0X8040 /* GT9XXX 控制寄存器 */
#define GT9XXX_CFGS_REG  0X8047 /* GT9XXX 配置起始地址寄存器 */
#define GT9XXX_CHECK_REG 0X80FF /* GT9XXX 校验和寄存器 */
#define GT9XXX_PID_REG   0X8140 /* GT9XXX 产品 ID 寄存器 */

#define GT9XXX_GSTID_REG 0X814E /* GT9XXX 当前检测到的触摸情况 */
#define GT9XXX_TP1_REG   0X8150 /* 第一个触摸点数据地址 */
#define GT9XXX_TP2_REG   0X8158 /* 第二个触摸点数据地址 */
#define GT9XXX_TP3_REG   0X8160 /* 第三个触摸点数据地址 */
#define GT9XXX_TP4_REG   0X8168 /* 第四个触摸点数据地址 */
#define GT9XXX_TP5_REG   0X8170 /* 第五个触摸点数据地址 */
#define GT9XXX_TP6_REG   0X8178 /* 第六个触摸点数据地址 */
#define GT9XXX_TP7_REG   0X8180 /* 第七个触摸点数据地址 */
#define GT9XXX_TP8_REG   0X8188 /* 第八个触摸点数据地址 */
#define GT9XXX_TP9_REG   0X8190 /* 第九个触摸点数据地址 */
#define GT9XXX_TP10_REG  0X8198 /* 第十个触摸点数据地址 */

/**
 * @brief 向 gt9xxx 写入一次数据
 *
 * @param reg 起始寄存器地址
 * @param buf 数据缓缓存区
 * @param len 写数据长度
 * @return 写入状态
 * @retval - 0: 成功
 * @retval - 1: 失败
 */
uint8_t gt9xxx_wr_reg(uint16_t reg, uint8_t *buf, uint8_t len) {
    uint8_t i;
    uint8_t ret = 0;
    ct_iic_start();
    ct_iic_send_byte(GT9XXX_CMD_WR); /* 发送写命令 */
    ct_iic_wait_ack();
    ct_iic_send_byte(reg >> 8); /* 发送高 8 位地址 */
    ct_iic_wait_ack();
    ct_iic_send_byte(reg & 0XFF); /* 发送低 8 位地址 */
    ct_iic_wait_ack();

    for (i = 0; i < len; i++) {
        ct_iic_send_byte(buf[i]); /* 发数据 */
        ret = ct_iic_wait_ack();

        if (ret) {
            break;
        }
    }

    ct_iic_stop(); /* 产生一个停止条件 */
    return ret;
}

/**
 * @brief 从 gt9xxx 读出一次数据
 *
 * @param reg 起始寄存器地址
 * @param[out] buf 数据缓缓存区
 * @param len 写数据长度
 */
void gt9xxx_rd_reg(uint16_t reg, uint8_t *buf, uint8_t len) {
    uint8_t i;
    ct_iic_start();
    ct_iic_send_byte(GT9XXX_CMD_WR); /* 发送写命令 */
    ct_iic_wait_ack();
    ct_iic_send_byte(reg >> 8); /* 发送高 8 位地址 */
    ct_iic_wait_ack();
    ct_iic_send_byte(reg & 0XFF); /* 发送低 8 位地址 */
    ct_iic_wait_ack();
    ct_iic_start();
    ct_iic_send_byte(GT9XXX_CMD_RD); /* 发送读命令 */
    ct_iic_wait_ack();

    for (i = 0; i < len; i++) {
        buf[i] = ct_iic_read_byte(i == (len - 1) ? 0 : 1); /* 发数据 */
    }

    ct_iic_stop(); /* 产生一个停止条件 */
}

/**
 * @brief 初始化 gt9xxx 触摸屏
 *
 * @retval 初始化状态
 * @retval - 0: 初始化成功
 * @retval - 1: 初始化失败
 */
uint8_t gt9xxx_init(void) {
    GPIO_InitTypeDef gpio_init_struct;
    uint8_t temp[5];

    CSP_GPIO_CLK_ENABLE(GT9XXX_RST_GPIO_PORT);
    CSP_GPIO_CLK_ENABLE(GT9XXX_INT_GPIO_PORT);

    gpio_init_struct.Pin = GT9XXX_RST_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;        /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; /* 高速 */
    HAL_GPIO_Init(CSP_GPIO_PORT(GT9XXX_RST_GPIO_PORT), &gpio_init_struct);

    gpio_init_struct.Pin = GT9XXX_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;            /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; /* 高速 */
    HAL_GPIO_Init(CSP_GPIO_PORT(GT9XXX_INT_GPIO_PORT), &gpio_init_struct);

    ct_iic_init(); /* 初始化电容屏的 I2C 总线 */
    GT9XXX_RST(0); /* 复位 */
    delay_ms(10);
    GT9XXX_RST(1); /* 释放复位 */
    delay_ms(10);

    /* INT 引脚模式设置,输入模式,浮空输入 */
    gpio_init_struct.Pin = GT9XXX_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT; /* 输入 */
    gpio_init_struct.Pull = GPIO_NOPULL;     /* 不带上下拉,浮空模式 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; /* 高速 */
    HAL_GPIO_Init(CSP_GPIO_PORT(GT9XXX_INT_GPIO_PORT),
                  &gpio_init_struct); /* 初始化 INT 引脚 */

    delay_ms(100);
    gt9xxx_rd_reg(GT9XXX_PID_REG, temp, 4); /* 读取产品 ID */
    temp[4] = 0;
    /* 判断一下是否是特定的触摸屏 */
    if (strcmp((char *)temp, "911") && strcmp((char *)temp, "9147") &&
        strcmp((char *)temp, "1158") && strcmp((char *)temp, "9271")) {
        /* 若不是触摸屏用到的 GT911/9147/1158/9271, 则初始化失败,
         * 需硬件查看触摸 IC 型号以及查看时序函数是否正确 */
        return 1;
    }

    if (strcmp((char *)temp, "9271") == 0) {
        g_gt_tnum = 10; /* 支持 10 点触摸屏 */
    }

    temp[0] = 0X02;
    gt9xxx_wr_reg(GT9XXX_CTRL_REG, temp, 1); /* 软复位 GT9XXX */

    delay_ms(10);

    temp[0] = 0X00;
    gt9xxx_wr_reg(GT9XXX_CTRL_REG, temp, 1); /* 结束复位,进入读坐标状态 */

    return 0;
}

/* GT9XXX 10 个触摸点 (最多) 对应的寄存器表 */
const uint16_t GT9XXX_TPX_TBL[10] = {
    GT9XXX_TP1_REG, GT9XXX_TP2_REG,  GT9XXX_TP3_REG, GT9XXX_TP4_REG,
    GT9XXX_TP5_REG, GT9XXX_TP6_REG,  GT9XXX_TP7_REG, GT9XXX_TP8_REG,
    GT9XXX_TP9_REG, GT9XXX_TP10_REG,
};

/**
 * @brief 扫描触摸屏 (采用查询方式)
 *
 * @param mode 电容屏未用到此1参数, 为了兼容电阻屏
 * @return 当前触屏状态
 * @retval - 0: 触屏无触摸
 * @retval - 1: 触屏有触摸
 */
uint8_t gt9xxx_scan(uint8_t mode) {
    uint8_t buf[4];
    uint8_t i = 0;
    uint8_t res = 0;
    uint16_t temp;
    uint16_t tempsta;
    static uint8_t t = 0; /* 控制查询间隔,从而降低 CPU 占用率 */
    t++;

    if ((t % 10) == 0 || t < 10) {
        /* 空闲时,每进入 10 次 CTP_Scan 函数才检测 1 次,从而节省 CPU 使用率 */
        gt9xxx_rd_reg(GT9XXX_GSTID_REG, &mode, 1); /* 读取触摸点的状态 */

        if ((mode & 0X80) && ((mode & 0XF) <= g_gt_tnum)) {
            i = 0;
            gt9xxx_wr_reg(GT9XXX_GSTID_REG, &i, 1); /* 清标志 */
        }

        if ((mode & 0XF) && ((mode & 0XF) <= g_gt_tnum)) {
            /* 将点的个数转换为 1 的位数, 匹配 tp_dev.sta 定义 */
            temp = 0XFFFF << (mode & 0XF);

            tempsta = tp_dev.sta; /* 保存当前的 tp_dev.sta 值 */
            tp_dev.sta = (~temp) | TP_PRES_DOWN | TP_CATH_PRES;

            /* 保存触点 0 的数据,保存在最后一个上 */
            tp_dev.x[g_gt_tnum - 1] = tp_dev.x[0];
            tp_dev.y[g_gt_tnum - 1] = tp_dev.y[0];

            for (i = 0; i < g_gt_tnum; i++) {
                if (tp_dev.sta & (1 << i)) {
                    /* 触摸有效? */

                    /* 读取 XY 坐标值 */
                    gt9xxx_rd_reg(GT9XXX_TPX_TBL[i], buf, 4);

                    if (lcddev.id == 0X5510 || lcddev.id == 0X9806 ||
                        lcddev.id == 0X7796) {
                        /* 4.3 寸 800*480 和 3.5 寸 480*320 MCU 屏 */
                        if (tp_dev.touchtype & 0X01) {
                            /* 横屏 */
                            tp_dev.x[i] = lcddev.width -
                                          (((uint16_t)buf[3] << 8) + buf[2]);
                            tp_dev.y[i] = ((uint16_t)buf[1] << 8) + buf[0];
                        } else {
                            tp_dev.x[i] = ((uint16_t)buf[1] << 8) + buf[0];
                            tp_dev.y[i] = ((uint16_t)buf[3] << 8) + buf[2];
                        }
                    } else {
                        /* 其他型号 */
                        if (tp_dev.touchtype & 0X01) {
                            /* 横屏 */
                            tp_dev.x[i] = ((uint16_t)buf[1] << 8) + buf[0];
                            tp_dev.y[i] = ((uint16_t)buf[3] << 8) + buf[2];
                        } else {
                            tp_dev.x[i] = lcddev.width -
                                          (((uint16_t)buf[3] << 8) + buf[2]);
                            tp_dev.y[i] = ((uint16_t)buf[1] << 8) + buf[0];
                        }
                    }
                }
            }

            res = 1;

            if (tp_dev.x[0] > lcddev.width || tp_dev.y[0] > lcddev.height) {
                /* 非法数据 (坐标超出了) */
                if ((mode & 0XF) > 1) {
                    /* 有其他点有数据,则复第二个触点的数据到第一个触点. */
                    tp_dev.x[0] = tp_dev.x[1];
                    tp_dev.y[0] = tp_dev.y[1];
                    t = 0; /* 触发一次,则会最少连续监测 10 次,从而提高命中率 */
                } else {
                    /* 非法数据,则忽略此次数据 (还原原来的) */
                    tp_dev.x[0] = tp_dev.x[g_gt_tnum - 1];
                    tp_dev.y[0] = tp_dev.y[g_gt_tnum - 1];
                    mode = 0X80;
                    tp_dev.sta = tempsta; /* 恢复 tp_dev.sta */
                }
            } else {
                t = 0; /* 触发一次,则会最少连续监测 10 次,从而提高命中率 */
            }
        }
    }

    if ((mode & 0X8F) == 0X80) {
        /* 无触摸点按下 */
        if (tp_dev.sta & TP_PRES_DOWN) {
            /* 之前是被按下的 */
            tp_dev.sta &= ~TP_PRES_DOWN; /* 标记按键松开 */
        } else {
            /* 之前就没有被按下 */
            tp_dev.x[0] = 0xffff;
            tp_dev.y[0] = 0xffff;
            tp_dev.sta &= 0XE000; /* 清除点有效标记 */
        }
    }

    if (t > 240) {
        t = 10; /* 重新从 10 开始计数 */
    }

    return res;
}
