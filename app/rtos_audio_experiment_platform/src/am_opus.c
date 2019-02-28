
/* This file is the source file of opus test in apollo3.*/

#include "am_opus.h"



//
// OPUS codec configuration
//
OpusEncoder *g_opusEnc = NULL;
int g_opusErr;
uint32_t g_audioSampleRate = 16000;
int32_t g_audioChannel = 1;
opus_int32 g_opusComplexity = 4;
opus_int32 g_opusEncRet;
opus_int32 g_opusBitRate_bps = 32000;
//opus_int32 g_opusBitRate_bps = 16000;
opus_int32 g_opusBandWidth = OPUS_AUTO;
opus_int32 g_opusUseVbr = 0;
opus_int32 g_opusVariableDuration = OPUS_FRAMESIZE_ARG;



uint8_t g_opusOutputBuff[OPUS_MAX_PACKET] = {0};


void am_opus_encoder_init(OpusEncoder* opusEnc)
{
    //
    // Opus codec init
    //
    g_opusEnc = opus_encoder_create((opus_int32)g_audioSampleRate, g_audioChannel, OPUS_APPLICATION_AUDIO, &g_opusErr);
    if (g_opusErr != OPUS_OK)
    {
//        am_util_stdio_printf("Cannot create encoder: %s\r\n", opus_strerror(g_opusErr));
        while(1);
    }
    opus_encoder_ctl(g_opusEnc, OPUS_SET_BITRATE(g_opusBitRate_bps));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_BANDWIDTH(g_opusBandWidth));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_VBR(g_opusUseVbr));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_VBR_CONSTRAINT(0));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_COMPLEXITY(g_opusComplexity));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_INBAND_FEC(0));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_FORCE_CHANNELS(OPUS_AUTO));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_DTX(0));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_PACKET_LOSS_PERC(0));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_LSB_DEPTH(16));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_EXPERT_FRAME_DURATION(g_opusVariableDuration));

    am_util_stdio_printf("Opus encoder initialization is finished!\r\n\n");

}
