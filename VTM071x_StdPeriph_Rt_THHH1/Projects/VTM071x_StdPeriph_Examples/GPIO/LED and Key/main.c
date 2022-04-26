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
#define USART0_CLOCK_DIV	1		//将USART0_CLOCK_DIV定义为宏“1”

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t systick_ms = 0;		//
volatile uint32_t led_half_period = 30;		//

/* Private function prototypes -----------------------------------------------*/
void USART_Configuration(void);		//配置USART
void GPIO_Configuration(void);		//配置GPIO

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Configuare GPIO.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;																						//构建结构体USART_InitStructure
    
    /* LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;																				//构建结构体USART_InitStructure
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;															//设置频率为50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;																		//设置模式为输出模式
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;																//设置模式为浮空输入模式
    GPIO_Init(GPIO6, &GPIO_InitStructure);																					//GPIO6_4
    
    /* LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;																				//使能GPIO_Pin_5
    GPIO_Init(GPIO6, &GPIO_InitStructure);																					//GPIO6_5
    
    /* Key */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;																				//使能GPIO1_0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;															//设置频率为50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;																		//设置模式为输入模式
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;																	//设置模式为输入下拉模式
    GPIO_Init(GPIO1, &GPIO_InitStructure);																					//GPIO1_0
    
    NVIC_EnableIRQ(GPIO0_TO_GPIO3_IRQn);																						//中断

    GPIO_ITConfig(GPIO1, GPIO_Pin_0, GPIO_IT_EDGE_RISING, ENABLE);									//指定GPIO1_0 启用中断
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
    uint32_t systickclk = 0;																												//变量systickclk为0
    
    /* USART */
    USART_Configuration();																													//配置USART
    printf("\r\n-----------------|- VTM071x StdPeriph -|-----------------\r\n");			//输出打印
    
    /* SYSTICK */
	systickclk = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 2000;										//将片上时钟的速率除以1000，并赋值给systickclk，控制输出速度
    SysTick_Config(systickclk);																											

    GPIO_Configuration();																														//配置USART
    
	while(1)																																					//无限循环
	{
        systick_ms = led_half_period;
        while(systick_ms);
        GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_SET);																	//使能GPIO6_4
        GPIO_WriteBit(GPIO6, GPIO_Pin_5, Bit_SET);																	//使能GPIO6_5
        systick_ms = led_half_period;	
        while(systick_ms);																													
        GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_RESET);																//关闭LED灯GPIO6_4
        GPIO_WriteBit(GPIO6, GPIO_Pin_5, Bit_RESET);																//关闭LED灯GPIO6_5
	}
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;																					//结构体
    GPIO_InitTypeDef GPIO_InitStructure;																						//结构体
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);														//使能USART0时钟
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);																		//选取时钟源
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);										//设置时钟分频因子

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;																				//GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;															//频率高50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;																	//备用功能模式1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;																//浮空输入
    GPIO_Init(GPIO1, &GPIO_InitStructure);																					//GPIO1_1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;																				//GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);																					//GPIO1

    USART_DeInit(USART0);																														//将USART0寄存器重置为默认值
    USART_StructInit(&USART_InitStructure);																					//将USART_InitStructure结构体变量成员按默认值填充
    USART_Init(USART0, &USART_InitStructure);																				//根据结构体的参数配置来对USART0外设进行初始化
    USART_Cmd(USART0, ENABLE);																											//使能USART0外设
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

