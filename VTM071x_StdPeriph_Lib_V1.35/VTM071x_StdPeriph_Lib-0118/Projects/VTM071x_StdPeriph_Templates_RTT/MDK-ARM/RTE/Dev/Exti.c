#include "config.h"
#include "Exti.h"

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

//void GPIO0_TO_GPIO3_IRQHandler(void)
//{    
//	uint32_t jitters;
//    if (GPIO_GetITStatus(GPIO1, GPIO_Pin_0) == SET)
//    {
//		GPIO_ClearITPendingBit(GPIO1, GPIO_Pin_0);
//        for(jitters=0; jitters<0x3000; jitters++);
//        if (GPIO_ReadDataBit(GPIO1, GPIO_Pin_0) != SET)
//            return;		
//		rt_mq_send(key_mq, "key(P1.0)EXIT Occur \n", sizeof("key(P1.0)EXIT Occur \n"));		
//    }
//}

void GPIO0_TO_GPIO3_IRQHandler (void)
{
	MSG_TYPE msg = MSG_KEY1_PRESS;
	if (GPIO_GetITStatus(GPIO1, GPIO_Pin_0) == SET)
	{
		//用户代码	
		rt_mq_send(msg_mq,       // 写入（发送）队列的ID(句柄)
		           &msg,         // 写入（发送）的数据所对应地址 
		           sizeof(msg)   // 数据的长度 
							);	
		//--------------------------------
		GPIO_ClearITPendingBit(GPIO1, GPIO_Pin_0);
	}
}



