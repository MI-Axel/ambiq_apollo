#ifndef AUDIO_PREPROCESSOR_H
#define AUDIO_PREPROCESSOR_H
#include <arm_math.h>
#include "config.h"
#include "beamforming.h"
#include "stft.h"
#include "hanning_window.h"
#include "beamforming_weights.h"
#include "scnr.h"

typedef struct
{
//
// input and output interface (externally used)
//
    int16_t* audio_leftCh;
    int16_t* audio_rightCh;
    int16_t* mono_out;
//
// internal used buffs and modules
//
    uint32_t ui32BuffFrames;
//
// including modules and correspondant switch
//
    uint32_t ui32BeamformingEnable;
    uint32_t ui32ScnrEnable;
    uint32_t ui32HPfilterEnable;
    am_app_stft_instance_f32 Sf;
    am_app_beamforming_instance_f32 Bf;
    am_app_scnr_instance_f32 Sn;
}am_AudioPrepro_Instance;

extern void am_audio_preprocess_init(am_AudioPrepro_Instance* p_vos);

extern void am_audio_preprocess_handler(am_AudioPrepro_Instance* p_vos);














#endif // AUDIO_PREPROCESSOR_H
