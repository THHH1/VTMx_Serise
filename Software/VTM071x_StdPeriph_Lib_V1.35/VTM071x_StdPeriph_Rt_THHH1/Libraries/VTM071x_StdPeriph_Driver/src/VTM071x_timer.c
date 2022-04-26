/**
  ******************************************************************************
  * @file    VTM071x_timer.c
  * @author  MIC Software Team 
  * @version V0.0.0
  * @date    03/01/2018
  * @brief   This file provides all the TIMER firmware functions.
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
#include "VTM071x_timer.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup TIMER
  * @brief TIMER driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PWM_PULSE_COUNTER_BIT_OFFSET    4
#define PWM_INVERT_BIT_OFFSET           16

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup TIMER_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TIMERx peripheral registers to their default reset values.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMER peripheral.
  * @retval None
  */
void TIMER_DeInit(TIMER_TypeDef* TIMERx)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx)); 

	if (TIMERx == TIMER0)
	{
		RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_TIMER0, ENABLE);
		RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_TIMER0, DISABLE);
	}
	else if (TIMERx == TIMER1)
	{
		RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_TIMER1, ENABLE);
		RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_TIMER1, DISABLE);
	}
	else if (TIMERx == TIMER2)
	{
		RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_TIMER2, ENABLE);
		RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_TIMER2, DISABLE);
	}
	else if (TIMERx == TIMER3)
	{
		RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_TIMER3, ENABLE);
		RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_TIMER3, DISABLE);
	}
}

/**
  * @brief  Initializes the TIMER according to 
  *   the specified parameters in the TIMER_InitTypeDef.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMER peripheral.
  * @param  TIMER_InitStruct: pointer to a TIMER_InitTypeDef
  *   structure that contains the configuration information for the specified TIMER peripheral.
  * @retval None
  */
void TIMER_Init(TIMER_TypeDef* TIMERx, TIMER_InitTypeDef* TIMER_InitStruct)
{
    uint32_t tmpreg=0;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_CONFIG(TIMER_InitStruct->TIMER_Channel));
    assert_param(IS_TIMER_Direction(TIMER_InitStruct->TIMER_Dir));
    assert_param(IS_TIMER_Match_Action(TIMER_InitStruct->TIMER_MatchAction));
    assert_param(IS_TIMER_Match_Config(TIMER_InitStruct->TIMER_MatchConfig));

    /* DIR */
    tmpreg = TIMERx->DIR;
    if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        tmpreg &= ~TIMER_DIR0;
        tmpreg |= TIMER_InitStruct->TIMER_Dir;
    }
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        tmpreg &= ~TIMER_DIR1;
        tmpreg |= (TIMER_InitStruct->TIMER_Dir << 4);
    }
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        tmpreg &= ~TIMER_DIR2;
        tmpreg |= (TIMER_InitStruct->TIMER_Dir << 8);
    }
    else
    {
        tmpreg &= ~TIMER_DIR3;
        tmpreg |= (TIMER_InitStruct->TIMER_Dir << 12);
    }
    TIMERx->DIR = tmpreg;

    /* MR */
    if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_0)
        TIMERx->MR0 = TIMER_InitStruct->TIMER_MatchValue;
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_1)
        TIMERx->MR1 = TIMER_InitStruct->TIMER_MatchValue;
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_2)
        TIMERx->MR2 = TIMER_InitStruct->TIMER_MatchValue;
    else
        TIMERx->MR3 = TIMER_InitStruct->TIMER_MatchValue;

    /* EMR */
    tmpreg = TIMERx->EMR;
    if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        tmpreg &= ~TIMER_EMR_EMC0;
        tmpreg |= TIMER_InitStruct->TIMER_MatchAction << 4;
    }
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        tmpreg &= ~TIMER_EMR_EMC1;
        tmpreg |= TIMER_InitStruct->TIMER_MatchAction << 6;
    }
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        tmpreg &= ~TIMER_EMR_EMC2;
        tmpreg |= TIMER_InitStruct->TIMER_MatchAction << 8;
    }
    else
    {
        tmpreg &= ~TIMER_EMR_EMC3;
        tmpreg |= TIMER_InitStruct->TIMER_MatchAction << 10;
    }
    TIMERx->EMR = tmpreg;

    /* MCR */
    tmpreg = TIMERx->MCR;
    if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        tmpreg &= ~(TIMER_MCR_MR0R | TIMER_MCR_MR0S);
        tmpreg |= TIMER_InitStruct->TIMER_MatchConfig;
    }
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        tmpreg &= ~(TIMER_MCR_MR1R | TIMER_MCR_MR1S);
        tmpreg |= (TIMER_InitStruct->TIMER_MatchConfig << 3);
    }
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        tmpreg &= ~(TIMER_MCR_MR2R | TIMER_MCR_MR2S);
        tmpreg |= (TIMER_InitStruct->TIMER_MatchConfig << 6);
    }
    else
    {
        tmpreg &= ~(TIMER_MCR_MR3R | TIMER_MCR_MR3S);
        tmpreg |= (TIMER_InitStruct->TIMER_MatchConfig << 9);
    }
    TIMERx->MCR = tmpreg;

    /* CTCR */
    tmpreg = TIMERx->CTCR;
    if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        tmpreg &= ~TIMER_CTCR_MODE0_MASK;
    }
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        tmpreg &= ~TIMER_CTCR_MODE1_MASK;
    }
    else if (TIMER_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        tmpreg &= ~TIMER_CTCR_MODE2_MASK;
    }
    else
    {
        tmpreg &= ~TIMER_CTCR_MODE3_MASK;
    }
    TIMERx->CTCR = tmpreg;
}

/**
  * @brief  Set prescale.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  Prescale: Prescale value.
  * @retval None
  */
void TIMER_SetPrescale(TIMER_TypeDef* TIMERx, uint32_t Prescale)
{  
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->PR = Prescale;
}

/**
  * @brief  Get prescale.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @retval Prescale
  */
uint32_t TIMER_GetPrescale(TIMER_TypeDef* TIMERx)
{  
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return TIMERx->PR;
}

/**
  * @brief  Set idle level.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  Value: Count of pulse.
  *   This parameter can be one of the following values:
  *     @arg Timer_IDLE_LEVEL_HOLD
  *     @arg Timer_IDLE_LEVEL_LOW
  *     @arg Timer_IDLE_LEVEL_HIGH
  *     @arg Timer_IDLE_LEVEL_HIGH_RESISTANCE
  * @retval None
  */
void TIMER_SetIdleLevel(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Level)
{
    uint32_t tmpreg;
    
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_CONFIG(Channel));
	assert_param(IS_TIMER_IDLE_LEVEL(Level));
    
    tmpreg = TIMERx->TCR;
    
    if (Channel == Timer_Channel_0)
    {
        tmpreg &= ~TIMER_TCR0_OUT;
        tmpreg |= Level << 8;
    }
    else if (Channel == Timer_Channel_1)
    {
        tmpreg &= ~TIMER_TCR1_OUT;
        tmpreg |= Level << 10;
    }
    else if (Channel == Timer_Channel_2)
    {
        tmpreg &= ~TIMER_TCR2_OUT;
        tmpreg |= Level << 12;
    }
    else
    {
        tmpreg &= ~TIMER_TCR3_OUT;
        tmpreg |= Level << 14;
    }
    
    TIMERx->TCR = tmpreg;
}

/**
  * @brief  Set Match default level.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  Value: Count of pulse.
  *   This parameter can be one of the following values:
  *     @arg Timer_MATCH_DEFAULT_LEVEL_LOW
  *     @arg Timer_MATCH_DEFAULT_LEVEL_HIGH
  * @retval None
  */
void TIMER_SetMatchDefaultLevel(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Level)
{
    uint32_t tmpreg;
    
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_CONFIG(Channel));
	assert_param(IS_TIMER_MATCH_DEFAULT_LEVEL(Level));
    
    tmpreg = TIMERx->EMR;
    
    if (Channel == Timer_Channel_0)
    {
        tmpreg &= ~(Timer_MATCH_DEFAULT_LEVEL_HIGH << 12);
        tmpreg |= Level << 12;
    }
    else if (Channel == Timer_Channel_1)
    {
        tmpreg &= ~(Timer_MATCH_DEFAULT_LEVEL_HIGH << 13);
        tmpreg |= Level << 13;
    }
    else if (Channel == Timer_Channel_2)
    {
        tmpreg &= ~(Timer_MATCH_DEFAULT_LEVEL_HIGH << 14);
        tmpreg |= Level << 14;
    }
    else
    {
        tmpreg &= ~(Timer_MATCH_DEFAULT_LEVEL_HIGH << 15);
        tmpreg |= Level << 15;
    }
    
    TIMERx->EMR = tmpreg;
}

/**
  * @brief  Set match action.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  Value: Count of pulse.
  *   This parameter can be one of the following values:
  *     @arg Timer_MATCH_ACTION_HOLD
  *     @arg Timer_MATCH_ACTION_LOW
  *     @arg Timer_MATCH_ACTION_HIGH
  *     @arg Timer_MATCH_ACTION_TOG
  * @retval None
  */
void TIMER_SetMatchAction(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Action)
{
    uint32_t tmpreg;
    
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_CONFIG(Channel));
	assert_param(IS_TIMER_MATCH_ACTION(Action));
    
    tmpreg = TIMERx->EMR;
    
    if (Channel == Timer_Channel_0)
    {
        tmpreg &= ~TIMER_EMR_EMC0;
        tmpreg |= Action << 4;
    }
    else if (Channel == Timer_Channel_1)
    {
        tmpreg &= ~TIMER_EMR_EMC1;
        tmpreg |= Action << 6;
    }
    else if (Channel == Timer_Channel_2)
    {
        tmpreg &= ~TIMER_EMR_EMC2;
        tmpreg |= Action << 8;
    }
    else
    {
        tmpreg &= ~TIMER_EMR_EMC3;
        tmpreg |= Action << 10;
    }
    
    TIMERx->EMR = tmpreg;
}

/**
  * @brief  Get timer match status.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @retval None
  */
FlagStatus TIMER_GetMatchLevel(TIMER_TypeDef* TIMERx, uint32_t Channel)
{
    FlagStatus status = RESET;
    
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_SWITCH(Channel));

    if (Channel == Timer_Channel_0)
    {
        if (TIMERx->EMR & TIMER_EMR_EM0)
            status = SET;
    }
    else if (Channel == Timer_Channel_1)
    {
        if (TIMERx->EMR & TIMER_EMR_EM1)
            status = SET;
    }
    else if (Channel == Timer_Channel_2)
    {
        if (TIMERx->EMR & TIMER_EMR_EM2)
            status = SET;
    }
    else
    {
        if (TIMERx->EMR & TIMER_EMR_EM3)
            status = SET;
    }
    
    return status;
}

/**
  * @brief  Reset Timer.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  NewState: new state of the TIMERx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_ResetCmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_TIMER_CHANNEL_SWITCH(Channel));

	if (NewState != DISABLE)
    {
        TIMERx->TCR |= Channel << 4;
    }
	else
    {
        TIMERx->TCR &= ~(Channel << 4);
    }
}

/**
  * @brief  Stop timer when next matching.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  NewState: new state of the TIMERx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_StopTC(TIMER_TypeDef* TIMERx, uint32_t Channel)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_SWITCH(Channel));

	if (Channel == Timer_Channel_0)
		TIMERx->MCR |= TIMER_MCR_MR0S;
	else if (Channel == Timer_Channel_1)
		TIMERx->MCR |= TIMER_MCR_MR1S;
	else if (Channel == Timer_Channel_2)
		TIMERx->MCR |= TIMER_MCR_MR2S;
	else
		TIMERx->MCR |= TIMER_MCR_MR3S;
}

/**
  * @brief  Enables or disables Timer.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be any combination of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  NewState: new state of the TIMERx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_Cmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_TIMER_CHANNEL_SWITCH(Channel));

	if (NewState != DISABLE)
    {
        TIMERx->TCR |= Channel;
    }
	else
    {
        TIMERx->TCR &= ~Channel;
    }
}

/**
  * @brief  Get TC register.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @retval TC register value.
  */
uint32_t TIMER_GetTC(TIMER_TypeDef* TIMERx, uint32_t Channel)
{
    uint32_t tmpreg=0;

    /* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_CONFIG(Channel));

    if (Channel == Timer_Channel_0)
        tmpreg = TIMERx->TC0;
    else if (Channel == Timer_Channel_1)
        tmpreg = TIMERx->TC1;
    else if (Channel == Timer_Channel_2)
        tmpreg = TIMERx->TC2;
    else
        tmpreg = TIMERx->TC3;

    return tmpreg;
}

/**
  * @brief  Initializes the Counter according to 
  *   the specified parameters in the COUNTER_InitTypeDef.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMER peripheral.
  * @param  COUNTER_InitStruct: pointer to a COUNTER_InitTypeDef
  *   structure that contains the configuration information for the specified TIMER peripheral.
  * @retval None
  */
void COUNTER_Init(TIMER_TypeDef* TIMERx, COUNTER_InitTypeDef* COUNTER_InitStruct)
{
    uint32_t tmpreg=0;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_CONFIG(COUNTER_InitStruct->TIMER_Channel));
    assert_param(IS_COUNTERMODE(COUNTER_InitStruct->COUNTER_Mode));
    assert_param(IS_TIMER_Direction(COUNTER_InitStruct->COUNTER_Dir));
    assert_param(IS_COUNTER_GPIO_Pin(COUNTER_InitStruct->COUNTER_Pin));
    assert_param(IS_COUNTER_Filter_Cycles(COUNTER_InitStruct->COUNTER_Filter));
    assert_param(IS_TIMER_Match_Action(COUNTER_InitStruct->COUNTER_MatchAction));
    assert_param(IS_TIMER_Match_Config(COUNTER_InitStruct->COUNTER_MatchConfig));

    /* DIR */
    tmpreg = TIMERx->DIR;
    if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        tmpreg &= ~TIMER_DIR0;
        tmpreg |= COUNTER_InitStruct->COUNTER_Dir;
    }
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        tmpreg &= ~TIMER_DIR1;
        tmpreg |= (COUNTER_InitStruct->COUNTER_Dir << 4);
    }
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        tmpreg &= ~TIMER_DIR2;
        tmpreg |= (COUNTER_InitStruct->COUNTER_Dir << 8);
    }
    else
    {
        tmpreg &= ~TIMER_DIR3;
        tmpreg |= (COUNTER_InitStruct->COUNTER_Dir << 12);
    }
    TIMERx->DIR = tmpreg;

    /* MR */
    if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_0)
        TIMERx->MR0 = COUNTER_InitStruct->COUNTER_MatchValue;
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_1)
        TIMERx->MR1 = COUNTER_InitStruct->COUNTER_MatchValue;
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_2)
        TIMERx->MR2 = COUNTER_InitStruct->COUNTER_MatchValue;
    else
        TIMERx->MR3 = COUNTER_InitStruct->COUNTER_MatchValue;

    /* EMR */
    tmpreg = TIMERx->EMR;
    if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        tmpreg &= ~TIMER_EMR_EMC0;
        tmpreg |= COUNTER_InitStruct->COUNTER_MatchAction << 4;
    }
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        tmpreg &= ~TIMER_EMR_EMC1;
        tmpreg |= COUNTER_InitStruct->COUNTER_MatchAction << 6;
    }
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        tmpreg &= ~TIMER_EMR_EMC2;
        tmpreg |= COUNTER_InitStruct->COUNTER_MatchAction << 8;
    }
    else
    {
        tmpreg &= ~TIMER_EMR_EMC3;
        tmpreg |= COUNTER_InitStruct->COUNTER_MatchAction << 10;
    }
    TIMERx->EMR = tmpreg;

    /* MCR */
    tmpreg = TIMERx->MCR;
    if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        tmpreg &= ~(TIMER_MCR_MR0R | TIMER_MCR_MR0S);
        tmpreg |= COUNTER_InitStruct->COUNTER_MatchConfig;
    }
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        tmpreg &= ~(TIMER_MCR_MR1R | TIMER_MCR_MR1S);
        tmpreg |= (COUNTER_InitStruct->COUNTER_MatchConfig << 3);
    }
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        tmpreg &= ~(TIMER_MCR_MR2R | TIMER_MCR_MR2S);
        tmpreg |= (COUNTER_InitStruct->COUNTER_MatchConfig << 6);
    }
    else
    {
        tmpreg &= ~(TIMER_MCR_MR3R | TIMER_MCR_MR3S);
        tmpreg |= (COUNTER_InitStruct->COUNTER_MatchConfig << 9);
    }
    TIMERx->MCR = tmpreg;

    /* CTCR */
    tmpreg = TIMERx->CTCR;
    if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        tmpreg &= ~TIMER_CTCR_MODE0_MASK;
        tmpreg |= COUNTER_InitStruct->COUNTER_Mode;
    }
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        tmpreg &= ~TIMER_CTCR_MODE1_MASK;
        tmpreg |= (COUNTER_InitStruct->COUNTER_Mode << 2);
    }
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        tmpreg &= ~TIMER_CTCR_MODE2_MASK;
        tmpreg |= (COUNTER_InitStruct->COUNTER_Mode << 4);
    }
    else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_3)
    {
        tmpreg &= ~TIMER_CTCR_MODE3_MASK;
        tmpreg |= (COUNTER_InitStruct->COUNTER_Mode << 6);
    }
    TIMERx->CTCR = tmpreg;

    /* CCR */
    tmpreg = 0;
    if (COUNTER_InitStruct->COUNTER_Pin == COUNTER_Pin_0)
    {
        if (COUNTER_InitStruct->COUNTER_Mode == COUNTER_RISING_EDGE)
            tmpreg |= TIMER_CCR_CAP0RE;
        else if (COUNTER_InitStruct->COUNTER_Mode == COUNTER_FALLING_EDGE)
            tmpreg |= TIMER_CCR_CAP0FE;
        else
            tmpreg |= TIMER_CCR_CAP0RE | TIMER_CCR_CAP0FE;
        
        tmpreg |= COUNTER_InitStruct->COUNTER_Filter << 4;
        
        if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_0)
        {
            tmpreg &= ~TIMER_CCR_CNT0CAP;
        }
        else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_1)
        {
            tmpreg &= ~TIMER_CCR_CNT1CAP;
        }
        else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_2)
        {
            tmpreg &= ~TIMER_CCR_CNT2CAP;
        }
        else
        {
            tmpreg &= ~TIMER_CCR_CNT3CAP;
        }
    }
    else
    {
        if (COUNTER_InitStruct->COUNTER_Mode == COUNTER_RISING_EDGE)
            tmpreg |= TIMER_CCR_CAP1RE;
        else if (COUNTER_InitStruct->COUNTER_Mode == COUNTER_FALLING_EDGE)
            tmpreg |= TIMER_CCR_CAP1FE;
        else
            tmpreg |= TIMER_CCR_CAP1RE | TIMER_CCR_CAP1FE;
        
        tmpreg |= COUNTER_InitStruct->COUNTER_Filter << 12;

        if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_0)
        {
            tmpreg |= TIMER_CCR_CNT0CAP;
        }
        else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_1)
        {
            tmpreg |= TIMER_CCR_CNT1CAP;
        }
        else if (COUNTER_InitStruct->TIMER_Channel == Timer_Channel_2)
        {
            tmpreg |= TIMER_CCR_CNT2CAP;
        }
        else
        {
            tmpreg |= TIMER_CCR_CNT3CAP;
        }
    }
    TIMERx->CCR = tmpreg;
}

/**
  * @brief  Get CR register.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @retval CR register value.
  */
uint32_t TIMER_GetCR(TIMER_TypeDef* TIMERx, uint32_t Channel)
{
    uint32_t tmpreg=0;

    /* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_CONFIG(Channel));

    if (Channel == Timer_Channel_0)
        tmpreg = TIMERx->CR0;
    else if (Channel == Timer_Channel_1)
        tmpreg = TIMERx->CR1;
    else if (Channel == Timer_Channel_2)
        tmpreg = TIMERx->CR2;
    else
        tmpreg = TIMERx->CR3;

    return tmpreg;
}

/**
  * @brief  Get state of external match.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @retval CR register value.
  */
FlagStatus TIMER_GetExternalMatchState(TIMER_TypeDef* TIMERx, uint32_t Channel)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_CONFIG(Channel));

    if ((TIMERx->EMR & Channel) != RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * @brief  Initializes the PWM according to 
  *   the specified parameters in the PWM_InitTypeDef.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMER peripheral.
  * @param  COUNTER_InitStruct: pointer to a PWM_InitTypeDef
  *   structure that contains the configuration information for the specified TIMER peripheral.
  * @retval None
  */
void PWM_Init(TIMER_TypeDef* TIMERx, PWM_InitTypeDef* PWM_InitStruct)
{
    uint32_t tmpreg=0;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_CONFIG(PWM_InitStruct->TIMER_Channel));
    assert_param(IS_PWM_ValidState(PWM_InitStruct->PWM_ValidState));
    assert_param(IS_PWM_InvalidState(PWM_InitStruct->PWM_InvalidState));

    /* PWMTH & MR */
    if (PWM_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        TIMERx->PWMTH0 = PWM_InitStruct->PWM_Threshold;
        TIMERx->MR0 = PWM_InitStruct->PWM_MatchValue;
    }
    else if (PWM_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        TIMERx->PWMTH1 = PWM_InitStruct->PWM_Threshold;
        TIMERx->MR1 = PWM_InitStruct->PWM_MatchValue;
    }
    else if (PWM_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        TIMERx->PWMTH2 = PWM_InitStruct->PWM_Threshold;
        TIMERx->MR2 = PWM_InitStruct->PWM_MatchValue;
    }
    else
    {
        TIMERx->PWMTH3 = PWM_InitStruct->PWM_Threshold;
        TIMERx->MR3 = PWM_InitStruct->PWM_MatchValue;
    }

    /* PWMCR */
    tmpreg = TIMERx->PWMC;
    if (PWM_InitStruct->TIMER_Channel == Timer_Channel_0)
    {
        tmpreg &= ~(TIMER_PWMCR_A0HIZ | TIMER_PWMCR_INA0HIZ);
        tmpreg |= (PWM_InitStruct->PWM_ValidState << 8);
        tmpreg |= (PWM_InitStruct->PWM_InvalidState << 9);
    }
    else if (PWM_InitStruct->TIMER_Channel == Timer_Channel_1)
    {
        tmpreg &= ~(TIMER_PWMCR_A1HIZ | TIMER_PWMCR_INA1HIZ);
        tmpreg |= (PWM_InitStruct->PWM_ValidState << 10);
        tmpreg |= (PWM_InitStruct->PWM_InvalidState << 11);
    }
    else if (PWM_InitStruct->TIMER_Channel == Timer_Channel_2)
    {
        tmpreg &= ~(TIMER_PWMCR_A2HIZ | TIMER_PWMCR_INA2HIZ);
        tmpreg |= (PWM_InitStruct->PWM_ValidState << 12);
        tmpreg |= (PWM_InitStruct->PWM_InvalidState << 13);
    }
    else if (PWM_InitStruct->TIMER_Channel == Timer_Channel_3)
    {
        tmpreg &= ~(TIMER_PWMCR_A3HIZ | TIMER_PWMCR_INA3HIZ);
        tmpreg |= (PWM_InitStruct->PWM_ValidState << 14);
        tmpreg |= (PWM_InitStruct->PWM_InvalidState << 15);
    }
    TIMERx->PWMC = tmpreg;
}

/**
  * @brief  Set PWM threshold and match
  * @param  TIMERx: where x can be 0 to 3 to select the TIMER peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be any combination of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  PWM_Threshold
  * @param  Match
  * @retval None
  */
void PWM_SetPWMTHandMATCH(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t PWM_Threshold, uint32_t Match)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_SWITCH(Channel));
    
    /* PWMTH & MR */
    if (Channel == Timer_Channel_0)
    {
        TIMERx->MR0 = Match;
        TIMERx->PWMTH0 = PWM_Threshold;
    }
    else if (Channel == Timer_Channel_1)
    {
        TIMERx->MR1 = Match;
        TIMERx->PWMTH1 = PWM_Threshold;
    }
    else if (Channel == Timer_Channel_2)
    {
        TIMERx->MR2 = Match;
        TIMERx->PWMTH2 = PWM_Threshold;
    }
    else
    {
        TIMERx->MR3 = Match;
        TIMERx->PWMTH3 = PWM_Threshold;
    }
}

/**
  * @brief  Enables or disables PWM single inverted.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be any combination of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  NewState: new state of the TIMERx peripheral.
  *   This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void PWM_InvertCmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_TIMER_CHANNEL_SWITCH(Channel));
    
	if (NewState != DISABLE)
    {
        TIMERx->PWMC |= (Channel << PWM_INVERT_BIT_OFFSET);
    }
	else
    {
        TIMERx->PWMC &= ~(Channel << PWM_INVERT_BIT_OFFSET);
    }
}

/**
  * @brief  Set pulse counter value.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be one of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  Value: Count of pulse.
  *   This parameter can be: uint32_t.
  * @retval None
  */
void PWM_SetPulseCounterValue(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Value)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL_CONFIG(Channel));
    
    if (Channel == Timer_Channel_0)
    {
        TIMERx->PWMV0 = Value;
    }
    else if (Channel == Timer_Channel_1)
    {
        TIMERx->PWMV1 = Value;
    }
    else if (Channel == Timer_Channel_2)
    {
        TIMERx->PWMV2 = Value;
    }
    else
    {
        TIMERx->PWMV3 = Value;
    }
}

/**
  * @brief  Enables or disables PWM pulse counter.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be any combination of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  NewState: new state of the TIMERx peripheral.
  *   This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void PWM_PulseCounterCmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_TIMER_CHANNEL_SWITCH(Channel));

	if (NewState != DISABLE)
    {
        TIMERx->PWMC |= (Channel << PWM_PULSE_COUNTER_BIT_OFFSET);
    }
	else
    {
        TIMERx->PWMC &= ~(Channel << PWM_PULSE_COUNTER_BIT_OFFSET);
    }
}

/**
  * @brief  Enables or disables PWM.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_Channel: channel num of the TIMERx peripheral.
  *   This parameter can be any combination of the following values:
  *     @arg Timer_Channel_0.
  *     @arg Timer_Channel_1.
  *     @arg Timer_Channel_2.
  *     @arg Timer_Channel_3. 
  * @param  NewState: new state of the TIMERx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWM_Cmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_TIMER_CHANNEL_SWITCH(Channel));

	if (NewState != DISABLE)
    {
        TIMERx->TCR |= (Channel | Channel << 16);
    }
	else
    {
        TIMERx->TCR &= ~(Channel | Channel << 16);
    }
}

/**
  * @brief  Enables or disables the specified TIMER interrupts.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMERx peripheral.
  * @param  TIMER_IT: specifies the TIMER interrupts sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg TIMER_IT_MR0I.
  *     @arg TIMER_IT_MR1I.
  *     @arg TIMER_IT_MR2I.
  *     @arg TIMER_IT_MR3I.
  *     @arg TIMER_IT_PULSE_COUNTER0.
  *     @arg TIMER_IT_PULSE_COUNTER1.
  *     @arg TIMER_IT_PULSE_COUNTER2.
  *     @arg TIMER_IT_PULSE_COUNTER3.
  *     @arg TIMER_IT_CAP0.
  *     @arg TIMER_IT_CAP1.
  * @param  NewState: new state of the TIMER interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIMER_ITConfig(TIMER_TypeDef* TIMERx, uint32_t TIMER_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_IT(TIMER_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
        if ((TIMER_IT & TIMER_IT_CAP_FLAG) != 0)
        {
            TIMERx->CCR |= (TIMER_IT & (~TIMER_IT_CAP_FLAG));
        }
        else if ((TIMER_IT & TIMER_IT_PULSE_COUNTER_FLAG) != 0)
        {
            TIMERx->PWMC |= (TIMER_IT & (~TIMER_IT_PULSE_COUNTER_FLAG));
        }
        else
        {
            TIMERx->MCR |= TIMER_IT;
        }
	}
	else
	{
        if ((TIMER_IT & TIMER_IT_CAP_FLAG) != 0)
        {
            TIMERx->CCR &= ~(TIMER_IT & (~TIMER_IT_CAP_FLAG));
        }
        else if ((TIMER_IT & TIMER_IT_PULSE_COUNTER_FLAG) != 0)
        {
            TIMERx->PWMC &= ~(TIMER_IT & (~TIMER_IT_PULSE_COUNTER_FLAG));
        }
        else
        {
            TIMERx->MCR &= ~TIMER_IT;
        }
	}
}

/**
  * @brief  Checks whether the TIMER interrupt has occurred or not.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMER peripheral.
  * @param  TIMER_IT: specifies the TIMER interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg TIMER_IT_PENDING_MR0.
  *     @arg TIMER_IT_PENDING_MR1.
  *     @arg TIMER_IT_PENDING_MR2.
  *     @arg TIMER_IT_PENDING_MR3. 
  *     @arg TIMER_IT_PENDING_CR0.
  *     @arg TIMER_IT_PENDING_PULSE_COUNTER0.
  *     @arg TIMER_IT_PENDING_PULSE_COUNTER1.
  *     @arg TIMER_IT_PENDING_PULSE_COUNTER2.
  *     @arg TIMER_IT_PENDING_PULSE_COUNTER3.
  * @retval The new state of the TIMER_IT(SET or RESET).
  */
ITStatus TIMER_GetITStatus(TIMER_TypeDef* TIMERx, uint32_t TIMER_IT)
{
	ITStatus bitstatus = RESET, enablestatus = RESET;

	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_GET_IT(TIMER_IT));

    if (TIMER_IT == TIMER_IT_PENDING_CR0)
    {
        if ((TIMERx->CCR & TIMER_CCR_CAP0I) != RESET)
            enablestatus = SET;
    }
    else if (TIMER_IT == TIMER_IT_PENDING_CR1)
    {
        if ((TIMERx->CCR & TIMER_CCR_CAP1I) != RESET)
            enablestatus = SET;
    }
    else if (TIMER_IT == TIMER_IT_PENDING_MR0)
    {
        if ((TIMERx->MCR & TIMER_IT_MR0I) != RESET)
            enablestatus = SET;
    }
    else if (TIMER_IT == TIMER_IT_PENDING_MR1)
    {
        if ((TIMERx->MCR & TIMER_IT_MR1I) != RESET)
            enablestatus = SET;
    }
    else if (TIMER_IT == TIMER_IT_PENDING_MR2)
    {
        if ((TIMERx->MCR & TIMER_IT_MR2I) != RESET)
            enablestatus = SET;
    }
    else if (TIMER_IT == TIMER_IT_PENDING_MR3)
    {
        if ((TIMERx->MCR & TIMER_IT_MR3I) != RESET)
            enablestatus = SET;
    }
    else if (TIMER_IT == TIMER_IT_PENDING_PULSE_COUNTER0)
    {
        if ((TIMERx->PWMC & TIMER_PWMCR_PULSE_COUNTER0_INT) != RESET)
            enablestatus = SET;
    }
    else if (TIMER_IT == TIMER_IT_PENDING_PULSE_COUNTER1)
    {
        if ((TIMERx->PWMC & TIMER_PWMCR_PULSE_COUNTER1_INT) != RESET)
            enablestatus = SET;
    }
    else if (TIMER_IT == TIMER_IT_PENDING_PULSE_COUNTER2)
    {
        if ((TIMERx->PWMC & TIMER_PWMCR_PULSE_COUNTER2_INT) != RESET)
            enablestatus = SET;
    }
    else if (TIMER_IT == TIMER_IT_PENDING_PULSE_COUNTER3)
    {
        if ((TIMERx->PWMC & TIMER_PWMCR_PULSE_COUNTER3_INT) != RESET)
            enablestatus = SET;
    }

    if (((TIMERx->IR & TIMER_IT) != RESET) && (enablestatus == SET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

 	return bitstatus;
}

/**
  * @brief  Clears the TIMERx's interrupt pending bits.
  * @param  TIMERx: where x can be 0 to 3 to select the TIMER peripheral.
  * @param  TIMER_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg TIMER_IT_PENDING_MR0.
  *     @arg TIMER_IT_PENDING_MR1.
  *     @arg TIMER_IT_PENDING_MR2.
  *     @arg TIMER_IT_PENDING_MR3. 
  *     @arg TIMER_IT_PENDING_CR0.
  *     @arg TIMER_IT_PENDING_PULSE_COUNTER0.
  *     @arg TIMER_IT_PENDING_PULSE_COUNTER1.
  *     @arg TIMER_IT_PENDING_PULSE_COUNTER2.
  *     @arg TIMER_IT_PENDING_PULSE_COUNTER3.
  * @retval None
  */
void TIMER_ClearITPendingBit(TIMER_TypeDef* TIMERx, uint32_t TIMER_IT)
{
	/* Check the parameters */
	assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
	assert_param(IS_TIMER_CLEAR_IT(TIMER_IT));

	/* Clear the IT pending Bit */
	TIMERx->IR = TIMER_IT;
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
