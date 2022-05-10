/* RT-Thread config file */
//add #define RT_USING_PIN-1213
//add #define SOC_SERIES_MT071








#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Basic Configuration
// <o>Maximal level of thread priority <8-256>
//  <i>Default: 32
#define RT_THREAD_PRIORITY_MAX  32	//����ϵͳ������ȼ���������8��256��Ĭ��ֵ32
// <o>OS tick per second
//  <i>Default: 1000   (1ms)
#define RT_TICK_PER_SECOND  1000	//Ĭ��100��һ������10ms��ʱ�ӽ���Խ�죬ϵͳ�Ķ��⿪����Խ��
// <o>Alignment size for CPU architecture data access
//  <i>Default: 4
#define RT_ALIGN_SIZE   4			//�ֽڶ���ʱ�趨������ֽڸ�����Ĭ��4
// <o>the max length of object name<2-16>
//  <i>Default: 8
#define RT_NAME_MAX    16			//���ö������Ƶ���󳤶ȣ�Ĭ��Ϊ8���ַ�
// <c1>Using RT-Thread components initialization
//  <i>Using RT-Thread components initialization
#define RT_USING_COMPONENTS_INIT	//����ʹ������Զ���ʼ�����ܣ�Ĭ����Ҫʹ�ã������ú������ʹ���Զ���ʼ�����ܡ�
// </c>

#define RT_USING_USER_MAIN			//���� RT_USING_USER_MAIN �꣬��� user_main ���ܣ�Ĭ����Ҫ�������������ܵ��� RT-Thread ���������룻main �̵߳�ջ��С���޸ġ�

// <o>the stack size of main thread<1-4086>
//  <i>Default: 512
#define RT_MAIN_THREAD_STACK_SIZE     512

// </h>

// <h>Debug Configuration
// <c1>enable kernel debug configuration
//  <i>Default: enable kernel debug configuration
//#define RT_DEBUG					// �ر� debug
// </c>
// <o>enable components initialization debug configuration<0-1>
//  <i>Default: 0
#define RT_DEBUG_INIT 0				// ���������ʼ���������ã�����Ϊ 1 ����ӡ�Զ���ʼ���ĺ�������
// <c1>thread stack over flow detect
//  <i> Diable Thread stack over flow detect
//#define RT_USING_OVERFLOW_CHECK	// �ر�ջ������
// </c>
// </h>

// <h>Hook Configuration
// <c1>using hook
//  <i>using hook
#define RT_USING_HOOK				// �Ƿ� ����ϵͳ���ӹ���
// </c>
// <c1>using idle hook
//  <i>using idle hook
#define RT_USING_IDLE_HOOK		// �Ƿ� ���������̹߳��ӹ���
// </c>
// </h>

// <e>Software timers Configuration
// <i> Enables user timers
#define RT_USING_TIMER_SOFT         0	// �ر������ʱ�����ܣ�Ϊ 1 ���
#if RT_USING_TIMER_SOFT == 0
    #undef RT_USING_TIMER_SOFT
#endif
// <o>The priority level of timer thread <0-31>
//  <i>Default: 4
#define RT_TIMER_THREAD_PRIO        4	// ���������ʱ���̵߳����ȼ���Ĭ��Ϊ 4
// <o>The stack size of timer thread <0-8192>
//  <i>Default: 512
#define RT_TIMER_THREAD_STACK_SIZE  512	// ���������ʱ���̵߳�ջ��С��Ĭ��Ϊ 512 �ֽ�
// </e>

// <h>IPC(Inter-process communication) Configuration
// <c1>Using Semaphore
//  <i>Using Semaphore
#define RT_USING_SEMAPHORE			// �����Ƿ�ʹ�� �ź�����Ĭ�ϴ�
// </c>
// <c1>Using Mutex
//  <i>Using Mutex
#define RT_USING_MUTEX			// �����Ƿ�ʹ�� ������
// </c>
// <c1>Using Event
//  <i>Using Event
#define RT_USING_EVENT			// �����Ƿ�ʹ�� �¼���
// </c>
// <c1>Using MailBox
//  <i>Using MailBox
#define RT_USING_MAILBOX			// �����Ƿ�ʹ��  ����
// </c>
// <c1>Using Message Queue
//  <i>Using Message Queue
#define RT_USING_MESSAGEQUEUE		// �����Ƿ�ʹ�� ��Ϣ����
// </c>
// </h>

// <h>Memory Management Configuration
// <c1>Memory Pool Management
//  <i>Memory Pool Management
//#define RT_USING_MEMPOOL			// �Ƿ�ʹ�� �ڴ��
// </c>
// <c1>Dynamic Heap Management(Algorithm: small memory )
//  <i>Dynamic Heap Management
#define RT_USING_HEAP				// �Ƿ�ʹ�� �ڴ��
#define RT_USING_SMALL_MEM			// �Ƿ�ʹ�� С�ڴ����
// </c>
// <c1>using tiny size of memory
//  <i>using tiny size of memory
//#define RT_USING_TINY_SIZE		// �Ƿ�ʹ�� С������㷨��ǣ���� rt_memset��rt_memcpy �����������
// </c>
// </h>

// <h>Console Configuration
// <c1>Using console
//  <i>Using console
#define RT_USING_CONSOLE			//����̨����
// </c>
// <o>the buffer size of console <1-1024>
//  <i>the buffer size of console
//  <i>Default: 128  (128Byte)
#define RT_CONSOLEBUF_SIZE          256
// </h>

// <h>FinSH Configuration
// <c1>include finsh config
//  <i>Select this choice if you using FinSH 
#include "finsh_config.h"
// </c>
// </h>

// <h>Device Configuration
// <c1>using device framework
//  <i>using device framework
#define RT_USING_DEVICE				//���������򽫼��� device ���Դ�롣
#define RT_CONSOLE_DEVICE_NAME "uart0"
#define RT_USING_PIN
#define SOC_SERIES_MT071
// </c>
// </h>

// <<< end of configuration section >>>

#endif
