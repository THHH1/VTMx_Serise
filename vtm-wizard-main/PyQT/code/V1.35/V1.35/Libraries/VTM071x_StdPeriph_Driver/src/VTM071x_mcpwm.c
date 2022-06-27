/**
  ******************************************************************************
  * @file    VTM071x_mcpwm.c
  * @author  MIC Software Team 
  * @version V0.0.0
  * @date    03/01/2018
  * @brief   This file provides all the PWM firmware functions.
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
#include "VTM071x_mcpwm.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup MCPWM 
  * @brief MCPWM driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MCPWM_CENTER_SHIFT          1
#define MCPWM_POLARITY_SHIFT        2
#define MCPWM_UPDATE_SHIFT          4
#define MCPWM_CON0_SHIFT            0
#define MCPWM_CON1_SHIFT            8
#define MCPWM_CON2_SHIFT            16
#define MCPWM_CAP_RST0_SHIFT        18
#define MCPWM_CAP_RST1_SHIFT        19
#define MCPWM_CAP_RST2_SHIFT        20
#define MCPWM_CAP_HNF0_SHIFT        21
#define MCPWM_CAP_HNF1_SHIFT        22
#define MCPWM_CAP_HNF2_SHIFT        23
#define MCPWM_CAP_SRC0_SHIFT        0
#define MCPWM_CAP_SRC1_SHIFT        6
#define MCPWM_CAP_SRC2_SHIFT        12
#define MCPWM_COUNTER_SRC0_SHIFT    0
#define MCPWM_COUNTER_SRC1_SHIFT    6
#define MCPWM_COUNTER_SRC2_SHIFT    12

#define MCPWM_INS_PSLA0_SHIFT       8
#define MCPWM_INS_PSLB0_SHIFT       9
#define MCPWM_INS_PSLA1_SHIFT       10
#define MCPWM_INS_PSLB1_SHIFT       11
#define MCPWM_INS_PSLA2_SHIFT       12
#define MCPWM_INS_PSLB2_SHIFT       13

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup MCPWM_Private_Functions
  * @{
  */

/**
  * @brief  Open MCPWM clock.
  * @param  NULL
  * @retval None
  */
void MCPWM_DeInit(void)
{ 
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL_MCPWM, ENABLE);
    
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL_MCPWM, DISABLE);
}

/**
  * @brief  Initializes the MCPWM peripheral according to the specified 
  *         parameters in the MCPWM_InitStruct.
  * @param  MCPWM_InitStruct: pointer to a MCPWM_InitTypeDef structure that
  *         contains the configuration information for the specified MCPWM peripheral.
  * @retval None
  */
void MCPWM_Init(MCPWM_InitTypeDef* MCPWM_InitStruct)
{
	/* Check the SPI parameters */
    assert_param(IS_MCPWM_DEADTIME(MCPWM_InitStruct->MCPWM_DeadTime));
    assert_param(IS_MCPWM_CENTER(MCPWM_InitStruct->MCPWM_Center));
    assert_param(IS_MCPWM_Polarity(MCPWM_InitStruct->MCPWM_Polarity));
    assert_param(IS_MCPWM_Update(MCPWM_InitStruct->MCPWM_Update));
    assert_param(IS_MCPWM_CHANNEL(MCPWM_InitStruct->MCPWM_Channel));

    if (MCPWM_InitStruct->MCPWM_Channel == MCPWM_CHANNEL_0)
    {
        MCPWM->MAT0 = MCPWM_InitStruct->MCPWM_Match;
        MCPWM->LIM0 = MCPWM_InitStruct->MCPWM_Limit;
        if (MCPWM_InitStruct->MCPWM_DeadTime == 0)
        {
            MCPWM->CON_CLR = MCPWM_CON_DTE0;
            MCPWM->DT &= ~MCPWM_DT_DT0;
        }
        else
        {
            MCPWM->CON_SET = MCPWM_CON_DTE0;
            MCPWM->DT &= ~MCPWM_DT_DT0;
            MCPWM->DT |= MCPWM_InitStruct->MCPWM_DeadTime;
        }

        MCPWM->CON_CLR = MCPWM_CON_CENTER0 | MCPWM_CON_POLA0 | MCPWM_CON_DISUP0;
        MCPWM->CON_SET = MCPWM_InitStruct->MCPWM_Center << (MCPWM_CENTER_SHIFT + MCPWM_CON0_SHIFT);
        MCPWM->CON_SET = MCPWM_InitStruct->MCPWM_Polarity << (MCPWM_POLARITY_SHIFT + MCPWM_CON0_SHIFT);
        MCPWM->CON_SET = MCPWM_InitStruct->MCPWM_Update << (MCPWM_UPDATE_SHIFT + MCPWM_CON0_SHIFT);
    }
    else if (MCPWM_InitStruct->MCPWM_Channel == MCPWM_CHANNEL_1)
    {
        MCPWM->MAT1 = MCPWM_InitStruct->MCPWM_Match;
        MCPWM->LIM1 = MCPWM_InitStruct->MCPWM_Limit;
        if (MCPWM_InitStruct->MCPWM_DeadTime == 0)
        {
            MCPWM->CON_CLR = MCPWM_CON_DTE1;
            MCPWM->DT &= ~MCPWM_DT_DT1;
        }
        else
        {
            MCPWM->CON_SET = MCPWM_CON_DTE1;
            MCPWM->DT &= ~MCPWM_DT_DT1;
            MCPWM->DT |= MCPWM_InitStruct->MCPWM_DeadTime << 10;
        }

        MCPWM->CON_CLR = MCPWM_CON_CENTER1 | MCPWM_CON_POLA1 | MCPWM_CON_DISUP1;
        MCPWM->CON_SET = MCPWM_InitStruct->MCPWM_Center << (MCPWM_CENTER_SHIFT + MCPWM_CON1_SHIFT);
        MCPWM->CON_SET = MCPWM_InitStruct->MCPWM_Polarity << (MCPWM_POLARITY_SHIFT + MCPWM_CON1_SHIFT);
        MCPWM->CON_SET = MCPWM_InitStruct->MCPWM_Update << (MCPWM_UPDATE_SHIFT + MCPWM_CON1_SHIFT);
    }
    else
    {
        MCPWM->MAT2 = MCPWM_InitStruct->MCPWM_Match;
        MCPWM->LIM2 = MCPWM_InitStruct->MCPWM_Limit;
        if (MCPWM_InitStruct->MCPWM_DeadTime == 0)
        {
            MCPWM->CON_CLR = MCPWM_CON_DTE2;
            MCPWM->DT &= ~MCPWM_DT_DT2;
        }
        else
        {
            MCPWM->CON_SET = MCPWM_CON_DTE2;
            MCPWM->DT &= ~MCPWM_DT_DT2;
            MCPWM->DT |= MCPWM_InitStruct->MCPWM_DeadTime << 20;
        }

        MCPWM->CON_CLR = MCPWM_CON_CENTER2 | MCPWM_CON_POLA2 | MCPWM_CON_DISUP2;
        MCPWM->CON_SET = MCPWM_InitStruct->MCPWM_Center << (MCPWM_CENTER_SHIFT + MCPWM_CON2_SHIFT);
        MCPWM->CON_SET = MCPWM_InitStruct->MCPWM_Polarity << (MCPWM_POLARITY_SHIFT + MCPWM_CON2_SHIFT);
        MCPWM->CON_SET = MCPWM_InitStruct->MCPWM_Update << (MCPWM_UPDATE_SHIFT + MCPWM_CON2_SHIFT);
    }
}

/**
  * @brief  Set prescale.
  * @param  Prescale: Prescale value.
  * @retval None
  */
void MCPWM_SetPrescale(uint32_t Prescale)
{
    MCPWM->PR = Prescale;
}

/**
  * @brief  Change MAT and LIM.
  * @param  MCPWM_Channel: MCPWM Channel.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_CHANNEL_0.
  *     @arg MCPWM_CHANNEL_1.
  *     @arg MCPWM_CHANNEL_2.
  *     @arg MCPWM_CHANNEL_0 | MCPWM_CHANNEL_1.
  *     @arg MCPWM_CHANNEL_0 | MCPWM_CHANNEL_2.
  *     @arg MCPWM_CHANNEL_1 | MCPWM_CHANNEL_2.
  *     @arg MCPWM_CHANNEL_0 | MCPWM_CHANNEL_1 | MCPWM_CHANNEL_2.
  * @param  MCPWM_MAT: Match value.
  * @param  MCPWM_LIM: Limit value.
  * @retval None
  */
void MCPWM_ChangeMATAndLIM(uint32_t MCPWM_Channel_COM, uint32_t MCPWM_MAT, uint32_t MCPWM_LIM)
{
	/* Check the parameters */
    assert_param(IS_MCPWM_CHANNEL_COM(MCPWM_Channel_COM));

    if (MCPWM_Channel_COM & MCPWM_CHANNEL_0)
    {
        MCPWM->MAT0 = MCPWM_MAT;
        MCPWM->LIM0 = MCPWM_LIM;
    }

    if (MCPWM_Channel_COM & MCPWM_CHANNEL_1)
    {
        MCPWM->MAT1 = MCPWM_MAT;
        MCPWM->LIM1 = MCPWM_LIM;
    }

    if (MCPWM_Channel_COM & MCPWM_CHANNEL_2)
    {
        MCPWM->MAT2 = MCPWM_MAT;
        MCPWM->LIM2 = MCPWM_LIM;
    }
}

/**
  * @brief  Enable or disable MCPWM.
  * @param  MCPWM_Channel: MCPWM Channel.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_CHANNEL_0.
  *     @arg MCPWM_CHANNEL_1.
  *     @arg MCPWM_CHANNEL_2.
  *     @arg MCPWM_CHANNEL_0 | MCPWM_CHANNEL_1.
  *     @arg MCPWM_CHANNEL_0 | MCPWM_CHANNEL_2.
  *     @arg MCPWM_CHANNEL_1 | MCPWM_CHANNEL_2.
  *     @arg MCPWM_CHANNEL_0 | MCPWM_CHANNEL_1 | MCPWM_CHANNEL_2.
  * @param  NewState: new state of DC mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCPWM_Cmd(uint32_t MCPWM_Channel_COM, FunctionalState NewState)
{
	/* Check the parameters */
    assert_param(IS_MCPWM_CHANNEL_COM(MCPWM_Channel_COM));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
    {
        MCPWM->CON_SET = MCPWM_Channel_COM;
    }
	else
    {
        MCPWM->CON_CLR = MCPWM_Channel_COM;
    }
}

/**
  * @brief  Configure the MCPWM DC mode.
  * @param  Invbdc: The direction of MCOA and MCOB.
  * @param  MCPWM_CPStruct: pointer to a MCPWM_CPTypeDef structure that
  *         contains the configuration information for the specified MCPWM peripheral.
  * @retval None
  */
void MCPWM_DCConfig(uint32_t Invbdc, MCPWM_CPTypeDef* MCPWM_CPStruct)
{
	uint32_t tmpreg = 0;

	/* Check the parameters */
    assert_param(IS_MCPWM_INVBDC(Invbdc));
	assert_param(IS_MCPWM_CPA0(MCPWM_CPStruct->MCPWM_CPA0));
	assert_param(IS_MCPWM_CPB0(MCPWM_CPStruct->MCPWM_CPB0));
	assert_param(IS_MCPWM_CPA1(MCPWM_CPStruct->MCPWM_CPA1));
	assert_param(IS_MCPWM_CPB1(MCPWM_CPStruct->MCPWM_CPB1));
	assert_param(IS_MCPWM_CPA2(MCPWM_CPStruct->MCPWM_CPA2));
	assert_param(IS_MCPWM_CPB2(MCPWM_CPStruct->MCPWM_CPB2));

    /* The direction of MCOA and MCOB */
    if (Invbdc == MCPWM_INVBDC_SAME)
        MCPWM->CON_CLR = MCPWM_INVBDC_OPPOSITE;
    else
        MCPWM->CON_SET = MCPWM_INVBDC_OPPOSITE;
    
    /* MCOA0,MCOB0,MCOA1,MCOB1,MCOA2,MCOB2 */
    tmpreg = 0;
    tmpreg |= MCPWM_CPStruct->MCPWM_CPA0;
    tmpreg |= MCPWM_CPStruct->MCPWM_CPB0;
    tmpreg |= MCPWM_CPStruct->MCPWM_CPA1;
    tmpreg |= MCPWM_CPStruct->MCPWM_CPB1;
    tmpreg |= MCPWM_CPStruct->MCPWM_CPA2;
    tmpreg |= MCPWM_CPStruct->MCPWM_CPB2;
    MCPWM->CCP = tmpreg;
}

/**
  * @brief  Configure inactive status.
  * @param  MCPWM_CPINSStruct: pointer to a MCPWM_CPINSTypeDef structure that
  *         contains the configuration information for the specified MCPWM peripheral.
  * @retval None
  */
void MCPWM_INSConfig(MCPWM_CPINSTypeDef* MCPWM_CPINSStruct)
{
    uint32_t tmpreg = 0;
    
	/* Check the parameters */
    assert_param(IS_MCPWM_INS(MCPWM_CPINSStruct->MCPWM_CPA0_INS));
    assert_param(IS_MCPWM_INS(MCPWM_CPINSStruct->MCPWM_CPB0_INS));
    assert_param(IS_MCPWM_INS(MCPWM_CPINSStruct->MCPWM_CPA1_INS));
    assert_param(IS_MCPWM_INS(MCPWM_CPINSStruct->MCPWM_CPB1_INS));
    assert_param(IS_MCPWM_INS(MCPWM_CPINSStruct->MCPWM_CPA2_INS));
    assert_param(IS_MCPWM_INS(MCPWM_CPINSStruct->MCPWM_CPB2_INS));

    tmpreg = MCPWM->HALL;
    tmpreg &= ~MCPWM_HALL_INS_MASK;
    tmpreg |= MCPWM_CPINSStruct->MCPWM_CPA0_INS << MCPWM_INS_PSLA0_SHIFT;
    tmpreg |= MCPWM_CPINSStruct->MCPWM_CPB0_INS << MCPWM_INS_PSLB0_SHIFT;
    tmpreg |= MCPWM_CPINSStruct->MCPWM_CPA1_INS << MCPWM_INS_PSLA1_SHIFT;
    tmpreg |= MCPWM_CPINSStruct->MCPWM_CPB1_INS << MCPWM_INS_PSLB1_SHIFT;
    tmpreg |= MCPWM_CPINSStruct->MCPWM_CPA2_INS << MCPWM_INS_PSLA2_SHIFT;
    tmpreg |= MCPWM_CPINSStruct->MCPWM_CPB2_INS << MCPWM_INS_PSLB2_SHIFT;
    MCPWM->HALL = tmpreg;
}

/**
  * @brief  Enable or disable DC mode.
  * @param  NewState: new state of DC mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCPWM_DCCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
    {
        MCPWM->CON_SET = MCPWM_CON_DCMODE;
    }
	else
    {
        MCPWM->CON_CLR = MCPWM_CON_DCMODE;
    }
}

/**
  * @brief  Enable or disable AC mode.
  * @param  NewState: new state of AC mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCPWM_ACCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
    {
        MCPWM->CON_SET = MCPWM_CON_ACMODE;
    }
	else
    {
        MCPWM->CON_CLR = MCPWM_CON_ACMODE;
    }
}

/**
  * @brief  Configure capture.
  * @param  MCPWM_CPStruct: pointer to a MCPWM_CapStruct structure that
  *         contains the configuration information for the specified MCPWM peripheral.
  * @retval None
  */
void MCPWM_CaptureConfig(MCPWM_CapTypeDef* MCPWM_CapStruct)
{    
	/* Check the parameters */
    assert_param(IS_MCPWM_CAPTURE_RST_TC(MCPWM_CapStruct->MCPWM_CaptureRstTC));
    assert_param(IS_MCPWM_CAPTURE_SOURCE(MCPWM_CapStruct->MCPWM_CaptureSource));
    assert_param(IS_MCPWM_Capture_Noise_Filter(MCPWM_CapStruct->MCPWM_CaptureNoiseFilter));
    assert_param(IS_MCPWM_CHANNEL(MCPWM_CapStruct->MCPWM_Channel));

    if (MCPWM_CapStruct->MCPWM_Channel == MCPWM_CHANNEL_0)
    {
        if (MCPWM_CapStruct->MCPWM_CaptureRstTC)
            MCPWM->CAPCON_SET = MCPWM_RST_TC_DIS << MCPWM_CAP_RST0_SHIFT;
        else
            MCPWM->CAPCON_CLR = MCPWM_RST_TC_DIS << MCPWM_CAP_RST0_SHIFT;

        if (MCPWM_CapStruct->MCPWM_CaptureNoiseFilter)
            MCPWM->CAPCON_SET = MCPWM_NOISE_FILTER_DIS << MCPWM_CAP_HNF0_SHIFT;
        else
            MCPWM->CAPCON_CLR = MCPWM_NOISE_FILTER_DIS << MCPWM_CAP_HNF0_SHIFT;

        MCPWM->CAPCON_CLR = MCPWM_CAPCON_C0_SOURCE;
        MCPWM->CAPCON_SET = MCPWM_CapStruct->MCPWM_CaptureSource << MCPWM_CAP_SRC0_SHIFT;
    }
    else if (MCPWM_CapStruct->MCPWM_Channel == MCPWM_CHANNEL_1)
    {
        if (MCPWM_CapStruct->MCPWM_CaptureRstTC)
            MCPWM->CAPCON_SET = MCPWM_RST_TC_DIS << MCPWM_CAP_RST1_SHIFT;
        else
            MCPWM->CAPCON_CLR = MCPWM_RST_TC_DIS << MCPWM_CAP_RST1_SHIFT;

        if (MCPWM_CapStruct->MCPWM_CaptureNoiseFilter)
            MCPWM->CAPCON_SET = MCPWM_NOISE_FILTER_DIS << MCPWM_CAP_HNF1_SHIFT;
        else
            MCPWM->CAPCON_CLR = MCPWM_NOISE_FILTER_DIS << MCPWM_CAP_HNF1_SHIFT;

        MCPWM->CAPCON_CLR = MCPWM_CAPCON_C1_SOURCE;
        MCPWM->CAPCON_SET = MCPWM_CapStruct->MCPWM_CaptureSource << MCPWM_CAP_SRC1_SHIFT;
    }
    else
    {
        if (MCPWM_CapStruct->MCPWM_CaptureRstTC)
            MCPWM->CAPCON_SET = MCPWM_RST_TC_DIS << MCPWM_CAP_RST2_SHIFT;
        else
            MCPWM->CAPCON_CLR = MCPWM_RST_TC_DIS << MCPWM_CAP_RST2_SHIFT;

        if (MCPWM_CapStruct->MCPWM_CaptureNoiseFilter)
            MCPWM->CAPCON_SET = MCPWM_NOISE_FILTER_DIS << MCPWM_CAP_HNF2_SHIFT;
        else
            MCPWM->CAPCON_CLR = MCPWM_NOISE_FILTER_DIS << MCPWM_CAP_HNF2_SHIFT;

        MCPWM->CAPCON_CLR = MCPWM_CAPCON_C2_SOURCE;
        MCPWM->CAPCON_SET = MCPWM_CapStruct->MCPWM_CaptureSource << MCPWM_CAP_SRC2_SHIFT;
    }
}

/**
  * @brief  Timer or Counter.
  * @param  NewState: new state of MCPWM.
  *   This parameter can be: ENABLE or DISABLE.
  * @param  MCPWM_Channel: MCPWM Channel.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_CHANNEL_0.
  *     @arg MCPWM_CHANNEL_1.
  *     @arg MCPWM_CHANNEL_2.
  * @retval None
  */
void MCPWM_TimerorCounter(uint32_t TOC, uint32_t MCPWM_Channel)
{
	/* Check the parameters */
	assert_param(IS_MCPWM_TOC(TOC));
    assert_param(IS_MCPWM_CHANNEL(MCPWM_Channel));

    if (MCPWM_Channel == MCPWM_CHANNEL_0)
    {
        if (TOC == MCPWM_TIMER)
            MCPWM->CNTCON_CLR = MCPWM_CNTCON_CNTR0;
        else
            MCPWM->CNTCON_SET = MCPWM_CNTCON_CNTR0;
    }
    else if (MCPWM_Channel == MCPWM_CHANNEL_1)
    {
        if (TOC == MCPWM_TIMER)
            MCPWM->CNTCON_CLR = MCPWM_CNTCON_CNTR1;
        else
            MCPWM->CNTCON_SET = MCPWM_CNTCON_CNTR1;
    }
    else
    {
        if (TOC == MCPWM_TIMER)
            MCPWM->CNTCON_CLR = MCPWM_CNTCON_CNTR2;
        else
            MCPWM->CNTCON_SET = MCPWM_CNTCON_CNTR2;
    }
}

/**
  * @brief  Configure Counter.
  * @param  ConterSource: Counter source.
  *   This parameter can be the following values:
  *     @arg MCPWM_COUNTER_SOURCE_MCI0_RE.
  *     @arg MCPWM_COUNTER_SOURCE_MCI0_FE.
  *     @arg MCPWM_COUNTER_SOURCE_MCI1_RE.
  *     @arg MCPWM_COUNTER_SOURCE_MCI1_FE.
  *     @arg MCPWM_COUNTER_SOURCE_MCI2_RE.
  *     @arg MCPWM_COUNTER_SOURCE_MCI2_FE.
  * @param  MCPWM_Channel: MCPWM Channel.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_CHANNEL_0.
  *     @arg MCPWM_CHANNEL_1.
  *     @arg MCPWM_CHANNEL_2.
  * @retval None
  */
void MCPWM_CounterConfig(uint32_t ConterSource, uint32_t MCPWM_Channel)
{
	/* Check the parameters */
	assert_param(IS_MCPWM_COUNTER_SOURCE(ConterSource));
    assert_param(IS_MCPWM_CHANNEL(MCPWM_Channel));

    if (MCPWM_Channel == MCPWM_CHANNEL_0)
    {
        MCPWM->CNTCON_CLR = MCPWM_CNTCON_TC0_SOURCE;
        MCPWM->CNTCON_SET = ConterSource << MCPWM_COUNTER_SRC0_SHIFT;
    }
    else if (MCPWM_Channel == MCPWM_CHANNEL_1)
    {
        MCPWM->CNTCON_CLR = MCPWM_CNTCON_TC1_SOURCE;
        MCPWM->CNTCON_SET = ConterSource << MCPWM_COUNTER_SRC1_SHIFT;
    }
    else
    {
        MCPWM->CNTCON_CLR = MCPWM_CNTCON_TC2_SOURCE;
        MCPWM->CNTCON_SET = ConterSource << MCPWM_COUNTER_SRC2_SHIFT;
    }
}

/**
  * @brief  Get CR register.
  * @param  MCPWM_Channel: MCPWM Channel.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_CHANNEL_0.
  *     @arg MCPWM_CHANNEL_1.
  *     @arg MCPWM_CHANNEL_2.
  * @retval CR register value.
  */
uint32_t MCPWM_GetCAP(uint32_t MCPWM_Channel)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
    assert_param(IS_MCPWM_CHANNEL(MCPWM_Channel));

    if (MCPWM_Channel == MCPWM_CHANNEL_0)
        tmpreg = MCPWM->CAP0;
    else if (MCPWM_Channel == MCPWM_CHANNEL_1)
        tmpreg = MCPWM->CAP1;
    else
        tmpreg = MCPWM->CAP2;

    return tmpreg;
}

/**
  * @brief  Clear CR register.
  * @param  MCPWM_Channel: MCPWM Channel.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_CHANNEL_0.
  *     @arg MCPWM_CHANNEL_1.
  *     @arg MCPWM_CHANNEL_2.
  * @retval None.
  */
void MCPWM_ClearCAP(uint32_t MCPWM_Channel)
{
	/* Check the parameters */
    assert_param(IS_MCPWM_CHANNEL(MCPWM_Channel));

    if (MCPWM_Channel == MCPWM_CHANNEL_0)
        MCPWM->CAP_CLR |= MCPWM_CAPCLR_CLR0;
    else if (MCPWM_Channel == MCPWM_CHANNEL_1)
        MCPWM->CAP_CLR |= MCPWM_CAPCLR_CLR1;
    else
        MCPWM->CAP_CLR |= MCPWM_CAPCLR_CLR2;
}

/**
  * @brief  Configure HALL.
  * @param  CurrentStatus: HALL current status.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_HALL_CUR_STAT_1.
  *     @arg MCPWM_HALL_CUR_STAT_2.
  *     @arg MCPWM_HALL_CUR_STAT_3.
  *     @arg MCPWM_HALL_CUR_STAT_4.
  *     @arg MCPWM_HALL_CUR_STAT_5.
  *     @arg MCPWM_HALL_CUR_STAT_6.
  * @param  Currentstatus: HALL expected status.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_HALL_EXP_STAT_1.
  *     @arg MCPWM_HALL_EXP_STAT_2.
  *     @arg MCPWM_HALL_EXP_STAT_3.
  *     @arg MCPWM_HALL_EXP_STAT_4.
  *     @arg MCPWM_HALL_EXP_STAT_5.
  *     @arg MCPWM_HALL_EXP_STAT_6.
  * @retval None.
  */
void MCPWM_HALLStatusConfig(uint32_t CurrentStatus, uint32_t ExpectedStatus)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
    assert_param(IS_MCPWM_HALL_CUR_STAT(CurrentStatus));
    assert_param(IS_MCPWM_HALL_EXP_STAT(ExpectedStatus));

    tmpreg = MCPWM->HALL;
    tmpreg &= ~MCPWM_HALL_CURH;
    tmpreg &= ~MCPWM_HALL_EXPH;

    tmpreg |= CurrentStatus;
    tmpreg |= ExpectedStatus;
    MCPWM->HALL = tmpreg;
}

/**
  * @brief  Configure the MCPWM HALL polarity.
  * @param  MCPWM_CPStruct: pointer to a MCPWM_CPTypeDef structure that
  *         contains the configuration information for the specified MCPWM peripheral.
  * @retval None
  */
void MCPWM_HALLPolarityConfig(MCPWM_CPTypeDef* MCPWM_HALLCPStruct)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_MCPWM_HALLA0(MCPWM_HALLCPStruct->MCPWM_CPA0));
	assert_param(IS_MCPWM_HALLB0(MCPWM_HALLCPStruct->MCPWM_CPB0));
	assert_param(IS_MCPWM_HALLA1(MCPWM_HALLCPStruct->MCPWM_CPA1));
	assert_param(IS_MCPWM_HALLB1(MCPWM_HALLCPStruct->MCPWM_CPB1));
	assert_param(IS_MCPWM_HALLA2(MCPWM_HALLCPStruct->MCPWM_CPA2));
	assert_param(IS_MCPWM_HALLB2(MCPWM_HALLCPStruct->MCPWM_CPB2));

    tmpreg = MCPWM->HALL;
    tmpreg &= ~MCPWM_HALL_MCP_MASK;
    tmpreg |= MCPWM_HALLCPStruct->MCPWM_CPA0;
    tmpreg |= MCPWM_HALLCPStruct->MCPWM_CPB0;
    tmpreg |= MCPWM_HALLCPStruct->MCPWM_CPA1;
    tmpreg |= MCPWM_HALLCPStruct->MCPWM_CPB1;
    tmpreg |= MCPWM_HALLCPStruct->MCPWM_CPA2;
    tmpreg |= MCPWM_HALLCPStruct->MCPWM_CPB2;
    MCPWM->HALL = tmpreg;
}

/**
  * @brief  Enable or disable HALL.
  * @param  NewState: new state of HALL.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCPWM_HALLCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
    {
        MCPWM->CON_SET = MCPWM_CON_HALL;
    }
	else
    {
        MCPWM->CON_CLR = MCPWM_CON_HALL;
    }
}

/**
  * @brief  Get HALL status.
  * @param  None.
  * @retval HALL status.
  */
uint32_t MCPWM_GetHALLStat(void)
{
    return (MCPWM->HALL_VEL_MCIST & MCPWM_MCIST);
}

/**
  * @brief  Configure Velocity detect.
  * @param  Velocity: Velocity.
  * @param  Offset: Offset of velocity threshold.
  * @retval None.
  */
void MCPWM_VelocityDetectConfig(uint32_t Velocity, uint32_t Offset)
{
    MCPWM->HALL_VEL_CMP = Velocity;
    MCPWM->HALL_VEL_TH = Offset;
}

/**
  * @brief  Enable or disable velocity detection.
  * @param  NewState: new state of velocity detection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCPWM_VelocityDetectCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
    {
        MCPWM->CON_SET = MCPWM_CON_VEL;
    }
	else
    {
        MCPWM->CON_CLR = MCPWM_CON_VEL;
    }
}

/**
  * @brief  Get velocity value.
  * @param  None.
  * @retval Velocity.
  */
uint32_t MCPWM_GetVelocity(void)
{
    return MCPWM->HALL_VEL_VAL;
}

/**
  * @brief  Enables or disables the specified MCPWM interrupts.
  * @param  MCPWM_IT: specifies the MCPWM interrupts sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_IT_ILIM0.
  *     @arg MCPWM_IT_IMAT0.
  *     @arg MCPWM_IT_ICAP0.
  *     @arg MCPWM_IT_ILIM1.
  *     @arg MCPWM_IT_IMAT1.
  *     @arg MCPWM_IT_ICAP1.
  *     @arg MCPWM_IT_ILIM2.
  *     @arg MCPWM_IT_IMAT2.
  *     @arg MCPWM_IT_ICAP2.
  *     @arg MCPWM_IT_ABORT.
  *     @arg MCPWM_IT_STCHG.
  *     @arg MCPWM_IT_STERR.
  *     @arg MCPWM_IT_VSLOW.
  *     @arg MCPWM_IT_VFAST.
  *     @arg MCPWM_IT_MATR0.
  *     @arg MCPWM_IT_MATF0.
  *     @arg MCPWM_IT_CTZERO0.
  *     @arg MCPWM_IT_MATR1.
  *     @arg MCPWM_IT_MATF1.
  *     @arg MCPWM_IT_CTZERO1.
  *     @arg MCPWM_IT_MATR2.
  *     @arg MCPWM_IT_MATF2.
  *     @arg MCPWM_IT_CTZERO2.
  * @param  NewState: new state of the TIMER interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCPWM_ITConfig(uint32_t MCPWM_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_MCPWM_IT(MCPWM_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
        MCPWM->INTEN_SET = MCPWM_IT;
	}
	else
	{
        MCPWM->INTEN_CLR = MCPWM_IT;
	}
}

/**
  * @brief  Checks whether the MCPWM interrupt has occurred or not.
  * @param  MCPWM_IT: specifies the MCPWM interrupts sources to check.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_IT_ILIM0.
  *     @arg MCPWM_IT_IMAT0.
  *     @arg MCPWM_IT_ICAP0.
  *     @arg MCPWM_IT_ILIM1.
  *     @arg MCPWM_IT_IMAT1.
  *     @arg MCPWM_IT_ICAP1.
  *     @arg MCPWM_IT_ILIM2.
  *     @arg MCPWM_IT_IMAT2.
  *     @arg MCPWM_IT_ICAP2.
  *     @arg MCPWM_IT_ABORT.
  *     @arg MCPWM_IT_STCHG.
  *     @arg MCPWM_IT_STERR.
  *     @arg MCPWM_IT_VSLOW.
  *     @arg MCPWM_IT_VFAST.
  *     @arg MCPWM_IT_MATR0.
  *     @arg MCPWM_IT_MATF0.
  *     @arg MCPWM_IT_CTZERO0.
  *     @arg MCPWM_IT_MATR1.
  *     @arg MCPWM_IT_MATF1.
  *     @arg MCPWM_IT_CTZERO1.
  *     @arg MCPWM_IT_MATR2.
  *     @arg MCPWM_IT_MATF2.
  *     @arg MCPWM_IT_CTZERO2.
  * @param  NewState: new state of the TIMER interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
ITStatus MCPWM_GetITStatus(uint32_t MCPWM_IT)
{
	ITStatus bitstatus = RESET, enablestatus = RESET;

	/* Check the parameters */
	assert_param(IS_Get_MCPWM_IT(MCPWM_IT));
    
    if ((MCPWM->INTEN & MCPWM_IT) != RESET)
        enablestatus = SET;

    if (((MCPWM->INTF & MCPWM_IT) != RESET) && (enablestatus == SET))
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
  * @brief  Clears the MCWPM's interrupt pending bits.
  * @param  MCPWM_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be one of the following values:
  *     @arg MCPWM_IT_ILIM0.
  *     @arg MCPWM_IT_IMAT0.
  *     @arg MCPWM_IT_ICAP0.
  *     @arg MCPWM_IT_ILIM1.
  *     @arg MCPWM_IT_IMAT1.
  *     @arg MCPWM_IT_ICAP1.
  *     @arg MCPWM_IT_ILIM2.
  *     @arg MCPWM_IT_IMAT2.
  *     @arg MCPWM_IT_ICAP2.
  *     @arg MCPWM_IT_ABORT.
  *     @arg MCPWM_IT_STCHG.
  *     @arg MCPWM_IT_STERR.
  *     @arg MCPWM_IT_VSLOW.
  *     @arg MCPWM_IT_VFAST.
  *     @arg MCPWM_IT_MATR0.
  *     @arg MCPWM_IT_MATF0.
  *     @arg MCPWM_IT_CTZERO0.
  *     @arg MCPWM_IT_MATR1.
  *     @arg MCPWM_IT_MATF1.
  *     @arg MCPWM_IT_CTZERO1.
  *     @arg MCPWM_IT_MATR2.
  *     @arg MCPWM_IT_MATF2.
  *     @arg MCPWM_IT_CTZERO2.
  * @retval None
  */
void MCPWM_ClearITPendingBit(uint32_t MCPWM_IT)
{
	/* Check the parameters */
	assert_param(IS_Clear_MCPWM_IT(MCPWM_IT));

	/* Clear the IT pending Bit */
	MCPWM->INTF_CLR = MCPWM_IT;
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
