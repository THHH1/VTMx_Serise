#include "config.h"
#include "system.h"


//void CpuInit(void)
//{
//	//CPU�������
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ѡ���2���ж����ȼ�����2λ�����ȼ���2λ�����ȼ�
//	
//}

void SysInit(void)
{
	
//	CpuInit();//����ϵͳ��Ϣ
	
	//����������ʼ��
	SysTickInit();//ϵͳ�δ�ʱ����ʼ��
	LedGpioInit();//LED��ʼ��
	UsartInit();//���ڳ�ʼ��
	ExtiInit();//�ⲿ�жϳ�ʼ��
	Timer_Configuration();//�ж�����Ϊ1ms,���ڰ���ɨ��

		
}




