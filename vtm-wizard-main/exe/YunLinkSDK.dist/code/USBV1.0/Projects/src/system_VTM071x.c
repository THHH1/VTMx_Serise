
#include "VTM071x.h"

#if 1
#define	SYSCLK_FREQ_IRC			12000000
#define	SYSCLK_SOURCE_FREQ		SYSCLK_FREQ_IRC
#else
#define	SYSCLK_FREQ_OSC			12000000
#define	SYSCLK_SOURCE_FREQ		SYSCLK_FREQ_OSC
#endif

#define SYSCLK_FREQ_SYSPLL_84MHz        84000000

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
{{SYSCLK_FREQ_SYSPLL_96MHz}}
#else /*!< IRC Selected as System Clock source */
    uint32_t SystemCoreClock         = SYSCLK_FREQ_IRC;           /*!< System Clock Frequency (Core Clock) */
#endif


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
{{IF_SYSCLK_FREQ_SYSPLL_96MHz}}
#endif


void SystemInit (void)
{    
    /*Init BOR control*/
    RCC->BORCTRL = 0x8005;
    {{system_VTM071x_c_SystemInit}}
    SetSysClock();
}

{{system_VTM071x_c_delay}}

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
{{SET_IF_SYSCLK_FREQ_SYSPLL_96MHz}}
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
    {{system_VTM071x_c_SetSysClockToSYS}}
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

    {{system_VTM071x_c_SetSysClockTo48_1}}

    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | RCC_REF_SEL | (0 << 0);
    
    /* Use external OSC */
    RCC->USBCTRL |= 0x40000000;
#endif

    while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTAT_LOCK)
    {
        if((timeout++) >= 0x8000)
            break;
    }

    {{system_VTM071x_c_SetSysClockTo48_2}}

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

    {{system_VTM071x_c_SetSysClockTo60_1}}

    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | RCC_REF_SEL | (1 << 0);
    
    /* Use external OSC */
    RCC->USBCTRL |= 0x40000000;
#endif

    while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTAT_LOCK)
    {
        if((timeout++) >= 0x8000)
            break;
    }

    {{system_VTM071x_c_SetSysClockTo60_2}}

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

    {{system_VTM071x_c_SetSysClockTo72_1}}

    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | RCC_REF_SEL | (2 << 0);
    
    /* Use external OSC */
    RCC->USBCTRL |= 0x40000000;
#endif

    while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTAT_LOCK)
    {
        if((timeout++) >= 0x8000)
            break;
    }

    {{system_VTM071x_c_SetSysClockTo72_2}}

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

    {{system_VTM071x_c_SetSysClockTo84_1}}
    
    RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | RCC_REF_SEL | (3 << 0);
    
    /* Use external OSC */
    RCC->USBCTRL |= 0x40000000;
#endif

    while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTAT_LOCK)
    {
        if((timeout++) >= 0x8000)
            break;
    }

    {{system_VTM071x_c_SetSysClockTo84_2}}

    /*switch main clk source to syspll_out*/
    RCC->MAINCLKSEL = 1;
    /*make switch available*/
    RCC->MAINCLKUEN = 0;
    RCC->MAINCLKUEN = 1;
}
{{ELIF_IFDEFINED_SYSCLK_FREQ_SYSPLL_96MHz}}
#endif


{{system_VTM071x_c_SystemCoreClockUpdate}}

