
/* This file is the source file of opus test in apollo3.*/

#include "am_opus.h"
#include "opus.h"
//
// OPUS codec configuration
//
OpusEncoder *g_opusEnc = NULL;
opus_int32 g_opusBandWidth = OPUS_AUTO;
opus_int32 g_opusUseVbr = 0;
opus_int32 g_opusVariableDuration = OPUS_FRAMESIZE_ARG;

int am_opus_encoder_init(OpusEncoder* opusEnc)
{
    int opusErr = 0;
    //
    // Opus codec init
    //
    g_opusEnc = opus_encoder_create((opus_int32)am_opus_enc_config.audio_sample_rate, am_opus_enc_config.channel, OPUS_APPLICATION_AUDIO, &opusErr);
    if (opusErr != OPUS_OK)
    {
        return opusErr;
    }
    opus_encoder_ctl(g_opusEnc, OPUS_SET_BITRATE(am_opus_enc_config.audio_in_bps));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_BANDWIDTH(g_opusBandWidth));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_VBR(g_opusUseVbr));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_VBR_CONSTRAINT(0));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_COMPLEXITY(am_opus_enc_config.complexity));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_INBAND_FEC(0));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_FORCE_CHANNELS(OPUS_AUTO));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_DTX(0));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_PACKET_LOSS_PERC(0));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_LSB_DEPTH(16));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_EXPERT_FRAME_DURATION(g_opusVariableDuration));

//    DebugLog("Opus encoder initialization is finished!\r\n\n");
    return opusErr;
}

uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | (val >> 16);
}

int am_opus_encode_oneshot(OpusEncoder *st, const opus_int16 *pcm, int analysis_frame_size, unsigned char *data, opus_int32 out_data_bytes, int header_opt)
{
    int enc_ret;
    uint32_t* pout = (uint32_t*)data;
    uint32_t tempRange = 0;

    if(header_opt == 0)
    {
        enc_ret = opus_encode(st, pcm, analysis_frame_size, data, out_data_bytes);
        return enc_ret;
    }
    else
    {
        enc_ret = opus_encode(st, pcm, analysis_frame_size, (unsigned char*)(data+8), out_data_bytes);
        opus_encoder_ctl(st, OPUS_GET_FINAL_RANGE(&tempRange));
        pout[0] = swap_uint32(enc_ret);
        pout[1] = swap_uint32(tempRange);
        return (enc_ret+8);
    }
}

int audio_enc_init(int option)
{
    int init_ret = 0;
    init_ret = am_opus_encoder_init(g_opusEnc);
    return init_ret;
}

int audio_enc_encode_frame(short *p_pcm_buffer, int n_pcm_samples, unsigned char *p_encoded_buffer)
{
    // short: 2 bytes
    uint32_t ui32EncOutputBytes = 2 * n_pcm_samples / am_opus_enc_config.compress_ratio;
    return am_opus_encode_oneshot(g_opusEnc, (opus_int16*)p_pcm_buffer, n_pcm_samples, p_encoded_buffer, ui32EncOutputBytes, am_opus_enc_config.header_opt);
}
