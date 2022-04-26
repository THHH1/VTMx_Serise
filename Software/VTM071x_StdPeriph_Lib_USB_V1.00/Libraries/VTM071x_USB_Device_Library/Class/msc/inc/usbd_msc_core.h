/**
  ******************************************************************************
  * @file    usbd_msc_core.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   header for the usbd_msc_core.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USB_MSC_CORE_H_
#define _USB_MSC_CORE_H_

/* Includes ------------------------------------------------------------------*/
#include "usbd_req.h"
#include "usbd_msc_bot.h"

/* Exported defines ----------------------------------------------------------*/
#define BOT_GET_MAX_LUN              0xFE
#define BOT_RESET                    0xFF
#define USB_MSC_CONFIG_DESC_SIZ      32

#define MSC_EPIN_SIZE                MSC_MAX_PACKET 
#define MSC_EPOUT_SIZE               MSC_MAX_PACKET 

/* Exported types ------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern USBD_Class_cb_TypeDef  USBD_MSC_cb;

/* Exported functions ------------------------------------------------------- */ 

#endif  /* _USB_MSC_CORE_H_ */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
