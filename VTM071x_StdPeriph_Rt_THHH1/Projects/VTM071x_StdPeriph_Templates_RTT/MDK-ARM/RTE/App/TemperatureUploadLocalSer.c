#include "config.h"
#include "TemperatureUploadLocalSer.h"

/*
*****************************************************************************
    功能：数据上传至本地服务器
    时间：2022.03.03
    人员：th
    修改记录：
        th 2022.03.03  修改
*****************************************************************************
*/ 

static rt_timer_t Ds18B20ProcessSoftTimer;
static char SendData[30];//发往服务器的包，暂存数组
static	float  temprture=36.7;
static void Ds18B20ProcessSoftTimer_callback(void* parameter)
{
//	sprintf(SendData,"\r\nTemperature： %.1f\r\n",DS18B20_GetTemp_SkipRom());
	sprintf(SendData,"\r\nTemperature： %.1f\r\n",temprture);
  ESP8266_SendString ( ENABLE, SendData, strlen(SendData), Single_ID_0 );
//   printf ( "\r\nTemperature： %.1f\r\n", DS18B20_GetTemp_SkipRom() );
}

static void SensorDataUploadCycle(void* parameter)
{
	rt_timer_start(Ds18B20ProcessSoftTimer);
}
MSH_CMD_EXPORT(SensorDataUploadCycle,SensorDataUploadCycle.);

static void SensorDataUploadStop(void* parameter)
{
	rt_timer_stop(Ds18B20ProcessSoftTimer);
}
MSH_CMD_EXPORT(SensorDataUploadStop,SensorDataUploadStop.);

int SensorDataSendToServerInit()
{
	
	Ds18B20ProcessSoftTimer = rt_timer_create("Ds18B20ProcessSoftTimer", /* 软件定时器的名称 */
                        Ds18B20ProcessSoftTimer_callback,/* 软件定时器的回调函数 */
                        0,			/* 定时器超时函数的入口参数 */
                        5*RT_TICK_PER_SECOND,   /* 软件定时器的超时时间(周期回调时间) */
                        RT_TIMER_FLAG_PERIODIC );
                        /* 软件定时器HARD_TIMER模式 周期模式 */
	return 0;
}
MSH_CMD_EXPORT(SensorDataSendToServerInit, Temperature Data Sendto Server Init.);



