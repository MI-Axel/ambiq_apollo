//*****************************************************************************
//
//! @file hci_spi_em9304.h
//!
//! @brief This File contains the routines to Transmit and Receive Data from
//! to the EM9304 via the SPI Transport Layer for the BlueLitE/Ethermind BLE
//! host stack.
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
// This is part of revision 1.2.12 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef _H_HCI_SPI_EM9304_
#define _H_HCI_SPI_EM9304_

/** --------------------------------- Header File Inclusion */
#include "BT_common.h"


/* ---------------------------------- Global Definitions */
#if defined BT_SPI
	#define hci_transport_write_data    hci_spi_send_data
#endif /* BT_UART && !BT_BCSP */

/* ---------------------------------- Function Declarations */
/** HCI SPI enable interface */
void hci_spi_enable(void);

/** HCI SPI Initialization & Shutdown */
void hci_spi_init (void);
void hci_spi_bt_init (void);
void hci_spi_bt_shutdown (void);

/* HCI SPI Send Data */
API_RESULT hci_spi_send_data (UCHAR, UCHAR *, UINT16, UCHAR);

#endif /* _H_HCI_SPI_EM9304_ */
