#ifndef __WEATHER_INFO__
#define __WEATHER_INFO__

/*
*****************************************************************************
    ���ܣ��������ݽṹ��
    ʱ�䣺2022.03.04
    ��Ա��th
    �޸ļ�¼��
        th 2022.03.04  �޸�
*****************************************************************************
*/
/* �������ݽṹ�� */
typedef struct
{
	/* ʵ���������� */
	char name[32];				//����
	char text[32];				//����Ԥ������
	char code[32];				//����Ԥ������
	char temperature[32];   	//����
	
	/* ���졢���졢������������ */
//	char date[1][32];			//����
//	char text_day[1][64];	    //����������������
//	char code_day[1][32];		//���������������
//	char code_night[1][64]; 	//��������������
//	char high[1][32];			//�����
//	char low[1][32];			//�����
//	char wind_direction[1][64]; //����
//	char wind_speed[1][32];  	//���٣���λkm/h����unit=cʱ��
//	char wind_scale[1][32];  	//�����ȼ�
	
//	char life_suggestion[128][2];	//�����
}WeatherType;

extern WeatherType weather_data;


#endif
