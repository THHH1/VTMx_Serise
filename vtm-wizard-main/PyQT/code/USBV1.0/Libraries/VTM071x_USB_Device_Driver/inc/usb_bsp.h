/**
  ******************************************************************************
  * @file    usb_bsp.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   Specific api's related to the used hardware platform
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_BSP__H__
#define __USB_BSP__H__

/* Includes ------------------------------------------------------------------*/
#include "usb_dcd.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void USB_BSP_Init (USB_CORE_HANDLE *pdev);
void USB_BSP_EnableInterrupt (USB_CORE_HANDLE *pdev);
void USB_BSP_uDelay (const uint32_t usec);
void USB_BSP_mDelay (const uint32_t msec);

#endif /* __USB_BSP__H__ */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/

