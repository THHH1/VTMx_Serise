/*
*****************************************************************************
    ���ܣ�main ����
    ʱ�䣺2022.02.15
    ��Ա��wjonas
    �޸ļ�¼��
        wjonas 2022.02.15  �޸�
*****************************************************************************
*/  
#include "config.h"

/************************************************************
���ܣ�������
ʱ�䣺2022.02.15
��Ա��wjonas
��Σ���
���Σ���
************************************************************/
int main()
{	
#if	USING_TASKINIT	
	TaskInit();
#endif	
	while(1)
	{
		rt_thread_mdelay(1000);
        LedControl(Led0_num,1);
        BeepControl(1);
		rt_thread_mdelay(1000);
        LedControl(Led0_num,0);	
        BeepControl(0);        
	}	
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);
    while (1)
    {
    }
}
#endif

