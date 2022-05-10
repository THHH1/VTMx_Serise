#include "config.h"
#include "Button.h"

/*
*****************************************************************************
    ���ܣ�ɨ�谴��
    ʱ�䣺2022.02.12
    ��Ա��th
    �޸ļ�¼��
        th 2022.02.12  �޸�
*****************************************************************************
*/
//-----------------------------------------------------------------------------------------------
// �����߳���ز����궨��
#define BUTTON_THREAD_STACK_SIZE 512
#define BUTTON_THREAD_PRIORITY   5

//-----------------------------------------------------------------------------------------------
// �����¼�����

static rt_mq_t button_mq = RT_NULL;//�����¼����ж���

//-----------------------------------------------------------------------------------------------
// ��������
static Button_t s_tBtnKey1;			
static Button_t s_tBtnKey2;		
static Button_t s_tBtnKey3;	
/****************************************************************************************/
//�û�����Զ���ӿڱ���	

/****************************************************************************************/
//-------------------------------------------------------------------------------
// Key1 ��������
#define GPIO_Pin_Key1				GPIO_Pin_4                  
#define GPIO_Mode_Key1				GPIO_Mode_IN  
#define GPIO_Key1				  	GPIO4                     
#define Key1In					  	GPIO_ReadDataBit(GPIO_Key1, GPIO_Pin_Key1)	
//-------------------------------------------------------------------------------
// Key2 ��������
#define GPIO_Pin_Key2				GPIO_Pin_5                 
#define GPIO_Mode_Key2				GPIO_Mode_IN  
#define GPIO_Key2					GPIO4                   
#define Key2In						GPIO_ReadDataBit(GPIO_Key2	, GPIO_Pin_Key2)
//-------------------------------------------------------------------------------
// Key3 ��������
#define GPIO_Pin_Key3				GPIO_Pin_0                
#define GPIO_Mode_Key3				GPIO_Mode_IN  
#define GPIO_Key3					GPIO2                     
#define Key3In						GPIO_ReadDataBit(GPIO_Key3	, GPIO_Pin_Key3)		
/****************************************************************************************/
//�û�����Զ��尴���ӿ�	

/****************************************************************************************/


//-----------------------------------------------------------------------------------------------
// Key��������ʱ�ĵ�ƽ��=0,����ʱΪ�͵�ƽ;=1,����ʱΪ�ߵ�ƽ
#define KeyPressedLevel 0
//-----------------------------------------------------------------------------------------------
// ��ȡ�������º���	
static unsigned char IsKey1Down(void) 		{if (Key1In != KeyPressedLevel) return 0; return 1;}
static unsigned char IsKey2Down(void) 		{if (Key2In != KeyPressedLevel) return 0; return 1;}
static unsigned char IsKey3Down(void) 		{if (Key3In != KeyPressedLevel) return 0; return 1;}


/*******************************************************************************************************
** ����: ButtonGpioInit,Button������ʼ������
**------------------------------------------------------------------------------------------------------
** ����: void
** ����: void
********************************************************************************************************/
static void ButtonGpioInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//-------------------------------------------------------------------------------------------	
	// ��Ӧ����ʱ����GPIO����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Key1;					//ʹ��GPIO0_2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;				//����Ƶ��Ϊ50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					//����ģʽΪ����ģʽ
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;					//����ģʽΪ��������ģʽ
    GPIO_Init(GPIO4, &GPIO_InitStructure);							//GPIO0_2
	//-------------------------------------------------------------------------------------------
	// ��Ӧ����ʱ����GPIO���� 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Key2;					//ʹ��GPIO0_3
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;				//����Ƶ��Ϊ50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					//����ģʽΪ����ģʽ
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;					//����ģʽΪ��������ģʽ
    GPIO_Init(GPIO4, &GPIO_InitStructure);							//GPIO0_3				
	//-------------------------------------------------------------------------------------------
	// ��Ӧ����ʱ����GPIO���� 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Key3;					//ʹ��GPIO0_4
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;				//����Ƶ��Ϊ50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					//����ģʽΪ����ģʽ
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;					//����ģʽΪ��������ģʽ
    GPIO_Init(GPIO2, &GPIO_InitStructure);							//GPIO0_4
	/****************************************************************************************/
	//�û�����Զ��尴������	

	/****************************************************************************************/
}

/*******************************************************************************************************
** ����: ButtonVarInit,��ʼ����������
**------------------------------------------------------------------------------------------------------
** ����: void
** ����: void
********************************************************************************************************/
static void ButtonVarInit(void)
{
	s_tBtnKey1.IsKeyDownFunc=IsKey1Down;							// ��ⰴ�����º���
	s_tBtnKey1.wFilterCount=0;										// �˲��������� 
	s_tBtnKey1.wFilterTime =BUTTON_FILTER_TIME;						// �˲�ʱ�� 
	s_tBtnKey1.wLongCount =0;										// ���������� 
	s_tBtnKey1.wLongTime=BUTTON_LONG_TIME;							// ����ʱ�� 	
	s_tBtnKey1.byState=0;											// ������ǰ״̬�����»��ǵ���
	s_tBtnKey1.byKeyCodeUp=KEY1_UP;									// ��������ļ�ֵ����, 0��ʾ����ⰴ������ 
	s_tBtnKey1.byKeyCodeDown=KEY1_DOWN;								// �������µļ�ֵ����, 0��ʾ����ⰴ������
	s_tBtnKey1.byKeyCodeLong=KEY1_LONG;								// ���������ļ�ֵ����, 0��ʾ����ⳤ�� 
	
	s_tBtnKey2.IsKeyDownFunc=IsKey2Down;							// ��ⰴ�����º���
	s_tBtnKey2.wFilterCount=0;										// �˲��������� 
	s_tBtnKey2.wFilterTime =BUTTON_FILTER_TIME;						// �˲�ʱ�� 
	s_tBtnKey2.wLongCount =0;										// ���������� 
	s_tBtnKey2.wLongTime=BUTTON_LONG_TIME;							// ����ʱ�� 	
	s_tBtnKey2.byState=0;											// ������ǰ״̬�����»��ǵ���
	s_tBtnKey2.byKeyCodeUp=KEY2_UP;									// ��������ļ�ֵ����, 0��ʾ����ⰴ������ 
	s_tBtnKey2.byKeyCodeDown=KEY2_DOWN;								// �������µļ�ֵ����, 0��ʾ����ⰴ������
	s_tBtnKey2.byKeyCodeLong=KEY2_LONG;								// ���������ļ�ֵ����, 0��ʾ����ⳤ�� 

	s_tBtnKey3.IsKeyDownFunc=IsKey3Down;							// ��ⰴ�����º���
	s_tBtnKey3.wFilterCount=0;										// �˲��������� 
	s_tBtnKey3.wFilterTime =BUTTON_FILTER_TIME;						// �˲�ʱ�� 
	s_tBtnKey3.wLongCount =0;										// ���������� 
	s_tBtnKey3.wLongTime=BUTTON_LONG_TIME;							// ����ʱ�� 	
	s_tBtnKey3.byState=0;											// ������ǰ״̬�����»��ǵ���
	s_tBtnKey3.byKeyCodeUp=KEY3_UP;									// ��������ļ�ֵ����, 0��ʾ����ⰴ������ 
	s_tBtnKey3.byKeyCodeDown=KEY3_DOWN;								// �������µļ�ֵ����, 0��ʾ����ⰴ������
	s_tBtnKey3.byKeyCodeLong=KEY3_LONG;								// ���������ļ�ֵ����, 0��ʾ����ⳤ�� 

	/****************************************************************************************/
	//�û�����Զ��尴��������ʼ��

	/****************************************************************************************/
}



/*******************************************************************************************************
** ����: ButtonDetect,Button������⺯��
**------------------------------------------------------------------------------------------------------
** ����: ptBtn �����ṹ��ָ��
** ����: void
********************************************************************************************************/
static void ButtonDetect(Button_t *ptBtn)
{
	if(ptBtn->IsKeyDownFunc && ptBtn->IsKeyDownFunc()) 				// ��ⰴ�������Ƿ���ڣ������Ƿ���
	{
		if(ptBtn->wFilterCount < ptBtn->wFilterTime)				// �˲���⣬�˲������������˲�ʱ��
		{
			ptBtn->wFilterCount++;									// ��������һ
			return;													// �˳���⺯��
		}		
		if(ptBtn->byState ==0 ) 									// ����Ƿ��ǰ�������							
		{
			ptBtn->byState = 1;
			rt_mq_send(button_mq,									// д�루���ͣ����е�ID(���)
								&(ptBtn->byKeyCodeDown),  			// д�루���ͣ�����������Ӧ��ַ 
								sizeof(ptBtn->byKeyCodeDown)		// ���ݵĳ��� 
								);
			return;
		}
		if( ptBtn->wLongCount++ == ptBtn->wLongTime) 				// ����Ƿ��ǰ��������������������Ƿ񵽴ﳤ��ʱ��
		{
			rt_mq_send(button_mq,									// д�루���ͣ����е�ID(���)
								&(ptBtn->byKeyCodeLong),  			// д�루���ͣ�����������Ӧ��ַ 
								sizeof(ptBtn->byKeyCodeLong)		// ���ݵĳ��� 
								);
			return;
		}			
	}
	else 
	{		
		if(ptBtn->wFilterCount) 									// �˲���⣬�˲��������Ƿ�Ϊ0
		{
			ptBtn->wFilterCount--;									// ��������һ
			return;													// �˳���⺯��
		}			
		
		if(ptBtn->byState ==1 )										// ����Ƿ��ǰ�������
		{
			ptBtn->byState =0; 										
			rt_mq_send(button_mq,									// д�루���ͣ����е�ID(���)
								&(ptBtn->byKeyCodeUp),  			// д�루���ͣ�����������Ӧ��ַ 
								sizeof(ptBtn->byKeyCodeUp)			// ���ݵĳ��� 
								);
		}
		ptBtn->wLongCount = 0;										// ������������������
	}
	
}





/*******************************************************************************************************
** ����: ButtonInit,Button��ʼ��
**------------------------------------------------------------------------------------------------------
** ����: void
** ����: void
********************************************************************************************************/
void ButtonInit(void)
{
	ButtonGpioInit();												// Button ����GPIO��ʼ��
	ButtonVarInit();												// Button �������ó�ʼ��
}

/*******************************************************************************************************
** ����: ButtonProj,��������ɨ�裩����
**------------------------------------------------------------------------------------------------------
** ����: void
** ����: void
********************************************************************************************************/
void ButtonProj(void)
{
	//�ú����ڶ�ʱ���жϻص������е��ã���ʱ�ж�����Ϊ1ms
	ButtonDetect(&s_tBtnKey1);										// ��� K1 �� 
	ButtonDetect(&s_tBtnKey2);										// ��� K2 �� 
	ButtonDetect(&s_tBtnKey3);										// ��� K3 �� 
	/****************************************************************************************/
	//�û�����Զ��尴��������ʼ��
    //���磺ButtonDetect(&s_tBtnKeyN);	
	
	/****************************************************************************************/
}


/*******************************************************************************************************
** ����: button_thread_entry,��ȡ�����¼������д���
**------------------------------------------------------------------------------------------------------
** ����: void
** ����: void
********************************************************************************************************/


void button_thread_entry(void *parameter)//�û���Ϣ������ں���
{
	rt_err_t uwRet = RT_EOK;
	uint8_t r_queue;//���ڽ���msg_mq��Ϣ������Ϣ
	uint32_t AdcSoftTimerPeriod = 0;//�洢ADC�����ʱ������ֵ
	uint8_t  AdcSoftTimerStatus = 0;//ADC�����ʱ��״̬��=0,ֹͣ;=1,����
	
	button_mq = rt_mq_create("button_mq",							//��Ϣ��������
								1,  									//��Ϣ����󳤶�, bytes
								256,										//��Ϣ���е��������(����)
								RT_IPC_FLAG_FIFO			//����ģʽ FIFO
								);
	if(button_mq != RT_NULL)
		rt_kprintf("button_mq create success\n\n");
	
	ButtonInit();//����Ӳ���ӿڳ�ʼ��
	
	while(1)
	{  //��ȡ������Ϣ
		uwRet = rt_mq_recv(button_mq,
								&r_queue,
								sizeof(r_queue),
								RT_WAITING_FOREVER
								);
		if(RT_EOK == uwRet )
		{
			switch(r_queue)//���ݽ��յ�����Ϣ���ݷֱ���д���
			{
				case KEY1_DOWN:
					rt_kprintf("\nReceive message:KEY1(PE.3) Down\n");
					if(AdcSoftTimerStatus == 0)
					{
						rt_kprintf("ADCProcessSoftTimer Start!\n\n");
						rt_timer_start(ADCProcessSoftTimer);
						AdcSoftTimerStatus = !AdcSoftTimerStatus;
					}
					else
					{
						rt_kprintf("ADCProcessSoftTimer Stop!\n\n");
						rt_timer_stop(ADCProcessSoftTimer);
						AdcSoftTimerStatus = !AdcSoftTimerStatus;
					}
					break;
				case KEY1_UP:
					break;
				case KEY1_LONG:
					break;
				case KEY2_DOWN:
					rt_kprintf("\nReceive message:KEY2(PE.2) Down\n");
					rt_timer_control(ADCProcessSoftTimer, RT_TIMER_CTRL_GET_TIME, (void *)&AdcSoftTimerPeriod); 
					AdcSoftTimerPeriod += 2*RT_TICK_PER_SECOND;
					rt_timer_control(ADCProcessSoftTimer, RT_TIMER_CTRL_SET_TIME, (void *)&AdcSoftTimerPeriod);
					rt_kprintf("ADCProcessSoftTimer Period is Added,Now is:%d\n\n",AdcSoftTimerPeriod /RT_TICK_PER_SECOND);
					break;
				case KEY2_UP:
					break;
				case KEY2_LONG:
					break;
				case KEY3_DOWN:
					rt_kprintf("\nReceive message:KEY3(PE.4) Down\n");
					rt_timer_control(ADCProcessSoftTimer, RT_TIMER_CTRL_GET_TIME, (void *)&AdcSoftTimerPeriod); 
					if(AdcSoftTimerPeriod > 2*RT_TICK_PER_SECOND)
					{   
						AdcSoftTimerPeriod -= 2*RT_TICK_PER_SECOND;	
						rt_timer_control(ADCProcessSoftTimer, RT_TIMER_CTRL_SET_TIME, (void *)&AdcSoftTimerPeriod);
						rt_kprintf("ADCProcessSoftTimer Period is subtracted,Now is:%d\n\n",AdcSoftTimerPeriod /RT_TICK_PER_SECOND);
					}
					else
					rt_kprintf("ADCProcessSoftTimer Period Low Limited!\n\n"); 
					break;
				case   KEY3_UP:
					break;
				case KEY3_LONG:
					break;
				default:
					break;

			}

		}
		else
		{
			rt_kprintf("���ݽ��մ��󣬴�����룺0x%lx\n\n",uwRet);
		}
	}	
}
int button_process_init(void)
{
    rt_thread_t tid;


    tid = rt_thread_create("button_process",
                           button_thread_entry, RT_NULL,
                           BUTTON_THREAD_STACK_SIZE, BUTTON_THREAD_PRIORITY, 10);


    if (tid != NULL)
        rt_thread_startup(tid);
    return 0;
}
INIT_APP_EXPORT(button_process_init);









/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
