/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "BMI160.h"
#include <stdio.h>

/*
*****************************************************************************
    功能：BMI160 SPI初始化配置
    时间：2022.03.25
    人员：th
    修改记录：
        th 2022.03.25  修改
*****************************************************************************
*/ 
void SPI_BMI160_LowLevel_Init(SPI_TypeDef *SPIx)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	SPI_InitTypeDef   SPI_InitStructure;

    /* SPI clock */
    if (SPIx == SPI0)
    {
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_SPI0, ENABLE);
        RCC_SETCLKDivider(RCC_CLOCKFREQ_SPI0CLK, 2);
    }
	else
    {
        RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_SPI1, ENABLE);
        RCC_SETCLKDivider(RCC_CLOCKFREQ_SPI1CLK, 2);
    }

    /* SPI pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO3, &GPIO_InitStructure);
    GPIO_WriteBit(GPIO3, GPIO_Pin_4, Bit_SET);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO3, &GPIO_InitStructure);
    	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
	GPIO_Init(GPIO3, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
	GPIO_Init(GPIO3, &GPIO_InitStructure);

    /* Reset SPI */
	SPI_DeInit(SPIx);

	SPI_InitStructure.SPI_Mode        = SPI_MODE_MASTER;
	SPI_InitStructure.SPI_Direction   = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize    = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL        = SPI_CPOL_Low;//SPI_CPOL_High;SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA        = SPI_CPHA_1Edge;//SPI_CPHA_1Edge;SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_Init(SPIx, &SPI_InitStructure);
}
/**
  * @brief  Read data from SPI BMI160 or write data to SPI BMI160.
  * @param  TxData: data.
  * @retval data
  */
static uint16_t SPI_BMI160_ReadWriteByte(uint16_t TxData)
{
	uint16_t i, retry = 0;

	while(SPI_GetFlagStatus(SPI_BMI160_X, SPI_STATUS_Transmit_FIFO_Empty) != SET)
    {
        retry++;
        if(retry > SPI_TIMEOUT_VALUE2)
            return 0;
    }
	SPI_SendData(SPI_BMI160_X, TxData);
  for(i=0;i<10;i++);

	retry = 0;
	while (SPI_GetFlagStatus(SPI_BMI160_X, SPI_STATUS_Receive_FIFO_Not_Empty) != SET)
    {
        retry++;
        if(retry > SPI_TIMEOUT_VALUE2)
            return 0;
    }

	return SPI_ReceiveData(SPI_BMI160_X);
}

/**
  * @brief  Enables or disables the specified SPI BMI160 peripheral.
  * @param  NewState: new state of the SPI BMI160 peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
static void SPI_BMI160_Cmd(FunctionalState NewState)
{
    int retry = 0;

	if (NewState != DISABLE)
	{
		SPI_Cmd(SPI_BMI160_X, ENABLE);
        SPI_BMI160_ReadWriteByte(0xFF);
	}
	else
	{
		while(SPI_GetFlagStatus(SPI_BMI160_X, SPI_STATUS_SSP_BUSY) == SET)
        {
            retry++;
            if (retry > SPI_TIMEOUT_VALUE2)
                break;
        }
		SPI_Cmd(SPI_BMI160_X, DISABLE);
	}
}



/**
  * @brief  DeInitializes the SPI BMI160 communication.
  * @param  None
  * @retval None
  */
void SPI_BMI160_DeInit(void)
{
	SPI_FLASH_LowLevel_DeInit(SPI_BMI160_X);
}

/**
  * @brief  Initializes the SPI communication.
  * @param  None
  * @retval None
  */
int SPI_BMI160_Init(void)
{  
	/* Initialize SPI BMI160 */
	SPI_BMI160_LowLevel_Init(SPI_BMI160_X);

    SPI_BMI160_Cmd(ENABLE);
	//向命令寄存器写入0x15,使角速度处于正常工作模式		
	BMI160_write_Reg(0x7e,0x15);
	//切换工作模式之后，延时10ms
	rt_thread_mdelay(100);
	//向命令寄存器写入0x11,使加速度处于正常工作模式
	BMI160_write_Reg(0x7e,0x11);
	//切换工作模式之后，延时100ms
	rt_thread_mdelay(100);    
    return 0;
}
/*
*****************************************************************************
    功能：BMI160 读取寄存器的值
    时间：2022.03.25
    人员：th
    修改记录：
        th 2022.03.25  修改
*****************************************************************************
*/

uint8_t BMI160_Read_Reg(uint8_t reg)//读取SPI的寄存器值
{
	uint8_t reg_val;
	SPI_BMI160_CS_LOW();//使能SPI
	rt_thread_mdelay(1);
	SPI_BMI160_ReadWriteByte(reg|0x80);//read request
	reg_val=SPI_BMI160_ReadWriteByte(0xFF);//读取内容
	rt_thread_mdelay(1);
	SPI_BMI160_CS_HIGH();//禁止SPI传输
	return (reg_val);
}
/*
*****************************************************************************
    功能：BMI160 向指定寄存器写入值
    时间：2022.03.25
    人员：th
    修改记录：
        th 2022.03.25  修改
*****************************************************************************
*/
uint8_t BMI160_write_Reg(uint8_t reg,uint8_t value)//写入指定寄存器值
{
	uint8_t ststus;
	SPI_BMI160_CS_LOW();//使能SPI
	rt_thread_mdelay(1);
	ststus=SPI_BMI160_ReadWriteByte(reg&0x7F);//发送寄存器号
	SPI_BMI160_ReadWriteByte(value);//写入寄存器值
	rt_thread_mdelay(1);
	SPI_BMI160_CS_HIGH();//禁止SPI传输
	return (ststus);
}

/*
*****************************************************************************
    功能：获取三轴加速度值
    时间：2022.03.25
    人员：th
    修改记录：
        th 2022.03.25  修改
*****************************************************************************
*/
void getAccelerometervalue(void)
{
	
	float acc_x,acc_y,acc_z;
	unsigned short x,y,z;
//	//向命令寄存器写入0x11,使加速度处于正常工作模式
//  BMI160_write_Reg(0x7e,0x11);
//	//切换工作模式之后，延时100ms
//  rt_thread_mdelay(100);


	//加速度 X轴
	x =( BMI160_Read_Reg(0x12) &0xff);
	x = x|(( BMI160_Read_Reg(0x13) &0xff)<<8);
	if(x>0x7fff)
	{
		acc_x =(float) -(0xffff-x);
	}
	else
	{		
		acc_x=(float)x;
	}
	acc_x =(acc_x*9.8)/(0x8000/2);//当量程为±2g时，转换为g/s的加速度换算公式
	
	//加速度 Y轴
	y =( BMI160_Read_Reg(0x14) &0xff);
	y = y|(( BMI160_Read_Reg(0x15) &0xff)<<8);
	if(y>0x7fff)
	{
		acc_y =(float) -(0xffff-y);
	}	
	else
	{	
		acc_y=(float)y;
	}
	
	acc_y =(acc_y*9.8)/(0x8000/2);//当量程为±2g时，转换为g/s的加速度换算公式
	//加速度 Z轴
	z =( BMI160_Read_Reg(0x16) &0xff);        
	z = z|(( BMI160_Read_Reg(0x17) &0xff)<<8);
	if(z>0x7fff)
	{
		acc_z =(float) -(0xffff-z);
	}	
	else
	{	
		acc_z=(float)z;
	}

	acc_z =(acc_z*9.8)/(0x8000/2);//当量程为±2g时，转换为g/s的加速度换算公式
	rt_kprintf("================================\n\n");	
	rt_kprintf("X轴加速度 = %.2f g/s \n\n",acc_x);
	rt_kprintf("Y轴加速度 = %.2f g/s \n\n",acc_y);
	rt_kprintf("Z轴加速度 = %.2f g/s \n\n",acc_z);
}
/*
*****************************************************************************
    功能：获取三轴角速度值
    时间：2022.03.25
    人员：th
    修改记录：
        th 2022.03.25  修改
*****************************************************************************
*/
void  getGyroscopeValue(void)
{
	float gry_x,gry_y,gry_z;
	unsigned short x,y,z;
	
//	//向命令寄存器写入0x15,使角速度处于正常工作模式	
//	
//	BMI160_write_Reg(0x7e,0x15);
//	//切换工作模式之后，延时10ms
//	rt_thread_mdelay(100);

	//陀螺仪角速度 X轴
	x =( BMI160_Read_Reg(0x0c) &0xff);
	x = x|(( BMI160_Read_Reg(0x0d) &0xff)<<8);
	if(x>0x7fff)
	{
		gry_x =(float) -(0xffff-x);
	}	
	else
	{
		gry_x=(float)x;
	}

	gry_x =(gry_x*2000)/0x7fff;// range为2000dps时，转换为角速度°/s的公式

	
	//陀螺仪角速度 Y轴
	y =( BMI160_Read_Reg(0x0e) &0xff);
	y = y|(( BMI160_Read_Reg(0x0f) &0xff)<<8);
	if(y>0x7fff)
	{
		gry_y =(float) -(0xffff-y);
	}	
	else
	{
		gry_y=(float)y;
	}

	gry_y =(gry_y*2000)/0x7fff;// range为2000dps时，转换为角速度°/s的公式
	
	//陀螺仪角速度 Z轴
	z =( BMI160_Read_Reg(0x10) &0xff);
	z = z|(( BMI160_Read_Reg(0x11) &0xff)<<8);
	if(z>0x7fff)
	{
		gry_z =(float) -(0xffff-z);
	}	
	else
	{
		gry_z=(float)z;
	}
	
	gry_z =(gry_z*2000)/0x7fff; // range为2000dps时，转换为角速度°/s的公式
	
	rt_kprintf("--------------------------------\n\n");	
	rt_kprintf("X轴角速度 = %.2f °/s \n\n",gry_x);
	rt_kprintf("Y轴角速度 = %.2f °/s \n\n",gry_y);
	rt_kprintf("Z轴角速度 = %.2f °/s \n\n",gry_z);
	rt_kprintf("================================\n\n");	
}

/*
*****************************************************************************
    功能：初始化陀螺仪
    时间：2022.04.01
    人员：th
    修改记录：
        th 2022.04.01  修改
*****************************************************************************
*/
int BMIProcessInit()
{
	/* Init SPI */
	SPI_BMI160_Init();//初始化SPI	
	return 0;
}
INIT_APP_EXPORT(BMIProcessInit);
/*
*****************************************************************************
    功能：读取6轴陀螺仪角速度，加速度值
    时间：2022.03.28
    人员：th
    修改记录：
        th 2022.03.28  修改
*****************************************************************************
*/
int GetBmi160Data(void)
{
	uint8_t ID[6];//数组ID
	uint16_t temp_data=0;
	/* Read ID */
	ID[0]=BMI160_Read_Reg(0x00);//读取ID	
	rt_kprintf("读取IDbmi160_id = %x \n\n",ID[0]);
	ID[1]=BMI160_Read_Reg(0x03);//读取设备状态
	rt_kprintf("读取设备状态bmi160_status = %x \n\n",ID[1]);
	ID[2]=BMI160_Read_Reg(0x41);//读取加速度工作状态
	rt_kprintf("读取加速度工作状态bmi160_acc_range = %x \n\n",ID[2]);
	ID[3]=BMI160_Read_Reg(0x43);//读取角速度工作状态
	rt_kprintf("读取角速度工作状态bmi160_gyr_range = %x \n\n",ID[3]);	

	ID[4]=BMI160_Read_Reg(0x20);//读取角速度工作状态
	ID[5]=BMI160_Read_Reg(0x21);//读取角速度工作状态
	temp_data=ID[4];
	temp_data=temp_data<<8;
	temp_data=temp_data+ID[5];
	rt_kprintf("读取陀螺仪温度数据 temperature_data = %x_%x \n\n",ID[4],ID[5]);

	if(temp_data>32768)
	{
		temp_data=temp_data-32768;
		temp_data=temp_data/512;
		if(temp_data>41)
		{
			temp_data=temp_data-41;
			rt_kprintf("读取陀螺仪温度数据1 temperature_data = %d \n\n",temp_data);
		}
		else
		{
			temp_data=41-temp_data;
			rt_kprintf("读取陀螺仪温度数据1 temperature_data = -%d \n\n",temp_data);
		}
	}
	else
	{
		temp_data=temp_data/512;
		temp_data=temp_data+23;
		rt_kprintf("读取陀螺仪温度数据2 temperature_data = %d \n\n",temp_data);
	}
	
	getAccelerometervalue();//获取三轴加速度值
	getGyroscopeValue();//获取三轴角速度值
	return 0;
}
MSH_CMD_EXPORT(GetBmi160Data, Get acc gry data.);
/****************************************************************************
msh >GetBmi160Data
读取IDbmi160_id = 0xd1 

读取设备状态bmi160_status = 14 

读取加速度工作状态bmi160_acc_range = 3 

读取角速度工作状态bmi160_gyr_range = 0 

================================

X轴加速度 = -0.61 g/s 

Y轴加速度 = -1.39 g/s 

Z轴加速度 = 9.88 g/s 

--------------------------------

X轴角速度 = -0.24 °/s 

Y轴角速度 = 0.55 °/s 

Z轴角速度 = 0.61 °/s 

================================
	Sensor温度换算表
	Value 		Temperature
	0x7FFF		87- 1/(2^9)
	...			...
	0x0000		23度
	0x8001		-41+1/(2^9)
	0x8000		Invalid
	
	32768/512=64度	分辨率512
****************************************************************************/
