/**
  ******************************************************************************
  * @file    usb_dcd_int.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   Device Control driver Interrupt management Header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef USB_DCD_INT_H__
#define USB_DCD_INT_H__

/* Includes ------------------------------------------------------------------*/
#include "usbd_pwr.h"

/* Exported defines ----------------------------------------------------------*/
/* Mask defining which events has to be handled by the device application software */
#define IMR_MSK (USB_INTR_DISCONNECT | USB_INTR_SOF | USB_INTR_RESET | USB_INTR_RESUME | USB_INTR_SUSPEND)

/* Exported types ------------------------------------------------------------*/
typedef struct _USBD_DCD_INT
{
  uint8_t (* DataOutStage) (USB_CORE_HANDLE *pdev , uint8_t epnum);
  uint8_t (* DataInStage)  (USB_CORE_HANDLE *pdev , uint8_t epnum);
  uint8_t (* SetupStage) (USB_CORE_HANDLE *pdev);
  uint8_t (* SOF) (USB_CORE_HANDLE *pdev);
  uint8_t (* Reset) (USB_CORE_HANDLE *pdev);
  uint8_t (* Suspend) (USB_CORE_HANDLE *pdev);
  uint8_t (* Resume) (USB_CORE_HANDLE *pdev);   
  
}USBD_DCD_INT_cb_TypeDef;

extern USBD_DCD_INT_cb_TypeDef *USBD_DCD_INT_fops;

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void EP_Isr(uint8_t tx_ep, uint8_t rx_ep);
void USB_Isr(void);

#endif /* USB_DCD_INT_H__ */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
