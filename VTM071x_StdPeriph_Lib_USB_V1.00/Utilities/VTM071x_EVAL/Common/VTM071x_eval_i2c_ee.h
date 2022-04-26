/**
  ******************************************************************************
  * @file    mt071x_eval_i2c_ee.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the 
  *              mt071x_eval_i2c_ee.c driver.
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
#ifndef __MT071X_EVAL_I2C_EE_H
#define __MT071X_EVAL_I2C_EE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mt071X_eval.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup MT071x_EVAL
  * @{
  */
  
/** @addtogroup MT071x_EVAL_I2C_EE
  * @{
  */  

/** @defgroup MT071x_EVAL_I2C_EE_Exported_Types
  * @{
  */ 
struct EEPROM_Info 
{
    char *Name;
    uint32_t SlaveAddress;
    uint32_t XbitAddress;
    uint32_t Size;
    uint32_t PageSize;
    uint32_t AddressBytes;
    uint32_t Speed;
    uint32_t SDASetupTime;
    uint32_t CLKPulseWidthHigh;
    uint32_t CLKPulseWidthLow;
};

enum I2C_Master_Status
{
    I2C_MS_Deinit,
    I2C_MS_Idle,
    I2C_MS_Standby,
    I2C_MS_WriteProcess,
    I2C_MS_WriteSucceed,
    I2C_MS_ReadProcess,
    I2C_MS_ReadSucceed,
    I2C_MS_ReadFailed,
    I2C_MS_AbortOops,
    I2C_MS_AbortFatal,
};

/**
  * @}
  */  

/** @defgroup MT071x_EVAL_I2C_EE_Exported_Constants
  * @{
  */

/**
  * @}
  */  

/** @defgroup MT071x_EVAL_I2C_EE_Exported_Macros
  * @{
  */    
#define I2C_INIT_FAILED             0xE0100000          //Tries to init while I2C_MasterStatus isn't Idle
#define I2C_TRANSMIT_OOPS           0xE0200000          //Transmit Oops
#define I2C_TRANSMIT_FATAL          0xE0300000          //Transmit Fatal
#define I2C_RECEIVE_FAILED          0xE0400000          //Receive failed

#define I2C_DISABLE_TIMEOUT         0xE1000000          //Disable failed
#define I2C_TRANSMIT_TIMEOUT        0xE2000000          //Transmit failed
#define I2C_WRONG_ADDRESSBYTES      0xE3000000          //Wrong Address Bytes

#define I2C_ERROR_FLAG              0xE0000000          //

#define I2C_X                       I2C1
/**
  * @}
  */ 

/** @defgroup MT071x_EVAL_I2C_EE_Exported_Functions
  * @{
  */ 
void sEE_DeInit(void);
int sEE_Init(void);
int sEE_WritePage(uint8_t *WriteBuf, uint32_t EEPROMAddress, uint32_t Size);
int sEE_WriteBuffer(uint8_t *WriteBuf, uint32_t EEPROMAddress, uint32_t Size);
int sEE_ReadBuffer(uint8_t *ReadBuf, uint32_t EEPROMAddress, uint32_t Size);
void I2C_IRQHandler(void);

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __MT071x_EVAL_I2C_EE_H */
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

