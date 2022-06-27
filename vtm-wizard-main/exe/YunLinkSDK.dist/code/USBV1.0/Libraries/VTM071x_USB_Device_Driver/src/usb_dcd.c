/**
  ******************************************************************************
  * @file    usb_dcd.c
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   Device interface layer used by the library to access the core.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_dcd.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t wInterrupt_Mask=0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief Device Initialization
  * @param  pdev: device instance
  * @retval : None
  */
void DCD_Init(USB_CORE_HANDLE *pdev)
{
    /*Device is in Default State*/
    pdev->dev.device_state = USB_EP0_IDLE;
    pdev->dev.device_status = USB_DEFAULT;
    pdev->dev.device_address = 0;
    pdev->dev.DevRemoteWakeup = 0;

    pdev->dev.speed = USB_SPEED_FULL; /*kept for API compatibility reason*/

    /* Power = 0 */
    SetPower(0);

    /*Clear pending interrupts*/
    GetIntrUSB();
    GetIntrRx();
    GetIntrTx();

    /*set wInterrupt_Mask global variable, USB Device*/
    wInterrupt_Mask = USB_INTR_DISCONNECT | USB_INTR_SOF | USB_INTR_RESET | USB_INTR_RESUME | USB_INTR_SUSPEND;

    /*Set interrupt mask*/
    SetIntrUSBE(wInterrupt_Mask); 
}


/**
  * @brief Stop device
  * @param  pdev: device instance
  * @retval : None
  */
void DCD_StopDevice(USB_CORE_HANDLE *pdev)
{
    /*Disable all interrupts*/
    SetIntrUSBE(0); 
    
    /*Clear pending interrupts*/
    GetIntrUSB();
    GetIntrRx();
    GetIntrTx();
    
    /* AddR = 0 */
    SetFADDR(0);

    /*Device is in default state*/
    pdev->dev.device_status  = USB_DEFAULT;
}

/**
  * @brief Configure PMA for EP
  * @param  pdev : Device instance
  * @param  ep_addr: endpoint address
  * @param  ep_Kind: endpoint Kind
  *                @arg USB_SNG_BUF: Single Buffer used
  *                @arg USB_DBL_BUF: Double Buffer used
  * @param  pmaadress: EP address in The PMA: In case of single buffer endpoint
  * @retval : status
  */
uint32_t DCD_PMA_Config(USB_CORE_HANDLE *pdev,
                        uint16_t ep_addr,
                        uint16_t ep_kind,
                        uint32_t pmaadress)
{
    USB_EP *ep;
    
    /* initialize ep structure*/
    if ((ep_addr & 0x80) == 0x80)
    {
        ep = &pdev->dev.in_ep[ep_addr & 0x7F];
    }
    else
    {
        ep = &pdev->dev.out_ep[ep_addr & 0x7F];
    }

    ep->doublebuffer = ep_kind;
    ep->pmaadress = pmaadress;

    return USB_OK; 
}

/**
  * @brief Configure an EP
  * @param  pdev : Device instance
  * @param  ep_addr: endpoint address
  * @param  ep_mps: endpoint max packet size
  * @param  ep_type: endpoint Type
  */
uint32_t DCD_EP_Open(USB_CORE_HANDLE *pdev , 
                     uint16_t ep_addr,
                     uint16_t ep_mps,
                     uint8_t ep_type)
{
    USB_EP *ep;

    /* initialize ep structure*/
    if ((ep_addr & 0x80) == 0x80)
    {
        ep = &pdev->dev.in_ep[ep_addr & 0x7F];
    }
    else
    {
        ep = &pdev->dev.out_ep[ep_addr & 0x7F];
    }

    ep->maxpacket = ep_mps;
    ep->type      = ep_type;
    ep->num       = ep_addr & 0x7F;

    if (ep->num == 0)
    {
        /* Initialize the control transfer variables*/ 
        ep->ctl_data_len   = 0;
        ep->total_data_len = 0;
    }

    /* Initialize the transaction level variables */
    ep->xfer_buff  = 0;
    ep->xfer_len   = 0;
    ep->xfer_count = 0;
    ep->is_stall   = 0;

    /* initialize HW */
    SetIndex(ep->num);
    
    if (ep_addr & 0x80)
    {
        /*Set the endpoint Transmit buffer address and size */
        SetEPnTxAddrAndSize(ep->pmaadress, ep->maxpacket, ep->doublebuffer);
        if (ep->num != 0)
        {
            SetEPnTxMAXP(ep->maxpacket);    //Set max packet size
            SetIntrTxE(1 << ep->num);       //Enable endpoint intrrupt
            SetEPnTxMode(1);                //Enable tx FIFO
            SetEPnTxType(ep->type);
            
            /* Flush tx fifo */
            if (GetEPnTxFIFONotEmpty())
            {
                FlushEPnTxFIFO();
                if (ep->doublebuffer)
                    FlushEPnTxFIFO();
            }
            
            ClearEPnTxDataTog();
        }
        else
        {
            SetIntrTxE(1 << 0);       //Enable endpoint0 intrrupt
        }
    }
    else
    {
        /*Set the endpoint Transmit buffer address and size */
        SetEPnRxAddrAndSize(ep->pmaadress, ep->maxpacket, ep->doublebuffer);
        if (ep->num != 0)
        {
            SetEPnRxMAXP(ep->maxpacket);
            SetIntrRxE(1 << ep->num);
            
            ClearEPnRxDataTog();
            SetEPnRxType(ep->type);

            /* Flush rx fifo */
            if (GetEPnRxFIFOFull())
            {
                FlushEPnRxFIFO();
                if (ep->doublebuffer)
                    FlushEPnRxFIFO();
            }
        }
        else
        {
            SetIntrTxE(1 << 0);       //Enable endpoint0 intrrupt
        }
    }

    return USB_OK;
}

/**
  * @brief called when an EP is disabled
  * @param  pdev: device instance
  * @param  ep_addr: endpoint address
  * @retval : status
  */
uint32_t DCD_EP_Close(USB_CORE_HANDLE *pdev , uint8_t  ep_addr)
{
    if ((ep_addr&0x80) == 0x80)
    {
        /*Clear the endpoint Transmit buffer address and size */
        SetEPnTxAddrAndSize(0, 0, 0);
    }
    else
    {
        /*Set the endpoint Transmit buffer address and size */
        SetEPnRxAddrAndSize(0, 0, 0);
    }
    
    return USB_OK;
}


/**
  * @brief DCD_EP_PrepareRx
  * @param  pdev: device instance
  * @param  ep_addr: endpoint address
  * @param  pbuf: pointer to Rx buffer
  * @param  buf_len: data length
  * @retval : status
  */
uint32_t DCD_EP_PrepareRx(USB_CORE_HANDLE *pdev,
                          uint8_t  ep_addr,
                          uint8_t  *pbuf,                        
                          uint16_t buf_len)
{
    __IO uint32_t len = 0; 
    USB_EP *ep = &pdev->dev.out_ep[ep_addr & 0x7F];

    /*setup and start the Xfer */
    ep->xfer_buff = pbuf;
    ep->xfer_len = buf_len;
    ep->xfer_count = 0;

    /*Multi packet transfer*/
    if (ep->xfer_len > ep->maxpacket)
    {
        len=ep->maxpacket;
        ep->xfer_len-=len; 
    }
    else
    {
        len=ep->xfer_len;
        ep->xfer_len =0;
    }

    return USB_OK;
}

/**
  * @brief Transmit data Buffer
  * @param  pdev: device instance
  * @param  ep_addr: endpoint address
  * @param  pbuf: pointer to Tx buffer
  * @param  buf_len: data length
  * @retval : status
  */
uint32_t  DCD_EP_Tx( USB_CORE_HANDLE *pdev,
                     uint8_t  ep_addr,
                     uint8_t  *pbuf,
                     uint32_t buf_len)
{
    __IO uint32_t len = 0; 
    USB_EP *ep = &pdev->dev.in_ep[ep_addr & 0x7F];

    /* configure and validate Tx endpoint */
    SetIndex(ep->num);

    /*setup and start the Xfer */
    ep->xfer_buff = pbuf;
    ep->xfer_len = buf_len;

    /*Multi packet transfer*/
    if (ep->xfer_len >= ep->maxpacket)
    {
        len = ep->maxpacket;
        ep->xfer_len -= len;
    }
    else
    {
        len = ep->xfer_len;
        ep->xfer_len = 0;
    }
    
    CopyDataToEP(ep->num, ep->xfer_buff, len);
    SetTxPktRdy(ep->num);
    
    if (ep->num == 0)
    {
        if (len < ep->maxpacket)
        {
            SetEP0DataEnd();
            ep->ctl_data_len = 0;
            ep->total_data_len = 0;
            pdev->dev.device_state = USB_EP0_IDLE;
        }
    }
    
    ep->busy = 1;
    ep->xfer_buff += len;
    
    return USB_OK;
}


/**
  * @brief Stall an endpoint.
  * @param  pdev: device instance
  * @param  epnum: endpoint address
  * @retval : status
  */
uint32_t DCD_EP_Stall(USB_CORE_HANDLE *pdev, uint8_t epnum)
{
    USB_EP *ep;
    
    if ((0x80 & epnum) == 0x80)
    {
        ep = &pdev->dev.in_ep[epnum & 0x7F];
    }
    else
    {
        ep = &pdev->dev.out_ep[epnum];
    }

    SetIndex(epnum&0x7F);
    
    /*Endpoint is stalled */
    ep->is_stall = 1;

    if (ep->num ==0)
    {
        /* This macro sets STALL status for RX & TX*/ 
        SetEP0SendStall();
    }
    else if (0x80 & epnum)
    {
        /* IN Endpoint stalled */
        SetEPnTxSendStall();
    }
    else
    {
        /* OUT Endpoint stalled */
        SetEPnRxSendStall();
    }
    
    return USB_OK;
}


/**
  * @brief Clear stall condition on endpoints.
  * @param  pdev: device instance
  * @param  epnum: endpoint address
  * @retval : status
  */
uint32_t  DCD_EP_ClrStall (USB_CORE_HANDLE *pdev, uint8_t epnum)
{
    USB_EP *ep;
    
    if (!(epnum & 0x7F))
    {
        return USB_OK;
    }

    if ((0x80 & epnum) == 0x80)
    {
        ep = &pdev->dev.in_ep[epnum & 0x7F];
        ClearEPnTxFrcDataTog();
        ClearEPnTxSendStall();
        ep->is_stall = 0;
    }
    else
    {
        ep = &pdev->dev.out_ep[epnum];
        ClearEPnRxDataTog();
        ClearEPnRxSentStall();
        ep->is_stall = 0;
    } 

    return USB_OK;
}

/**
  * @brief This Function set USB device address
  * @param  pdev: device instance
  * @param  address: new device address
  */
void  DCD_EP_SetAddress (USB_CORE_HANDLE *pdev, uint8_t address)
{
    pdev->dev.device_address = address;
  
    SetFADDR(address);
}

/**
  * @brief Connect device (enable internal pull-up)
  * @param  pdev: device instance
  * @retval : None
  */
void  DCD_DevConnect (USB_CORE_HANDLE *pdev)
{
    /*Device is in default state*/
    pdev->dev.device_status  = USB_DEFAULT;
}

/**
  * @brief Disconnect device (disable internal pull-up)
  * @param  pdev: device instance
  * @retval : None
  */
void  DCD_DevDisconnect (USB_CORE_HANDLE *pdev)
{
    /* Disable DP Pull-Down bit*/

    
    /*Device is in unconnected state*/
    pdev->dev.device_status  = USB_UNCONNECTED;
}

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
