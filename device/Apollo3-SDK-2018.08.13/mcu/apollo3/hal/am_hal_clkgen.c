// ****************************************************************************
//
//  am_hal_clkgen.c
//! @file
//!
//! @brief Functions for interfacing with the CLKGEN.
//!
//! @addtogroup clkgen3 Clock Generator (CLKGEN)
//! @ingroup apollo3hal
//! @{
//
// ****************************************************************************

// ****************************************************************************
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
// ****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"


// ****************************************************************************
//
//  am_hal_clkgen_control()
//      Apply various specific commands/controls on the CLKGEN module.
//
// ****************************************************************************
uint32_t
am_hal_clkgen_control(am_hal_clkgen_control_e eControl, void *pArgs)
{
    uint32_t ui32Regval;

#if AM_CMSIS_REGS
    switch ( eControl )
    {
        case AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX:
            //
            // Unlock the clock control register.
            // Set the HFRC divisor to the required operating value.
            // Lock the clock configuration registers.
            //
            CLKGEN->CLKKEY         = CLKGEN_CLKKEY_CLKKEY_Key;
            CLKGEN->CCTRL          = CLKGEN_CCTRL_CORESEL_HFRC;
            CLKGEN->CLKKEY         = 0;
            break;

        case AM_HAL_CLKGEN_CONTROL_SYSCLK_DIV2:
            CLKGEN->CLKKEY         = CLKGEN_CLKKEY_CLKKEY_Key;
            CLKGEN->CCTRL          = CLKGEN_CCTRL_CORESEL_HFRC_DIV2;
            CLKGEN->CLKKEY         = 0;
            break;

        case AM_HAL_CLKGEN_CONTROL_LFRC_START:
            CLKGEN->OCTRL         &= ~_VAL2FLD(CLKGEN_OCTRL_STOPRC,
                                               CLKGEN_OCTRL_STOPRC_STOP);
            break;

        case AM_HAL_CLKGEN_CONTROL_XTAL_START:
            CLKGEN->OCTRL         &= ~_VAL2FLD(CLKGEN_OCTRL_STOPXT,
                                               CLKGEN_OCTRL_STOPXT_STOP);
            break;

        case AM_HAL_CLKGEN_CONTROL_LFRC_STOP:
            CLKGEN->OCTRL         |= _VAL2FLD(CLKGEN_OCTRL_STOPRC,
                                              CLKGEN_OCTRL_STOPRC_STOP);
            break;

        case AM_HAL_CLKGEN_CONTROL_XTAL_STOP:
            CLKGEN->OCTRL         |= _VAL2FLD(CLKGEN_OCTRL_STOPXT,
                                              CLKGEN_OCTRL_STOPXT_STOP);
            break;

        case AM_HAL_CLKGEN_CONTROL_HFADJ_ENABLE:
            if ( pArgs == 0 )
            {
                ui32Regval =
                    _VAL2FLD(CLKGEN_HFADJ_HFADJGAIN, CLKGEN_HFADJ_HFADJGAIN_Gain_of_1_in_2) |   /* Default value (Apollo3) */
                    _VAL2FLD(CLKGEN_HFADJ_HFWARMUP, CLKGEN_HFADJ_HFWARMUP_1SEC)             |   /* Default value */
                    _VAL2FLD(CLKGEN_HFADJ_HFXTADJ, 0x5B8)                                   |   /* Default value */
                    _VAL2FLD(CLKGEN_HFADJ_HFADJCK, CLKGEN_HFADJ_HFADJCK_4SEC)               |   /* Default value */
                    _VAL2FLD(CLKGEN_HFADJ_HFADJEN, CLKGEN_HFADJ_HFADJEN_EN);
            }
            else
            {
                ui32Regval = *(uint32_t*)pArgs;
            }

            //
            // Make sure the ENABLE bit is set.
            //
            ui32Regval |= _VAL2FLD(CLKGEN_HFADJ_HFADJEN, CLKGEN_HFADJ_HFADJEN_EN);
            CLKGEN->HFADJ = ui32Regval;
            break;

        case AM_HAL_CLKGEN_CONTROL_HFADJ_DISABLE:
            CLKGEN->HFADJ_b.HFADJEN = 0;
            break;

        default:
            return AM_HAL_STATUS_INVALID_ARG;
    }
#else // AM_CMSIS_REGS
    switch ( eControl )
    {
        case AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX:
            //
            // Unlock the clock control register.
            // Set the HFRC divisor to the required operating value.
            // Lock the clock configuration registers.
            //
            AM_REG(CLKGEN, CLKKEY) = AM_REG_CLKGEN_CLKKEY_KEYVAL;
            AM_REG(CLKGEN, CCTRL)  = AM_REG_CLKGEN_CCTRL_CORESEL_HFRC;
            AM_REG(CLKGEN, CLKKEY) = 0;
            break;

        case AM_HAL_CLKGEN_CONTROL_SYSCLK_DIV2:
            AM_REG(CLKGEN, CLKKEY) = AM_REG_CLKGEN_CLKKEY_KEYVAL;
            AM_REG(CLKGEN, CCTRL)  = AM_REG_CLKGEN_CCTRL_CORESEL_HFRC_DIV2;
            AM_REG(CLKGEN, CLKKEY) = 0;
            break;

        case AM_HAL_CLKGEN_CONTROL_LFRC_START:
            AM_BFW(CLKGEN, OCTRL, STOPRC, 0);
            break;

        case AM_HAL_CLKGEN_CONTROL_XTAL_START:
            //
            // IMPORTANT: After starting the XTAL, a 2s (yes, 2 seconds) delay
            // is required. The delay is expected to be handled by the caller.
            //
            AM_BFW(CLKGEN, OCTRL, STOPXT, 0);
            break;

        case AM_HAL_CLKGEN_CONTROL_LFRC_STOP:
            AM_BFW(CLKGEN, OCTRL, STOPRC, 1);
            break;

        case AM_HAL_CLKGEN_CONTROL_XTAL_STOP:
            AM_BFW(CLKGEN, OCTRL, STOPXT, 1);
            break;

        case AM_HAL_CLKGEN_CONTROL_RTC_SEL_LFRC:
            AM_BFW(CLKGEN, OCTRL, OSEL, 1);     // RTC osc: 1=LFRC, 0=XTAL
            break;

        case AM_HAL_CLKGEN_CONTROL_RTC_SEL_XTAL:
            AM_BFW(CLKGEN, OCTRL, OSEL, 0);     // RTC osc: 1=LFRC, 0=XTAL
            break;

        case AM_HAL_CLKGEN_CONTROL_HFADJ_ENABLE:
            if ( pArgs == 0 )
            {
                ui32Regval =
                    AM_REG_CLKGEN_HFADJ_HFADJGAIN_Gain_of_1_in_2    |   /* Default value (Apollo3) */
                    AM_REG_CLKGEN_HFADJ_HFWARMUP_1SEC               |   /* Default value */
                    AM_REG_CLKGEN_HFADJ_HFXTADJ(0x5B8)              |   /* Default value */
                    AM_REG_CLKGEN_HFADJ_HFADJCK_4SEC                |   /* Default value */
                    AM_REG_CLKGEN_HFADJ_HFADJEN_EN;
            }
            else
            {
                ui32Regval = *(uint32_t*)pArgs;
            }

            //
            // Make sure the ENABLE bit is set.
            //
            ui32Regval |= AM_REG_CLKGEN_HFADJ_HFADJEN_EN;
            AM_REG(CLKGEN, HFADJ) = ui32Regval;
            break;

        case AM_HAL_CLKGEN_CONTROL_HFADJ_DISABLE:
            AM_BFW(CLKGEN, HFADJ, HFADJEN, 0);
            break;

        default:
            return AM_HAL_STATUS_INVALID_ARG;
    }
#endif // AM_CMSIS_REGS


    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;
} // am_hal_clkgen_control()

// ****************************************************************************
//
//  am_hal_clkgen_status_get()
//  This function returns the current value of various CLKGEN statuses.
//
// ****************************************************************************
uint32_t
am_hal_clkgen_status_get(am_hal_clkgen_status_t *psStatus)
{
    uint32_t ui32Status;

    if ( psStatus == NULL )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

#if AM_CMSIS_REGS
    psStatus->ui32SysclkFreq =
        CLKGEN->CCTRL_b.CORESEL                     ?
            AM_HAL_CLKGEN_FREQ_MAX_HZ / 2           :
            AM_HAL_CLKGEN_FREQ_MAX_HZ;

    ui32Status = CLKGEN->STATUS;

    psStatus->eRTCOSC =
        _FLD2VAL(CLKGEN_STATUS_OMODE, ui32Status)   ?
            AM_HAL_CLKGEN_STATUS_RTCOSC_LFRC        :
            AM_HAL_CLKGEN_STATUS_RTCOSC_XTAL;

    psStatus->bXtalFailure =
        _FLD2VAL(CLKGEN_STATUS_OSCF, ui32Status);
#else // AM_CMSIS_REGS
    psStatus->ui32SysclkFreq =
        AM_BFR(CLKGEN, CCTRL, CORESEL)              ?
                AM_HAL_CLKGEN_FREQ_MAX_HZ / 2       :
                AM_HAL_CLKGEN_FREQ_MAX_HZ;

    ui32Status = AM_REG(CLKGEN, STATUS);

    psStatus->eRTCOSC =
        AM_BFX(CLKGEN, STATUS, OMODE, ui32Status)   ?
                AM_HAL_CLKGEN_STATUS_RTCOSC_LFRC    :
                AM_HAL_CLKGEN_STATUS_RTCOSC_XTAL;

    psStatus->bXtalFailure =
        AM_BFX(CLKGEN, STATUS, OSCF, ui32Status);
#endif // AM_CMSIS_REGS

    return AM_HAL_STATUS_SUCCESS;

} // am_hal_clkgen_status_get()

// ****************************************************************************
//
//  am_hal_clkgen_clkout_enable()
//  This function is used to select and enable CLKOUT.
//
// ****************************************************************************
uint32_t
am_hal_clkgen_clkout_enable(bool bEnable, am_hal_clkgen_clkout_e eClkSelect)
{
#if AM_CMSIS_REGS
    if ( !bEnable )
    {
        CLKGEN->CLKOUT_b.CKEN = 0;
    }

    //
    // Do a basic validation of the eClkSelect parameter.
    // Not every value in the range is valid, but at least this simple check
    //  provides a reasonable chance that the parameter is valid.
    //
    if ( eClkSelect <= (am_hal_clkgen_clkout_e)CLKGEN_CLKOUT_CKSEL_LFRCNE )
    {
        //
        // Are we actually changing the frequency?
        //
        if ( CLKGEN->CLKOUT_b.CKSEL != eClkSelect )
        {
            //
            // Disable before changing the clock
            //
            CLKGEN->CLKOUT_b.CKEN = 0;

            //
            // Set the new clock select
            //
            CLKGEN->CLKOUT_b.CKSEL = eClkSelect;
        }

        //
        // Enable/disable as requested.
        //
        CLKGEN->CLKOUT_b.CKEN = bEnable;
    }
    else
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }
#else // AM_CMSIS_REGS
    if ( !bEnable )
    {
        AM_BFW(CLKGEN, CLKOUT, CKEN, 0);
    }

    //
    // Do a basic validation of the eClkSelect parameter.
    // Not every value in the range is valid, but at least this simple check
    //  provides a reasonable chance that the parameter is valid.
    //
    if ( eClkSelect <= AM_REG_CLKGEN_CLKOUT_CKSEL_LFRCNE )
    {
        //
        // Are we actually changing the frequency?
        //
        if ( AM_BFR(CLKGEN, CLKOUT, CKSEL) != eClkSelect )
        {
            //
            // Disable before changing the clock
            //
            AM_BFW(CLKGEN, CLKOUT, CKEN, 0);

            //
            // Set the new clock select
            //
            AM_BFW(CLKGEN, CLKOUT, CKSEL, eClkSelect);
        }

        //
        // Enable/disable as requested.
        //
        AM_BFW(CLKGEN, CLKOUT, CKEN, bEnable);
    }
    else
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_clkgen_clkout_enable()

// ****************************************************************************
//
//  am_hal_clkgen_interrupt_enable()
//  Enable selected CLKGEN Interrupts.
//
// ****************************************************************************
uint32_t am_hal_clkgen_interrupt_enable(am_hal_clkgen_interrupt_e ui32IntMask)
{
#if AM_CMSIS_REGS
    if ( (ui32IntMask &
            (CLKGEN_INTRPTEN_OF_Msk         |
             CLKGEN_INTRPTEN_ACC_Msk        |
             CLKGEN_INTRPTEN_ACF_Msk)) == 0 )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Set the interrupt enables according to the mask.
    //
    CLKGEN->INTRPTEN |= ui32IntMask;
#else // AM_CMSIS_REGS
    if ( (ui32IntMask &
            (AM_REG_CLKGEN_INTRPTEN_OF_M    |
             AM_REG_CLKGEN_INTRPTEN_ACC_M   |
             AM_REG_CLKGEN_INTRPTEN_ACF_M)) == 0 )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Set the interrupt enables according to the mask.
    //
    AM_REG(CLKGEN, INTRPTEN) |= ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_clkgen_interrupt_enable()

// ****************************************************************************
//
//  am_hal_clkgen_interrupt_disable(
//  Disable selected CLKGEN Interrupts.
//
// ****************************************************************************
uint32_t
am_hal_clkgen_interrupt_disable(am_hal_clkgen_interrupt_e ui32IntMask)
{
#if AM_CMSIS_REGS
    if ( (ui32IntMask &
            (CLKGEN_INTRPTEN_OF_Msk         |
             CLKGEN_INTRPTEN_ACC_Msk        |
             CLKGEN_INTRPTEN_ACF_Msk)) == 0 )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Disable the interrupts.
    //
    CLKGEN->INTRPTEN &= ~ui32IntMask;
#else // AM_CMSIS_REGS
    if ( (ui32IntMask &
            (AM_REG_CLKGEN_INTRPTEN_OF_M    |
             AM_REG_CLKGEN_INTRPTEN_ACC_M   |
             AM_REG_CLKGEN_INTRPTEN_ACF_M)) == 0 )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Disable the interrupts.
    //
    AM_REG(CLKGEN, INTRPTEN) &= ~ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_clkgen_interrupt_disable()

//*****************************************************************************
//
//  am_hal_clkgen_interrupt_clear()
//  IOM interrupt clear
//
//*****************************************************************************
uint32_t
am_hal_clkgen_interrupt_clear(am_hal_clkgen_interrupt_e ui32IntMask)
{
#if AM_CMSIS_REGS
    if ( (ui32IntMask &
            (CLKGEN_INTRPTEN_OF_Msk         |
             CLKGEN_INTRPTEN_ACC_Msk        |
             CLKGEN_INTRPTEN_ACF_Msk)) == 0 )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Clear the requested interrupts.
    //
    CLKGEN->INTRPTCLR = ui32IntMask;
#else // AM_CMSIS_REGS
    if ( (ui32IntMask &
            (AM_REG_CLKGEN_INTRPTEN_OF_M    |
             AM_REG_CLKGEN_INTRPTEN_ACC_M   |
             AM_REG_CLKGEN_INTRPTEN_ACF_M)) == 0 )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Clear the requested interrupts.
    //
    AM_REG(CLKGEN, INTRPTCLR) = ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_clkgen_interrupt_clear()

// ****************************************************************************
//
//  am_hal_clkgen_interrupt_status_get()
//  Return CLKGEN interrupts.
//
// ****************************************************************************
uint32_t
am_hal_clkgen_interrupt_status_get(bool bEnabledOnly,
                                   uint32_t *pui32IntStatus)
{
    uint32_t ui32IntStatus;

    if ( !pui32IntStatus )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

#if AM_CMSIS_REGS
    ui32IntStatus = CLKGEN->INTRPTSTAT;

    if ( bEnabledOnly )
    {
        ui32IntStatus &= CLKGEN->INTRPTEN;
    }
#else // AM_CMSIS_REGS
    ui32IntStatus = AM_REG(CLKGEN, INTRPTSTAT);

    if ( bEnabledOnly )
    {
        ui32IntStatus &= AM_REG(CLKGEN, INTRPTEN);
    }
#endif // AM_CMSIS_REGS

    *pui32IntStatus = ui32IntStatus;

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_clkgen_interrupt_status_get)

// ****************************************************************************
//
// This function sets the CLKGEN interrupts.
//
// ****************************************************************************
uint32_t
am_hal_clkgen_interrupt_set(am_hal_clkgen_interrupt_e ui32IntMask)
{
#if AM_CMSIS_REGS
    if ( (ui32IntMask &
            (CLKGEN_INTRPTEN_OF_Msk         |
             CLKGEN_INTRPTEN_ACC_Msk        |
             CLKGEN_INTRPTEN_ACF_Msk)) == 0 )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Set the interrupt status.
    //
    CLKGEN->INTRPTSET = ui32IntMask;
#else // AM_CMSIS_REGS
    if ( (ui32IntMask &
            (AM_REG_CLKGEN_INTRPTEN_OF_M    |
             AM_REG_CLKGEN_INTRPTEN_ACC_M   |
             AM_REG_CLKGEN_INTRPTEN_ACF_M)) == 0 )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Set the interrupt status.
    //
    AM_REG(CLKGEN, INTRPTSET) = ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_clkgen_interrupt_set()



//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
