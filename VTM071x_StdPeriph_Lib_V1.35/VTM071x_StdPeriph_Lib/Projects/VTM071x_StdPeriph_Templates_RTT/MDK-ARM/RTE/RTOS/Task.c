#include "config.h"
#include "Task.h"

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
	
	
/*************************************************************************
*                             �߳̽ṹ������(�ʺ��̶߳�̬����)
*************************************************************************
*/
TaskStruct TaskThreads[] = {
			{"ledThread", led_thread_entry,  RT_NULL,  256,  5, 10},
			{"usart1_recv_thread", usart1_recv_thread_entry, 	RT_NULL, 512, 2, 	10 	},
			{"msg_process_thread",  msg_process_thread_entry, RT_NULL, 512, 2,   10 },
			
			/*********************************************************/
			//�û�����̲߳���
			//���磺{�߳�����,�߳���ں���,�߳���ں�������,�߳�ջ��С,�̵߳����ȼ�,�߳�ʱ��Ƭ},
			
			
			
			{"",RT_NULL, RT_NULL,RT_NULL,RT_NULL,RT_NULL}
	
};
	
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


/*************************************************************************
*                             �߳���ں�������
*************************************************************************
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
				BeepOn();
			}
			if(strstr((char*)g_USART1_RxBuf,"BeepOff")!=NULL)
			{
				BeepOff();
			}
//			 memset(g_USART1_RxBuf,0,USART1_RX_BUF_SIZE);//����
			g_USART1_RecPos = 0;
		}
	}
}

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
















