/*
*****************************************************************************
    功能：全局配置
    时间：2022.02.17
    人员：wjonas
    修改记录：
        wjonas 2022.02.17  修改
*****************************************************************************
*/ 
//无符号类型的定义
#define uchar unsigned char
#define uint unsigned int 
	
#define uint8 unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int
	
//----------------------------------------
//全局中断宏定义
#define CPU_INT_DISABLE()  {__set_PRIMASK(1);}              //关闭中断
#define CPU_INT_ENABLE()   {__set_PRIMASK(0);}              //打开中断

typedef enum //定义消息枚举类型
{
	MSG_NULL = 0,
	/******************************/
	//添加用户消息常量，例如：MSG_XXX,
	MSG_KEY1_PRESS,
	MSG_KEY2_PRESS,
	
	
	/******************************/
	MSG_NUM
	
}MSG_TYPE;

//头文件被多个C调用时，避免变量冲突问题
#ifdef MAIN_CONFIG  
	#define EXT
#else 
	#define EXT extern
#endif
	
//RTOS相关头文件包含
#include <rthw.h>
#include <rtthread.h>
#include "Task.h"                                           //自定义文件，Task.c中存放线程、定时器、IPC等相关代码
	
//常用头文件包含
#include "VTM071x.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdarg.h"
#include "stdbool.h"
	
//外设驱动头文件包含
#include "system.h"
#include "SysTick.h"
#include "Gpio.h"
#include "Led.h"
#include "Beep.h"
#include "USart.h"
#include "Exti.h"
#include "BspTimer.h"
#include "Button.h"
#include "Adc.h"
#include "BspEsp8266.h"  //ESP8226 WIFI模块头文件

#include "oled.h"
#include "BMI160.h"
#include "LM75BD.h"
//应用相关头文件包含
#include "WeatherInfo.h"
#include "NtpExample.h"
#include "TemperatureUploadLocalSer.h"
#include "WifiCmdTest.h"


//全局变量定义,请使用EXT修饰
EXT unsigned char g_Var;	
EXT rt_sem_t usart1_recv_sem;                               //定义串口2接收信号量控制块指针
EXT rt_mq_t  msg_mq;                                        //定义消息队列控制块
EXT rt_timer_t ADCProcessSoftTimer;                         //软件定时器控制块指针

//功能开关宏定义	开启后注意RAM空间的使用情况
#define	USING_TASKINIT		1//开启线程初始化
#define	USING_MEMPOOL	0//内存管理
#define	USING_MAILBOX	0//邮箱管理
#define	USING_BUTTON	0//按键扫描

#define	Gyroscope	//使用陀螺仪
