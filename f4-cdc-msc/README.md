# STM32F4 USB CDC+MSC 复合设备 示例程序

开发平台：正点原子阿波罗 STM32F429

MCU: STM32F429IGT6

LCD 屏幕：正点原子 ATK4348, RGB565 接口，800 * 480 尺寸，5 点触控电容触摸屏

添加的外设代码：AT24C02, SDRAM, NAND Flash, SD-Card, LCD (支持 RGB), 触摸

添加了 FreeRTOS，FATFS

USB 部分添加了 CDC 与 MSC 设备的复合设备，插上电脑会出现存储设备和虚拟串口，可以同时使用。

不知道为什么，不能只留一个 USB 任务，否则会进入 HardFault。
