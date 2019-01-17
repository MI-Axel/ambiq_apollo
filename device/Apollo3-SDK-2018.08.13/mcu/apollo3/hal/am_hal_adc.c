//*****************************************************************************
//
//  am_hal_adc.c
//! @file
//!
//! @brief Functions for interfacing with the Analog to Digital Converter.
//!
//! @addtogroup adc2 Analog-to-Digital Converter (ADC)
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
// Private Types.
//
//*****************************************************************************

#define AM_HAL_MAGIC_ADC                0xAFAFAF
#define AM_HAL_ADC_CHK_HANDLE(h)        ((h) && ((am_hal_handle_prefix_t *)(h))->s.bInit && (((am_hal_handle_prefix_t *)(h))->s.magic == AM_HAL_MAGIC_ADC))

//
// ADC Power save register state.
//
typedef struct
{
    bool          bValid;
    uint32_t      regCFG;
    uint32_t      regSL0CFG;
    uint32_t      regSL1CFG;
    uint32_t      regSL2CFG;
    uint32_t      regSL3CFG;
    uint32_t      regSL4CFG;
    uint32_t      regSL5CFG;
    uint32_t      regSL6CFG;
    uint32_t      regSL7CFG;
    uint32_t      regWULIM;
    uint32_t      regWLLIM;
    uint32_t      regINTEN;
} am_hal_adc_register_state_t;

//
// ADC State structure.
//
typedef struct
{
    //
    // Handle validation prefix.
    //
    am_hal_handle_prefix_t      prefix;

    //
    // Physical module number.
    //
    uint32_t                    ui32Module;

    //
    // ADC Capabilities.
    //
    am_hal_adc_capabilities_t   capabilities;

    // Power Save-Restore register state
    am_hal_adc_register_state_t registerState;

} am_hal_adc_state_t;

//*****************************************************************************
//
// Global Variables.
//
//*****************************************************************************
am_hal_adc_state_t             g_ADCState[AM_REG_ADC_NUM_MODULES];

uint32_t                       g_ADCSlotsConfigured;

//*****************************************************************************
//
//! @brief ADC initialization function
//!
//! @param ui32Module   - module instance.
//! @param handle       - returns the handle for the module instance.
//!
//! This function accepts a module instance, allocates the interface and then
//! returns a handle to be used by the remaining interface functions.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_initialize(uint32_t ui32Module, void **ppHandle)
{

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Validate the module number
    //
    if ( ui32Module >= AM_REG_ADC_NUM_MODULES )
    {
        return AM_HAL_STATUS_OUT_OF_RANGE;
    }

    //
    // Check for valid arguements.
    //
    if ( !ppHandle )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Check if the handle is unallocated.
    //
    if ( g_ADCState[ui32Module].prefix.s.bInit )
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif

    //
    // Initialize the handle.
    //
    g_ADCState[ui32Module].prefix.s.bInit = true;
    g_ADCState[ui32Module].prefix.s.magic = AM_HAL_MAGIC_ADC;
    g_ADCState[ui32Module].ui32Module = ui32Module;

    //
    // Initialize the number of slots configured.
    //
    g_ADCSlotsConfigured = 0;

    //
    // Return the handle.
    //
    *ppHandle = (void *)&g_ADCState[ui32Module];

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief MSPI deinitialization function
//!
//! @param handle       - returns the handle for the module instance.
//!
//! This function accepts a handle to an instance and de-initializes the
//! interface.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_deinitialize(void *pHandle)
{
    uint32_t            status = AM_HAL_STATUS_SUCCESS;
    am_hal_adc_state_t  *pADCState = (am_hal_adc_state_t *)pHandle;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    if ( pADCState->prefix.s.bEnable )
    {
        status = am_hal_adc_disable(pHandle);
    }

    pADCState->prefix.s.bInit = false;

    //
    // Return the status.
    //
    return status;
}

//*****************************************************************************
//
//! @brief ADC configuration function
//!
//! @param handle   - handle for the module instance.
//! @param pConfig  - pointer to the configuration structure.
//!
//! This function configures the ADC for operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_configure(void *pHandle,
                     am_hal_adc_config_t *psConfig)
{
    uint32_t            ui32Config;
    am_hal_adc_state_t  *pADCState = (am_hal_adc_state_t *)pHandle;
    uint32_t            ui32Module = pADCState->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    ui32Config = 0;

#if AM_CMSIS_REGS
    //
    // Set the ADC clock source.
    //
    ui32Config |= _VAL2FLD(ADC_CFG_CLKSEL, psConfig->eClock);

    //
    // Set the ADC trigger polarity.
    //
    ui32Config |= _VAL2FLD(ADC_CFG_TRIGPOL, psConfig->ePolarity);

    //
    // Set the ADC trigger.
    //
    ui32Config |= _VAL2FLD(ADC_CFG_TRIGSEL, psConfig->eTrigger);

    //
    // Set the ADC reference voltage.
    //
    ui32Config |= _VAL2FLD(ADC_CFG_REFSEL, psConfig->eReference);

    //
    // Set the Destructive FIFO read.
    //
    ui32Config |= _VAL2FLD(ADC_CFG_DFIFORDEN, 1);

    //
    // Set the ADC clock mode.
    //
    ui32Config |= _VAL2FLD(ADC_CFG_CKMODE, psConfig->eClockMode);

    //
    // Set the ADC low power mode.
    //
    ui32Config |= _VAL2FLD(ADC_CFG_LPMODE, psConfig->ePowerMode);

    //
    // Set the ADC repetition mode.
    //
    ui32Config |= _VAL2FLD(ADC_CFG_RPTEN, psConfig->eRepeat);

    //
    // Set the configuration in the ADC peripheral.
    //
    ADCn(ui32Module)->CFG = ui32Config;
#else // AM_CMSIS_REGS
    //
    // Set the ADC clock source.
    //
    ui32Config |= AM_REG_ADC_CFG_CLKSEL(psConfig->eClock);

    //
    // Set the ADC trigger polarity.
    //
    ui32Config |= AM_REG_ADC_CFG_TRIGPOL(psConfig->ePolarity);

    //
    // Set the ADC trigger.
    //
    ui32Config |= AM_REG_ADC_CFG_TRIGSEL(psConfig->eTrigger);

    //
    // Set the ADC reference voltage.
    //
    ui32Config |= AM_REG_ADC_CFG_REFSEL(psConfig->eReference);

    //
    // Set the Destructive FIFO read.
    //
    ui32Config |= AM_REG_ADC_CFG_DFIFORDEN_EN;

    //
    // Set the ADC clock mode.
    //
    ui32Config |= AM_REG_ADC_CFG_CKMODE(psConfig->eClockMode);

    //
    // Set the ADC low power mode.
    //
    ui32Config |= AM_REG_ADC_CFG_LPMODE(psConfig->ePowerMode);

    //
    // Set the ADC repetition mode.
    //
    ui32Config |= AM_REG_ADC_CFG_RPTEN(psConfig->eRepeat);

    //
    // Set the configuration in the ADC peripheral.
    //
    AM_REGn(ADC, ui32Module, CFG) = ui32Config;
#endif // AM_CMSIS_REGS

    //
    // Return status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC slot configuration function
//!
//! @param handle   - handle for the module instance.
//! @param pConfig  - pointer to the configuration structure.
//!
//! This function configures the ADC slot for operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_configure_slot(void *pHandle,
                          uint32_t ui32SlotNumber,
                          am_hal_adc_slot_config_t *pSlotConfig)
{
    uint32_t            ui32Config;
    uint32_t            ui32RegOffset;
    am_hal_adc_state_t  *pADCState = (am_hal_adc_state_t *)pHandle;
    uint32_t            ui32Module = pADCState->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Check the slot number.
    //
    if ( ui32SlotNumber >= AM_HAL_ADC_MAX_SLOTS )
    {
        return AM_HAL_STATUS_OUT_OF_RANGE;
    }
#endif

    ui32Config = 0;

#if AM_CMSIS_REGS
    //
    // Set the measurements to average
    //
    ui32Config |= _VAL2FLD(ADC_SL0CFG_ADSEL0, pSlotConfig->eMeasToAvg);

    //
    // Set the precision mode.
    //
    ui32Config |= _VAL2FLD(ADC_SL0CFG_PRMODE0, pSlotConfig->ePrecisionMode);

    //
    // Set the channel.
    //
    ui32Config |= _VAL2FLD(ADC_SL0CFG_CHSEL0, pSlotConfig->eChannel);

    //
    // Enable window comparison if configured.
    //
    ui32Config |= _VAL2FLD(ADC_SL0CFG_WCEN0, pSlotConfig->bWindowCompare);

    //
    // Enable the slot if configured.
    //
    ui32Config |= _VAL2FLD(ADC_SL0CFG_SLEN0, pSlotConfig->bEnabled);

    //
    // Locate the correct register for this ADC slot.
    //
    ui32RegOffset = ((uint32_t)&ADCn(ui32Module)->SL0CFG) + (4 * ui32SlotNumber);

    //
    // Write the register with the caller's configuration value.
    //
    AM_REGVAL(ui32RegOffset) = ui32Config;
#else // AM_CMSIS_REGS
    //
    // Set the measurements to average
    //
    ui32Config |= AM_REG_ADC_SL0CFG_ADSEL0(pSlotConfig->eMeasToAvg);

    //
    // Set the precision mode.
    //
    ui32Config |= AM_REG_ADC_SL0CFG_PRMODE0(pSlotConfig->ePrecisionMode);

    //
    // Set the channel.
    //
    ui32Config |= AM_REG_ADC_SL0CFG_CHSEL0(pSlotConfig->eChannel);

    //
    // Enable window comparison if configured.
    //
    ui32Config |= AM_REG_ADC_SL0CFG_WCEN0(pSlotConfig->bWindowCompare);

    //
    // Enable the slot if configured.
    //
    ui32Config |= AM_REG_ADC_SL0CFG_SLEN0(pSlotConfig->bEnabled);

    //
    // Locate the correct register for this ADC slot.
    //
    ui32RegOffset = (AM_REG_ADCn(ui32Module) + AM_REG_ADC_SL0CFG_O + (4 * ui32SlotNumber));

    //
    // Write the register with the caller's configuration value.
    //
    AM_REGVAL(ui32RegOffset) = ui32Config;
#endif // AM_CMSIS_REGS

    //
    // Update the nubmer of slots configured.
    //
    g_ADCSlotsConfigured++;

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC DMA configuration function
//!
//! @param handle   - handle for the module instance.
//! @param pConfig  - pointer to the configuration structure.
//!
//! This function configures the ADC DMA for operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_configure_dma(void *pHandle,
                         am_hal_adc_dma_config_t *pDMAConfig)
{
    uint32_t    ui32Config;
    uint32_t    ui32Module = ((am_hal_adc_state_t *)pHandle)->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    ui32Config = 0;

    //
    // Configure the DMA complete power-off.
    //
#if AM_CMSIS_REGS
    ui32Config |= _VAL2FLD(ADC_DMACFG_DPWROFF, pDMAConfig->bPwrOffOnDMAComplete);

    //
    // Configure the data to be transferred.
    //
    if ( g_ADCSlotsConfigured > 1 )
    {
        // Need slot number to distinguish between slot results.
        ui32Config |= _VAL2FLD(ADC_DMACFG_DMAMSK, ADC_DMACFG_DMAMSK_DIS);
    }
    else
    {
        ui32Config |= _VAL2FLD(ADC_DMACFG_DMAMSK, ADC_DMACFG_DMAMSK_EN);
    }

    //
    // Enable DMA Halt on Status (DMAERR or DMACPL) by default.
    //
    ui32Config |= _VAL2FLD(ADC_DMACFG_DMAHONSTAT, ADC_DMACFG_DMAHONSTAT_EN);

    //
    // Configure the DMA dynamic priority handling.
    //
    ui32Config |= _VAL2FLD(ADC_DMACFG_DMADYNPRI, pDMAConfig->bDynamicPriority);

    //
    // Configure the DMA static priority.
    //
    ui32Config |= _VAL2FLD(ADC_DMACFG_DMAPRI, pDMAConfig->ePriority);

    //
    // Enable the DMA (does not start until ADC is enabled and triggered).
    //
    ui32Config |= _VAL2FLD(ADC_DMACFG_DMAEN, ADC_DMACFG_DMAEN_EN);

    //
    // Set the DMA configuration.
    //
    ADCn(ui32Module)->DMACFG = ui32Config;

    //
    // Set the DMA transfer count.
    //
    ADCn(ui32Module)->DMATOTCOUNT_b.TOTCOUNT = pDMAConfig->ui32SampleCount;

    //
    // Set the DMA target address.
    //
    ADCn(ui32Module)->DMATARGADDR = pDMAConfig->ui32TargetAddress;

    //
    // Set the DMA trigger on FIFO 75% full.
    //
    ADCn(ui32Module)->DMATRIGEN = ADC_DMATRIGEN_DFIFO75_Msk;
#else // AM_CMSIS_REGS
    ui32Config |= AM_REG_ADC_DMACFG_DPWROFF(pDMAConfig->bPwrOffOnDMAComplete);

    //
    // Configure the data to be transferred.
    //
    if ( g_ADCSlotsConfigured > 1 )
    {
        ui32Config |= AM_REG_ADC_DMACFG_DMAMSK_DIS;  // Need slot number to distinguish between slot results.
    }
    else
    {
        ui32Config |= AM_REG_ADC_DMACFG_DMAMSK_EN;
    }

    //
    // Enable DMA Halt on Status (DMAERR or DMACPL) by default.
    //
    ui32Config |= AM_REG_ADC_DMACFG_DMAHONSTAT_EN;

    //
    // Configure the DMA dynamic priority handling.
    //
    ui32Config |= AM_REG_ADC_DMACFG_DMADYNPRI(pDMAConfig->bDynamicPriority);

    //
    // Configure the DMA static priority.
    //
    ui32Config |= AM_REG_ADC_DMACFG_DMAPRI(pDMAConfig->ePriority);

    //
    // Enable the DMA (does not start until ADC is enabled and triggered).
    //
    ui32Config |= AM_REG_ADC_DMACFG_DMAEN_EN;

    //
    // Set the DMA configuration.
    //
    AM_REGn(ADC, ui32Module, DMACFG) = ui32Config;

    //
    // Set the DMA transfer count.
    //
    AM_BFWn(ADC, ui32Module, DMATOTCOUNT, TOTCOUNT, pDMAConfig->ui32SampleCount);

    //
    // Set the DMA target address.
    //
    AM_REGn(ADC, ui32Module, DMATARGADDR) = pDMAConfig->ui32TargetAddress;

    //
    // Set the DMA trigger on FIFO 75% full.
    //
    AM_REGn(ADC, ui32Module, DMATRIGEN) = AM_REG_ADC_DMATRIGEN_DFIFO75_M;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC device specific control function.
//!
//! @param handle   - handle for the module instance.
//!
//! This function provides for special control functions for the ADC operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t am_hal_adc_control(void *pHandle,
                            am_hal_adc_request_e eRequest,
                            void *pConfig)
{
    uint32_t    ui32Module = ((am_hal_adc_state_t *)pHandle)->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    switch(eRequest)
    {
        case AM_HAL_ADC_REQ_WINDOW_CONFIG:
        {
            am_hal_adc_window_config_t *pWindowConfig = (am_hal_adc_window_config_t *)pConfig;

#ifndef AM_HAL_DISABLE_API_VALIDATION
            //
            // Check the window limits.
            //
#if AM_CMSIS_REGS
            if ( (pWindowConfig->ui32Upper > ADC_WULIM_ULIM_Msk)   ||
                 (pWindowConfig->ui32Lower > ADC_WLLIM_LLIM_Msk) )
            {
                return AM_HAL_STATUS_OUT_OF_RANGE;
            }
#else // AM_CMSIS_REGS
            if ( (pWindowConfig->ui32Upper > AM_REG_ADC_WULIM_ULIM_M)   ||
                 (pWindowConfig->ui32Lower > AM_REG_ADC_WLLIM_LLIM_M) )
            {
                return AM_HAL_STATUS_OUT_OF_RANGE;
            }
#endif // AM_CMSIS_REGS
#endif
            //
            // Set the window comparison upper and lower limits.
            //
#if AM_CMSIS_REGS
            ADCn(ui32Module)->WULIM = _VAL2FLD(ADC_WULIM_ULIM, pWindowConfig->ui32Upper);
            ADCn(ui32Module)->WLLIM = _VAL2FLD(ADC_WLLIM_LLIM, pWindowConfig->ui32Lower);

            //
            // Set the window scale per precision mode if indicated.
            //
            ADCn(ui32Module)->SCWLIM = _VAL2FLD(ADC_SCWLIM_SCWLIMEN,
                                                pWindowConfig->bScaleLimits);
#else // AM_CMSIS_REGS
            AM_REGn(ADC, ui32Module, WULIM) = AM_REG_ADC_WULIM_ULIM(pWindowConfig->ui32Upper);
            AM_REGn(ADC, ui32Module, WLLIM) = AM_REG_ADC_WLLIM_LLIM(pWindowConfig->ui32Lower);

            //
            // Set the window scale per precision mode if indicated.
            //
            AM_REGn(ADC, ui32Module, SCWLIM) =
            AM_REG_ADC_SCWLIM_SCWLIMEN(pWindowConfig->bScaleLimits);
#endif // AM_CMSIS_REGS
        }
        break;
        default:
            return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Return status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC enable function
//!
//! @param handle   - handle for the module instance.
//!
//! This function enables the ADC operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_enable(void *pHandle)
{
    am_hal_adc_state_t  *pADCState = (am_hal_adc_state_t *)pHandle;
    uint32_t            ui32Module = pADCState->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    if ( pADCState->prefix.s.bEnable )
    {
        return AM_HAL_STATUS_SUCCESS;
    }
#endif

    //
    // Enable the ADC.
    //
#if AM_CMSIS_REGS
    ADCn(ui32Module)->CFG_b.ADCEN = 0x1;
#else // AM_CMSIS_REGS
    AM_BFWn(ADC, ui32Module, CFG, ADCEN, 0x1);
#endif // AM_CMSIS_REGS

    //
    // Set flag to indicate module is enabled.
    //
    pADCState->prefix.s.bEnable = true;

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC disable function
//!
//! @param handle   - handle for the module instance.
//!
//! This function disables the ADC operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_disable(void *pHandle)
{
    am_hal_adc_state_t  *pADCState = (am_hal_adc_state_t *)pHandle;
    uint32_t            ui32Module = pADCState->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    //
    // Disable the ADC.
    //
#if AM_CMSIS_REGS
    ADCn(ui32Module)->CFG_b.ADCEN = 0x0;
#else // AM_CMSIS_REGS
    AM_BFWn(ADC, ui32Module, CFG, ADCEN, 0x0);
#endif // AM_CMSIS_REGS

    //
    // Set flag to indicate module is disabled.
    //
    pADCState->prefix.s.bEnable = false;

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC status function
//!
//! @param handle       - handle for the interface.
//!
//! This function returns the current status of the DMA operation.
//!
//! @return status      - DMA status flags.
//
//*****************************************************************************
uint32_t
am_hal_adc_status_get(void *pHandle, am_hal_adc_status_t *pStatus )
{
    uint32_t    ui32Module = ((am_hal_adc_state_t *)pHandle)->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    //
    // Get the power status.
    //
#if AM_CMSIS_REGS
    pStatus->bPoweredOn = (ADCn(ui32Module)->STAT & ADC_STAT_PWDSTAT_Msk) ==
                          _VAL2FLD(ADC_STAT_PWDSTAT, ADC_STAT_PWDSTAT_ON);

    //
    // Get the low power mode 1 status.
    //
    pStatus->bLPMode1 = (ADCn(ui32Module)->STAT & ADC_STAT_PWDSTAT_Msk) ==
                        _VAL2FLD(ADC_STAT_PWDSTAT, ADC_STAT_PWDSTAT_POWERED_DOWN);

    //
    //  Get the DMA status.
    //
    pStatus->bErr = ((ADCn(ui32Module)->DMASTAT & ADC_DMASTAT_DMAERR_Msk) > 0);
    pStatus->bCmp = ((ADCn(ui32Module)->DMASTAT & ADC_DMASTAT_DMACPL_Msk) > 0);
    pStatus->bTIP = ((ADCn(ui32Module)->DMASTAT & ADC_DMASTAT_DMATIP_Msk) > 0);
#else // AM_CMSIS_REGS
    pStatus->bPoweredOn = ((AM_REGn(ADC, ui32Module, STAT) & AM_REG_ADC_STAT_PWDSTAT_M) ==
                           AM_REG_ADC_STAT_PWDSTAT_ON);

    //
    // Get the low power mode 1 status.
    //
    pStatus->bLPMode1 = ((AM_REGn(ADC, ui32Module, STAT) & AM_REG_ADC_STAT_PWDSTAT_M) ==
                         AM_REG_ADC_STAT_PWDSTAT_POWERED_DOWN);

    //
    //  Get the DMA status.
    //
    pStatus->bErr = ((AM_REGn(ADC, ui32Module, DMASTAT) & AM_REG_ADC_DMASTAT_DMAERR_M) > 0);
    pStatus->bCmp = ((AM_REGn(ADC, ui32Module, DMASTAT) & AM_REG_ADC_DMASTAT_DMACPL_M) > 0);
    pStatus->bTIP = ((AM_REGn(ADC, ui32Module, DMASTAT) & AM_REG_ADC_DMASTAT_DMATIP_M) > 0);
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC enable interrupts function
//!
//! @param handle       - handle for the interface.
//! @param ui32IntMask  - ADC interrupt mask.
//!
//! This function enables the specific indicated interrupts.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_interrupt_enable(void *pHandle, uint32_t ui32IntMask)
{
    uint32_t    ui32Module = ((am_hal_adc_state_t*)pHandle)->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    //
    // Enable the interrupts.
    //
#if AM_CMSIS_REGS
    ADCn(ui32Module)->INTEN |= ui32IntMask;
#else // AM_CMSIS_REGS
    AM_REGn(ADC, ui32Module, INTEN) |= ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC disable interrupts function
//!
//! @param handle       - handle for the interface.
//! @param ui32IntMask  - ADC interrupt mask.
//!
//! This function disable the specific indicated interrupts.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_interrupt_disable(void *pHandle, uint32_t ui32IntMask)
{
    uint32_t    ui32Module = ((am_hal_adc_state_t*)pHandle)->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    //
    // Disable the interrupts.
    //
#if AM_CMSIS_REGS
    ADCn(ui32Module)->INTEN &= ~ui32IntMask;
#else // AM_CMSIS_REGS
    AM_REGn(ADC, ui32Module, INTEN) &= ~ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC interrupt status function
//!
//! @param handle       - handle for the interface.
//!
//! This function returns the specific indicated interrupt status.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_interrupt_status(void *pHandle,
                            uint32_t  *pui32Status,
                            bool bEnabledOnly)
{
    uint32_t    ui32Module = ((am_hal_adc_state_t*)pHandle)->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    //
    // if requested, only return the interrupts that are enabled.
    //
#if AM_CMSIS_REGS
    if ( bEnabledOnly )
    {
        uint32_t ui32RetVal = ADCn(ui32Module)->INTSTAT;
        *pui32Status = ADCn(ui32Module)->INTEN & ui32RetVal;
    }
    else
    {
        *pui32Status = ADCn(ui32Module)->INTSTAT;
    }
#else // AM_CMSIS_REGS
    if ( bEnabledOnly )
    {
        uint32_t ui32RetVal = AM_REGn(ADC, ui32Module, INTSTAT);
        *pui32Status = ui32RetVal & AM_REGn(ADC, ui32Module, INTEN);
    }
    else
    {
        *pui32Status = AM_REGn(ADC, ui32Module, INTSTAT);
    }
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}


//*****************************************************************************
//
//! @brief ADC interrupt clear
//!
//! @param handle         - handle for the interface.
//! @param ui32IntMask    - uint32_t for interrupts to clear
//!
//! This function clears the interrupts for the given peripheral.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_interrupt_clear(void *pHandle, uint32_t ui32IntMask)
{
    uint32_t    ui32Module = ((am_hal_adc_state_t*)pHandle)->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    //
    // Clear the interrupts.
    //
#if AM_CMSIS_REGS
    ADCn(ui32Module)->INTCLR = ui32IntMask;
#else // AM_CMSIS_REGS
    AM_REGn(ADC, ui32Module, INTCLR) = ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC sample read function
//!
//! @param pHandle              - handle for the module instance.
//! @param ui32SlotNumber       - desired slot number to filter samples on.
//!                               If set to AM_HAL_ADC_MAX_SLOTS then all
//!                               values will be provided.
//! @param ui32BufferSize       - number of entries in the sample buffer.
//!                               If 0 then samples will be read directly
//!                               from the FIFO.
//! @param pui32SampleBuffer    - pointer to the input sample buffer.
//! @param pui32NumberSamples   - returns the number of samples found.
//! @param pui32Samples         - pointer to a sample buffer to process.
//!                               If NULL then samples will be read directly
//!                               from the FIFO.
//!
//!
//! This function reads samples from the ADC FIFO or an SRAM sample buffer
//! returned by a DMA operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t am_hal_adc_samples_read(void *pHandle,
                                 uint32_t *pui32InSampleBuffer,
                                 uint32_t *pui32InOutNumberSamples,
                                 am_hal_adc_sample_t *pui32OutBuffer)

{
    uint32_t      ui32Sample;
    uint32_t      ui32RequestedSamples = *pui32InOutNumberSamples;

    uint32_t ui32Module = ((am_hal_adc_state_t*)pHandle)->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Check the output sample buffer pointer.
    //
    if ( NULL == pui32OutBuffer )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }
#endif


    *pui32InOutNumberSamples = 0;

    //
    // Check if we are reading directly from FIFO or DMA SRAM buffer.
    //
    if ( NULL == pui32InSampleBuffer )
    {
        //
        // Grab a value from the ADC FIFO
        //
        do
        {
#if AM_CMSIS_REGS
            ui32Sample = ADCn(ui32Module)->FIFOPR;
#else // AM_CMSIS_REGS
            ui32Sample = AM_REGn(ADC, ui32Module, FIFOPR);
#endif // AM_CMSIS_REGS
            pui32OutBuffer->ui32Slot   = AM_HAL_ADC_FIFO_SLOT(ui32Sample);
            pui32OutBuffer->ui32Sample = AM_HAL_ADC_FIFO_SAMPLE(ui32Sample);
            pui32OutBuffer++;
            (*pui32InOutNumberSamples)++;
        } while ((AM_HAL_ADC_FIFO_COUNT(ui32Sample) > 0) &&
                 (*pui32InOutNumberSamples < ui32RequestedSamples));
    }
    else
    {
        //
        // Process the samples from the provided sample buffer
        //
        do
        {
#if AM_CMSIS_REGS
            ui32Sample = ADCn(ui32Module)->FIFOPR;
#else // AM_CMSIS_REGS
            ui32Sample = AM_REGn(ADC, ui32Module, FIFOPR);
#endif // AM_CMSIS_REGS
            pui32OutBuffer->ui32Slot   = AM_HAL_ADC_FIFO_SLOT(*pui32InSampleBuffer);
            pui32OutBuffer->ui32Sample = AM_HAL_ADC_FIFO_SAMPLE(*pui32InSampleBuffer);
            pui32InSampleBuffer++;
            pui32OutBuffer++;
            (*pui32InOutNumberSamples)++;
        } while (*pui32InOutNumberSamples < ui32RequestedSamples);
    }

    //
    // Return FIFO valid bits.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief Issue Software Trigger to the ADC.
//!
//! @param handle   - handle for the module instance.
//!
//! This function triggers the ADC operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_sw_trigger(void *pHandle)
{
    uint32_t    ui32Module = ((am_hal_adc_state_t*)pHandle)->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    //
    // Write to the Software trigger register in the ADC.
    //
#if AM_CMSIS_REGS
    ADCn(ui32Module)->SWT = 0x37;
#else // AM_CMSIS_REGS
    AM_REGn(ADC, ui32Module, SWT) = 0x37;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief ADC power control function
//!
//! @param handle       - handle for the interface.
//! @param ePowerState  - the desired power state to move the peripheral to.
//! @param bRetainState - flag (if true) to save/restore peripheral state upon
//!                       power state change.
//!
//! This function updates the peripheral to a given power state.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_adc_power_control(void *pHandle,
                         am_hal_sysctrl_power_state_e ePowerState,
                         bool bRetainState)
{
    am_hal_adc_state_t  *pADCState = (am_hal_adc_state_t *)pHandle;
    uint32_t            ui32Module = pADCState->ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Check the handle.
    //
    if ( !AM_HAL_ADC_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    //
    // Decode the requested power state and update MSPI operation accordingly.
    //
    switch (ePowerState)
    {
        case AM_HAL_SYSCTRL_WAKE:
            if ( bRetainState  &&  !pADCState->registerState.bValid )
            {
                return AM_HAL_STATUS_INVALID_OPERATION;
            }

            //
            // Enable the ADC power domain.
            //
            am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_PERIPH_ADC);

            if ( bRetainState )
            {
#if AM_CMSIS_REGS
                ADCn(ui32Module)->SL0CFG = pADCState->registerState.regSL0CFG;
                ADCn(ui32Module)->SL1CFG = pADCState->registerState.regSL1CFG;
                ADCn(ui32Module)->SL2CFG = pADCState->registerState.regSL2CFG;
                ADCn(ui32Module)->SL3CFG = pADCState->registerState.regSL3CFG;
                ADCn(ui32Module)->SL4CFG = pADCState->registerState.regSL4CFG;
                ADCn(ui32Module)->SL5CFG = pADCState->registerState.regSL5CFG;
                ADCn(ui32Module)->SL6CFG = pADCState->registerState.regSL6CFG;
                ADCn(ui32Module)->SL7CFG = pADCState->registerState.regSL7CFG;
                ADCn(ui32Module)->WULIM  = pADCState->registerState.regWULIM;
                ADCn(ui32Module)->WLLIM  = pADCState->registerState.regWLLIM;
                ADCn(ui32Module)->INTEN  = pADCState->registerState.regINTEN;
                ADCn(ui32Module)->CFG    = pADCState->registerState.regCFG;
#else // AM_CMSIS_REGS
                AM_REGn(ADC, ui32Module, SL0CFG)    = pADCState->registerState.regSL0CFG;
                AM_REGn(ADC, ui32Module, SL1CFG)    = pADCState->registerState.regSL1CFG;
                AM_REGn(ADC, ui32Module, SL2CFG)    = pADCState->registerState.regSL2CFG;
                AM_REGn(ADC, ui32Module, SL3CFG)    = pADCState->registerState.regSL3CFG;
                AM_REGn(ADC, ui32Module, SL4CFG)    = pADCState->registerState.regSL4CFG;
                AM_REGn(ADC, ui32Module, SL5CFG)    = pADCState->registerState.regSL5CFG;
                AM_REGn(ADC, ui32Module, SL6CFG)    = pADCState->registerState.regSL6CFG;
                AM_REGn(ADC, ui32Module, SL7CFG)    = pADCState->registerState.regSL7CFG;
                AM_REGn(ADC, ui32Module, WULIM)     = pADCState->registerState.regWULIM;
                AM_REGn(ADC, ui32Module, WLLIM)     = pADCState->registerState.regWLLIM;
                AM_REGn(ADC, ui32Module, INTEN)     = pADCState->registerState.regINTEN;
                AM_REGn(ADC, ui32Module, CFG)       = pADCState->registerState.regCFG;
#endif // AM_CMSIS_REGS

                pADCState->registerState.bValid     = false;
            }
            break;

        case AM_HAL_SYSCTRL_NORMALSLEEP:
        case AM_HAL_SYSCTRL_DEEPSLEEP:
            if ( bRetainState )
            {
#if AM_CMSIS_REGS
                pADCState->registerState.regSL0CFG  = ADCn(ui32Module)->SL0CFG;
                pADCState->registerState.regSL1CFG  = ADCn(ui32Module)->SL1CFG;
                pADCState->registerState.regSL2CFG  = ADCn(ui32Module)->SL2CFG;
                pADCState->registerState.regSL3CFG  = ADCn(ui32Module)->SL3CFG;
                pADCState->registerState.regSL4CFG  = ADCn(ui32Module)->SL4CFG;
                pADCState->registerState.regSL5CFG  = ADCn(ui32Module)->SL5CFG;
                pADCState->registerState.regSL6CFG  = ADCn(ui32Module)->SL6CFG;
                pADCState->registerState.regSL7CFG  = ADCn(ui32Module)->SL7CFG;
                pADCState->registerState.regWULIM   = ADCn(ui32Module)->WULIM;
                pADCState->registerState.regWLLIM   = ADCn(ui32Module)->WLLIM;
                pADCState->registerState.regINTEN   = ADCn(ui32Module)->INTEN;
                pADCState->registerState.regCFG     = ADCn(ui32Module)->CFG;
#else // AM_CMSIS_REGS
                pADCState->registerState.regSL0CFG  = AM_REGn(ADC, ui32Module, SL0CFG);
                pADCState->registerState.regSL1CFG  = AM_REGn(ADC, ui32Module, SL1CFG);
                pADCState->registerState.regSL2CFG  = AM_REGn(ADC, ui32Module, SL2CFG);
                pADCState->registerState.regSL3CFG  = AM_REGn(ADC, ui32Module, SL3CFG);
                pADCState->registerState.regSL4CFG  = AM_REGn(ADC, ui32Module, SL4CFG);
                pADCState->registerState.regSL5CFG  = AM_REGn(ADC, ui32Module, SL5CFG);
                pADCState->registerState.regSL6CFG  = AM_REGn(ADC, ui32Module, SL6CFG);
                pADCState->registerState.regSL7CFG  = AM_REGn(ADC, ui32Module, SL7CFG);
                pADCState->registerState.regWULIM   = AM_REGn(ADC, ui32Module, WULIM);
                pADCState->registerState.regWLLIM   = AM_REGn(ADC, ui32Module, WLLIM);
                pADCState->registerState.regINTEN   = AM_REGn(ADC, ui32Module, INTEN);
                pADCState->registerState.regCFG     = AM_REGn(ADC, ui32Module, CFG);
#endif // AM_CMSIS_REGS

                pADCState->registerState.bValid     = true;
            }

            //
            // Disable the ADC power domain.
            //
            am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_ADC);
            break;

        default:
            return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
