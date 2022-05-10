/*
*****************************************************************************
    ���ܣ�SYSTICK�ĳ�ʼ��
    ʱ�䣺2022.02.16
    ��Ա��wjonas
    �޸ļ�¼��
        wjonas 2022.02.16  �޸�
*****************************************************************************
*/ 
#include "config.h"

/************************************************************
���ܣ�SYSTICK��ʼ��
ʱ�䣺2022.02.16
��Ա��wjonas
��Σ���
���Σ���
************************************************************/
void SysTickInit(void)
{
	uint32_t systickclk = 0;
	systickclk = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / RT_TICK_PER_SECOND;
    SysTick_Config(systickclk);	
}


/************************************************************
���ܣ�ϵͳ�δ�΢����ʱ
ʱ�䣺2022.02.16
��Ա��wjonas
��Σ�us
���Σ���
************************************************************/
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
            {
				current_delay = delta - SysTick->VAL;
            }
			else
            {
                /* ��ʱ��Խ��һ��OS tick�ı߽�ʱ�Ĵ��� */
				current_delay = SysTick->LOAD + delta - SysTick->VAL;
            }
    } while( current_delay < us );
}
/************************************************************
���ܣ�ϵͳ�δ������ʱ
ʱ�䣺2022.02.25
��Ա��th
��Σ�ms
���Σ���
************************************************************/
void rt_hw_ms_delay(rt_uint32_t ms)
{
    rt_uint32_t delta1;
    rt_uint32_t current_delay1;

    /* �����ʱ������tick�� */
    ms = ms * (SysTick->LOAD/1000000);

    /* ��õ�ǰʱ�� */
    delta1 = SysTick->VAL;

    /* ѭ����õ�ǰʱ�䣬ֱ���ﵽָ����ʱ����˳�ѭ�� */
    do
    {
			if ( delta1 > SysTick->VAL )
            {
				current_delay1 = delta1 - SysTick->VAL;
            }
			else
            {
                /* ��ʱ��Խ��һ��OS tick�ı߽�ʱ�Ĵ��� */
				current_delay1 = SysTick->LOAD + delta1 - SysTick->VAL;
            }
    } while( current_delay1 < ms );
}


