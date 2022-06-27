
#include "usbd_cdc_vcp.h"

LINE_CODING linecoding =
{
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* nb. of bits 8*/
};

USART_InitTypeDef USART_InitStructure;

extern uint8_t  APP_Rx_Buffer [];
extern uint32_t APP_Rx_ptr_in;

{{usbd_cdc_vcp_c_var}}

static uint16_t VCP_Init     (void);
static uint16_t VCP_DeInit   (void);
static uint16_t VCP_Ctrl     (uint32_t Cmd, uint8_t* Buf, uint32_t Len);
static uint16_t VCP_DataTx   (uint8_t* Buf, uint32_t Len);
static uint16_t VCP_DataRx   (uint8_t* Buf, uint32_t Len);

static uint16_t VCP_COMConfig(uint8_t Conf);

CDC_IF_Prop_TypeDef VCP_fops = 
{
    VCP_Init,
    VCP_DeInit,
    VCP_Ctrl,
    VCP_DataTx,
    VCP_DataRx
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  VCP_Init
  *         Initializes the Media on the MIC
  * @param  None
  * @retval Result of the operation (USBD_OK in all cases)
  */
static uint16_t VCP_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* USART0 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - Parity None
        - Hardware flow control disabled
        - Receive and transmit enabled
    */
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, 1);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO1, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIO1, &GPIO_InitStructure);

    USART_DeInit(USART0);
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_Init(USART0, &USART_InitStructure);
    
    /* Enable the USART Receive interrupt */
    USART_ITConfig(USART0, USART_IT_RXIEN, ENABLE);
    USART_ITConfig(USART0, USART_IT_RXTOEN, ENABLE);
    
    USART_Cmd(USART0, ENABLE);

    /* Enable USART Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = USART_IT_PRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    return USBD_OK;
}

/**
  * @brief  VCP_DeInit
  *         DeInitializes the Media on the MIC
  * @param  None
  * @retval Result of the opeartion (USBD_OK in all cases)
  */
static uint16_t VCP_DeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    uint32_t timeout = 0;

    while (USART_GetFlagStatus(USART0, USART_FLAG_TXFE) == RESET)
    {
        timeout++;
        if (timeout > 0x10000)
            break;
    }
    
    USART_Cmd(USART0, DISABLE);
    USART_DeInit(USART0);
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0, DISABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO1, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIO1, &GPIO_InitStructure);

    /* Disable USART Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = USART_IT_PRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    return USBD_OK;
}

/**
  * @brief  VCP_Ctrl
  *         Manage the CDC class requests
  * @param  Cmd: Command code            
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation (USBD_OK in all cases)
  */
static uint16_t VCP_Ctrl(uint32_t Cmd, uint8_t* Buf, uint32_t Len)
{
    switch (Cmd)
    {
        case SEND_ENCAPSULATED_COMMAND:
            /* Not  needed for this driver */
        break;

        case GET_ENCAPSULATED_RESPONSE:
            /* Not  needed for this driver */
        break;

        case SET_COMM_FEATURE:
            /* Not  needed for this driver */
        break;

        case GET_COMM_FEATURE:
            /* Not  needed for this driver */
        break;

        case CLEAR_COMM_FEATURE:
            /* Not  needed for this driver */
        break;

        case SET_LINE_CODING:
            linecoding.bitrate = (uint32_t)(Buf[0] | (Buf[1] << 8) | (Buf[2] << 16) | (Buf[3] << 24));
            linecoding.format = Buf[4];
            linecoding.paritytype = Buf[5];
            linecoding.datatype = Buf[6];
            /* Set the new configuration */
            VCP_COMConfig(OTHER_CONFIG);
        break;

        case GET_LINE_CODING:
            Buf[0] = (uint8_t)(linecoding.bitrate);
            Buf[1] = (uint8_t)(linecoding.bitrate >> 8);
            Buf[2] = (uint8_t)(linecoding.bitrate >> 16);
            Buf[3] = (uint8_t)(linecoding.bitrate >> 24);
            Buf[4] = linecoding.format;
            Buf[5] = linecoding.paritytype;
            Buf[6] = linecoding.datatype; 
        break;

        case SET_CONTROL_LINE_STATE:
            /* Not  needed for this driver */
        break;

        case SEND_BREAK:
            /* Not  needed for this driver */
        break;    

        default:
        break;
    }

    return USBD_OK;
}

/**
  * @brief  VCP_DataTx
  *         CDC received data to be send over USB IN endpoint are managed in 
  *         this function.
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else VCP_FAIL
  */
static uint16_t VCP_DataTx (uint8_t* Buf, uint32_t Len)
{
    {{usbd_cdc_vcp_c_VCP_DataTx}}

    return USBD_OK;
}

/**
  * @brief  VCP_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface 
  *         through this function.
  * @note   This function will block any OUT packet reception on USB endpoint 
  *         untill exiting this function. If you exit this function before transfer
  *         is complete on CDC interface (ie. using DMA controller) it will result 
  *         in receiving more data while previous ones are still not sent.
  *                 
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else VCP_FAIL
  */
static uint16_t VCP_DataRx (uint8_t* Buf, uint32_t Len)
{
    uint32_t i;

    for (i = 0; i < Len; i++)
    {
        while(USART_GetFlagStatus(USART0, USART_FLAG_TXFF) == SET);
        USART_SendData(USART0, *(Buf + i));
    }
    while(USART_GetFlagStatus(USART0, USART_FLAG_TXFE) == RESET); 

    return USBD_OK;
}

/**
  * @brief  VCP_COMConfig
  *         Configure the COM Port with default values or values received from host.
  * @param  Conf: can be DEFAULT_CONFIG to set the default configuration or OTHER_CONFIG
  *         to set a configuration received from the host.
  * @retval None.
  */
static uint16_t VCP_COMConfig(uint8_t Conf)
{
    if (Conf == DEFAULT_CONFIG)  
    {
        /* EVAL_COM1 default configuration */
        /* EVAL_COM1 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - Parity None
        - Hardware flow control disabled
        - Receive and transmit enabled
        */
        USART_DeInit(USART0);
        USART_StructInit(&USART_InitStructure);
        USART_InitStructure.USART_BaudRate = 115200;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_Init(USART0, &USART_InitStructure);
        
        /* Enable the USART Receive interrupt */
        USART_ITConfig(USART0, USART_IT_RXIEN, ENABLE);
        USART_ITConfig(USART0, USART_IT_RXTOEN, ENABLE);

        USART_Cmd(USART0, ENABLE);
    }
    else
    {
        /* set the Stop bit*/
        switch (linecoding.format)
        {
            case 0:
                USART_InitStructure.USART_StopBits = USART_StopBits_1;
                break;
            case 2:
                USART_InitStructure.USART_StopBits = USART_StopBits_2;
                break;
            default :
                VCP_COMConfig(DEFAULT_CONFIG);
                return (USBD_FAIL);
        }

        /* set the parity bit*/
        switch (linecoding.paritytype)
        {
            case 0:
                USART_InitStructure.USART_Parity = USART_Parity_No;
                break;
            case 1:
                USART_InitStructure.USART_Parity = USART_Parity_Odd;
                break;
            case 2:
                USART_InitStructure.USART_Parity = USART_Parity_Even;
                break;
            case 3:
                USART_InitStructure.USART_Parity = USART_Parity_EPS_1;
                break;
            case 4:
                USART_InitStructure.USART_Parity = USART_Parity_EPS_0;
                break;
            default :
                VCP_COMConfig(DEFAULT_CONFIG);
                return (USBD_FAIL);
        }

        /*set the data type : only 8bits and 9bits is supported */
        switch (linecoding.datatype)
        {
            case 0x05:
                USART_InitStructure.USART_WordLength = USART_WordLength_5b;
                break;
            case 0x06:
                USART_InitStructure.USART_WordLength = USART_WordLength_6b;
                break;
            case 0x07:
                USART_InitStructure.USART_WordLength = USART_WordLength_7b;
                break;
            case 0x08:
                USART_InitStructure.USART_WordLength = USART_WordLength_8b;
                break;
            default:
                VCP_COMConfig(DEFAULT_CONFIG);
                return (USBD_FAIL);
        }

        USART_InitStructure.USART_BaudRate = linecoding.bitrate;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

        /* Configure and enable the USART */
        USART_Init(USART0, &USART_InitStructure);
        USART_Cmd(USART0, ENABLE);
    }
    
    return USBD_OK;
}

/**
  * @brief  EVAL_COM_IRQHandler
  * @param  None.
  * @retval None.
  */
void USART0_IRQHandler(void)
{
    {{usbd_cdc_vcp_c_USART0_IRQHandler}}
}