/*
*****************************************************************************
    ���ܣ�NMI160 ��ض���
    ʱ�䣺2022.03.24
    ��Ա��th
    �޸ļ�¼��
        th 2022.03.14  �޸�
*****************************************************************************
*/ 
#ifndef __BMI160_H
#define __BMI160_H

#ifdef __cplusplus
 extern "C" {
#endif
#include "VTM071x_eval.h"


#define SPI_BMI160_CS_LOW()          (GPIODATA0->DT_CLR = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_4)))
#define SPI_BMI160_CS_HIGH()         (GPIODATA0->DT_SET = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_4)))

#define SPI_BMI160_X                 SPI1
#define SPI_TIMEOUT_VALUE2           0x4000




void SPI_BMI160_DeInit(void);
int SPI_BMI160_Init(void);
static uint16_t SPI_BMI160_ReadWriteByte(uint16_t TxData);
uint8_t BMI160_Read_Reg(uint8_t reg);//��ȡSPI�ļĴ���ֵ
uint8_t BMI160_write_Reg(uint8_t reg,uint8_t value);//д��ָ���Ĵ���ֵ

void getAccelerometervalue(void);
void  getGyroscopeValue(void);

#ifdef __cplusplus
}
#endif

#endif



















