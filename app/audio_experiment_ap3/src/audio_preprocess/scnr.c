#include "scnr.h"

void scnr_init(am_app_scnr_instance_f32* scnr, uint16_t nfft, uint16_t db_reduc, uint16_t lookback, uint16_t beta, uint16_t alpha)
{
    scnr->ui16FftLen = nfft;
    scnr->ui16BinNum = nfft/2 + 1;
    scnr->ui16dB_reduc = db_reduc;
    scnr->ui16LookbackFrames = lookback;
    scnr->ui16Beta = beta;
    scnr->ui16Alpha = alpha;
}

void scnr_process(am_app_scnr_instance_f32* scnr, float32_t* p_sn)
{
    float32_t p_sn_mag[scnr->ui16BinNum];
        


}
