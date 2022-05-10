#include "config.h"
#include "BspTimer.h"

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

uint32_t Prescale = 1;
uint32_t Period, Duty_t;
void Timer_Configuration(void)
{
    /* Set Prescale to 1 */
    Timer_Init(TIMER0, Prescale);
    
    /* 通道0配置为定时器，1ms中断 */
    Timer_Config(TIMER0, Timer_Channel_0, 1000);
    NVIC_EnableIRQ(TIMER0_IRQn);
}

void TIMER0_IRQHandler(void)
{
    if (TIMER_GetITStatus(TIMER0, TIMER_IT_PENDING_MR0) == SET)
    {
        TIMER_ClearITPendingBit(TIMER0, TIMER_IT_PENDING_MR0);

		//----------------------------------------------------------
		//填充用户代码 Add User Code
		
		ButtonProj();//按键定时扫描
		//---------------------------------------------------------
    }
}

