//*****************************************************************************
//
//! @file hci_spi_internal.h
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
#ifndef _H_HCI_SPI_INTERNAL_
#define _H_HCI_SPI_INTERNAL_

/* ---------------------------------- Header File Inclusion */
#include "BT_common.h"
#include "BT_api.h"
#include "BT_serial.h"
#include "hci_spi_em9304.h"

/* ---------------------------------- HCI UART Debug */
#ifdef HCI_SPI_DEBUG

#define HCI_SPI_ERR(...)               BT_debug_error(BT_MODULE_ID_TRANSPORT, __VA_ARGS__)
#define HCI_SPI_TRC(...)               BT_debug_trace(BT_MODULE_ID_TRANSPORT, __VA_ARGS__)
#define HCI_SPI_INF(...)               BT_debug_info(BT_MODULE_ID_TRANSPORT, __VA_ARGS__)

#define HCI_SPI_debug_dump_bytes(data, datalen) BT_debug_dump_bytes(BT_MODULE_ID_TRANSPORT, (data), (datalen))

#else /* HCI_SPI_DEBUG */

#define HCI_SPI_ERR                    BT_debug_null
#define HCI_SPI_TRC                    BT_debug_null
#define HCI_SPI_INF                    BT_debug_null

#define HCI_SPI_debug_dump_bytes(data, datalen)

#endif /* HCI_SPI_DEBUG */


/* ---------------------------------- Global Definitions */
#define hci_spi_lock(mutex)            BT_thread_mutex_lock(&mutex)
#define hci_spi_unlock(mutex)          BT_thread_mutex_unlock(&mutex)

#define hci_spi_signal(cond)           BT_thread_cond_signal(&cond)
#define hci_spi_wait(cond, mutex)      BT_thread_cond_wait(&cond,&mutex)


/* ---------------------------------- Internal Functions */


#endif /* _H_HCI_SPI_INTERNAL_ */

