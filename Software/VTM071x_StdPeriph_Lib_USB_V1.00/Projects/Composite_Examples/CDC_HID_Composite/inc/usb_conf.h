/**
  ******************************************************************************
  * @file    usb_conf.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    10-09-2018
  * @brief   General low level driver configuration
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF__H__
#define __USB_CONF__H__

/* Includes ------------------------------------------------------------------*/
#include "vtm071x.h"
//#include "VTM071x_eval.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Define if Low power mode is enabled; it allows entering the device into STOP mode
    following USB Suspend event, and wakes up after the USB wakeup event is received. */
/* #define USB_DEVICE_LOW_PWR_MGMT_SUPPORT */

/* Configure the USB clock source as HSI48 with Clock Recovery System(CRS)*/
#define USB_CLOCK_SOURCE_CRS


/* Endpoints used by the device */
#define EP_NUM     (4)  /* EP0 + EP1 For HID + EP2/EP3 for CDC  */

/* buffer table base address */
#define BTABLE_ADDRESS      (0x000)

/* EP0, RX/TX buffers base address */
#define ENDP0_RX_ADDRESS   (0x00)
#define ENDP0_TX_ADDRESS   (0x40)

/* EP1 Tx buffer base address */
#define HID_IN_TX_ADDRESS  (0x80)

/* EP1 Rx buffer base address */
#define HID_OUT_RX_ADDRESS (0xC0)

/* EP2 Tx buffer base address */
#define BULK_IN_TX_ADDRESS  (0x100)

/* EP2 Rx buffer base address */
#define BULK_OUT_RX_ADDRESS (0x140)

/* EP3 Tx buffer base address */
#define INT_IN_TX_ADDRESS   (0x180)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif /* __USB_CONF__H__ */


/************************ (C) COPYRIGHT MIC *****END OF FILE****/
