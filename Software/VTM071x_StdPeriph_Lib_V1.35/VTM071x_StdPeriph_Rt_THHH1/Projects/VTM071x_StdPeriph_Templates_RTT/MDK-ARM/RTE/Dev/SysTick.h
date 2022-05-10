/*
*****************************************************************************
    功能：SYSTICK的初始化
    时间：2022.02.16
    人员：wjonas
    修改记录：
        wjonas 2022.02.16  修改
*****************************************************************************
*/ 
#include "rtdef.h"

/************************************************************
功能：SYSTICK初始化
时间：2022.02.16
人员：wjonas
入参：无
出参：无
************************************************************/
void SysTickInit(void);

/************************************************************
功能：系统滴答微秒延时
时间：2022.02.16
人员：wjonas
入参：us
出参：无
************************************************************/
void rt_hw_us_delay(rt_uint32_t us);//系统滴答微秒延时
/************************************************************
功能：系统滴答毫秒延时
时间：2022.02.25
人员：th
入参：us
出参：无
************************************************************/
void rt_hw_ms_delay(rt_uint32_t ms);//系统滴答毫秒延时

