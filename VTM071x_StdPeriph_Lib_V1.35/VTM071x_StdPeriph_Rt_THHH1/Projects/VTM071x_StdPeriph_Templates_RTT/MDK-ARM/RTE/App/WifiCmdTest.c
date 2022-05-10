#include "config.h"
#include "WifiCmdTest.h"

/*
*****************************************************************************
    ���ܣ�ESP8266 ATָ�����
    ʱ�䣺2022.03.02
    ��Ա��th
    �޸ļ�¼��
        th 2022.03.02  �޸�
*****************************************************************************
*/ 
void ATcmd(int argc,char **argv)
{
	if(!rt_strcmp(argv[1],"AT"))
	{
		ESP8266_Cmd ( "AT", "OK", NULL, 500 );
		rt_kprintf("%s\r\n",strEsp8266_Fram_Record .Data_RX_BUF);
		
	}
	else if(!rt_strcmp(argv[1],"RST"))//AT����
	{
		
		ESP8266_Rst();
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	
	else if(!rt_strcmp(argv[1],"STA"))//����Ϊ����վģʽ
	{
		ESP8266_Net_Mode_Choose ( STA );
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"AP"))//����Ϊ�ȵ�ģʽ
	{
		ESP8266_Net_Mode_Choose ( AP );
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"STA_AP"))  //����Ϊ����վ+�ȵ�ģʽ
	{
		ESP8266_Net_Mode_Choose ( STA_AP );
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
  else 	if(!rt_strcmp(argv[1],"JoinAP")) //�����ȵ�
	{
		ESP8266_JoinAP ( argv[2], argv[3]);
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"ipconfig")) //��ѯ����IP
	{
		ESP8266_InquireIP( );
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}	 
	else if(!rt_strcmp(argv[1],"LinkServer")) //���������
	{
		if(!rt_strcmp(argv[2],"TCP"))
		 ESP8266_Link_Server ( enumTCP, argv[3], argv[4], Single_ID_0);
		else
		 ESP8266_Link_Server ( enumUDP, argv[3], argv[4], Single_ID_0);
		
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"CloseLink")) //�ر�TCP��UDP����
	{
		ESP8266_Close_Link();
		
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	
	else if(!rt_strcmp(argv[1],"Unvarnish")) //����͸��
	{
		ESP8266_UnvarnishSend();
		
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"SendData")) //͸��ʱ�������ݣ����ݼ䲻�ܰ����ո����跢�Ϳո��������˫����
	{
		ESP8266_SendString ( ENABLE, argv[2], rt_strlen(argv[2]), Single_ID_0 );
		
		rt_kprintf("Send Data:%s\r\n",argv[2]);
	}
	else if(!rt_strcmp(argv[1],"ExitUnvarnish")) //�ر�͸��
	{
		ESP8266_ExitUnvarnishSend ();
		
		rt_kprintf("ExitUnvarnish Success!\r\n");
	}
	
}


MSH_CMD_EXPORT(ATcmd, ESP8266 Test.);

