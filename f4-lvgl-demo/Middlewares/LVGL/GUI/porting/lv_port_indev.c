/**
 * @file lv_port_indev.c
 *
 */

/* Copy this file as "lv_port_indev.c" and set this value to "1" to enable
 * content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include <lvgl.h>

#include <bsp.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/* 触摸屏 */
static void touchpad_init(void);
static void touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(lv_coord_t *x, lv_coord_t *y);

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_indev_t *indev_touchpad;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @brief 初始化并注册输入设备
 *
 */
void lv_port_indev_init(void) {
    /**
     * 在这里你可以找到 LittlevGL 支持的出入设备的实现示例:
     *  - 触摸屏
     *  - 鼠标 (支持光标)
     *  - 键盘 (仅支持按键的 GUI 用法)
     *  - 编码器 (支持的 GUI 用法仅包括: 左, 右, 按下)
     *  - 按钮 (按下屏幕上指定点的外部按钮)
     *
     *  函数 `..._read()` 只是示例
     *  你需要根据具体的硬件来完成这些函数
     */

    static lv_indev_drv_t indev_drv;

    /*------------------
     * 触摸屏
     * -----------------*/

    /* 初始化触摸屏(如果有) */
    touchpad_init();

    /* 注册触摸屏输入设备 */
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&indev_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * 触摸屏
 * -----------------*/

/**
 * @brief 初始化触摸屏
 *
 */
static void touchpad_init(void) {
    /*Your code comes here*/
    tp_dev.init();
    /* 电阻屏如果发现显示屏 XY 镜像现象，需要坐标矫正 */
    if (0 == (tp_dev.touchtype & 0x80)) {
        tp_adjust();
    }
}

/**
 * @brief 图形库的触摸屏读取回调函数
 *
 * @param indev_drv 触摸屏设备
 * @param data 输入设备数据结构体
 */
static void touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;

    UNUSED(indev_drv);

    /* 保存按下的坐标和状态 */
    if (touchpad_is_pressed()) {
        touchpad_get_xy(&last_x, &last_y);
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    /* 设置最后按下的坐标 */
    data->point.x = last_x;
    data->point.y = last_y;
}

/**
 * @brief 获取触摸屏设备的状态
 *
 * @return 触摸屏设备是否被按下
 */
static bool touchpad_is_pressed(void) {
    tp_dev.scan(0);

    if (tp_dev.sta & TP_PRES_DOWN) {
        return true;
    }

    return false;
}

/**
 * @brief 在触摸屏被按下的时候读取 x, y 坐标
 *
 * @param[out] x x坐标的指针
 * @param[out] y y坐标的指针
 */
static void touchpad_get_xy(lv_coord_t *x, lv_coord_t *y) {
    (*x) = tp_dev.x[0];
    (*y) = tp_dev.y[0];
}

#endif
