//*****************************************************************************
//
//! @file am_hal_ble_patch_b0.c
//!
//! @brief This is a binary patch for the BLE core.
//!
//! @addtogroup
//! @ingroup
//! @{
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

#include "am_mcu_apollo.h"

//*****************************************************************************
//
// Patches included in this file.
//
//*****************************************************************************
am_hal_ble_patch_t am_ble_buffer_patch_b0;
am_hal_ble_patch_t am_ble_performance_patch_b0;
am_hal_ble_patch_t am_ble_performance_copy_patch_b0;
am_hal_ble_patch_t am_ble_nvds_patch_b0;

//*****************************************************************************
//
// Patch application order.
//
//*****************************************************************************
am_hal_ble_patch_t *am_hal_ble_default_patch_array_b0[] =
{
    // FTCODE patches (type 0xAA)

    // RAMCODE patches (type 0xBB)
      &am_ble_performance_patch_b0,

    // Standard patches (type 0xCC)
      &am_ble_buffer_patch_b0,

    // nvds param (type 0xDD)
      &am_ble_nvds_patch_b0,
};

am_hal_ble_patch_t *am_hal_ble_default_copy_patch_array_b0[] =
{
    // FTCODE patches (type 0xAA)

    // RAMCODE patches (type 0xBB)
      &am_ble_performance_copy_patch_b0,

};

#define AM_HAL_BLE_NUM_DEFAULT_PATCHES_B0                                        \
    (sizeof(am_hal_ble_default_patch_array_b0) /                                 \
     sizeof(am_hal_ble_default_patch_array_b0[0]))

am_hal_ble_patch_t **am_hal_ble_default_patches_b0 = am_hal_ble_default_patch_array_b0;
am_hal_ble_patch_t **am_hal_ble_default_copy_patches_b0 = am_hal_ble_default_copy_patch_array_b0;

const uint32_t am_hal_ble_num_default_patches_b0 = AM_HAL_BLE_NUM_DEFAULT_PATCHES_B0;


//*****************************************************************************
//
// Initial patch for B0 silicon.
//
// Patch Name:  RAMCODE PATCH ENTRY v0.1
// Date:        2019-01-11
//
//*****************************************************************************


 am_hal_ble_buffer(0x0038)am_ble_performance_patch_data_b0 =
{
    .bytes =
    {
		0x00,0x11,0x34,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0xc5,0x01,
		0x39,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x20,0x70,0x47	 
    }
};

am_hal_ble_patch_t am_ble_performance_patch_b0 =
{
    .ui32Type = 0xBB,
    .ui32Length = 0x0038,
    .ui32CRC = 0xf1e1,
    .pui32Data = am_ble_performance_patch_data_b0.words,
};

//*****************************************************************************
//
// Initial patch for B0 silicon.
//
// Patch Name:  Function Patch  v0.1
// Date:        2019-01-11
//
// Adjust HCI timing check for WAKE signal used as sync between host and controller.
//
//*****************************************************************************


 am_hal_ble_buffer(0x0008)am_ble_buffer_patch_data_b0 =
{
    .bytes =
    {
		0x00,0x22,0x08,0x00,0x00,0x00,0x00,0x00	 
    }
};

am_hal_ble_patch_t am_ble_buffer_patch_b0 =
{
    .ui32Type = 0xCC,
    .ui32Length = 0x0008,
    .ui32CRC = 0x6029,
    .pui32Data = am_ble_buffer_patch_data_b0.words,
};

//*****************************************************************************
//
// Initial patch for B0 silicon.
//
// Patch Name:  NVDS  v0.1
// Date:        2019-01-11
//
// Increases the number of internal buffers in the BLE core from one to four.
//
//*****************************************************************************

//nvds test
 am_hal_ble_buffer(0x00cd)am_ble_buffer_nvds_data_b0 =
{
    .bytes =
    {
		0x4e,0x56,0x44,0x53, //NVDS_MAGIC_NUMBER
		0x01,0x06,0x06,0xef,0xbb,0x23,0x88,0x77,0x66, //bluetooth address
		0x02,0x06,0x0a,0x4e,0x5a,0x38,0x38,0x30,0x31,0x56,0x31,0x41,0x00, //device name
		0x03,0x06,0x01,0x00, //system clock frequency, 00=32MHz  01=24MHz  others=16MHz
		0x04,0x06,0x01,0x28, //internal dvdd voltage level control if using 0.9V from MCU side
		0x05,0x06,0x02,0x34,0x00, //no use
		0x06,0x06,0x08,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //ble feature mask
		0x07,0x06,0x02,0xf4,0x01, //32K clock drift, 0x01f4 = 500 ppm
		0x08,0x06,0x01,0x00, //01 for BQB qualification, 00 for normal usage
		0x09,0x06,0x01,0x02, //clock source selection, 00 = internal RC32KHz, 02= use Apollo3 MCU 32.768KHz
		0x0a,0x06,0x04,0x00,0x00,0x00,0x00, //0x00000000 = auto detect and low frequency clock calibration
		0x0b,0x06,0x01,0x96, //rx_ifs  0x96 = 150us
		0x0c,0x06,0x02,0xf4,0x01, //sleep clock accuracy in ppm, 0x01f4 = 500 ppm
		0x0d,0x06,0x02,0xb8,0x0b, //duration allowed for XO32M stabilization from external wakeup signal
		0x0e,0x06,0x02,0xb8,0x0b, //duration allowed for XO32M stabilization from internal wakeup signal
		0x0f,0x06,0x02,0x2c,0x01, //duration allowed for radio to leave low power mode
		0x10,0x06,0x04,0x00,0xc2,0x01,0x00, //set UART_BAUDRATE
		0x11,0x06,0x01,0x01, //sleep algorithm enabled
		0x12,0x06,0x01,0x01, //external wake-up support
		0x13,0x06,0x02,0x90,0x02, //duration of sleep and wake-up algorithm
		0x14,0x06,0x02,0x60,0x00, //BLE Company ID
		0x15,0x06,0x01,0x08, //BLE major version
		0x16,0x06,0x01,0x03, //BLE minor version
		0x17,0x06,0x01,0x29, //BLE SW version build
		0x18,0x06,0x02,0xdc,0x05, //advertising interval (undirect)
		0x19,0x06,0x02,0xe2,0x04, //advertising interval (direct)
		0x20,0x06,0x01,0x01, //agc switch
		0x21,0x06,0x01,0x01, //EA programming latency
		0x22,0x06,0x01,0x00, //EA asap latency
		0x23,0x06,0x01,0x96, //rx_ifs  0x96 = 150us
		0x24,0x06,0x04,0x42,0x02,0x60,0x09, //radio TRX timing
		0x25,0x06,0x01,0x11, //modem polarity setting
		0x26,0x06,0x01,0x00, //modem sync setting
		0x27,0x06,0x01,0x03, //BLE reset delay
		0x28,0x06,0x02,0xf6,0x3f, //initial agc gain setting
		0x29,0x06,0x01,0x0f, //initial Tx output power, 0x0f is +4dBm
		0x2d,0x06,0x01,0x00, //2 byte mode switch, 01 to enable
		0x2e,0x06,0x01,0x01, //instant indication
		0x35,0x06,0x01,0x08, //maximum Tx ouput power setting
		0x37,0x06,0x01,0x00, //RC32K calibration control, 0xAA to enable
		0x00,0x00,0x00,0x00	 //dummy
    }
};

am_hal_ble_patch_t am_ble_nvds_patch_b0 =
{
    .ui32Type = 0xDD,
    .ui32Length = 0x00cd,
    .ui32CRC = 0x112b,
    .pui32Data = am_ble_buffer_nvds_data_b0.words,
};

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
