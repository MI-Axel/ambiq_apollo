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
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

/*****************************************************************************
 *
 *    Tuning Driver
 *
 ******************************************************************************
 *  TuningDriver.c
 ******************************************************************************
 *
 *     Description:  UART0 Driver for Ambiq Apollo
 *
 *     Copyright:    DSP Concepts, Inc. (c) 2007 - 2016
 *                   1800 Wyatt Drive, Suite 14
 *                   Sunnyvale, CA 95054
 *
 *****************************************************************************/

//
// ambiq apollo headers
//
#include "am_mcu_apollo.h"
#include "am_util.h"
#include "am_bsp.h"

//
// AWE include 
//
#include "AWECore.h"
#include "StandardDefs.h"
#include "AWECoreUtils.h"
#include "Platform.h"
#include "TargetInfo.h"

//
// board config
//
#include "BoardSetup.h"
static volatile UINT32 g_nTotalBytesToSend = 0;

volatile BOOL g_bReadyToSend = TRUE;
volatile UINT32 g_ui32PacketComplete = TRUE;

unsigned char dbgbuf[128] = {0};

//-----------------------------------------------------------------------------
// METHOD:  TuningInit
// PURPOSE: 
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_SLOW_CODE
void UARTMsgInit(void)
{   
    // Initialize (reset) the communication handler
    tuningResetByteEncoderUART();
           
}   // End UARTMsgInit

//-----------------------------------------------------------------------------
// METHOD:  CheckForUARTPacketReady
// PURPOSE: Checks if UART packet has been received and calls into framework
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_SLOW_CODE
UINT32 packet_num = 0;
void CheckForUARTPacketReady(void)
{
    static char pcTempBuf[(MAX_COMMAND_BUFFER_LEN * 4) + 1];
    UINT32 ind = 0;
    static uint32_t ui32Length; // number of bytes in the packet  
    INT32 in32DecRet = 0;
        // g_bUARTPacketReceived is set in UART isr when a packet is received
        // Reset flag so we'll know when the next UART packet is received
    if(g_bUARTPacketReceived)
    {
        memset(pcTempBuf, 0x00, sizeof(pcTempBuf));
        g_bUARTPacketReceived = FALSE;
#if defined (AM_PART_APOLLO3)
        extern void* g_sCOMUART;
        const am_hal_uart_transfer_t sUartRead =
        {
            .ui32Direction = AM_HAL_UART_READ,
            .pui8Data = (uint8_t *) pcTempBuf,
            .ui32NumBytes = MAX_COMMAND_BUFFER_LEN * 4,
            .ui32TimeoutMs = 0,
            .pui32BytesTransferred = &ui32Length
        };
        am_hal_uart_transfer(g_sCOMUART, &sUartRead);
#endif // AM_PART_APOLLO3
        for (ind = 0; ind < ui32Length; ind++)
        {
            in32DecRet = tuningDecodeByteUART(g_packet_buffer, (uint8_t)pcTempBuf[ind]);
            if(in32DecRet == COMPLETE_NEW_PACKET)
            {
                g_bPacketReceived = TRUE;
                break;
            }
        }	           
    }
}	// End CheckForUSBPacketReady

//-----------------------------------------------------------------------------
// METHOD:  UART0SendReply
// PURPOSE: Setup to send reply to sender byte by byte
//-----------------------------------------------------------------------------

void UART0SendReply(void)
{
    static uint32_t nPacketLenInDWords;
    unsigned char ucHoldingByte;
	
    nPacketLenInDWords = g_packet_buffer[0] >> 16;
	
    g_nTotalBytesToSend = nPacketLenInDWords << 2;

    do
    {
        g_ui32PacketComplete = tuningEncodeByteUART(g_packet_buffer, &ucHoldingByte);

        if (g_ui32PacketComplete == INCOMPLETE_PACKET)
        {
#if defined (AM_PART_APOLLO3)
            uint32_t ui32BytesWritten = 0;
            extern void* g_sCOMUART;
            const am_hal_uart_transfer_t sUartWrite =
            {
                .ui32Direction = AM_HAL_UART_WRITE,
                .pui8Data = (uint8_t *) &ucHoldingByte,
                .ui32NumBytes = 1,
                .ui32TimeoutMs = 0,
                .pui32BytesTransferred = &ui32BytesWritten,
            };

            am_hal_uart_transfer(g_sCOMUART, &sUartWrite);
#endif //
        }
    }	
    while(g_ui32PacketComplete==INCOMPLETE_PACKET);
	
}   // End UART0SendReply


/**
 * @}
 * End of file.
 */
