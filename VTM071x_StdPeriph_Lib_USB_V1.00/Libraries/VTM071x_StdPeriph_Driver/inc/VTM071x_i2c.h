/**
  ******************************************************************************
  * @file    VTM071x_i2c.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the I2C firmware 
  *              library.
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
#ifndef __VTM071x_I2C_H
#define __VTM071x_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "vtm071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  I2C Init structure definition  
  */
typedef struct
{
    uint32_t I2C_Mode;                      /*!< Specifies the I2C mode.
                                            This parameter can be a value of @ref I2C_Mode*/

    uint32_t I2C_XbitAddress;               /*!< Specifies whether the DW_apb_i2c is 7-bit or 10-bit addressing mode.
                                            This parameter can be a value of @ref I2C_Xbit_Address*/

    uint32_t I2C_ClockSpeed;                /*!< Specifies the clock frequency.
                                            This parameter can be a value of @ref I2C_Speed*/

    uint32_t I2C_RestartMode;             /*!< Specifies whether RESTART conditions may be sent when acting as a master.
                                            This parameter can be a value of @ref I2C_Restart_Mode*/
    
}I2C_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup I2C_Exported_Constants
  * @{
  */

#define IS_I2C_ALL_PERIPH(PERIPH)       (((PERIPH) == I2C0) || ((PERIPH) == I2C1))

/** @defgroup I2C_Mode 
  * @{
  */
#define I2C_MODE_MASTER                 ((uint32_t)0x00000041)
#define I2C_MODE_SLAVE                  ((uint32_t)0x00000000)
#define IS_I2C_Mode(Mode)               (((Mode) == I2C_MODE_MASTER) || \
                                        ((Mode) == I2C_MODE_SLAVE))
/**
  * @}
  */

/** @defgroup I2C_Xbit_Address 
  * @{
  */
#define I2C_XBIT_ADDRESS_7BIT           ((uint32_t)0x00000000)
#define I2C_XBIT_ADDRESS_10BIT          ((uint32_t)0x00000001)
#define IS_I2C_Xbit_Address(XBIT)       (((XBIT) == I2C_MODE_MASTER) || \
                                        ((XBIT) == I2C_MODE_SLAVE))
/**
  * @}
  */

/** @defgroup I2C_Speed
  * @{
  */
#define I2C_CLOCK_STANDARD_MODE         ((uint32_t)0x00000002)
#define I2C_CLOCK_FAST_MODE             ((uint32_t)0x00000004)
#define I2C_CLOCK_HIGH_SPEED_MODE       ((uint32_t)0x00000006)
#define IS_I2C_Speed_MODE(MODE)         (((MODE) == I2C_CLOCK_STANDARD_MODE) || \
                                        ((MODE) == I2C_CLOCK_FAST_MODE) || \
                                        ((MODE) == I2C_CLOCK_HIGH_SPEED_MODE))
/**
  * @}
  */

/** @defgroup I2C_Restart_Mode
  * @{
  */
#define I2C_RESTART_ENABLE              ((uint32_t)0x00000020)
#define I2C_RESTART_DISABLE             ((uint32_t)0x00000000)
#define IS_I2C_Restart_Mode(Mode)       (((Mode) == I2C_RESTART_ENABLE) || \
                                        ((Mode) == I2C_RESTART_DISABLE))
/**
  * @}
  */

/** @defgroup I2C_HCNT
  * @{
  */
#define IS_I2C_HCNT(HCNT)               ((HCNT) < 0x10000)
/**
  * @}
  */

/** @defgroup I2C_LCNT
  * @{
  */
#define IS_I2C_LCNT(LCNT)               ((LCNT) < 0x10000)
/**
  * @}
  */

/** @defgroup I2C_SPECIAL_CMD
  * @{
  */
#define I2C_SPECIAL_CMD_START           ((uint32_t)0x00000C00)
#define I2C_SPECIAL_CMD_GENERAL_CALL    ((uint32_t)0x00000800)
#define I2C_SPECIAL_CMD_NONE            ((uint32_t)0x00000000)
#define IS_I2C_SPECIAL_CMD(CMD)         (((CMD) == I2C_SPECIAL_CMD_START) || \
                                        ((CMD) == I2C_SPECIAL_CMD_GENERAL_CALL) || \
                                        ((CMD) == I2C_SPECIAL_CMD_NONE))
/**
  * @}
  */

/** @defgroup I2C_TAR
  * @{
  */
#define IS_I2C_TAR(TAR)                 ((TAR) < 0x400)
/**
  * @}
  */

/** @defgroup I2C_SAR
  * @{
  */
#define IS_I2C_SAR(SAR)                 ((SAR) < 0x400)
/**
  * @}
  */

/** @defgroup I2C_HSMasterCode
  * @{
  */
#define IS_I2C_HSMasterCode(CODE)       ((CODE) < 8)
/**
  * @}
  */

/** @defgroup I2C_SU_DAT
  * @{
  */
#define IS_I2C_SU_DAT(DAT)                 ((DAT) < 0xFF)
/**
  * @}
  */

/** @defgroup I2C_INTERRUPTS
  * @{
  */
#define I2C_IT_RX_UNDER                     ((uint32_t)0x00000001)
#define I2C_IT_RX_OVER                      ((uint32_t)0x00000002)
#define I2C_IT_RX_FULL                      ((uint32_t)0x00000004)
#define I2C_IT_TX_OVER                      ((uint32_t)0x00000008)
#define I2C_IT_TX_EMPTY                     ((uint32_t)0x00000010)
#define I2C_IT_RD_REQ                       ((uint32_t)0x00000020)
#define I2C_IT_TX_ABRT                      ((uint32_t)0x00000040)
#define I2C_IT_RX_DONE                      ((uint32_t)0x00000080)
#define I2C_IT_ACTIVITY                     ((uint32_t)0x00000100)
#define I2C_IT_STOP_DET                     ((uint32_t)0x00000200)
#define I2C_IT_START_DET                    ((uint32_t)0x00000400)
#define I2C_IT_GEN_CALL                     ((uint32_t)0x00000800)
#define I2C_IT_ALL				            ((uint32_t)0x00000fff)

#define IS_I2C_IT(IT)                       ((((IT) & (uint32_t)0xFFFFF000) == 0) && ((IT) != 0x00))
#define IS_I2C_GET_IT(IT)                   (((IT) == I2C_IT_RX_UNDER) || \
                                            ((IT) == I2C_IT_RX_OVER)   || \
                                            ((IT) == I2C_IT_RX_FULL)   || \
                                            ((IT) == I2C_IT_TX_OVER)   || \
                                            ((IT) == I2C_IT_TX_EMPTY)  || \
                                            ((IT) == I2C_IT_RD_REQ)    || \
                                            ((IT) == I2C_IT_TX_ABRT)   || \
                                            ((IT) == I2C_IT_RX_DONE)   || \
                                            ((IT) == I2C_IT_ACTIVITY)  || \
                                            ((IT) == I2C_IT_STOP_DET)  || \
                                            ((IT) == I2C_IT_START_DET) || \
                                            ((IT) == I2C_IT_GEN_CALL))
/**
  * @}
  */ 

/** @defgroup I2C_INTERRUPTS
  * @{
  */
#define I2C_CLEAR_ALL_INTR                  0x40
#define I2C_CLEAR_RX_UNDER                  0x44
#define I2C_CLEAR_RX_OVER                   0x48
#define I2C_CLEAR_TX_OVER                   0x4C
#define I2C_CLEAR_RD_REQ                    0x50
#define I2C_CLEAR_TX_ABRT                   0x54
#define I2C_CLEAR_RX_DONE                   0x58
#define I2C_CLEAR_ACTIVITY                  0x5C
#define I2C_CLEAR_STOP_DET                  0x60
#define I2C_CLEAR_START_DET                 0x64
#define I2C_CLEAR_GEN_CALL                  0x68

#define IS_I2C_CLEAR_IT(IT)                 (((IT) == I2C_CLEAR_ALL_INTR) || \
                                            ((IT) == I2C_CLEAR_RX_UNDER)   || \
                                            ((IT) == I2C_CLEAR_RX_OVER)   || \
                                            ((IT) == I2C_CLEAR_TX_OVER)   || \
                                            ((IT) == I2C_CLEAR_RD_REQ)  || \
                                            ((IT) == I2C_CLEAR_TX_ABRT)    || \
                                            ((IT) == I2C_CLEAR_RX_DONE)   || \
                                            ((IT) == I2C_CLEAR_ACTIVITY)   || \
                                            ((IT) == I2C_CLEAR_STOP_DET)  || \
                                            ((IT) == I2C_CLEAR_START_DET)  || \
                                            ((IT) == I2C_CLEAR_GEN_CALL))
/**
  * @}
  */ 

/** @defgroup I2C_FIFO_reception_threshold 
  * @{
  */
#define IS_I2C_RX_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) > 0) && ((THRESHOLD) <= 16))
/**
  * @}
  */

/** @defgroup I2C_FIFO_transmit_threshold 
  * @{
  */
#define IS_I2C_TX_FIFO_THRESHOLD(THRESHOLD) ((THRESHOLD) < 16)
/**
  * @}
  */

/** @defgroup I2C_FLAG
  * @{
  */
#define I2C_FLAG_ACTIVITY                   ((uint32_t)0x00000001)
#define I2C_FLAG_TFNF                       ((uint32_t)0x00000002)
#define I2C_FLAG_TFE                        ((uint32_t)0x00000004)
#define I2C_FLAG_RFNE                       ((uint32_t)0x00000008)
#define I2C_FLAG_RFF                        ((uint32_t)0x00000010)
#define I2C_FLAG_MST_ACTIVITY               ((uint32_t)0x00000020)
#define I2C_FLAG_SLV_ACTIVITY               ((uint32_t)0x00000040)

#define I2C_FLAG_IC_EN                      ((uint32_t)0x01000001)
#define I2C_FLAG_SLV_DISABLED_WHILE_BUSY    ((uint32_t)0x01000002)
#define I2C_FLAG_SLV_RX_DATA_LOST           ((uint32_t)0x01000004)
#define I2C_ENABLE_STATUS_FLAG              ((uint32_t)0x01000000)

#define IS_I2C_FLAG(FLAG)                   (((FLAG) == I2C_FLAG_ACTIVITY)    || \
                                            ((FLAG) == I2C_FLAG_TFNF)         || \
                                            ((FLAG) == I2C_FLAG_TFE)          || \
                                            ((FLAG) == I2C_FLAG_RFNE)         || \
                                            ((FLAG) == I2C_FLAG_RFF)          || \
                                            ((FLAG) == I2C_FLAG_MST_ACTIVITY) || \
                                            ((FLAG) == I2C_FLAG_SLV_ACTIVITY) || \
                                            ((FLAG) == I2C_FLAG_IC_EN)        || \
                                            ((FLAG) == I2C_FLAG_SLV_DISABLED_WHILE_BUSY) || \
                                            ((FLAG) == I2C_FLAG_SLV_RX_DATA_LOST))
/**
  * @}
  */ 

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/*  Function used to set the I2C configuration to the default reset state *****/
void I2C_DeInit(I2C_TypeDef * I2Cx);
void I2C_Init(I2C_TypeDef * I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef * I2Cx, FunctionalState NewState);
void I2C_SpecialCmdConfig(I2C_TypeDef * I2Cx, uint32_t SpecialCmd);
void I2C_TARConfig(I2C_TypeDef * I2Cx, uint32_t TarAddr);
void I2C_SARConfig(I2C_TypeDef * I2Cx, uint32_t SarAddr);
void I2C_HSMasterCodeConfig(I2C_TypeDef * I2Cx, uint32_t HSMasterCode);
void I2C_SCLKCountConfig(I2C_TypeDef * I2Cx, uint32_t HCNT, uint32_t LCNT, uint32_t ClockSpeed);
void I2C_SDASetupConfig(I2C_TypeDef * I2Cx, uint32_t SU_DAT);
void I2C_SendData(I2C_TypeDef * I2Cx, uint8_t Data);
void I2C_TriggerRecData(I2C_TypeDef * I2Cx);
uint8_t I2C_ReceiveData(I2C_TypeDef * I2Cx);
void I2C_RxFIFOThresholdConfig(I2C_TypeDef * I2Cx, uint32_t I2C_RxFIFOThreshold);
void I2C_TxFIFOThresholdConfig(I2C_TypeDef * I2Cx, uint32_t I2C_TxFIFOThreshold);
uint32_t I2C_GetTransmissionFIFONum(I2C_TypeDef * I2Cx);
uint32_t I2C_GetReceptionFIFONum(I2C_TypeDef * I2Cx);
uint32_t I2C_GetSpeedMode(I2C_TypeDef * I2Cx);
void I2C_NACKCmd(I2C_TypeDef * I2Cx, FunctionalState NewState);
void I2C_ACKGenCallCmd(I2C_TypeDef * I2Cx, FunctionalState NewState);
void I2C_ITConfig(I2C_TypeDef * I2Cx, uint32_t I2C_IT, FunctionalState NewState);
ITStatus I2C_GetITFlag(I2C_TypeDef * I2Cx, uint32_t I2C_IT);
ITStatus I2C_GetRawITFlag(I2C_TypeDef * I2Cx, uint32_t I2C_IT);
uint32_t I2C_GetTXAbortSource(I2C_TypeDef * I2Cx);
void I2C_ClearITPendingBit(I2C_TypeDef * I2Cx, uint32_t I2C_CLEAR_IT);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef * I2Cx, uint32_t I2C_FLAG);

#ifdef __cplusplus
}
#endif

#endif /*__VTM071x_I2C_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT MIC *****END OF FILE****/
