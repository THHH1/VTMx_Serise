/**
  ******************************************************************************
  * @file    usbd_hid_core.c
  * @author  MIC Software Team
  * @version V1.0.1
  * @date    08-01-2018
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                HID Class  Description
  *          =================================================================== 
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse protocol
  *             - Usage Page : Generic Desktop
  *             - Usage : Joystick
  *             - Collection : Application 
  *           
  *      
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 MIC</center></h2>
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_hid_core.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/ 
static uint8_t  USBD_HID_Init (void  *pdev, 
                               uint8_t cfgidx);

static uint8_t  USBD_HID_DeInit (void  *pdev, 
                                 uint8_t cfgidx);

static uint8_t  USBD_HID_Setup (void  *pdev, 
                                USB_SETUP_REQ *req);

static uint8_t  *USBD_HID_GetCfgDesc (uint8_t speed, uint16_t *length);

static uint8_t USBD_HID_Suspend(void);

USBD_Class_cb_TypeDef  USBD_HID_cb = 
{
    USBD_HID_Init,
    USBD_HID_DeInit,
    USBD_HID_Setup,
    NULL, /*EP0_TxSent*/  
    NULL, /*EP0_RxReady*/
    NULL, /*DataIn*/
    NULL, /*DataOut*/
    NULL, /*SOF */    
    USBD_HID_GetCfgDesc, 
    USBD_HID_Suspend,
};

static uint32_t  USBD_HID_AltSet = 0;
    
static uint32_t  USBD_HID_Protocol = 0;
 
static uint32_t  USBD_HID_IdleState  = 0;

//static uint32_t  USBD_HID_ReportDescState = 0;

/* USB HID device Configuration Descriptor */
const uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ] =
{
    0x09, /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,          /* bDescriptorType: Configuration */
    (USB_HID_CONFIG_DESC_SIZ & 0xFF),           /* wTotalLength: Bytes returned */
    ((USB_HID_CONFIG_DESC_SIZ >> 8) & 0xFF),    /* wTotalLength: Bytes returned */
    0x01,         /*bNumInterfaces: 1 interface*/
    0x01,         /*bConfigurationValue: Configuration value*/
    0x00,         /*iConfiguration: Index of string descriptor describing
    the configuration*/
    0xA0,         /*bmAttributes: bus powered and Support Remote Wake-up */
    0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

    /************** Descriptor of Joystick Mouse interface ****************/
    /* 09 */
    0x09,         /*bLength: Interface Descriptor size*/
    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
    0x00,         /*bInterfaceNumber: Number of Interface*/
    0x00,         /*bAlternateSetting: Alternate setting*/
    0x01,         /*bNumEndpoints*/
    0x03,         /*bInterfaceClass: HID*/
    0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0,            /*iInterface: Index of string descriptor*/
    
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,         /*bLength: HID Descriptor size*/
    HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
    0x11,         /*bcdHID: HID Class Spec release number*/
    0x01,
    0x21,         /*bCountryCode: Hardware target country*/
    0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
    0x22,         /*bDescriptorType*/
    (HID_MOUSE_REPORT_DESC_SIZE & 0xFF),/*wItemLength: Total length of Report descriptor*/
    ((HID_MOUSE_REPORT_DESC_SIZE >> 8) & 0xFF),/*wItemLength: Total length of Report descriptor*/
    
    /******************** Descriptor of Mouse endpoint ********************/
    /* 27 */
    0x07,          /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/
    HID_IN_EP,     /*bEndpointAddress: Endpoint Address (IN)*/
    0x03,          /*bmAttributes: Interrupt endpoint*/
    HID_IN_PACKET, /*wMaxPacketSize: 4 Byte max */
    0x00,
    0x01,          /*bInterval: Polling Interval (1 ms)*/
    /* 34 */
};

const uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE] =
{
  0x05,   0x01,
  0x09,   0x02,
  0xA1,   0x01,
  0x09,   0x01,
  
  0xA1,   0x00,
  0x95,   0x03,
  0x75,   0x01,
  0x05,   0x09,
  
  0x19,   0x01,
  0x29,   0x03,
  0x15,   0x00,
  0x25,   0x01,
  
  0x81,   0x02,
  0x95,   0x01,
  0x75,   0x05,
  0x81,   0x03,
  
  0x95,   0x03,
  0x75,   0x08,
  0x05,   0x01,
  0x09,   0x30,
  0x09,   0x31,
  0x09,   0x38,
  
  0x15,   0x81,
  0x25,   0x7F,
  0x81,   0x06,
  
  0xC0,   0xC0
};

/* Private function ----------------------------------------------------------*/ 
/**
  * @brief  USBD_HID_Init
  *         Initialize the HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_Init (void  *pdev, 
                               uint8_t cfgidx)
{
    DCD_PMA_Config(pdev, HID_IN_EP, USB_DBL_BUF, HID_IN_TX_ADDRESS);

    /* Open EP IN */
    DCD_EP_Open(pdev,
                HID_IN_EP,
                HID_IN_PACKET,
                USB_EP_INT);
    
    return USBD_OK;
}

/**
  * @brief  USBD_HID_Init
  *         DeInitialize the HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_DeInit (void  *pdev, 
                                 uint8_t cfgidx)
{
    /* Close HID EPs */
    DCD_EP_Close(pdev, HID_IN_EP);

    return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup
  *         Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t USBD_HID_Setup(void *pdev, 
                              USB_SETUP_REQ *req)
{
    uint16_t len = 0;
    uint8_t  *pbuf = NULL;

    switch (req->bmRequest & USB_REQ_TYPE_MASK)
    {
        case USB_REQ_TYPE_CLASS:
            switch (req->bRequest)
            {
                case HID_REQ_SET_PROTOCOL:
                    USBD_HID_Protocol = (uint8_t)(req->wValue);
                    break;

                case HID_REQ_GET_PROTOCOL:
                    USBD_CtlSendData(pdev,
                                     (uint8_t *)&USBD_HID_Protocol,
                                     1);
                    break;

                case HID_REQ_SET_IDLE:
                    USBD_HID_IdleState = (uint8_t)(req->wValue >> 8);
//                    USBD_HID_ReportDescState = 1;

                    break;

                case HID_REQ_GET_IDLE:
                    USBD_CtlSendData(pdev,
                                     (uint8_t *)&USBD_HID_IdleState,
                                     1);
                    break;

                default:
                    USBD_CtlError (pdev, req);
                    return USBD_FAIL; 
            }
            break;

        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest)
            {
                case USB_REQ_GET_DESCRIPTOR: 
                    if((req->wValue >> 8) == HID_REPORT_DESC)
                    {
                        len = MIN(HID_MOUSE_REPORT_DESC_SIZE, req->wLength);
                        pbuf = (uint8_t *)HID_MOUSE_ReportDesc;
                    }
                    else if((req->wValue >> 8) == HID_DESCRIPTOR_TYPE)
                    {
                        pbuf = (uint8_t *)USBD_HID_CfgDesc + 0x12;
                        len = MIN(USB_HID_DESC_SIZ , req->wLength);
                    }

                    USBD_CtlSendData(pdev,
                                     pbuf,
                                     len);

                    break;

                case USB_REQ_GET_INTERFACE:
                    USBD_CtlSendData(pdev,
                                     (uint8_t *)&USBD_HID_AltSet,
                                     1);
                    break;

                case USB_REQ_SET_INTERFACE:
                    USBD_HID_AltSet = (uint8_t)(req->wValue);
                    break;
            }
    }
    
    return USBD_OK;
}

/**
  * @brief  USBD_HID_SendReport 
  *         Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport(USB_CORE_HANDLE  *pdev, 
                            uint8_t *report,
                            uint16_t len)
{
    USB_EP *ep = &pdev->dev.in_ep[HID_IN_EP & 0x7F];

    if (ep->busy == 0)
    {
        /* Check if USB is configured */
//        if ((pdev->dev.device_status == USB_CONFIGURED) && (USBD_HID_ReportDescState))
        if ((pdev->dev.device_status == USB_CONFIGURED) && (1))
        {
            DCD_EP_Tx(pdev, HID_IN_EP, report, len);
        }
        
        return USBD_OK;
    }
    else
    {
        return USBD_BUSY;
    }
}

static uint8_t USBD_HID_Suspend(void)
{
    USB_EP *ep = &USB_Device_dev.dev.in_ep[HID_IN_EP & 0x7F];
    
    if (ep->busy == 1)
    {
        ep->busy = 0;
        
        FlushEPnTxFIFO();
        if (ep->doublebuffer)
            FlushEPnTxFIFO();
    }
    
    return USBD_OK;
}

/**
  * @brief  USBD_HID_GetCfgDesc 
  *         return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetCfgDesc (uint8_t speed, uint16_t *length)
{
    *length = sizeof(USBD_HID_CfgDesc);
    return (uint8_t *)USBD_HID_CfgDesc;
}

/************************ (C) COPYRIGHT MIC *****END OF FILE****/
