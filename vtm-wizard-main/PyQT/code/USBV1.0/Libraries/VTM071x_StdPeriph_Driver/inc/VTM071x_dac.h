/**
  ******************************************************************************
  * @file    VTM071x_dac.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the DAC firmware
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
#ifndef __VTM071x_DAC_H
#define __VTM071x_DAC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup DAC
  * @{
  */ 
/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  DAC Init structure definition
  */
typedef struct
{
    uint32_t DAC_Trigger;           /*!< Specifies the external trigger for the selected DAC channel.
                                    This parameter can be a value of @ref DAC_trigger_selection */

    uint32_t DAC_ReferenceVoltage;  /*!< Specifies DAC reference voltage
                                    This parameter can be a value of @ref DAC_reference_voltage */

    uint32_t DAC_OutputBuffer;      /*!< Specifies whether the DAC channel output buffer is enabled or disabled.
                                    This parameter can be a value of @ref DAC_output_buffer */
}DAC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DAC_Exported_Constants
  * @{
  */ 

#define IS_DAC_ALL_PERIPH(PERIPH)           (((PERIPH) == DAC0)   || \
                                             ((PERIPH) == DAC1))

/** @defgroup DAC_trigger_selection 
  * @{
  */
#define DAC_Trigger_WRITE_DATA              ((uint32_t)0x00000000)
#define DAC_Trigger_DMA_ACK                 ((uint32_t)0x00000010)
#define DAC_Trigger_TIMER0_RISINGEDGE       ((uint32_t)0x00000020)
#define DAC_Trigger_TIMER1_RISINGEDGE       ((uint32_t)0x00000030)
#define DAC_Trigger_TIMER2_RISINGEDGE       ((uint32_t)0x00000040)
#define DAC_Trigger_TIMER3_RISINGEDGE       ((uint32_t)0x00000050)

#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_Trigger_WRITE_DATA)          || \
                                 ((TRIGGER) == DAC_Trigger_DMA_ACK)             || \
                                 ((TRIGGER) == DAC_Trigger_TIMER0_RISINGEDGE)   || \
                                 ((TRIGGER) == DAC_Trigger_TIMER1_RISINGEDGE)   || \
                                 ((TRIGGER) == DAC_Trigger_TIMER2_RISINGEDGE)   || \
                                 ((TRIGGER) == DAC_Trigger_TIMER3_RISINGEDGE))
                                 
/**
  * @}
  */

/** @defgroup DAC_reference_voltage 
  * @{
  */
#define DAC_REF_VOLTAGE_VDDA                ((uint32_t)0x00000000)
#define DAC_REF_VOLTAGE_2P048               ((uint32_t)0x00000100)
#define DAC_REF_VOLTAGE_PAD_VREFH           ((uint32_t)0x00000200)

#define IS_DAC_REF_VOLTAGE(VOLTAGE)        (((VOLTAGE) == DAC_REF_VOLTAGE_VDDA)     || \
                                            ((VOLTAGE) == DAC_REF_VOLTAGE_2P048)    || \
                                            ((VOLTAGE) == DAC_REF_VOLTAGE_PAD_VREFH))
                                 
/**
  * @}
  */

/** @defgroup DAC_OutputBuffer 
  * @{
  */
#define DAC_OutputBuffer_Enable             ((uint32_t)0x00000000)
#define DAC_OutputBuffer_Disable            ((uint32_t)0x00000020)
#define IS_DAC_OUTPUT_BUFFER_STATE(STATE)  (((STATE) == DAC_OutputBuffer_Enable)    || \
                                            ((STATE) == DAC_OutputBuffer_Disable))
/**
  * @}
  */

/** @defgroup DAC_data 
  * @{
  */
#define IS_DAC_DATA(DATA)                   ((DATA) <= 0xFFF) 
/**
  * @}
  */

/** @defgroup DAC_flags_definition 
  * @{
  */ 
#define DAC_FLAG_BUSY                       DAC_STATUS_BUSY
  
#define IS_DAC_FLAG(FLAG)                   (((FLAG) == DAC_FLAG_BUSY))
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void DAC_DeInit(void);
void DAC_Init(DACx_TypeDef *DACx, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(DACx_TypeDef *DACx, FunctionalState NewState);
void DAC_GroupCmd(FunctionalState NewState);
void DAC_SetData(DACx_TypeDef *DACx, uint16_t Data);
FlagStatus DAC_GetFlagStatus(DACx_TypeDef *DACx, uint32_t DAC_FLAG);
void DAC_ITConfig(DACx_TypeDef *DACx, FunctionalState NewState);
ITStatus DAC_GetITStatus(DACx_TypeDef *DACx);
void DAC_ClearITPendingBit(DACx_TypeDef *DACx);



#ifdef __cplusplus
}
#endif

#endif /* VTM071x_DAC_H */

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
