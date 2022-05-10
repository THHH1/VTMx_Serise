/*
*****************************************************************************
    ���ܣ��̳߳�ʼ������
    ʱ�䣺2022.02.18
    ��Ա��th
    �޸ļ�¼��
        th 2022.02.18  �޸�
*****************************************************************************
*/ 

#include "config.h"
#include "Task.h"
#include "bmp.h"
#include "VTM071x_eval_spi.h"
/*************************************************************************
*                            ��������
*************************************************************************
*/
rt_sem_t usart1_recv_sem;//���崮��2�����ź������ƿ�ָ��
rt_mq_t  msg_mq;//������Ϣ���п��ƿ�


static rt_thread_t dynamic_thread = RT_NULL;//��̬�߳̿��ƿ�ָ��

/*************************************************************************
*                             �߳���ں�������
*************************************************************************
*/
void led_thread_entry(void *parameter);
void usart1_recv_thread_entry(void *parameter);//����2���մ�����ں���
void msg_process_thread_entry(void *parameter);//�û���Ϣ������ں���
void weatherOLD_thread_entry(void *parameter);//�û���Ϣ������ں���	
/*************************************************************************
*                             �߳̽ṹ������(�ʺ��̶߳�̬����)
*************************************************************************
*/
TaskStruct TaskThreads[] = {
//			{"ledThread", led_thread_entry,  RT_NULL,  256,  5, 10},
//			{"usart1_recv_thread", usart1_recv_thread_entry, 	RT_NULL, 512, 2, 	10 	},
//			{"msg_process_thread",  msg_process_thread_entry, RT_NULL, 512, 2,   10 },
			{"weatherOLD_thread",  weatherOLD_thread_entry, RT_NULL, 256, 2,   10 },
			/*********************************************************/
			//�û�����̲߳���
			//���磺{�߳�����,�߳���ں���,�߳���ں�������,�߳�ջ��С,�̵߳����ȼ�,�߳�ʱ��Ƭ},
			
			
			
			{"",RT_NULL, RT_NULL,RT_NULL,RT_NULL,RT_NULL}
	
};
/*
*****************************************************************************
    ���ܣ��̳߳�ʼ������
    ʱ�䣺2022.02.18
    ��Ա��th
    �޸ļ�¼��
        th 2022.02.18  �޸�
*****************************************************************************
*/ 	
void TaskInit(void)
{
	uint8_t TaskThreadIndex = 0;
	usart1_recv_sem = rt_sem_create("usart1_recv_sem",  //�ź�������
									0,                  //�ź�����ʼֵ
									RT_IPC_FLAG_FIFO    //�ź���ģʽ FIFO(0x00)
	                                );
	
	if(usart1_recv_sem != RT_NULL)
		rt_kprintf("�ź���usart1_recv_sem�����ɹ�\n\n");
	
	msg_mq = rt_mq_create("msg_mq",							//��Ϣ��������
					32,  									//��Ϣ����󳤶�, bytes
					10,										//��Ϣ���е��������(����)
								RT_IPC_FLAG_FIFO			//����ģʽ FIFO
	                     );
	if(msg_mq != RT_NULL)
		rt_kprintf("��Ϣ����key_mq�����ɹ�\n\n");
	
	while(1)
	{
		if(strcmp(TaskThreads[TaskThreadIndex].name,"") != 0)
		{
			 
			dynamic_thread = rt_thread_create(TaskThreads[TaskThreadIndex].name,  	// �߳����� 
							TaskThreads[TaskThreadIndex].entry,  					// �߳���ں��� 
							TaskThreads[TaskThreadIndex].parameter,           		// �߳���ں�������
							TaskThreads[TaskThreadIndex].stack_size,          		// �߳�ջ��С 
							TaskThreads[TaskThreadIndex].priority,            		// �̵߳����ȼ� 
							TaskThreads[TaskThreadIndex].tick                 		// �߳�ʱ��Ƭ
							);
			if(dynamic_thread != RT_NULL)
			{
				rt_thread_startup(dynamic_thread);
			}
			TaskThreadIndex ++;
		}
		else
			break;	 
	 }
}


/*
*****************************************************************************
    ���ܣ��߳���ں���
    ʱ�䣺2022.02.18
    ��Ա��th
    �޸ļ�¼��
        th 2022.02.18  �޸�
*****************************************************************************
*/ 
void led_thread_entry(void *parameter)
{//led�̣߳�ÿ��2s,�任P6.5״̬
	while(1)
	{
		rt_thread_mdelay(1000);
        GPIO_WriteBit(GPIO6, GPIO_Pin_5, Bit_SET);
		rt_thread_mdelay(1000);
        GPIO_WriteBit(GPIO6, GPIO_Pin_5, Bit_RESET);	
	}
}

#if 0//����1��espռ��
void usart1_recv_thread_entry(void *parameter)
{//����1���մ���
	rt_err_t uwRet = RT_EOK;
	while(1)
	{
		uwRet =rt_sem_take(usart1_recv_sem, RT_WAITING_FOREVER);//��ȡ����1����֡����ź���
		if(RT_EOK == uwRet )
		{
			rt_kprintf("Usart1 Receive Data:%s\n",g_USART1_RxBuf);

			if(strstr((char*)g_USART1_RxBuf,"BeepOn")!=NULL)
			{
				
			}
			if(strstr((char*)g_USART1_RxBuf,"BeepOff")!=NULL)
			{
				
			}
//			 memset(g_USART1_RxBuf,0,USART1_RX_BUF_SIZE);//����
			g_USART1_RecPos = 0;
		}
	}
}
#endif

void msg_process_thread_entry(void *parameter)
{
	rt_err_t uwRet = RT_EOK;
	uint8_t r_queue;//���ڽ���msg_mq��Ϣ������Ϣ
	
	while(1)
	{  //��ȡ������Ϣ
		 uwRet = rt_mq_recv(msg_mq,
							&r_queue,
							sizeof(r_queue),
							RT_WAITING_FOREVER);
		if(RT_EOK == uwRet )
		{
			switch(r_queue)//���ݽ��յ�����Ϣ���ݷֱ���д���
			{
				case MSG_KEY1_PRESS:rt_kprintf("Receive message:KEY1(P1.0) is press\n\n");break;
				case MSG_KEY2_PRESS:rt_kprintf("Receive message:KEY2(P1.x) is press\n\n");break;
				default: rt_kprintf("No Message!\n\n");break;		 
			}
			
		}
		else
		{
			rt_kprintf("���ݽ��մ��󣬴�����룺0x%lx\n\n",uwRet);
		}
	}					
}
/*
*****************************************************************************
    ���ܣ�OLED��ʾ����
    ʱ�䣺2022.03.04
    ��Ա��th
    �޸ļ�¼��
        th 2022.03.04  �޸�
*****************************************************************************
*/ 
uint16_t	tim_year=0;
uint8_t		tim_mon=0;
uint8_t		tim_mday=0;
uint8_t		tim_time=23;
uint8_t		tim_min=59;
uint8_t		tim_sec=40;
void weatherOLD_thread_entry(void *parameter)//�û���Ϣ������ں���	
{
	u8 t=40;
	OLED_Init();
//	OLED_ShowPicture(0,0,128,0,Water_Drop);

	OLED_ShowChinese(8,16,0,16);	//��
	OLED_ShowChinese(24,16,1,16);	//��
	OLED_ShowChinese(40,16,2,16);	//��
	OLED_ShowChinese(56,16,3,16);	//��
	OLED_ShowChinese(72,16,4,16);	//��
	OLED_ShowChinese(88,16,5,16);	//��
	OLED_ShowChinese(104,16,6,16);	//��
	
	OLED_ShowString(32,48,"YunLink",16);
	OLED_Refresh();
	OLED_ShowPicture(0,0,128,2,BMP2);//��˾LOGO
	rt_thread_mdelay(1000);	
	weather_data.code[0]=0x32;
	weather_data.code[1]=0x37;
	weather_data.temperature[0]=0x30;
	weather_data.temperature[1]=0x30;
	weather_data.temperature[2]=0x30;
	OLED_Clear();
	while (1)
	{	
#ifdef   Gyroscope
	
		rt_thread_mdelay(500);
		
		OLED_ShowChinese1(0,16,0,16);	//��
		OLED_ShowChinese1(16,16,1,16);//��	
		
		OLED_ShowChinese2(96,16,1,16);	//��
		OLED_ShowChinese2(112,16,2,16);	//��
		OLED_ShowString(32,16,"        ",16);
				
		OLED_ShowString(0,32,"CODE:",16);
		OLED_ShowChar(48,32,weather_data.code[0],16);//��ʾASCII�ַ�
		if(weather_data.code[1]>=0x30&&weather_data.code[1]<=0x39)
		{
			OLED_ShowChar(56,32,weather_data.code[1],16);//��ʾASCII�ַ�
		}
		else
		{
			OLED_ShowChar(56,32,0x20,16);//��ʾASCII�ַ�
		}
		
		OLED_ShowChar(80,32,weather_data.temperature[0],16);//��ʾASCII�ַ�
		OLED_ShowChar(88,32,weather_data.temperature[1],16);//��ʾASCII�ַ�
		OLED_ShowChinese2(104,32,0,16);	//��
		
		OLED_ShowChar(0,48,(tim_mon/10+0x30),16);//�·�
		OLED_ShowChar(8,48,(tim_mon%10+0x30),16);
		OLED_ShowChar(16,48,0x2F,16);
		OLED_ShowChar(24,48,(tim_mday/10+0x30),16);//����
		OLED_ShowChar(32,48,(tim_mday%10+0x30),16);
		OLED_ShowChar(40,48,0x20,16);
		
		OLED_ShowChar(48,48,(tim_time/10+0x30),16);//Сʱ
		OLED_ShowChar(56,48,(tim_time%10+0x30),16);
		OLED_ShowChar(64,48,0x3A,16);
		OLED_ShowChar(72,48,(tim_min/10+0x30),16);//����
		OLED_ShowChar(80,48,(tim_min%10+0x30),16);
		

		OLED_ShowNum(103,48,t,2,16);
		OLED_Refresh();
		t++;
		if(t>59)
		{
			t=0;
			tim_min++;
			if(tim_min>59)
			{
				tim_min=0;tim_time++;
				if(tim_time>23)
				{
					tim_time=0;tim_mday++;
				}
			}
		}		
		rt_thread_mdelay(500);
		
//		OLED_Clear();
//		OLED_ScrollDisplay(11,4);
//==================================================================
//		getAccelerometervalue();//��ȡ������ٶ�ֵ
//		getGyroscopeValue();//��ȡ������ٶ�ֵ		
//		OLED_ShowPicture(0,0,128,8,Water_Drop);
#else 

		OLED_DrawLine(64,0,64,23);
		OLED_DrawLine(64,42,64,64);
		
		OLED_DrawLine(0,32,55,32);
		OLED_DrawLine(74,32,128,32);
		
		OLED_DrawCircle(64,32,2);
		OLED_DrawCircle(64,32,4);
		OLED_DrawCircle(64,32,6);
		OLED_DrawCircle(64,32,8);
		OLED_Refresh();
		t++;
		rt_thread_mdelay(5);
#endif
//==================================================================
	}
}






