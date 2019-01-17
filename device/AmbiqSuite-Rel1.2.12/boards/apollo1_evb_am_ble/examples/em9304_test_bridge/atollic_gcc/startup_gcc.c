//*****************************************************************************
//
//! @file startup_gcc.c
//!
//! @brief Definitions for interrupt handlers, the vector table, and the stack.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2018, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.12 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
// Forward declaration of interrupt handlers.
//
//*****************************************************************************
extern void am_reset_isr(void)        __attribute ((naked));
extern void am_nmi_isr(void)          __attribute ((weak));
extern void am_fault_isr(void)        __attribute ((weak));
extern void am_mpufault_isr(void)     __attribute ((weak, alias ("am_fault_isr")));
extern void am_busfault_isr(void)     __attribute ((weak, alias ("am_fault_isr")));
extern void am_usagefault_isr(void)   __attribute ((weak, alias ("am_fault_isr")));
extern void am_svcall_isr(void)       __attribute ((weak, alias ("am_default_isr")));
extern void am_debugmon_isr(void)     __attribute ((weak, alias ("am_default_isr")));
extern void am_pendsv_isr(void)       __attribute ((weak, alias ("am_default_isr")));
extern void am_systick_isr(void)      __attribute ((weak, alias ("am_default_isr")));

extern void am_brownout_isr(void)     __attribute ((weak, alias ("am_default_isr")));
extern void am_adc_isr(void)          __attribute ((weak, alias ("am_default_isr")));
extern void am_watchdog_isr(void)     __attribute ((weak, alias ("am_default_isr")));
extern void am_clkgen_isr(void)       __attribute ((weak, alias ("am_default_isr")));
extern void am_vcomp_isr(void)        __attribute ((weak, alias ("am_default_isr")));
extern void am_ioslave_ios_isr(void)  __attribute ((weak, alias ("am_default_isr")));
extern void am_ioslave_acc_isr(void)  __attribute ((weak, alias ("am_default_isr")));
extern void am_iomaster0_isr(void)    __attribute ((weak, alias ("am_default_isr")));
extern void am_iomaster1_isr(void)    __attribute ((weak, alias ("am_default_isr")));
extern void am_gpio_isr(void)         __attribute ((weak, alias ("am_default_isr")));
extern void am_ctimer_isr(void)       __attribute ((weak, alias ("am_default_isr")));
extern void am_uart_isr(void)         __attribute ((weak, alias ("am_default_isr")));
extern void am_software12_isr(void)   __attribute ((weak, alias ("am_default_isr")));
extern void am_software13_isr(void)   __attribute ((weak, alias ("am_default_isr")));
extern void am_software14_isr(void)   __attribute ((weak, alias ("am_default_isr")));
extern void am_software15_isr(void)   __attribute ((weak, alias ("am_default_isr")));

extern void am_default_isr(void)      __attribute ((weak));

//*****************************************************************************
//
// The entry point for the application.
//
//*****************************************************************************
extern int main(void);

//*****************************************************************************
//
// Reserve space for the system stack.
//
//*****************************************************************************
__attribute__ ((section(".stack")))
static uint32_t g_pui32Stack[512];

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
// Note: Aliasing and weakly exporting am_mpufault_isr, am_busfault_isr, and
// am_usagefault_isr does not work if am_fault_isr is defined externally.
// Therefore, we'll explicitly use am_fault_isr in the table for those vectors.
//
//*****************************************************************************
__attribute__ ((section(".isr_vector")))
void (* const g_am_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)g_pui32Stack + sizeof(g_pui32Stack)),
                                            // The initial stack pointer
    am_reset_isr,                           // The reset handler
    am_nmi_isr,                             // The NMI handler
    am_fault_isr,                           // The hard fault handler
    am_fault_isr,                           // The MPU fault handler
    am_fault_isr,                           // The bus fault handler
    am_fault_isr,                           // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    am_svcall_isr,                          // SVCall handle
    am_debugmon_isr,                        // Debug monitor handler
    0,                                      // Reserved
    am_pendsv_isr,                          // The PendSV handler
    am_systick_isr,                         // The SysTick handler

    //
    // Peripheral Interrupts
    //
    am_brownout_isr,                        //  0: Brownout
    am_watchdog_isr,                        //  1: Watchdog
    am_clkgen_isr,                          //  2: CLKGEN
    am_vcomp_isr,                           //  3: Voltage Comparator
    am_ioslave_ios_isr,                     //  4: I/O Slave general
    am_ioslave_acc_isr,                     //  5: I/O Slave access
    am_iomaster0_isr,                       //  6: I/O Master 0
    am_iomaster1_isr,                       //  7: I/O Master 1
    am_adc_isr,                             //  8: ADC
    am_gpio_isr,                            //  9: GPIO
    am_ctimer_isr,                          // 10: CTIMER
    am_uart_isr,                            // 11: UART
    am_software12_isr,                      // 12: Software Interrupt
    am_software13_isr,                      // 13: Software Interrupt
    am_software14_isr,                      // 14: Software Interrupt
    am_software15_isr                       // 15: Software Interrupt
};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.
//
//*****************************************************************************
#if defined(__GNUC_STDC_INLINE__)
void
am_reset_isr(void)
{
    //
    // Set the vector table pointer.
    //
    __asm("    ldr    r0, =0xE000ED08\n"
          "    ldr    r1, =g_am_pfnVectors\n"
          "    str    r1, [r0]");

    //
    // Set the stack pointer.
    //
    __asm("    ldr    sp, [r1]");
#ifndef NOFPU
    //
    // Enable the FPU.
    //
    __asm("ldr  r0, =0xE000ED88\n"
          "ldr  r1,[r0]\n"
          "orr  r1,#(0xF << 20)\n"
          "str  r1,[r0]\n"
          "dsb\n"
          "isb\n");
#endif
    //
    // Copy the data segment initializers from flash to SRAM.
    //
    __asm("    ldr     r0, =_init_data\n"
          "    ldr     r1, =_sdata\n"
          "    ldr     r2, =_edata\n"
          "copy_loop:\n"
          "        ldr   r3, [r0], #4\n"
          "        str   r3, [r1], #4\n"
          "        cmp     r1, r2\n"
          "        blt     copy_loop\n");
    //
    // Zero fill the bss segment.
    //
    __asm("    ldr     r0, =_sbss\n"
          "    ldr     r1, =_ebss\n"
          "    mov     r2, #0\n"
          "zero_loop:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop");

    //
    // Call the application's entry point.
    //
    main();

    //
    // If main returns then execute a break point instruction
    //
    __asm("    bkpt     ");
}
#else
#error GNU STDC inline not supported.
#endif

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
void
am_nmi_isr(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
void
am_fault_isr(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
void
am_default_isr(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}

