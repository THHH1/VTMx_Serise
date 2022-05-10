/**
  ******************************************************************************
  * @file    VTM071x_maths.h
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file contains all the functions prototypes for the MATHS firmware
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
#ifndef __VTM071x_MATHS_H
#define __VTM071x_MATHS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "vtm071x.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @addtogroup MATHS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  MATHS Init Structure definition  
  */ 
typedef struct
{
    uint32_t DIV_K;                         /*!< Specifies weather Cordic DIV K.
                                            This parameter can be a value of @ref Cordic_DIV_K */

    uint32_t Bypass_Handle;                 /*!< Specifies weather Bypass.
                                            This parameter can be a value of @ref Cordic_Bypass_Handle */
    
    uint32_t XYMRS;                         /*!< Specifies XYMRS value.
                                            This parameter can be a value of @ref Cordic_XYMRS */
    
    uint32_t MOD_V;                         /*!< Specifies Cordic mode.
                                            This parameter can be a value of @ref Cordic_MOD_V */
} Cordic_InitTypeDef;

typedef struct
{
    uint32_t CHUSHU_SRC;

    uint32_t BEICHUSHU_SLC;
    
    uint32_t SHANGCNT;
    
    uint32_t SHANGDIR;
    
    uint32_t USIGN;
    
    uint32_t STMODE;

} Division_InitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup MATHS_Exported_Constants
  * @{
  */

/** @defgroup Cordic_DIV_K 
  * @{
  */ 
#define Cordic_DIV_K_ENABLE                 ((uint32_t)0x00010000)
#define Cordic_DIV_K_DISABLE                ((uint32_t)0x00000000)
#define IS_CORDIC_DIV_K(DIV)               (((DIV) == Cordic_DIV_K_ENABLE)   || \
                                            ((DIV) == Cordic_DIV_K_DISABLE))
/**
  * @}
  */ 

/** @defgroup Cordic_Bypass_Handle 
  * @{
  */ 
#define Cordic_Bypass_Handle_ENABLE         ((uint32_t)0x00001000)
#define Cordic_Bypass_Handle_DISABLE        ((uint32_t)0x00000000)
#define IS_CORDIC_Bypass_Handle(BYPASS)           (((BYPASS) == Cordic_Bypass_Handle_ENABLE)   || \
                                            ((BYPASS) == Cordic_Bypass_Handle_DISABLE))
/**
  * @}
  */ 

/** @defgroup Cordic_XYMRS 
  * @{
  */ 
#define Cordic_XYMRS_DIV_1                  ((uint32_t)0x00000000)
#define Cordic_XYMRS_DIV_2                  ((uint32_t)0x00000100)
#define Cordic_XYMRS_DIV_4                  ((uint32_t)0x00000200)
#define IS_CORDIC_XYMRS_DIV(DIV)           (((DIV) == Cordic_XYMRS_DIV_1)   || \
                                            ((DIV) == Cordic_XYMRS_DIV_2)   || \
                                            ((DIV) == Cordic_XYMRS_DIV_4))
/**
  * @}
  */ 

/** @defgroup Cordic_MOD_V
  * @{
  */ 
#define Cordic_MOD_V_VECTORING              ((uint32_t)0x00000010)
#define Cordic_MOD_V_ROTATION               ((uint32_t)0x00000000)
#define IS_CORDIC_MOD_V(MODE)              (((MODE) == Cordic_MOD_V_VECTORING)   || \
                                            ((MODE) == Cordic_MOD_V_ROTATION))
/**
  * @}
  */ 

/** @defgroup Division_CHUSHU_SRC
  * @{
  */ 
#define IS_Division_CHUSHU_SRC(SRC)         (((SRC) & (~MATHS_DIV_CTRL_CHUSHU_SRC_MASK)) == 0)
/**
  * @}
  */ 

/** @defgroup Division_BEICHUSHU_SLC
  * @{
  */ 
#define IS_Division_BEICHUSHU_SLC(SLC)      (((SLC) & (~MATHS_DIV_CTRL_BEICHUSHU_SLC_MASK)) == 0)
/**
  * @}
  */ 

/** @defgroup Division_SHANGCNT
  * @{
  */ 
#define IS_Division_SHANGCNT(CNT)           (((CNT) & (~MATHS_DIV_CTRL_SHANGCNT_MASK)) == 0)
/**
  * @}
  */ 

/** @defgroup Division_SHANGDIR
  * @{
  */ 
#define Division_SHANGDIR_LEFT              ((uint32_t)0x00000000)
#define Division_SHANGDIR_RIGHT             ((uint32_t)0x00000008)
#define IS_Division_SHANGDIR(DIR)          (((DIR) == Division_SHANGDIR_LEFT)   || \
                                            ((DIR) == Division_SHANGDIR_RIGHT))
/**
  * @}
  */ 

/** @defgroup Division_UNSIGN
  * @{
  */ 
#define Division_USIGN_SIGNED               ((uint32_t)0x00000000)
#define Division_USIGN_UNSIGNED             ((uint32_t)0x00000004)
#define IS_Division_UNSIGN(USIGN)          (((USIGN) == Division_USIGN_SIGNED)   || \
                                            ((USIGN) == Division_USIGN_UNSIGNED))
/**
  * @}
  */ 

/** @defgroup Division_STMODE
  * @{
  */ 
#define Division_STMODE_AUTO                ((uint32_t)0x00000000)
#define Division_STMODE_ST                  ((uint32_t)0x00000002)
#define IS_Division_STMODE(MODE)           (((MODE) == Division_STMODE_AUTO)   || \
                                            ((MODE) == Division_STMODE_ST))
/**
  * @}
  */ 

/** @defgroup Division_IT
  * @{
  */ 
#define Division_IT_ZEROERR                 ((uint32_t)0x00020000)
#define Division_IT_DONE                    ((uint32_t)0x00010000)
#define IS_Division_IT(IT)                 (((IT) == Division_IT_ZEROERR)   || \
                                            ((IT) == Division_IT_DONE))
/**
  * @}
  */ 

/** @defgroup Division_IT
  * @{
  */ 
#define Division_IT_FLAG_ZEROERR            ((uint32_t)0x00000002)
#define Division_IT_FLAG_DONE               ((uint32_t)0x00000001)
#define IS_Division_GET_IT(IT)             (((IT) == Division_IT_FLAG_ZEROERR)   || \
                                            ((IT) == Division_IT_FLAG_DONE))
/**
  * @}
  */ 

/** @defgroup Division_IT
  * @{
  */ 
#define Division_IT_FLAG_ZEROERR            ((uint32_t)0x00000002)
#define Division_IT_FLAG_DONE               ((uint32_t)0x00000001)
#define IS_Division_GET_IT_FLAG(IT)        (((IT) == Division_IT_FLAG_ZEROERR)   || \
                                            ((IT) == Division_IT_FLAG_DONE))
/**
  * @}
  */ 

/** @defgroup Division_FLAG
  * @{
  */ 
#define Division_FLAG_BUSY                  ((uint32_t)0x00000001)
#define IS_Division_FLAG(FLAG)             (((FLAG) == Division_FLAG_BUSY))
/**
  * @}
  */ 

/** @defgroup Cordic_FLAG
  * @{
  */ 
#define Cordic_FLAG_READY                   ((uint32_t)0x00000001)
#define Cordic_FLAG_OVF                     ((uint32_t)0x00000002)
#define IS_Cordic_FLAG(FLAG)               (((FLAG) == Cordic_FLAG_READY) || ((FLAG) == Cordic_FLAG_OVF))
/**
  * @}
  */ 


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MATHS_DeInit(void);
void Cordic_Init(Cordic_InitTypeDef* Cordic_InitStruct);
void Cordic_Go(uint32_t *in_xyz, uint32_t *out_xyz);
FlagStatus Cordic_GetFlagStatus(uint32_t Cordic_FLAG);
void CRC_WriteWord(uint32_t Value);
void CRC_Reset(void);
void Division_Init(Division_InitTypeDef* Division_InitStruct);
void DIV_SetDividend(uint32_t Dividend);
void DIV_SetDivisor(uint32_t Divisor);
uint32_t DIV_GetQuotient(void);
uint32_t DIV_GetRemainder(void);
void DIV_Start(void);
void DIV_ITConfig(uint32_t DIV_IT, FunctionalState NewState);
ITStatus DIV_GetITStatus(uint32_t DIV_IT_FLAG);
FlagStatus DIV_GetFlagStatus(uint32_t DIV_FLAG);



#ifdef __cplusplus
}
#endif

#endif /* __VTM071x_MATHS_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT MIC *****END OF FILE****/
