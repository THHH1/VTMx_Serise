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
#ifndef __VTM071x_GPIO_H
#define __VTM071x_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/* Exported types ------------------------------------------------------------*/
#define	GPIO0                               0x00000000
#define	GPIO1                               0x00000001
#define	GPIO2                               0x00000002
#define	GPIO3                               0x00000003
#define	GPIO4                               0x00000004
#define GPIO5                               0x00000005
#define GPIO6                               0x00000006

#define IS_GPIO_ALL_PERIPH(PERIPH)          (((PERIPH) == GPIO0)    || \
                                             ((PERIPH) == GPIO1)    || \
                                             ((PERIPH) == GPIO2)    || \
                                             ((PERIPH) == GPIO3)    || \
                                             ((PERIPH) == GPIO4)    || \
                                             ((PERIPH) == GPIO5)    || \
                                             ((PERIPH) == GPIO6))


/** @defgroup Configuration_Mode_enumeration 
  * @{
  */
typedef enum
{
    GPIO_Mode_AN   = 0x00,    /*!< GPIO Analog In/Out Mode        */
    GPIO_Mode_AF_1 = 0x01,    /*!< GPIO Alternate function Mode 1 */
    GPIO_Mode_AF_2 = 0x02,    /*!< GPIO Alternate function Mode 2 */
    GPIO_Mode_AF_3 = 0x03,    /*!< GPIO Alternate function Mode 3 */
    GPIO_Mode_IN   = 0x04,    /*!< GPIO Input Mode                */
    GPIO_Mode_OUT  = 0x05     /*!< GPIO Output Mode               */
}GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE)                 (((MODE) == GPIO_Mode_IN)    || ((MODE) == GPIO_Mode_OUT)    || \
                                            ((MODE) == GPIO_Mode_AF_1)  || ((MODE) == GPIO_Mode_AF_2)   || \
                                            ((MODE) == GPIO_Mode_AF_3)  || ((MODE) == GPIO_Mode_AN))
/**
  * @}
  */

/** @defgroup Output_Maximum_frequency_enumeration 
  * @{
  */
typedef enum
{
    GPIO_Speed_Level_1  = 0x01,     /*!< I/O output speed: Low 10 MHz */
    GPIO_Speed_Level_2  = 0x00,     /*!< I/O output speed: High 50 MHz */
}GPIOSpeed_TypeDef;

#define IS_GPIO_SPEED(SPEED)                (((SPEED) == GPIO_Speed_Level_1) || ((SPEED) == GPIO_Speed_Level_2))
/**
  * @}
  */

/** @defgroup Configuration_Pull-Up_Pull-Down_enumeration 
  * @{
  */
typedef enum
{
    GPIO_PuPd_NOPULL = 0x00,
    GPIO_PuPd_DOWN   = 0x01,
    GPIO_PuPd_UP     = 0x02
}GPIOPuPd_TypeDef;

#define IS_GPIO_PUPD(PUPD)                  (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                                             ((PUPD) == GPIO_PuPd_DOWN))
/**
  * @}
  */

/** @defgroup Bit_SET_and_Bit_RESET_enumeration
  * @{
  */
typedef enum
{ 
    Bit_RESET = 0,
    Bit_SET
}BitAction;

#define IS_GPIO_BIT_ACTION(ACTION)          (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))
/**
  * @}
  */

/** 
  * @brief  GPIO Init structure definition  
  */
typedef struct
{
    uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                         This parameter can be any value of @ref GPIO_pins_define */
                                         
    GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                         This parameter can be a value of @ref GPIOMode_TypeDef   */

    GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
                                         This parameter can be a value of @ref GPIOSpeed_TypeDef  */

    GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                         This parameter can be a value of @ref GPIOPuPd_TypeDef   */
}GPIO_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants
  * @{
  */

/** @defgroup GPIO_pins_define 
  * @{
  */
#define GPIO_Pin_0                          ((uint32_t)0x00000000)  /*!< Pin 0 selected */
#define GPIO_Pin_1                          ((uint32_t)0x00000001)  /*!< Pin 1 selected */
#define GPIO_Pin_2                          ((uint32_t)0x00000002)  /*!< Pin 2 selected */
#define GPIO_Pin_3                          ((uint32_t)0x00000003)  /*!< Pin 3 selected */
#define GPIO_Pin_4                          ((uint32_t)0x00000004)  /*!< Pin 4 selected */
#define GPIO_Pin_5                          ((uint32_t)0x00000005)  /*!< Pin 5 selected */
#define GPIO_Pin_6                          ((uint32_t)0x00000006)  /*!< Pin 6 selected */
#define GPIO_Pin_7                          ((uint32_t)0x00000007)  /*!< Pin 7 selected */
#define IS_GPIO_PIN(PIN)                   (((PIN) == GPIO_Pin_0) || \
                                            ((PIN) == GPIO_Pin_1) || \
                                            ((PIN) == GPIO_Pin_2) || \
                                            ((PIN) == GPIO_Pin_3) || \
                                            ((PIN) == GPIO_Pin_4) || \
                                            ((PIN) == GPIO_Pin_5) || \
                                            ((PIN) == GPIO_Pin_6) || \
                                            ((PIN) == GPIO_Pin_7))

#define IS_GET_GPIO_PIN(PIN)               (((PIN) == GPIO_Pin_0) || \
                                            ((PIN) == GPIO_Pin_1) || \
                                            ((PIN) == GPIO_Pin_2) || \
                                            ((PIN) == GPIO_Pin_3) || \
                                            ((PIN) == GPIO_Pin_4) || \
                                            ((PIN) == GPIO_Pin_5) || \
                                            ((PIN) == GPIO_Pin_6) || \
                                            ((PIN) == GPIO_Pin_7))
/**
  * @}
  */

/** @defgroup GPIO_Filter_Cycles 
  * @{
  */
#define IS_GPIO_FILTER_CYCLES(CYCLES)       (((CYCLES) > 0) && ((CYCLES) < 256))
/**
  * @}
  */

/** 
  * @brief  Configuration Edge Action enumeration  
  */
typedef enum
{
	GPIO_IT_EDGE_FALLING = 0,
	GPIO_IT_EDGE_RISING  = 1,
	GPIO_IT_EDGE_DOUBLE  = 2,
	GPIO_IT_LEVEL_LOW   = 3,
	GPIO_IT_LEVEL_HIGH  = 4
}ITAction;

#define IS_GPIO_IT_ACTION(ACTION)          (((ACTION) == GPIO_IT_EDGE_FALLING)  || \
                                            ((ACTION) == GPIO_IT_EDGE_RISING)   || \
                                            ((ACTION) == GPIO_IT_EDGE_DOUBLE)   || \
                                            ((ACTION) == GPIO_IT_LEVEL_LOW)     || \
                                            ((ACTION) == GPIO_IT_LEVEL_HIGH))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GPIO_DeInit(void);
void GPIO_Init(uint32_t GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_ANAConfig(uint32_t GPIOx, uint32_t GPIO_Pin, FunctionalState NewState);
uint8_t GPIO_ReadData(uint32_t GPIOx);
uint8_t GPIO_ReadDataBit(uint32_t GPIOx, uint32_t GPIO_Pin);
void GPIO_WriteBit(uint32_t GPIOx, uint32_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(uint32_t GPIOx, uint8_t PortVal);
void GPIO_Write_Port0_1(uint16_t SetVal, uint16_t ClearVal);
void GPIO_Write_Port2_3(uint16_t SetVal, uint16_t ClearVal);
void GPIO_Write_Port4_5(uint16_t SetVal, uint16_t ClearVal);
void GPIO_Write_Port6_7(uint16_t SetVal, uint16_t ClearVal);
void GPIO_Write_Port8_9(uint16_t SetVal, uint16_t ClearVal);
void GPIO_Write_Port10_11(uint16_t SetVal, uint16_t ClearVal);
void GPIO_FilterConfig(uint32_t Cycles, FunctionalState NewState);
void GPIO_Write_Port0_1(uint16_t SetVal, uint16_t ClearVal);
void GPIO_Write_Port2_3(uint16_t SetVal, uint16_t ClearVal);
void GPIO_Write_Port4_5(uint16_t SetVal, uint16_t ClearVal);
void GPIO_Write_Port6_7(uint16_t SetVal, uint16_t ClearVal);
void GPIO_ITConfig(uint32_t GPIOx, uint32_t GPIO_Pin, uint32_t GPIO_IT, FunctionalState NewState);
ITStatus GPIO_GetITStatus(uint32_t GPIOx, uint32_t GPIO_Pin);
void GPIO_ClearITPendingBit(uint32_t GPIOx, uint32_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif /* __VTM071x_GPIO_H */
/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT MIC *****END OF FILE****/

