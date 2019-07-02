
/* this is the header file of stereo audio application RAM optimization */

#ifndef AM_AUDIO_BUFFER_H
#define AM_AUDIO_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include "am_app_utils_ring_buffer.h"
#include "am_audio_buffer.h"
//*****************************************************************************
//
// helper functions
//
//*****************************************************************************

//
// Read/Head combo enum name
//
typedef enum{
    AM_AUDIO_BUFFER_STEREO,             // raw audio data from 2 channels of mics
    AM_AUDIO_BUFFER_MONO,               // audio data filtered by dspc signal chain
    AM_AUDIO_BUFFER_ENCODED,            // compressed audio data
//    AM_AUDIO_BUFFER_COMM,
    AM_AUDIO_BUFFER_MAX
}enum_audio_buffer_t;

typedef struct{
    uint8_t * head;
    uint8_t * tail;
}audio_buffer_ptr_t;

#define BYTES_UNIVERSAL_BUFFER_SIZE (96*1024)

// size = BYTES_UNIVERSAL_BUFFER_SIZE
extern uint8_t g_ringUniversalBuffer[];

extern am_app_utils_ring_buffer_t am_audio_ring_buffers[];
//extern audio_buffer_ptr_t am_audio_ring_buffer_ptr[];

extern void am_audio_buffer_init(void);

extern bool am_audio_buffer_push(enum_audio_buffer_t buffer_type, void *pvSource, uint32_t ui32Bytes);
extern uint32_t am_audio_buffer_pop(enum_audio_buffer_t buffer_type, void *pvDest, uint32_t ui32Bytes);

extern void am_audio_buffer_rewind (enum_audio_buffer_t buffer_type, uint32_t offset_back);

void am_audio_buffer_nested_push(enum_audio_buffer_t buffer_push_to, enum_audio_buffer_t buffer_origin, void *pvSource, uint32_t ui32Bytes);
void am_audio_buffer_nested_pop(enum_audio_buffer_t buffer_pop_from, enum_audio_buffer_t buffer_dest, void *pvDest, uint32_t ui32Bytes);


#endif    // ndefAM_AUDIO_BUFFER_H
