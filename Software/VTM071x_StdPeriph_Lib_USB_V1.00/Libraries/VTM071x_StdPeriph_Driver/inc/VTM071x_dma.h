/**
  ******************************************************************************
  * @file    VTM071x_dma.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the DMA firmware 
  *              library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VTM071x_DMA_H
#define __VTM071x_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "vtm071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/* Exported defines ------------------------------------------------------------*/

/*Bit domain Shift for CTRL_L*/
#define DMA_CTRL_INT_EN             (0) 
#define DMA_CTRL_DST_TR_WIDTH       (1) 		//see DMA Transfer Width
#define DMA_CTRL_SRC_TR_WIDTH       (4) 		//see DMA Transfer Width
#define DMA_CTRL_DINC               (7)		    //see DMA Address Changing
#define DMA_CTRL_SINC               (9)		    //see DMA Address Changing
#define DMA_DEST_MSIZE              (11)		//see Burst Transaction Length
#define DMA_SRC_MSIZE               (14)		//see Burst Transaction Length
#define DMA_SRC_GATHER_EN           (17)
#define DMA_DST_GATHER_EN           (18)
#define DMA_TTC_FC                  (20)		//see Transfer Type and Flow Control
#define DMA_DMS	                    (23)
#define DMA_SMS	                    (25)
#define DMA_LLP_DST_EN              (27)
#define DMA_LLP_SRC_EN              (28)

/*Bit domain Shift for CTRL_H*/
#define DMA_BLOCK_TS				(32)
#define DMA_DONE					(44)

/*Bit domain shift for CFG_H*/
#define DMA_CFG_SRC_PER             (7)
#define DMA_CFG_DEST_PER            (11) 

/*DMA Transfer Width*/
#define DMA_WIDTH_8 				(0x00)
#define DMA_WIDTH_16 				(0x01)
#define DMA_WIDTH_32				(0x02)
#define DMA_WIDTH_64 				(0x03)
#define DMA_WIDTH_128 				(0x04)
#define DMA_WIDTH_256 				(0x05)

/*DMA Address Changing*/
#define DMA_ADDRESS_INCREMENT 	    (0x00)
#define DMA_ADDRESS_DECREMENT 	    (0x01)
#define DMA_ADDRESS_NO_CHANGE 	    (0x02)

/*Burst Transaction Length*/
#define DMA_BURST_1_ITEM			(0x00)
#define DMA_BURST_4_ITEM			(0x01)
#define DMA_BURST_8_ITEM			(0x02)
#define DMA_BURST_16_ITEM			(0x03)
#define DMA_BURST_32_ITEM			(0x04)
#define DMA_BURST_64_ITEM			(0x05)
#define DMA_BURST_128_ITEM		    (0x06)
#define DMA_BURST_256_ITEM		    (0x07)

/*Transfer Type and Flow Control*/
#define DMA_MEM_TO_MEM_DMAC			(0x00)
#define DMA_MEM_TO_PER_DMAC			(0x01)
#define DMA_PER_TO_MEM_DMAC			(0x02)
#define DMA_PER_TO_PER_DMAC			(0x03)
#define DMA_PER_TO_MEM_PERI			(0x04)
#define DMA_PER_TO_PER_SOU_PER		(0x05)
#define DMA_MEM_TO_PER_PER			(0x06)
#define DMA_PER_TO_PER_DES_PER		(0x07)

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants
  * @{
  */

/** @defgroup DMA_channel 
  * @{
  */
#define DMAChannelNum   8
typedef enum {
    DMA_CHANNEL_0 = 0, 
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3,
    DMA_CHANNEL_4,
    DMA_CHANNEL_5,
    DMA_CHANNEL_6,
    DMA_CHANNEL_7,
}DMAchannel;

#define IS_DMA_CHANNEL(CHANNEL) (((CHANNEL) == DMA_CHANNEL_0) || \
                                 ((CHANNEL) == DMA_CHANNEL_1) || \
                                 ((CHANNEL) == DMA_CHANNEL_2) || \
                                 ((CHANNEL) == DMA_CHANNEL_3) || \
                                 ((CHANNEL) == DMA_CHANNEL_4) || \
                                 ((CHANNEL) == DMA_CHANNEL_5) || \
                                 ((CHANNEL) == DMA_CHANNEL_6) || \
                                 ((CHANNEL) == DMA_CHANNEL_7))
/**
  * @}
  */ 

/** @defgroup DMA_method
  * @{
  */ 
#define DMAMETHODNUM 10
typedef enum {
		DMAtranstype1 = 1,
		DMAtranstype2,
		DMAtranstype3,
		DMAtranstype4,
		DMAtranstype5,
		DMAtranstype6,
		DMAtranstype7,
		DMAtranstype8,
		DMAtranstype9,
		DMAtranstype10
}DMAmethod;

#define IS_DMA_METHOD(METHOD) (((METHOD) == DMAtranstype1) || \
                                 ((METHOD) == DMAtranstype2) || \
                                 ((METHOD) == DMAtranstype3) || \
                                 ((METHOD) == DMAtranstype4) || \
                                 ((METHOD) == DMAtranstype5) || \
                                 ((METHOD) == DMAtranstype6) || \
                                 ((METHOD) == DMAtranstype7) || \
								 ((METHOD) == DMAtranstype8) || \
								 ((METHOD) == DMAtranstype9) || \
                                 ((METHOD) == DMAtranstype10) )
/**
  * @}
  */ 

/** @defgroup DMA_ChannelState
  * @{
  */ 
typedef enum {
		CHANNEL_IDLE =0,
		CHANNEL_BUSY		
}ChannelState;	  
/**
  * @}
  */ 

/** @defgroup DMA_ChannelState
  * @{
  */
typedef enum {
		INT_TFR = 0,
		INT_BLOCK,
		INT_SRCTRAN,
		INT_DSTTRAN,
		INT_ERR
}DMAinterruptType;	

#define IS_DMA_INT_TYPE(INTTYPE) (((INTTYPE) == INT_TFR) || \
	                                 ((INTTYPE) == INT_BLOCK) || \
	                                 ((INTTYPE) == INT_SRCTRAN) || \
	                                 ((INTTYPE) == INT_DSTTRAN) || \
	                                 ((INTTYPE) == INT_ERR))
/**
  * @}
  */ 

/** @defgroup DMA_TransferDMAChainPkg
  * @{
  */

/**
  *  _DmaPkg - For DMAmethod 1-5, it's used as a struct to retrieve the information to 
  *  start the DMA directly. For DMAmethod 6-10, it's used as node struct to set up link  
  *  list of DMA chains.   
  */
typedef struct _DmaPkg
{
	unsigned int SAR;
	unsigned int DAR;
	unsigned int LLP;
	unsigned int CTRL_L;
	unsigned int CTRL_H;
}DmaPkg;

typedef struct _dma_chain
{
	DMAchannel dmachannel;
	int pkg_num;    
	DmaPkg* chain_head; /* point to the 1st dma package*/
}DmaChain;

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
int DMAChannelBlockTsBits(DMAchannel channel);
DmaChain* DmaRequestChain(DMAchannel channel, int pkg_num, int* channel_ready);
void DmaFreeChain(DmaChain* dma_chain);
int DmaInit(DMAchannel channel);
static int _WaitDmaSemaphore(DMAchannel channel);
int DmaStop(DMAchannel channel);
void DmaChannelCFGset(DMAchannel channel, uint32_t lowregval, uint32_t highregval);
static void DmaStart(DMAchannel channel, DmaPkg* Addr, DMAmethod dmamethod);
int DmaStartRoutine(DMAchannel channel, void* Addr, int bWaitSemaAfter, DMAmethod dmamethod);
ChannelState DmaIsBusy(DMAchannel channel);
void DmaChannelInterrupt(DMAchannel channel, DMAinterruptType inttype, int funswitch );
int DmaChannelInterruptStatusBit(DMAchannel channel, DMAinterruptType inttype, int statustype );
void DmaChannelClearInterruptStatus(DMAchannel channel, DMAinterruptType inttype);

#ifdef __cplusplus
}
#endif

#endif /*__VTM071x_DMA_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2018 MIC *****END OF FILE****/
