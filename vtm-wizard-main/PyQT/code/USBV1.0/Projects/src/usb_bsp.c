#include "usb_bsp.h"
{{usb_bsp_c_include}}

{{usb_bsp_c_define}}

void delay(uint32_t n)
{
    int i;
    
    for (i=0; i<n; i++)
        __nop();
}


void USB_BSP_Init(USB_CORE_HANDLE *pdev)
{
    {{usb_bsp_c_USB_BSP_Init}}
    /* power on usb_pll */
    RCC->PDRUNCFG = RCC->PDRUNCFG & (~(1<<10));
    
    /* open usb_pll clk */
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USB, ENABLE);
    
    /* Reset usb */
    RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_USB, ENABLE);
#if 1
    delay(300000); //delay 10ms, plug detect
#else
    #warning "Delay 10ms, plug detect"
#endif
    
    RCC_APBPeriphResetCmd(RCC_AHBCLKCTRL_USB, DISABLE);
}

{{USB_BSP_DevConnect}}


void USB_BSP_EnableInterrupt(USB_CORE_HANDLE *pdev)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the USB interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USB_IRQn;
    {{usb_bsp_c_USB_BSP_EnableInterrupt}}
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
