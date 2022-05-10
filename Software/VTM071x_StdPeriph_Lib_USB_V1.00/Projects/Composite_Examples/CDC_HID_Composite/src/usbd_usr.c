/**
  ******************************************************************************
  * @file    usbd_usr.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    10-09-2018
  * @brief   This file contains user callback structure for USB events Management
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_usr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address    0x40012440

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USBD_Usr_cb_TypeDef USR_cb =
{
  USBD_USR_Init,
  USBD_USR_DeviceReset,
  USBD_USR_DeviceConfigured,
  USBD_USR_DeviceSuspended,
  USBD_USR_DeviceResumed,   
};

uint32_t ADC_ConvertedValueX = 0;
uint32_t ADC_ConvertedValueX_1 = 0;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Device lib initialization
  * @param  None
  * @retval None
  */
void USBD_USR_Init(void)
{   
    /* SysTick used for periodic check mouse position */
    SysTick_Config(SystemCoreClock / 125);
}

/**
  * @brief  Reset Event
  * @param  speed : device speed
  * @retval None
  */
void USBD_USR_DeviceReset(uint8_t speed )
{
}

/**
  * @brief  Configuration Event
  * @param  None
    * @retval Status
  */
void USBD_USR_DeviceConfigured (void)
{
}

/**
  * @brief  Device suspend Event
  * @param  None
  * @retval None
  */
void USBD_USR_DeviceSuspended(void)
{
}


/**
  * @brief  Device resume Event
  * @param  None
  * @retval None
  */
void USBD_USR_DeviceResumed(void)
{
}

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
