/**
  ******************************************************************************
  * @file    VTM071x_spi.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the SPI firmware
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
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VTM071x_SPI_H
#define __VTM071x_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  SPI Init structure definition  
  */
typedef struct
{
    uint32_t SPI_Mode;                  /*!< Specifies the SPI mode (Master/Slave).
                                            This parameter can be a value of @ref SPI_mode */

    uint32_t SPI_Direction;             /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                            This parameter can be a value of @ref SPI_data_direction */
    
	uint32_t SPI_DataSize;              /*!< Specifies the SPI data size.
                                            This parameter can be a value of @ref SPI_data_size */

	uint32_t SPI_CPOL;                  /*!< Specifies the serial clock steady state.
                                            This parameter can be a value of @ref SPI_Clock_Polarity */

	uint32_t SPI_CPHA;                  /*!< Specifies the clock active edge for the bit capture.
                                            This parameter can be a value of @ref SPI_Clock_Phase */

	uint32_t SPI_BaudRatePrescaler;     /*!< Specifies the Baud Rate prescaler value which will be
                                            used to configure the transmit and receive SCK clock.
                                            This parameter can be a value of @ref SPI_BaudRate_Prescaler */
                                            
    uint32_t SPI_FirstBit;              /*!< Specifies whether data transfers start from MSB or LSB bit.
                                            This parameter can be a value of @ref SPI_MSB_LSB_transmission */
}SPI_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  * @{
  */

#define IS_SPI_ALL_PERIPH(PERIPH)           (((PERIPH) == SPI0) || ((PERIPH) == SPI1))

/** @defgroup SPI_mode 
  * @{
  */
#define SPI_MODE_MASTER 		            ((uint32_t)0x00000000)
#define SPI_MODE_SLAVE     		            ((uint32_t)0x00000004)
#define IS_SPI_MODE(MODE)                  (((MODE) == SPI_MODE_MASTER) || \
                                            ((MODE) == SPI_MODE_SLAVE))
/**
  * @}
  */

/** @defgroup SPI_MSB_LSB_transmission 
  * @{
  */
#define SPI_FirstBit_MSB                    ((uint32_t)0x00000000)
#define SPI_FirstBit_LSB                    ((uint32_t)0x00000008)
#define IS_SPI_FIRST_BIT(BIT)              (((BIT) == SPI_FirstBit_MSB) || \
                                            ((BIT) == SPI_FirstBit_LSB))
/**
  * @}
  */

/** @defgroup SPI_data_direction 
  * @{
  */
  
#define SPI_Direction_2Lines_FullDuplex     ((uint32_t)0x00000000)
#define SPI_Direction_1Line_Rx              ((uint32_t)0x00000040)
#define SPI_Direction_1Line_Tx              ((uint32_t)0x00000020)
#define IS_SPI_DIRECTION_MODE(MODE)        (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                            ((MODE) == SPI_Direction_1Line_Rx) || \
                                            ((MODE) == SPI_Direction_1Line_Tx))
/**
  * @}
  */

/** @defgroup SPI_data_size
  * @{
  */

#define SPI_DataSize_4b                     ((uint32_t)0x00000003)
#define SPI_DataSize_5b                     ((uint32_t)0x00000004)
#define SPI_DataSize_6b                     ((uint32_t)0x00000005)
#define SPI_DataSize_7b                     ((uint32_t)0x00000006)
#define SPI_DataSize_8b                     ((uint32_t)0x00000007)
#define SPI_DataSize_9b                     ((uint32_t)0x00000008)
#define SPI_DataSize_10b                    ((uint32_t)0x00000009)
#define SPI_DataSize_11b                    ((uint32_t)0x0000000A)
#define SPI_DataSize_12b                    ((uint32_t)0x0000000B)
#define SPI_DataSize_13b                    ((uint32_t)0x0000000C)
#define SPI_DataSize_14b                    ((uint32_t)0x0000000D)
#define SPI_DataSize_15b                    ((uint32_t)0x0000000E)
#define SPI_DataSize_16b                    ((uint32_t)0x0000000F)
#define IS_SPI_DATA_SIZE(SIZE)             (((SIZE) == SPI_DataSize_4b) || \
                                            ((SIZE) == SPI_DataSize_5b) || \
                                            ((SIZE) == SPI_DataSize_6b) || \
                                            ((SIZE) == SPI_DataSize_7b) || \
                                            ((SIZE) == SPI_DataSize_8b) || \
                                            ((SIZE) == SPI_DataSize_9b) || \
                                            ((SIZE) == SPI_DataSize_10b) || \
                                            ((SIZE) == SPI_DataSize_11b) || \
                                            ((SIZE) == SPI_DataSize_12b) || \
                                            ((SIZE) == SPI_DataSize_13b) || \
                                            ((SIZE) == SPI_DataSize_14b) || \
                                            ((SIZE) == SPI_DataSize_15b) || \
                                            ((SIZE) == SPI_DataSize_16b))

/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity 
  * @{
  */

#define SPI_CPOL_Low                        ((uint32_t)0x00000000)
#define SPI_CPOL_High                       ((uint32_t)0x00000040)
#define IS_SPI_CPOL(CPOL)                  (((CPOL) == SPI_CPOL_Low) || \
                                            ((CPOL) == SPI_CPOL_High))

/**
  * @}
  */

/** @defgroup SPI_Clock_Phase 
  * @{
  */

#define SPI_CPHA_1Edge                      ((uint32_t)0x00000000)
#define SPI_CPHA_2Edge                      ((uint32_t)0x00000080)
#define IS_SPI_CPHA(CPHA)                  (((CPHA) == SPI_CPHA_1Edge) || \
                                            ((CPHA) == SPI_CPHA_2Edge))

/**
  * @}
  */

/** @defgroup SPI_BaudRate_Prescaler 
  * @{
  */

#define SPI_BaudRatePrescaler_2             ((uint32_t)0x00000002)
#define SPI_BaudRatePrescaler_4             ((uint32_t)0x00000004)
#define SPI_BaudRatePrescaler_6             ((uint32_t)0x00000006)
#define SPI_BaudRatePrescaler_8        	    ((uint32_t)0x00000008)
#define SPI_BaudRatePrescaler_10            ((uint32_t)0x0000000A)
#define SPI_BaudRatePrescaler_12            ((uint32_t)0x0000000C)
#define SPI_BaudRatePrescaler_14       	    ((uint32_t)0x0000000E)
#define SPI_BaudRatePrescaler_16       	    ((uint32_t)0x00000010)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) <= 254) && ((PRESCALER) % 2 == 0))

/**
  * @}
  */

/** @defgroup SPI_FLAG
  * @{
  */
#define	SPI_STATUS_Transmit_FIFO_Empty		((uint32_t)0x00000001)
#define	SPI_STATUS_Transmit_FIFO_Not_Full	((uint32_t)0x00000002)
#define	SPI_STATUS_Receive_FIFO_Not_Empty	((uint32_t)0x00000004)
#define	SPI_STATUS_Receive_FIFO_Full		((uint32_t)0x00000008)
#define	SPI_STATUS_SSP_BUSY			        ((uint32_t)0x00000010)
#define IS_SPI_FLAG(FLAG)	               (((FLAG) == SPI_STATUS_Transmit_FIFO_Empty)      || \
                                            ((FLAG) == SPI_STATUS_Transmit_FIFO_Not_Full)   || \
                                            ((FLAG) == SPI_STATUS_Receive_FIFO_Not_Empty)   || \
                                            ((FLAG) == SPI_STATUS_Receive_FIFO_Full)        || \
                                            ((FLAG) == SPI_STATUS_SSP_BUSY))

/**
  * @}
  */

/** @defgroup SPI_IT
  * @{
  */
#define	SPI_IT_RECEIVE_OVERRUN				((uint32_t)0x00000001)
#define	SPI_IT_RECEIVE_TIMEOUT				((uint32_t)0x00000002)
#define	SPI_IT_RECEIVE				        ((uint32_t)0x00000004)
#define	SPI_IT_TRANSMIT				        ((uint32_t)0x00000008)

#define	IS_SPI_CONFIG_IT(IT)               (((IT) != 0) && (((IT) & 0xFFFFFFF0) == 0))

#define	IS_SPI_GET_IT(IT)                  (((IT) == SPI_IT_RECEIVE_OVERRUN)    || \
                                            ((IT) == SPI_IT_RECEIVE_TIMEOUT)    || \
                                            ((IT) == SPI_IT_RECEIVE)            || \
                                            ((IT) == SPI_IT_TRANSMIT))

#define	IS_SPI_CLEAR_IT(IT)	               (((IT) == SPI_IT_RECEIVE_OVERRUN)    || \
                                            ((IT) == SPI_IT_RECEIVE_TIMEOUT))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void SPI_DeInit(SPI_TypeDef *SPIx);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_TxDMACmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void SPI_RxDMACmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef *SPIx, uint32_t SPI_DataSize);
uint32_t SPI_GetDataSize(SPI_TypeDef *SPIx);
void SPI_LoopBackCmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void SPI_SlaveOutputCmd(SPI_TypeDef *SPIx, FunctionalState NewState);

/* Data transfers functions ***************************************************/
void SPI_SendData(SPI_TypeDef *SPIx, uint16_t Data);
uint16_t SPI_ReceiveData(SPI_TypeDef *SPIx);

/* Interrupts and flags management functions **********************************/
FlagStatus SPI_GetFlagStatus(SPI_TypeDef *SPIx, uint32_t SPI_FLAG);
void SPI_ITConfig(SPI_TypeDef *SPIx, uint32_t SPI_IT, FunctionalState NewState);
ITStatus SPI_GetITStatusAfterMasking(SPI_TypeDef *SPIx, uint32_t SPI_IT);
ITStatus SPI_GetITStatusPriorToMasking(SPI_TypeDef *SPIx, uint32_t SPI_IT);
void SPI_ClearITPendingBit(SPI_TypeDef *SPIx, uint32_t SPI_IT);

#ifdef __cplusplus
}
#endif

#endif /* __VTM071x_SPI_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT MIC *****END OF FILE****/
