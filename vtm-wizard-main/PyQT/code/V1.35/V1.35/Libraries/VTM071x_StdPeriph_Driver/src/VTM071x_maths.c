/**
  ******************************************************************************
  * @file    VTM071x_maths.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides all the MATHS firmware functions.
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
#include "VTM071x_maths.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup MATHS
  * @brief MATHS driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup Maths_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the MATHS peripheral registers to their default reset values.
  * @retval None
  */
void MATHS_DeInit(void)
{
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL1_MATHS, ENABLE);
    RCC_APBPeriphResetCmd(RCC_PRESETCTRL1_MATHS, DISABLE);
}

/**
  * @brief  Initializes the MATHS peripheral according to the specified
  *   parameters in the Cordic_InitTypeDef.
  * @param  Cordic_InitStruct: pointer to a Cordic_InitTypeDef structure
  *   that contains the configuration information for the specified Cordic peripheral.
  * @retval None
  */
void Cordic_Init(Cordic_InitTypeDef* Cordic_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_CORDIC_DIV_K(Cordic_InitStruct->DIV_K));
    assert_param(IS_CORDIC_Bypass_Handle(Cordic_InitStruct->Bypass_Handle));  
    assert_param(IS_CORDIC_XYMRS_DIV(Cordic_InitStruct->XYMRS));
    assert_param(IS_CORDIC_MOD_V(Cordic_InitStruct->MOD_V));

    MATHS->CTRL = Cordic_InitStruct->DIV_K | Cordic_InitStruct->Bypass_Handle | \
                  Cordic_InitStruct->XYMRS | Cordic_InitStruct->MOD_V;
}

void Cordic_Go(uint32_t *in_xyz, uint32_t *out_xyz)
{
    MATHS->DATA_IN_X = in_xyz[0];
    MATHS->DATA_IN_Y = in_xyz[1];
    MATHS->DATA_IN_Z = in_xyz[2];
    
    MATHS->CTRL |= MATHS_CORDIC_CTRL_EN;
    
    /* Delay */
    /* TODO: 需要在最大倍频下，测得延时 */
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    
    out_xyz[0] = MATHS->DATA_IN_X;
    out_xyz[1] = MATHS->DATA_IN_Y;
    out_xyz[2] = MATHS->DATA_IN_Z;
}

/**
  * @brief  Checks whether the specified Cordic flag is set or not.
  * @param  Cordic_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg Cordic_FLAG_READY
  *     @arg Cordic_FLAG_OVF
  * @retval The new state of Cordic_FLAG (SET or RESET).
  */
FlagStatus Cordic_GetFlagStatus(uint32_t Cordic_FLAG)
{
    FlagStatus bitstatus = RESET;
  
    /* Check the parameters */
    assert_param(IS_Cordic_FLAG(Cordic_FLAG));
  
    if ((MATHS->STATUS & Cordic_FLAG) != RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    
    return bitstatus;
}

void CRC_WriteWord(uint32_t Value)
{
    MATHS->CRC_DR = Value;
}

void CRC_Reset(void)
{
    MATHS->CRC_CR = MATHS_CRC_CR_RESET;
}


/**
  * @brief  Initializes the MATHS peripheral according to the specified
  *   parameters in the Cordic_InitTypeDef.
  * @param  Division_InitStruct: pointer to a Division_InitTypeDef structure
  *   that contains the configuration information for the specified Division peripheral.
  * @retval None
  */
void Division_Init(Division_InitTypeDef* Division_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_Division_CHUSHU_SRC(Division_InitStruct->CHUSHU_SRC));
    assert_param(IS_Division_BEICHUSHU_SLC(Division_InitStruct->BEICHUSHU_SLC));  
    assert_param(IS_Division_SHANGCNT(Division_InitStruct->SHANGCNT));
    assert_param(IS_Division_SHANGDIR(Division_InitStruct->SHANGDIR));
    assert_param(IS_Division_UNSIGN(Division_InitStruct->USIGN));
    assert_param(IS_Division_STMODE(Division_InitStruct->STMODE));

    MATHS->DIV_CTRL = Division_InitStruct->BEICHUSHU_SLC | Division_InitStruct->CHUSHU_SRC | \
                      Division_InitStruct->SHANGCNT | Division_InitStruct->SHANGDIR | \
                      Division_InitStruct->STMODE | Division_InitStruct->USIGN;
}

void DIV_SetDividend(uint32_t Dividend)
{
    MATHS->DIV_BEICHUSHU = Dividend;
}

void DIV_SetDivisor(uint32_t Divisor)
{
    MATHS->DIV_CHUSHU = Divisor;
}

uint32_t DIV_GetQuotient(void)
{
    return MATHS->DIV_SHANG;
}

uint32_t DIV_GetRemainder(void)
{
    return MATHS->DIV_YUSHU;
}

/**
  * @brief  Enables division.
  * @retval None
  */
void DIV_Start(void)
{
    MATHS->DIV_CTRL |= MATHS_DIV_CTRL_START;
}

/**
  * @brief  Enables or disables the specified MATHS interrupts.
  * @param  DIV_IT: specifies the USART interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg Division_IT_ZEROERR
  *     @arg Division_IT_DONE
  * @param  NewState: new state of the specified DIV interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DIV_ITConfig(uint32_t DIV_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_Division_IT(DIV_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        MATHS->DIV_IRQ |= DIV_IT;
    }
    else
    {
        MATHS->DIV_IRQ &= ~DIV_IT;
    }
}

/**
  * @brief  Checks whether the specified MATHS interrupt has occurred or not.
  * @param  DIV_IT_FLAG: specifies the MATHS interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg Division_IT_FLAG_ZEROERR
  *     @arg Division_IT_FLAG_DONE
  * @retval The new state of DIV_IT_FLAG (SET or RESET).
  */
ITStatus DIV_GetITStatus(uint32_t DIV_IT_FLAG)
{
    ITStatus bitstatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_Division_GET_IT_FLAG(DIV_IT_FLAG));

    if((MATHS->DIV_IRQ & (DIV_IT_FLAG >> 16)) && (MATHS->DIV_IRQ & DIV_IT_FLAG))
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
  * @brief  Checks whether the specified DIV flag is set or not.
  * @param  DIV_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg Division_FLAG_BUSY
  * @retval The new state of DIV_FLAG (SET or RESET).
  */
FlagStatus DIV_GetFlagStatus(uint32_t DIV_FLAG)
{
    FlagStatus bitstatus = RESET;
  
    /* Check the parameters */
    assert_param(IS_Division_FLAG(DIV_FLAG));
  
    if ((MATHS->DIV_STATUS & DIV_FLAG) != RESET)
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
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT MIC *****END OF FILE****/
