#include "config.h"
#include "WeatherInfo.h"
#include "CJSON.h"

	


/* ��֪������api.seniverse.com��--�������ݵ���Դ */
#define WEATHER_IP 		"116.62.81.138"
#define WEATHER_PORT 	"80"



/* ����һЩȫ�ֱ��� */
//------------------------------------------------------------------------------------------
//����Ҫ����������,������Ӧ��ʹ��
WeatherType weather_data;


/********************************************************************************************************
** ����: cJSON_NowWeatherParse, ��������ʵ�����ݰ�now.json
**------------------------------------------------------------------------------------------------------
** ����: JSON:����ʵ�����ݰ�  WeatherType:�洢�����õ������õ�����
** ˵��: ������Դ����֪������api.seniverse.com��
** ����: 0:�����ɹ� ����������ʧ��		
** ����: 2022.03.04 by th
********************************************************************************************************/

static int cJSON_NowWeatherParse(char *JSON, WeatherType *result)
{

	cJSON *json,*arrayItem,*object,*subobject,*item;

	
//printf("Receive now data:%s\r\n",JSON);
 
	json = cJSON_Parse(JSON);//����JSON���ݰ�
	if(json == NULL)		  //���JSON���ݰ��Ƿ�����﷨�ϵĴ��󣬷���NULL��ʾ���ݰ���Ч
	{
		rt_kprintf("Error before: [%s]\r\n",cJSON_GetErrorPtr()); //��ӡ���ݰ��﷨�����λ��
		return 1;
	}
	else
	{
		if((arrayItem = cJSON_GetObjectItem(json,"results")) != NULL) //ƥ���ַ���"results",��ȡ��������
		{
			int size = cJSON_GetArraySize(arrayItem);     //��ȡ�����ж������
//			printf("cJSON_GetArraySize: size=%d\n",size); 
			
			if((object = cJSON_GetArrayItem(arrayItem,0)) != NULL)//��ȡ����������
			{
        rt_kprintf("--------------------------------Now Weather Data Begin------------------------------\r\n");
				/* ƥ���Ӷ���1 */
				if((subobject = cJSON_GetObjectItem(object,"location")) != NULL)
				{
					
					rt_kprintf("---------------------------------subobject1-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"id")) != NULL)   
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string,item->valuestring);
					}
					if((item = cJSON_GetObjectItem(subobject,"name")) != NULL) //����--��Ҫ�õ�������
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string,item->valuestring);
						sprintf(weather_data .name,"%s",item->valuestring);
					}
					if((item = cJSON_GetObjectItem(subobject,"country")) != NULL)
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string,item->valuestring);
					}
					if((item = cJSON_GetObjectItem(subobject,"path")) != NULL)  
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string,item->valuestring);
					}
					if((item = cJSON_GetObjectItem(subobject,"timezone")) != NULL)
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string,item->valuestring);
					}
					if((item = cJSON_GetObjectItem(subobject,"timezone_offset")) != NULL)
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string,item->valuestring);
					}
				}
				/* ƥ���Ӷ���2 */
				if((subobject = cJSON_GetObjectItem(object,"now")) != NULL)
				{
					rt_kprintf("---------------------------------subobject2-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"text")) != NULL)//����Ԥ������--��Ҫ�õ�������
					{
						 rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string,item->valuestring);
						sprintf(weather_data .text,"%s",item->valuestring);
					}
					if((item = cJSON_GetObjectItem(subobject,"code")) != NULL)//����Ԥ������--��Ҫ�õ�������
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string, item->valuestring);
						sprintf(weather_data .code,"%s",item->valuestring);
						rt_kprintf("%d\n",weather_data .code[0]);rt_kprintf("%d\n",weather_data .code[1]);
					}
					if((item = cJSON_GetObjectItem(subobject,"temperature")) != NULL) //�¶�--��Ҫ�õ�������
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string, item->valuestring);
						sprintf(weather_data .temperature,"%s",item->valuestring);
					}
				}
				/* ƥ���Ӷ���3 */
				if((subobject = cJSON_GetObjectItem(object,"last_update")) != NULL)
				{
					rt_kprintf("---------------------------------subobject3-------------------------------\r\n");
					rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",subobject->string,subobject->valuestring);
				}
				rt_kprintf("--------------------------------Now Weather Data End--------------------------------\r\n");
			} 
		
		}
	}
	
	cJSON_Delete(json); //�ͷ�cJSON_Parse()����������ڴ�ռ�


	return 0;

}	


/********************************************************************************************************
** ����: GetNowWeather, GET ����ʵ�����ݰ�now.json
**------------------------------------------------------------------------------------------------------
** ����: void
** ˵��: ������Դ����֪������api.seniverse.com��
** ����: 0:��ȡ�ɹ� ��������ȡʧ��	
** ����: 2022.03.04 by th
********************************************************************************************************/
int GetNowWeather(void)
{

	ESP8266_Link_Server(enumTCP, (char*)WEATHER_IP, (char*)WEATHER_PORT,Single_ID_0);//TCP
	ESP8266_UnvarnishSend ();//����ģʽΪ��͸��	

//	macESP8266_Usart ( "GET https://api.seniverse.com/v3/weather/now.json?"
//	"key=2owqvhhd2dd9o9f9&location=%s&language=zh-Hans&unit=c\r\n\r\n","fuzhou" );
	macESP8266_Usart ( "GET https://api.seniverse.com/v3/weather/now.json?key=ragjskuzlv5jzerq&location=hefei\r\n\r\n");//�Ը�������Ϊ���ӻ�ȡ

	strEsp8266_Fram_Record .InfBit .FramLength = 0;  //���¿�ʼ�����µ����ݰ�

	rt_thread_mdelay(2000);
	
	strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';
//	rt_kprintf("Receive now data:%s\r\n",strEsp8266_Fram_Record .Data_RX_BUF);
	rt_thread_mdelay(200);

	cJSON_NowWeatherParse((char*)strEsp8266_Fram_Record .Data_RX_BUF, &weather_data);	

	ESP8266_ExitUnvarnishSend ( );//�˳�͸��HZJ
	ESP8266_Close_Link (  );//�ر�TCP��UDP����HZJ
	
	
	return 0;
}
MSH_CMD_EXPORT(GetNowWeather, Get Weather Infomation.);


