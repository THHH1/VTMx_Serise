/**
  ******************************************************************************
  * @file    usbd_pwr.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    10-09-2018
  * @brief   This file provides functions for power management
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
