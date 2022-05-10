#include "config.h"
#include "NtpExample.h"
#include "time.h"

/*
*****************************************************************************
    功能：ESP8266获取标准时间
    时间：2022.03.03
    人员：th
    修改记录：
        th 2022.03.03  修改
*****************************************************************************
*/ 
#define NTP_TIMESTAMP_DELTA 2208988800ull //number of seconds between 1900 and 1970，1900-1970的时间差
#define SEC_TIME_ZONE         + (8*60*60)  //Beijing,GMT+8， 时区差



/* 时间服务器--用于同步网络时间 */
#define TIME_SERVERIP	"cn.ntp.org.cn"//NTP服务器  
#define TIME_PORTNUM	"123"//NTP服务器端口号，固定为123

extern uint16_t		tim_year;
extern uint8_t		tim_mon;
extern uint8_t		tim_mday;
extern uint8_t		tim_time;
extern uint8_t		tim_min;
extern uint8_t		tim_sec;

int GetNtp(void)
{
	uint8_t PosInNtpPacket;
	uint8_t buf[48];//存储NTP服务器返回的数据
	uint32_t local_timestamp; 
  ntp_packet packet ;
  struct tm * Net_time; 
  uint8_t NTP_Data[48]; //48字节的报文
	
	
	/*******************************/
	//NTP查询报文赋初值
  NTP_Data[0]=0xa3; 
	//10100011, 0xa3,100 版本4
  //00011011, 0x1b,011 版本3
  //00010011, 0x13,010 版本2
  //00001011, 0x0b,001 版本1
	for(PosInNtpPacket=1;PosInNtpPacket<48;PosInNtpPacket++) NTP_Data[PosInNtpPacket]=0;//剩余的47字节为0
  /*******************************/
	
	ESP8266_Link_Server(enumUDP, (char*)TIME_SERVERIP, (char*)TIME_PORTNUM,Single_ID_0);//UDP连接
	rt_thread_mdelay(300);
	
	ESP8266_UnvarnishSend ();//传输模式为：透传	
//	strEsp8266_Fram_Record .InfBit .FramLength = 0;  //重新开始接收新的数据包
	for(PosInNtpPacket=0;PosInNtpPacket<48;PosInNtpPacket++) //发送NTP查询包
		UsartSendByte(macESP8266_USARTx,NTP_Data[PosInNtpPacket]);

//	rt_thread_mdelay(20);
	strEsp8266_Fram_Record .InfBit .FramLength = 0;  //重新开始接收新的数据包

	rt_thread_mdelay(1000);

	rt_memcpy(buf,strEsp8266_Fram_Record.Data_RX_BUF,48);
		
	
	ESP8266_ExitUnvarnishSend ( );//退出透传HZJ
  ESP8266_Close_Link (  );//关闭TCP或UDP连接HZJ
	

	/*******************************/
	//接收包原始数据打印
	rt_kprintf("/*******************************/\r\n");
	rt_kprintf("Receive NTP Packet (Hex):");
	for(PosInNtpPacket=0;PosInNtpPacket<48;PosInNtpPacket++)
		if(PosInNtpPacket%16==0)
		{
			rt_kprintf("\r\n");
			rt_kprintf("%02X ",buf[PosInNtpPacket]);
		}
		else
			rt_kprintf("%02X ",buf[PosInNtpPacket]);

	rt_kprintf("\r\n/*******************************/\r\n");
	/*******************************/

	packet.txTm_s = buf[40]<<24 | buf[40+1]<<16|buf[40+2]<<8 |buf[40+3];//由于本演示时间精度要求不高，故直接用服务器返回的时间作为对时的时间，并未用公式：时间差offset=（（T2-T1）+（T3-T4））/2。而是用T3作为对时基准时间。  
  local_timestamp = packet.txTm_s - NTP_TIMESTAMP_DELTA;//减去1970和1900的差值
  local_timestamp +=SEC_TIME_ZONE; //加上北京的时间差，GMT+8
  Net_time = localtime(&local_timestamp); //秒数转换位标准时间
	
	rt_kprintf("NTP Time:%04d-%02d-%02d %02d:%02d:%02d\r\n",(Net_time->tm_year)+1900, (Net_time->tm_mon)+1, Net_time->tm_mday, Net_time->tm_hour,Net_time->tm_min,Net_time->tm_sec); //打印出时间
	tim_year=(Net_time->tm_year)+1900;
	tim_mon=(Net_time->tm_mon)+1;
	tim_mday=Net_time->tm_mday;
	tim_time=Net_time->tm_hour;
	tim_min=Net_time->tm_min;
	tim_sec=Net_time->tm_sec;
	return 0;
}
MSH_CMD_EXPORT(GetNtp, Get BeiJing Time.);


