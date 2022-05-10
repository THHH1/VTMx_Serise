#include "config.h"
#include "Adc.h"

#if ADC_EN == 1

#define ADC_CLKDIV	        8

void ADC_Configuration(void)						  
{
    uint32_t delay=0;
	ADC_InitTypeDef ADC_InitStructure;							//结构体										
	NVIC_InitTypeDef NVIC_InitStructure;						//结构体

    /* PowerDown digital function */
    GPIO_ANAConfig(GPIO0, GPIO_Pin_0, ENABLE);					//配置GPIO0_0模拟功能
    GPIO_ANAConfig(GPIO0, GPIO_Pin_1, ENABLE);					//配置GPIO0_1模拟功能
   
    /* Enable ADC interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;				//使能ADC_IRQn通道
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;				//指定IRQ通道优先级为0（值在0-3之间）
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能NVIC_IRQChannel中定义的IRQ通道
	NVIC_Init(&NVIC_InitStructure);								//初始化NVIC
	
    /* PownOn ADC Analog switch */
	RCC_PDRUNConfig(RCC_PDCFG_ADC, RCC_PDCFG_POWER_ON);			//使能RCC_PDCFG_ADC
    
    /* ADC clock -- Main clock / (ADC_CLKDIV * 14) */
	RCC_SETCLKDivider(RCC_CLOCKFREQ_ADCCLK, ADC_CLKDIV);		//设置时钟分频因子
    
    /* PowerOn ADC clock */
	RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_ADC, ENABLE);			//使能ADC时钟
    
    /* DeInit */
	ADC_DeInit();												//将ADC外设寄存器初始化为其默认重置值

    /* Initialize */
	ADC_StructInit(&ADC_InitStructure);							//将默认值填充每个ADC_InitStruct成员
    
    /* TIMER0 MAT0 rising edge trigger ADC */
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T0_IRQ;
	ADC_Init(&ADC_InitStructure);

    /* Discontinuous mode */
	ADC_DiscModeCmd(DISABLE);									//为所选通道关闭间断模式
    
    /* Cover previous data */
	ADC_OverrunModeCmd(ENABLE);									//为所选通道启用溢出模式
    
    /* Enable channle 0 1 */
	ADC_ChannelConfig(ADC_Channel_0|ADC_Channel_1);				//使能channle_0和channle_1
    
    /* Delay ms */
	for (delay=0; delay<0x2000; delay++){;}						//for循环
    
    /* Start Conversion */
    ADC_StartOfConversion();									//开始转换
    
    /* ADC EOSEQ interrupt */
	ADC_ITConfig(ADC_IT_EOSEQ, ENABLE);							//使能中断
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
*                            变量定义
*************************************************************************
*/
rt_timer_t ADCProcessSoftTimer;//软件定时器控制块指针

/*************************************************************************
*                             软件定时器回调函数定义
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
	ADC_Configuration();//ADC初始化
	ADCProcessSoftTimer = rt_timer_create("ADCProcessSoftTimer", /* 软件定时器的名称 */
                        ADCProcessSoftTimer_callback,/* 软件定时器的回调函数 */
                        0,			/* 定时器超时函数的入口参数 */
                        2*RT_TICK_PER_SECOND,   /* 软件定时器的超时时间(周期回调时间) */
                        RT_TIMER_FLAG_PERIODIC );
                        /* 软件定时器HARD_TIMER模式 周期模式 */
 
	
	return 0;
}
	
INIT_APP_EXPORT(ADCProcessInit);


#endif


