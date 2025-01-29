# STM32F4 lvgl 示例程序

开发平台：正点原子阿波罗 STM32F429

MCU: STM32F429IGT6

LCD 屏幕：正点原子 ATK4348, RGB565 接口，800 * 480 尺寸，5 点触控电容触摸屏

添加的外设代码：AT24C02, W25Q64, SDRAM (), NAND Flash, SD-Card, LCD (支持 RGB), 触摸

添加了 LVGL，FreeRTOS，FATFS

USB 部分添加了 CDC 与 MSC 设备，两者不可以共存。在之前的提交中有二者的复合设备，但是有问题所以取消了。

集成 EEZ Studio，用来减少 UI 代码工作。

## 现象

上电后会检测 key0 是否按下，当板子上电时按下 key0 不放，持续 3 秒后会提示进入 USB Storage 也就是 U 盘模式，此时可以向 NAND Flash 写入资源文件。

如果没有按下 key0，则会直接进入 GUI 应用程序。屏幕上会出现两个开关，分别控制 LED0 和 LED1。
