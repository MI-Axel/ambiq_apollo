/* this file is the source file of RTT output */ 

#include "am_app_utils_rtt_recorder.h"


void am_app_utils_rtt_init(uint8_t* rttBuffer, uint32_t LenBytes)
{
    
    SEGGER_RTT_Init();    
    
    SEGGER_RTT_ConfigUpBuffer(1, "DataLogger", rttBuffer, LenBytes, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

}

void am_app_utils_rtt_record(void* pBuffer, uint32_t NumBytes)
{
    uint32_t bytes_stored;
    bytes_stored = SEGGER_RTT_Write(1, (uint8_t*)pBuffer, NumBytes);
    configASSERT((bytes_stored == NumBytes));
}





