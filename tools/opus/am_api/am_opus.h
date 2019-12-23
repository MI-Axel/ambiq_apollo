
#ifndef AM_OPUS_H_
#define AM_OPUS_H_
#include <stddef.h>
#include <stdint.h>
//*****************************************************************************
//
// Structure for OPUS encoder configuration
//
//*****************************************************************************
typedef struct
{
    int32_t header_opt;
    uint32_t compress_ratio;
    uint32_t audio_sample_rate;
    int32_t audio_in_bps;
    int32_t channel;
    int32_t complexity;
}
AM_Opus_Encoder_config;

/*
 *
 * User configuration of OPUS encoder
 *
 */

#define AM_OPUS_CONFIG              {           \
                                        0,      \
                                        8,      \
                                        16000,  \
                                        32000,  \
                                        1,      \
                                        4       \
                                    }

//
// header_opt = 0: there is no header added to each frame
// header_opt = 1: there is a header of 2 words added to each frame
//

//am_opus_enc_config.header_opt = 0;
//am_opus_enc_config.compress_ratio = 8;
//am_opus_enc_config.audio_sample_rate = 16000;
//am_opus_enc_config.audio_in_bps = 32000;
//am_opus_enc_config.channel = 1;
//am_opus_enc_config.complexity = 4;

const AM_Opus_Encoder_config am_opus_enc_config = AM_OPUS_CONFIG;

extern int audio_enc_init(int option);

extern int audio_enc_encode_frame(short *p_pcm_buffer, int n_pcm_samples, unsigned char *p_encoded_buffer);

#endif /* AM_OPUS_H_ */


