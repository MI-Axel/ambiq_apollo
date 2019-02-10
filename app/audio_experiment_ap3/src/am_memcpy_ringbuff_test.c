/* this source file is the test of memcpy and ringbuff */

#include "am_audio_platform_config.h"
#include "am_memcpy_ringbuff_test.h"
#include "am_app_utils_memcpy.h"
#if configUSE_SYSVIEW
#include "SEGGER_SYSVIEW.h"
#endif

extern const uint8_t mono_16b_USP1602[80000];

uint8_t g_pui8MemcpyBuff[80001];

uint8_t g_pui8FastMemcpyBuff[80001];

void am_memcpy_test(uint8_t* pSrc, uint8_t* pDst, uint32_t Len)
{
    SEGGER_SYSVIEW_RecordVoid(34);

    memcpy(pDst, pSrc, Len);

    SEGGER_SYSVIEW_RecordEndCall(34);
}

void am_fast_memcpy_test(uint8_t* pSrc, uint8_t* pDst, uint32_t Len)
{
    SEGGER_SYSVIEW_RecordVoid(33);

    MEMCOPY(pDst, pSrc, Len);

    SEGGER_SYSVIEW_RecordEndCall(33);
}

bool am_memcpy_verify(uint8_t* pCompBuff1, uint8_t* pCompBuff2, uint32_t compLen)
{
    uint32_t indx = 0;
    for(indx=0; indx<compLen; indx++)
    {
        if(pCompBuff1[indx] != pCompBuff2[indx])
            return false;
    }
    return true;
}

