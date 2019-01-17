//*****************************************************************************
//
//  am_hal_ctimer.c
//! @file
//!
//! @brief Functions for interfacing with the Counter/Timer module.
//!
//! @addtogroup ctimer3 Counter/Timer (CTIMER)
//! @ingroup apollo3hal
//! @{
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
// This is part of revision v1.2.12-830-g39ebe7dbe of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

//*****************************************************************************
//
// Address space distance between timer configuration registers.
//
//*****************************************************************************
#if AM_CMSIS_REGS
//! Size of timer register block. T/E, CMPA, CMPB, CTRL, AUXA, AUXB, AUXCTRL.
#define TIMER_OFFSET            (&CTIMER->TMR1 - &CTIMER->TMR0)
//! CMPR Register Offset.
#define CTIMER_CMPR_OFFSET      (&CTIMER->CMPRB0 - &CTIMER->CMPRA0)
//! AUX CMPR Register Offset.
#define CTIMER_CMPR_AUX_OFFSET  (&CTIMER->CMPRAUXB0 - &CTIMER->CMPRAUXA0)
#else // AM_CMSIS_REGS
//! Size of timer register block. T/E, CMPA, CMPB, CTRL, AUXA, AUXB, AUXCTRL.
#define TIMER_OFFSET        (AM_REG_CTIMER_TMR1_O - AM_REG_CTIMER_TMR0_O)
//! CMPR Register Offset.
#define CTIMER_CMPR_OFFSET  (AM_REG_CTIMER_CMPRB0_O - AM_REG_CTIMER_CMPRA0_O)
//! AUX CMPR Register Offset.
#define CTIMER_CMPR_AUX_OFFSET  (AM_REG_CTIMER_CMPRAUXB0_O - AM_REG_CTIMER_CMPRAUXA0_O)
#endif // AM_CMSIS_REGS


//*****************************************************************************
//
// Adjacency check
//
// This is related to the timer read workaround. This macro checks to see if
// the two supplied count values are within one "tick" of eachother. It should
// still pass in the event of a timer rollover.
//
//*****************************************************************************
//! Timer read workaround: Do count values differ by one tick or less.
#define adjacent(A, B)      (((A) == (B)) || (((A) + 1) == (B)) || ((B) == 0))

//*****************************************************************************
//
//! Array of function pointers for handling CTimer interrupts.
//
//*****************************************************************************
am_hal_ctimer_handler_t am_hal_ctimer_ppfnHandlers[32];


#if (NEED_BACK2BACK_READ)
//*****************************************************************************
//
// Static function for reading the timer value.
//
//*****************************************************************************
#if defined(__GNUC_STDC_INLINE__)
__attribute__((naked))
static
void
back2back_reads(uint32_t u32TimerAddr, uint32_t u32Data[])
{
    // u32TimerAddr = address of the timer to be read.
    // u32Data[] is a pointer to a 3 word data array provided by the caller.
    __asm
    (
        // Do 3 back-to-back reads of the register
        "   push    {r4}\n"                     // Save r4
        "   push    {r1}\n"                     // Save the data array ptr for later
        "   mov     r2, r0\n"                   // Get Timer Addr
        "   mrs     r4, PRIMASK\n"              // Save PRIMASK
        "   cpsid   i\n"                        // __disable_irq()
        "   nop\n"                              // Give the disable a cycle to take affect (but almost certainly not really needed)
        "   ldr     r0, [r2, #0]\n"             // Get TMRn register value
        "   ldr     r1, [r2, #0]\n"             // Get TMRn register value again
        "   ldr     r3, [r2, #0]\n"             // Get TMRn register value for a third time
        "   msr     PRIMASK, r4\n"              // Restore PRIMASK
        "   pop     {r2}\n"                     // Get the array ptr
        "   str     r0, [r2, #0]\n"             // Store register value to variable
        "   str     r1, [r2, #4]\n"             // Store register value to variable
        "   str     r3, [r2, #8]\n"             // Store register value to variable
        "   pop     {r4}\n"                     // restore r4
        "   bx      lr\n"
    );
}

#elif (defined (__ARMCC_VERSION)) && (__ARMCC_VERSION <  6000000)
__asm static uint32_t
back2back_reads( uint32_t u32TimerAddr, uint32_t u32Data[])
{
    push    {r4}                     // Save r4
    push    {r1}                     // Save the data array ptr for later
    mov     r2, r0                   // Get Timer Addr
    mrs     r4, PRIMASK              // Save PRIMASK
    cpsid   i                        // __disable_irq()
    nop                              // Give the disable a cycle to take affect (but almost certainly not really needed)
    ldr     r0, [r2, #0]             // Get TMRn register value
    ldr     r1, [r2, #0]             // Get TMRn register value again
    ldr     r3, [r2, #0]             // Get TMRn register value for a third time
    msr     PRIMASK, r4              // Restore PRIMASK
    pop     {r2}                     // Get the array ptr
    str     r0, [r2, #0]             // Store register value to variable
    str     r1, [r2, #4]             // Store register value to variable
    str     r3, [r2, #8]             // Store register value to variable
    pop     {r4}                     // Restore r4
    bx      lr
}

#elif defined(__IAR_SYSTEMS_ICC__)
#pragma diag_suppress = Pe940   // Suppress IAR compiler warning about missing
                                // return statement on a non-void function
__stackless static uint32_t
back2back_reads( uint32_t u32TimerAddr, uint32_t u32Data[])
{
    __asm("    push    {r4}");          // Save r4
    __asm("    push    {r1}");          // Save the data array ptr for later
    __asm("    mov     r2, r0");        // Get Timer Addr
    __asm("    mrs     r4, PRIMASK");   // Save PRIMASK"
    __asm("    cpsid   i");             // __disable_irq()
    __asm("    nop");                   // Give the disable a cycle to take affect (but almost certainly not really needed)
    __asm("    ldr     r0, [r2, #0]");  // Get TMRn register value
    __asm("    ldr     r1, [r2, #0]");  // Get TMRn register value again
    __asm("    ldr     r3, [r2, #0]");  // Get TMRn register value for a third time
    __asm("    msr     PRIMASK, r4");   // Restore PRIMASK
    __asm("    pop     {r2}");          // Get the array ptr
    __asm("    str     r0, [r2, #0]");  // Store register value to variable
    __asm("    str     r1, [r2, #4]");  // Store register value to variable
    __asm("    str     r3, [r2, #8]");  // Store register value to variable
    __asm("    pop     {r4}");          // Restore r4
    __asm("    bx      lr");
}
#pragma diag_default = Pe940    // Restore IAR compiler warning
#endif
#endif


//*****************************************************************************
//
//! @brief Convenience function for responding to CTimer interrupts.
//!
//! @param ui32Status is the interrupt status as returned by
//! am_hal_ctimer_int_status_get()
//!
//! This function may be called from am_ctimer_isr() to read the status of
//! the CTimer interrupts, determine which source caused the most recent
//! interrupt, and call an interrupt handler function to respond. The interrupt
//! handler to be called must be first registered with the
//! am_hal_ctimer_int_register() function.
//!
//! In the event that multiple sources are active, the corresponding
//! interrupt handlers will be called in numerical order based on interrupt def.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_int_service(uint32_t ui32Status)
{

    am_hal_ctimer_handler_t pfnHandler;

    while ( ui32Status )
    {
        uint32_t ui32Clz;
        //
        // Pick one of any remaining active interrupt bits
        //
#ifdef __IAR_SYSTEMS_ICC__
        ui32Clz = __CLZ(ui32Status);
#else
        ui32Clz = __builtin_clz(ui32Status);
#endif

        //
        // Turn off the bit we picked in the working copy
        //
        ui32Status &= ~(0x80000000 >> ui32Clz);

        //
        // Check the bit handler table to see if there is an interrupt handler
        // registered for this particular bit.
        //
        pfnHandler = am_hal_ctimer_ppfnHandlers[31 - ui32Clz];
        if ( pfnHandler )
        {
            //
            // If we found an interrupt handler routine, call it now.
            //
            pfnHandler();
        }
    }

} // am_hal_ctimer_int_service()

//*****************************************************************************
//
//! @brief Register an interrupt handler for CTimer.
//!
//! @param ui32Interrupt - interrupt number to assign this interrupt handler to.
//! @param pfnHandler - Function to call when this interrupt is received.
//!
//! This function allows the caller to specify a function that should be called
//! any time a Ctimer interrupt is received. Registering an
//! interrupt handler using this function adds the function pointer to an array
//! in SRAM. This interrupt handler will be called by am_hal_ctimer_int_service()
//! whenever the ui32Status parameter indicates that the corresponding interrupt.
//!
//! To remove an interrupt handler that has already been registered, the
//! pfnHandler parameter may be set to zero.
//!
//! @note This function will not have any effect unless the
//! am_hal_ctimer_int_service() function is being used.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_int_register(uint32_t ui32Interrupt,
                           am_hal_ctimer_handler_t pfnHandler)
{
    uint32_t intIdx = 0;

    //
    // Check to make sure the interrupt number is valid. (Debug builds only)
    //
#if AM_CMSIS_REGS
    switch (ui32Interrupt)
    {
        case CTIMER_INTEN_CTMRA0C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA0C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB0C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB0C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA1C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA1C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB1C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB1C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA2C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA2C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB2C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB2C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA3C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA3C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB3C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB3C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA4C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA4C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB4C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB4C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA5C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA5C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB5C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB5C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA6C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA6C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB6C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB6C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA7C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA7C0INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB7C0INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB7C0INT_Pos;
            break;

        // Counter/Timer A0 interrupt based on COMPR1.
        case CTIMER_INTEN_CTMRA0C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA0C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB0C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB0C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA1C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA1C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB1C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB1C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA2C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA2C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB2C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB2C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA3C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA3C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB3C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB3C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRA4C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA4C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB4C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB4C1INT_Pos;
            break;
        case CTIMER_INTEN_CTMRA5C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA5C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB5C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB5C1INT_Pos;
            break;
        case CTIMER_INTEN_CTMRA6C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA6C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB6C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB6C1INT_Pos;
            break;
        case CTIMER_INTEN_CTMRA7C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRA7C1INT_Pos;
            break;

        case CTIMER_INTEN_CTMRB7C1INT_Msk:
            intIdx = CTIMER_INTEN_CTMRB7C1INT_Pos;
            break;

        default:
            am_hal_debug_assert_msg(false, "CTimer interrupt number out of range.");
    }
#else // AM_CMSIS_REGS
    switch (ui32Interrupt)
    {
        case AM_REG_CTIMER_INTEN_CTMRA0C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA0C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB0C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB0C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA1C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA1C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB1C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB1C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA2C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA2C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB2C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB2C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA3C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA3C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB3C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB3C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA4C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA4C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB4C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB4C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA5C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA5C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB5C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB5C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA6C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA6C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB6C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB6C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA7C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA7C0INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB7C0INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB7C0INT_S;
            break;

        // Counter/Timer A0 interrupt based on COMPR1.
        case AM_REG_CTIMER_INTEN_CTMRA0C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA0C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB0C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB0C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA1C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA1C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB1C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB1C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA2C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA2C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB2C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB2C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA3C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA3C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB3C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB3C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRA4C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA4C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB4C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB4C1INT_S;
            break;
        case AM_REG_CTIMER_INTEN_CTMRA5C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA5C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB5C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB5C1INT_S;
            break;
        case AM_REG_CTIMER_INTEN_CTMRA6C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA6C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB6C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB6C1INT_S;
            break;
        case AM_REG_CTIMER_INTEN_CTMRA7C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRA7C1INT_S;
            break;

        case AM_REG_CTIMER_INTEN_CTMRB7C1INT_M:
            intIdx = AM_REG_CTIMER_INTEN_CTMRB7C1INT_S;
            break;

        default:
            am_hal_debug_assert_msg(false, "CTimer interrupt number out of range.");
    }
#endif // AM_CMSIS_REGS

    am_hal_ctimer_ppfnHandlers[intIdx] = pfnHandler;

} // am_hal_ctimer_int_register()

//*****************************************************************************
//
//! @brief Set up the counter/timer.
//!
//! @param ui32ConfigVal is the value to set the global enable register.
//!
//! This function sets the global enable register inside a critical section.
//!
//! @return None.
//
//*****************************************************************************
void am_hal_ctimer_globen(uint32_t ui32ConfigVal)
{
    uint32_t *pui32ConfigReg;

    //
    // Find the correct register to write.
    //
#if AM_CMSIS_REGS
    pui32ConfigReg = (uint32_t *)(&CTIMERn(0)->GLOBEN);
#else // AM_CMSIS_REGS
    pui32ConfigReg = (uint32_t *)(AM_REG_CTIMERn(0) + AM_REG_CTIMER_GLOBEN_O);
#endif // AM_CMSIS_REGS

    //
    // Begin critical section while config registers are read and modified.
    //
    AM_CRITICAL_BEGIN

    //
    // Write our configuration value.
    //
    AM_REGVAL(pui32ConfigReg) = ui32ConfigVal;

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_globen()

//*****************************************************************************
//
//! @brief Set up the counter/timer.
//!
//! @param ui32TimerNumber is the number of the Timer that should be
//! configured.
//!
//! @param psConfig is a pointer to a structure that holds important settings
//! for the timer.
//!
//! This function should be used to perform the initial set-up of the
//! counter-timer.
//!
//! @note This function will eventually be replaced by
//! am_hal_ctimer_config_single(), which performs the same configuration
//! without requiring a structure. Please use am_hal_ctimer_config_single() for
//! new development.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_config(uint32_t ui32TimerNumber,
                     am_hal_ctimer_config_t *psConfig)
{
    uint32_t ui32ConfigVal;

    //
    // Start preparing the configuration word for this timer. The configuration
    // values for Timer A and Timer B provided in the config structure should
    // match the register definitions already, so we will mostly just need to
    // OR them together.
    //
    ui32ConfigVal = ( (psConfig->ui32TimerAConfig)  |
                      (psConfig->ui32TimerBConfig << 16) );

    //
    // OR in the Link bit if the timers need to be linked.
    //
    ui32ConfigVal |= psConfig->ui32Link ? AM_HAL_CTIMER_LINK : 0;

    //
    // Begin critical section while config registers are read and modified.
    //
    AM_CRITICAL_BEGIN

    //
    // Find the correct register to write.
    //
#if AM_CMSIS_REGS
    uint32_t *pui32ConfigReg = (uint32_t *)(&CTIMERn(0)->CTRL0 +
                                           (ui32TimerNumber * TIMER_OFFSET));
#else // AM_CMSIS_REGS
    uint32_t *pui32ConfigReg = (uint32_t *)(AM_REG_CTIMERn(0) + AM_REG_CTIMER_CTRL0_O +
                                  (ui32TimerNumber * TIMER_OFFSET));
#endif // AM_CMSIS_REGS

    //
    // Write our configuration value.
    //
    AM_REGVAL(pui32ConfigReg) = ui32ConfigVal;


    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_config()

//*****************************************************************************
//
//! @brief Set up the counter/timer.
//!
//! @param ui32TimerNumber is the number of the Timer that should be
//! configured.
//!
//! @param ui32TimerSegment specifies which segment of the timer should be
//! enabled.
//!
//! @param ui32ConfigVal specifies the configuration options for the selected
//! timer.
//!
//! This function should be used to perform the initial set-up of the
//! counter-timer. It can be used to configure either a 16-bit timer (A or B) or a
//! 32-bit timer using the BOTH option.
//!
//! Valid values for ui32TimerSegment are:
//!
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! The timer's clock source, mode, interrupt, and external pin behavior are
//! all controlled through the \e ui32Configval parameter. The valid options
//! for ui32ConfigVal include any ORed together combination of the following:
//!
//! Clock configuration macros:
//!
//!     AM_HAL_CTIMER_HFRC_24MHZ
//!     AM_HAL_CTIMER_LFRC_512HZ
//!     ... etc. (See am_hal_ctimer.h for the full set of options.)
//!
//! Mode selection macros:
//!
//!     AM_HAL_CTIMER_FN_ONCE
//!     AM_HAL_CTIMER_FN_REPEAT
//!     AM_HAL_CTIMER_FN_PWM_ONCE
//!     AM_HAL_CTIMER_FN_PWM_REPEAT
//!     AM_HAL_CTIMER_FN_CONTINUOUS
//!
//! Interrupt control:
//!
//!     AM_HAL_CTIMER_INT_ENABLE
//!
//! Pin control:
//!
//!     AM_HAL_CTIMER_PIN_ENABLE
//!     AM_HAL_CTIMER_PIN_INVERT
//!
//! ADC trigger (Timer 3 only):
//!
//!     AM_HAL_CTIMER_ADC_TRIG
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_config_single(uint32_t ui32TimerNumber,
                            uint32_t ui32TimerSegment,
                            uint32_t ui32ConfigVal)
{
    volatile uint32_t *pui32ConfigReg;

    //
    // Find the correct register to write based on the timer number.
    //
#if AM_CMSIS_REGS
    pui32ConfigReg = (uint32_t *)(&CTIMERn(0)->CTRL0 +
                                  (ui32TimerNumber * TIMER_OFFSET));
#else // AM_CMSIS_REGS
    pui32ConfigReg = (uint32_t *)(AM_REG_CTIMERn(0) + AM_REG_CTIMER_CTRL0_O +
                                  (ui32TimerNumber * TIMER_OFFSET));
#endif // AM_CMSIS_REGS

    //
    // Begin critical section while config registers are read and modified.
    //
    AM_CRITICAL_BEGIN
    uint32_t ui32WriteVal;

    //
    // Save the value that's already in the register.
    //
    ui32WriteVal = AM_REGVAL(pui32ConfigReg);

    //
    // If we're working with TIMERB, we need to shift our configuration value
    // up by 16 bits.
    //

    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        ui32ConfigVal = ((ui32ConfigVal & 0xFFFF) << 16);
    }

    //
    // Replace part of the saved register value with the configuration value
    // from the caller.
    //
    ui32WriteVal = (ui32WriteVal & ~(ui32TimerSegment)) | ui32ConfigVal;

    //
    // If we're configuring both timers, we need to set the "link" bit.
    //
    if ( ui32TimerSegment == AM_HAL_CTIMER_BOTH )
    {
        ui32WriteVal |= AM_HAL_CTIMER_LINK;
    }

    //
    // Write our completed configuration value.
    //
    AM_REGVAL(pui32ConfigReg) = ui32WriteVal;


    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_config_single()

//*****************************************************************************
//
//! @brief Start a timer
//!
//! @param ui32TimerNumber is the number of the timer to enable
//!
//! @param ui32TimerSegment specifies which segment of the timer should be
//! enabled.  Valid values for ui32TimerSegment are:
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! This function will enable a timer to begin incrementing. The \e
//! ui32TimerNumber parameter selects the timer that should be enabled, for
//! example, a 0 would target TIMER0. The \e ui32TimerSegment parameter allows
//! the caller to individually select a segment within a timer to be enabled,
//! such as TIMER0A, TIMER0B, or both.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_start(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment)
{
    //
    // Find the correct control register.
    //
#if AM_CMSIS_REGS
    volatile uint32_t *pui32ConfigReg = (uint32_t *)(&CTIMERn(0)->CTRL0 +
                                        (ui32TimerNumber * TIMER_OFFSET));
#else // AM_CMSIS_REGS
    volatile uint32_t *pui32ConfigReg = (uint32_t *)(AM_REG_CTIMERn(0) +
                                        AM_REG_CTIMER_CTRL0_O +
                                        (ui32TimerNumber * TIMER_OFFSET));
#endif // AM_CMSIS_REGS

    //
    // Begin critical section while config registers are read and modified.
    //
    AM_CRITICAL_BEGIN

    //
    // Read the current value.
    //
    uint32_t ui32ConfigVal = *pui32ConfigReg;

#if AM_CMSIS_REGS
    //
    // Clear out the "clear" bit.
    //
    ui32ConfigVal &= ~(ui32TimerSegment & (CTIMER_CTRL0_TMRA0CLR_Msk |
                                           CTIMER_CTRL0_TMRB0CLR_Msk));

    //
    // Set the "enable bit"
    //
    ui32ConfigVal |= (ui32TimerSegment & (CTIMER_CTRL0_TMRA0EN_Msk |
                                          CTIMER_CTRL0_TMRB0EN_Msk));
#else // AM_CMSIS_REGS
    //
    // Clear out the "clear" bit.
    //
    ui32ConfigVal &= ~(ui32TimerSegment & (AM_REG_CTIMER_CTRL0_TMRA0CLR_M |
                                           AM_REG_CTIMER_CTRL0_TMRB0CLR_M));

    //
    // Set the "enable bit"
    //
    ui32ConfigVal |= (ui32TimerSegment & (AM_REG_CTIMER_CTRL0_TMRA0EN_M |
                                          AM_REG_CTIMER_CTRL0_TMRB0EN_M));
#endif // AM_CMSIS_REGS

    //
    // Write the value back to the register.
    //
    AM_REGVAL(pui32ConfigReg) = ui32ConfigVal;

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_start()

//*****************************************************************************
//
//! @brief Stop a timer
//!
//! @param ui32TimerNumber is the number of the timer to disable.
//!
//! @param ui32TimerSegment specifies which segment of the timer should be
//! disabled.
//!
//! This function will stop the selected timer from incrementing. The \e
//! ui32TimerNumber parameter selects the timer that should be disabled, for
//! example, a 0 would target TIMER0. The \e ui32TimerSegment parameter allows
//! the caller to individually select a segment within a timer to be disabled,
//! such as TIMER0A, TIMER0B, or both.
//!
//! This function will stop a counter/timer from counting, but does not return
//! the count value to 'zero'. If you would like to reset the counter back to
//! zero, try the am_hal_ctimer_clear() function instead.
//!
//! Valid values for ui32TimerSegment are:
//!
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_stop(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment)
{
    volatile uint32_t *pui32ConfigReg;

    //
    // Find the correct control register.
    //
#if AM_CMSIS_REGS
    pui32ConfigReg = (uint32_t *)(&CTIMERn(0)->CTRL0 +
                                 (ui32TimerNumber * TIMER_OFFSET));
#else // AM_CMSIS_REGS
    pui32ConfigReg = (uint32_t *)(AM_REG_CTIMERn(0) + AM_REG_CTIMER_CTRL0_O +
                                  (ui32TimerNumber * TIMER_OFFSET));
#endif // AM_CMSIS_REGS

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Clear the "enable" bit
    //
#if AM_CMSIS_REGS
    AM_REGVAL(pui32ConfigReg) &= ~(ui32TimerSegment &
                                   (CTIMER_CTRL0_TMRA0EN_Msk |
                                    CTIMER_CTRL0_TMRB0EN_Msk));
#else // AM_CMSIS_REGS
    AM_REGVAL(pui32ConfigReg) &= ~(ui32TimerSegment &
                                   (AM_REG_CTIMER_CTRL0_TMRA0EN_M |
                                    AM_REG_CTIMER_CTRL0_TMRB0EN_M));
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_stop()

//*****************************************************************************
//
//! @brief Stops a timer and resets its value back to zero.
//!
//! @param ui32TimerNumber is the number of the timer to clear.
//!
//! @param ui32TimerSegment specifies which segment of the timer should be
//! cleared.
//!
//! This function will stop a free-running counter-timer, reset its value to
//! zero, and leave the timer disabled. When you would like to restart the
//! counter, you will need to call am_hal_ctimer_start().
//!
//! The \e ui32TimerSegment parameter allows the caller to individually select
//! a segment within, such as TIMER0A, TIMER0B, or both.
//!
//! Valid values for ui32TimerSegment are:
//!
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_clear(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment)
{
    volatile uint32_t *pui32ConfigReg;

    //
    // Find the correct control register.
    //
#if AM_CMSIS_REGS
    pui32ConfigReg = (uint32_t *)(&CTIMERn(0)->CTRL0 +
                                 (ui32TimerNumber * TIMER_OFFSET));

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Set the "clear" bit
    //
    AM_REGVAL(pui32ConfigReg) |= (ui32TimerSegment &
                                  (CTIMER_CTRL0_TMRA0CLR_Msk |
                                   CTIMER_CTRL0_TMRB0CLR_Msk));

    //
    // Done with critical section.
    //
    AM_CRITICAL_END
#else // AM_CMSIS_REGS
    pui32ConfigReg = (uint32_t *)(AM_REG_CTIMERn(0) + AM_REG_CTIMER_CTRL0_O +
                                  (ui32TimerNumber * TIMER_OFFSET));

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Set the "clear" bit
    //
    AM_REGVAL(pui32ConfigReg) |= (ui32TimerSegment &
                                  (AM_REG_CTIMER_CTRL0_TMRA0CLR_M |
                                   AM_REG_CTIMER_CTRL0_TMRB0CLR_M));

    //
    // Done with critical section.
    //
    AM_CRITICAL_END
#endif // AM_CMSIS_REGS

} // am_hal_ctimer_clear()

//*****************************************************************************
//
//! @brief Returns the current free-running value of the selected timer.
//!
//! @param ui32TimerNumber is the number of the timer to read.
//! @param ui32TimerSegment specifies which segment of the timer should be
//! read.
//!
//! This function returns the current free-running value of the selected timer.
//!
//! @note When reading from a linked timer, be sure to use AM_HAL_CTIMER both
//! for the segment argument.
//!
//! Valid values for ui32TimerSegment are:
//!
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! @return Current timer value.
//
//*****************************************************************************
uint32_t
am_hal_ctimer_read(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment)
{
    volatile uint32_t ui32Value = 0;

#if !NEED_BACK2BACK_READ
#if AM_CMSIS_REGS
    ui32Value = CTIMERn(ui32TimerNumber)->TMR0;
#else // AM_CMSIS_REGS
    ui32Value = AM_REGn(CTIMER, ui32TimerNumber, TMR0);
#endif // AM_CMSIS_REGS

    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        ui32Value >>= 16;
    }
    else if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERA )
    {
        ui32Value &= 0xFFFF;
    }
#else // (NEED_BACK2BACK_READ)
NOT_NEEDED  // Force a compile error if enabled. Not needed for Apollo3.
    uint32_t ui32Values[AM_HAL_CTIMER_TIMERS_NUM] = {0, };
    uint32_t ui32TimerAddrTbl[AM_HAL_CTIMER_TIMERS_NUM] =
    {
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_TMR0_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_TMR1_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_TMR2_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_TMR3_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_TMR4_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_TMR5_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_TMR6_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_TMR7_O
    };

    //
    //! Read the timer with back2back reads. This is a workaround for a clock
    //! domain synchronization issue. Some timer bits may be slow to increment,
    //! which means that the value in the timer register will sometimes be
    //! wrong.
    //!
    //! The architecture guarantees that:
    //!
    //! 1) If the timer is running at a speed close to the core frequency, the
    //! core and timer clock domains will be synchronized, and no "bad" reads
    //! will happen.
    //!
    //! 2) Bad reads will only happen if the core reads the timer register while
    //! the timer value is transitioning from one count to the next.
    //!
    //! 3) The timer will resolve to the correct value within one 24 MHz clock
    //! cycle.
    //!
    //! If we read the timer three times in a row with back-to-back load
    //! instructions, then we can guarantee that the timer will only have time
    //! to increment once, and that only one of the three reads can be wrong.
    //! This routine will perform the back-to-back reads and return all three
    //! values. The rest of this fuction determines which value we should
    //! actually use.
    //
    back2back_reads(ui32TimerAddrTbl[ui32TimerNumber], ui32Values);

    //
    // Shift or mask the values based on the given timer segment.
    //
    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        ui32Values[0] >>= 16;
        ui32Values[1] >>= 16;
        ui32Values[2] >>= 16;
    }
    else if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERA )
    {
        ui32Values[0] &= 0xFFFF;
        ui32Values[1] &= 0xFFFF;
        ui32Values[2] &= 0xFFFF;
    }

    //
    // Now, we'll figure out which of the three values is the correct time.
    //
    if (ui32Values[0] == ui32Values[1])
    {
        //
        // If the first two values match, then neither one was a bad read.
        // We'll take this as the current time.
        //
        ui32Value = ui32Values[1];
    }
    else
    {
        //
        // If the first two values didn't match, then one of them might be bad.
        // If one of the first two values is bad, then the third one should
        // always be correct. We'll take the third value as the correct time.
        //
        ui32Value = ui32Values[2];

        //
        // If all of the statements about the architecture are true, the third
        // value should be correct, and it should always be within one count of
        // either the first or the second value.
        //
        // Just in case, we'll check against the previous two values to make
        // sure that our final answer was reasonable. If it isn't, we will
        // flag it as a "bad read", and fail this assert statement.
        //
        // This shouldn't ever happen, and it hasn't ever happened in any of
        // our tests so far.
        //
        am_hal_debug_assert_msg((adjacent(ui32Values[1], ui32Values[2]) ||
                                 adjacent(ui32Values[0], ui32Values[2])),
                                "Bad CTIMER read");
    }
#endif // !NEED_BACK2BACK_READ

    return ui32Value;

} // am_hal_ctimer_read()


//*****************************************************************************
//
//! @brief Returns the current free-running value of the selected timer.
//!
//! @param ui32TimerNumber is the number of the timer to read.
//! @param ui32TimerSegment specifies which segment of the timer should be
//! read.
//!
//! This function returns the current free-running value of the selected timer.
//!
//! @note When reading from a linked timer, be sure to use AM_HAL_CTIMER both
//! for the segment argument.
//!
//! Valid values for ui32TimerSegment are:
//!
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! @return Current timer value.
//
//*****************************************************************************
uint32_t
am_hal_ctimer_aux_read(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment)
{
    volatile uint32_t ui32Value = 0;
    uint32_t ui32Values[AM_HAL_CTIMER_TIMERS_NUM] = {0, };
#if (NEED_BACK2BACK_READ)
    uint32_t ui32TimerAddrTbl[AM_HAL_CTIMER_TIMERS_NUM] =
    {
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_AUX0_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_AUX1_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_AUX2_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_AUX3_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_AUX4_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_AUX5_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_AUX6_O,
        REG_CTIMER_BASEADDR + AM_REG_CTIMER_AUX7_O
    };

    //
    // Read the timer with back2back reads. This is a workaround for a clock
    // domain synchronization issue. Some timer bits may be slow to increment,
    // which means that the value in the timer register will sometimes be
    // wrong.
    //
    // The architecture guarantees that:
    //
    // 1) If the timer is running at a speed close to the core frequency, the
    // core and timer clock domains will be synchronized, and no "bad" reads
    // will happen.
    //
    // 2) Bad reads will only happen if the core reads the timer register while
    // the timer value is transitioning from one count to the next.
    //
    // 3) The timer will resolve to the correct value within one 24 MHz clock
    // cycle.
    //
    // If we read the timer three times in a row with back-to-back load
    // instructions, then we can guarantee that the timer will only have time
    // to increment once, and that only one of the three reads can be wrong.
    // This routine will perform the back-to-back reads and return all three
    // values. The rest of this fuction determines which value we should
    // actually use.
    //
    back2back_reads(ui32TimerAddrTbl[ui32TimerNumber], ui32Values);
#endif

    //
    // Shift or mask the values based on the given timer segment.
    //
    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        ui32Values[0] >>= 16;
        ui32Values[1] >>= 16;
        ui32Values[2] >>= 16;
    }
    else if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERA )
    {
        ui32Values[0] &= 0xFFFF;
        ui32Values[1] &= 0xFFFF;
        ui32Values[2] &= 0xFFFF;
    }

    //
    // Now, we'll figure out which of the three values is the correct time.
    //
    if (ui32Values[0] == ui32Values[1])
    {
        //
        // If the first two values match, then neither one was a bad read.
        // We'll take this as the current time.
        //
        ui32Value = ui32Values[1];
    }
    else
    {
        //
        // If the first two values didn't match, then one of them might be bad.
        // If one of the first two values is bad, then the third one should
        // always be correct. We'll take the third value as the correct time.
        //
        ui32Value = ui32Values[2];

        //
        // If all of the statements about the architecture are true, the third
        // value should be correct, and it should always be within one count of
        // either the first or the second value.
        //
        // Just in case, we'll check against the previous two values to make
        // sure that our final answer was reasonable. If it isn't, we will
        // flag it as a "bad read", and fail this assert statement.
        //
        // This shouldn't ever happen, and it hasn't ever happened in any of
        // our tests so far.
        //
        am_hal_debug_assert_msg((adjacent(ui32Values[1], ui32Values[2]) ||
                                 adjacent(ui32Values[0], ui32Values[2])),
                                "Bad CTIMER read");
    }

    return ui32Value;

} // am_hal_ctimer_aux_read()

//*****************************************************************************
//
// Lookup tables used by am_hal_ctimer_output_config().
//
//  CTx_tbl[] relates the padnum and pad funcsel based on a given CTx.
//  Valid pads for CTx are: 4-7, 11-13, 18-19, 22-33, 35, 37, 39, 42-49.
//
//  outcfg_tbl[] contains attributes of the 4 output signal types for each
//  of the 32 CTx signals. Therefore it is indexed by CTnumber 0-31.
//  This table provides only the non-common OUTCFG attributes (2-5, other
//  settings are shown below).
//  OUTCFG 0 = Force output to 0.
//  OUTCFG 1 = Force output to 1.
//  OUTCFG 6 = A6OUT2.
//  OUTCFG 7 = A7OUT2.
//
//*****************************************************************************
#define CTXPADNUM(ctx)  ((CTx_tbl[ctx] >> 0) & 0x3f)
#define CTXPADFNC(ctx)  ((CTx_tbl[ctx] >> 8) & 0x7)
#define CTX(pad, fn)    ((fn << 8) | (pad << 0))
static const uint16_t CTx_tbl[32] =
{
    CTX(12,2), CTX(25,2), CTX(13,2), CTX(26,2), CTX(18,2),      // 0 - 4
    CTX(27,2), CTX(19,2), CTX(28,2), CTX( 5,7), CTX(29,2),      // 5 - 9
    CTX( 6,5), CTX(30,2), CTX(22,2), CTX(31,2), CTX(23,2),      // 10 - 14
    CTX(32,2), CTX(42,2), CTX( 4,6), CTX(43,2), CTX( 7,7),      // 15 - 19
    CTX(44,2), CTX(24,5), CTX(45,2), CTX(33,6), CTX(46,2),      // 20 - 24
    CTX(39,2), CTX(47,2), CTX(35,5), CTX(48,2), CTX(37,7),      // 25 - 29
    CTX(49,2), CTX(11,2)                                        // 30 - 31
};

#define OUTC(timB,timN,N2)      ((N2 << 4) | (timB << 3) | (timN << 0))
#define OUTCTIMN(ctx,n)         (outcfg_tbl[ctx][n] & (0x7 << 0))
#define OUTCTIMB(ctx,n)         (outcfg_tbl[ctx][n] & (0x1 << 3))
#define OUTCO2(ctx,n)           (outcfg_tbl[ctx][n] & (0x1 << 4))
static const uint8_t outcfg_tbl[32][4] =
{
    OUTC(0,0,0), OUTC(1,2,1), OUTC(0,5,1), OUTC(0,6,0),     // CTX0:  A0OUT,  B2OUT2, A5OUT2, A6OUT
    OUTC(0,0,1), OUTC(0,0,0), OUTC(0,5,0), OUTC(1,7,1),     // CTX1:  A0OUT2, A0OUT,  A5OUT,  B7OUT2
    OUTC(1,0,0), OUTC(1,1,1), OUTC(1,6,1), OUTC(0,7,0),     // CTX2:  B0OUT,  B1OUT2, B6OUT2, A7OUT
    OUTC(1,0,1), OUTC(1,0,0), OUTC(0,1,0), OUTC(0,6,0),     // CTX3:  B0OUT2, B0OUT,  A1OUT,  A6OUT
    OUTC(0,1,0), OUTC(0,2,1), OUTC(0,5,1), OUTC(1,5,0),     // CTX4:  A1OUT,  A2OUT2, A5OUT2, B5OUT
    OUTC(0,1,1), OUTC(0,1,0), OUTC(1,6,0), OUTC(0,7,0),     // CTX5:  A1OUT2, A1OUT,  B6OUT,  A7OUT
    OUTC(1,1,0), OUTC(0,1,0), OUTC(1,5,1), OUTC(1,7,0),     // CTX6:  B1OUT,  A1OUT,  B5OUT2, B7OUT
    OUTC(1,1,1), OUTC(1,1,0), OUTC(1,5,0), OUTC(0,7,0),     // CTX7:  B1OUT2, B1OUT,  B5OUT,  A7OUT
    OUTC(0,2,0), OUTC(0,3,1), OUTC(0,4,1), OUTC(1,6,0),     // CTX8:  A2OUT,  A3OUT2, A4OUT2, B6OUT
    OUTC(0,2,1), OUTC(0,2,0), OUTC(0,4,0), OUTC(1,0,0),     // CTX9:  A2OUT2, A2OUT,  A4OUT,  B0OUT
    OUTC(1,2,0), OUTC(1,3,1), OUTC(1,4,1), OUTC(0,6,0),     // CTX10: B2OUT,  B3OUT2, B4OUT2, A6OUT
    OUTC(1,2,1), OUTC(1,2,0), OUTC(1,4,0), OUTC(1,5,1),     // CTX11: B2OUT2, B2OUT,  B4OUT,  B5OUT2
    OUTC(0,3,0), OUTC(1,1,0), OUTC(1,0,1), OUTC(1,6,1),     // CTX12: A3OUT,  B1OUT,  B0OUT2, B6OUT2
    OUTC(0,3,1), OUTC(0,3,0), OUTC(0,6,0), OUTC(1,4,1),     // CTX13: A3OUT2, A3OUT,  A6OUT,  B4OUT2
    OUTC(1,3,0), OUTC(1,1,0), OUTC(1,7,1), OUTC(0,7,0),     // CTX14: B3OUT,  B1OUT,  B7OUT2, A7OUT
    OUTC(1,3,1), OUTC(1,3,0), OUTC(0,7,0), OUTC(0,4,1),     // CTX15: B3OUT2, B3OUT,  A7OUT,  A4OUT2
    OUTC(0,4,0), OUTC(0,0,0), OUTC(0,0,1), OUTC(1,3,1),     // CTX16: A4OUT,  A0OUT,  A0OUT2, B3OUT2
    OUTC(0,4,1), OUTC(1,7,0), OUTC(1,4,0), OUTC(0,1,1),     // CTX17: A4OUT2, B7OUT,  B4OUT,  A1OUT2
    OUTC(1,4,0), OUTC(1,0,0), OUTC(0,0,0), OUTC(0,3,1),     // CTX18: B4OUT,  B0OUT,  A0OUT,  A3OUT2
    OUTC(1,4,1), OUTC(0,2,0), OUTC(1,4,0), OUTC(1,1,1),     // CTX19: B4OUT2, A2OUT,  B4OUT,  B1OUT2
    OUTC(0,5,0), OUTC(0,1,0), OUTC(0,1,1), OUTC(1,2,1),     // CTX20: A5OUT,  A1OUT,  A1OUT2, B2OUT2
    OUTC(0,5,1), OUTC(0,1,0), OUTC(1,5,0), OUTC(0,0,1),     // CTX21: A5OUT2, A1OUT,  B5OUT,  A0OUT2
    OUTC(1,5,0), OUTC(0,6,0), OUTC(0,1,0), OUTC(0,2,1),     // CTX22: B5OUT,  A6OUT,  A1OUT,  A2OUT2
    OUTC(1,5,1), OUTC(0,7,0), OUTC(0,5,0), OUTC(1,0,1),     // CTX23: B5OUT2, A7OUT,  A5OUT,  B0OUT2
    OUTC(0,6,0), OUTC(0,2,0), OUTC(0,1,0), OUTC(1,1,1),     // CTX24: A6OUT,  A2OUT,  A1OUT,  B1OUT2
    OUTC(1,4,1), OUTC(1,2,0), OUTC(0,6,0), OUTC(0,2,1),     // CTX25: B4OUT2, B2OUT,  A6OUT,  A2OUT2
    OUTC(1,6,0), OUTC(1,2,0), OUTC(0,5,0), OUTC(0,1,1),     // CTX26: B6OUT,  B2OUT,  A5OUT,  A1OUT2
    OUTC(1,6,1), OUTC(0,1,0), OUTC(1,6,0), OUTC(1,2,1),     // CTX27: B6OUT2, A1OUT,  B6OUT,  B2OUT2
    OUTC(0,7,0), OUTC(0,3,0), OUTC(0,5,0), OUTC(1,0,1),     // CTX28: A7OUT,  A3OUT,  A5OUT,  B0OUT2
    OUTC(1,5,1), OUTC(0,1,0), OUTC(0,7,0), OUTC(1,3,1),     // CTX29: B5OUT2, A1OUT,  A7OUT,  A3OUT2
    OUTC(1,7,0), OUTC(1,3,0), OUTC(0,4,1), OUTC(0,0,1),     // CTX30: B7OUT,  B3OUT,  A4OUT2, A0OUT2
    OUTC(1,7,1), OUTC(0,6,0), OUTC(1,7,0), OUTC(1,3,1),     // CTX31: B7OUT2, A6OUT,  B7OUT,  B3OUT2
};

//*****************************************************************************
//
//! @brief Configure timer pin output.
//!
//! @param ui32TimerNumber is the number of the timer to configure.
//!
//! @param ui32TimerSegment specifies which segment of the timer to use.
//!
//! @param ui32TimerOutputConfig Output Configuration options.
//!
//! This function will configure the output pin for the selected timer.
//!
//! ui32TimerNumber
//!     The timer number, 0-7.
//! ui32TimerSegment
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//! ui32PadNum
//!     Pad number to be used for the output signal.
//! eOutputType
//!     AM_HAL_CTIMER_OUTPUT_NORMAL
//!     AM_HAL_CTIMER_OUTPUT_SECONDARY
//!     AM_HAL_CTIMER_OUTPUT_FORCE0
//!     AM_HAL_CTIMER_OUTPUT_FORCE1
//! eDriveStrength
//!     AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA   = 0x0,
//!     AM_HAL_GPIO_PIN_DRIVESTRENGTH_4MA   = 0x1,
//!     AM_HAL_GPIO_PIN_DRIVESTRENGTH_8MA   = 0x2,
//!     AM_HAL_GPIO_PIN_DRIVESTRENGTH_12MA  = 0x3
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_output_config(uint32_t ui32TimerNumber,
                            uint32_t ui32TimerSegment,
                            uint32_t ui32PadNum,
                            uint32_t eOutputType,
                            uint32_t eDriveStrength)
{
    uint32_t ux, ui32Ctx, ui32CtxPadNum;
    uint32_t ui32CtxOutcfgFnc, ui32CtxOutcfgMsk, ui32CfgShf;

    am_hal_gpio_pincfg_t sPinCfg = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    if ( (ui32PadNum > 49)  ||  (ui32TimerNumber > 7)   ||
         (eOutputType > AM_HAL_CTIMER_OUTPUT_FORCE1)    ||
         ( (ui32TimerSegment != AM_HAL_CTIMER_TIMERA) &&
           (ui32TimerSegment != AM_HAL_CTIMER_TIMERB) &&
           (ui32TimerSegment != AM_HAL_CTIMER_BOTH) ) )
    {
        return;
    }

    //
    // Lookup the CTx number based on the given pad number.
    //
    for ( ux = 0; ux < 32; ux++ )
    {
        ui32CtxPadNum = CTXPADNUM(ux);
        if ( ui32CtxPadNum == ui32PadNum )
        {
            ui32Ctx = ux;
            break;
        }
        ui32CtxPadNum = 0xFF;
    }

    if ( ui32CtxPadNum > 31 )
    {
        // No valid pad found.
        return;
    }

    if ( ( ui32TimerNumber >= 6 )                               &&
         ( ui32TimerSegment == AM_HAL_CTIMER_TIMERA )           &&
         (eOutputType == AM_HAL_CTIMER_OUTPUT_SECONDARY) )
    {
        //
        // A6OUT2 is function 6 for every CTx.
        // A7OUT2 is function 7 for every CTx.
        // Set the function to either 6 or 7.
        //
        ui32CtxOutcfgFnc = ui32TimerNumber;
    }
    else if ( eOutputType >= AM_HAL_CTIMER_OUTPUT_FORCE0 )
    {
        // Set the function to 0 or 1.
        ui32CtxOutcfgFnc = eOutputType - AM_HAL_CTIMER_OUTPUT_FORCE0;
    }
    else
    {
        //
        // Now, scan outcfg_tbl[] to determine how to set the pin.
        //
        for ( ux = 0; ux < 4; ux++ )
        {
            if ( (OUTCTIMN(ui32Ctx, ux) == ui32TimerNumber) )
            {
                bool bTimerB = OUTCTIMB(ui32Ctx, ux);
                bool bO2 = OUTCO2(ui32Ctx, ux) ? true : false;
                bool bOut2 = (eOutputType == AM_HAL_CTIMER_OUTPUT_SECONDARY);
                if ( ( ui32TimerSegment == AM_HAL_CTIMER_TIMERA )   &&
                     (!bTimerB)                                     &&
                     (bO2 == bOut2) )
                {
                    break;
                }

                if ( ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )   &&
                     (bTimerB)                                      &&
                     (bO2 == bOut2) )
                {
                    break;
                }
            }
        }

        if ( ux >= 4 )
        {
            return;
        }

        ui32CtxOutcfgFnc = ux + 2;
    }

    //
    // Looks like everything is valid.  Configure the pin.
    // Do the actual configuring inside a critical section.
    //
    ux = ui32Ctx % 10;
    ui32CfgShf = ux * 3;
    if ( ux > 4 )
    {
        ui32CfgShf += 1;
    }
    ui32CtxOutcfgMsk   = 0x7 << ui32CfgShf;
    ui32CtxOutcfgFnc <<= ui32CfgShf;

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Note: It turns out that the offsets of the 4 OUTCFG registers are not
    // evenly spaced.  Therefore we purposely use this 'if' chain to program
    // them explicitly (as opposed to doing modulo math to compute an addr).
    //
#if AM_CMSIS_REGS
    if ( ui32Ctx < 10 )
    {
        CTIMER->OUTCFG0 &= ~ui32CtxOutcfgMsk;
        CTIMER->OUTCFG0 |=  ui32CtxOutcfgFnc;
    }
    else if ( ui32Ctx < 20 )
    {
        CTIMER->OUTCFG1 &= ~ui32CtxOutcfgMsk;
        CTIMER->OUTCFG1 |=  ui32CtxOutcfgFnc;
    }
    else if ( ui32Ctx < 30 )
    {
        CTIMER->OUTCFG2 &= ~ui32CtxOutcfgMsk;
        CTIMER->OUTCFG2 |=  ui32CtxOutcfgFnc;
    }
    else
    {
        CTIMER->OUTCFG3 &= ~ui32CtxOutcfgMsk;
        CTIMER->OUTCFG3 |=  ui32CtxOutcfgFnc;
    }

    GPIO->CTENCFG &= ~(1 << ui32Ctx);
#else // AM_CMSIS_REGS
    if ( ui32Ctx < 10 )
    {
        AM_REG(CTIMER, OUTCFG0) &= ~ui32CtxOutcfgMsk;
        AM_REG(CTIMER, OUTCFG0) |=  ui32CtxOutcfgFnc;
    }
    else if ( ui32Ctx < 20 )
    {
        AM_REG(CTIMER, OUTCFG1) &= ~ui32CtxOutcfgMsk;
        AM_REG(CTIMER, OUTCFG1) |=  ui32CtxOutcfgFnc;
    }
    else if ( ui32Ctx < 20 )
    {
        AM_REG(CTIMER, OUTCFG2) &= ~ui32CtxOutcfgMsk;
        AM_REG(CTIMER, OUTCFG2) |=  ui32CtxOutcfgFnc;
    }
    else
    {
        AM_REG(CTIMER, OUTCFG3) &= ~ui32CtxOutcfgMsk;
        AM_REG(CTIMER, OUTCFG3) |=  ui32CtxOutcfgFnc;
    }

    AM_REG(GPIO, CTENCFG) &= ~(1 << ui32Ctx);
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

    //
    // Configure the GPIO for the given pad.
    //
    sPinCfg.uFuncSel = CTXPADFNC(ui32Ctx);
    sPinCfg.eDriveStrength = eDriveStrength;
    am_hal_gpio_pinconfig(ui32CtxPadNum, sPinCfg);

} // am_hal_ctimer_output_config()

//*****************************************************************************
//
//! @brief Configure timer inputs.
//!
//! @param ui32TimerNumber is the number of the timer to configure.
//!
//! @param ui32TimerSegment specifies which segment of the timer to use.
//!
//! @param ui32TimerInputConfig Input Configuration options.
//!
//! This function will configure the input pin for the selected timer.
//!
//! Valid values for ui32TimerSegment are:
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_input_config(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment,
                           uint32_t ui32TimerInputConfig)
{
    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_input_config()

//*****************************************************************************
//
//! @brief Set a compare register.
//!
//! @param ui32TimerNumber is the number of the timer to configure.
//!
//! @param ui32TimerSegment specifies which segment of the timer to use.
//! Valid values for ui32TimerSegment are:
//!
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! @param ui32CompareReg specifies which compare register should be set
//! (either 0 or 1)
//!
//! @param ui32Value is the value that should be written to the compare
//! register.
//!
//! This function allows the caller to set the values in the compare registers
//! for a timer. These registers control the period and duty cycle of the
//! timers and their associated output pins. Please see the datasheet for
//! further information on the operation of the compare registers. The \e
//! ui32TimerSegment parameter allows the caller to individually select a
//! segment within, such as TIMER0A, TIMER0B, or both.
//!
//! @note For simple manipulations of period or duty cycle for timers and PWMs,
//! you may find it easier to use the am_hal_ctimer_period_set() function.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_compare_set(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment,
                          uint32_t ui32CompareReg, uint32_t ui32Value)
{
    volatile uint32_t *pui32CmprRegA, *pui32CmprRegB;
    uint32_t ui32CmprRegA, ui32CmprRegB, ui32ValB;

    //
    // Find the correct compare register to write.
    // Assume A or BOTH.  We'll change later if B.
    //
#if AM_CMSIS_REGS
    pui32CmprRegA = (uint32_t *)(&CTIMERn(0)->CMPRA0 +
                                (ui32TimerNumber * TIMER_OFFSET));
#else // AM_CMSIS_REGS
    pui32CmprRegA = (uint32_t *)(AM_REG_CTIMERn(0) +
                                 AM_REG_CTIMER_CMPRA0_O +
                                 (ui32TimerNumber * TIMER_OFFSET));
#endif // AM_CMSIS_REGS
    pui32CmprRegB = pui32CmprRegA + CTIMER_CMPR_OFFSET / 4;

    ui32ValB = ( ui32TimerSegment == AM_HAL_CTIMER_BOTH ) ?
               ui32Value >> 16 : ui32Value & 0xFFFF;

    //
    // Write the compare register with the selected value.
    // Begin critical section while CMPR registers are modified.
    //
    AM_CRITICAL_BEGIN

    ui32CmprRegA = *pui32CmprRegA;
    ui32CmprRegB = *pui32CmprRegB;

#if AM_CMSIS_REGS
    if ( ui32CompareReg == 1 )
    {
        //
        // CMPR reg 1
        // Get the lower 16b (but may not be used if TIMERB).
        //
        ui32CmprRegA = ( (ui32CmprRegA & CTIMER_CMPRA0_CMPR0A0_Msk) |
                          _VAL2FLD(CTIMER_CMPRA0_CMPR1A0, ui32Value & 0xFFFF) );

        //
        // Get the upper 16b (but may not be used if TIMERA)
        //
        ui32CmprRegB = ( (ui32CmprRegB & CTIMER_CMPRA0_CMPR0A0_Msk) |
                          _VAL2FLD(CTIMER_CMPRA0_CMPR1A0, ui32ValB) );
    }
    else
    {
        //
        // CMPR reg 0
        // Get the lower 16b (but may not be used if TIMERB)
        //
        ui32CmprRegA = ( (ui32CmprRegA & CTIMER_CMPRA0_CMPR1A0_Msk) |
                         _VAL2FLD(CTIMER_CMPRA0_CMPR0A0, ui32Value & 0xFFFF) );

        //
        // Set the upper 16b (but may not be used if TIMERA)
        //
        ui32CmprRegB = ( (ui32CmprRegB & CTIMER_CMPRA0_CMPR1A0_Msk) |
                         _VAL2FLD(CTIMER_CMPRA0_CMPR0A0, ui32ValB) );
    }

    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        *pui32CmprRegB = ui32CmprRegB;
    }
    else
    {
        //
        // It's TIMERA or BOTH.
        //
        *pui32CmprRegA = ui32CmprRegA;

        if ( ui32TimerSegment == AM_HAL_CTIMER_BOTH )
        {
            *pui32CmprRegB = ui32CmprRegB;
        }
    }
#else // AM_CMSIS_REGS
    if ( ui32CompareReg == 1 )
    {
        //
        // CMPR reg 1
        // Get the lower 16b (but may not be used if TIMERB).
        //
        ui32CmprRegA = ( (ui32CmprRegA & AM_REG_CTIMER_CMPRA0_CMPR0A0_M) |
                          AM_REG_CTIMER_CMPRA0_CMPR1A0(ui32Value & 0xFFFF) );

        //
        // Get the upper 16b (but may not be used if TIMERA)
        //
        ui32CmprRegB = ( (ui32CmprRegB & AM_REG_CTIMER_CMPRA0_CMPR0A0_M) |
                          AM_REG_CTIMER_CMPRA0_CMPR1A0(ui32ValB) );
    }
    else
    {
        //
        // CMPR reg 0
        // Get the lower 16b (but may not be used if TIMERB)
        //
        ui32CmprRegA = ( (ui32CmprRegA & AM_REG_CTIMER_CMPRA0_CMPR1A0_M) |
                         AM_REG_CTIMER_CMPRA0_CMPR0A0(ui32Value & 0xFFFF) );

        //
        // Set the upper 16b (but may not be used if TIMERA)
        //
        ui32CmprRegB = ( (ui32CmprRegB & AM_REG_CTIMER_CMPRA0_CMPR1A0_M) |
                         AM_REG_CTIMER_CMPRA0_CMPR0A0(ui32ValB) );
    }

    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        *pui32CmprRegB = ui32CmprRegB;
    }
    else
    {
        //
        // It's TIMERA or BOTH.
        //
        *pui32CmprRegA = ui32CmprRegA;

        if ( ui32TimerSegment == AM_HAL_CTIMER_BOTH )
        {
            *pui32CmprRegB = ui32CmprRegB;
        }
    }
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_compare_set()

//*****************************************************************************
//
//! @brief Set a compare register.
//!
//! @param ui32TimerNumber is the number of the timer to configure.
//!
//! @param ui32TimerSegment specifies which segment of the timer to use.
//! Valid values for ui32TimerSegment are:
//!
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! @param ui32CompareReg specifies which compare register should be set
//! (either 0 or 1)
//!
//! @param ui32Value is the value that should be written to the compare
//! register.
//!
//! This function allows the caller to set the values in the compare registers
//! for a timer. These registers control the period and duty cycle of the
//! timers and their associated output pins. Please see the datasheet for
//! further information on the operation of the compare registers. The \e
//! ui32TimerSegment parameter allows the caller to individually select a
//! segment within, such as TIMER0A, TIMER0B, or both.
//!
//! @note For simple manipulations of period or duty cycle for timers and PWMs,
//! you may find it easier to use the am_hal_ctimer_period_set() function.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_aux_compare_set(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment,
                              uint32_t ui32CompareReg, uint32_t ui32Value)
{
    volatile uint32_t *pui32CmprRegA, *pui32CmprRegB;
    uint32_t ui32CmprRegA, ui32CmprRegB, ui32ValB;

    //
    // Find the correct compare register to write.
    // Assume A or BOTH.  We'll change later if B.
    //
#if AM_CMSIS_REGS
    pui32CmprRegA = (uint32_t *)(&CTIMERn(0)->CMPRAUXA0 +
                                (ui32TimerNumber * TIMER_OFFSET));
#else // AM_CMSIS_REGS
    pui32CmprRegA = (uint32_t *)(AM_REG_CTIMERn(0) +
                                 AM_REG_CTIMER_CMPRAUXA0_O +
                                 (ui32TimerNumber * TIMER_OFFSET));
#endif // AM_CMSIS_REGS
    pui32CmprRegB = pui32CmprRegA + CTIMER_CMPR_AUX_OFFSET / 4;
    ui32ValB = ( ui32TimerSegment == AM_HAL_CTIMER_BOTH ) ?
               ui32Value >> 16 : ui32Value & 0xFFFF;

    //
    // Write the compare register with the selected value.
    // Begin critical section while CMPR registers are modified.
    //
    AM_CRITICAL_BEGIN

    ui32CmprRegA = *pui32CmprRegA;
    ui32CmprRegB = *pui32CmprRegB;

#if AM_CMSIS_REGS
    if ( ui32CompareReg == 1 )
    {
        //
        // CMPR reg 1
        // Get the lower 16b (but may not be used if TIMERB).
        //
        ui32CmprRegA = ( (ui32CmprRegA & CTIMER_CMPRAUXA0_CMPR2A0_Msk) |
                          _VAL2FLD(CTIMER_CMPRAUXA0_CMPR3A0, ui32Value & 0xFFFF) );

        //
        // Get the upper 16b (but may not be used if TIMERA)
        //
        ui32CmprRegB = ( (ui32CmprRegB & CTIMER_CMPRAUXA0_CMPR2A0_Msk) |
                          _VAL2FLD(CTIMER_CMPRAUXA0_CMPR3A0, ui32ValB) );
    }
    else
    {
        //
        // CMPR reg 0
        // Get the lower 16b (but may not be used if TIMERB)
        //
        ui32CmprRegA = ( (ui32CmprRegA & CTIMER_CMPRAUXA0_CMPR3A0_Msk) |
                         _VAL2FLD(CTIMER_CMPRAUXA0_CMPR2A0, ui32Value & 0xFFFF) );

        //
        // Set the upper 16b (but may not be used if TIMERA)
        //
        ui32CmprRegB = ( (ui32CmprRegB & CTIMER_CMPRAUXA0_CMPR3A0_Msk) |
                         _VAL2FLD(CTIMER_CMPRAUXA0_CMPR2A0, ui32ValB) );
    }

    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        *pui32CmprRegB = ui32CmprRegB;
    }
    else
    {
        //
        // It's TIMERA or BOTH.
        //
        *pui32CmprRegA = ui32CmprRegA;

        if ( ui32TimerSegment == AM_HAL_CTIMER_BOTH )
        {
            *pui32CmprRegB = ui32CmprRegB;
        }
    }
#else // AM_CMSIS_REGS
    if ( ui32CompareReg == 1 )
    {
        //
        // CMPR reg 1
        // Get the lower 16b (but may not be used if TIMERB).
        //
        ui32CmprRegA = ( (ui32CmprRegA & AM_REG_CTIMER_CMPRAUXA0_CMPR2A0_M) |
                          AM_REG_CTIMER_CMPRAUXA0_CMPR3A0(ui32Value & 0xFFFF) );

        //
        // Get the upper 16b (but may not be used if TIMERA)
        //
        ui32CmprRegB = ( (ui32CmprRegB & AM_REG_CTIMER_CMPRAUXA0_CMPR2A0_M) |
                          AM_REG_CTIMER_CMPRAUXA0_CMPR3A0(ui32ValB) );
    }
    else
    {
        //
        // CMPR reg 0
        // Get the lower 16b (but may not be used if TIMERB)
        //
        ui32CmprRegA = ( (ui32CmprRegA & AM_REG_CTIMER_CMPRAUXA0_CMPR3A0_M) |
                         AM_REG_CTIMER_CMPRAUXA0_CMPR2A0(ui32Value & 0xFFFF) );

        //
        // Set the upper 16b (but may not be used if TIMERA)
        //
        ui32CmprRegB = ( (ui32CmprRegB & AM_REG_CTIMER_CMPRAUXA0_CMPR3A0_M) |
                         AM_REG_CTIMER_CMPRAUXA0_CMPR2A0(ui32ValB) );
    }

    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        *pui32CmprRegB = ui32CmprRegB;
    }
    else
    {
        //
        // It's TIMERA or BOTH.
        //
        *pui32CmprRegA = ui32CmprRegA;

        if ( ui32TimerSegment == AM_HAL_CTIMER_BOTH )
        {
            *pui32CmprRegB = ui32CmprRegB;
        }
    }
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_aux_compare_set()

//*****************************************************************************
//
//! @brief Set the period and duty cycle of a timer.
//!
//! @param ui32TimerNumber is the number of the timer to configure.
//!
//! @param ui32TimerSegment specifies which segment of the timer to use.
//!
//! @param ui32Period specifies the desired period.  This parameter effectively
//! specifies the CTIMER CMPR field(s). The CMPR fields are handled in hardware
//! as (n+1) values, therefore ui32Period is actually specified as 1 less than
//! the desired period. Finally, as mentioned in the data sheet, the CMPR fields
//! cannot be 0 (a value of 1), so neither can ui32Period be 0.
//!
//! @param ui32OnTime set the number of clocks where the output signal is high.
//!
//! This function should be used for simple manipulations of the period and
//! duty cycle of a counter/timer. To set the period and/or duty cycle of a
//! linked timer pair, use AM_HAL_CTIMER_BOTH as the timer segment argument. If
//! you would like to set the period and/or duty cycle for both TIMERA and
//! TIMERB you will need to call this function twice: once for TIMERA, and once
//! for TIMERB.
//!
//! Valid values for ui32TimerSegment are:
//!
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! @note The ui32OnTime parameter will only work if the timer is currently
//! operating in one of the PWM modes.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_period_set(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment,
                         uint32_t ui32Period, uint32_t ui32OnTime)
{
    volatile uint32_t *pui32ControlReg;
    volatile uint32_t *pui32CompareRegA;
    volatile uint32_t *pui32CompareRegB;
    uint32_t ui32Mode, ui32Comp0, ui32Comp1;

#if AM_CMSIS_REGS
    //
    // Find the correct control register to pull the function select field
    // from.
    //
    pui32ControlReg = (uint32_t *)(&CTIMERn(0)->CTRL0 +
                                  (ui32TimerNumber * TIMER_OFFSET));

    //
    // Find the correct compare registers to write.
    //
    pui32CompareRegA = (uint32_t *)(&CTIMERn(0)->CMPRA0 +
                                   (ui32TimerNumber * TIMER_OFFSET));

    pui32CompareRegB = (uint32_t *)(&CTIMERn(0)->CMPRB0 +
                                   (ui32TimerNumber * TIMER_OFFSET));
#else // AM_CMSIS_REGS
    //
    // Find the correct control register to pull the function select field
    // from.
    //
    pui32ControlReg = (uint32_t *)(AM_REG_CTIMERn(0) + AM_REG_CTIMER_CTRL0_O +
                                   (ui32TimerNumber * TIMER_OFFSET));

    //
    // Find the correct compare registers to write.
    //
    pui32CompareRegA = (uint32_t *)(AM_REG_CTIMERn(0) +
                                    AM_REG_CTIMER_CMPRA0_O +
                                    (ui32TimerNumber * TIMER_OFFSET));

    pui32CompareRegB = (uint32_t *)(AM_REG_CTIMERn(0) +
                                    AM_REG_CTIMER_CMPRB0_O +
                                    (ui32TimerNumber * TIMER_OFFSET));
#endif // AM_CMSIS_REGS

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Extract the timer mode from the register based on the ui32TimerSegment
    // selected by the user.
    //
    ui32Mode = *pui32ControlReg;
    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        ui32Mode = ui32Mode >> 16;
    }

    //
    // Mask to get to the bits we're interested in.
    //
#if AM_CMSIS_REGS
    ui32Mode = ui32Mode & CTIMER_CTRL0_TMRA0FN_Msk;
#else // AM_CMSIS_REGS
    ui32Mode = ui32Mode & AM_REG_CTIMER_CTRL0_TMRA0FN_M;
#endif // AM_CMSIS_REGS

    //
    // If the mode is a PWM mode, we'll need to calculate the correct CMPR0 and
    // CMPR1 values here.
    //
    if (ui32Mode == AM_HAL_CTIMER_FN_PWM_ONCE   ||
        ui32Mode == AM_HAL_CTIMER_FN_PWM_REPEAT)
    {
        ui32Comp0 = ui32Period - ui32OnTime;
        ui32Comp1 = ui32Period;
    }
    else
    {
        ui32Comp0 = ui32Period;
        ui32Comp1 = 0;
    }

    //
    // Based on the timer segment argument, write the calculated Compare 0 and
    // Compare 1 values to the correct halves of the correct registers.
    //
#if AM_CMSIS_REGS
    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERA )
    {
        //
        // For timer A, write the values to the TIMERA compare register.
        //
        *pui32CompareRegA = (_VAL2FLD(CTIMER_CMPRA0_CMPR0A0, ui32Comp0) |
                             _VAL2FLD(CTIMER_CMPRA0_CMPR1A0, ui32Comp1));
    }
    else if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        //
        // For timer B, write the values to the TIMERA compare register.
        //
        *pui32CompareRegB = (_VAL2FLD(CTIMER_CMPRA0_CMPR0A0, ui32Comp0) |
                             _VAL2FLD(CTIMER_CMPRA0_CMPR1A0, ui32Comp1));
    }
    else
    {
        //
        // For the linked case, write the lower halves of the values to the
        // TIMERA compare register, and the upper halves to the TIMERB compare
        // register.
        //
        *pui32CompareRegA = (_VAL2FLD(CTIMER_CMPRA0_CMPR0A0, ui32Comp0) |
                             _VAL2FLD(CTIMER_CMPRA0_CMPR1A0, ui32Comp1));

        *pui32CompareRegB = (_VAL2FLD(CTIMER_CMPRA0_CMPR0A0, ui32Comp0 >> 16) |
                             _VAL2FLD(CTIMER_CMPRA0_CMPR1A0, ui32Comp1 >> 16));
    }
#else // AM_CMSIS_REGS
    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERA )
    {
        //
        // For timer A, write the values to the TIMERA compare register.
        //
        *pui32CompareRegA = (AM_REG_CTIMER_CMPRA0_CMPR0A0(ui32Comp0) |
                             AM_REG_CTIMER_CMPRA0_CMPR1A0(ui32Comp1));
    }
    else if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        //
        // For timer B, write the values to the TIMERA compare register.
        //
        *pui32CompareRegB = (AM_REG_CTIMER_CMPRA0_CMPR0A0(ui32Comp0) |
                             AM_REG_CTIMER_CMPRA0_CMPR1A0(ui32Comp1));
    }
    else
    {
        //
        // For the linked case, write the lower halves of the values to the
        // TIMERA compare register, and the upper halves to the TIMERB compare
        // register.
        //
        *pui32CompareRegA = (AM_REG_CTIMER_CMPRA0_CMPR0A0(ui32Comp0) |
                             AM_REG_CTIMER_CMPRA0_CMPR1A0(ui32Comp1));

        *pui32CompareRegB = (AM_REG_CTIMER_CMPRA0_CMPR0A0(ui32Comp0 >> 16) |
                             AM_REG_CTIMER_CMPRA0_CMPR1A0(ui32Comp1 >> 16));
    }
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_period_set()

//*****************************************************************************
//
//! @brief Set the period and duty cycle of a timer.
//!
//! @param ui32TimerNumber is the number of the timer to configure.
//!
//! @param ui32TimerSegment specifies which segment of the timer to use.
//!
//! @param ui32Period specifies the desired period.  This parameter effectively
//! specifies the CTIMER CMPR field(s). The CMPR fields are handled in hardware
//! as (n+1) values, therefore ui32Period is actually specified as 1 less than
//! the desired period. Finally, as mentioned in the data sheet, the CMPR fields
//! cannot be 0 (a value of 1), so neither can ui32Period be 0.
//!
//! @param ui32OnTime set the number of clocks where the output signal is high.
//!
//! This function should be used for simple manipulations of the period and
//! duty cycle of a counter/timer. To set the period and/or duty cycle of a
//! linked timer pair, use AM_HAL_CTIMER_BOTH as the timer segment argument. If
//! you would like to set the period and/or duty cycle for both TIMERA and
//! TIMERB you will need to call this function twice: once for TIMERA, and once
//! for TIMERB.
//!
//! Valid values for ui32TimerSegment are:
//!
//!     AM_HAL_CTIMER_TIMERA
//!     AM_HAL_CTIMER_TIMERB
//!     AM_HAL_CTIMER_BOTH
//!
//! @note The ui32OnTime parameter will only work if the timer is currently
//! operating in one of the PWM modes.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_aux_period_set(uint32_t ui32TimerNumber, uint32_t ui32TimerSegment,
                             uint32_t ui32Period, uint32_t ui32OnTime)
{
    volatile uint32_t *pui32ControlReg;
    volatile uint32_t *pui32CompareRegA;
    volatile uint32_t *pui32CompareRegB;
    uint32_t ui32Mode, ui32Comp0, ui32Comp1;

#if AM_CMSIS_REGS
    //
    // Find the correct control register to pull the function select field
    // from.
    //
    pui32ControlReg = (uint32_t *)(&CTIMERn(0)->CTRL0 +
                                  (ui32TimerNumber * TIMER_OFFSET));

    //
    // Find the correct compare registers to write.
    //
    pui32CompareRegA = (uint32_t *)(&CTIMERn(0)->CMPRAUXA0 +
                                   (ui32TimerNumber * TIMER_OFFSET));

    pui32CompareRegB = (uint32_t *)(&CTIMERn(0)->CMPRAUXB0 +
                                   (ui32TimerNumber * TIMER_OFFSET));
#else // AM_CMSIS_REGS
    //
    // Find the correct control register to pull the function select field
    // from.
    //
    pui32ControlReg = (uint32_t *)(AM_REG_CTIMERn(0) + AM_REG_CTIMER_CTRL0_O +
                                   (ui32TimerNumber * TIMER_OFFSET));

    //
    // Find the correct compare registers to write.
    //
    pui32CompareRegA = (uint32_t *)(AM_REG_CTIMERn(0) +
                                    AM_REG_CTIMER_CMPRAUXA0_O +
                                    (ui32TimerNumber * TIMER_OFFSET));

    pui32CompareRegB = (uint32_t *)(AM_REG_CTIMERn(0) +
                                    AM_REG_CTIMER_CMPRAUXB0_O +
                                    (ui32TimerNumber * TIMER_OFFSET));
#endif // AM_CMSIS_REGS

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Extract the timer mode from the register based on the ui32TimerSegment
    // selected by the user.
    //
    ui32Mode = *pui32ControlReg;
    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        ui32Mode = ui32Mode >> 16;
    }

    //
    // Mask to get to the bits we're interested in.
    //
#if AM_CMSIS_REGS
    ui32Mode = ui32Mode & CTIMER_CTRL0_TMRA0FN_Msk;
#else // AM_CMSIS_REGS
    ui32Mode = ui32Mode & AM_REG_CTIMER_CTRL0_TMRA0FN_M;
#endif // AM_CMSIS_REGS

    //
    // If the mode is a PWM mode, we'll need to calculate the correct CMPR0 and
    // CMPR1 values here.
    //
    if (ui32Mode == AM_HAL_CTIMER_FN_PWM_ONCE   ||
        ui32Mode == AM_HAL_CTIMER_FN_PWM_REPEAT)
    {
        ui32Comp0 = ui32Period - ui32OnTime;
        ui32Comp1 = ui32Period;
    }
    else
    {
        ui32Comp0 = ui32Period;
        ui32Comp1 = 0;
    }

    //
    // Based on the timer segment argument, write the calculated Compare 0 and
    // Compare 1 values to the correct halves of the correct registers.
    //
#if AM_CMSIS_REGS
    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERA )
    {
        //
        // For timer A, write the values to the TIMERA compare register.
        //
        *pui32CompareRegA = (_VAL2FLD(CTIMER_CMPRAUXA0_CMPR2A0, ui32Comp0) |
                             _VAL2FLD(CTIMER_CMPRAUXA0_CMPR3A0, ui32Comp1));
    }
    else if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        //
        // For timer B, write the values to the TIMERA compare register.
        //
        *pui32CompareRegB = (_VAL2FLD(CTIMER_CMPRAUXA0_CMPR2A0, ui32Comp0) |
                             _VAL2FLD(CTIMER_CMPRAUXA0_CMPR3A0, ui32Comp1));
    }
    else
    {
        //
        // For the linked case, write the lower halves of the values to the
        // TIMERA compare register, and the upper halves to the TIMERB compare
        // register.
        //
        *pui32CompareRegA = (_VAL2FLD(CTIMER_CMPRAUXA0_CMPR2A0, ui32Comp0) |
                             _VAL2FLD(CTIMER_CMPRAUXA0_CMPR3A0, ui32Comp1));

        *pui32CompareRegB = (_VAL2FLD(CTIMER_CMPRAUXA0_CMPR2A0, ui32Comp0 >> 16) |
                             _VAL2FLD(CTIMER_CMPRAUXA0_CMPR3A0, ui32Comp1 >> 16));
    }
#else // AM_CMSIS_REGS
    if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERA )
    {
        //
        // For timer A, write the values to the TIMERA compare register.
        //
        *pui32CompareRegA = (AM_REG_CTIMER_CMPRAUXA0_CMPR2A0(ui32Comp0) |
                             AM_REG_CTIMER_CMPRAUXA0_CMPR3A0(ui32Comp1));
    }
    else if ( ui32TimerSegment == AM_HAL_CTIMER_TIMERB )
    {
        //
        // For timer B, write the values to the TIMERA compare register.
        //
        *pui32CompareRegB = (AM_REG_CTIMER_CMPRAUXA0_CMPR2A0(ui32Comp0) |
                             AM_REG_CTIMER_CMPRAUXA0_CMPR3A0(ui32Comp1));
    }
    else
    {
        //
        // For the linked case, write the lower halves of the values to the
        // TIMERA compare register, and the upper halves to the TIMERB compare
        // register.
        //
        *pui32CompareRegA = (AM_REG_CTIMER_CMPRAUXA0_CMPR2A0(ui32Comp0) |
                             AM_REG_CTIMER_CMPRAUXA0_CMPR3A0(ui32Comp1));

        *pui32CompareRegB = (AM_REG_CTIMER_CMPRAUXA0_CMPR2A0(ui32Comp0 >> 16) |
                             AM_REG_CTIMER_CMPRAUXA0_CMPR3A0(ui32Comp1 >> 16));
    }
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_aux_period_set()

//*****************************************************************************
//
//! @brief Enable the TIMERA3 ADC trigger
//!
//! This function enables the ADC trigger within TIMERA3.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_adc_trigger_enable(void)
{
    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Enable the ADC trigger.
    //
#if AM_CMSIS_REGS
    CTIMERn(0)->CTRL3 |= CTIMER_CTRL3_ADCEN_Msk;
#else // AM_CMSIS_REGS
    AM_REGn(CTIMER, 0, CTRL3) |= AM_REG_CTIMER_CTRL3_ADCEN_M;
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_adc_trigger_enable()

//*****************************************************************************
//
//! @brief Disable the TIMERA3 ADC trigger
//!
//! This function disables the ADC trigger within TIMERA3.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_adc_trigger_disable(void)
{
    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Disable the ADC trigger.
    //
#if AM_CMSIS_REGS
    CTIMERn(0)->CTRL3 &= ~CTIMER_CTRL3_ADCEN_Msk;
#else // AM_CMSIS_REGS
    AM_REGn(CTIMER, 0, CTRL3) &= ~AM_REG_CTIMER_CTRL3_ADCEN_M;
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_adc_trigger_disable()

//*****************************************************************************
//
//! @brief Enables the selected timer interrupt.
//!
//! @param ui32Interrupt is the interrupt to be used.
//!
//! This function will enable the selected interrupts in the main CTIMER
//! interrupt enable register. In order to receive an interrupt from a timer,
//! you will need to enable the interrupt for that timer in this main register,
//! as well as in the timer control register (accessible though
//! am_hal_ctimer_config()), and in the NVIC.
//!
//! ui32Interrupt should be the logical OR of one or more of the following
//! values:
//!
//!     AM_HAL_CTIMER_INT_TIMERAxCx, AM_HAL_CTIMER_INT_TIMERAxCx,
//!
//! @note The AM_HAL_CTIMER_INT_TIMER defines were re-definitions of
//!       AM_REG_CTIMER_INTEN_CTMRAxCxINT_M register defines. They are
//!       dropped in this release to go back to a single source definition.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_int_enable(uint32_t ui32Interrupt)
{
    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Enable the interrupt at the module level.
    //
#if AM_CMSIS_REGS
    CTIMERn(0)->INTEN |= ui32Interrupt;
#else // AM_CMSIS_REGS
    AM_REGn(CTIMER, 0, INTEN) |= ui32Interrupt;
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_int_enable()

//*****************************************************************************
//
//! @brief Return the enabled timer interrupts.
//!
//! This function will return all enabled interrupts in the main CTIMER
//! interrupt enable register.
//!
//! @return return enabled interrupts. This will be a logical or of:
//!
//!     AM_REG_CTIMER_INTEN_CTMRAxC0INT_M, AM_HAL_CTIMER_INT_TIMERAxC1,
//!
//! @return Return the enabled timer interrupts.
//
//*****************************************************************************
uint32_t
am_hal_ctimer_int_enable_get(void)
{
    //
    // Return enabled interrupts.
    //
#if AM_CMSIS_REGS
    return CTIMERn(0)->INTEN;
#else // AM_CMSIS_REGS
    return AM_REGn(CTIMER, 0, INTEN);
#endif // AM_CMSIS_REGS

} // am_hal_ctimer_int_enable_get()

//*****************************************************************************
//
//! @brief Disables the selected timer interrupt.
//!
//! @param ui32Interrupt is the interrupt to be used.
//!
//! This function will disable the selected interrupts in the main CTIMER
//! interrupt register.
//!
//! ui32Interrupt should be the logical OR of one or more of the following
//! values:
//!
//!     AM_REG_CTIMER_INTEN_CTMRAxC0INT_M, AM_HAL_CTIMER_INT_TIMERAxC1,
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_int_disable(uint32_t ui32Interrupt)
{
    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Disable the interrupt at the module level.
    //
#if AM_CMSIS_REGS
    CTIMERn(0)->INTEN &= ~ui32Interrupt;
#else // AM_CMSIS_REGS
    AM_REGn(CTIMER, 0, INTEN) &= ~ui32Interrupt;
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_int_disable()

//*****************************************************************************
//
//! @brief Clears the selected timer interrupt.
//!
//! @param ui32Interrupt is the interrupt to be used.
//!
//! This function will clear the selected interrupts in the main CTIMER
//! interrupt register.
//!
//! ui32Interrupt should be the logical OR of one or more of the following
//! values:
//!
//!     AM_REG_CTIMER_INTEN_CTMRAxC0INT_M, AM_HAL_CTIMER_INT_TIMERAxC1,
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_int_clear(uint32_t ui32Interrupt)
{
    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Disable the interrupt at the module level.
    //
#if AM_CMSIS_REGS
    CTIMERn(0)->INTCLR = ui32Interrupt;
#else // AM_CMSIS_REGS
    AM_REGn(CTIMER, 0, INTCLR) = ui32Interrupt;
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_int_clear()

//*****************************************************************************
//
//! @brief Sets the selected timer interrupt.
//!
//! @param ui32Interrupt is the interrupt to be used.
//!
//! This function will set the selected interrupts in the main CTIMER
//! interrupt register.
//!
//! ui32Interrupt should be the logical OR of one or more of the following
//! values:
//!
//!     AM_REG_CTIMER_INTEN_CTMRAxC0INT_M, AM_HAL_CTIMER_INT_TIMERAxC1,
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ctimer_int_set(uint32_t ui32Interrupt)
{
    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Set the interrupts.
    //
#if AM_CMSIS_REGS
    CTIMERn(0)->INTSET = ui32Interrupt;
#else // AM_CMSIS_REGS
    AM_REGn(CTIMER, 0, INTSET) = ui32Interrupt;
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

} // am_hal_ctimer_int_set()

//*****************************************************************************
//
//! @brief Returns either the enabled or raw timer interrupt status.
//!
//! This function will return the timer interrupt status.
//!
//! @param bEnabledOnly if true returns the status of the enabled interrupts
//! only.
//!
//! The return value will be the logical OR of one or more of the following
//! values:
//!
//!     AM_REG_CTIMER_INTEN_CTMRAxC0INT_M, AM_HAL_CTIMER_INT_TIMERAxC1,
//!
//! @return u32RetVal either the timer interrupt status, or interrupt enabled.
//
//*****************************************************************************
uint32_t
am_hal_ctimer_int_status_get(bool bEnabledOnly)
{
    uint32_t u32RetVal = 0;

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN

    //
    // Return the desired status.
    //

#if AM_CMSIS_REGS
    if ( bEnabledOnly )
    {
        u32RetVal  = CTIMERn(0)->INTSTAT;
        u32RetVal &= CTIMERn(0)->INTEN;
    }
    else
    {
        u32RetVal = CTIMERn(0)->INTSTAT;
    }
#else // AM_CMSIS_REGS
    if ( bEnabledOnly )
    {

        u32RetVal  = AM_REGn(CTIMER, 0, INTSTAT);
        u32RetVal &= AM_REGn(CTIMER, 0, INTEN);

    }
    else
    {
        u32RetVal = AM_REGn(CTIMER, 0, INTSTAT);
    }
#endif // AM_CMSIS_REGS

    //
    // Done with critical section.
    //
    AM_CRITICAL_END

    return u32RetVal;

} // am_hal_ctimer_int_status_get()

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
