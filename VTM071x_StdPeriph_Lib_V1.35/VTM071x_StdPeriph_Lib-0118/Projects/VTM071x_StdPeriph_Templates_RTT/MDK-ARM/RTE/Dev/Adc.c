#include "config.h"
#include "Adc.h"

#if ADC_EN == 1

#define ADC_CLKDIV	        8

void ADC_Configuration(void)						  
{
    uint32_t delay=0;
	ADC_InitTypeDef ADC_InitStructure;							//�ṹ��										
	NVIC_InitTypeDef NVIC_InitStructure;						//�ṹ��

    /* PowerDown digital function */
    GPIO_ANAConfig(GPIO0, GPIO_Pin_0, ENABLE);					//����GPIO0_0ģ�⹦��
    GPIO_ANAConfig(GPIO0, GPIO_Pin_1, ENABLE);					//����GPIO0_1ģ�⹦��
   
    /* Enable ADC interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;				//ʹ��ADC_IRQnͨ��
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;				//ָ��IRQͨ�����ȼ�Ϊ0��ֵ��0-3֮�䣩
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ��NVIC_IRQChannel�ж����IRQͨ��
	NVIC_Init(&NVIC_InitStructure);								//��ʼ��NVIC
	
    /* PownOn ADC Analog switch */
	RCC_PDRUNConfig(RCC_PDCFG_ADC, RCC_PDCFG_POWER_ON);			//ʹ��RCC_PDCFG_ADC
    
    /* ADC clock -- Main clock / (ADC_CLKDIV * 14) */
	RCC_SETCLKDivider(RCC_CLOCKFREQ_ADCCLK, ADC_CLKDIV);		//����ʱ�ӷ�Ƶ����
    
    /* PowerOn ADC clock */
	RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_ADC, ENABLE);			//ʹ��ADCʱ��
    
    /* DeInit */
	ADC_DeInit();												//��ADC����Ĵ�����ʼ��Ϊ��Ĭ������ֵ

    /* Initialize */
	ADC_StructInit(&ADC_InitStructure);							//��Ĭ��ֵ���ÿ��ADC_InitStruct��Ա
    
    /* TIMER0 MAT0 rising edge trigger ADC */
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T0_IRQ;
	ADC_Init(&ADC_InitStructure);

    /* Discontinuous mode */
	ADC_DiscModeCmd(DISABLE);									//Ϊ��ѡͨ���رռ��ģʽ
    
    /* Cover previous data */
	ADC_OverrunModeCmd(ENABLE);									//Ϊ��ѡͨ���������ģʽ
    
    /* Enable channle 0 1 */
	ADC_ChannelConfig(ADC_Channel_0|ADC_Channel_1);				//ʹ��channle_0��channle_1
    
    /* Delay ms */
	for (delay=0; delay<0x2000; delay++){;}						//forѭ��
    
    /* Start Conversion */
    ADC_StartOfConversion();									//��ʼת��
    
    /* ADC EOSEQ interrupt */
	ADC_ITConfig(ADC_IT_EOSEQ, ENABLE);							//ʹ���ж�
}

void ADC_IRQHandler(void)
{
    if (ADC_GetITStatus(ADC_IT_EOSEQ) == SET)
    {
        ADC_ClearITPendingBit(ADC_IT_EOC|ADC_IT_EOSEQ);

        /* Print adc channal 0 1 value */
        //rt_kprintf("Ch0: %d, Ch1: %d\r\n", ADC_GetConversionValue(ADC_Channel_0), ADC_GetConversionValue(ADC_Channel_1));
    }
}

/*************************************************************************
*                            ��������
*************************************************************************
*/
rt_timer_t ADCProcessSoftTimer;//�����ʱ�����ƿ�ָ��

/*************************************************************************
*                             �����ʱ���ص���������
*************************************************************************
*/
static void ADCProcessSoftTimer_callback(void* parameter)
{
	#if 0
	rt_kprintf("\r\n GPIO0_0(ADC0) value = %.2f V \r\n",(float)ADC_GetConversionValue(ADC_Channel_0)/4096 * 3.3);
	rt_kprintf("\r\n GPIO0_1(ADC1) value = %.2f V \r\n",(float)ADC_GetConversionValue(ADC_Channel_1)/4096 * 3.3);
	#endif
}

int ADCProcessInit()
{
	ADC_Configuration();//ADC��ʼ��
	ADCProcessSoftTimer = rt_timer_create("ADCProcessSoftTimer", /* �����ʱ�������� */
                        ADCProcessSoftTimer_callback,/* �����ʱ���Ļص����� */
                        0,			/* ��ʱ����ʱ��������ڲ��� */
                        2*RT_TICK_PER_SECOND,   /* �����ʱ���ĳ�ʱʱ��(���ڻص�ʱ��) */
                        RT_TIMER_FLAG_PERIODIC );
                        /* �����ʱ��HARD_TIMERģʽ ����ģʽ */
 
	
	return 0;
}
	
INIT_APP_EXPORT(ADCProcessInit);


#endif


