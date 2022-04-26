;******************** (C) COPYRIGHT 2018 MIC ********************
;* File Name          : startup_vtm071x.s
;* Author             : MIC Software Team
;* Version            : V1.0.0
;* Date               : 03/01/2018
;* Description        : vtm071x Devices vector table for MDK-ARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM0 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>   
;******************************************************************************
;  @attention
; 
;  THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
;  WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
;  TIME. AS A RESULT, MIC SHALL NOT BE HELD LIABLE FOR ANY
;  DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
;  FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
;  CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;******************************************************************************
;
; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>


Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000800

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
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

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler    PROC
                 EXPORT  Reset_Handler                 [WEAK]
        IMPORT  __main
        IMPORT  SystemInit  
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  RTC_IRQHandler                 [WEAK]
                EXPORT  USB_IRQHandler                 [WEAK]
                EXPORT  USB_DMA_IRQHandler             [WEAK]
                EXPORT  FLASH_IRQHandler               [WEAK]
                EXPORT  USART0_IRQHandler              [WEAK]
                EXPORT  USART1_IRQHandler              [WEAK]
                EXPORT  I2C0_IRQHandler                [WEAK]
                EXPORT  SPI0_IRQHandler                [WEAK]
                EXPORT  TIMER0_IRQHandler              [WEAK]
                EXPORT  TIMER1_IRQHandler              [WEAK]
                EXPORT  MCPWM_IRQHandler               [WEAK]
                EXPORT  DMA_IRQHandler                 [WEAK]
                EXPORT  GPIO0_TO_GPIO3_IRQHandler      [WEAK]
                EXPORT  ADC_IRQHandler                 [WEAK]
                EXPORT  ACMP_IRQHandler                [WEAK]
                EXPORT  BOD_IRQHandler                 [WEAK]
                EXPORT  BOR_IRQHandler                 [WEAK]
                EXPORT  GPIO4_TO_GPIO6_IRQHandler      [WEAK]
                EXPORT  DAC_IRQHandler                 [WEAK]
                EXPORT  I2C1_IRQHandler                [WEAK]
                EXPORT  TSC_IRQHandler                 [WEAK]
                EXPORT  SPI1_IRQHandler                [WEAK]
                EXPORT  TIMER2_IRQHandler              [WEAK]
                EXPORT  TIMER3_IRQHandler              [WEAK]
                EXPORT  CORDIC_IRQHandler              [WEAK]

RTC_IRQHandler
USB_IRQHandler
USB_DMA_IRQHandler
FLASH_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
I2C0_IRQHandler
SPI0_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
MCPWM_IRQHandler
DMA_IRQHandler
GPIO0_TO_GPIO3_IRQHandler
ADC_IRQHandler
ACMP_IRQHandler
BOD_IRQHandler
BOR_IRQHandler
GPIO4_TO_GPIO6_IRQHandler
DAC_IRQHandler
I2C1_IRQHandler
TSC_IRQHandler
SPI1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
CORDIC_IRQHandler

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;************************ (C) COPYRIGHT MIC *****END OF FILE*****
