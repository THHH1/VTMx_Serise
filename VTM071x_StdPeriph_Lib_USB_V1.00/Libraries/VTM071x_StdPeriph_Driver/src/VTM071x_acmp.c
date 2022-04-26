/**
  ******************************************************************************
  * @file    VTM071x_acmp.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog Comparator (ACMP) peripheral:
  *           + Comparators configuration
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
#include "VTM071x_acmp.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup ACMP 
  * @brief ACMP driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ACMP_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes ACMP peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void ACMP_DeInit(void)
{
	RCC_APBPeriphResetCmd(RCC_PRESETCTRL_ACMP, ENABLE);
	RCC_APBPeriphResetCmd(RCC_PRESETCTRL_ACMP, DISABLE);
}

/**
  * @brief  Initializes the ACMP peripheral according to the specified parameters
  *         in the ACMP_InitStruct.
  * @param  ACMPx: Select the ACMP peripheral. 
  * @param  ACMP_InitStruct: pointer to an ACMP_InitTypeDef structure that contains 
  *         the configuration information for the specified ACMP peripheral.
  * @retval None
  */
void ACMP_Init(uint32_t ACMPx, ACMP_InitTypeDef* ACMP_InitStruct)
{
    assert_param(IS_ACMP_NEGATIVE_SELECT(ACMP_InitStruct->ACMP_NegativeSelect));
    assert_param(IS_ACMP_POSITIVE_SELECT(ACMP_InitStruct->ACMP_PositiveSelect));
    assert_param(IS_ACMP_OUTPUT_STATE(ACMP_InitStruct->ACMP_Output));
    assert_param(IS_ACMP_HYSTERESIS(ACMP_InitStruct->ACMP_Hysteresis));
    assert_param(IS_ACMP_ALL_PERIPH(ACMPx));
    
    switch(ACMPx)
    {
        case ACMP0:
            ACMP->CTRL0 = ACMP_InitStruct->ACMP_PositiveSelect | \
                          ACMP_InitStruct->ACMP_NegativeSelect | \
                          ACMP_InitStruct->ACMP_Output | \
                          ACMP_InitStruct->ACMP_Hysteresis;
        break;
        
        case ACMP1:
            ACMP->CTRL1 = ACMP_InitStruct->ACMP_PositiveSelect | \
                          ACMP_InitStruct->ACMP_NegativeSelect | \
                          ACMP_InitStruct->ACMP_Output | \
                          ACMP_InitStruct->ACMP_Hysteresis;
        break;
        
        default:
            ACMP->CTRL2 = ACMP_InitStruct->ACMP_PositiveSelect | \
                          ACMP_InitStruct->ACMP_NegativeSelect | \
                          ACMP_InitStruct->ACMP_Output | \
                          ACMP_InitStruct->ACMP_Hysteresis;
        break;
    }
}

/**
  * @brief  Select ACMP0 pin.
  * @param  ACMP_Pin: ACMP 0 pin.
  *   This parameter can be: ACMP0_PIN_GPIO00_GPIO01 or ACMP0_PIN_GPIO20_GPIO21.
  * @retval None
  */
void ACMP0_PinConfig(uint32_t ACMP_Pin)
{
	/* Check the parameters */
    assert_param(IS_ACMP0_PIN(ACMP_Pin));
    
    if (ACMP_Pin == ACMP0_PIN_GPIO00_GPIO01)
        ACMP->ADV_CTRL0 &= ~ACMP0_PIN_GPIO20_GPIO21;
    else
        ACMP->ADV_CTRL0 |= ACMP0_PIN_GPIO20_GPIO21;
}

/**
  * @brief  Select ACMP1 pin.
  * @param  ACMP_Pin: ACMP 1 pin.
  *   This parameter can be: ACMP1_PIN_GPIO02_GPIO03 or ACMP1_PIN_GPIO40_GPIO41.
  * @retval None
  */
void ACMP1_PinConfig(uint32_t ACMP_Pin)
{
	/* Check the parameters */
    assert_param(IS_ACMP1_PIN(ACMP_Pin));
    
    if (ACMP_Pin == ACMP1_PIN_GPIO02_GPIO03)
        ACMP->ADV_CTRL1 &= ~ACMP1_PIN_GPIO40_GPIO41;
    else
        ACMP->ADV_CTRL1 |= ACMP1_PIN_GPIO40_GPIO41;
}

/**
  * @brief  Select ACMP2 pin.
  * @param  ACMP_Pin: ACMP 2 pin.
  *   This parameter can be: ACMP2_PIN_GPIO04_GPIO05 or ACMP2_PIN_GPIO42_GPIO43.
  * @retval None
  */
void ACMP2_PinConfig(uint32_t ACMP_Pin)
{
	/* Check the parameters */
    assert_param(IS_ACMP2_PIN(ACMP_Pin));
    
    if (ACMP_Pin == ACMP2_PIN_GPIO04_GPIO05)
        ACMP->ADV_CTRL2 &= ~ACMP2_PIN_GPIO42_GPIO43;
    else
        ACMP->ADV_CTRL2 |= ACMP2_PIN_GPIO42_GPIO43;
}

/**
  * @brief  Enables or disables ACMP.
  * @param  ACMPx: Select the ACMP peripheral. 
  *   This parameter can be one of the following values: ACMPx,x:[0:2].
  * @param  NewState: new state of ACMP.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ACMP_Cmd(uint32_t ACMPx, FunctionalState NewState)
{
	/* Check the parameters */
    assert_param(IS_ACMP_ALL_PERIPH(ACMPx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        switch(ACMPx)
        {
            case ACMP0:
                ACMP->CTRL0 |= ACMP_CTRL_CMP_EN;
            break;
            
            case ACMP1:
                ACMP->CTRL1 |= ACMP_CTRL_CMP_EN;
            break;
            
            default:
                ACMP->CTRL2 |= ACMP_CTRL_CMP_EN;
            break;
        }
    }
    else
    {
        switch(ACMPx)
        {
            case ACMP0:
                ACMP->CTRL0 &= ~ACMP_CTRL_CMP_EN;
            break;
            
            case ACMP1:
                ACMP->CTRL1 &= ~ACMP_CTRL_CMP_EN;
            break;
            
            default:
                ACMP->CTRL2 &= ~ACMP_CTRL_CMP_EN;
            break;
        }
    }
}

/**
  * @brief  Enables or disables the specified ACMP interrupts.
  * @param  ACMPx: Select the ACMP peripheral. 
  *   This parameter can be one of the following values: ACMPx,x:[0:2].
  * @param  NewState: new state of the specified ACMP interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ACMP_ITConfig(uint32_t ACMPx, FunctionalState NewState)
{
	/* Check the parameters */
    assert_param(IS_ACMP_ALL_PERIPH(ACMPx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        switch(ACMPx)
        {
            case ACMP0:
                ACMP->CTRL0 |= ACMP_CTRL_CMP_IE;
            break;
            
            case ACMP1:
                ACMP->CTRL1 |= ACMP_CTRL_CMP_IE;
            break;
            
            default:
                ACMP->CTRL2 |= ACMP_CTRL_CMP_IE;
            break;
        }
    }
    else
    {
        switch(ACMPx)
        {
            case ACMP0:
                ACMP->CTRL0 &= ~ACMP_CTRL_CMP_IE;
            break;
            
            case ACMP1:
                ACMP->CTRL1 &= ~ACMP_CTRL_CMP_IE;
            break;
            
            default:
                ACMP->CTRL2 &= ~ACMP_CTRL_CMP_IE;
            break;
        }
    }
}

/**
  * @brief  Get ACMP result.
  * @param  ACMPx: Select the ACMP peripheral. 
  *   This parameter can be one of the following values: ACMPx,x:[0:2].
  * @retval None
  */
FlagStatus ACMP_GetResult(uint32_t ACMPx)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
    assert_param(IS_ACMP_ALL_PERIPH(ACMPx));
    
    switch(ACMPx)
    {
        case ACMP0:
            if (ACMP->STATUS & ACMP_STATUS_RESULT0)
                bitstatus = SET;
        break;
        
        case ACMP1:
            if (ACMP->STATUS & ACMP_STATUS_RESULT1)
                bitstatus = SET;
        break;
        
        default:
            if (ACMP->STATUS & ACMP_STATUS_RESULT2)
                bitstatus = SET;
        break;
    }

	return bitstatus;
}

/**
  * @brief  Checks whether ACMP interrupt has occurred or not.
  * @param  ACMPx: Select the ACMP peripheral. 
  *   This parameter can be one of the following values: ACMPx,x:[0:2].
  * @retval The new state of ACMP (SET or RESET).
  */
ITStatus ACMP_GetITStatus(uint32_t ACMPx)
{
	ITStatus bitstatus = RESET;
	uint32_t enablestatus = 0;

	/* Check the parameters */
    assert_param(IS_ACMP_ALL_PERIPH(ACMPx));
    
    switch(ACMPx)
    {
        case ACMP0:
            if (ACMP->CTRL0 & ACMP_CTRL_CMP_IE)
                enablestatus = 1;
            
            if (enablestatus && (ACMP->STATUS & ACMP_STATUS_INT_FLAG0))
                bitstatus = SET;
        break;
        
        case ACMP1:
            if (ACMP->CTRL1 & ACMP_CTRL_CMP_IE)
                enablestatus = 1;
            
            if (enablestatus && (ACMP->STATUS & ACMP_STATUS_INT_FLAG1))
                bitstatus = SET;
        break;
        
        default:
            if (ACMP->CTRL2 & ACMP_CTRL_CMP_IE)
                enablestatus = 1;
            
            if (enablestatus && (ACMP->STATUS & ACMP_STATUS_INT_FLAG2))
                bitstatus = SET;
        break;
    }
    
	return  bitstatus;
}

/**
  * @brief  Clears the ACMP's interrupt pending bits.
  * @param  ACMPx: Select the ACMP peripheral. 
  *   This parameter can be one of the following values: ACMPx,x:[0:2].
  * @retval None
  */
void ACMP_ClearITPendingBit(uint32_t ACMPx)
{
	/* Check the parameters */
    assert_param(IS_ACMP_ALL_PERIPH(ACMPx));
    
    switch(ACMPx)
    {
        case ACMP0:
            ACMP->STATUS |= ACMP_STATUS_INT_FLAG0;
        break;
        
        case ACMP1:
            ACMP->STATUS |= ACMP_STATUS_INT_FLAG1;
        break;
        
        default:
            ACMP->STATUS |= ACMP_STATUS_INT_FLAG2;
        break;
    }
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

/************************ (C) COPYRIGHT MIC *****END OF FILE****/

