#include "config.h"
#include "Task.h"

/*************************************************************************
*                            变量定义
*************************************************************************
*/
rt_sem_t usart1_recv_sem;//定义串口2接收信号量控制块指针
rt_mq_t  msg_mq;//定义消息队列控制块


static rt_thread_t dynamic_thread = RT_NULL;//动态线程控制块指针

/*************************************************************************
*                             线程入口函数声明
*************************************************************************
*/
void led_thread_entry(void *parameter);
void usart1_recv_thread_entry(void *parameter);//串口2接收处理入口函数
void msg_process_thread_entry(void *parameter);//用户消息处理入口函数
	
	
/*************************************************************************
*                             线程结构体数组(适合线程动态创建)
*************************************************************************
*/
TaskStruct TaskThreads[] = {
			{"ledThread", led_thread_entry,  RT_NULL,  256,  5, 10},
			{"usart1_recv_thread", usart1_recv_thread_entry, 	RT_NULL, 512, 2, 	10 	},
			{"msg_process_thread",  msg_process_thread_entry, RT_NULL, 512, 2,   10 },
			
			/*********************************************************/
			//用户添加线程参数
			//例如：{线程名字,线程入口函数,线程入口函数参数,线程栈大小,线程的优先级,线程时间片},
			
			
			
			{"",RT_NULL, RT_NULL,RT_NULL,RT_NULL,RT_NULL}
	
};
	
void TaskInit(void)
{
	uint8_t TaskThreadIndex = 0;
	usart1_recv_sem = rt_sem_create("usart1_recv_sem",  //信号量名字
									0,                  //信号量初始值
									RT_IPC_FLAG_FIFO    //信号量模式 FIFO(0x00)
	                                );
	
	if(usart1_recv_sem != RT_NULL)
		rt_kprintf("信号量usart1_recv_sem创建成功\n\n");
	
	msg_mq = rt_mq_create("msg_mq",							//消息队列名字
					32,  									//消息的最大长度, bytes
					10,										//消息队列的最大容量(个数)
								RT_IPC_FLAG_FIFO			//队列模式 FIFO
	                     );
	if(msg_mq != RT_NULL)
		rt_kprintf("消息队列key_mq创建成功\n\n");
	
	while(1)
	{
		if(strcmp(TaskThreads[TaskThreadIndex].name,"") != 0)
		{
			 
			dynamic_thread = rt_thread_create(TaskThreads[TaskThreadIndex].name,  	// 线程名字 
							TaskThreads[TaskThreadIndex].entry,  					// 线程入口函数 
							TaskThreads[TaskThreadIndex].parameter,           		// 线程入口函数参数
							TaskThreads[TaskThreadIndex].stack_size,          		// 线程栈大小 
							TaskThreads[TaskThreadIndex].priority,            		// 线程的优先级 
							TaskThreads[TaskThreadIndex].tick                 		// 线程时间片
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
*                             线程入口函数定义
*************************************************************************
*/
void led_thread_entry(void *parameter)
{//led线程，每隔2s,变换P6.5状态
	while(1)
	{
		rt_thread_mdelay(1000);
        GPIO_WriteBit(GPIO6, GPIO_Pin_5, Bit_SET);
		rt_thread_mdelay(1000);
        GPIO_WriteBit(GPIO6, GPIO_Pin_5, Bit_RESET);	
	}
}

void usart1_recv_thread_entry(void *parameter)
{//串口1接收处理
	rt_err_t uwRet = RT_EOK;
	while(1)
	{
		uwRet =rt_sem_take(usart1_recv_sem, RT_WAITING_FOREVER);//获取串口1接收帧完成信号量
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
//			 memset(g_USART1_RxBuf,0,USART1_RX_BUF_SIZE);//清零
			g_USART1_RecPos = 0;
		}
	}
}

void msg_process_thread_entry(void *parameter)
{
	rt_err_t uwRet = RT_EOK;
	uint8_t r_queue;//用于接收msg_mq消息队列信息
	
	while(1)
	{  //获取队列信息
		 uwRet = rt_mq_recv(msg_mq,
							&r_queue,
							sizeof(r_queue),
							RT_WAITING_FOREVER);
		if(RT_EOK == uwRet )
		{
			switch(r_queue)//根据接收到的消息内容分别进行处理
			{
				case MSG_KEY1_PRESS:rt_kprintf("Receive message:KEY1(P1.0) is press\n\n");break;
				case MSG_KEY2_PRESS:rt_kprintf("Receive message:KEY2(P1.x) is press\n\n");break;
				default: rt_kprintf("No Message!\n\n");break;		 
			}
			
		}
		else
		{
			rt_kprintf("数据接收错误，错误代码：0x%lx\n\n",uwRet);
		}
	}					
}
















