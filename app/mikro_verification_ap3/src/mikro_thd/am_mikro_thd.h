/* this file is the header file of the micro-phone THD calculation API */

#include <stdint.h>
#include "arm_math.h"
#include "arm_const_structs.h"
    
#include "am_util.h"
#include "am_app_utils.h"
#include "am_app_utils_ring_buffer.h"

extern void am_pcm_fft(int16_t* time_buff, float* freq_buff, uint32_t fft_size);

extern float am_thd_calc(uint32_t base_freq_indx, float* freq_magnitude_buff, uint32_t fft_size, uint32_t sample_freq);
