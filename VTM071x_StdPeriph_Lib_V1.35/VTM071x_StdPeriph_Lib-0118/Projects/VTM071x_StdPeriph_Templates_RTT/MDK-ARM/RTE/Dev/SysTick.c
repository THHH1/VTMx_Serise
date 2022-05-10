#include "config.h"
#include "SysTick.h"





void SysTickInit(void)
{
	uint32_t systickclk = 0;
	systickclk = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / RT_TICK_PER_SECOND;
    SysTick_Config(systickclk);	
}


void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t delta;
    rt_uint32_t current_delay;

    /* �����ʱ������tick�� */
    us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));

    /* ��õ�ǰʱ�� */
    delta = SysTick->VAL;

    /* ѭ����õ�ǰʱ�䣬ֱ���ﵽָ����ʱ����˳�ѭ�� */
    do
    {
			if ( delta > SysTick->VAL )
				current_delay = delta - SysTick->VAL;
			else
        /* ��ʱ��Խ��һ��OS tick�ı߽�ʱ�Ĵ��� */
				current_delay = SysTick->LOAD + delta - SysTick->VAL;
    } while( current_delay < us );
}


#if 0
void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t delta;
    /* �����ʱ������ tick �� */
    us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));
    /* ��õ�ǰʱ�� */
    delta = SysTick->VAL;
    /* ѭ����õ�ǰʱ�䣬ֱ���ﵽָ����ʱ����˳�ѭ�� */
    while (delta - SysTick->VAL< us);
}
#endif


