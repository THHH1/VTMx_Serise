/*
*****************************************************************************
    功能：main 函数
    时间：2022.02.15
    人员：wjonas
    修改记录：
        wjonas 2022.02.15  修改
*****************************************************************************
*/  
#include "config.h"

/************************************************************
功能：主函数
时间：2022.02.15
人员：wjonas
入参：无
出参：无
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

