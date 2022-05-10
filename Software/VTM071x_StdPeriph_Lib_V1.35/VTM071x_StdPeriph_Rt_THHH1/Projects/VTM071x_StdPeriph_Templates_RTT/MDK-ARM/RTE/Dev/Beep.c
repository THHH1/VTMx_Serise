/*
*****************************************************************************
    ���ܣ�BEEP�ĳ�ʼ��
    ʱ�䣺2022.02.16
    ��Ա��wjonas
    �޸ļ�¼��
        wjonas 2022.02.16  �޸�
*****************************************************************************
*/ 
#include "config.h"

/************************************************************
���ܣ�BEEP-GPIO��ʼ��
ʱ�䣺2022.02.16
��Ա��wjonas
��Σ���
���Σ���
************************************************************/
void BeepGpioInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    /* BEEP */
    GPIO_InitStructure.GPIO_Pin = Beep_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(Beep_GPIOx, &GPIO_InitStructure);
}

/************************************************************
���ܣ�Beep-GPIO����
ʱ�䣺2022.02.16
��Ա��wjonas
��Σ�
      flag
                0  �ر�BEEP
                1  ����BEEP    
���Σ���
************************************************************/
void BeepControl(rt_uint8_t flag)
{
    if(flag == 0)
    {
        GPIO_WriteBit(Beep_GPIOx, Beep_Pin, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(Beep_GPIOx, Beep_Pin, Bit_RESET);
    }
}


