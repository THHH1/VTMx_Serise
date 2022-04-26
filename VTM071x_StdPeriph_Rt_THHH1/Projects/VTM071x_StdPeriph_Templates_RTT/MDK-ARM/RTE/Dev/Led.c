/*
*****************************************************************************
    功能：LED的初始化
    时间：2022.02.15
    人员：wjonas
    修改记录：
        wjonas 2022.02.15  修改
*****************************************************************************
*/ 
#include "config.h"

/************************************************************
功能：LED-GPIO初始化
时间：2022.02.15
人员：wjonas
入参：无
出参：无
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
    
    //LED初始化为熄灭状态
    GPIO_WriteBit(Led0_GPIOx, Led0_Pin, Bit_SET);
    GPIO_WriteBit(Led1_GPIOx, Led1_Pin, Bit_SET);
	
}

/************************************************************
功能：LED-GPIO控制
时间：2022.02.15
人员：wjonas
入参：led_num    
                Led0_num  LED1
                Led1_num  LED2
      flag
                0  关闭LED
                1  开启LED     
出参：无
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
