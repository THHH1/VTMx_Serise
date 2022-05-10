/**
  ******************************************************************************
  * @file    usbd_pwr.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    10-28-2018
  * @brief   This file provides functions for power management
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
struct
{
  __IO RESUME_STATE eState;
  __IO uint8_t bESOFcnt;
}
ResumeS;

__IO uint32_t remotewakeupon=0;

extern void Delay_ms(uint32_t ms);

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Sets suspend mode operating conditions
  * @param  None
  * @retval USB_SUCCESS
  */
void Suspend(void)
{

}

/**
  * @brief  Handles wake-up restoring normal operations
  * @param  None
  * @retval USB_SUCCESS
  */
void Resume_Init(void)
{

}

void Remote_Wakeup(void)
{
    /* remote wakeup */
    SetPower(GetPower() | 0x4);
    Delay_ms(10);
    SetPower(GetPower() & (~0x4));
    
    /* No Resume interrupt will be generated when the software initiates a remote wakeup */
    USBD_DCD_INT_fops->Resume(&USB_Device_dev);
}


/**
  * @brief  Provides the state machine handling resume operations and
  *         timing sequence. The control is based on the Resume structure
  *         variables and on the ESOF interrupt calling this subroutine
  *         without changing machine state.
  * @param  a state machine value (RESUME_STATE)
  *         RESUME_ESOF doesn't change ResumeS.eState allowing
  *         decrementing of the ESOF counter in different states.
  * @retval Status
  */
void Resume(RESUME_STATE eResumeSetVal)
{
    
}

/**
  * @brief  Restores system clocks and power while exiting suspend mode
  * @param  None
  * @retval None
  */
void Leave_LowPowerMode(void)
{
    
}

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
