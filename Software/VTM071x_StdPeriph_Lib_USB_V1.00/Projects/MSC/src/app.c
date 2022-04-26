/**
  ******************************************************************************
  * @file    app.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    08-01-2018
  * @brief   This file provides all the Application firmware functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/ 
#include  "usbd_msc_core.h"
#include  "usbd_usr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USB_CORE_HANDLE  USB_Device_dev ;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Program entry point
  * @param  None
  * @retval None
  */
int main(void)
{  
    /* The Application layer has only to call USBD_Init to 
    initialize the USB low level driver, the USB device library, the USB clock 
    ,pins and interrupt service routine (BSP) to start the Library*/

    USBD_Init(&USB_Device_dev,
              &USR_desc, 
              &USBD_MSC_cb, 
              &USR_cb);

    while (1)
    {
    }
} 

#ifdef USE_FULL_ASSERT
/**
  * @brief  assert_failed
  *         Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  File: pointer to the source file name
  * @param  Line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {}
}
#endif

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
