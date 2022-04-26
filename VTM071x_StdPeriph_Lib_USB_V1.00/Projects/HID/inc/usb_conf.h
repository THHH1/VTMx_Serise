/**
  ******************************************************************************
  * @file    usb_conf.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    10-28-2018
  * @brief   General low level driver configuration
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF__H__
#define __USB_CONF__H__

/* Includes ------------------------------------------------------------------*/
#include "vtm071x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Endpoints used by the device */
#define EP_NUM              (2)  /* EP0 + EP1 IN For HID */

/* EP0, RX/TX buffers base address */
#define ENDP0_RX_ADDRESS    (0x00)
#define ENDP0_TX_ADDRESS    (0x40)

/* EP1 Tx buffer base address */
#define HID_IN_TX_ADDRESS   (0x80)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __USB_CONF__H__ */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
