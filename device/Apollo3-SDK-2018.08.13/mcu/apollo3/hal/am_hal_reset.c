//*****************************************************************************
//
//  am_hal_reset.c
//! @file
//!
//! @brief Hardware abstraction layer for the Reset Generator module.
//!
//! @addtogroup rstgen2 Reset Generator (RSTGEN)
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

#include "am_mcu_apollo.h"

//*****************************************************************************
//
//  am_hal_reset_enable()
//  Enable and configure the Reset controller.
//
//*****************************************************************************
uint32_t
am_hal_reset_configure(am_hal_reset_configure_e eConfigure)
{
    uint32_t ui32Val;
    bool     bEnable;

#if AM_CMSIS_REGS
    switch ( eConfigure )
    {
        case AM_HAL_RESET_BROWNOUT_HIGH_ENABLE:
            bEnable = true;
            ui32Val = RSTGEN_CFG_BODHREN_Msk;
            break;

        case AM_HAL_RESET_WDT_RESET_ENABLE:
            bEnable = true;
            ui32Val = RSTGEN_CFG_WDREN_Msk;
            break;

        case AM_HAL_RESET_BROWNOUT_HIGH_DISABLE:
            bEnable = false;
            ui32Val = RSTGEN_CFG_BODHREN_Msk;
            break;

        case AM_HAL_RESET_WDT_RESET_DISABLE:
            bEnable = false;
            ui32Val = RSTGEN_CFG_WDREN_Msk;
            break;

        default:
            return AM_HAL_STATUS_INVALID_ARG;
    }

    AM_CRITICAL_BEGIN
    if ( bEnable )
    {
        RSTGEN->CFG |= ui32Val;
    }
    else
    {
        RSTGEN->CFG &= ~ui32Val;
    }
    AM_CRITICAL_END
#else // AM_CMSIS_REGS
    switch ( eConfigure )
    {
        case AM_HAL_RESET_BROWNOUT_HIGH_ENABLE:
            bEnable = true;
            ui32Val = AM_REG_RSTGEN_CFG_BODHREN_M;
            break;

        case AM_HAL_RESET_WDT_RESET_ENABLE:
            bEnable = true;
            ui32Val = AM_REG_RSTGEN_CFG_WDREN_M;
            break;

        case AM_HAL_RESET_BROWNOUT_HIGH_DISABLE:
            bEnable = false;
            ui32Val = AM_REG_RSTGEN_CFG_BODHREN_M;
            break;

        case AM_HAL_RESET_WDT_RESET_DISABLE:
            bEnable = false;
            ui32Val = AM_REG_RSTGEN_CFG_WDREN_M;
            break;

        default:
            return AM_HAL_STATUS_INVALID_ARG;
    }

    if ( bEnable )
    {
        AM_REGa_SET(RSTGEN, CFG, ui32Val);
    }
    else
    {
        AM_REGa_CLR(RSTGEN, CFG, ui32Val);
    }
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_reset_configure()


//*****************************************************************************
//
//  am_hal_reset_control()
//  Perform various reset functions including assertion of software resets.
//
//*****************************************************************************
uint32_t
am_hal_reset_control(am_hal_reset_control_e eControl, void *pArgs)
{
    switch ( eControl )
    {
        case AM_HAL_RESET_CONTROL_SWPOR:
            //
            // Perform a Power On Reset level reset.
            // Write the POR key to the software POR register.
            //
#if AM_CMSIS_REGS
            RSTGEN->SWPOR =
                   _VAL2FLD(RSTGEN_SWPOR_SWPORKEY, RSTGEN_SWPOR_SWPORKEY_KEYVALUE);
#else // AM_CMSIS_REGS
            AM_REG(RSTGEN, SWPOR) =
                   AM_REG_RSTGEN_SWPOR_SWPORKEY(AM_REG_RSTGEN_SWPOR_SWPORKEY_KEYVALUE);
#endif // AM_CMSIS_REGS
            break;

        case AM_HAL_RESET_CONTROL_SWPOI:
            //
            // Perform a Power On Initialization level reset.
            // Write the POI key to the software POI register.
            //
#if AM_CMSIS_REGS
            RSTGEN->SWPOI =
                _VAL2FLD(RSTGEN_SWPOI_SWPOIKEY, RSTGEN_SWPOI_SWPOIKEY_KEYVALUE);
#else // AM_CMSIS_REGS
            AM_REG(RSTGEN, SWPOI) =
                AM_REG_RSTGEN_SWPOI_SWPOIKEY(AM_REG_RSTGEN_SWPOI_SWPOIKEY_KEYVALUE);
#endif // AM_CMSIS_REGS
            break;

        case AM_HAL_RESET_CONTROL_STATUSCLEAR:
            //
            // Clear ALL of the reset status register bits.
            //
#if AM_CMSIS_REGS
            RSTGEN->STAT = 0;
#else // AM_CMSIS_REGS
            AM_REG(RSTGEN, STAT) = 0;
#endif // AM_CMSIS_REGS
            break;

        case AM_HAL_RESET_CONTROL_TPIU_RESET:
            //
            // Reset the TPIU.
            //
#if AM_CMSIS_REGS
            RSTGEN->TPIURST = _VAL2FLD(RSTGEN_TPIURST_TPIURST, 1);
#else // AM_CMSIS_REGS
            AM_REG(RSTGEN, TPIURST) = AM_REG_RSTGEN_TPIURST_TPIURST(1);
#endif // AM_CMSIS_REGS
            break;

        default:
            return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_reset_control()


//*****************************************************************************
//
//  am_hal_reset_status_get()
//  Return status of the reset generator.
//
//*****************************************************************************
uint32_t
am_hal_reset_status_get(am_hal_reset_status_t *psStatus)
{
    uint32_t ui32Status;

    if ( psStatus == NULL )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Retrieve the reset generator status bits
    //
#if AM_CMSIS_REGS
    ui32Status = RSTGEN->STAT;
    psStatus->eStatus      = (am_hal_reset_status_e)ui32Status;
    psStatus->bEXTStat     = _FLD2VAL(RSTGEN_STAT_EXRSTAT, ui32Status);
    psStatus->bPORStat     = _FLD2VAL(RSTGEN_STAT_PORSTAT, ui32Status);
    psStatus->bBODStat     = _FLD2VAL(RSTGEN_STAT_BORSTAT, ui32Status);
    psStatus->bSWPORStat   = _FLD2VAL(RSTGEN_STAT_SWRSTAT, ui32Status);
    psStatus->bSWPOIStat   = _FLD2VAL(RSTGEN_STAT_POIRSTAT, ui32Status);
    psStatus->bDBGRStat    = _FLD2VAL(RSTGEN_STAT_DBGRSTAT, ui32Status);
    psStatus->bWDTStat     = _FLD2VAL(RSTGEN_STAT_WDRSTAT, ui32Status);
    psStatus->bBOUnregStat = _FLD2VAL(RSTGEN_STAT_BOUSTAT, ui32Status);
    psStatus->bBOCOREStat  = _FLD2VAL(RSTGEN_STAT_BOCSTAT, ui32Status);
    psStatus->bBOMEMStat   = _FLD2VAL(RSTGEN_STAT_BOFSTAT, ui32Status);
    psStatus->bBOBLEStat   = _FLD2VAL(RSTGEN_STAT_BOBSTAT, ui32Status);
#else // AM_CMSIS_REGS
    ui32Status = AM_REG(RSTGEN, STAT);
    psStatus->eStatus      = (am_hal_reset_status_e)ui32Status;
    psStatus->bEXTStat     = AM_BFX(RSTGEN, STAT, EXRSTAT, ui32Status);
    psStatus->bPORStat     = AM_BFX(RSTGEN, STAT, PORSTAT, ui32Status);
    psStatus->bBODStat     = AM_BFX(RSTGEN, STAT, BORSTAT, ui32Status);
    psStatus->bSWPORStat   = AM_BFX(RSTGEN, STAT, SWRSTAT, ui32Status);
    psStatus->bSWPOIStat   = AM_BFX(RSTGEN, STAT, POIRSTAT, ui32Status);
    psStatus->bDBGRStat    = AM_BFX(RSTGEN, STAT, DBGRSTAT, ui32Status);
    psStatus->bWDTStat     = AM_BFX(RSTGEN, STAT, WDRSTAT, ui32Status);
    psStatus->bBOUnregStat = AM_BFX(RSTGEN, STAT, BOUSTAT, ui32Status);
    psStatus->bBOCOREStat  = AM_BFX(RSTGEN, STAT, BOCSTAT, ui32Status);
    psStatus->bBOMEMStat   = AM_BFX(RSTGEN, STAT, BOFSTAT, ui32Status);
    psStatus->bBOBLEStat   = AM_BFX(RSTGEN, STAT, BOBSTAT, ui32Status);
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_reset_status_get()

//*****************************************************************************
//
//! @brief Enable selected RSTGEN Interrupts.
//!
//! Use this function to enable the reset generator interrupts.
//!
//! @param ui32IntMask - One or more of the following bits, any of which can
//! be ORed together.
//!   AM_HAL_RESET_INTERRUPT_BODH
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_reset_interrupt_enable(uint32_t ui32IntMask)
{
#if AM_CMSIS_REGS
    AM_CRITICAL_BEGIN
    RSTGEN->INTEN |= ui32IntMask;
    AM_CRITICAL_END
#else // AM_CMSIS_REGS
    AM_REGa_SET(RSTGEN, INTEN, ui32IntMask);
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_reset_interrupt_enable()

//*****************************************************************************
//
//  am_hal_reset_interrupt_disable()
//  Disable selected RSTGEN Interrupts.
//
//*****************************************************************************
uint32_t
am_hal_reset_interrupt_disable(uint32_t ui32IntMask)
{
#if AM_CMSIS_REGS
    AM_CRITICAL_BEGIN
    RSTGEN->INTEN &= ~ui32IntMask;
    AM_CRITICAL_END
#else //  AM_CMSIS_REGS
    AM_REGa_CLR(RSTGEN, INTEN, ui32IntMask);
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_reset_interrupt_disable()

//*****************************************************************************
//
//  am_hal_reset_interrupt_clear()
//  Reset generator interrupt clear
//
//*****************************************************************************
uint32_t
am_hal_reset_interrupt_clear(uint32_t ui32IntMask)
{
#if AM_CMSIS_REGS
    RSTGEN->INTEN = ui32IntMask;
#else // AM_CMSIS_REGS
    AM_REG(RSTGEN, INTEN) = ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_reset_interrupt_clear()

//*****************************************************************************
//
//  am_hal_reset_interrupt_status_get()
//  Get interrupt status of reset generator.
//
//*****************************************************************************
uint32_t
am_hal_reset_interrupt_status_get(bool bEnabledOnly,
                                  uint32_t *pui32IntStatus)
{
    if ( pui32IntStatus == NULL )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Retrieve the reset generator status bits
    //
#if AM_CMSIS_REGS
    *pui32IntStatus = RSTGEN->INTSTAT;
#else // AM_CMSIS_REGS
    *pui32IntStatus = AM_REG(RSTGEN, INTSTAT);
#endif // AM_CMSIS_REGS

    //
    // Return success status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_reset_interrupt_status_get()


//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
