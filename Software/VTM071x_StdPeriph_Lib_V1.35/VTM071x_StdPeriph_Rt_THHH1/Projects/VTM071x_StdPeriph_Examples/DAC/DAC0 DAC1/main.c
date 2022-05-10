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
#include "VTM071x_dac.h"

/** @addtogroup VTM071x_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USART0_CLOCK_DIV	1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART_Configuration(void);
void DAC_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
    /* USART */
    USART_Configuration();																																//����USART
	printf("\r\n-----------------|- VTM071x DAC -|-----------------\r\n");										//�����ӡ

    SysTick_Config(SystemCoreClock / 4000);																								//
    
    /* DAC */
    DAC_Configuration();																																	//����DAC

    while(1)																																							//����ѭ��
	{
	}
}

/**
  * @brief  Configuare DAC.
  * @param  None
  * @retval None
  */
void DAC_Configuration(void)						  
{
    DAC_InitTypeDef DAC_InitStructure;																										//�ṹ��

    RCC_PDRUNConfig(RCC_PDCFG_DAC0, RCC_PDCFG_POWER_ON);																	//ʹ��RCC_PDCFG_DAC0
    RCC_PDRUNConfig(RCC_PDCFG_DAC1, RCC_PDCFG_POWER_ON);																	//ʹ��RCC_PDCFG_DAC1

    RCC_SETCLKDivider(RCC_CLOCKFREQ_DACCLK, 128);																					//����ʱ�ӷ�Ƶ����
    
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL1_DAC, ENABLE);																		//ʹ��DACʱ��
    DAC_DeInit();																																					//��DAC�Ĵ�������ΪĬ��ֵ
    
    GPIO_ANAConfig(GPIO4, GPIO_Pin_4, ENABLE);																						//����GPIO4_4ģ�⹦��
    GPIO_ANAConfig(GPIO4, GPIO_Pin_5, ENABLE);																						//����GPIO4_5ģ�⹦��
    
    DAC_InitStructure.DAC_ReferenceVoltage = DAC_REF_VOLTAGE_VDDA;												//ָ��DAC�ο���ѹ
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;												//������DAC_OutputBuffer
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_WRITE_DATA;																//ָ��DACͨ������������
    DAC_Init(DAC0, &DAC_InitStructure);																										//��ʼ��DAC0
    DAC_Init(DAC1, &DAC_InitStructure);																										//��ʼ��DAC1
    
    DAC_Cmd(DAC0, ENABLE);																																//ʹ��DAC0
    DAC_Cmd(DAC1, ENABLE);																																//ʹ��DAC1
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;																									//�ṹ��
    GPIO_InitTypeDef GPIO_InitStructure;																										//�ṹ��

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);																		//ʹ��USARTʱ��
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);																						//ѡȡʱ��Դ
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);														//����ʱ�ӷ�Ƶ����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                                               //GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;																			//Ƶ�ʸ�50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;																					//���ù���ģʽ1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;																				//��������
    GPIO_Init(GPIO1, &GPIO_InitStructure);																									//GPIO1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;																								//GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);																									//GPIO1

    USART_DeInit(USART0);																																		//��USART0�Ĵ�������ΪĬ��ֵ
    USART_StructInit(&USART_InitStructure);																									//��USART_InitStructure�ṹ�������Ա��Ĭ��ֵ���
    USART_Init(USART0, &USART_InitStructure);																								//���ݽṹ��Ĳ�����������USART0������г�ʼ��
    USART_Cmd(USART0, ENABLE);																															//ʹ��USART0����
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

