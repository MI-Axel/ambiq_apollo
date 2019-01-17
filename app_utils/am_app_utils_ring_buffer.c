//*****************************************************************************
//
//! @file am_app_utils_ring_buffer.c
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

#include <stdint.h>
#include <stdbool.h>
//#include <string.h>
#include "am_app_utils_task.h"
#include "am_app_utils_macros.h"
#include "am_app_utils_ring_buffer.h"

extern void* memcpy();  // fixme: to suppress the warnings, however, 
                        // include not correct, need further debug
//*****************************************************************************
//
//! @brief Initializes a ring buffer structure.
//!
//! @param psBuffer is a pointer to the buffer structure to be initialized.
//!
//! @param pvArray is a pointer to the array that the new ringbuffer will use
//! for storage space
//!
//! @param ui32Bytes is the total number of bytes that the ringbuffer will be
//! allowed to use.
//!
//! This function should be called on a ring buffer structure before it is
//! used. If this function is called on a ring buffer that is already being
//! used, it will "erase" the buffer, effectively removing all of the buffer
//! contents from the perspective of the other ring buffer access functions.
//! The data will remain in memory, but it will be overwritten as the buffer is
//! used.
//!
//! @note This operation is not inherently thread-safe, so the caller must make
//! sure that it is appropriately guarded from interrupts and context switches.
//!
//! @return
//
//*****************************************************************************
void
am_app_utils_ring_buffer_init(am_app_utils_ringbuff_setup_t setup)
{
    configASSERT(setup.indx < AM_APP_RINGBUFF_MAX);
    am_KWD_ring_buffers[setup.indx].ui32BufferHead_read = 0;
    am_KWD_ring_buffers[setup.indx].ui32BufferTail_write = 0;
    am_KWD_ring_buffers[setup.indx].ui32OverWriting = 0;
    am_KWD_ring_buffers[setup.indx].ui32Capacity = setup.ui32ByteSize;
    am_KWD_ring_buffers[setup.indx].pui8Data = setup.pData;
}

void
am_app_utils_ring_buffer_init_all(const am_app_utils_ringbuff_setup_t* setup_array, 
                                    uint32_t ui32BufferCount)
{
    uint32_t ringbuff = 0;
    for(ringbuff =0; ringbuff<ui32BufferCount; ringbuff++)
    {
        am_app_utils_ring_buffer_init(setup_array[ringbuff]);    
    }

}

//*****************************************************************************
//
//! @brief Write a single byte to the ring buffer.
//!
//! @param psBuffer is the address of the ring buffer structure to be written.
//! @param ui8Value is the byte to be added to the ring buffer.
//!
//! This function will write a single byte to the given ring buffer. Make sure
//! that the ring buffer is not already full when calling this function. If the
//! ring buffer is already full, this function will fail silently.
//!
//! @note This operation is not inherently thread-safe, so the caller must make
//! sure that it is appropriately guarded from interrupts and context switches.
//!
//! @return True if the data was written to the buffer. False for insufficient
//! space.
//
//*****************************************************************************
bool
am_app_utils_ring_buffer_push(am_app_utils_ring_buffer_t *psBuffer, void *pvSource,
                          uint32_t ui32Bytes, bool bFullCheck)
{
    uint32_t i;
    uint8_t *pui8Source;

    pui8Source = (uint8_t *) pvSource;

        //
        // Loop over the bytes in the source array.
        //
    for ( i = 0; i < ui32Bytes; i++ )
    {
        //
        // Check to make sure that the buffer isn't already full
        //

        if((bFullCheck) && am_app_utils_ring_buffer_full(psBuffer))
            return FALSE;
        
        //
        // Write the value to the buffer.
        //
        psBuffer->pui8Data[psBuffer->ui32BufferTail_write] = pui8Source[i];

        //
        // Advance the write index, making sure to wrap if necessary.
        //
        psBuffer->ui32BufferTail_write = ((psBuffer->ui32BufferTail_write + 1) %
                                        psBuffer->ui32Capacity);
        
        if(psBuffer->ui32BufferTail_write == psBuffer->ui32BufferHead_read)
            psBuffer->ui32OverWriting = 1;
    }
        //
        // Report a success.
        //
        return TRUE;

}

void
am_app_utils_ring_buffer_push_fast(am_app_utils_ring_buffer_t *psBuffer, void *pvSource, uint32_t ui32Bytes)
{
    uint32_t ui32CopyLen;
    uint32_t ui32TempLen;

    ui32CopyLen = ui32Bytes;

    if(am_app_utils_ring_buffer_empty(psBuffer))
    {
        if(ui32CopyLen >= psBuffer->ui32Capacity)
            psBuffer->ui32OverWriting = 1;
    }
    else
    {
        if(((psBuffer->ui32BufferHead_read + psBuffer->ui32Capacity - psBuffer->ui32BufferTail_write) 
            % psBuffer->ui32Capacity) <= ui32CopyLen)
            psBuffer->ui32OverWriting = 1;

    }        
        
    while((psBuffer->ui32BufferTail_write + ui32CopyLen) >= psBuffer->ui32Capacity)
    {
        ui32TempLen = psBuffer->ui32Capacity - psBuffer->ui32BufferTail_write;
        memcpy((void*)&psBuffer->pui8Data[psBuffer->ui32BufferTail_write], (void*)pvSource, ui32TempLen);
        psBuffer->ui32BufferTail_write = ((psBuffer->ui32BufferTail_write + ui32TempLen) % psBuffer->ui32Capacity);
        ui32CopyLen -= ui32TempLen;
    }
    configASSERT((psBuffer->ui32BufferTail_write + ui32CopyLen) < psBuffer->ui32Capacity);
    
    memcpy((void*)&psBuffer->pui8Data[psBuffer->ui32BufferTail_write], (void*)pvSource, ui32CopyLen);
    psBuffer->ui32BufferTail_write = ((psBuffer->ui32BufferTail_write + ui32CopyLen) % psBuffer->ui32Capacity);
    

}

//*****************************************************************************
//
//! @brief Read a single byte from the ring buffer.
//!
//! @param psBuffer is the address of the ring buffer structure to be read.
//!
//! This function will write a single byte to the given ring buffer. Make sure
//! that the ring buffer is not already empty. If the ring buffer is empty,
//! this function will just return a NULL character.
//!
//! @note This operation is not inherently thread-safe, so the caller must make
//! sure that it is appropriately guarded from interrupts and context switches.
//!
//! @return The byte read from the buffer, or a NULL if the buffer was empty.
//
//*****************************************************************************
bool
am_app_utils_ring_buffer_pop(am_app_utils_ring_buffer_t *psBuffer, void *pvDest,
                         uint32_t ui32Bytes, bool bCheckEmpty)
{
    uint32_t i;
    uint8_t *pui8Dest;

    pui8Dest = (uint8_t *) pvDest;

    //
    // Check to make sure that the buffer isn't over writed and isn't empty
    //

    for ( i = 0; i < ui32Bytes; i++ )
    {    
        if((bCheckEmpty) && am_app_utils_ring_buffer_empty(psBuffer) )
            return FALSE;

        //
        // Grab the next value from the buffer.
        //
        if(am_app_utils_ring_buffer_overwrite(psBuffer))
        {    
            psBuffer->ui32BufferHead_read = (psBuffer->ui32BufferTail_write); 
        }

        
        pui8Dest[i] = psBuffer->pui8Data[psBuffer->ui32BufferHead_read];

        //
        // Advance the read index, wrapping if needed.
        //
        psBuffer->ui32BufferHead_read = ((psBuffer->ui32BufferHead_read + 1) %
                                           psBuffer->ui32Capacity);
        
        //
        // it clears the buffer full flag
        //
        psBuffer->ui32OverWriting = 0;
    }
        //
        // Report a success.
        //
    return TRUE;
    
}

void
am_app_utils_ring_buffer_pop_fast(am_app_utils_ring_buffer_t *psBuffer, void *pvDest,
                         uint32_t ui32Bytes)
{
    uint32_t ui32CopyLen;
    
    uint32_t ui32TempLen;
    
    uint32_t ui32DataLen;

    ui32DataLen = am_app_utils_get_ring_buffer_status(psBuffer);
   
    if(am_app_utils_ring_buffer_overwrite(psBuffer))
    {
        psBuffer->ui32BufferHead_read = (psBuffer->ui32BufferTail_write);
       
    }

    ui32CopyLen = ui32Bytes < ui32DataLen ? ui32Bytes : ui32DataLen;
   
    while((psBuffer->ui32BufferHead_read + ui32CopyLen) >= psBuffer->ui32Capacity)
    {
        ui32TempLen = psBuffer->ui32Capacity - psBuffer->ui32BufferHead_read;
        memcpy((void*)pvDest, (void*)&psBuffer->pui8Data[psBuffer->ui32BufferHead_read], ui32TempLen);
        psBuffer->ui32BufferHead_read = ((psBuffer->ui32BufferHead_read + ui32TempLen) % psBuffer->ui32Capacity);
        ui32CopyLen -= ui32TempLen;
    }

    configASSERT((psBuffer->ui32BufferHead_read + ui32CopyLen) < psBuffer->ui32Capacity);
    
    memcpy((void*)pvDest, (void*)&psBuffer->pui8Data[psBuffer->ui32BufferHead_read], ui32CopyLen);
    psBuffer->ui32BufferHead_read = ((psBuffer->ui32BufferHead_read + ui32CopyLen) % psBuffer->ui32Capacity);
      

    
    psBuffer->ui32OverWriting = 0;

}
//*****************************************************************************
//
//! @brief get the number of data left in ring buffer .
//!
//! @param psBuffer is the address of the ring buffer structure to be read.
//!
//! @note This operation is not inherently thread-safe, so the caller must make
//! sure that it is appropriately guarded from interrupts and context switches.
//!
//! @return The number of data left.
//
//*****************************************************************************
uint32_t
am_app_utils_get_ring_buffer_status(am_app_utils_ring_buffer_t *psBuffer)
{
    uint32_t ui32NewDataLen = 0;
    
    if (am_app_utils_ring_buffer_overwrite(psBuffer) || am_app_utils_ring_buffer_full(psBuffer))
    {
        ui32NewDataLen = psBuffer->ui32Capacity;
        return ui32NewDataLen;
    }
    
    ui32NewDataLen = ((psBuffer->ui32BufferTail_write + psBuffer->ui32Capacity - psBuffer->ui32BufferHead_read) % 
        psBuffer->ui32Capacity);

    return ui32NewDataLen; 

}

//*****************************************************************************
//
//! @brief flush the ring buffer 
//!
//! @param psBuffer is the address of the ring buffer which needs to be flushed.
//!
//! @note None.
//!
//! @return None.
//
//*****************************************************************************
void
am_app_utils_flush_ring_buffer(am_app_utils_ring_buffer_t *psBuffer)
{
    psBuffer->ui32OverWriting = 0;
    psBuffer->ui32BufferTail_write = psBuffer->ui32BufferHead_read;
}


