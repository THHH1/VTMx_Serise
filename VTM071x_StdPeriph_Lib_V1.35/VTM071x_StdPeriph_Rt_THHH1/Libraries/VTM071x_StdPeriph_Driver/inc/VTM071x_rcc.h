/**
  ******************************************************************************
  * @file    VTM071x_rcc.h
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the RCC firmware 
  *          library.
  ******************************************************************************
  * @copy
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VTM071x_RCC_H
#define __VTM071x_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup AHB_peripheral 
  * @{
  */
#define IS_RCC_AHB_PERIPH(PERIPH)          (((PERIPH) == RCC_AHBCLKCTRL_FLASH)  || \
                                            ((PERIPH) == RCC_AHBCLKCTRL_GPIO)   || \
                                            ((PERIPH) == RCC_AHBCLKCTRL_DMA))

#define IS_RCC_AHB_RST_PERIPH(PERIPH)      (((PERIPH) == RCC_AHBCLKCTRL_FLASH)  || \
                                            ((PERIPH) == RCC_AHBCLKCTRL_GPIO)   || \
                                            ((PERIPH) == RCC_AHBCLKCTRL_DMA))
/**
  * @}
  */ 

/** @defgroup APB_peripheral 
  * @{
  */
#define IS_RCC_APB_PERIPH(PERIPH)           ((((PERIPH) & 0x3CB20848) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup Boot_mode 
  * @{
  */
#define RCC_BOOT_MODE_IO                    ((uint32_t)0x00000001)
#define BOOT_MODE_FLASH                     ((uint32_t)0x00000002)
#define RCC_BOOT_MODE_REG                   ((uint32_t)0x00000010)
/**
  * @}
  */

/** @defgroup Protect_level 
  * @{
  */
#define RCC_PROTECT_LEVEL0                  ((uint32_t)0x00000004)
#define RCC_PROTECT_LEVEL1                  ((uint32_t)0x00000008)

#define IS_RCC_PROTECT_LEVEL(LEVEL)        (((LEVEL) == RCC_PROTECT_LEVEL0) || \
                                            ((LEVEL) == RCC_PROTECT_LEVEL1))
/**
  * @}
  */

/** @defgroup Reset_source 
  * @{
  */
#define RCC_RESET_SOURCE_POR                ((uint32_t)0x00000001)
#define RCC_RESET_SOURCE_EXT                ((uint32_t)0x00000002)
#define RCC_RESET_SOURCE_WDT                ((uint32_t)0x00000004)
#define RCC_RESET_SOURCE_BOR                ((uint32_t)0x00000008)
#define RCC_RESET_SOURCE_SYS                ((uint32_t)0x00000010)
#define RCC_RESET_SOURCE_IWDG               ((uint32_t)0x00000020)

#define IS_RCC_RESET_SOURCE(SOURCE)        (((SOURCE) == RCC_RESET_SOURCE_POR)  || \
                                            ((SOURCE) == RCC_RESET_SOURCE_EXT)  || \
                                            ((SOURCE) == RCC_RESET_SOURCE_WDT)  || \
                                            ((SOURCE) == RCC_RESET_SOURCE_BOR)  || \
                                            ((SOURCE) == RCC_RESET_SOURCE_SYS)  || \
                                            ((SOURCE) == RCC_RESET_SOURCE_IWDG))
/**
  * @}
  */

/** @defgroup MAINCLK_SOURCE 
  * @{
  */
#define RCC_MAINCLK_SOURCE_12M_IRC          ((uint32_t)0x00000000)
#define RCC_MAINCLK_SOURCE_SYSPLL           ((uint32_t)0x00000001)
#define RCC_MAINCLK_SOURCE_12M_OSC          ((uint32_t)0x00000002)
#define RCC_MAINCLK_SOURCE_10K_IRC          ((uint32_t)0x00000003)

#define IS_RCC_MAINCLK_SOURCE(SOURCE)      (((SOURCE) == RCC_MAINCLK_SOURCE_12M_IRC)  || \
                                            ((SOURCE) == RCC_MAINCLK_SOURCE_SYSPLL)   || \
                                            ((SOURCE) == RCC_MAINCLK_SOURCE_12M_OSC)  || \
                                            ((SOURCE) == RCC_MAINCLK_SOURCE_10K_IRC))
/**
  * @}
  */

/** @defgroup USARTCLK_SOURCE 
  * @{
  */
#define RCC_USARTCLK_SOURCE_12M_IRC         ((uint32_t)0x00000000)
#define RCC_USARTCLK_SOURCE_SYSPLL          ((uint32_t)0x00000001)
#define RCC_USARTCLK_SOURCE_12M_OSC         ((uint32_t)0x00000002)
#define RCC_USARTCLK_SOURCE_10K_OSC         ((uint32_t)0x00000003)

#define IS_RCC_USARTCLK_SOURCE(SOURCE)     (((SOURCE) == RCC_USARTCLK_SOURCE_12M_IRC) || \
                                            ((SOURCE) == RCC_USARTCLK_SOURCE_SYSPLL)  || \
                                            ((SOURCE) == RCC_USARTCLK_SOURCE_12M_OSC) || \
                                            ((SOURCE) == RCC_USARTCLK_SOURCE_10K_OSC))
/**
  * @}
  */

/** @defgroup USBCLK_SOURCE 
  * @{
  */
#define RCC_USBCLK_SOURCE_IRC               ((uint32_t)0x00000000)
#define RCC_USBCLK_SOURCE_OSC               ((uint32_t)0x00000001)

#define IS_RCC_USBCLK_SOURCE(SOURCE)	   (((SOURCE) == RCC_USBCLK_SOURCE_IRC) || \
                                            ((SOURCE) == RCC_USBCLK_SOURCE_OSC))
/**
  * @}
  */

/** @defgroup OUTCLK_SOURCE 
  * @{
  */
#define RCC_OUTCLK_SOURCE_12M_IRC           ((uint32_t)0x00000000)
#define RCC_OUTCLK_SOURCE_SYSPLL            ((uint32_t)0x00000001)
#define RCC_OUTCLK_SOURCE_10K_IRC           ((uint32_t)0x00000002)
#define RCC_OUTCLK_SOURCE_12M_OSC           ((uint32_t)0x00000003)
#define RCC_OUTCLK_SOURCE_32768_OSC         ((uint32_t)0x00000004)
#define RCC_OUTCLK_SOURCE_USBPLL            ((uint32_t)0x00000008)

#define IS_RCC_OUTCLK_SOURCE(SOURCE)       (((SOURCE) == RCC_OUTCLK_SOURCE_12M_IRC)   || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_SYSPLL)    || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_10K_IRC)   || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_12M_OSC)   || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_32768_OSC) || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_USBPLL))
/**
  * @}
  */

/** @defgroup WWDGCLK_SOURCE 
  * @{
  */
#define RCC_WWDGCLK_SOURCE_12M_IRC          ((uint32_t)0x00000000)
#define RCC_WWDGCLK_SOURCE_SYSPLL           ((uint32_t)0x00000001)
#define RCC_WWDGCLK_SOURCE_12M_OSC          ((uint32_t)0x00000002)
#define RCC_WWDGCLK_SOURCE_10K_IRC          ((uint32_t)0x00000003)

#define IS_RCC_WWDGCLK_SOURCE(SOURCE)      (((SOURCE) == RCC_WWDGCLK_SOURCE_12M_IRC)    || \
                                            ((SOURCE) == RCC_WWDGCLK_SOURCE_SYSPLL)     || \
                                            ((SOURCE) == RCC_WWDGCLK_SOURCE_12M_OSC)    || \
                                            ((SOURCE) == RCC_WWDGCLK_SOURCE_10K_IRC))
/**
  * @}
  */

/** @defgroup Peripheral_CLK 
  * @{
  */
#define RCC_CLOCKFREQ_SYSAHBCLK             ((uint32_t)0x00000080)
#define RCC_CLOCKFREQ_USART0CLK             ((uint32_t)0x00000090)
#define RCC_CLOCKFREQ_USART1CLK             ((uint32_t)0x00000094)
#define RCC_CLOCKFREQ_SYSTICKCLK            ((uint32_t)0x000000A0)
#define RCC_CLOCKFREQ_SPI0CLK               ((uint32_t)0x000000A4)
#define RCC_CLOCKFREQ_WWDGCLK               ((uint32_t)0x000000A8)
#define RCC_CLOCKFREQ_CLKOUTCLK             ((uint32_t)0x000000AC)
#define RCC_CLOCKFREQ_ADCCLK                ((uint32_t)0x000000B0)
#define RCC_CLOCKFREQ_SPI1CLK               ((uint32_t)0x000000D0)
#define RCC_CLOCKFREQ_DACCLK                ((uint32_t)0x000000D8)

#define RCC_CLOCKFREQ_IWDG                  ((uint32_t)0x10000001)
#define RCC_CLOCKFREQ_TIMER                 ((uint32_t)0x10000002)
#define RCC_CLOCKFREQ_TSC                   ((uint32_t)0x10000004)
#define RCC_CLOCKFREQ_FLASH                 ((uint32_t)0x10000008)

#define IS_RCC_CLKDIV_PER(CLK)             (((CLK) == RCC_CLOCKFREQ_SYSAHBCLK)  || \
                                            ((CLK) == RCC_CLOCKFREQ_USART0CLK)  || \
                                            ((CLK) == RCC_CLOCKFREQ_USART1CLK)  || \
                                            ((CLK) == RCC_CLOCKFREQ_SYSTICKCLK) || \
                                            ((CLK) == RCC_CLOCKFREQ_SPI0CLK)    || \
                                            ((CLK) == RCC_CLOCKFREQ_WWDGCLK)    || \
                                            ((CLK) == RCC_CLOCKFREQ_CLKOUTCLK)  || \
                                            ((CLK) == RCC_CLOCKFREQ_ADCCLK)     || \
                                            ((CLK) == RCC_CLOCKFREQ_SPI1CLK)    || \
                                            ((CLK) == RCC_CLOCKFREQ_DACCLK))
/**
  * @}
  */

/** @defgroup RCC_Wakeup_Enable
  * @{
  */
#define RCC_WAKEUP_GPIO1_0                  ((uint32_t)0x00000001)
#define RCC_WAKEUP_GPIO1_1                  ((uint32_t)0x00000002)
#define RCC_WAKEUP_GPIO1_2                  ((uint32_t)0x00000004)
#define RCC_WAKEUP_GPIO1_3                  ((uint32_t)0x00000008)
#define RCC_WAKEUP_GPIO1_4                  ((uint32_t)0x00000010)
#define RCC_WAKEUP_GPIO0_0                  ((uint32_t)0x00000020)
#define RCC_WAKEUP_GPIO5_5                  ((uint32_t)0x00000040)

#define IS_RCC_WAKEUP_PIN(PIN)             (((PIN) != 0) && (((PIN) & 0xFFFFFF80) == 0))
/**
  * @}
  */

/** @defgroup RCC_SYSTICK_CALIBRATION_VALUE
  * @{
  */
#define IS_RCC_SYSTICK_CALIBRATION_VALUE(VALUE) \
                                            (((VALUE) & 0xFC000000) == 0) 
/**
  * @}
  */

/** @defgroup BORRST_VAL 
  * @{
  */
#define RCC_BORRST_VAL_1_8                  ((uint32_t)0x00000000)
#define RCC_BORRST_VAL_2_2                  ((uint32_t)0x00000001)
#define RCC_BORRST_VAL_2_7                  ((uint32_t)0x00000002)
#define RCC_BORRST_VAL_3_7                  ((uint32_t)0x00000003)

#define IS_RCC_BORRST_VAL(VAL)             (((VAL) == RCC_BORRST_VAL_3_7) || \
                                            ((VAL) == RCC_BORRST_VAL_2_7) || \
                                            ((VAL) == RCC_BORRST_VAL_2_2) || \
                                            ((VAL) == RCC_BORRST_VAL_1_8))	
/**
  * @}
  */

/** @defgroup BOD_VAL 
  * @{
  */
#define RCC_BOD_VAL_4_4                     ((uint32_t)0x00000000)
#define RCC_BOD_VAL_3_7                     ((uint32_t)0x00008000)
#define RCC_BOD_VAL_2_7                     ((uint32_t)0x00010000)
#define RCC_BOD_VAL_2_2                     ((uint32_t)0x00018000)

#define IS_RCC_BOD_VAL(VAL)                (((VAL) == RCC_BOD_VAL_4_4) || \
                                            ((VAL) == RCC_BOD_VAL_3_7) || \
                                            ((VAL) == RCC_BOD_VAL_2_7) || \
                                            ((VAL) == RCC_BOD_VAL_2_2))	
/**
  * @}
  */

/** @defgroup PDCFG_MOD 
  * @{
  */
#define RCC_PDCFG_OSC12M                    ((uint32_t)0x00000001)
#define RCC_PDCFG_ADC                       ((uint32_t)0x00000004)
#define RCC_PDCFG_SYSPLL                    ((uint32_t)0x00000008)
#define RCC_PDCFG_BOD                       ((uint32_t)0x00000010)
#define RCC_PDCFG_BOR                       ((uint32_t)0x00000020)
#define RCC_PDCFG_IRC12M                    ((uint32_t)0x00000080)
#define RCC_PDCFG_FLASH                     ((uint32_t)0x00000100)
#define RCC_PDCFG_ACMP                      ((uint32_t)0x00000200)
#define RCC_PDCFG_USB                       ((uint32_t)0x00000400)
#define RCC_PDCFG_32768_OSC                 ((uint32_t)0x00000800)
#define RCC_PDCFG_DAC0                      ((uint32_t)0x00001000)
#define RCC_PDCFG_DAC1                      ((uint32_t)0x00002000)
#define RCC_PDCFG_USB_LDO                   ((uint32_t)0x00004000)

#define IS_RCC_PDCFG_ANALOG_BLOCK(MODULE)  (((MODULE) != 0) && (((MODULE) & 0xFFFF8042) == 0))
/**
  * @}
  */

/** @defgroup PDCFG_MODE 
  * @{
  */
#define RCC_PDCFG_POWER_ON                  ((uint32_t)0x00000000)
#define RCC_PDCFG_POWER_DOWN				        ((uint32_t)0x00000001)
#define IS_RCC_PDCFG_MODE(MODE)            (((MODE) == RCC_PDCFG_POWER_ON) || ((MODE) == RCC_PDCFG_POWER_DOWN))
/**
  * @}
  */

/** @defgroup DMACHANNEL_CONFIG 
  * @{
  */
#define RCC_DMACHANNEL0_USART0_TX           ((uint32_t)0x00000001)
#define RCC_DMACHANNEL1_USART0_RX           ((uint32_t)0x00000002)
#define RCC_DMACHANNEL2_USART1_TX           ((uint32_t)0x00000004)
#define RCC_DMACHANNEL3_USART1_RX           ((uint32_t)0x00000008)
#define RCC_DMACHANNEL4_I2C0_TX             ((uint32_t)0x00000010)
#define RCC_DMACHANNEL4_ADC                 ((uint32_t)0x10000010)
#define RCC_DMACHANNEL5_I2C1_RX             ((uint32_t)0x00000020)
#define RCC_DMACHANNEL5_DAC0                ((uint32_t)0x10000020)
#define RCC_DMACHANNEL6_I2C1_TX             ((uint32_t)0x00000040)
#define RCC_DMACHANNEL6_DAC1                ((uint32_t)0x10000040)
#define RCC_DMACHANNEL7_I2C1_RX             ((uint32_t)0x00000080)
#define RCC_DMACHANNEL8_SPI0_TX             ((uint32_t)0x00000100)
#define RCC_DMACHANNEL9_SPI0_RX             ((uint32_t)0x00000200)
#define RCC_DMACHANNEL10_SPI1_TX            ((uint32_t)0x00000400)
#define RCC_DMACHANNEL11_SPI1_RX            ((uint32_t)0x00000800)
#define RCC_DMACHANNEL12_TIMER0             ((uint32_t)0x00001000)
#define RCC_DMACHANNEL13_TIMER1             ((uint32_t)0x00002000)
#define RCC_DMACHANNEL14_TIMER2             ((uint32_t)0x00004000)
#define RCC_DMACHANNEL15_TIMER3             ((uint32_t)0x00008000)
#define RCC_DMACHANNEL_FLAG                 ((uint32_t)0x10000000)

#define IS_RCC_DMACHANNEL_CONFIG(CONFIG)   (((CONFIG) == RCC_DMACHANNEL0_USART0_TX)|| ((CONFIG) == RCC_DMACHANNEL1_USART0_RX)  || \
                                            ((CONFIG) == RCC_DMACHANNEL2_USART1_TX)|| ((CONFIG) == RCC_DMACHANNEL3_USART1_RX)  || \
                                            ((CONFIG) == RCC_DMACHANNEL4_I2C0_TX)  || ((CONFIG) == RCC_DMACHANNEL4_ADC)        || \
                                            ((CONFIG) == RCC_DMACHANNEL5_I2C1_RX)  || ((CONFIG) == RCC_DMACHANNEL5_DAC0)       || \
                                            ((CONFIG) == RCC_DMACHANNEL6_I2C1_TX)  || ((CONFIG) == RCC_DMACHANNEL6_DAC1)       || \
                                            ((CONFIG) == RCC_DMACHANNEL7_I2C1_RX)  || ((CONFIG) == RCC_DMACHANNEL8_SPI0_TX)    || \
                                            ((CONFIG) == RCC_DMACHANNEL9_SPI0_RX)  || ((CONFIG) == RCC_DMACHANNEL10_SPI1_TX)   || \
                                            ((CONFIG) == RCC_DMACHANNEL11_SPI1_RX) || ((CONFIG) == RCC_DMACHANNEL12_TIMER0)    || \
                                            ((CONFIG) == RCC_DMACHANNEL13_TIMER1)  || ((CONFIG) == RCC_DMACHANNEL14_TIMER2)    || \
                                            ((CONFIG) == RCC_DMACHANNEL15_TIMER3))
/**
  * @}
  */

/** @defgroup RCC_FLAG 
  * @{
  */
#define RCC_SLEEPFLAG                       ((uint32_t)0x00000100)
#define RCC_DPFLAG                          ((uint32_t)0x00000800)
#define RCC_LDO_STATUS                      ((uint32_t)0x00100000)

#define IS_RCC_FLAG(FLAG)                  (((FLAG) == RCC_SLEEPFLAG) || \
                                            ((FLAG) == RCC_DPFLAG)    || \
                                            ((FLAG) == RCC_LDO_STATUS))

#define IS_RCC_CLEAR_FLAG(FLAG)             (((FLAG) == RCC_SLEEPFLAG))
/**
  * @}
  */

/** @defgroup RCC_LDO 
  * @{
  */
#define RCC_MAIN_LDO                        ((uint32_t)0x00000000)
#define RCC_LOW_POWER_LDO                   ((uint32_t)0x00010000)
#define IS_RCC_LDO(LDO)                    (((LDO) == RCC_MAIN_LDO) || ((LDO) == RCC_LOW_POWER_LDO))
/**
  * @}
  */

/** @defgroup DEBUG_WDG
  * @{
  */
#define DBGMCU_IWDG_STOP                    ((uint32_t)0x00000010)
#define DBGMCU_WWDG_STOP                    ((uint32_t)0x00000020)
#define IS_DBGMCU_WDG_STOP(WDG)            (((WDG) == DBGMCU_IWDG_STOP) || ((WDG) == DBGMCU_WWDG_STOP))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APBPeriphClockCmd(uint32_t RCC_APBPeriph, FunctionalState NewState);
void RCC_APBPeriphResetCmd(uint32_t RCC_APBPeriph, FunctionalState NewState);
void RCC_BODConfig(uint8_t BODVal);
void RCC_BORConfig(uint8_t BORRSTVal, FunctionalState NewState);
void RCC_MAINCLKSel(uint8_t RCC_MAINCLKSource);
void RCC_USBCLKSel(uint8_t RCC_FLASHCLKSource);
void RCC_OUTCLKSel(uint8_t RCC_OUTCLKSource);
void RCC_USARTCLKSel(uint8_t RCC_USARTCLKSource);
void RCC_WWDGCLKSel(uint8_t RCC_WWDGCLKSource);
void RCC_PDSLEEPConfig(uint16_t RCC_Analog_Switch, uint8_t PD_MODE);
void RCC_PDAWAKEConfig(uint16_t RCC_Analog_Switch, uint8_t PD_MODE);
void RCC_PDRUNConfig(uint16_t RCC_Analog_Switch, uint8_t PD_MODE);
void RCC_DMAChannelConfig(uint32_t DMAChannelForPeripheral);
FlagStatus RCC_GetBootMode(void);
uint32_t RCC_GetClocksFreq(uint32_t RCC_Clocks);
FlagStatus RCC_GetFlagStatus(uint32_t RCC_FLAG);
uint32_t RCC_GetID(void);
FlagStatus RCC_GetANAStatus(void);
FlagStatus RCC_GetProtectStatus(uint32_t RCC_PROTECT);
FlagStatus RCC_GetResetSourceStatus(uint32_t RCC_ResetSource);
void RCC_ClearFlag(uint32_t RCC_FLAG);
void RCC_WakeupPinCmd(uint32_t RCC_Wakeup, FunctionalState NewState);
void RCC_SRAMRemapCmd(FunctionalState NewState);
void RCC_LDROMRemapCmd(FunctionalState NewState);
void RCC_PowerDownCmd(FunctionalState NewState);
void RCC_SETCLKDivider(uint32_t RCC_Peripheral_Clock, uint8_t RCC_CLKDIV);
void RCC_SetSystickCalibrationValue(uint32_t CalibrationValue);
void RCC_SwitchLDO(uint32_t LDO);
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);


#ifdef __cplusplus
}
#endif

#endif /* __VTM071x_RCC_H */

/**
  * @}
  */

/**
  * @}
  */ 

/******************* (C) COPYRIGHT MIC *****END OF FILE****/

