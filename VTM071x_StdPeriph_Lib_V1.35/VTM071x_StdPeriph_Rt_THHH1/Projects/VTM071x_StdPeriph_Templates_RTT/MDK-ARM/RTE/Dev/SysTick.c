/*
*****************************************************************************
    功能：SYSTICK的初始化
    时间：2022.02.16
    人员：wjonas
    修改记录：
        wjonas 2022.02.16  修改
*****************************************************************************
*/ 
#include "config.h"

/************************************************************
功能：SYSTICK初始化
时间：2022.02.16
人员：wjonas
入参：无
出参：无
************************************************************/
void SysTickInit(void)
{
	uint32_t systickclk = 0;
	systickclk = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / RT_TICK_PER_SECOND;
    SysTick_Config(systickclk);	
}


/************************************************************
功能：系统滴答微秒延时
时间：2022.02.16
人员：wjonas
入参：us
出参：无
************************************************************/
void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t delta;
    rt_uint32_t current_delay;

    /* 获得延时经过的tick数 */
    us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));

    /* 获得当前时间 */
    delta = SysTick->VAL;

    /* 循环获得当前时间，直到达到指定的时间后退出循环 */
    do
    {
			if ( delta > SysTick->VAL )
            {
				current_delay = delta - SysTick->VAL;
            }
			else
            {
                /* 延时跨越了一次OS tick的边界时的处理 */
				current_delay = SysTick->LOAD + delta - SysTick->VAL;
            }
    } while( current_delay < us );
}
/************************************************************
功能：系统滴答毫秒延时
时间：2022.02.25
人员：th
入参：ms
出参：无
************************************************************/
void rt_hw_ms_delay(rt_uint32_t ms)
{
    rt_uint32_t delta1;
    rt_uint32_t current_delay1;

    /* 获得延时经过的tick数 */
    ms = ms * (SysTick->LOAD/1000000);

    /* 获得当前时间 */
    delta1 = SysTick->VAL;

    /* 循环获得当前时间，直到达到指定的时间后退出循环 */
    do
    {
			if ( delta1 > SysTick->VAL )
            {
				current_delay1 = delta1 - SysTick->VAL;
            }
			else
            {
                /* 延时跨越了一次OS tick的边界时的处理 */
				current_delay1 = SysTick->LOAD + delta1 - SysTick->VAL;
            }
    } while( current_delay1 < ms );
}


