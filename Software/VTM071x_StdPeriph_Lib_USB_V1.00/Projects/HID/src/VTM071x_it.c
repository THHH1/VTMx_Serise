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
#include <stdio.h>

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CURSOR_STEP         5

#define BUTTON_LEFT_GPIO    GPIO6
#define BUTTON_LEFT_PIN     GPIO_Pin_3

#define BUTTON_RIGHT_GPIO   GPIO6
#define BUTTON_RIGHT_PIN    GPIO_Pin_1

#define BUTTON_UP_GPIO      GPIO6
#define BUTTON_UP_PIN       GPIO_Pin_0

#define BUTTON_DOWN_GPIO    GPIO6
#define BUTTON_DOWN_PIN     GPIO_Pin_2

#define BUTTON_PUSH_GPIO    GPIO5
#define BUTTON_PUSH_PIN     GPIO_Pin_7

#define BUTTON_LEFTCLICK_GPIO   GPIO1
#define BUTTON_LEFTCLICK_PIN    GPIO_Pin_4

#define BUTTON_RIGHTCLICK_GPIO  GPIO1
#define BUTTON_RIGHTCLICK_PIN   GPIO_Pin_3


typedef enum 
{ 
  JOY_NONE  = 0,
  JOY_SEL   = 1,
  JOY_DOWN  = 2,
  JOY_LEFT  = 3,
  JOY_RIGHT = 4,
  JOY_UP    = 5
} JOYState_TypeDef;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t remote_wakeup =0;
static uint8_t HID_Buffer [4];

volatile uint32_t Ticks_ms = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static uint8_t *USBD_HID_GetPos (void);

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

void Delay_ms(uint32_t ms)
{
    volatile uint32_t ticks = Ticks_ms + ms;
    
    while(Ticks_ms < ticks);
}

/**
  * @brief  This function sends the input report repeatedly.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    uint8_t *buf=HID_Buffer;

    Ticks_ms++;
        
//    /* Get Joystick position */
//    buf = USBD_HID_GetPos();

//    /* Update the cursor position */
//    if((buf[0] != 0) || (buf[1] != 0) || (buf[2] != 0))
//    {
//        /* Send Report */
//        USBD_HID_SendReport (&USB_Device_dev, buf, 4);
//    }


    /* TEST */
    static uint8_t flag = 0;
    uint8_t ret;
    
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;

    flag = !flag;
    if (flag)
        buf[1] += 4;
    else
        buf[1] -= 4;
    
    /* Update the cursor position */
    if((buf[0] != 0) || (buf[1] != 0) || (buf[2] != 0))
    {
        /* Send Report */
        ret = USBD_HID_SendReport (&USB_Device_dev, buf, 4);
        if (ret == USBD_BUSY)
        {
            flag = !flag;
        }
    }
    /* TEST */
}

/**
  * @brief  This function handles USB FS Handler.
  * @param  None
  * @retval None
  */
void USB_IRQHandler(void)
{
    USB_Isr();
}

/**
  * @brief  JoyState
  * @param  None
  * @retval The direction value
*/
uint8_t JoyState(void)
{
    /* "right" key is pressed */
    if (!GPIO_ReadDataBit(BUTTON_RIGHT_GPIO, BUTTON_RIGHT_PIN))
    {
        return JOY_RIGHT;
    }
    /* "left" key is pressed */
    if (!GPIO_ReadDataBit(BUTTON_LEFT_GPIO, BUTTON_LEFT_PIN))
    {
        return JOY_LEFT;
    }
    /* "up" key is pressed */
    if (!GPIO_ReadDataBit(BUTTON_UP_GPIO, BUTTON_UP_PIN))    
    {
        return JOY_UP;
    }
    /* "down" key is pressed */
    if (!GPIO_ReadDataBit(BUTTON_DOWN_GPIO, BUTTON_DOWN_PIN))
    {
        return JOY_DOWN;
    }
    
    if (!GPIO_ReadDataBit(BUTTON_PUSH_GPIO, BUTTON_PUSH_PIN))
    {
        return JOY_SEL;
    }
    /* No key is pressed */
    else
    {
        return 0;
    } 
}

static uint8_t *USBD_HID_GetPos (void)
{
    int8_t  x = 0 , y = 0;
    uint8_t sel = 0;
        
    switch (JoyState())
    {
        case JOY_LEFT:
            x -= CURSOR_STEP;
            break;  

        case JOY_RIGHT:
            x += CURSOR_STEP;
            break;

        case JOY_UP:
            y -= CURSOR_STEP;
            break;

        case JOY_DOWN:
            y += CURSOR_STEP;
            break;
        
        case JOY_SEL:
            sel |= 0x04;
            break;
        
        default:
            break;
    }
    
    if (GPIO_ReadDataBit(BUTTON_LEFTCLICK_GPIO, BUTTON_LEFTCLICK_PIN))
    {
        sel |= 0x01;
    }

    if (GPIO_ReadDataBit(BUTTON_RIGHTCLICK_GPIO, BUTTON_RIGHTCLICK_PIN))
    {
        sel |= 0x02;
    }
    
    HID_Buffer[0] = sel;
    HID_Buffer[1] = x;
    HID_Buffer[2] = y;
    HID_Buffer[3] = 0;
    
    return HID_Buffer;
}

/******************************************************************************/
/*                 MT0s71x Peripherals Interrupt Handlers                      */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_vtm071x.s).                                                  */
/******************************************************************************/

/**
  * @}
  */ 

/******************* (C) COPYRIGHT MIC  *****END OF FILE****/
