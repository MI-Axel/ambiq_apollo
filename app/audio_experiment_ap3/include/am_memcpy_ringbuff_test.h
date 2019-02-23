#ifndef AM_MEMCPY_RINGBUFF_TEST_H
#define AM_MEMCPY_RINGBUFF_TEST_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "am_app_utils_ring_buffer.h"

//*****************************************************************************
//
// App ring buffer list structure typedefs
//
//*****************************************************************************
// this enum list contains all app related ring buffers between AM_APP_RINGBUFF_NONE and AM_APP_RINGBUFF_MAX
// where each index corresponds to a ring buffer
typedef enum
{
    AM_AEP_RINGBUFF_NONE = 0, // The enum must begin with this value as named.
    AM_AEP_RINGBUFF_TEST,
    AM_APP_RINGBUFF_MAX // The enum must end with this value as named.
} am_app_utils_ring_buffer_enum_t;

extern am_app_utils_ring_buffer_t am_AEP_ring_buffers[AM_APP_RINGBUFF_MAX];

extern am_app_utils_ringbuff_setup_t g_AEP_RingBuffSetup[];

extern uint32_t g_ui32RingBuffCount;

extern const uint8_t mono_16b_USP1602[80000];

extern uint8_t g_pui8MemcpyBuff[80001];

extern uint8_t g_pui8FastMemcpyBuff[80001];

extern void am_memcpy_test(uint8_t* pSrc, uint8_t* pDst, uint32_t Len);

extern void am_fast_memcpy_test(uint8_t* pSrc, uint8_t* pDst, uint32_t Len);

extern bool am_memcpy_verify(uint8_t* pCompBuff1, uint8_t* pCompBuff2, uint32_t compLen);

extern void am_ringbuff_test(void);



















#endif
