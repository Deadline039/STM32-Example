/**
 ******************************************************************************
 * @file    USB_Device/MSC_Standalone/Src/usbd_storage.c
 * @author  MCD Application Team
 * @brief   Memory management layer
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------
 */

#include "usbd_storage_if.h"

#include <bsp.h>

/* 自己定义的一个标记 USB 状态的寄存器, 方便判断 USB 状态
 * bit0 : 表示电脑正在向 SD 卡写入数据
 * bit1 : 表示电脑正从 SD 卡读出数据
 * bit2 : SD 卡写数据错误标志位
 * bit3 : SD 卡读数据错误标志位
 * bit4 : 1, 表示电脑有轮询操作(表明连接还保持着)
 */
volatile uint8_t g_usb_state_reg = 0;

/* Private typedef -----------------------------------------------------------
 */
/* Private define ------------------------------------------------------------
 */
#define STORAGE_LUN_NBR        2
#define STORAGE_BLK_NBR        0x10000
#define STORAGE_BLK_SIZ        0x200

#define STORAGE_DEV_NAND_FLASH 0
#define STORAGE_DEV_SD_CARD    1

/* Private macro -------------------------------------------------------------
 */
/* Private variables ---------------------------------------------------------
 */
__IO uint32_t writestatus, readstatus = 0;

/* clang-format off */

/* USB Mass storage Standard Inquiry Data */
const int8_t STORAGE_Inquirydata[] = {
  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 4),
  0x00,
  0x00,
  0x00,
  'S', 'T', 'M', '3', '2', ' ', ' ', ' ', /* Manufacturer: 8 bytes */
  'N', 'A', 'N', 'D', ' ', 'F', 'l', 'a', /* Product : 16 Bytes */
  's', 'h', ' ', 'D', 'i', 's', 'k', ' ',
  '1', '.', '0', ' ',           /* Version : 4 Bytes */

  /* LUN 1 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 4),
  0x00,
  0x00,
  0x00,
  'S', 'T', 'M', '3', '2', ' ', ' ', ' ', /* Manufacturer: 8 bytes */
  'S', 'D', ' ' , 'C', 'a', 'r', 'd', ' ', /* Product : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '1', '.', '0', ' ',           /* Version : 4 Bytes */
};

/* clang-format on */

/* Private function prototypes -----------------------------------------------
 */
static int8_t STORAGE_Init(uint8_t lun);
static int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num,
                                  uint16_t *block_size);
static int8_t STORAGE_IsReady(uint8_t lun);
static int8_t STORAGE_IsWriteProtected(uint8_t lun);
static int8_t STORAGE_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr,
                           uint16_t blk_len);
static int8_t STORAGE_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr,
                            uint16_t blk_len);
static int8_t STORAGE_GetMaxLun(void);

USBD_StorageTypeDef USBD_DISK_fops = {
    STORAGE_Init,      STORAGE_GetCapacity,
    STORAGE_IsReady,   STORAGE_IsWriteProtected,
    STORAGE_Read,      STORAGE_Write,
    STORAGE_GetMaxLun, (int8_t *)STORAGE_Inquirydata,
};

/* Private functions ---------------------------------------------------------
 */

/**
 * @brief  Initializes the storage unit (medium)
 * @param  lun: Logical unit number
 * @retval Status (0 : Ok / -1 : Error)
 */
int8_t STORAGE_Init(uint8_t lun) {
    uint8_t res = 0;
    switch (lun) {
        case STORAGE_DEV_NAND_FLASH:
            res = ftl_init();
            break;

        case STORAGE_DEV_SD_CARD:
            res = sdcard_init();
            break;

        default:
            res = -1;
            break;
    }
    return res;
}

/**
 * @brief  Returns the medium capacity.
 * @param  lun: Logical unit number
 * @param  block_num: Number of total block number
 * @param  block_size: Block size
 * @retval Status (0: Ok / -1: Error)
 */
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num,
                           uint16_t *block_size) {
    switch (lun) {
        case STORAGE_DEV_NAND_FLASH: {
            *block_size = 512;
            *block_num = nand_dev.valid_blocknum * nand_dev.block_pagenum *
                         nand_dev.page_mainsize / 512;
        } break;

        case STORAGE_DEV_SD_CARD: {
            sdcard_get_info(&g_sdcard_info);
            *block_num = g_sdcard_info.LogBlockNbr - 1;
            *block_size = g_sdcard_info.LogBlockSize;
        } break;

        default:
            return -1;
    }

    return 0;
}

/**
 * @brief  Checks whether the medium is ready.
 * @param  lun: Logical unit number
 * @retval Status
 */
int8_t STORAGE_IsReady(uint8_t lun) {
    g_usb_state_reg |= 0X10;
    return USBD_OK;
}

/**
 * @brief  Checks whether the medium is write protected.
 * @param  lun: Logical unit number
 * @retval Status (0: write enabled / -1: otherwise)
 */
int8_t STORAGE_IsWriteProtected(uint8_t lun) {
    return USBD_OK;
}

/**
 * @brief  Reads data from the medium.
 * @param  lun: Logical unit number
 * @param  blk_addr: Logical block address
 * @param  blk_len: Blocks number
 * @retval Status (0: Ok / -1: Error)
 */
int8_t STORAGE_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr,
                    uint16_t blk_len) {
    int8_t ret = -1;
    g_usb_state_reg |= 0X02;

    switch (lun) {
        case STORAGE_DEV_NAND_FLASH:
            ret = ftl_read_sectors(buf, blk_addr, 512, blk_len);
            break;

        case STORAGE_DEV_SD_CARD:
            ret = sdcard_read_disk(buf, blk_addr, blk_len);
            break;

        default:
            ret = -1;
    }

    if (ret) {
        g_usb_state_reg |= 0X08;
    }

    return ret;
}

/**
 * @brief  Writes data into the medium.
 * @param  lun: Logical unit number
 * @param  blk_addr: Logical block address
 * @param  blk_len: Blocks number
 * @retval Status (0 : Ok / -1 : Error)
 */
int8_t STORAGE_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr,
                     uint16_t blk_len) {
    int8_t ret = -1;

    g_usb_state_reg |= 0X01;

    switch (lun) {
        case STORAGE_DEV_NAND_FLASH:
            ret = ftl_write_sectors(buf, blk_addr, 512, blk_len);
            break;

        case STORAGE_DEV_SD_CARD:
            ret = sdcard_write_disk(buf, blk_addr, blk_len);
            break;

        default:
            break;
    }

    if (ret) {
        g_usb_state_reg |= 0X04;
    }

    return ret;
}

/**
 * @brief  Returns the Max Supported LUNs.
 * @param  None
 * @retval Lun(s) number
 */
int8_t STORAGE_GetMaxLun(void) {
    sdcard_get_info(&g_sdcard_info);
    /* 返回的逻辑单元个数是减了 1 的. 0 就表示 1 个; 1 表示 2 个. 以此类推 */
    if (g_sdcard_info.LogBlockNbr) {
        /* SD 卡正常, 会有两个磁盘 */
        return STORAGE_LUN_NBR - 1;
    } else {
        /* 不正常, 只有 1 个 */
        return STORAGE_LUN_NBR - 2;
    }
}
