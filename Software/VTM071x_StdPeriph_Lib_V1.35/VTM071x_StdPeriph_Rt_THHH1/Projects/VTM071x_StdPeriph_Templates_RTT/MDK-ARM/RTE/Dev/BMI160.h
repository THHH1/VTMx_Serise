/*
*****************************************************************************
    功能：NMI160 相关定义
    时间：2022.03.24
    人员：th
    修改记录：
        th 2022.03.14  修改
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
uint8_t BMI160_Read_Reg(uint8_t reg);//读取SPI的寄存器值
uint8_t BMI160_write_Reg(uint8_t reg,uint8_t value);//写入指定寄存器值

void getAccelerometervalue(void);
void  getGyroscopeValue(void);

#ifdef __cplusplus
}
#endif

#endif



















