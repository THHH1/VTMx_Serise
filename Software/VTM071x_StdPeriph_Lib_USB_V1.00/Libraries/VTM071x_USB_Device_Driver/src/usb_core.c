/**
  ******************************************************************************
  * @file    usb_core.c
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   This file provides the interface functions to USB cell registers
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_core.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Set the FADDR register value
  * @param  wRegValue: new register value
  * @retval None
  */
void SetFADDR(uint8_t wRegValue)
{
    USB_Common->FAddr = wRegValue & 0x7F;
}

/**
  * @brief  Set the POWER register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetPower(uint8_t wRegValue)
{
    USB_Common->Power = wRegValue;
}

/**
  * @brief  returns the POWER register value 
  * @param  None
  * @retval POWER register Value
  */
uint8_t GetPower(void)
{
    return (USB_Common->Power);
}

/**
  * @brief  Set the IntrTxE register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetIntrTxE(uint8_t wRegValue)
{
    USB_Common->IntrTxE |= wRegValue;
}

/**
  * @brief  returns the IntrTxE register value 
  * @param  None
  * @retval IntrTxE register Value
  */
uint8_t GetIntrTxE(void)
{
    return (USB_Common->IntrTxE);
}

/**
  * @brief  Set the IntrRxE register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetIntrRxE(uint8_t wRegValue)
{
    USB_Common->IntrRxE |= wRegValue;
}

/**
  * @brief  returns the IntrRxE register value 
  * @param  None
  * @retval IntrRxE register Value
  */
uint8_t GetIntrRxE(void)
{
    return (USB_Common->IntrRxE);
}

/**
  * @brief  Set the IntrUSBE register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetIntrUSBE(uint8_t wRegValue)
{
    USB_Common->IntrUSBE = wRegValue;
}

/**
  * @brief  returns the IntrUSBE register value 
  * @param  None
  * @retval IntrUSBE register Value
  */
uint8_t GetIntrUSBE(void)
{
    return (USB_Common->IntrUSBE);
}

/**
  * @brief  returns the IntrTx register value 
  * @param  None
  * @retval IntrTx register Value
  */
uint8_t GetIntrTx(void)
{
    return (USB_Common->IntrTx);
}

/**
  * @brief  returns the IntrRx register value 
  * @param  None
  * @retval IntrRx register Value
  */
uint8_t GetIntrRx(void)
{
    return (USB_Common->IntrRx);
}

/**
  * @brief  returns the IntrUSB register value 
  * @param  None
  * @retval IntrUSB register Value
  */
uint8_t GetIntrUSB(void)
{
    return (USB_Common->IntrUSB);
}

/**
  * @brief  returns the Frame register value 
  * @param  None
  * @retval Frame register Value
  */
uint16_t GetFrame(void)
{
    uint16_t reg;
    
    reg = (USB_Common->Frame2) & 0x7;
    reg = (reg << 8) | (USB_Common->Frame1);
    
    return reg;
}

/**
  * @brief  Set the Index register value 
  * @param  RegValue: new register value
  * @retval None
  */
void SetIndex(uint8_t RegValue)
{
    USB_Common->Index = RegValue;
}

/**
  * @brief  returns the Index register value 
  * @param  None
  * @retval Index register Value
  */
uint8_t GetIndex(void)
{
    return (USB_Common->Index);
}

/**
  * @brief  Set the DevCtl register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetDevCtl(uint8_t wRegValue)
{
    USB_Common->DevCtl = wRegValue;
}

/**
  * @brief  returns the DevCtl register value 
  * @param  None
  * @retval DevCtl register Value
  */
uint8_t GetDevCtl(void)
{
    return (USB_Common->DevCtl);
}

/**
  * @brief  Set the EP0CSR1 register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetEP0CSR1(uint8_t wRegValue)
{
    USB_EP0->CSR1 = wRegValue;
}

/**
  * @brief  returns the EP0CSR1 register value 
  * @param  None
  * @retval EP0CSR1 register Value
  */
uint8_t GetEP0CSR1(void)
{
    return (USB_EP0->CSR1);
}

/**
  * @brief  Set the EP0CSR2 register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetEP0CSR2(uint8_t wRegValue)
{
    USB_EP0->CSR2 = wRegValue;
}

/**
  * @brief  returns the EP0CSR2 register value 
  * @param  None
  * @retval EP0CSR2 register Value
  */
uint8_t GetEP0CSR2(void)
{
    return (USB_EP0->CSR2);
}

/**
  * @brief  returns the EP0Count register value 
  * @param  None
  * @retval EP0Count register Value
  */
uint8_t GetEP0RxCount(void)
{
    return (USB_EP0->Count);
}

/**
  * @brief  Set the EPnTxCSR1 register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetEPnTxCSR1(uint8_t wRegValue)
{
    USB_EPN->TxCSR1 = wRegValue;
}

/**
  * @brief  returns the EPnTxCSR1 register value 
  * @param  None
  * @retval EPnTxCSR1 register Value
  */
uint8_t GetEPnTxCSR1(void)
{
    return (USB_EPN->TxCSR1);
}

/**
  * @brief  Set the EPnTxCSR2 register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetEPnTxCSR2(uint8_t wRegValue)
{
    USB_EPN->TxCSR2 = wRegValue;
}

/**
  * @brief  returns the EPnTxCSR2 register value 
  * @param  None
  * @retval EPnTxCSR2 register Value
  */
uint8_t GetEPnTxCSR2(void)
{
    return (USB_EPN->TxCSR2);
}

/**
  * @brief  Set the EPnRxCSR1 register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetEPnRxCSR1(uint8_t wRegValue)
{
    USB_EPN->RxCSR1 = wRegValue;
}

/**
  * @brief  returns the EPnRxCSR1 register value 
  * @param  None
  * @retval EPnRxCSR1 register Value
  */
uint8_t GetEPnRxCSR1(void)
{
    return (USB_EPN->RxCSR1);
}

/**
  * @brief  Set the EPnRxCSR2 register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetEPnRxCSR2(uint8_t wRegValue)
{
    USB_EPN->RxCSR2 = wRegValue;
}

/**
  * @brief  returns the EPnRxCSR2 register value 
  * @param  None
  * @retval EPnRxCSR2 register Value
  */
uint8_t GetEPnRxCSR2(void)
{
    return (USB_EPN->RxCSR2);
}

/**
  * @brief  returns the EPnCount register value 
  * @param  None
  * @retval EPnCount register Value
  */
uint8_t GetEPnRxCount(void)
{
    uint16_t reg;
    
    reg = (USB_EPN->RxCount2) & 0x7;
    reg = (reg << 8) | (USB_EPN->RxCount1);
    
    return reg;
}

/**
  * @brief  Copy Data to EP 
  * @param  EP_n: can be USB_EP_x(0-7)
  *         buf: buffer
  *         size: size
  * @retval None
  */
void CopyDataToEP(uint8_t EP_n, uint8_t *buf, uint32_t size)
{
    volatile uint8_t *FIFOn = (volatile uint8_t *)(USB_FIFO_Base + EP_n * 0x4);
    int i;

    for (i=0; i<size; i++)
    {
        *FIFOn = buf[i];
    }
}

/**
  * @brief  Copy Data from EP 
  * @param  EP_n: Endpoint Number, can be USB_EP_x(0-7)
  *         buf: buffer
  *         size: size
  * @retval None
  */
void CopyDataFromEP(uint8_t EP_n, uint8_t *buf, uint32_t size)
{
    volatile uint8_t *FIFOn = (volatile uint8_t *)(USB_FIFO_Base + EP_n * 0x4);
    int i;
    
    for (i=0; i<size; i++)
    {
        buf[i] = *FIFOn;
    }
}

/**
  * @brief  Set the endpoint Tx buffer address and size.
  * @param  addr: Tx buffer address, it can be (0-0x7FF8)
  * @param  size: Tx buffer size, it can be 8, 16, 32, 64, 128, 256, 512, 1024
  * @param  dpb: Defines whether double-packet buffering supported.
  * @retval None.
  */
void SetEPnTxAddrAndSize(uint16_t addr, uint16_t size, uint8_t dpb)
{
    uint16_t reg;
    uint8_t tmp;
    
    switch(size)
    {
        case 8:
            tmp = FIFO_SIZE_8;
            break;
        case 16:
            tmp = FIFO_SIZE_16;
            break;
        case 32:
            tmp = FIFO_SIZE_32;
            break;
        case 64:
            tmp = FIFO_SIZE_64;
            break;
        case 128:
            tmp = FIFO_SIZE_128;
            break;
        case 256:
            tmp = FIFO_SIZE_256;
            break;
        case 512:
            tmp = FIFO_SIZE_512;
            break;
        case 1024:
            tmp = FIFO_SIZE_1024;
            break;
        default:
            tmp = FIFO_SIZE_64;
            break;
    }
    
    reg = addr >> 3;
    USB_EPN->TXFIFO1 = (uint8_t)(reg & 0xFF);
    
    reg = (reg >> 8) & 0xF;
    if (dpb)
        reg |= (1<<4);
    reg |= tmp;
    
    USB_EPN->TXFIFO2 = reg;
}

/**
  * @brief  Set the endpoint Rx buffer address and size.
  * @param  addr: Rx buffer address, it can be (0-0x7FF8)
  * @param  size: Rx buffer size, it can be 8, 16, 32, 64, 128, 256, 512, 1024
  * @param  dpb: Defines whether double-packet buffering supported.
  * @retval None.
  */
void SetEPnRxAddrAndSize(uint16_t addr, uint16_t size, uint8_t dpb)
{
    uint16_t reg;
    uint8_t tmp;
    
    switch(size)
    {
        case 8:
            tmp = FIFO_SIZE_8;
            break;
        case 16:
            tmp = FIFO_SIZE_16;
            break;
        case 32:
            tmp = FIFO_SIZE_32;
            break;
        case 64:
            tmp = FIFO_SIZE_64;
            break;
        case 128:
            tmp = FIFO_SIZE_128;
            break;
        case 256:
            tmp = FIFO_SIZE_256;
            break;
        case 512:
            tmp = FIFO_SIZE_512;
            break;
        case 1024:
            tmp = FIFO_SIZE_1024;
            break;
        default:
            tmp = FIFO_SIZE_64;
            break;
    }    
    
    reg = addr >> 3;
    USB_EPN->RXFIFO1 = (uint8_t)(reg & 0xFF);
    
    reg = (reg >> 8) & 0xF;
    if (dpb)
        reg |= (1<<4);
    reg |= tmp;
    
    USB_EPN->RXFIFO2 = reg;
}

/**
  * @brief  Clear EP0 RxPktRdy
  * @param  None
  * @retval None
  */
void ClearEP0RxPktRdy(void)
{
    USB_EP0->CSR1 |= USB_CSR0_SERVICED_RX_PKG_RDY;
}

/**
  * @brief  Set EP0 TxPktRdy
  * @param  None
  * @retval None
  */
void SetEP0TxPktRdy(void)
{
    USB_EP0->CSR1 |= USB_CSR0_TX_PKT_RDY;
}

/**
  * @brief  Clear EP0 SentStall
  * @param  None
  * @retval None
  */
void ClearEP0SentStall(void)
{
    USB_EP0->CSR1 &= ~USB_CSR0_SENT_STALL;
}

/**
  * @brief  Set EP0 DataEnd
  * @param  None
  * @retval None
  */
void SetEP0DataEnd(void)
{
    if (!(USB_EP0->CSR1 & USB_CSR0_DATA_END))
        USB_EP0->CSR1 |= USB_CSR0_DATA_END;
}

/**
  * @brief  Clear EP0 SetupEnd
  * @param  None
  * @retval None
  */
void ClearEP0SetupEnd(void)
{
    USB_EP0->CSR1 |= USB_CSR0_SERVICED_SETUP_END;
}

/**
  * @brief  Send EP0 Stall
  * @param  None
  * @retval None
  */
void SetEP0SendStall(void)
{
    USB_EP0->CSR1 |= USB_CSR0_SEND_STALL;
}

/**
  * @brief  Set the EPnTxMAXP register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetEPnTxMAXP(uint8_t wRegValue)
{
    USB_EPN->TxMAXP = wRegValue;
}

/**
  * @brief  returns the EPnTxMAXP register value 
  * @param  None
  * @retval EPnTxMAXP register Value
  */
uint8_t GetEPnTxMAXP(void)
{
    return (USB_EPN->TxMAXP);
}

/**
  * @brief  Set the EPnRxMAXP register value 
  * @param  wRegValue: new register value
  * @retval None
  */
void SetEPnRxMAXP(uint8_t wRegValue)
{
    USB_EPN->RxMAXP = wRegValue;
}

/**
  * @brief  returns the EPnRxMAXP register value 
  * @param  None
  * @retval EPnRxMAXP register Value
  */
uint8_t GetEPnRxMAXP(void)
{
    return (USB_EPN->RxMAXP);
}

/**
  * @brief  Clear the Tx endpoint data toggle to 0 
  * @param  None
  * @retval None
  */
void ClearEPnTxDataTog(void)
{
    USB_EPN->TxCSR1 |= USB_TXCSR1_CLR_DATA_TOG;
}

/**
  * @brief  Clear TXCSR1 SentStall bit 
  * @param  None
  * @retval None
  */
void ClearEPnTxSentStall(void)
{
    USB_EPN->TxCSR1 &= ~USB_TXCSR1_SENT_STALL;
}

/**
  * @brief  Set TXCSR1 SendStall bit 
  * @param  None
  * @retval None
  */
void SetEPnTxSendStall(void)
{
    USB_EPN->TxCSR1 |= USB_TXCSR1_SEND_STALL;
}

/**
  * @brief  Clear TXCSR1 SendStall bit 
  * @param  None
  * @retval None
  */
void ClearEPnTxSendStall(void)
{
    USB_EPN->TxCSR1 &= ~USB_TXCSR1_SEND_STALL;
}

/**
  * @brief  Flush EPn TX FIFO 
  * @param  None
  * @retval None
  */
void FlushEPnTxFIFO(void)
{
    USB_EPN->TxCSR1 |= USB_TXCSR1_FLUSH_FIFO;
}

/**
  * @brief  Clear TXCSR1 UnderRun bit 
  * @param  None
  * @retval None
  */
void ClearEPnTxUnderRun(void)
{
    USB_EPN->TxCSR1 &= ~USB_TXCSR1_UNDER_RUN;
}

/**
  * @brief  Get TX FIFO state 
  * @param  None
  * @retval None
  */
uint8_t GetEPnTxFIFONotEmpty(void)
{
    if (USB_EPN->TxCSR1 & USB_TXCSR1_FIFO_NOT_EMPTY)
        return 1;
    else
        return 0;
}

/**
  * @brief  Get TxRdy state 
  * @param  None
  * @retval None
  */
uint8_t GetEPnTxRdyState(void)
{
    if (USB_EPN->TxCSR1 & USB_TXCSR1_TX_PKT_RDY)
        return 1;
    else
        return 0;
}

/**
  * @brief  Set TxPktRdy bit
  * @param  None
  * @retval None
  */
void SetEPnTxPktRdy(void)
{
    USB_EPN->TxCSR1 |= USB_TXCSR1_TX_PKT_RDY;
}

/**
  * @brief  Set TXCSR2 AutoSet bit
  * @param  None
  * @retval None
  */
void SetEPnTxAutoSet(void)
{
    USB_EPN->TxCSR2 |= USB_TXCSR2_AUTO_SET;
}

/**
  * @brief  Clear TXCSR2 AutoSet bit
  * @param  None
  * @retval None
  */
void ClearEPnTxAutoSet(void)
{
    USB_EPN->TxCSR2 &= ~USB_TXCSR2_AUTO_SET;
}

/**
  * @brief  sets the type.
  * @param  wType: type definition
  * @retval None.
  */
void SetEPnTxType(uint8_t Type)
{
    if (Type == USB_EP_ISOC)
        USB_EPN->TxCSR2 |= USB_TXCSR2_ISO;
    else
        USB_EPN->TxCSR2 &= ~USB_TXCSR2_ISO;
    
    if ((Type == USB_EP_BULK) || (Type == USB_EP_ISOC))
        ClearEPnTxFrcDataTog();
    else if (Type == USB_EP_INT)
        SetEPnTxFrcDataTog();
}

/**
  * @brief  Set this bit to enable the DMA request for Tx endpoint
  * @param  None
  * @retval None
  */
void SetEPnTxDMAEnab(void)
{
    USB_EPN->TxCSR2 |= USB_TXCSR2_DMA_ENABLE;
}

/**
  * @brief  Clear this bit to disable the DMA request for Tx endpoint
  * @param  None
  * @retval None
  */
void ClearEPnTxDMAEnab(void)
{
    USB_EPN->TxCSR2 &= ~USB_TXCSR2_DMA_ENABLE;
}

/**
  * @brief  Set this bit to force the endpoint data toggle
  * @param  None
  * @retval None
  */
void SetEPnTxFrcDataTog(void)
{
    USB_EPN->TxCSR2 |= USB_TXCSR2_FRC_DATA_TOG;
}

/**
  * @brief  Clear TXCSR2 FrcDataTog bit
  * @param  None
  * @retval None
  */
void ClearEPnTxFrcDataTog(void)
{
    USB_EPN->TxCSR2 &= ~USB_TXCSR2_FRC_DATA_TOG;
}

/**
  * @brief  Set Tx dma mode
  * @param  None
  * @retval None
  */
void SetEPnTxDMAMode(uint8_t Mode)
{
    if (Mode)
        USB_EPN->TxCSR2 |= USB_TXCSR2_DMA_MODE;
    else
        USB_EPN->TxCSR2 &= ~USB_TXCSR2_DMA_MODE;
}

/**
  * @brief  Set Tx mode
  * @param  None
  * @retval None
  */
void SetEPnTxMode(uint8_t Mode)
{
    if (Mode)
        USB_EPN->TxCSR2 |= USB_TXCSR2_MODE;
    else
        USB_EPN->TxCSR2 &= ~USB_TXCSR2_MODE;
}

/**
  * @brief  Clear the Rx endpoint data toggle to 0 
  * @param  None
  * @retval None
  */
void ClearEPnRxDataTog(void)
{
    USB_EPN->RxCSR1 |= USB_RXCSR1_CLR_DATA_TOG;
}

/**
  * @brief  Clear RXCSR1 SentStall bit 
  * @param  None
  * @retval None
  */
void ClearEPnRxSentStall(void)
{
    USB_EPN->RxCSR1 &= ~USB_RXCSR1_SENT_STALL;
}

/**
  * @brief  Set RXCSR1 SendStall bit 
  * @param  None
  * @retval None
  */
void SetEPnRxSendStall(void)
{
    USB_EPN->RxCSR1 |= USB_RXCSR1_SEND_STALL;
}

/**
  * @brief  Clear RXCSR1 SendStall bit 
  * @param  None
  * @retval None
  */
void ClearEPnRxSendStall(void)
{
    USB_EPN->RxCSR1 &= ~USB_RXCSR1_SEND_STALL;
}

/**
  * @brief  Flush EPn RX FIFO 
  * @param  None
  * @retval None
  */
void FlushEPnRxFIFO(void)
{
    USB_EPN->RxCSR1 |= USB_RXCSR1_FLUSH_FIFO;
}

/**
  * @brief  Get Rx data error state 
  * @param  None
  * @retval None
  */
uint8_t GetEPnRxDataError(void)
{
    if (USB_EPN->RxCSR1 & USB_RXCSR1_DATA_ERROR)
        return 1;
    else
        return 0;
}

/**
  * @brief  Clear RXCSR1 UnderRun bit 
  * @param  None
  * @retval None
  */
void ClearEPnRxOverRun(void)
{
    USB_EPN->RxCSR1 &= ~USB_RXCSR1_OVER_RUN;
}

/**
  * @brief  Get Rx FIFOFull state 
  * @param  None
  * @retval None
  */
uint8_t GetEPnRxFIFOFull(void)
{
    if (USB_EPN->RxCSR1 & USB_RXCSR1_FIFO_FULL)
        return 1;
    else
        return 0;
}

/**
  * @brief  Clear RxPktRdy bit
  * @param  None
  * @retval None
  */
void ClearEPnRxPktRdy(void)
{
    USB_EPN->RxCSR1 &= ~USB_RXCSR1_RX_PKT_RDY;
}

/**
  * @brief  Set RXCSR2 AutoClear bit
  * @param  None
  * @retval None
  */
void SetEPnRxAutoClear(void)
{
    USB_EPN->RxCSR2 |= USB_RXCSR2_AUTO_CLEAR;
}

/**
  * @brief  Clear RXCSR2 AutoClear bit
  * @param  None
  * @retval None
  */
void ClearEPnRxAutoClear(void)
{
    USB_EPN->RxCSR2 &= ~USB_RXCSR2_AUTO_CLEAR;
}

/**
  * @brief  sets the Rx endpoint type.
  * @param  Type: type definition
  * @retval None.
  */
void SetEPnRxType(uint8_t Type)
{
    if (Type == USB_EP_ISOC)
        USB_EPN->RxCSR2 |= USB_RXCSR2_ISO;
    else
        USB_EPN->RxCSR2 &= ~USB_RXCSR2_ISO;
}

/**
  * @brief  Set this bit to enable the DMA request for Rx endpoint
  * @param  None
  * @retval None
  */
void SetEPnRxDMAEnab(void)
{
    USB_EPN->RxCSR2 |= USB_RXCSR2_DMA_ENABLE;
}

/**
  * @brief  Clear this bit to disable the DMA request for Rx endpoint
  * @param  None
  * @retval None
  */
void ClearEPnRxDMAEnab(void)
{
    USB_EPN->RxCSR2 &= ~USB_RXCSR2_DMA_ENABLE;
}

/**
  * @brief  Set Rx dma mode
  * @param  None
  * @retval None
  */
void SetEPnRxDMAMode(uint8_t Mode)
{
    if (Mode)
        USB_EPN->RxCSR2 |= USB_RXCSR2_DMA_MODE;
    else
        USB_EPN->RxCSR2 &= ~USB_RXCSR2_DMA_MODE;
}

/**
  * @brief  Set TxPktRdy bit
  * @param  EPn: Endpoint number
  * @retval None
  */
void SetTxPktRdy(uint8_t EPn)
{
//    uint8_t reg;
    
    if (EPn == 0)
    {        
        USB_EP0->CSR1 |= USB_CSR0_TX_PKT_RDY;
    }
    else
    {
        USB_EPN->TxCSR1 |= USB_TXCSR1_TX_PKT_RDY;
    }
}

/**
  * @brief  Clear RxPktRdy bit
  * @param  EPn: Endpoint number
  * @retval None
  */
void ClearEPRxPktRdy(uint8_t EPn)
{
    if (EPn == 0)
    {
        USB_EP0->CSR1 |= USB_CSR0_SERVICED_RX_PKG_RDY;
    }
    else
    {
        USB_EPN->RxCSR1 &= ~USB_RXCSR1_RX_PKT_RDY;
    }
}

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
