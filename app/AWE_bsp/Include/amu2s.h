//*****************************************************************************
//
//  amu2s.h
//! @file
//!
//! @brief Functions for interfacing with AMU2S module
//!
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
// This is part of revision v2.2.0-7-g63f7c2ba1 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AMU2S_H
#define AMU2S_H

//
// Hardware interface to be defined by user
//
#define AMU2S_SPI_IOM    0//2   // IOM2
#define AMU2S_SPI_CS     0//3   // M2nCE3


typedef enum{
    Amu2s_generic   = 0,    // user defined data
    Amu2s_pcm       = 1,    // raw pcm data from 2 channels
    Amu2s_spp       = 2,    // sound after pre-processing
    Amu2s_opus      = 3,    // opus encoded data (8:1)
    Amu2s_max_types
}amu2s_type_e_t;

#define AMU2S_BUFFER_MAX_INSTANCES      6   // user define,
                                            // slower transfer speed requires higher number,
                                            // larger transfer interval smaller number

#define AMU2S_ERROR_SUCCESS             0x00
#define AMU2S_ERROR_INITIALIZATION      0x01
#define AMU2S_ERROR_DEINITIALIZATION    0x02
#define AMU2S_ERROR_IOM_NUM             0x03
#define AMU2S_ERROR_SENDING             0x04

#define AMU2S_PCM_BYTES                 320*2
#define AMU2S_SPP_BYTES                 160*2
#define AMU2S_OPUS_BYTES                80

#define AMU2S_BUFFER_OVERHEAD_BYTES     14  // 2 (0x0080) + 2 (header) + 2 (length-drv) + 2 (type) + 2 (length-exe) + 2 (packet num) + 2 (checksum)

#define AMU2S_BUFFER_MAX_LEN_BYTES      (AMU2S_BUFFER_MAX_INSTANCES*(AMU2S_BUFFER_OVERHEAD_BYTES + AMU2S_PCM_BYTES + AMU2S_SPP_BYTES + AMU2S_OPUS_BYTES))

extern void amu2s_send(amu2s_type_e_t type, const void* buf, uint32_t len);
extern uint8_t amu2s_init(void);
extern uint8_t amu2s_deinit(void);

static uint16_t amu2s_get_checksum(uint8_t* pBuf, uint32_t numBytes);
static uint8_t amu2s_blocking_write(uint8_t* buf, uint32_t len);
static uint8_t amu2s_nonblocking_write(uint8_t *pui8TxBuffer, uint32_t ui32NumBytes, am_hal_iom_callback_t pfnCallback,void *pCallbackCtxt);

#endif // AMU2S_H
