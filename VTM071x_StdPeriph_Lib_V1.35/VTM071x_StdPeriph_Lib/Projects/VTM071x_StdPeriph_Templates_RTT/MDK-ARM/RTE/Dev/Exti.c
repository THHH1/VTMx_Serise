#include "config.h"
#include "Exti.h"

void  ExtiInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    /* Key */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;						//ʹ��GPIO1_0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;				//����Ƶ��Ϊ50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					//����ģʽΪ����ģʽ
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;					//����ģʽΪ��������ģʽ
    GPIO_Init(GPIO1, &GPIO_InitStructure);							//GPIO1_0
    
    NVIC_EnableIRQ(GPIO0_TO_GPIO3_IRQn);							//�ж�

    GPIO_ITConfig(GPIO1, GPIO_Pin_0, GPIO_IT_EDGE_RISING, ENABLE);	//ָ��GPIO1_0 �����ж�
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
		//�û�����	
		rt_mq_send(msg_mq,       // д�루���ͣ����е�ID(���)
		           &msg,         // д�루���ͣ�����������Ӧ��ַ 
		           sizeof(msg)   // ���ݵĳ��� 
							);	
		//--------------------------------
		GPIO_ClearITPendingBit(GPIO1, GPIO_Pin_0);
	}
}



