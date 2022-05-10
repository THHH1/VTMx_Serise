/**
  ******************************************************************************
  * @file    VTM071x_tim.h
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the TIMER firmware 
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
  ******************************************************************************  
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VTM071x_TIMER_H__
#define __VTM071x_TIMER_H__

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIMER
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup TIMER_Direction
  * @{
  */
typedef enum {
		TIMER_DIR_INCREASE = 0,
		TIMER_DIR_DECREASE = 1,
		TIMER_DIR_CENTER_ALIGN = 2
}TIMER_Direction;
#define IS_TIMER_Direction(DIR) (((DIR) == TIMER_DIR_INCREASE) || \
								((DIR) == TIMER_DIR_DECREASE) || \
								((DIR) == TIMER_DIR_CENTER_ALIGN))
/**
  * @}
  */ 

/** @defgroup TIMER_Match_Action
  * @{
  */
typedef enum {
    TIMER_MatchAction_HOLD    = 0,
    TIMER_MatchAction_OUTPUT0 = 1,
    TIMER_MatchAction_OUTPUT1 = 2,
    TIMER_MatchAction_TOGGLE  = 3
}TIMER_Match_Action;
#define IS_TIMER_Match_Action(Action) (((Action) == TIMER_MatchAction_HOLD)   || \
								      ((Action) == TIMER_MatchAction_OUTPUT0) || \
								      ((Action) == TIMER_MatchAction_OUTPUT1) || \
								      ((Action) == TIMER_MatchAction_TOGGLE))
/**
  * @}
  */ 

/** @defgroup TIMER_Match_Config
  * @{
  */
typedef enum {
    TIMER_MatchConfig_NONE     = 0,
    TIMER_MatchConfig_RESET_TC = 0x2,
    TIMER_MatchConfig_STOP     = 0x4
}TIMER_Match_Config;
#define IS_TIMER_Match_Config(Config)   (((Config) == TIMER_MatchConfig_NONE)    || \
                                        ((Config) == TIMER_MatchConfig_RESET_TC) || \
                                        ((Config) == TIMER_MatchConfig_STOP)     || \
                                        ((Config) == (TIMER_MatchConfig_RESET_TC | TIMER_MatchConfig_STOP)))
/**
  * @}
  */ 

/** 
  * @brief  TIMER Init structure definition
  */
typedef struct
{
    uint32_t TIMER_Channel;             /*!< Specifies the TIMER channel.
                                            This parameter can be a value of @ref Timer_Channel */

    uint32_t TIMER_Dir;                 /*!< Specifies the TIMER or COUNTER direction.
                                            This parameter can be a value of @ref TIMER_Direction */

    uint32_t TIMER_MatchValue;          /*!< Specifies the match value.
                                            This parameter can be a value between 0x00000000 and 0xFFFFFFFF */

    uint32_t TIMER_MatchAction;         /*!< Specifies the match action.
                                            This parameter can be a value of @ref TIMER_Match_Action */

    uint32_t TIMER_MatchConfig;         /*!< Specifies the match configuration.
                                            This parameter can be a value of @ref TIMER_Match_Config */
}TIMER_InitTypeDef;  


/** @defgroup COUNTERMODE
  * @{
  */
typedef enum {
    COUNTER_RISING_EDGE  = 1,
    COUNTER_FALLING_EDGE = 2,
    COUNTER_DOUBLE_EDGE  = 3
}COUNTERMODE;
#define IS_COUNTERMODE(Mode) (((Mode) == COUNTER_RISING_EDGE)   || \
						      ((Mode) == COUNTER_FALLING_EDGE) || \
						      ((Mode) == COUNTER_DOUBLE_EDGE))
/**
  * @}
  */ 

/** 
  * @brief  COUNTER Init structure definition
  */
typedef struct
{
    uint32_t TIMER_Channel;               /*!< Specifies the timer channel.
                                            This parameter can be a value of @ref Timer_Channel */

    uint32_t COUNTER_Mode;                /*!< Specifies the COUNTER mode.
                                            This parameter can be a value of @ref COUNTERMODE */
    
    uint32_t COUNTER_Dir;                 /*!< Specifies the TIMER or COUNTER direction.
                                            This parameter can be a value of @ref TIMER_Direction */

    uint32_t COUNTER_Pin;                 /*!< Specifies the Capture Pin.
                                            This parameter can be a value of @ref COUNTER_GPIO_Pin */

    uint32_t COUNTER_Filter;              /*!< Specifies the Capture filter.
                                            This parameter can be a value of @ref COUNTER_Filter_Cycles */

    uint32_t COUNTER_MatchValue;          /*!< Specifies the match value.
                                            This parameter can be a value between 0x00000000 and 0xFFFFFFFF */

    uint32_t COUNTER_MatchAction;         /*!< Specifies the match action.
                                            This parameter can be a value of @ref TIMER_Match_Action */

    uint32_t COUNTER_MatchConfig;         /*!< Specifies the match configuration.
                                            This parameter can be a value of @ref TIMER_Match_Config */
}COUNTER_InitTypeDef;


/** @defgroup PWM_Valid_State
  * @{
  */
typedef enum {
		PWM_ValidState_HIGH_LEVEL = 0,
		PWM_ValidState_HIGH_IMPEDANCE = 1
}PWM_Valid_State;
#define IS_PWM_ValidState(STATE) (((STATE) == PWM_ValidState_HIGH_LEVEL) || \
								  ((STATE) == PWM_ValidState_HIGH_IMPEDANCE))
/**
  * @}
  */ 

/** @defgroup PWM_Invalid_State
  * @{
  */
typedef enum {
		PWM_InvalidState_LOW_LEVEL = 0,
		PWM_InvalidState_HIGH_IMPEDANCE = 1
}PWM_Invalid_State;
#define IS_PWM_InvalidState(STATE) (((STATE) == PWM_InvalidState_LOW_LEVEL) || \
                                    ((STATE) == PWM_InvalidState_HIGH_IMPEDANCE))
/**
  * @}
  */ 

/** 
  * @brief  TIMER PWM Output Init structure definition  
  */
typedef struct
{
    uint32_t TIMER_Channel;         /*!< Specifies the timer channel.
                                        This parameter can be a value of @ref Timer_Channel */

    uint32_t PWM_Threshold;         /*!< Specifies the threshold value.
                                        This parameter can be a value between 0x00000000 and 0xFFFFFFFF */

    uint32_t PWM_MatchValue;        /*!< Specifies the match value.
                                        This parameter can be a value between 0x00000000 and 0xFFFFFFFF */

    uint32_t PWM_ValidState;        /*!< Specifies the valid state.
                                        This parameter can be a value of @ref PWM_ValidState */
                                        
    uint32_t PWM_InvalidState;      /*!< Specifies the invalid state.
                                        This parameter can be a value of @ref PWM_InvalidState */
}PWM_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup Timer_Exported_Constants
  * @{
  */

#define IS_TIMER_ALL_PERIPH(PERIPH) (((PERIPH) == TIMER0) || ((PERIPH) == TIMER1) || ((PERIPH) == TIMER2) || ((PERIPH) == TIMER3))

/** @defgroup Timer_Channel_SWITCH
  * @{
  */
#define Timer_Channel_0                     ((uint32_t)0x00000001)
#define Timer_Channel_1                     ((uint32_t)0x00000002)
#define Timer_Channel_2                     ((uint32_t)0x00000004)
#define Timer_Channel_3                     ((uint32_t)0x00000008)

#define IS_TIMER_CHANNEL_CONFIG(CHANNEL)    (((CHANNEL) == Timer_Channel_0) || \
                                            ((CHANNEL) == Timer_Channel_1)  || \
                                            ((CHANNEL) == Timer_Channel_2)  || \
                                            ((CHANNEL) == Timer_Channel_3))
#define IS_TIMER_CHANNEL_SWITCH(CHANNEL)    ((((CHANNEL) & 0xFFFFFFF0) == 0) && ((CHANNEL) != 0))
/**
  * @}
  */ 

/** @defgroup Timer_idle_level
  * @{
  */
#define Timer_IDLE_LEVEL_HOLD               ((uint32_t)0x00000000)
#define Timer_IDLE_LEVEL_LOW                ((uint32_t)0x00000001)
#define Timer_IDLE_LEVEL_HIGH               ((uint32_t)0x00000002)
#define Timer_IDLE_LEVEL_HIGH_RESISTANCE    ((uint32_t)0x00000003)

#define IS_TIMER_IDLE_LEVEL(LEVEL)         (((LEVEL) == Timer_Channel_0)  || \
                                            ((LEVEL) == Timer_Channel_1)  || \
                                            ((LEVEL) == Timer_Channel_2)  || \
                                            ((LEVEL) == Timer_Channel_3))
/**
  * @}
  */ 

/** @defgroup Timer_match_action
  * @{
  */
#define Timer_MATCH_ACTION_HOLD             ((uint32_t)0x00000000)
#define Timer_MATCH_ACTION_LOW              ((uint32_t)0x00000001)
#define Timer_MATCH_ACTION_HIGH             ((uint32_t)0x00000002)
#define Timer_MATCH_ACTION_TOG              ((uint32_t)0x00000003)

#define IS_TIMER_MATCH_ACTION(ACTION)      (((ACTION) == Timer_MATCH_ACTION_HOLD) || \
                                            ((ACTION) == Timer_MATCH_ACTION_LOW)  || \
                                            ((ACTION) == Timer_MATCH_ACTION_HIGH) || \
                                            ((ACTION) == Timer_MATCH_ACTION_TOG))
/**
  * @}
  */ 

/** @defgroup Timer_match_default_level
  * @{
  */
#define Timer_MATCH_DEFAULT_LEVEL_LOW       ((uint32_t)0x00000000)
#define Timer_MATCH_DEFAULT_LEVEL_HIGH      ((uint32_t)0x00000001)

#define IS_TIMER_MATCH_DEFAULT_LEVEL(LEVEL) (((LEVEL) == Timer_MATCH_DEFAULT_LEVEL_LOW) || \
                                            ((LEVEL) == Timer_MATCH_DEFAULT_LEVEL_HIGH))
/**
  * @}
  */ 

/** @defgroup COUNTER_GPIO_Pin
  * @{
  */
#define COUNTER_Pin_0                       ((uint32_t)0x00000000)
#define COUNTER_Pin_1                       ((uint32_t)0x00000001)

#define IS_COUNTER_GPIO_Pin(Pin)           (((Pin) == COUNTER_Pin_0) || ((Pin) == COUNTER_Pin_1))
/**
  * @}
  */ 

/** @defgroup COUNTER_Filter_Cycles
  * @{
  */
#define COUNTER_FILTER_CYCLES_0             ((uint32_t)0x00000000)
#define COUNTER_FILTER_CYCLES_1             ((uint32_t)0x00000001)
#define COUNTER_FILTER_CYCLES_2             ((uint32_t)0x00000002)
#define COUNTER_FILTER_CYCLES_3             ((uint32_t)0x00000003)
#define COUNTER_FILTER_CYCLES_4             ((uint32_t)0x00000004)
#define COUNTER_FILTER_CYCLES_5             ((uint32_t)0x00000005)
#define COUNTER_FILTER_CYCLES_6             ((uint32_t)0x00000006)
#define COUNTER_FILTER_CYCLES_7             ((uint32_t)0x00000007)
#define COUNTER_FILTER_CYCLES_8             ((uint32_t)0x00000008)
#define COUNTER_FILTER_CYCLES_9             ((uint32_t)0x00000009)
#define COUNTER_FILTER_CYCLES_10            ((uint32_t)0x0000000A)
#define COUNTER_FILTER_CYCLES_11            ((uint32_t)0x0000000B)
#define COUNTER_FILTER_CYCLES_12            ((uint32_t)0x0000000C)
#define COUNTER_FILTER_CYCLES_13            ((uint32_t)0x0000000D)
#define COUNTER_FILTER_CYCLES_14            ((uint32_t)0x0000000E)
#define COUNTER_FILTER_CYCLES_15            ((uint32_t)0x0000000F)

#define IS_COUNTER_Filter_Cycles(Cycles)    (((Cycles) <= 0x10))
/**
  * @}
  */ 

/** @defgroup TIMER_Interrupt 
  * @{
  */
#define TIMER_IT_MR0I              	((uint32_t)0x00000001)
#define TIMER_IT_MR1I              	((uint32_t)0x00000008)
#define TIMER_IT_MR2I              	((uint32_t)0x00000040)
#define TIMER_IT_MR3I              	((uint32_t)0x00000200)
#define	TIMER_IT_CAP0				((uint32_t)0x01000004)
#define	TIMER_IT_CAP1				((uint32_t)0x01000400)
#define TIMER_IT_PULSE_COUNTER0     ((uint32_t)0x10100000)
#define TIMER_IT_PULSE_COUNTER1     ((uint32_t)0x10200000)
#define TIMER_IT_PULSE_COUNTER2     ((uint32_t)0x10400000)
#define TIMER_IT_PULSE_COUNTER3     ((uint32_t)0x10800000)

#define	TIMER_IT_CAP_FLAG			((uint32_t)0x01000000)
#define	TIMER_IT_PULSE_COUNTER_FLAG	((uint32_t)0x10000000)

#define IS_TIMER_IT(IT)             (((IT) == TIMER_IT_MR0I)            || \
							        ((IT) == TIMER_IT_MR1I)             || \
							        ((IT) == TIMER_IT_MR2I)             || \
							        ((IT) == TIMER_IT_MR3I)             || \
							        ((IT) == TIMER_IT_PULSE_COUNTER0)   || \
							        ((IT) == TIMER_IT_PULSE_COUNTER1)   || \
							        ((IT) == TIMER_IT_PULSE_COUNTER2)   || \
							        ((IT) == TIMER_IT_PULSE_COUNTER3)   || \
							        ((IT) == TIMER_IT_CAP0)             || \
                                    ((IT) == TIMER_IT_CAP1))

#define TIMER_IT_PENDING_MR0                ((uint32_t)0x00000001)
#define TIMER_IT_PENDING_MR1                ((uint32_t)0x00000002)
#define TIMER_IT_PENDING_MR2                ((uint32_t)0x00000004)
#define TIMER_IT_PENDING_MR3                ((uint32_t)0x00000008)
#define TIMER_IT_PENDING_CR0                ((uint32_t)0x00000010)
#define TIMER_IT_PENDING_PULSE_COUNTER0     ((uint32_t)0x00000020)
#define TIMER_IT_PENDING_PULSE_COUNTER1     ((uint32_t)0x00000040)
#define TIMER_IT_PENDING_PULSE_COUNTER2     ((uint32_t)0x00000080)
#define TIMER_IT_PENDING_PULSE_COUNTER3     ((uint32_t)0x00000100)
#define TIMER_IT_PENDING_CR1                ((uint32_t)0x00000200)

#define IS_TIMER_GET_IT(IT)         (((IT) == TIMER_IT_PENDING_MR0) || \
							        ((IT) == TIMER_IT_PENDING_MR1)  || \
							        ((IT) == TIMER_IT_PENDING_MR2)  || \
							        ((IT) == TIMER_IT_PENDING_MR3)  || \
							        ((IT) == TIMER_IT_PENDING_CR0)  || \
							        ((IT) == TIMER_IT_PENDING_CR1)  || \
							        ((IT) == TIMER_IT_PENDING_PULSE_COUNTER0)  || \
							        ((IT) == TIMER_IT_PENDING_PULSE_COUNTER1)  || \
							        ((IT) == TIMER_IT_PENDING_PULSE_COUNTER2)  || \
							        ((IT) == TIMER_IT_PENDING_PULSE_COUNTER3))

#define IS_TIMER_CLEAR_IT(TIMER_IT) ((((TIMER_IT) & 0xFFFFFC00) == 0x00000000) && ((TIMER_IT) != 0x00000000))
/**
  * @}
  */

/** @defgroup TIMER_Flag
  * @{
  */
#define TIMER_FLAG_EM0              ((uint32_t)0x00000001)
#define TIMER_FLAG_EM1              ((uint32_t)0x00000002)
#define TIMER_FLAG_EM2              ((uint32_t)0x00000004)
#define TIMER_FLAG_EM3              ((uint32_t)0x00000008)
#define IS_TIMER_GET_FLAG(FLAG)     (((FLAG) == TIMER_FLAG_EM0) || \
                                    ((FLAG) == TIMER_FLAG_EM1) || \
                                    ((FLAG) == TIMER_FLAG_EM2) || \
                                    ((FLAG) == TIMER_FLAG_EM3))
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TIMER_DeInit(TIMER_TypeDef* TIMERx);
void TIMER_Init(TIMER_TypeDef* TIMERx, TIMER_InitTypeDef* TIMER_InitStruct);
void TIMER_SetPrescale(TIMER_TypeDef* TIMERx, uint32_t Prescale);
uint32_t TIMER_GetPrescale(TIMER_TypeDef* TIMERx);
void TIMER_SetIdleLevel(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Level);
void TIMER_SetMatchDefaultLevel(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Level);
void TIMER_SetMatchAction(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Action);
FlagStatus TIMER_GetMatchLevel(TIMER_TypeDef* TIMERx, uint32_t Channel);
void TIMER_ResetCmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState);
void TIMER_StopTC(TIMER_TypeDef* TIMERx, uint32_t Channel);
void TIMER_Cmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState);
uint32_t TIMER_GetTC(TIMER_TypeDef* TIMERx, uint32_t Channel);
void COUNTER_Init(TIMER_TypeDef* TIMERx, COUNTER_InitTypeDef* COUNTER_InitStruct);
uint32_t TIMER_GetCR(TIMER_TypeDef* TIMERx, uint32_t Channel);
FlagStatus TIMER_GetExternalMatchState(TIMER_TypeDef* TIMERx, uint32_t Channel);
void PWM_Init(TIMER_TypeDef* TIMERx, PWM_InitTypeDef* PWM_InitStruct);
void PWM_SetPWMTHandMATCH(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t PWM_Threshold, uint32_t Match);
void PWM_InvertCmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState);
void PWM_SetPulseCounterValue(TIMER_TypeDef* TIMERx, uint32_t Channel, uint32_t Value);
void PWM_PulseCounterCmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState);
void PWM_Cmd(TIMER_TypeDef* TIMERx, uint32_t Channel, FunctionalState NewState);
void TIMER_ITConfig(TIMER_TypeDef* TIMERx, uint32_t TIMER_IT, FunctionalState NewState);
ITStatus TIMER_GetITStatus(TIMER_TypeDef* TIMERx, uint32_t TIMER_IT);
void TIMER_ClearITPendingBit(TIMER_TypeDef* TIMERx, uint32_t TIMER_IT);

#ifdef __cplusplus
}
#endif

#endif /*__VTM071x_TIMER_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT MIC *****END OF FILE****/

