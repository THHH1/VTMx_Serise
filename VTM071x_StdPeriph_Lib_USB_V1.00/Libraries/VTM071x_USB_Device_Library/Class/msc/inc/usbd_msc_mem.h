/**
  ******************************************************************************
  * @file    usbd_msc_mem.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   header for the STORAGE DISK file file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_MEM_H
#define __USBD_MEM_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_def.h"

/* Exported defines ----------------------------------------------------------*/
#define USBD_STD_INQUIRY_LENGTH		36

/* Exported types ------------------------------------------------------------*/
typedef struct _USBD_STORAGE
{
  int8_t (* Init) (uint8_t lun);
  int8_t (* GetCapacity) (uint8_t lun, uint32_t *block_num, uint32_t *block_size);
  int8_t (* IsReady) (uint8_t lun);
  int8_t (* IsWriteProtected) (uint8_t lun);
  int8_t (* Read) (uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
  int8_t (* Write)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
  int8_t (* GetMaxLun)(void);
  int8_t *pInquiry;
  
}USBD_STORAGE_cb_TypeDef;

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
extern USBD_STORAGE_cb_TypeDef *USBD_STORAGE_fops;


#endif /* __USBD_MEM_H */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
