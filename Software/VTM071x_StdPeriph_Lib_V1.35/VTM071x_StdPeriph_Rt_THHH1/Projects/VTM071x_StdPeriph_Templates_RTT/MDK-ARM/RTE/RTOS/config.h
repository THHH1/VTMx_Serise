/*
*****************************************************************************
    ���ܣ�ȫ������
    ʱ�䣺2022.02.17
    ��Ա��wjonas
    �޸ļ�¼��
        wjonas 2022.02.17  �޸�
*****************************************************************************
*/ 
//�޷������͵Ķ���
#define uchar unsigned char
#define uint unsigned int 
	
#define uint8 unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int
	
//----------------------------------------
//ȫ���жϺ궨��
#define CPU_INT_DISABLE()  {__set_PRIMASK(1);}              //�ر��ж�
#define CPU_INT_ENABLE()   {__set_PRIMASK(0);}              //���ж�

typedef enum //������Ϣö������
{
	MSG_NULL = 0,
	/******************************/
	//����û���Ϣ���������磺MSG_XXX,
	MSG_KEY1_PRESS,
	MSG_KEY2_PRESS,
	
	
	/******************************/
	MSG_NUM
	
}MSG_TYPE;

//ͷ�ļ������C����ʱ�����������ͻ����
#ifdef MAIN_CONFIG  
	#define EXT
#else 
	#define EXT extern
#endif
	
//RTOS���ͷ�ļ�����
#include <rthw.h>
#include <rtthread.h>
#include "Task.h"                                           //�Զ����ļ���Task.c�д���̡߳���ʱ����IPC����ش���
	
//����ͷ�ļ�����
#include "VTM071x.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdarg.h"
#include "stdbool.h"
	
//��������ͷ�ļ�����
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
#include "BspEsp8266.h"  //ESP8226 WIFIģ��ͷ�ļ�

#include "oled.h"
#include "BMI160.h"
#include "LM75BD.h"
//Ӧ�����ͷ�ļ�����
#include "WeatherInfo.h"
#include "NtpExample.h"
#include "TemperatureUploadLocalSer.h"
#include "WifiCmdTest.h"


//ȫ�ֱ�������,��ʹ��EXT����
EXT unsigned char g_Var;	
EXT rt_sem_t usart1_recv_sem;                               //���崮��2�����ź������ƿ�ָ��
EXT rt_mq_t  msg_mq;                                        //������Ϣ���п��ƿ�
EXT rt_timer_t ADCProcessSoftTimer;                         //�����ʱ�����ƿ�ָ��

//���ܿ��غ궨��	������ע��RAM�ռ��ʹ�����
#define	USING_TASKINIT		1//�����̳߳�ʼ��
#define	USING_MEMPOOL	0//�ڴ����
#define	USING_MAILBOX	0//�������
#define	USING_BUTTON	0//����ɨ��

#define	Gyroscope	//ʹ��������
