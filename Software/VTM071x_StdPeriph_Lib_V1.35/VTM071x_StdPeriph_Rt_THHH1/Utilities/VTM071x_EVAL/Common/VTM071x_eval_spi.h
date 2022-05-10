/**
  ******************************************************************************
  * @file    VTM071x_eval_spi.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the 
  *              VTM071x_eval_spi.c driver.
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
#ifndef __VTM071X_EVAL_SPI_H
#define __VTM071X_EVAL_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x_eval.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup VTM071x_EVAL
  * @{
  */
  
/** @addtogroup VTM071x_EVAL_SPI_FLASH
  * @{
  */  

/** @defgroup VTM071x_EVAL_SPI_Flash_Macros
  * @{
  */ 
#define SPI_FLASH_CMD_WRITE_ENABLE          0x06
#define SPI_FLASH_CMD_WRITE_DISABLE         0x04
#define SPI_FLASH_CMD_READ_STATUS1          0x05
#define SPI_FLASH_CMD_READ_STATUS2          0x35
#define SPI_FLASH_CMD_WRITE_STATUS          0x01
#define SPI_FLASH_CMD_WRITE                 0x02
#define SPI_FLASH_CMD_ERASE_64K             0xD8
#define SPI_FLASH_CMD_ERASE_32K             0x52
#define SPI_FLASH_CMD_ERASE_4K              0x20
#define SPI_FLASH_CMD_ERASE_ALL             0x60 // 0xC7
#define SPI_FLASH_CMD_ERASE_SUSPEND         0x75
#define SPI_FLASH_CMD_ERASE_RESUME          0x7A
#define SPI_FLASH_CMD_Power_Down            0xB9 
#define SPI_FLASH_CMD_READ_MANUFACTURER_ID  0x90
#define SPI_FLASH_CMD_READ_UNIQUE_ID        0x4B
#define SPI_FLASH_CMD_READ_JEDEC_ID         0x9F
#define SPI_FLASH_CMD_READ          	    0x03
#define SPI_FLASH_CMD_FAST_READ             0x0B
#define SPI_FLASH_CMD_Release_PowerDown	    0xAB 

#define	SPI_FLASH_STATUS1_BUSY		((uint8_t)0x01)
#define	SPI_FLASH_STATUS1_WEL		((uint8_t)0x02)
#define	SPI_FLASH_STATUS1_BP0		((uint8_t)0x04)
#define	SPI_FLASH_STATUS1_BP1		((uint8_t)0x08)
#define	SPI_FLASH_STATUS1_BP2		((uint8_t)0x10)
#define	SPI_FLASH_STATUS1_BP		(SPI_FLASH_STATUS1_BP0 | SPI_FLASH_STATUS1_BP1 | SPI_FLASH_STATUS1_BP2)


#define SPI_FLASH_PAGESIZE  		256 // 256 Byte

#define SPI_FLASH_CS_LOW()          (GPIODATA1->DT_CLR = (uint32_t)(1 << (GPIO_Pin_3)))
#define SPI_FLASH_CS_HIGH()         (GPIODATA1->DT_SET = (uint32_t)(1 << (GPIO_Pin_3)))

#define SPI_X                       SPI0
#define SPI_TIMEOUT_VALUE           0x5000
/**
  * @}
  */

/** @defgroup VTM071x_EVAL_SPI_FLASH_Functions
  * @{
  */ 
void SPI_FLASH_DeInit(void);
int SPI_FLASH_Init(void);
void SPI_FLASH_ReadID(uint8_t *Flash_ID);
int SPI_FLASH_EraseSector4K(uint32_t Addr);
int SPI_FLASH_EraseSector32K(uint32_t Addr);
int SPI_FLASH_EraseSector64K(uint32_t Addr);
int SPI_FLASH_EraseFull(void);
int SPI_FLASH_Read(uint8_t *RecBuf, uint32_t Addr, uint32_t RecSize);
int SPI_FLASH_Write(uint8_t *SendBuf, uint32_t Addr, uint32_t SendSize);
int SPI_FLASH_PowerDown(void);
int SPI_FLASH_WakeUp(void);

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __VTM071x_EVAL_SPI_H */
/**
  * @}
  */

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

