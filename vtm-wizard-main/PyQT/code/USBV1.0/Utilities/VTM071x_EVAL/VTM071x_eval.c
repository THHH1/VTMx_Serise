/**
  ******************************************************************************
  * @file    VTM071x_eval.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides
  *            - low level initialization functions for SPI FLASH and serial EEPROM (sEE)
  *          available on VTM071x_EVAL evaluation board from MIC.
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
#include "VTM071x_eval.h"	

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup VTM071x_EVAL
  * @{
  */   

/** @defgroup VTM071x_EVAL_LOW_LEVEL 
  * @brief This file provides firmware functions to manage Leds, push-buttons, 
  *        COM ports, SPI FLASH and serial EEPROM (sEE) available on 
  *        VTM071x_EVAL evaluation board from MIC.
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/ 

/** @defgroup MT71x_EVAL_LOW_LEVEL_Private_Functions
  * @{
  */

/**
  * @brief  DeInitializes the SPI interface.
  * @retval None
  */
void SPI_FLASH_LowLevel_DeInit(SPI_TypeDef *SPIx)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 

	SPI_Cmd(SPIx, DISABLE);
	SPI_DeInit(SPIx);
	
    if (SPIx == SPI0)
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_SPI0, DISABLE);
	else
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_SPI1, DISABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO4, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIO5, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIO5, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIO5, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the SPI controller into StandBy State (Ready for 
  *         initialization).
  * @retval  0, okay; else, error.
  */
void SPI_FLASH_LowLevel_Init(SPI_TypeDef *SPIx)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	SPI_InitTypeDef   SPI_InitStructure;

    /* SPI clock */
    if (SPIx == SPI0)
    {
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_SPI0, ENABLE);
        RCC_SETCLKDivider(RCC_CLOCKFREQ_SPI0CLK, 2);
    }
	else
    {
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_SPI1, ENABLE);
        RCC_SETCLKDivider(RCC_CLOCKFREQ_SPI1CLK, 2);
    }

    /* SPI pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO4, &GPIO_InitStructure);
    GPIO_WriteBit(GPIO4, GPIO_Pin_3, Bit_SET);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO4, &GPIO_InitStructure);
    	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
	GPIO_Init(GPIO4, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
	GPIO_Init(GPIO4, &GPIO_InitStructure);

    /* Reset SPI */
	SPI_DeInit(SPIx);

	SPI_InitStructure.SPI_Mode        = SPI_MODE_MASTER;
	SPI_InitStructure.SPI_FirstBit    = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Direction   = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize    = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL        = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA        = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_Init(SPIx, &SPI_InitStructure);
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

/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT MIC *****END OF FILE****/
