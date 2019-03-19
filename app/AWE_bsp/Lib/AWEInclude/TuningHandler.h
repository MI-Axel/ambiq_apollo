/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     TuningHandler.h
********************************************************************************
*
*     Description:  Prototypes for AudioWeaver communication handler
*
*     Copyright:    (c) 2007 - 2016 DSP Concepts Inc., All rights reserved
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
*******************************************************************************/

/* Protect the file from multiple inclusion. */
#ifndef AWETUNINGHANDLER_H_INCLUDED
#define AWETUNINGHANDLER_H_INCLUDED

#include <stddef.h>
#include "Framework.h"

/* Enter C naming convention */
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/* ----------------------------------------------------------------------------
 *   Types
 * ------------------------------------------------------------------------- */
#define REPLY_READY			0
#define NEW_PACKET			1
#define REPEATED_PACKET		        2
#define IDLE_PACKET			3	/* Indicate to Target BSP that packet processing is idle (may be packet rx is in progress) */

#define MAX_MSG_SIZE 0x3fff

/*
* State of the Messaging System.
*/
typedef enum
{
    /* --- States for receiving a command --- */

    tMS_Rx_CmdSTX,          /* Receive Command STX */
    tMS_Rx_CmdSeq,          /* Receive Command Sequence ID */
    tMS_Rx_CmdData,         /* Receive Command Data */
    tMS_Rx_CmdETX,          /* Receive Command ETX */

    /* --- State while processing command --- */

    tMS_Tx_WaitingForRsp,   /* Processing Command. */

    /* --- States for sending a response --- */

    tMS_Tx_RspSTX,          /* Send Response STX */
    tMS_Tx_RspSeq,          /* Send Response Sequence ID */
    tMS_Tx_RspData,         /* Send Response Data */
    tMS_Tx_RspETX           /* Send Response ETX */
} tMsgState;
 
/* ----------------------------------------------------------------------------
 *   Function Prototypes
 * ------------------------------------------------------------------------- */

/* Pack received byte in to packet processing buffer */
void awe_fwTuningRxByte(UINT8 ch);

/* Get the byte from packet buffer to be sent as reply packet */
BOOL awe_fwTuningTxByte(UINT8 * ch);

/* Function to pack 32-bit message words in to packet buffer */
INT32 awe_fwTuningRxWord(UINT32 word);

/* Get the word from packet buffer to be sent as reply message */
INT32 awe_fwTuningTxWord(UINT32 * word);

/* Signal packet has been received */
void awe_fwTuningRxPacket(void);

/* Foreground tuning handler */
INT32 awe_fwTuningTick(AWEInstance *pAWE);

/* API to initialize AWE Tuning Handler */
void awe_fwTuningInit(UINT32 * packet_buf, INT32 buf_length);

/* Leave C naming convention */
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* !AWETUNINGHANDLER_H_INCLUDED */
