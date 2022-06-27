/**
  ******************************************************************************
  * @file    VTM071x_gpio.c
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides all the GPIO firmware functions.
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
#include "VTM071x_gpio.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO 
  * @brief GPIO driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IOCON_PUPD_OFFSET                   (3)
#define IOCON_DR_OFFSET                     (8)
#define IOCON_SPEED_OFFSET                  (9)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @retval None
  */
void GPIO_DeInit(void)
{
    /* Reset GPIO */
    RCC_AHBPeriphResetCmd(RCC_PRESETCTRL_GPIO, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_PRESETCTRL_GPIO, DISABLE);
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *   parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (0..6) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
  *   contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(uint32_t GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    IOCON_TypeDef *IOCON;
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
    assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

    IOCON = (IOCON_TypeDef *)(IOCON_BASE + (GPIOx * 8 + GPIO_InitStruct->GPIO_Pin) * 4);
    tmpreg = IOCON->CON;
    
    /* GPIO Mode */
    if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AN)
    {
        tmpreg = IOCON_ANA;
    }
    else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)
    {
        tmpreg &= ~IOCON_FUNC_MASK;
        if (GPIOx > GPIO3)
            GPIOBANK1->DIR_CLR = (uint32_t)(1 << ((GPIOx - 4) * 8 + GPIO_InitStruct->GPIO_Pin));
        else
            GPIOBANK0->DIR_CLR = (uint32_t)(1 << ((GPIOx - 0) * 8 + GPIO_InitStruct->GPIO_Pin));
    }
    else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
    {
        tmpreg &= ~IOCON_FUNC_MASK;
        if (GPIOx > GPIO3)
            GPIOBANK1->DIR_SET = (uint32_t)(1 << ((GPIOx - 4) * 8 + GPIO_InitStruct->GPIO_Pin));
        else
            GPIOBANK0->DIR_SET = (uint32_t)(1 << ((GPIOx - 0) * 8 + GPIO_InitStruct->GPIO_Pin));
    }
    else
    {
        tmpreg &= ~IOCON_FUNC_MASK;
        tmpreg |= GPIO_InitStruct->GPIO_Mode;
    }

    /* GPIO Speed */
    tmpreg |= GPIO_InitStruct->GPIO_Speed << IOCON_SPEED_OFFSET;
    /* GPIO PuPd */
    tmpreg |= GPIO_InitStruct->GPIO_PuPd << IOCON_PUPD_OFFSET;
    /* GPIO IE and DR */
    tmpreg |= (IOCON_IE) | (0<<IOCON_DR_OFFSET);
    
    IOCON->CON = tmpreg;
}

/**
  * @brief  Configure GPIO analog function.
  * @param  GPIOx: where x can be (0..6) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be GPIO_Pin_x where x can be (0..7).
  * @param  NewState: new state of the specified GPIO analog function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_ANAConfig(uint32_t GPIOx, uint32_t GPIO_Pin, FunctionalState NewState)
{
	IOCON_TypeDef *IOCON;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
	IOCON = (IOCON_TypeDef *)(IOCON_BASE + (GPIOx * 8 + GPIO_Pin) * 4);
    
    if (NewState != DISABLE)
    {
        IOCON->CON |= IOCON_ANA;
    }
    else
    {
        IOCON->CON &= ~IOCON_ANA;
    }
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (0..6) to select the GPIO peripheral.
  * @retval GPIO data port value.
  */
uint8_t GPIO_ReadData(uint32_t GPIOx)
{
	uint32_t tmpreg;
	uint8_t Data;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    if (GPIOx > GPIO3)
	{
		tmpreg = GPIODATA1->DT;
		Data = (uint8_t)((tmpreg >> ((GPIOx - 4) * 8)) & 0xFF);
	}
	else
	{
		tmpreg = GPIODATA0->DT;
		Data = (uint8_t)((tmpreg >> (GPIOx * 8)) & 0xFF);
	}

	return Data;
}

/**
  * @brief  Reads the specified data port bit.
  * @param  GPIOx: where x can be (0..6) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadDataBit(uint32_t GPIOx, uint32_t GPIO_Pin)
{
	uint8_t bitstatus = 0x00;
	uint32_t tmpreg;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if (GPIOx > GPIO3)
	{
		tmpreg = GPIODATA1->DT;
		bitstatus = (uint8_t)((tmpreg >> ((GPIOx - 4) * 8 + GPIO_Pin)) & 1);
	}
	else
	{
		tmpreg = GPIODATA0->DT;
		bitstatus = (uint8_t)((tmpreg >> ((GPIOx - 0) * 8 + GPIO_Pin)) & 1);
	}

	return bitstatus;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (0..6) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be GPIO_Pin_x where x can be (0..7).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *          This parameter can be one of the BitAction enumeration values:
  *            @arg Bit_RESET: to clear the port pin
  *            @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(uint32_t GPIOx, uint32_t GPIO_Pin, BitAction BitVal)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
	assert_param(IS_GPIO_BIT_ACTION(BitVal));

	if (BitVal != Bit_RESET)
	{
        if (GPIOx > GPIO3)
        {
            GPIODATA1->DT_SET = (uint32_t)(1 << ((GPIOx - 4) * 8 + GPIO_Pin));
        }
		else
        {
            GPIODATA0->DT_SET = (uint32_t)(1 << ((GPIOx - 0) * 8 + GPIO_Pin));
        }
	}
	else
	{
        if (GPIOx > GPIO3)
        {
            GPIODATA1->DT_CLR = (uint32_t)(1 << ((GPIOx - 4) * 8 + GPIO_Pin));
        }
		else
        {
            GPIODATA0->DT_CLR = (uint32_t)(1 << ((GPIOx - 0) * 8 + GPIO_Pin));
        }
	}
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (0..6) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(uint32_t GPIOx, uint8_t PortVal)
{
	uint32_t tmpreg;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	if (GPIOx > GPIO3)
	{
		tmpreg = GPIODATA1->DT;
		tmpreg &= (uint32_t)(~(0x000000FF << (GPIOx % 4 * 8)));
		tmpreg |= (uint32_t)PortVal << (GPIOx % 4 * 8);
		GPIODATA1->DT = tmpreg;
	}
	else
	{
		tmpreg = GPIODATA0->DT;
		tmpreg &= (uint32_t)(~(0x000000FF << (GPIOx % 4 * 8)));
		tmpreg |= (uint32_t)PortVal << (GPIOx % 4 * 8);
		GPIODATA0->DT = tmpreg;
	}
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  SetVal: specifies the set value to be written to the port0 and port1 output data register.
  * @param  ClearVal: specifies the clear value to be written to the port0 and port1 output data register.
  * @retval None
  */
void GPIO_Write_Port0_1(uint16_t SetVal, uint16_t ClearVal)
{
    GPIOBSRR0->BSRR_LOW = (ClearVal<<16) | SetVal;
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  SetVal: specifies the set value to be written to the port2 and port3 output data register.
  * @param  ClearVal: specifies the clear value to be written to the port2 and port3 output data register.
  * @retval None
  */
void GPIO_Write_Port2_3(uint16_t SetVal, uint16_t ClearVal)
{
    GPIOBSRR0->BSRR_HIGH = (ClearVal<<16) | SetVal;
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  SetVal: specifies the set value to be written to the port4 and port5 output data register.
  * @param  ClearVal: specifies the clear value to be written to the port4 and port5 output data register.
  * @retval None
  */
void GPIO_Write_Port4_5(uint16_t SetVal, uint16_t ClearVal)
{
    GPIOBSRR1->BSRR_LOW = (ClearVal<<16) | SetVal;
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  SetVal: specifies the set value to be written to the port6 and port7 output data register.
  * @param  ClearVal: specifies the clear value to be written to the port6 and port7 output data register.
  * @retval None
  */
void GPIO_Write_Port6_7(uint16_t SetVal, uint16_t ClearVal)
{
    GPIOBSRR1->BSRR_HIGH = (ClearVal<<16) | SetVal;
}

/**
  * @brief  Configure GPIO filter function.
  * @param  Cycles: specifies the filter cycles to be written.
  *   This parameter can be (1..255).
  * @param  NewState: new state of the specified GPIO analog function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_FilterConfig(uint32_t Cycles, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_GPIO_FILTER_CYCLES(Cycles));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        GPIOFILTER->FILTER = GPIO_FILTER_ENABLE | Cycles;
    }
    else
    {
        GPIOFILTER->FILTER = (~GPIO_FILTER_ENABLE) | Cycles;
    }
}

/**
  * @brief  Enables or disables the specified GPIO interrupts.
  * @param  GPIOx: where x can be (0..10) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be GPIO_Pin_x where x can be (0..7).
  * @param  GPIO_IT: specifies the GPIO interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg GPIO_IT_EDGE_FALLING
  *            @arg GPIO_IT_EDGE_RISING
  *            @arg GPIO_IT_EDGE_DOUBLE
  *            @arg GPIO_IT_LEVEL_LOW
  *            @arg GPIO_IT_LEVEL_HIGH
  * @param  NewState: new state of the specified GPIO interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_ITConfig(uint32_t GPIOx, uint32_t GPIO_Pin, uint32_t GPIO_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
	assert_param(IS_GPIO_IT_ACTION(GPIO_IT)); 

	if (NewState != DISABLE)
	{
		if (GPIO_IT == GPIO_IT_EDGE_FALLING)
		{
            if (GPIOx > GPIO3)
			{
				GPIOBANK1->IS_CLR = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IBE_CLR = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IEV_CLR = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IE_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
			}
			else
			{
				GPIOBANK0->IS_CLR = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IBE_CLR = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IEV_CLR = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IE_SET = (1 << (GPIOx * 8 + GPIO_Pin));
			}
		}
		else if (GPIO_IT == GPIO_IT_EDGE_RISING)
		{
            if (GPIOx > GPIO3)
			{
				GPIOBANK1->IS_CLR = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IBE_CLR = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IEV_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IE_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
			}
			else
			{
				GPIOBANK0->IS_CLR = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IBE_CLR = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IEV_SET = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IE_SET = (1 << (GPIOx * 8 + GPIO_Pin));
			}
		}
		else if (GPIO_IT == GPIO_IT_EDGE_DOUBLE)
		{
            if (GPIOx > GPIO3)
			{
				GPIOBANK1->IS_CLR = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IBE_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IE_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
			}
			else
			{
				GPIOBANK0->IS_CLR = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IBE_SET = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IE_SET = (1 << (GPIOx * 8 + GPIO_Pin));
			}
		}
		else if (GPIO_IT == GPIO_IT_LEVEL_LOW)
		{
            if (GPIOx > GPIO3)
			{
				GPIOBANK1->IS_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IEV_CLR = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IE_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
			}
			else
			{
				GPIOBANK0->IS_SET = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IEV_CLR = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IE_SET = (1 << (GPIOx * 8 + GPIO_Pin));
			}
		}
		else if (GPIO_IT == GPIO_IT_LEVEL_HIGH)
		{
            if (GPIOx > GPIO3)
			{
				GPIOBANK1->IS_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IEV_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
				GPIOBANK1->IE_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
			}
			else
			{
				GPIOBANK0->IS_SET = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IEV_SET = (1 << (GPIOx * 8 + GPIO_Pin));
				GPIOBANK0->IE_SET = (1 << (GPIOx * 8 + GPIO_Pin));
			}
		}
	}
	else
	{
        if (GPIOx > GPIO3)
        {
            GPIOBANK1->IE_CLR = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
        }
		else
        {
			GPIOBANK0->IE_CLR = (1 << (GPIOx * 8 + GPIO_Pin));
        }
	}
}

/**
  * @brief  Checks whether the specified GPIO interrupt has occurred or not.
  * @param  GPIOx: where x can be (0..10) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval The new state of GPIO_IT (SET or RESET).
  */
ITStatus GPIO_GetITStatus(uint32_t GPIOx, uint32_t GPIO_Pin)
{
	ITStatus bitstatus = RESET;
	uint32_t enablestatus = 0;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

	/* Get the GPIO_IT enable bit status */
    if (GPIOx > GPIO3)
		enablestatus = (uint32_t)(GPIOBANK1->IE & (1 << ((GPIOx - 4) * 8 + GPIO_Pin)));
	else
		enablestatus = (uint32_t)(GPIOBANK0->IE & (1 << (GPIOx * 8 + GPIO_Pin)));

	/* Check the status of the specified GPIO interrupt */
    if (GPIOx > GPIO3)
	{
		if (((uint32_t)(GPIOBANK1->IRS & (1 << ((GPIOx - 4) * 8 + GPIO_Pin))) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
			bitstatus = SET;
		else
			bitstatus = RESET;
	}
	else
	{
		if (((uint32_t)(GPIOBANK0->IRS & (1 << (GPIOx * 8 + GPIO_Pin))) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
			bitstatus = SET;
		else
			bitstatus = RESET;
	}

	/* Return the GPIO_IT status */
	return  bitstatus;
}

/**
  * @brief  Clears the GPIO's interrupt pending bits.
  * @param  GPIOx: where x can be (0..10) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_ClearITPendingBit(uint32_t GPIOx, uint32_t GPIO_Pin)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if (GPIOx > GPIO3)
		GPIOBANK1->IC_SET = (1 << ((GPIOx - 4) * 8 + GPIO_Pin));
	else
		GPIOBANK0->IC_SET = (1 << (GPIOx * 8 + GPIO_Pin));
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

