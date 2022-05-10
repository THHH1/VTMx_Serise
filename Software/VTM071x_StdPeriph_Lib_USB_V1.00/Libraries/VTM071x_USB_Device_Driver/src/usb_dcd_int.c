/**
  ******************************************************************************
  * @file    usb_dcd_int.c
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   This file provides the interrupt subroutines for the Device
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_dcd_int.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  MIN(a, b)      (((a) < (b)) ? (a) : (b))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern USB_CORE_HANDLE  USB_Device_dev;
extern uint32_t wInterrupt_Mask;
extern uint32_t ADDRESS;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Correct Transfer interrupt's service
  * @param  None
  * @retval None
  */
void EP0_IdleProcess(USB_EP *ep, uint8_t csr)
{
    if (csr & USB_CSR0_RX_PKT_RDY)
    {
        ep = &((&USB_Device_dev)->dev.out_ep[USB_EP_0]);

        /* Get SETUP Packet*/
        ep->xfer_count = GetEP0RxCount();
        CopyDataFromEP(USB_EP_0, &((&USB_Device_dev)->dev.setup_packet[0]), ep->xfer_count);
        
        /* Clear RxPktRdy bit */
        ClearEPRxPktRdy(USB_EP_0);
        
        /* Process SETUP Packet*/
        USBD_DCD_INT_fops->SetupStage(&USB_Device_dev);
    }
}

void EP0_TxProcess(void)
{
    /* Process Control Data IN Packet*/
    USBD_DCD_INT_fops->DataInStage(&USB_Device_dev, USB_EP_0);
}

void EP0_RxProcess(void)
{
    USB_EP *ep;
    
    uint8_t csr = GetEP0CSR1();
    
    if (csr & USB_CSR0_RX_PKT_RDY)
    {
        ep = &((&USB_Device_dev)->dev.out_ep[USB_EP_0]);

        /* Get Control Data OUT Packet*/
        ep->xfer_count = GetEP0RxCount();

        if (ep->xfer_count != 0)
        {
            CopyDataFromEP(USB_EP_0, ep->xfer_buff, ep->xfer_count);
            ep->xfer_buff += ep->xfer_count;
        }

        /* Clear RxPktRdy bit */
        ClearEPRxPktRdy(USB_EP_0);

        /* Process Control Data OUT Packet*/
        USBD_DCD_INT_fops->DataOutStage(&USB_Device_dev, 0x00);
    }
}

void EP_Isr(uint8_t tx_ep, uint8_t rx_ep)
{
    USB_CORE_HANDLE *pdev = &USB_Device_dev;
    USB_EP *ep;
    uint16_t i;
    uint8_t EPindex;
    uint8_t tx_intr_ep = tx_ep, rx_intr_ep = rx_ep;
    uint32_t count;
    
    /* stay in loop while pending interrupts */
    do
    {        
        /* endpoint 0 interrupt */
        if (tx_intr_ep & USB_INTR_EP0)
        {
            uint8_t csr1;
            
            SetIndex(0);
            
            ep = &((&USB_Device_dev)->dev.out_ep[USB_EP_0]);

            csr1 = GetEP0CSR1();

            /* Decode and service control endpoint interrupt */
            if (csr1 & USB_CSR0_SENT_STALL)
            {
                ClearEP0SentStall();
                ep->is_stall = 0;
                
                /* State-->IDLE */
                pdev->dev.device_state = USB_EP0_IDLE;
            }
            
            if (csr1 & USB_CSR0_SETUP_END)
            {
                ClearEP0SetupEnd();

                if ((pdev->dev.device_status == USB_ADDRESSED) && (ADDRESS != 0))
                {
                    DCD_EP_SetAddress(&USB_Device_dev, ADDRESS);
                    ADDRESS = 0;
                }
                
                /* State-->IDLE */
                pdev->dev.device_state = USB_EP0_IDLE;
            }

            if (pdev->dev.device_state == USB_EP0_IDLE)
            {
                EP0_IdleProcess(ep, csr1);
            }
            
            if (pdev->dev.device_state == USB_EP0_DATA_IN)
            {
                EP0_TxProcess();
            }
            
            if (pdev->dev.device_state == USB_EP0_DATA_OUT)
            {
                EP0_RxProcess();
            }
        }
        
        if (rx_intr_ep & 0xFE)
        {
            uint8_t rxcsr1;
            
            /* Get rx_ep number */
            for (i=1; i<8; i++)
            {
                rx_intr_ep >>= 1;
                if (rx_intr_ep & 0x1)
                {
                    EPindex = i;
                    SetIndex(EPindex);
                    break;
                }
            }

            ep = &((&USB_Device_dev)->dev.out_ep[EPindex]);
            ep->busy = 0;
            
            rxcsr1 = GetEPnRxCSR1();
            
            if (rxcsr1 & USB_RXCSR1_SENT_STALL)
            {
                ClearEPnRxSentStall();
                ClearEPnRxDataTog();
                
                ep->is_stall = 0;
            }

            if (rxcsr1 & USB_RXCSR1_OVER_RUN)
            {
                ClearEPnRxOverRun();
            }
            
            if (rxcsr1 & USB_RXCSR1_RX_PKT_RDY)
            {
                /* Get Control Data OUT Packet*/
                count = GetEPnRxCount();

                if (count != 0)
                {
                    CopyDataFromEP(EPindex, ep->xfer_buff, count);
                                        
                    ep->xfer_count += count;
                    ep->xfer_buff  += count;
                }

                /* Clear RxPktRdy bit */
                ClearEPRxPktRdy(EPindex);

                /* Process Control Data OUT Packet*/
                if ((ep->xfer_len == 0) || (ep->xfer_count < ep->maxpacket))
                {
                    /* RX COMPLETE */
                    USBD_DCD_INT_fops->DataOutStage(&USB_Device_dev, EPindex);
                }
                else
                {
                    DCD_EP_PrepareRx(&USB_Device_dev, ep->num, ep->xfer_buff, ep->xfer_len);
                }
            }
        }

        if (tx_intr_ep & 0xFE)
        {
            uint8_t txcsr1 = GetEPnTxCSR1();
            uint8_t txcsr2 = GetEPnTxCSR2();
            
            /* Get tx_ep number */
            for (i=1;i<8;i++)
            {
                tx_intr_ep >>= 1;
                if (tx_intr_ep & 0x1)
                {
                    EPindex = i;
                    SetIndex(EPindex);
                    break;
                }
            }

            ep = &((&USB_Device_dev)->dev.in_ep[EPindex]);
            ep->busy = 0;
                        
            if (txcsr1 & USB_TXCSR1_SENT_STALL)
            {
                ClearEPnTxSentStall();
                ClearEPnTxDataTog();
                
                ep->is_stall = 0;
            }
            
            if (txcsr1 & USB_TXCSR1_UNDER_RUN)
            {
                ClearEPnTxUnderRun();
                
            }

            /* Zero Length Packet? */
            if (ep->xfer_len == 0)
            {
                /* Process Control Data IN Packet*/
                USBD_DCD_INT_fops->DataInStage(&USB_Device_dev, EPindex);
            }
            else
            {
                DCD_EP_Tx(&USB_Device_dev,ep->num, ep->xfer_buff, ep->xfer_len);
            }
        }
        
    }while (((tx_intr_ep = GetIntrTx()) | (rx_intr_ep = GetIntrRx())) != 0);

}

/**
  * @brief ISTR events interrupt service routine
  * @param  None
  * @retval None
  */
void USB_Isr(void)
{
    volatile uint8_t usb_intr, tx_intr_ep, rx_intr_ep;

    tx_intr_ep = GetIntrTx();
    rx_intr_ep = GetIntrRx();
    usb_intr = GetIntrUSB();
//    devctl = GetDevCtl();
    
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & USB_INTR_RESUME)
    if (usb_intr & USB_INTR_RESUME & wInterrupt_Mask)
    {
        SetPower(GetPower() | 0x1);
        
        USBD_DCD_INT_fops->Resume(&USB_Device_dev);
    }
#endif
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    if (tx_intr_ep | rx_intr_ep)
    {
        EP_Isr(tx_intr_ep, rx_intr_ep);
    }
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & USB_INTR_RESET)
    if (usb_intr & USB_INTR_RESET & wInterrupt_Mask)
    {
        USBD_DCD_INT_fops->Reset(&USB_Device_dev);
        DCD_EP_SetAddress(&USB_Device_dev, 0);
        
        /*Set interrupt mask*/
        SetIntrUSBE(wInterrupt_Mask); 
        SetPower(GetPower() | 0x1);
    }
#endif
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & USB_INTR_SOF)
    if (usb_intr & USB_INTR_SOF & wInterrupt_Mask)
    {
        USBD_DCD_INT_fops->SOF(&USB_Device_dev);
    }
#endif
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & USB_INTR_DISCONNECT)
    if (usb_intr & USB_INTR_DISCONNECT & wInterrupt_Mask)
    {
        //
    }
#endif
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & USB_INTR_SUSPEND)
    if (usb_intr & USB_INTR_SUSPEND & wInterrupt_Mask)
    {
        /* process library core layer suspend routine*/
        USBD_DCD_INT_fops->Suspend(&USB_Device_dev); 
    }
#endif
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

} /* USB_Isr */


/************************ (C) COPYRIGHT MIC *****END OF FILE****/
