/**
  ******************************************************************************
  * @file    usbd_cdc_vcp.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    10-28-2018
  * @brief   Header for usbd_cdc_vcp.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CDC_VCP_H
#define __USBD_CDC_VCP_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_core.h"

/* Exported typef ------------------------------------------------------------*/
/* The following structures groups all needed parameters to be configured for the 
   ComPort. These parameters can be modified on the fly by the host through CDC class
   command class requests. */
typedef struct
{
  uint32_t bitrate;
  uint8_t  format;
  uint8_t  paritytype;
  uint8_t  datatype;
}LINE_CODING;

/* Exported constants --------------------------------------------------------*/
/* The following define is used to route the USART IRQ handler to be used.
   The IRQ handler function is implemented in the usbd_cdc_vcp.c file. */
          
#define USART_IT_PRIO                  0 
#define USB_IT_PRIO                    1 /* USB priority should be lower than USART
                                            in order to not loose data reception from
                                            USART while USB interrupt is being handled*/

#define DEFAULT_CONFIG                  0
#define OTHER_CONFIG                    1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void EVAL_COM_IRQHandler(void);

#endif /* __USBD_CDC_VCP_H */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
