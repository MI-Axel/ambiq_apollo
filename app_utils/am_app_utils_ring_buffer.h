//*****************************************************************************
//
//! @file am_app_utils_ring_buffer.h
//!
//! @brief Some helper functions for implementing and managing a ring buffer.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
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
// This is part of revision 1.2.9 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AM_UTIL_RING_BUFFER_H
#define AM_UTIL_RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include "am_app_utils_macros.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "am_app_KWD_task.h"
#ifdef __cplusplus
extern "C"
{
#endif
  
//*****************************************************************************
//
// App ring buffer list structure typedefs
//
//*****************************************************************************
// this enum list contains all app related ring buffers between AM_APP_RINGBUFF_NONE and AM_APP_RINGBUFF_MAX
// where each index corresponds to a ring buffer
typedef enum
{
    AM_APP_RINGBUFF_NONE = 0, // The enum must begin with this value as named.
    AM_APP_RINGBUFF_PCM,
    AM_APP_RINGBUFF_PRE_AUDIO_STREAM,
    AM_APP_RINGBUFF_POST_AUDIO_STREAM,
    AM_APP_RINGBUFF_TEST,
    AM_APP_RINGBUFF_MAX // The enum must end with this value as named.
} am_app_utils_ring_buffer_enum_t;

//*****************************************************************************
//
// Ring buffer setup structure definitions
//
//*****************************************************************************
typedef struct
{
    am_app_utils_ring_buffer_enum_t indx;
    uint8_t* pData;
    uint32_t ui32ByteSize;
}am_app_utils_ringbuff_setup_t;

//*****************************************************************************
//
// Ring buffer structure definitions
//
//*****************************************************************************
typedef struct
{
    volatile uint8_t *pui8Data;
    volatile uint32_t ui32BufferTail_write;
    volatile uint32_t ui32BufferHead_read;
    volatile uint32_t ui32OverWriting;
    volatile uint32_t ui32Capacity;
}
am_app_utils_ring_buffer_t;


//*****************************************************************************
//
// Function-like macros.
//
//*****************************************************************************
#define am_app_utils_ring_buffer_empty(psBuffer)                                   \
    (((psBuffer)->ui32BufferTail_write == (psBuffer)->ui32BufferHead_read) && ((psBuffer)->ui32OverWriting == 0))

#define am_app_utils_ring_buffer_full(psBuffer)                                    \
    (((psBuffer)->ui32BufferTail_write == (psBuffer)->ui32BufferHead_read) && ((psBuffer)->ui32OverWriting == 1))

#define am_app_utils_ring_buffer_overwrite(psBuffer)                                    \
    (((psBuffer)->ui32BufferTail_write != (psBuffer)->ui32BufferHead_read) && ((psBuffer)->ui32OverWriting == 1))

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern am_app_utils_ring_buffer_t am_KWD_ring_buffers[AM_APP_RINGBUFF_MAX];

void am_app_utils_ring_buffer_init(am_app_utils_ringbuff_setup_t setup);

void am_app_utils_ring_buffer_init_all(const am_app_utils_ringbuff_setup_t* setup_array, uint32_t ui32BufferCount);

bool am_app_utils_ring_buffer_push(am_app_utils_ring_buffer_t *psBuffer,
                               void *pvSource, uint32_t ui32Bytes, bool bFullCheck);

void am_app_utils_ring_buffer_push_fast(am_app_utils_ring_buffer_t *psBuffer, void *pvSource, uint32_t ui32Bytes);

bool am_app_utils_ring_buffer_pop(am_app_utils_ring_buffer_t *psBuffer,
                              void *pvDest, uint32_t ui32Bytes, bool bCheckEmpty);

void am_app_utils_ring_buffer_pop_fast(am_app_utils_ring_buffer_t *psBuffer, void *pvDest,
                         uint32_t ui32Bytes);

uint32_t am_app_utils_get_ring_buffer_status(am_app_utils_ring_buffer_t *psBuffer);

void am_app_utils_flush_ring_buffer(am_app_utils_ring_buffer_t *psBuffer);

#ifdef __cplusplus
}
#endif

#endif // AM_UTIL_RING_BUFFER_H

