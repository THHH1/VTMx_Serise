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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART_Configuration(void);																									//建立变量USART

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
    /* USART */
    USART_Configuration();																											//配置USART
    printf("\r\n-----------------|- VTM071x USART -|-----------------\r\n");			//输出打印
    
    while(1)																																		//无限循环
    {}
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;																			//结构体
    GPIO_InitTypeDef GPIO_InitStructure;																				//结构体

    /* Enable USART0 IRQ */
    NVIC_EnableIRQ(USART0_IRQn);																								//使能USART0中断请求

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);												//启用RCC外设时钟
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);																//选取时钟源（选取时钟源有要求么p27）
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);								//设置时钟分频器系数
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;																		//使能GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;													//输出频率50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;															//复用功能1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;														//浮空输入
    GPIO_Init(GPIO1, &GPIO_InitStructure);																			//结构体

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;																		//使能GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);																			//结构体

    USART_DeInit(USART0);																												//将USART寄存器重置为默认值
    USART_StructInit(&USART_InitStructure);																			//将USART_InitStructure结构体变量成员按默认值填充
    USART_Init(USART0, &USART_InitStructure);																		//根据结构体的参数配置来对USART外设进行初始化
		
    /* Enable USART0 RX and Receive timeout irq */
    USART_ITConfig(USART0, USART_IT_RXIEN, ENABLE);															//启用USART_IT_RXIEN中断源
    USART_RXTOCountConfig(USART0, 20);																					//配置 RXTO 计数
    USART_ITConfig(USART0, USART_IT_RXTOEN, ENABLE);														//启用USART_IT_RXTOEN中断源
    USART_Cmd(USART0, ENABLE);																									//使能USART外设
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
    USART_SendData(USART0, (uint8_t) ch);		//-

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

