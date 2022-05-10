#include "config.h"
#include "NtpExample.h"
#include "time.h"

/*
*****************************************************************************
    ���ܣ�ESP8266��ȡ��׼ʱ��
    ʱ�䣺2022.03.03
    ��Ա��th
    �޸ļ�¼��
        th 2022.03.03  �޸�
*****************************************************************************
*/ 
#define NTP_TIMESTAMP_DELTA 2208988800ull //number of seconds between 1900 and 1970��1900-1970��ʱ���
#define SEC_TIME_ZONE         + (8*60*60)  //Beijing,GMT+8�� ʱ����



/* ʱ�������--����ͬ������ʱ�� */
#define TIME_SERVERIP	"cn.ntp.org.cn"//NTP������  
#define TIME_PORTNUM	"123"//NTP�������˿ںţ��̶�Ϊ123

extern uint16_t		tim_year;
extern uint8_t		tim_mon;
extern uint8_t		tim_mday;
extern uint8_t		tim_time;
extern uint8_t		tim_min;
extern uint8_t		tim_sec;

int GetNtp(void)
{
	uint8_t PosInNtpPacket;
	uint8_t buf[48];//�洢NTP���������ص�����
	uint32_t local_timestamp; 
  ntp_packet packet ;
  struct tm * Net_time; 
  uint8_t NTP_Data[48]; //48�ֽڵı���
	
	
	/*******************************/
	//NTP��ѯ���ĸ���ֵ
  NTP_Data[0]=0xa3; 
	//10100011, 0xa3,100 �汾4
  //00011011, 0x1b,011 �汾3
  //00010011, 0x13,010 �汾2
  //00001011, 0x0b,001 �汾1
	for(PosInNtpPacket=1;PosInNtpPacket<48;PosInNtpPacket++) NTP_Data[PosInNtpPacket]=0;//ʣ���47�ֽ�Ϊ0
  /*******************************/
	
	ESP8266_Link_Server(enumUDP, (char*)TIME_SERVERIP, (char*)TIME_PORTNUM,Single_ID_0);//UDP����
	rt_thread_mdelay(300);
	
	ESP8266_UnvarnishSend ();//����ģʽΪ��͸��	
//	strEsp8266_Fram_Record .InfBit .FramLength = 0;  //���¿�ʼ�����µ����ݰ�
	for(PosInNtpPacket=0;PosInNtpPacket<48;PosInNtpPacket++) //����NTP��ѯ��
		UsartSendByte(macESP8266_USARTx,NTP_Data[PosInNtpPacket]);

//	rt_thread_mdelay(20);
	strEsp8266_Fram_Record .InfBit .FramLength = 0;  //���¿�ʼ�����µ����ݰ�

	rt_thread_mdelay(1000);

	rt_memcpy(buf,strEsp8266_Fram_Record.Data_RX_BUF,48);
		
	
	ESP8266_ExitUnvarnishSend ( );//�˳�͸��HZJ
  ESP8266_Close_Link (  );//�ر�TCP��UDP����HZJ
	

	/*******************************/
	//���հ�ԭʼ���ݴ�ӡ
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

	packet.txTm_s = buf[40]<<24 | buf[40+1]<<16|buf[40+2]<<8 |buf[40+3];//���ڱ���ʾʱ�侫��Ҫ�󲻸ߣ���ֱ���÷��������ص�ʱ����Ϊ��ʱ��ʱ�䣬��δ�ù�ʽ��ʱ���offset=����T2-T1��+��T3-T4����/2��������T3��Ϊ��ʱ��׼ʱ�䡣  
  local_timestamp = packet.txTm_s - NTP_TIMESTAMP_DELTA;//��ȥ1970��1900�Ĳ�ֵ
  local_timestamp +=SEC_TIME_ZONE; //���ϱ�����ʱ��GMT+8
  Net_time = localtime(&local_timestamp); //����ת��λ��׼ʱ��
	
	rt_kprintf("NTP Time:%04d-%02d-%02d %02d:%02d:%02d\r\n",(Net_time->tm_year)+1900, (Net_time->tm_mon)+1, Net_time->tm_mday, Net_time->tm_hour,Net_time->tm_min,Net_time->tm_sec); //��ӡ��ʱ��
	tim_year=(Net_time->tm_year)+1900;
	tim_mon=(Net_time->tm_mon)+1;
	tim_mday=Net_time->tm_mday;
	tim_time=Net_time->tm_hour;
	tim_min=Net_time->tm_min;
	tim_sec=Net_time->tm_sec;
	return 0;
}
MSH_CMD_EXPORT(GetNtp, Get BeiJing Time.);


