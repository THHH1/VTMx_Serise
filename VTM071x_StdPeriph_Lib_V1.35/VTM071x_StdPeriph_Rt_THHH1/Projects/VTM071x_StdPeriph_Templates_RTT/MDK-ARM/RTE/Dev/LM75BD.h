/*
*****************************************************************************
    ���ܣ�LM75BD ��ض���
    ʱ�䣺2022.05.10
    ��Ա��th
    �޸ļ�¼��
        th 2022.05.10  �޸�
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
void LM75BD_IIC_Start(void);//����IIC��ʼ�ź�
void LM75BD_IIC_Stop(void);//����IIC�����ź�
uint8_t LM75BD_IIC_Wait_Ack(void);//�ȴ��ӻ�Ӧ��
void LM75BD_IIC_Ack(void);//��������ACKӦ����һ��������SCL������SDA���ֵ�
void LM75BD_IIC_NAck(void);//����������ACKӦ����һ��������SCL������SDA���ָ�
void LM75BD_IIC_Send_Byte(uint8_t txd);//����ͨ��IIC��ӻ�����һ���ֽ�
uint8_t LM75BD_IIC_Read_Byte(uint8_t ack);//����ͨ��IIC�Ӵӻ�����һ���ֽڣ�ack=1������ACK ,ack=0������NACK
uint16_t Read_LM75BD_Temputerature(void);//��ȡLM75BD���¶�
#endif


