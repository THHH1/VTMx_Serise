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
#include <math.h>
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USART0_CLOCK_DIV	1
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t timer_ms = 0;

/* Private function prototypes -----------------------------------------------*/
void APROM_Erase(uint32_t flash_addr);
void APROM_ProgramData(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize);
void Flash_ReadData(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ReadSize);
void LDROM_Erase(uint32_t flash_addr);
void LDROM_ProgramData(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize);
void USART_Configuration(void);
void Timer_Configuration(void);


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/* Private functions ---------------------------------------------------------*/
void APROM_Erase(uint32_t flash_addr)
{
    //禁能Cache并且打开FLASH寄存器开关
    FLASH_CacheCmd(DISABLE);																											//禁用缓存																					
    FLASH_FlushCacheCmd(ENABLE);																									//启用刷新缓存
    FLASH_Unlock();																																//解锁FLASH控制寄存器和程序存储器访问

    //擦除该地址所在扇区
    FLASH_EraseAPROM(flash_addr);																									//清除程序内存中的指定扇区

    //使能Cache并且关闭FLASH寄存器开关
    FLASH_Lock();																																	//简短锁定程序内存访问
    FLASH_FlushCacheCmd(DISABLE);																									//禁用刷新缓存
	
    FLASH_CacheCmd(ENABLE);																												//启用缓存
}

void APROM_ProgramData(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize)
{
    //禁能Cache并且打开FLASH寄存器开关
    FLASH_CacheCmd(DISABLE);																											//禁用缓存
    FLASH_FlushCacheCmd(ENABLE);																									//
    FLASH_Unlock();

    //写APROM
    FLASH_ProgramAPROM(SramBuf, FlashAddr, ProgramSize);

    //使能Cache并且关闭FLASH寄存器开关
    FLASH_Lock();
    FLASH_FlushCacheCmd(DISABLE);
    FLASH_CacheCmd(ENABLE);
}

/* FlashAddr, ReadSize必须是4的倍数 */
void Flash_ReadData(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ReadSize)
{
    uint32_t i;

    for (i=0; i<(ReadSize >> 2); i++)
    {
        *(SramBuf + i) = *(volatile uint32_t *)(FlashAddr + i * 4);
    }
}

void LDROM_Erase(uint32_t flash_addr)
{
    //禁能Cache并且打开FLASH寄存器开关
    FLASH_CacheCmd(DISABLE);
    FLASH_FlushCacheCmd(ENABLE);
    FLASH_Unlock();

    //擦除该地址所在扇区
    FLASH_EraseLDROM(flash_addr);

    //使能Cache并且关闭FLASH寄存器开关
    FLASH_Lock();
    FLASH_FlushCacheCmd(DISABLE);
    FLASH_CacheCmd(ENABLE);
}

void LDROM_ProgramData(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize)
{
    //禁能Cache并且打开FLASH寄存器开关
    FLASH_CacheCmd(DISABLE);
    FLASH_FlushCacheCmd(ENABLE);
    FLASH_Unlock();

    //写APROM
    FLASH_ProgramLDROM(SramBuf, FlashAddr, ProgramSize);

    //使能Cache并且关闭FLASH寄存器开关
    FLASH_Lock();
    FLASH_FlushCacheCmd(DISABLE);
    FLASH_CacheCmd(ENABLE);
}

/* LDROM启动，可以打开这个宏，注意KEIL下载算法需要修改为MT220_FLASH_LD */
#define BOOT_FROM_LDROM

#ifdef  BOOT_FROM_LDROM
    #define FLASH_TEST_APROM_ADDR     0x10000000
    #define FLASH_TEST_LDROM_ADDR     0x1e00
#else
    #define FLASH_TEST_APROM_ADDR     0x10000
    #define FLASH_TEST_LDROM_ADDR     0x10000000
#endif

uint32_t r_buf[128];
uint32_t w_buf[128];

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
    int i;

    /* USART0 */
    USART_Configuration();
	printf("\r\n-----------------|- VTM071x IAP -|-----------------\r\n");

    for (i=0; i<128; i++)
    {
        r_buf[i] = i;
        w_buf[i] = 255-i;
    }

    APROM_Erase(FLASH_TEST_APROM_ADDR);
    APROM_ProgramData(w_buf, FLASH_TEST_APROM_ADDR, 512);
    Flash_ReadData(r_buf, FLASH_TEST_APROM_ADDR, 512);

    for (i=0; i<128; i++)
    {
        if (w_buf[i] != r_buf[i])
        {
            printf("Programm APROM ........................... Failed!\r\n");
            break;
        }
    }

    if (i == 128)
        printf("APROM Test.................................... OK!\r\n");

    for (i=0; i<128; i++)																		
    {
        r_buf[i] = i;
        w_buf[i] = 255-i;
    }

    LDROM_Erase(FLASH_TEST_LDROM_ADDR);
    LDROM_ProgramData(w_buf, FLASH_TEST_LDROM_ADDR, 512);
    Flash_ReadData(r_buf, FLASH_TEST_LDROM_ADDR, 512);														//

    for (i=0; i<128; i++)																													//for循环
    {
        if (w_buf[i] != r_buf[i])
        {
            printf("Programm LDROM ........................... Failed!\r\n");			//输出打印
            break;			
        }
    }

    if (i == 128)																																	//i是否等于128
        printf("LDROM Test.................................... OK!\r\n");

	while(1)																																				//无限循环
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
    USART_InitTypeDef USART_InitStructure;																				//结构体
    GPIO_InitTypeDef GPIO_InitStructure;																					//结构体

    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);													//使能USART0时钟
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);																	//选取时钟源
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);									//设置时钟分频因子

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;																			//GPIO1_1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;														//频率高50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;																//备用功能模式1
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;															//浮空输入
    GPIO_Init(GPIO1, &GPIO_InitStructure);																				//GPIO1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;																			//GPIO1_2
    GPIO_Init(GPIO1, &GPIO_InitStructure);																				//GPIO1

    USART_DeInit(USART0);																													//将USART0寄存器重置为默认值
    USART_StructInit(&USART_InitStructure);																				//将USART_InitStructure结构体变量成员按默认值填充
    USART_Init(USART0, &USART_InitStructure);																			//根据结构体的参数配置来对USART0外设进行初始化
    USART_Cmd(USART0, ENABLE);																										//使能USART0外设
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

