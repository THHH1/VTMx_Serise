#ifndef __OLED_H
#define __OLED_H


/*
*****************************************************************************
    功能：OLED端口定义
    时间：2022.02.25
    人员：th
    修改记录：
        th 2022.02.25  修改
*****************************************************************************
*/
//-----------------OLED端口定义---------------- 
#define Led0_num  0
#define Led1_num  1

#define oledSCL_Pin   	GPIO_Pin_6
#define oledSCL_GPIOx 	GPIO2
#define oledSDA_Pin   	GPIO_Pin_7
#define oledSDA_GPIOx 	GPIO2

#define OLED_SCLK_Clr() GPIO_WriteBit(oledSCL_GPIOx, oledSCL_Pin, Bit_RESET)//SCL
#define OLED_SCLK_Set() GPIO_WriteBit(oledSCL_GPIOx, oledSCL_Pin, Bit_SET)

#define OLED_SDIN_Clr() GPIO_WriteBit(oledSDA_GPIOx, oledSDA_Pin, Bit_RESET)//DIN
#define OLED_SDIN_Set() GPIO_WriteBit(oledSDA_GPIOx, oledSDA_Pin, Bit_SET)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define u8 unsigned char
#define u16 const unsigned char
#define u32 unsigned int

/*
*****************************************************************************
    功能：OLED操作函数
    时间：2022.02.25
    人员：th
    修改记录：
        th 2022.02.25  修改
*****************************************************************************
*/
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y);
void OLED_ClearPoint(u8 x,u8 y);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
void OLED_ShowChinese1(u8 x,u8 y,u8 num,u8 size1);
void OLED_ShowChinese2(u8 x,u8 y,u8 num,u8 size1);
void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_WR_BP(u8 x,u8 y);
//void OLED_ShowPicture(u8 x1,u8 y1,u8 x2,u8 y2,u16 *p);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_Init(void);

#endif  
