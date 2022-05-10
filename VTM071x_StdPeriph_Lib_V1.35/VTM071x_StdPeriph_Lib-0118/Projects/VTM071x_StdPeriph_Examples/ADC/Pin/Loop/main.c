/**
  ******************************************************************************
  * @file    Project/VTM071x_StdPeriph_Templates/main.c 
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MIC SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USART0_CLOCK_DIV	1
#define ADC_CLKDIV	        7

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t systick_ms = 0;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART_Configuration(void);																									//����USART_Configuration
void ADC_Configuration(void);   																								//����ADC_Configuration

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
   	uint32_t systickclk;																											//����systickclk
    uint32_t adc_ch0, adc_ch1;																								//����adc_ch0������adc_ch1
    
    /* USART */
    USART_Configuration();																										//����USART
	printf("\r\n-----------------|- VTM071x ADC -|-----------------\r\n");				//�����ӡ

    /* SYSTICK */
	systickclk = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000;							//��Ƭ��ʱ�ӵ����ʳ���1000������ֵ��systickclk����������ٶ�
    SysTick_Config(systickclk);

    /* ADC */
	ADC_Configuration();																												//����ADC

	while(1)																																		//����ѭ��
	{
        /* Conversion per 50ms */
		ADC_StartOfConversion();																									//��ʼת��
        
        while (ADC_GetITStatus(ADC_IT_EOSEQ) != SET);													//
        ADC_ClearITPendingBit(ADC_IT_EOSEQ);																	//���ADC_IT_EOSEQ���жϹ���λ

        adc_ch0 = ADC_GetConversionValue(ADC_Channel_0);											//����ADC_Channel_0ͨ���� ADC ת���������
        adc_ch1 = ADC_GetConversionValue(ADC_Channel_1);											//����ADC_Channel_0ͨ���� ADC ת���������
        
        /* Print adc channal 0 1 2 value */
        printf("%4d, %4d\r\n", adc_ch0, adc_ch1);															//�����ӡ

        systick_ms = 50;
        while(systick_ms){}
	}
}

/**
  * @brief  Configuare ADC.
  * @param  None
  * @retval None
  */
void ADC_Configuration(void)																										//����ADC_Configuration	  
{
    uint32_t delay=0;                                                           //
    
	ADC_InitTypeDef ADC_InitStructure;																						//�ṹ��

    /* PowerDown digital function */
    GPIO_ANAConfig(GPIO0, GPIO_Pin_0, ENABLE);																	//����GPIO0_0ģ�⹦��
    GPIO_ANAConfig(GPIO0, GPIO_Pin_1, ENABLE);																	//����GPIO0_1ģ�⹦��

    /* PownOn ADC Analog switch */
	RCC_PDRUNConfig(RCC_PDCFG_ADC, RCC_PDCFG_POWER_ON);														//ʹ��RCC_PDCFG_ADC����������								
    
    /* ADC clock -- Main clock / (ADC_CLKDIV * 14) */
	RCC_SETCLKDivider(RCC_CLOCKFREQ_ADCCLK, ADC_CLKDIV);													//����ʱ�ӷ�Ƶ����
    
    /* PowerOn ADC clock */
	RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_ADC, ENABLE);														//ʹ��ADC����
    
    /* DeInit */
	ADC_DeInit();																																	//��ADC����Ĵ�����ʼ��Ϊ��Ĭ������ֵ

    /* Initialize */
	ADC_StructInit(&ADC_InitStructure);																						//��Ĭ��ֵ���ÿ��ADC_InitStruct��Ա
	ADC_Init(&ADC_InitStructure);																									//��ʼ��ADC
    
    /* Continuous mode */
	ADC_DiscModeCmd(DISABLE);																											//Ϊ��ѡͨ���رռ��ģʽ																								
    
    /* Cover previous data */
	ADC_OverrunModeCmd(ENABLE);																										//Ϊ��ѡͨ���������ģʽ
    
    /* Enable channle 0 1 */
	ADC_ChannelConfig(ADC_Channel_0 | ADC_Channel_1);															//ʹ��channle 0��channle 1
    
    /* ADC EOSEQ interrupt */
	ADC_ITConfig(ADC_IT_EOSEQ, ENABLE);																						//ʹ��ADC_IT_EOSEQ�ж�

    /* Delay ms */
	for (delay=0; delay<0x2000; delay++);																					//forѭ��
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)																								
{
    USART_InitTypeDef USART_InitStructure;																			//�ṹ��
    GPIO_InitTypeDef GPIO_InitStructure;																				//�ṹ��

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);												//ʹ��USART0ʱ��
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);																//ѡȡʱ��Դ
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);								//����ʱ�ӷ�Ƶ����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;																		//GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;													//Ƶ�ʸ�50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;															//���ù���ģʽ1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;														//��������
    GPIO_Init(GPIO1, &GPIO_InitStructure);																			//GPIO1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;																		//GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);																			//GPIO1

    USART_DeInit(USART0);																												//��USART0�Ĵ�������ΪĬ��ֵ
    USART_StructInit(&USART_InitStructure);																			//��USART_InitStructure�ṹ�������Ա��Ĭ��ֵ���
    USART_Init(USART0, &USART_InitStructure);																		//���ݽṹ��Ĳ�����������USART0������г�ʼ��
    USART_Cmd(USART0, ENABLE);																									//ʹ��USART0����
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART0, (uint8_t) ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART0, USART_FLAG_TXFE) == RESET)
    {}

    return ch;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

