#include "config.h"
#include "BspTimer.h"

/*
 * ������飺��ʱ��ģ���ʼ������ʱ�ӣ���λͨ��
 * ����������TIMERx  -- ��ʱ��ģ�飬����ΪTIMER0,TIMER1,TIMER2,TIMER3
 *           Prescale-- ��ʱ��ģ��Ԥ��Ƶ
 * �� �� ֵ����
 * ע�����Prescale�Ƽ�ֵΪ1���������Ի����ߵķֱ��ʣ����ڸ�Ƶ��PWM���Ի����ߵľ�ȷ��
*/
void Timer_Init(TIMER_TypeDef* TIMERx, uint32_t Prescale)
{
    /* ��TIMER��ʱ�� */
    if (TIMERx == TIMER0)
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_TIMER0, ENABLE);
    else if (TIMERx == TIMER1)
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_TIMER1, ENABLE);
    else if (TIMERx == TIMER2)
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_TIMER2, ENABLE);
    else
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_TIMER3, ENABLE);

    /* ��λ��TIMER��4��ͨ�� */
    TIMER_DeInit(TIMERx);

    /* д�뵽�Ĵ�����ֵΪPrescale-1 */
    TIMER_SetPrescale(TIMERx, Prescale - 1);
}

/*
 * ������飺����һ����ʱ��
 * ����������TIMERx -- ��ʱ��ģ�飬����ΪTIMER0,TIMER1,TIMER2,TIMER3
 *           Channel-- ��ʱ��ͨ��������ΪTimer_Channel_0,Timer_Channel_1,Timer_Channel_2,Timer_Channel_3
 *           us     -- ��ʱ��ʱ�䣬��λΪ΢��
 * �� �� ֵ����
 * ע�������PR�Ĵ���Ϊ0ʱ��us����С��0xFFFFFFFF / AHBʱ��(��λM) * (PR+1)��������96MΪ����������44739242
*/
void Timer_Config(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t us)
{
    TIMER_InitTypeDef TIMER_InitStructure;

    /* ���Է�Ƶϵ�� */
    us = us / (TIMER_GetPrescale(TIMERx) + 1);     

    /* Խ�紦�� */
    if (us > 44739242)
        us = 44739242;

    TIMER_InitStructure.TIMER_Channel = Channel;		                                    //ͨ��
    TIMER_InitStructure.TIMER_Dir = TIMER_DIR_INCREASE;		                                //���ϼ���
    TIMER_InitStructure.TIMER_MatchValue = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000000 * us - 1;  //ƥ��ֵ����ΪAHBCLK-1����ʱ������Ϊ1MS
    TIMER_InitStructure.TIMER_MatchAction = TIMER_MatchAction_HOLD;                         //TC��MRƥ��ʱ������ܽ�MAT��ƽ����
    TIMER_InitStructure.TIMER_MatchConfig = TIMER_MatchConfig_RESET_TC;                     //TC��MRƥ��ʱ����λTC
    TIMER_Init(TIMERx, &TIMER_InitStructure);                                               //��ʼ��
    TIMER_ITConfig(TIMERx, TIMER_IT_MR0I, ENABLE);                                          //����ƥ���ж�
    
    TIMER_Cmd(TIMERx, Channel, ENABLE);
}

uint32_t Prescale = 1;
uint32_t Period, Duty_t;
void Timer_Configuration(void)
{
    /* Set Prescale to 1 */
    Timer_Init(TIMER0, Prescale);
    
    /* ͨ��0����Ϊ��ʱ����1ms�ж� */
    Timer_Config(TIMER0, Timer_Channel_0, 1000);
    NVIC_EnableIRQ(TIMER0_IRQn);
}

void TIMER0_IRQHandler(void)
{
    if (TIMER_GetITStatus(TIMER0, TIMER_IT_PENDING_MR0) == SET)
    {
        TIMER_ClearITPendingBit(TIMER0, TIMER_IT_PENDING_MR0);

		//----------------------------------------------------------
		//����û����� Add User Code
		
		ButtonProj();//������ʱɨ��
		//---------------------------------------------------------
    }
}

