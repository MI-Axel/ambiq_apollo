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
*     Copyright:    (c) 2018 DSP Concepts Inc., All rights reserved
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
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
#define REPEATED_PACKET		2
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
/* Process a command or route the command to another core for processing */
INT32 awe_pltPacketProcess(void);

/* Pack received byte in to packet processing buffer */
void awe_pltTuningRxByte(UINT8 ch);

/* Get the byte from packet buffer to be sent as reply packet */
BOOL awe_pltTuningTxByte(UINT8 * ch);

/* Insert a word into the packet buffer to build the send message */
BOOL awe_pltTuningRxWord(UINT32 word);

/* Get the word from packet buffer to be sent as reply message */
BOOL awe_pltTuningTxWord(UINT32 * word);

/* Signal packet has been received */
void awe_pltTuningRxPacket(void);

/* Foreground tuning handler */
INT32 awe_pltTuningTick(void);

/* Get message length */
INT32 awe_pltGetMessageLen(void);

/* Leave C naming convention */
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* !AWETUNINGHANDLER_H_INCLUDED */
