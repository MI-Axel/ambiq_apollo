//*****************************************************************************
//
//! @file am_hal_ble.c
//!
//! @brief HAL functions for the BLE interface.
//!
//! @addtogroup
//! @ingroup
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
#include <string.h>
#include "am_mcu_apollo.h"
#include "am_hal_ble_patch.h"

//*****************************************************************************
//
// Globals
//
//*****************************************************************************
am_hal_ble_state_t g_sBLEState[AM_REG_BLEIF_NUM_MODULES];

//*****************************************************************************
//
// SPI "options"
//
// These values affect the behavior of the BLE HAL in regards to the SPI bus,
// but end users aren't likely to need to modify them. They are collected here
// for testing and debugging purposes.
//
//*****************************************************************************
// The amount of extra delay to add between successive SPI TX packets (in
// microseconds).
#define AM_BLE_TX_PACKET_SPACING_US     1

// The BLE core takes a little while to wake up from a fresh boot, which means
// that the patch_apply function might time-out on the first few tries. Set
// this variable to let it try again for a finite number of trials.
#define AM_BLE_NUM_PATCH_TRIALS         5000

// Patch complete can also take some time.
#define AM_BLE_NUM_PATCH_CMP_TRIALS     5000

// How long the MCU should wait for SPI_STATUS before assuming the BLE core is
// busy (measured in 10 us increments).
#define AM_BLE_STATUS_TIMEOUT           300

//*****************************************************************************
//
// Private types.
//
//*****************************************************************************
#define AM_HAL_MAGIC_BLE        0x775230

#define AM_HAL_BLE_CHK_HANDLE(h)                                              \
    ((h) && ((am_hal_handle_prefix_t *)(h))->s.bInit                          \
     && (((am_hal_handle_prefix_t *)(h))->s.magic == AM_HAL_MAGIC_BLE))

//*****************************************************************************
//
// BLE Core maximum patch packet size.
//
// Specified as part of the protocol.
//
//*****************************************************************************
#define MAX_PATCH_PACKET_LEN    0x80

//*****************************************************************************
//
// Static function prototypes.
//
//*****************************************************************************
static bool am_hal_ble_lock_and_check_status(am_hal_ble_state_t *pBle);
static bool am_hal_ble_bus_lock(am_hal_ble_state_t *pBle);
static void am_hal_ble_bus_release(am_hal_ble_state_t *pBle);
#if 0
static void am_hal_ble_fifo_write(void *pHandle, uint32_t *pui32Data, uint32_t ui32NumBytes);
static uint32_t am_hal_ble_fifo_fill(void *pHandle);
#endif
static uint32_t am_hal_ble_fifo_drain(void *pHandle);
static void am_hal_ble_fifo_read(void *pHandle, uint32_t *pui32Data, uint32_t ui32NumBytes);
static bool am_hal_ble_check_status(am_hal_ble_state_t *pBle);
static bool am_hal_ble_check_status_edge(am_hal_ble_state_t *pBle);
static void am_hal_ble_wakeup_set(am_hal_ble_state_t *pBle, uint32_t ui32Mode);
static uint32_t am_hal_ble_cmd_write(void *pHandle, am_hal_ble_transfer_t *psTransfer);
static uint32_t am_hal_ble_plf_reg_read(void *pHandle, uint32_t ui32Address, uint32_t *pui32Value);
static uint32_t am_hal_ble_plf_reg_write(void *pHandle, uint32_t ui32Address, uint32_t pui32Value);

// LOOK UP TABLE for NZ CRC16 generation
static const uint16_t ccitt_table[] = {
    0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
    0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
    0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
    0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
    0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
    0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
    0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
    0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
    0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
    0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
    0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
    0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
    0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
    0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
    0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
    0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
    0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
    0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
    0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
    0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
    0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
    0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
    0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
    0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
    0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
    0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
    0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
    0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
    0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
    0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
    0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
    0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
};

//*****************************************************************************
//
// Helper macros for delays.
//
//*****************************************************************************
#define delay_ms(ms)        am_hal_flash_delay(FLASH_CYCLES_US(1000 * (ms)))
#define delay_us(us)        am_hal_flash_delay(FLASH_CYCLES_US(us))

#define WHILE_TIMEOUT_MS(expr, timeout, error)                                \
    {                                                                         \
        uint32_t ui32Timeout = 0;                                             \
        while (expr)                                                          \
        {                                                                     \
            if (ui32Timeout == (timeout * 1000))                              \
            {                                                                 \
                return error;                                                 \
            }                                                                 \
                                                                              \
            delay_us(1);                                                      \
            ui32Timeout++;                                                    \
        }                                                                     \
    }

//*****************************************************************************
//
// Helper function for checking BLE data.
//
//*****************************************************************************
static bool
buffer_compare(void *b1, void *b2, uint32_t len)
{
    uint8_t *p1 = b1;
    uint8_t *p2 = b2;

    for (uint32_t i = 0; i < len; i++)
    {
        if (p1[i] != p2[i])
        {
            return false;
        }
    }

    return true;
}

//*****************************************************************************
//
// Helper function for CRC caculation of BLE patch.
//
//*****************************************************************************
static uint16_t am_hal_ble_crc_nz(uint8_t *pui8Data, uint32_t len)
{
    uint16_t ui16CurValue = 0;
    uint32_t i;

    for (i = 0; i < len; i++) {
        ui16CurValue = ccitt_table[(((uint8_t)(ui16CurValue >> 8)) ^ pui8Data[i]) & 0xFF] ^ (ui16CurValue << 8);
    }

    return ((ui16CurValue ^ 0) & ((1 << 16) - 1));
}

//*****************************************************************************
//
// Default options for the BLE module.
//
//*****************************************************************************
const am_hal_ble_config_t am_hal_ble_default_config =
{
    // Clock divider of 8.
#if AM_CMSIS_REGS
    (_VAL2FLD(BLEIF_CLKCFG_FSEL, BLEIF_CLKCFG_FSEL_HFRC_DIV8)   |
     _VAL2FLD(BLEIF_CLKCFG_IOCLKEN, 1)                          |
     _VAL2FLD(BLEIF_CLKCFG_CLK32KEN, 1)),
#else // AM_CMSIS_REGS
    (AM_REG_BLEIF_CLKCFG_FSEL_HFRC_DIV8 |
     AM_REG_BLEIF_CLKCFG_IOCLKEN(1) |
     AM_REG_BLEIF_CLKCFG_CLK32KEN(1)),
#endif // AM_CMSIS_REGS

    // Read threshold of 16.
    0x20,

    // Write threshold of 16.
    0x20,
};

//*****************************************************************************
//
// Function for controlling the WAKE signal.
//
//*****************************************************************************
static void
am_hal_ble_wakeup_set(am_hal_ble_state_t *pBle, uint32_t ui32Mode)
{
//    am_hal_debug_gpio_set(BLE_DEBUG_TRACE_08);

#if AM_CMSIS_REGS
    uint32_t ui32Module = 0;
    if ( ui32Mode )
    {
        BLEIFn(ui32Module)->BLECFG_b.WAKEUPCTL = BLEIF_BLECFG_WAKEUPCTL_ON;
        am_hal_debug_gpio_set(BLE_DEBUG_TRACE_08);
    }
    else
    {
#ifndef AM_DISABLE_BLE_SLEEP
        BLEIFn(ui32Module)->BLECFG_b.WAKEUPCTL = BLEIF_BLECFG_WAKEUPCTL_OFF;
        am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_08);
#endif
    }
#else // AM_CMSIS_REGS
    if ( ui32Mode )
    {
        AM_BFWen(BLEIF, pBle->ui32Module, BLECFG, WAKEUPCTL, ON);
    }
    else
    {
#ifndef AM_DISABLE_BLE_SLEEP
        AM_BFWen(BLEIF, pBle->ui32Module, BLECFG, WAKEUPCTL, OFF);
#endif
    }
#endif // AM_CMSIS_REGS

//    am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_08);
}

//*****************************************************************************
//
// Buffer for patch data.
//
//*****************************************************************************
am_hal_ble_buffer(128 + 4) g_psPatchBuffer;

//*****************************************************************************
//
// Initialize the global variables associated with a BLE module, and return its
// handle.
//
//*****************************************************************************
uint32_t
am_hal_ble_initialize(uint32_t ui32Module, void **ppHandle)
{
    //
    // Check the arguments.
    //
    if (ui32Module >= AM_REG_BLEIF_NUM_MODULES)
    {
        return AM_HAL_STATUS_OUT_OF_RANGE;
    }

    if (!ppHandle)
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Check if the handle is unallocated.
    //
    if (g_sBLEState[ui32Module].prefix.s.bInit)
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }

    //
    // Initialize the handle.
    //
    memset(&g_sBLEState[ui32Module].sCurrentTransfer, 0, sizeof(am_hal_ble_transfer_t));
    memset(&g_sBLEState[ui32Module].sSavedTransfer, 0, sizeof(am_hal_ble_transfer_t));

    g_sBLEState[ui32Module].prefix.s.bInit = true;
    g_sBLEState[ui32Module].prefix.s.magic = AM_HAL_MAGIC_BLE;
    g_sBLEState[ui32Module].ui32Module = ui32Module;
    g_sBLEState[ui32Module].ui32TransferIndex = 0;
    g_sBLEState[ui32Module].bPatchComplete = 0;
    g_sBLEState[ui32Module].bContinuePacket = 0;
    g_sBLEState[ui32Module].bSavedPacket = 0;
    g_sBLEState[ui32Module].bBusy = 0;
    g_sBLEState[ui32Module].bCmdComplete = 0;
    g_sBLEState[ui32Module].bDmaComplete = 0;

    //
    // Pass the handle back to the caller.
    //
    *ppHandle = &g_sBLEState[ui32Module];

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Initialize the global variables associated with a BLE module, and return its
// handle.
//
//*****************************************************************************
uint32_t
am_hal_ble_deinitialize(void *pHandle)
{
    am_hal_ble_state_t *pBLE = (am_hal_ble_state_t *)pHandle;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Initialize the handle.
    //
    memset(&(pBLE->sCurrentTransfer), 0, sizeof(am_hal_ble_transfer_t));

    pBLE->prefix.s.bInit = false;
    pBLE->prefix.s.magic = 0;
    pBLE->ui32Module = 0;
    pBLE->ui32TransferIndex = 0;
    pBLE->bPatchComplete = 0;
    pBLE->bContinuePacket = 0;
    pBLE->bSavedPacket = 0;
    pBLE->bBusy = 0;
    pBLE->bCmdComplete = 0;
    pBLE->bDmaComplete = 0;

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Configuration function.
//
//*****************************************************************************
uint32_t
am_hal_ble_config(void *pHandle, const am_hal_ble_config_t *psConfig)
{
    uint32_t ui32Module;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

    //
    // Configure the SPI.
    //
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->MSPICFG = 0x3;
    BLEIFn(ui32Module)->MSPICFG_b.RDFC = 0;
    BLEIFn(ui32Module)->MSPICFG_b.WTFC = 0;
    BLEIFn(ui32Module)->MSPICFG_b.WTFCPOL = 1;
    BLEIFn(ui32Module)->FIFOTHR_b.FIFOWTHR = psConfig->ui32WriteThreshold;
    BLEIFn(ui32Module)->FIFOTHR_b.FIFORTHR = psConfig->ui32ReadThreshold;
    BLEIFn(ui32Module)->FIFOCTRL |= BLEIF_FIFOCTRL_POPWR_Msk;
    BLEIFn(ui32Module)->CLKCFG = psConfig->ui32ClkCfg;
#else // AM_CMSIS_REGS
    AM_REGn(BLEIF, ui32Module, MSPICFG) = 0x3;
    AM_BFWn(BLEIF, ui32Module, MSPICFG, RDFC, 0);
    AM_BFWn(BLEIF, ui32Module, MSPICFG, WTFC, 0);
    AM_BFWn(BLEIF, ui32Module, MSPICFG, WTFCPOL, 1);
    AM_BFWn(BLEIF, ui32Module, FIFOTHR, FIFOWTHR, psConfig->ui32WriteThreshold);
    AM_BFWn(BLEIF, ui32Module, FIFOTHR, FIFORTHR, psConfig->ui32ReadThreshold);
    AM_REGn(BLEIF, ui32Module, FIFOCTRL) |= AM_REG_BLEIF_FIFOCTRL_POPWR_M;
    AM_REGn(BLEIF, ui32Module, CLKCFG) = psConfig->ui32ClkCfg;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Enable BLE
//
//*****************************************************************************
uint32_t
am_hal_ble_power_control(void *pHandle, uint32_t ui32PowerState)
{
    uint32_t ui32Module;

    //
    // Enable the BLE buck trim values
    //
#if AM_CMSIS_REGS
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
#else // AM_CMSIS_REGS
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
#endif // AM_CMSIS_REGS

    //
    // Check the handle.
    //
    if ( !AM_HAL_BLE_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

#if AM_CMSIS_REGS
    if (ui32PowerState == AM_HAL_BLE_POWER_ACTIVE)
    {
        //
        // Don't run this initialization if the BLE is already enabled.
        //
        if ( PWRCTRL->DEVPWRSTATUS_b.BLEL == 0)
        {
            MCUCTRL->FEATUREENABLE = 1;
            WHILE_TIMEOUT_MS ( ((MCUCTRL->FEATUREENABLE & 0x7) != 0x7), 100,
                               AM_HAL_BLE_FEATURE_DISABLED );

            //
            // Enable the BLE module.
            //
            if (am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_PERIPH_BLEL) !=
                AM_HAL_STATUS_SUCCESS)
            {
                return AM_HAL_BLE_REGULATOR_FAILED;
            }

            //
            // Release the BLE module RESET, start the "power state machine", and
            // enable the clocks.
            //
            BLEIFn(ui32Module)->CLKCFG = _VAL2FLD(BLEIF_CLKCFG_CLK32KEN, 1);
            BLEIFn(ui32Module)->BLEDBG_b.DBGDATA = 1 << 14;

            //
            // The reset bit is different between A0 and A1.
            //
            if ( APOLLO3_A1 )
            {
                AM_REGVAL(0x40020198) = 0x1 << 5;
            }
            else
            {
                AM_REGVAL(0x40020198) = 0x1 << 2;
            }

            delay_ms(5);
            BLEIFn(ui32Module)->BLECFG_b.PWRSMEN = 1;

            //
            // Wait for indication that the power is on.
            //
            WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->BSTATUS_b.PWRST != 3, 1000,
                               AM_HAL_BLE_POWERUP_INCOMPLETE );
        }
    }
    else if (ui32PowerState == AM_HAL_BLE_POWER_OFF)
    {
        //
        // Reverse of power-up. Disable clocks, set reset, then disable power.
        //
        BLEIFn(ui32Module)->CLKCFG = 0;
        BLEIF->BLEDBG_b.DBGDATA = 0;

        if ( APOLLO3_A1 )
        {
            AM_REGVAL(0x40020198) &= ~(0x1 << 5);
        }
        else
        {
            AM_REGVAL(0x40020198) &= ~(0x1 << 2);
        }

        BLEIF->BLECFG_b.PWRSMEN = 0;

        if (am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_BLEL) !=
            AM_HAL_STATUS_SUCCESS)
        {
            return AM_HAL_BLE_SHUTDOWN_FAILED;
        }

        delay_us(100);
    }
    else
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#else // AM_CMSIS_REGS
    if (ui32PowerState == AM_HAL_BLE_POWER_ACTIVE)
    {
        //
        // Don't run this initialization if the BLE is already enabled.
        //
        if (AM_BFR(PWRCTRL, DEVPWRSTATUS, BLEL) == 0)
        {
            AM_REG(MCUCTRL, FEATUREENABLE) = 1;
            WHILE_TIMEOUT_MS ((AM_REG(MCUCTRL, FEATUREENABLE) & 0x7) != 0x7, 1,
                              AM_HAL_BLE_FEATURE_DISABLED);

            //
            // Enable the BLE module.
            //
            if (am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_PERIPH_BLEL) !=
                AM_HAL_STATUS_SUCCESS)
            {
                return AM_HAL_BLE_REGULATOR_FAILED;
            }

            //
            // Release the BLE module RESET, start the "power state machine", and
            // enable the clocks.
            //
            AM_REG(BLEIF, CLKCFG) = AM_REG_BLEIF_CLKCFG_CLK32KEN(1);
            AM_BFW(BLEIF, BLEDBG, DBGDATA, 1 << 14);

            //
            // Reset the BLE
            // The reset bit is different between A0 and A1.
            //
            if ( APOLLO3_A1 )
            {
                AM_BFWa(MCUCTRL, MISCCTRL, BLE_RESETN, 1);
            }
            else
            {
                AM_CRITICAL_BEGIN
                AM_REGVAL(0x40020198) |= 0x1 << 2;
                AM_CRITICAL_END
            }

            delay_ms(5);
            AM_BFW(BLEIF, BLECFG, PWRSMEN, 1);

            //
            // Wait for indication that the power is on.
            //
            WHILE_TIMEOUT_MS (AM_BFR(BLEIF, BSTATUS, PWRST) != 3, 1000,
                              AM_HAL_BLE_POWERUP_INCOMPLETE);

            delay_ms(100);
        }
    }
    else if (ui32PowerState == AM_HAL_BLE_POWER_OFF)
    {
        AM_REGn(BLEIF, ui32Module, CLKCFG) = 0;
        AM_BFW(BLEIF, BLEDBG, DBGDATA, 0);

        //
        // Reverse of power-up. Disable clocks, set reset, then disable power.
        //
        if ( APOLLO3_A1 )
        {
            AM_REGVAL(0x40020198) &= ~(0x1 << 5);
        }
        else
        {
            AM_CRITICAL_BEGIN
            AM_REGVAL(0x40020198) &= ~(0x1 << 2);
            AM_CRITICAL_END
        }

        AM_BFW(BLEIF, BLECFG, PWRSMEN, 0);

        if (am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_BLEL) !=
            AM_HAL_STATUS_SUCCESS)
        {
            return AM_HAL_BLE_SHUTDOWN_FAILED;
        }

        delay_us(100);
    }
    else
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Apply a patch.
//
// Returns 0 for success or a numerical error code for failures.
//
//*****************************************************************************
uint32_t
am_hal_ble_patch_apply(void *pHandle, am_hal_ble_patch_t *psPatch)
{
    uint8_t pui8ExpectedResponse[32];
    uint32_t ui32ErrorStatus;
    uint32_t ui32Trial;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    uint32_t ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;
    am_hal_ble_transfer_t sTransfer;
    am_hal_ble_buffer(16) psPatchBuffer;

    //
    // Send a header packet.
    //
    psPatchBuffer.bytes[0] = 0x01;
    psPatchBuffer.bytes[1] = psPatch->ui32Type;
    psPatchBuffer.bytes[2] = 0xF1;
    psPatchBuffer.bytes[3] = 0x02;
    psPatchBuffer.bytes[4] = (psPatch->ui32Length & 0xFF);
    psPatchBuffer.bytes[5] = ((psPatch->ui32Length >> 8) & 0xFF);

    //
    // This first packet might take a few tries.
    //
    for ( ui32Trial = 0; ui32Trial < AM_BLE_NUM_PATCH_TRIALS; ui32Trial++)
    {
        ui32ErrorStatus = am_hal_ble_blocking_hci_write(pHandle,
                                                        AM_HAL_BLE_RAW,
                                                        psPatchBuffer.words,
                                                        6);

        if ( ui32ErrorStatus == AM_HAL_STATUS_SUCCESS )
        {
            break;
        }
    }

    if (ui32ErrorStatus != AM_HAL_STATUS_SUCCESS)
    {
        return ui32ErrorStatus;
    }

    //
    // Wait for the header response. It should be 5 bytes long.
    //
#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 1000,
                       AM_HAL_BLE_NO_HCI_RESPONSE );

#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS( AM_BFMn(BLEIF, ui32Module, BSTATUS, BLEIRQ) == 0, 1000,
                      AM_HAL_BLE_NO_HCI_RESPONSE );
#endif // AM_CMSIS_REGS

    memset(&sTransfer, 0, sizeof(am_hal_ble_transfer_t));
    sTransfer.ui8Command = AM_HAL_BLE_READ;
    sTransfer.pui32Data = psPatchBuffer.words;
    sTransfer.ui16Length = 5;

    ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
    if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS )
    {
        return ui32ErrorStatus;
    }

    pui8ExpectedResponse[0] = 0x04;
    pui8ExpectedResponse[1] = psPatch->ui32Type;
    pui8ExpectedResponse[2] = 0xF1;
    pui8ExpectedResponse[3] = 0x01;
    pui8ExpectedResponse[4] = 0x00;

    if (!buffer_compare(psPatchBuffer.words, pui8ExpectedResponse, 5))
    {
        return AM_HAL_STATUS_FAIL;
    }

    //
    // Send all of the data, including the acknowledgements.
    //
    uint32_t ui32RemainingBytes = psPatch->ui32Length;
    uint32_t ui32Index = 0;

    while (ui32RemainingBytes)
    {
        //
        // Figure out how many bytes to send in the next packet.
        //
        uint32_t ui32TransferSize = (ui32RemainingBytes > MAX_PATCH_PACKET_LEN ?
                                     MAX_PATCH_PACKET_LEN : ui32RemainingBytes);

        //
        // Send a data header.
        //
        memset(&sTransfer, 0, sizeof(am_hal_ble_transfer_t));
        sTransfer.ui8Command = AM_HAL_BLE_WRITE;
        sTransfer.pui32Data = g_psPatchBuffer.words;
        sTransfer.ui16Length = ui32TransferSize + 4;
        sTransfer.bContinue = false;

        g_psPatchBuffer.bytes[0] = 0x01;
        g_psPatchBuffer.bytes[1] = psPatch->ui32Type;
        g_psPatchBuffer.bytes[2] = 0xF2;
        g_psPatchBuffer.bytes[3] = ui32TransferSize;

        // copy data into buffer
        memcpy(&g_psPatchBuffer.bytes[4], (uint8_t *)&(psPatch->pui32Data[ui32Index / 4]), ui32TransferSize);

        ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
        if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS )
        {
            return ui32ErrorStatus;
        }

        //
        // Read the acknowledgement.
        //
#if AM_CMSIS_REGS
        WHILE_TIMEOUT_MS( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 1000,
                          AM_HAL_BLE_NO_HCI_RESPONSE);
#else // AM_CMSIS_REGS
        WHILE_TIMEOUT_MS( AM_BFMn(BLEIF, ui32Module, BSTATUS, BLEIRQ) == 0, 1000,
                          AM_HAL_BLE_NO_HCI_RESPONSE);
#endif // AM_CMSIS_REGS

        memset(&sTransfer, 0, sizeof(am_hal_ble_transfer_t));
        sTransfer.ui8Command = AM_HAL_BLE_READ;
        sTransfer.pui32Data = psPatchBuffer.words;
        sTransfer.ui16Length = 5;

        ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
        if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS )
        {
            return ui32ErrorStatus;
        }

        pui8ExpectedResponse[0] = 0x04;
        pui8ExpectedResponse[1] = psPatch->ui32Type;
        pui8ExpectedResponse[2] = 0xF2;
        pui8ExpectedResponse[3] = 0x01;
        pui8ExpectedResponse[4] = 0x00;

        if (!buffer_compare(psPatchBuffer.words, pui8ExpectedResponse, 5))
        {
            return AM_HAL_STATUS_FAIL;
        }

        //
        // Update the tracking variables
        //
        ui32RemainingBytes -= ui32TransferSize;
        ui32Index += ui32TransferSize;
    }

    //
    // Send the CRC, and make sure we got it right.
    //
    psPatchBuffer.bytes[0] = 0x01;
    psPatchBuffer.bytes[1] = psPatch->ui32Type;
    psPatchBuffer.bytes[2] = 0xF3;
    psPatchBuffer.bytes[3] = 0x02;
    psPatchBuffer.bytes[4] = (psPatch->ui32CRC & 0xFF);
    psPatchBuffer.bytes[5] = ((psPatch->ui32CRC >> 8) & 0xFF);

    if (am_hal_ble_blocking_hci_write(pHandle, AM_HAL_BLE_RAW, psPatchBuffer.words, 6) !=
        AM_HAL_STATUS_SUCCESS)
    {
        return AM_HAL_STATUS_FAIL;
    }

    //
    // Wait for the header response. It should be 5 bytes long.
    //
#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 1000,
                      AM_HAL_BLE_NO_HCI_RESPONSE );
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS( AM_BFMn(BLEIF, ui32Module, BSTATUS, BLEIRQ) == 0, 1000,
                      AM_HAL_BLE_NO_HCI_RESPONSE );
#endif // AM_CMSIS_REGS

    memset(&sTransfer, 0, sizeof(am_hal_ble_transfer_t));
    sTransfer.ui8Command = AM_HAL_BLE_READ;
    sTransfer.pui32Data = psPatchBuffer.words;
    sTransfer.ui16Length = 5;

    ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
    if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS )
    {
        return ui32ErrorStatus;
    }

    pui8ExpectedResponse[0] = 0x04;
    pui8ExpectedResponse[1] = psPatch->ui32Type;
    pui8ExpectedResponse[2] = 0xF3;
    pui8ExpectedResponse[3] = 0x01;
    pui8ExpectedResponse[4] = 0x00;

    if (!buffer_compare(psPatchBuffer.words, pui8ExpectedResponse, 5))
    {
        return AM_HAL_STATUS_FAIL;
    }
    else
    {
        return AM_HAL_STATUS_SUCCESS;
    }
}


uint32_t
am_hal_ble_patch_copy_end_apply(void *pHandle)
{
	uint8_t pui8ExpectedResponse[32];
    uint32_t ui32ErrorStatus;
    uint32_t ui32Trial;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    uint32_t ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;
    am_hal_ble_transfer_t sTransfer;
    am_hal_ble_buffer(16) psPatchBuffer;

    //
    // Send a header packet.
    //
    psPatchBuffer.bytes[0] = 0x01;
    psPatchBuffer.bytes[1] = 0xEE;
    psPatchBuffer.bytes[2] = 0xF1;
    psPatchBuffer.bytes[3] = 0x02;
    psPatchBuffer.bytes[4] = 0x00;
    psPatchBuffer.bytes[5] = 0x00;

    //
    // This first packet might take a few tries.
    //
    for ( ui32Trial = 0; ui32Trial < AM_BLE_NUM_PATCH_TRIALS; ui32Trial++)
    {
        ui32ErrorStatus = am_hal_ble_blocking_hci_write(pHandle,
                                                        AM_HAL_BLE_RAW,
                                                        psPatchBuffer.words,
                                                        6);

        if ( ui32ErrorStatus == AM_HAL_STATUS_SUCCESS )
        {
			
            break;
        }
    }

    if (ui32ErrorStatus != AM_HAL_STATUS_SUCCESS)
    {
		 
        return ui32ErrorStatus;
    }

    //
    // Wait for the header response. It should be 5 bytes long.
    //
#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 1000, AM_HAL_BLE_NO_HCI_RESPONSE);
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS(AM_BFMn(BLEIF, ui32Module, BSTATUS, BLEIRQ) == 0, 1000, AM_HAL_BLE_NO_HCI_RESPONSE);
#endif // AM_CMSIS_REGS
     
    memset(&sTransfer, 0, sizeof(am_hal_ble_transfer_t));
    sTransfer.ui8Command = AM_HAL_BLE_READ;
    sTransfer.pui32Data = psPatchBuffer.words;
    sTransfer.ui16Length = 5;

    ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
    if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS )
    {
		 
        return ui32ErrorStatus;
    }
     
    pui8ExpectedResponse[0] = 0x04;
    pui8ExpectedResponse[1] = 0xEE;
    pui8ExpectedResponse[2] = 0xF1;
    pui8ExpectedResponse[3] = 0x01;
    pui8ExpectedResponse[4] = 0x00;
     
    if (!buffer_compare(psPatchBuffer.words, pui8ExpectedResponse, 5))
    {
		 
        return AM_HAL_STATUS_FAIL;
    }
	return 0;	
}

//*****************************************************************************
//
// Apply the default copy patch.
//
// Returns 0 for success or a numerical error code for failures.
//
//*****************************************************************************
uint32_t
am_hal_ble_default_copy_patch_apply(void *pHandle)
{
    uint32_t ui32Status, i = 0;
    uint16_t ui16Crc;
		 
    ui16Crc = am_hal_ble_crc_nz((uint8_t*)(am_hal_ble_default_copy_patches[0]->pui32Data), am_hal_ble_default_copy_patches[0]->ui32Length);        
    am_hal_ble_default_copy_patches[i]->ui32CRC = ui16Crc;
    ui32Status = am_hal_ble_patch_apply(pHandle, am_hal_ble_default_copy_patches[0]);
    if (ui32Status != AM_HAL_STATUS_SUCCESS)
    {
        return ui32Status;
    }
		
	ui32Status = am_hal_ble_patch_copy_end_apply(pHandle);
	if (ui32Status != AM_HAL_STATUS_SUCCESS)
    {
        return ui32Status;
    }

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Apply the default patch.
//
// Returns 0 for success or a numerical error code for failures.
//
//*****************************************************************************
uint32_t
am_hal_ble_default_patch_apply(void *pHandle)
{
    uint32_t ui32Status, i = 0;
    uint16_t ui16Crc;

    for ( i = 0; i < am_hal_ble_num_default_patches; i++ )
    {
        ui16Crc = am_hal_ble_crc_nz((uint8_t*)(am_hal_ble_default_patches[i]->pui32Data), am_hal_ble_default_patches[i]->ui32Length);
        am_hal_ble_default_patches[i]->ui32CRC = ui16Crc;
        ui32Status = am_hal_ble_patch_apply(pHandle, am_hal_ble_default_patches[i]);
        if (ui32Status != AM_HAL_STATUS_SUCCESS)
        {
            return ui32Status;
        }
    }

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Complete the patching process
//
//*****************************************************************************
uint32_t
am_hal_ble_patch_complete(void *pHandle)
{
    uint32_t ui32ErrorStatus;
    am_hal_ble_transfer_t sTransfer;
    am_hal_ble_buffer(12) sTxBuffer;
    am_hal_ble_buffer(12) sRxBuffer;
    uint32_t ui32Trial;

    am_hal_ble_state_t *pBLE = pHandle;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

#if AM_CMSIS_REGS
    uint32_t ui32Module = pBLE->ui32Module;
#else // AM_CMSIS_REGS
#endif // AM_CMSIS_REGS

    //
    // Write the "patch complete" command.
    //
    memset(&sTransfer, 0, sizeof(am_hal_ble_transfer_t));
    sTransfer.ui8Command = AM_HAL_BLE_WRITE;
    sTransfer.pui32Data = sTxBuffer.words;
    sTransfer.ui16Length = 6;

    sTxBuffer.bytes[0] = 0x01;
    sTxBuffer.bytes[1] = 0xEE;
    sTxBuffer.bytes[2] = 0xF1;
    sTxBuffer.bytes[3] = 0x02;
    sTxBuffer.bytes[4] = 0x00;
    sTxBuffer.bytes[5] = 0x00;

    for ( ui32Trial = 0; ui32Trial < AM_BLE_NUM_PATCH_CMP_TRIALS; ui32Trial++)
    {
        ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
        if ( ui32ErrorStatus == AM_HAL_STATUS_SUCCESS )
        {
            break;
        }
    }

#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 10,
                       AM_HAL_BLE_NO_HCI_RESPONSE );
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS (AM_BFM(BLEIF, BSTATUS, BLEIRQ) == 0, 10,
                       AM_HAL_BLE_NO_HCI_RESPONSE);
#endif //AM_CMSIS_REGS

    //
    // Read back the response.
    //
    sTransfer.ui8Command = AM_HAL_BLE_READ;
    sTransfer.pui32Data = sRxBuffer.words;
    sTransfer.ui16Length = 2;
    ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
    if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS )
    {
        return ui32ErrorStatus;
    }

    //
    // Check to see which format the response came back in. If it doesn't have
    // a 2-byte length header, we need to manually override the length, and
    // continue on to adjust the HCI format in the next packet. Otherwise, we
    // can just return from here.
    //
    if ( sRxBuffer.bytes[1] == 0xEE )
    {
        sTransfer.ui16Length = 3;
        ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
        if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS )
        {
            return ui32ErrorStatus;
        }
    }
    else
    {
        sTransfer.ui16Length = (sRxBuffer.bytes[0] + (sRxBuffer.bytes[1] << 8));
        ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
        if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS )
        {
            return ui32ErrorStatus;
        }

        //
        // Make sure to remember that we've sent the "patch complete" packet.
        //
        pBLE->bPatchComplete = true;

        return AM_HAL_STATUS_SUCCESS;
    }

    //
    // If we made it here, we need to tell the radio that we need two-byte
    // headers prepended to each HCI packet it sends us.
    //
    memset(&sTransfer, 0, sizeof(am_hal_ble_transfer_t));
    sTransfer.ui8Command = AM_HAL_BLE_WRITE;
    sTransfer.pui32Data = sTxBuffer.words;
    sTransfer.ui16Length = 5;

    sTxBuffer.bytes[0] = 0x01;
    sTxBuffer.bytes[1] = 0x04;
    sTxBuffer.bytes[2] = 0xFD;
    sTxBuffer.bytes[3] = 0x01;
    sTxBuffer.bytes[4] = 0x01;

    for ( ui32Trial = 0; ui32Trial < AM_BLE_NUM_PATCH_CMP_TRIALS; ui32Trial++)
    {
        ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
        if ( ui32ErrorStatus == AM_HAL_STATUS_SUCCESS )
        {
            break;
        }
    }

    if (ui32ErrorStatus != AM_HAL_STATUS_SUCCESS)
    {
        return ui32ErrorStatus;
    }

#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 10,
                       AM_HAL_BLE_NO_HCI_RESPONSE );
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS (AM_BFM(BLEIF, BSTATUS, BLEIRQ) == 0, 10,
                      AM_HAL_BLE_NO_HCI_RESPONSE);
#endif //AM_CMSIS_REGS

    sTransfer.ui8Command = AM_HAL_BLE_READ;
    sTransfer.pui32Data = sRxBuffer.words;
    sTransfer.ui16Length = 9;
    ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &sTransfer);
    if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS )
    {
        return ui32ErrorStatus;
    }

    //
    // Now that we're done patching, we can let the radio sleep.
    //
    am_hal_ble_wakeup_set(pBLE, 0);

    //
    // Make sure to remember that we've sent the "patch complete" packet.
    //
    pBLE->bPatchComplete = true;

    //
    // Delay to give the BLE core time to take the patch (assuming a patch was sent).
    //
    delay_ms(500);

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Read a register value from the BLE core.
//
//*****************************************************************************
uint32_t
am_hal_ble_plf_reg_read(void *pHandle, uint32_t ui32Address, uint32_t *pui32Value)
{
    am_hal_ble_state_t *pBLE = pHandle;
    uint8_t pui8Parameter[4];
    uint32_t ui32IntEnable;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    uint32_t ui32Module = pBLE->ui32Module;

    //
    // Make a buffer big enough to hold the register write command, and a
    // second one big enough to hold the response.
    //
    am_hal_ble_buffer(AM_HAL_BLE_PLF_REGISTER_READ_LENGTH) sWriteCommand;
    am_hal_ble_buffer(32) sResponse;

    //
    // Prepare our register write value.
    //
    pui8Parameter[0] = ui32Address;
    pui8Parameter[1] = (ui32Address >> 8);
    pui8Parameter[2] = (ui32Address >> 16);
    pui8Parameter[3] = (ui32Address >> 24);

    //
    // Fill the buffer with the specific command we want to write, and send it.
    //
    am_hal_ble_vs_command_build(sWriteCommand.words,
                                AM_HAL_BLE_PLF_REGISTER_READ_OPCODE,
                                AM_HAL_BLE_PLF_REGISTER_READ_LENGTH,
                                pui8Parameter);

    //
    // Temporarily disable BLE interrupts.
    //
#if AM_CMSIS_REGS
    ui32IntEnable = BLEIFn(ui32Module)->INTEN;
    BLEIFn(ui32Module)->INTEN = 0;
#else // AM_CMSIS_REGS
    ui32IntEnable = AM_REGn(BLEIF, ui32Module, INTEN);
    AM_REGn(BLEIF, ui32Module, INTEN) = 0;
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_write(pBLE,
                                  AM_HAL_BLE_RAW,
                                  sWriteCommand.words,
                                  AM_HAL_BLE_PLF_REGISTER_READ_LENGTH);

#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->BLEDBG_b.IOCLKON = 1;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, ui32Module, BLEDBG, IOCLKON, 1);
#endif // AM_CMSIS_REGS

    //
    // Wait for the response, and return it to the caller via our variable.
    //
#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 10,
                       AM_HAL_BLE_NO_HCI_RESPONSE );
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS (AM_BFM(BLEIF, BSTATUS, BLEIRQ) == 0, 10,
                      AM_HAL_BLE_NO_HCI_RESPONSE);
#endif // AM_CMSIS_REGS


    am_hal_ble_blocking_hci_read(pBLE, sResponse.words, 0);

    *pui32Value = (((sResponse.words[1] & 0xFF000000) >> 24) |
                   ((sResponse.words[2] & 0x00FFFFFF) << 8));
    //
    // Re-enable BLE interrupts.
    //
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->INTCLR = ui32IntEnable;
    BLEIFn(ui32Module)->INTEN = ui32IntEnable;
#else // AM_CMSIS_REGS
    AM_REGn(BLEIF, ui32Module, INTCLR) = ui32IntEnable;
    AM_REGn(BLEIF, ui32Module, INTEN) = ui32IntEnable;
#endif // AM_CMSIS_REGS

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Write a register value to the BLE core.
//
//*****************************************************************************
uint32_t
am_hal_ble_plf_reg_write(void *pHandle, uint32_t ui32Address, uint32_t ui32Value)
{
    am_hal_ble_state_t *pBLE = pHandle;
    uint8_t pui8Parameter[8];
    uint32_t ui32IntEnable;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    uint32_t ui32Module = pBLE->ui32Module;


    //
    // Make a buffer big enough to hold the register write command, and a
    // second one big enough to hold the response.
    //
    am_hal_ble_buffer(AM_HAL_BLE_PLF_REGISTER_WRITE_LENGTH) sWriteCommand;
    am_hal_ble_buffer(16) sResponse;

    //
    // Prepare our register write value.
    //
    pui8Parameter[0] = ui32Address;
    pui8Parameter[1] = (ui32Address >> 8);
    pui8Parameter[2] = (ui32Address >> 16);
    pui8Parameter[3] = (ui32Address >> 24);
    pui8Parameter[4] = ui32Value;
    pui8Parameter[5] = (ui32Value >> 8);
    pui8Parameter[6] = (ui32Value >> 16);
    pui8Parameter[7] = (ui32Value >> 24);

    //
    // Fill the buffer with the specific command we want to write, and send it.
    //
    am_hal_ble_vs_command_build(sWriteCommand.words,
                                AM_HAL_BLE_PLF_REGISTER_WRITE_OPCODE,
                                AM_HAL_BLE_PLF_REGISTER_WRITE_LENGTH,
                                pui8Parameter);

    //
    // Temporarily disable BLE interrupts.
    //
#if AM_CMSIS_REGS
    ui32IntEnable = BLEIFn(ui32Module)->INTEN;
    BLEIFn(ui32Module)->INTEN = 0;
#else // AM_CMSIS_REGS
    ui32IntEnable = AM_REGn(BLEIF, ui32Module, INTEN);
    AM_REGn(BLEIF, ui32Module, INTEN) = 0;
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_write(pBLE,
                                  AM_HAL_BLE_RAW,
                                  sWriteCommand.words,
                                  AM_HAL_BLE_PLF_REGISTER_WRITE_LENGTH);

#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->BLEDBG_b.IOCLKON = 1;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, ui32Module, BLEDBG, IOCLKON, 1);
#endif // AM_CMSIS_REGS

    //
    // Wait for the response.
    //
#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 10,
                       AM_HAL_BLE_NO_HCI_RESPONSE );
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS (AM_BFM(BLEIF, BSTATUS, BLEIRQ) == 0, 10,
                      AM_HAL_BLE_NO_HCI_RESPONSE );
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_read(pBLE, sResponse.words, 0);

    //
    // Re-enable BLE interrupts.
    //
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->INTCLR = ui32IntEnable;
    BLEIFn(ui32Module)->INTEN = ui32IntEnable;
#else // AM_CMSIS_REGS
    AM_REGn(BLEIF, ui32Module, INTCLR) = ui32IntEnable;
    AM_REGn(BLEIF, ui32Module, INTEN) = ui32IntEnable;
#endif // AM_CMSIS_REGS

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Set one of the trim values for the BLE core.
//
//*****************************************************************************
uint32_t
am_hal_ble_trim_set(void *pHandle, uint32_t ui32BleCoreAddress, uint32_t ui32TrimValue, uint32_t ui32TrimMask)
{
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t ui32TrimValueSwapped, ui32LockValue, ui32ReadVal, ui32WriteVal;

    ui32TrimValueSwapped = (((ui32TrimValue & 0x000000FF) << 24) |
                            ((ui32TrimValue & 0x0000FF00) << 8) |
                            ((ui32TrimValue & 0x00FF0000) >> 8) |
                            ((ui32TrimValue & 0xFF000000) >> 24));

    if (ui32TrimValue != 0xFFFFFFFF)
    {
        //
        // Unlock the BLE registers and save the "lock register" value.
        //
        am_hal_ble_plf_reg_read(pBLE, 0x43000004, &ui32LockValue);
        am_hal_ble_plf_reg_write(pBLE, 0x43000004, 0xFFFFFFFF);

        //
        // Check to see if we need a bitfield mask. If not, we can just write
        // directly.
        //
        if (ui32TrimMask == 0xFFFFFFFF)
        {
            am_hal_ble_plf_reg_write(pBLE, ui32BleCoreAddress, ui32TrimValueSwapped);
        }
        else
        {
            //
            // If we do need a mask, read the register, mask out the old bits,
            // OR in the new, and write the new value back.
            //
            am_hal_ble_plf_reg_read(pBLE, ui32BleCoreAddress, &ui32ReadVal);
            ui32WriteVal = ((ui32ReadVal & (~ui32TrimMask)) | ui32TrimValueSwapped);

            am_hal_ble_plf_reg_write(pBLE, ui32BleCoreAddress, ui32WriteVal);
        }

        //
        // Unlock the BLE register.
        //
        am_hal_ble_plf_reg_write(pBLE, 0x43000004, ui32LockValue);
    }

    return AM_HAL_STATUS_SUCCESS;
}


//*****************************************************************************
//
// Set BLE sleep enable/disable for the BLE core.
// enable = 'true' set sleep enable, enable = 'false' set sleep disable
//
//*****************************************************************************
uint32_t
am_hal_ble_sleep_set(void *pHandle, bool enable)
{
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t sleepenable=0;

    am_hal_ble_plf_reg_read(pBLE, 0x200067c4, &sleepenable);
    sleepenable &=0xffff0000;
    if(enable)
    {
        sleepenable |= 0x0101;
    }
    am_hal_ble_plf_reg_write(pBLE,0x200067c4, sleepenable);

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Get current sleep enable status
//return 'true'  = sleep enable , 'false' =  sleep disable
//*****************************************************************************
bool
am_hal_ble_sleep_get(void *pHandle)
{
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t sleepenable=0;

    am_hal_ble_plf_reg_read(pBLE, 0x200067c4, &sleepenable);
       if((sleepenable & 0xFFFF)>0)
    {
        return true;
    }

    return false;
}

//*****************************************************************************
//
// In DTM mode, set TX to constant trans mode for SRRC/FCC/CE
//set enable as 'true' to constant trans mode, 'false' back to normal
//*****************************************************************************
uint32_t
am_hal_ble_set_constant_transmission(void *pHandle, bool enable)
{
    am_hal_ble_state_t *pBLE = pHandle;

    am_hal_ble_sleep_set(pBLE, false);
    am_hal_ble_plf_reg_write(pBLE, 0x43000004, 0xFFFFFFFF);
    if(enable)
    {
        am_hal_ble_plf_reg_write(pBLE, 0x508000E0, 0x00008000);
    }else{
        am_hal_ble_plf_reg_write(pBLE, 0x508000E0, 0x00000000);
    }

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Manually enable/disable transmitter
// set ui8TxCtrl as 1 to manually enable transmitter, 0 back to default
//
//*****************************************************************************
uint32_t
am_hal_ble_transmitter_control(void *pHandle, uint8_t ui8TxCtrl)
{
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t RegValueTRX;

    am_hal_ble_sleep_set(pBLE, false);
    if (ui8TxCtrl)
    {
        RegValueTRX = 0x2000A;
    }
    else
    {
        RegValueTRX = 0x8;
    }

    //
    // Unlock the BLE registers.
    //
    am_hal_ble_plf_reg_write(pBLE, 0x43000004, 0xFFFFFFFF);
    am_hal_ble_plf_reg_write(pBLE, 0x52400000, RegValueTRX);

    return AM_HAL_STATUS_SUCCESS;
}


//*****************************************************************************
//
//to fix the channel 1 bug in DTM mode
//
//*****************************************************************************

uint32_t
am_hal_ble_init_rf_channel(void *pHandle)
{
    am_hal_ble_buffer(16) sWriteCommand;
    am_hal_ble_buffer(16) sResponse;
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t ui32IntEnable;

      //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    uint32_t ui32Module = pBLE->ui32Module;
    am_hal_ble_sleep_set(pBLE, false);

    //issue the HCI command with to init for the channel 1
    sWriteCommand.bytes[0] = 0x01;
    sWriteCommand.bytes[1] = 0x1d;
    sWriteCommand.bytes[2] = 0x20;
    sWriteCommand.bytes[3] = 0x01;
    sWriteCommand.bytes[4] = 0x00;

    //
    // Temporarily disable BLE interrupts.
    //
#if AM_CMSIS_REGS
    ui32IntEnable = BLEIFn(ui32Module)->INTEN;
    BLEIFn(ui32Module)->INTEN = 0;
#else // AM_CMSIS_REGS
    ui32IntEnable = AM_REGn(BLEIF, ui32Module, INTEN);
    AM_REGn(BLEIF, ui32Module, INTEN) = 0;
#endif // AM_CMSIS_REGS

    // reserved packet_payload
    am_hal_ble_blocking_hci_write(pBLE,
                                  AM_HAL_BLE_RAW,
                                  sWriteCommand.words,
                                  5);
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->BLEDBG_b.IOCLKON = 1;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, ui32Module, BLEDBG, IOCLKON, 1);
#endif // AM_CMSIS_REGS


    //
    // Wait for the response.
    //
#if AM_CMSIS_REGS
    while ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0 );
#else // AM_CMSIS_REGS
    while (AM_BFM(BLEIF, BSTATUS, BLEIRQ) == 0);
#endif // AM_CMSIS_REGS
    am_hal_ble_blocking_hci_read(pBLE, sResponse.words, 0);

    delay_ms(10);

  // issue the HCI command with to stop test for the channel 1
    sWriteCommand.bytes[0] = 0x01;
    sWriteCommand.bytes[1] = 0x1f;
    sWriteCommand.bytes[2] = 0x20;
    sWriteCommand.bytes[3] = 0x00;
 // reserved packet_payload
    am_hal_ble_blocking_hci_write(pBLE,
                                  AM_HAL_BLE_RAW,
                                  sWriteCommand.words,
                                  4);
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->BLEDBG_b.IOCLKON = 1;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, ui32Module, BLEDBG, IOCLKON, 1);
#endif // AM_CMSIS_REGS

    //
    // Wait for the response.
    //
#if AM_CMSIS_REGS
    while ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0 );
#else // AM_CMSIS_REGS
    while (AM_BFM(BLEIF, BSTATUS, BLEIRQ) == 0);
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_read(pBLE, sResponse.words, 0);

    //
    // Re-enable BLE interrupts.
    //
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->INTCLR = ui32IntEnable;
    BLEIFn(ui32Module)->INTEN = ui32IntEnable;
#else // AM_CMSIS_REGS
    AM_REGn(BLEIF, ui32Module, INTCLR) = ui32IntEnable;
    AM_REGn(BLEIF, ui32Module, INTEN) = ui32IntEnable;
#endif // AM_CMSIS_REGS

    return AM_HAL_STATUS_SUCCESS;
}


//*****************************************************************************
//
// BLE init for BQB test
//set enable as 'true' to init as BQB test mode, 'false' back to default
//*****************************************************************************
uint32_t
am_hal_ble_BQB_test_init(void *pHandle, bool enable)
{
    am_hal_ble_state_t *pBLE = pHandle;

    am_hal_ble_sleep_set(pBLE,false);
    am_hal_ble_plf_reg_write(pBLE, 0x43000004, 0xFFFFFFFF);

    if(enable)
    {
        am_hal_ble_plf_reg_write(pBLE,0x51800028, 0x0000209c);
    }
    else
    {
        am_hal_ble_plf_reg_write(pBLE,0x51800028, 0x00003ff6);
    }

    am_hal_ble_plf_reg_write(pBLE,0x45800070, 0x100);
    am_hal_ble_plf_reg_write(pBLE,0x45800070, 0);

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Set the bandgap voltage, bandgap current, and retention LDO output values
// based on the tested values stored in non-volatile memory.
//
//*****************************************************************************
uint32_t
am_hal_ble_default_trim_set(void *pHandle)
{
    uint32_t ui32TrimValue;

    //
    // Set the bandgap voltage and current.
    //
    ui32TrimValue = AM_REGVAL(0x50023800);
    am_hal_ble_trim_set(pHandle, 0x43C00008, ui32TrimValue, 0xFFFFFFFF);

    //
    // Set the retention LDO voltage.
    //
    ui32TrimValue = AM_REGVAL(0x50023804);
    if (ui32TrimValue != 0xFFFFFFFF) {
        // 0xFFFFFFFF means the part has not been trimed.
        ui32TrimValue += 0x40000000; // Increase the retention voltage to > 0.75v
    }
    am_hal_ble_trim_set(pHandle, 0x43C00000, ui32TrimValue, 0x1F0);

    return AM_HAL_STATUS_SUCCESS;
}

extern am_hal_ble_patch_t am_ble_performance_patch;
uint32_t
am_hal_ble_default_trim_set_ramcode(void *pHandle)
{
    uint32_t ui32TrimValue;
    uint32_t ui32TrimValueSwapped;
    uint32_t *pRamCode = (uint32_t *) (am_ble_performance_patch.pui32Data);

    //
    // Set the bandgap voltage and current.
    //
    //ui32TrimValue = (AM_REGVAL(0x50023800) | (0x0F000000)) & (0xEFFFFFFF);
    ui32TrimValue = AM_REGVAL(0x50023800);
    ui32TrimValueSwapped = (((ui32TrimValue & 0x000000FF) << 24) |
                            ((ui32TrimValue & 0x0000FF00) << 8) |
                            ((ui32TrimValue & 0x00FF0000) >> 8) |
                            ((ui32TrimValue & 0xFF000000) >> 24));

    if (ui32TrimValueSwapped != 0xFFFFFFFF)
    {
        pRamCode[2] = ui32TrimValueSwapped;
    }

    //
    // Set the retention LDO voltage.
    //
    ui32TrimValue = AM_REGVAL(0x50023804);
    if (ui32TrimValue != 0xFFFFFFFF) {
         // 0xFFFFFFFF means the part has not been trimed.
         ui32TrimValue += 0x40000000; // Increase the retention voltage to > 0.75v
    }
    ui32TrimValueSwapped = (((ui32TrimValue & 0x000000FF) << 24) |
                            ((ui32TrimValue & 0x0000FF00) << 8) |
                            ((ui32TrimValue & 0x00FF0000) >> 8) |
                            ((ui32TrimValue & 0xFF000000) >> 24));

    if ( ui32TrimValueSwapped != 0xFFFFFFFF )
    {
        pRamCode[3] = ((pRamCode[3] & (~0x1F0)) | ui32TrimValueSwapped);
    }

    return AM_HAL_STATUS_SUCCESS;
}


//*****************************************************************************
//
// Set the 32M crystal frequency
// based on the tested values at customer side.
// set trim value smaller in case of negative frequency offset
// ui32TrimValue: default is 0x400
//*****************************************************************************
uint32_t
am_hal_ble_crystal_trim_set(void *pHandle, uint32_t ui32TrimValue)
{
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t RegValueMCGR;

    ui32TrimValue &= 0x7FF;

    am_hal_ble_plf_reg_read(pBLE, 0x43000004, &RegValueMCGR);
    //
    // Unlock the BLE registers.
    //
    am_hal_ble_plf_reg_write(pBLE, 0x43000004, 0xFFFFFFFF);
    am_hal_ble_plf_reg_write(pBLE, 0x43800004, ui32TrimValue);
    am_hal_ble_plf_reg_write(pBLE, 0x43000004, RegValueMCGR);

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Manually enable/disable transmitter to output carrier signal
// set ui8TxChannel as 0 to 0x27 for each transmit channel, 0xFF back to normal modulate mode
//
//*****************************************************************************
uint32_t
am_hal_ble_hci_reset(void *pHandle)
{
    am_hal_ble_buffer(16) sWriteCommand;
    am_hal_ble_buffer(16) sResponse;
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t ui32IntEnable;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    am_hal_ble_sleep_set(pBLE, false);
    uint32_t ui32Module = pBLE->ui32Module;

    // issue the HCI command with to reset hci 
    sWriteCommand.bytes[0] = 0x01;
    sWriteCommand.bytes[1] = 0x03;
    sWriteCommand.bytes[2] = 0x0c;
    sWriteCommand.bytes[3] = 0x00;
    //
    // Temporarily disable BLE interrupts.
    //
#if AM_CMSIS_REGS
    ui32IntEnable = BLEIFn(ui32Module)->INTEN;
    BLEIFn(ui32Module)->INTEN = 0;
#else // AM_CMSIS_REGS
    ui32IntEnable = AM_REGn(BLEIF, ui32Module, INTEN);
    AM_REGn(BLEIF, ui32Module, INTEN) = 0;
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_write(pBLE,
                                  AM_HAL_BLE_RAW,
                                  sWriteCommand.words,
                                  4);
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->BLEDBG_b.IOCLKON = 1;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, ui32Module, BLEDBG, IOCLKON, 1);
#endif // AM_CMSIS_REGS

    //
    // Wait for the response.
    //
#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 10,
                       AM_HAL_BLE_NO_HCI_RESPONSE );
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS (AM_BFM(BLEIF, BSTATUS, BLEIRQ) == 0, 10,
                      AM_HAL_BLE_NO_HCI_RESPONSE );
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_read(pBLE, sResponse.words, 0);

    //
    // Re-enable BLE interrupts.
    //
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->INTCLR = ui32IntEnable;
    BLEIFn(ui32Module)->INTEN = ui32IntEnable;
#else // AM_CMSIS_REGS
    AM_REGn(BLEIF, ui32Module, INTCLR) = ui32IntEnable;
    AM_REGn(BLEIF, ui32Module, INTEN) = ui32IntEnable;
#endif // AM_CMSIS_REGS

  return AM_HAL_STATUS_SUCCESS;
}


//*****************************************************************************
//
//to directly TX carrier wave. change ranges from 0 to 0x27.
//
//*****************************************************************************
uint32_t
am_hal_ble_set_carrier_wave_ex(void *pHandle, uint8_t channel)
{
    am_hal_ble_buffer(16) sWriteCommand;
    am_hal_ble_buffer(16) sResponse;
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t ui32IntEnable;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    // channel 0xFF to disable the constant transmission
    if(channel == 0xFF)
    {
        am_hal_ble_transmitter_control(pBLE, false);
        return AM_HAL_STATUS_SUCCESS;
    }

    am_hal_ble_sleep_set(pBLE, false);
    uint32_t ui32Module = pBLE->ui32Module;

    // issue the HCI command with to TX carrier wave
    sWriteCommand.bytes[0] = 0x01;
    sWriteCommand.bytes[1] = 0x1E;
    sWriteCommand.bytes[2] = 0x20;
    sWriteCommand.bytes[3] = 0x03;
    sWriteCommand.bytes[4] = channel;
    sWriteCommand.bytes[5] = 0x25;
    sWriteCommand.bytes[6] = 0x00;

    //
    // Temporarily disable BLE interrupts.
    //
#if AM_CMSIS_REGS
    ui32IntEnable = BLEIFn(ui32Module)->INTEN;
    BLEIFn(ui32Module)->INTEN = 0;
#else // AM_CMSIS_REGS
    ui32IntEnable = AM_REGn(BLEIF, ui32Module, INTEN);
    AM_REGn(BLEIF, ui32Module, INTEN) = 0;
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_write(pBLE,
                                  AM_HAL_BLE_RAW,
                                  sWriteCommand.words,
                                  7);
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->BLEDBG_b.IOCLKON = 1;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, ui32Module, BLEDBG, IOCLKON, 1);
#endif // AM_CMSIS_REGS

    //
    // Wait for the response.
    //
#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 10,
                       AM_HAL_BLE_NO_HCI_RESPONSE );
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS (AM_BFM(BLEIF, BSTATUS, BLEIRQ) == 0, 10,
                      AM_HAL_BLE_NO_HCI_RESPONSE );
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_read(pBLE, sResponse.words, 0);

    //
    // Re-enable BLE interrupts.
    //
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->INTCLR = ui32IntEnable;
    BLEIFn(ui32Module)->INTEN = ui32IntEnable;
#else // AM_CMSIS_REGS
    AM_REGn(BLEIF, ui32Module, INTCLR) = ui32IntEnable;
    AM_REGn(BLEIF, ui32Module, INTEN) = ui32IntEnable;
#endif // AM_CMSIS_REGS

    am_hal_ble_transmitter_control(pBLE, true);

  return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Manually enable/disable transmitter to output carrier signal
// set ui8TxChannel as 0 to 0x27 for each transmit channel, 0xFF back to normal modulate mode
//
//*****************************************************************************
uint32_t
am_hal_ble_transmitter_control_ex(void *pHandle, uint8_t ui8TxChannel)
{
	return am_hal_ble_set_carrier_wave_ex(pHandle,ui8TxChannel);
}

//*****************************************************************************
//
//to directly TX constant modulation signal. change ranges from 0 to 0x27.
//
//*****************************************************************************
uint32_t
am_hal_ble_set_constant_transmission_ex(void *pHandle, uint8_t channel)
{
    am_hal_ble_buffer(16) sWriteCommand;
    am_hal_ble_buffer(16) sResponse;
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t ui32IntEnable;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    // channel 0xFF to disable the constant transmission
    if(channel == 0xFF)
    {
        am_hal_ble_set_constant_transmission(pBLE, false);
        return AM_HAL_STATUS_SUCCESS;
    }

    uint32_t ui32Module = pBLE->ui32Module;
    am_hal_ble_set_constant_transmission(pBLE, true);

    // issue the HCI command with to TX constant transmission
    sWriteCommand.bytes[0] = 0x01;
    sWriteCommand.bytes[1] = 0x1E;
    sWriteCommand.bytes[2] = 0x20;
    sWriteCommand.bytes[3] = 0x03;
    sWriteCommand.bytes[4] = channel;
    sWriteCommand.bytes[5] = 0x25;
    sWriteCommand.bytes[6] = 0x00;

    //
    // Temporarily disable BLE interrupts.
    //
#if AM_CMSIS_REGS
    ui32IntEnable = BLEIFn(ui32Module)->INTEN;
    BLEIFn(ui32Module)->INTEN = 0;
#else // AM_CMSIS_REGS
    ui32IntEnable = AM_REGn(BLEIF, ui32Module, INTEN);
    AM_REGn(BLEIF, ui32Module, INTEN) = 0;
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_write(pBLE,
                                  AM_HAL_BLE_RAW,
                                  sWriteCommand.words,
                                  7);
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->BLEDBG_b.IOCLKON = 1;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, ui32Module, BLEDBG, IOCLKON, 1);
#endif // AM_CMSIS_REGS

    //
    // Wait for the response.
    //
#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0, 10,
                       AM_HAL_BLE_NO_HCI_RESPONSE );
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS (AM_BFM(BLEIF, BSTATUS, BLEIRQ) == 0, 10,
                      AM_HAL_BLE_NO_HCI_RESPONSE );
#endif // AM_CMSIS_REGS

    am_hal_ble_blocking_hci_read(pBLE, sResponse.words, 0);

    //
    // Re-enable BLE interrupts.
    //
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->INTCLR = ui32IntEnable;
    BLEIFn(ui32Module)->INTEN = ui32IntEnable;
#else // AM_CMSIS_REGS
    AM_REGn(BLEIF, ui32Module, INTCLR) = ui32IntEnable;
    AM_REGn(BLEIF, ui32Module, INTEN) = ui32IntEnable;
#endif // AM_CMSIS_REGS

  return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Manually set modulation characteristic
// based on the tested values at customer side.
// manually set frequency offset for 10101010 or 01010101 pattern
// parameter default value is 0x34, increase to get larger frequency offset
//
//*****************************************************************************
uint32_t
am_hal_ble_transmitter_modex_set(void *pHandle, uint8_t ui8ModFrqOffset)
{
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t RegValueMCGR, RegValueBACKCR, RegValueSTCR, RegValueDACSPICR;

    ui8ModFrqOffset &= 0x7F;

    am_hal_ble_plf_reg_read(pBLE, 0x43000004, &RegValueMCGR);
    //
    // Unlock the BLE registers.
    //
    am_hal_ble_plf_reg_write(pBLE, 0x43000004, 0xFFFFFFFF);

    am_hal_ble_plf_reg_read(pBLE, 0x52000000, &RegValueSTCR);
    RegValueSTCR |= (1 << 10);
    am_hal_ble_plf_reg_write(pBLE, 0x52000000, RegValueSTCR);

    //fix the extra emmision at 800MHz
    //am_hal_ble_plf_reg_write(pBLE, 0x52400024, 0x3);

    am_hal_ble_plf_reg_read(pBLE, 0x45800070, &RegValueBACKCR);
    am_hal_ble_plf_reg_write(pBLE, 0x45800070, (RegValueBACKCR | 0x8));
    RegValueDACSPICR = (ui8ModFrqOffset << 1) | 0x1;
    am_hal_ble_plf_reg_write(pBLE, 0x52000014, RegValueDACSPICR);

    am_hal_ble_plf_reg_write(pBLE, 0x43000004, RegValueMCGR);

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Trims the BLE core bandgap reference based on the factory-set recommended
// values.
// ui32TxPower: 0x03->-20dBm 0x04->-10dBm 0x05->-5dBm 0x08->0dBm 0x0F->4dBm
//*****************************************************************************
uint32_t
am_hal_ble_tx_power_set(void *pHandle, uint8_t ui32TxPower)
{
    am_hal_ble_state_t *pBLE = pHandle;

    uint32_t ui32PowerValue = 0x08000000;
    ui32PowerValue |= (ui32TxPower & 0xFF);

    //
    //
    am_hal_ble_plf_reg_write(pBLE, 0x20006038, ui32PowerValue);

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Builds a vendor-specific BLE command.
//
//*****************************************************************************
uint32_t
am_hal_ble_vs_command_build(uint32_t *pui32Command, uint32_t ui32OpCode,
                            uint32_t ui32TotalLength, uint8_t *pui8Parameters)
{
    uint8_t *pui8Dest = (uint8_t *) pui32Command;

    //
    // Build the header portion of the command from the given argments.
    //
    pui8Dest[0] = 0x01;
    pui8Dest[1] = ui32OpCode & 0xFF;
    pui8Dest[2] = (ui32OpCode >> 8) & 0xFF;
    pui8Dest[3] = (ui32TotalLength - 4) & 0xFF;

    //
    // Finish filling the array with any parameters that may be required.
    //
    for (uint32_t i = 4; i < ui32TotalLength; i++)
    {
        pui8Dest[i] = pui8Parameters[i - 4];
    }

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Returns the number of bytes written.
//
//*****************************************************************************
uint32_t
am_hal_ble_blocking_hci_write(void *pHandle, uint8_t ui8Type,
                              uint32_t *pui32Data, uint32_t ui32NumBytes)
{
    uint32_t ui32ErrorStatus;

    am_hal_ble_transfer_t HciWrite =
    {
        .pui32Data = pui32Data,
        .pui8Offset = {ui8Type, 0x0, 0x0},
        .ui8OffsetLen = 0,
        .ui16Length = ui32NumBytes,
        .ui8Command = AM_HAL_BLE_WRITE,
        .ui8RepeatCount = 0,
        .bContinue = false,
        .pfnTransferCompleteCB = 0x0,
        .pvContext = 0x0,
    };

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return 0;
    }

    //
    // Fix up the offset length based on the packet type, and send the bytes.
    //
    if (ui8Type != AM_HAL_BLE_RAW)
    {
        HciWrite.ui8OffsetLen = 1;
    }

    ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &HciWrite);
    if (ui32ErrorStatus != AM_HAL_STATUS_SUCCESS)
    {
        return ui32ErrorStatus;
    }

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Returns the number of bytes received.
//
//*****************************************************************************
uint32_t
am_hal_ble_blocking_hci_read(void *pHandle, uint32_t *pui32Data, uint32_t *pui32BytesReceived)
{
    uint32_t ui32Module, ui32NumBytes, ui32ErrorStatus;

    am_hal_ble_buffer(2) sLengthBytes;

    am_hal_ble_transfer_t HciRead =
    {
        .pui32Data = sLengthBytes.words,
        .pui8Offset = {0x0, 0x0, 0x0},
        .ui8OffsetLen = 0,
        .ui16Length = 2,
        .ui8Command = AM_HAL_BLE_READ,
        .ui8RepeatCount = 0,
        .bContinue = false,
        .pfnTransferCompleteCB = 0x0,
        .pvContext = 0x0,
    };

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return 0;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

    //
    // Make sure the IRQ signal is set.
    //
#if AM_CMSIS_REGS
    if ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ )
#else // AM_CMSIS_REGS
    if ( AM_BFMn(BLEIF, ui32Module, BSTATUS, BLEIRQ) )
#endif // AM_CMSIS_REGS
    {
        //
        // Read the length bytes.
        //
        ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &HciRead);
        if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS)
        {
            return ui32ErrorStatus;
        }

        //
        // Read the rest of the packet.
        //
        HciRead.pui32Data = pui32Data;
        HciRead.ui16Length = (sLengthBytes.bytes[0] +
                              (sLengthBytes.bytes[1] << 8));

        ui32ErrorStatus = am_hal_ble_blocking_transfer(pHandle, &HciRead);
        if ( ui32ErrorStatus != AM_HAL_STATUS_SUCCESS)
        {
            return ui32ErrorStatus;
        }

        ui32NumBytes =  HciRead.ui16Length;
    }
    else
    {
        ui32NumBytes = 0;
    }

    if (pui32BytesReceived)
    {
        *pui32BytesReceived = ui32NumBytes;
    }

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Returns the number of bytes written.
//
//*****************************************************************************
uint32_t
am_hal_ble_nonblocking_hci_write(void *pHandle, uint8_t ui8Type,
                                 uint32_t *pui32Data, uint32_t ui32NumBytes,
                                 am_hal_ble_transfer_complete_cb_t pfnCallback,
                                 void *pvContext)
{
    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return 0;
    }

    am_hal_ble_transfer_t HciWrite =
    {
        .pui32Data = pui32Data,
        .pui8Offset = {ui8Type, 0x0, 0x0},
        .ui8OffsetLen = 0,
        .ui16Length = ui32NumBytes,
        .ui8Command = AM_HAL_BLE_WRITE,
        .ui8RepeatCount = 0,
        .bContinue = false,
        .pfnTransferCompleteCB = pfnCallback,
        .pvContext = pvContext,
    };

    //
    // Fix up the offset length based on the packet type, and send the bytes.
    //
    if (ui8Type != AM_HAL_BLE_RAW)
    {
        HciWrite.ui8OffsetLen = 1;
    }

    uint32_t ui32Status = am_hal_ble_nonblocking_transfer(pHandle, &HciWrite);

    return ui32Status;
}

//*****************************************************************************
//
// Returns the number of bytes received.
//
//*****************************************************************************
uint32_t
am_hal_ble_nonblocking_hci_read(void *pHandle, uint32_t *pui32Data,
                                am_hal_ble_transfer_complete_cb_t pfnCallback,
                                void *pvContext)
{
    uint32_t ui32Module, ui32Status;

    am_hal_ble_buffer(2) sLengthBytes;

    am_hal_ble_transfer_t HciRead =
    {
        .pui32Data = sLengthBytes.words,
        .pui8Offset = {0x0, 0x0, 0x0},
        .ui8OffsetLen = 0,
        .ui16Length = 2,
        .ui8Command = AM_HAL_BLE_READ,
        .ui8RepeatCount = 0,
        .bContinue = false,
        .pfnTransferCompleteCB = pfnCallback,
        .pvContext = pvContext,
    };

    //
    // Check the handle.
    //
    if ( !AM_HAL_BLE_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

    //
    // Make sure the IRQ signal is set.
    //
#if AM_CMSIS_REGS
    if ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ )
#else // AM_CMSIS_REGS
    if ( AM_BFMn(BLEIF, ui32Module, BSTATUS, BLEIRQ) )
#endif // AM_CMSIS_REGS
    {
        //
        // Read the length bytes.
        //
        ui32Status = am_hal_ble_blocking_transfer(pHandle, &HciRead);

        if ( ui32Status != AM_HAL_STATUS_SUCCESS )
        {
            return ui32Status;
        }

        //
        // Read the rest of the packet.
        //
        HciRead.pfnTransferCompleteCB = pfnCallback;
        HciRead.pui32Data = pui32Data;
        HciRead.ui16Length = (sLengthBytes.bytes[0] +
                              (sLengthBytes.bytes[1] << 8));

        if ( am_hal_ble_nonblocking_transfer(pHandle, &HciRead) == AM_HAL_STATUS_SUCCESS )
        {
            return AM_HAL_STATUS_SUCCESS;
        }
        else
        {
            return AM_HAL_STATUS_FAIL;
        }
    }

    //
    // If we get here, return fail.
    //
    return AM_HAL_STATUS_FAIL;
}

//*****************************************************************************
//
// Flow Control helper function.
//
//*****************************************************************************
//static bool
//WaitForStatus(void)
//{
//    uint32_t ui32Timeout = 0;
//
//    if (AM_BFMn(BLEIF, ui32Module, MSPICFG, WTFC))
//    {
//        return false;
//    }
//
//    //
//    // Check the status pin every millisecond for a full second to see if
//    // the Nationz chip is ready for messages.
//    //
//    while (1)
//    {
//        //
//        // The status pin has glitches on in occasionally, so if we see it
//        // go high, we have to check it a second time to make sure it's a
//        // "real" status event instead of a glitch.
//        //
//        if (AM_BFMn(BLEIF, ui32Module, BSTATUS, SPISTATUS))
//        {
//            delay_us(50);
//            if (AM_BFMn(BLEIF, ui32Module, BSTATUS, SPISTATUS))
//            {
//                //
//                // Getting here means that the Nationz chip is ready to the
//                // best of our knowledge.
//                //
//                return false;
//            }
//        }
//        else
//        {
//            //
//            // No ready signal, or just glitches. Delay and keep looking.
//            //
//            ui32Timeout++;
//            delay_us(50);
//        }
//    }
//}

//*****************************************************************************
//
// Return true if BSTATUS is high.
//
//*****************************************************************************
static bool
am_hal_ble_check_status(am_hal_ble_state_t *pBle)
{
    //
    // We need to make a special exception for "continue" packets, since the
    // BLE radio may deassert the STATUS signal mid-packet.
    //
    if (pBle->bContinuePacket)
    {
        pBle->bContinuePacket = false;
        return true;
    }

#if AM_CMSIS_REGS
    if ( BLEIFn(0)->BSTATUS_b.SPISTATUS == 0)
    {
        return false;
    }
#else // AM_CMSIS_REGS
    if (AM_BFMn(BLEIF, 0, BSTATUS, SPISTATUS) == 0)
    {
        return false;
    }
#endif // AM_CMSIS_REGS

    return true;
}

//*****************************************************************************
//
// Return true if we recently received a BSTATUS edge.
//
//*****************************************************************************
static bool
am_hal_ble_check_status_edge(am_hal_ble_state_t *pBle)
{
    //
    // We need to make a special exception for "continue" packets, since the
    // BLE radio may deassert the STATUS signal mid-packet.
    //
    if (pBle->bContinuePacket)
    {
        pBle->bContinuePacket = false;
        return true;
    }

    if (pBle->bPatchComplete == false)
    {
        return am_hal_ble_check_status(pBle);
    }

#if AM_CMSIS_REGS
    if ( BLEIFn(0)->INTSTAT_b.BLECSSTAT == 0)
    {
        return false;
    }
#else // AM_CMSIS_REGS
    if (AM_BFMn(BLEIF, 0, INTSTAT, BLECSSTAT) == 0)
    {
        return false;
    }
#endif // AM_CMSIS_REGS

    return true;
}

//*****************************************************************************
//
// Blocking write to the BLE module.
//
//*****************************************************************************
uint32_t
am_hal_ble_blocking_transfer(void *pHandle, am_hal_ble_transfer_t *psTransfer)
{
    am_hal_ble_state_t *pBle = pHandle;
    uint32_t ui32IntEnable;
    uint32_t ui32Module;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

    //
    // If the transfer doesn't have any bytes in it, just return success.
    //
    if (psTransfer->ui16Length == 0)
    {
        return AM_HAL_STATUS_SUCCESS;
    }

    //
    // If we're writing, we need to lock down the bus now. Set the wakeup
    // signal, and start monitoring STATUS. If STATUS isn't high within our
    // configured timeout, we have to assume that the BLE core is unresponsive
    // and report an error back to the caller.
    //
    if (psTransfer->ui8Command == AM_HAL_BLE_WRITE)
    {
        uint32_t ui32SpiStatus = false;

        if ( pBle->bLastPacketWasTX == true)
        {
            delay_ms(2);
            pBle->bLastPacketWasTX = false;
        }

        AM_CRITICAL_BEGIN;

        //
        // Clear the STATUS interrupt.
        //
#if AM_CMSIS_REGS
        BLEIFn(0)->BLEDBG_b.IOCLKON = 1;
        BLEIFn(0)->INTCLR_b.BLECSSTAT = 1;
#else // AM_CMSIS_REGS
        AM_BFWn(BLEIF, 0, BLEDBG, IOCLKON, 1);
        AM_BFWn(BLEIF, 0, INTCLR, BLECSSTAT, 1);
#endif // AM_CMSIS_REGS

        delay_us(5);

        //
        // Set WAKE, and wait for a positive edge on the STATUS signal.
        //
        am_hal_ble_wakeup_set(pBle, 1);

        //
        // If we don't see an edge on STATUS in X ms, assume it's not coming
        // and return with an AM_HAL_BLE_STATUS_SPI_NOT_READY error.
        //
        uint32_t ui32Timeout = 0;
        uint32_t ui32TimeoutLimit = AM_BLE_STATUS_TIMEOUT;

        while(1)
        {
            if (am_hal_ble_check_status_edge(pBle) == true)
            {
                if (am_hal_ble_bus_lock(pBle))
                {
                    ui32SpiStatus = AM_HAL_STATUS_SUCCESS;
                    break;
                }
            }
#if AM_CMSIS_REGS
            else if ((ui32Timeout == ui32TimeoutLimit) ||
                     (BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ))
            {
                ui32SpiStatus = AM_HAL_BLE_STATUS_SPI_NOT_READY;
                am_hal_ble_wakeup_set(pBle, 0);
                break;
            }
#else // !AM_CMSIS_REGS
            else if ((ui32Timeout == ui32TimeoutLimit) ||
                     (AM_BFRn(BLEIF, 0, BSTATUS, BLEIRQ)))
            {
                ui32SpiStatus = AM_HAL_BLE_STATUS_SPI_NOT_READY;
                am_hal_ble_wakeup_set(pBle, 0);
                break;
            }
#endif // AM_CMSIS_REGS

            ui32Timeout++;
            delay_us(10);
        }

#if AM_CMSIS_REGS
    BLEIFn(0)->BLEDBG_b.IOCLKON = 0;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, 0, BLEDBG, IOCLKON, 0);
#endif // AM_CMSIS_REGS

        AM_CRITICAL_END;

        if (ui32SpiStatus != AM_HAL_STATUS_SUCCESS)
        {
            return ui32SpiStatus;
        }

    }
    else
    {
#if AM_CMSIS_REGS
        if (BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0)
        {
            return AM_HAL_BLE_STATUS_IRQ_LOW;
        }
#else // AM_CMSIS_REGS
        if (AM_BFMn(BLEIF, ui32Module, BSTATUS, BLEIRQ) == 0)
        {
            return AM_HAL_BLE_STATUS_IRQ_LOW;
        }
#endif // AM_CMSIS_REGS

        if (!am_hal_ble_bus_lock(pBle))
        {
            return AM_HAL_BLE_STATUS_BUS_BUSY;
        }
    }

    if (psTransfer->bContinue)
    {
        pBle->bContinuePacket = true;
    }

    //
    // Set the current transfer, and clear the command complete interrupt so we
    // can tell when the next command completes.
    //
    memcpy(&pBle->sCurrentTransfer, psTransfer, sizeof(am_hal_ble_transfer_t));

    //
    // Make sure we don't get any interrupts that might interfere with this
    // operation. We will save the interrupt enable register state so we can
    // restore it later. Also, make sure "command complete" is clear, so we can
    // detect the end of the transaction.
    //
#if AM_CMSIS_REGS
    ui32IntEnable = BLEIFn(ui32Module)->INTEN;
    BLEIFn(ui32Module)->INTEN_b.BLECIRQ = 0;
    BLEIFn(ui32Module)->INTEN_b.CMDCMP = 0;
    BLEIFn(ui32Module)->INTEN_b.THR = 0;
    BLEIFn(ui32Module)->INTCLR_b.CMDCMP = 1;
#else // AM_CMSIS_REGS
    ui32IntEnable = AM_REGn(BLEIF, ui32Module, INTEN);
    AM_BFWn(BLEIF, ui32Module, INTEN, BLECIRQ, 0);
    AM_BFWn(BLEIF, ui32Module, INTEN, CMDCMP, 0);
    AM_BFWn(BLEIF, ui32Module, INTEN, THR, 0);
    AM_BFWn(BLEIF, ui32Module, INTCLR, CMDCMP, 1);
#endif // AM_CMSIS_REGS

    //
    // Critical section to protect the gap between command and data.
    //
    AM_CRITICAL_BEGIN;

    //
    // Write the command word.
    //
    am_hal_ble_cmd_write(pHandle, psTransfer);

    //
    // Now we need to manage the fifos based on the type of transfer. In either
    // case, we will keep draining or refilling the FIFO until the full
    // transaction is complete.
    //
    if (psTransfer->ui8Command == AM_HAL_BLE_WRITE)
    {
#if 0   // 0 for FIFO handling with IOM hal style
        while (pBle->ui32TransferIndex < pBle->sCurrentTransfer.ui16Length)
        {
            am_hal_ble_fifo_fill(pHandle);
        }
#else   // 0 for FIFO handling with IOM hal style
        bool     bCmdCmp = false;
        uint32_t numWait = 0;
        // Adjust the byte count to be sent/received for repeat count
        uint32_t ui32Bytes = pBle->sCurrentTransfer.ui16Length;

        uint32_t ui32FifoRem;
        uint32_t *pui32Buffer = pBle->sCurrentTransfer.pui32Data;

        //
        // Write the command word.
        //
        am_hal_ble_cmd_write(pHandle, psTransfer);

        //
        // Keep looping until we're out of bytes to send or command complete (error).
        //
        while (ui32Bytes)
        {
            //
            // Limit the wait to reasonable limit - instead of blocking forever
            //
            numWait = 0;
#if AM_CMSIS_REGS
            while ((ui32FifoRem = BLEIFn(ui32Module)->FIFOPTR_b.FIFO0REM) < 4)
            {
                bCmdCmp = BLEIFn(ui32Module)->INTSTAT_b.CMDCMP;
#else // AM_CMSIS_REGS
            while ((ui32FifoRem = AM_BFRn(BLEIF, ui32Module, FIFOPTR, FIFO0REM)) < 4)
            {
                bCmdCmp = AM_BFRn(BLEIF, ui32Module, INTSTAT, CMDCMP);
#endif // AM_CMSIS_REGS
                if (bCmdCmp || (numWait++ >= AM_HAL_IOM_MAX_BLOCKING_WAIT))
                {
                    //
                    // FIFO not expected to change any more - get out
                    //
                    break;
                }
                else
                {
                    am_hal_flash_delay( FLASH_CYCLES_US(1) );
                }
            }
            if (bCmdCmp || (ui32FifoRem < 4))
            {
                //
                // Something went wrong - bail out
                //
                break;
            }

            while ((ui32FifoRem >= 4) && ui32Bytes)
            {
#if AM_CMSIS_REGS
                BLEIFn(ui32Module)->FIFOPUSH = *pui32Buffer++;
#else // AM_CMSIS_REGS
                AM_REGn(BLEIF, ui32Module, FIFOPUSH) = *pui32Buffer++;
#endif // AM_CMSIS_REGS
                ui32FifoRem -= 4;
                if (ui32Bytes >= 4)
                {
                    ui32Bytes -= 4;
                }
                else
                {
                    ui32Bytes = 0;
                }
            }
        }
#endif //0 for FIFO handling with IOM hal style
    }
    else
    {
        while (pBle->ui32TransferIndex < pBle->sCurrentTransfer.ui16Length)
        {
            am_hal_ble_fifo_drain(pHandle);
        }
    }

    //
    // End the critical section.
    //
//    AM_CRITICAL_END;  //fixme moved further down to cover am_hal_ble_bus_release();

    //
    // Wait for the transaction to complete, and clear out any interrupts that
    // may have come up.
    //
#if AM_CMSIS_REGS
    WHILE_TIMEOUT_MS ( BLEIFn(ui32Module)->INTSTAT_b.CMDCMP == 0, 10,
                       AM_HAL_BLE_HCI_PACKET_INCOMPLETE );
    BLEIFn(ui32Module)->INTCLR_b.CMDCMP = 1;
    BLEIFn(ui32Module)->INTCLR_b.THR = 1;
#else // AM_CMSIS_REGS
    WHILE_TIMEOUT_MS (AM_BFMn(BLEIF, ui32Module, INTSTAT, CMDCMP) == 0, 10,
                      AM_HAL_BLE_HCI_PACKET_INCOMPLETE);
    AM_BFWn(BLEIF, ui32Module, INTCLR, CMDCMP, 1);
    AM_BFWn(BLEIF, ui32Module, INTCLR, THR, 1);
#endif // AM_CMSIS_REGS

    //
    // Clear out the current transfer. We're done.
    //
    memset(&pBle->sCurrentTransfer, 0, sizeof(am_hal_ble_transfer_t));
    pBle->ui32TransferIndex = 0;

    //
    // Let the radio go back to sleep.
    //
    if (psTransfer->ui8Command == AM_HAL_BLE_WRITE)
    {
        am_hal_ble_wakeup_set(pBle, 0);
        pBle->bLastPacketWasTX = true;
    }

    if ((psTransfer->ui8Command == AM_HAL_BLE_READ) &&
        (pBle->bPatchComplete == true))
    {
        pBle->bLastPacketWasTX = false;
    }

    //
    // Restore the interrupt state.
    //
#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->INTEN = ui32IntEnable;
#else // AM_CMSIS_REGS
    AM_REGn(BLEIF, ui32Module, INTEN) = ui32IntEnable;
#endif // AM_CMSIS_REGS

    //
    // Release the bus.
    //
    am_hal_ble_bus_release(pBle);

    //
    // End the critical section.
    //
    AM_CRITICAL_END;  //fixme moved further down to cover am_hal_ble_bus_release();

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Nonblocking write to the BLE module.
//
//*****************************************************************************
uint32_t
am_hal_ble_nonblocking_transfer(void *pHandle, am_hal_ble_transfer_t *psTransfer)
{
    am_hal_ble_state_t *pBle = pHandle;
    uint32_t ui32Module;
    uint32_t ui32Status;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

    //
    // If the transfer doesn't have any bytes in it, just return success.
    //
    if (psTransfer->ui16Length == 0)
    {
        return AM_HAL_STATUS_SUCCESS;
    }

    //
    // Check to see if this is a write or a read.
    //
    if (psTransfer->ui8Command == AM_HAL_BLE_WRITE)
    {
        //
        // If we're doing a write, start a critical section here, because the
        // timing between STATUS and nCE on the bus needs to be very tight.
        //
        AM_CRITICAL_BEGIN;

        //
        // Check the status pin to see if we have permission to send. If we do,
        // set up the DMA and start the transaction.
        //
        if (pBle->bSavedPacket == true)
        {
            am_hal_debug_gpio_set(BLE_DEBUG_TRACE_09);
            ui32Status = AM_HAL_BLE_STATUS_BUS_BUSY;
            am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_09);
        }
        else
        {
            am_hal_ble_wakeup_set(pBle, 1);
            if ( am_hal_ble_lock_and_check_status(pBle))
            {
                am_hal_debug_gpio_set(BLE_DEBUG_TRACE_06);

                //
                // Set the current transfer.
                //
                memcpy(&pBle->sCurrentTransfer, psTransfer, sizeof(am_hal_ble_transfer_t));

                //
                // Prepare the DMA.
                //
#if AM_CMSIS_REGS
                BLEIFn(ui32Module)->DMATARGADDR = (uint32_t)pBle->sCurrentTransfer.pui32Data;
                BLEIFn(ui32Module)->DMATOTCOUNT = pBle->sCurrentTransfer.ui16Length;
                BLEIFn(ui32Module)->DMATRIGEN   = BLEIF_DMATRIGEN_DTHREN_Msk;
                BLEIFn(ui32Module)->DMACFG      = (_VAL2FLD(BLEIF_DMACFG_DMADIR, BLEIF_DMACFG_DMADIR_M2P)    |
                                      _VAL2FLD(BLEIF_DMACFG_DMAPRI, BLEIF_DMACFG_DMAPRI_HIGH));
#else // AM_CMSIS_REGS
                AM_REGn(BLEIF, ui32Module, DMATARGADDR) = (uint32_t) pBle->sCurrentTransfer.pui32Data;
                AM_REGn(BLEIF, ui32Module, DMATOTCOUNT) =  pBle->sCurrentTransfer.ui16Length;
                AM_REGn(BLEIF, ui32Module, DMATRIGEN) =  AM_REG_BLEIF_DMATRIGEN_DTHREN_M;
                AM_REGn(BLEIF, ui32Module, DMACFG) =  (AM_REG_BLEIF_DMACFG_DMADIR_M2P |
                                                       AM_REG_BLEIF_DMACFG_DMAPRI_HIGH);
#endif // AM_CMSIS_REGS

                //
                // Write the command word, and enable the DMA.
                //
                am_hal_ble_cmd_write(pHandle, &pBle->sCurrentTransfer);
#if AM_CMSIS_REGS
                BLEIFn(ui32Module)->DMACFG |= _VAL2FLD(BLEIF_DMACFG_DMAEN, BLEIF_DMACFG_DMAEN_EN);
#else // AM_CMSIS_REGS
                AM_REGn(BLEIF, ui32Module, DMACFG) |= AM_REG_BLEIF_DMACFG_DMAEN_EN;
#endif // AM_CMSIS_REGS

                ui32Status = AM_HAL_STATUS_SUCCESS;
                am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_06);
            }
            else
            {
                am_hal_debug_gpio_set(BLE_DEBUG_TRACE_07);

                //
                // If status was low, we need to wake up the radio ourselves. Make
                // sure the STATUS interrupt is enabled.
                //
#if AM_CMSIS_REGS
                am_hal_ble_int_enable(pHandle, BLEIF_INTEN_BLECSSTAT_Msk);
#else // AM_CMSIS_REGS
                am_hal_ble_int_enable(pHandle, AM_REG_BLEIF_INTEN_BLECSSTAT_M);
#endif // AM_CMSIS_REGS

                //
                // Record this transaction as a "saved transfer".
                //
                memcpy(&pBle->sSavedTransfer, psTransfer, sizeof(am_hal_ble_transfer_t));
                pBle->bSavedPacket = true;

                ui32Status = AM_HAL_STATUS_SUCCESS;
                am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_07);
            }
        }
        AM_CRITICAL_END;
    }
    else  // AM_HAL_BLE_READ case.
    {
        //
        // Make sure IRQ is high, and that the bus isn't already busy.
        //
        if (!am_hal_ble_bus_lock(pBle))
        {
            am_hal_debug_gpio_set(BLE_DEBUG_TRACE_04);
            ui32Status = AM_HAL_BLE_STATUS_BUS_BUSY;
            am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_04);

            //
            // CAJ - I think a return is actually needed here.
            //
            // return ui32Status;
        }
#if AM_CMSIS_REGS
        if ( BLEIFn(ui32Module)->BSTATUS_b.BLEIRQ == 0 )
        {
            am_hal_ble_bus_release(pBle);
            ui32Status = AM_HAL_BLE_STATUS_IRQ_LOW;
        }
#else // AM_CMSIS_REGS
        if ( AM_BFMn(BLEIF, ui32Module, BSTATUS, BLEIRQ) == 0 )
        {
            am_hal_ble_bus_release(pBle);
            ui32Status = AM_HAL_BLE_STATUS_IRQ_LOW;
        }
#endif // AM_CMSIS_REGS
        else
        {
            am_hal_debug_gpio_set(BLE_DEBUG_TRACE_05);

            //
            // Set the current transfer.
            //
            memcpy(&pBle->sCurrentTransfer, psTransfer, sizeof(am_hal_ble_transfer_t));

            //
            // If we're doing a read, we can just set up the DMA and go.
            //
#if AM_CMSIS_REGS
            BLEIFn(ui32Module)->DMATARGADDR = (uint32_t) pBle->sCurrentTransfer.pui32Data;
            BLEIFn(ui32Module)->DMATOTCOUNT = pBle->sCurrentTransfer.ui16Length;
            BLEIFn(ui32Module)->DMATRIGEN   = (BLEIF_DMATRIGEN_DTHREN_Msk | BLEIF_INTCLR_CMDCMP_Msk);
            BLEIFn(ui32Module)->DMACFG      = (_VAL2FLD(BLEIF_DMACFG_DMADIR, BLEIF_DMACFG_DMADIR_P2M)    |
                                               _VAL2FLD(BLEIF_DMACFG_DMAPRI, BLEIF_DMACFG_DMAPRI_HIGH));

            //
            // Write the command word, and enable the DMA.
            //
            am_hal_ble_cmd_write(pHandle, &pBle->sCurrentTransfer);
            BLEIFn(ui32Module)->DMACFG |= _VAL2FLD(BLEIF_DMACFG_DMAEN, BLEIF_DMACFG_DMAEN_EN);
#else // AM_CMSIS_REGS
            AM_REGn(BLEIF, ui32Module, DMATARGADDR) = (uint32_t) pBle->sCurrentTransfer.pui32Data;
            AM_REGn(BLEIF, ui32Module, DMATOTCOUNT) =  pBle->sCurrentTransfer.ui16Length;
            AM_REGn(BLEIF, ui32Module, DMATRIGEN) =  (AM_REG_BLEIF_DMATRIGEN_DTHREN_M | AM_REG_BLEIF_INTCLR_CMDCMP_M);
            AM_REGn(BLEIF, ui32Module, DMACFG) = (AM_REG_BLEIF_DMACFG_DMADIR_P2M | AM_REG_BLEIF_DMACFG_DMAPRI_HIGH);

            //
            // Write the command word, and enable the DMA.
            //
            am_hal_ble_cmd_write(pHandle, &pBle->sCurrentTransfer);
            AM_REGn(BLEIF, ui32Module, DMACFG) |= AM_REG_BLEIF_DMACFG_DMAEN_EN;
#endif // AM_CMSIS_REGS

            ui32Status =  AM_HAL_STATUS_SUCCESS;
            am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_05);
        }
    }

    return ui32Status;
}

#if 0
//*****************************************************************************
//
// Write ui32NumBytes to the TX FIFO.
//
//*****************************************************************************
static void
am_hal_ble_fifo_write(void *pHandle, uint32_t *pui32Data, uint32_t ui32NumBytes)
{
    uint32_t ui32Index;
    uint32_t ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;


    for (ui32Index = 0; (ui32Index * 4) < ui32NumBytes; ui32Index++)
    {
#if AM_CMSIS_REGS
        BLEIFn(ui32Module)->FIFOPUSH = pui32Data[ui32Index];
#else // AM_CMSIS_REGS
        AM_REGn(BLEIF, ui32Module, FIFOPUSH) = pui32Data[ui32Index];
#endif // AM_CMSIS_REGS
    }

    // we need to have 10us delay to not overwrite FIFO.
    delay_us(10);
}

//*****************************************************************************
//
// Refill the fifo for transmit.
//
//*****************************************************************************
static uint32_t
am_hal_ble_fifo_fill(void *pHandle)
{
    uint32_t ui32Module;
    uint32_t ui32FifoFillSize, ui32Space, ui32BytesLeft;
    uint32_t *pSrc;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return 0;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

    //
    // Rename some pointers for convenience.
    //
    am_hal_ble_state_t *pBle = pHandle;
    am_hal_ble_transfer_t *pTransfer = &pBle->sCurrentTransfer;

    //
    // Check to see how much space there is in the FIFO, and also how many
    // bytes are remaining in the transfer.
    //
#if AM_CMSIS_REGS
    ui32Space = BLEIFn(ui32Module)->FIFOPTR_b.FIFO0REM;
#else // AM_CMSIS_REGS
    ui32Space = AM_BFRn(BLEIF, ui32Module, FIFOPTR, FIFO0REM);
#endif // AM_CMSIS_REGS
    ui32BytesLeft = (pTransfer->ui16Length - pBle->ui32TransferIndex);

    //
    // Calculate how much we can fill the fifo. If our data doesn't all fit
    // right now, fill up the fifo as much as we can, up to the closest
    // multiple of 4.
    //
    if (ui32Space == 0)
    {
        return 0;
    }
    else if (ui32Space >= ui32BytesLeft)
    {
        ui32FifoFillSize = ui32BytesLeft;
    }
    else
    {
        ui32FifoFillSize = ui32Space & (~0x3);
    }

    //
    // Calculate the place where we last left off, feed the FIFO starting from
    // that location, and update the index to match.
    //
    pSrc = &pTransfer->pui32Data[pBle->ui32TransferIndex / 4];

    am_hal_ble_fifo_write(pHandle, pSrc, ui32FifoFillSize);

    pBle->ui32TransferIndex += ui32FifoFillSize;

    //
    // Return the number of bytes we wrote.
    //
    return ui32FifoFillSize;
}
#endif

//*****************************************************************************
//
// Mark the BLE interface busy so it doesn't get used by more than one
// interface.
//
//*****************************************************************************
static bool
am_hal_ble_bus_lock(am_hal_ble_state_t *pBle)
{
    bool bLockObtained;

    //
    // In one atomic sweep, check to see if the bus is busy, and reserve it if
    // it isn't.
    //
    AM_CRITICAL_BEGIN;

    if (pBle->bBusy == false)
    {
        am_hal_debug_gpio_set(BLE_DEBUG_TRACE_11);
        pBle->bBusy = true;
        bLockObtained = true;
        pBle->bCmdComplete = 0;
        pBle->bDmaComplete = 0;
    }
    else
    {
        bLockObtained = false;
    }

    AM_CRITICAL_END;

    //
    // Tell the caller if we successfully locked the bus.
    //
    return bLockObtained;
}

//*****************************************************************************
//
// Mark the BLE interface busy so it doesn't get used by more than one
// interface.
//
//*****************************************************************************
static bool
am_hal_ble_lock_and_check_status(am_hal_ble_state_t *pBle)
{
    bool bLockObtained = false;

    //
    // In one atomic sweep, check to see if the bus is busy, and reserve it if
    // it isn't.
    //
    AM_CRITICAL_BEGIN;

#if AM_CMSIS_REGS
    BLEIFn(0)->BLEDBG_b.IOCLKON = 1;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, 0, BLEDBG, IOCLKON, 1);
#endif // AM_CMSIS_REGS
    delay_us(5);

    if ( am_hal_ble_check_status(pBle) && am_hal_ble_bus_lock(pBle) )
    {
        bLockObtained = true;
    }

#if AM_CMSIS_REGS
    BLEIFn(0)->BLEDBG_b.IOCLKON = 0;
#else // AM_CMSIS_REGS
    AM_BFWn(BLEIF, 0, BLEDBG, IOCLKON, 0);
#endif // AM_CMSIS_REGS

    AM_CRITICAL_END;

    //
    // Tell the caller if we successfully locked the bus.
    //
    return bLockObtained;
}

//*****************************************************************************
//
// Release the bus so someone else can use it.
//
//*****************************************************************************
static void
am_hal_ble_bus_release(am_hal_ble_state_t *pBle)
{
    pBle->bBusy = false;
    am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_11);
}

//*****************************************************************************
//
// Pull data out of the fifo for reads.
//
//*****************************************************************************
static uint32_t
am_hal_ble_fifo_drain(void *pHandle)
{
    uint32_t ui32Module;
    uint32_t ui32ReadSize, ui32RxDataLen, ui32BytesLeft;
    uint32_t *pDest;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return 0;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

    //
    // Rename some pointers for convenience.
    //
    am_hal_ble_state_t *pBle = pHandle;
    am_hal_ble_transfer_t *pTransfer = &pBle->sCurrentTransfer;

    //
    // Check to see how much data there is in the FIFO, and also how many
    // bytes are remaining in the transfer.
    //
#if AM_CMSIS_REGS
    ui32RxDataLen = BLEIFn(ui32Module)->FIFOPTR_b.FIFO1SIZ;
#else // AM_CMSIS_REGS
    ui32RxDataLen = AM_BFRn(BLEIF, ui32Module, FIFOPTR, FIFO1SIZ);
#endif // AM_CMSIS_REGS
    ui32BytesLeft = (pTransfer->ui16Length - pBle->ui32TransferIndex);

    //
    // Calculate how much we can drain the fifo.
    //
    if (ui32RxDataLen < 4)
    {
        return 0;
    }
    else if (ui32RxDataLen >= pTransfer->ui16Length)
    {
        ui32ReadSize = ui32BytesLeft;
    }
    else
    {
        ui32ReadSize = ui32RxDataLen & (~0x3);
    }

    //
    // Calculate the place where we last left off, feed the FIFO starting from
    // that location, and update the index to match.
    //
    pDest = &pTransfer->pui32Data[pBle->ui32TransferIndex / 4];

    am_hal_ble_fifo_read(pHandle, pDest, ui32ReadSize);

    pBle->ui32TransferIndex += ui32ReadSize;

    //
    // Return the number of bytes we wrote.
    //
    return ui32ReadSize;
}

//*****************************************************************************
//
// Write the command word for a BLE transfer.
//
//*****************************************************************************
uint32_t
am_hal_ble_cmd_write(void *pHandle, am_hal_ble_transfer_t *psTransfer)
{
    uint32_t ui32CmdWord, ui32OffsetHigh;
    uint32_t ui32Module;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

#if AM_CMSIS_REGS
    //
    // Figure out the command word and the offset register. Then write them.
    //
    switch (psTransfer->ui8OffsetLen)
    {
        case 0:
            ui32CmdWord = 0;
            ui32OffsetHigh = 0;
            break;

        case 1:
            ui32CmdWord = _VAL2FLD(BLEIF_CMD_OFFSETLO, psTransfer->pui8Offset[0]);
            ui32OffsetHigh = 0;
            break;

        case 2:
            ui32CmdWord = _VAL2FLD(BLEIF_CMD_OFFSETLO, psTransfer->pui8Offset[1]);
            ui32OffsetHigh = psTransfer->pui8Offset[0];
            break;

        case 3:
            ui32CmdWord = _VAL2FLD(BLEIF_CMD_OFFSETLO, psTransfer->pui8Offset[2]);
            ui32OffsetHigh = ((psTransfer->pui8Offset[1]) |
                              (psTransfer->pui8Offset[0] << 8));
            break;

        default:
            // Offset length was incorrect.
            return AM_HAL_STATUS_INVALID_ARG;
    }

    ui32CmdWord |= (_VAL2FLD(BLEIF_CMD_OFFSETCNT, psTransfer->ui8OffsetLen) |
                    _VAL2FLD(BLEIF_CMD_TSIZE, psTransfer->ui16Length)       |
                    _VAL2FLD(BLEIF_CMD_CONT, psTransfer->bContinue)         |
                    psTransfer->ui8Command);

    BLEIFn(ui32Module)->OFFSETHI = ui32OffsetHigh;
    BLEIFn(ui32Module)->CMD = ui32CmdWord;
#else // AM_CMSIS_REGS
    //
    // Figure out the command word and the offset register. Then write them.
    //
    switch (psTransfer->ui8OffsetLen)
    {
        case 0:
            ui32CmdWord = 0;
            ui32OffsetHigh = 0;
            break;

        case 1:
            ui32CmdWord = AM_REG_BLEIF_CMD_OFFSETLO(psTransfer->pui8Offset[0]);
            ui32OffsetHigh = 0;
            break;

        case 2:
            ui32CmdWord = AM_REG_BLEIF_CMD_OFFSETLO(psTransfer->pui8Offset[1]);
            ui32OffsetHigh = psTransfer->pui8Offset[0];
            break;

        case 3:
            ui32CmdWord = AM_REG_BLEIF_CMD_OFFSETLO(psTransfer->pui8Offset[2]);
            ui32OffsetHigh = ((psTransfer->pui8Offset[1]) |
                              (psTransfer->pui8Offset[0] << 8));
            break;

        default:
            // Offset length was incorrect.
            return AM_HAL_STATUS_INVALID_ARG;
    }

    ui32CmdWord |= (AM_REG_BLEIF_CMD_OFFSETCNT(psTransfer->ui8OffsetLen) |
                    AM_REG_BLEIF_CMD_TSIZE(psTransfer->ui16Length) |
                    AM_REG_BLEIF_CMD_CONT(psTransfer->bContinue) |
                    psTransfer->ui8Command);

    AM_REGn(BLEIF, ui32Module, OFFSETHI) = ui32OffsetHigh;
    AM_REGn(BLEIF, ui32Module, CMD) = ui32CmdWord;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Read ui32NumBytes from the RX FIFO.
//
//*****************************************************************************
static void
am_hal_ble_fifo_read(void *pHandle, uint32_t *pui32Data, uint32_t ui32NumBytes)
{
    uint32_t ui32Index;
    uint32_t ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

    for (ui32Index = 0; (ui32Index * 4) < ui32NumBytes; ui32Index++)
    {
#if AM_CMSIS_REGS
        pui32Data[ui32Index] = BLEIFn(ui32Module)->FIFOPOP;
#else // AM_CMSIS_REGS
        pui32Data[ui32Index] = AM_REGn(BLEIF, ui32Module, FIFOPOP);
#endif // AM_CMSIS_REGS

#ifndef AM_HAL_BLE_NO_FIFO_PROTECTION
#if AM_CMSIS_REGS
        BLEIFn(ui32Module)->FIFOPOP = 0;
#else // AM_CMSIS_REGS
        AM_REGn(BLEIF, ui32Module, FIFOPOP) = 0;
#endif // AM_CMSIS_REGS
#endif

    }
}

//*****************************************************************************
//
// Call the appropriate callbacks when DMA transfers complete.
//
//*****************************************************************************
uint32_t
am_hal_ble_int_service(void *pHandle, uint32_t ui32Status)
{
    am_hal_ble_state_t *pBle = pHandle;
    uint32_t ui32Module;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

    //
    // Check to see if this is a STATUS interrupt. If so, we should execute any
    // saved writes we might have.
    //
#if AM_CMSIS_REGS
    if ( (ui32Status & BLEIF_INTSTAT_BLECSSTAT_Msk) &&
         (pBle->bSavedPacket == true) )
    {
        am_hal_debug_gpio_set(BLE_DEBUG_TRACE_03);

        //
        // The BLE core can't handle quick, repeated writes, even if the
        // protocol will allow it. Add some delay to make sure we're not
        // overwhelming the BLE interface.
        //
        if ( pBle->bLastPacketWasTX == true )
        {
            delay_us(AM_BLE_TX_PACKET_SPACING_US);
        }

        if ( am_hal_ble_lock_and_check_status(pBle) )
        {
            //
            // Set the current transfer.
            //
            memcpy(&pBle->sCurrentTransfer, &pBle->sSavedTransfer, sizeof(am_hal_ble_transfer_t));

            //
            // Prepare the DMA.
            //
            BLEIFn(ui32Module)->DMATARGADDR = (uint32_t)pBle->sCurrentTransfer.pui32Data;
            BLEIFn(ui32Module)->DMATOTCOUNT = pBle->sCurrentTransfer.ui16Length;
            BLEIFn(ui32Module)->DMATRIGEN   = BLEIF_DMATRIGEN_DTHREN_Msk;
            BLEIFn(ui32Module)->DMACFG      = (_VAL2FLD(BLEIF_DMACFG_DMADIR, BLEIF_DMACFG_DMADIR_M2P) |
                                  _VAL2FLD(BLEIF_DMACFG_DMAPRI, BLEIF_DMACFG_DMAPRI_HIGH) );

            //
            // Write the command word, and enable the DMA.
            //
            am_hal_ble_cmd_write(pHandle, &pBle->sCurrentTransfer);
            BLEIFn(ui32Module)->DMACFG |= _VAL2FLD(BLEIF_DMACFG_DMAEN, BLEIF_DMACFG_DMAEN_EN);

            //
            // Once this command is gone, the additional STATUS interupts are not necessary.
            //
            am_hal_ble_int_disable(pHandle, BLEIF_INTEN_BLECSSTAT_Msk);
            am_hal_ble_int_clear(pHandle,   BLEIF_INTEN_BLECSSTAT_Msk);
            pBle->bSavedPacket = false;
        }
        else if ( BLEIFn(ui32Module)->BSTATUS_b.SPISTATUS )
        {
            AM_CRITICAL_BEGIN
            BLEIFn(ui32Module)->INTSET = BLEIF_INTEN_BLECSSTAT_Msk;
            AM_CRITICAL_END
        }

        am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_03);
    }

    if ( ui32Status & BLEIF_INTSTAT_CMDCMP_Msk )
    {
        //am_hal_gpio_out_bit_set(4);
        pBle->bCmdComplete = true;
        //am_hal_gpio_out_bit_clear(4);
    }

    if ( ui32Status & BLEIF_INTSTAT_DCMP_Msk )
    {
        //am_hal_gpio_out_bit_set(18);
        pBle->bDmaComplete = true;
        //am_hal_gpio_out_bit_clear(18);
    }
#else // AM_CMSIS_REGS
    if ((ui32Status & AM_REG_BLEIF_INTSTAT_BLECSSTAT_M) &&
        (pBle->bSavedPacket == true))
    {
        am_hal_debug_gpio_set(BLE_DEBUG_TRACE_03);

        //
        // The BLE core can't handle quick, repeated writes, even if the
        // protocol will allow it. Add some delay to make sure we're not
        // overwhelming the BLE interface.
        //
        if ( pBle->bLastPacketWasTX == true )
        {
            delay_us(AM_BLE_TX_PACKET_SPACING_US);
        }

        if ( am_hal_ble_lock_and_check_status(pBle) )
        {
            //
            // Set the current transfer.
            //
            memcpy(&pBle->sCurrentTransfer, &pBle->sSavedTransfer, sizeof(am_hal_ble_transfer_t));

            //
            // Prepare the DMA.
            //
            AM_REGn(BLEIF, ui32Module, DMATARGADDR) = (uint32_t) pBle->sCurrentTransfer.pui32Data;
            AM_REGn(BLEIF, ui32Module, DMATOTCOUNT) =  pBle->sCurrentTransfer.ui16Length;
            AM_REGn(BLEIF, ui32Module, DMATRIGEN) =  AM_REG_BLEIF_DMATRIGEN_DTHREN_M;
            AM_REGn(BLEIF, ui32Module, DMACFG) =  (AM_REG_BLEIF_DMACFG_DMADIR_M2P |
                                                   AM_REG_BLEIF_DMACFG_DMAPRI_HIGH);

            //
            // Write the command word, and enable the DMA.
            //
            am_hal_ble_cmd_write(pHandle, &pBle->sCurrentTransfer);
            AM_REGn(BLEIF, ui32Module, DMACFG) |= AM_REG_BLEIF_DMACFG_DMAEN_EN;

            //
            // Once this command is gone, the additional STATUS interupts are not necessary.
            //

            am_hal_ble_int_disable(pHandle, AM_REG_BLEIF_INTEN_BLECSSTAT_M);
            am_hal_ble_int_clear(pHandle, AM_REG_BLEIF_INTEN_BLECSSTAT_M);
            pBle->bSavedPacket = false;
        }
        else if (AM_BFMn(BLEIF, 0, BSTATUS, SPISTATUS))
        {
            AM_REGan_SET(BLEIF, ui32Module, INTSET,
                         AM_REG_BLEIF_INTEN_BLECSSTAT_M);
        }

        am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_03);
    }

    if (ui32Status & AM_REG_BLEIF_INTSTAT_CMDCMP_M)
    {
        //am_hal_gpio_out_bit_set(4);
        pBle->bCmdComplete = true;
        //am_hal_gpio_out_bit_clear(4);
    }

    if (ui32Status & AM_REG_BLEIF_INTSTAT_DCMP_M)
    {
        //am_hal_gpio_out_bit_set(18);
        pBle->bDmaComplete = true;
        //am_hal_gpio_out_bit_clear(18);
    }
#endif // AM_CMSIS_REGS

    //
    // If we get a command complete, we need to release the wake signal,
    // disable the DMA, release the bus, and call any callback that might
    // exist.
    //
    if ( pBle->bCmdComplete && pBle->bDmaComplete)
    {
//        am_hal_gpio_out_bit_set(14);

        //
        // Clean up our state flags.
        //
        pBle->bCmdComplete = false;
        pBle->bDmaComplete = false;

        //
        // If our FIFOs aren't empty right now, either the DMA didn't finish,
        // or this interrupt handler is somehow being called incorrectly.
        //
#if AM_CMSIS_REGS
        if ( BLEIFn(ui32Module)->FIFOPTR != 0x20002000 )
        {
            return AM_HAL_BLE_FIFO_ERROR;
        }
#else // AM_CMSIS_REGS
        if (AM_REGn(BLEIF, 0, FIFOPTR) != 0x20002000)
        {
            return AM_HAL_BLE_FIFO_ERROR;
        }
#endif // AM_CMSIS_REGS

        //
        // Drop the wake request if we had one, and make sure we remember if
        // the last packet was a transmit packet.
        //
        if ((pBle->sCurrentTransfer.ui8Command == AM_HAL_BLE_WRITE) &&
            (pBle->bSavedPacket == false) &&
            (pBle->bPatchComplete == true))
        {
            pBle->bLastPacketWasTX = true;
            am_hal_ble_wakeup_set(pBle, 0);
        }

        //
        // If this was a read packet, remember that it wasn't a TX packet.
        //
        if (pBle->sCurrentTransfer.ui8Command == AM_HAL_BLE_READ)
        {
            pBle->bLastPacketWasTX = false;
        }

        //
        // Disable the DMA
        //
#if AM_CMSIS_REGS
        BLEIFn(ui32Module)->DMACFG = 0;
#else // AM_CMSIS_REGS
        AM_REGn(BLEIF, ui32Module, DMACFG) = 0;
#endif // AM_CMSIS_REGS


        am_hal_ble_bus_release(pBle);

        if ( pBle->sCurrentTransfer.pfnTransferCompleteCB )
        {
            am_hal_ble_transfer_complete_cb_t pfnCallback;
            uint32_t ui32Length;
            uint8_t *pui8Data;
            void *pvContext;

            pfnCallback = pBle->sCurrentTransfer.pfnTransferCompleteCB;
            pui8Data = (uint8_t * ) pBle->sCurrentTransfer.pui32Data;
            ui32Length = pBle->sCurrentTransfer.ui16Length;
            pvContext = pBle->sCurrentTransfer.pvContext;

            pfnCallback(pui8Data, ui32Length, pvContext);
        }

//        am_hal_gpio_out_bit_clear(14);
    }

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Interrupt Enable
//
//*****************************************************************************
uint32_t
am_hal_ble_int_enable(void *pHandle, uint32_t ui32InterruptMask)
{
    uint32_t ui32Module;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

#if AM_CMSIS_REGS
    AM_CRITICAL_BEGIN
    BLEIFn(ui32Module)->INTEN |= ui32InterruptMask;
    AM_CRITICAL_END
#else // AM_CMSIS_REGS
    AM_REGan_SET(BLEIF, ui32Module, INTEN, ui32InterruptMask);
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Interrupt Enable
//
//*****************************************************************************
uint32_t
am_hal_ble_int_disable(void *pHandle, uint32_t ui32InterruptMask)
{
    uint32_t ui32Module;

    //
    // Check the handle.
    //
    if (!AM_HAL_BLE_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

#if AM_CMSIS_REGS
    AM_CRITICAL_BEGIN
    BLEIFn(ui32Module)->INTEN &= ~ui32InterruptMask;
    AM_CRITICAL_END
#else // AM_CMSIS_REGS
    AM_REGan_CLR(BLEIF, ui32Module, INTEN, ui32InterruptMask);
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Check the status of the interrupts.
//
//*****************************************************************************
uint32_t
am_hal_ble_int_status(void *pHandle, bool bEnabledOnly)
{
    uint32_t ui32Module = ((am_hal_ble_state_t *) pHandle)->ui32Module;

#if AM_CMSIS_REGS
    if (bEnabledOnly)
    {
        uint32_t ui32IntEn = BLEIFn(ui32Module)->INTEN;
        return ( BLEIFn(ui32Module)->INTSTAT & ui32IntEn );
    }
    else
    {
        return BLEIFn(ui32Module)->INTSTAT;
    }
#else // AM_CMSIS_REGS
    if (bEnabledOnly)
    {
        uint32_t ui32IntEn = AM_REGn(BLEIF, ui32Module, INTEN);
        return ( AM_REGn(BLEIF, ui32Module, INTSTAT) & ui32IntEn );
    }
    else
    {
        return AM_REGn(BLEIF, ui32Module, INTSTAT);
    }
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
//
// Clear the interrupt status.
//
//*****************************************************************************
uint32_t
am_hal_ble_int_clear(void *pHandle, uint32_t ui32InterruptMask)
{
    uint32_t ui32Module;

    //
    // Check the handle.
    //
    if ( !AM_HAL_BLE_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Handle is good, so get the module number.
    //
    ui32Module = ((am_hal_ble_state_t *)pHandle)->ui32Module;

#if AM_CMSIS_REGS
    BLEIFn(ui32Module)->INTCLR = ui32InterruptMask;
#else // AM_CMSIS_REGS
    AM_REGn(BLEIF, ui32Module, INTCLR) = ui32InterruptMask;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
}


//*****************************************************************************
//
// check 32768Hz clock is ready.
//
//*****************************************************************************
uint32_t
am_hal_ble_check_32k_clock(void *pHandle)
{
    am_hal_ble_state_t *pBLE = pHandle;
    uint32_t rc32k_clock = 0xFFFFFFFF;

    am_hal_ble_plf_reg_read(pBLE, 0x20006054, &rc32k_clock);
    // Normal 32KHz clock is about 0x8000
    if(rc32k_clock > 0x8200 || rc32k_clock < 0x7B00) {
        return AM_HAL_STATUS_FAIL;
    } else {
        return AM_HAL_STATUS_SUCCESS;
    }
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
