/* this header file of frequency domain functions source code*/

#ifdef AM_APP_UTILS_FREQ_DOMAIN_H
#define AM_APP_UTILS_FREQ_DOMAIN_H

extern void am_app_utils_microphone_balance(am_app_utils_ring_buffer_t* buff, uint32_t window_len, bool LRswap, uint8_t ref, float thr,  float* scalar);

extern void am_app_utils_fft(int16_t* time_buff, float* freq_buff, uint32_t fft_size);

extern float am_app_utils_thd_calc(uint32_t base_freq_indx, float* freq_magnitude_buff, uint32_t fft_size, uint32_t sample_freq);


















#endif

