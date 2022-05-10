/*
*****************************************************************************
    ���ܣ�LM75BD�ĳ�ʼ��
    ʱ�䣺2022.05.10
    ��Ա��th
    �޸ļ�¼��
        th 2022.05.10  �޸�
*****************************************************************************
*/
#include "config.h"

/************************************************************
���ܣ�LM75BD�ĳ�ʼ��
ʱ�䣺2022.05.10
��Ա��th
��Σ���
���Σ���
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
���ܣ�LM7BD_IIC��������
ʱ�䣺2022.05.10
��Ա��th
��Σ���
���Σ���
************************************************************/
//#define IIC_LM75BD_SDA_LOW()          (GPIODATA0->DT_CLR = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_3)))
//#define IIC_LM75BD_SDA_HIGH()         (GPIODATA0->DT_SET = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_3)))

//#define IIC_LM75BD_SCL_LOW()          (GPIODATA0->DT_CLR = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_2)))
//#define IIC_LM75BD_SCL_HIGH()         (GPIODATA0->DT_SET = (uint32_t)(1 << (GPIO3 * 8 +GPIO_Pin_2)))

void LM75BD_IIC_Start(void)//����IIC��ʼ�ź�
{	
	IIC_LM75BD_SDA_HIGH();
	
	IIC_LM75BD_SCL_HIGH();
	rt_hw_us_delay(4);
	IIC_LM75BD_SDA_LOW();//START:when CLK is high,frist DATA change come
	rt_hw_us_delay(4);
	IIC_LM75BD_SCL_LOW();//ǯסIIC���ߣ�׼�����ͻ��߽�������
}

void LM75BD_IIC_Stop(void)//����IIC�����ź�
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
	IIC_LM75BD_SDA_HIGH();//����IIC���߽����ź�
	rt_hw_us_delay(4);
}

uint8_t LM75BD_IIC_Wait_Ack(void)//�ȴ��ӻ�Ӧ��
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
	IIC_LM75BD_SCL_LOW();//ʱ�����0
	return 0;
}

void LM75BD_IIC_Ack(void)//��������ACKӦ����һ��������SCL������SDA���ֵ�
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

void LM75BD_IIC_NAck(void)//����������ACKӦ����һ��������SCL������SDA���ָ�
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

void LM75BD_IIC_Send_Byte(uint8_t txd)//����ͨ��IIC��ӻ�����һ���ֽ�
{
	uint8_t t;

	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = LM75BD_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LM75BD_GPIOx, &GPIO_InitStructure);
	
	IIC_LM75BD_SCL_LOW();//����ʱ�ӣ���ʼ����
	for(t=0;t<8;t++)
	{
		if((txd&0x80)>>7)
		{
			IIC_LM75BD_SDA_HIGH();//SDAѭ��ȡtxd bit7
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

uint8_t LM75BD_IIC_Read_Byte(uint8_t ack)//����ͨ��IIC�Ӵӻ�����һ���ֽڣ�ack=1������ACK ,ack=0������NACK
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

uint16_t Read_LM75BD_Temputerature(void)//��ȡLM75BD���¶�
{
	uint8_t ACK_SIG;//Ӧ���ź�
	uint16_t Temputerature_8,Temputerature_16;//�¶�ֵ
	float LM75BD_Temputerature;
	//IIC������SDA 1->0,SCL 1->0
	//Ĭ�������¶�ģʽ
	LM75BD_GpioInit();
	LM75BD_IIC_Start();
	//����0x91 1001 0001 
	LM75BD_IIC_Send_Byte(0x91);
	
	ACK_SIG=LM75BD_IIC_Wait_Ack();//����ֵ 1����Ӧ��ʧ�ܣ�0���ճɹ�
	
	Temputerature_8 = LM75BD_IIC_Read_Byte(!ACK_SIG);//��һ���ֽڣ�ack=1ʱ����ack����֮nack

	Temputerature_16 = (Temputerature_8 << 8)+(LM75BD_IIC_Read_Byte(!ACK_SIG));
	
	LM75BD_IIC_Stop();//IICֹͣ
	
	Temputerature_16 = Temputerature_16>>5;//1LSB=0.125
	rt_kprintf("Temputerature_16 = %d  \n\n",Temputerature_16);
	if(Temputerature_16&0x0400)//���¶�
	{
		LM75BD_Temputerature = -(~(Temputerature_16&0x03FF)+1)*0.125;
	}
	else//���¶�
	{
		LM75BD_Temputerature = 0.125*(float)Temputerature_16;
	}
	rt_kprintf("LM75BD_Temputerature = %.2f ���϶�  \n\n",LM75BD_Temputerature);
	return (uint16_t)(LM75BD_Temputerature*100);
}


