/**
  ******************************************************************************
  * @file    VTM071x_eval.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains definitions for VTM071x_EVAL's hardware resources.
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
#ifndef __VTM071x_EVAL_H
#define __VTM071x_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"
   
/** @addtogroup Utilities
  * @{
  */

/** @addtogroup VTM071x_EVAL
  * @{
  */
      
/** @addtogroup VTM071x_EVAL_LOW_LEVEL
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** @defgroup VTM071x_EVAL_LOW_LEVEL_Exported_Constants
  * @{
  */ 

/** 
  * @brief  Define for VTM071x_EVAL board  
  */ 

/** @addtogroup VTM071x_EVAL_LOW_LEVEL_I2C_EE
  * @{
  */
#define sEE_I2C                          I2C
/**
  * @}
  */  

/**
  * @}
  */ 

/**
  * @}
  */ 

/** @defgroup VTM071x_EVAL_LOW_LEVEL_Exported_Functions
  * @{
  */
void SPI_FLASH_LowLevel_DeInit(SPI_TypeDef *SPIx);
void SPI_FLASH_LowLevel_Init(SPI_TypeDef *SPIx);
void sEE_LowLevel_DeInit(I2C_TypeDef * I2Cx);
void sEE_LowLevel_Init(I2C_TypeDef * I2Cx);
/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __VTM071x_EVAL_H */
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
