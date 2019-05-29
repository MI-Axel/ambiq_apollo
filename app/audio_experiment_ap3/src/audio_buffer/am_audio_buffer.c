
//*****************************************************************************
//
// this is the source file of stereo audio application RAM optimization.
// In this application, there are 3 nested buffers:BUFFER_STEREO, BUFFER_MONO and BUFFER_ENCODED.
// PDM_ISR -> BUFFER_STEREO ->BUFFER_MONO -> BUFFER_ENCODED -> BLE
// 3 BUFFERs share the same physical buffer: g_ringUniversalBuffer. Each buffer use its own read_head and write_tail.
// Simple summary 
//
//*****************************************************************************

#include "am_app_utils_ring_buffer.h"
#include "am_audio_buffer.h"
//*****************************************************************************
//
// fundamental functions: init, push, pop, rewind.
//
//*****************************************************************************
#if USE_UNIVERSAL_AUDIO_BUFFER

//audio_buffer_ptr_t am_audio_ring_buffer_ptr[AM_AUDIO_BUFFER_MAX];
uint8_t g_ringUniversalBuffer[BYTES_UNIVERSAL_BUFFER_SIZE];
am_app_utils_ring_buffer_t am_audio_ring_buffers[AM_AUDIO_BUFFER_MAX];

void am_audio_buffer_init(void)
{

    for(uint8_t i = 0; i < AM_AUDIO_BUFFER_MAX; i++)
    {
        am_audio_ring_buffers[i].ui32BufferHead_read = 0;
        am_audio_ring_buffers[i].ui32BufferTail_write = 0;
        am_audio_ring_buffers[i].ui32OverWriting = 0;
        am_audio_ring_buffers[i].ui32Capacity = BYTES_UNIVERSAL_BUFFER_SIZE;
        am_audio_ring_buffers[i].pui8Data = g_ringUniversalBuffer;

//        am_audio_ring_buffer_ptr[i].head = g_ringUniversalBuffer;
//        am_audio_ring_buffer_ptr[i].tail = g_ringUniversalBuffer;
    }

}

// returns true if a push results in overwrite
bool am_audio_buffer_push(enum_audio_buffer_t buffer_type, void *pvSource, uint32_t ui32Bytes)
{
    uint32_t pushBytes = 0;
    if(buffer_type > AM_AUDIO_BUFFER_MAX)
    {
        // type error
        
    }
    else
    {
        AM_APP_CRITICAL_BEGIN;
//        AM_CRITICAL_BEGIN_VOS;
        am_app_utils_ring_buffer_push(&am_audio_ring_buffers[buffer_type], pvSource, ui32Bytes, false);
//        am_audio_ring_buffer_ptr[buffer_type].tail = (uint8_t *)&am_audio_ring_buffers[buffer_type].pui8Data[am_audio_ring_buffers[buffer_type].ui32BufferTail_write];
//        AM_CRITICAL_END_VOS;
        AM_APP_CRITICAL_END;
    }
    
#if AUDIO_BUFFER_DEBUG

// // too many log info....
//    AM_APP_LOG_DEBUG("Push, type: %d, head: %d, tail: %d\n", 
//                buffer_type,
//                am_audio_ring_buffers[buffer_type].ui32BufferHead_read, 
//                am_audio_ring_buffers[buffer_type].ui32BufferTail_write);
#endif // #if AUDIO_BUFFER_DEBUG

    return(am_audio_ring_buffers[buffer_type].ui32OverWriting);
}


// returns the actual data bytes popped
uint32_t 
am_audio_buffer_pop(enum_audio_buffer_t buffer_type, void *pvDest, uint32_t ui32Bytes)
{
    if(buffer_type > AM_AUDIO_BUFFER_MAX)
    {
        // type error
        return 0;
    }
    uint32_t ui32PopLen = 0;
    AM_APP_CRITICAL_BEGIN;
//    AM_CRITICAL_BEGIN_VOS;
    ui32PopLen = am_app_utils_ring_buffer_pop(&am_audio_ring_buffers[buffer_type], pvDest, ui32Bytes);
//    am_audio_ring_buffer_ptr[buffer_type].head = (uint8_t *)&am_audio_ring_buffers[buffer_type].pui8Data[am_audio_ring_buffers[buffer_type].ui32BufferHead_read];
//    AM_CRITICAL_END_VOS;
    AM_APP_CRITICAL_END;
    
#if AUDIO_BUFFER_DEBUG
    AM_APP_LOG_DEBUG("Pop, type: %d, head: %d, tail: %d\n", 
                buffer_type,
                am_audio_ring_buffers[buffer_type].ui32BufferHead_read, 
                am_audio_ring_buffers[buffer_type].ui32BufferTail_write);
#endif // #if AUDIO_BUFFER_DEBUG

    return ui32PopLen;
}

bool am_audio_buffer_empty(enum_audio_buffer_t buffer_type)
{
    bool bRetValue = false;
    AM_APP_CRITICAL_BEGIN;
    bRetValue = am_app_utils_ring_buffer_empty(&am_audio_ring_buffers[buffer_type]); 
    AM_APP_CRITICAL_END;
    return bRetValue;
}


// rewind the index pointers of an audio buffer to a position in the past
// test: only for mono buffer
// enum_audio_buffer_t buffer_type, 
void am_audio_buffer_rewind (enum_audio_buffer_t buffer_type, uint32_t offset_back)
{
    if(buffer_type > AM_AUDIO_BUFFER_MAX)
    {
        // type error
        return;
    }

    AM_APP_CRITICAL_BEGIN;
//    AM_CRITICAL_BEGIN_VOS;

    am_audio_ring_buffers[buffer_type].ui32OverWriting = 0; // clear overwrite flag
    am_audio_ring_buffers[buffer_type].ui32BufferHead_read = 
                        (am_audio_ring_buffers[buffer_type].ui32BufferTail_write + BYTES_UNIVERSAL_BUFFER_SIZE - offset_back) % BYTES_UNIVERSAL_BUFFER_SIZE;
    am_audio_ring_buffer_ptr[buffer_type].head = (uint8_t *)&am_audio_ring_buffers[buffer_type].pui8Data[am_audio_ring_buffers[buffer_type].ui32BufferHead_read];
//    AM_CRITICAL_END_VOS;

    AM_APP_CRITICAL_END;
#if AUDIO_BUFFER_DEBUG
    AM_APP_LOG_DEBUG("Rewind, type: %d, head: %d, tail: %d\n", 
                    buffer_type,
                    am_audio_ring_buffers[buffer_type].ui32BufferHead_read, 
                    am_audio_ring_buffers[buffer_type].ui32BufferTail_write);
#endif // #if AUDIO_BUFFER_DEBUG

}

//
// Set audio buffer index into a specific position.
// It's effective only when the buffer is empty.
// Return: 
//      true  --the head and tail are successfully changed.
//      false --the head and tail are unchanged.
//

bool am_audio_buffer_index_set(enum_audio_buffer_t buffer_type, uint32_t index)
{
    if(buffer_type > AM_AUDIO_BUFFER_MAX)
    {
        // type error
        return;
    }

//    AM_CRITICAL_BEGIN_VOS;

    if(am_audio_buffer_empty(buffer_type))
    {
        
        AM_APP_CRITICAL_BEGIN;
        am_audio_ring_buffers[buffer_type].ui32BufferHead_read = index;
        am_audio_ring_buffers[buffer_type].ui32BufferTail_write = index;
//    am_audio_ring_buffer_ptr[buffer_type].head =  (uint8_t *)&am_audio_ring_buffers[buffer_type].pui8Data[am_audio_ring_buffers[buffer_type].ui32BufferHead_read];
//    am_audio_ring_buffer_ptr[buffer_type].tail =  (uint8_t *)&am_audio_ring_buffers[buffer_type].pui8Data[am_audio_ring_buffers[buffer_type].ui32BufferHead_read];
        AM_APP_CRITICAL_END;
        return true;
    }
    else
        return false;
//    AM_CRITICAL_END_VOS;
    
}

//*****************************************************************************
//
// specific-optimized functions: nested_push
// parameters:
//          buffer_push_to: the target ring buffer where we push data to
//          buffer_origin: consider it as parent buffer, where pvSource data comes from
//          pvSource: data source 
//          ui32Bytes: how many bytes needs to be pushed
//
// Notice:
//      the difference between nested_push and push is: nested_push will move the 
//      parent buffer head and tail to the tail of sub-buffer if parent buffer is empty.
//
//*****************************************************************************
bool am_audio_buffer_nested_push(enum_audio_buffer_t buffer_push_to, enum_audio_buffer_t buffer_origin, void *pvSource, uint32_t ui32Bytes)
{
    bool bReturnVal = false;

    am_audio_buffer_push(buffer_push_to, pvSource, ui32Bytes);

    am_audio_buffer_index_set(buffer_origin, am_audio_ring_buffers[buffer_push_to].ui32BufferTail_write)
}


// update mono pointers after encoded
// only called 
#define ENCODED_SAFETY_MARGIN   128
bool am_audio_buffer_update_mono_pointers(void)
{
    bool bResult = false;

    AM_APP_CRITICAL_BEGIN;
//    AM_CRITICAL_BEGIN_VOS;
    if(am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO].ui32BufferHead_read == am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO].ui32BufferTail_write)
    {
        // no more raw mono data in the buffer
        // move the pointer to tail of encoded data to save room
        am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO].ui32BufferHead_read = (am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED].ui32BufferTail_write 
                                                                            + ENCODED_SAFETY_MARGIN)% BYTES_UNIVERSAL_BUFFER_SIZE;
        am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO].ui32BufferTail_write = am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO].ui32BufferHead_read;

//        am_audio_ring_buffer_ptr[AM_AUDIO_BUFFER_MONO].head = (uint8_t *)&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED].pui8Data[am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED].ui32BufferTail_write];
//        am_audio_ring_buffer_ptr[AM_AUDIO_BUFFER_MONO].tail = am_audio_ring_buffer_ptr[AM_AUDIO_BUFFER_MONO].head;


#if AUDIO_BUFFER_DEBUG
        AM_APP_LOG_DEBUG("Update mono, head: %d, tail: %d\n", 
                            am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO].ui32BufferHead_read, 
                            am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO].ui32BufferTail_write);
#endif // #if AUDIO_BUFFER_DEBUG

        // indexes and pointers are updated.
        bResult = true;
    }

    AM_APP_CRITICAL_END;
//    AM_CRITICAL_END_VOS;
    return bResult;

}


#endif // USE_UNIVERSAL_AUDIO_BUFFER

