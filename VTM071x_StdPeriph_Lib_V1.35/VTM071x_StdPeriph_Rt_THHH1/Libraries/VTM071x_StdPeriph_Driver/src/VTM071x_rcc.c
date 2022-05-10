/**
  ******************************************************************************
  * @file    VTM071x_rcc.c
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides all the RCC firmware functions.
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
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC 
  * @brief RCC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup RCC_Private_Defines
  * @{
  */
#define RCC_MAINCLKUEN_DISABLE				0
#define RCC_MAINCLKUEN_ENABLE				1

#define RCC_USARTCLKUEN_DISABLE				0
#define RCC_USARTCLKUEN_ENABLE				1

#define RCC_FLASHCLKUEN_DISABLE				0
#define RCC_FLASHCLKUEN_ENABLE				1

#define RCC_WWDGCLKUEN_DISABLE              0
#define RCC_WWDGCLKUEN_ENABLE               1

#define RCC_OUTCLKUEN_DISABLE				0
#define RCC_OUTCLKUEN_ENABLE				1

#define RCC_DEEPSLEEPEN_SET					((uint32_t)0x00000002)
#define RCC_DEEPSLEEPEN_RESET				((uint32_t)0x0000FFFD)

#define SYSTICK_SOURCE_HCLK                 ((uint32_t)0x00000004)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RCC_Private_Functions
  * @{
  */

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
  *   
  *   This parameter can be any combination of the following values:        
  *	@arg RCC_AHBCLKCTRL_FLASH
  *	@arg RCC_AHBCLKCTRL_GPIO
  *	@arg RCC_AHBCLKCTRL_DMA
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		RCC->AHBCLKCTRL0_SET = RCC_AHBPeriph;
	}
	else
	{
		RCC->AHBCLKCTRL0_CLR = RCC_AHBPeriph;
	}
}

/**
  * @brief  Enables or disables the APB peripheral clock.
  * @param  RCC_APBPeriph: specifies the APB peripheral to gates its clock.
  *   
  *   This parameter can be any combination of the following values:
  *     @arg RCC_AHBCLKCTRL1_DAC 
  *     @arg RCC_AHBCLKCTRL1_MATHS  
  *     @arg RCC_AHBCLKCTRL1_TSC   
  *     @arg RCC_AHBCLKCTRL_USART0
  *     @arg RCC_AHBCLKCTRL_USART1
  *     @arg RCC_AHBCLKCTRL_I2C0  
  *     @arg RCC_AHBCLKCTRL_ADC   
  *     @arg RCC_AHBCLKCTRL_IOCON 
  *     @arg RCC_AHBCLKCTRL_WWDG  
  *     @arg RCC_AHBCLKCTRL_MCPWM 
  *     @arg RCC_AHBCLKCTRL_SPI0  
  *     @arg RCC_AHBCLKCTRL_TIMER0
  *     @arg RCC_AHBCLKCTRL_TIMER1
  *     @arg RCC_AHBCLKCTRL_ACMP  
  *     @arg RCC_AHBCLKCTRL_TIMER2
  *     @arg RCC_AHBCLKCTRL_IWDG  
  *     @arg RCC_AHBCLKCTRL_SPI1  
  *     @arg RCC_AHBCLKCTRL_I2C1  
  *     @arg RCC_AHBCLKCTRL_TIMER3
  *     @arg RCC_AHBCLKCTRL_RTC   
  *     @arg RCC_AHBCLKCTRL_USB   
  * 
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APBPeriphClockCmd(uint32_t RCC_APBPeriph, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
        if ((RCC_APBPeriph == RCC_AHBCLKCTRL1_DAC) || \
            (RCC_APBPeriph == RCC_AHBCLKCTRL1_MATHS) || \
            (RCC_APBPeriph == RCC_AHBCLKCTRL1_TSC))
        {
            RCC->AHBCLKCTRL1_SET = RCC_APBPeriph;
        }
        else
        {
            RCC->AHBCLKCTRL0_SET = RCC_APBPeriph;
        }
	}
	else
	{
        if ((RCC_APBPeriph == RCC_AHBCLKCTRL1_DAC) || \
            (RCC_APBPeriph == RCC_AHBCLKCTRL1_MATHS) || \
            (RCC_APBPeriph == RCC_AHBCLKCTRL1_TSC))
        {
            RCC->AHBCLKCTRL1_CLR = RCC_APBPeriph;
        }
        else
        {
            RCC->AHBCLKCTRL0_CLR = RCC_APBPeriph;
        }
	}
}

/**
  * @brief  Forces or releases AHB peripheral reset.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
  *   This parameter can be any combination of the following values:
  *	    @arg RCC_PRESETCTRL_FLASH
  *	    @arg RCC_PRESETCTRL_GPIO
  *	    @arg RCC_PRESETCTRL_DMA
  * @param  NewState: new state of the specified peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_RCC_AHB_RST_PERIPH(RCC_AHBPeriph));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
    
	if (NewState != DISABLE)
	{
		RCC->PRESETCTRL0_CLR = RCC_AHBPeriph;
	}
	else
	{
		RCC->PRESETCTRL0_SET = RCC_AHBPeriph;
	}
}

/**
  * @brief  Forces or releases APB peripheral reset.
  * @param  RCC_APBPeriph: specifies the APB peripheral to reset.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_PRESETCTRL1_DAC 
  *     @arg RCC_PRESETCTRL1_MATHS  
  *     @arg RCC_PRESETCTRL1_TSC   
  *     @arg RCC_PRESETCTRL_USART0
  *     @arg RCC_PRESETCTRL_USART1
  *     @arg RCC_PRESETCTRL_I2C0  
  *     @arg RCC_PRESETCTRL_ADC   
  *     @arg RCC_PRESETCTRL_IOCON 
  *     @arg RCC_PRESETCTRL_WWDG  
  *     @arg RCC_PRESETCTRL_MCPWM 
  *     @arg RCC_PRESETCTRL_SPI0  
  *     @arg RCC_PRESETCTRL_TIMER0
  *     @arg RCC_PRESETCTRL_TIMER1
  *     @arg RCC_PRESETCTRL_ACMP  
  *     @arg RCC_PRESETCTRL_TIMER2
  *     @arg RCC_PRESETCTRL_IWDG  
  *     @arg RCC_PRESETCTRL_SPI1  
  *     @arg RCC_PRESETCTRL_I2C1  
  *     @arg RCC_PRESETCTRL_TIMER3
  *     @arg RCC_PRESETCTRL_RTC   
  *     @arg RCC_PRESETCTRL_USB   
  *
  * @param  NewState: new state of the specified peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APBPeriphResetCmd(uint32_t RCC_APBPeriph, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
        if ((RCC_APBPeriph == RCC_PRESETCTRL1_DAC)  || \
            (RCC_APBPeriph == RCC_PRESETCTRL1_MATHS)  || \
            (RCC_APBPeriph == RCC_PRESETCTRL1_TSC))
        {
            RCC->PRESETCTRL1_CLR = RCC_APBPeriph;
        }
        else
        {
            RCC->PRESETCTRL0_CLR = RCC_APBPeriph;
        }
	}
	else
	{
        if ((RCC_APBPeriph == RCC_PRESETCTRL1_DAC)  || \
            (RCC_APBPeriph == RCC_PRESETCTRL1_MATHS)  || \
            (RCC_APBPeriph == RCC_PRESETCTRL1_TSC))
        {
            RCC->PRESETCTRL1_SET = RCC_APBPeriph;
        }
        else
        {
            RCC->PRESETCTRL0_SET = RCC_APBPeriph;
        }
	}
}

/**
  * @brief  Check boot mode.
  * @param  None.
  * @retval The boot mode (SET--debug or RESET-normal).
  */
FlagStatus RCC_GetBootMode(void)
{
	FlagStatus bitstatus = RESET;

    if (RCC->BOOTREMAP & (RCC_BOOTREMAP_BOOT_IO | RCC_BOOTREMAP_BOOT_FLASH | RCC_BOOTREMAP_BOOT_REG))
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
  * @brief  Checks whether the protect flag is set or not.
  * @param  RCC_PROTECT: specifies the protect level.
  *   This parameter can be one of the following values:
  *     @arg RCC_PROTECT_LEVEL0
  *     @arg RCC_PROTECT_LEVEL1
  * @retval The new state of protect level (SET or RESET).
  */
FlagStatus RCC_GetProtectStatus(uint32_t RCC_PROTECT)
{
	FlagStatus bitstatus = RESET;
	assert_param(IS_RCC_PROTECT_LEVEL(RCC_PROTECT));
	
	if((RCC->BOOTREMAP & RCC_PROTECT) != 0)
		bitstatus = SET;
	else
		bitstatus = RESET;

	return bitstatus;	
}

/**
  * @brief  Enable or disable SRAM remap.
  * @param  NewState: new state of SRAM remap. 
                This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_SRAMRemapCmd(FunctionalState NewState)
{
    uint32_t regtmp = RCC->BOOTSRAM;
    
    assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState != DISABLE)
	{
        regtmp &= ~0xFF;
        regtmp |= RCC_BOOTSRAM_SRAM_REMAP;
        RCC->BOOTSRAM = regtmp;
	}
	else
	{
        regtmp &= ~0xFF;
        RCC->BOOTSRAM = regtmp;
	}
}

/**
  * @brief  Enable or disable LDROM remap.
  * @param  NewState: new state of LDROM remap. 
                This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_LDROMRemapCmd(FunctionalState NewState)
{
    uint32_t regtmp = RCC->BOOTSRAM;
    
    assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState != DISABLE)
	{
        regtmp &= ~0xFF0000;
        regtmp |= RCC_BOOTSRAM_LDROM_REMAP;
        RCC->BOOTSRAM = regtmp;
	}
	else
	{
        regtmp &= ~0xFF0000;
        RCC->BOOTSRAM = regtmp;
	}
}

/**
  * @brief  Checks whether the reset source flag is set or not.
  * @param  RCC_ResetSource: specifies the reset source.
  *   This parameter can be one of the following values:
  *     @arg RCC_RESET_SOURCE_POR
  *     @arg RCC_RESET_SOURCE_EXT
  *     @arg RCC_RESET_SOURCE_WDT
  *     @arg RCC_RESET_SOURCE_BOR
  *     @arg RCC_RESET_SOURCE_SYS
  *     @arg RCC_RESET_SOURCE_IWDG
  * @retval The new state of reset source (SET or RESET).
  */
FlagStatus RCC_GetResetSourceStatus(uint32_t RCC_ResetSource)
{
	FlagStatus bitstatus = RESET;
	assert_param(IS_RCC_RESET_SOURCE(RCC_ResetSource));
	
	if((RCC->SYSRSTSTAT & RCC_ResetSource) != 0)
		bitstatus = SET;
	else
		bitstatus = RESET;

	return bitstatus;	
}

/**
  * @brief  Select MAIN Clock Source 
  * @param  RCC_MAINCLKSource: specifies MAIN Clock Source .
  *   This parameter can be the following values:
  *     @arg RCC_MAINCLK_SOURCE_12M_IRC
  *     @arg RCC_MAINCLK_SOURCE_SYSPLL
  *		@arg RCC_MAINCLK_SOURCE_12M_OSC
  *		@arg RCC_MAINCLK_SOURCE_10K_IRC
  * @retval None
  */
void RCC_MAINCLKSel(uint8_t RCC_MAINCLKSource)
{
	assert_param(IS_RCC_MAINCLK_SOURCE(RCC_MAINCLKSource));

	RCC->MAINCLKSEL = RCC_MAINCLKSource;
	RCC->MAINCLKUEN = RCC_MAINCLKUEN_DISABLE;
	RCC->MAINCLKUEN = RCC_MAINCLKUEN_ENABLE;	
}

/**
  * @brief  Select USART Clock Source 
  * @param  RCC_USARTCLKSource: specifies USART Clock Source .
  *   This parameter can be the following values:
  *     @arg RCC_USARTCLK_SOURCE_12M_IRC
  *     @arg RCC_USARTCLK_SOURCE_SYSPLL
  *     @arg RCC_USARTCLK_SOURCE_12M_OSC
  *     @arg RCC_USARTCLK_SOURCE_10K_OSC
  * @retval None
  */
void RCC_USARTCLKSel(uint8_t RCC_USARTCLKSource)
{
	assert_param(IS_RCC_USARTCLK_SOURCE(RCC_USARTCLKSource));

	RCC->USARTCLKSEL = RCC_USARTCLKSource;
	RCC->USARTCLKUEN = RCC_USARTCLKUEN_DISABLE;
	RCC->USARTCLKUEN = RCC_USARTCLKUEN_ENABLE;
}

/**
  * @brief  Select USB Clock Source 
  * @param  RCC_USBCLKSource: specifies USB Clock Source .
  *   This parameter can be the following values:
  *     @arg RCC_USBCLK_SOURCE_IRC
  *     @arg RCC_USBCLK_SOURCE_OSC
  * @retval None
  */
void RCC_USBCLKSel(uint8_t RCC_USBCLKSource)
{
	assert_param(IS_RCC_USBCLK_SOURCE(RCC_USBCLKSource));

	RCC->USBCLKSEL = RCC_USBCLKSource;
	RCC->USBCLKUEN = RCC_FLASHCLKUEN_DISABLE;
	RCC->USBCLKUEN = RCC_FLASHCLKUEN_ENABLE;
}

/**
  * @brief  Select OUT Clock Source 
  * @param  RCC_OUTCLKSource: specifies OUT Clock Source .
  *   This parameter can be the following values:
  *     @arg RCC_OUTCLK_SOURCE_12M_IRC
  *     @arg RCC_OUTCLK_SOURCE_SYSPLL
  *     @arg RCC_OUTCLK_SOURCE_10K_IRC
  *     @arg RCC_OUTCLK_SOURCE_12M_OSC
  *     @arg RCC_OUTCLK_SOURCE_32768_OSC
  *     @arg RCC_OUTCLK_SOURCE_USBPLL
  * @retval None
  */
void RCC_OUTCLKSel(uint8_t RCC_OUTCLKSource)
{
	assert_param(IS_RCC_OUTCLK_SOURCE(RCC_OUTCLKSource));

	RCC->OUTCLKSEL = RCC_OUTCLKSource;
	RCC->OUTCLKUEN = RCC_OUTCLKUEN_DISABLE;
	RCC->OUTCLKUEN = RCC_OUTCLKUEN_ENABLE;	
}

/**
  * @brief  Select WWDG Clock Source
  * @param  RCC_WWDGCLKSource: specifies WWDG Clock Source.
  *   This parameter can be the following values:
  *     @arg RCC_WWDGCLK_SOURCE_12M_IRC
  *     @arg RCC_WWDGCLK_SOURCE_SYSPLL
  *     @arg RCC_WWDGCLK_SOURCE_12M_OSC
  *     @arg RCC_WWDGCLK_SOURCE_10K_IRC
  * @retval None
  */
void RCC_WWDGCLKSel(uint8_t RCC_WWDGCLKSource)
{
	assert_param(IS_RCC_WWDGCLK_SOURCE(RCC_WWDGCLKSource));
    
	RCC->WWDGCLKSEL = RCC_WWDGCLKSource;
	RCC->WWDGCLKUEN = RCC_WWDGCLKUEN_DISABLE;
	RCC->WWDGCLKUEN = RCC_WWDGCLKUEN_ENABLE;
}

/**
  * @brief  Set Clock divider factor .
  * @param  RCC_Peripheral: specifies the Peripheral.
  *   This parameter can be one of the following values:
  *     @arg RCC_CLOCKFREQ_SYSAHBCLK
  *     @arg RCC_CLOCKFREQ_USART0CLK
  *     @arg RCC_CLOCKFREQ_USART1CLK
  *     @arg RCC_CLOCKFREQ_SYSTICKCLK
  *     @arg RCC_CLOCKFREQ_SPI0CLK
  *     @arg RCC_CLOCKFREQ_WWDGCLK
  *     @arg RCC_CLOCKFREQ_CLKOUTCLK
  *     @arg RCC_CLOCKFREQ_ADCCLK
  *     @arg RCC_CLOCKFREQ_SPI1CLK
  *     @arg RCC_CLOCKFREQ_DACCLK
  * @param  RCC_CLKDIV: specifies the Clock divider factor.
  *   This parameter can be x where x:[0,255].
  * @retval None
  */
void RCC_SETCLKDivider(uint32_t RCC_Peripheral_Clock, uint8_t RCC_CLKDIV)
{
	assert_param(IS_RCC_CLKDIV_PER(RCC_Peripheral_Clock));

	(*((__IO uint32_t *)(RCC_BASE + RCC_Peripheral_Clock))) = RCC_CLKDIV;		
}

/**
  * @brief  Enable or disable wakeup function.
  * @param  RCC_Wakeup: specifies the number of pin.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_WAKEUP_GPIO1_0
  *     @arg RCC_WAKEUP_GPIO1_1
  *     @arg RCC_WAKEUP_GPIO1_2
  *     @arg RCC_WAKEUP_GPIO1_3
  *     @arg RCC_WAKEUP_GPIO1_4
  *     @arg RCC_WAKEUP_GPIO0_0
  *     @arg RCC_WAKEUP_GPIO5_5
  * @param  NewState: new state of wakeup pin. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_WakeupPinCmd(uint32_t RCC_Wakeup, FunctionalState NewState)
{
	assert_param(IS_RCC_WAKEUP_PIN(RCC_Wakeup));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState != DISABLE)
	{
		RCC->WAKEUPEN |= RCC_Wakeup;
	}
	else
	{
		RCC->WAKEUPEN &= ~RCC_Wakeup;
	}
}

/**
  * @brief  Checks whether the RTC POR flag is set or not.
  * @param  None
  * @retval The new state of RTC POR flag (SET or RESET).
  */
FlagStatus RCC_GetANAStatus(void)
{
	FlagStatus bitstatus = RESET;
	
	if((RCC->ANASTATUS & RCC_PORSTATUS_RTC) != 0)
		bitstatus = SET;
	else
		bitstatus = RESET;

	return bitstatus;	
}

/**
  * @brief  Set systick calibration value.
  * @param  CalibrationValue: specifies calibration value.
  *   This parameter can be one x where x:[0,0x3FFFFF].
  * @retval None
  */
void RCC_SetSystickCalibrationValue(uint32_t CalibrationValue)
{
	assert_param(IS_RCC_SYSTICK_CALIBRATION_VALUE(CalibrationValue));

	RCC->SYSTICKCAL = CalibrationValue;
}

/**
  * @brief  Configures the BOR reset electrical level.
  * @param  BORRSTVal: specifies BOR reset electrical level.
  *   This parameter can be one of the following values:
  *     @arg RCC_BORRST_VAL_3_7
  *     @arg RCC_BORRST_VAL_2_7
  *     @arg RCC_BORRST_VAL_2_2
  *     @arg RCC_BORRST_VAL_1_8
  * @param  NewState: new mode of the BOR reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_BORConfig(uint8_t BORRSTVal, FunctionalState NewState)
{  	
	uint32_t tmpreg;
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_RCC_BORRST_VAL(BORRSTVal));

	tmpreg = RCC->BORCTRL;
	tmpreg &= ~RCC_BORCTRL_BORLEV_MASK;
	tmpreg |= BORRSTVal;

	if(NewState != DISABLE)
	{
		tmpreg |= RCC_BORCTRL_BORENA;	
	}
	else
	{
		tmpreg &= ~RCC_BORCTRL_BORENA;	
	}
    
    RCC->BORCTRL = tmpreg;
}

/**
  * @brief  Configures the BOD electrical level.
  * @param  BODVal: specifies BOD electrical level.
  *   This parameter can be one of the following values:
  *     @arg RCC_BOD_VAL_4_4
  *     @arg RCC_BOD_VAL_3_7
  *     @arg RCC_BOD_VAL_2_7
  *     @arg RCC_BOD_VAL_2_2
  * @retval None
  */
void RCC_BODConfig(uint8_t BODVal)
{
	uint8_t tmpreg;
	assert_param(IS_RCC_BORRST_VAL(BODVal));

	tmpreg = RCC->BORCTRL;
	tmpreg &= ~RCC_BORCTRL_BODLEV_MASK;
	tmpreg |= BODVal;
	RCC->BORCTRL = tmpreg;
}

/**
  * @brief  Configures the state the chip must enter when the Deep-sleep mode is asserted by the ARM.
  * @param  RCC_Analog_Switch: specifies Module which will be power on or down.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_PDCFG_OSC12M
  *     @arg RCC_PDCFG_ADC
  *     @arg RCC_PDCFG_SYSPLL
  *     @arg RCC_PDCFG_BOD
  *     @arg RCC_PDCFG_BOR
  *     @arg RCC_PDCFG_IRC12M
  *     @arg RCC_PDCFG_FLASH
  *     @arg RCC_PDCFG_ACMP
  *     @arg RCC_PDCFG_USB
  *     @arg RCC_PDCFG_32768_OSC
  *     @arg RCC_PDCFG_DAC0
  *     @arg RCC_PDCFG_DAC1
  *     @arg RCC_PDCFG_USB_LDO
  * @param  PD_MODE: new mode of the Oscillator.
  *   This parameter can be one of the following values:
  *     @arg RCC_PDCFG_POWER_ON
  *     @arg RCC_PDCFG_POWER_DOWN
  * @retval None
  */
void RCC_PDSLEEPConfig(uint16_t RCC_Analog_Switch, uint8_t PD_MODE)
{
	assert_param(IS_RCC_PDCFG_ANALOG_BLOCK(RCC_Analog_Switch));
	assert_param(IS_RCC_PDCFG_MODE(PD_MODE));

	if(PD_MODE != RCC_PDCFG_POWER_DOWN)
	{
		RCC->PDSLEEPCFG &= ~RCC_Analog_Switch;
	}
	else
	{
		RCC->PDSLEEPCFG |= RCC_Analog_Switch;
	}
}

/**
  * @brief  Configures the state the chip must enter when it is waking up from Deep-sleep mode.
  * @param  RCC_Analog_Switch: specifies Module which will be power on or down.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_PDCFG_OSC12M
  *     @arg RCC_PDCFG_ADC
  *     @arg RCC_PDCFG_SYSPLL
  *     @arg RCC_PDCFG_BOD
  *     @arg RCC_PDCFG_BOR
  *     @arg RCC_PDCFG_IRC12M
  *     @arg RCC_PDCFG_FLASH
  *     @arg RCC_PDCFG_ACMP
  *     @arg RCC_PDCFG_USB
  *     @arg RCC_PDCFG_32768_OSC
  *     @arg RCC_PDCFG_DAC0
  *     @arg RCC_PDCFG_DAC1
  *     @arg RCC_PDCFG_USB_LDO
  *
  * @param  PD_MODE: new mode of the Oscillator.
  *   This parameter can be one of the following values:
  *     @arg RCC_PDCFG_POWER_ON
  *     @arg RCC_PDCFG_POWER_DOWN
  * @retval None
  */
void RCC_PDAWAKEConfig(uint16_t RCC_Analog_Switch, uint8_t PD_MODE)
{
	assert_param(IS_RCC_PDCFG_ANALOG_BLOCK(RCC_Analog_Switch));
	assert_param(IS_RCC_PDCFG_MODE(PD_MODE));
    
	if(PD_MODE != RCC_PDCFG_POWER_DOWN)
	{
		RCC->PDAWAKECFG &= ~RCC_Analog_Switch;
	}
	else
	{
		RCC->PDAWAKECFG |= RCC_Analog_Switch;
	}
}

/**
  * @brief  Configures the power to the various analog blocks.
  * @param  RCC_Analog_Switch: specifies Module which will be power on or down.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_PDCFG_OSC12M
  *     @arg RCC_PDCFG_ADC
  *     @arg RCC_PDCFG_SYSPLL
  *     @arg RCC_PDCFG_BOD
  *     @arg RCC_PDCFG_BOR
  *     @arg RCC_PDCFG_IRC12M
  *     @arg RCC_PDCFG_FLASH
  *     @arg RCC_PDCFG_ACMP
  *     @arg RCC_PDCFG_USB
  *     @arg RCC_PDCFG_32768_OSC
  *     @arg RCC_PDCFG_DAC0
  *     @arg RCC_PDCFG_DAC1
  *     @arg RCC_PDCFG_USB_LDO
  *
  * @param  PD_MODE: new mode of the Oscillator.
  *   This parameter can be one of the following values:
  *     @arg RCC_PDCFG_POWER_ON
  *     @arg RCC_PDCFG_POWER_DOWN
  * @retval None
  */
void RCC_PDRUNConfig(uint16_t RCC_Analog_Switch, uint8_t PD_MODE)
{
	assert_param(IS_RCC_PDCFG_ANALOG_BLOCK(RCC_Analog_Switch));
	assert_param(IS_RCC_PDCFG_MODE(PD_MODE));
    
	if(PD_MODE != RCC_PDCFG_POWER_DOWN)
	{
		RCC->PDRUNCFG &= ~RCC_Analog_Switch;
	}
	else
	{
		RCC->PDRUNCFG |= RCC_Analog_Switch;
	}
}

/**
  * @brief  Get VTM071x Chip ID.
  * @param  None
  * @retval ID.
  */
uint32_t RCC_GetID(void)
{
	return RCC->DEVICEID;	
}

/**
  * @brief  Configures DMA Channel for peripheral.
  * @param  DMAChannelForPeripheral: specifies DMA Channel for peripheral.
  *   This parameter can be one of the following values:
  *     @arg RCC_DMACHANNEL0_USART0_TX
  *     @arg RCC_DMACHANNEL1_USART0_RX
  *     @arg RCC_DMACHANNEL2_USART1_TX
  *     @arg RCC_DMACHANNEL3_USART1_RX
  *     @arg RCC_DMACHANNEL4_I2C0_TX
  *     @arg RCC_DMACHANNEL4_ADC
  *     @arg RCC_DMACHANNEL5_I2C1_RX
  *     @arg RCC_DMACHANNEL5_DAC0
  *     @arg RCC_DMACHANNEL6_I2C1_TX
  *     @arg RCC_DMACHANNEL6_DAC1
  *     @arg RCC_DMACHANNEL7_I2C1_RX
  *     @arg RCC_DMACHANNEL8_SPI0_TX
  *     @arg RCC_DMACHANNEL9_SPI0_RX
  *     @arg RCC_DMACHANNEL10_SPI1_TX
  *     @arg RCC_DMACHANNEL11_SPI1_RX
  *     @arg RCC_DMACHANNEL12_TIMER0
  *     @arg RCC_DMACHANNEL13_TIMER1
  *     @arg RCC_DMACHANNEL14_TIMER2
  *     @arg RCC_DMACHANNEL15_TIMER3
  * @retval None
  */
void RCC_DMAChannelConfig(uint32_t DMAChannelForPeripheral)
{
    assert_param(IS_RCC_DMACHANNEL_CONFIG(DMAChannelForPeripheral));
    
    if (DMAChannelForPeripheral & RCC_DMACHANNEL_FLAG)
    {
        RCC->DMACTRL |= (DMAChannelForPeripheral & (~RCC_DMACHANNEL_FLAG));
    }
    else
    {
        RCC->DMACTRL &= ~(DMAChannelForPeripheral);
    }
}

/**
  * @brief  Enables or disables the PowerDown mode.
  * @param  NewState: new state of the PowerDown mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PowerDownCmd(FunctionalState NewState)
{
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		RCC->PCON |= RCC_DEEPSLEEPEN_SET;
	}
	else
	{
		RCC->PCON &= RCC_DEEPSLEEPEN_RESET;
	}
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg RCC_SLEEPFLAG 
  *     @arg RCC_DPFLAG
  *     @arg RCC_LDO_STATUS
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(uint32_t RCC_FLAG)
{
	FlagStatus bitstatus = RESET;
	assert_param(IS_RCC_FLAG(RCC_FLAG));

    if ((RCC->PCON & RCC_FLAG) != (uint16_t)RESET)
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
  * @brief  Clears the RCC reset flags.
  * @param  RCC_FLAG: specifies the flag to clear.
  *   This parameter can be one of the following values:
  *     @arg RCC_SLEEPFLAG
  * @retval None
  */
void RCC_ClearFlag(uint32_t RCC_FLAG)
{
	assert_param(IS_RCC_CLEAR_FLAG(RCC_FLAG));

    RCC->PCON |= RCC_FLAG;
}

/**
  * @brief  Switch LDO.
  * @param  LDO: specifies the main LDO or low power ldo.
  *   This parameter can be one of the following values:
  *     @arg RCC_MAIN_LDO
  *     @arg RCC_LOW_POWER_LDO
  * @retval None
  */
void RCC_SwitchLDO(uint32_t LDO)
{
	assert_param(IS_RCC_LDO(LDO));
    
	if(LDO == RCC_MAIN_LDO)
	{
		RCC->PCON &= ~RCC_LOW_POWER_LDO;
	}
	else
	{
		RCC->PCON |= RCC_LOW_POWER_LDO;
	}
}

/**
  * @brief  Configures WDG behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the WDG.
  *          This parameter can be any combination of the following values:
  *             @arg DBGMCU_WWDG_STOP: Debug WWDG stopped when Core is halted
  *             @arg DBGMCU_IWDG_STOP: Debug IWDG stopped when Core is halted
  * @param  NewState: new state of the specified WDG in Debug mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_WDG_STOP(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->DBGCTRL |= DBGMCU_Periph;
  }
  else
  {
    RCC->DBGCTRL &= ~DBGMCU_Periph;
  }
}

/**
  * @brief  Returns the frequencies of different on chip clocks.
  * @param  RCC_Clocks: specifies on chip clock.
  *   This parameter can be one of the following values:
  *     @arg RCC_CLOCKFREQ_SYSAHBCLK
  *     @arg RCC_CLOCKFREQ_USART0CLK
  *     @arg RCC_CLOCKFREQ_USART1CLK
  *     @arg RCC_CLOCKFREQ_SYSTICKCLK
  *     @arg RCC_CLOCKFREQ_SPI0CLK
  *     @arg RCC_CLOCKFREQ_WWDGCLK
  *     @arg RCC_CLOCKFREQ_CLKOUTCLK
  *     @arg RCC_CLOCKFREQ_ADCCLK
  *     @arg RCC_CLOCKFREQ_SPI1CLK
  *     @arg RCC_CLOCKFREQ_DACCLK
  *     @arg RCC_CLOCKFREQ_IWDG
  *     @arg RCC_CLOCKFREQ_TIMER
  *     @arg RCC_CLOCKFREQ_TSC
  *     @arg RCC_CLOCKFREQ_FLASH
  * @retval The frequency of different on chip clocks.
  */
uint32_t RCC_GetClocksFreq(uint32_t RCC_Clocks)
{
 	uint32_t tmpclk = 0, syspll, mainclk, hclk, usartclk, wdtclk, outclk;
	uint8_t usartclk_sel, wwdgclk_sel, outclk_sel;
	
	usartclk_sel = RCC->USARTCLKSEL;
	wwdgclk_sel = RCC->WWDGCLKSEL;
    outclk_sel = RCC->OUTCLKSEL;
    
	syspll = ((RCC->SYSPLLCTRL & RCC_SYSPLLCTRL_FREQ) + 4) * 12000000;
	mainclk = SystemCoreClock;
	hclk = mainclk / RCC->SYSAHBCLKDIV;

	if ((RCC_Clocks == RCC_CLOCKFREQ_SYSAHBCLK) || (RCC_Clocks == RCC_CLOCKFREQ_TIMER) || (RCC_Clocks == RCC_CLOCKFREQ_TSC))
		tmpclk = hclk;
	else if ((RCC_Clocks == RCC_CLOCKFREQ_USART0CLK) || (RCC_Clocks == RCC_CLOCKFREQ_USART1CLK))
	{
		if ((*((__IO uint8_t *)(RCC_BASE + RCC_Clocks))) == 0)
			return 0;

		if ((usartclk_sel == RCC_USARTCLK_SOURCE_12M_IRC) ||(usartclk_sel == RCC_USARTCLK_SOURCE_12M_OSC))
		{
			usartclk = 12000000 / (*((__IO uint8_t *)(RCC_BASE + RCC_Clocks)));
		}
		else if (usartclk_sel == RCC_USARTCLK_SOURCE_SYSPLL)
		{
			usartclk = syspll / (*((__IO uint8_t *)(RCC_BASE + RCC_Clocks)));
		}
        else if (usartclk_sel == RCC_USARTCLK_SOURCE_10K_OSC)
        {
            usartclk = 10000 / (*((__IO uint8_t *)(RCC_BASE + RCC_Clocks)));
        }

		tmpclk = usartclk;
	}
	else if (RCC_Clocks == RCC_CLOCKFREQ_WWDGCLK)
	{
		if (RCC->WWDGCLKDIV == 0)
			return 0;

		if ((wwdgclk_sel == RCC_WWDGCLK_SOURCE_12M_IRC) || (wwdgclk_sel == RCC_WWDGCLK_SOURCE_12M_OSC))
			wdtclk = 12000000 / RCC->WWDGCLKDIV;
		else if (wwdgclk_sel == RCC_WWDGCLK_SOURCE_SYSPLL)
			wdtclk = syspll / RCC->WWDGCLKDIV;
		else if (wwdgclk_sel == RCC_WWDGCLK_SOURCE_10K_IRC)
			wdtclk = 10000 / RCC->WWDGCLKDIV;

		tmpclk = wdtclk;
	}
	else if (RCC_Clocks == RCC_CLOCKFREQ_CLKOUTCLK)
	{
		if (RCC->OUTCLKDIV == 0)
			return 0;

		if ((outclk_sel == RCC_OUTCLK_SOURCE_12M_IRC) || (outclk_sel == RCC_OUTCLK_SOURCE_12M_OSC))
			outclk = 12000000 / RCC->OUTCLKDIV;
		else if (outclk_sel == RCC_OUTCLK_SOURCE_SYSPLL)
			outclk = syspll / RCC->OUTCLKDIV;
		else if (outclk_sel == RCC_OUTCLK_SOURCE_10K_IRC)
			outclk = 10000 / RCC->OUTCLKDIV;
		else if (outclk_sel == RCC_OUTCLK_SOURCE_32768_OSC)
			outclk = 32768 / RCC->OUTCLKDIV;
		else if (outclk_sel == RCC_OUTCLK_SOURCE_USBPLL)
			outclk = 48000000 / RCC->OUTCLKDIV;

		tmpclk = outclk;
	}
	else if (RCC_Clocks == RCC_CLOCKFREQ_ADCCLK)
	{
		if (RCC->ADCCLKDIV == 0)
			return 0;

		tmpclk = syspll / RCC->ADCCLKDIV;
	}
    else if ((RCC_Clocks == RCC_CLOCKFREQ_SPI0CLK) || (RCC_Clocks == RCC_CLOCKFREQ_SPI1CLK))
    {
		if ((*((__IO uint8_t *)(RCC_BASE + RCC_Clocks))) == 0)
			return 0;
        
        tmpclk = syspll / (*((__IO uint8_t *)(RCC_BASE + RCC_Clocks)));
    }
    else if (RCC_Clocks == RCC_CLOCKFREQ_SYSTICKCLK)
    {
        if (SysTick->CTRL & SYSTICK_SOURCE_HCLK)
        {
            tmpclk = hclk;
        }
        else
        {
            if (RCC->SYSTICKCLKDIV == 0)
                return 0;
            
            tmpclk = hclk / RCC->SYSTICKCLKDIV;
        }
    }
    else if (RCC_Clocks == RCC_CLOCKFREQ_DACCLK)
    {
		if (RCC->DACCLKDIV == 0)
			return 0;

		tmpclk = syspll / RCC->DACCLKDIV;
    }
    else if (RCC_Clocks == RCC_CLOCKFREQ_IWDG)
    {
		tmpclk = 10000;
    }
    else if (RCC_Clocks == RCC_CLOCKFREQ_FLASH)
    {
		tmpclk = 12000000;	
    }

	return tmpclk;
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

