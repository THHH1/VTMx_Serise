/**
  ******************************************************************************
  * @file    usbd_storage_msd.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    08-01-2018
  * @brief   This file provides the disk operations functions.
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_msc_mem.h"
#include "VTM071x_eval_spi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define STORAGE_LUN_NBR                  1 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* USB Mass storage Standard Inquiry Data */
const int8_t  STORAGE_Inquirydata[] = {
  
  /* LUN 0 */
  0x00,		
  0x80,		
  0x02,		
  0x02,
  (USBD_STD_INQUIRY_LENGTH - 5),
  0x00,
  0x00,	
  0x00,
  'M', 'I', 'C', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'F', 'l', 'a', 's', 'h', ' ', ' ', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '1', '.', '0' ,'0',                     /* Version      : 4 Bytes */
}; 

__IO uint32_t count = 0;
/* Private function prototypes -----------------------------------------------*/
int8_t STORAGE_Init (uint8_t lun);

int8_t STORAGE_GetCapacity (uint8_t lun, 
                           uint32_t *block_num, 
                           uint32_t *block_size);

int8_t  STORAGE_IsReady (uint8_t lun);

int8_t  STORAGE_IsWriteProtected (uint8_t lun);

int8_t STORAGE_Read (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);

int8_t STORAGE_Write (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);

int8_t STORAGE_GetMaxLun (void);


USBD_STORAGE_cb_TypeDef USBD_MICRO_SDIO_fops =
{
    STORAGE_Init,
    STORAGE_GetCapacity,
    STORAGE_IsReady,
    STORAGE_IsWriteProtected,
    STORAGE_Read,
    STORAGE_Write,
    STORAGE_GetMaxLun,
    (int8_t *)STORAGE_Inquirydata,
};

USBD_STORAGE_cb_TypeDef  *USBD_STORAGE_fops = &USBD_MICRO_SDIO_fops;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize the storage medium
  * @param  lun : logical unit number
  * @retval Status
  */

int8_t STORAGE_Init (uint8_t lun)
{    
    if(SPI_FLASH_Init() != 0)
    {
        return (-1);
    } 

    return (0);
}

/**
  * @brief  return medium capacity and block size
  * @param  lun : logical unit number
  * @param  block_num :  number of physical block
  * @param  block_size : size of a physical block
  * @retval Status
  */
int8_t STORAGE_GetCapacity (uint8_t lun, uint32_t *block_num, uint32_t *block_size)
{
    if(SPI_FLASH_Detect())
    {
        return (-1);
    }

    *block_size = 4096;
    *block_num = SPI_FLASH_TOTAL_SIZE / 4096;

    return (0);
}

/**
  * @brief  check whether the medium is ready
  * @param  lun : logical unit number
  * @retval Status
  */
int8_t  STORAGE_IsReady (uint8_t lun)
{
    static uint8_t status = 0;
        
    if(SPI_FLASH_Detect())
    {
        status = 1;
        return (-1);
    }
    else if(status == 1)
    {
        status = 0;
        if(SPI_FLASH_Init() != 0)
        {
            return (-1);
        }
        return 0;
    }
    
    return (0);
}

/**
  * @brief  check whether the medium is write-protected
  * @param  lun : logical unit number
  * @retval Status
  */
int8_t STORAGE_IsWriteProtected (uint8_t lun)
{
    
    return  0;
}

/**
  * @brief  Read data from the medium
  * @param  lun : logical unit number
  * @param  buf : Pointer to the buffer to save data
  * @param  blk_addr :  address of 1st block to be read
  * @param  blk_len : number of blocks to be read
  * @retval Status
  */
int8_t STORAGE_Read (uint8_t lun, 
                 uint8_t *buf, 
                 uint32_t blk_addr,
                 uint16_t blk_len)
{    
    if(SPI_FLASH_Detect())
    {
        return (-1);
    }
  
    if(SPI_FLASH_Read (buf, blk_addr, blk_len) != 0)
    {
        return 5;
    }
    
    return 0;
}
/**
  * @brief  Write data to the medium
  * @param  lun : logical unit number
  * @param  buf : Pointer to the buffer to write from
  * @param  blk_addr :  address of 1st block to be written
  * @param  blk_len : number of blocks to be read
  * @retval Status
  */
int8_t STORAGE_Write (uint8_t lun, 
                  uint8_t *buf, 
                  uint32_t blk_addr,
                  uint16_t blk_len)
{    
    if(SPI_FLASH_Detect())
    {
        return (-1);
    }
    
    if (!(blk_addr & (4096-1)))
        SPI_FLASH_EraseSector4K(blk_addr);
    
    if( SPI_FLASH_Write (buf, blk_addr, blk_len) != 0)
    {
        return 5;
    }
    
    return 0;
}

/**
  * @brief  Return number of supported logical unit
  * @param  None
  * @retval number of logical unit
  */

int8_t STORAGE_GetMaxLun (void)
{
    return (STORAGE_LUN_NBR - 1);
}
/************************ (C) COPYRIGHT MIC *****END OF FILE****/

