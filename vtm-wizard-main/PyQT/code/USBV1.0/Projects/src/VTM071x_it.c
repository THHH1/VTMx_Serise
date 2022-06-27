
/* Includes ------------------------------------------------------------------*/
#include "VTM071x_it.h"
#include <stdio.h>

{{VTM071x_it_c_define}}
{{VTM071x_it_c_var}}
{{VTM071x_it_c_function}}

void NMI_Handler(void)
{

}

void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}


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


void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}


void PendSV_Handler(void)
{
}


{{VTM071x_it_c_Delay_ms}}
void SysTick_Handler(void)
{   
    {{VTM071x_it_c_SysTick_Handler}}
}


void USB_IRQHandler(void)
{
    USB_Isr();
}

{{VTM071x_it_c_funbody}}

