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
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void USART_Configuration(void);																									//����USART����
void RTC_Configuration(void);																										//����RTC����
void Delay_cycles(uint32_t cycles);																							//

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/* Private functions ---------------------------------------------------------*/
void Delay_cycles(uint32_t cycles)
{
    while(cycles--)
        __NOP();
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
    /* USART0 */
    USART_Configuration();																											//����USART������
	printf("\r\n-----------------|- VTM071x -|-----------------\r\n");						//�����ӡ

    RTC_Configuration();																												//����RTC������
    
	while(1)																																			//����ѭ��
	{

	}
}

/**
  * @brief  Configuare RTC.
  * @param  None
  * @retval None
  */
void RTC_Configuration(void)
{
    RTC_InitTypeDef RTC_InitStructure;																					//�ṹ��
    
	/* RTC Clock */
	RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_RTC, ENABLE);														//����RTCʱ��

    /* DeInit */
    RTC_DeInit();																																//��ʼ��RTC

    /* RTC register can be write */
    RTC_LoadCmd(ENABLE);																												//��RTC�Ĵ�����Ϊ��д״̬
    
    /* Select IRC 12M, Set default value to 100s */
    RTC_InitStructure.RTC_ClkSource = RTC_CTRL_CLK_SEL_IRC12M;									//ָ��RTCʱ��ԴΪIRC 12M
    RTC_InitStructure.RTC_Second = 100;																					//ѡ���ʼֵΪ100s
    RTC_Init(&RTC_InitStructure);																								//����ָ����ʼ��RTC������
    
    /* Alarm 110s */
    RTC_AlarmConfig(110);																												//����RTC��ʱ���ڵ�110s����
    
    /* Enable HZ and Alarm interrupt */
    RTC_ITConfig(RTC_IT_SEC | RTC_IT_ALARM, ENABLE);														//����HZ�������ж�
    
    /* Enable RTC */
    RTC_Cmd(ENABLE);																														//����RTC��ʱ��
    
    /* Disable load bit*/
    RTC_LoadCmd(DISABLE);																												//����RTC����λ
    
    /* Enable RTC NVIC */
    NVIC_EnableIRQ(RTC_IRQn);																										//�����ⲿ�ж�
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)																									//����USART
{
    USART_InitTypeDef USART_InitStructure;																			//�ṹ��
    GPIO_InitTypeDef GPIO_InitStructure;																				//�ṹ��

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);												//ʹ��APB����ʱ��
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

