/**
  ******************************************************************************
  * @file    usb_dcd.h
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   Device Control Driver Header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DCD_H__
#define __DCD_H__

/* Includes ------------------------------------------------------------------*/
#include "usb_core.h"

/* Exported defines ----------------------------------------------------------*/

/*  Endpoint Kind */
#define USB_SNG_BUF                          0
#define USB_DBL_BUF                          1

/*  Device Status */
#define USB_UNCONNECTED                      0
#define USB_DEFAULT                          1
#define USB_ADDRESSED                        2
#define USB_CONFIGURED                       3
#define USB_SUSPENDED                        4


/* Exported types ------------------------------------------------------------*/
/********************************************************************************
Data structure type
********************************************************************************/
typedef struct
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bEndpointAddress;
  uint8_t  bmAttributes;
  uint16_t wMaxPacketSize;
  uint8_t  bInterval;
}
EP_DESCRIPTOR , *PEP_DESCRIPTOR;

__packed typedef struct USB_ep
{
    uint8_t     num;
    uint8_t     is_stall;  
    uint8_t     type;
    uint8_t     doublebuffer;
    uint32_t    pmaadress;
    uint32_t    maxpacket;
    /* transaction level variables !!! up to one max packet per transaction !!! */
    uint8_t     *xfer_buff;
    uint32_t    xfer_len ;
    uint32_t    xfer_count;
    /* control transfer variables*/
    uint32_t    total_data_len;
    uint32_t    ctl_data_len;
    uint32_t    busy;
}
USB_EP;

typedef  struct  usb_setup_req {
    
    uint8_t   bmRequest;                      
    uint8_t   bRequest;                           
    uint16_t  wValue;                             
    uint16_t  wIndex;                             
    uint16_t  wLength;                            
} USB_SETUP_REQ;

typedef struct _Device_TypeDef
{
  uint8_t  *(*GetDeviceDescriptor)( uint8_t speed , uint16_t *length);  
#ifdef LPM_ENABLED
  uint8_t  *(*GetBOSDescriptor)( uint8_t speed , uint16_t *length);
#endif
  uint8_t  *(*GetLangIDStrDescriptor)( uint8_t speed , uint16_t *length); 
  uint8_t  *(*GetManufacturerStrDescriptor)( uint8_t speed , uint16_t *length);  
  uint8_t  *(*GetProductStrDescriptor)( uint8_t speed , uint16_t *length);  
  uint8_t  *(*GetSerialStrDescriptor)( uint8_t speed , uint16_t *length);  
  uint8_t  *(*GetConfigurationStrDescriptor)( uint8_t speed , uint16_t *length);  
  uint8_t  *(*GetInterfaceStrDescriptor)( uint8_t speed , uint16_t *length);   
} USBD_DEVICE, *pUSBD_DEVICE;




typedef struct _Device_cb
{
  uint8_t  (*Init)         (void *pdev , uint8_t cfgidx);
  uint8_t  (*DeInit)       (void *pdev , uint8_t cfgidx);
 /* Control Endpoints*/
  uint8_t  (*Setup)        (void *pdev , USB_SETUP_REQ  *req);  
  uint8_t  (*EP0_TxSent)   (void *pdev );
  uint8_t  (*EP0_RxReady)  (void *pdev);
  /* Class Specific Endpoints*/
  uint8_t  (*DataIn)       (void *pdev , uint8_t epnum);   
  uint8_t  (*DataOut)      (void *pdev , uint8_t epnum); 
  uint8_t  (*SOF)          (void *pdev);   
  uint8_t  *(*GetConfigDescriptor)( uint8_t speed , uint16_t *length); 
  uint8_t  (*Suspend)      (void);

#ifdef USB_SUPPORT_USER_STRING_DESC 
  uint8_t  *(*GetUsrStrDescriptor)( uint8_t speed ,uint8_t index,  uint16_t *length);   
#endif  
  
} USBD_Class_cb_TypeDef;



typedef struct _USBD_USR_PROP
{
  void (*Init)(void);   
  void (*DeviceReset)(uint8_t speed); 
  void (*DeviceConfigured)(void);
  void (*DeviceSuspended)(void);
  void (*DeviceResumed)(void);      
}
USBD_Usr_cb_TypeDef;

__packed typedef struct _DCD
{
    uint8_t     device_config;
    uint8_t     device_status;
    uint8_t     device_old_status;
    uint8_t     device_address;
    uint32_t    device_state;
    uint32_t    DevRemoteWakeup;
    uint32_t    speed;
    uint8_t     setup_packet[8];
    USB_EP      in_ep[EP_NUM];
    USB_EP      out_ep[EP_NUM];
    USBD_Class_cb_TypeDef   *class_cb;
    USBD_Usr_cb_TypeDef     *usr_cb;
    USBD_DEVICE             *usr_device;
    uint8_t                 *pConfig_descriptor;
}
DCD_DEV , *DCD_PDEV;

typedef struct USB_Device_handle
{
  DCD_DEV     dev;
}
USB_DEVICE_HANDLE, USB_CORE_HANDLE;

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/********************************************************************************
EXPORTED FUNCTION FROM THE USB-DEVICE LAYER
********************************************************************************/
void       DCD_Init(USB_CORE_HANDLE *pdev);

void        DCD_DevConnect (USB_CORE_HANDLE *pdev);
void        DCD_DevDisconnect (USB_CORE_HANDLE *pdev);
void        DCD_EP_SetAddress (USB_CORE_HANDLE *pdev,
                               uint8_t address);

uint32_t DCD_PMA_Config(USB_CORE_HANDLE *pdev , 
                        uint16_t ep_addr,
                        uint16_t ep_kind,
                        uint32_t pmaadress);

uint32_t    DCD_EP_Open(USB_CORE_HANDLE *pdev , 
                     uint16_t ep_addr,
                     uint16_t ep_mps,
                     uint8_t ep_type);

uint32_t    DCD_EP_Close  (USB_CORE_HANDLE *pdev,
                                uint8_t  ep_addr);


uint32_t   DCD_EP_PrepareRx ( USB_CORE_HANDLE *pdev,
                        uint8_t   ep_addr,                                  
                        uint8_t *pbuf,                                  
                        uint16_t  buf_len);
  
uint32_t    DCD_EP_Tx (USB_CORE_HANDLE *pdev,
                               uint8_t  ep_addr,
                               uint8_t  *pbuf,
                               uint32_t   buf_len);
uint32_t    DCD_EP_Stall (USB_CORE_HANDLE *pdev,
                              uint8_t   epnum);
uint32_t    DCD_EP_ClrStall (USB_CORE_HANDLE *pdev,
                                  uint8_t epnum);

uint32_t    DCD_Handle_ISR(USB_CORE_HANDLE *pdev);


void DCD_StopDevice(USB_CORE_HANDLE *pdev);

#endif /* __DCD_H__ */

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
