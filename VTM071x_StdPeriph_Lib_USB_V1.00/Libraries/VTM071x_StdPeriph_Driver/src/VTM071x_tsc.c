/**
  ******************************************************************************
  * @file    VTM071x_tsc.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of Touch Sensor Controller
  *           - Initialization and Configuration
  *           - Data transfers
  *           - Interrupts, events and flags management        
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
#include "VTM071x_tsc.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup TSC 
  * @brief TSC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup TSC_Private_Functions
  * @{
  */
/**
  * @brief  Deinitializes the TSC peripheral registers to their default reset values.
  * @retval None
  */
void TSC_DeInit(void)
{
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL1_TSC, ENABLE);
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL1_TSC, DISABLE);
}

/**
  * @brief  Initializes the TSC peripheral according to the specified parameters
  *         in the TSC_InitStruct.
  * @param  TSC_InitStruct: pointer to a TSC_InitTypeDef structure that contains
  *         the configuration information for TSC.
  * @retval None
  */
void TSC_Init(TSC_InitTypeDef* TSC_InitStruct)
{
    /* Check the TSC parameters */
    assert_param(IS_TSC_CTPH_CYCLES(TSC_InitStruct->TSC_CTPH));
    assert_param(IS_TSC_CTPL_CYCLES(TSC_InitStruct->TSC_CTPL));
    assert_param(IS_TSC_PRESCALER_VALUE(TSC_InitStruct->TSC_PrescalerValue));
    assert_param(IS_TSC_MAX_COUNT_ERROR(TSC_InitStruct->TSC_MaxCountError));
    assert_param(IS_TSC_IO_DEFAULT_STATUS(TSC_InitStruct->TSC_IODefaultStatus));
    assert_param(IS_TSC_SYNC_POLAR(TSC_InitStruct->TSC_SyncPolar));
    assert_param(IS_TSC_SAMPLE_MODE(TSC_InitStruct->TSC_SampleMode));

    /* Set CR */
    TSC->CR = TSC_InitStruct->TSC_CTPH | TSC_InitStruct->TSC_CTPL | \
              TSC_InitStruct->TSC_PrescalerValue | TSC_InitStruct->TSC_MaxCountError | \
              TSC_InitStruct->TSC_IODefaultStatus | TSC_InitStruct->TSC_SyncPolar | \
              TSC_InitStruct->TSC_SampleMode;
}

/**
  * @brief  Initializes the TSC peripheral according to the specified parameters
  *         in the TSC_IOInitStruct.
  * @param  TSC_IOInitStruct: pointer to a TSC_IOInitTypeDef structure that contains
  *         the configuration information for TSC.
  * @param  TSC_IO: TSC IO
  *         This parameter can be any combination of the following values
                TSC_IO_Gx_IOy(x[1:6], y[1-4])
  * @retval None
  */
void TSC_IOInit(TSC_IOInitTypeDef* TSC_IOInitStruct, uint32_t TSC_IO)
{
    uint32_t temp_reg = 0;
    
    /* Check the TSC parameters */
    assert_param(IS_TSC_IO(TSC_IO));
    assert_param(IS_FUNCTIONAL_STATE(TSC_IOInitStruct->TSC_IOHysteresis));
    assert_param(IS_FUNCTIONAL_STATE(TSC_IOInitStruct->TSC_IOAnalogSwitch));
    assert_param(IS_FUNCTIONAL_STATE(TSC_IOInitStruct->TSC_IOSampleCapacitance));
    assert_param(IS_FUNCTIONAL_STATE(TSC_IOInitStruct->TSC_IOChannelMode));
    assert_param(IS_FUNCTIONAL_STATE(TSC_IOInitStruct->TSC_IOEnable));
    
    /* Set IOHCR */
    if (TSC_IOInitStruct->TSC_IOHysteresis != DISABLE)
    {
        TSC->IOHCR |= TSC_IO;
    }
    else
    {
        TSC->IOHCR &= ~(TSC_IO);
    }
    
    /* Set IOASCR */
    if (TSC_IOInitStruct->TSC_IOAnalogSwitch != DISABLE)
    {
        TSC->IOASCR |= TSC_IO;
    }
    else
    {
        TSC->IOASCR &= ~(TSC_IO);
    }

    /* Set IOSCR */
    if (TSC_IOInitStruct->TSC_IOSampleCapacitance != DISABLE)
    {
        TSC->IOSCR |= TSC_IO;
    }
    else
    {
        TSC->IOSCR &= ~(TSC_IO);
    }

    /* Set IOCCR */
    if (TSC_IOInitStruct->TSC_IOChannelMode != DISABLE)
    {
        TSC->IOCCR |= TSC_IO;
    }
    else
    {
        TSC->IOCCR &= ~(TSC_IO);
    }

    /* Set IOGCSR */
    if (TSC_IO & 0xF)
        temp_reg |= 0x1;
    if (TSC_IO & 0xF0)
        temp_reg |= 0x2;
    if (TSC_IO & 0xF00)
        temp_reg |= 0x4;
    if (TSC_IO & 0xF000)
        temp_reg |= 0x8;
    if (TSC_IO & 0xF0000)
        temp_reg |= 0x10;
    if (TSC_IO & 0xF00000)
        temp_reg |= 0x20;
    
    if (TSC_IOInitStruct->TSC_IOEnable != DISABLE)
    {
        TSC->IOSCR |= temp_reg;
    }
    else
    {
        TSC->IOSCR &= ~(temp_reg);
    }
}

/**
  * @brief  Enables or disables TSC .
  * @param  NewState: new state of the TSC. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TSC_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable TSC */
        TSC->CR |= TSC_CR_TSCE;
    }
    else
    {
        /* Disable TSC */
        TSC->CR &= ~TSC_CR_TSCE;
    }
}

/**
  * @brief  Start or stop TSC .
  * @param  NewState: new state of the TSC. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TSC_StartCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable TSC */
        TSC->CR |= TSC_CR_START;
    }
    else
    {
        /* Disable TSC */
        TSC->CR &= ~TSC_CR_START;
    }
}

/**
  * @brief  Returns TSC sample result data.  
  * @param  TSC_IO: TSC IO
  *         This parameter can be one of the following values:
                TSC_IO_Gx_IOy(x[1:6], y[1-4])
  * @retval The sample value.
  */
uint16_t TSC_GetSampleValue(uint32_t TSC_IO)
{
    uint16_t temp;
    
    /* Check the parameters */
    assert_param(IS_TSC_GET_SAMPLE_VALUE_IO(TSC_IO));

    /* Return the selected TSC sample value */
    if (TSC_IO & 0xF)
        temp = (uint16_t)(TSC->IOG1CR);
    if (TSC_IO & 0xF0)
        temp = (uint16_t)(TSC->IOG2CR);
    if (TSC_IO & 0xF00)
        temp = (uint16_t)(TSC->IOG3CR);
    if (TSC_IO & 0xF000)
        temp = (uint16_t)(TSC->IOG4CR);
    if (TSC_IO & 0xF0000)
        temp = (uint16_t)(TSC->IOG5CR);
    if (TSC_IO & 0xF00000)
        temp = (uint16_t)(TSC->IOG6CR);

    return temp;
}

/**
  * @brief  Checks whether the specified TSC flag is set or not.
  * @param  TSC_FLAG: specifies the flag to check. 
  *          This parameter can be one of the following values:
  *            @arg TSC_FLAG_G1S
  *            @arg TSC_FLAG_G2S
  *            @arg TSC_FLAG_G3S
  *            @arg TSC_FLAG_G4S
  *            @arg TSC_FLAG_G5S
  *            @arg TSC_FLAG_G6S
  * @retval The new state of TSC_FLAG (SET or RESET).
  */
FlagStatus TSC_GetFlagStatus(uint32_t TSC_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_TSC_FLAG(TSC_FLAG));

    /* Check the status of the specified TSC flag */
    if ((TSC->IOGCSR & TSC_FLAG) != (uint32_t)RESET)
    {
        /* TSC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* TSC_FLAG is reset */
        bitstatus = RESET;
    }
    
    /* Return the TSC_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Enables or disables the TSC interrupt.
  * @param  TSC_IT: specifies the TSC interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg TSC_IT_MCE.
  *     @arg TSC_IT_EOA.
  * @param  NewState: new state of the TSC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TSC_ITConfig(uint32_t TSC_IT, FunctionalState NewState)  
{
    /* Check the parameters */
    assert_param(IS_TSC_IT(TSC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected TSC interrupts */
        TSC->IER |=  (TSC_IT);
    }
    else
    {
        /* Disable the selected TSC interrupts */
        TSC->IER &= ~(TSC_IT);
    }
}

/**
  * @brief  Checks whether the TSC interrupt has occurred or not.
  * @param  TSC_IT: specifies the TSC interrupts sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg TSC_IT_MCE.
  *     @arg TSC_IT_EOA.
  * @retval The new state of TSC_IT (SET or RESET).
  */
ITStatus TSC_GetITStatus(uint32_t TSC_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;
  
    /* Check the parameters */
    assert_param(IS_TSC_IT(TSC_IT));

    /* Get the TSC enable bit status */
    enablestatus = TSC->IER & TSC_IT;
  
    /* Check the status of the specified TSC interrupt */
    if (((TSC->ISR & TSC_IT) != (uint32_t)RESET) && enablestatus)
    {
        /* TSC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* TSC_IT is reset */
        bitstatus = RESET;
    }
    
    /* Return the TSC_IT status */
    return  bitstatus;
}

/**
  * @brief  Clears the TSC interrupt pending bits.
  * @param  TSC_IT: specifies the TSC interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg TSC_IT_MCE.
  *     @arg TSC_IT_EOA.
  * @retval None
  */
void TSC_ClearITPendingBit(uint32_t TSC_IT)
{
    /* Check the parameters */
    assert_param(IS_TSC_IT(TSC_IT));

    /* Clear the selected TSC interrupt pending bits */
    TSC->ICR |= TSC_IT;
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
