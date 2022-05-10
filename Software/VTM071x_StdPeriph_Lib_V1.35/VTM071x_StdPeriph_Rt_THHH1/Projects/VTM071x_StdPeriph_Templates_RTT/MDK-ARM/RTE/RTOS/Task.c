/*
*****************************************************************************
    功能：线程初始化函数
    时间：2022.02.18
    人员：th
    修改记录：
        th 2022.02.18  修改
*****************************************************************************
*/ 

#include "config.h"
#include "Task.h"
#include "bmp.h"
#include "VTM071x_eval_spi.h"
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
void weatherOLD_thread_entry(void *parameter);//用户消息处理入口函数	
/*************************************************************************
*                             线程结构体数组(适合线程动态创建)
*************************************************************************
*/
TaskStruct TaskThreads[] = {
//			{"ledThread", led_thread_entry,  RT_NULL,  256,  5, 10},
//			{"usart1_recv_thread", usart1_recv_thread_entry, 	RT_NULL, 512, 2, 	10 	},
//			{"msg_process_thread",  msg_process_thread_entry, RT_NULL, 512, 2,   10 },
			{"weatherOLD_thread",  weatherOLD_thread_entry, RT_NULL, 256, 2,   10 },
			/*********************************************************/
			//用户添加线程参数
			//例如：{线程名字,线程入口函数,线程入口函数参数,线程栈大小,线程的优先级,线程时间片},
			
			
			
			{"",RT_NULL, RT_NULL,RT_NULL,RT_NULL,RT_NULL}
	
};
/*
*****************************************************************************
    功能：线程初始化函数
    时间：2022.02.18
    人员：th
    修改记录：
        th 2022.02.18  修改
*****************************************************************************
*/ 	
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


/*
*****************************************************************************
    功能：线程入口函数
    时间：2022.02.18
    人员：th
    修改记录：
        th 2022.02.18  修改
*****************************************************************************
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

#if 0//串口1被esp占用
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
				
			}
			if(strstr((char*)g_USART1_RxBuf,"BeepOff")!=NULL)
			{
				
			}
//			 memset(g_USART1_RxBuf,0,USART1_RX_BUF_SIZE);//清零
			g_USART1_RecPos = 0;
		}
	}
}
#endif

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
/*
*****************************************************************************
    功能：OLED显示进程
    时间：2022.03.04
    人员：th
    修改记录：
        th 2022.03.04  修改
*****************************************************************************
*/ 
uint16_t	tim_year=0;
uint8_t		tim_mon=0;
uint8_t		tim_mday=0;
uint8_t		tim_time=23;
uint8_t		tim_min=59;
uint8_t		tim_sec=40;
void weatherOLD_thread_entry(void *parameter)//用户消息处理入口函数	
{
	u8 t=40;
	OLED_Init();
//	OLED_ShowPicture(0,0,128,0,Water_Drop);

	OLED_ShowChinese(8,16,0,16);	//合
	OLED_ShowChinese(24,16,1,16);	//肥
	OLED_ShowChinese(40,16,2,16);	//云
	OLED_ShowChinese(56,16,3,16);	//联
	OLED_ShowChinese(72,16,4,16);	//半
	OLED_ShowChinese(88,16,5,16);	//导
	OLED_ShowChinese(104,16,6,16);	//体
	
	OLED_ShowString(32,48,"YunLink",16);
	OLED_Refresh();
	OLED_ShowPicture(0,0,128,2,BMP2);//公司LOGO
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
		
		OLED_ShowChinese1(0,16,0,16);	//天
		OLED_ShowChinese1(16,16,1,16);//气	
		
		OLED_ShowChinese2(96,16,1,16);	//合
		OLED_ShowChinese2(112,16,2,16);	//肥
		OLED_ShowString(32,16,"        ",16);
				
		OLED_ShowString(0,32,"CODE:",16);
		OLED_ShowChar(48,32,weather_data.code[0],16);//显示ASCII字符
		if(weather_data.code[1]>=0x30&&weather_data.code[1]<=0x39)
		{
			OLED_ShowChar(56,32,weather_data.code[1],16);//显示ASCII字符
		}
		else
		{
			OLED_ShowChar(56,32,0x20,16);//显示ASCII字符
		}
		
		OLED_ShowChar(80,32,weather_data.temperature[0],16);//显示ASCII字符
		OLED_ShowChar(88,32,weather_data.temperature[1],16);//显示ASCII字符
		OLED_ShowChinese2(104,32,0,16);	//度
		
		OLED_ShowChar(0,48,(tim_mon/10+0x30),16);//月份
		OLED_ShowChar(8,48,(tim_mon%10+0x30),16);
		OLED_ShowChar(16,48,0x2F,16);
		OLED_ShowChar(24,48,(tim_mday/10+0x30),16);//日期
		OLED_ShowChar(32,48,(tim_mday%10+0x30),16);
		OLED_ShowChar(40,48,0x20,16);
		
		OLED_ShowChar(48,48,(tim_time/10+0x30),16);//小时
		OLED_ShowChar(56,48,(tim_time%10+0x30),16);
		OLED_ShowChar(64,48,0x3A,16);
		OLED_ShowChar(72,48,(tim_min/10+0x30),16);//分钟
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
//		getAccelerometervalue();//获取三轴加速度值
//		getGyroscopeValue();//获取三轴角速度值		
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






