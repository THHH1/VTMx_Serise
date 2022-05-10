/**
  ******************************************************************************
  * @file    VTM071x_dma.c
  * @author  MIC Application Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Direct Memory Access controller (DMA):           
  *           - Initialization and Configuration
  *           - Data Counter
  *           - Double Buffer mode configuration and command  
  *           - Interrupts and flags management
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

/* Includes ------------------------------------------------------------------*/
#include "VTM071x_dma.h"
#include "VTM071x_rcc.h"
#include <stdlib.h>
#include <string.h>

/** @addtogroup MT071_StdPeriph_Driver
  * @{
  */

/** @defgroup DMA 
  * @brief DMA driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_RBB_WAIT				(0x1000000)

/* Masks Definition */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static unsigned long DmaChannelBitMap = 0;
const int DmaChannelBlockTsBits[DMAChannelNum] = {8, 8};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup DMA_Private_Functions
  * @{
  */

/** @defgroup DMA_Group1 Initialization and package allocation functions
 *  @brief   Initialization and Reservation functions
 *
@verbatim   
 ===============================================================================
                 Initialization and Reservation functions
 ===============================================================================  

  This subsection provides functions allowing to initialize the DMA controller and allocate the
  resources for DMA transferring.
  
@endverbatim
  * @{
  */

/**
 *  @brief  DMAChannelBlockTsBits - get the BLOCK_TS bits for the target channel.  
 *  @param  dma_channel: which channel of the chosen module to be used.
 *
 *  @retval  BLOCK_TS bits for the target channel.
 */
int DMAChannelBlockTsBits(DMAchannel channel)
{
    assert_param(IS_DMA_CHANNEL(channel));
    return DmaChannelBlockTsBits[channel];
}

/**
  * @brief  DmaRequestChain - alloc memory space for dma chain
  * @param  dma_channel: which channel of the chosen module to be used.
  * @param  pkg_num: how many descriptors(AKA, Linked List Item) needed.
  * @param  channel_ready: the desired (dma_module, dma_channel) ready for use?  1,yes; 0, no.
  * 
  * @note  We probably requesting a busy channel, then we should try another one according to channel_ready.
  *
  * @retval  The allocated DMA chain struct pointer.
  */
DmaChain* DmaRequestChain(DMAchannel channel, int pkg_num, int* channel_ready)
{
   DmaChain* dma_chain;
   DmaPkg* chain_ptr;
   int i;

   assert_param(IS_DMA_CHANNEL(channel));

   if( (channel>DMA_CHANNEL_1)||(!pkg_num) )
   {
		return NULL;
   }

   if( (DmaIsBusy(channel)==CHANNEL_BUSY)|| ((DmaChannelBitMap&(1<<channel))!=0) )
   {
	   *channel_ready = 0;
	   return NULL;	   
   }

   DmaChannelBitMap |= (uint32_t)(1<<channel);
   *channel_ready = 1;  
    
   dma_chain = (DmaChain*)malloc(sizeof(DmaChain));
   if (!dma_chain)
   {
	   return NULL;
   }

   memset(dma_chain,0,sizeof(DmaChain));

   dma_chain->chain_head = (DmaPkg*)malloc(sizeof(DmaPkg)*pkg_num);  
   if ( dma_chain->chain_head==NULL )
   {
	   free(dma_chain);
	   return NULL;
   }
   memset((void *)dma_chain->chain_head,0,(size_t)(sizeof(DmaPkg) * pkg_num));   
  
      
   dma_chain->dmachannel = channel;
   dma_chain->pkg_num = pkg_num;
 

   chain_ptr = dma_chain->chain_head;
   for(i=0; i<pkg_num; i++)
   {
		chain_ptr[i].LLP = (uint32_t)((uint32_t)dma_chain->chain_head + ((i+1)*sizeof(DmaPkg)));
   }
   chain_ptr[pkg_num-1].LLP = (uint32_t)NULL;
  

   return dma_chain;
}


/**
 *  @brief  DmaFreeChain - free up the memory space allocated for dma_chain.
 *  @param  dma_chain: the targeted one. 
 *
 *  @retval  None.
 */
void DmaFreeChain(DmaChain* dma_chain)
{
	DmaChannelBitMap &= ~(uint32_t)(1<<(dma_chain->dmachannel));
	free(dma_chain->chain_head);
    free(dma_chain);
}


/**
  *  @brief  DmaInit - init the desired DMA channel.
  *  @param  channel: which channel of the chosen module to be used.
  *
  *  @note  If the channel is being used, we just return, and may retry for another one.
  *
  *  @retval  0, okay; else, error.
  */   
int DmaInit(DMAchannel channel)
{  
	assert_param(IS_DMA_CHANNEL(channel));

	if( DmaIsBusy(channel)==CHANNEL_BUSY ) 
	   return -1;

	RCC_AHBPeriphClockCmd(RCC_AHBCLKCTRL_DMA, ENABLE);

	RCC_AHBPeriphResetCmd(RCC_AHBCLKCTRL_DMA, ENABLE);
	RCC_AHBPeriphResetCmd(RCC_AHBCLKCTRL_DMA, DISABLE);

	DMA->DmaCfgReg = 1;

	if ( DmaStop(channel) )
		return -1;
	else
		return 0;
}

/**
  * @}
  */

/** @defgroup DMA_Group2 Transferring control functions
 *  @brief   Data Counter functions 
 *
@verbatim   
 ===============================================================================
                            Transferring Control functions
 ===============================================================================  

  This subsection provides function allowing to configure and control the DMA transfer.

@endverbatim
  * @{
  */

/**
  *  @brief   _WaitDmaSemaphore - wait for a dma channel to be idle. Like not ready before start   
  *              and timeout for finish.
  *  @param  dma_channel: which channel of the chosen module to be used.
  *
  *  @note: For data service finish verification check, user may need to check the busy bit of the function controller, 
  *              which requests DMA service, even when _WaitDmaSemaphore finishes; 
  *
  *  @retval  0, okay; -1, error;
  */
static int _WaitDmaSemaphore(DMAchannel channel)
{
   int wait_dma = MAX_RBB_WAIT;

   assert_param(IS_DMA_CHANNEL(channel));
   
   while( DmaIsBusy(channel)==CHANNEL_BUSY )
   {
	  if(!(wait_dma--))
	  {
		return -1;
	  }
   }
 
   return 0; 		
}

/**
  *  @brief  DmaStop - disable a dma channel, and clear the corresponding interrupt enable bits and interrupt status bits.
  *  @param  channel: which channel  to be used.
  *
  *  @retval  value: 0, channel is disabled properly. -1, error of timeout.
  */
int DmaStop(DMAchannel channel)
{     
    int i;
	int wait_time = MAX_RBB_WAIT;

	assert_param(IS_DMA_CHANNEL(channel));

	DMA->ChEnReg = (1<<channel)<<8;

	/*disable all interrupts*/
	for(i=0; i<5; i++)
	{
	   DmaChannelInterrupt(channel, (DMAinterruptType)i, 0);
	}
	
	/*clear all interrupt status*/
	for(i=0; i<5; i++)
	{
	   DmaChannelClearInterruptStatus(channel, (DMAinterruptType)i);
	}
	
	/*according to the data book, we must poll the corresponding ChEnReg.CH_EN bit*/
	while( DmaIsBusy(channel)==CHANNEL_BUSY )
	{
	  if(!(wait_time--))
	  {
		return -1;
	  }
	}

	return 0;
}

/**
 *  @brief  DmaChannelCFGset - set DMA channel's Channel ConfigurationRegister(CFG)
 *  @param  dma_channel: which channel of the chosen module to be used.
 *  @param  lowregval: CFG's low 32-bit setting.
 *  @param  highregval: CFG's high 32-bit setting.
 * 
 *  @note  This must be called before DMA-start(DmaStartRoutine).
 *
 *  @retval  None.
 */
void DmaChannelCFGset(DMAchannel channel, uint32_t lowregval, uint32_t highregval)
{
	 assert_param(IS_DMA_CHANNEL(channel));

	 *(uint32_t *)((uint32_t)(&(DMA->CFG0_L))+0x58*channel) = lowregval;	 
	 *(uint32_t *)((uint32_t)(&(DMA->CFG0_H))+0x58*channel) = highregval;
}

/**
  *  @brief  DmaStart - start DMA transmission.  
  *  @param  dma_channel: which channel of the chosen module to be used.
  *  @param  Addr: the virtual address of the the first LLI(dma descriptor).
  *  @param  dmamethod: Programming of Transfer Types and Channel Register Update Method.
  *
  *  @note: 
  *  1. For DMAmethod within ROW1-ROW5's range, we should have only one LLI(descriptor), and 
  *  use it in a special way. We strip the information from it to fill the hardware registers, then start DMA.
  *  2. For DMAmethod within ROW6-ROW10's range, !!**when CTRL's LLP_DST_EN or LLP_SRC_EN(or both)is set,
  *  the DMA just directly load the first LLI from LLP(register), no DMA data transmission before the loading for all cases.**!!
  *
  *  @retval  None.
  */
static void DmaStart(DMAchannel channel, DmaPkg* Addr, DMAmethod dmamethod)
{	
    assert_param(IS_DMA_CHANNEL(channel));
	assert_param(IS_DMA_METHOD(dmamethod));

	if( (dmamethod<=DMAtranstype5)&&(dmamethod>=DMAtranstype1) )
	{
        *(uint32_t *)((uint32_t)(&(DMA->SAR0))+0x58*channel) = Addr->SAR;
		*(uint32_t *)((uint32_t)(&(DMA->DAR0))+0x58*channel) = Addr->DAR;
		*(uint32_t *)((uint32_t)(&(DMA->CTL0_L))+0x58*channel) = Addr->CTRL_L;
		*(uint32_t *)((uint32_t)(&(DMA->CTL0_H))+0x58*channel) = Addr->CTRL_H;
		
		if(dmamethod!=DMAtranstype5)
		{
			*(uint32_t *)((uint32_t)(&(DMA->LLP0))+0x58*channel) = 0;
		}
		else
		{
			*(uint32_t *)((uint32_t)(&(DMA->LLP0))+0x58*channel) = Addr->LLP;
		}
	}
	else
	{
		*(uint32_t *)((uint32_t)(&(DMA->LLP0))+0x58*channel) = (unsigned int)Addr; //first LLI address
	
		if( (dmamethod==DMAtranstype6)||(dmamethod==DMAtranstype7) )
		{
			*(uint32_t *)((uint32_t)(&(DMA->SAR0))+0x58*channel) = Addr->SAR;
			*(uint32_t *)((uint32_t)(&(DMA->CTL0_L))+0x58*channel) = Addr->CTRL_L;			
		}
		else if( (dmamethod==DMAtranstype8)||(dmamethod==DMAtranstype9 ) )
		{
			*(uint32_t *)((uint32_t)(&(DMA->DAR0))+0x58*channel) = Addr->DAR;
			*(uint32_t *)((uint32_t)(&(DMA->CTL0_L))+0x58*channel) = Addr->CTRL_L;
		}	
		else//DMAmethod==10
		{
			*(uint32_t *)((uint32_t)(&(DMA->CTL0_L))+0x58*channel) = Addr->CTRL_L;
		}
	}
 
	DMA->DmaCfgReg = 0x01;	
	DMA->ChEnReg = ((1<<channel)<<8)+(1<<channel);
	
	return ;
}

/**
  *  @brief  DmaStartRoutine - do preparation for dma start. 
  *  @param  channel: which channel of the chosen module to be used.
  *  @param  Addr: the address of the first LLI(dma descriptor).
  *  @param  bWaitSemaAfter: wait until this LLI finish? 0, no; !0, yes.
  *  @param  dmamethod: Programming of Transfer Types and Channel Register Update Method.
  *
  *  @note
  * 1. user must already set Channel Configuration Register(CFG) 
  * properly before calling this function. 
  *  
  * 2. user must ensure that the DmaPkg->SAR and DmaPkg->DAR are
  * aligned to the setting of CTRL->SRC_TR_WIDTH and 
  * CTRL->DST_TR_WIDTH, we just ignore it here for avoiding the 
  * unnecessary complexity. 
  *   For more, see DesignWare DW_ahb_dmac Databook.
  *
  *  @retval  0, okay; else, error.   
  */
int DmaStartRoutine(DMAchannel channel, void* Addr, int bWaitSemaAfter, DMAmethod dmamethod)
{
	int ret = 0;

	assert_param(IS_DMA_CHANNEL(channel));
	assert_param(IS_DMA_METHOD(dmamethod));

    if( DmaIsBusy(channel)!=CHANNEL_BUSY )
    {
        ret = CHANNEL_IDLE;
        DmaStart(channel, (DmaPkg *)Addr, dmamethod);        
    }
    else
    {
        ret = CHANNEL_BUSY;
    }


    if(ret!=CHANNEL_IDLE)
    {
        return -1;
    }
			

	if( !bWaitSemaAfter )
	{
		return 0;
	}
	else
	{	
		return _WaitDmaSemaphore(channel);
	}
}

/**
  * @}
  */

/** @defgroup DMA_Group3 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
 ===============================================================================
                  Interrupts and flags management functions
 ===============================================================================  

  This subsection provides functions allowing to
   - Check the DMA channel busy status
   - Configure the DMA Interrupts sources and check or clear the flags or pending bits status.   
@endverbatim
  * @{
  */

/**
  *  @brief  DmaIsBusy - check whether one channel is reday for use.
  *  @param  channel: which channel of the chosen module to be used.
  *
  *  @retval  The DMA target channel state.
  */
ChannelState DmaIsBusy(DMAchannel channel)
{
   assert_param(IS_DMA_CHANNEL(channel));

   if( (DMA->ChEnReg)&(1<<channel) )
   		return CHANNEL_BUSY;
   else
   		return CHANNEL_IDLE;	
}

/**
   *  @brief  DmaChannelInterrupt - disable or enable a kind of interrupt for one channel.
   *  @param  channel: which channel to be used.
   *  @param  inttype: the desired interrupt
   *  @param  funswitch: disable or enable. 0, disable; 1, enable.
   *
   *  @retval None
   */
void DmaChannelInterrupt(DMAchannel channel, DMAinterruptType inttype, int funswitch )
{
		assert_param(IS_DMA_CHANNEL(channel));
		assert_param(IS_DMA_INT_TYPE(inttype));

		if( funswitch!=0 )
		{			
			*(uint32_t *)((uint32_t)(&DMA->MaskTfr)+8*inttype) = ((1<<channel)<<8)+(1<<channel);
		}
		else
		{
			*(uint32_t *)((uint32_t)(&DMA->MaskTfr)+8*inttype) = (1<<channel)<<8;
		}
}

/**
  *  @brief  DmaChannelInterruptStatusBit - read Interrupt Raw Status Registers or Interrupt Status Registers of
  *              one dma channel for the targeted interrupt status type.
  *  @param  channel: which channel of the chosen module to be used.
  *  @param  inttype  the desired interrupt status type.
  *  @param  statustype: 0, raw; 1, masked. 
  *
  *  return value: 0, interrupt status bit not set; !0, interrupt status bit is set.
  */
int DmaChannelInterruptStatusBit(DMAchannel channel, DMAinterruptType inttype, int statustype )
{
	int retval;
	
	assert_param(IS_DMA_CHANNEL(channel));
	assert_param(IS_DMA_INT_TYPE(inttype));

	if(statustype == 0) //raw interrupt status type
	{
		retval = *(uint32_t *)((uint32_t)(&DMA->RawTfr)+8*inttype)&(1<<channel);
	}
	else //masked 
	{
		retval = *(uint32_t *)((uint32_t)(&DMA->StatusTfr)+8*inttype)&(1<<channel);
	}


	return retval;
}

/**
  *  @brief  DmaChannelClearInterruptStatus - clear the corresponding bit in the chosen interrupt type's  
  *              interrupt Raw Status and interrupt Status registers of one dma channel.
  *  @param  channel: which channel to be used.
  *  @param  inttype: the desired interrupt status type.
  *
  *  @retval None.
  */
void DmaChannelClearInterruptStatus(DMAchannel channel, DMAinterruptType inttype)
{		
		assert_param(IS_DMA_CHANNEL(channel));
		assert_param(IS_DMA_INT_TYPE(inttype));
		
		*((uint32_t *)( (uint32_t)(&DMA->ClearTfr)+8*inttype)) = (uint32_t)(1<<channel);
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

/******************* (C) COPYRIGHT 2018 MIC *****END OF FILE****/
