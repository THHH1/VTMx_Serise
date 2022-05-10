/**
  ******************************************************************************
  * @file    VTM071x_adc.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC) peripheral:
  *           + Initialization and Configuration
  *           + Power saving
  *           + Analog Watchdog configuration
  *           + Temperature Sensormanagement 
  *           + ADC Channels Configuration
  *           + Interrupts and flags management
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
#include "VTM071x_adc.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC 
  * @brief ADC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ADC CFGR mask */
#define	CFGR1_CLEAR_MASK			((uint32_t)0x7FFFD003)
#define	CFGR2_CLEAR_MASK			((uint32_t)0x3FFFFFFF)
#define	ACR_CLEAR_MASK				((uint32_t)0xFFFFFFCC)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ADC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes ADC peripheral registers to their default reset values.
  * @retval None
  */
void ADC_DeInit(void)
{
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL_ADC, ENABLE);
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL_ADC, DISABLE);
}

/**
  * @brief  Initializes the ADC peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC ( 
  *         Resolution, Data Alignment, continuous mode activation, External 
  *         trigger source and edge, Sequence Scan Direction, Discard, Clock Mode).   
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains 
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ADC_RESOLUTION(ADC_InitStruct->ADC_Resolution));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
    assert_param(IS_ADC_EXT_TRIG_EDGE(ADC_InitStruct->ADC_ExternalTrigConvEdge));
    assert_param(IS_ADC_EXTERNAL_TRIG_CONV(ADC_InitStruct->ADC_ExternalTrigConv));
    assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
    assert_param(IS_ADC_SCAN_DIRECTION(ADC_InitStruct->ADC_ScanDirection)); 
    assert_param(IS_ADC_DISCARD0(ADC_InitStruct->ADC_Discard0)); 
    assert_param(IS_ADC_DISCARD1(ADC_InitStruct->ADC_Discard1)); 
    assert_param(IS_ADC_CLOCKMODE(ADC_InitStruct->ADC_CLKMode)); 

    /* Get the ADC CFGR1 value */
    tmpreg = ADC->CFGR1;

    /* Clear SCANDIR, RES[1:0], ALIGN, EXTSEL[3:0], EXTEN[1:0] , ASYNC_TRG and CONT bits */
    tmpreg &= CFGR1_CLEAR_MASK;

    tmpreg  |= (uint32_t)(ADC_InitStruct->ADC_Resolution | (uint32_t)(ADC_InitStruct->ADC_ContinuousConvMode << 13) |
         ADC_InitStruct->ADC_ExternalTrigConvEdge | ADC_InitStruct->ADC_ExternalTrigConv |
         ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ScanDirection);

    /* Write to ADC CFGR1 */
    ADC->CFGR1 = tmpreg;

    /* Get the ADC CFGR2 value */
    tmpreg = ADC->CFGR2;

    tmpreg &= CFGR2_CLEAR_MASK;

    tmpreg |= ADC_InitStruct->ADC_CLKMode;

    ADC->CFGR2 = tmpreg;

    /* Get the ADC ACR value */
    tmpreg = ADC->ACR0;

    tmpreg &= ACR_CLEAR_MASK;

    tmpreg |= ADC_InitStruct->ADC_Discard0 | ADC_InitStruct->ADC_Discard1;

    ADC->ACR0 = tmpreg;
    
//    ADC->ACR1 = FLASH->ID3;
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @note   This function is used to initialize the global features of the ADC ( 
  *         Resolution, Data Alignment, continuous mode activation, External 
  *         trigger source and edge, Sequence Scan Direction, Discard, Clock Mode).
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
    /* Reset ADC init structure parameters values */
    /* Initialize the ADC_Resolution member */
    ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;

    /* Initialize the ADC_ContinuousConvMode member */
    ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;

    /* Initialize the ADC_ExternalTrigConvEdge member */
    ADC_InitStruct->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;

    /* Initialize the ADC_ExternalTrigConv member */
    ADC_InitStruct->ADC_ExternalTrigConv = 0;

    /* Initialize the ADC_DataAlign member */
    ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;

    /* Initialize the ADC_ScanDirection member */
    ADC_InitStruct->ADC_ScanDirection = ADC_ScanDirection_Upward;

    /* Initialize the ADC_Discard0 member */
    ADC_InitStruct->ADC_Discard0 = ADC_Discard0_0;

    /* Initialize the ADC_Discard1 member */
    ADC_InitStruct->ADC_Discard1 = ADC_Discard1_0;

    /* Initialize the ADC_CLKMode member */
    ADC_InitStruct->ADC_CLKMode = ADC_ClockMode_ADCClk;
}

/**
  * @brief  Start Conversion.
  * @note   In continuous mode, ADSTART is not cleared by hardware with the 
  *         assertion of EOSEQ because the sequence is automatic relaunched
  * @retval None
  */
void ADC_StartOfConversion(void)
{
    ADC->CR |= ADC_CR_ADSTART;
}

/**
  * @brief  Stop conversions.
  * @retval None
  */
void ADC_StopOfConversion(void)
{
    ADC->CR &= ~ADC_CR_ADSTART;
}

/**
  * @brief  Configure the ADC to either be clocked by the asynchronous clock
  *         or the synchronous clock derived from
  *         the APB clock of the ADC bus interface divided by 2 or 4
  * @note   This function can be called only when ADC is disabled.
  * @param  ADC_ClockMode: This parameter can be :
  *            @arg ADC_ClockMode_ADCClk: ADC clocked by the adc clock
  *            @arg ADC_ClockMode_SynClkDiv2: ADC clocked by HCLK/2
  *            @arg ADC_ClockMode_SynClkDiv4: ADC clocked by HCLK/4  
  * @retval None
  */
void ADC_ClockModeConfig(uint32_t ADC_ClockMode)
{
    /* Check the parameters */
    assert_param(IS_ADC_CLOCKMODE(ADC_ClockMode));

    /* Configure the ADC Clock mode according to ADC_ClockMode */
    ADC->CFGR2 = ADC_ClockMode;
}

/**
  * @brief  Enables or disables the Wait conversion mode.
  * @note   When the CPU clock is not fast enough to manage the data rate, a 
  *         Hardware delay can be introduced between ADC conversions to reduce 
  *         this data rate. 
  * @note   The Hardware delay is inserted after each conversions and until the
  *         previous data is read from the ADC data register
  * @note   This is a way to automatically adapt the speed of the ADC to the speed 
  *         of the system which will read the data.
  * @note   Any hardware triggers wich occur while a conversion is on going or 
  *         while the automatic Delay is applied are ignored 
  * @param  NewState: new state of the ADCx Auto-Delay.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_WaitModeCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the ADC Automatic Delayed conversion */
        ADC->CFGR1 |= ADC_CFGR1_WAIT;
    }
    else
    {
        /* Disable the ADC Automatic Delayed conversion */
        ADC->CFGR1 &= ~ADC_CFGR1_WAIT;
    }
}

/** @defgroup ADC_Group3 Analog Watchdog configuration functions
 *  @brief   Analog Watchdog configuration functions 
 *
@verbatim
 ===============================================================================
                   ##### Analog Watchdog configuration functions #####
 ===============================================================================  
    [..] This section provides functions allowing to configure the Analog Watchdog
         (AWD) feature in the ADC.
    [..] A typical configuration Analog Watchdog is done following these steps :
         (#) the ADC guarded channel(s) is (are) selected using the 
             ADC_AnalogWatchdogSingleChannelConfig() function.
         (#) The Analog watchdog lower and higher threshold are configured using the  
             ADC_AnalogWatchdogThresholdsConfig() function.
         (#) The Analog watchdog is enabled and configured to enable the check, on one
             or more channels, using the  ADC_AnalogWatchdogCmd() function.
         (#) Enable the analog watchdog on the selected channel using
             ADC_AnalogWatchdogSingleChannelCmd() function

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the analog watchdog 
  * @param  NewState: new state of the ADC Analog Watchdog.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AnalogWatchdogCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the ADC Analog Watchdog */
        ADC->CFGR1 |= ADC_CFGR1_AWDEN;
    }
    else
    {
        /* Disable the ADC Analog Watchdog */
        ADC->CFGR1 &= (uint32_t)~ADC_CFGR1_AWDEN;
    }
}

/**
  * @brief  Configures the high and low thresholds of the analog watchdog. 
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *          This parameter must be a 12bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *          This parameter must be a 12bit value.
  * @retval None
  */
void ADC_AnalogWatchdogThresholdsConfig(uint16_t HighThreshold,
                                        uint16_t LowThreshold)
{
    /* Check the parameters */
    assert_param(IS_ADC_THRESHOLD(HighThreshold));
    assert_param(IS_ADC_THRESHOLD(LowThreshold));

    /* Set the ADC high and low threshold */
    ADC->TR = LowThreshold | ((uint32_t)HighThreshold << 16);
}

/**
  * @brief  Configures the analog watchdog guarded single channel
  * @param  ADC_AnalogWatchdog_Channel: the ADC channel to configure for the analog watchdog.
  *          This parameter can be one of the following values:
  *            @arg ADC_AnalogWatchdog_Channel_0: ADC Channel0 selected
  *            @arg ADC_AnalogWatchdog_Channel_1: ADC Channel1 selected
  *            @arg ADC_AnalogWatchdog_Channel_2: ADC Channel2 selected
  *            @arg ADC_AnalogWatchdog_Channel_3: ADC Channel3 selected
  *            @arg ADC_AnalogWatchdog_Channel_4: ADC Channel4 selected
  *            @arg ADC_AnalogWatchdog_Channel_5: ADC Channel5 selected
  *            @arg ADC_AnalogWatchdog_Channel_6: ADC Channel6 selected
  *            @arg ADC_AnalogWatchdog_Channel_7: ADC Channel7 selected
  *            @arg ADC_AnalogWatchdog_Channel_8: ADC Channel8 selected
  *            @arg ADC_AnalogWatchdog_Channel_9: ADC Channel9 selected
  *            @arg ADC_AnalogWatchdog_Channel_10: ADC Channel10 selected
  *            @arg ADC_AnalogWatchdog_Channel_11: ADC Channel11 selected
  *            @arg ADC_AnalogWatchdog_Channel_12: ADC Channel12 selected
  *            @arg ADC_AnalogWatchdog_Channel_13: ADC Channel13 selected
  *            @arg ADC_AnalogWatchdog_Channel_14: ADC Channel14 selected
  *            @arg ADC_AnalogWatchdog_Channel_15: ADC Channel15 selected
  *            @arg ADC_AnalogWatchdog_Channel_16: ADC Channel16 selected
  *            @arg ADC_AnalogWatchdog_Channel_17: ADC Channel17 selected
  *            @arg ADC_AnalogWatchdog_Channel_18: ADC Channel18 selected
  * @note   The channel selected on the AWDCH must be also set into the CHSELR 
  *         register 
  * @retval None
  */
void ADC_AnalogWatchdogSingleChannelConfig(uint32_t ADC_AnalogWatchdog_Channel)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ADC_ANALOG_WATCHDOG_CHANNEL(ADC_AnalogWatchdog_Channel));

    /* Get the old register value */
    tmpreg = ADC->CFGR1;

    /* Clear the Analog watchdog channel select bits */
    tmpreg &= ~ADC_CFGR1_AWDCH_MASK;

    /* Set the Analog watchdog channel */
    tmpreg |= ADC_AnalogWatchdog_Channel;

    /* Store the new register value */
    ADC->CFGR1 = tmpreg;
}

/**
  * @brief  Enables or disables the ADC Analog Watchdog Single Channel.
  * @param  NewState: new state of the ADC Analog Watchdog Single Channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AnalogWatchdogSingleChannelCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
      /* Enable the ADC Analog Watchdog Single Channel */
      ADC->CFGR1 |= ADC_CFGR1_AWDSGL;
    }
    else
    {
      /* Disable the ADC Analog Watchdog Single Channel */
      ADC->CFGR1 &= (uint32_t)~ADC_CFGR1_AWDSGL;
    }
}

/**
  * @}
  */

/**
  * @brief  Enables or disables the temperature sensor channel.
  * @param  NewState: new state of the temperature sensor input channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_TempSensorCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
      /* Enable the temperature sensor channel*/
      ADC->CCR |= (uint32_t)ADC_CCR_TSEN;
    }
    else
    {
      /* Disable the temperature sensor channel*/
      ADC->CCR &= (uint32_t)(~ADC_CCR_TSEN);
    }
}

/**
  * @brief  Select ADC VREF.
  * @param  ADC_Vref: specifies the ADC VREF.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_EOC: End of conversion interrupt 
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
  * @retval None
  */
void ADC_VrefConfig(uint32_t ADC_Vref)
{
    uint32_t tmp_reg;
    
    /* Check the parameters */
    assert_param(IS_ADC_VREF_SEL(ADC_Vref)); 

    tmp_reg = ADC->CCR;
    tmp_reg &= (uint32_t)(~ADC_CCR_VREF_MASK);
    tmp_reg |= ADC_Vref;
    
    ADC->CCR = tmp_reg;
}

/**
  * @brief  Enable ADC internal vref 2.048V.
  * @param  NewState: new state of ADC internal vref.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_InternalVrefCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable internal vref*/
        ADC->CCR &= (uint32_t)(~ADC_CCR_VREF_PWD);
    }
    else
    {
        /* Disable internal vref */
        ADC->CCR |= (uint32_t)ADC_CCR_VREF_PWD;
    }
}


/**
  * @brief  Configures for the selected ADC.
  * @param  ADC_Channel: the ADC channel to configure. 
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  * @retval None
  */
void ADC_ChannelConfig(uint32_t ADC_Channel)
{
    /* Check the parameters */
    assert_param(IS_ADC_CHANNEL(ADC_Channel));

    /* Configure the ADC Channel */
    ADC->CHSELR |= (uint32_t)ADC_Channel;
}

/**
  * @brief  Enable the Continuous mode for the selected ADC channels.
  * @param  NewState: new state of the Continuous mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   It is not possible to have both discontinuous mode and continuous mode
  *         enabled. In this case (If DISCEN and CONT are Set), the ADC behaves 
  *         as if continuous mode was disabled
  * @retval None
  */
void ADC_ContinuousModeCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Continuous mode*/
        ADC->CFGR1 |= (uint32_t)ADC_CFGR1_CONT;
    }
    else
    {
        /* Disable the Continuous mode */
        ADC->CFGR1 &= (uint32_t)(~ADC_CFGR1_CONT);
    }
}

/**
  * @brief  Enable the discontinuous mode for the selected ADC channels.
  * @param  NewState: new state of the discontinuous mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   It is not possible to have both discontinuous mode and continuous mode
  *         enabled. In this case (If DISCEN and CONT are Set), the ADC behaves 
  *         as if continuous mode was disabled
  * @retval None
  */
void ADC_DiscModeCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Discontinuous mode */
        ADC->CFGR1 |= (uint32_t)ADC_CFGR1_DISCEN;
    }
    else
    {
        /* Disable the Discontinuous mode */
        ADC->CFGR1 &= (uint32_t)(~ADC_CFGR1_DISCEN);
    }
}

/**
  * @brief  Enable the Overrun mode for the selected ADC channels.
  * @param  NewState: new state of the Overrun mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_OverrunModeCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Overrun mode */
        ADC->CFGR1 |= (uint32_t)ADC_CFGR1_OVRMOD;
    }
    else
    {
        /* Disable the Overrun mode */
        ADC->CFGR1 &= (uint32_t)(~ADC_CFGR1_OVRMOD);
    }
}

/**
  * @brief  Returns ADC conversion result data for ADC channel.  
  * @param  ADC_Channel: the ADC channel to configure. 
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(uint32_t ADC_Channel)
{
    /* Check the parameters */
    assert_param(IS_ADC_CHANNEL(ADC_Channel));

    /* Return the selected ADC conversion value */
    if (ADC_Channel == ADC_Channel_0)
        return (uint16_t) ADC->DR0;
    else if (ADC_Channel == ADC_Channel_1)
        return (uint16_t) ADC->DR1;
    else if (ADC_Channel == ADC_Channel_2)
        return (uint16_t) ADC->DR2;
    else if (ADC_Channel == ADC_Channel_3)
        return (uint16_t) ADC->DR3;
    else if (ADC_Channel == ADC_Channel_4)
        return (uint16_t) ADC->DR4;
    else if (ADC_Channel == ADC_Channel_5)
        return (uint16_t) ADC->DR5;
    else if (ADC_Channel == ADC_Channel_6)
        return (uint16_t) ADC->DR6;
    else if (ADC_Channel == ADC_Channel_7)
        return (uint16_t) ADC->DR7;
    else if (ADC_Channel == ADC_Channel_8)
        return (uint16_t) ADC->DR8;
    else if (ADC_Channel == ADC_Channel_9)
        return (uint16_t) ADC->DR9;
    else if (ADC_Channel == ADC_Channel_10)
        return (uint16_t) ADC->DR10;
    else if (ADC_Channel == ADC_Channel_11)
        return (uint16_t) ADC->DR11;
    else if (ADC_Channel == ADC_Channel_12)
        return (uint16_t) ADC->DR12;
    else if (ADC_Channel == ADC_Channel_13)
        return (uint16_t) ADC->DR13;
    else if (ADC_Channel == ADC_Channel_14)
        return (uint16_t) ADC->DR14;
    else 
        return (uint16_t) ADC->DR15;
}

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_EOC: End of conversion interrupt 
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
  * @param  NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(uint32_t ADC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_CONFIG_IT(ADC_IT)); 

    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADC->IER |= ADC_IT;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADC->IER &= (~(uint32_t)ADC_IT);
    }
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADC_FLAG: specifies the flag to check. 
  *          This parameter can be one of the following values:
  *            @arg ADC_FLAG_AWD: Analog watchdog flag
  *            @arg ADC_FLAG_OVR: Overrun flag 
  *            @arg ADC_FLAG_EOSEQ: End of Sequence flag
  *            @arg ADC_FLAG_EOC: End of conversion flag
  *            @arg ADC_FLAG_ADSTART: ADC start flag 
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(uint32_t ADC_FLAG)
{
    FlagStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

    if((uint32_t)(ADC_FLAG & 0x01000000))
    {
        tmpreg = ADC->CR & ADC_CR_ADSTART;
    }
    else
    {
        tmpreg = ADC->ISR;
    }

    /* Check the status of the specified ADC flag */
    if ((tmpreg & ADC_FLAG) != (uint32_t)RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Clears the ADC's pending flags.
  * @param  ADC_FLAG: specifies the flag to clear. 
  *          This parameter can be any combination of the following values:
  *            @arg ADC_FLAG_AWD: Analog watchdog flag
  *            @arg ADC_FLAG_EOC: End of conversion flag
  *            @arg ADC_FLAG_EOSEQ: End of Sequence flag
  *            @arg ADC_FLAG_OVR: Overrun flag 
  * @retval None
  */
void ADC_ClearFlag(uint32_t ADC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));

    /* Clear the selected ADC flags */
    ADC->ISR = ADC_FLAG;
}

/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  ADC_IT: specifies the ADC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_EOC: End of conversion interrupt 
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
  * @retval The new state of ADC_IT (SET or RESET).
  */
ITStatus ADC_GetITStatus(uint32_t ADC_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* Check the parameters */
    assert_param(IS_ADC_GET_IT(ADC_IT));

    /* Get the ADC_IT enable bit status */
    enablestatus = (uint32_t)(ADC->IER & ADC_IT); 

    /* Check the status of the specified ADC interrupt */
    if (((uint32_t)(ADC->ISR & ADC_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
    {
        /* ADC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_IT is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_IT status */
    return  bitstatus;
}

/**
  * @brief  Clears the ADC's interrupt pending bits.
  * @param  ADC_IT: specifies the ADC interrupt pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_EOC: End of conversion interrupt
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
  * @retval None
  */
void ADC_ClearITPendingBit(uint32_t ADC_IT)
{
    /* Check the parameters */
    assert_param(IS_ADC_CLEAR_IT(ADC_IT));

    /* Clear the selected ADC interrupt pending bits */
    ADC->ISR = ADC_IT;
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
