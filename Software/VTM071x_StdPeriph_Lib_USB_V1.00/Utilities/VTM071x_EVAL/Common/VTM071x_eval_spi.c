/**
  ******************************************************************************
  * @file    VTM071x_eval_spi.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides a set of functions needed to manage the SPI FLASH 
  *              mounted on VTM071x_EVAL evaluation board.
  *
  *          It implements a high level communication layer for read and write 
  *          from/to this memory. The needed MIC hardware resources (SPI and 
  *          GPIO) are defined in VTM071x_eval.h file, and the initialization is 
  *          performed in spi_LowLevel_Init() function declared in VTM071x_eval.c 
  *          file.
  *          You can easily tailor this driver to any other development board, 
  *          by just adapting the defines for hardware resources and 
  *          spi_LowLevel_Init() function. 
  *               
  *
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MIC SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************  
  */ 
#if 1
/* Includes ------------------------------------------------------------------*/
#include "VTM071x_eval_spi.h"
#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup VTM071x_EVAL
  * @{
  */

/** @addtogroup VTM071x_EVAL_SPI_FLASH
  * @brief      This file includes the SPI FLASH driver of VTM071x_EVAL boards.
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define SPI_FLASH_TX_RX_DMA

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup VTM071x_EVAL_SPI_FLASH_Private_Functions
  * @{
  */ 
#ifdef SPI_FLASH_TX_RX_DMA
#include "VTM071x_dma.h"

DmaChain* tx_dma_chain;
DmaChain* rx_dma_chain;
int rx_pkg_num = 1;
int tx_pkg_num = 1;

void i2s_dma_tx_pkg_config(uint32_t audio_frag_size);
void i2s_dma_rx_pkg_config(uint32_t audio_frag_size);


DmaPkg*  dma_llp_tx_vir;
DmaPkg*  dma_llp_rx_vir;
DmaPkg*  dma_llp_tx_phy;
DmaPkg*  dma_llp_rx_phy;

/* spi_tx_size小于等于511 */
void spi_dma_tx_pkg_config(uint32_t spi_tx_size)
{
	dma_llp_tx_vir[0].DAR    = (uint32_t)&SPI_X->DR;
    dma_llp_tx_vir[0].CTRL_L = 0x00000000
                            +(1<<0)	   //INT_EN
                            +(0<<1)	   //DST_TR_WIDTH 
                            +(0<<4)	   //SRC_TR_WIDTH
                            +(2<<7)	   //DINC 1x = No change
                            +(0<<9)	   //SINC 00 = Increment
                            +(0<<11)   //DEST_MSIZE
                            +(0<<14)   //SRC_MSIZE
                            +(1<<20)   //TT_FC 00=m2m,01=m2p,02=p2m,11=p2p
                            +(0<<23)   //DMS Destination Master interface.
                            +(0<<25)   //SMS source Master interface
                            +(0<<27)   //LLP_DST_DISABLE
                            +(0<<28);   //LLP_SRC_DISABLE
	dma_llp_tx_vir[0].CTRL_H = spi_tx_size;
}

/* spi_rx_size小于等于511 */
void spi_dma_rx_pkg_config(uint32_t spi_rx_size)
{
	dma_llp_rx_vir[0].SAR    = (uint32_t)&SPI_X->DR;
    dma_llp_rx_vir[0].CTRL_L = 0x00000000
                            +(1<<0)	   //INT_EN
                            +(0<<1)	   //DST_TR_WIDTH 
                            +(0<<4)	   //SRC_TR_WIDTH
                            +(0<<7)	   //DINC 1x = No change
                            +(2<<9)	   //SINC 00 = Increment
                            +(0<<11)   //DEST_MSIZE
                            +(0<<14)   //SRC_MSIZE
                            +(2<<20)   //TT_FC 00=m2m,01=m2p,02=p2m,11=p2p
                            +(0<<23)   //DMS Destination Master interface.
                            +(0<<25)   //SMS source Master interface
                            +(0<<27)   //LLP_DST_DISABLE
                            +(0<<28);   //LLP_SRC_DISABLE
	dma_llp_rx_vir[0].CTRL_H = spi_rx_size;
}
#endif

#if 0
/**
  * @brief  Write data to SPI FLASH.
  * @param  SendBuf: Specifies SRAM address.
  * @param  SendBytes: Specifies writing size.
  * @retval None
  */
static void SPI_FLASH_WriteBuf(void *SendBuf, uint32_t SendBytes)
{
	uint32_t Index;
	uint32_t DataLength;
	uint8_t *temp8 = (uint8_t *)SendBuf;
	uint16_t *temp16 = (uint16_t *)SendBuf;

	DataLength = (SPI_GetDataSize(SPI_X) <= 8)?8:16;
	if (DataLength == 8)
	{
		for (Index=0; Index<SendBytes; Index++)
		{
			while(SPI_GetFlagStatus(SPI_X, SPI_STATUS_Transmit_FIFO_Not_Full) != SET);
			SPI_SendData(SPI_X, (uint16_t)temp8[Index]);
		}
	}
	else
	{
		for (Index=0; Index<(SendBytes>>1); Index++)
		{
			while(SPI_GetFlagStatus(SPI_X, SPI_STATUS_Transmit_FIFO_Not_Full) != SET);
			SPI_SendData(SPI_X, temp16[Index]);
		}
	}

    while(SPI_GetFlagStatus(SPI_X, SPI_STATUS_Transmit_FIFO_Empty) != SET);
}

/**
  * @brief  Read data to SPI FLASH.
  * @param  RecBuf: Specifies SRAM address.
  * @param  RecBytes: Specifies writing size.
  * @retval None
  */
static void SPI_FLASH_ReadBuf(void *RecBuf, uint32_t RecBytes)
{
	uint32_t Index = 0, Num, i;
	uint32_t DataLength;
	uint8_t *temp8 = (uint8_t *)RecBuf;
	uint16_t *temp16 = (uint16_t *)RecBuf;
	
	DataLength = (SPI_GetDataSize(SPI_X) <= 8)?8:16;
	if (DataLength == 8)
	{
		for (Index=0; Index<RecBytes; )
		{
            while(SPI_GetFlagStatus(SPI_X, SPI_STATUS_Receive_FIFO_Not_Empty) != SET);
            temp8[Index] = (uint8_t)SPI_ReceiveData(SPI_X);
			Index++;
		}
	}
	else
	{
		for (Index=0; Index<(RecBytes >> 1); )
		{
            while(SPI_GetFlagStatus(SPI_X, SPI_STATUS_Receive_FIFO_Not_Empty) != SET);
            temp16[Index] = SPI_ReceiveData(SPI_X);
			Index++;
		}
	}
}
#endif

/**
  * @brief  Read data from SPI FLASH or write data to SPI FLASH.
  * @param  TxData: data.
  * @retval data
  */
static uint16_t SPI_ReadWriteByte(uint16_t TxData)
{
	uint16_t i, retry = 0;

	while(SPI_GetFlagStatus(SPI_X, SPI_STATUS_Transmit_FIFO_Empty) != SET)
    {
        retry++;
        if(retry > SPI_TIMEOUT_VALUE)
            return 0;
    }
	SPI_SendData(SPI_X, TxData);
  for(i=0;i<10;i++);

	retry = 0;
	while (SPI_GetFlagStatus(SPI_X, SPI_STATUS_Receive_FIFO_Not_Empty) != SET)
    {
        retry++;
        if(retry > SPI_TIMEOUT_VALUE)
            return 0;
    }

	return SPI_ReceiveData(SPI_X);
}

/**
  * @brief  Wait for the SPI to be idle.
  * @param  None
  * @retval 0--OK, 1--Failed
  */
static int SPI_BusyWait(void)
{
    int retry = 0;

	while (SPI_GetFlagStatus(SPI_X, SPI_STATUS_SSP_BUSY) == SET)
    {
        retry++;
        if(retry > SPI_TIMEOUT_VALUE)
            return 1;
    }

    return 0;
}

/**
  * @brief  Enables or disables the specified SPI flash peripheral.
  * @param  NewState: new state of the SPI Flash peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
static void SPI_FLASH_Cmd(FunctionalState NewState)
{
    int retry = 0;

	if (NewState != DISABLE)
	{
		SPI_Cmd(SPI_X, ENABLE);
        SPI_ReadWriteByte(0xFF);
	}
	else
	{
		while(SPI_GetFlagStatus(SPI_X, SPI_STATUS_SSP_BUSY) == SET)
        {
            retry++;
            if (retry > SPI_TIMEOUT_VALUE)
                break;
        }
		SPI_Cmd(SPI_X, DISABLE);
	}
}

/**
  * @brief  Enable SPI wirte.
  * @param  None
  * @retval None
  */
static void SPI_FLASH_WriteEnable(void)
{
	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_WRITE_ENABLE);
    SPI_BusyWait();
	SPI_FLASH_CS_HIGH();
}

/**
  * @brief  Read SPI Status1.
  * @param  Status: Specifies a variable to store Status1.
  * @retval None
  */
static void SPI_FLASH_ReadStatus1(uint8_t *Status)
{
	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_READ_STATUS1);
    *Status = SPI_ReadWriteByte(0xFF);
	SPI_FLASH_CS_HIGH();
}

/**
  * @brief  Write SPI Status1 and Status2.
  * @param  Status1: Specifies Status1.
  * @param  Status2: Specifies Status2.
  * @retval 0--OK, 1--Failed
  */
static int SPI_FLASH_WriteStatus(uint8_t Status1, uint8_t Status2)
{
    uint8_t sta;
    int retry = 0;

	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_WRITE_STATUS);
    SPI_ReadWriteByte(Status1);
    SPI_ReadWriteByte(Status2);
    SPI_BusyWait();
	SPI_FLASH_CS_HIGH();

	do
	{
		SPI_FLASH_ReadStatus1(&sta);
        retry++;
        if (retry > SPI_TIMEOUT_VALUE)
            return 1;
	}while(sta & SPI_FLASH_STATUS1_BUSY);

    return 0;
}

/**
  * @brief  Allow writing data to SPI FLASH .
  * @param  None
  * @retval None
  */
static void SPI_FLASH_GlobalUnprotect(void)
{
	uint8_t Status1 = 0, Status2 = 0;
	
	SPI_FLASH_ReadStatus1(&Status1);

	if ((Status1 & SPI_FLASH_STATUS1_BP) == 0)
		return ;
	else
		Status1 &= ~SPI_FLASH_STATUS1_BP;

	SPI_FLASH_WriteStatus(Status1, Status2);
}

/**
  * @brief  DeInitializes the SPI FLASH communication.
  * @param  None
  * @retval None
  */
void SPI_FLASH_DeInit(void)
{
	SPI_FLASH_LowLevel_DeInit(SPI_X);
}

/**
  * @brief  Initializes the SPI communication.
  * @param  None
  * @retval None
  */
int SPI_FLASH_Init(void)
{
#ifdef SPI_FLASH_TX_RX_DMA
    int channel_ready=0;

    /* Initialize DMA */
    DmaInit(DMA_CHANNEL_0);
    tx_dma_chain = DmaRequestChain(DMA_CHANNEL_0, tx_pkg_num, &channel_ready);
    if(!channel_ready)
    {
        return -1;
    }
    if(!tx_dma_chain)
    {
        return -1;
    }
    dma_llp_tx_vir = tx_dma_chain->chain_head;
    dma_llp_tx_phy = dma_llp_tx_vir;
    DmaChannelCFGset(DMA_CHANNEL_0, (4<<20), ((8<<7)+(8<<11)));		//SPI0 TX
    DmaChannelInterrupt(DMA_CHANNEL_0, INT_TFR, 1);
    
    rx_dma_chain = DmaRequestChain(DMA_CHANNEL_1, rx_pkg_num, &channel_ready);
    if(!channel_ready)
    {
        return -1;
    }
    if(!tx_dma_chain)
    {
        return -1;
    }
    dma_llp_rx_vir = rx_dma_chain->chain_head;
    dma_llp_rx_phy = dma_llp_rx_vir;
    DmaChannelCFGset(DMA_CHANNEL_1, (4<<20), ((9<<7)+(9<<11)));       //SPI1 RX
    DmaChannelInterrupt(DMA_CHANNEL_1, INT_TFR, 2);
#endif
    
	/* Initialize SPI FLASH */
	SPI_FLASH_LowLevel_Init(SPI_X);

    SPI_FLASH_Cmd(ENABLE);
        
    if (!SPI_FLASH_Detect())
        return 0;
    else
        return -1;
}

int SPI_FLASH_Detect(void)
{
    uint8_t Flash_ID[2] = {0};
    
    SPI_FLASH_ReadID(Flash_ID);
    
    if ((Flash_ID[0] == SPI_FLASH_ID0) && (Flash_ID[1] == SPI_FLASH_ID1))
        return 0;
    else
        return -1;
}

/**
  * @brief  Read ID of SPI FLASH.
  * @param  Flash_ID: Specifies a pointer to store ID
  * @retval None
  */
void SPI_FLASH_ReadID(uint8_t *Flash_ID)
{
    SPI_FLASH_CS_LOW();
	SPI_ReadWriteByte(SPI_FLASH_CMD_READ_MANUFACTURER_ID);
	SPI_ReadWriteByte(0);
	SPI_ReadWriteByte(0);
	SPI_ReadWriteByte(0);
	Flash_ID[0] = SPI_ReadWriteByte(0xFF);
	Flash_ID[1] = SPI_ReadWriteByte(0xFF);
	SPI_FLASH_CS_HIGH();
}

/**
  * @brief  Erase a sector(4KB).
  * @param  Addr: Specifies the erase address.
  * @retval 0--OK, 1--Failed
  */
int SPI_FLASH_EraseSector4K(uint32_t Addr)
{
    uint8_t sta;
    int retry = 0;
    volatile int delay = 0;

	SPI_FLASH_GlobalUnprotect();
	SPI_FLASH_WriteEnable();	

	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_ERASE_4K);
    SPI_ReadWriteByte((Addr>>16)&0xFF);
    SPI_ReadWriteByte((Addr>>8)&0xFF);
    SPI_ReadWriteByte((Addr>>0)&0xFF);
    SPI_BusyWait();
	SPI_FLASH_CS_HIGH();

	do
	{
		SPI_FLASH_ReadStatus1(&sta);
        retry++;
        if (retry > SPI_TIMEOUT_VALUE)
            return 1;
        for (delay=0; delay<0x1000; delay++);
	}while(sta & SPI_FLASH_STATUS1_BUSY);

    return 0;
}

/**
  * @brief  Erase a block(32KB).
  * @param  Addr: Specifies the erase address.
  * @retval 0--OK, 1--Failed
  */
int SPI_FLASH_EraseSector32K(uint32_t Addr)
{
    uint8_t sta;
    int retry = 0;
    volatile int delay = 0;

	SPI_FLASH_GlobalUnprotect();
	SPI_FLASH_WriteEnable();	

	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_ERASE_32K);
    SPI_ReadWriteByte((Addr>>16)&0xFF);
    SPI_ReadWriteByte((Addr>>8)&0xFF);
    SPI_ReadWriteByte((Addr>>0)&0xFF);
    SPI_BusyWait();
	SPI_FLASH_CS_HIGH();

	do
	{
		SPI_FLASH_ReadStatus1(&sta);
        retry++;
        if (retry > SPI_TIMEOUT_VALUE)
            return 1;
        for (delay=0; delay<0x1000; delay++);
	}while(sta & SPI_FLASH_STATUS1_BUSY);

    return 0;
}

/**
  * @brief  Erase a block(64KB).
  * @param  Addr: Specifies the erase address.
  * @retval 0--OK, 1--Failed
  */
int SPI_FLASH_EraseSector64K(uint32_t Addr)
{
    uint8_t sta;
    int retry = 0;
    volatile int delay = 0;

	SPI_FLASH_GlobalUnprotect();
	SPI_FLASH_WriteEnable();	

	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_ERASE_64K);
    SPI_ReadWriteByte((Addr>>16)&0xFF);
    SPI_ReadWriteByte((Addr>>8)&0xFF);
    SPI_ReadWriteByte((Addr>>0)&0xFF);
    SPI_BusyWait();
	SPI_FLASH_CS_HIGH();

	do
	{
		SPI_FLASH_ReadStatus1(&sta);
        retry++;
        if (retry > SPI_TIMEOUT_VALUE)
            return 1;
        for (delay=0; delay<0x1000; delay++);
	}while(sta & SPI_FLASH_STATUS1_BUSY);

    return 0;
}

/**
  * @brief  Erase all the chip.
  * @param  None
  * @retval 0--OK, 1--Failed
  */
int SPI_FLASH_EraseFull(void)
{
    uint8_t sta;
    int retry = 0;
    volatile int delay = 0;

	SPI_FLASH_GlobalUnprotect();
	SPI_FLASH_WriteEnable();

	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_ERASE_ALL);
    SPI_BusyWait();
	SPI_FLASH_CS_HIGH();

	do
	{
		SPI_FLASH_ReadStatus1(&sta);
        retry++;
        if (retry > SPI_TIMEOUT_VALUE)
            return 1;
        for (delay=0; delay<0x20000; delay++);
	}while(sta & SPI_FLASH_STATUS1_BUSY);

    return 0;
}

/**
  * @brief  Program from one byte to 256 bytes to SPI FLASH.
  * @param  SendBuf: Specifies buffers which will be write to SPI FLASH.
  * @param  Addr: Specifies the address where will be programmed at.
  * @param  SendSize: Specifies programming size.
  * @retval 0--OK, 1--Failed
  */
static int SPI_FLASH_WritePage(uint8_t *SendBuf, uint32_t Addr, uint32_t SendSize)
{
    uint8_t sta;
 	int retry = 0;
    volatile int delay = 0;

    SPI_FLASH_WriteEnable();
	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_WRITE);
    SPI_ReadWriteByte((Addr>>16)&0xFF);
    SPI_ReadWriteByte((Addr>>8)&0xFF);
    SPI_ReadWriteByte((Addr>>0)&0xFF);

#ifdef SPI_FLASH_TX_RX_DMA
    {
        int ret;
        uint32_t tmpreg;
        
        spi_dma_tx_pkg_config(SPI_FLASH_PAGESIZE);
        SPI_X->CR1 |= (1<<5);
        SPI_TxDMACmd(SPI_X, ENABLE);
        dma_llp_tx_phy->SAR = (uint32_t)SendBuf;
        ret = DmaStartRoutine(DMA_CHANNEL_0, dma_llp_tx_phy, 1, DMAtranstype1);
        SPI_BusyWait();                         //等待写结束
        SPI_FLASH_CS_HIGH();                    //取消片选
        tmpreg = SPI_X->CR1;
        tmpreg &= ~(1<<5);
        SPI_X->CR1 = 0;
        SPI_TxDMACmd(SPI_X, DISABLE);
        SPI_X->CR1 = tmpreg;
        if (ret != 0)
            return -1;
    }
#else
    {
        int i;
        
        for(i=0; i<SendSize; i++)
            SPI_ReadWriteByte(SendBuf[i]);      //循环写数
        SPI_BusyWait();                         //等待写结束
        SPI_FLASH_CS_HIGH();                    //取消片选
    }
#endif
    
	do
	{
		SPI_FLASH_ReadStatus1(&sta);
        retry++;
        if (retry > SPI_TIMEOUT_VALUE)
            return 1;
        for (delay=0; delay<0x1000; delay++);
	}while(sta & SPI_FLASH_STATUS1_BUSY);

    return 0;
}

/**
  * @brief  Read data from SPI FLASH.
  * @param  RecBuf: Specifies buffers where store data.
  * @param  Addr: Specifies the address where read from.
  * @param  RecSize: Specifies reading size.
  *            This parameter should be less than 0x10000.
  * @retval 0--OK, 1--Failed
  */
int SPI_FLASH_Read(uint8_t *RecBuf, uint32_t Addr, uint32_t RecSize)
{
 	int retry = 0;
    uint8_t sta;

	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_READ);
    SPI_ReadWriteByte((Addr>>16)&0xFF);
    SPI_ReadWriteByte((Addr>>8)&0xFF);
    SPI_ReadWriteByte((Addr>>0)&0xFF);

#ifdef SPI_FLASH_TX_RX_DMA
    {
        int ret;
        uint32_t tmpreg;

        spi_dma_rx_pkg_config(RecSize);
        SPI_RxDMACmd(SPI_X, ENABLE);
        dma_llp_rx_phy->DAR = (uint32_t)RecBuf;
            SPI_X->CR1 |= (1<<6);
        ret = DmaStartRoutine(DMA_CHANNEL_1, dma_llp_rx_phy, 1, DMAtranstype1);
        tmpreg = SPI_X->CR1;
        tmpreg &= ~(1<<6);
        SPI_X->CR1 = 0;
        SPI_X->CR1 = tmpreg;
        SPI_RxDMACmd(SPI_X, DISABLE);
        if (ret != 0)
            return -1;
    }
#else
    int i;
    
    for(i=0; i<RecSize; i++)
    {
        RecBuf[i] = SPI_ReadWriteByte(0XFF);//循环读数
    }
#endif
	SPI_FLASH_CS_HIGH();

	do
	{
		SPI_FLASH_ReadStatus1(&sta);
        retry++;
        if (retry > SPI_TIMEOUT_VALUE)
            return 1;
	}while(sta & SPI_FLASH_STATUS1_BUSY);

    return 0;
}

/**
  * @brief  Program data to SPI FLASH.
  * @param  SendBuf: Specifies buffers which will be write to SPI FLASH.
  * @param  Addr: Specifies the address where will be programmed at.
  * @param  SendSize: Specifies programming size.
  * @retval 0--OK, 1--Failed
  */
int SPI_FLASH_Write(uint8_t *SendBuf, uint32_t Addr, uint32_t SendSize)
{
	uint32_t LeftSize = SendSize;
	uint32_t WriteSize;
	uint8_t *SrcBuf = SendBuf;
	uint32_t FlashAddr = Addr;

	SPI_FLASH_GlobalUnprotect();

	while(LeftSize)
	{
		WriteSize = SPI_FLASH_PAGESIZE - (FlashAddr & (SPI_FLASH_PAGESIZE-1));
		if (WriteSize > LeftSize)
			WriteSize = LeftSize;
		
		if (SPI_FLASH_WritePage(SrcBuf, FlashAddr, WriteSize) != 0)
            return 1;
		
		SrcBuf += WriteSize;
		FlashAddr += WriteSize;
		LeftSize -= WriteSize;
	}

    return 0;
}

/**
  * @brief  SPI FLASH Power down.
  * @retval None
  */
int SPI_FLASH_PowerDown(void)   
{
 	int retry = 0;
    uint8_t sta;

	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_Power_Down);
	SPI_FLASH_CS_HIGH();

	do
	{
		SPI_FLASH_ReadStatus1(&sta);
        retry++;
        if (retry > SPI_TIMEOUT_VALUE)
            return 1;
	}while(sta & SPI_FLASH_STATUS1_BUSY);

    return 0;
}

/**
  * @brief  SPI FLASH wake up.
  * @retval None
  */
int SPI_FLASH_WakeUp(void)   
{
 	int retry = 0;
    uint8_t sta;

	SPI_FLASH_CS_LOW();
    SPI_ReadWriteByte(SPI_FLASH_CMD_Release_PowerDown);
	SPI_FLASH_CS_HIGH();

	do
	{
		SPI_FLASH_ReadStatus1(&sta);
        retry++;
        if (retry > SPI_TIMEOUT_VALUE)
            return 1;
	}while(sta & SPI_FLASH_STATUS1_BUSY);

    return 0;
}   

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */  
#endif
/******************* (C) COPYRIGHT MIC *****END OF FILE****/
