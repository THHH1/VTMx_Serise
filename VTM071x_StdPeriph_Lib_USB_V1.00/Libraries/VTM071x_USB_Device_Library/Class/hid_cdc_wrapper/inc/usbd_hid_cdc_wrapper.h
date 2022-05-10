/**
  ******************************************************************************
  * @file    usbd_hid_cdc_wrapper.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    10-09-2018
  * @brief   header file for the usbd_hid_cdc_wrapper.c file.
  ******************************************************************************
  */  

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_HID_CDC_WRAPPER_H_
#define __USB_HID_CDC_WRAPPER_H_

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_core.h"
#include "usbd_cdc_core.h"

/* Exported defines ----------------------------------------------------------*/
#define HID_INTERFACE       0x0
#define CDC_COM_INTERFACE   0x1

/* Exported types ------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
#define USB_HID_CDC_CONFIG_DESC_SIZ  (CUSTOMHID_SIZ_CONFIG_DESC -9 + USB_CDC_CONFIG_DESC_SIZ  + 8)

/* Exported variables --------------------------------------------------------*/
extern USBD_Class_cb_TypeDef  USBD_HID_CDC_cb;

/* Exported functions ------------------------------------------------------- */ 

#endif  /* __USB_HID_CDC_WRAPPER_H_ */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
