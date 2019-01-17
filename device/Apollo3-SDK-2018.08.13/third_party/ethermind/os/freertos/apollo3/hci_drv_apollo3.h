//*****************************************************************************
//
//! @file hci_drv_apollo3.h
//!
//! @brief Support functions for the Nationz BTLE radio in Apollo3.
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
#ifndef HCI_DRV_APOLLO3_H
#define HCI_DRV_APOLLO3_H

/** --------------------------------- Header File Inclusion */
#include "BT_common.h"


/* ---------------------------------- Global Definitions */
#if defined BT_SPI
	#define hci_transport_write_data    hci_spi_send_data
#endif /* BT_UART && !BT_BCSP */

/* ---------------------------------- Function Declarations */

/** HCI SPI Initialization & Shutdown */
void hci_spi_init (void);
void hci_spi_bt_init (void);
void hci_spi_bt_shutdown (void);

/* HCI SPI Send Data */
API_RESULT hci_spi_send_data (UCHAR, UCHAR *, UINT16, UCHAR);

//*****************************************************************************
//
// NATIONZ vendor specific events
//
//*****************************************************************************


// Tx power level in dBm.
typedef enum
{
  TX_POWER_LEVEL_MINUS_10P0_dBm = 0x3,
  TX_POWER_LEVEL_0P0_dBm = 0x8,
  TX_POWER_LEVEL_PLUS_3P0_dBm = 0xF,
  TX_POWER_LEVEL_INVALID = 0x10,
}txPowerLevel_t;


bool HciVsA3_SetRfPowerLevelEx(txPowerLevel_t txPowerlevel);
void HciVsA3_SetBDAddr(uint8_t *bd_addr);

#endif // HCI_DRV_APOLLO3_H
