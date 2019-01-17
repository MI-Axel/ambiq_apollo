//*****************************************************************************
//
//  am_hal_burst.c
//! @file
//!
//! @brief Functions for controlling Burst Mode operation.
//!
//! @addtogroup burstmode3
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
#include "am_util.h"

// Disable wait for WFE
//#define NO_WFE

//
// Globals.
//
bool    g_am_hal_burst_mode_available = false;

// ****************************************************************************
//
//  am_hal_burst_mode_initialize()
//  Burst mode initialization function
//
// ****************************************************************************
uint32_t
am_hal_burst_mode_initialize(am_hal_burst_avail_e *peBurstAvail)
{
    uint32_t    ui32Status;
    //
    // Check if the Burst Mode feature is available based on the SKU.
    //
#if AM_CMSIS_REGS
    if ( 0 == MCUCTRL->SKU_b.ALLOWBURST )
    {
        //
        // Burst mode is not available.
        //
        g_am_hal_burst_mode_available = false;
        *peBurstAvail = AM_HAL_BURST_NOTAVAIL;
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#else // AM_CMSIS_REGS
    if (0 == AM_BFR(MCUCTRL, SKU, ALLOWBURST))
    {
        //
        // Burst mode is not available.
        //
        g_am_hal_burst_mode_available = false;
        *peBurstAvail = AM_HAL_BURST_NOTAVAIL;
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif // AM_CMSIS_REGS

    //
    // Enable the Burst Feature Event (DEVPWREVENTEN).
    //
#if AM_CMSIS_REGS
    PWRCTRL->DEVPWREVENTEN_b.BURSTEVEN = 1;
#else // AM_CMSIS_REGS
    AM_BFW(PWRCTRL, DEVPWREVENTEN, BURSTEVEN, 1);
#endif // AM_CMSIS_REGS

    //
    // BLE buck is shared by Burst as well
    // Enable the BLE buck trim values if in use
    //
#if AM_CMSIS_REGS
    if (PWRCTRL->SUPPLYSRC_b.BLEBUCKEN)
    {
        if ( APOLLO3_A1 )
        {
            CLKGEN->BLEBUCKTONADJ =
                _VAL2FLD(CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTEN, CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTEN_EN)         |
                _VAL2FLD(CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM, CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_SetF)   |
                _VAL2FLD(CLKGEN_BLEBUCKTONADJ_TONADJUSTEN, CLKGEN_BLEBUCKTONADJ_TONADJUSTEN_EN)                 |
                _VAL2FLD(CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD, CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD_HFRC_94KHz) |
                _VAL2FLD(CLKGEN_BLEBUCKTONADJ_TONHIGHTHRESHOLD, 0x19)                                           |
                _VAL2FLD(CLKGEN_BLEBUCKTONADJ_TONLOWTHRESHOLD, 0xF);
        }
    }
#else // AM_CMSIS_REGS
    if (AM_BFR(PWRCTRL, SUPPLYSRC, BLEBUCK))
    {
        if ( APOLLO3_A1 )
        {
            AM_REG(CLKGEN, BLEBUCKTONADJ) =
                AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTEN_EN          |
                AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_SetF      |
                AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTEN_EN              |
                AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD_HFRC_94KHz  |
                AM_REG_CLKGEN_BLEBUCKTONADJ_TONHIGHTHRESHOLD(0x19)      |
                AM_REG_CLKGEN_BLEBUCKTONADJ_TONLOWTHRESHOLD(0xF);
        }
    }
#endif // AM_CMSIS_REGS

    //
    // Enable the Burst Functionality (FEATUREENABLE).
    //
#if AM_CMSIS_REGS
    MCUCTRL->FEATUREENABLE_b.BURSTREQ = 1;

    ui32Status = am_hal_flash_delay_status_check(10000,
                            (uint32_t)&MCUCTRL->FEATUREENABLE,
                            MCUCTRL_FEATUREENABLE_BURSTACK_Msk,
                            MCUCTRL_FEATUREENABLE_BURSTACK_Msk,
                            true);
#else // AM_CMSIS_REGS
    AM_BFW(MCUCTRL, FEATUREENABLE, BURSTREQ, 1);

    ui32Status = am_hal_flash_delay_status_check(10000,
                            AM_REG_MCUCTRLn(0) + AM_REG_MCUCTRL_FEATUREENABLE_O,
                            AM_REG_MCUCTRL_FEATUREENABLE_BURSTACK_M,
                            AM_REG_MCUCTRL_FEATUREENABLE_BURSTACK_M,
                            true);
#endif // AM_CMSIS_REGS

    if ( ui32Status != AM_HAL_STATUS_SUCCESS )
    {
        g_am_hal_burst_mode_available = false;
        *peBurstAvail = AM_HAL_BURST_NOTAVAIL;
        return ui32Status;
    }

#if AM_CMSIS_REGS
    if ( 0 == MCUCTRL->FEATUREENABLE_b.BURSTAVAIL )
    {
        //
        // Burst mode is not available.
        //
        g_am_hal_burst_mode_available = false;
        *peBurstAvail = AM_HAL_BURST_NOTAVAIL;
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#else // AM_CMSIS_REGS
    if (0 == AM_BFR(MCUCTRL, FEATUREENABLE, BURSTAVAIL))
    {
        //
        // Burst mode is not available.
        //
        g_am_hal_burst_mode_available = false;
        *peBurstAvail = AM_HAL_BURST_NOTAVAIL;
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif // AM_CMSIS_REGS

    //
    // Check the ACK for the Burst Functionality.
    //
#if AM_CMSIS_REGS
    if ( MCUCTRL->FEATUREENABLE_b.BURSTACK == 0 )
    {
        //
        // If NACK, return status.
        //
        g_am_hal_burst_mode_available = false;
        *peBurstAvail = AM_HAL_BURST_NOTAVAIL;
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#else // AM_CMSIS_REGS
    if (AM_BFR(MCUCTRL, FEATUREENABLE, BURSTACK) == 0)
    {
        //
        // If NACK, return status.
        //
        g_am_hal_burst_mode_available = false;
        *peBurstAvail = AM_HAL_BURST_NOTAVAIL;
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif // AM_CMSIS_REGS

    //
    // Return Availability
    //
    g_am_hal_burst_mode_available = true;
    *peBurstAvail = AM_HAL_BURST_AVAIL;
    return AM_HAL_STATUS_SUCCESS;
}

// ****************************************************************************
//
//  am_hal_burst_mode_enable()
//  Burst mode enable function
//
// ****************************************************************************
uint32_t
am_hal_burst_mode_enable(am_hal_burst_mode_e *peBurstStatus)
{
    uint32_t    ui32Status;

    //
    // Check if Burst Mode is allowed and return status if it is not.
    //
    if (!g_am_hal_burst_mode_available)
    {
        *peBurstStatus = AM_HAL_NORMAL_MODE;
        return AM_HAL_STATUS_INVALID_OPERATION;
    }

    //
    // Request Burst Mode Enable (FREQCTRL)
    //
#if AM_CMSIS_REGS
    CLKGEN->FREQCTRL_b.BURSTREQ = CLKGEN_FREQCTRL_BURSTREQ_EN;

//    while (0 == AM_BFR(CLKGEN, FREQCTRL, BURSTACK));
    ui32Status = am_hal_flash_delay_status_check(10000,
                    (uint32_t)&CLKGEN->FREQCTRL,
                    CLKGEN_FREQCTRL_BURSTSTATUS_Msk,
                    CLKGEN_FREQCTRL_BURSTSTATUS_Msk,
                    true);
#else // AM_CMSIS_REGS
    AM_BFW(CLKGEN, FREQCTRL, BURSTREQ, AM_REG_CLKGEN_FREQCTRL_BURSTREQ_EN);

//    while (0 == AM_BFR(CLKGEN, FREQCTRL, BURSTACK));
    ui32Status = am_hal_flash_delay_status_check(10000,
                            AM_REG_CLKGENn(0) + AM_REG_CLKGEN_FREQCTRL_O,
                            AM_REG_CLKGEN_FREQCTRL_BURSTSTATUS_M,
                            AM_REG_CLKGEN_FREQCTRL_BURSTSTATUS_M,
                            true);
#endif // AM_CMSIS_REGS

    if ( ui32Status != AM_HAL_STATUS_SUCCESS )
    {
        *peBurstStatus = AM_HAL_NORMAL_MODE;
        return ui32Status;
    }

    //
    // Check that the Burst Request was ACK'd.
    //
#if AM_CMSIS_REGS
    if ( 0 == CLKGEN->FREQCTRL_b.BURSTACK )
    {
        *peBurstStatus = AM_HAL_NORMAL_MODE;
        return AM_HAL_STATUS_FAIL;
    }

    //
    // Check the Burst Mode Status (FREQCTRL)
    //
    if ( CLKGEN->FREQCTRL_b.BURSTSTATUS > 0)
    {
        *peBurstStatus =  AM_HAL_BURST_MODE;
    }
    else
    {
        *peBurstStatus =  AM_HAL_NORMAL_MODE;
    }
#else // AM_CMSIS_REGS
    if (0 == AM_BFR(CLKGEN, FREQCTRL, BURSTACK))
    {
        *peBurstStatus = AM_HAL_NORMAL_MODE;
        return AM_HAL_STATUS_FAIL;
    }

    //
    // Check the Burst Mode Status (FREQCTRL)
    //
    if (AM_BFR(CLKGEN, FREQCTRL, BURSTSTATUS) > 0)
    {
        *peBurstStatus =  AM_HAL_BURST_MODE;
    }
    else
    {
        *peBurstStatus =  AM_HAL_NORMAL_MODE;
    }
#endif // AM_CMSIS_REGS

    return AM_HAL_STATUS_SUCCESS;
}

// ****************************************************************************
//
//  am_hal_burst_mode_disable()
//  Burst mode disable function
//
// ****************************************************************************
uint32_t
am_hal_burst_mode_disable(am_hal_burst_mode_e *peBurstStatus)
{
    uint32_t    ui32Status;

    //
    // Request Burst Mode Enable (FREQCTRL)
    //
#if AM_CMSIS_REGS
    CLKGEN->FREQCTRL_b.BURSTREQ = CLKGEN_FREQCTRL_BURSTREQ_DIS;

    //
    // Disable the Burst Feature Event (DEVPWREVENTEN).
    //
    PWRCTRL->DEVPWREVENTEN_b.BURSTEVEN = 0;

//  while (1 == CLKGEN->FREQCTRL_b.BURSTACK);
    ui32Status = am_hal_flash_delay_status_check(10000,
                            (uint32_t)&CLKGEN->FREQCTRL,
                            CLKGEN_FREQCTRL_BURSTSTATUS_Msk,
                            0,
                            true);
#else // AM_CMSIS_REGS
    AM_BFW(CLKGEN, FREQCTRL, BURSTREQ, AM_REG_CLKGEN_FREQCTRL_BURSTREQ_DIS);

    //
    // Disable the Burst Feature Event (DEVPWREVENTEN).
    //
    AM_BFW(PWRCTRL, DEVPWREVENTEN, BURSTEVEN, 0);

//  while (1 == AM_BFR(CLKGEN, FREQCTRL, BURSTACK));
    ui32Status = am_hal_flash_delay_status_check(10000,
                            AM_REG_CLKGENn(0) + AM_REG_CLKGEN_FREQCTRL_O,
                            AM_REG_CLKGEN_FREQCTRL_BURSTSTATUS_M,
                            0,
                            true);
#endif // AM_CMSIS_REGS

    if ( ui32Status != AM_HAL_STATUS_SUCCESS )
    {
        *peBurstStatus = AM_HAL_NORMAL_MODE;
        return ui32Status;
    }

    //
    // Check the Burst Mode Status (FREQCTRL)
    //
#if AM_CMSIS_REGS
    //
    // Check the Burst Mode Status (FREQCTRL)
    //
    if ( CLKGEN->FREQCTRL_b.BURSTSTATUS > 0 )
    {
        *peBurstStatus = AM_HAL_BURST_MODE;
    }
    else
    {
        *peBurstStatus = AM_HAL_NORMAL_MODE;
    }

#else // AM_CMSIS_REGS
    if (AM_BFR(CLKGEN, FREQCTRL, BURSTSTATUS) > 0)
    {
        *peBurstStatus = AM_HAL_BURST_MODE;
    }
    else
    {
        *peBurstStatus = AM_HAL_NORMAL_MODE;
    }
#endif // AM_CMSIS_REGS

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
