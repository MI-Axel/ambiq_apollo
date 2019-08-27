#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "am_app_utils.h"
#include "audio_preprocessor.h"

void audio_fft_frame_concatenate(int16_t* prev, int16_t* hop_buff, int16_t* ret, uint32_t hop, uint32_t fft_len)
{
    configASSERT(fft_len >= hop);
    configASSERT(2*hop > fft_len)
    memcpy(ret, prev, (fft_len-hop)*sizeof(int16_t));
    memcpy(&ret[fft_len-hop], hop_buff, hop*sizeof(int16_t));
    //
    // update the previous frame
    //
    memcpy(prev, &hop_buff[2*hop-fft_len], (fft_len-hop)*sizeof(int16_t));

//    for(uint32_t indx=0; indx< fft_len; indx++)
//    {
//        ret[indx] = (float) temp_buff[indx];
//    }

}
