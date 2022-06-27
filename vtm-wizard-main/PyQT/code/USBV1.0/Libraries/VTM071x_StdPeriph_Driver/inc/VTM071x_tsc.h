/**
  ******************************************************************************
  * @file    VTM071x_tsc.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    07/11/2018
  * @brief   This file contains all the functions prototypes for the TSC firmware
  *          library.
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
#ifndef __VTM071x_TSC_H
#define __VTM071x_TSC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup TSC
  * @{
  */ 
/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  TSC Init structure definition
  */
typedef struct
{
    uint32_t TSC_CTPH;              /*!< Specifies the TSC high level.
                                        This parameter can be a value of @ref TSC_CTPH_Cycles */

    uint32_t TSC_CTPL;              /*!< Specifies the TSC low level.
                                        This parameter can be a value of @ref TSC_CTPL_Cycles */

    uint32_t TSC_PrescalerValue;    /*!< Specifies the TSC prescaler value.
                                        This parameter can be a value of @ref TSC_Prescaler_Value */
    
    uint32_t TSC_MaxCountError;     /*!< Specifies the TSC Maximum error count.
                                        This parameter can be a value of @ref TSC_Max_Count_Error */
    
    uint32_t TSC_IODefaultStatus;   /*!< Specifies the TSC IO default status.
                                        This parameter can be a value of @ref TSC_IO_Default_Status */

    uint32_t TSC_SyncPolar;         /*!< Specifies the TSC sync polar.
                                        This parameter can be a value of @ref TSC_Sync_Polar */

    uint32_t TSC_SampleMode;         /*!< Specifies the TSC sample mode.
                                        This parameter can be a value of @ref TSC_Sample_Mode */
}TSC_InitTypeDef;

typedef struct
{
    FunctionalState TSC_IOHysteresis;          /*!< Specifies whether the IO hysteresis(IOHCR) will be enabled or disabled. 
                                                This parameter can be set either to ENABLE or DISABLE */
    
    FunctionalState TSC_IOAnalogSwitch;        /*!< Specifies whether the IO analog switch(IOASCR) will be enabled or disabled. 
                                                This parameter can be set either to ENABLE or DISABLE */

    FunctionalState TSC_IOSampleCapacitance;   /*!< Specifies whether the IO sample capacitance(IOSCR) will be enabled or disabled. 
                                                This parameter can be set either to ENABLE or DISABLE */

    FunctionalState TSC_IOChannelMode;         /*!< Specifies whether the IO channel mode(IOCCR) will be enabled or disabled. 
                                                This parameter can be set either to ENABLE or DISABLE */

    FunctionalState TSC_IOEnable;              /*!< Specifies whether the IO(IOGCSR) will be enabled or disabled. 
                                                This parameter can be set either to ENABLE or DISABLE */
}TSC_IOInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup TSC_Exported_Constants
  * @{
  */ 

/** @defgroup TSC_CTPH_Cycles
  * @{
  */
#define TSC_CTPH_Cycles_0                   ((uint32_t)0x00000000)
#define TSC_CTPH_Cycles_1                   ((uint32_t)0x10000000)
#define TSC_CTPH_Cycles_2                   ((uint32_t)0x20000000)
#define TSC_CTPH_Cycles_3                   ((uint32_t)0x30000000)
#define TSC_CTPH_Cycles_4                   ((uint32_t)0x40000000)
#define TSC_CTPH_Cycles_5                   ((uint32_t)0x50000000)
#define TSC_CTPH_Cycles_6                   ((uint32_t)0x60000000)
#define TSC_CTPH_Cycles_7                   ((uint32_t)0x70000000)
#define TSC_CTPH_Cycles_8                   ((uint32_t)0x80000000)
#define TSC_CTPH_Cycles_9                   ((uint32_t)0x90000000)
#define TSC_CTPH_Cycles_10                  ((uint32_t)0xA0000000)
#define TSC_CTPH_Cycles_11                  ((uint32_t)0xB0000000)
#define TSC_CTPH_Cycles_12                  ((uint32_t)0xC0000000)
#define TSC_CTPH_Cycles_13                  ((uint32_t)0xD0000000)
#define TSC_CTPH_Cycles_14                  ((uint32_t)0xE0000000)
#define TSC_CTPH_Cycles_15                  ((uint32_t)0xF0000000)

#define IS_TSC_CTPH_CYCLES(CYCLES)         (((CYCLES) == TSC_CTPH_Cycles_0) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_1) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_2) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_3) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_4) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_5) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_6) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_7) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_8) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_9) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_10) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_11) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_12) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_13) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_14) || \
                                            ((CYCLES) == TSC_CTPH_Cycles_15))
/**
  * @}
  */

/** @defgroup TSC_CTPL_Cycles
  * @{
  */
#define TSC_CTPL_Cycles_0                   ((uint32_t)0x00000000)
#define TSC_CTPL_Cycles_1                   ((uint32_t)0x01000000)
#define TSC_CTPL_Cycles_2                   ((uint32_t)0x02000000)
#define TSC_CTPL_Cycles_3                   ((uint32_t)0x03000000)
#define TSC_CTPL_Cycles_4                   ((uint32_t)0x04000000)
#define TSC_CTPL_Cycles_5                   ((uint32_t)0x05000000)
#define TSC_CTPL_Cycles_6                   ((uint32_t)0x06000000)
#define TSC_CTPL_Cycles_7                   ((uint32_t)0x07000000)
#define TSC_CTPL_Cycles_8                   ((uint32_t)0x08000000)
#define TSC_CTPL_Cycles_9                   ((uint32_t)0x09000000)
#define TSC_CTPL_Cycles_10                  ((uint32_t)0x0A000000)
#define TSC_CTPL_Cycles_11                  ((uint32_t)0x0B000000)
#define TSC_CTPL_Cycles_12                  ((uint32_t)0x0C000000)
#define TSC_CTPL_Cycles_13                  ((uint32_t)0x0D000000)
#define TSC_CTPL_Cycles_14                  ((uint32_t)0x0E000000)
#define TSC_CTPL_Cycles_15                  ((uint32_t)0x0F000000)

#define IS_TSC_CTPL_CYCLES(CYCLES)         (((CYCLES) == TSC_CTPL_Cycles_0) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_1) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_2) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_3) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_4) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_5) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_6) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_7) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_8) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_9) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_10) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_11) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_12) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_13) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_14) || \
                                            ((CYCLES) == TSC_CTPL_Cycles_15))
/**
  * @}
  */

/** @defgroup TSC_Prescaler_Value
  * @{
  */
#define TSC_PRESCALER_VALUE_1               ((uint32_t)0x00000000)
#define TSC_PRESCALER_VALUE_2               ((uint32_t)0x00001000)
#define TSC_PRESCALER_VALUE_4               ((uint32_t)0x00002000)
#define TSC_PRESCALER_VALUE_8               ((uint32_t)0x00003000)
#define TSC_PRESCALER_VALUE_16              ((uint32_t)0x00004000)
#define TSC_PRESCALER_VALUE_32              ((uint32_t)0x00005000)
#define TSC_PRESCALER_VALUE_64              ((uint32_t)0x00006000)
#define TSC_PRESCALER_VALUE_128             ((uint32_t)0x00007000)

#define IS_TSC_PRESCALER_VALUE(VALUE)      (((VALUE) == TSC_PRESCALER_VALUE_1)  || \
                                            ((VALUE) == TSC_PRESCALER_VALUE_2)  || \
                                            ((VALUE) == TSC_PRESCALER_VALUE_4)  || \
                                            ((VALUE) == TSC_PRESCALER_VALUE_8)  || \
                                            ((VALUE) == TSC_PRESCALER_VALUE_16) || \
                                            ((VALUE) == TSC_PRESCALER_VALUE_32) || \
                                            ((VALUE) == TSC_PRESCALER_VALUE_64) || \
                                            ((VALUE) == TSC_PRESCALER_VALUE_128))
/**
  * @}
  */

/** @defgroup TSC_Max_Count_Error
  * @{
  */
#define TSC_Max_Count_Error_255             ((uint32_t)0x00000000)
#define TSC_Max_Count_Error_511             ((uint32_t)0x00000020)
#define TSC_Max_Count_Error_1023            ((uint32_t)0x00000040)
#define TSC_Max_Count_Error_2047            ((uint32_t)0x00000060)
#define TSC_Max_Count_Error_4095            ((uint32_t)0x00000080)
#define TSC_Max_Count_Error_8191            ((uint32_t)0x000000A0)
#define TSC_Max_Count_Error_16383           ((uint32_t)0x000000C0)

#define IS_TSC_MAX_COUNT_ERROR(COUNT)      (((COUNT) == TSC_Max_Count_Error_255)    || \
                                            ((COUNT) == TSC_Max_Count_Error_511)    || \
                                            ((COUNT) == TSC_Max_Count_Error_1023)   || \
                                            ((COUNT) == TSC_Max_Count_Error_2047)   || \
                                            ((COUNT) == TSC_Max_Count_Error_4095)   || \
                                            ((COUNT) == TSC_Max_Count_Error_8191)   || \
                                            ((COUNT) == TSC_Max_Count_Error_16383))
/**
  * @}
  */

/** @defgroup TSC_IO_Default_Status
  * @{
  */
#define TSC_IO_DEFAULT_STATUS_OUTPUT_LOW             ((uint32_t)0x00000000)
#define TSC_IO_DEFAULT_STATUS_INPUT_HIGH_IMPEDANCE   ((uint32_t)0x00000010)

#define IS_TSC_IO_DEFAULT_STATUS(STATUS)   (((STATUS) == TSC_IO_DEFAULT_STATUS_OUTPUT_LOW)    || \
                                            ((STATUS) == TSC_IO_DEFAULT_STATUS_INPUT_HIGH_IMPEDANCE))
/**
  * @}
  */

/** @defgroup TSC_Sync_Polar
  * @{
  */
#define TSC_SYNC_POLAR_FALLING_EDGE                     ((uint32_t)0x00000000)
#define TSC_SYNC_POLAR_RISING_EDGE_AND_HIGH_LEVEL       ((uint32_t)0x00000008)

#define IS_TSC_SYNC_POLAR(POLAR)           (((POLAR) == TSC_SYNC_POLAR_FALLING_EDGE)    || \
                                            ((POLAR) == TSC_SYNC_POLAR_RISING_EDGE_AND_HIGH_LEVEL))
/**
  * @}
  */

/** @defgroup TSC_Sample_Mode
  * @{
  */
#define TSC_SAMPLE_MODE_NORMAL              ((uint32_t)0x00000000)
#define TSC_SAMPLE_MODE_SYNC                ((uint32_t)0x00000004)

#define IS_TSC_SAMPLE_MODE(MODE)           (((MODE) == TSC_SAMPLE_MODE_NORMAL)    || \
                                            ((MODE) == TSC_SAMPLE_MODE_SYNC))
/**
  * @}
  */

/** @defgroup TSC_IO
  * @{
  */
#define TSC_IO_G1_IO1                       ((uint32_t)0x00000001)
#define TSC_IO_G1_IO2                       ((uint32_t)0x00000002)
#define TSC_IO_G1_IO3                       ((uint32_t)0x00000004)
#define TSC_IO_G1_IO4                       ((uint32_t)0x00000008)
#define TSC_IO_G2_IO1                       ((uint32_t)0x00000010)
#define TSC_IO_G2_IO2                       ((uint32_t)0x00000020)
#define TSC_IO_G2_IO3                       ((uint32_t)0x00000040)
#define TSC_IO_G2_IO4                       ((uint32_t)0x00000080)
#define TSC_IO_G3_IO1                       ((uint32_t)0x00000100)
#define TSC_IO_G3_IO2                       ((uint32_t)0x00000200)
#define TSC_IO_G3_IO3                       ((uint32_t)0x00000400)
#define TSC_IO_G3_IO4                       ((uint32_t)0x00000800)
#define TSC_IO_G4_IO1                       ((uint32_t)0x00001000)
#define TSC_IO_G4_IO2                       ((uint32_t)0x00002000)
#define TSC_IO_G4_IO3                       ((uint32_t)0x00004000)
#define TSC_IO_G4_IO4                       ((uint32_t)0x00008000)
#define TSC_IO_G5_IO1                       ((uint32_t)0x00010000)
#define TSC_IO_G5_IO2                       ((uint32_t)0x00020000)
#define TSC_IO_G5_IO3                       ((uint32_t)0x00040000)
#define TSC_IO_G5_IO4                       ((uint32_t)0x00080000)
#define TSC_IO_G6_IO1                       ((uint32_t)0x00100000)
#define TSC_IO_G6_IO2                       ((uint32_t)0x00200000)
#define TSC_IO_G6_IO3                       ((uint32_t)0x00400000)
#define TSC_IO_G6_IO4                       ((uint32_t)0x00800000)

#define IS_TSC_GET_SAMPLE_VALUE_IO(IO)     (((IO) == TSC_IO_G1_IO1) || ((IO) == TSC_IO_G1_IO2) || \
                                            ((IO) == TSC_IO_G1_IO3) || ((IO) == TSC_IO_G1_IO4) || \
                                            ((IO) == TSC_IO_G2_IO1) || ((IO) == TSC_IO_G2_IO2) || \
                                            ((IO) == TSC_IO_G2_IO3) || ((IO) == TSC_IO_G2_IO4) || \
                                            ((IO) == TSC_IO_G3_IO1) || ((IO) == TSC_IO_G3_IO2) || \
                                            ((IO) == TSC_IO_G3_IO3) || ((IO) == TSC_IO_G3_IO4) || \
                                            ((IO) == TSC_IO_G4_IO1) || ((IO) == TSC_IO_G4_IO2) || \
                                            ((IO) == TSC_IO_G4_IO3) || ((IO) == TSC_IO_G4_IO4) || \
                                            ((IO) == TSC_IO_G5_IO1) || ((IO) == TSC_IO_G5_IO2) || \
                                            ((IO) == TSC_IO_G5_IO3) || ((IO) == TSC_IO_G5_IO4) || \
                                            ((IO) == TSC_IO_G6_IO1) || ((IO) == TSC_IO_G6_IO2) || \
                                            ((IO) == TSC_IO_G6_IO3) || ((IO) == TSC_IO_G6_IO4))

#define IS_TSC_IO(IO)                      ((((IO) & 0x00FFFFFF) != 0) && (((IO) & 0xFF000000) == 0))
/**
  * @}
  */

/** @defgroup TSC_FLAG
  * @{
  */
#define TSC_FLAG_G1S                        ((uint32_t)0x00010000)
#define TSC_FLAG_G2S                        ((uint32_t)0x00020000)
#define TSC_FLAG_G3S                        ((uint32_t)0x00040000)
#define TSC_FLAG_G4S                        ((uint32_t)0x00080000)
#define TSC_FLAG_G5S                        ((uint32_t)0x00100000)
#define TSC_FLAG_G6S                        ((uint32_t)0x00200000)

#define IS_TSC_FLAG(FLAG)                  (((FLAG) == TSC_FLAG_G1S) || ((FLAG) == TSC_FLAG_G2S) || \
                                            ((FLAG) == TSC_FLAG_G3S) || ((FLAG) == TSC_FLAG_G4S) || \
                                            ((FLAG) == TSC_FLAG_G5S) || ((FLAG) == TSC_FLAG_G6S))
/**
  * @}
  */ 

/** @defgroup TSC_IT
  * @{
  */
#define TSC_IT_MCE                          ((uint32_t)0x00000001)
#define TSC_IT_EOA                          ((uint32_t)0x00000002)

#define IS_TSC_IT(IT)                      ((((IT) & 0xFFFFFFFC) == 0x00000000) && ((IT) != 0x00000000))

#define IS_TSC_GET_IT(IT)                  (((IT) == TSC_IT_MCE) || ((IT) == TSC_IT_EOA))

#define IS_TSC_CLEAR_IT(IT)                ((((IT) & 0xFFFFFFFC) == 0x00000000) && ((IT) != 0x00000000))

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TSC_DeInit(void);
void TSC_Cmd(FunctionalState NewState);
void TSC_Init(TSC_InitTypeDef* TSC_InitStruct);
void TSC_IOInit(TSC_IOInitTypeDef* TSC_IOInitStruct, uint32_t TSC_IO);
void TSC_Cmd(FunctionalState NewState);
uint16_t TSC_GetSampleValue(uint32_t TSC_IO);
void TSC_StartCmd(FunctionalState NewState);
FlagStatus TSC_GetFlagStatus(uint32_t TSC_FLAG);
void TSC_ITConfig(uint32_t TSC_IT, FunctionalState NewState);
ITStatus TSC_GetITStatus(uint32_t TSC_IT);
void TSC_ClearITPendingBit(uint32_t TSC_IT);

#ifdef __cplusplus
}
#endif

#endif /* VTM071x_TSC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2018 MIC *****END OF FILE****/
