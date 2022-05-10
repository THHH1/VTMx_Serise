/**
  ******************************************************************************
  * @file    VTM071x_flash.c
  * @author  MIC Software Team
  * @version V1.0.0
  * @date    03/01/2018
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the FLASH peripheral:
  *            - FLASH Interface configuration
  *            - FLASH Memory Programming
  *            - Option Bytes Programming
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
#include "VTM071x_flash.h"

/** @addtogroup VTM071x_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH 
  * @brief FLASH driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
 
/** @defgroup FLASH_Private_Functions
  * @{
  */ 

/** @defgroup FLASH_Group1 FLASH Interface configuration functions
  *  @brief   FLASH Interface configuration functions 
 *
@verbatim   
 ===============================================================================
               ##### FLASH Interface configuration functions #####
 ===============================================================================

    [..] FLASH_Interface configuration_Functions, includes the following functions:
       (+) void FLASH_SetLatency(uint32_t FLASH_Latency):
    [..] To correctly read data from Flash memory, the number of wait states (LATENCY) 
     must be correctly programmed according to the frequency of the CPU clock (HCLK) 
    [..]
        +--------------------------------------------- +
        |  Wait states  |   HCLK clock frequency (MHz) |
        |---------------|------------------------------|
        |0WS(1CPU cycle)|       0 < HCLK <= 40         |
        |---------------|------------------------------|
        |1WS(2CPU cycle)|       40 < HCLK <= 80        |
        |---------------|------------------------------|
        |2WS(2CPU cycle)|       80 < HCLK <= 84        |
        +----------------------------------------------+
    [..]
       (+) void FLASH_PrefetchBufferCmd(FunctionalState NewState);
    [..]
     All these functions don't need the unlock sequence.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the code latency value.
  * @param  FLASH_Latency: specifies the FLASH Latency value.
  *          This parameter can be one of the following values:
  *             @arg FLASH_Latency_0: FLASH Zero Latency cycle
  *             @arg FLASH_Latency_1: FLASH One Latency cycle
  *             @arg FLASH_Latency_2: FLASH Two Latency cycle
  * @retval None
  */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
	uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_FLASH_LATENCY(FLASH_Latency));

	/* Read the ACR register */
	tmpreg = FLASH->ACR;  

	/* Sets the Latency value */
	tmpreg &= (uint32_t) (~((uint32_t)FLASH_ACR_LATENCY));
	tmpreg |= FLASH_Latency;

	/* Write the ACR register */
	FLASH->ACR = tmpreg;
}

/**
  * @brief  Enables or disables Cache.
  * @param  NewState: new state of the FLASH prefetch buffer.
  *          This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */
void FLASH_CacheCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState != DISABLE)
	{
		FLASH->ACR |= FLASH_ACR_CACHENA;
	}
	else
	{
		FLASH->ACR &= (uint32_t)(~((uint32_t)FLASH_ACR_CACHENA));
	}
}

/**
  * @brief  Flush Cache.
  * @param  NewState: new state of the FLASH prefetch buffer.
  *          This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */
void FLASH_FlushCacheCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState != DISABLE)
	{
		FLASH->ACR |= FLASH_ACR_FLUSH;
	}
	else
	{
		FLASH->ACR &= (uint32_t)(~((uint32_t)FLASH_ACR_FLUSH));
	}
}
/**
  * @}
  */

/** @defgroup FLASH_Group2 FLASH Memory Programming functions
 *  @brief   FLASH Memory Programming functions
 *
@verbatim   
 ===============================================================================
                ##### FLASH Memory Programming functions #####
 ===============================================================================

    [..] The FLASH Memory Programming functions, includes the following functions:
       (+) void FLASH_Unlock(void);
       (+) void FLASH_Lock(void);
       (+) void FLASH_EraseSector(uint32_t Page_Address);
       (+) void FLASH_EraseAllSectors(void);
       (+) void FLASH_ProgramAPROM(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize);
       (+) void FLASH_ProgramLDROM(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize);

    [..] Any operation of erase or program should follow these steps:
       
       (#) Call the FLASH_Unlock() function to enable the flash control register and 
           program memory access
       (#) Call the desired function to erase page or program data
       (#) Call the FLASH_Lock() to disable the flash program memory access 
      (recommended to protect the FLASH memory against possible unwanted operation)

@endverbatim
  * @{
  */

/**
  * @brief  Unlocks the FLASH control register and program memory access.
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
	if((FLASH->CR & FLASH_CR_LOCK) != RESET)
	{
		/* Unlocking the program memory access */
		FLASH->KEYR = FLASH_FKEY1;
		FLASH->KEYR = FLASH_FKEY2;
	}
}

/**
  * @brief  Locks the Program memory access.
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
	/* Set the LOCK Bit to lock the FLASH control register and program memory access */
	FLASH->CR |= FLASH_CR_LOCK;
}

/**
  * @brief  Erases a specified sector in program memory.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Flash: Flash mode, it can be: FLASH_APROM or FLASH_LDROM.
  * @param  Sector: The sector number in program memory to be erased.
  * @retval None
  */
void FLASH_EraseAPROM(uint32_t FlashAddr)
{
	uint32_t tmpreg = 0, sector = 0, boot;
    
    tmpreg = RCC_BOOTREMAP_BOOT_IO | RCC_BOOTREMAP_BOOT_FLASH | RCC_BOOTREMAP_BOOT_REG;
    boot = RCC->BOOTREMAP & tmpreg;
    
	/* Check the parameters */
    if (boot)
    {
        assert_param(FlashAddr >= FLASH_BASE2);
        assert_param(FlashAddr < (FLASH_BASE2 + APROM_SIZE));
    }
    else
    {
        assert_param((FlashAddr) < (FLASH_BASE1 + APROM_SIZE));
    }

	/* Clear FLASH End of erasing flag*/
	FLASH_ClearFlag(FLASH_FLAG_EOE);

	/* Wait for last operation to be completed */
	while(FLASH->SR & FLASH_SR_BUSY){}
	
	/* Erase the sector */
    sector = (FlashAddr & 0x1FFFFUL) >> 9;
    tmpreg = (FlashAddr & (~(0x1FFFFUL))) | sector;
	FLASH->ERASE = tmpreg;

	tmpreg = FLASH_CR_SER | FLASH_CR_START;
	FLASH->CR = tmpreg;
    
	/* Wait for FLASH End of erasing */
	while(!FLASH_GetFlagStatus(FLASH_FLAG_EOE));
	FLASH_ClearFlag(FLASH_FLAG_EOE);

	/* Wait for erase to be completed */
	while(FLASH->SR & FLASH_SR_BUSY);

	/* Disable the SER Bit */
	FLASH->CR &= ~FLASH_CR_SER;
}

void FLASH_EraseLDROM(uint32_t FlashAddr)
{
	uint32_t tmpreg = 0, sector = 0, boot;
    
    tmpreg = RCC_BOOTREMAP_BOOT_IO | RCC_BOOTREMAP_BOOT_FLASH | RCC_BOOTREMAP_BOOT_REG;
    boot = RCC->BOOTREMAP & tmpreg;

	/* Check the parameters */
    if (boot)
    {
        assert_param(FlashAddr < (FLASH_BASE1 + LDROM_SIZE));
    }
    else
    {
        assert_param(FlashAddr >= FLASH_BASE2);
        assert_param(FlashAddr < (FLASH_BASE2 + LDROM_SIZE));
    }

	/* Clear FLASH End of erasing flag*/
	FLASH_ClearFlag(FLASH_FLAG_EOE);

	/* Wait for last operation to be completed */
	while(FLASH->SR & FLASH_SR_BUSY){}
	
	/* Erase the sector */
    sector = (FlashAddr & 0x1FFFUL) >> 9;
    tmpreg = (FlashAddr & (~(0x1FFFUL))) | sector;
	FLASH->ERASE = tmpreg;

    tmpreg = FLASH_CR_LDROMEN;
	tmpreg |= FLASH_CR_SER | FLASH_CR_START;
	FLASH->CR = tmpreg;
    
	/* Wait for FLASH End of erasing */
	while(!FLASH_GetFlagStatus(FLASH_FLAG_EOE));
	FLASH_ClearFlag(FLASH_FLAG_EOE);

	/* Wait for erase to be completed */
	while(FLASH->SR & FLASH_SR_BUSY);

	/* Disable the SER Bit */
	FLASH->CR &= ~FLASH_CR_SER;
}

/**
  * @brief  Programs APROM at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  FlashAddr: specifies the address to be programmed(multiple of 4 bytes).
  * @param  SramBuf: specifies the sram data which whill be programmed to flash(multiple of 4 bytes).
  * @param  ProgramSize: specifies programming size(multiple of 4 bytes).
  * @note   The three params must be multiple of 4 bytes.
  * @retval None
  */
void FLASH_ProgramAPROM(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize)
{
	uint32_t tmpreg = 0, i, boot;

    tmpreg = RCC_BOOTREMAP_BOOT_IO | RCC_BOOTREMAP_BOOT_FLASH | RCC_BOOTREMAP_BOOT_REG;
    boot = RCC->BOOTREMAP & tmpreg;

	/* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_SRAM_ADDR((uint32_t)SramBuf));
    
    if (boot)
    {
        assert_param(FlashAddr >= FLASH_BASE2);
        assert_param((FlashAddr + ProgramSize) <= (FLASH_BASE2 + APROM_SIZE));
    }
    else
    {
        assert_param((FlashAddr + ProgramSize) <= (FLASH_BASE1 + APROM_SIZE));
    }

	/* Clear FLASH End of Programming flag */
	FLASH_ClearFlag(FLASH_FLAG_EOP);

	/* Configure CR register */
	tmpreg = FLASH_CR_PG;
	FLASH->CR = tmpreg;

	/* Programming */
	for (i=0; i<(ProgramSize>>2); i++)
	{
		/* Wait for last operation to be completed */
		while(FLASH->SR & FLASH_SR_BUSY);

		*(__IO uint32_t*)(FlashAddr + i * 4) = *(SramBuf + i);
	}

	/* Wait for FLASH End of Programming */
	while(!FLASH_GetFlagStatus(FLASH_FLAG_EOP));
	FLASH_ClearFlag(FLASH_FLAG_EOP);

	/* Wait for last operation to be completed */
	while(FLASH->SR & FLASH_SR_BUSY);

	FLASH->CR &= ~FLASH_CR_PG;
}

/**
  * @brief  Programs LDROM at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  FlashAddr: specifies the address to be programmed(multiple of 4 bytes).
  * @param  SramBuf: specifies the sram data which whill be programmed to flash(multiple of 4 bytes).
  * @param  ProgramSize: specifies programming size(multiple of 4 bytes).
  * @note   The three params must be multiple of 4 bytes.
  * @retval None
  */
void FLASH_ProgramLDROM(uint32_t *SramBuf, uint32_t FlashAddr, uint32_t ProgramSize)
{
	uint32_t tmpreg = 0, i, boot;

    tmpreg = RCC_BOOTREMAP_BOOT_IO | RCC_BOOTREMAP_BOOT_FLASH | RCC_BOOTREMAP_BOOT_REG;
    boot = RCC->BOOTREMAP & tmpreg;

	/* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_SRAM_ADDR((uint32_t)SramBuf));
    
    if (boot)
    {
        assert_param((FlashAddr + ProgramSize) <= (FLASH_BASE1 + LDROM_SIZE));
    }
    else
    {
        assert_param(FlashAddr >= FLASH_BASE2);
        assert_param((FlashAddr + ProgramSize) <= (FLASH_BASE2 + LDROM_SIZE));
    }

	/* Clear FLASH End of Programming flag */
	FLASH_ClearFlag(FLASH_FLAG_EOP);

	/* Configure CR register */
	tmpreg = FLASH_CR_PG | FLASH_CR_LDROMEN;
	FLASH->CR = tmpreg;

	/* Programming */
	for (i=0; i<(ProgramSize>>2); i++)
	{
		/* Wait for last operation to be completed */
		while(FLASH->SR & FLASH_SR_BUSY);

		*(__IO uint32_t*)(FlashAddr + i * 4) = *(SramBuf + i);
	}

	/* Wait for FLASH End of Programming */
	while(!FLASH_GetFlagStatus(FLASH_FLAG_EOP));
	FLASH_ClearFlag(FLASH_FLAG_EOP);

	/* Wait for last operation to be completed */
	while(FLASH->SR & FLASH_SR_BUSY);

	FLASH->CR &= ~(FLASH_CR_PG | FLASH_CR_LDROMEN);
}

/**
  * @}
  */

/** @defgroup FLASH_Group4 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim   
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or 
  *         disabled.
  *          This parameter can be any combination of the following values:
  *             @arg FLASH_IT_EOP: FLASH end of programming Interrupt
  *             @arg FLASH_IT_ERR: FLASH Error Interrupt
  * @retval None 
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FLASH_IT(FLASH_IT)); 
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState != DISABLE)
	{
		/* Enable the interrupt sources */
		FLASH->CR |= FLASH_IT;
	}
	else
	{
		/* Disable the interrupt sources */
		FLASH->CR &= ~(uint32_t)FLASH_IT;
	}
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *          This parameter can be one of the following values:
  *             @arg FLASH_FLAG_BUSY: FLASH write/erase operations in progress flag 
  *             @arg FLASH_FLAG_EOE: FLASH End of Erase flag
  *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));

	if((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
	{
		bitstatus = SET;
	}
	else
	{
		bitstatus = RESET;
	}
	/* Return the new state of FLASH_FLAG (SET or RESET) */
	return bitstatus; 
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *          This parameter can be any combination of the following values:
  *             @arg FLASH_FLAG_EOE: FLASH End of Erase flag
  *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
	/* Check the parameters */
	assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

	/* Clear the flags */
	FLASH->SR |= FLASH_FLAG;
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

/************************ (C) COPYRIGHT MIC *****END OF FILE****/

