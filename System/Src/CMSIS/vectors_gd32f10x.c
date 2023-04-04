/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------
#include "cortexm/exception-handlers.h"

// ----------------------------------------------------------------------------

void __attribute__((weak))
Default_Handler(void);

// Forward declaration of the specific IRQ handlers. These are aliased
// to the Default_Handler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
void __attribute__ ((weak, alias ("Default_Handler")))
WWDGT_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
LVD_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
TAMPER_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
RTC_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
FMC_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
RCU_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
EXTI0_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
EXTI1_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
EXTI2_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
EXTI3_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
EXTI4_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
DMA0_Channel0_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
DMA0_Channel1_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
DMA0_Channel2_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
DMA0_Channel3_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
DMA0_Channel4_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
DMA0_Channel5_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
DMA0_Channel6_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
ADC0_1_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
USBD_HP_CAN0_TX_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
USBD_LP_CAN0_RX0_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
CAN0_RX1_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
CAN0_EWMC_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
EXTI5_9_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
TIMER0_BRK_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
TIMER0_UP_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
TIMER0_TRG_CMT_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
TIMER0_Channel_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
TIMER1_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
TIMER2_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
TIMER3_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
I2C0_EV_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
I2C0_ER_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
I2C1_EV_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
I2C1_ER_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
SPI0_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
SPI1_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
USART0_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
USART1_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
USART2_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
EXTI10_15_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
RTC_Alarm_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
USBD_WKUP_IRQHandler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
EXMC_IRQHandler(void);

// ----------------------------------------------------------------------------

extern unsigned int _estack;

typedef void
(*const pHandler)(void);

// ----------------------------------------------------------------------------

// The vector table.
// This relies on the linker script to place at correct location in memory.

__attribute__ ((section(".isr_vector"),used))
pHandler __isr_vectors[] = { //
		(pHandler) &_estack,                        // The initial stack pointer
				Reset_Handler,                            // The reset handler

				NMI_Handler,                              // The NMI handler
				HardFault_Handler,                     // The hard fault handler

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
				MemManage_Handler,                      // The MPU fault handler
				BusFault_Handler,                       // The bus fault handler
				UsageFault_Handler,                   // The usage fault handler
#else
        0, 0, 0,				  // Reserved
#endif
				0,                                        // Reserved
				0,                                        // Reserved
				0,                                        // Reserved
				0,                                        // Reserved
				SVC_Handler,                              // SVCall handler
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
				DebugMon_Handler,                       // Debug monitor handler
#else
        0,					  // Reserved
#endif
				0,                                        // Reserved
				PendSV_Handler,                           // The PendSV handler
				SysTick_Handler,                          // The SysTick handler

				// ----------------------------------------------------------------------
				// gd32f10x vectors
				WWDGT_IRQHandler,				//
				LVD_IRQHandler,					//
				TAMPER_IRQHandler,				//
				RTC_IRQHandler,					//
				FMC_IRQHandler,					//
				RCU_IRQHandler,					//
				EXTI0_IRQHandler,				//
				EXTI1_IRQHandler,				//
				EXTI2_IRQHandler,				//
				EXTI3_IRQHandler,				//
				EXTI4_IRQHandler,				//
				DMA0_Channel0_IRQHandler,		//
				DMA0_Channel1_IRQHandler,		//
				DMA0_Channel2_IRQHandler,		//
				DMA0_Channel3_IRQHandler,		//
				DMA0_Channel4_IRQHandler,		//
				DMA0_Channel5_IRQHandler,		//
				DMA0_Channel6_IRQHandler,		//
				ADC0_1_IRQHandler,				//
				USBD_HP_CAN0_TX_IRQHandler,		//
				USBD_LP_CAN0_RX0_IRQHandler,	//
				CAN0_RX1_IRQHandler,			//
				CAN0_EWMC_IRQHandler,			//
				EXTI5_9_IRQHandler,				//
				TIMER0_BRK_IRQHandler,			//
				TIMER0_UP_IRQHandler,			//
				TIMER0_TRG_CMT_IRQHandler,		//
				TIMER0_Channel_IRQHandler,		//
				TIMER1_IRQHandler,				//
				TIMER2_IRQHandler,				//
				TIMER3_IRQHandler,				//
				I2C0_EV_IRQHandler,				//
				I2C0_ER_IRQHandler,				//
				I2C1_EV_IRQHandler,				//
				I2C1_ER_IRQHandler,				//
				SPI0_IRQHandler,				//
				SPI1_IRQHandler,				//
				USART0_IRQHandler,				//
				USART1_IRQHandler,				//
				USART2_IRQHandler,				//
				EXTI10_15_IRQHandler,			//
				RTC_Alarm_IRQHandler,			//
				USBD_WKUP_IRQHandler,			//
				0,								//
				0,								//
				0,								//
				0,								//
				0,								//
				EXMC_IRQHandler,				//
		};

// ----------------------------------------------------------------------------

// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.

void __attribute__ ((section(".after_vectors"))) Default_Handler(void) {
	while (1) {
		;
	}
}

// ----------------------------------------------------------------------------
