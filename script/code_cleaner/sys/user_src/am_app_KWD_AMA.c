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
#include "am_app_KWD_ble.h"
#include "wsf_types.h"
#include "wsf_trace.h"

#include <pb_encode.h>
#include <pb_decode.h>
#include "accessories.pb.h"
#include "am_app_KWD_init.h"
#include "am_app_KWD_AMA.h"

#include "am_audio_buffer.h"
#include "hci_api.h"
#include "dm_api.h"
#include "amvos_api.h"

#if USE_OUTPUT_AMVOS_AMA
uint32_t g_ui32AmaDialogID = 0;
uint32_t g_ui32FlushCheckFlag = 0;
eVosAmaStatus_t g_eAmaStatus = VOS_AMA_INIT;
Platform g_eAlexaAppPlatform = Platform_UNDEFINED;

amaEvtCback_t pFuncAmaEventCallback = NULL;

bool am_app_KWD_AMA_evt_cback_register(amaEvtCback_t cback)
{
    if(cback == NULL)
    {
        return true;    // return true if fail
    }
    else
    {
        pFuncAmaEventCallback = cback;
        return false;
    }
    
}

bool am_app_KWD_AMA_tx_ver_exchange_send(void)
{
    sRadioCmdQueue_t bleMessageCmd;
    
    memset(bleMessageCmd.cmd_buf, 0, 20);

    bleMessageCmd.cmd_buf[0] = 0xFE;
    bleMessageCmd.cmd_buf[1] = 0x03; // AMA_TRANSPORT_DATA_TYPE_CMD
    bleMessageCmd.cmd_buf[2] = 0x1;
    bleMessageCmd.cmd_buf[3] = 0x0;
    bleMessageCmd.cmd_buf[4] = 0x0;
    bleMessageCmd.cmd_buf[5] = 0xFF;
    bleMessageCmd.cmd_buf[6] = 0x0;
    bleMessageCmd.cmd_buf[7] = 0xFF;
    bleMessageCmd.len = 20;

    if(xQueueSend(radioCmdQueue, &bleMessageCmd, 0) == NULL)
    {
        AM_APP_LOG_WARNING("queue send fail in rx!\r\n");

        WsfTaskSetReady(0,0);

        return false;
    }

    WsfTaskSetReady(0,0);                // Lewis : Need to review with Renton.

    return true;
}

bool am_app_KWD_AMA_pb_cmd_send(uint8_t *cmd_buf, uint8_t length)
{
    sRadioCmdQueue_t bleMessageCmd;

    bleMessageCmd.cmd_buf[0] = 0x10;
    bleMessageCmd.cmd_buf[1] = 0x0;
    bleMessageCmd.cmd_buf[2] = length;
    memcpy(&(bleMessageCmd.cmd_buf[3]), cmd_buf, length);
    
    bleMessageCmd.len = length + 3;
    
    if(xQueueSend(radioCmdQueue, &bleMessageCmd, 0) == NULL)
    {
        AM_APP_LOG_WARNING("xQueueSend fail in cmd_send!\r\n");

        WsfTaskSetReady(0,0);

        return false;
    }

    #if VOS_configUSE_BLE_Measure_Throughput
        g_ui32AmaDataSentCnt += 1;
    #endif

    WsfTaskSetReady(0,0);                // Lewis : Need to review with Renton.

    return true;
}

uint16_t am_app_KWD_AMA_stream_send(uint8_t* buf, uint32_t len)
{
    sRadioCmdQueue_t bleMessageStream;

    //fill audio data header
    bleMessageStream.cmd_buf[0] = 0x10;
    bleMessageStream.cmd_buf[1] = 0x80;	 //AMA_TRANSPORT_DATA_TYPE_VOICE
    bleMessageStream.cmd_buf[2] = len;
    memcpy(&(bleMessageStream.cmd_buf[3]), buf, len);

    bleMessageStream.len = len + 3;

    if(xQueueSend(radioCmdQueue, &bleMessageStream, 0) == NULL)
    {
        AM_APP_LOG_WARNING("f");
        bleMessageStream.len = -1;
    }
    #if VOS_configUSE_BLE_Measure_Throughput
        else
            g_ui32AmaDataSentCnt += 1;
    #endif

//    if(g_ui8VosTxBusy == 0)
        WsfTaskSetReady(0,0);                // Lewis : Need to review with Renton.

    return bleMessageStream.len; //ui16TxLength;
}

bool am_app_KWD_AMA_sync_rsp_send(void)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    Response *pRsp;
    uint8_t ama_cmd_buffer[128] = {0,};

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));
    message_tx.command = (Command)ControlEnvelope_synchronize_settings_tag;
    message_tx.which_payload = ControlEnvelope_response_tag;
    
    pRsp = (Response *)&(message_tx.payload);
    
    pRsp->error_code = ErrorCode_SUCCESS;
    pRsp->which_payload = Response_error_code_tag;
    
    uint8_t status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);
    
    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_rsp_send(uint8_t tag, uint8_t err)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    Response *pRsp;
    uint8_t ama_cmd_buffer[128] = {0,};

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));
    message_tx.command = (Command) tag;
    message_tx.which_payload = ControlEnvelope_response_tag;
    
    pRsp = (Response *)&(message_tx.payload);
    
    pRsp->error_code = (ErrorCode) err;
    pRsp->which_payload = Response_error_code_tag;
    
    uint8_t status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);
    
    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }
  
    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

extern int32_t g_delayedSample;
extern int32_t g_endingSampleCnt;
extern bool g_config_preroll_enabled;
extern bool g_config_opus_enabled;
extern const uint8_t g_ui8AudioFormat;

bool am_app_KWD_AMA_start_speech_send(void)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    StartSpeech *pStartSpeech;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));
    message_tx.command = Command_START_SPEECH;
    message_tx.which_payload = ControlEnvelope_start_speech_tag;

    pStartSpeech = (StartSpeech *)&(message_tx.payload);

    g_bEnableWakeWordDetection = false; // disable barge-in

    if(g_config_opus_enabled == true)
    {
        if(g_eAlexaAppPlatform == Platform_ANDROID)
            pStartSpeech->settings.audio_format = g_ui8AudioFormat;//AudioFormat_OPUS_16KHZ_32KBPS_CBR_0_20MS;
        else if(g_eAlexaAppPlatform == Platform_IOS)
            pStartSpeech->settings.audio_format = g_ui8AudioFormat;//AudioFormat_OPUS_16KHZ_32KBPS_CBR_0_20MS;
    }
    else
        pStartSpeech->settings.audio_format = g_ui8AudioFormat;//AudioFormat_OPUS_16KHZ_32KBPS_CBR_0_20MS;
//        pStartSpeech->settings.audio_format = AudioFormat_MSBC;

    pStartSpeech->settings.audio_profile = AudioProfile_NEAR_FIELD;
//      pStartSpeech->settings.audio_profile = AudioProfile_FAR_FIELD;
    pStartSpeech->settings.audio_source = AudioSource_STREAM; // Lewis : need to confirm!!

    if(g_ui8PushTalkFlag)
        pStartSpeech->initiator.type = SpeechInitiator_Type_TAP;
    else
    {
        if(g_config_preroll_enabled == true)
        {
            pStartSpeech->initiator.type = SpeechInitiator_Type_WAKEWORD;
//            pStartSpeech->initiator.wake_word.start_index_in_samples = AUDIO_PREBUFF_TIME_MS * BYTES_PER_1MS_DSPC_SAMPLE / BYTES_PER_DSPC_SAMPLE;
//            pStartSpeech->initiator.wake_word.end_index_in_samples = pStartSpeech->initiator.wake_word.start_index_in_samples + g_delayedSample - g_endingSampleCnt;
            // fixme: testing for unified audio buffer
            pStartSpeech->initiator.wake_word.start_index_in_samples = (16000 * 0.5);   // Alexa keyword starts 500ms after the first sound sample
                                                                                        // AUDIO_PREBUFF_TIME_MS * BYTES_PER_1MS_DSPC_SAMPLE / BYTES_PER_DSPC_SAMPLE;
            pStartSpeech->initiator.wake_word.end_index_in_samples = pStartSpeech->initiator.wake_word.start_index_in_samples + g_delayedSample - g_endingSampleCnt;
//            AM_APP_LOG_INFO("[CBWWV] g_delayedSample: %d g_endingSampleCnt %d, Start_Index %d End_Index: %d\n",
//                            g_delayedSample, g_endingSampleCnt,
//                            pStartSpeech->initiator.wake_word.start_index_in_samples,
//                            pStartSpeech->initiator.wake_word.end_index_in_samples);
        }
        else
        {
            pStartSpeech->initiator.type = SpeechInitiator_Type_TAP;
        }
        
    }

    pStartSpeech->dialog.id = g_ui32AmaDialogID;	// ID of each dialog.

    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);

    if (!status)
    {
      AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
      return false;
    }

    extern void AMVOS_RSP_TIMER_RESTART(void);
    AMVOS_RSP_TIMER_RESTART(); // start app response timer
    AM_APP_LOG_DEBUG("[AMA] Command_START_SPEECH sent.\n");

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_reset_connection_send(void)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    ResetConnection *pResetConnection;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));
    message_tx.command = Command_RESET_CONNECTION;
    message_tx.which_payload = ControlEnvelope_reset_connection_tag;
  
    pResetConnection = (ResetConnection *)&(message_tx.payload);
    pResetConnection->timeout = 1;//0;
    pResetConnection->force_disconnect = true;
    
    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);

    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_get_devinfo_rsp_send(void)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    Response *pRsp;
    DeviceInformation *pDevInfo;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

    uint8_t test_bdaddress[6];
    uint8_t * pBda;
    uint8_t name_index;
    
    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));

    message_tx.command = (Command) ControlEnvelope_get_device_information_tag;
    message_tx.which_payload = ControlEnvelope_response_tag;

    pRsp = (Response *)&(message_tx.payload);

    pRsp->error_code = ErrorCode_SUCCESS;
    pRsp->which_payload = Response_device_information_tag;

    pDevInfo = (DeviceInformation *)&(pRsp->payload);
//    strcpy(pDevInfo->serial_number, "11223344");
//    strcpy(pDevInfo->name, "Ambiq-AMA-LE");
//
////  strcpy(pDevInfo->device_type, "A3U3B4RTI76K2J");
//    strcpy(pDevInfo->device_type, "A2Y04QPFCANLPQ");

    pBda = HciGetBdAddr();
    BdaCpy(test_bdaddress, pBda);
    pBda = (uint8_t*)Bda2Str(test_bdaddress);

    strcpy(pDevInfo->serial_number, pBda);

#if VOS_configUSE_BLE || USE_OUTPUT_AMVOS_AMA
    name_index = strlen(g_amaDeviceInformation.name);
    if(name_index <= 10)
    {
        g_amaDeviceInformation.name[name_index++] = '-';    
        g_amaDeviceInformation.name[name_index++] = pBda[8];
        g_amaDeviceInformation.name[name_index++] = pBda[9];
        g_amaDeviceInformation.name[name_index++] = pBda[10];
        g_amaDeviceInformation.name[name_index++] = pBda[11];
        g_amaDeviceInformation.name[name_index++] = '\0';
    }
    strcpy(pDevInfo->name, g_amaDeviceInformation.name);
    strcpy(pDevInfo->device_type, g_amaDeviceInformation.device_type);
#endif    

    pDevInfo->supported_transports_count = 1;
    pDevInfo->supported_transports[0] = Transport_BLUETOOTH_LOW_ENERGY;
  
    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);
    
    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_get_devconf_rsp_send(void)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    Response *pRsp;
    DeviceConfiguration *pDevConf;
    uint8_t ama_cmd_buffer[128] = {0,};

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));
    bool status;

    message_tx.command = (Command) ControlEnvelope_get_device_configuration_tag;
    message_tx.which_payload = ControlEnvelope_response_tag;
    
    pRsp = (Response *)&(message_tx.payload);
    
    pRsp->error_code = ErrorCode_SUCCESS;
    pRsp->which_payload = Response_device_configuration_tag;
    
    pDevConf = (DeviceConfiguration *)&(pRsp->payload);
    pDevConf->needs_assistant_override = false;
    pDevConf->needs_setup = true;
    
    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);
    
    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_speech_rsp_send(uint8_t cmd, uint32_t dialogId)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    Response *pRsp;
    Dialog *pDialog;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

   pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));

    message_tx.command = (Command) cmd;
    message_tx.which_payload = ControlEnvelope_response_tag;
    
    pRsp = (Response *)&(message_tx.payload);
    
    pRsp->error_code = ErrorCode_SUCCESS;
    pRsp->which_payload = Response_dialog_tag;
    
    pDialog = (Dialog *)&(pRsp->payload);
    pDialog->id = dialogId;
    
    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);
    
    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_provide_speech_rsp_send(uint32_t dialogId)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    Response *pRsp;
    SpeechProvider *pSpeechProvider;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));

    message_tx.command = Command_PROVIDE_SPEECH;
    message_tx.which_payload = ControlEnvelope_response_tag;
  
    pRsp = (Response *)&(message_tx.payload);
    
    pRsp->error_code = ErrorCode_SUCCESS;
    pRsp->which_payload = Response_speech_provider_tag;
    
    pSpeechProvider = (SpeechProvider *)&(pRsp->payload);
    pSpeechProvider->speech_settings.audio_format = g_ui8AudioFormat;//AudioFormat_OPUS_16KHZ_32KBPS_CBR_0_20MS;
//    pSpeechProvider->speech_settings.audio_format = AudioFormat_MSBC;
    pSpeechProvider->speech_settings.audio_profile = AudioProfile_NEAR_FIELD;
//    pSpeechProvider->speech_settings.audio_profile = AudioProfile_FAR_FIELD;
    pSpeechProvider->speech_settings.audio_source = AudioSource_STREAM;  // Lewis : need to confirm!!
    pSpeechProvider->dialog.id = dialogId;
    
    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);
  
    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_notify_config_send(void)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    DeviceConfiguration *pConfig;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));
    message_tx.command = (Command) ControlEnvelope_notify_device_configuration_tag;
    message_tx.which_payload = ControlEnvelope_notify_device_configuration_tag;

    pConfig = (DeviceConfiguration *)&(message_tx.payload);

    pConfig->needs_assistant_override = FALSE;
    pConfig->needs_setup = TRUE;

    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);

    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_get_central_info_send(void)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    GetCentralInformation *pCentInfo;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));
    message_tx.command = (Command) ControlEnvelope_get_central_information_tag;
    message_tx.which_payload = ControlEnvelope_get_central_information_tag;

    pCentInfo = (GetCentralInformation *)&(message_tx.payload);

    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);

    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_keep_alive_send(void)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    KeepAlive *pKeepAlive;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));
    message_tx.command = (Command) ControlEnvelope_keep_alive_tag;
    message_tx.which_payload = ControlEnvelope_keep_alive_tag;

    pKeepAlive = (KeepAlive *)&(message_tx.payload);

    pKeepAlive->dummy_field = 0;        // Lewis : What is this value?

    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);

    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_get_state_send(uint32_t feature)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    GetState *pGetState;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));

    message_tx.command = ControlEnvelope_get_state_tag;
    message_tx.which_payload = ControlEnvelope_get_state_tag;
  
    pGetState = (GetState *)&(message_tx.payload);
    pGetState->feature = feature;
    
    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);
  
    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

bool am_app_KWD_AMA_get_state_rsp_send(uint32_t feature)
{
    ControlEnvelope message_tx = ControlEnvelope_init_zero;
    Response *pRsp;
    State *pState;
    uint8_t ama_cmd_buffer[128] = {0,};
    bool status;

    pb_ostream_t ostream = pb_ostream_from_buffer(ama_cmd_buffer, sizeof(ama_cmd_buffer));

    message_tx.command = Command_GET_STATE;
    message_tx.which_payload = ControlEnvelope_response_tag;
  
    pRsp = (Response *)&(message_tx.payload);

    switch(feature)
    {
        case 0x132:     // Bluetooth A2DP Connected
            pRsp->error_code = ErrorCode_SUCCESS;
            pRsp->which_payload = Response_state_tag;

            pState = (State *)&(pRsp->payload);
            pState->feature = feature;
            pState->which_value = sizeof(bool);
            pState->value.boolean = false;
            break;

        case 0x133:     // Bluetooth HFP Connected
            pRsp->error_code = ErrorCode_SUCCESS;
            pRsp->which_payload = Response_state_tag;

            pState = (State *)&(pRsp->payload);
            pState->feature = feature;
            pState->which_value = sizeof(bool);
            pState->value.boolean = false;
            break;

        default:
            pRsp->error_code = ErrorCode_UNSUPPORTED;
            pRsp->which_payload = Response_error_code_tag;      
            break;
    }
    
    status = pb_encode(&ostream, ControlEnvelope_fields, &message_tx);
  
    if (!status)
    {
        AM_APP_LOG_INFO("Encoding failed: %s\n", PB_GET_ERROR(&ostream));
        return false;
    }

    return am_app_KWD_AMA_pb_cmd_send(ama_cmd_buffer, ostream.bytes_written);
}

int am_app_KWD_AMA_rx_handler(uint8_t *data, uint16_t len)
{
    size_t message_length;

    /* Allocate space on the stack to store the message data.
     *
     * Nanopb generates simple struct definitions for all the messages.
     * - check out the contents of simple.pb.h!
     * It is a good idea to always initialize your structures
     * so that you do not have garbage data from RAM in there.
     */
    ControlEnvelope message_rx = ControlEnvelope_init_zero;

    /* Create a stream that reads from the buffer. */
    pb_istream_t istream;

    ProvideSpeech *pProvideSpeech;
    StopSpeech *pStopSpeech;
    EndpointSpeech *pEndpointSpeech;
    NotifySpeechState *pSpeechState;
    CentralInformation *pCentralInfo;
    Response *pResponse;

    if(!data){
        AM_APP_LOG_WARNING("NULL data ptr\n");
        return -1;
    }

    if(data[1] & AMA_TRANSPORT_HEADER_LENGTH_TYPE_MASK) {
        message_length = (uint16_t)data[2];
        istream = pb_istream_from_buffer(data + 4, message_length);
    }
    else {
        message_length = (uint8_t)data[2];
        istream = pb_istream_from_buffer(data + 3, message_length);
    }

    /* Now we are ready to decode the message. */
    pb_decode(&istream, ControlEnvelope_fields, &message_rx);

//    AM_APP_LOG_INFO("[AMA] RX command : %d", message_rx.command);
//    AM_APP_LOG_INFO("which_payload : %d", message_rx.which_payload);

    switch(message_rx.command)
    {
        case Command_PROVIDE_SPEECH :
            pProvideSpeech = (ProvideSpeech *)&(message_rx.payload);
            AM_APP_LOG_INFO("[AMA] Cmd PROVIDE_SPEECH Cmd recv\n");
            am_app_KWD_AMA_provide_speech_rsp_send(pProvideSpeech->dialog.id);
            am_kwd_streaming_provide_speech();

            if(pFuncAmaEventCallback != NULL)
            {
                pFuncAmaEventCallback(VOS_AMA_EVT_PROVIDE_SPEECH, NULL);
            }
            break;

        case Command_START_SPEECH :
            AM_APP_LOG_INFO("[AMA] Cmd START_SPEECH Ack recv\n");
            break;

        case Command_STOP_SPEECH :
            pStopSpeech = (StopSpeech *)&(message_rx.payload);
            AM_APP_LOG_INFO("[AMA] Cmd STOP_SPEECH dialog %d err_no %d recv\n", pStopSpeech->dialog.id, pStopSpeech->error_code);

//            am_app_utils_flush_ring_buffer(&am_KWD_ring_buffers[AM_APP_RINGBUFF_POST_AUDIO_STREAM]);

#if USE_UNIVERSAL_AUDIO_BUFFER
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
#endif // USE_UNIVERSAL_AUDIO_BUFFER

            g_bEnableWakeWordDetection = true;
#if VOS_configUSE_PUSH_TO_TALK
#if defined (AM_PART_APOLLO3)
            // enable push to talk interrupt again
            am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#else
            // enable push to talk interrupt again
            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif //#if defined (AM_PART_APOLLO3)
#endif // VOS_configUSE_PUSH_TO_TALK
            am_kwd_streaming_stop();

            am_app_KWD_AMA_speech_rsp_send(Command_STOP_SPEECH, pStopSpeech->dialog.id);

            if(g_ui32AmaDialogID == 2^31 - 1)
                g_ui32AmaDialogID = 0;
            else
                g_ui32AmaDialogID++;

            if(pFuncAmaEventCallback != NULL)
            {
                pFuncAmaEventCallback(VOS_AMA_EVT_STOP_SPEECH, NULL);
            }
            break;

        case Command_ENDPOINT_SPEECH :
            pEndpointSpeech = (EndpointSpeech *)&(message_rx.payload);
            AM_APP_LOG_INFO("[AMA] Cmd ENDPOINT_SPEECH dialog %d recv\n", pEndpointSpeech->dialog.id);

//            am_app_utils_flush_ring_buffer(&am_KWD_ring_buffers[AM_APP_RINGBUFF_POST_AUDIO_STREAM]);
            
#if USE_UNIVERSAL_AUDIO_BUFFER
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
#endif // USE_UNIVERSAL_AUDIO_BUFFER
            g_bEnableWakeWordDetection = true;

#if VOS_configUSE_PUSH_TO_TALK
#if defined (AM_PART_APOLLO3)
            // enable push to talk interrupt again
            am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#else
            // enable push to talk interrupt again
            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif //#if defined (AM_PART_APOLLO3)
#endif // VOS_configUSE_PUSH_TO_TALK

            am_kwd_streaming_stop();

            am_app_KWD_AMA_speech_rsp_send(Command_ENDPOINT_SPEECH, pEndpointSpeech->dialog.id);

            if(g_ui32AmaDialogID == 2^31 - 1)
                g_ui32AmaDialogID = 0;
            else
                g_ui32AmaDialogID++;
            break;

        case Command_NOTIFY_SPEECH_STATE :
            g_ui32FlushCheckFlag = 1;
            pSpeechState = (NotifySpeechState *)&(message_rx.payload);
            switch(pSpeechState->state)
            {
                case SpeechState_IDLE :
                    AM_APP_LOG_INFO("[AMA] Cmd NOTIFY_SPEECH_STATE recv IDLE\n");
                    g_eAmaStatus = VOS_AMA_IDLE;

                    
#if USE_UNIVERSAL_AUDIO_BUFFER
                    if ((g_ui32FlushCheckFlag == 1)&&(g_bEnableWakeWordDetection == true))
                    {
                        am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
                        am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
                    }
#endif // USE_UNIVERSAL_AUDIO_BUFFER
                    g_bEnableWakeWordDetection = true;

#if VOS_configUSE_PUSH_TO_TALK
#if defined (AM_PART_APOLLO3)
            // enable push to talk interrupt again
            am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#else
            // enable push to talk interrupt again
            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif //#if defined (AM_PART_APOLLO3)
#endif // VOS_configUSE_PUSH_TO_TALK

                    break;

                case SpeechState_LISTENING :
                    g_ui32FlushCheckFlag = 0;
                    AM_APP_LOG_INFO("[AMA] Cmd NOTIFY_SPEECH_STATE recv LISTENING\n");
                    g_eAmaStatus = VOS_AMA_LISTENING;

                    am_app_KWD_AMA_get_state_send(0x203);
                    
                    if(pFuncAmaEventCallback != NULL)
                    {
                        pFuncAmaEventCallback(VOS_AMA_EVT_LISTENING, NULL);
                    }
                    break;

                case SpeechState_PROCESSING :
                    g_ui32FlushCheckFlag = 1;
                    AM_APP_LOG_INFO("[AMA] Cmd NOTIFY_SPEECH_STATE recv PROCESSING\n");
                    g_eAmaStatus = VOS_AMA_PROCESSING;

                    
#if USE_UNIVERSAL_AUDIO_BUFFER
                    am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
                    am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
#endif // USE_UNIVERSAL_AUDIO_BUFFER
                    g_bEnableWakeWordDetection = true;

#if VOS_configUSE_PUSH_TO_TALK
#if defined (AM_PART_APOLLO3)
                    // enable push to talk interrupt again
                    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
                    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#else
                    // enable push to talk interrupt again
                    am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
                    am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif //#if defined (AM_PART_APOLLO3)
#endif // VOS_configUSE_PUSH_TO_TALK

                    break;

                case SpeechState_SPEAKING :
                    g_ui32FlushCheckFlag = 1;
                    AM_APP_LOG_INFO("[AMA] Cmd NOTIFY_SPEECH_STATE recv SPEAKING\n");
                    g_eAmaStatus = VOS_AMA_SPEAKING;
                    break;

                default :
                    g_ui32FlushCheckFlag = 1;
                    AM_APP_LOG_INFO("[AMA] Cmd NOTIFY_SPEECH_STATE recv unknown %d\n", pSpeechState->state);
                    break;
            }        
            break;

        case Command_START_SETUP :
            AM_APP_LOG_INFO("[AMA] Cmd START_SETUP recv\n");
            am_app_KWD_AMA_rsp_send(ControlEnvelope_start_setup_tag, ErrorCode_SUCCESS);
            break;

        case Command_COMPLETE_SETUP :
            AM_APP_LOG_INFO("[AMA] Cmd COMPLETE_SETUP recv\n");

#if USE_UNIVERSAL_AUDIO_BUFFER
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
#endif // USE_UNIVERSAL_AUDIO_BUFFER
            g_bEnableWakeWordDetection = true;

#if VOS_configUSE_PUSH_TO_TALK
#if defined (AM_PART_APOLLO3)
            // enable push to talk interrupt again
            am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#else
            // enable push to talk interrupt again
            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif //#if defined (AM_PART_APOLLO3)
#endif // VOS_configUSE_PUSH_TO_TALK

            am_app_KWD_AMA_rsp_send(ControlEnvelope_complete_setup_tag, ErrorCode_SUCCESS);
            break;

        case Command_GET_DEVICE_INFORMATION :
            AM_APP_LOG_INFO("[AMA] Cmd GET_DEVICE_INFORMATION recv\n");
            am_app_KWD_AMA_get_devinfo_rsp_send();

            if(pFuncAmaEventCallback != NULL)
            {
                pFuncAmaEventCallback(VOS_AMA_EVT_GET_DEV_INFO, NULL);
            }
            break;

        case Command_GET_DEVICE_CONFIGURATION :
            AM_APP_LOG_INFO("[AMA] Cmd GET_DEVICE_CONFIGURATION recv\n");
            am_app_KWD_AMA_get_devconf_rsp_send();
            break;

        case Command_SYNCHRONIZE_SETTINGS :
            AM_APP_LOG_INFO("[AMA] Cmd SYNCHRONIZE_SETTINGS recv\n");
            g_eAmaStatus = VOS_AMA_IDLE;
//            am_app_KWD_AMA_get_devinfo_rsp_send();    // Lewis : Workaround for Android AMA app. need to check with Alexa team!
//            am_app_KWD_AMA_get_devconf_rsp_send();    // Lewis : Workaround for Android AMA app.

#if USE_UNIVERSAL_AUDIO_BUFFER
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
#endif // USE_UNIVERSAL_AUDIO_BUFFER
            am_app_KWD_reset_detected_flag();
            g_bEnableWakeWordDetection = true;

#if VOS_configUSE_PUSH_TO_TALK
#if defined (AM_PART_APOLLO3)
            // enable push to talk interrupt again
            am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#else
            // enable push to talk interrupt again
            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif //#if defined (AM_PART_APOLLO3)
#endif // VOS_configUSE_PUSH_TO_TALK

            g_bAmaIsReady = true;

            am_app_KWD_AMA_sync_rsp_send();

            am_app_KWD_AMA_get_central_info_send();

            break;

        case Command_KEEP_ALIVE :
            if(message_rx.which_payload == ControlEnvelope_response_tag)
                AM_APP_LOG_INFO("[AMA] Cmd KEEP_ALIVE Ack recv\n");
            else if(message_rx.which_payload == ControlEnvelope_keep_alive_tag)
            {
                AM_APP_LOG_INFO("[AMA] Cmd KEEP_ALIVE recv\n");
                am_app_KWD_AMA_rsp_send(message_rx.command, ErrorCode_SUCCESS);
            }
            break;

        case Command_GET_STATE :
            if(message_rx.which_payload == ControlEnvelope_response_tag)
            {
                pResponse = (Response *)&(message_rx.payload);
                State *pState = (State *)&(pResponse->payload);
//                AM_APP_LOG_INFO("[AMA] Platform : %d Name : %s\n", pCentralInfo->platform, pCentralInfo->name);
                AM_APP_LOG_INFO("[AMA] Cmd GET_STATE Ack recv feature 0x%x value %d\n" , 
                            pState->feature, pState->which_value == 1?
                              pState->value.boolean : pState->value.integer);                
//                g_eAlexaAppPlatform = pCentralInfo->platform;

                if(pFuncAmaEventCallback != NULL)
                {
                    amaGetStateRsp_t state;
                    state.feature = pState->feature;
                    state.value = pState->value.integer;
                    pFuncAmaEventCallback(VOS_AMA_EVT_GET_STATE, (void*)&state);
                }
            }
            else if(message_rx.which_payload == ControlEnvelope_get_state_tag)
            {
                GetState *pGetState = (GetState *)&(message_rx.payload);
                AM_APP_LOG_INFO("[AMA] Cmd GET_STATE recv feature 0x%x\n", pGetState->feature);
                am_app_KWD_AMA_get_state_rsp_send(pGetState->feature);
            }
            break;

        case Command_GET_CENTRAL_INFORMATION :
            if(message_rx.which_payload == ControlEnvelope_response_tag)
            {
                AM_APP_LOG_INFO("[AMA] Cmd GET_CENTRAL_INFORMATION Ack recv\n");
                pResponse = (Response *)&(message_rx.payload);
                pCentralInfo = (CentralInformation *)&(pResponse->payload);
                AM_APP_LOG_INFO("[AMA] Platform : %d Name : %s\n", pCentralInfo->platform, pCentralInfo->name);
                g_eAlexaAppPlatform = pCentralInfo->platform;

                if(pFuncAmaEventCallback != NULL)
                {
                    pFuncAmaEventCallback(VOS_AMA_EVT_GET_CENTRAL_INFO, NULL);
                }
            }
            break;

        case Command_SYNCHRONIZE_STATE :
            SynchronizeState *pSyncState = (SynchronizeState *)&(message_rx.payload);
            AM_APP_LOG_INFO("[AMA] Cmd SYNCHRONIZE_STATE recv feature 0x%x value %d\n ",
                            pSyncState->state.feature, pSyncState->state.which_value == 1?
                              pSyncState->state.value.boolean : pSyncState->state.value.integer);
            am_app_KWD_AMA_rsp_send(ControlEnvelope_synchronize_state_tag, ErrorCode_SUCCESS);

            if(pFuncAmaEventCallback != NULL)
            {
                amaSyncStateRsp_t state;
                state.feature = pSyncState->state.feature;
                state.value = pSyncState->state.value.integer;
                pFuncAmaEventCallback(VOS_AMA_EVT_SYNC_STATE, (void*)&state);
            }

            break;

        default :
            AM_APP_LOG_INFO("[AMA] Cmd %d recv\n", message_rx.command);
            am_app_KWD_AMA_rsp_send(message_rx.command, ErrorCode_SUCCESS);
            break;
    }

    return 0;
}

#endif // USE_OUTPUT_AMVOS_AMA
