//*****************************************************************************
//
//! @file mspi_flash_loader.c
//!
//! @brief Example demonstrating how to load a binary image from internal
//! flash to MSPI external flash and run the same
//!
//! The binary must be linked to run from MSPI flash address range
//! (as specified by BIN_INSTALL_ADDR). The location and size of the binary
//! in internal flash are specified using BIN_ADDR_FLASH & BIN_SIZE
//!
//! This example has been enhanced to use the new 'binary patching' feature
//!
//! This example will not build if proper startup/linker files are not used
//! The prime_number() routine is open source and is used here under the
//! GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007.  Details,
//! documentation, and the full license for this routine can be found in
//! the third_party/prime_mpi/ directory of the SDK.
//!
//! The prime_number() routine is open source and is used here under the
//! GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007.  Details,
//! documentation, and the full license for this routine can be found in
//! the third_party/prime_mpi/ directory of the SDK.
//!
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
#include "am_bsp.h"
#include "am_devices_mspi_flash.h"
#include "am_util.h"

#ifdef ENABLE_LOGGING
#define DEBUG_PRINT am_util_stdio_printf
#else
#define DEBUG_PRINT(...)
#endif

//*****************************************************************************
//
// Prototype for third-party algorithm.
//
//*****************************************************************************
// n: number of primes, id=process number (), p=number of processes (1)
int prime_number ( int n, int id, int p );

//*****************************************************************************
//
// The Fireball card contains the device
//
//*****************************************************************************
#if FIREBALL_CARD
//
// The Fireball device card multiplexes various devices including each of an SPI
// and I2C FRAM and MSPI flash devices.
// The Fireball device driver controls access to these devices.
// If the Fireball card is not used, FRAM devices can be connected directly
// to appropriate GPIO pins.
//
#include "am_devices_fireball.h"
#endif // FIREBALL_CARD

//*****************************************************************************
//
// Prime routine definitions
//
//*****************************************************************************
//
// 10,000 takes about 5 sec. (on which chip and which compiler?)
//
 #define NUM_OF_PRIMES_IN 10000
 #define EXP_PRIMES 1229
//
// 100,000 takes just under 4 minutes with GCC v5.3 on Apollo2.
// 100,000 takes just under 2.25 minutes with IAR v8.11.1 on Apollo2.
//
// Set target to 100000 (the correct answer is 9592).
//
//#define NUM_OF_PRIMES_IN 100000
//#define EXP_PRIMES 9592

//*****************************************************************************
//
// Other definitions
//
//*****************************************************************************
#define DEFAULT_TIMEOUT         10000

uint32_t        DMATCBBuffer[2560];

am_hal_mspi_dev_config_t      MSPI_Flash_Quad_CE0_MSPIConfig =
{
    .eSpiMode           = AM_HAL_MSPI_SPI_MODE_0,
    .eClockFreq         = AM_HAL_MSPI_CLK_24MHZ,
#if defined(MICRON_N25Q256A)
  .ui8TurnAround        = 3,
#elif defined (CYPRESS_S25FS064S)
  .ui8TurnAround        = 5,
#endif
  .eAddrCfg             = AM_HAL_MSPI_ADDR_3_BYTE,
  .eInstrCfg            = AM_HAL_MSPI_INSTR_1_BYTE,
  .eDeviceConfig        = AM_HAL_MSPI_FLASH_QUAD_CE0,
  .bSeparateIO          = false,
  .bSendInstr           = true,
  .bSendAddr            = true,
  .bTurnaround          = true,
#if defined(MICRON_N25Q256A)
  .ui8ReadInstr         = AM_DEVICES_MSPI_FLASH_FAST_READ,
#elif defined (CYPRESS_S25FS064S)
  .ui8ReadInstr         = AM_DEVICES_MSPI_FLASH_QUAD_IO_READ,
#endif          // TODO - Flag an error if another part.
    .ui8WriteInstr        = AM_DEVICES_MSPI_FLASH_PAGE_PROGRAM,
    .ui32TCBSize          = (sizeof(DMATCBBuffer) / sizeof(uint32_t)),
    .pTCB                 = DMATCBBuffer,
    .scramblingStartAddr  = 0,
    .scramblingEndAddr    = 0,
};

//*****************************************************************************
//
// MSPI Example Main.
//
//*****************************************************************************
int
main(void)
{
    uint32_t      ui32Status;
    void          *pHandle;
    am_hal_mspi_dev_config_t *pMspiCfg = &MSPI_Flash_Quad_CE0_MSPIConfig;
    uint32_t      ui32Result;

    //
    // Set the clock frequency.
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);

    //
    // Set the default cache configuration
    //
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();

    //
    // Configure the board for low power operation.
    //
    am_bsp_low_power_init();

#if 1
    //
    // Initialize the printf interface for UART output.
    //
    am_bsp_uart_printf_enable();
#else
    //
    // Initialize the printf interface for ITM/SWO output.
    //
    am_bsp_itm_printf_enable();
#endif

    //
    // Print the banner.
    //
    am_util_stdio_terminal_clear();
    DEBUG_PRINT("Apollo3 Prime Example from MSPI\n\n");

#if FIREBALL_CARD
    //
    // Set the MUX for the Flash Device
    //
    uint32_t ui32Ret, ui32ID;

#if 1
    //
    // Get Fireball ID and Rev info.
    //
    ui32Ret = am_devices_fireball_control(AM_DEVICES_FIREBALL_STATE_ID_GET, &ui32ID);
    if ( ui32Ret != 0 )
    {
        DEBUG_PRINT("FAIL: am_devices_fireball_control(%d) returned 0x%X.\n",
                             AM_DEVICES_FIREBALL_STATE_ID_GET, ui32Ret);
        return -1;
    }
    else if ( ui32ID == FIREBALL_ID )
    {
        DEBUG_PRINT("Fireball found, ID is 0x%X.\n", ui32ID);
    }
    else
    {
        DEBUG_PRINT("Unknown device returned ID as 0x%X.\n", ui32ID);
    }

    ui32Ret = am_devices_fireball_control(AM_DEVICES_FIREBALL_STATE_VER_GET, &ui32ID);
    if ( ui32Ret != 0 )
    {
        DEBUG_PRINT("FAIL: am_devices_fireball_control(%d) returned 0x%X.\n",
                             AM_DEVICES_FIREBALL_STATE_VER_GET, ui32Ret);
        return -1;
    }
    else
    {
        DEBUG_PRINT("Fireball Version is 0x%X.\n", ui32ID);
    }
#endif

    ui32Ret = am_devices_fireball_control(AM_DEVICES_FIREBALL_STATE_TWIN_QUAD_CE0_CE1, 0);
    if ( ui32Ret != 0 )
    {
        DEBUG_PRINT("FAIL: am_devices_fireball_control(%d) returned 0x%X.\n",
                             AM_DEVICES_FIREBALL_STATE_TWIN_QUAD_CE0_CE1, ui32Ret);
        return -1;
    }
#endif // FIREBALL_CARD

    //
    // Configure the MSPI and Flash Device.
    //
    ui32Status = am_devices_mspi_flash_init(pMspiCfg, &pHandle);
    if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
    {
        DEBUG_PRINT("Failed to configure the MSPI and Flash Device correctly!\n");
        return -1;
    }

    //
    // Read the MSPI Device ID.
    //
    ui32Status = am_devices_mspi_flash_id();
    if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
    {
        DEBUG_PRINT("Failed to read Flash Device ID!\n");
        return -1;
    }

    //
    // Set up for XIP operation.
    //
    DEBUG_PRINT("Putting the MSPI and External Flash into XIP mode\n");
    ui32Status = am_devices_mspi_flash_enable(true, false);
    if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
    {
        DEBUG_PRINT("Failed to put the MSPI into XIP mode!\n");
        return -1;
    }

    //
    // Call the prime function
    //
    while(1)
    {
        //
        // Determine the number of primes for the given value.
        //
        ui32Result = prime_number(NUM_OF_PRIMES_IN, 0, 1);

        //
        // Print the result
        //
        if ( ui32Result == EXP_PRIMES )
        {
            DEBUG_PRINT("Pass: number of primes for %d is %d.\n", NUM_OF_PRIMES_IN, ui32Result);
        }
        else
        {
            DEBUG_PRINT("ERROR: Invalid result. Expected %d, got %d.\n", NUM_OF_PRIMES_IN, ui32Result);
        }

        am_hal_flash_delay(FLASH_CYCLES_US(10000));

    }
}

