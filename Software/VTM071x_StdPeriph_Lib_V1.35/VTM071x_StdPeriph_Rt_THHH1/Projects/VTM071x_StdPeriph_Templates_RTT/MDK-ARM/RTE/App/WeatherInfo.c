#include "config.h"
#include "WeatherInfo.h"
#include "CJSON.h"

	


/* 心知天气（api.seniverse.com）--天气数据的来源 */
#define WEATHER_IP 		"116.62.81.138"
#define WEATHER_PORT 	"80"



/* 定义一些全局变量 */
//------------------------------------------------------------------------------------------
//所需要的天气数据,供其他应用使用
WeatherType weather_data;


/********************************************************************************************************
** 函数: cJSON_NowWeatherParse, 解析天气实况数据包now.json
**------------------------------------------------------------------------------------------------------
** 参数: JSON:天气实况数据包  WeatherType:存储解析得到的有用的数据
** 说明: 数据来源：心知天气（api.seniverse.com）
** 返回: 0:解析成功 其他：解析失败		
** 作者: 2022.03.04 by th
********************************************************************************************************/

static int cJSON_NowWeatherParse(char *JSON, WeatherType *result)
{

	cJSON *json,*arrayItem,*object,*subobject,*item;

	
//printf("Receive now data:%s\r\n",JSON);
 
	json = cJSON_Parse(JSON);//解析JSON数据包
	if(json == NULL)		  //检测JSON数据包是否存在语法上的错误，返回NULL表示数据包无效
	{
		rt_kprintf("Error before: [%s]\r\n",cJSON_GetErrorPtr()); //打印数据包语法错误的位置
		return 1;
	}
	else
	{
		if((arrayItem = cJSON_GetObjectItem(json,"results")) != NULL) //匹配字符串"results",获取数组内容
		{
			int size = cJSON_GetArraySize(arrayItem);     //获取数组中对象个数
//			printf("cJSON_GetArraySize: size=%d\n",size); 
			
			if((object = cJSON_GetArrayItem(arrayItem,0)) != NULL)//获取父对象内容
			{
        rt_kprintf("--------------------------------Now Weather Data Begin------------------------------\r\n");
				/* 匹配子对象1 */
				if((subobject = cJSON_GetObjectItem(object,"location")) != NULL)
				{
					
					rt_kprintf("---------------------------------subobject1-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"id")) != NULL)   
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string,item->valuestring);
					}
					if((item = cJSON_GetObjectItem(subobject,"name")) != NULL) //地名--需要用到的数据
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
				/* 匹配子对象2 */
				if((subobject = cJSON_GetObjectItem(object,"now")) != NULL)
				{
					rt_kprintf("---------------------------------subobject2-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"text")) != NULL)//天气预报文字--需要用到的数据
					{
						 rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string,item->valuestring);
						sprintf(weather_data .text,"%s",item->valuestring);
					}
					if((item = cJSON_GetObjectItem(subobject,"code")) != NULL)//天气预报代码--需要用到的数据
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string, item->valuestring);
						sprintf(weather_data .code,"%s",item->valuestring);
						rt_kprintf("%d\n",weather_data .code[0]);rt_kprintf("%d\n",weather_data .code[1]);
					}
					if((item = cJSON_GetObjectItem(subobject,"temperature")) != NULL) //温度--需要用到的数据
					{
						rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",item->string, item->valuestring);
						sprintf(weather_data .temperature,"%s",item->valuestring);
					}
				}
				/* 匹配子对象3 */
				if((subobject = cJSON_GetObjectItem(object,"last_update")) != NULL)
				{
					rt_kprintf("---------------------------------subobject3-------------------------------\r\n");
					rt_kprintf("cJSON_GetObjectItem: %s:%s\r\n",subobject->string,subobject->valuestring);
				}
				rt_kprintf("--------------------------------Now Weather Data End--------------------------------\r\n");
			} 
		
		}
	}
	
	cJSON_Delete(json); //释放cJSON_Parse()分配出来的内存空间


	return 0;

}	


/********************************************************************************************************
** 函数: GetNowWeather, GET 天气实况数据包now.json
**------------------------------------------------------------------------------------------------------
** 参数: void
** 说明: 数据来源：心知天气（api.seniverse.com）
** 返回: 0:获取成功 其他：获取失败	
** 作者: 2022.03.04 by th
********************************************************************************************************/
int GetNowWeather(void)
{

	ESP8266_Link_Server(enumTCP, (char*)WEATHER_IP, (char*)WEATHER_PORT,Single_ID_0);//TCP
	ESP8266_UnvarnishSend ();//传输模式为：透传	

//	macESP8266_Usart ( "GET https://api.seniverse.com/v3/weather/now.json?"
//	"key=2owqvhhd2dd9o9f9&location=%s&language=zh-Hans&unit=c\r\n\r\n","fuzhou" );
	macESP8266_Usart ( "GET https://api.seniverse.com/v3/weather/now.json?key=ragjskuzlv5jzerq&location=hefei\r\n\r\n");//以福州天气为例子获取

	strEsp8266_Fram_Record .InfBit .FramLength = 0;  //重新开始接收新的数据包

	rt_thread_mdelay(2000);
	
	strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';
//	rt_kprintf("Receive now data:%s\r\n",strEsp8266_Fram_Record .Data_RX_BUF);
	rt_thread_mdelay(200);

	cJSON_NowWeatherParse((char*)strEsp8266_Fram_Record .Data_RX_BUF, &weather_data);	

	ESP8266_ExitUnvarnishSend ( );//退出透传HZJ
	ESP8266_Close_Link (  );//关闭TCP或UDP连接HZJ
	
	
	return 0;
}
MSH_CMD_EXPORT(GetNowWeather, Get Weather Infomation.);


