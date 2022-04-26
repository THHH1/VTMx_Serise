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
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART_Configuration(void);																									//��������USART

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
    /* USART */
    USART_Configuration();																											//����USART
    printf("\r\n-----------------|- VTM071x USART -|-----------------\r\n");			//�����ӡ
    
    while(1)																																		//����ѭ��
    {}
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

    /* Enable USART0 IRQ */
    NVIC_EnableIRQ(USART0_IRQn);																								//ʹ��USART0�ж�����

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);												//����RCC����ʱ��
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);																//ѡȡʱ��Դ��ѡȡʱ��Դ��Ҫ��ôp27��
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);								//����ʱ�ӷ�Ƶ��ϵ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;																		//ʹ��GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;													//���Ƶ��50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;															//���ù���1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;														//��������
    GPIO_Init(GPIO1, &GPIO_InitStructure);																			//�ṹ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;																		//ʹ��GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);																			//�ṹ��

    USART_DeInit(USART0);																												//��USART�Ĵ�������ΪĬ��ֵ
    USART_StructInit(&USART_InitStructure);																			//��USART_InitStructure�ṹ�������Ա��Ĭ��ֵ���
    USART_Init(USART0, &USART_InitStructure);																		//���ݽṹ��Ĳ�����������USART������г�ʼ��
		
    /* Enable USART0 RX and Receive timeout irq */
    USART_ITConfig(USART0, USART_IT_RXIEN, ENABLE);															//����USART_IT_RXIEN�ж�Դ
    USART_RXTOCountConfig(USART0, 20);																					//���� RXTO ����
    USART_ITConfig(USART0, USART_IT_RXTOEN, ENABLE);														//����USART_IT_RXTOEN�ж�Դ
    USART_Cmd(USART0, ENABLE);																									//ʹ��USART����
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
    USART_SendData(USART0, (uint8_t) ch);		//-

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

