/**
  ******************************************************************************
  * @file    usbd_ioreq.c
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   This file provides the IO requests APIs for control endpoints.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_ioreq.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  USBD_CtlSendData
  *         send data on the ctl pipe
  * @param  pdev: device instance
  * @param  buff: pointer to data buffer
  * @param  len: length of data to be sent
  * @retval status
  */
USBD_Status USBD_CtlSendData(USB_CORE_HANDLE  *pdev, 
                             uint8_t *pbuf,
                             uint16_t len)
{
    USBD_Status ret = USBD_OK;

    pdev->dev.in_ep[0].total_data_len = len;

    pdev->dev.in_ep[0].xfer_buff = pbuf;
    pdev->dev.in_ep[0].xfer_len = len;
    
    pdev->dev.device_state = USB_EP0_DATA_IN;
    
    return ret;
}

/**
  * @brief  USBD_CtlContinueSendData
  *         continue sending data on the ctl pipe
  * @param  pdev: device instance
  * @param  buff: pointer to data buffer
  * @param  len: length of data to be sent
  * @retval status
  */
USBD_Status  USBD_CtlContinueSendData (USB_CORE_HANDLE  *pdev, 
                                       uint8_t *pbuf,
                                       uint16_t len)
{
    USBD_Status ret = USBD_OK;

    DCD_EP_Tx(pdev, 0, pbuf, len);

    return ret;
}

/**
  * @brief  USBD_CtlPrepareRx
  *         receive data on the ctl pipe
  * @param  pdev: USB device instance
  * @param  buff: pointer to data buffer
  * @param  len: length of data to be received
  * @retval status
  */
USBD_Status  USBD_CtlPrepareRx (USB_CORE_HANDLE  *pdev,
                                  uint8_t *pbuf,                                  
                                  uint16_t len)
{
    USBD_Status ret = USBD_OK;

    pdev->dev.out_ep[0].total_data_len = len;

    pdev->dev.out_ep[0].xfer_buff = pbuf;
    pdev->dev.out_ep[0].xfer_len = len;

    pdev->dev.device_state = USB_EP0_DATA_OUT;

    return ret;
}

/**
  * @brief  USBD_CtlContinueRx
  *         continue receive data on the ctl pipe
  * @param  pdev: USB device instance
  * @param  buff: pointer to data buffer
  * @param  len: length of data to be received
  * @retval status
  */
USBD_Status  USBD_CtlContinueRx (USB_CORE_HANDLE  *pdev, 
                                          uint8_t *pbuf,                                          
                                          uint16_t len)
{
    USBD_Status ret = USBD_OK;

    DCD_EP_PrepareRx (pdev,
                      0,
                      pbuf,
                      len);
    return ret;
}
/**
  * @brief  USBD_CtlSendStatus
  *         send zero length packet on the ctl pipe
  * @param  pdev: USB device instance
  * @retval status
  */
USBD_Status  USBD_CtlSendStatus(USB_CORE_HANDLE  *pdev)
{
    USBD_Status ret = USBD_OK;
    
    SetEP0DataEnd();
    
    return ret;
}

/**
  * @brief  USBD_GetRxCount
  *         returns the received data length
  * @param  pdev: USB device instance
  *         epnum: endpoint index
  * @retval Rx Data blength
  */
uint16_t  USBD_GetRxCount(USB_CORE_HANDLE *pdev, uint8_t epnum)
{
    return pdev->dev.out_ep[epnum].xfer_count;
}

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
