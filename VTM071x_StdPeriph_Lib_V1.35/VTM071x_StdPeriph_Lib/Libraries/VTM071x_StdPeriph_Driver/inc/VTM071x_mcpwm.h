/**
  ******************************************************************************
  * @file    VTM071x_mcpwm.h
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the TIM firmware 
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
#ifndef __VTM071x_MCPWM_H__
#define __VTM071x_MCPWM_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "VTM071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup MCPWM
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** @defgroup MCPWM_CENTER
  * @{
  */
typedef enum {
		MCPWM_CENTER_EA = 0,
		MCPWM_CENTER_CA = 1
}MCPWM_CENTER;
#define IS_MCPWM_CENTER(CENTER) (((CENTER) == MCPWM_CENTER_EA) || \
								((CENTER) == MCPWM_CENTER_CA))
/**
  * @}
  */ 

/** @defgroup MCPWM_POLARITY
  * @{
  */
typedef enum {
		MCPWM_Polarity_ILAH = 0,
		MCPWM_Polarity_IHAL = 1
}MCPWM_POLARITY;
#define IS_MCPWM_Polarity(POLA) (((POLA) == MCPWM_Polarity_ILAH) || \
								((POLA) == MCPWM_Polarity_IHAL))
/**
  * @}
  */ 

/** @defgroup MCPWM_UPDATE
  * @{
  */
typedef enum {
		MCPWM_Update_EN = 0,
		MCPWM_Update_DIS = 1
}MCPWM_UPDATE;
#define IS_MCPWM_Update(Update) (((Update) == MCPWM_Update_EN) || \
								((Update) == MCPWM_Update_DIS))
/**
  * @}
  */ 

/** @defgroup MCPWM_Capture_Rst_TC
  * @{
  */
typedef enum {
		MCPWM_RST_TC_EN = 0,
		MCPWM_RST_TC_DIS = 1
}MCPWM_Capture_Rst_TC;
#define IS_MCPWM_CAPTURE_RST_TC(RST)    (((RST) == MCPWM_RST_TC_EN) || \
								        ((RST) == MCPWM_RST_TC_DIS))
/**
  * @}
  */ 

/** @defgroup MCPWM_Capture_Noise_Filter
  * @{
  */
typedef enum {
		MCPWM_NOISE_FILTER_EN = 0,
		MCPWM_NOISE_FILTER_DIS = 1
}MCPWM_Capture_Noise_Filter;
#define IS_MCPWM_Capture_Noise_Filter(NF)   (((NF) == MCPWM_NOISE_FILTER_EN) || \
								            ((NF) == MCPWM_NOISE_FILTER_DIS))
/**
  * @}
  */ 

/** @defgroup MCPWM_TOC
  * @{
  */
typedef enum {
		MCPWM_TIMER = 0,
		MCPWM_COUNTER = 1
}MCPWM_TOC;
#define IS_MCPWM_TOC(TOC)               (((TOC) == MCPWM_TIMER) || \
								        ((TOC) == MCPWM_COUNTER))
/**
  * @}
  */ 

/** @defgroup MCPWM_INS
  * @{
  */
typedef enum {
		MCPWM_INS_LOW = 0,
		MCPWM_INS_HIGH = 1
}MCPWM_INS;
#define IS_MCPWM_INS(STAT)              (((STAT) == MCPWM_INS_LOW) || \
								        ((STAT) == MCPWM_INS_HIGH))
/**
  * @}
  */ 

/** 
  * @brief  MCPWM Init structure definition  
  */
typedef struct
{
    uint32_t MCPWM_Match;                       /*!< Specifies the MCPWM Match Val.
                                                This parameter can be a value between 0x00000000 and 0xFFFFFFFF */

    uint32_t MCPWM_Limit;                       /*!< Specifies the MCPWM Limit Val.
                                                This parameter can be be a value between 0x00000000 and 0xFFFFFFFF */

    uint32_t MCPWM_DeadTime;                    /*!< Specifies the MCPWM dead time.
                                                This parameter can be a value between 0x00000000 and 0x000003FF */

    uint32_t MCPWM_Center;                      /*!< Specifies edge-align or center-align.
                                                This parameter can be a value of @ref MCPWM_CENTER */

    uint32_t MCPWM_Polarity;                    /*!< Specifies the polarity.
                                                This parameter can be a value of @ref MCPWM_POLARITY */

    uint32_t MCPWM_Update;                      /*!< Specifies the update function.
                                                This parameter can be a value of @ref MCPWM_UPDATE */

    uint32_t MCPWM_Channel;                     /*!< Specifies the MCPWM channel.
                                                This parameter can be a value of @ref MCPWM_CHANNEL */

}MCPWM_InitTypeDef;

/** 
  * @brief  MCPWM CP structure definition  
  */
typedef struct
{
	uint32_t MCPWM_CPA0;                        /*!< Specifies the MCPWM CPA0 connection.
                                                This parameter can be a value of @ref MCPWM_CP_A0 or @ref MCPWM_HALL_A0 */
    
    uint32_t MCPWM_CPB0;                        /*!< Specifies the MCPWM CPB0 connection.
                                                This parameter can be a value of @ref MCPWM_CP_B0 or @ref MCPWM_HALL_B0 */

    uint32_t MCPWM_CPA1;                        /*!< Specifies the MCPWM CPA1 connection.
                                                This parameter can be a value of @ref MCPWM_CP_A1 or @ref MCPWM_HALL_A1 */

    uint32_t MCPWM_CPB1;                        /*!< Specifies the MCPWM CPB1 connection.
                                                This parameter can be a value of @ref MCPWM_CP_B1 or @ref MCPWM_HALL_B1 */

    uint32_t MCPWM_CPA2;                        /*!< Specifies the MCPWM CPA2 connection.
                                                This parameter can be a value of @ref MCPWM_CP_A2 or @ref MCPWM_HALL_A2 */

    uint32_t MCPWM_CPB2;                        /*!< Specifies the MCPWM CPB2 connection.
                                                This parameter can be a value of @ref MCPWM_CP_B2 or @ref MCPWM_HALL_B2 */

}MCPWM_CPTypeDef;

/** 
  * @brief  MCPWM inactive status structure definition  
  */
typedef struct
{
	uint32_t MCPWM_CPA0_INS;                    /*!< Specifies the MCPWM CPA0 inactive status.
                                                This parameter can be a value of @ref MCPWM_INS */
    
    uint32_t MCPWM_CPB0_INS;                    /*!< Specifies the MCPWM CPB0 inactive status.
                                                This parameter can be a value of @ref MCPWM_INS */

    uint32_t MCPWM_CPA1_INS;                    /*!< Specifies the MCPWM CPA1 inactive status.
                                                This parameter can be a value of @ref MCPWM_INS */

    uint32_t MCPWM_CPB1_INS;                    /*!< Specifies the MCPWM CPB1 inactive status.
                                                This parameter can be a value of @ref MCPWM_INS */

    uint32_t MCPWM_CPA2_INS;                    /*!< Specifies the MCPWM CPA2 inactive status.
                                                This parameter can be a value of @ref MCPWM_INS */

    uint32_t MCPWM_CPB2_INS;                    /*!< Specifies the MCPWM CPB2 inactive status.
                                                This parameter can be a value of @ref MCPWM_INS */

}MCPWM_CPINSTypeDef;

/** 
  * @brief  MCPWM Capture structure definition  
  */
typedef struct
{
	uint32_t MCPWM_CaptureSource;               /*!< Specifies the capture source.
                                                This parameter can be a value of @ref IS_MCPWM_CAPTURE_SOURCE */

    uint32_t MCPWM_CaptureRstTC;                /*!< Enable or disable Reset TC function.
                                                This parameter can be a value of @ref IS_MCPWM_CAPTURE_RST_TC */

    uint32_t MCPWM_CaptureNoiseFilter;          /*!< Enable or disable hardware noise filter.
                                                This parameter can be a value of @ref IS_MCPWM_Capture_Noise_Filter */

    uint32_t MCPWM_Channel;                     /*!< Specifies the MCPWM channel.
                                                This parameter can be a value of @ref MCPWM_CHANNEL */

}MCPWM_CapTypeDef;



/* Exported constants --------------------------------------------------------*/

/** @defgroup MCPWM_Exported_Constants
  * @{
  */

/** @defgroup MCPWM_CHANNEL 
  * @{
  */
#define MCPWM_CHANNEL_0                     ((uint32_t)0x00000001)
#define MCPWM_CHANNEL_1                     ((uint32_t)0x00000100)
#define MCPWM_CHANNEL_2                     ((uint32_t)0x00010000)
#define IS_MCPWM_CHANNEL(CHANNEL)           (((CHANNEL) == MCPWM_CHANNEL_0) || \
                                            ((CHANNEL) == MCPWM_CHANNEL_1)  || \
                                            ((CHANNEL) == MCPWM_CHANNEL_2))

#define IS_MCPWM_CHANNEL_COM(CHANNEL)       (((CHANNEL) == MCPWM_CHANNEL_0) || \
                                            ((CHANNEL) == MCPWM_CHANNEL_1)  || \
                                            ((CHANNEL) == MCPWM_CHANNEL_2)  || \
                                            ((CHANNEL) == (MCPWM_CHANNEL_0 | MCPWM_CHANNEL_1)) || \
                                            ((CHANNEL) == (MCPWM_CHANNEL_0 | MCPWM_CHANNEL_2)) || \
                                            ((CHANNEL) == (MCPWM_CHANNEL_1 | MCPWM_CHANNEL_2)) || \
                                            ((CHANNEL) == (MCPWM_CHANNEL_0 | MCPWM_CHANNEL_1 | MCPWM_CHANNEL_2)))

/**
  * @}
  */ 

/** @defgroup MCPWM_DEADTIME 
  * @{
  */
#define IS_MCPWM_DEADTIME(DT)               ((DT) <= 0x3FF)
/**
  * @}
  */ 

/** @defgroup MCPWM_INVBDC
  * @{
  */
#define MCPWM_INVBDC_SAME                   ((uint32_t)0x00000000)
#define MCPWM_INVBDC_OPPOSITE               ((uint32_t)0x20000000)
#define IS_MCPWM_INVBDC(INVBDC)             (((INVBDC) == MCPWM_INVBDC_SAME) || \
                                            ((INVBDC) == MCPWM_INVBDC_OPPOSITE))
/**
  * @}
  */ 

/** @defgroup MCPWM_CP_A0 
  * @{
  */
#define MCPWM_CPA0_ACTIVATE                 ((uint32_t)0x00000001)
#define MCPWM_CPA0_UNCONNECT                ((uint32_t)0x00000000)
#define IS_MCPWM_CPA0(CPA0)                 (((CPA0) == MCPWM_CPA0_ACTIVATE) || \
                                            ((CPA0) == MCPWM_CPA0_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_CP_B0 
  * @{
  */
#define MCPWM_CPB0_CONNECT_A0               ((uint32_t)0x00000002)
#define MCPWM_CPB0_UNCONNECT                ((uint32_t)0x00000000)
#define IS_MCPWM_CPB0(CPB0)                 (((CPB0) == MCPWM_CPB0_CONNECT_A0) || \
                                            ((CPB0) == MCPWM_CPB0_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_CP_A1
  * @{
  */
#define MCPWM_CPA1_CONNECT_A0               ((uint32_t)0x00000004)
#define MCPWM_CPA1_UNCONNECT                ((uint32_t)0x00000000)
#define IS_MCPWM_CPA1(CPA1)                 (((CPA1) == MCPWM_CPA1_CONNECT_A0) || \
                                            ((CPA1) == MCPWM_CPA1_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_CP_B1
  * @{
  */
#define MCPWM_CPB1_CONNECT_A0               ((uint32_t)0x00000008)
#define MCPWM_CPB1_UNCONNECT                ((uint32_t)0x00000000)
#define IS_MCPWM_CPB1(CPB1)                 (((CPB1) == MCPWM_CPB1_CONNECT_A0) || \
                                            ((CPB1) == MCPWM_CPB1_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_CP_A2 
  * @{
  */
#define MCPWM_CPA2_CONNECT_A0               ((uint32_t)0x00000010)
#define MCPWM_CPA2_UNCONNECT                ((uint32_t)0x00000000)
#define IS_MCPWM_CPA2(CPA2)                 (((CPA2) == MCPWM_CPA2_CONNECT_A0) || \
                                            ((CPA2) == MCPWM_CPA2_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_CP_B2 
  * @{
  */
#define MCPWM_CPB2_CONNECT_A0               ((uint32_t)0x00000020)
#define MCPWM_CPB2_UNCONNECT                ((uint32_t)0x00000000)
#define IS_MCPWM_CPB2(CPB2)                 (((CPB2) == MCPWM_CPB2_CONNECT_A0) || \
                                            ((CPB2) == MCPWM_CPB2_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_HALL_A0
  * @{
  */
#define MCPWM_HALLA0_ACTIVATE               ((uint32_t)0x00000001)
#define MCPWM_HALLA0_UNCONNECT              ((uint32_t)0x00000000)
#define IS_MCPWM_HALLA0(HALLA0)             (((HALLA0) == MCPWM_HALLA0_ACTIVATE) || \
                                            ((HALLA0) == MCPWM_HALLA0_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_HALL_B0 
  * @{
  */
#define MCPWM_HALLB0_ACTIVATE               ((uint32_t)0x00000002)
#define MCPWM_HALLB0_UNCONNECT              ((uint32_t)0x00000000)
#define IS_MCPWM_HALLB0(HALLB0)             (((HALLB0) == MCPWM_HALLB0_ACTIVATE) || \
                                            ((HALLB0) == MCPWM_HALLB0_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_HALL_A1
  * @{
  */
#define MCPWM_HALLA1_CONNECT_A0             ((uint32_t)0x00000004)
#define MCPWM_HALLA1_UNCONNECT              ((uint32_t)0x00000000)
#define IS_MCPWM_HALLA1(HALLA1)             (((HALLA1) == MCPWM_HALLA1_CONNECT_A0) || \
                                            ((HALLA1) == MCPWM_HALLA1_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_HALL_B1
  * @{
  */
#define MCPWM_HALLB1_CONNECT_A0             ((uint32_t)0x00000008)
#define MCPWM_HALLB1_UNCONNECT              ((uint32_t)0x00000000)
#define IS_MCPWM_HALLB1(HALLB1)             (((HALLB1) == MCPWM_HALLB1_CONNECT_A0) || \
                                            ((HALLB1) == MCPWM_HALLB1_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_HALL_A2 
  * @{
  */
#define MCPWM_HALLA2_CONNECT_A0             ((uint32_t)0x00000010)
#define MCPWM_HALLA2_UNCONNECT              ((uint32_t)0x00000000)
#define IS_MCPWM_HALLA2(HALLA2)             (((HALLA2) == MCPWM_HALLA2_CONNECT_A0) || \
                                            ((HALLA2) == MCPWM_HALLA2_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_HALL_B2 
  * @{
  */
#define MCPWM_HALLB2_CONNECT_A0             ((uint32_t)0x00000020)
#define MCPWM_HALLB2_UNCONNECT              ((uint32_t)0x00000000)
#define IS_MCPWM_HALLB2(HALLB2)             (((HALLB2) == MCPWM_HALLB2_CONNECT_A0) || \
                                            ((HALLB2) == MCPWM_HALLB2_UNCONNECT))
/**
  * @}
  */ 

/** @defgroup MCPWM_CAPTURE_SOURCE
  * @{
  */
#define MCPWM_CAPTURE_SOURCE_MCI0_RE        ((uint32_t)0x00000001)
#define MCPWM_CAPTURE_SOURCE_MCI0_FE        ((uint32_t)0x00000002)
#define MCPWM_CAPTURE_SOURCE_MCI1_RE        ((uint32_t)0x00000004)
#define MCPWM_CAPTURE_SOURCE_MCI1_FE        ((uint32_t)0x00000008)
#define MCPWM_CAPTURE_SOURCE_MCI2_RE        ((uint32_t)0x00000010)
#define MCPWM_CAPTURE_SOURCE_MCI2_FE        ((uint32_t)0x00000020)
#define IS_MCPWM_CAPTURE_SOURCE(SOURCE)     (((SOURCE) & 0xFFFFFFC0) == 0)
/**
  * @}
  */

/** @defgroup MCPWM_COUNTER_SOURCE
  * @{
  */
#define MCPWM_COUNTER_SOURCE_MCI0_RE        ((uint32_t)0x00000001)
#define MCPWM_COUNTER_SOURCE_MCI0_FE        ((uint32_t)0x00000002)
#define MCPWM_COUNTER_SOURCE_MCI1_RE        ((uint32_t)0x00000004)
#define MCPWM_COUNTER_SOURCE_MCI1_FE        ((uint32_t)0x00000008)
#define MCPWM_COUNTER_SOURCE_MCI2_RE        ((uint32_t)0x00000010)
#define MCPWM_COUNTER_SOURCE_MCI2_FE        ((uint32_t)0x00000020)
#define IS_MCPWM_COUNTER_SOURCE(SOURCE)     (((SOURCE) & 0xFFFFFFC0) == 0)
/**
  * @}
  */

/** @defgroup MCPWM_HALL_CUR_STAT
  * @{
  */
#define MCPWM_HALL_CUR_STAT_1               ((uint32_t)0x00100000)
#define MCPWM_HALL_CUR_STAT_2               ((uint32_t)0x00200000)
#define MCPWM_HALL_CUR_STAT_3               ((uint32_t)0x00300000)
#define MCPWM_HALL_CUR_STAT_4               ((uint32_t)0x00400000)
#define MCPWM_HALL_CUR_STAT_5               ((uint32_t)0x00500000)
#define MCPWM_HALL_CUR_STAT_6               ((uint32_t)0x00600000)
#define IS_MCPWM_HALL_CUR_STAT(STAT)        (((STAT) == MCPWM_HALL_CUR_STAT_1) || \
                                            ((STAT) == MCPWM_HALL_CUR_STAT_2)  || \
                                            ((STAT) == MCPWM_HALL_CUR_STAT_3)  || \
                                            ((STAT) == MCPWM_HALL_CUR_STAT_4)  || \
                                            ((STAT) == MCPWM_HALL_CUR_STAT_5)  || \
                                            ((STAT) == MCPWM_HALL_CUR_STAT_6))
/**
  * @}
  */

/** @defgroup MCPWM_HALL_EXP_STAT
  * @{
  */
#define MCPWM_HALL_EXP_STAT_1               ((uint32_t)0x00010000)
#define MCPWM_HALL_EXP_STAT_2               ((uint32_t)0x00020000)
#define MCPWM_HALL_EXP_STAT_3               ((uint32_t)0x00030000)
#define MCPWM_HALL_EXP_STAT_4               ((uint32_t)0x00040000)
#define MCPWM_HALL_EXP_STAT_5               ((uint32_t)0x00050000)
#define MCPWM_HALL_EXP_STAT_6               ((uint32_t)0x00060000)
#define IS_MCPWM_HALL_EXP_STAT(STAT)        (((STAT) == MCPWM_HALL_EXP_STAT_1) || \
                                            ((STAT) == MCPWM_HALL_EXP_STAT_2)  || \
                                            ((STAT) == MCPWM_HALL_EXP_STAT_3)  || \
                                            ((STAT) == MCPWM_HALL_EXP_STAT_4)  || \
                                            ((STAT) == MCPWM_HALL_EXP_STAT_5)  || \
                                            ((STAT) == MCPWM_HALL_EXP_STAT_6))
/**
  * @}
  */

/** @defgroup MCPWM_Interrupt 
  * @{
  */
#define MCPWM_IT_ILIM0              	        ((uint32_t)0x00000001)
#define MCPWM_IT_IMAT0              	        ((uint32_t)0x00000002)
#define MCPWM_IT_ICAP0              	        ((uint32_t)0x00000004)
#define MCPWM_IT_ILIM1              	        ((uint32_t)0x00000010)
#define MCPWM_IT_IMAT1              	        ((uint32_t)0x00000020)
#define MCPWM_IT_ICAP1              	        ((uint32_t)0x00000040)
#define MCPWM_IT_ILIM2              	        ((uint32_t)0x00000100)
#define MCPWM_IT_IMAT2              	        ((uint32_t)0x00000200)
#define MCPWM_IT_ICAP2              	        ((uint32_t)0x00000400)
#define MCPWM_IT_ABORT              	        ((uint32_t)0x00001000)
#define MCPWM_IT_STCHG              	        ((uint32_t)0x00010000)
#define MCPWM_IT_STERR              	        ((uint32_t)0x00020000)
#define MCPWM_IT_VSLOW              	        ((uint32_t)0x00040000)
#define MCPWM_IT_VFAST              	        ((uint32_t)0x00080000)
#define MCPWM_IT_MATR0              	        ((uint32_t)0x00100000)
#define MCPWM_IT_MATF0              	        ((uint32_t)0x00200000)
#define MCPWM_IT_CTZERO0              	        ((uint32_t)0x00400000)
#define MCPWM_IT_MATR1              	        ((uint32_t)0x01000000)
#define MCPWM_IT_MATF1              	        ((uint32_t)0x02000000)
#define MCPWM_IT_CTZERO1              	        ((uint32_t)0x04000000)
#define MCPWM_IT_MATR2              	        ((uint32_t)0x10000000)
#define MCPWM_IT_MATF2              	        ((uint32_t)0x20000000)
#define MCPWM_IT_CTZERO2              	        ((uint32_t)0x40000000)

#define IS_MCPWM_IT(IT)                         (((IT) == MCPWM_IT_ILIM0) || \
                                                ((IT) == MCPWM_IT_IMAT0) || \
                                                ((IT) == MCPWM_IT_ICAP0) || \
                                                ((IT) == MCPWM_IT_ILIM1) || \
                                                ((IT) == MCPWM_IT_IMAT1) || \
                                                ((IT) == MCPWM_IT_ICAP1) || \
                                                ((IT) == MCPWM_IT_ILIM2) || \
                                                ((IT) == MCPWM_IT_IMAT2) || \
                                                ((IT) == MCPWM_IT_ICAP2) || \
                                                ((IT) == MCPWM_IT_ABORT) || \
                                                ((IT) == MCPWM_IT_STCHG) || \
                                                ((IT) == MCPWM_IT_STERR) || \
                                                ((IT) == MCPWM_IT_VSLOW) || \
                                                ((IT) == MCPWM_IT_VFAST) || \
                                                ((IT) == MCPWM_IT_MATR0) || \
                                                ((IT) == MCPWM_IT_MATF0) || \
                                                ((IT) == MCPWM_IT_CTZERO0) || \
                                                ((IT) == MCPWM_IT_MATR1) || \
                                                ((IT) == MCPWM_IT_MATF1) || \
                                                ((IT) == MCPWM_IT_CTZERO1) || \
                                                ((IT) == MCPWM_IT_MATR2) || \
                                                ((IT) == MCPWM_IT_MATF2) || \
                                                ((IT) == MCPWM_IT_CTZERO2))
                                                
#define IS_Get_MCPWM_IT(IT)                     (((IT) == MCPWM_IT_ILIM0) || \
                                                ((IT) == MCPWM_IT_IMAT0) || \
                                                ((IT) == MCPWM_IT_ICAP0) || \
                                                ((IT) == MCPWM_IT_ILIM1) || \
                                                ((IT) == MCPWM_IT_IMAT1) || \
                                                ((IT) == MCPWM_IT_ICAP1) || \
                                                ((IT) == MCPWM_IT_ILIM2) || \
                                                ((IT) == MCPWM_IT_IMAT2) || \
                                                ((IT) == MCPWM_IT_ICAP2) || \
                                                ((IT) == MCPWM_IT_ABORT) || \
                                                ((IT) == MCPWM_IT_STCHG) || \
                                                ((IT) == MCPWM_IT_STERR) || \
                                                ((IT) == MCPWM_IT_VSLOW) || \
                                                ((IT) == MCPWM_IT_VFAST) || \
                                                ((IT) == MCPWM_IT_MATR0) || \
                                                ((IT) == MCPWM_IT_MATF0) || \
                                                ((IT) == MCPWM_IT_CTZERO0) || \
                                                ((IT) == MCPWM_IT_MATR1) || \
                                                ((IT) == MCPWM_IT_MATF1) || \
                                                ((IT) == MCPWM_IT_CTZERO1) || \
                                                ((IT) == MCPWM_IT_MATR2) || \
                                                ((IT) == MCPWM_IT_MATF2) || \
                                                ((IT) == MCPWM_IT_CTZERO2))

#define IS_Clear_MCPWM_IT(IT)                   (((IT) == MCPWM_IT_ILIM0) || \
                                                ((IT) == MCPWM_IT_IMAT0) || \
                                                ((IT) == MCPWM_IT_ICAP0) || \
                                                ((IT) == MCPWM_IT_ILIM1) || \
                                                ((IT) == MCPWM_IT_IMAT1) || \
                                                ((IT) == MCPWM_IT_ICAP1) || \
                                                ((IT) == MCPWM_IT_ILIM2) || \
                                                ((IT) == MCPWM_IT_IMAT2) || \
                                                ((IT) == MCPWM_IT_ICAP2) || \
                                                ((IT) == MCPWM_IT_ABORT) || \
                                                ((IT) == MCPWM_IT_STCHG) || \
                                                ((IT) == MCPWM_IT_STERR) || \
                                                ((IT) == MCPWM_IT_VSLOW) || \
                                                ((IT) == MCPWM_IT_VFAST) || \
                                                ((IT) == MCPWM_IT_MATR0) || \
                                                ((IT) == MCPWM_IT_MATF0) || \
                                                ((IT) == MCPWM_IT_CTZERO0) || \
                                                ((IT) == MCPWM_IT_MATR1) || \
                                                ((IT) == MCPWM_IT_MATF1) || \
                                                ((IT) == MCPWM_IT_CTZERO1) || \
                                                ((IT) == MCPWM_IT_MATR2) || \
                                                ((IT) == MCPWM_IT_MATF2) || \
                                                ((IT) == MCPWM_IT_CTZERO2))
/**
  * @}
  */

/**
 * @}
 */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void MCPWM_DeInit(void);
void MCPWM_Init(MCPWM_InitTypeDef* MCPWM_InitStruct);
void MCPWM_SetPrescale(uint32_t Prescale);
void MCPWM_ChangeMATAndLIM(uint32_t MCPWM_Channel_COM, uint32_t MCPWM_MAT, uint32_t MCPWM_LIM);
void MCPWM_Cmd(uint32_t MCPWM_Channel_COM, FunctionalState NewState);
void MCPWM_DCConfig(uint32_t Invbdc, MCPWM_CPTypeDef* MCPWM_CPStruct);
void MCPWM_INSConfig(MCPWM_CPINSTypeDef* MCPWM_CPINSStruct);
void MCPWM_DCCmd(FunctionalState NewState);
void MCPWM_ACCmd(FunctionalState NewState);
void MCPWM_CaptureConfig(MCPWM_CapTypeDef* MCPWM_CapStruct);
void MCPWM_TimerorCounter(uint32_t TOC, uint32_t MCPWM_Channel);
void MCPWM_CounterConfig(uint32_t ConterSource, uint32_t MCPWM_Channel);
uint32_t MCPWM_GetCAP(uint32_t MCPWM_Channel);
void MCPWM_ClearCAP(uint32_t MCPWM_Channel);
void MCPWM_HALLStatusConfig(uint32_t CurrentStatus, uint32_t ExpectedStatus);
void MCPWM_HALLPolarityConfig(MCPWM_CPTypeDef* MCPWM_HALLCPStruct);
void MCPWM_HALLCmd(FunctionalState NewState);
uint32_t MCPWM_GetHALLStat(void);
void MCPWM_VelocityDetectConfig(uint32_t Velocity, uint32_t Offset);
void MCPWM_VelocityDetectCmd(FunctionalState NewState);
uint32_t MCPWM_GetVelocity(void);
void MCPWM_ITConfig(uint32_t MCPWM_IT, FunctionalState NewState);
ITStatus MCPWM_GetITStatus(uint32_t MCPWM_IT);
void MCPWM_ClearITPendingBit(uint32_t MCPWM_IT);

#ifdef __cplusplus
}
#endif

#endif /*__VTM071x_MCPWM_H */

/**
  * @}
  */ 

/**
  * @}
  */

/******************* (C) COPYRIGHT MIC *****END OF FILE****/
