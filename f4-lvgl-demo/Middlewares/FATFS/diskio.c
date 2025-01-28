/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h" /* Declarations of disk functions */
#include "bsp.h"
#include "ff.h" /* Obtains integer types */

/* Definitions of physical drive number for each drive */
#define DEV_NAND   0 /* NAND flash to physical drive 0 */
#define DEV_SDCARD 1 /* SD-Card to physical drive 1    */

uint32_t NAND_FLASH_SECTOR_COUNT;
uint8_t NAND_FLASH_BLOCK_SIZE;

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status(
    BYTE pdrv /* Physical drive nmuber to identify the drive */) {
    UNUSED(pdrv);
    return RES_OK;
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(
    BYTE pdrv /* Physical drive nmuber to identify the drive */
) {
    uint8_t res = 0;
    uint8_t times = 0;

    while (times < 10) {
        if (pdrv == DEV_NAND) {
            if (ftl_init() == 0) {
                break;
            }
        } else if (pdrv == DEV_SDCARD) {
            if (sdcard_init() == SD_OPERATE_OK) {
                break;
            }
        } else {
            res = 1;
            break;
        }
        ++times;
    }

    if (times >= 10) {
        res = 1;
    } else {
        res = 0;
    }

    if (res) {
        return STA_NOINIT;
    } else {
        return 0;
    }
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read(BYTE pdrv,  /* Physical drive nmuber to identify the drive */
                  BYTE *buff, /* Data buffer to store read data */
                  LBA_t sector, /* Start sector in LBA */
                  UINT count    /* Number of sectors to read */
) {
    uint8_t res;

    if (!count) {
        return RES_PARERR;
    }

    switch (pdrv) {
        case DEV_NAND:
            res = ftl_read_sectors(buff, sector, 512, count);
            break;

        case DEV_SDCARD:
            res = sdcard_read_disk((uint8_t *)buff, sector, count);
            break;

        default:
            res = 1;
            break;
    }

    if (res == 0) {
        return RES_OK;
    } else {
        return RES_ERROR;
    }
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write(BYTE pdrv, /* Physical drive nmuber to identify the drive */
                   const BYTE *buff, /* Data to be written */
                   LBA_t sector,     /* Start sector in LBA */
                   UINT count        /* Number of sectors to write */
) {
    uint8_t res;

    if (!count) {
        return RES_PARERR;
    }

    switch (pdrv) {
        case DEV_NAND:
            res = ftl_write_sectors((uint8_t *)buff, sector, 512, count);
            break;

        case DEV_SDCARD:
            res = sdcard_write_disk((uint8_t *)buff, sector, count);
            break;

        default:
            res = 1;
            break;
    }

    if (res == 0) {
        return RES_OK;
    } else {
        return RES_ERROR;
    }
}
#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl(BYTE pdrv, /* Physical drive nmuber (0..) */
                   BYTE cmd,  /* Control code */
                   void *buff /* Buffer to send/receive control data */
) {
    DRESULT res;

    if (pdrv == DEV_SDCARD) {
        switch (cmd) {
            case CTRL_SYNC:
                res = RES_OK;
                break;

            case GET_SECTOR_SIZE:
                *(DWORD *)buff = 512;
                res = RES_OK;
                break;

            case GET_BLOCK_SIZE:
                *(DWORD *)buff = g_sdcard_info.LogBlockSize;
                res = RES_OK;
                break;

            case GET_SECTOR_COUNT:
                *(DWORD *)buff = g_sdcard_info.LogBlockNbr;
                res = RES_OK;
                break;

            default:
                res = RES_PARERR;
                break;
        }
    } else if (pdrv == DEV_NAND) {
        switch (cmd) {
            case CTRL_SYNC:
                res = RES_OK;
                break;

            case GET_SECTOR_SIZE:
                /* NAND FLASH 扇区强制为 512 字节大小 */
                *(WORD *)buff = 512;
                res = RES_OK;
                break;

            case GET_BLOCK_SIZE:
                /* block 大小, 定义成一个page的大小 */
                *(WORD *)buff = nand_dev.page_mainsize / 512;
                res = RES_OK;
                break;

            case GET_SECTOR_COUNT:
                /* NAND FLASH 的总扇区大小 */
                *(DWORD *)buff = nand_dev.valid_blocknum *
                                 nand_dev.block_pagenum *
                                 nand_dev.page_mainsize / 512;
                res = RES_OK;
                break;

            default:
                res = RES_PARERR;
                break;
        }
    } else {
        res = RES_ERROR;
    }

    return res;
}
