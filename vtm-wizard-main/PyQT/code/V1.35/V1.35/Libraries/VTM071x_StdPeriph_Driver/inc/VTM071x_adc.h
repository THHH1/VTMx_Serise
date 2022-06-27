/**
  ******************************************************************************
  * @file    VTM071x_adc.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the ADC firmware 
  *          library
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VTM071x_ADC_H
#define __VTM071x_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  ADC Init structure definition
  */
typedef struct
{
	uint32_t ADC_Resolution;                  /*!< Selects the resolution of the conversion.
	                                             This parameter can be a value of @ref ADC_Resolution */

	uint32_t ADC_Discard0;                    /*!< Specifies the discarded number when first converting.
	                                             This parameter can be a value of @ref ADC_Discard0 */

	uint32_t ADC_Discard1;                    /*!< Specifies the discarded number when switching channel.
	                                             This parameter can be a value of @ref ADC_Discard1 */

	uint32_t ADC_CLKMode;                     /*!< Specifies ADC clock mode.
	                                             This parameter can be a value of @ref ADC_Clock_Mode */

	uint32_t  ADC_ScanDirection;              /*!< Specifies in which direction the channels will be scanned
	                                             in the sequence. 
	                                             This parameter can be a value of @ref ADC_Scan_Direction */

	uint32_t ADC_DataAlign;                   /*!< Specifies whether the ADC data alignment is left or right.
	                                             This parameter can be a value of @ref ADC_data_align */

	FunctionalState ADC_ContinuousConvMode;   /*!< Specifies whether the conversion is performed in
	                                             Continuous or Single mode.
	                                             This parameter can be set to ENABLE or DISABLE. */

	uint32_t ADC_ExternalTrigConvEdge;        /*!< Selects the external trigger Edge and enables the
	                                             trigger of a regular group. This parameter can be a value
	                                             of @ref ADC_external_trigger_edge_conversion */

	uint32_t ADC_ExternalTrigConv;            /*!< Defines the external trigger used to start the analog
	                                             to digital conversion of regular channels. This parameter
	                                             can be a value of @ref ADC_external_trigger_sources_for_channels_conversion */
}ADC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */ 

/** @defgroup ADC_Resolution
  * @{
  */ 
#define ADC_Resolution_12b                         ((uint32_t)0x00000000)
#define ADC_Resolution_10b                         ((uint32_t)0x00000008)
#define ADC_Resolution_8b                          ((uint32_t)0x00000010)
#define ADC_Resolution_6b                          ((uint32_t)0x00000018)

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_Resolution_12b) 	|| \
                                       ((RESOLUTION) == ADC_Resolution_10b)	|| \
                                       ((RESOLUTION) == ADC_Resolution_8b)	|| \
                                       ((RESOLUTION) == ADC_Resolution_6b))
/**
  * @}
  */ 

/** @defgroup ADC_Resolution
  * @{
  */ 
#define ADC_Resolution_12b                         ((uint32_t)0x00000000)
#define ADC_Resolution_10b                         ((uint32_t)0x00000008)
#define ADC_Resolution_8b                          ((uint32_t)0x00000010)
#define ADC_Resolution_6b                          ((uint32_t)0x00000018)

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_Resolution_12b) 	|| \
                                       ((RESOLUTION) == ADC_Resolution_10b)	|| \
                                       ((RESOLUTION) == ADC_Resolution_8b)	|| \
                                       ((RESOLUTION) == ADC_Resolution_6b))
/**
  * @}
  */ 

/** @defgroup ADC_Discard0
  * @{
  */ 
#define	ADC_Discard0_0								((uint32_t)0x00000000)
#define	ADC_Discard0_1								((uint32_t)0x00000001)
#define	ADC_Discard0_2								((uint32_t)0x00000002)
#define	ADC_Discard0_3								((uint32_t)0x00000003)
#define IS_ADC_DISCARD0(DISCARD0) 	  (((DISCARD0) == ADC_Discard0_0) 	|| \
                                       ((DISCARD0) == ADC_Discard0_1)	|| \
                                       ((DISCARD0) == ADC_Discard0_2)	|| \
                                       ((DISCARD0) == ADC_Discard0_3))
/**
  * @}
  */ 

/** @defgroup ADC_Discard1
  * @{
  */ 
#define	ADC_Discard1_0								((uint32_t)0x00000000)
#define	ADC_Discard1_1								((uint32_t)0x00000010)
#define	ADC_Discard1_2								((uint32_t)0x00000020)
#define	ADC_Discard1_3								((uint32_t)0x00000030)
#define IS_ADC_DISCARD1(DISCARD1) 	  (((DISCARD1) == ADC_Discard1_0) 	|| \
                                       ((DISCARD1) == ADC_Discard1_1)	|| \
                                       ((DISCARD1) == ADC_Discard1_2)	|| \
                                       ((DISCARD1) == ADC_Discard1_3))
/**
  * @}
  */ 

/** @defgroup ADC_Clock_Mode
  * @{
  */
#define	ADC_ClockMode_ADCClk								((uint32_t)0x00000000)
#define	ADC_ClockMode_SynClkDiv2							((uint32_t)0x40000000)
#define	ADC_ClockMode_SynClkDiv4							((uint32_t)0x80000000)
#define IS_ADC_CLOCKMODE(MODE) 	      (((MODE) == ADC_ClockMode_ADCClk) 		|| \
                                       ((MODE) == ADC_ClockMode_SynClkDiv2)	|| \
                                       ((MODE) == ADC_ClockMode_SynClkDiv4))
/**
  * @}
  */

/** @defgroup ADC_Scan_Direction 
  * @{
  */ 
  
#define ADC_ScanDirection_Upward                   ((uint32_t)0x00000000)
#define ADC_ScanDirection_Backward                 ((uint32_t)0x00000004)

#define IS_ADC_SCAN_DIRECTION(DIRECTION) (((DIRECTION) == ADC_ScanDirection_Upward) || \
                                          ((DIRECTION) == ADC_ScanDirection_Backward))
/**
  * @}
  */ 

/** @defgroup ADC_data_align 
  * @{
  */ 
#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                         ADC_CFGR1_ALIGN

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))
/**
  * @}
  */ 

/** @defgroup ADC_external_trigger_edge_conversion 
  * @{
  */ 
#define ADC_ExternalTrigConvEdge_None              ((uint32_t)0x00000000)
#define ADC_ExternalTrigConvEdge_Rising            ((uint32_t)0x00000400)
#define ADC_ExternalTrigConvEdge_Falling           ((uint32_t)0x00000800)
#define ADC_ExternalTrigConvEdge_RisingFalling     ((uint32_t)0x00000C00)

#define IS_ADC_EXT_TRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigConvEdge_None) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Rising) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Falling) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_RisingFalling))
/**
  * @}
  */ 

/** @defgroup ADC_Vref
  * @{
  */ 
#define ADC_VREF_VDDB               ((uint32_t)0x00000000)
#define ADC_VREF_INTERNAL_2P048     ((uint32_t)0x00200000)
#define ADC_VREF_VREFH              ((uint32_t)0x00400000)

#define IS_ADC_VREF_SEL(SEL)       (((SEL) == ADC_VREF_VDDB) || \
                                    ((SEL) == ADC_VREF_INTERNAL_2P048) || \
                                    ((SEL) == ADC_VREF_VREFH))
/**
  * @}
  */ 

/** @defgroup ADC_external_trigger_sources_for_channels_conversion
  * @{
  */ 
#define	ADC_ExternalTrigConv_MCOA0					((uint32_t)0x00000000)
#define	ADC_ExternalTrigConv_MCOA1					((uint32_t)0x00000040)
#define	ADC_ExternalTrigConv_MCOA2					((uint32_t)0x00000080)
#define	ADC_ExternalTrigConv_MCOB0					((uint32_t)0x000000C0)
#define	ADC_ExternalTrigConv_MCOB1					((uint32_t)0x00000100)
#define	ADC_ExternalTrigConv_MCOB2					((uint32_t)0x00000140)
#define	ADC_ExternalTrigConv_T0_MAT0				((uint32_t)0x00000180)
#define	ADC_ExternalTrigConv_T0_MAT1				((uint32_t)0x000001C0)
#define	ADC_ExternalTrigConv_T0_MAT2				((uint32_t)0x00000200)
#define	ADC_ExternalTrigConv_T0_MAT3				((uint32_t)0x00000240)
#define	ADC_ExternalTrigConv_T1_MAT0				((uint32_t)0x00000280)
#define	ADC_ExternalTrigConv_T1_MAT1				((uint32_t)0x000002C0)
#define	ADC_ExternalTrigConv_T1_MAT2				((uint32_t)0x00000300)
#define	ADC_ExternalTrigConv_T1_MAT3				((uint32_t)0x00000340)
#define	ADC_ExternalTrigConv_MCPWM_IRQ				((uint32_t)0x00000380)
#define	ADC_ExternalTrigConv_T0_IRQ					((uint32_t)0x000003C0)
#define	ADC_ExternalTrigConv_T2_MAT0                ((uint32_t)0x01000000)
#define	ADC_ExternalTrigConv_T2_MAT1                ((uint32_t)0x01000040)
#define	ADC_ExternalTrigConv_T2_MAT2                ((uint32_t)0x01000080)
#define	ADC_ExternalTrigConv_T2_MAT3                ((uint32_t)0x010000C0)


#define	ADC_ExternalTrigConv_GPIO0_7				((uint32_t)0x80000000)
#define	ADC_ExternalTrigConv_GPIO1_7				((uint32_t)0x80000040)
#define	ADC_ExternalTrigConv_GPIO2_7				((uint32_t)0x80000080)
#define	ADC_ExternalTrigConv_GPIO3_7				((uint32_t)0x800000C0)
#define	ADC_ExternalTrigConv_GPIO4_7				((uint32_t)0x80000100)
#define	ADC_ExternalTrigConv_CMP_CO0				((uint32_t)0x80000140)
#define	ADC_ExternalTrigConv_CMP_CO1				((uint32_t)0x80000180)
#define	ADC_ExternalTrigConv_CMP_CO2				((uint32_t)0x800001C0)
#define	ADC_ExternalTrigConv_WDT_IRQ				((uint32_t)0x80000200)
#define	ADC_ExternalTrigConv_T1_IRQ					((uint32_t)0x80000240)
#define	ADC_ExternalTrigConv_CMP_IRQ				((uint32_t)0x80000280)
#define	ADC_ExternalTrigConv_ADC_IRQ				((uint32_t)0x800002C0)
#define	ADC_ExternalTrigConv_GPIO0_0				((uint32_t)0x80000300)
#define	ADC_ExternalTrigConv_GPIO1_0				((uint32_t)0x80000340)
#define	ADC_ExternalTrigConv_GPIO2_0				((uint32_t)0x80000380)
#define	ADC_ExternalTrigConv_GPIO3_0				((uint32_t)0x800003C0)
#define	ADC_ExternalTrigConv_T3_MAT0                ((uint32_t)0x81000000)
#define	ADC_ExternalTrigConv_T3_MAT1                ((uint32_t)0x81000040)
#define	ADC_ExternalTrigConv_T3_MAT2                ((uint32_t)0x81000080)
#define	ADC_ExternalTrigConv_T3_MAT3                ((uint32_t)0x810000C0)

#define IS_ADC_EXTERNAL_TRIG_CONV(CONV) (((CONV) == ADC_ExternalTrigConv_MCOA0)     || \
                                         ((CONV) == ADC_ExternalTrigConv_MCOA1)		|| \
                                         ((CONV) == ADC_ExternalTrigConv_MCOA2)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_MCOB0)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_MCOB1)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_MCOB2)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T0_MAT0)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T0_MAT1)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T0_MAT2)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T0_MAT3)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T1_MAT0)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T1_MAT1)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T1_MAT2)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T1_MAT3)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_MCPWM_IRQ) || \
                                         ((CONV) == ADC_ExternalTrigConv_T0_IRQ)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T2_MAT0)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T2_MAT1)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T2_MAT2)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T2_MAT3)   || \
                                         ((CONV) == ADC_ExternalTrigConv_GPIO0_7)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_GPIO1_7)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_GPIO2_7)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_GPIO3_7)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_GPIO4_7)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_CMP_CO0)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_CMP_CO1)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_CMP_CO2)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_WDT_IRQ)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T1_IRQ)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_CMP_IRQ)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_ADC_IRQ)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_GPIO0_0)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_GPIO1_0)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_GPIO2_0)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_GPIO3_0)   || \
                                         ((CONV) == ADC_ExternalTrigConv_T3_MAT0)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T3_MAT1)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T3_MAT2)  	|| \
                                         ((CONV) == ADC_ExternalTrigConv_T3_MAT3)) 
/**
  * @}
  */ 

/** @defgroup ADC_thresholds 
  * @{
  */ 
#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)
/**
  * @}
  */ 
    
/** @defgroup ADC_analog_watchdog_selection 
  * @{
  */ 
#define ADC_AnalogWatchdog_Channel_0                 ((uint32_t)0x00000000)
#define ADC_AnalogWatchdog_Channel_1                 ((uint32_t)0x04000000)
#define ADC_AnalogWatchdog_Channel_2                 ((uint32_t)0x08000000)
#define ADC_AnalogWatchdog_Channel_3                 ((uint32_t)0x0C000000)
#define ADC_AnalogWatchdog_Channel_4                 ((uint32_t)0x10000000)
#define ADC_AnalogWatchdog_Channel_5                 ((uint32_t)0x14000000)
#define ADC_AnalogWatchdog_Channel_6                 ((uint32_t)0x18000000)
#define ADC_AnalogWatchdog_Channel_7                 ((uint32_t)0x1C000000)
#define ADC_AnalogWatchdog_Channel_8                 ((uint32_t)0x20000000)
#define ADC_AnalogWatchdog_Channel_9                 ((uint32_t)0x24000000)
#define ADC_AnalogWatchdog_Channel_10                ((uint32_t)0x28000000)
#define ADC_AnalogWatchdog_Channel_11                ((uint32_t)0x2C000000)
#define ADC_AnalogWatchdog_Channel_12                ((uint32_t)0x30000000)
#define ADC_AnalogWatchdog_Channel_13                ((uint32_t)0x34000000)
#define ADC_AnalogWatchdog_Channel_14                ((uint32_t)0x38000000)
#define ADC_AnalogWatchdog_Channel_15                ((uint32_t)0x3C000000)

#define IS_ADC_ANALOG_WATCHDOG_CHANNEL(CHANNEL) (((CHANNEL) == ADC_AnalogWatchdog_Channel_0)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_1)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_2)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_3)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_4)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_5)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_6)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_7)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_8)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_9)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_10) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_11) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_12) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_13) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_14) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_15))
/**
  * @}
  */ 

/** @defgroup ADC_channels 
  * @{
  */
#define ADC_Channel_0                              ((uint32_t)0x00000001)
#define ADC_Channel_1                              ((uint32_t)0x00000002)
#define ADC_Channel_2                              ((uint32_t)0x00000004)
#define ADC_Channel_3                              ((uint32_t)0x00000008)
#define ADC_Channel_4                              ((uint32_t)0x00000010)
#define ADC_Channel_5                              ((uint32_t)0x00000020)
#define ADC_Channel_6                              ((uint32_t)0x00000040)
#define ADC_Channel_7                              ((uint32_t)0x00000080)
#define ADC_Channel_8                              ((uint32_t)0x00000100)
#define ADC_Channel_9                              ((uint32_t)0x00000200)
#define ADC_Channel_10                             ((uint32_t)0x00000400) 
#define ADC_Channel_11                             ((uint32_t)0x00000800) 
#define ADC_Channel_12                             ((uint32_t)0x00001000) 
#define ADC_Channel_13                             ((uint32_t)0x00002000) 
#define ADC_Channel_14                             ((uint32_t)0x00004000)
#define ADC_Channel_15                             ((uint32_t)0x00008000)

#define ADC_Channel_TempSensor                     ((uint32_t)ADC_Channel_15)

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) != (uint32_t)RESET) && (((CHANNEL) & 0xFFFF0000) == (uint32_t)RESET))
/**
  * @}
  */ 
  
/** @defgroup ADC_interrupts_definition 
  * @{
  */ 
#define ADC_IT_EOC                                 ADC_IER_EOCIE
#define ADC_IT_EOSEQ                               ADC_IER_EOSEQIE
#define ADC_IT_OVR                                 ADC_IER_OVRIE
#define ADC_IT_AWD                                 ADC_IER_AWDIE
 
#define IS_ADC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFF63) == (uint32_t)RESET))

#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_EOC)   || ((IT) == ADC_IT_EOSEQ) || \
                           ((IT) == ADC_IT_OVR)   || ((IT) == ADC_IT_AWD))

#define IS_ADC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFF63) == (uint32_t)RESET))
/**
  * @}
  */ 

/** @defgroup ADC_flags_definition 
  * @{
  */ 
#define ADC_FLAG_EOC                               ADC_ISR_EOC
#define ADC_FLAG_EOSEQ                             ADC_ISR_EOSEQ
#define ADC_FLAG_OVR                               ADC_ISR_OVR
#define ADC_FLAG_AWD                               ADC_ISR_AWD

#define ADC_FLAG_ADSTART                           ((uint32_t)0x01000004)

#define IS_ADC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFFFF63) == (uint32_t)RESET))

#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_EOC)     || ((FLAG) == ADC_FLAG_EOSEQ) || \
                               ((FLAG) == ADC_FLAG_AWD)     || ((FLAG) == ADC_FLAG_OVR)   || \
                               ((FLAG) == ADC_FLAG_ADSTART))
/**
  * @}
  */
  
/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/*  Function used to set the ADC configuration to the default reset state *****/
void ADC_DeInit(void);

/* Initialization and Configuration functions *********************************/ 
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_StartOfConversion(void);
void ADC_StopOfConversion(void);
void ADC_ClockModeConfig(uint32_t ADC_ClockMode);

/* Power saving functions *****************************************************/
void ADC_WaitModeCmd(FunctionalState NewState);

/* Analog Watchdog configuration functions ************************************/
void ADC_AnalogWatchdogCmd(FunctionalState NewState);
void ADC_AnalogWatchdogThresholdsConfig(uint16_t HighThreshold,uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(uint32_t ADC_AnalogWatchdog_Channel);
void ADC_AnalogWatchdogSingleChannelCmd(FunctionalState NewState);

/* Temperature Sensor , Vrefint and Vbat management function ******************/
void ADC_TempSensorCmd(FunctionalState NewState);
void ADC_VrefConfig(uint32_t ADC_Vref);
void ADC_InternalVrefCmd(FunctionalState NewState);

/* Channels Configuration functions *******************************************/
void ADC_ChannelConfig(uint32_t ADC_Channel);
void ADC_ContinuousModeCmd(FunctionalState NewState);
void ADC_DiscModeCmd(FunctionalState NewState);
void ADC_OverrunModeCmd(FunctionalState NewState);
uint16_t ADC_GetConversionValue(uint32_t ADC_Channel);

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(uint32_t ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(uint32_t ADC_FLAG);
void ADC_ClearFlag(uint32_t ADC_FLAG);
ITStatus ADC_GetITStatus(uint32_t ADC_IT);
void ADC_ClearITPendingBit(uint32_t ADC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__VTM071x_ADC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
