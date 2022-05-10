/**
  ******************************************************************************
  * @file    VTM071x_i2c.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Inter-integrated circuit (I2C)
  *           - Initialization and Configuration
  *           - Data transfers
  *           - Interrupts, events and flags management        
  *  
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
#include "VTM071x_i2c.h"
#include "VTM071x_rcc.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C 
  * @brief I2C driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_XBIT_SLAVE_SHIFT        3
#define I2C_XBIT_MASTER_SHIFT       4
#define I2C_DATA_CMD_CMD_READ       ((uint32_t)0x00000100)
#define I2C_DATA_CMD_CMD_WRITE      ((uint32_t)0x00000000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup I2C_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the I2C peripheral registers to their default reset values.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @retval None
  */
void I2C_DeInit(I2C_TypeDef * I2Cx)
{
    /* Check the I2C parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    if (I2Cx == I2C0)
    {
        /* Enable I2C reset state */
        RCC_APBPeriphResetCmd(RCC_PRESETCTRL_I2C0, ENABLE);
        /* Release I2C from reset state */
        RCC_APBPeriphResetCmd(RCC_PRESETCTRL_I2C0, DISABLE);
    }
    else
    {
        /* Enable I2C reset state */
        RCC_APBPeriphResetCmd(RCC_PRESETCTRL_I2C1, ENABLE);
        /* Release I2C from reset state */
        RCC_APBPeriphResetCmd(RCC_PRESETCTRL_I2C1, DISABLE);
    }
}

/**
  * @brief  Initializes the I2C peripheral according to the specified 
  *         parameters in the I2C_InitStruct.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that contains 
  *         the configuration information for the specified I2C peripheral.
  * @retval None.
  */
void I2C_Init(I2C_TypeDef * I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
    uint32_t tmpreg = 0;
    
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_Mode(I2C_InitStruct->I2C_Mode));
    assert_param(IS_I2C_Xbit_Address(I2C_InitStruct->I2C_XbitAddress));
    assert_param(IS_I2C_Speed_MODE(I2C_InitStruct->I2C_ClockSpeed));  
    assert_param(IS_I2C_Restart_Mode(I2C_InitStruct->I2C_RestartMode));  

    tmpreg = I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_RestartMode | I2C_InitStruct->I2C_ClockSpeed;
    if (I2C_InitStruct->I2C_Mode == I2C_MODE_MASTER)
        tmpreg |= I2C_InitStruct->I2C_XbitAddress << I2C_XBIT_MASTER_SHIFT;
    else
        tmpreg |= I2C_InitStruct->I2C_XbitAddress << I2C_XBIT_SLAVE_SHIFT;
    
    I2Cx->CON = tmpreg;
}

/**
  * @brief  Controls whether the DW_apb_i2c is enabled.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  NewState: new state of the I2C peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_Cmd(I2C_TypeDef * I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        I2Cx->ENABLE |= I2C_ENABLE_ENABLE;
    }
    else
    {
        I2Cx->ENABLE &= ~I2C_ENABLE_ENABLE;
    }
}

/**
  * @brief  Configure special cmd.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  SpecialCmd: Special cmd.
  * @retval None.
  */
void I2C_SpecialCmdConfig(I2C_TypeDef * I2Cx, uint32_t SpecialCmd)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_SPECIAL_CMD(SpecialCmd));

    tmpreg = I2Cx->TAR;
    tmpreg &= ~(I2C_TAR_GC_OR_START | I2C_TAR_SPECIAL);
    tmpreg |= SpecialCmd;
    I2Cx->TAR = tmpreg;
}

/**
  * @brief  Configure target address when I2C mode is master.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  SarAddr: Target address.
  * @retval None.
  */
void I2C_TARConfig(I2C_TypeDef * I2Cx, uint32_t TarAddr)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_TAR(TarAddr));

    tmpreg = I2Cx->TAR;
    tmpreg &= ~I2C_TAR_TAR0_9;
    tmpreg |= TarAddr;
    I2Cx->TAR = tmpreg;
}

/**
  * @brief  Configure slave address when I2C mode is slave.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  SarAddr: Slave address.
  * @retval None.
  */
void I2C_SARConfig(I2C_TypeDef * I2Cx, uint32_t SarAddr)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_SAR(SarAddr));

    tmpreg = I2Cx->SAR;
    tmpreg &= ~I2C_SAR_SAR0_9;
    tmpreg |= SarAddr;
    I2Cx->SAR = tmpreg;
}

/**
  * @brief  Configure master code of high speed.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  HSMasterCode: Master code of high speed bit[0:2].
  * @retval None.
  */
void I2C_HSMasterCodeConfig(I2C_TypeDef * I2Cx, uint32_t HSMasterCode)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_HSMasterCode(HSMasterCode));

    I2Cx->HS_MADDR = HSMasterCode;
}

/**
  * @brief  Configure SCLK high count and low count.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  HCNT: SCLK high count.
  * @param  LCNT: SCLK low count.
  * @param  ClockSpeed: I2C speed mode.
  * @note   Computing method:
  ***********************************************************************
  *         OSCFREQ = ic_clk Clock Frequency (Hz).
  *         MIN_SCL_HIGHtime = Minimum High Period
  *         MIN_SCL_LOWtime = Minimum Low Period
  *
  *         MIN_SCL_HIGHtime = 4000 ns for 100 kbps
  *                            600 ns for 400 kbps
  *                            60 ns for 3.4 Mbs, bus loading = 100pF
  *                            160 ns for 3.4 Mbs, bus loading = 400pF
  *
  *         MIN_SCL_LOWtime = 4700 ns for 100 kbps
  *                           1300 ns for 400 kbps
  *                           120 ns for 3.4Mbs, bus loading = 100pF
  *                           320 ns for 3.4Mbs, bus loading = 400pF
  *
  *         For example(1):
  *                     OSCFREQ = 48M, I2CMode = fs(400kbps)
  *                     MIN_SCL_HIGHtime = 600ns
  *                     MIN_SCL_LOWtime = 1300ns
  *                     FS_SCL_HCNT = 600ns / (1000 / 48)ns  * (2500 / (600ns + 1300ns))= 37.9
  *                     FS_SCL_LCNT = 1300ns / (1000 / 48)ns * (2500 / (600ns + 1300ns))= 82.1
  *
  *                     FS_SCL_HCNT = 38
  *                     FS_SCL_LCNT = 82
  *
  *         For example(2):
  *                     OSCFREQ = 72M, I2CMode = ss(100kbps)
  *                     MIN_SCL_HIGHtime = 4000ns
  *                     MIN_SCL_LOWtime = 4700ns
  *                     FS_SCL_HCNT = 4000ns / (1000 / 72)ns * (10000ns / (4000ns + 4700ns)) = 331.0
  *                     FS_SCL_LCNT = 4700ns / (1000 / 72)ns * (10000ns / (4000ns + 4700ns)) = 389.0
  *
  *                     FS_SCL_HCNT = 331
  *                     FS_SCL_LCNT = 389
  *
  *         Note: The MIN_SCL_HIGHtime and MIN_SCL_LOWtime is specified by I2C protocol.
  ***********************************************************************
  * @retval None.
  */
void I2C_SCLKCountConfig(I2C_TypeDef * I2Cx, uint32_t HCNT, uint32_t LCNT, uint32_t ClockSpeed)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_HCNT(HCNT));
    assert_param(IS_I2C_LCNT(LCNT));
    assert_param(IS_I2C_Speed_MODE(ClockSpeed));

    if (ClockSpeed == I2C_CLOCK_STANDARD_MODE)
    {
        I2Cx->SS_SCL_HCNT = HCNT;
        I2Cx->SS_SCL_LCNT = LCNT;
    }
    else if (ClockSpeed == I2C_CLOCK_FAST_MODE)
    {
        I2Cx->FS_SCL_HCNT = HCNT;
        I2Cx->FS_SCL_LCNT = LCNT;
    }
    else
    {
        I2Cx->HS_SCL_HCNT = HCNT;
        I2Cx->HS_SCL_LCNT = LCNT;
    }
}

/**
  * @brief  Configure SDA setup time(tSU:DAT).
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  SU_DAT: SDA setup time.
  * @note   Suggested values:
  *         1750ns for SS mode(100kbps)
  *         750ns for FS mode(400kbps)
  *         100 ns for HS mode, 3.4Mbs, bus loading = 100pF
  *         250 ns for HS mode, 3.4Mbs, bus loading = 400pF
  *         For example(1):
  *                     OSCFREQ = 72M, I2CMode = ss(100kbps)
  *                     SU_DAT = 1750ns / (1000 / 72)ns = 126
  *         For example(2):
  *                     OSCFREQ = 48M, I2CMode = fs(400kbps)
  *                     SU_DAT = 750ns / (1000 / 48)ns = 36
  * @retval None.
  */
void I2C_SDASetupConfig(I2C_TypeDef * I2Cx, uint32_t SU_DAT)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_SU_DAT(SU_DAT));

    I2Cx->SDA_SETUP = SU_DAT + 1;
}

/**
  * @brief  Sends a data byte through the I2C peripheral.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_TypeDef * I2Cx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    /* Write in the DR register the data to be sent */
    I2Cx->DATA_CMD = (uint32_t)Data | I2C_DATA_CMD_CMD_WRITE;
}

/**
  * @brief  Trigger data receiving.
  * @param  I2C: the target I2C peripheral.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @retval None.
  */
void I2C_TriggerRecData(I2C_TypeDef * I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    I2Cx->DATA_CMD = I2C_DATA_CMD_CMD_READ;
}

/**
  * @brief  Returns the most recent received data by the I2C peripheral.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @retval The value of the received data.
  */
uint8_t I2C_ReceiveData(I2C_TypeDef * I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    /* Return the data in the IC_DATA_CMD register */
    return (uint8_t)(I2Cx->DATA_CMD & I2C_DATA_CMD_DAT0_7);
}

/**
  * @brief  Configures the FIFO reception threshold.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  I2C_RxFIFOThreshold: specifies the FIFO reception threshold.
  *          This parameter can be 1-16.
  * @retval None
  */
void I2C_RxFIFOThresholdConfig(I2C_TypeDef * I2Cx, uint32_t I2C_RxFIFOThreshold)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_RX_FIFO_THRESHOLD(I2C_RxFIFOThreshold));

	/* Set new RXFTL bit value */
	I2Cx->RX_TL = I2C_RxFIFOThreshold - 1;
}

/**
  * @brief  Configures the FIFO transmition threshold.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  I2C_TxFIFOThreshold: specifies the FIFO reception threshold.
  *          This parameter can be 0-15.
  * @retval None
  */
void I2C_TxFIFOThresholdConfig(I2C_TypeDef * I2Cx, uint32_t I2C_TxFIFOThreshold)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_TX_FIFO_THRESHOLD(I2C_TxFIFOThreshold));

	/* Set new TXFTL bit value */
	I2Cx->TX_TL = I2C_TxFIFOThreshold;
}

/**
  * @brief  Returns the number of valid data in the transmit FIFO memory.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @retval The number of valid data.
  */
uint32_t I2C_GetTransmissionFIFONum(I2C_TypeDef * I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

	/* Get the I2C Transmission FIFO level */
	return (uint32_t)(I2Cx->TXFLR & I2C_TXFLR_TXFLR0_3);
}

/**
  * @brief  Returns the number of valid data in the receive FIFO memory.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @retval The number of valid data.
  */
uint32_t I2C_GetReceptionFIFONum(I2C_TypeDef * I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

	/* Get the I2C reception FIFO level */
	return (uint32_t)(I2Cx->RXFLR & I2C_RXFLR_RXFLR0_3);
}

/**
  * @brief  Returns Speed mode.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @retval Speed mode.
  */
uint32_t I2C_GetSpeedMode(I2C_TypeDef * I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

	/* Get speed mode */
	return (uint32_t)(I2Cx->CON & I2C_CON_SPEED1_2);
}

/**
  * @brief  Send NACK or ACK.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  NewState: new state of the NACK command. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_NACKCmd(I2C_TypeDef * I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        I2Cx->SLV_DATA_NACK_ONLY = I2C_SLV_DATA_NACK_ONLY_NACK;
    }
    else
    {
        I2Cx->SLV_DATA_NACK_ONLY = 0;
    }
}

/**
  * @brief  ACK General Call.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  NewState: When set to ENABLE, I2C responds with a ACK when it receives a General Call.
  *                   When set to DISABLE, I2C does not generate General Call interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_ACKGenCallCmd(I2C_TypeDef * I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        I2Cx->ACK_GENERAL_CALL = I2C_ACK_GENERAL_CALL;
    }
    else
    {
        I2Cx->ACK_GENERAL_CALL = 0;
    }
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg I2C_IT_RX_UNDER
  *            @arg I2C_IT_RX_OVER
  *            @arg I2C_IT_RX_FULL
  *            @arg I2C_IT_TX_OVER
  *            @arg I2C_IT_TX_EMPTY
  *            @arg I2C_IT_RD_REQ
  *            @arg I2C_IT_TX_ABRT
  *            @arg I2C_IT_RX_DONE
  *            @arg I2C_IT_ACTIVITY
  *            @arg I2C_IT_STOP_DET
  *            @arg I2C_IT_START_DET
  *            @arg I2C_IT_GEN_CALL
  * @param  NewState: new state of the specified I2C interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(I2C_TypeDef * I2Cx, uint32_t I2C_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_I2C_IT(I2C_IT));

    if (NewState != DISABLE)
    {
        /* Enable the selected I2C interrupts */
        I2Cx->INTR_MASK |= I2C_IT;
    }
    else
    {
        /* Disable the selected I2C interrupts */
        I2Cx->INTR_MASK &= ~I2C_IT;
    }
}

/**
  * @brief  Get the I2C's Interrupt Status Register.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg I2C_IT_RX_UNDER
  *            @arg I2C_IT_RX_OVER
  *            @arg I2C_IT_RX_FULL
  *            @arg I2C_IT_TX_OVER
  *            @arg I2C_IT_TX_EMPTY
  *            @arg I2C_IT_RD_REQ
  *            @arg I2C_IT_TX_ABRT
  *            @arg I2C_IT_RX_DONE
  *            @arg I2C_IT_ACTIVITY
  *            @arg I2C_IT_STOP_DET
  *            @arg I2C_IT_START_DET
  *            @arg I2C_IT_GEN_CALL
  * @retval The new state of the I2C_IT(SET or RESET).
  */
ITStatus I2C_GetITFlag(I2C_TypeDef * I2Cx, uint32_t I2C_IT)
{
	ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_GET_IT(I2C_IT));
    
    if ((I2Cx->INTR_STAT & I2C_IT) != RESET)
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
  * @brief  Get the I2C's Raw Interrupt Status Register.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg I2C_IT_RX_UNDER
  *            @arg I2C_IT_RX_OVER
  *            @arg I2C_IT_RX_FULL
  *            @arg I2C_IT_TX_OVER
  *            @arg I2C_IT_TX_EMPTY
  *            @arg I2C_IT_RD_REQ
  *            @arg I2C_IT_TX_ABRT
  *            @arg I2C_IT_RX_DONE
  *            @arg I2C_IT_ACTIVITY
  *            @arg I2C_IT_STOP_DET
  *            @arg I2C_IT_START_DET
  *            @arg I2C_IT_GEN_CALL
  * @retval The new state of the I2C_IT(SET or RESET).
  */
ITStatus I2C_GetRawITFlag(I2C_TypeDef * I2Cx, uint32_t I2C_IT)
{
	ITStatus bitstatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_GET_IT(I2C_IT));

    if ((I2Cx->RAW_INTR_STAT & I2C_IT) != RESET)
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
  * @brief  Get the TX abort source.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @retval TX abort source.
  */
uint32_t I2C_GetTXAbortSource(I2C_TypeDef * I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    return (uint32_t)(I2Cx->TX_ABRT_SOURCE);
}

/**
  * @brief  Clears the I2C's interrupt pending bits.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  I2C_IT: specifies the I2C interrupt sources to be cleared.
  *          This parameter can be one of the following values:
  *            @arg I2C_CLEAR_ALL_INTR: Clear all interrupt flag.
  *            @arg I2C_CLEAR_RX_UNDER: Clear RX_UNDER interrupt flag.
  *            @arg I2C_CLEAR_RX_OVER: Clear RX_OVER interrupt flag.
  *            @arg I2C_CLEAR_TX_OVER: Clear TX_OVER interrupt flag.
  *            @arg I2C_CLEAR_RD_REQ: Clear RD_REQ interrupt flag.
  *            @arg I2C_CLEAR_TX_ABRT: Clear TX_ABRT interrupt flag.
  *            @arg I2C_CLEAR_RX_DONE: Clear RX_DONE interrupt flag.
  *            @arg I2C_CLEAR_ACTIVITY: Clear ACTIVITY interrupt flag.
  *            @arg I2C_CLEAR_STOP_DET: Clear STOP_DET interrupt flag.
  *            @arg I2C_CLEAR_START_DET: Clear START_DET interrupt flag.
  *            @arg I2C_CLEAR_GEN_CALL: Clear GEN_CALL interrupt flag.
  * @retval None
  */
void I2C_ClearITPendingBit(I2C_TypeDef * I2Cx, uint32_t I2C_CLEAR_IT)
{
    volatile uint32_t clearreg = 0;
    
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLEAR_IT(I2C_CLEAR_IT));
    
    if (I2Cx == I2C0)
    {
        /* Clear the selected I2C interrupt pending bits */
        clearreg = *(volatile uint32_t *)(I2C0_BASE + I2C_CLEAR_IT);
    }
    else
    {
        /* Clear the selected I2C interrupt pending bits */
        clearreg = *(volatile uint32_t *)(I2C1_BASE + I2C_CLEAR_IT);
    }
}

/**
  * @brief  Checks whether the specified I2C flag is set or not.
  * @param  I2Cx: where x can be 0 or 1 to select the i2c peripheral.
  * @param  I2C_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg I2C_FLAG_ACTIVITY: I2C activity status.
  *     @arg I2C_FLAG_TFNF:  Transmit FIFO Not Full.
  *     @arg I2C_FLAG_TFE:  Transmit FIFO Completely Empty.
  *     @arg I2C_FLAG_RFNE:  Receive FIFO Not Empty.
  *     @arg I2C_FLAG_RFF:  Receive FIFO Completely Full.
  *     @arg I2C_FLAG_MST_ACTIVITY:  Master Finite State Machine Activity Status.
  *     @arg I2C_FLAG_SLV_ACTIVITY:  Slave Finite State Machine Activity Status.
  *     @arg I2C_FLAG_IC_EN:  IC_EN Status.
  *     @arg I2C_FLAG_SLV_DISABLED_WHILE_BUSY:  Slave Disabled While Busy (Transmit, Receive).
  *     @arg I2C_FLAG_SLV_RX_DATA_LOST:  Slave Received Data Lost.
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef * I2Cx, uint32_t I2C_FLAG)
{
	FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_FLAG(I2C_FLAG));

    if ((I2C_FLAG == I2C_FLAG_IC_EN) | \
        (I2C_FLAG == I2C_FLAG_SLV_DISABLED_WHILE_BUSY) | \
        (I2C_FLAG == I2C_FLAG_SLV_RX_DATA_LOST))
    {
    	if ((I2Cx->ENABLE_STATUS & (I2C_FLAG & (~I2C_ENABLE_STATUS_FLAG))) != RESET)
    	{
    		bitstatus = SET;
    	}
        else
        {
    		bitstatus = RESET;
        }
    }
    else
    {
    	if ((I2Cx->STAT & I2C_FLAG) != RESET)
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
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT MIC *****END OF FILE****/
