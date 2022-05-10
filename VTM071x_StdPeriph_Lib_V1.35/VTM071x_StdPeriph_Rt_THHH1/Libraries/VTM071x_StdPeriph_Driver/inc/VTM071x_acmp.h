/**
  ******************************************************************************
  * @file    VTM071x_acmp.h
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
#ifndef __VTM071x_ACMP_H
#define __VTM071x_ACMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup ACMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  ACMP Init structure definition
  */
typedef struct
{
	uint32_t ACMP_NegativeSelect;		    /*!< Selects the source of negative pole.
                                            This parameter can be a value of @ref ACMP_Negative_Select */

	uint32_t ACMP_PositiveSelect;           /*!< Selects the source of positive pole.
                                            This parameter can be a value of @ref ACMP_Positive_Select */

	uint32_t ACMP_Hysteresis;               /*!< Selects ACMP hysteresis.
                                            This parameter can be a value of @ref ACMP_Hysteresis */

	uint32_t ACMP_Output;		            /*!< Selects the state of Output.
                                            This parameter can be a value of @ref ACMP_Output_State */
}ACMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup ACMP_Exported_Constants
  * @{
  */ 
#define ACMP0                               ((uint32_t)0xDCDC0000)
#define ACMP1                               ((uint32_t)0xDCDC0010)
#define ACMP2                               ((uint32_t)0xDCDC0020)
#define IS_ACMP_ALL_PERIPH(PERIPH)          (((PERIPH) == ACMP0) || ((PERIPH) == ACMP1) || ((PERIPH) == ACMP2))


/** @defgroup ACMP_Negative_Select
  * @{
  */
#define	ACMP_NEGATIVE_SELECT_PIN                    ((uint32_t)0x00000000)
#define	ACMP_NEGATIVE_SELECT_REF_VOL_1P25           ((uint32_t)0x00000010)
#define	ACMP_NEGATIVE_SELECT_REF_VOL_1P09375        ((uint32_t)0x00001010)
#define	ACMP_NEGATIVE_SELECT_REF_VOL_0P9375         ((uint32_t)0x00002010)
#define	ACMP_NEGATIVE_SELECT_REF_VOL_0P78125        ((uint32_t)0x00003010)
#define	ACMP_NEGATIVE_SELECT_REF_VOL_0P625          ((uint32_t)0x00004010)
#define	ACMP_NEGATIVE_SELECT_REF_VOL_0P46875        ((uint32_t)0x00005010)
#define	ACMP_NEGATIVE_SELECT_REF_VOL_0P3125         ((uint32_t)0x00006010)
#define	ACMP_NEGATIVE_SELECT_REF_VOL_0P15625        ((uint32_t)0x00007010)
#define	ACMP_NEGATIVE_SELECT_DAC0                   ((uint32_t)0x00000020)
#define	ACMP_NEGATIVE_SELECT_DAC1                   ((uint32_t)0x00000030)

#define IS_ACMP_NEGATIVE_SELECT(SELECT)    		    (((SELECT) == ACMP_NEGATIVE_SELECT_PIN)             || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_REF_VOL_1P25)    || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_REF_VOL_1P09375) || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_REF_VOL_0P9375)  || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_REF_VOL_0P78125) || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_REF_VOL_0P625)   || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_REF_VOL_0P46875) || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_REF_VOL_0P3125)  || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_REF_VOL_0P15625) || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_DAC0)            || \
                                                     ((SELECT) == ACMP_NEGATIVE_SELECT_DAC1))
/**
  * @}
  */ 

/** @defgroup ACMP_Positive_Select
  * @{
  */
#define	ACMP_POSITIVE_SELECT_PIN                    ((uint32_t)0x00000000)
#define	ACMP_POSITIVE_SELECT_OP0                    ((uint32_t)0x00000100)
#define	ACMP_POSITIVE_SELECT_OP1                    ((uint32_t)0x00000300)
#define	ACMP_POSITIVE_SELECT_OP2                    ((uint32_t)0x00000500)
#define	ACMP_POSITIVE_SELECT_OP3                    ((uint32_t)0x00000700)

#define IS_ACMP_POSITIVE_SELECT(SELECT)    		    (((SELECT) == ACMP_POSITIVE_SELECT_PIN) || \
                                                     ((SELECT) == ACMP_POSITIVE_SELECT_OP0) || \
                                                     ((SELECT) == ACMP_POSITIVE_SELECT_OP1) || \
                                                     ((SELECT) == ACMP_POSITIVE_SELECT_OP2) || \
                                                     ((SELECT) == ACMP_POSITIVE_SELECT_OP3))
/**
  * @}
  */ 

/** @defgroup ACMP_Output_State
  * @{
  */
#define	ACMP_OUTPUT_DISABLE                         ((uint32_t)0x00000000)
#define	ACMP_OUTPUT_ENABLE                          ((uint32_t)0x00200000)
#define	ACMP_OUTPUT_ENABLE_INV                      ((uint32_t)0x00300000)

#define IS_ACMP_OUTPUT_STATE(STATE)    		       (((STATE) == ACMP_OUTPUT_DISABLE) || \
                                                    ((STATE) == ACMP_OUTPUT_ENABLE) || \
                                                    ((STATE) == ACMP_OUTPUT_ENABLE_INV))
/**
  * @}
  */ 

/** @defgroup ACMP_Hysteresis
  * @{
  */
#define	ACMP_HYSTERESIS_DISABLE                     ((uint32_t)0x00000000)
#define	ACMP_HYSTERESIS_10MV                        ((uint32_t)0x00000004)
#define	ACMP_HYSTERESIS_20MV                        ((uint32_t)0x00000008)
#define	ACMP_HYSTERESIS_50MV                        ((uint32_t)0x0000000C)

#define IS_ACMP_HYSTERESIS(HYSTERESIS)    		    (((HYSTERESIS) == ACMP_HYSTERESIS_DISABLE)  || \
                                                     ((HYSTERESIS) == ACMP_HYSTERESIS_10MV)     || \
                                                     ((HYSTERESIS) == ACMP_HYSTERESIS_20MV)     || \
                                                     ((HYSTERESIS) == ACMP_HYSTERESIS_50MV))
/**
  * @}
  */ 

/** @defgroup ACMP0_Pin
  * @{
  */
#define	ACMP0_PIN_GPIO00_GPIO01                     ((uint32_t)0x00000000)
#define	ACMP0_PIN_GPIO20_GPIO21                     ((uint32_t)0x00000040)

#define IS_ACMP0_PIN(PIN)    		               (((PIN) == ACMP0_PIN_GPIO00_GPIO01)  || \
                                                    ((PIN) == ACMP0_PIN_GPIO20_GPIO21))
/**
  * @}
  */ 

/** @defgroup ACMP1_Pin
  * @{
  */
#define	ACMP1_PIN_GPIO02_GPIO03                     ((uint32_t)0x00000000)
#define	ACMP1_PIN_GPIO40_GPIO41                     ((uint32_t)0x00000040)

#define IS_ACMP1_PIN(PIN)    		               (((PIN) == ACMP1_PIN_GPIO02_GPIO03)  || \
                                                    ((PIN) == ACMP1_PIN_GPIO40_GPIO41))
/**
  * @}
  */ 

/** @defgroup ACMP2_Pin
  * @{
  */
#define	ACMP2_PIN_GPIO04_GPIO05                     ((uint32_t)0x00000000)
#define	ACMP2_PIN_GPIO42_GPIO43                     ((uint32_t)0x00000040)

#define IS_ACMP2_PIN(PIN)    		               (((PIN) == ACMP2_PIN_GPIO04_GPIO05)  || \
                                                    ((PIN) == ACMP2_PIN_GPIO42_GPIO43))
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void ACMP_DeInit(void);
void ACMP_Init(uint32_t ACMPx, ACMP_InitTypeDef* ACMP_InitStruct);
void ACMP0_PinConfig(uint32_t ACMP_Pin);
void ACMP1_PinConfig(uint32_t ACMP_Pin);
void ACMP2_PinConfig(uint32_t ACMP_Pin);
void ACMP_Cmd(uint32_t ACMPx, FunctionalState NewState);
void ACMP_ITConfig(uint32_t ACMPx, FunctionalState NewState);
FlagStatus ACMP_GetResult(uint32_t ACMPx);
ITStatus ACMP_GetITStatus(uint32_t ACMPx);
void ACMP_ClearITPendingBit(uint32_t ACMPx);


#ifdef __cplusplus
}
#endif

#endif /*__VTM071x_ACMP_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT MIC *****END OF FILE****/

