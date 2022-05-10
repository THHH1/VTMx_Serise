/**
  ******************************************************************************
  * @file    Project/VTM071x_StdPeriph_Templates/main.c 
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   Main program body
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
#include <stdio.h>
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USART0_CLOCK_DIV	1
#define CLOCK_PER_US        (SystemCoreClock / 1000000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void USART_Configuration(void);
void Toggle_LED(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/* Private functions ---------------------------------------------------------*/
void Toggle_LED(void)
{
    static int flag = 1;
    
    if (flag)
        GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_SET);
    else
        GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_RESET);

    flag = !flag;
}

void Delay_us(uint32_t us)
{
    SysTick->LOAD = us * CLOCK_PER_US;
    SysTick->VAL  = (0x00);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Waiting for down-count to zero */
    while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
}

void Delay_ms(uint32_t ms)
{
    int i;
    
    for (i=0; i<ms; i++)
    {
        Delay_us(1000);
    }
}
    
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO6, &GPIO_InitStructure);
    GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_SET);

    /* USART */
    USART_Configuration();
    printf("\r\n-----------------|- VTM071x WWDG Reset -|-----------------\r\n");

    /* WWDG Clock */
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_WWDG, ENABLE);
    
    /* DeInit */
    WWDG_DeInit();

    /* WWDG clock counter = (AHB (84MHz)/16384)/8 = 641.4Hz (~1.56 ms)  */
    WWDG_SetPrescaler(WWDG_Prescaler_8);

    /* Set Window value to 80; WWDG counter should be refreshed only when the counter
    is below 80 (and greater than 64) otherwise a reset will be generated */
    WWDG_SetWindowValue(80);

    /* Enable WWDG and set counter value to 127, WWDG timeout = ~1.56 ms * 64 = 99.84 ms 
       In this case the refresh window is: 
       ~1.56 ms * (127-80) = 73.32ms < refresh window < ~1.56 ms * 64 = 99.84 ms 
    */
    WWDG_Enable(127);

    while (1)
    {
        Toggle_LED();
        
        Delay_ms(80);

        /* Update WWDG counter */
        WWDG_SetCounter(127);
    }
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO1, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIO1, &GPIO_InitStructure);

    USART_DeInit(USART0);
    USART_StructInit(&USART_InitStructure);
    USART_Init(USART0, &USART_InitStructure);
    USART_Cmd(USART0, ENABLE);
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART0, (uint8_t) ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART0, USART_FLAG_TXFE) == RESET)
    {}

    return ch;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

