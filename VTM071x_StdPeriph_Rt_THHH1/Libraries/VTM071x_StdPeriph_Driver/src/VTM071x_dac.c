/**
  ******************************************************************************
  * @file    VTM071x_dac.c
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    07/01/2018
  * @brief   This file provides all the DAC firmware functions.
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
#include "VTM071x_dac.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup DAC 
  * @brief DAC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup DAC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @retval None
  */
void DAC_DeInit(void)
{
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL1_DAC, ENABLE);
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL1_DAC, DISABLE);
}

/**
  * @brief  Initializes the DAC peripheral according to the specified parameters
  *         in the DAC_InitStruct.
  * @param  DACx: the selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC0: DAC Channel0 selected
  *            @arg DAC1: DAC Channel1 selected
  * @param  DAC_InitStruct: pointer to a DAC_InitTypeDef structure that contains
  *         the configuration information for the  specified DAC channel.
  * @retval None
  */
void DAC_Init(DACx_TypeDef *DACx, DAC_InitTypeDef* DAC_InitStruct)
{
    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));
    assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
    assert_param(IS_DAC_REF_VOLTAGE(DAC_InitStruct->DAC_ReferenceVoltage));
    assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));

    DACx->CTRL = DAC_InitStruct->DAC_Trigger;
    DACx->ANACTRL = DAC_InitStruct->DAC_OutputBuffer | DAC_InitStruct->DAC_ReferenceVoltage;
}

/**
  * @brief  Fills each DAC_InitStruct member with its default value.
  * @param  DAC_InitStruct: pointer to a DAC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
    /*--------------- Reset DAC init structure parameters values -----------------*/
    /* Initialize the DAC_Trigger member */
    DAC_InitStruct->DAC_Trigger = DAC_Trigger_WRITE_DATA;

    /* Initialize the DAC_ReferenceVoltage member */
    DAC_InitStruct->DAC_ReferenceVoltage = DAC_REF_VOLTAGE_VDDA;

    /* Initialize the DAC_OutputBuffer member */
    DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/**
  * @brief  Enables or disables the specified DAC channel.
  * @param  DACx: the selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC0: DAC Channel0 selected
  *            @arg DAC1: DAC Channel1 selected
  * @param  NewState: new state of the DAC channel. 
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When the DAC channel is enabled the trigger source can no more be modified.
  * @retval None
  */
void DAC_Cmd(DACx_TypeDef *DACx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected DAC channel */
        DACx->CTRL |= (DAC_CTRL_EN);
    }
    else
    {
        /* Disable the selected DAC channel */
        DACx->CTRL &= ~(DAC_CTRL_EN);
    }
}

/**
  * @brief  Enables or disables simultaneously the two DAC channels .
  * @param  NewState: new state of the DAC triggers.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_GroupCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable software trigger for both DAC channels */
        
        DAC->COMCTRL |= DAC_COMCTRL_GRP;
    }
    else
    {
        /* Disable software trigger for both DAC channels */
        DAC->COMCTRL &= ~DAC_COMCTRL_GRP;
    }
}

/**
  * @brief  Set the specified data holding register value for DAC channel.
  * @param  DACx: the selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC0: DAC Channel0 selected
  *            @arg DAC1: DAC Channel1 selected
  * @param  Data: Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetData(DACx_TypeDef *DACx, uint16_t Data)
{  
    /* Check the parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));
    assert_param(IS_DAC_DATA(Data));

    DACx->DATA = Data;
}

/**
  * @brief  Enables or disables the DAC interrupt.
  * @param  DACx: the selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC0: DAC Channel0 selected
  *            @arg DAC1: DAC Channel1 selected
  * @param  NewState: new state of the DAC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */ 
void DAC_ITConfig(DACx_TypeDef *DACx, FunctionalState NewState)  
{
    /* Check the parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected DAC interrupts */
        DACx->CTRL |=  (DAC_CTRL_IE);
    }
    else
    {
        /* Disable the selected DAC interrupts */
        DACx->CTRL &= ~(DAC_CTRL_IE);
    }
}

/**
  * @brief  Checks whether the specified DAC flag is set or not.
  * @param  DACx: the selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC0: DAC Channel0 selected
  *            @arg DAC1: DAC Channel1 selected
  * @param  DAC_FLAG: specifies the flag to check. 
  *          This parameter can be only of the following value:
  *            @arg DAC_FLAG_DMAUDR: DMA underrun flag
  * @retval The new state of DAC_FLAG (SET or RESET).
  */
FlagStatus DAC_GetFlagStatus(DACx_TypeDef *DACx, uint32_t DAC_FLAG)
{
    FlagStatus bitstatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));
    assert_param(IS_DAC_FLAG(DAC_FLAG));

    /* Check the status of the specified DAC flag */
    if ((DACx->STS & DAC_FLAG) != (uint8_t)RESET)
    {
        /* DAC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* DAC_FLAG is reset */
        bitstatus = RESET;
    }
    
    /* Return the DAC_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Checks whether the specified DAC interrupt has occurred or not.
  * @param  DACx: the selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC0: DAC Channel0 selected
  *            @arg DAC1: DAC Channel1 selected
  * @retval The new state of DAC_IT (SET or RESET).
  */
ITStatus DAC_GetITStatus(DACx_TypeDef *DACx)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;
  
    /* Check the parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));

    /* Get the DAC enable bit status */
    enablestatus = DACx->CTRL & DAC_CTRL_IE;
  
    /* Check the status of the specified DAC interrupt */
    if (((DACx->STS & DAC_STATUS_IFG) != (uint32_t)RESET) && enablestatus)
    {
        /* DAC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* DAC_IT is reset */
        bitstatus = RESET;
    }
    
    /* Return the DAC_IT status */
    return  bitstatus;
}

/**
  * @brief  Clears the DAC channel's interrupt pending bits.
  * @param  DACx: the selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC0: DAC Channel0 selected
  *            @arg DAC1: DAC Channel1 selected
  * @retval None
  */
void DAC_ClearITPendingBit(DACx_TypeDef *DACx)
{
    /* Check the parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));

    /* Clear the selected DAC interrupt pending bits */
    DACx->STS |= DAC_STATUS_IFG;
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

