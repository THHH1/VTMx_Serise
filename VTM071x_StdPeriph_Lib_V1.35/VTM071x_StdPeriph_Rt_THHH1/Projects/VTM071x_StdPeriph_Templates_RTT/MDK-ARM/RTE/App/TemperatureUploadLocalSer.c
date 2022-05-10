#include "config.h"
#include "TemperatureUploadLocalSer.h"

/*
*****************************************************************************
    ���ܣ������ϴ������ط�����
    ʱ�䣺2022.03.03
    ��Ա��th
    �޸ļ�¼��
        th 2022.03.03  �޸�
*****************************************************************************
*/ 

static rt_timer_t Ds18B20ProcessSoftTimer;
static char SendData[30];//�����������İ����ݴ�����
static	float  temprture=36.7;
static void Ds18B20ProcessSoftTimer_callback(void* parameter)
{
//	sprintf(SendData,"\r\nTemperature�� %.1f\r\n",DS18B20_GetTemp_SkipRom());
	sprintf(SendData,"\r\nTemperature�� %.1f\r\n",temprture);
  ESP8266_SendString ( ENABLE, SendData, strlen(SendData), Single_ID_0 );
//   printf ( "\r\nTemperature�� %.1f\r\n", DS18B20_GetTemp_SkipRom() );
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
	
	Ds18B20ProcessSoftTimer = rt_timer_create("Ds18B20ProcessSoftTimer", /* �����ʱ�������� */
                        Ds18B20ProcessSoftTimer_callback,/* �����ʱ���Ļص����� */
                        0,			/* ��ʱ����ʱ��������ڲ��� */
                        5*RT_TICK_PER_SECOND,   /* �����ʱ���ĳ�ʱʱ��(���ڻص�ʱ��) */
                        RT_TIMER_FLAG_PERIODIC );
                        /* �����ʱ��HARD_TIMERģʽ ����ģʽ */
	return 0;
}
MSH_CMD_EXPORT(SensorDataSendToServerInit, Temperature Data Sendto Server Init.);



