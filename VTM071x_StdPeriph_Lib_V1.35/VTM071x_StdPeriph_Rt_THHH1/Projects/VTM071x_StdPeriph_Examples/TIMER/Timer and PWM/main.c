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
#include <math.h>
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USART0_CLOCK_DIV	1
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t timer_ms = 0;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART_Configuration(void);
void Timer_Configuration(void);
void Timer_Init(TIMER_TypeDef* TIMERx, uint32_t Prescale);
void Timer_Config(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t us);
void PWM_Standby(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Period, uint32_t Duty_t, uint32_t Mode);
void PWM_OutDuty(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Period, uint32_t Duty, uint32_t Mode);
void PWM0_CH1_OutDuty(uint32_t Period, uint32_t Duty);
void PWM_OutCount(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Count);
void PWM_Start(TIMER_TypeDef* TIMERx, uint32_t Channel);
void PWM_Stop(TIMER_TypeDef* TIMERx, uint32_t Channel);
void Delay_ms(uint32_t ms);
void TIMER0_IRQHandler(void);

/* Private functions ---------------------------------------------------------*/

/*
 * 函数简介：定时器模块初始化，打开时钟，复位通道
 * 函数参数：TIMERx  -- 定时器模块，可以为TIMER0,TIMER1,TIMER2,TIMER3
 *           Prescale-- 定时器模块预分频
 * 返 回 值：无
 * 注意事项：Prescale推荐值为1，这样可以获得最高的分辨率，对于高频率PWM可以获得最高的精确度
*/
void Timer_Init(TIMER_TypeDef* TIMERx, uint32_t Prescale)
{
    /* 打开TIMER的时钟 */
    if (TIMERx == TIMER0)
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_TIMER0, ENABLE);
    else if (TIMERx == TIMER1)
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_TIMER1, ENABLE);
    else if (TIMERx == TIMER2)
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_TIMER2, ENABLE);
    else
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_TIMER3, ENABLE);

    /* 复位该TIMER的4个通道 */
    TIMER_DeInit(TIMERx);

    /* 写入到寄存器的值为Prescale-1 */
    TIMER_SetPrescale(TIMERx, Prescale - 1);
}

/*
 * 函数简介：生成一个定时器
 * 函数参数：TIMERx -- 定时器模块，可以为TIMER0,TIMER1,TIMER2,TIMER3
 *           Channel-- 定时器通道，可以为Timer_Channel_0,Timer_Channel_1,Timer_Channel_2,Timer_Channel_3
 *           us     -- 定时器时间，单位为微秒
 * 返 回 值：无
 * 注意事项：当PR寄存器为0时，us必须小于0xFFFFFFFF / AHB时钟(单位M) * (PR+1)，这里以96M为例，不大于44739242
*/
void Timer_Config(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t us)
{
    TIMER_InitTypeDef TIMER_InitStructure;

    /* 除以分频系数 */
    us = us / (TIMER_GetPrescale(TIMERx) + 1);     

    /* 越界处理 */
    if (us > 44739242)
        us = 44739242;

    TIMER_InitStructure.TIMER_Channel = Channel;		                                    //通道
    TIMER_InitStructure.TIMER_Dir = TIMER_DIR_INCREASE;		                                //向上计数
    TIMER_InitStructure.TIMER_MatchValue = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 * us - 1;  //匹配值设置为AHBCLK-1，定时器周期为1MS
    TIMER_InitStructure.TIMER_MatchAction = TIMER_MatchAction_HOLD;                         //TC与MR匹配时，输出管脚MAT电平不变
    TIMER_InitStructure.TIMER_MatchConfig = TIMER_MatchConfig_RESET_TC;                     //TC与MR匹配时，复位TC
    TIMER_Init(TIMERx, &TIMER_InitStructure);                                               //初始化
    TIMER_ITConfig(TIMERx, TIMER_IT_MR0I, ENABLE);                                          //产生匹配中断
    
    TIMER_Cmd(TIMERx, Channel, ENABLE);
}

/*
 * 函数简介：配置PWM发生器
 * 函数参数：TIMERx -- 定时器模块，可以为TIMER0,TIMER1,TIMER2,TIMER3
 *           Channel-- 定时器通道，可以为Timer_Channel_0,Timer_Channel_1,Timer_Channel_2,Timer_Channel_3
 *           Period -- PWM周期，单位为AHB时钟(SystemCoreClock)的倒数，然后再乘以(PR+1)，例如48M，PR寄存器为4，单位为1/9600000秒，PR越大，分辨率越低
 *           Duty_t -- PWM占空比，单位为AHB时钟(SystemCoreClock)的倒数，然后再乘以(PR+1)，例如48M，PR寄存器为9，单位为1/4800000秒，PR越大，分辨率越低
 *           Mode   -- PWM模式，模式0(PWM_MODE_0)：默认状态为低电平，PWM先输出低再输出高电平
 *                              模式1(PWM_MODE_1)：默认状态为高电平，PWM先输出高再输出低电平
 * 返 回 值：无
 * 注意事项：1、SystemCoreClock时钟不同，参数Period和Duty的单位也不同
 *           2、调用该函数前需要先将指定的PWM管脚配置为PWM功能
 *           3、Duty不能等于0或Period，输出0%和100%的占空比可以将PWM管脚设置为GPIO模式，输出低电平或高电平,
 *              或者使用PWM_Stop函数关闭PWM功能，然后调用TIMER_SetIdleLevel设置默认电平。
 *           4、如果需要较高频率的PWM，建议预分频设置为1(Timer_Init中的Prescale)
*/
#define PWM_MODE_0      (0UL)
#define PWM_MODE_1      (1UL)
void PWM_Standby(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Period, uint32_t Duty_t, uint32_t Mode)
{
    PWM_InitTypeDef PWM_InitStructure;

    if (Mode == PWM_MODE_0)
    {
        TIMER_SetIdleLevel(TIMERx, Channel, Timer_IDLE_LEVEL_LOW);  //默认状态为低电平
        TIMER_SetMatchDefaultLevel(TIMERx, Channel, Timer_MATCH_DEFAULT_LEVEL_LOW);  //默认状态为低电平
        PWM_InvertCmd(TIMERx, Channel, DISABLE);                    //PWM先低后高
        Duty_t = Period - Duty_t;
    }
    else
    {
        TIMER_SetIdleLevel(TIMERx, Channel, Timer_IDLE_LEVEL_HIGH); //默认状态为高电平
        TIMER_SetMatchDefaultLevel(TIMERx, Channel, Timer_MATCH_DEFAULT_LEVEL_HIGH);  //默认状态为高电平
        PWM_InvertCmd(TIMERx, Channel, ENABLE);                     //PWM先高后低
    }

    PWM_InitStructure.TIMER_Channel = Channel;                          //通道
    PWM_InitStructure.PWM_Threshold = Duty_t - 1;                       //占空比
    PWM_InitStructure.PWM_MatchValue = Period - 1;                      //周期
    PWM_InitStructure.PWM_ValidState = PWM_ValidState_HIGH_LEVEL;       //有效电平为高电平
    PWM_InitStructure.PWM_InvalidState = PWM_InvalidState_LOW_LEVEL;    //无效电平为低电平
    PWM_Init(TIMERx, &PWM_InitStructure);                               //初始化
}

/*
 * 函数简介：PWM输出占空比
 * 函数参数：TIMERx  -- 定时器模块，可以为TIMER0,TIMER1,TIMER2,TIMER3
 *           Channel -- 定时器通道，可以为Timer_Channel_0,Timer_Channel_1,Timer_Channel_2,Timer_Channel_3
 *           Period  -- PWM周期，单位为AHB时钟(SystemCoreClock)的倒数，然后再乘以(PR+1)，例如48M，PR寄存器为4，单位为1/9600000秒，PR越大，分辨率越低
 *           Duty    -- PWM占空比，0表示低电平，1表示千分之一，999表示千分之九百九十九，1000表示高电平
 *           Mode    -- PWM模式，模式0(PWM_MODE_0)：默认状态为低电平，PWM先输出低再输出高电平
 *                              模式1(PWM_MODE_1)：默认状态为高电平，PWM先输出高再输出低电平
 * 返 回 值：无
 * 注意事项：已知TIMERx，Channel，PWM Mode，可以简化函数，如PWM0_CH1_OutDuty
*/
void PWM_OutDuty(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Period, uint32_t Duty, uint32_t Mode)
{
    if (Mode == PWM_MODE_0)
    {
        if (Duty == 0)
        {
            TIMER_SetIdleLevel(TIMERx, Channel, Timer_IDLE_LEVEL_LOW);  //默认状态为低电平
            TIMER_Cmd(TIMERx, Channel, DISABLE);
        }
        else if (Duty == Period)
        {
            TIMER_SetIdleLevel(TIMERx, Channel, Timer_IDLE_LEVEL_HIGH);  //默认状态为高电平
            TIMER_Cmd(TIMERx, Channel, DISABLE);
        }
        else
        {
            Duty = Period - Duty;
            
            PWM_SetPWMTHandMATCH(TIMERx, Channel, Duty - 1, Period - 1);
            TIMER_Cmd(TIMERx, Channel, ENABLE);
        }
    }
    else
    {
        if (Duty == 0)
        {
            TIMER_SetIdleLevel(TIMERx, Channel, Timer_IDLE_LEVEL_LOW);  //默认状态为低电平
            TIMER_Cmd(TIMERx, Channel, DISABLE);
        }
        else if (Duty == Period)
        {
            TIMER_SetIdleLevel(TIMERx, Channel, Timer_IDLE_LEVEL_HIGH);  //默认状态为高电平
            TIMER_Cmd(TIMERx, Channel, DISABLE);
        }
        else
        {
            PWM_SetPWMTHandMATCH(TIMERx, Channel, Duty - 1, Period - 1);
            TIMER_Cmd(TIMERx, Channel, ENABLE);
        }
    }
}

/*
 * 函数简介：更改TIMER0 Channel1的占空比和周期
 * 函数参数：Period  -- 周期
 *           Duty    -- 占空比(单位为1/Period)
 * 返 回 值：无
* 注意事项：建议尽量根据Period的值决定Duty的单位，1/100或1/1000一般除不到整数
*/
void PWM0_CH1_OutDuty(uint32_t Period, uint32_t Duty)
{
    if (Duty == 0)
    {
        TIMER_SetIdleLevel(TIMER0, Timer_Channel_1, Timer_IDLE_LEVEL_LOW);  //默认状态为低电平
        TIMER_Cmd(TIMER0, Timer_Channel_1, DISABLE);
    }
    else if (Duty == Period)
    {
        TIMER_SetIdleLevel(TIMER0, Timer_Channel_1, Timer_IDLE_LEVEL_HIGH);  //默认状态为高电平
        TIMER_Cmd(TIMER0, Timer_Channel_1, DISABLE);
    }
    else
    {
        Duty = Period - Duty;

        TIMER0->MR1 = Period - 1;
        TIMER0->PWMTH1 = Duty - 1;
        TIMER_Cmd(TIMER0, Timer_Channel_1, ENABLE);
    }
}

/*
 * 函数简介：自定义输出多少个PWM
 * 函数参数：TIMERx   -- 定时器模块，可以为TIMER0,TIMER1,TIMER2,TIMER3
 *           Channel  -- 定时器通道，可以为Timer_Channel_0,Timer_Channel_1,Timer_Channel_2,Timer_Channel_3
 *           Count    -- PWM个数
 * 返 回 值：无
 * 注意事项：必须开启TIMERx的中断，在中断处理程序中进行后续处理
*/
void PWM_OutCount(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Count)
{
    PWM_SetPulseCounterValue(TIMERx, Channel, Count - 1);       //设置发送Count个脉冲
    PWM_PulseCounterCmd(TIMERx, Channel, ENABLE);               //使能脉冲个数发生器
    TIMER_ITConfig(TIMERx, TIMER_IT_PULSE_COUNTER_FLAG | (Channel << 20), ENABLE);    //必须打开中断，在中断中进行后续处理
}

/*
 * 函数简介：PWM输出使能
 * 函数参数：TIMERx   -- 定时器模块，可以为TIMER0,TIMER1,TIMER2,TIMER3
 *           Channel  -- 定时器通道，可以为Timer_Channel_0,Timer_Channel_1,Timer_Channel_2,Timer_Channel_3
 * 返 回 值：无
 * 注意事项：无
*/
void PWM_Start(TIMER_TypeDef* TIMERx, uint32_t Channel)
{
    PWM_Cmd(TIMERx, Channel, ENABLE);
}

/*
 * 函数简介：PWM输出禁止
 * 函数参数：TIMERx   -- 定时器模块，可以为TIMER0,TIMER1,TIMER2,TIMER3
 *           Channel  -- 定时器通道，可以为Timer_Channel_0,Timer_Channel_1,Timer_Channel_2,Timer_Channel_3
 *           Count    -- PWM个数
 * 返 回 值：无
 * 注意事项：无
*/
void PWM_Stop(TIMER_TypeDef* TIMERx, uint32_t Channel)
{
    PWM_Cmd(TIMERx, Channel, DISABLE);
    TIMER_ResetCmd(TIMERx, Channel, ENABLE);
    TIMER_ResetCmd(TIMERx, Channel, DISABLE);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
uint32_t Prescale = 1;
uint32_t Period, Duty_t;
volatile uint32_t systime_ms;

void Delay_ms(uint32_t ms)
{
    systime_ms = ms;
    while(systime_ms);
}

int main()
{
    int flag = 0;
    
    /* USART */
    USART_Configuration();
	printf("\r\n-----------------|- VTM071x Timer -|-----------------\r\n");

    Timer_Configuration();
    
	while(1)
	{
        if (flag == 0)
        {
            Duty_t++;
            if (Duty_t == Period)
                flag = 1;
        }
        else
        {
            Duty_t--;
            if (Duty_t == 0)
                flag = 0;
        }
        
        Delay_ms(1);
        PWM_OutDuty(TIMER0, Timer_Channel_1, Period, Duty_t, PWM_MODE_0);
//        PWM0_CH1_OutDuty(Period, Duty_t);
	}
}

void Timer_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    /* Set Prescale to 1 */
    Timer_Init(TIMER0, Prescale);
    
    /* 通道0配置为定时器，1ms中断 */
    Timer_Config(TIMER0, Timer_Channel_0, 1000);
    NVIC_EnableIRQ(TIMER0_IRQn);
    
    /* 通道1配置为PWM，输出100KHz的方波 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_2;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStructure);
    
    Period = ((SystemCoreClock / 1000000) * 10 / Prescale); //10us
    Duty_t = 0;

    PWM_Standby(TIMER0, Timer_Channel_1, Period, Duty_t, PWM_MODE_0);
    PWM_Start(TIMER0, Timer_Channel_1);
}

void TIMER0_IRQHandler(void)
{
    if (TIMER_GetITStatus(TIMER0, TIMER_IT_PENDING_MR0) == SET)
    {
        TIMER_ClearITPendingBit(TIMER0, TIMER_IT_PENDING_MR0);

        if (systime_ms)
            systime_ms--;
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

