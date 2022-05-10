#ifndef __WEATHER_INFO__
#define __WEATHER_INFO__

/*
*****************************************************************************
    功能：天气数据结构体
    时间：2022.03.04
    人员：th
    修改记录：
        th 2022.03.04  修改
*****************************************************************************
*/
/* 天气数据结构体 */
typedef struct
{
	/* 实况天气数据 */
	char name[32];				//地名
	char text[32];				//天气预报文字
	char code[32];				//天气预报代码
	char temperature[32];   	//气温
	
	/* 今天、明天、后天天气数据 */
//	char date[1][32];			//日期
//	char text_day[1][64];	    //白天天气现象文字
//	char code_day[1][32];		//白天天气现象代码
//	char code_night[1][64]; 	//晚间天气现象代码
//	char high[1][32];			//最高温
//	char low[1][32];			//最低温
//	char wind_direction[1][64]; //风向
//	char wind_speed[1][32];  	//风速，单位km/h（当unit=c时）
//	char wind_scale[1][32];  	//风力等级
	
//	char life_suggestion[128][2];	//生活建议
}WeatherType;

extern WeatherType weather_data;


#endif
