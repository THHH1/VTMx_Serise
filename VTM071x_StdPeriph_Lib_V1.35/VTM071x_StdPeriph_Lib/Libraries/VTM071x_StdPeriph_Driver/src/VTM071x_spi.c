/**
  ******************************************************************************
  * @file    VTM071x_spi.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides all the SPI firmware functions.
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
#include "VTM071x_spi.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup SPI
  * @brief SPI driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SPI_CR0_SCR_0       (0UL)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SPI_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the SPI peripheral registers to their default
  *         reset values.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @retval None
  */
void SPI_DeInit(SPI_TypeDef *SPIx)
{
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
    
    if (SPIx == SPI0)
    {
        /* Enable SPIx reset state */
        RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_SPI0, ENABLE);
        /* Release SPIx from reset state */
        RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_SPI0, DISABLE);
    }
    else
    {
        /* Enable SPIx reset state */
        RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_SPI1, ENABLE);
        /* Release SPIx from reset state */
        RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_SPI1, DISABLE);
    }
}

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
	/*--------------- Reset SPI init structure parameters values -----------------*/
	/* Initialize the SPI_Mode member */
	SPI_InitStruct->SPI_Mode = SPI_MODE_MASTER;
	/* Initialize the SPI_Direction member */
	SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	/* Initialize the SPI_DataSize member */
	SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
	/* Initialize the SPI_CPOL member */
	SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
	/* Initialize the SPI_CPHA member */
	SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
	/* Initialize the SPI_BaudRatePrescaler member */
	SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
}

/**
  * @brief  Initializes the SPI peripheral according to the specified 
  *         parameters in the SPI_InitStruct.
  * @param  SPIx: where x can be 0 to 1 to select the spi peripheral.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
  *         contains the configuration information for the specified SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
	assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
	assert_param(IS_SPI_DATA_SIZE(SPI_InitStruct->SPI_DataSize));
	assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
	assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));

	/*---------------------------- SPI CPSR Configuration --------------------------*/
	SPIx->CPSR = SPI_InitStruct->SPI_BaudRatePrescaler;

	/*---------------------------- SPI CR0 Configuration ------------------------*/
    SPIx->CR0 = SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL | \
                SPI_InitStruct->SPI_CPHA| SPI_CR0_SCR_0;

	/*---------------------------- SPI CR1 Configuration ------------------------*/
	SPIx->CR1 = SPI_InitStruct->SPI_Mode | SPI_InitStruct->SPI_Direction;
}

/**
  * @brief  Enables or disables Tx DMA.
  * @param  SPIx: where x can be 0 to 1 to select the spi peripheral.
  * @param  NewState: new state of the SPI peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_TxDMACmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
    /* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		SPIx->DMACR |= SPI_DMACR_TXDMAE;
	}
	else
	{
		SPIx->DMACR &= ~SPI_DMACR_TXDMAE;
	}
}

/**
  * @brief  Enables or disables Rx DMA.
  * @param  SPIx: where x can be 0 to 1 to select the spi peripheral.
  * @param  NewState: new state of the SPI peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_RxDMACmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
    /* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		SPIx->DMACR |= SPI_DMACR_RXDMAE;
	}
	else
	{
		SPIx->DMACR &= ~SPI_DMACR_RXDMAE;
	}
}

/**
  * @brief  Enables or disables the specified SPI peripheral.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @param  NewState: new state of the SPI peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable the selected SPI peripheral */
		SPIx->CR1 |= SPI_CR1_SSE;
	}
	else
	{
		/* Disable the selected SPI peripheral */
		SPIx->CR1 &= ~SPI_CR1_SSE;
	}
}

/**
  * @brief  Enables or disables loop back mode.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @param  NewState: new state of the SPI peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_LoopBackCmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable loop back mode */
		SPIx->CR1 |= SPI_CR1_LBM;
	}
	else
	{
		/* Disable loop back mode */
		SPIx->CR1 &= ~SPI_CR1_LBM;
	}
}

/**
  * @brief  Enables or disables Slave-mode receive.
  * @param  NewState: new state of the SPI peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_SlaveReceiveCmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable Slave-mode output */
		SPIx->CR1 &= ~SPI_CR1_SOD;
	}
	else
	{
		/* Disable Slave-mode output */
		SPIx->CR1 |= SPI_CR1_SOD;
	}
}

/**
  * @brief  Configures the data size for the selected SPI.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @param  SPI_DataSize: specifies the SPI data size.
  *         For the SPI peripheral this parameter can be one of the following values:
  *            @arg SPI_DataSize_4b: Set data size to 4 bits
  *            @arg SPI_DataSize_5b: Set data size to 5 bits
  *            @arg SPI_DataSize_6b: Set data size to 6 bits
  *            @arg SPI_DataSize_7b: Set data size to 7 bits
  *            @arg SPI_DataSize_8b: Set data size to 8 bits
  *            @arg SPI_DataSize_9b: Set data size to 9 bits
  *            @arg SPI_DataSize_10b: Set data size to 10 bits
  *            @arg SPI_DataSize_11b: Set data size to 11 bits
  *            @arg SPI_DataSize_12b: Set data size to 12 bits
  *            @arg SPI_DataSize_13b: Set data size to 13 bits
  *            @arg SPI_DataSize_14b: Set data size to 14 bits
  *            @arg SPI_DataSize_15b: Set data size to 15 bits
  *            @arg SPI_DataSize_16b: Set data size to 16 bits
  * @retval None
  */
void SPI_DataSizeConfig(SPI_TypeDef *SPIx, uint32_t SPI_DataSize)
{
	uint32_t tmpreg = 0;

	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_DATA_SIZE(SPI_DataSize));

	/* Read the CTRL0 register */
	tmpreg = SPIx->CR0;
	/* Clear DSS[3:0] bits */
	tmpreg &= (uint32_t)~SPI_CR0_DSS_MASK;
	/* Set new DSS[3:0] bits value */
	tmpreg |= SPI_DataSize;
	SPIx->CR0 = tmpreg;
}

/**
  * @brief  Get the data size for the selected SPI.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @retval Data size
  */
uint32_t SPI_GetDataSize(SPI_TypeDef *SPIx)
{
	uint32_t datasize = 0;

	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));

    datasize = SPIx->CR0 & SPI_CR0_DSS_MASK;
    datasize += 1;

    return datasize;
}

/**
  * @brief  Transmits a Data through the SPI peripheral.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void SPI_SendData(SPI_TypeDef *SPIx, uint16_t Data)
{
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));

	SPIx->DR = Data;
}

/**
  * @brief  Returns the most recent received data by the SPI peripheral. 
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @retval The value of the received data.
  */
uint16_t SPI_ReceiveData(SPI_TypeDef *SPIx)
{
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));

	return (uint16_t)SPIx->DR;
}

/**
  * @brief Returns the current SPI Control Status.
  * @param SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @param Status:The current SPI Control Status.
  *          - SPI_STATUS_Transmit_FIFO_Empty: return SET if tx FIFO is empty, or return RESET.
  *          - SPI_STATUS_Transmit_FIFO_Not_Full: return SET if tx FIFO is not full, or return RESET.
  *          - SPI_STATUS_Receive_FIFO_Not_Empty: return SET if rx FIFO is not empty, or return RESET.
  *          - SPI_STATUS_Receive_FIFO_Full: return SET if rx FIFO is full, or return RESET.
  *          - SPI_STATUS_SSP_BUSY: return SET if busy, or return RESET.
  * @retval SET or RESET.
  */
FlagStatus SPI_GetFlagStatus(SPI_TypeDef *SPIx, uint32_t SPI_FLAG)
{
	FlagStatus bitstatus = RESET;
	
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_FLAG(SPI_FLAG));

	/* Get the the current SPI Control Status */
    if ((SPIx->SR & SPI_FLAG) != 0)
        bitstatus = SET;
    else
        bitstatus = RESET;

	return bitstatus;
}

/**
  * @brief  Enables or disables the specified SPI interrupts.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @param  SPI_IT: specifies the SPI interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg SPI_IT_TRANSMIT: Tx FIFO half empty or less condition.
  *            @arg SPI_IT_RECEIVE: Rx FIFO half full or less condition.
  *            @arg SPI_IT_RECEIVE_OVERRUN: Receive FIFO Overrun.
  *            @arg SPI_IT_RECEIVE_TIMEOUT: Receive FIFO Timeout.
  * @param  NewState: new state of the specified SPI interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_ITConfig(SPI_TypeDef *SPIx, uint32_t SPI_IT, FunctionalState NewState)
{
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_SPI_CONFIG_IT(SPI_IT)); 

	if (NewState != DISABLE)
	{
		/* Enable the selected SPI interrupts */
		SPIx->IMSC |= SPI_IT;
	}
	else
	{
		/* Disable the selected SPI interrupts */
		SPIx->IMSC &= ~SPI_IT;
	}
}

/**
  * @brief  Checks whether the specified SPI interrupt has occurred or not after Masking.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @param  SPI_IT: specifies the SPI interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg SPI_IT_TRANSMIT: Tx FIFO half empty or less condition.
  *            @arg SPI_IT_RECEIVE: Rx FIFO half full or less condition.
  *            @arg SPI_IT_RECEIVE_OVERRUN: Receive FIFO Overrun.
  *            @arg SPI_IT_RECEIVE_TIMEOUT: Receive FIFO Timeout.
  * @retval The new state of SPI_IT (SET or RESET).
  */
ITStatus SPI_GetITStatusAfterMasking(SPI_TypeDef *SPIx, uint32_t SPI_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_GET_IT(SPI_IT));

	/* Check the status of the specified SPI interrupt */
	if ((uint32_t)(SPIx->MIS & SPI_IT) != (uint32_t)RESET)
	{
		/* SPI_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* SPI_IT is reset */
		bitstatus = RESET;
	}

	/* Return the SPI_IT status */
	return  bitstatus;
}

/**
  * @brief  Checks whether the specified SPI interrupt has occurred or not prior to Masking.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @param  SPI_IT: specifies the SPI interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg SPI_IT_TRANSMIT: Tx FIFO half empty or less condition.
  *            @arg SPI_IT_RECEIVE: Rx FIFO half full or less condition.
  *            @arg SPI_IT_RECEIVE_OVERRUN: Receive FIFO Overrun.
  *            @arg SPI_IT_RECEIVE_TIMEOUT: Receive FIFO Timeout.
  * @retval The new state of SPI_IT (SET or RESET).
  */
ITStatus SPI_GetITStatusPriorToMasking(SPI_TypeDef *SPIx, uint32_t SPI_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_GET_IT(SPI_IT));

	/* Check the status of the specified SPI interrupt */
	if ((uint32_t)(SPIx->RIS & SPI_IT) != (uint32_t)RESET)
	{
		/* SPI_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* SPI_IT is reset */
		bitstatus = RESET;
	}

	/* Return the SPI_IT status */
	return  bitstatus;
}

/**
  * @brief  Clears the SPI's interrupt pending bits.
  * @param  SPIx: where x can be 0 to 2 to select the spi peripheral.
  * @param  SPI_IT: specifies the SPI interrupt sources to be cleared.
  *          This parameter can be one of the following values:
  *            @arg SPI_IT_RECEIVE_OVERRUN: Receive FIFO Overrun.
  *            @arg SPI_IT_RECEIVE_TIMEOUT: Receive FIFO Timeout.
  * @retval None
  */
void SPI_ClearITPendingBit(SPI_TypeDef *SPIx, uint32_t SPI_IT)
{
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_CLEAR_IT(SPI_IT));

	/* Clear the selected SPI interrupt pending bits */
    SPIx->ICR = SPI_IT;
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

/******************* (C) COPYRIGHT MIC *****END OF FILE****/
