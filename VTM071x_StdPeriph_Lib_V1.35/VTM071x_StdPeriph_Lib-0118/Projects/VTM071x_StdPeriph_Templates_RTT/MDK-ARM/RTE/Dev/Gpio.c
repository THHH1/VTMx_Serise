#include "config.h"
#include "Gpio.h"

void LedGpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO6, &GPIO_InitStructure);
    
    /* LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIO6, &GPIO_InitStructure);
	
}
void LedControl(void)
{
	GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_SET);
	rt_thread_mdelay(1000);
	GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_RESET);
	rt_thread_mdelay(1000);
	
}


int BeepGpioInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    /* BEEP */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO6, &GPIO_InitStructure);
    	
	
	return TRUE;
}
INIT_BOARD_EXPORT(BeepGpioInit);



void BeepOn(void)
{
	GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_RESET);
	rt_kprintf("GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_RESET);\n");
}
MSH_CMD_EXPORT(BeepOn, Control Beep On);

void BeepOff(void)
{
	GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_SET);
	rt_kprintf("GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_SET);\n");
}
MSH_CMD_EXPORT(BeepOff, Control Beep Off);


