#ifndef AM_MEMCPY_RINGBUFF_TEST_H
#define AM_MEMCPY_RINGBUFF_TEST_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>


extern const uint8_t mono_16b_USP1602[80000];

extern uint8_t g_pui8MemcpyBuff[80001];

extern uint8_t g_pui8FastMemcpyBuff[80001];

extern void am_memcpy_test(uint8_t* pSrc, uint8_t* pDst, uint32_t Len);

extern void am_fast_memcpy_test(uint8_t* pSrc, uint8_t* pDst, uint32_t Len);

extern bool am_memcpy_verify(uint8_t* pCompBuff1, uint8_t* pCompBuff2, uint32_t compLen);





















#endif
