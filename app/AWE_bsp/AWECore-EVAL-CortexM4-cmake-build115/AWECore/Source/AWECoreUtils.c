/**
 **************************************************************************
 * @defgroup Tuning AWE Utilities and Helper Functions
 * @{
 **************************************************************************
 *
 * @file AWEUtils.c
 * @brief Helper functions and utilities.
 *
 * @details These helper functions aid the user with tuning, and generating replies
 *
 ***************************************************************************/
#include "AWECoreUtils.h"
#include <string.h>

#if defined(__ADSP21000__) || defined(__ADSPBLACKFIN__)
#pragma default_section(SWITCH, "awe_fw_slowanydata")
#endif

/* ----------------------------------------------------------------------------
 *   Local Variables
 * ------------------------------------------------------------------------- */

/** Transmit message state. */
AWE_FW_SLOW_ANY_DATA static tMsgState s_state = tMS_Rx_CmdSTX;

/** Message sequence number. */
AWE_FW_SLOW_ANY_DATA static INT8 s_msg_seq = 0;

/** Message sequence number (previous). */
AWE_FW_SLOW_ANY_DATA static INT8 s_msg_seqlast = 0;

/** Message size. */
AWE_FW_SLOW_ANY_DATA static size_t s_msg_size = 0u;

/** Message offset. */
AWE_FW_SLOW_ANY_DATA static size_t s_msg_offs = 0u;

/** Message processing word. */
AWE_FW_SLOW_ANY_DATA static UINT32 s_msg_word = 0u;

/** Message processing word index. */
AWE_FW_SLOW_ANY_DATA static UINT32 s_msg_wordpos = 0u;

/** Flag indicating that the message is processed and the reply is ready to transmit */
static volatile INT32 s_msg_transmit = 0;

static UINT32 readIndex = 0;

AWE_OPTIMIZE_FOR_SPEED
AWE_FW_FAST_CODE
void tuningResetByteEncoderUART(void)
{
	s_state = tMS_Rx_CmdSTX;
	s_msg_seq = 0;
	s_msg_seqlast = 0;
	s_msg_size = 0u;
	s_msg_offs = 0u;
	s_msg_word = 0u;
	s_msg_wordpos = 0u;

}	// End tuningResetByteEncoderUART


/**
 * @brief Handler for byte communication transmitter ready.
 * @details This method is typically called in the transmit holding buffer empty interrupt handler.
 * @param[out] ch       Character to transmit.
 * @return              FALSE - message not complete; a character is returned and should be transmitted.
 * @return              TRUE - message complete; no more characters to transmit
 */
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_FAST_CODE
INT32 tuningEncodeByteUART(UINT32 *packetBuffer, UINT8 * ch)
{
    /* Switch on the module state. */
    switch (s_state)
    {
        case tMS_Tx_RspSTX:
            s_msg_size = PACKET_LENGTH_WORDS(packetBuffer);
            s_state = tMS_Tx_RspSeq;
            *ch = 0x02;
            return 0;

        case tMS_Tx_RspSeq:
            s_state = tMS_Tx_RspData;
            *ch = s_msg_seq;
            s_msg_offs = 0u;
            s_msg_wordpos = 0u;
            return 0;

        case tMS_Tx_RspData:
            /* Test if we need the next word. */
            if (s_msg_wordpos == 0)
            {
                /* Check for end of data. */
                if (s_msg_offs == s_msg_size)
                {
                    /* Transmit the ETX and finish. */
                    s_state = tMS_Rx_CmdSTX;
                    *ch = 0x03;
                    return 0;
                }

                /* Consume the next word. */
                s_msg_word = packetBuffer[s_msg_offs++];
            }

            /* Send the word pieces. */
            switch (s_msg_wordpos)
            {
                case 0u: *ch = (UINT8)(0x80 | (s_msg_word & 0x7F)); s_msg_wordpos = 1u; break;
                case 1u: *ch = (UINT8)(0x80 | ((s_msg_word >>  7) & 0x7F)); s_msg_wordpos = 2u; break;
                case 2u: *ch = (UINT8)(0x80 | ((s_msg_word >> 14) & 0x7F)); s_msg_wordpos = 3u; break;
                case 3u: *ch = (UINT8)(0x80 | ((s_msg_word >> 21) & 0x7F)); s_msg_wordpos = 4u; break;
                case 4u: *ch = (UINT8)(0x80 | ((s_msg_word >> 28) & 0x7F)); s_msg_wordpos = 0u; break;
            }
            return 0;

		default:
			;
    }

    return COMPLETE_NEW_PACKET;

}   // End tuningEncodeByteUART


/**
 * @brief Handler for data ready in the byte communication interface.
 * @param[in] ch  Received character to be placed in the message packet..
 */
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_SLOW_CODE
INT32 tuningDecodeByteUART(UINT32 *packetBuffer, UINT8 ch)
{
    /* Switch on the module state. */
    switch (s_state)
    {
        case tMS_Rx_CmdSTX:
            if (ch == 0x02u)
            {
                s_state = tMS_Rx_CmdSeq;
            }
            break;

        case tMS_Rx_CmdSeq:
            s_msg_seq = ch;
            s_msg_size = 0u;
            s_msg_wordpos = 0u;
            s_state = tMS_Rx_CmdData;
            break;

        case tMS_Rx_CmdData:
            /* Process end of data. */
            if (ch == 0x03u)
            {
                if (s_msg_wordpos != 0 )
                {
                    /* Bad packet, ignore. */
                    s_state = tMS_Rx_CmdSTX;
                }
                else
                {
                    /* New command, process. */
                    s_msg_seqlast  = s_msg_seq;
                    s_state = tMS_Tx_RspSTX;

                    /* Set the return flag indicating that a complete message has arrived. */
					return COMPLETE_NEW_PACKET;
                }
            }
            else if (s_msg_seq != s_msg_seqlast)
            {
                /* Process word data. */
                switch (s_msg_wordpos)
                {
                    case 0u: s_msg_word  =  (ch & 0x7F);        s_msg_wordpos = 1u; break;
                    case 1u: s_msg_word |= ((ch & 0x7F) <<  7); s_msg_wordpos = 2u; break;
                    case 2u: s_msg_word |= ((ch & 0x7F) << 14); s_msg_wordpos = 3u; break;
                    case 3u: s_msg_word |= ((ch & 0x7F) << 21); s_msg_wordpos = 4u; break;
                    case 4u: s_msg_word |= ((ch & 0x7F) << 28); s_msg_wordpos = 0u; break;
                    default:
                    	;
                }

                /* Save complete words. */
                if (s_msg_wordpos == 0u)
                {
                	packetBuffer[s_msg_size++] = s_msg_word;
                }
            }
            break;

        default:
        	;
    }	// End switch

    return 0;

}   // End tuningDecodeByteUART

/*The following helper functions are currently not working, but they demonstrate how our SPI state machine works*/
/**
 * @brief Handler for data ready in the word communication interface.
 * @param[in] word      32-bit word received
 * @return              Returns 1 when a complete message is received.  Otherwise 0.
 * @private

 */
//AWE_OPTIMIZE_FOR_SPEED
//AWE_FW_SLOW_CODE
//BOOL awe_tuningRxCmdWordSPI(AWEInstance * pAWE, UINT32 word)
//{
//    /* Check for the first word (header word) */
//    if (s_msg_wordpos == 0)
//    {
//        /* First word of the packet so get the message length */
//        s_msg_size = (word >> 16) & MAX_MSG_SIZE;
//
//        if( (s_msg_size < 2) || (s_msg_size > pAWE->packetBufferSize) )	//Invalid message
//        {
//        	return FALSE;
//        }
//    }
//
//    pAWE->pPacketBuffer[s_msg_wordpos++] = word;
//
//    if (s_msg_wordpos >= s_msg_size)
//    {
//        /* Complete message received */
//        pAWE->nPacketReceived = NEW_PACKET;
//
//        s_msg_transmit = 1;
//
//        return TRUE;
//    }
//
//    return FALSE;
//
//}   // End awe_tuningRxCmdWordSPI


/**
 * @brief Handler for data word communication transmitter ready.
 * @param[in] word      32-bit word to
 * @return              Returns 1 when a complete message is transmitted.  Otherwise 0.
 * @private
 */
//AWE_OPTIMIZE_FOR_SPEED
//AWE_FW_SLOW_CODE
//BOOL awe_tuningGetReplyWordSPI(AWEInstance * pAWE, UINT32 *word)
//{
//	/* Check the message received and processed */
//	if (s_msg_transmit)
//	{
//		s_msg_transmit = 0;
//
//		/* Save the reply packet length. */
//        s_msg_size = (pAWE->pPacketBuffer[0] >> 16);
//
//        s_msg_wordpos = 0;
//	}
//
//	if (s_msg_wordpos >= s_msg_size)
//	{
//		/* Reply message transmit completed */
//		s_msg_wordpos = 0;
//
//		return TRUE;
//	}
//
//	*word = pAWE->pPacketBuffer[s_msg_wordpos++];
//
//	return FALSE;
//
//}   // End awe_tuningGetReplyWordSPI
/*-----------------------------END SPI/UART HELPER FUNCTIONS------------------------------------- */


void ComputeCheckSumPublic(UINT32 * pPacketBuffer)
{

	UINT32 i;
	UINT32 nLen = pPacketBuffer[0] >> 16;

	UINT32 nCRC = 0;

	for (i = 0; i < (nLen - 1); i++)
	{
		nCRC ^= pPacketBuffer[i];
	}

	pPacketBuffer[nLen - 1] = nCRC;

}	// End ComputeCheckSumPublic


void GenerateInstanceTableReply(UINT32 * pPacketBuffer, UINT32 numInstances, UINT32 * pInstanceTable)
{
	pPacketBuffer[0] = ((3 + numInstances) << 16);
	pPacketBuffer[1] = numInstances;
	memcpy(&pPacketBuffer[2], (void *)pInstanceTable, numInstances * sizeof(UINT32));
	ComputeCheckSumPublic(pPacketBuffer);
}	// End GenerateInstanceTableReply


INT32 float_to_fract32(FLOAT32 x)
{
    // Clip to the allowable range
	FLOAT32 temp;

    if (x < -1.0f)
    {
        return (INT32)0x80000000;
    }

    if (x >= 1.0f)
    {
        return 0x7FFFFFFF;
    }

	temp = x * 2147483648.0f;
	temp += temp > 0.0f? 0.5f : -0.5f;

    // Multiply by 2^31
    return (INT32)temp;

}	// End float_to_fract32


FLOAT32 fract32_to_float(INT32 x)
{
	// Multiply by 2^(-31)
	return ((FLOAT32)x * 4.6566128731e-010f);
}	// End fract32_to_float


INT32 awe_getNextAWBCmd(const UINT32 *pArray, UINT32 arraySize, UINT32 * pErrorOffset, UINT32 *pPacketBuffer)
{
	UINT32 length = PACKET_LENGTH_WORDS((pArray + readIndex)) - 1;

	if (readIndex >= (arraySize - 1) )
	{
		readIndex = 0;
		return AWB_DONE;
	}
	else
	{
		memcpy(pPacketBuffer, (pArray + readIndex), length * sizeof(UINT32));
		ComputeCheckSumPublic(pPacketBuffer);
		readIndex += length;
		*pErrorOffset = readIndex;
		return AWB_NOT_DONE;
	}

}	// End awe_getNextAWBCmd

/**
 * @}
 * End of file
 */
