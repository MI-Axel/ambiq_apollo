#include "scnr.h"


void scnr_init(am_app_scnr_instance_f32* scnr, uint32_t nfft, float32_t db_reduc, uint32_t lookback, float32_t beta, float_t alpha)
{
    scnr->ui32FftLen = nfft;
    scnr->ui32BinNum = nfft/2 + 1;
    scnr->fdB_reduc = db_reduc;
    scnr->ui32LookbackFrames = lookback;
    scnr->fBeta = beta;
    scnr->fAlpha = alpha;
    scnr->fGmin = pow(10, (-db_reduc/20));
}

void scnr_process(am_app_scnr_instance_f32* scnr, float32_t* roll_buff_mag_squared, float32_t* roll_buff_cmplx)
{
    uint32_t cmplx_pair_num = scnr->ui32BinNum;
    uint32_t lookback = scnr->ui32LookbackFrames;
    float32_t beta = scnr->fBeta;
    uint32_t Index = 0;
    float32_t alpha = scnr->fAlpha;
    float32_t gain_min = scnr->fGmin;
    //
    // buffer to store the minimal bin of lookback frames
    // in this algo, lookback == rolling_num
    // p_n_mag: magnitude squared of noise
    // p_sn_mag: magnitude squared of noise+signal
    //
    float32_t p_n_mag[cmplx_pair_num];
    float32_t p_freqbin_mag[lookback];
    float32_t p_sn_mag[cmplx_pair_num];
    float32_t p_s_cmplx[cmplx_pair_num*2];
    memcpy(p_s_cmplx, &roll_buff_cmplx[(lookback-1)*2*cmplx_pair_num], 2*cmplx_pair_num*sizeof(float32_t));
    //
    // scnr gain: real array
    //
    float32_t p_gain_filter[cmplx_pair_num];
    float32_t reduced_sig = 0;
    memcpy(p_sn_mag, &roll_buff_mag_squared[(lookback-1)*cmplx_pair_num], cmplx_pair_num*sizeof(float32_t));
    //
    // generate noise frequency bin
    //
    for(uint32_t idx=0; idx<cmplx_pair_num; idx++)
    {
        for(uint32_t k=0; k<lookback; k++)
        {
            p_freqbin_mag[k] = roll_buff_mag_squared[cmplx_pair_num*k+idx];

//            AM_APP_LOG_DEBUG("%d: %f, ", idx, p_freqbin_mag[k]);   
        }
//        AM_APP_LOG_DEBUG("\n\r");   
        arm_min_f32(p_freqbin_mag, lookback, &p_n_mag[idx], &Index);
//        AM_APP_LOG_DEBUG("%f,\n\r", p_n_mag[idx]);   
    }

    for(uint32_t idx=0; idx<cmplx_pair_num; idx++)
    {
        reduced_sig = (p_sn_mag[idx] - beta*p_n_mag[idx]) > 0. ? (p_sn_mag[idx]-beta*p_n_mag[idx]) : 0.;
        p_gain_filter[idx] = reduced_sig / pow(p_sn_mag[idx], alpha);
        p_gain_filter[idx] = p_gain_filter[idx] > gain_min ? p_gain_filter[idx] : gain_min;
//        AM_APP_LOG_DEBUG("%f, %f, \n\r", p_sn_mag[idx], p_n_mag[idx]);
    }

//    AM_APP_LOG_DEBUG("\n\n\r");
    arm_cmplx_mult_real_f32(p_s_cmplx, p_gain_filter, &roll_buff_cmplx[(lookback-1)*2*cmplx_pair_num], cmplx_pair_num);
}
