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
#include "VTM071x_eval_spi.h"

/** @addtogroup VTM071x_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USART0_CLOCK_DIV	1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t read_buf[256];
uint8_t write_buf[256];

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
    int i;																																//变量 i
    uint8_t ID[4];																												//数组ID
    
    /* USART */
    USART_Configuration();																								//配置USART
    printf("\r\n-----------------|- VTM071x SPI Flash -|-----------------\r\n");				//输出打印
    
    for (i=0; i<256; i++)																									//for 循环
    {
        read_buf[i] = 0;																									//
        write_buf[i] = i;																									//
    }
    
    /* Init SPI */
    SPI_FLASH_Init();																											//初始化SPI
    /* Read ID */
    SPI_FLASH_ReadID(ID);																									//读取SPI FLASH 的ID
    printf("ID: 0x%x, 0x%x.\r\n", ID[0], ID[1]);													//输出打印
    
    /* Erase Sector 0 */
    SPI_FLASH_EraseSector4K(0);																						//擦除一个扇区
    /* Read */
    SPI_FLASH_Read(read_buf, 0, 256);																			//从 SPI FLASH 读取数据
    for (i=0; i<256; i++)																									//for 循环
    {
        printf("0x%x.\r\n", read_buf[i]);																	//输出打印
    }
    
    /* Write */
    SPI_FLASH_Write(write_buf, 0, 256);																		//将数据写入SPI FLASH
    SPI_FLASH_Read(read_buf, 0, 256);																			//从SPI FLASH 读取数据
    for (i=0; i<256; i++)																									//for 循环
    {
        printf("0x%x.\r\n", read_buf[i]);																	//输出打印
    }
    
	while(1)																																//无限循环
	{
	}
}

/**
  * @brief  Configuare USART.
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;																//结构体
    GPIO_InitTypeDef GPIO_InitStructure;																	//结构体

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);									//使能USART0时钟
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);													//选取时钟源
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);					//设置时钟分频因子

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;															//GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;										//频率高50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;												//备用功能模式1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;											//浮空输入
    GPIO_Init(GPIO1, &GPIO_InitStructure);																//GPIO1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;															//GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);																//GPIO1

    USART_DeInit(USART0);																									//将USART0寄存器重置为默认值
    USART_StructInit(&USART_InitStructure);																//将USART_InitStructure结构体变量成员按默认值填充
    USART_Init(USART0, &USART_InitStructure);															//根据结构体的参数配置来对USART0外设进行初始化
    USART_Cmd(USART0, ENABLE);																						//使能USART0外设
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

