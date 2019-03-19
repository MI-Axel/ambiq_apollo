/**
 * @mainpage Audio Weaver API Documentation
 * <b>Copyright</b> (c) 2007 - 2016 DSP Concepts Inc., All rights reserved.
 * <br>                       1800 Wyatt Drive, Suite 14
 * <br>                       Sunnyvale, CA 95054
 *
 **************************************************************************
 * @defgroup Tuning Tuning Interface API
 * @{
 **************************************************************************
 *
 * @file TuningHandler.c
 * @brief AudioWeaver Tuning Communications API.
 *
 * @details These methods provide an API to interact with the AWE tuning interface.
 *
 ***************************************************************************/
#include "TuningHandler.h"
#include "Framework.h"
#include "PlatformAPI.h"
#include "Errors.h"

#if defined(__ADSP21000__) || defined(__ADSPBLACKFIN__)
#pragma default_section(SWITCH, "awe_fw_slowanydata")
#endif

/* ----------------------------------------------------------------------------
 *   Local Variables
 * ------------------------------------------------------------------------- */

/** Transmit message state. */
AWE_FW_SLOW_ANY_DATA static tMsgState s_state = tMS_Rx_CmdSTX;

/** Payload buffer. */
AWE_FW_SLOW_ANY_DATA static UINT32 *s_msg_data = NULL;

/** Message sequence number. */
AWE_FW_SLOW_ANY_DATA static char s_msg_seq = 0;

/** Message sequence number (previous). */
AWE_FW_SLOW_ANY_DATA static char s_msg_seqlast = 0;

/** Message size. */
AWE_FW_SLOW_ANY_DATA static size_t s_msg_size = 0u;

/** Message size (previous). */
AWE_FW_SLOW_ANY_DATA static size_t s_msg_sizelast = 0u;

/** Message offset. */
AWE_FW_SLOW_ANY_DATA static size_t s_msg_offs = 0u;

/** Message processing word. */
AWE_FW_SLOW_ANY_DATA static UINT32 s_msg_word = 0u;

/** Message processing word index. */
AWE_FW_SLOW_ANY_DATA static UINT32 s_msg_wordpos = 0u;

/* Message length maximum */
static INT32 s_msg_data_len = 0;

/* Packet received */
static UINT32 s_packet_received = 0;

/** @static Flag indicating that the message is processed and the reply is ready to transmit */
volatile INT32 s_msg_transmit = 0;


/**
 * @brief Handler for byte communication transmitter ready.
 * @details This method is typically called in the transmit holding buffer empty interrupt handler.
 * @param[out] ch       Character to transmit.
 * @return              FALSE - message not complete; a character is returned and should be transmitted.
 * @return              TRUE - message complete; no more characters to transmit
 */
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_FAST_CODE
BOOL awe_fwTuningTxByte(UINT8 *ch)
{
	if (s_state == tMS_Tx_WaitingForRsp)
	{
		/* Save the reply packet length. */
        s_msg_size = (s_msg_data[0] >> 16);

        /* Change the state so that the packet starts transmitting back */
        s_state    = tMS_Tx_RspSTX;
	}
	        
    /* Switch on the module state. */   
    switch (s_state)
    {
        case tMS_Tx_RspSTX:
            s_state = tMS_Tx_RspSeq;
            *ch = 0x02;
            return FALSE;

        case tMS_Tx_RspSeq:
            s_state       = tMS_Tx_RspData;
            *ch = s_msg_seq;
            s_msg_offs    = 0u;
            s_msg_wordpos = 0u;
            return FALSE;

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
                    return FALSE;
                }

                /* Consume the next word. */
                s_msg_word = s_msg_data[s_msg_offs++];
            }

            /* Send the word pieces. */
            switch (s_msg_wordpos)
            {
                case 0u: *ch = (unsigned char)(0x80 |  s_msg_word        & 0x7F); s_msg_wordpos = 1u; break;
                case 1u: *ch = (unsigned char)(0x80 | (s_msg_word >>  7) & 0x7F); s_msg_wordpos = 2u; break;
                case 2u: *ch = (unsigned char)(0x80 | (s_msg_word >> 14) & 0x7F); s_msg_wordpos = 3u; break;
                case 3u: *ch = (unsigned char)(0x80 | (s_msg_word >> 21) & 0x7F); s_msg_wordpos = 4u; break;
                case 4u: *ch = (unsigned char)(0x80 | (s_msg_word >> 28) & 0x7F); s_msg_wordpos = 0u; break;
            }
            return FALSE;
    }

    return TRUE;

}   // End awe_fwTuningTxByte


/**
 * @brief Handler for data ready in the byte communication interface.
 * @param[in] ch  Received character to be placed in the message packet.
 * @note Sets global variable "s_packet_received".
 */
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_SLOW_CODE
void awe_fwTuningRxByte(UINT8 ch)
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
            s_msg_seq     = (char)ch;
            s_msg_size    = 0u;
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
                else if (s_msg_seq == s_msg_seqlast)
                {
                    /* Repeat command, send the last response. */
                    s_msg_size = s_msg_sizelast;
                    s_state    = tMS_Tx_RspSTX;

                    /* Set the return flag indicating that a repeated packet is received. */
                    s_packet_received = REPEATED_PACKET;
                }
                else
                {
                    /* New command, process. */
                    s_msg_seqlast  = s_msg_seq;
                    s_state        = tMS_Tx_WaitingForRsp;

                    /* Set the return flag indicating that a complete message has arrived. */
                    s_packet_received = NEW_PACKET;
                }
            }
            else if (s_msg_seq != s_msg_seqlast)
            {
                /* Process word data. */
                switch (s_msg_wordpos)
                {
                    case 0u: s_msg_word  =  ch & 0x7F;        s_msg_wordpos = 1u; break;
                    case 1u: s_msg_word |= (ch & 0x7F) <<  7; s_msg_wordpos = 2u; break;
                    case 2u: s_msg_word |= (ch & 0x7F) << 14; s_msg_wordpos = 3u; break;
                    case 3u: s_msg_word |= (ch & 0x7F) << 21; s_msg_wordpos = 4u; break;
                    case 4u: s_msg_word |= (ch & 0x7F) << 28; s_msg_wordpos = 0u; break;
                }

                /* Save complete words. */
                if (s_msg_wordpos == 0u)
                {
                    s_msg_data[s_msg_size++] = s_msg_word;
                }
            }
        break;
    }

}   // End awe_fwTuningRxByte


/**
 * @brief Handler for data ready in the word communication interface.
 * @param[in] word      32-bit word received
 * @return              Returns 1 when a complete message is received.  Otherwise 0.
 */
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_SLOW_CODE
INT32 awe_fwTuningRxWord(UINT32 word)
{
    /* Check for the first word (header word) */
    if (s_msg_wordpos == 0)
    {
        /* First word of the packet so get the message length */
        s_msg_size = (word >> 16) & MAX_MSG_SIZE;

        if (s_msg_size > s_msg_data_len)
        {
            s_msg_size = s_msg_data_len;
        }
    }

    s_msg_data[s_msg_wordpos++] = word;

    if (s_msg_wordpos == s_msg_size)
    {
        /* Complete message received */
        s_packet_received = NEW_PACKET;

        /*  */
        s_msg_transmit = 1;

        return 1;
    }

    return 0;

}   // End awe_fwTuningRxWord


/**
 * @brief Handler for data word communication transmitter ready.
 * @param[in] word      32-bit word to 
 * @return              Returns 1 when a complete message is transmitted.  Otherwise 0.
 */
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_SLOW_CODE
INT32 awe_fwTuningTxWord(UINT32 *word)
{
	/* Check the message received and processed */
	if(s_msg_transmit)
	{
		s_msg_transmit = 0;
		
		/* Save the reply packet length. */
        s_msg_size = (s_msg_data[0] >> 16);
        
        s_msg_wordpos = 0;
	}
		
	if(s_msg_wordpos == s_msg_size)
	{
		/* Reply message tyransmit completed */
		s_msg_wordpos = 0;
		
		return 0;
	}
	
	*word = s_msg_data[s_msg_wordpos++];
	
	return 1;
}


/**
 * @brief Handler for data ready in the packet communication interface.
 * Called when a new packet has been received over USB or Ethernet.
 * @note Sets global variable "s_packet_received"
 */
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_SLOW_CODE
void awe_fwTuningRxPacket(void)
{
    s_packet_received = NEW_PACKET;

}   // End awe_fwTuningRxPacket


/**
 * @brief Initialize the tuning framework
 * @param[in] packet_buf      Buffer to hold tuning packet
 * @param[in] buf_length      Buffer length in 32-bit words
 */
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
void awe_fwTuningInit(UINT32 * packet_buf, INT32 buf_length)
{
    /* Save the parameters. */
    s_msg_data = packet_buf;

    s_msg_data_len = buf_length;

    /* Initialize packet API */
    awe_fwPacketInit(packet_buf, buf_length);

}   // End awe_fwTuningInit


/**
 * @brief Poll for tuning packet ready
 * @return Returns   REPLY_READY when a complete message is received,
 * @return otherwise returns IDLE_PACKET or E_UNKNOWN_MESSAGE.
 */
INT32 awe_fwTuningTick(AWEInstance *pAWE)
{
    INT32 status = E_SUCCESS;

    if (s_packet_received)
    {
        if (s_packet_received == NEW_PACKET)
        {
            s_packet_received = 0;

            // Process the message
            status = awe_fwPacketProcess(pAWE);

            if (status != E_UNKNOWN_MESSAGE)
            {
                /* Reply is constructed in packet process */
                return REPLY_READY;
            }
            else
            {
                return E_UNKNOWN_MESSAGE;
            }
        }

        if (s_packet_received == REPEATED_PACKET)
        {
            s_packet_received = 0;

            return REPLY_READY;
        }

        s_packet_received = 0;
    }

    return IDLE_PACKET;

}   // End awe_fwTuningTick

/**
 * @}
 * End of file
 */
