#ifndef  __CONFIG_H__
#define  __CONFIG_H__

//�޷������͵Ķ���
#define uchar unsigned char
#define uint unsigned int 
	
#define uint8 unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int
	
//----------------------------------------


//ȫ�ֺ궨��
#define CPU_INT_DISABLE()  {__set_PRIMASK(1);} //�ر��ж�
#define CPU_INT_ENABLE()   {__set_PRIMASK(0);}  //���ж�

//ȫ�����Ͷ���
typedef enum{FALSE = 0, TRUE = !FALSE}BOOL;

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

//-------------------------------------
#ifdef MAIN_CONFIG  //ͷ�ļ������C����ʱ�����������ͻ����
	#define EXT
#else 
	#define EXT extern
#endif
	
//-------------------------------------
//RTOS���ͷ�ļ�����
#include <rthw.h>
#include <rtthread.h>
#include "Task.h"//�Զ����ļ���Task.c�д���̡߳���ʱ����IPC����ش���
	
	
//-------------------------------------
	
//����ͷ�ļ�����
#include "VTM071x.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
	
//-------------------------------------
	
//��������ͷ�ļ�����
#include "system.h"
#include "SysTick.h"
#include "Gpio.h"
#include "USart.h"
#include "Exti.h"
#include "BspTimer.h"
#include "Button.h"
	

		
//----------------------------------------
//ȫ�ֱ�������,��ʹ��EXT����
EXT unsigned char g_Var;	
EXT rt_sem_t usart1_recv_sem;//���崮��2�����ź������ƿ�ָ��
EXT rt_mq_t  msg_mq;//������Ϣ���п��ƿ�
EXT rt_timer_t ADCProcessSoftTimer;//�����ʱ�����ƿ�ָ��
//----------------------------------------
#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/



