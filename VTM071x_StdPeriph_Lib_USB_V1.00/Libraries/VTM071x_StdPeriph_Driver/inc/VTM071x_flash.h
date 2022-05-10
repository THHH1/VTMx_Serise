/**
  ******************************************************************************
  * @file    VTM071x_gpio.h
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the GPIO 
  *          firmware library.
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
#ifndef __VTM071x_FLASH_H
#define __VTM071x_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "vtm071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup FLASH_Exported_Constants
  * @{
  */ 
  
/** @defgroup FLASH_Latency 
  * @{
  */ 
#define FLASH_Latency_0                     FLASH_ACR_LATENCY_0		/*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1                     FLASH_ACR_LATENCY_1		/*!< FLASH One Latency cycle */
#define FLASH_Latency_2                     FLASH_ACR_LATENCY_2		/*!< FLASH TWO Latency cycle */
#define FLASH_Latency_3                     FLASH_ACR_LATENCY_3		/*!< FLASH THERE Latency cycle */

#define IS_FLASH_LATENCY(LATENCY)          (((LATENCY) == FLASH_Latency_0)  || \
                                            ((LATENCY) == FLASH_Latency_1)  || \
                                            ((LATENCY) == FLASH_Latency_2)  || \
                                            ((LATENCY) == FLASH_Latency_3))
/**
  * @}
  */ 

/** @defgroup FLASH_Interrupts 
  * @{
  */
#define FLASH_IT_EOP                        FLASH_CR_EOPIE  /*!< End of programming interrupt source */
#define FLASH_IT_EOE                        FLASH_CR_EOEIE  /*!< Error interrupt source */
#define IS_FLASH_IT(IT)                     ((((IT) & (uint32_t)0xFCFFFFFF) == 0x00000000) && (((IT) != 0x00000000)))
/**
  * @}
  */ 

/** @defgroup FLASH_Flags 
  * @{
  */ 
#define FLASH_FLAG_BSY                 FLASH_SR_BUSY     /*!< FLASH Busy flag */
#define FLASH_FLAG_EOE                 FLASH_SR_EOE  	 /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP                 FLASH_SR_EOP      /*!< FLASH End of Programming flag */
 
#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFFC) == 0x00000000) && ((FLAG) != 0x00000000))

#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_BSY)  || \
								  ((FLAG) == FLASH_FLAG_EOE) || \
                                  ((FLAG) == FLASH_FLAG_EOP))
/**
  * @}
  */ 

/** @defgroup FLASH_PROGRAM_SRAM_ADDR 
  * @{
  */  
#define IS_FLASH_PROGRAM_SRAM_ADDR(ADDR) (((ADDR) >= SRAM_BASE) && ((ADDR) <= (SRAM_BASE + SRAM_SIZE)))
/**
  * @}
  */

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** 
  * @brief  FLASH memory functions that can be executed from FLASH.  
  */  
/* FLASH Interface configuration functions ************************************/
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_CacheCmd(FunctionalState NewState);
void FLASH_FlushCacheCmd(FunctionalState NewState);

/* FLASH Memory Programming functions *****************************************/
void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_EraseAPROM(uint32_t FlashAddr);
void FLASH_EraseLDROM(uint32_t FlashAddr);
void FLASH_ProgramLDROM(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize);
void FLASH_ProgramAPROM(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize);

/* FLASH Interrupts and flags management functions **********************************/
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __VTM071x_FLASH_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT MIC *****END OF FILE****/

