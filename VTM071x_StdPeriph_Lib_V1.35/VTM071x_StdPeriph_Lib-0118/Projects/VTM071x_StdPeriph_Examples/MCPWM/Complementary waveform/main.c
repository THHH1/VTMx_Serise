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
void USART_Configuration(void);
void MCPWM_Configuration(void);
void MCPWM_Stop(uint32_t MCPWM_Channel_COM);
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
/* MCPWM必须在一个周期结束后关闭，如果使能了Limit中断，那么关闭动作可以在中断中关闭 */
void MCPWM_Stop(uint32_t MCPWM_Channel_COM)
{
    /* 等待这个周期结束 */
    if (MCPWM_Channel_COM & MCPWM_CHANNEL_0)													
    {
        MCPWM->INTF_CLR = MCPWM_IT_ILIM0;
        while ((MCPWM->INTF & MCPWM_IT_ILIM0) == 0);
    }
    else if (MCPWM_Channel_COM & MCPWM_CHANNEL_1)
    {
        MCPWM->INTF_CLR = MCPWM_IT_ILIM1;
        while ((MCPWM->INTF & MCPWM_IT_ILIM1) == 0);
    }
    else if (MCPWM_Channel_COM & MCPWM_CHANNEL_2)
    {
        MCPWM->INTF_CLR = MCPWM_IT_ILIM2;
        while ((MCPWM->INTF & MCPWM_IT_ILIM2) == 0);
    }
    
    /* 关闭MCPWM */
    MCPWM_Cmd(MCPWM_Channel_COM, DISABLE);
}

void Delay_us(uint32_t us)
{
    SysTick->LOAD = us * 96;
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
    /* USART */
    USART_Configuration();
    printf("\r\n-----------------|- VTM071x MCPWM -|-----------------\r\n");    
    
    MCPWM_Configuration();
    
	while(1)
	{
        /* 延时100ms */
        Delay_ms(100);
        /* 三组MCPWM同相时可以同时关闭，否则需要一个个关闭 */
        MCPWM_Stop(MCPWM_CHANNEL_0 | MCPWM_CHANNEL_1 | MCPWM_CHANNEL_2);
        /* 延时100ms */
        Delay_ms(100);
        /* 开启三组MCPWM */
        MCPWM_Cmd(MCPWM_CHANNEL_0 | MCPWM_CHANNEL_1 | MCPWM_CHANNEL_2, ENABLE);
	}
}

/**
  * @brief  Configuare MCPWM.
  * @param  None
  * @retval None
  */
void MCPWM_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    MCPWM_InitTypeDef MCPWM_InitStructure;

    // MC0A0--GPIO2-6
    // MC0A1--GPIO2-0
    // MC0A2--GPIO2-1
    // MC0B0--GPIO3-1
    // MC0B1--GPIO3-2
    // MC0B2--GPIO3-3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;																		//GPIO2_6
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;													//频率高50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_2;															//备用功能模式2
    GPIO_Init(GPIO2, &GPIO_InitStructure);																			//GPIO2

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;																		//GPIO2_0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;															//备用功能模式1
    GPIO_Init(GPIO2, &GPIO_InitStructure);																			//GPIO2

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;																		//GPIO2_1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;															//备用功能模式1
    GPIO_Init(GPIO2, &GPIO_InitStructure);																			//GPIO2
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;																		//GPIO3_1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_3;															//备用功能模式3
    GPIO_Init(GPIO3, &GPIO_InitStructure);																			//GPIO3

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;																		//GPIO3_2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_3;															//备用功能模式3
    GPIO_Init(GPIO3, &GPIO_InitStructure);																			//GPIO3

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;																		//GPIO3_3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_3;															//备用功能模式3
    GPIO_Init(GPIO3, &GPIO_InitStructure);																			//GPIO3_3
												//
    /* MCPWM Clock */
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_MCPWM, ENABLE);												//使能MCPWM时钟
    MCPWM_DeInit();																															//初始化MCPWM

    /* Channel0 100KHz, Duty 60% */
    MCPWM_InitStructure.MCPWM_Channel = MCPWM_CHANNEL_0;												//通道0
    MCPWM_InitStructure.MCPWM_Match = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 * 2 - 1; //2us
    MCPWM_InitStructure.MCPWM_Limit = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 * 5 - 1; //5us
    MCPWM_InitStructure.MCPWM_DeadTime = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 / 2 - 1;  //0.5us
    MCPWM_InitStructure.MCPWM_Center = MCPWM_CENTER_CA;													//中心对齐边对齐
    MCPWM_InitStructure.MCPWM_Update = MCPWM_Update_EN;													//指定更新的参数
    MCPWM_InitStructure.MCPWM_Polarity = MCPWM_Polarity_ILAH;										//MCPWM极性
    MCPWM_Init(&MCPWM_InitStructure);																						//MCPWM

    /* Channel1 100KHz, Duty 40% */
    MCPWM_InitStructure.MCPWM_Channel = MCPWM_CHANNEL_1;												//通道1
    MCPWM_InitStructure.MCPWM_Match = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 * 3 - 1; //3us
    MCPWM_InitStructure.MCPWM_Limit = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 * 5 - 1; //5us
    MCPWM_InitStructure.MCPWM_DeadTime = 0;
    MCPWM_InitStructure.MCPWM_Center = MCPWM_CENTER_CA;													//中心对齐边对齐
    MCPWM_InitStructure.MCPWM_Update = MCPWM_Update_EN;													//指定更新的参数
    MCPWM_InitStructure.MCPWM_Polarity = MCPWM_Polarity_ILAH;										//MCPWM极性
    MCPWM_Init(&MCPWM_InitStructure);																						//MCPWM

    /* Channel2 200KHz, Duty 60% */
    MCPWM_InitStructure.MCPWM_Channel = MCPWM_CHANNEL_2;												//通道2
    MCPWM_InitStructure.MCPWM_Match = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 * 2 - 1; //2us
    MCPWM_InitStructure.MCPWM_Limit = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 * 5 - 1; //5us
    MCPWM_InitStructure.MCPWM_DeadTime = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 / 2 - 1;  //0.5us
    MCPWM_InitStructure.MCPWM_Center = MCPWM_CENTER_EA;													//中心对齐边对齐
    MCPWM_InitStructure.MCPWM_Update = MCPWM_Update_EN;													//指定更新的参数
    MCPWM_InitStructure.MCPWM_Polarity = MCPWM_Polarity_ILAH;										//MCPWM极性
    MCPWM_Init(&MCPWM_InitStructure);																						//MCPWM

    MCPWM_Cmd(MCPWM_CHANNEL_0 | MCPWM_CHANNEL_1 | MCPWM_CHANNEL_2, ENABLE);			//使能MCPWM通道0，MCPWM通道1，MCPWM通道2
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

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);												//使能USART0时钟
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);																//选取时钟源
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);								//设置时钟分频因子

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;																		//GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;													//频率高50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;															//备用功能模式1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;														//浮空输入
    GPIO_Init(GPIO1, &GPIO_InitStructure);																			//GPIO1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;																		//GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);																			//GPIO1

    USART_DeInit(USART0);																												//将USART0寄存器重置为默认值
    USART_StructInit(&USART_InitStructure);																			//将USART_InitStructure结构体变量成员按默认值填充
    USART_Init(USART0, &USART_InitStructure);																		//根据结构体的参数配置来对USART0外设进行初始化
    USART_Cmd(USART0, ENABLE);																									//使能USART0外设
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

