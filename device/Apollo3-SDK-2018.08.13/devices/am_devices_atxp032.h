//*****************************************************************************
//
//! @file am_devices_atxp032.h
//!
//! @brief Adesto MSPI Flash driver.
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

#ifndef AM_DEVICES_ATXP032_H
#define AM_DEVICES_ATXP032_H

#ifdef __cplusplus
extern "C"
{
#endif
  
  //*****************************************************************************
  //
  // Global definitions for flash commands
  //
  //*****************************************************************************
#define AM_DEVICES_ATXP032_WRITE_STATUS         0x01
#define AM_DEVICES_ATXP032_PAGE_PROGRAM         0x02
#define AM_DEVICES_ATXP032_WRITE_DISABLE        0x04
#define AM_DEVICES_ATXP032_READ_STATUS          0x05
#define AM_DEVICES_ATXP032_WRITE_ENABLE         0x06
#define AM_DEVICES_ATXP032_READ                 0x0B
#define AM_DEVICES_ATXP032_BLOCK_ERASE_4K       0x20
#define AM_DEVICES_ATXP032_WRITE_STATUS_BYTE2   0x31
#define AM_DEVICES_ATXP032_PROTECT_SECTOR       0x36
#define AM_DEVICES_ATXP032_ENTER_QUAD_MODE      0x38
#define AM_DEVICES_ATXP032_UNPROTECT_SECTOR     0x39
#define AM_DEVICES_ATXP032_BLOCK_ERASE_32K      0x52
#define AM_DEVICES_ATXP032_WRITE_STATUS_CTRL    0x71
#define AM_DEVICES_ATXP032_READ_ID              0x9F
#define AM_DEVICES_ATXP032_BULK_ERASE           0xC7
#define AM_DEVICES_ATXP032_SECTOR_ERASE         0xD8
#define AM_DEVICES_ATXP032_ENTER_OCTAL_MODE     0xE8
#define AM_DEVICES_ATXP032_RESET                0xF0
#define AM_DEVICES_ATXP032_RETURN_TO_SPI_MODE   0xFF
  
  //*****************************************************************************
  //
  // Global definitions for the flash status register
  //
  //*****************************************************************************
#define AM_DEVICES_ATXP032_RSTE        0x00000010        // Reset enable
#define AM_DEVICES_ATXP032_WEL         0x00000002        // Write enable latch
#define AM_DEVICES_ATXP032_WIP         0x00000001        // Operation in progress
  
  //*****************************************************************************
  //
  // Global definitions for the flash size information
  //
  //*****************************************************************************
#define AM_DEVICES_ATXP032_PAGE_SIZE       0x100    //256 bytes, minimum program unit
#define AM_DEVICES_ATXP032_SUBSECTOR_SIZE  0x1000   //4096 bytes
#define AM_DEVICES_ATXP032_SECTOR_SIZE     0x10000  //65536 bytes
//#define AM_DEVICES_ATXP032_SECTOR_SIZE     0x01000  //4096 bytes.  Reduced to avoid CQ overflow.
#define AM_DEVICES_ATXP032_MAX_SECTORS     256      // Sectors within 3-byte address range.
  
  //*****************************************************************************
  //
  // Device specific identification.
  //
  //*****************************************************************************
#define AM_DEVICES_ATXP032_ID        0x0043A700
#define AM_DEVICES_ATXP032_ID_MASK   0x00FFFFFF
  
  //*****************************************************************************
  //
  // Global definitions for the MSPI instance to use.
  //
  //*****************************************************************************
#define AM_DEVICES_ATXP032_MSPI_INSTANCE        0
  
  //*****************************************************************************
  //
  // Global type definitions.
  //
  //*****************************************************************************
  typedef enum
  {
    AM_DEVICES_ATXP032_STATUS_SUCCESS,
    AM_DEVICES_ATXP032_STATUS_ERROR
  } am_devices_atxp032_status_t;
  
  //*****************************************************************************
  //
  // External function definitions.
  //
  //*****************************************************************************
  extern volatile uint32_t g_MSPIInterruptStatus;
  
  extern uint32_t am_devices_atxp032_init(am_hal_mspi_dev_config_t *psMSPISettings, 
                                          uint32_t ui32DMACtrlBufferSize,
                                          uint32_t *pDMACtrlBuffer);
  
  extern uint32_t am_devices_atxp032_deinit(am_hal_mspi_dev_config_t *psMSPISettings);
  
  extern uint32_t am_devices_atxp032_id(uint32_t *pDeviceID);
  
  extern uint32_t am_devices_atxp032_reset(void);
  
  extern uint32_t am_devices_atxp032_status(uint32_t *pStatus);
  
  extern uint32_t am_devices_atxp032_read(uint8_t *pui8RxBuffer, 
                                          uint32_t ui32ReadAddress,
                                          uint32_t ui32NumBytes,
                                          bool bWaitForCompletion);
  
  extern uint32_t am_devices_atxp032_write(uint8_t *ui8TxBuffer,
                                           uint32_t ui32WriteAddress,
                                           uint32_t ui32NumBytes);
  
  extern uint32_t am_devices_atxp032_mass_erase(void);
  
  extern uint32_t am_devices_atxp032_sector_erase(uint32_t ui32SectorAddress);
  
  extern uint32_t am_devices_atxp032_enable(bool bEnableXIP, bool bEnableScrambling);
  
  extern uint32_t am_devices_atxp032_disable_xip(void);
  
#ifdef __cplusplus
}
#endif

#endif // AM_DEVICES_ATXP032_H

