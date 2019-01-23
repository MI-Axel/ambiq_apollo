//*****************************************************************************
//
//! @file am_devices_fireball.c
//!
//! @brief Control the Ambiq FIREBALL board.
//!
//! This module contains functions for controlling the Ambiq internal FIREBALL
//! board.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2019, Ambiq Micro
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
// This is part of revision v2.0.0 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices_fireball.h"

//*****************************************************************************
//
// Macros.
//
//*****************************************************************************
//
// The IOM to be used is defined by the Apollo3 MCU Engineering Board.
//
#define FIREBALL_IOM_MODULE     5

//
// Helper macros
//
#define FB_CMD(op, pio)     (((op & 0x03) << 6) | ((pio & 0x3F) << 0))
#define FB_OP_LOW           0
#define FB_OP_HI            1
#define FB_OP_TRI           2

//
// Fireball version info
//
#define FIRBBALL_OFFSET_ID      0x40    // (16 bits at 0x40/0x41)
#define FIREBALL_OFFSET_SWREV   0x42    // 1 byte

//
// Apollo3 IOM5 pin definitions.
// These should be defined in the BSP.  If not, use these for Apollo3.
//
#if 0
#define am_bsp_pin_enable(name)                                               \
    am_hal_gpio_pin_config(AM_BSP_GPIO_ ## name, AM_BSP_GPIO_CFG_ ## name);

#define AM_BSP_GPIO_IOM5_MISO           49
#define AM_BSP_GPIO_CFG_IOM5_MISO       AM_HAL_PIN_49_M5MISO
#define AM_BSP_GPIO_IOM5_MOSI           47
#define AM_BSP_GPIO_CFG_IOM5_MOSI       AM_HAL_PIN_47_M5MOSI
#define AM_BSP_GPIO_IOM5_SCK            48
#define AM_BSP_GPIO_CFG_IOM5_SCK        (AM_HAL_PIN_48_M5SCK | AM_HAL_GPIO_INPEN | AM_HAL_GPIO_HIGH_DRIVE)
#define AM_BSP_GPIO_FIREBALL_CE         30
#define AM_BSP_GPIO_CFG_FIREBALL_CE     (AM_HAL_PIN_30_NCE30 | (AM_REG_GPIO_CFGD_GPIO30OUTCFG_M5nCE3 >> 16) | AM_HAL_GPIO_DRIVE_12MA)
#define AM_BSP_FIREBALL_CE_CHNL         3
#endif


//*****************************************************************************
//
// Globals.
//
//*****************************************************************************
static void *g_pIOM5Handle = 0;

static const am_hal_iom_config_t g_FireballIOM5Config =
{
    .eInterfaceMode     = AM_HAL_IOM_SPI_MODE,
    .ui32ClockFreq      = AM_HAL_IOM_1MHZ,
    .eSpiMode           = AM_HAL_IOM_SPI_MODE_0,
    .pNBTxnBuf          = 0,
    .ui32NBTxnBufLength = 0
};

static am_hal_iom_transfer_t g_sFireballTransaction =
{
    .uPeerInfo.ui32SpiChipSelect = 0,
    .ui32InstrLen     = 0,
    .ui32Instr        = 0,
    .ui32NumBytes     = 0,
    .eDirection       = AM_HAL_IOM_TX,
    .pui32TxBuffer    = 0,
    .pui32RxBuffer    = 0,
    .bContinue        = false,
    .ui8RepeatCount   = 0,
    .ui8Priority      = 0
};

static am_hal_iom_transfer_t g_sFireballReadIDTransaction =
{
    .uPeerInfo.ui32SpiChipSelect = 0,
    .ui32InstrLen     = 0,
    .ui32Instr        = 0,
    .ui32NumBytes     = 0,
    .eDirection       = AM_HAL_IOM_RX,
    .pui32TxBuffer    = 0,
    .pui32RxBuffer    = 0,
    .bContinue        = false,
    .ui8RepeatCount   = 0,
    .ui8Priority      = 0
};

//*****************************************************************************
// fireball_init()
//*****************************************************************************
static uint32_t
fireball_init(uint32_t ui32Board, uint32_t ui32Module)
{
    if ( ui32Board != 1 )
    {
        return 1;
    }

    if ( g_pIOM5Handle )
    {
        //
        // Already initialized
        //
        return 0;
    }

    //
    // Fireball is communicated with from the Apollo3 MCU engineering board via
    // SPI on IOM5.
    // The 1-byte commands are defined as follows:
    //  [7:6] = OP
    //  [5:0] = GPIO number
    // OP:
    //  0 = Set the GPIO low.
    //  1 = Set the GPIO high.
    //  2 = Set the GPIO tri-state.
    //  3 = Reserved.
    //
    // Note - the commands are handled by a macro, FB_CMD(op, pio).
    //

    //
    // Set up IOM5 to talk to Fireball.
    //
    if ( am_hal_iom_initialize(ui32Module, &g_pIOM5Handle)                  ||
         am_hal_iom_power_ctrl(g_pIOM5Handle, AM_HAL_SYSCTRL_WAKE, false)   ||
         am_hal_iom_configure(g_pIOM5Handle,
                              (am_hal_iom_config_t*)&g_FireballIOM5Config)  ||
         am_hal_iom_enable(g_pIOM5Handle))
    {
        return 2;
    }

    //
    // Set up the pins, including CE, for Apollo3 IOM5 pins that will
    // communicate with the Apollo IOS SPI device.
    //
#if AM_APOLLO3_GPIO
    am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM5_SCK,    g_AM_BSP_GPIO_IOM5_SCK);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM5_MISO,   g_AM_BSP_GPIO_IOM5_MISO);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM5_MOSI,   g_AM_BSP_GPIO_IOM5_MOSI);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_FIREBALL_CE, g_AM_BSP_GPIO_FIREBALL_CE);
#else // AM_APOLLO3_GPIO
    am_bsp_pin_enable(IOM5_SCK);
    am_bsp_pin_enable(IOM5_MISO);
    am_bsp_pin_enable(IOM5_MOSI);
    am_bsp_pin_enable(FIREBALL_CE);
#endif // AM_APOLLO3_GPIO

    //
    // Initialize the write transaction structure.
    // After this, we should only need to set ui32InstrLen and ui32Instr.
    //
    g_sFireballTransaction.uPeerInfo.ui32SpiChipSelect = AM_BSP_FIREBALL_CE_CHNL;
    g_sFireballTransaction.ui32InstrLen     = 0;
    g_sFireballTransaction.ui32Instr        = 0;
    g_sFireballTransaction.ui32NumBytes     = 0;
    g_sFireballTransaction.eDirection       = AM_HAL_IOM_TX;
    g_sFireballTransaction.pui32TxBuffer    = 0;
    g_sFireballTransaction.pui32RxBuffer    = 0;
    g_sFireballTransaction.bContinue        = false;
    g_sFireballTransaction.ui8RepeatCount   = 0;
    g_sFireballTransaction.ui8Priority      = 0;

    //
    // Initialize the read transaction structure.
    // After this, we should only need to set ui32InstrLen, ui32Instr, and
    // pui32RxBuffer.
    //
    g_sFireballReadIDTransaction.uPeerInfo.ui32SpiChipSelect = AM_BSP_FIREBALL_CE_CHNL;
    g_sFireballReadIDTransaction.ui32InstrLen     = 0;
    g_sFireballReadIDTransaction.ui32Instr        = 0;
    g_sFireballReadIDTransaction.ui32NumBytes     = 0;
    g_sFireballReadIDTransaction.eDirection       = AM_HAL_IOM_RX;
    g_sFireballReadIDTransaction.pui32TxBuffer    = 0;
    g_sFireballReadIDTransaction.pui32RxBuffer    = 0;
    g_sFireballReadIDTransaction.bContinue        = false;
    g_sFireballReadIDTransaction.ui8RepeatCount   = 0;
    g_sFireballReadIDTransaction.ui8Priority      = 0;

    return 0;

} // fireball_init()

//*****************************************************************************
// fireball_write_cmd()
//*****************************************************************************
static uint32_t
fireball_write_cmd(uint32_t ui32FireballCmd)
{
    //
    // On the Apollo slave, bit7 of the offset byte determines write or read.
    // 1=write, 0=read.
    //
    g_sFireballTransaction.ui32InstrLen     = 2;
    g_sFireballTransaction.ui32Instr        = (0x80 << 8) |
                                              (ui32FireballCmd & 0xFF);

    return am_hal_iom_blocking_transfer(g_pIOM5Handle,
                                        &g_sFireballTransaction);

} // fireball_write_cmd()

//*****************************************************************************
// fireball_id_get()
//*****************************************************************************
static uint32_t
fireball_id_get(uint32_t *pui32ID)
{
    //
    // The ID is at offset 0x40, the SW Rev at 0x42.
    // We'll read all 3 bytes here.
    // On the Apollo slave, bit7 of the offset byte determines write or read.
    // 1=write, 0=read.
    //
    g_sFireballReadIDTransaction.ui32InstrLen     = 1;
    g_sFireballReadIDTransaction.ui32Instr        = 0x00 | FIRBBALL_OFFSET_ID;
    g_sFireballReadIDTransaction.ui32NumBytes     = 3;
    g_sFireballReadIDTransaction.pui32RxBuffer    = pui32ID;

    return am_hal_iom_blocking_transfer(g_pIOM5Handle,
                                        &g_sFireballReadIDTransaction);

} // fireball_id_get()

//*****************************************************************************
// fireball_set()
//*****************************************************************************
static uint32_t
fireball_set(uint64_t ui64GPIOLowMask, uint64_t ui64GPIOHighMask)
{
    uint32_t ui32GPIOnum, ui32Ret;

    ui32GPIOnum = 0;
    while ( ui64GPIOLowMask  ||  ui64GPIOHighMask )
    {
        if ( ui64GPIOLowMask & 0x1 )
        {
            ui32Ret = fireball_write_cmd(FB_CMD(FB_OP_LOW, ui32GPIOnum));
            if ( ui32Ret )
            {
                return (1 << 8) | ui32Ret;
            }

            //
            // Give the Fireball Apollo a little time to process the command.
            //
            am_hal_flash_delay(FLASH_CYCLES_US(1));
        }
        ui64GPIOLowMask >>= 1;

        if ( ui64GPIOHighMask & 0x1 )
        {
            ui32Ret = fireball_write_cmd(FB_CMD(FB_OP_HI, ui32GPIOnum));
            if ( ui32Ret )
            {
                return (2 << 8) | ui32Ret;
            }

            //
            // Give the Fireball Apollo a little time to process the command.
            //
            am_hal_flash_delay(FLASH_CYCLES_US(1));
        }
        ui64GPIOHighMask >>= 1;
        ui32GPIOnum++;
    }

    return 0;

} // fireball_set()

//*****************************************************************************
// device_reset()
//*****************************************************************************
static uint32_t
device_reset(uint32_t ui32GPIO, bool bAssertLow)
{
    uint32_t ui32Assert, ui32Deassert;

    ui32Assert   = bAssertLow ? FB_OP_LOW : FB_OP_HI;
    ui32Deassert = bAssertLow ? FB_OP_HI  : FB_OP_LOW;

    //
    // Assert the reset signal.
    //
    if ( fireball_write_cmd(FB_CMD(ui32Assert, ui32GPIO)) )
    {
        return 1;
    }

    //
    // Reset pulse width.   (1ms)
    //
    am_hal_flash_delay(FLASH_CYCLES_US(1000));

    //
    // De-assert the reset signal.
    //
    if ( fireball_write_cmd(FB_CMD(ui32Deassert, ui32GPIO)) )
    {
        return 3;
    }

    return 0;

} // device_reset()

//*****************************************************************************
//
//  am_devices_fireball_control()
//  Set FIREBALL state.
//
//*****************************************************************************
uint32_t
am_devices_fireball_control(am_devices_fireball_control_e eControl,
                            void *pArgs)
{
    uint64_t ui64GPIOLowMask, ui64GPIOHighMask;

    if ( eControl >= AM_DEVICES_FIREBALL_STATE_INVALID )
    {
        return 1;
    }

    if ( fireball_init(1, FIREBALL_IOM_MODULE) )
    {
        return 2;
    }

    switch ( eControl )
    {
        uint32_t ui32Ret, ui32Val;

        case AM_DEVICES_FIREBALL_STATE_ID_GET:
            ui32Ret = fireball_id_get(&ui32Val);
            ui32Val = ui32Ret ? 0 : ui32Val & 0xFFFF;
            *((uint32_t*)pArgs) = ui32Val;
            return ui32Ret;

        case AM_DEVICES_FIREBALL_STATE_VER_GET:
            ui32Ret = fireball_id_get(&ui32Val);
            ui32Val = ui32Ret ? 0 : (ui32Val >> 16) & 0xFF;
            *((uint32_t*)pArgs) = ui32Val;
            return ui32Ret;

        case AM_DEVICES_FIREBALL_STATE_SPI_FLASH:
            //
            // GPIO LOW:  4-7,10,11
            // GPIO HIGH: -
            //
            ui64GPIOLowMask  = ((uint64_t)0xF << 4)  | ((uint64_t)0x3 << 10);
            ui64GPIOHighMask = ((uint64_t)0x0 << 0);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_SPI_FRAM:
            //
            // GPIO LOW:  4-7,10
            // GPIO HIGH: 11
            //
            ui64GPIOLowMask  = ((uint64_t)0xF << 4)  | ((uint64_t)0x1 << 10);
            ui64GPIOHighMask = ((uint64_t)0x1 << 11);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_I2C_IOM0:
            //
            // GPIO LOW:  5,12-13
            // GPIO HIGH: 4
            //
            ui64GPIOLowMask  = ((uint64_t)0x1 << 5)  | ((uint64_t)0x3 << 12);
            ui64GPIOHighMask = ((uint64_t)0x1 << 4);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_I2C_IOM1:
            //
            // GPIO LOW:  5,12
            // GPIO HIGH: 4,13
            //
            ui64GPIOLowMask  = ((uint64_t)0x1 << 5)  | ((uint64_t)0x1 << 12);
            ui64GPIOHighMask = ((uint64_t)0x1 << 4)  | ((uint64_t)0x1 << 13);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_I2C_IOM2:
            //
            // GPIO LOW:  5,13
            // GPIO HIGH: 4,12
            //
            ui64GPIOLowMask  = ((uint64_t)0x1 << 5)  | ((uint64_t)0x1 << 13);
            ui64GPIOHighMask = ((uint64_t)0x1 << 4)  | ((uint64_t)0x1 << 12);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_I2C_IOM3:
            //
            // GPIO LOW:  5,14-15
            // GPIO HIGH: 4
            //
            ui64GPIOLowMask  = ((uint64_t)0x1 << 5)  | ((uint64_t)0x3 << 14);
            ui64GPIOHighMask = ((uint64_t)0x1 << 4);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_I2C_IOM4:
            //
            // GPIO LOW:  5,14
            // GPIO HIGH: 4,15
            //
            ui64GPIOLowMask  = ((uint64_t)0x1 << 5)  | ((uint64_t)0x1 << 14);
            ui64GPIOHighMask = ((uint64_t)0x1 << 4)  | ((uint64_t)0x1 << 15);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_I2C_IOM5:
            //
            // GPIO LOW:  5,15
            // GPIO HIGH: 4,14
            //
            ui64GPIOLowMask  = ((uint64_t)0x1 << 5)  | ((uint64_t)0x1 << 15);
            ui64GPIOHighMask = ((uint64_t)0x1 << 4)  | ((uint64_t)0x1 << 14);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_OCTAL_FLASH_CE0:
            //
            // GPIO LOW:  8-9,35-36
            // GPIO HIGH: 34,37
            //
            ui64GPIOLowMask  = ((uint64_t)0x3 << 8)  | ((uint64_t)0x3 << 35);
            ui64GPIOHighMask = ((uint64_t)0x1 << 34) | ((uint64_t)0x1 << 37);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_OCTAL_FLASH_CE1:
            //
            // GPIO LOW:  8-9,37
            // GPIO HIGH: 36
            //
            ui64GPIOLowMask  = ((uint64_t)0x3 << 8) | ((uint64_t)0x1 << 37);
            ui64GPIOHighMask = ((uint64_t)0x1 << 36);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_TWIN_QUAD_CE0_CE1:
            //
            // GPIO LOW:  8-9,35-37
            // GPIO HIGH: 34
            //
            ui64GPIOLowMask  = ((uint64_t)0x3 << 8) | ((uint64_t)0x7 << 35);
            ui64GPIOHighMask = ((uint64_t)0x1 << 34);
            return fireball_set(ui64GPIOLowMask, ui64GPIOHighMask);

        case AM_DEVICES_FIREBALL_STATE_ALL_RESET:
            //
            // SX9300:  43
            // BNO055:  42
            // MSPI:    41
            // MKB1:    40
            // MKB2:    39
            //
            device_reset(43, true);
            device_reset(42, true);
            device_reset(41, true);
            device_reset(40, false);
            device_reset(39, false);
            return 0;

        case AM_DEVICES_FIREBALL_STATE_SX9300_RESET:
            return device_reset(43, true);

        case AM_DEVICES_FIREBALL_STATE_BNO055_RESET:
            return device_reset(42, true);

        case AM_DEVICES_FIREBALL_STATE_MSPI_RESET:
            return device_reset(41, true);

        case AM_DEVICES_FIREBALL_STATE_MKB1_RESET:
            //
            // The 2 click reset signals actually drive a transistor.
            // Therefore, the signal ends up inverted.
            //
            return device_reset(40, false);

        case AM_DEVICES_FIREBALL_STATE_MKB2_RESET:
            //
            // The 2 click reset signals actually drive a transistor.
            // Therefore, the signal ends up inverted.
            //
            return device_reset(39, false);

        default:
            return 0xdeadbeef;

    } // switch()

} // am_devices_fireball_control()

