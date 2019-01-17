//*****************************************************************************
//
//  am_hal_systick.c
//! @file
//!
//! @brief Functions for interfacing with the SYSTICK
//!
//! @addtogroup systick2 System Timer (SYSTICK)
//! @ingroup apollo2hal
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
// Macro definitions
//
//*****************************************************************************
#define SYSTICK_MAX_TICKS   ((1 << 24)-1)
#define MAX_U32             (0xffffffff)

//*****************************************************************************
//
//! @brief Start the SYSTICK.
//!
//! This function starts the systick timer.
//!
//! @note This timer does not run in deep-sleep mode as it runs from the core
//! clock, which is gated in deep-sleep. If a timer is needed in deep-sleep use
//! one of the ctimers instead. Also to note is this timer will consume higher
//! power than the ctimers.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_systick_start(void)
{
    //
    // Start the systick timer.
    //
#if AM_CMSIS_REGS
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
#else // AM_CMSIS_REGS
    AM_REG(SYSTICK, SYSTCSR) |= AM_REG_SYSTICK_SYSTCSR_ENABLE_M;
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Stop the SYSTICK.
//!
//! This function stops the systick timer.
//!
//! @note This timer does not run in deep-sleep mode as it runs from the core
//! clock, which is gated in deep-sleep. If a timer is needed in deep-sleep use
//! one of the ctimers instead. Also to note is this timer will consume higher
//! power than the ctimers.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_systick_stop(void)
{
    //
    // Stop the systick timer.
    //
#if AM_CMSIS_REGS
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
#else // AM_CMSIS_REGS
    AM_REG(SYSTICK, SYSTCSR) &= ~AM_REG_SYSTICK_SYSTCSR_ENABLE_M;
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Enable the interrupt in the SYSTICK.
//!
//! This function enables the interupt in the systick timer.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_systick_int_enable(void)
{
    //
    // Enable the systick timer interrupt.
    //
#if AM_CMSIS_REGS
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
#else // AM_CMSIS_REGS
    AM_REG(SYSTICK, SYSTCSR) |= AM_REG_SYSTICK_SYSTCSR_TICKINT_M;
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Disable the interrupt in the SYSTICK.
//!
//! This function disables the interupt in the systick timer.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_systick_int_disable(void)
{
    //
    // Disable the systick timer interrupt.
    //
#if AM_CMSIS_REGS
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
#else // AM_CMSIS_REGS
    AM_REG(SYSTICK, SYSTCSR) &= ~AM_REG_SYSTICK_SYSTCSR_TICKINT_M;
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Reads the interrupt status.
//!
//! This function reads the interrupt status in the systick timer.
//!
//! @return the interrupt status.
//
//*****************************************************************************
uint32_t
am_hal_systick_int_status_get(void)
{
    //
    // Return the systick timer interrupt status.
    //
#if AM_CMSIS_REGS
    return SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk;
#else // AM_CMSIS_REGS
    return AM_REG(SYSTICK, SYSTCSR) & AM_REG_SYSTICK_SYSTCSR_COUNTFLAG_M;
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Reset the interrupt in the SYSTICK.
//!
//! This function resets the systick timer by clearing out the configuration
//! register.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_systick_reset(void)
{
    //
    // Reset the systick timer interrupt.
    //
#if AM_CMSIS_REGS
    SysTick->CTRL = 0x0;
#else // AM_CMSIS_REGS
    AM_REG(SYSTICK, SYSTCSR) = 0x0;
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Load the value into the SYSTICK.
//!
//! @param ui32LoadVal the desired load value for the systick. Maximum value is
//! 0x00FF.FFFF.
//!
//! This function loads the desired value into the systick timer.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_systick_load(uint32_t ui32LoadVal)
{
    //
    //  The proper SysTick initialization sequence is: (p 4-36 of the M4 UG).
    //      1. Program reload value
    //      2. Clear current value
    //      3. Program CSR
    // Write the given value to the reload register.
    // Write the Current Value Register to clear it to 0.
    //
#if AM_CMSIS_REGS
    SysTick->LOAD = ui32LoadVal;
    SysTick->VAL = 0;
#else // AM_CMSIS_REGS
    AM_REG(SYSTICK, SYSTRVR) = ui32LoadVal;
    AM_REG(SYSTICK, SYSTCVR) = 0;
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Get the current count value in the SYSTICK.
//!
//! This function gets the current count value in the systick timer.
//!
//! @return Current count value.
//
//*****************************************************************************
uint32_t
am_hal_systick_count(void)
{
    //
    // Return the current systick timer count value.
    //
#if AM_CMSIS_REGS
    return SysTick->VAL;
#else // AM_CMSIS_REGS
    return AM_REG(SYSTICK, SYSTCVR);
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Wait the specified number of ticks.
//!
//! This function delays for the given number of SysTick ticks.
//!
//! @note If the SysTick timer is being used elsewhere, it will be corrupted
//! by calling this function.
//!
//! @return 0 if successful.
//
//*****************************************************************************
uint32_t
am_hal_systick_wait_ticks(uint32_t ui32Ticks)
{

    if ( ui32Ticks == 0 )
    {
        ui32Ticks++;                // Make sure we get the COUNTFLAG
    }

    //
    //  The proper SysTick initialization sequence is: (p 4-36 of the M4 UG).
    //      1. Program reload value
    //      2. Clear current value
    //      3. Program CSR
    //
    // Set the reload value to the required number of ticks.
    //
#if AM_CMSIS_REGS
    SysTick->LOAD = ui32Ticks;

    //
    // Clear the current count.
    //
    SysTick->VAL = 0x0;

    //
    // Set to use the processor clock, but don't cause an exception (we'll poll).
    //
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;

    //
    // Poll till done
    //
    while ( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) );

    //
    // And disable systick before exiting.
    //
    SysTick->CTRL = 0x0;
#else // AM_CMSIS_REGS
    AM_REG(SYSTICK, SYSTRVR) = ui32Ticks;

    //
    // Clear the current count.
    //
    AM_REG(SYSTICK, SYSTCVR) = 0x0;

    //
    // Set to use the processor clock, but don't cause an exception (we'll poll).
    //
    AM_REG(SYSTICK, SYSTCSR) = AM_REG_SYSTICK_SYSTCSR_ENABLE_M;

    //
    // Poll till done
    //
    while ( !(AM_REG(SYSTICK, SYSTCSR) & AM_REG_SYSTICK_SYSTCSR_COUNTFLAG_M) );

    //
    // And disable systick before exiting.
    //
    AM_REG(SYSTICK, SYSTCSR) = 0;
#endif // AM_CMSIS_REGS

    return 0;
}

//*****************************************************************************
//
//! @brief Delay the specified number of microseconds.
//!
//! This function will use the SysTick timer to delay until the specified
//!  number of microseconds have elapsed.  It uses the processor clocks and
//!  takes into account the current CORESEL setting.
//!
//! @note If the SysTick timer is being used elsewhere, it will be corrupted
//! by calling this function.
//!
//! @return Total number of SysTick ticks delayed.
//
//*****************************************************************************
uint32_t
am_hal_systick_delay_us(uint32_t u32NumUs)
{
    uint32_t u32ClkFreq, u32nLoops, ui32Ticks, uRet;
#if AM_CMSIS_REGS
    uint32_t u32CoreSel = CLKGEN->CCTRL_b.CORESEL;
#else // AM_CMSIS_REGS
    uint32_t u32CoreSel = AM_BFR(CLKGEN, CCTRL, CORESEL);
#endif // AM_CMSIS_REGS

    u32nLoops = 1;
    switch (u32CoreSel)
    {
        //
        // We need to compute the required number of ticks.  To do so and to
        //   minimize divide operations, we'll use the following equation:
        // ui32Ticks = (u32NumUs * HFCR_EXACT)/1000000
        //           = (u32NumUs * (HFCR_EXACT * 1024)/1000000) / 1024
        // The values for the variable u32ClkFreq are computed as follows:
        //  u32ClkFreq = (24390200 * 1024) / ((clksel+1)*1000000);
        //  (and we'll do the remaining divide by 1024, using a shift, later).
        //
        case 0:
            u32ClkFreq = 24975;
            if ( u32NumUs > ((SYSTICK_MAX_TICKS / 24975)*1024) )
            {
                u32nLoops = (u32NumUs / ((SYSTICK_MAX_TICKS / 24975)*1024)) + 1;
                u32NumUs /= u32nLoops;
            }
            if ( u32NumUs > (MAX_U32 / 24975) )
            {
                ui32Ticks = (u32NumUs >> 10) * u32ClkFreq;
            }
            else
            {
                ui32Ticks = (u32NumUs * u32ClkFreq) >> 10;
            }
            break;
        case 1:
            u32ClkFreq = 12487;
            if ( u32NumUs > ((SYSTICK_MAX_TICKS / 12487)*1024) )
            {
                u32nLoops = (u32NumUs / ((SYSTICK_MAX_TICKS / 12487)*1024)) + 1;
                u32NumUs /= u32nLoops;
            }
            if ( u32NumUs > (MAX_U32 / 12487) )
            {
                ui32Ticks = (u32NumUs >> 10) * u32ClkFreq;
            }
            else
            {
                ui32Ticks = (u32NumUs * u32ClkFreq) >> 10;
            }
            break;
        case 2:
            u32ClkFreq = 8325;
            if ( u32NumUs > ((SYSTICK_MAX_TICKS / 8325)*1024) )
            {
                u32nLoops = (u32NumUs / ((SYSTICK_MAX_TICKS / 8325)*1024)) + 1;
                u32NumUs /= u32nLoops;
            }
            if ( u32NumUs > (MAX_U32 / 8325) )
            {
                ui32Ticks = (u32NumUs >> 10) * u32ClkFreq;
            }
            else
            {
                ui32Ticks = (u32NumUs * u32ClkFreq) >> 10;
            }
            break;
        case 3:
            u32ClkFreq = 6243;
            if ( u32NumUs > ((SYSTICK_MAX_TICKS / 6243)*1024) )
            {
                u32nLoops = (u32NumUs / ((SYSTICK_MAX_TICKS / 6243)*1024)) + 1;
                u32NumUs /= u32nLoops;
            }
            if ( u32NumUs > (MAX_U32 / 6243) )
            {
                ui32Ticks = (u32NumUs >> 10) * u32ClkFreq;
            }
            else
            {
                ui32Ticks = (u32NumUs * u32ClkFreq) >> 10;
            }
            break;
        case 4:
            u32ClkFreq = 4995;
            if ( u32NumUs > ((SYSTICK_MAX_TICKS / 4995)*1024) )
            {
                u32nLoops = (u32NumUs / ((SYSTICK_MAX_TICKS / 4995)*1024)) + 1;
                u32NumUs /= u32nLoops;
            }
            if ( u32NumUs > (MAX_U32 / 4995) )
            {
                ui32Ticks = (u32NumUs >> 10) * u32ClkFreq;
            }
            else
            {
                ui32Ticks = (u32NumUs * u32ClkFreq) >> 10;
            }
            break;
        case 5:
            u32ClkFreq = 4162;
            if ( u32NumUs > ((SYSTICK_MAX_TICKS / 4162)*1024) )
            {
                u32nLoops = (u32NumUs / ((SYSTICK_MAX_TICKS / 4162)*1024)) + 1;
                u32NumUs /= u32nLoops;
            }
            if ( u32NumUs > (MAX_U32 / 4162) )
            {
                ui32Ticks = (u32NumUs >> 10) * u32ClkFreq;
            }
            else
            {
                ui32Ticks = (u32NumUs * u32ClkFreq) >> 10;
            }
            break;
        case 6:
            u32ClkFreq = 3567;
            if ( u32NumUs > ((SYSTICK_MAX_TICKS / 3567)*1024) )
            {
                u32nLoops = (u32NumUs / ((SYSTICK_MAX_TICKS / 3567)*1024)) + 1;
                u32NumUs /= u32nLoops;
            }
            if ( u32NumUs > (MAX_U32 / 3567) )
            {
                ui32Ticks = (u32NumUs >> 10) * u32ClkFreq;
            }
            else
            {
                ui32Ticks = (u32NumUs * u32ClkFreq) >> 10;
            }
            break;
        case 7:
            u32ClkFreq = 3121;
            if ( u32NumUs > ((SYSTICK_MAX_TICKS / 3121)*1024) )
            {
                u32nLoops = (u32NumUs / ((SYSTICK_MAX_TICKS / 3121)*1024)) + 1;
                u32NumUs /= u32nLoops;
            }
            if ( u32NumUs > (MAX_U32 / 3121) )
            {
                ui32Ticks = (u32NumUs >> 10) * u32ClkFreq;
            }
            else
            {
                ui32Ticks = (u32NumUs * u32ClkFreq) >> 10;
            }
            break;
        default:
            ui32Ticks = 1;
            break;
    } // switch()

    uRet = ui32Ticks * u32nLoops;
    while ( u32nLoops-- )
    {
        am_hal_systick_wait_ticks(ui32Ticks);
    }

    return uRet;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
