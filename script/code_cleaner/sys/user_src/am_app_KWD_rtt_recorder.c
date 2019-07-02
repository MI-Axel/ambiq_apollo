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
// This is part of revision v1.2.12 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_app_KWD_rtt_recorder.h"

#if (VOS_configUSE_RTT_RECORDER)

void am_app_KWD_rtt_init(uint8_t* rttBuffer, uint32_t LenBytes)
{
    
    SEGGER_RTT_ConfigUpBuffer(1, "DataLogger", rttBuffer, LenBytes, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

}

void am_app_KWD_rtt_record(void* pBuffer, uint32_t NumBytes)
{
    uint32_t bytes_stored;
    bytes_stored = SEGGER_RTT_Write(1, (uint8_t*)pBuffer, NumBytes);
    configASSERT((bytes_stored == NumBytes));
}

#endif

#if VOS_configUSE_SYS_LOG

void am_app_KWD_log_print(am_app_utils_task_enum_t senderID, uint32_t message)
{
    #if VOS_configUSE_LOG_UART0
        am_app_utils_task_send(senderID, AM_APP_TASK_UART0, AM_APP_MESSAGE_SHORT, 
                                message, NULL); 
    #endif

}

#endif

#if VOS_configUSE_STDIO_PRINTF

void am_app_KWD_printf(uint32_t indx, uint8_t printType)
{
    configASSERT(indx < AM_APP_PRINTF_TOTAL_BUFFSIZE);

    if(xPortIsInsideInterrupt() == pdTRUE)
    {
        #if VOS_configUSE_PRINTF_UART0
            am_app_utils_task_send_fromISR(0, AM_APP_TASK_UART0, AM_APP_MESSAGE_STR, indx, NULL);
        #endif

        #if (VOS_configUSE_PRINTF_RTT || VOS_configUSE_PRINTF_SWO)
            am_app_utils_task_send_fromISR(0, AM_APP_TASK_STDIO, AM_APP_MESSAGE_STR, indx, NULL);
        #endif
    }
    else
    {
        #if VOS_configUSE_PRINTF_UART0
            am_app_utils_task_send(0, AM_APP_TASK_UART0, AM_APP_MESSAGE_STR, indx, NULL);
        #endif

        #if (VOS_configUSE_PRINTF_RTT || VOS_configUSE_PRINTF_SWO)
            am_app_utils_task_send(printType, AM_APP_TASK_STDIO, AM_APP_MESSAGE_STR, indx, NULL);
        #endif
    }
}
#endif

