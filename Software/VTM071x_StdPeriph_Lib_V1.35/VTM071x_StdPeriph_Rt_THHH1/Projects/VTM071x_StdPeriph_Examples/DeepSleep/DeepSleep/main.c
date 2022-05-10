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
volatile uint32_t systick_ms = 0;

/* Private function prototypes -----------------------------------------------*/
void PowerDown(void);
void DeepSleep(void);
void Delay_ms(uint32_t ms);
void LED_Init(void);
void LED_Toggle(void);
void DeepSleep_Configuration(void);


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART_Configuration(void);

/* Private functions ---------------------------------------------------------*/

void PowerDown(void)
{
	RCC->PCON = 0x2;
	SCB->SCR = 0x4;
	__WFI();
}

void DeepSleep(void)
{
	RCC->PCON = 0x10000;
	SCB->SCR = 0x4;
	__WFI();
}

void Delay_ms(uint32_t ms)
{
    systick_ms = ms;
    while(systick_ms);
}

void LED_Init(void)																																			//����LED_Init
{
    GPIO_InitTypeDef GPIO_InitStructure;																								//�ṹ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;																						//GPIO6_4
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;																	//Ƶ�ʸ�50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;																				//���ģʽ
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;																		//��������
    GPIO_Init(GPIO6, &GPIO_InitStructure);																							//GPIO6																					
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;																						//GPIO6_5
    GPIO_Init(GPIO6, &GPIO_InitStructure);																							//GPIO6
    
    GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_SET);																					//����GPIO6_4Ϊ1
    GPIO_WriteBit(GPIO6, GPIO_Pin_5, Bit_SET);																					//����GPIO6_5Ϊ1
}

void LED_Toggle(void)																																		//����LED_Toggle
{
    static BitAction flag = Bit_SET;																										//
    
    GPIO_WriteBit(GPIO6, GPIO_Pin_4, flag);																							//
    GPIO_WriteBit(GPIO6, GPIO_Pin_5, flag);
    
    if (flag ==  Bit_SET)
        flag = Bit_RESET;
    else
        flag = Bit_SET;
}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
    uint32_t systickclk, i;																															//����systickclk��i
        
    /* USART */
    USART_Configuration();																															//����USART
	printf("\r\n-----------------|- VTM071x DeepSleep -|-----------------\r\n");						//�����ӡ

    /* SYSTICK */
	systickclk = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000;												//��Ƭ��ʱ�ӵ����ʳ���1000������ֵ��systickclk����������ٶ�
    SysTick_Config(systickclk);																													

    /* LED initialize */
    LED_Init();																																					//��ʼ��LED
    
    /* Delay 3S, LED Blink */
    for (i=0; i<21; i++)																																//forѭ��
    {	
        LED_Toggle();
        Delay_ms(150);
    }

    /* DeepSleep */
    DeepSleep_Configuration();																													//����DeepSleep

    /* SYSTICK */
	systickclk = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK) / 1000;												//��Ƭ��ʱ�ӵ����ʳ���1000������ֵ��systickclk����������ٶ�
    SysTick_Config(systickclk);																		

    /* LED initialize */
    LED_Init();																																					//��ʼ��LED

    while(1)																																						//����ѭ��
	{
        /* LED */
        LED_Toggle();
        Delay_ms(50);
	}
}

/**
  * @brief  Configuare DeepSleep.
  * @param  None
  * @retval None
  */
void DeepSleep_Configuration(void)																											//����DeepSleep
{
    int i;
    GPIO_InitTypeDef GPIO_InitStructure; 																								//�ṹ��

    /* GPIO */
    //TODO: INPUT pull-down
    GPIOBANK0->DIR_CLR = 0xFFFFFFFF;																										//
    GPIOBANK1->DIR_CLR = 0xFFFFFFFF;

    for (i=0; i<56; i++)
    {
        *(volatile uint32_t *)(0x40001000+i*4) = 0x88;
    }
    
    /* Wakeup IO */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;																						//GPIO1_0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;																	//Ƶ�ʸ�50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;																				//����ģʽ
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;																			//��������
    GPIO_Init(GPIO1, &GPIO_InitStructure);																							//GPIO1
    GPIO_ClearITPendingBit(GPIO1, GPIO_Pin_0);																					//���GPIO���жϹ���λ
    GPIO_ITConfig(GPIO1, GPIO_Pin_0, GPIO_IT_EDGE_RISING, ENABLE);
    NVIC_EnableIRQ(GPIO0_TO_GPIO3_IRQn);

    /* Digital */
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, 0);																			//����ʱ�ӷ�Ƶ����
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART1CLK, 0);																			//����ʱ�ӷ�Ƶ����
    RCC_SETCLKDivider(RCC_CLOCKFREQ_SYSTICKCLK, 0);																			//����ʱ�ӷ�Ƶ����
    RCC_SETCLKDivider(RCC_CLOCKFREQ_SPI0CLK, 0);																	  		//����ʱ�ӷ�Ƶ����
    RCC_SETCLKDivider(RCC_CLOCKFREQ_SPI1CLK, 0);																				//����ʱ�ӷ�Ƶ����
    RCC_SETCLKDivider(RCC_CLOCKFREQ_WWDGCLK, 0);																				//����ʱ�ӷ�Ƶ����
    RCC_SETCLKDivider(RCC_CLOCKFREQ_CLKOUTCLK, 0);																			//����ʱ�ӷ�Ƶ����
    RCC_SETCLKDivider(RCC_CLOCKFREQ_ADCCLK, 0);																					//����ʱ�ӷ�Ƶ����
    RCC_SETCLKDivider(RCC_CLOCKFREQ_DACCLK, 0);																					//����ʱ�ӷ�Ƶ����
    SysTick->CTRL = 0;

    RCC->AHBCLKCTRL0 = RCC_AHBCLKCTRL_IOCON | RCC_AHBCLKCTRL_ROM | \
                       RCC_AHBCLKCTRL_GPIO | RCC_AHBCLKCTRL_RAM | \
                       RCC_AHBCLKCTRL_FLASH;
    RCC->AHBCLKCTRL1 = 0;
    
    RCC_SETCLKDivider(RCC_CLOCKFREQ_SYSAHBCLK, 10);																			//����ʱ�ӷ�Ƶ����
    
    /* Analog */
    RCC_PDAWAKEConfig(RCC_PDCFG_OSC12M | RCC_PDCFG_ADC | RCC_PDCFG_BOD | \
                      RCC_PDCFG_ACMP | RCC_PDCFG_USB | RCC_PDCFG_32768_OSC | \
                      RCC_PDCFG_DAC0 | RCC_PDCFG_DAC1 | RCC_PDCFG_USB_LDO | \
                      RCC_PDCFG_BOR, RCC_PDCFG_POWER_DOWN);
    RCC_PDAWAKEConfig(RCC_PDCFG_IRC12M | RCC_PDCFG_FLASH, RCC_PDCFG_POWER_ON);

    RCC_BORConfig(RCC_BORRST_VAL_2_2, DISABLE);

    RCC_PDSLEEPConfig(RCC_PDCFG_OSC12M | RCC_PDCFG_ADC | RCC_PDCFG_BOD | \
                      RCC_PDCFG_ACMP | RCC_PDCFG_USB | RCC_PDCFG_32768_OSC | \
                      RCC_PDCFG_DAC0 | RCC_PDCFG_DAC1 | RCC_PDCFG_USB_LDO | \
                      RCC_PDCFG_BOR | RCC_PDCFG_IRC12M | RCC_PDCFG_FLASH | \
                      RCC_PDCFG_SYSPLL, RCC_PDCFG_POWER_DOWN);

    /* PowerDown USB and Reset */
    RCC->PDRUNCFG |= (1<<10);
    RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_USB, ENABLE);
    RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_USB, DISABLE);
	
    /* Switch to 10K IRC */
    RCC_MAINCLKSel(RCC_MAINCLK_SOURCE_10K_IRC);

    /* Delay */
    for (i=0; i<10; i++);

    /* Deep Sleep */
    DeepSleep();
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;																								//�ṹ��
    GPIO_InitTypeDef GPIO_InitStructure;																									//�ṹ��

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);																	//ʹ��USART0ʱ��
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);																					//ѡȡʱ��Դ
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);													//����ʱ�ӷ�Ƶ����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;																							//GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;																		//Ƶ�ʸ�50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;																				//���ù���ģʽ1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;																			//��������
    GPIO_Init(GPIO1, &GPIO_InitStructure);																								//GPIO1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;																							//GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);																								//GPIO1

    USART_DeInit(USART0);																																	//��USART0�Ĵ�������ΪĬ��ֵ
    USART_StructInit(&USART_InitStructure);																								//��USART_InitStructure�ṹ�������Ա��Ĭ��ֵ���
    USART_Init(USART0, &USART_InitStructure);																							//���ݽṹ��Ĳ�����������USART0������г�ʼ��
    USART_Cmd(USART0, ENABLE);																														//ʹ��USART0����
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

