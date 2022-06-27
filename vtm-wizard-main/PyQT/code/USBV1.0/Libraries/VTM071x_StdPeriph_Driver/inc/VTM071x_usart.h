/**
  ******************************************************************************
  * @file    VTM071x_usart.h
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the USART 
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
#ifndef __VTM071x_USART_H
#define __VTM071x_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  USART Init Structure definition  
  */ 
typedef struct
{
	uint32_t USART_TXIFLSEL;

	uint32_t USART_RXIFLSEL;

	uint32_t USART_FEN;

	uint32_t USART_BaudRate;
	
	uint32_t USART_WordLength;          
	
	uint32_t USART_StopBits;           
	
	uint32_t USART_Parity;              
	
	uint32_t USART_Mode;               
	
	uint32_t USART_HardwareFlowControl; 

	uint32_t USART_SoftwareFlowControl;

} USART_InitTypeDef;

/** 
  * @brief  USART RS485 Init Structure definition  
  */ 
typedef struct
{

  uint8_t USART_RS485_MODE;   

  uint8_t USART_RS485_DCTRL; 

  uint8_t USART_RS485_ONIV;

} USART_RS485InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup USART_Exported_Constants
  * @{
  */ 
#define IS_USART_ALL_PERIPH(PERIPH)         (((PERIPH) == USART0)   || \
                                             ((PERIPH) == USART1))

#define IS_USART_FC_PERIPH(PERIPH)          (((PERIPH) == USART0)   || \
                                             ((PERIPH) == USART1))

#define IS_USART_IRDA_PERIPH(PERIPH)        (((PERIPH) == USART0)   || \
                                             ((PERIPH) == USART1))

#define IS_USART_DMA_PERIPH(PERIPH)         (((PERIPH) == USART0)   || \
                                             ((PERIPH) == USART1))

/** @defgroup USART_Word_Length 
  * @{
  */ 
#define USART_WordLength_5b                 ((uint32_t)0x00000000)
#define USART_WordLength_6b                 ((uint32_t)0x00000020)
#define USART_WordLength_7b                 ((uint32_t)0x00000040)
#define USART_WordLength_8b                 ((uint32_t)0x00000060)
#define IS_USART_WORD_LENGTH(LENGTH)      (((LENGTH) == USART_WordLength_5b)   || \
                                            ((LENGTH) == USART_WordLength_6b)  || \
                                            ((LENGTH) == USART_WordLength_7b)  || \
                                            ((LENGTH) == USART_WordLength_8b))
/**
  * @}
  */ 

/** @defgroup USART_Stop_Bits 
  * @{
  */ 
#define USART_StopBits_1                    ((uint32_t)0x00000000)
#define USART_StopBits_2                    ((uint32_t)0x00000008)
#define IS_USART_STOPBITS(STOPBITS)        (((STOPBITS) == USART_StopBits_1)    || \
                                            ((STOPBITS) == USART_StopBits_2))
/**
  * @}
  */ 

/** @defgroup USART_Parity 
  * @{
  */ 
#define USART_Parity_No                     ((uint32_t)0x00000000)
#define USART_Parity_Odd                    ((uint32_t)0x00000002)
#define USART_Parity_Even                   ((uint32_t)0x00000006)
#define USART_Parity_EPS_1                  ((uint32_t)0x00000082)
#define USART_Parity_EPS_0                  ((uint32_t)0x00000086)
 
#define IS_USART_PARITY(PARITY)            (((PARITY) == USART_Parity_No)       || \
                                            ((PARITY) == USART_Parity_Even)     || \
                                            ((PARITY) == USART_Parity_Odd)      || \
                                            ((PARITY) == USART_Parity_EPS_0)    || \
                                            ((PARITY) == USART_Parity_EPS_1))
/**
  * @}
  */ 

/** @defgroup USART_Mode 
  * @{
  */ 
#define USART_Mode_Tx                       ((uint32_t)0x00000100)
#define USART_Mode_Rx                       ((uint32_t)0x00000200)
#define IS_USART_MODE(MODE)                (((MODE) == USART_Mode_Tx) || \
                                            ((MODE) == USART_Mode_Rx) || \
                                            ((MODE) == (USART_Mode_Rx|USART_Mode_Tx)))
/**
  * @}
  */ 

/** @defgroup USART_Hardware_Flow_Control 
  * @{
  */ 
#define USART_HardwareFlowControl_None      ((uint32_t)0x00000000)
#define USART_HardwareFlowControl_RTS       ((uint32_t)0x00004000)
#define USART_HardwareFlowControl_CTS       ((uint32_t)0x00008000)
#define USART_HardwareFlowControl_RTS_CTS   ((uint32_t)0x0000C000)
#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)\
                                           (((CONTROL) == USART_HardwareFlowControl_None) || \
                                            ((CONTROL) == USART_HardwareFlowControl_RTS)  || \
                                            ((CONTROL) == USART_HardwareFlowControl_CTS)  || \
                                            ((CONTROL) == USART_HardwareFlowControl_RTS_CTS))
/**
  * @}
  */ 

/** @defgroup SoftwareFlowControl 
  * @{
  */ 
#define USART_SoftwareFlowControl_None      ((uint32_t)0x00000000)
#define USART_SoftwareFlowControl_RTS       ((uint32_t)0x00000800)
#define IS_USART_SoftwareFlowControl(CONTROL) \
                                           (((CONTROL) == USART_SoftwareFlowControl_None) || \
                                            ((CONTROL) == USART_SoftwareFlowControl_RTS))
/**
  * @}
  */ 

/** @defgroup USART_TXIFLSEL 
  * @{
  */ 
#define USART_TXIFLSEL_4                    ((uint32_t)0x00000000)
#define USART_TXIFLSEL_8                    ((uint32_t)0x00010000)
#define USART_TXIFLSEL_16                   ((uint32_t)0x00020000)
#define USART_TXIFLSEL_24                   ((uint32_t)0x00030000)
#define USART_TXIFLSEL_28                   ((uint32_t)0x00040000)
#define IS_USART_TXIFLSEL(TXIFLSEL)        (((TXIFLSEL) == USART_TXIFLSEL_4)    || \
                                            ((TXIFLSEL) == USART_TXIFLSEL_8)    || \
                                            ((TXIFLSEL) == USART_TXIFLSEL_16)   || \
                                            ((TXIFLSEL) == USART_TXIFLSEL_24)   || \
                                            ((TXIFLSEL) == USART_TXIFLSEL_28))
/**
  * @}
  */ 

/** @defgroup USART_RXIFLSEL 
  * @{
  */ 
#define USART_RXIFLSEL_4                    ((uint32_t)0x00000000)
#define USART_RXIFLSEL_8                    ((uint32_t)0x00100000)
#define USART_RXIFLSEL_16                   ((uint32_t)0x00200000)
#define USART_RXIFLSEL_24                   ((uint32_t)0x00300000)
#define USART_RXIFLSEL_28                   ((uint32_t)0x00400000)
#define IS_USART_RXIFLSEL(RXIFLSEL)        (((RXIFLSEL) == USART_RXIFLSEL_4)    || \
                                            ((RXIFLSEL) == USART_RXIFLSEL_8)    || \
                                            ((RXIFLSEL) == USART_RXIFLSEL_16)   || \
                                            ((RXIFLSEL) == USART_RXIFLSEL_24)   || \
                                            ((RXIFLSEL) == USART_RXIFLSEL_28))
/**
  * @}
  */ 

/** @defgroup USART_FEN 
  * @{
  */ 
#define USART_FEN_Enable                    ((uint32_t)0x00000010)
#define USART_FEN_Disable                   ((uint32_t)0x00000000)
#define IS_USART_FEN(STATE)                (((STATE) == USART_FEN_Enable) || \
                                            ((STATE) == USART_FEN_Disable))
/**
  * @}
  */ 

/** @defgroup USART_RS485_NMM 
  * @{
  */ 
#define USART_RS485_NMM_MAD                 ((uint8_t)0x03)
#define USART_RS485_NMM_AAD                 ((uint8_t)0x07)
#define USART_RS485_NMM_Disable             ((uint8_t)0x00)
#define IS_USART_RS485_NMM(MODE)           (((MODE) == USART_RS485_NMM_MAD) || \
                                            ((MODE) == USART_RS485_NMM_AAD) || \
                                            ((MODE) == USART_RS485_NMM_Disable))
/**
  * @}
  */ 

/** @defgroup USART_RS485_DCTRL 
  * @{
  */ 
#define USART_RS485_DCTRL_RTS               ((uint8_t)0x10)
#define USART_RS485_DCTRL_DTR               ((uint8_t)0x18)
#define USART_RS485_DCTRL_DISABLE           ((uint8_t)0x00)
#define IS_USART_RS485_DCTRL(MODE)         (((MODE) == USART_RS485_DCTRL_RTS) || \
                                            ((MODE) == USART_RS485_DCTRL_DTR) || \
                                            ((MODE) == USART_RS485_DCTRL_DISABLE))
/**
  * @}
  */ 

/** @defgroup USART_RS485_ONIV 
  * @{
  */ 
#define USART_RS485_ONIV_MODE_0             ((uint8_t)0x20)
#define USART_RS485_ONIV_MODE_1             ((uint8_t)0x00)
#define IS_USART_RS485_ONIV_MODE(MODE)     (((MODE) == USART_RS485_ONIV_MODE_0) || \
                                            ((MODE) == USART_RS485_ONIV_MODE_1))
/**
  * @}
  */ 

/** @defgroup USART_AUTOBAUD_MODE 
  * @{
  */ 
#define USART_AUTOBAUD_MODE_RE_0            ((uint16_t)0x0004)
#define USART_AUTOBAUD_MODE_RE_1            ((uint16_t)0x0006)
#define USART_AUTOBAUD_MODE_RD_0            ((uint16_t)0x0000)
#define USART_AUTOBAUD_MODE_RD_1            ((uint16_t)0x0002)
#define IS_USART_AUTOBAUD_MODE(MODE)       (((MODE) == USART_AUTOBAUD_MODE_RE_0)  || \
                                            ((MODE) == USART_AUTOBAUD_MODE_RE_1)  || \
                                            ((MODE) == USART_AUTOBAUD_MODE_RD_0)  || \
                                            ((MODE) == USART_AUTOBAUD_MODE_RD_1))
/**
  * @}
  */ 

/** @defgroup USART_Interrupt_definition 
  * @{
  */
#define USART_IT_LBDIE                      ((uint32_t)0x00000008)
#define USART_IT_RXTOEN                     ((uint32_t)0x80100000)
#define USART_IT_CTSMIEN                    ((uint32_t)0x00020000)
#define USART_IT_RXIEN                      ((uint32_t)0x00100000)
#define USART_IT_TXIEN                      ((uint32_t)0x00200000)
#define USART_IT_FEIEN                      ((uint32_t)0x00800000)
#define USART_IT_PEIEN                      ((uint32_t)0x01000000)
#define USART_IT_BEIEN                      ((uint32_t)0x02000000)
#define USART_IT_OEIEN                      ((uint32_t)0x04000000)
#define USART_IT_TFEIEN                     ((uint32_t)0x08000000)
#define USART_IT_ABEOEN                     ((uint32_t)0x10000000)
#define USART_IT_ABTOEN                     ((uint32_t)0x20000000)
#define USART_IT_RXTOFLAG                   ((uint32_t)0x80000000)
#define IS_USART_CONFIG_IT(IT)             (((((IT) & ((uint32_t)0x3FB00008)) != 0) && (((IT) & ((uint32_t)0x404FFFFF)) == 0)) || \
                                            ((IT) == USART_IT_RXTOEN))

#define USART_IT_LBDIS                      ((uint32_t)0x40000010)
#define USART_IT_RXTOIS                     ((uint32_t)0x00200000)
#define USART_IT_CTSMIS                     ((uint32_t)0x00000002)
#define USART_IT_RXIS                       ((uint32_t)0x00000010)
#define USART_IT_TXIS                       ((uint32_t)0x00000020)
#define USART_IT_FEIS                      	((uint32_t)0x00000080)
#define USART_IT_PEIS                      	((uint32_t)0x00000100)
#define USART_IT_BEIS                      	((uint32_t)0x00000200)
#define USART_IT_OEIS                      	((uint32_t)0x00000400)
#define USART_IT_TFEIS                      ((uint32_t)0x00000800)
#define USART_IT_ABEO                      	((uint32_t)0x00001000)
#define USART_IT_ABTO                      	((uint32_t)0x00002000)
#define USART_IT_ABEOIntClr                 (((uint32_t)0x00000100) << 16)
#define USART_IT_ABTOIntClr                 (((uint32_t)0x00000200) << 16)
#define USART_IT_LINFLAG                    ((uint32_t)0x40000000)

#define IS_USART_GET_IT(IT)                (((IT) == USART_IT_RXIS)  || ((IT) == USART_IT_TXIS)   || \
                                            ((IT) == USART_IT_CTSMIS)  || ((IT) == USART_IT_FEIS)   || \
                                            ((IT) == USART_IT_PEIS)  || ((IT) == USART_IT_BEIS)   || \
                                            ((IT) == USART_IT_OEIS)  || ((IT) == USART_IT_TFEIS)  || \
                                            ((IT) == USART_IT_ABEO)  || ((IT) == USART_IT_ABTO)   || \
                                            ((IT) == USART_IT_LBDIS) || ((IT) == USART_IT_RXTOIS))

#define IS_USART_CLEAR_IT(IT)               ((((IT) & 0x30203FF2) != 0) && (((IT) & 0x8FDFC00D) == 0))
/**
  * @}
  */

/** @defgroup USART_WakeUp_methods
  * @{
  */
#define USART_WakeUp_IdleLine               ((uint16_t)0x0000)
#define USART_WakeUp_AddressMark            ((uint16_t)0x0800)
#define IS_USART_WAKEUP(WAKEUP)            (((WAKEUP) == USART_WakeUp_IdleLine) || \
                                            ((WAKEUP) == USART_WakeUp_AddressMark))
/**
  * @}
  */

/** @defgroup USART_LIN_Break_Detection_Length 
  * @{
  */
#define USART_LINBreakDetectLength_10b      ((uint16_t)0x0000)
#define USART_LINBreakDetectLength_11b      ((uint16_t)0x0020)
#define IS_USART_LIN_BREAK_DETECT_LENGTH(LENGTH) \
                                           (((LENGTH) == USART_LINBreakDetectLength_10b)  || \
                                            ((LENGTH) == USART_LINBreakDetectLength_11b))
/**
  * @}
  */

/** @defgroup USART_IrDA_Low_Power 
  * @{
  */
#define USART_IrDAMode_LowPower             ((uint32_t)0x00000040)
#define USART_IrDAMode_Normal               ((uint32_t)0x00000000)
#define IS_USART_IRDA_MODE(MODE)           (((MODE) == USART_IrDAMode_LowPower) || \
                                            ((MODE) == USART_IrDAMode_Normal))
/**
  * @}
  */ 

/** @defgroup USART_Flags 
  * @{
  */
#define USART_FLAG_FERR                     ((uint32_t)0x00010000)
#define USART_FLAG_PERR                     ((uint32_t)0x00020000)
#define USART_FLAG_BERR                     ((uint32_t)0x00040000)
#define USART_FLAG_OERR                     ((uint32_t)0x00080000)
#define USART_FLAG_RXFE                     ((uint32_t)0x01000000)
#define USART_FLAG_TXFF                     ((uint32_t)0x02000000)
#define USART_FLAG_RXFF                     ((uint32_t)0x04000000)
#define USART_FLAG_TXFE                 		((uint32_t)0x08000000)
#define USART_FLAG_CTS                      ((uint32_t)0x10000000)
#define USART_FLAG_BUSY                     ((uint32_t)0x20000000)
#define IS_USART_FLAG(FLAG)                (((FLAG) == USART_FLAG_FERR) || ((FLAG) == USART_FLAG_PERR) || \
                                            ((FLAG) == USART_FLAG_BERR) || ((FLAG) == USART_FLAG_OERR) || \
                                            ((FLAG) == USART_FLAG_RXFE) || ((FLAG) == USART_FLAG_TXFF) || \
                                            ((FLAG) == USART_FLAG_RXFF) || ((FLAG) == USART_FLAG_TXFE) || \
                                            ((FLAG) == USART_FLAG_CTS)  || ((FLAG) == USART_FLAG_BUSY))

#define IS_USART_CLEAR_FLAG(FLAG)           ((((FLAG)&0xFFF0FFFF) == 0) && (((FLAG)&0x000F0000) != 0))

#define IS_USART_PERIPH_FLAG(PERIPH, USART_FLAG)  \
                                           ((((*(uint32_t*)&(PERIPH)) != USART4_BASE) && \
                                            ((*(uint32_t*)&(PERIPH)) != USART5_BASE)) || \
                                            ((USART_FLAG) != USART_FLAG_CTS))
#define IS_USART_BAUDRATE(BAUDRATE)        (((BAUDRATE) > 0) && ((BAUDRATE) < 0x0016E361))
#define IS_USART_ILPDVSR(ILPDVSR)          (((ILPDVSR) <= 0xFF) && ((ILPDVSR)>0))
#define IS_USART_RS485ADDRESS(ADDRESS)     (((ADDRESS) <= 0xFF) && ((ADDRESS)>0))
/**
  * @}
  */ 

/** @defgroup USART_RXTOCOUNT
  * @{
  */
#define IS_USART_RXTOCOUNT(COUNT)           ((((COUNT) & 0xFFF00000) == 0) && (((COUNT)&0x000FFFFF) != 0))
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState);
void USART_SendData(USART_TypeDef* USARTx, uint8_t Data);
uint32_t USART_ReceiveData(USART_TypeDef* USARTx);
void USART_IrDAConfig(USART_TypeDef* USARTx, uint32_t USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_RS485Init(USART_TypeDef* USARTx, USART_RS485InitTypeDef* USART_RS485InitStruct);
void USART_RS485StructInit(USART_RS485InitTypeDef* USART_RS485InitStruct);
void USART_RS485SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);
void USART_RS485SetDelay(USART_TypeDef* USARTx, uint8_t USART_DLYTime);
void USART_AUTOBAUDConfig(USART_TypeDef* USARTx, uint16_t USART_AUTOBAUDMODE);
void USART_AUTOBAUDCmd(USART_TypeDef* USARTx, FunctionalState NewState);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint32_t USART_IT);
void USART_LBECmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_BRKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_TXDMACmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_RXDMACmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SendBreak(USART_TypeDef* USARTx);
void USART_STTTOCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_RETTOCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_RXTOCountConfig(USART_TypeDef* USARTx, uint32_t RXTO_Count);

#ifdef __cplusplus
}
#endif

#endif /* __VTM071x_USART_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT MIC *****END OF FILE****/
