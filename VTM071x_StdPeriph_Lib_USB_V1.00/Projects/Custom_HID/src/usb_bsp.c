/**
  ******************************************************************************
  * @file    usb_bsp.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    10-28-2018
  * @brief   This file Provides Device Core configuration Functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usb_bsp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

void delay(uint32_t n)
{
    int i;
    
    for (i=0; i<n; i++)
        __nop();
}

/**
  * @brief  Initialize BSP configurations
  * @param  None
  * @retval None
  */
void USB_BSP_Init(USB_CORE_HANDLE *pdev)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Key Initialization */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIO2, &GPIO_InitStructure);

    /* Led Initialization */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_Init(GPIO6, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIO6, &GPIO_InitStructure);
    
    /* USB Initialization */
    /* power on usb_pll */
    RCC->PDRUNCFG = RCC->PDRUNCFG & (~(1<<10));
    /* open usb_pll clk */
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USB, ENABLE);
    /* Reset usb */
    RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_USB, ENABLE);
#if 1
    delay(300000); //delay 10ms, plug detect
#else
    #warning "Delay 10ms, plug detect"
#endif
    RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_USB, DISABLE);
}

void USB_BSP_DevConnect(void)
{
    
}

/**
  * @brief  Enable USB Global interrupt
  * @param  None
  * @retval None
  */
void USB_BSP_EnableInterrupt(USB_CORE_HANDLE *pdev)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the USB interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USB_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


/************************ (C) COPYRIGHT MIC *****END OF FILE****/
