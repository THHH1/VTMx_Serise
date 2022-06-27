/**
  ******************************************************************************
  * @file    usbd_hid_core.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    10-09-2018
  * @brief   header file for the usbd_hid_core.c file.
  ******************************************************************************
  */ 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_HID_CORE_H_
#define __USB_HID_CORE_H_

/* Includes ------------------------------------------------------------------*/
#include "usbd_req.h"

/* Exported defines ----------------------------------------------------------*/
#define USB_HID_CONFIG_DESC_SIZ       34
#define USB_HID_DESC_SIZ              9
#define HID_MOUSE_REPORT_DESC_SIZE    74

#define HID_DESCRIPTOR_TYPE           0x21
#define HID_REPORT_DESC               0x22


#define HID_REQ_SET_PROTOCOL          0x0B
#define HID_REQ_GET_PROTOCOL          0x03

#define HID_REQ_SET_IDLE              0x0A
#define HID_REQ_GET_IDLE              0x02

#define HID_REQ_SET_REPORT            0x09
#define HID_REQ_GET_REPORT            0x01

/* Exported types ------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern USBD_Class_cb_TypeDef  USBD_HID_cb;

/* Exported functions ------------------------------------------------------- */ 
 
uint8_t USBD_HID_SendReport (USB_CORE_HANDLE  *pdev, 
                                 uint8_t *report,
                                 uint16_t len);

#endif  /* __USB_HID_CORE_H_ */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
