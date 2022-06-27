/**
  ******************************************************************************
  * @file    VTM071x_eval_i2c_ee.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides a set of functions needed to manage the I2C AT24CXX 
  *          EEPROM memory mounted on VTM071x_EVAL evaluation board.
  *         
  *              
  *          It implements a high level communication layer for read and write 
  *          from/to this memory. The needed MIC hardware resources (I2C and 
  *          GPIO) are defined in VTM071x_eval.h file, and the initialization is 
  *          performed in sEE_LowLevel_Init() function declared in VTM071x_eval.c 
  *          file.
  *          You can easily tailor this driver to any other development board, 
  *          by just adapting the defines for hardware resources and 
  *          sEE_LowLevel_Init() function. 
  *               
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
#include "VTM071x_eval_i2c_ee.h"
#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup VTM071x_EVAL
  * @{
  */

/** @addtogroup VTM071x_EVAL_I2C_EE
  * @brief      This file includes the I2C EEPROM driver of VTM071x_EVAL boards.
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define I2C_RXFIFOTH                6           //接收FIFO阈值
#define I2C_EEPROM_CHIP_INDEX       0           //选择I2C EEPROM型号 Chip_List
#define I2C_EEPROM_RETRY_TIMES      20          //读写重试次数

//#define DEBUG
#ifdef DEBUG
#define dbgprint(...) printf(__VA_ARGS__)
#else
#define dbgprint(...)
#endif 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* 型号列表，由I2C_EEPROM_CHIP_INDEX选择 */
struct EEPROM_Info Chip_List[] = {
    {"AT24C08", 0xA0, I2C_XBIT_ADDRESS_7BIT, 1024, 16, 1, I2C_CLOCK_STANDARD_MODE, 126, 331, 389},
    {"AT24C256", 0xA0, I2C_XBIT_ADDRESS_7BIT, 32768, 64, 2, I2C_CLOCK_STANDARD_MODE, 126, 331, 389},
};

struct EEPROM_Info *EEPROM = &Chip_List[I2C_EEPROM_CHIP_INDEX];
uint8_t *RecBuf = 0;
volatile int RecIndex=0, RecTrigger=0;
uint32_t RecSize=0;
volatile uint32_t I2C_MasterStatus = I2C_MS_Deinit;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup VTM071x_EVAL_I2C_EE_Private_Functions
  * @{
  */ 

/* 延时10个I2C Clock */
static void I2C_Delay(void)
{
    int i=0, limit=0;
    uint32_t Freq = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK);

    if (EEPROM->Speed == I2C_CON_STANDARD_MODE)
        limit = 20 * Freq / 1000000;    //delay 100us
    else if (EEPROM->Speed == I2C_CON_FAST_MODE)
        limit = 5 * Freq / 1000000;     //delay 25us
    else
        limit = 5 * Freq / 8000000;     //delay 3us

    for (i=0; i<limit; i++);

    //while((i++) != limit);
}

/**
  * @brief  DeInitializes peripherals used by the I2C EEPROM driver.
  * @param  None
  * @retval None
  */
void sEE_DeInit(void)
{
    sEE_LowLevel_DeInit(I2C_X);
    
    I2C_MasterStatus = I2C_MS_Deinit;
}

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * @param  addresscycle:internal addressing cycles.
  * @param  speedmode:0 is standard while 1 is fast.
  * @retval 0: okay; else: fail.
  */
int sEE_Init(void)
{
    I2C_InitTypeDef I2C_InitStructure;

    if (I2C_MasterStatus == I2C_MS_Deinit)
    {
        sEE_LowLevel_Init(I2C_X);

        /* I2C Mode, 7bit or 10bit device address, Speed Mode, Reset Mode */
        I2C_InitStructure.I2C_Mode = I2C_MODE_MASTER;
        I2C_InitStructure.I2C_XbitAddress = EEPROM->XbitAddress;
        I2C_InitStructure.I2C_ClockSpeed = EEPROM->Speed;
        I2C_InitStructure.I2C_RestartMode = I2C_RESTART_ENABLE;
        I2C_Init(I2C_X, &I2C_InitStructure);

        /* Clock pulse width high, Clock pulse width low */
        I2C_SCLKCountConfig(I2C_X, EEPROM->CLKPulseWidthHigh, EEPROM->CLKPulseWidthLow, EEPROM->Speed);

        /* SDA setup time */
        I2C_SDASetupConfig(I2C_X, EEPROM->SDASetupTime);

        /* Mask all interrupt source */
        I2C_ITConfig(I2C_X, I2C_IT_ALL, DISABLE);
        I2C_ClearITPendingBit(I2C_X, I2C_CLEAR_ALL_INTR);

        /* Init */
        I2C_MasterStatus = I2C_MS_Idle;

        return 0;
    }
    else
    {
        return I2C_INIT_FAILED;
    }
}

static int sEE_Cmd(FunctionalState NewState)
{
    int retry = 5;

    if (NewState != DISABLE)
    {
        I2C_MasterStatus = I2C_MS_Standby;
        I2C_Cmd(I2C_X, ENABLE);
        return 0;
    }
    else
    {
        /* Necessary steps */
        while(retry--)
        {
            I2C_ClearITPendingBit(I2C_X, I2C_CLEAR_ALL_INTR);
            I2C_Cmd(I2C_X, DISABLE);
            if (I2C_GetFlagStatus(I2C_X, I2C_FLAG_IC_EN) == SET)
            {
                I2C_Delay();
                continue;
            }
            else
            {
                I2C_MasterStatus = I2C_MS_Idle;
                return 0;
            }
        }

        return I2C_DISABLE_TIMEOUT;
    }
}

int sEE_WritePage(uint8_t *WriteBuf, uint32_t EEPROMAddress, uint32_t Size)
{
    uint32_t AddressCycle;
    uint8_t AddrBuf[4];
    int i, ret, timeout = 100000, retry = I2C_EEPROM_RETRY_TIMES;

    if (EEPROM->AddressBytes == 2)
    {
        AddressCycle = 2;
        AddrBuf[0] = (uint8_t)(EEPROMAddress >> 8);
        AddrBuf[1] = (uint8_t)EEPROMAddress;
    }
    else if (EEPROM->AddressBytes == 1)
    {
        AddressCycle = 1;
        AddrBuf[0] = (uint8_t)EEPROMAddress;
    }
    else
        return I2C_WRONG_ADDRESSBYTES;

    while((retry) && ((I2C_MasterStatus == I2C_MS_AbortOops) || (I2C_MasterStatus == I2C_MS_Idle)))
    {
        retry--;
        ret = 0;

        if (sEE_Cmd(DISABLE) != 0)
            return I2C_TRANSMIT_FATAL;
        I2C_ClearITPendingBit(I2C_X, I2C_CLEAR_ALL_INTR);

        if (retry != (I2C_EEPROM_RETRY_TIMES-1))
            I2C_Delay();
        
        I2C_TARConfig(I2C_X, (EEPROM->SlaveAddress >> 1) | (EEPROMAddress >> (AddressCycle * 8)));
        I2C_ITConfig(I2C_X, I2C_IT_TX_ABRT, ENABLE);
        I2C0->INTR_MASK = 0;
        sEE_Cmd(ENABLE);

        I2C_MasterStatus = I2C_MS_WriteProcess;
        
        for (i=0; i<AddressCycle; i++)
        {
            I2C_SendData(I2C_X, AddrBuf[i]);
        }
        while((I2C_GetFlagStatus(I2C_X, I2C_FLAG_TFE) == RESET));

        for (i=0; i<Size; i++)
        {
            while (I2C_GetFlagStatus(I2C_X, I2C_FLAG_TFNF) == RESET);
            I2C_SendData(I2C_X, WriteBuf[i]);
            if (I2C_MasterStatus == I2C_MS_AbortOops)
            {
                ret = I2C_TRANSMIT_OOPS;
                break;
            }
        }

        if (I2C_MasterStatus != I2C_MS_AbortOops)
        {
            while((I2C_GetFlagStatus(I2C_X, I2C_FLAG_TFE) == RESET) || (I2C_GetFlagStatus(I2C_X, I2C_FLAG_ACTIVITY) == SET))
            {
                timeout--;
                if (timeout == 0)
                {
                    I2C_MasterStatus = I2C_MS_AbortOops;
                }
            }
        }
        
        if (I2C_MasterStatus == I2C_MS_WriteProcess)
        {
            ret = 0;
            I2C_MasterStatus = I2C_MS_WriteSucceed;
        }
        else if (I2C_MasterStatus == I2C_MS_AbortOops)
        {
            ret = I2C_TRANSMIT_OOPS;
        }
        else
        {
            ret = I2C_TRANSMIT_FATAL;
        }
    }

    I2C_ITConfig(I2C_X, I2C_IT_TX_ABRT, DISABLE);

    if (retry == 0)
        ret = I2C_TRANSMIT_FATAL;

    if (sEE_Cmd(DISABLE) != 0)
        ret = I2C_TRANSMIT_FATAL;

    return ret;
}

int sEE_WriteBuffer(uint8_t *WriteBuf, uint32_t EEPROMAddress, uint32_t Size)
{
    uint32_t PageNum;
    uint32_t SingleHead, SingleTail;
    uint32_t ret = 0;
    int i=0;
    uint8_t *Buf = WriteBuf;
    uint32_t sEEAddr = EEPROMAddress;

    SingleHead = EEPROM->PageSize - (sEEAddr & (EEPROM->PageSize - 1));
    if (SingleHead > Size)
        SingleHead = Size;
    SingleTail = (Size - SingleHead) % EEPROM->PageSize;
    PageNum = (Size - SingleHead - SingleTail) / EEPROM->PageSize;

    /* Write SingleHead */
    if (SingleHead != 0)
    {
        ret = sEE_WritePage(Buf, sEEAddr, SingleHead);
        if (ret & I2C_ERROR_FLAG)
            return ret;
        if (ret == 0)
        {
            Buf += SingleHead;
            sEEAddr += SingleHead;
        }
    }

    /* Write integrated pages */
    for (i=0; i<PageNum; i++)
    {
        ret = sEE_WritePage(Buf, sEEAddr, EEPROM->PageSize);
        if (ret & I2C_ERROR_FLAG)
            return ret;
        if (ret == 0)
        {
            Buf += EEPROM->PageSize;
            sEEAddr += EEPROM->PageSize;
        }
    }

    /* Write SingleTail */
    if (SingleTail != 0)
    {
        ret = sEE_WritePage(Buf, sEEAddr, SingleTail);
        if (ret & I2C_ERROR_FLAG)
            return ret;
    }

    return ret;
}

int sEE_ReadBuffer(uint8_t *ReadBuf, uint32_t EEPROMAddress, uint32_t Size)
{
    uint32_t AddressCycle;
    uint8_t AddrBuf[4];
    int i, ret=0, retry = I2C_EEPROM_RETRY_TIMES;

    if (Size == 0)
        return 0;
        
    if (EEPROM->AddressBytes == 2)
    {
        AddressCycle = 2;
        AddrBuf[0] = (uint8_t)(EEPROMAddress >> 8);
        AddrBuf[1] = (uint8_t)EEPROMAddress;
    }
    else if (EEPROM->AddressBytes == 1)
    {
        AddressCycle = 1;
        AddrBuf[0] = (uint8_t)EEPROMAddress;
    }
    else
        return I2C_WRONG_ADDRESSBYTES;

    I2C_RxFIFOThresholdConfig(I2C_X, I2C_RXFIFOTH);

    while(retry)
    {
        retry--;
        ret = 0;
        RecBuf = ReadBuf;
        RecSize = Size;
        RecIndex = 0;
        RecTrigger = 0;

        if (sEE_Cmd(DISABLE) != 0)
            return I2C_TRANSMIT_FATAL;
        I2C_ClearITPendingBit(I2C_X, I2C_CLEAR_ALL_INTR);
        
        if (retry != (I2C_EEPROM_RETRY_TIMES-1))
            I2C_Delay();

        I2C_TARConfig(I2C_X, (EEPROM->SlaveAddress >> 1) | (EEPROMAddress >> (AddressCycle * 8)));
        I2C_ITConfig(I2C_X, I2C_IT_TX_ABRT | I2C_IT_RX_FULL, ENABLE);
        sEE_Cmd(ENABLE);

        /* Read Process */
        I2C_MasterStatus = I2C_MS_ReadProcess;

        /* Send EEPROM internal Address */
        for (i=0; i<AddressCycle; i++)
        {
            I2C_SendData(I2C_X, AddrBuf[i]);
        }

        while(I2C_GetFlagStatus(I2C_X, I2C_FLAG_TFE) == RESET)
        {
            if (I2C_MasterStatus == I2C_MS_AbortOops)
            {
                ret = I2C_RECEIVE_FAILED;
                break;
            }
        }

        if (I2C_MasterStatus == I2C_MS_AbortOops)
        {
            ret = I2C_RECEIVE_FAILED;
            continue;
        }

        if ((RecSize - 1) < I2C_RXFIFOTH)
        {
            for (i=0; i<RecSize; i++)
            {
                RecTrigger++;
                I2C_TriggerRecData(I2C_X);
            }

            for (RecIndex=0; RecIndex<RecSize; RecIndex++)
            {
                while(I2C_GetFlagStatus(I2C_X, I2C_FLAG_RFNE) == RESET)
                {
                    if (I2C_MasterStatus == I2C_MS_AbortOops)
                    {
                        ret = I2C_RECEIVE_FAILED;
                        break;
                    }
                }

                if (I2C_MasterStatus == I2C_MS_AbortOops)
                {
                    ret = I2C_RECEIVE_FAILED;
                    break;
                }

                RecBuf[RecIndex] = I2C_ReceiveData(I2C_X);
            }

            if (I2C_MasterStatus == I2C_MS_AbortOops)
            {
                ret = I2C_RECEIVE_FAILED;
                continue;
            }

            I2C_MasterStatus = I2C_MS_ReadSucceed;
        }
        else
        {
            for (i=0; i<RecSize; i++)
            {
                while (I2C_GetFlagStatus(I2C_X, I2C_FLAG_TFNF) == RESET);

                if (I2C_MasterStatus == I2C_MS_AbortOops)
                {
                    ret = I2C_RECEIVE_FAILED;
                    break;
                }

                RecTrigger++;
                I2C_TriggerRecData(I2C_X);
            }
            if (I2C_MasterStatus == I2C_MS_AbortOops)
            {
                ret = I2C_RECEIVE_FAILED;
                continue;
            }
        }

        while(I2C_MasterStatus == I2C_MS_ReadProcess);

        if (I2C_MasterStatus == I2C_MS_ReadSucceed)
            break;
    }

    I2C_ClearITPendingBit(I2C_X, I2C_CLEAR_ALL_INTR);
    I2C_ITConfig(I2C_X, I2C_IT_ALL, DISABLE);

    if (sEE_Cmd(DISABLE) != 0)
        ret = I2C_DISABLE_TIMEOUT;
    
    if (retry == 0)
        ret = I2C_RECEIVE_FAILED;
    
    return ret;
}

void I2C1_IRQHandler(void)
{
    uint32_t TxAbortSource = 0;
    int i;

    if (I2C_GetITFlag(I2C_X, I2C_IT_TX_ABRT) == SET)
    {
        TxAbortSource = I2C_GetTXAbortSource(I2C_X);
        I2C_ClearITPendingBit(I2C_X, I2C_CLEAR_TX_ABRT);

        if (TxAbortSource & I2C_TAS_MASTER_DIS)
        {
            I2C_MasterStatus = I2C_MS_AbortFatal;
            dbgprint("Fatal error(software): Tries to initiate a Master operation with the Master mode disabled.\r\n");
            
            goto Fatal;
        }

        if (TxAbortSource & I2C_TAS_10B_RD_NORSTRT)
        {
            I2C_MasterStatus = I2C_MS_AbortFatal;
            dbgprint("Fatal error(software): The restart is disabled and the master sends a read command in 10-bit addressing mode.\r\n");
            
            goto Fatal;
        }
        
        if (TxAbortSource & I2C_TAS_SBYTE_NORSTRT)
        {
            I2C_MasterStatus = I2C_MS_AbortFatal;
            dbgprint("Fatal error(software): restart must be enabled(IC_CON[5]=1), " \
                    "the SPECIAL bit must be cleared (IC_TAR[11]), " \
                    "or the GC_OR_START bit must be cleared.\r\n");
            
            goto Fatal;
        }

        if (TxAbortSource & I2C_TAS_HS_NORSTRT)
        {
            I2C_MasterStatus = I2C_MS_AbortFatal;
            dbgprint("Fatal error(software): The restart is disabled((IC_CON[5]) = 0)" \
                    "and the user is trying to use the master to transfer data in High Speed mode.\r\n");
            
            goto Fatal;
        }

        if (TxAbortSource & I2C_TAS_SBYTE_ACKDET)
        {
            I2C_MasterStatus = I2C_MS_AbortFatal;
            dbgprint("Fatal error(hardware): Master has sent a START Byte and the START Byte was acknowledged.\r\n");
            
            goto Fatal;
        }

        if (TxAbortSource & I2C_TAS_HS_ACKDET)
        {
            I2C_MasterStatus = I2C_MS_AbortFatal;
            dbgprint("Fatal error(hardware): Master is in High Speed mode and the High Speed Master code was acknowledged.\r\n");
            
            goto Fatal;
        }

        if (TxAbortSource & I2C_TAS_GCALL_READ)
        {
            I2C_MasterStatus = I2C_MS_AbortFatal;
            dbgprint("Fatal error(software): I2C in master mode sent a General Call " \
                    "but the user programmed the byte following the General Call " \
                    "to be a read from the bus.\r\n");
            
            goto Fatal;
        }

        if (TxAbortSource & I2C_TAS_GCALL_NOACK)
        {
            I2C_MasterStatus = I2C_MS_AbortOops;
            dbgprint("Oops: I2C in master mode sent a " \
                    "General Call and no slave on the bus " \
                    "acknowledged the General Call.\r\n");
            
            goto Oops;
        }

        if (TxAbortSource & I2C_TAS_TXDATA_NOACK)
        {
            I2C_MasterStatus = I2C_MS_AbortOops;
            dbgprint("Oops: Master has received an acknowledgement for the " \
                    "address, but when it sent data byte(s) following the address, " \
                    "it did not receive an acknowledge from the remote slave(s).\r\n");
            
            goto Oops;
        }

        if (TxAbortSource & I2C_TAS_10ADDR1_NOACK)
        {
            I2C_MasterStatus = I2C_MS_AbortOops;
            dbgprint("Oops: Master is in 10-bit address mode and the " \
                    "first 10-bit address byte was not acknowledged by any slave.\r\n");
            
            goto Oops;
        }

        if (TxAbortSource & I2C_TAS_10ADDR2_NOACK)
        {
            I2C_MasterStatus = I2C_MS_AbortOops;
            dbgprint("Oops: Master is in 10-bit address mode and the " \
                    "second 10-bit address byte was not acknowledged by any slave.\r\n");
            
            goto Oops;
        }

        if (TxAbortSource & I2C_TAS_10ADDR2_NOACK)
        {
            I2C_MasterStatus = I2C_MS_AbortOops;
            dbgprint("Oops: Master is in 10-bit address mode and the " \
                    "second 10-bit address byte was not acknowledged by any slave.\r\n");
            
            goto Oops;
        }

        if (TxAbortSource & I2C_TAS_7B_ADDR_NOACK)
        {
            I2C_MasterStatus = I2C_MS_AbortOops;
            dbgprint("Oops: Master is in 7-bit addressing mode and the address " \
                    "sent was not acknowledged by any slave.\r\n");
            
            goto Oops;
        }

    }

    if (I2C_GetITFlag(I2C_X, I2C_IT_RX_FULL) == SET)
    {
//        I2C_ClearITPendingBit(I2C_X, I2C_CLEAR_TX_ABRT);
        
        if (I2C_MasterStatus == I2C_MS_ReadProcess)
        {
            if ((RecSize - RecIndex) > I2C_RXFIFOTH)
            {
                RecBuf[RecIndex++] = I2C_ReceiveData(I2C_X);
            }
            else
            {
                for (i=0; i<I2C_RXFIFOTH; i++)
                    RecBuf[RecIndex++] = I2C_ReceiveData(I2C_X);
            }

            if (RecIndex == RecSize)
            {
                if (RecTrigger == RecSize)
                    I2C_MasterStatus = I2C_MS_ReadSucceed;
                else
                    I2C_MasterStatus = I2C_MS_ReadFailed;
            }
        }
    }

    return;
    
Oops:
    return;

Fatal:
    /* Fatal error, reset I2C */
    I2C_DeInit(I2C_X);
    return;
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

/**
  * @}
  */  

/******************* (C) COPYRIGHT MIC *****END OF FILE****/
