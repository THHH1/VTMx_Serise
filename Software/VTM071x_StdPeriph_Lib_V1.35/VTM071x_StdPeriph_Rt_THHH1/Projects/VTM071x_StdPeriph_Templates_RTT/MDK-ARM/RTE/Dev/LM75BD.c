/*
*****************************************************************************
    功能：LM75BD的初始化
    时间：2022.05.10
    人员：th
    修改记录：
        th 2022.05.10  修改
*****************************************************************************
*/
#include "config.h"

/************************************************************
功能：LM75BD的初始化
时间：2022.05.10
人员：th
入参：无
出参：无
************************************************************/
void LM75BD_GpioInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    /* LM75BD */
    GPIO_InitStructure.GPIO_Pin = LM75BD_SCL_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LM75BD_GPIOx, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LM75BD_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LM75BD_GPIOx, &GPIO_InitStructure);
}
/************************************************************
功能：LM7BD_IIC驱动函数
时间：2022.05.10
人员：th
入参：无
出参：无
************************************************************/
//#define IIC_LM75BD_SDA_LOW()          (GPIODATA0->DT_CLR = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_3)))
//#define IIC_LM75BD_SDA_HIGH()         (GPIODATA0->DT_SET = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_3)))

//#define IIC_LM75BD_SCL_LOW()          (GPIODATA0->DT_CLR = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_2)))
//#define IIC_LM75BD_SCL_HIGH()         (GPIODATA0->DT_SET = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_2)))

void LM75BD_IIC_Start(void)//产生IIC开始信号
{	
	IIC_LM75BD_SDA_HIGH();
	
	IIC_LM75BD_SCL_HIGH();
	rt_hw_us_delay(4);
	IIC_LM75BD_SDA_LOW();//START:when CLK is high,frist DATA change come
	rt_hw_us_delay(4);
	IIC_LM75BD_SCL_LOW();//钳住IIC总线，准备发送或者接收数据
}

void LM75BD_IIC_Stop(void)//产生IIC结束信号
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = LM75BD_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LM75BD_GPIOx, &GPIO_InitStructure);	
	
	IIC_LM75BD_SCL_LOW();
	IIC_LM75BD_SDA_LOW();//START:When SDA is high,end DATA change
	rt_hw_us_delay(4);	
	IIC_LM75BD_SCL_HIGH();
	IIC_LM75BD_SDA_HIGH();//发送IIC总线结束信号
	rt_hw_us_delay(4);
}

uint8_t LM75BD_IIC_Wait_Ack(void)//等待从机应答
{
	uint8_t ErrTime=0;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = LM75BD_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LM75BD_GPIOx, &GPIO_InitStructure);
	
	IIC_LM75BD_SDA_HIGH();
	rt_hw_us_delay(1);

	IIC_LM75BD_SCL_HIGH();
	rt_hw_us_delay(1);
	while(GPIO_ReadDataBit(LM75BD_GPIOx,LM75BD_SDA_Pin))
	{
		ErrTime++;
		if(ErrTime>250)
		{
			LM75BD_IIC_Stop();
			return 1;
		}
	}
	IIC_LM75BD_SCL_LOW();//时钟输出0
	return 0;
}

void LM75BD_IIC_Ack(void)//主机产生ACK应答，在一个完整的SCL周期内SDA保持低
{
	IIC_LM75BD_SCL_LOW();

	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = LM75BD_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LM75BD_GPIOx, &GPIO_InitStructure);
	
	IIC_LM75BD_SDA_LOW();
	rt_hw_us_delay(2);
	IIC_LM75BD_SCL_HIGH();
	rt_hw_us_delay(2);
	IIC_LM75BD_SCL_LOW();
	
}

void LM75BD_IIC_NAck(void)//主机不产生ACK应答，在一个完整的SCL周期内SDA保持高
{
	IIC_LM75BD_SCL_LOW();

	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = LM75BD_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LM75BD_GPIOx, &GPIO_InitStructure);
	
	IIC_LM75BD_SDA_HIGH();
	rt_hw_us_delay(2);
	IIC_LM75BD_SCL_HIGH();
	rt_hw_us_delay(2);
	IIC_LM75BD_SCL_LOW();
	
}

void LM75BD_IIC_Send_Byte(uint8_t txd)//主机通过IIC向从机发送一个字节
{
	uint8_t t;

	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = LM75BD_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LM75BD_GPIOx, &GPIO_InitStructure);
	
	IIC_LM75BD_SCL_LOW();//拉低时钟，开始传输
	for(t=0;t<8;t++)
	{
		if((txd&0x80)>>7)
		{
			IIC_LM75BD_SDA_HIGH();//SDA循环取txd bit7
		}
		else
		{
			IIC_LM75BD_SDA_LOW();
		}
		txd<<=1;
		rt_hw_us_delay(2);
		IIC_LM75BD_SCL_HIGH();
		rt_hw_us_delay(2);
		IIC_LM75BD_SCL_LOW();	
		rt_hw_us_delay(2);	
	}
}

uint8_t LM75BD_IIC_Read_Byte(uint8_t ack)//主机通过IIC从从机读出一个字节，ack=1，发送ACK ,ack=0，发送NACK
{
	uint8_t i,receive=0;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = LM75BD_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LM75BD_GPIOx, &GPIO_InitStructure);
	
	for(i=0;i<8;i++)
	{
		IIC_LM75BD_SCL_LOW();	
		rt_hw_us_delay(2);
		IIC_LM75BD_SCL_HIGH();
		receive<<=1;
		if(GPIO_ReadDataBit(GPIO3,GPIO_Pin_3)==1)
		{
			receive++;
		}
		rt_hw_us_delay(1);	
	}
	if(!ack)
	{
		LM75BD_IIC_NAck();
	}
	else
	{
		LM75BD_IIC_Ack();
	}
	return receive;
}

uint16_t Read_LM75BD_Temputerature(void)//读取LM75BD的温度
{
	uint8_t ACK_SIG;//应答信号
	uint16_t Temputerature_8,Temputerature_16;//温度值
	float LM75BD_Temputerature;
	//IIC启动：SDA 1->0,SCL 1->0
	//默认配置温度模式
	LM75BD_GpioInit();
	LM75BD_IIC_Start();
	//发送0x91 1001 0001 
	LM75BD_IIC_Send_Byte(0x91);
	
	ACK_SIG=LM75BD_IIC_Wait_Ack();//返回值 1接收应答失败，0接收成功
	
	Temputerature_8 = LM75BD_IIC_Read_Byte(!ACK_SIG);//读一个字节，ack=1时发送ack，反之nack

	Temputerature_16 = (Temputerature_8 << 8)+(LM75BD_IIC_Read_Byte(!ACK_SIG));
	
	LM75BD_IIC_Stop();//IIC停止
	
	Temputerature_16 = Temputerature_16>>5;//1LSB=0.125
	rt_kprintf("Temputerature_16 = %d  \n\n",Temputerature_16);
	if(Temputerature_16&0x0400)//负温度
	{
		LM75BD_Temputerature = -(~(Temputerature_16&0x03FF)+1)*0.125;
	}
	else//正温度
	{
		LM75BD_Temputerature = 0.125*(float)Temputerature_16;
	}
	rt_kprintf("LM75BD_Temputerature = %.2f 摄氏度  \n\n",LM75BD_Temputerature);
	return (uint16_t)(LM75BD_Temputerature*100);
}


