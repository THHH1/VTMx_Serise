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
#define ADC_CLKDIV	        60

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

void USART_Configuration(void);											                    //����USART_Configuration
void ADC_Configuration(void);                                           //����ADC_Configuration

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
   	uint32_t systickclk;																								//����systickclk

    /* USART */																													
    USART_Configuration();																							//����USART
	printf("\r\n-----------------|- VTM071x ADC -|-----------------\r\n");	//�����ӡ

    /* SYSTICK */
	systickclk = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000;				//��Ƭ��ʱ�ӵ����ʳ���1000������ֵ��systickclk����������ٶ�,	������1000�������޸���ֵ������ٶȳ�����
    SysTick_Config(systickclk);

    /* ADC */
	ADC_Configuration();																									//����ADC

	while(1)																															//����ѭ��
	{
        /* Conversion per 200ms */
		ADC_StartOfConversion();																						//��ʼת��																				

        systick_ms = 200;																								//ÿ200ms����ת��	
        while(systick_ms){}
	}
}

/**
  * @brief  Configuare ADC.
  * @param  None
  * @retval None
  */
void ADC_Configuration(void)																						//����ADC_Configuration				  
{
    uint32_t delay=0;																				
	ADC_InitTypeDef ADC_InitStructure;																		//�ṹ��
	NVIC_InitTypeDef NVIC_InitStructure;																	//�ṹ��
    
    /* Enable ADC interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;                        //ʹ��ADC_IRQnͨ��
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;												//ָ��IRQͨ�����ȼ�Ϊ0��ֵ��0-3֮�䣩
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;												//ʹ��NVIC_IRQChannel�ж����IRQͨ��
	NVIC_Init(&NVIC_InitStructure);																				//��ʼ��NVIC
	
    /* PownOn ADC Analog switch */
	RCC_PDRUNConfig(RCC_PDCFG_ADC, RCC_PDCFG_POWER_ON);										//ʹ��RCC_PDCFG_ADC����������
    
    /* ADC clock -- Main clock / (ADC_CLKDIV * 14) = 100K */
	RCC_SETCLKDivider(RCC_CLOCKFREQ_ADCCLK, ADC_CLKDIV);									//����ʱ�ӷ�Ƶ����
    
    /* PowerOn ADC clock */
	RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_ADC, ENABLE);              			//ʹ��ADCʱ��
    
    /* DeInit */
	ADC_DeInit();                                                         //��ADC����Ĵ�����ʼ��Ϊ��Ĭ������ֵ

    /* Initialize */
	ADC_StructInit(&ADC_InitStructure);                                   //��Ĭ��ֵ���ÿ��ADC_InitStruct��Ա
    ADC_InitStructure.ADC_Discard0 = ADC_Discard0_1;                    //ָ���״�ת��ʱ������ֵ
	ADC_Init(&ADC_InitStructure);                                         //��ʼ��ADC
    
    /* Discontinuous mode */
	ADC_DiscModeCmd(ENABLE);																							//Ϊ��ѡͨ�����ü��ģʽ
    
    /* Cover previous data */
	ADC_OverrunModeCmd(ENABLE);																						//Ϊ��ѡͨ���������ģʽ
    
    /* Temperature Sensor must be enabled before ADC channel*/
    ADC_TempSensorCmd(ENABLE);                                          //ʹ���¶ȴ�����ͨ��
    
    /* Delay ms */
	for (delay=0; delay<0x2000; delay++);                                 //forѭ��
    
    /* Enable channle 15 */
	ADC_ChannelConfig(ADC_Channel_15);                                    //ʹ��channle 15
    
    /* Delay ms */
	for (delay=0; delay<0x2000; delay++);
    
    /* ADC EOC interrupt */
	ADC_ITConfig(ADC_IT_EOC, ENABLE);																			//ʹ��ADC_IT_EOC��ת���������ж�
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;												  	  //�ṹ��
    GPIO_InitTypeDef GPIO_InitStructure;                                //�ṹ��                             

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);						  	//ʹ��USART0ʱ��
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);											  //ѡȡʱ��Դ
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);			  //����ʱ�ӷ�Ƶ����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;													  //GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;								  //Ƶ�ʸ�50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;                      //���ù���ģʽ1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                    //��������
    GPIO_Init(GPIO1, &GPIO_InitStructure);                              //GPIO1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                           //GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);                              //GPIO1

    USART_DeInit(USART0);                                               //��USART0�Ĵ�������ΪĬ��ֵ	
    USART_StructInit(&USART_InitStructure);                             //��USART_InitStructure�ṹ�������Ա��Ĭ��ֵ���
    USART_Init(USART0, &USART_InitStructure);                           //���ݽṹ��Ĳ�����������USART0������г�ʼ��
    USART_Cmd(USART0, ENABLE);                                          //ʹ��USART0����
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

