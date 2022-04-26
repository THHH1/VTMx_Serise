/**
  ******************************************************************************
  * @file    system_mt071x.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer System Source File.
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup mt071x_system
  * @{
  */  

/** @addtogroup MT071x_System_Private_Includes
  * @{
  */

#include "mt071x.h"

/**
  * @}
  */

/** @addtogroup MT071x_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup MT071x_System_Private_Defines
  * @{
  */
/* define clock source */
#if 1
#define	SYSCLK_FREQ_IRC			12000000
#define	SYSCLK_SOURCE_FREQ		SYSCLK_FREQ_IRC
#else
#define	SYSCLK_FREQ_OSC			12000000
#define	SYSCLK_SOURCE_FREQ		SYSCLK_FREQ_OSC
#endif

/* define clock freq */
//#define SYSCLK_FREQ_SYS					SYSCLK_SOURCE_FREQ
//#define SYSCLK_FREQ_SYSPLL_48MHz  		48000000
//#define SYSCLK_FREQ_SYSPLL_60MHz  		60000000
//#define SYSCLK_FREQ_SYSPLL_72MHz  		72000000
#define SYSCLK_FREQ_SYSPLL_84MHz  		84000000

/**
  * @}
  */

/** @addtogroup MT071x_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup MT071x_System_Private_Variables
  * @{
  */

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
#ifdef SYSCLK_FREQ_SYS
    uint32_t SystemCoreClock         = SYSCLK_FREQ_SYS;           /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_SYSPLL_48MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_SYSPLL_48MHz;  /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_SYSPLL_60MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_SYSPLL_60MHz;  /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_SYSPLL_72MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_SYSPLL_72MHz;  /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_SYSPLL_84MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_SYSPLL_84MHz;  /*!< System Clock Frequency (Core Clock) */
#else /*!< IRC Selected as System Clock source */
    uint32_t SystemCoreClock         = SYSCLK_FREQ_IRC;           /*!< System Clock Frequency (Core Clock) */
#endif

/**
  * @} 
  */

/** @addtogroup MT071x_System_Private_FunctionPrototypes
  * @{
  */

static void SetSysClock(void);

#ifdef SYSCLK_FREQ_SYS
    static void SetSysClockToSYS(void);
#elif defined SYSCLK_FREQ_SYSPLL_48MHz
    static void SetSysClockTo48(void);
#elif defined SYSCLK_FREQ_SYSPLL_60MHz
    static void SetSysClockTo60(void);
#elif defined SYSCLK_FREQ_SYSPLL_72MHz
    static void SetSysClockTo72(void);
#elif defined SYSCLK_FREQ_SYSPLL_84MHz
    static void SetSysClockTo84(void);
#endif

/**
  * @}
  */

/** @addtogroup MT071x_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{    
    /*Init BOR control*/
    RCC->BORCTRL = 0x8005;
    RCC->OSC12_CTRL = 0x8000007F;
    RCC->IRC10_CTRL = 0x4;
    RCC->LDOCTRL = 0x8000C;

    SetSysClock();	
}

static void delay(unsigned long time)
{
    while(time)
    {
        time--; 
    }
}

/**
  * @brief  Configures the System clock frequency, HCLK prescalers.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_SYS
    SetSysClockToSYS();
#elif defined SYSCLK_FREQ_SYSPLL_48MHz
    SetSysClockTo48();
#elif defined SYSCLK_FREQ_SYSPLL_60MHz
    SetSysClockTo60();
#elif defined SYSCLK_FREQ_SYSPLL_72MHz
    SetSysClockTo72();
#elif defined SYSCLK_FREQ_SYSPLL_84MHz
    SetSysClockTo84();
#endif
}

#ifdef SYSCLK_FREQ_SYS
/**
  * @brief  Selects SYS oscillator as System clock source and configure HCLK prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockToSYS(void)
{
    RCC->AHBCLKCTRL0_SET = RCC_AHB_peripheral_GPIO | RCC_APB_Periph_IOCON;
    FLASH->ACR = FLASH_ACR_LATENCY_0 | FLASH_ACR_CACHENA;
    RCC->SYSAHBCLKDIV = 1;

    /*switch main clk source to syspll_in*/
    RCC->MAINCLKSEL = 0;
    /*make switch available*/
    RCC->MAINCLKUEN = 0;
    RCC->MAINCLKUEN = 1;
}
#elif defined SYSCLK_FREQ_SYSPLL_48MHz
/**
  * @brief  Sets System clock frequency to 48MHz and configure HCLK prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo48(void)
{
    uint32_t	timeout = 0;

    RCC->AHBCLKCTRL0_SET = RCC_AHBCLKCTRL_GPIO | RCC_AHBCLKCTRL_IOCON;
    FLASH->ACR = FLASH_ACR_LATENCY_1 | FLASH_ACR_CACHENA;
    RCC->SYSAHBCLKDIV = 1;

#ifdef	SYSCLK_FREQ_IRC	
    /* open sys_pll clk */
    RCC->PDRUNCFG = RCC->PDRUNCFG & 0xFFFFFF77;

    /*set sys_pll clk to 48MHz (12*(0+4))*/
    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | (0 << 0);
#else
    /* open sys_pll clk */
    RCC->PDRUNCFG = RCC->PDRUNCFG & 0xFFFFFFF6;

    /*set sys_pll clk to 48MHz (12*(0+4))*/
    RCC->OSC12_CTRL = RCC_12OSCCTRL_OSC_EN | (1<<17) | (RCC->OSC12_CTRL & 0xFF); //bit17´ý²âÊÔ
    while(!(RCC->OSC12_CTRL & RCC_12OSCCTRL_OSC_OK))
    {
        if((timeout++) >= 0x8000)
            break;
    }

    RCC->FLASHCLKSEL = RCC_FLASHCLKSEL_SEL_12M_OSC;
    RCC->FLASHCLKUEN = 0;
    RCC->FLASHCLKUEN = 1;

    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | RCC_REF_SEL | (0 << 0);
    
    /* Use external OSC */
    RCC->USBCTRL |= 0x40000000;
#endif

    while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTAT_LOCK)
    {
        if((timeout++) >= 0x8000)
            break;
    }

    delay(1000);

    /*switch main clk source to syspll_out*/
    RCC->MAINCLKSEL = 1;
    /*make switch available*/
    RCC->MAINCLKUEN = 0;
    RCC->MAINCLKUEN = 1;
}
#elif defined SYSCLK_FREQ_SYSPLL_60MHz
/**
  * @brief  Sets System clock frequency to 60MHz and configure HCLK prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo60(void)
{
    uint32_t	timeout = 0;

    RCC->AHBCLKCTRL0_SET = RCC_AHBCLKCTRL_GPIO | RCC_AHBCLKCTRL_IOCON;
    FLASH->ACR = FLASH_ACR_LATENCY_1 | FLASH_ACR_CACHENA;
    RCC->SYSAHBCLKDIV = 1;

#ifdef	SYSCLK_FREQ_IRC
    /* open sys_pll clk */
    RCC->PDRUNCFG = RCC->PDRUNCFG & 0xFFFFFF77;

    /*set sys_pll clk to 60MHz (12*(1+4))*/
    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | (1 << 0);
#else
    /* open sys_pll clk */
    RCC->PDRUNCFG = RCC->PDRUNCFG & 0xFFFFFFF6;

    /*set sys_pll clk to 60MHz (12*(1+4))*/
    RCC->OSC12_CTRL = RCC_12OSCCTRL_OSC_EN | (1<<17) | (RCC->OSC12_CTRL & 0xFF); //bit17´ý²âÊÔ
    while(!(RCC->OSC12_CTRL & RCC_12OSCCTRL_OSC_OK))
    {
        if((timeout++) >= 0x8000)
            break;
    }

    RCC->FLASHCLKSEL = RCC_FLASHCLKSEL_SEL_12M_OSC;
    RCC->FLASHCLKUEN = 0;
    RCC->FLASHCLKUEN = 1;

    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | RCC_REF_SEL | (1 << 0);
    
    /* Use external OSC */
    RCC->USBCTRL |= 0x40000000;
#endif

    while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTAT_LOCK)
    {
        if((timeout++) >= 0x8000)
            break;
    }

    delay(1000);

    /*switch main clk source to syspll_out*/
    RCC->MAINCLKSEL = 1;
    /*make switch available*/
    RCC->MAINCLKUEN = 0;
    RCC->MAINCLKUEN = 1;
}
#elif defined SYSCLK_FREQ_SYSPLL_72MHz
/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK prescalers. 
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo72(void)
{
    uint32_t	timeout = 0;

    RCC->AHBCLKCTRL0_SET = RCC_AHBCLKCTRL_GPIO | RCC_AHBCLKCTRL_IOCON;
    FLASH->ACR = FLASH_ACR_LATENCY_1 | FLASH_ACR_CACHENA;
    RCC->SYSAHBCLKDIV = 1;

#ifdef	SYSCLK_FREQ_IRC	
    /* open sys_pll clk */
    RCC->PDRUNCFG = RCC->PDRUNCFG & 0xFFFFFF77;

    /*set sys_pll clk to 72MHz (12*(2+4))*/
    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | (2 << 0);
#else
    /* open sys_pll clk */
    RCC->PDRUNCFG = RCC->PDRUNCFG & 0xFFFFFFF6;

    /*set sys_pll clk to 72MHz (12*(2+4))*/
    RCC->OSC12_CTRL = RCC_12OSCCTRL_OSC_EN | (1<<17) | (RCC->OSC12_CTRL & 0xFF); //bit17´ý²âÊÔ
    while(!(RCC->OSC12_CTRL & RCC_12OSCCTRL_OSC_OK))
    {
        if((timeout++) >= 0x8000)
            break;
    }

    RCC->FLASHCLKSEL = RCC_FLASHCLKSEL_SEL_12M_OSC;
    RCC->FLASHCLKUEN = 0;
    RCC->FLASHCLKUEN = 1;

    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | RCC_REF_SEL | (2 << 0);
    
    /* Use external OSC */
    RCC->USBCTRL |= 0x40000000;
#endif

    while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTAT_LOCK)
    {
        if((timeout++) >= 0x8000)
            break;
    }

    delay(1000);

    /*switch main clk source to syspll_out*/
    RCC->MAINCLKSEL = 1;
    /*make switch available*/
    RCC->MAINCLKUEN = 0;
    RCC->MAINCLKUEN = 1;
}
#elif defined SYSCLK_FREQ_SYSPLL_84MHz
/**
  * @brief  Sets System clock frequency to 84MHz and configure HCLK prescalers. 
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo84(void)
{
    uint32_t	timeout = 0;

    RCC->AHBCLKCTRL0_SET = RCC_AHBCLKCTRL_GPIO | RCC_AHBCLKCTRL_IOCON;
    FLASH->ACR = FLASH_ACR_LATENCY_2 | FLASH_ACR_CACHENA;
    RCC->SYSAHBCLKDIV = 1;

#ifdef	SYSCLK_FREQ_IRC	
    /* open sys_pll clk */
    RCC->PDRUNCFG = RCC->PDRUNCFG & 0xFFFFFF77;

    /*set sys_pll clk to 84MHz (12*(3+4))*/
    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | (3 << 0);
#else
    /* open sys_pll clk */
    RCC->PDRUNCFG = RCC->PDRUNCFG & 0xFFFFFFF6;

    /*set sys_pll clk to 84MHz (12*(3+4))*/
    RCC->OSC12_CTRL = RCC_12OSCCTRL_OSC_EN | (1<<17) | (RCC->OSC12_CTRL & 0xFF); //bit17´ý²âÊÔ
    while(!(RCC->OSC12_CTRL & RCC_12OSCCTRL_OSC_OK))
    {
        if((timeout++) >= 0x8000)
            break;
    }

    RCC->FLASHCLKSEL = RCC_FLASHCLKSEL_SEL_12M_OSC;
    RCC->FLASHCLKUEN = 0;
    RCC->FLASHCLKUEN = 1;
    
    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | RCC_REF_SEL | (3 << 0);
    
    /* Use external OSC */
    RCC->USBCTRL |= 0x40000000;
#endif

    while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTAT_LOCK)
    {
        if((timeout++) >= 0x8000)
            break;
    }

    delay(1000);

    /*switch main clk source to syspll_out*/
    RCC->MAINCLKSEL = 1;
    /*make switch available*/
    RCC->MAINCLKUEN = 0;
    RCC->MAINCLKUEN = 1;
}
#endif

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */    
/******************* (C) COPYRIGHT MIC *****END OF FILE****/
