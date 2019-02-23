/* this source file is the test of memcpy and ringbuff */

#include "am_audio_platform_config.h"
#include "am_memcpy_ringbuff_test.h"
#include "am_app_utils_memcpy.h"
#include "am_bsp.h"
#include "am_mcu_apollo.h"
#include "am_util.h"
#if configUSE_SYSVIEW
#include "SEGGER_SYSVIEW.h"
#endif

#include "board_setup.h"

extern const uint8_t mono_16b_USP1602[80000];

uint8_t g_pui8MemcpyBuff[80001];

uint8_t g_pui8FastMemcpyBuff[80001];

uint8_t g_TestDataFrame[100];

//******************************************************************************
//KWD Global ring buffers
//*****************************************************************************
am_app_utils_ring_buffer_t am_AEP_ring_buffers[AM_APP_RINGBUFF_MAX];

am_app_utils_ringbuff_setup_t g_AEP_RingBuffSetup[] = 
{

    {AM_AEP_RINGBUFF_TEST, g_TestDataFrame, 100}
   
};

#define AEP_RINGBUFF_INIT_COUNT     (sizeof(g_AEP_RingBuffSetup)/sizeof(am_app_utils_ringbuff_setup_t))

uint32_t g_ui32RingBuffCount = AEP_RINGBUFF_INIT_COUNT;

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

void am_ringbuff_test(void)
{
    uint32_t ui32PushLen;
    uint32_t ui32PopLen;
    ui32PushLen = am_app_utils_ring_buffer_push(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST], mono_16b_USP1602, 40);
    am_util_stdio_printf("Totally %d bytes are pushed into ringbuffer.\r\n", ui32PushLen);

    ui32PopLen = am_app_utils_ring_buffer_pop(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST], g_pui8MemcpyBuff, 13);
    am_util_stdio_printf("Totally %d bytes are poped out from ringbuffer.\r\n", ui32PopLen);

    ui32PopLen = am_app_utils_ring_buffer_pop(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST], g_pui8FastMemcpyBuff, 33);
    am_util_stdio_printf("Totally %d bytes are poped out from ringbuffer.\r\n", ui32PopLen);

    ui32PushLen = am_app_utils_ring_buffer_push(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST], mono_16b_USP1602, 80);
    am_util_stdio_printf("Totally %d bytes are pushed into ringbuffer.\r\n", ui32PushLen);
   
    ui32PopLen = am_app_utils_ring_buffer_pop(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST], g_pui8MemcpyBuff, 33);
    am_util_stdio_printf("Totally %d bytes are poped out from ringbuffer.\r\n", ui32PopLen);

    ui32PushLen = am_app_utils_ring_buffer_push(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST], mono_16b_USP1602, 80);
    am_util_stdio_printf("Totally %d bytes are pushed into ringbuffer.\r\n", ui32PushLen);

    am_app_utils_flush_ring_buffer(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST]);

    ui32PushLen = am_app_utils_ring_buffer_push(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST], mono_16b_USP1602, 100);
    am_util_stdio_printf("Totally %d bytes are pushed into ringbuffer.\r\n", ui32PushLen);

    configASSERT(am_app_utils_get_ring_buffer_status(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST])==100);

    ui32PopLen = am_app_utils_ring_buffer_pop(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST], g_pui8MemcpyBuff, 100);
    am_util_stdio_printf("Totally %d bytes are poped out from ringbuffer.\r\n", ui32PopLen);

    configASSERT(am_app_utils_get_ring_buffer_status(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_TEST])==0);
    if(am_memcpy_verify(mono_16b_USP1602, g_pui8MemcpyBuff, 100))
    {
        am_devices_led_on(am_bsp_psLEDs, 2);
        DebugLog("Ring buffer test passed!\r\n\n");
    }
    else
    {
        am_devices_led_on(am_bsp_psLEDs, 3);
        DebugLog("Ring buffer test passed!\r\n\n");
    }
}


