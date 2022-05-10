#include "config.h"
#include "Exti.h"


/*
*****************************************************************************
    功能：外部中断初始化函数
    时间：2022.02.10
    人员：th
    修改记录：
        th 2022.02.10  修改
*****************************************************************************
*/
void  ExtiInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    /* Key */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;						//使能GPIO1_0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;				//设置频率为50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					//设置模式为输入模式
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;					//设置模式为输入下拉模式
    GPIO_Init(GPIO1, &GPIO_InitStructure);							//GPIO1_0
    
    NVIC_EnableIRQ(GPIO0_TO_GPIO3_IRQn);							//中断

    GPIO_ITConfig(GPIO1, GPIO_Pin_0, GPIO_IT_EDGE_RISING, ENABLE);	//指定GPIO1_0 启用中断
}


/*
*****************************************************************************
    功能：外部中断服务函数入口
    时间：2022.02.10
    人员：th
    修改记录：
        th 2022.02.10  修改
*****************************************************************************
*/
void GPIO0_TO_GPIO3_IRQHandler (void)
{
	MSG_TYPE msg = MSG_KEY1_PRESS;
	if (GPIO_GetITStatus(GPIO1, GPIO_Pin_0) == SET)
	{
//		rt_kprintf("GPIO0_TO_GPIO3_IRQHandler\n");
		//用户代码	
		rt_mq_send(msg_mq,       // 写入（发送）队列的ID(句柄)
		           &msg,         // 写入（发送）的数据所对应地址 
		           sizeof(msg)   // 数据的长度 
							);	
		//--------------------------------
		GPIO_ClearITPendingBit(GPIO1, GPIO_Pin_0);
	}
}



