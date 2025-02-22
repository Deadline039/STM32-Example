/**
 * @file    main.c
 * @author  Deadline039
 * @brief   Main function files.
 * @version 1.0
 * @date    2024-07-29
 */

#include "includes.h"

/**
 * @brief The program entrance.
 *
 * @return Exit code.
 */
int main(void) {
    uint8_t x = 0;
    uint8_t lcd_id[12];
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    bsp_init();
    g_point_color = RED;
    sprintf((char *)lcd_id, "LCD ID:%04X",
            lcddev.id); /* 将LCD ID打印到lcd_id数组 */

    while (1) {
        switch (x) {
            case 0:
                lcd_clear(WHITE);
                break;

            case 1:
                lcd_clear(BLACK);
                break;

            case 2:
                lcd_clear(BLUE);
                break;

            case 3:
                lcd_clear(RED);
                break;

            case 4:
                lcd_clear(MAGENTA);
                break;

            case 5:
                lcd_clear(GREEN);
                break;

            case 6:
                lcd_clear(CYAN);
                break;

            case 7:
                lcd_clear(YELLOW);
                break;

            case 8:
                lcd_clear(BRRED);
                break;

            case 9:
                lcd_clear(GRAY);
                break;

            case 10:
                lcd_clear(LGRAY);
                break;

            case 11:
                lcd_clear(BROWN);
                break;

            default:
                break;
        }

        lcd_show_string(10, 40, 240, 32, 32, "STM32", RED);
        lcd_show_string(10, 80, 240, 24, 24, "TFTLCD TEST", RED);
        lcd_show_string(10, 110, 240, 16, 16, "ATOM@ALIENTEK", RED);
        lcd_show_string(10, 130, 240, 16, 16, (char *)lcd_id,
                        RED); /* 显示LCD ID */
        x++;

        if (x == 12) {
            x = 0;
        }

        LED0_TOGGLE(); /* 红灯闪烁 */
        delay_ms(1000);
    }
    freertos_start();

    return 0;
}
