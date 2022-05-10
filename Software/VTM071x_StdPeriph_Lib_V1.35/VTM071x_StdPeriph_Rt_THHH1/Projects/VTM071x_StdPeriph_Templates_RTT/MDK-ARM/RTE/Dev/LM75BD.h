/*
*****************************************************************************
    功能：LM75BD 相关定义
    时间：2022.05.10
    人员：th
    修改记录：
        th 2022.05.10  修改
*****************************************************************************
*/ 
#ifndef __LM75BD_H
#define __LM75BD_H

#include "rtdef.h"


#define LM75BD_SDA_Pin   GPIO_Pin_3
#define LM75BD_SCL_Pin   GPIO_Pin_2

#define LM75BD_GPIOx GPIO3

#define IIC_LM75BD_SDA_LOW()          (GPIODATA0->DT_CLR = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_3)))
#define IIC_LM75BD_SDA_HIGH()         (GPIODATA0->DT_SET = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_3)))

#define IIC_LM75BD_SCL_LOW()          (GPIODATA0->DT_CLR = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_2)))
#define IIC_LM75BD_SCL_HIGH()         (GPIODATA0->DT_SET = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_2)))



void LM75BD_GpioInit(void);
void LM75BD_IIC_Start(void);//产生IIC开始信号
void LM75BD_IIC_Stop(void);//产生IIC结束信号
uint8_t LM75BD_IIC_Wait_Ack(void);//等待从机应答
void LM75BD_IIC_Ack(void);//主机产生ACK应答，在一个完整的SCL周期内SDA保持低
void LM75BD_IIC_NAck(void);//主机不产生ACK应答，在一个完整的SCL周期内SDA保持高
void LM75BD_IIC_Send_Byte(uint8_t txd);//主机通过IIC向从机发送一个字节
uint8_t LM75BD_IIC_Read_Byte(uint8_t ack);//主机通过IIC从从机读出一个字节，ack=1，发送ACK ,ack=0，发送NACK
uint16_t Read_LM75BD_Temputerature(void);//读取LM75BD的温度
#endif


