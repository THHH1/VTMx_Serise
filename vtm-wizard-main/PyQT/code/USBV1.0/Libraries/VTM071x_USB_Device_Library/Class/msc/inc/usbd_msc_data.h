/**
  ******************************************************************************
  * @file    usbd_msc_data.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   header for the usbd_msc_data.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef _USBD_MSC_DATA_H_
#define _USBD_MSC_DATA_H_

/* Includes ------------------------------------------------------------------*/
#include "usbd_conf.h"

/* Exported defines ----------------------------------------------------------*/
#define MODE_SENSE6_LEN			    8
#define MODE_SENSE10_LEN		    8
#define LENGTH_INQUIRY_PAGE00       7
#define LENGTH_FORMAT_CAPACITIES    20

/* Exported types ------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern const uint8_t MSC_Page00_Inquiry_Data[];  
extern const uint8_t MSC_Mode_Sense6_data[];
extern const uint8_t MSC_Mode_Sense10_data[]; 

/* Exported functions ------------------------------------------------------- */ 

#endif /* _USBD_MSC_DATA_H_ */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
