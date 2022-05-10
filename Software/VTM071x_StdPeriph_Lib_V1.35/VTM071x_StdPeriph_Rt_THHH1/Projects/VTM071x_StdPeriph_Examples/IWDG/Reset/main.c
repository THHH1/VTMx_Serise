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
uint32_t mcpwm_ch0_val[32];

/* Private function prototypes -----------------------------------------------*/
void Toggle_LED(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void USART_Configuration(void);

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
    GPIO_InitTypeDef GPIO_InitStructure;																						//结构体

    /* LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;																				//GPIO6_4
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;															//频率高50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;																		//输出模式
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;																//浮空输入
    GPIO_Init(GPIO6, &GPIO_InitStructure);																					//GPIO6
    GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_SET);																			//GPIO6_4置为1
    
    /* USART */
    USART_Configuration();																													//配置USART
    printf("\r\n-----------------|- VTM071x IWDG Reset -|-----------------\r\n");		//输出打印

    /* IWDG Clock */
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_IWDG, ENABLE);															//使能IWDG时钟
    
    /* IWDG timeout equal to 250 ms (the timeout may varies due to 10K frequency
     dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);																		//启用IWDG_PR和IWDG_RLR寄存器的写入访问。

    /* IWDG counter clock: 10K/4 */
    IWDG_SetPrescaler(IWDG_Prescaler_4);																						//设置IWDG预分频器值

    /* Set counter reload value to obtain 250ms IWDG TimeOut.
     Counter Reload Value = 250ms/IWDG counter clock period
                          = 250ms / (10000/4)
                          = 0.25s / (10000/4)
                          = 10000/(4 * 4)
                          = 10000/16
    */
    IWDG_SetReload(10000/16);																												//设置 IWDG 重载值

    /* Reload IWDG counter */
    IWDG_ReloadCounter();																														//重新加载IWDG计数器

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();																																	//启用IWDG

    while (1)																																				//无限循环
    {
        /* Toggle LED */
        Toggle_LED();																																//
        
        /* Insert 220 ms delay */
        Delay_ms(220);

//        /* Insert 280 ms delay , Reset */
//        Delay_ms(280);

        /* Reload IWDG counter */
        IWDG_ReloadCounter();  																											//重新加载 IWDG 计数器
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
    GPIO_Init(GPIO1, &GPIO_InitStructure);																					//GPIO1
	
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

