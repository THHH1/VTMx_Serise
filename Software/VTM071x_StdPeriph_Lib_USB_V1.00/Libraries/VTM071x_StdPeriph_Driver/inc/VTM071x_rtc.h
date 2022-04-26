/**
  ******************************************************************************
  * @file    VTM071x_rtc.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the RTC firmware 
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
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VTM071x_RTC_H
#define __VTM071x_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "vtm071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  RTC Init structure definition  
  */
typedef struct
{
	uint16_t RTC_Second;                /*!< Specifies the RTC second.
                                            This parameter can be a 32bit */

	uint16_t RTC_ClkSource;             /*!< Specifies the RTC clock source.
                                            This parameter can be a value of @ref RTC_clock_source */

}RTC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RTC_Exported_Constants
  * @{
  */

/** @defgroup RTC_clock_source 
  * @{
  */
#define IS_RTC_CLOCK_SOURCE(SOURCE)             (((SOURCE) == RTC_CTRL_CLK_SEL_32K)  || ((SOURCE) == RTC_CTRL_CLK_SEL_IRC12M)   || \
                                                ((SOURCE) == RTC_CTRL_CLK_SEL_OSC12M) || ((SOURCE) == RTC_CTRL_CLK_SEL_10K))
/**
  * @}
  */

/** @defgroup RTC_interrupts_define 
  * @{
  */
#define RTC_IT_SEC                              RTC_CTRL_1HZ_INT
#define RTC_IT_ALARM					        RTC_CTRL_ALARM_INT
#define IS_RTC_IT(IT)                          (((IT) == RTC_IT_SEC) || ((IT) == RTC_IT_ALARM) || \
                                                ((IT) == (RTC_IT_SEC | RTC_IT_ALARM)))

/**
  * @}
  */ 

/** @defgroup RTC_STATUS_flags 
  * @{
  */
#define IS_RTC_IT_FLAG(FLAG)                    (((FLAG) == RTC_IT_SEC) || ((FLAG) == RTC_IT_ALARM))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RTC_DeInit(void);
void RTC_Init(RTC_InitTypeDef* RTC_InitStruct);
void RTC_LoadCmd(FunctionalState NewState);
void RTC_CLOCKSourceSelect(uint32_t ClockSource);
void RTC_Cmd(FunctionalState NewState);
void RTC_AlarmConfig(uint32_t Second);
void RTC_CountConfig(uint32_t Second);
uint32_t RTC_GetTime(void);
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState);
ITStatus RTC_GetITStatus(uint32_t RTC_IT);
void RTC_ClearITPendingBit(uint32_t RTC_IT);

#ifdef __cplusplus
}
#endif

#endif /* __VTM071x_RTC_H */
/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2018 MIC *****END OF FILE****/
