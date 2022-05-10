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
#define ADC_CLKDIV	        60

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t systick_ms = 0;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART_Configuration(void);											                    //变量USART_Configuration
void ADC_Configuration(void);                                           //变量ADC_Configuration

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
   	uint32_t systickclk;																								//变量systickclk

    /* USART */																													
    USART_Configuration();																							//配置USART
	printf("\r\n-----------------|- VTM071x ADC -|-----------------\r\n");	//输出打印

    /* SYSTICK */
	systickclk = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000;				//将片上时钟的速率除以1000，并赋值给systickclk，控制输出速度,	除数“1000”可以修改且值与输出速度成正比
    SysTick_Config(systickclk);

    /* ADC */
	ADC_Configuration();																									//配置ADC

	while(1)																															//无限循环
	{
        /* Conversion per 200ms */
		ADC_StartOfConversion();																						//开始转换																				

        systick_ms = 200;																								//每200ms进行转换	
        while(systick_ms){}
	}
}

/**
  * @brief  Configuare ADC.
  * @param  None
  * @retval None
  */
void ADC_Configuration(void)																						//变量ADC_Configuration				  
{
    uint32_t delay=0;																				
	ADC_InitTypeDef ADC_InitStructure;																		//结构体
	NVIC_InitTypeDef NVIC_InitStructure;																	//结构体
    
    /* Enable ADC interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;                        //使能ADC_IRQn通道
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;												//指定IRQ通道优先级为0（值在0-3之间）
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;												//使能NVIC_IRQChannel中定义的IRQ通道
	NVIC_Init(&NVIC_InitStructure);																				//初始化NVIC
	
    /* PownOn ADC Analog switch */
	RCC_PDRUNConfig(RCC_PDCFG_ADC, RCC_PDCFG_POWER_ON);										//使能RCC_PDCFG_ADC！！！！！
    
    /* ADC clock -- Main clock / (ADC_CLKDIV * 14) = 100K */
	RCC_SETCLKDivider(RCC_CLOCKFREQ_ADCCLK, ADC_CLKDIV);									//设置时钟分频因子
    
    /* PowerOn ADC clock */
	RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_ADC, ENABLE);              			//使能ADC时钟
    
    /* DeInit */
	ADC_DeInit();                                                         //将ADC外设寄存器初始化为其默认重置值

    /* Initialize */
	ADC_StructInit(&ADC_InitStructure);                                   //将默认值填充每个ADC_InitStruct成员
    ADC_InitStructure.ADC_Discard0 = ADC_Discard0_1;                    //指定首次转换时丢弃的值
	ADC_Init(&ADC_InitStructure);                                         //初始化ADC
    
    /* Discontinuous mode */
	ADC_DiscModeCmd(ENABLE);																							//为所选通道启用间断模式
    
    /* Cover previous data */
	ADC_OverrunModeCmd(ENABLE);																						//为所选通道启用溢出模式
    
    /* Temperature Sensor must be enabled before ADC channel*/
    ADC_TempSensorCmd(ENABLE);                                          //使能温度传感器通道
    
    /* Delay ms */
	for (delay=0; delay<0x2000; delay++);                                 //for循环
    
    /* Enable channle 15 */
	ADC_ChannelConfig(ADC_Channel_15);                                    //使能channle 15
    
    /* Delay ms */
	for (delay=0; delay<0x2000; delay++);
    
    /* ADC EOC interrupt */
	ADC_ITConfig(ADC_IT_EOC, ENABLE);																			//使能ADC_IT_EOC（转换结束）中断
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;												  	  //结构体
    GPIO_InitTypeDef GPIO_InitStructure;                                //结构体                             

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);						  	//使能USART0时钟
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);											  //选取时钟源
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);			  //设置时钟分频因子

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;													  //GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;								  //频率高50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;                      //备用功能模式1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                    //浮空输入
    GPIO_Init(GPIO1, &GPIO_InitStructure);                              //GPIO1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                           //GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);                              //GPIO1

    USART_DeInit(USART0);                                               //将USART0寄存器重置为默认值	
    USART_StructInit(&USART_InitStructure);                             //将USART_InitStructure结构体变量成员按默认值填充
    USART_Init(USART0, &USART_InitStructure);                           //根据结构体的参数配置来对USART0外设进行初始化
    USART_Cmd(USART0, ENABLE);                                          //使能USART0外设
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

