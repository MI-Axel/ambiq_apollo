/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     TuningDriver.c
********************************************************************************
*
*     Description:  AudioWeaver Tuning Driver for STM Discovery board
*
*     Copyright:    (c) 2018 DSP Concepts, Inc. All rights reserved.
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
*
*******************************************************************************/
#include <string.h>
#include "Platform.h"

/**This will determine the length of a packet in words.*/
#define PACKET_LENGTH_WORDS(x) (x[0]>>16)

static volatile UINT32 g_nPacketBufferNdx = 0;
static volatile UINT32 g_nTotalBytesToSend = 0;

volatile BOOL g_bReadyToSend = TRUE;

UINT32 g_packet_buffer[MAX_COMMAND_BUFFER_LEN] = {0};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN UINT8 HIDInBuff[HID_EP_BUFFER_SIZE] __ALIGN_END = {0};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN UINT8 HIDOutBuff[HID_EP_BUFFER_SIZE] __ALIGN_END = {0};


//-----------------------------------------------------------------------------
// METHOD:  ProcessUSBMsg_IRQHandler
// PURPOSE: Handler to send back multi-packet USB HID reply
//-----------------------------------------------------------------------------
void ProcessUSBMsg_IRQHandler(void)
{
    if (g_nTotalBytesToSend > 0)
    {
		uint32_t nBytesToSend;

        nBytesToSend = g_nTotalBytesToSend  > (HID_REPORT_DATA_SIZE - 4) ? (HID_REPORT_DATA_SIZE - 4): g_nTotalBytesToSend;

        HIDInBuff[3] = (uint8_t)nBytesToSend;

        memcpy(&HIDInBuff[4], &g_packet_buffer[g_nPacketBufferNdx], nBytesToSend);

		g_nPacketBufferNdx += nBytesToSend >> 2;
		g_nTotalBytesToSend -= nBytesToSend;

        // g_bReadyToSend is used in interrupt IN callback to call this handler again
        // if more data needs to be sent back to the host
        if (g_nTotalBytesToSend > 0)
        {
            g_bReadyToSend = TRUE;
        }
        else
        {
            g_bReadyToSend = FALSE;
        }

        USBD_LL_Transmit(&hUsbDeviceFS, HID_IN_EP, HIDInBuff, HID_REPORT_PACKET_SIZE);
    }

    NVIC_ClearPendingIRQ(ProcessUSBMsg_IRQ);

}   // End ProcessUSBMsg_IRQHandler


//-----------------------------------------------------------------------------
// METHOD:  USBSendReply
// PURPOSE: Sends the first packet of a possibly multi-packet reply
//-----------------------------------------------------------------------------
void USBSendReply(AWEInstance * pAWE)
{
    UINT32 nPacketLenInDWords;

    nPacketLenInDWords = PACKET_LENGTH_WORDS(g_packet_buffer);

    if (nPacketLenInDWords > (UINT32)MAX_COMMAND_BUFFER_LEN)
    {
        nPacketLenInDWords = MAX_COMMAND_BUFFER_LEN;
    }

    g_nPacketBufferNdx = 0;

    // HID Report ID
    HIDInBuff[0] = 1;

    HIDInBuff[1] = 0;
    HIDInBuff[2] = 0;

    g_nTotalBytesToSend = nPacketLenInDWords << 2;

    // Start process of sending back possibly multi-packet USB reply
    NVIC_SetPendingIRQ(ProcessUSBMsg_IRQ);

}   // End USBSendReply
