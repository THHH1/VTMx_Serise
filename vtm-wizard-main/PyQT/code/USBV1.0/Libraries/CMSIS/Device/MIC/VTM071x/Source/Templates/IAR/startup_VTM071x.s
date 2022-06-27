;/**************************************************************************//**
; * @file     startup_VTM071x.s
; * @brief    CMSIS Core Device Startup File for
; *           VTM071x
; * @version  V1.0.0
; * @date     12/06/2018
; *
; * @note
; *
;******************************************************************************
;  @attention
; 
;  THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
;  WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
;  TIME. AS A RESULT, XXXXXXXX SHALL NOT BE HELD LIABLE FOR ANY
;  DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
;  FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
;  CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;
;  <h2><center>&copy; COPYRIGHT 2015 XXXXXXXX</center></h2>
;******************************************************************************


;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                  ; Reset Handler

        DCD     NMI_Handler                    ; NMI Handler
        DCD     HardFault_Handler              ; Hard Fault Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
__vector_table_0x1c
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SVC_Handler                    ; SVCall Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     PendSV_Handler                 ; PendSV Handler
        DCD     SysTick_Handler                ; SysTick Handler

        ; External Interrupts
        DCD       0                            ; 0  -- Reserved
        DCD       0                            ; 1  -- Reserved
        DCD       0                            ; 2  -- Reserved
        DCD       0                            ; 3  -- Reserved
        DCD       0                            ; 4  -- Reserved
        DCD       RTC_IRQHandler               ; 5  -- RTC Handler
        DCD       USB_IRQHandler               ; 6  -- USB Handler
        DCD       USB_DMA_IRQHandler           ; 7  -- USB DMA Handler
        DCD       FLASH_IRQHandler             ; 8  -- FLASH Handler
        DCD       USART0_IRQHandler            ; 9  -- USART0 Handler
        DCD       USART1_IRQHandler            ; 10 -- USART1 Handler 
        DCD       I2C0_IRQHandler              ; 11 -- I2C0 Handler
        DCD       0                            ; 12 -- Reserved
        DCD       SPI0_IRQHandler              ; 13 -- SPI0 Handler
        DCD       TIMER0_IRQHandler            ; 14 -- TIMER0 Handler
        DCD       TIMER1_IRQHandler            ; 15 -- TIMER1 Handler
        DCD       MCPWM_IRQHandler             ; 16 -- MCPWM Handler
        DCD       DMA_IRQHandler               ; 17 -- DMA Handler
        DCD       GPIO0_TO_GPIO3_IRQHandler    ; 18 -- GPIO0-GPIO3 Handler
        DCD       ADC_IRQHandler               ; 19 -- ADC Handler
        DCD       ACMP_IRQHandler              ; 20 -- ACMP Handler
        DCD       BOD_IRQHandler               ; 21 -- BOD Handler
        DCD       BOR_IRQHandler               ; 22 -- BOR Handler
        DCD       GPIO4_TO_GPIO6_IRQHandler    ; 23 -- GPIO4-GPIO7 Handler
        DCD       DAC_IRQHandler               ; 24 -- DAC Handler
        DCD       I2C1_IRQHandler              ; 25 -- I2C1 Handler
        DCD       TSC_IRQHandler               ; 26 -- TSC Handler
        DCD       SPI1_IRQHandler              ; 27 -- SPI1 Handler
        DCD       0                            ; 28 -- Reserved
        DCD       TIMER2_IRQHandler            ; 29 -- TIMER2 Handler
        DCD       TIMER3_IRQHandler            ; 30 -- TIMER3 Handler
        DCD       CORDIC_IRQHandler            ; 31 -- CORDIC Handler

__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK USB_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_IRQHandler
        B USB_IRQHandler

        PUBWEAK USB_DMA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_DMA_IRQHandler
        B USB_DMA_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK USART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART0_IRQHandler
        B USART0_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK I2C0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_IRQHandler
        B I2C0_IRQHandler

        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
        B SPI0_IRQHandler

        PUBWEAK TIMER0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_IRQHandler
        B TIMER0_IRQHandler

        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler

        PUBWEAK MCPWM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MCPWM_IRQHandler
        B MCPWM_IRQHandler

        PUBWEAK DMA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_IRQHandler
        B DMA_IRQHandler

        PUBWEAK GPIO0_TO_GPIO3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIO0_TO_GPIO3_IRQHandler
        B GPIO0_TO_GPIO3_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler

        PUBWEAK ACMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ACMP_IRQHandler
        B ACMP_IRQHandler

        PUBWEAK BOD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
BOD_IRQHandler
        B BOD_IRQHandler

        PUBWEAK BOR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
BOR_IRQHandler
        B BOR_IRQHandler

        PUBWEAK GPIO4_TO_GPIO6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIO4_TO_GPIO6_IRQHandler
        B GPIO4_TO_GPIO6_IRQHandler

        PUBWEAK DAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DAC_IRQHandler
        B DAC_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK TSC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TSC_IRQHandler
        B TSC_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

		PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_IRQHandler
        B TIMER2_IRQHandler

		PUBWEAK TIMER3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER3_IRQHandler
        B TIMER3_IRQHandler

		PUBWEAK CORDIC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CORDIC_IRQHandler
        B CORDIC_IRQHandler

        END
