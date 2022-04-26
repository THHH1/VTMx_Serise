/**
  ******************************************************************************
  * @file    usbd_pwr.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   Header file for usbd_pwr.c
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_PWR_H__
#define __USBD_PWR_H__

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"
#include "usb_bsp.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum _RESUME_STATE
{
  RESUME_EXTERNAL,
  RESUME_INTERNAL,
#ifdef LPM_ENABLED  
  L1_RESUME_INTERNAL,
#endif
  RESUME_LATER,
  RESUME_WAIT,
  RESUME_START,
  RESUME_ON,
  RESUME_OFF,
  RESUME_ESOF
} RESUME_STATE;

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern USB_CORE_HANDLE USB_Device_dev;

/* Exported functions ------------------------------------------------------- */ 
void Suspend(void);
void Resume_Init(void);
void Resume(RESUME_STATE eResumeSetVal);
void Leave_LowPowerMode(void);

#endif /*__USBD_PWR_H__*/

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
