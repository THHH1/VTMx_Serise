/*
*****************************************************************************
    ���ܣ�LED�ĳ�ʼ��
    ʱ�䣺2022.02.15
    ��Ա��wjonas
    �޸ļ�¼��
        wjonas 2022.02.15  �޸�
*****************************************************************************
*/ 
#include "config.h"

/************************************************************
���ܣ�LED-GPIO��ʼ��
ʱ�䣺2022.02.15
��Ա��wjonas
��Σ���
���Σ���
************************************************************/
void LedGpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = Led0_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(Led0_GPIOx, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = Led1_Pin;
    GPIO_Init(Led1_GPIOx, &GPIO_InitStructure);
    
    //LED��ʼ��ΪϨ��״̬
    GPIO_WriteBit(Led0_GPIOx, Led0_Pin, Bit_SET);
    GPIO_WriteBit(Led1_GPIOx, Led1_Pin, Bit_SET);
	
}

/************************************************************
���ܣ�LED-GPIO����
ʱ�䣺2022.02.15
��Ա��wjonas
��Σ�led_num    
                Led0_num  LED1
                Led1_num  LED2
      flag
                0  �ر�LED
                1  ����LED     
���Σ���
************************************************************/
void LedControl(rt_uint8_t led_num ,rt_uint8_t flag)
{
    if(led_num == Led0_num)
    {
        if(flag == 0)
        {
            GPIO_WriteBit(Led0_GPIOx, Led0_Pin, Bit_SET);
        }
        else
        {
            GPIO_WriteBit(Led0_GPIOx, Led0_Pin, Bit_RESET);
        }
    }
    else
    {
        if(flag == 0)
        {
            GPIO_WriteBit(Led1_GPIOx, Led1_Pin, Bit_SET);
        }
        else
        {
            GPIO_WriteBit(Led1_GPIOx, Led1_Pin, Bit_RESET);
        }
    }
}
