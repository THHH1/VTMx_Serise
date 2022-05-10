/*
*****************************************************************************
    功能：BEEP的初始化
    时间：2022.02.16
    人员：wjonas
    修改记录：
        wjonas 2022.02.16  修改
*****************************************************************************
*/ 
#include "config.h"

/************************************************************
功能：BEEP-GPIO初始化
时间：2022.02.16
人员：wjonas
入参：无
出参：无
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
功能：Beep-GPIO控制
时间：2022.02.16
人员：wjonas
入参：
      flag
                0  关闭BEEP
                1  开启BEEP    
出参：无
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


