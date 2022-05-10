#ifndef __GPIO_H__
#define __GPIO_H__



void LedGpioInit(void);//Led管脚初始化
void LedControl(void); //Led控制代码
int BeepGpioInit(void);
void BeepOn(void);
void BeepOff(void);

#endif



