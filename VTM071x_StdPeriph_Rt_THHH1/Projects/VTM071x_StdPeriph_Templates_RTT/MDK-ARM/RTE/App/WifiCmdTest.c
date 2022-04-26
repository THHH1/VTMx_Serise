#include "config.h"
#include "WifiCmdTest.h"

/*
*****************************************************************************
    功能：ESP8266 AT指令测试
    时间：2022.03.02
    人员：th
    修改记录：
        th 2022.03.02  修改
*****************************************************************************
*/ 
void ATcmd(int argc,char **argv)
{
	if(!rt_strcmp(argv[1],"AT"))
	{
		ESP8266_Cmd ( "AT", "OK", NULL, 500 );
		rt_kprintf("%s\r\n",strEsp8266_Fram_Record .Data_RX_BUF);
		
	}
	else if(!rt_strcmp(argv[1],"RST"))//AT命令
	{
		
		ESP8266_Rst();
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	
	else if(!rt_strcmp(argv[1],"STA"))//设置为工作站模式
	{
		ESP8266_Net_Mode_Choose ( STA );
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"AP"))//设置为热点模式
	{
		ESP8266_Net_Mode_Choose ( AP );
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"STA_AP"))  //设置为工作站+热点模式
	{
		ESP8266_Net_Mode_Choose ( STA_AP );
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
  else 	if(!rt_strcmp(argv[1],"JoinAP")) //加入热点
	{
		ESP8266_JoinAP ( argv[2], argv[3]);
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"ipconfig")) //查询本机IP
	{
		ESP8266_InquireIP( );
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}	 
	else if(!rt_strcmp(argv[1],"LinkServer")) //加入服务器
	{
		if(!rt_strcmp(argv[2],"TCP"))
		 ESP8266_Link_Server ( enumTCP, argv[3], argv[4], Single_ID_0);
		else
		 ESP8266_Link_Server ( enumUDP, argv[3], argv[4], Single_ID_0);
		
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"CloseLink")) //关闭TCP或UDP连接
	{
		ESP8266_Close_Link();
		
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	
	else if(!rt_strcmp(argv[1],"Unvarnish")) //开启透传
	{
		ESP8266_UnvarnishSend();
		
		rt_kprintf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
	}
	else if(!rt_strcmp(argv[1],"SendData")) //透传时发送数据，数据间不能包含空格；若需发送空格数据请加双引号
	{
		ESP8266_SendString ( ENABLE, argv[2], rt_strlen(argv[2]), Single_ID_0 );
		
		rt_kprintf("Send Data:%s\r\n",argv[2]);
	}
	else if(!rt_strcmp(argv[1],"ExitUnvarnish")) //关闭透传
	{
		ESP8266_ExitUnvarnishSend ();
		
		rt_kprintf("ExitUnvarnish Success!\r\n");
	}
	
}


MSH_CMD_EXPORT(ATcmd, ESP8266 Test.);

