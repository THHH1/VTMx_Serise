/*
*****************************************************************************
    功能：LED的初始化
    时间：2022.02.15
    人员：wjonas
    修改记录：
        wjonas 2022.02.15  修改
*****************************************************************************
*/ 
#include "rtdef.h"

#define Led0_num  0
#define Led1_num  1

#define Led0_Pin   GPIO_Pin_4
#define Led0_GPIOx GPIO6
#define Led1_Pin   GPIO_Pin_5
#define Led1_GPIOx GPIO6

/************************************************************
功能：LED-GPIO初始化
时间：2022.02.15
人员：wjonas
入参：无
出参：无
************************************************************/
void LedGpioInit(void);

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
void LedControl(rt_uint8_t led_num ,rt_uint8_t flag);

