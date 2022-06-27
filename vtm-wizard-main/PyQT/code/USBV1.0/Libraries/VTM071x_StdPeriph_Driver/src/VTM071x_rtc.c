/**
  ******************************************************************************
  * @file    VTM071x_rtc.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides all the RTC firmware functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MIC SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "VTM071x_rtc.h"
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC
  * @brief RTC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RTC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the RTC peripheral registers to their default reset values.
  * @param  None. 
  * @retval None
  */
void RTC_DeInit(void)
{
    /* Enable RTC Clock */
    RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_RTC, ENABLE);
    RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_RTC, DISABLE);
}

/**
  * @brief  Initializes the RTC peripheral according to the specified 
  *         parameters in the RTC_InitStruct.
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure that
  *         contains the configuration information for the specified RTC peripheral.
  * @retval None
  */
void RTC_Init(RTC_InitTypeDef* RTC_InitStruct)
{
    volatile uint32_t tmpreg;

	/* Check the RTC parameters */
	assert_param(IS_RTC_CLOCK_SOURCE(RTC_InitStruct->RTC_ClkSource));

    RTC->CNT = RTC_InitStruct->RTC_Second;

    tmpreg = RTC->CTRL;
    tmpreg &= ~RTC_CTRL_CLK_SEL_MASK;
    tmpreg |= RTC_InitStruct->RTC_ClkSource;
    RTC->CTRL = tmpreg;
}

/**
  * @brief  Enable or disable RTC load bit.
  * @param  None
  * @retval None
  */
void RTC_LoadCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable RTC Counter */
		RTC->LOAD |= RTC_LOAD_EN;
	}
	else
	{
		/* Disable RTC Counter */
		RTC->LOAD &= ~RTC_LOAD_EN;
	}
}

/**
  * @brief  Select the source of RTC.
  * @param  ClockSource: Source of RTC. 
  *         This parameter can be one of the following values:
  *             @arg RTC_CCR_32K: 32KHz 
  *             @arg RTC_CCR_10K: 10KHz 
  *             @arg RTC_CCR_OSC_12M: 12MHz 
  *             @arg RTC_CCR_IRC_12M: 12MHz. 
  * @retval None
  */
void RTC_CLOCKSourceSelect(uint32_t ClockSource)
{
    volatile uint32_t tmpreg;

	/* Check the RTC parameters */
	assert_param(IS_RTC_CLOCK_SOURCE(ClockSource));

    tmpreg = RTC->CTRL;
    tmpreg &= ~RTC_CTRL_CLK_SEL_MASK;
    tmpreg |= ClockSource;
    RTC->CTRL = tmpreg;
}

/**
  * @brief  Enables or disables the RTC Counter.
  * @param  NewState: new state of RTC Counter. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable RTC Counter */
		RTC->CTRL |= RTC_CTRL_EN;
	}
	else
	{
		/* Disable RTC Counter */
		RTC->CTRL &= ~RTC_CTRL_EN;
	}
}

/**
  * @brief  Configure the RTC Alarm.
  * @param  Second: Second for the specified RTC Alarm.
  * @retval None
  */
void RTC_AlarmConfig(uint32_t Second)
{
	RTC->ALARM = Second;
}

/**
  * @brief  Configure the RTC count.
  * @param  Second: Second for the specified RTC Alarm.
  * @retval None
  */
void RTC_CountConfig(uint32_t Second)
{
	RTC->CNT = Second;
}

/**
  * @brief  Get RTC time.
  * @param  None.
  * @retval RTC time.
  */
uint32_t RTC_GetTime(void)
{
    return RTC->CNT;
}

/**
  * @brief  Enables or disables the specified RTC interrupts.
  * @param  RTC_IT: specifies the RTC interrupts sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg RTC_IT_SEC: Seccond interrupt.
  *     @arg RTC_IT_ALARM: Alarm interrupt.
  * @param  NewState: new state of the specified RTC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RTC_IT(RTC_IT));  
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RTC->CTRL |= RTC_IT;
    }
    else
    {
        RTC->CTRL &= ~RTC_IT;
    }
}

/**
  * @brief  Checks whether the specified RTC interrupt has occured or not.
  * @param  RTC_IT: specifies the RTC interrupts sources to check.
  *         This parameter can be one of the following values:
  *             @arg RTC_IT_SEC: Counter increment interrupt flag.
  *             @arg RTC_IT_ALARM: Alarm register interrupt flag.
  * @retval The new state of the RTC_IT (SET or RESET).
  */
ITStatus RTC_GetITStatus(uint32_t RTC_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_RTC_IT_FLAG(RTC_IT)); 

    if (RTC_IT == RTC_IT_SEC)
    {
        if ((RTC->CTRL & RTC_IT_SEC) && (RTC->STAT & RTC_STAT_1HZ_INT))
            bitstatus = SET;
        else
            bitstatus = RESET;
    }
    else
    {
        if ((RTC->CTRL & RTC_IT_ALARM) && (RTC->STAT & RTC_STAT_ALARM_INT))
            bitstatus = SET;
        else
            bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * @brief  Clears the RTC interrupt pending bits.
  * @param  RTC_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be one of the following values:
  *             @arg RTC_IT_SEC: Counter increment interrupt flag.
  *             @arg RTC_IT_ALARM: Alarm register interrupt flag.
  * @retval None
  */
void RTC_ClearITPendingBit(uint32_t RTC_IT)
{
    /* Check the parameters */
    assert_param(IS_RTC_IT_FLAG(RTC_IT));  

    /* Clear the coressponding RTC pending bit */
    if (RTC_IT == RTC_IT_SEC)
    {
        RTC->STAT = RTC_STAT_1HZ_INT;
    }
    else
    {
        RTC->STAT = RTC_STAT_ALARM_INT;
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

/******************* (C) COPYRIGHT 2018 MIC *****END OF FILE****/

