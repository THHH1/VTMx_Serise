/**
  ******************************************************************************
  * @file    Project/VTM071x_StdPeriph_Templates/VTM071x_it.c 
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "VTM071x_it.h"
#include "VTM071x_dac.h"
#include <stdio.h>

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint16_t dac0_val = 0;
volatile uint16_t dac1_val = 4095;

/* Private function prototypes -----------------------------------------------*/
void ACMP_IRQHandler(void);

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{

}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    static uint32_t flag = 0;

    DAC_SetData(DAC0, dac0_val);
    DAC_SetData(DAC1, dac1_val);
    
    if (flag == 0)
    {
        dac0_val ++;
        dac1_val --;
        if (dac0_val == 4095)
            flag = 1;
    }
    else
    {
        dac0_val --;
        dac1_val ++;
        if (dac0_val == 0)
            flag = 0;
    }
}

/******************************************************************************/
/*                 VTM071x Peripherals Interrupt Handlers                      */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_VTM071x.s).                                                  */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
void ACMP_IRQHandler(void)
{
    uint32_t val0 = dac0_val, val1 = dac1_val;
    
    if (ACMP_GetITStatus(ACMP2) == SET)
    {
        ACMP_ClearITPendingBit(ACMP2);
        
        if (ACMP_GetResult(ACMP2) == SET)
        {
            printf("POS > NEG \r\n");
            printf("dac0_val: %d, dac1_val: %d. \r\n", val0, val1);
        }
        else
        {
            printf("POS < NEG \r\n");
            printf("dac0_val: %d, dac1_val: %d. \r\n", val0, val1);
        }
    }
}

/**
  * @}
  */ 

/******************* (C) COPYRIGHT MIC  *****END OF FILE****/
