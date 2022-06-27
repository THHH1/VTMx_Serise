/* Includes ------------------------------------------------------------------*/ 
{{app_c_include}}
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 

USB_CORE_HANDLE  USB_Device_dev ;
{{app_c_extern}}
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

    {{app_c_USBD_Init}}

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
