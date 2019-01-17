//*****************************************************************************
//
//  am_hal_sysctrl.c
//! @file
//!
//! @brief Functions for interfacing with the M4F system control registers
//!
//! @addtogroup sysctrl3 System Control (SYSCTRL)
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
//! @brief Place the core into sleep or deepsleep.
//!
//! @param bSleepDeep - False for Normal or True Deep sleep.
//!
//! This function puts the MCU to sleep or deepsleep depending on bSleepDeep.
//!
//! Valid values for bSleepDeep are:
//!
//!     AM_HAL_SYSCTRL_SLEEP_NORMAL
//!     AM_HAL_SYSCTRL_SLEEP_DEEP
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_sleep(bool bSleepDeep)
{
    //
    // Disable interrupts and save the previous interrupt state.
    //
    AM_CRITICAL_BEGIN

#if AM_CMSIS_REGS
    //
    // If the user selected DEEPSLEEP and the TPIU is off, attempt to enter
    // DEEP SLEEP.
    //
    if ( (bSleepDeep == AM_HAL_SYSCTRL_SLEEP_DEEP)    &&
         (MCUCTRL->TPIUCTRL_b.ENABLE == MCUCTRL_TPIUCTRL_ENABLE_DIS) )
    {
        //
        // Prepare the core for deepsleep (write 1 to the DEEPSLEEP bit).
        //
        SCB->SCR = _VAL2FLD(SCB_SCR_SLEEPDEEP, 1);

        //
        // Execute the sleep instruction.
        //
        __WFI();
    }
    else
    {
        //
        // Prepare the core for normal sleep (write 0 to the DEEPSLEEP bit).
        //
        SCB->SCR &= ~_VAL2FLD(SCB_SCR_SLEEPDEEP, 1);

        //
        // Go to sleep.
        //
        __WFI();
    }
#else // AM_CMSIS_REGS
    //
    // If the user selected DEEPSLEEP and the TPIU is off, attempt to enter
    // DEEP SLEEP.
    //
    if ((bSleepDeep == AM_HAL_SYSCTRL_SLEEP_DEEP) &&
        (AM_BFM(MCUCTRL, TPIUCTRL, ENABLE) == AM_REG_MCUCTRL_TPIUCTRL_ENABLE_DIS))
    {
        //
        // Prepare the core for deepsleep (write 1 to the DEEPSLEEP bit).
        //
        AM_BFW(SYSCTRL, SCR, SLEEPDEEP, 1);

        //
        // Execute the sleep instruction.
        //
        AM_ASM_WFI
    }
    else
    {
        //
        // Prepare the core for normal sleep (write 0 to the DEEPSLEEP bit).
        //
        AM_BFW(SYSCTRL, SCR, SLEEPDEEP, 0);

        //
        // Go to sleep.
        //
        AM_ASM_WFI
    }
#endif // AM_CMSIS_REGS

    //
    // Restore the interrupt state.
    //
    AM_CRITICAL_END
}

//*****************************************************************************
//
//! @brief Enable the floating point module.
//!
//! Call this function to enable the ARM hardware floating point module.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_fpu_enable(void)
{
    //
    // Enable access to the FPU in both privileged and user modes.
    // NOTE: Write 0s to all reserved fields in this register.
    //
#if AM_CMSIS_REGS
    SCB->CPACR = _VAL2FLD(SCB_CPACR_CP11, 0x3) |
                 _VAL2FLD(SCB_CPACR_CP10, 0x3);
#else // AM_CMSIS_REGS
    AM_REG(SYSCTRL, CPACR) = (AM_REG_SYSCTRL_CPACR_CP11(0x3) |
                             AM_REG_SYSCTRL_CPACR_CP10(0x3));
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Disable the floating point module.
//!
//! Call this function to disable the ARM hardware floating point module.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_fpu_disable(void)
{
    //
    // Disable access to the FPU in both privileged and user modes.
    // NOTE: Write 0s to all reserved fields in this register.
    //
#if AM_CMSIS_REGS
    SCB->CPACR = 0x00000000                         &
                 ~(_VAL2FLD(SCB_CPACR_CP11, 0x3) |
                   _VAL2FLD(SCB_CPACR_CP10, 0x3));
#else // AM_CMSIS_REGS
    AM_REG(SYSCTRL, CPACR) = 0x00000000                     &
                          ~(AM_REG_SYSCTRL_CPACR_CP11(0x3) |
                            AM_REG_SYSCTRL_CPACR_CP10(0x3));
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Enable stacking of FPU registers on exception entry.
//!
//! @param bLazy - Set to "true" to enable "lazy stacking".
//!
//! This function allows the core to save floating-point information to the
//! stack on exception entry. Setting the bLazy option enables "lazy stacking"
//! for interrupt handlers.  Normally, mixing floating-point code and interrupt
//! driven routines causes increased interrupt latency, because the core must
//! save extra information to the stack upon exception entry. With the lazy
//! stacking option enabled, the core will skip the saving of floating-point
//! registers when possible, reducing average interrupt latency.
//!
//! @note This function should be called before the floating-point module is
//! used in interrupt-driven code. If it is not called, the core will not have
//! any way to save context information for floating-point variables on
//! exception entry.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_fpu_stacking_enable(bool bLazy)
{
#if AM_CMSIS_REGS
    if ( bLazy )
    {
        //
        // Enable automatic saving of FPU registers on exception entry, using lazy
        // context saving.
        //
        FPU->FPCCR |= _VAL2FLD(FPU_FPCCR_ASPEN, 1) |
                      _VAL2FLD(FPU_FPCCR_LSPEN, 1);
    }
    else
    {
        //
        // Enable automatic saving of FPU registers on exception entry.
        //
        FPU->FPCCR |= _VAL2FLD(FPU_FPCCR_ASPEN, 1);
    }
#else // AM_CMSIS_REGS
    if ( bLazy )
    {
        //
        // Enable automatic saving of FPU registers on exception entry, using lazy
        // context saving.
        //
        AM_REG(SYSCTRL, FPCCR) |= (AM_REG_SYSCTRL_FPCCR_ASPEN(0x1) |
                                   AM_REG_SYSCTRL_FPCCR_LSPEN(0x1));
    }
    else
    {
        //
        // Enable automatic saving of FPU registers on exception entry.
        //
        AM_REG(SYSCTRL, FPCCR) |= AM_REG_SYSCTRL_FPCCR_ASPEN(0x1);
    }
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Disable FPU register stacking on exception entry.
//!
//! This function disables all stacking of floating point registers for
//! interrupt handlers.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_fpu_stacking_disable(void)
{
    //
    // Enable automatic saving of FPU registers on exception entry, using lazy
    // context saving.
    //
#if AM_CMSIS_REGS
        FPU->FPCCR &= ~(_VAL2FLD(FPU_FPCCR_ASPEN, 1) |
                        _VAL2FLD(FPU_FPCCR_LSPEN, 1));
#else // AM_CMSIS_REGS
    AM_REG(SYSCTRL, FPCCR) &= ~(AM_REG_SYSCTRL_FPCCR_ASPEN(0x1) |
                                AM_REG_SYSCTRL_FPCCR_LSPEN(0x1));
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
//! @brief Issue a system wide reset using the AIRCR bit in the M4 system ctrl.
//!
//! This function issues a system wide reset (Apollo POR level reset).
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_aircr_reset(void)
{
    //
    // Set the system reset bit in the AIRCR register
    //
#if AM_CMSIS_REGS
    __NVIC_SystemReset();
#else // AM_CMSIS_REGS
    AM_REG(SYSCTRL, AIRCR) = AM_REG_SYSCTRL_AIRCR_VECTKEY(0x5FA) |
                             AM_REG_SYSCTRL_AIRCR_SYSRESETREQ(1);
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
