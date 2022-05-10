/**
  ******************************************************************************
  * @file    VTM071x_usart.c
  * @author  MIC Software Team 
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides all the USART firmware functions.
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

/* Includes ------------------------------------------------------------------*/
#include "VTM071x_usart.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup USART 
  * @brief USART driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup USART_Private_Defines
  * @{
  */

#define USART_LINECTRL_CLEAR_Mask           ((uint32_t)0x0000C001)
#define USART_CTRL2_CLEAR_Mask              ((uint32_t)0xFF8834FF)

#define USART_CTRL2_UE_BIT                  ((uint32_t)0x00000001) 				

#define USART_CTRL2_LBE_BIT                 ((uint32_t)0x00000080) 				

#define USART_LINECTRL_BRK_BIT              ((uint32_t)0x00000001) 				

#define USART_CTRL2_IREN_BIT                ((uint32_t)0x00000002)  /*!< USART IrDA Enable Mask */
#define USART_IRDA_CLEAR_Mask               ((uint32_t)0xFFFFFFFB)

#define USART_AUTOBAUD_EN_Set               ((uint16_t)0x0001)
#define USART_AUTOBAUD_EN_Reset             ((uint16_t)0xFFFE)
#define USART_AUTOBAUD_CLEAR_Mask           ((uint16_t)0xFFF9)

#define USART_INTR_IT_Mask                  ((uint32_t)0x00003FF0)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup USART_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the USARTx peripheral registers to their default reset values.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values: USARTx,x:[0:1].
  * @retval None
  */
void USART_DeInit(USART_TypeDef* USARTx)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    if (USARTx == USART0)
    {
        RCC_APBPeriphResetCmd(RCC_PRESETCTRL_USART0, ENABLE);
        RCC_APBPeriphResetCmd(RCC_PRESETCTRL_USART0, DISABLE);
    }
    else
    {
        RCC_APBPeriphResetCmd(RCC_PRESETCTRL_USART1, ENABLE);
        RCC_APBPeriphResetCmd(RCC_PRESETCTRL_USART1, DISABLE);
    }
}

/**
  * @brief  Initializes the USARTx peripheral according to the specified
  *   parameters in the USART_InitStruct .
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *   that contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
    uint32_t tmpreg = 0, USART_Freq = 0;
    uint32_t Baud_div,BAUD_DIVFRA,BAUD_DIVINT;
  
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));  
    assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
    assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
    assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
    assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
    assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
    assert_param(IS_USART_SoftwareFlowControl(USART_InitStruct->USART_SoftwareFlowControl));
    assert_param(IS_USART_TXIFLSEL(USART_InitStruct->USART_TXIFLSEL));
    assert_param(IS_USART_RXIFLSEL(USART_InitStruct->USART_RXIFLSEL));
    assert_param(IS_USART_FEN(USART_InitStruct->USART_FEN));

    /*---------------------------- USART LINECTRL Configuration -----------------------*/
    tmpreg = USARTx->LINECTRL;
    tmpreg &= USART_LINECTRL_CLEAR_Mask;

    if(USARTx == USART0)
      USART_Freq = RCC_GetClocksFreq(RCC_CLOCKFREQ_USART0CLK);
    else if(USARTx == USART1)
      USART_Freq = RCC_GetClocksFreq(RCC_CLOCKFREQ_USART1CLK);

    Baud_div = (USART_Freq * 4) / (USART_InitStruct->USART_BaudRate);
    BAUD_DIVFRA = (Baud_div & 0x3f)<<8;
    BAUD_DIVINT = ((Baud_div & 0x3fffc0) >> 6) << 16;
    tmpreg  |= 	BAUD_DIVINT | BAUD_DIVFRA | USART_InitStruct->USART_WordLength |
    USART_InitStruct->USART_StopBits | USART_InitStruct->USART_Parity|
    USART_InitStruct->USART_FEN;
    USARTx->LINECTRL = tmpreg;

    /*---------------------------- USART CTRL2 Configuration -----------------------*/
    tmpreg = USARTx->CTRL2;
    tmpreg &= USART_CTRL2_CLEAR_Mask;
    tmpreg |= USART_InitStruct->USART_TXIFLSEL | USART_InitStruct->USART_RXIFLSEL |
    USART_InitStruct->USART_Mode | USART_InitStruct->USART_HardwareFlowControl | 
    USART_InitStruct->USART_SoftwareFlowControl;
    USARTx->CTRL2 = tmpreg;
}

/**
  * @brief  Fills each USART_InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *   which will be initialized.
  * @retval None
  */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
    /* USART_InitStruct members default value */
    USART_InitStruct->USART_TXIFLSEL = USART_TXIFLSEL_16;
    USART_InitStruct->USART_RXIFLSEL = USART_RXIFLSEL_16;
    USART_InitStruct->USART_FEN = USART_FEN_Enable;
    USART_InitStruct->USART_BaudRate = 115200;
    USART_InitStruct->USART_WordLength = USART_WordLength_8b;
    USART_InitStruct->USART_StopBits = USART_StopBits_1;
    USART_InitStruct->USART_Parity = USART_Parity_No ;
    USART_InitStruct->USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
    USART_InitStruct->USART_SoftwareFlowControl = USART_SoftwareFlowControl_None;	
}

/**
  * @brief  Enables or disables the specified USART peripheral.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected USART by setting the UE bit in the CTRL2 register */
        USARTx->CTRL2_SET = USART_CTRL2_UE_BIT;
    }
    else
    {
        /* Disable the selected USART by clearing the UE bit in the CTRL2 register */
        USARTx->CTRL2_CLR = USART_CTRL2_UE_BIT;
    }
}

/**
  * @brief  Enables or disables TX DMA Mode.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_TXDMACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected USART by setting TX DMA bit in the CTRL2 register */
        USARTx->CTRL2_SET = USART_CTRL2_TXDMAE;
        USARTx->CTRL1_SET = 0x10000000;
    }
    else
    {
        /* Disable the selected USART by clearing TX DMA bit in the CTRL2 register */
        USARTx->CTRL2_CLR = USART_CTRL2_TXDMAE;
        USARTx->CTRL1_CLR = 0x10000000;
    }
}

/**
  * @brief  Enables or disables RX DMA Mode.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_RXDMACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected USART by setting RX DMA bit in the CTRL2 register */
        USARTx->CTRL2_SET = USART_CTRL2_RXDMAE;
        USARTx->CTRL0_SET = 0x10000000;
    }
    else
    {
        /* Disable the selected USART by clearing RX DMA bit in the CTRL2 register */
        USARTx->CTRL2_CLR = USART_CTRL2_RXDMAE;
        USARTx->CTRL0_CLR = 0x10000000;
    }
}

/**
  * @brief  Enables or disables the Loop-Back Mode.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_LBECmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected USART by setting the LBE bit in the CTRL2 register */
        USARTx->CTRL2_SET = USART_CTRL2_LBE_BIT;
    }
    else
    {
        /* Disable the selected USART by clearing the LBE bit in the CTRL2 register */
        USARTx->CTRL2_CLR = USART_CTRL2_LBE_BIT;
    }
}

/**
  * @brief  Enables or disables the BRK.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_BRKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected USART by setting the BRK bit in the CTRL2 register */
        USARTx->LINECTRL_SET = USART_LINECTRL_BRK_BIT;
    }
    else
    {
        /* Disable the selected USART by clearing the BRK bit in the CTRL2 register */
        USARTx->LINECTRL_CLR = USART_LINECTRL_BRK_BIT;
    }
}

/**
  * @brief  Enables or disables LIN.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        USARTx->LINCTRL &= USART_LINCTRL_EN;
    }
    else
    {
        USARTx->LINCTRL &= ~USART_LINCTRL_EN;
    }
}

/**
  * @brief  Send break.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @retval None
  */
void USART_SendBreak(USART_TypeDef* USARTx)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    USARTx->LINCTRL |= USART_LINCTRL_SBK;
}

/**
  * @brief  Enables or disables STTTO.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_STTTOCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        USARTx->RXTIMEOUT |= USART_RXTIMEROUT_STTTO;
    }
    else
    {
        USARTx->RXTIMEOUT &= ~USART_RXTIMEROUT_STTTO;
    }
}

/**
  * @brief  Enables or disables RETTO.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_RETTOCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        USARTx->RXTIMEOUT |= USART_RXTIMEROUT_RETTO;
    }
    else
    {
        USARTx->RXTIMEOUT &= ~USART_RXTIMEROUT_RETTO;
    }
}

/**
  * @brief  Configure RXTO count.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  RXTO_Count: receive timeout count.
  *   This parameter can be: 24bit.
  * @retval None
  */
void USART_RXTOCountConfig(USART_TypeDef* USARTx, uint32_t RXTO_Count)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_RXTOCOUNT(RXTO_Count));

    tmpreg = USARTx->RXTIMEOUT;
    tmpreg &= ~USART_RXTIMEROUT_COUNT_MASK;
    tmpreg |= RXTO_Count;
    USARTx->RXTIMEOUT = tmpreg;
}

/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  USARTx: Select the USARTperipheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_IT: specifies the USART interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg USART_IT_LBDIE: LIN Interrupt Enable.
  *     @arg USART_IT_RXTOEN: Receive Timeout Interrupt Enable.
  *     @arg USART_IT_RXIEN: Receive Interrupt Enable.
  *     @arg USART_IT_TXIEN: Transmit Interrupt Enable.
  *     @arg USART_IT_RTIEN: Receive Timeout Interrupt Enable.
  *     @arg USART_IT_FEIEN: Framing Error Interrupt Enable.
  *     @arg USART_IT_PEIEN: Parity Error Interrupt Enable.
  *     @arg USART_IT_BEIEN: Break Error Interrupt Enable.
  *     @arg USART_IT_OEIEN: Overrun Error Interrupt Enable.
  *     @arg USART_IT_TFEIEN:Tx FIFO EMPTY Raw Interrupt Enable.
  *     @arg USART_IT_ABEOEN:Autobaud End Interrupt Enable.
  *     @arg USART_IT_ABTOEN:Autobaud Timeout Interrupt Enable.
  * @param  NewState: new state of the specified USARTx interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CONFIG_IT(USART_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected USART by setting the USART_IT bit in the INTR register */
        if (USART_IT == USART_IT_LBDIE)
            USARTx->LINCTRL |= USART_IT_LBDIE;
        else if (USART_IT == USART_IT_RXTOEN)
            USARTx->RXTIMEOUT |= (USART_IT_RXTOEN & (~USART_IT_RXTOFLAG));
        else
            USARTx->INTR_SET = USART_IT;
    }
    else
    {
        /* Disable the selected USART by clearing the USART_IT bit in the INTR register */
        if (USART_IT == USART_IT_LBDIE)
            USARTx->LINCTRL &= ~USART_IT_LBDIE;
        else if (USART_IT == USART_IT_RXTOEN)
            USARTx->RXTIMEOUT &= ~(USART_IT_RXTOEN & (~USART_IT_RXTOFLAG));
        else
            USARTx->INTR_CLR = USART_IT;
    }
}

/**
  * @brief  Transmits single data through the USARTx peripheral.
  * @param  USARTx: Select the USART operipheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  Data: the data to transmit.
  * @retval None
  */
void USART_SendData(USART_TypeDef* USARTx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* Transmit Data */
    USARTx->DATA = Data;
}

/**
  * @brief  Returns the most recent received data by the USARTx peripheral.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @retval The received data.
  */
uint32_t USART_ReceiveData(USART_TypeDef* USARTx)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* Receive Data */
    return (USARTx->DATA);
}


/**
  * @brief  Configures the USARTx IrDA interface.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_IrDAMode: specifies the IrDA mode.
  *   This parameter can be one of the following values:
  *     @arg USART_IrDAMode_LowPower
  *     @arg USART_IrDAMode_Normal
  * @retval None
  */
void USART_IrDAConfig(USART_TypeDef* USARTx, uint32_t USART_IrDAMode)
{
    uint32_t tmpreg=0;

    /* Check the parameters */
    assert_param(IS_USART_IRDA_PERIPH(USARTx));
    assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));

    tmpreg = USARTx->CTRL2;
    tmpreg &= USART_IRDA_CLEAR_Mask;
    tmpreg |= USART_IrDAMode;
    USARTx->CTRL2 = tmpreg;
}

/**
  * @brief  Enables or disables the USARTx IrDA interface.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the IrDA mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_IRDA_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the IrDA mode by setting the IREN bit in the CTRL2 register */
        USARTx->CTRL2_SET = USART_CTRL2_IREN_BIT;
    }
    else
    {
        /* Disable the IrDA mode by clearing the IREN bit in the CTRL2 register */
        USARTx->CTRL2_CLR = USART_CTRL2_IREN_BIT;
    }
}

/**
  * @brief  Initializes the USARTx peripheral according to the specified
  *   parameters in the USART_RS485InitStruct .
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_RS485InitStruct: pointer to a USART_RS485InitTypeDef structure
  *   that contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void USART_RS485Init(USART_TypeDef* USARTx, USART_RS485InitTypeDef* USART_RS485InitStruct)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_RS485_NMM(USART_RS485InitStruct->USART_RS485_MODE));
    assert_param(IS_USART_RS485_DCTRL(USART_RS485InitStruct->USART_RS485_DCTRL));
    assert_param(IS_USART_RS485_ONIV_MODE(USART_RS485InitStruct->USART_RS485_ONIV));

    USARTx->RS485CTRL = USART_RS485InitStruct->USART_RS485_MODE | USART_RS485InitStruct->USART_RS485_DCTRL | USART_RS485InitStruct->USART_RS485_ONIV;
}

/**
  * @brief  Fills each USART_RS485InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a USART_RS485InitTypeDef structure
  *   which will be initialized.
  * @retval None
  */
void USART_RS485StructInit(USART_RS485InitTypeDef* USART_RS485InitStruct)
{
    USART_RS485InitStruct->USART_RS485_MODE = USART_RS485_NMM_AAD;
    USART_RS485InitStruct->USART_RS485_DCTRL = USART_RS485_DCTRL_RTS;
    USART_RS485InitStruct->USART_RS485_ONIV = USART_RS485_ONIV_MODE_0;
}

/**
  * @brief  Sets the address of the USART_RS485.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_Address: The Address of USART_RS485.
  * @retval None
  */
void USART_RS485SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    USARTx->RS485ADRMATCH = USART_Address;
}

/**
  * @brief  Sets the delay time of controling direction.
  * @param  USARTx: Select the USART or the HUSART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_DLYTime: The delay time of controling direction.
  * @retval None
  */
void USART_RS485SetDelay(USART_TypeDef* USARTx, uint8_t USART_DLYTime)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    USARTx->RS485DLY = USART_DLYTime;
}

/**
  * @brief  Configures the USARTx AUTOBAUD interface.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_AUTOBAUDMODE: specifies the AUTOBAUD mode.
  *   This parameter can be one of the following values:
  *     @arg USART_AUTOBAUD_MODE_RE_0
  *     @arg USART_AUTOBAUD_MODE_RE_1
  *     @arg USART_AUTOBAUD_MODE_RD_0
  *     @arg USART_AUTOBAUD_MODE_RD_1
  * @retval None
  */
void USART_AUTOBAUDConfig(USART_TypeDef* USARTx, uint16_t USART_AUTOBAUDMODE)
{
    uint16_t tmpreg=0;
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_AUTOBAUD_MODE(USART_AUTOBAUDMODE));

    tmpreg = USARTx->AUTOBAUD;
    tmpreg &= USART_AUTOBAUD_CLEAR_Mask;
    tmpreg |= USART_AUTOBAUDMODE;
    USARTx->AUTOBAUD = tmpreg;
}

/**
  * @brief  Enables or disables the USARTx AUTOBAUD interface.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  NewState: new state of the AUTOBAUD mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void USART_AUTOBAUDCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState)); 
    if (NewState != DISABLE)
    {
        /* Start AUTOBAUD */
        USARTx->AUTOBAUD |= USART_AUTOBAUD_EN_Set;
    }
    else
    {
        /* Stop AUTOBAUD */
        USARTx->AUTOBAUD &= USART_AUTOBAUD_EN_Reset;
    }
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg USART_FLAG_FERR:  Framing Error Flag.
  *     @arg USART_FLAG_PERR:  Parity Error Flag.
  *     @arg USART_FLAG_BERR:  Break Error Flag.
  *     @arg USART_FLAG_OERR:  Overrun Error Flag.
  *     @arg USART_FLAG_RXFE:  Receive FIFO Empty Flag.
  *     @arg USART_FLAG_TXFF:  Transmit FIFO Full Flag.
  *     @arg USART_FLAG_RXFF:  Receive FIFO Full Flag.
  *     @arg USART_FLAG_TXFE:  Transmit FIFO Empty Flag.
  *     @arg USART_FLAG_CTS:   Clear To Send Flag.
  *     @arg USART_FLAG_BUSY:  USART Busy Flag.
  * @retval The new state of USART_FLAG (SET or RESET).
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
    FlagStatus bitstatus = RESET;
  
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_FLAG(USART_FLAG));
  
    /* The CTS flag is not available for USART4 and USART5 */
    if (USART_FLAG == USART_FLAG_CTS)
    {
        assert_param(IS_USART_FC_PERIPH(USARTx));
    }  

    if ((USARTx->STAT & USART_FLAG) != RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    
    return bitstatus;
}

/**
  * @brief  Clears the USARTx's pending flags.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg USART_FLAG_FERR:  Framing Error Flag.
  *     @arg USART_FLAG_PERR:  Parity Error Flag.
  *     @arg USART_FLAG_BERR:  Break Error Flag.
  *     @arg USART_FLAG_OERR:  Overrun Error Flag.   
  * @retval None
  */
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));

    USARTx->STAT &= ~USART_FLAG;
}

/**
  * @brief  Checks whether the specified USART interrupt has occurred or not.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_IT: specifies the USART interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg USART_IT_LBDIS:  LIN Interrupt Status.
  *     @arg USART_IT_RXTOIS: Receive Timeout Interrupt Status.
  *     @arg USART_IT_CTSMIS: CTS Interrupt .
  *     @arg USART_IT_RXIS:   Receive Interrupt Status.
  *     @arg USART_IT_TXIS:   Transmit Interrupt Status.
  *     @arg USART_IT_RTIS:   Receive Timeout Interrupt Status.
  *     @arg USART_IT_FEIS:   Framing Error Interrupt Status.
  *     @arg USART_IT_PEIS:   Parity Error Interrupt Status.
  *     @arg USART_IT_BEIS:   Break Error Interrupt Status.
  *     @arg USART_IT_OEIS:   Overrun Error Interrupt Status.
  *     @arg USART_IT_TFEIS:  Tx FIFO EMPTY Raw Interrupt state.
  *     @arg USART_IT_ABEO:   AUTOBAUD End state.
  *     @arg USART_IT_ABTO:   AUTOBAUD TimeOut state.
  * @retval The new state of USART_IT (SET or RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT)
{
    ITStatus bitstatus = RESET, enablestatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_GET_IT(USART_IT));

    if (USART_IT == USART_IT_LBDIS)
    {
        if ((USARTx->LINCTRL & USART_IT_LBDIE) != RESET)
        {
            enablestatus = SET;
        }
    }
    else if (USART_IT == USART_IT_RXTOIS)
    {
        if ((USARTx->RXTIMEOUT & USART_RXTIMEROUT_IE) != RESET)
        {
            enablestatus = SET;
        }
    }
    else 
    {
        if((USARTx->INTR & (USART_IT << 16)) != RESET)
        {
            enablestatus = SET;
        }
    }    
    
    if (USART_IT == USART_IT_LBDIS)
    {
        if (enablestatus && ((USARTx->LINCTRL & (USART_IT_LBDIS & (~USART_IT_LINFLAG))) != RESET))
            bitstatus = SET;
        else
            bitstatus = RESET;
    }
    else if (USART_IT == USART_IT_RXTOIS)
    {
        if (enablestatus && ((USARTx->RXTIMEOUT & USART_IT_RXTOIS) != RESET))
            bitstatus = SET;
        else
            bitstatus = RESET;
    }
    else 
    {
        if(enablestatus && ((USARTx->INTR & USART_IT) != RESET))
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    return bitstatus;  
}

/**
  * @brief  Clears the USARTx interrupt pending bits.
  * @param  USARTx: Select the USART peripheral. 
  *   This parameter can be one of the following values:
  *   USARTx,x:[0:1].
  * @param  USART_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg USART_IT_LBDIS:  LIN Interrupt Status.
  *     @arg USART_IT_RXTOIS: Receive Timeout Interrupt Status.
  *     @arg USART_IT_CTSMIS: CTS Interrupt .
  *     @arg USART_IT_RXIS:   Receive Interrupt .
  *     @arg USART_IT_TXIS:   Transmit Interrupt .
  *     @arg USART_IT_RTIS:   Receive Timeout Interrupt .
  *     @arg USART_IT_FEIS:   Framing Error Interrupt .
  *     @arg USART_IT_PEIS:   Parity Error Interrupt .
  *     @arg USART_IT_BEIS:   Break Error Interrupt .
  *     @arg USART_IT_OEIS:   Overrun Error Interrupt .
  *     @arg USART_IT_TFEIS:  Tx FIFO EMPTY Raw Interrupt .
  *     @arg USART_IT_ABEOIntClr: AUTOBAUD End Interrupt.
  *     @arg USART_IT_ABTOIntClr: AUTOBAUD TimeOut Interrupt.
  * @retval None
  */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint32_t USART_IT)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_IT(USART_IT));

    if ((USART_IT == USART_IT_ABEOIntClr) || (USART_IT == USART_IT_ABTOIntClr))
    {
        USARTx->AUTOBAUD |= USART_IT >> 16;
    }
    else if (USART_IT == USART_IT_LBDIS)
    {
        USARTx->LINCTRL &= ~(USART_IT_LBDIS & (~USART_IT_LINFLAG));
    }
    else if (USART_IT == USART_IT_RXTOIS)
    {
        USARTx->RXTIMEOUT &= ~USART_IT_RXTOIS;
    }
    else
    {
        USARTx->INTR_CLR = USART_IT;
    }
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT MIC *****END OF FILE****/

