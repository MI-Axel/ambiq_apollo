//
// Standard Include
//
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
//
// app utils
//
#include "am_app_utils.h"
//
// Procedure config Include
//
#include "audio_preprocessor.h"

//
// Global input and output buffer of audio preprocessor:
// 2 input: left ch and right ch
// 1 output: processed audio to feed the KWS model
//

ALLOC(g_pin16PcmLeftInput, AUDIO_PREPROCESS_HOP_SIZE, int16_t);
ALLOC(g_pin16PcmRightInput, AUDIO_PREPROCESS_HOP_SIZE, int16_t);
ALLOC(g_pin16AudioOutput, AUDIO_PREPROCESS_HOP_SIZE, int16_t);

//
// Intermedia buffer used for calculation
//
ALLOC(pin16LeftPrev, (AUDIO_PREPROCESS_FFT_SIZE-AUDIO_PREPROCESS_HOP_SIZE), int16_t);
ALLOC(pin16RightPrev, (AUDIO_PREPROCESS_FFT_SIZE-AUDIO_PREPROCESS_HOP_SIZE), int16_t);

ALLOC(pin16LeftProcess, AUDIO_PREPROCESS_FFT_SIZE, int16_t);
ALLOC(pin16RightProcess, AUDIO_PREPROCESS_FFT_SIZE, int16_t);

ALLOC(pfLeftProcess, AUDIO_PREPROCESS_FFT_SIZE, float32_t);
ALLOC(pfRightProcess, AUDIO_PREPROCESS_FFT_SIZE, float32_t);

ALLOC(pfLeftFreq, AUDIO_PREPROCESS_CMPLX_SIZE, float32_t);
ALLOC(pfRightFreq, AUDIO_PREPROCESS_CMPLX_SIZE, float32_t);

ALLOC(pfMonoFreq, AUDIO_PREPROCESS_CMPLX_SIZE, float32_t);
ALLOC(pfMonoMagSqr, AUDIO_PREPROCESS_CMPLX_SIZE/2, float32_t);

//ALLOC(pfRollMagSqr, (AUDIO_PREPROCESS_CMPLX_SIZE/2)*AUDIO_PREPROCESS_ROLLING_FRAMES, float32_t);
ALLOC(pfRolMagSqr, (AUDIO_PREPROCESS_CMPLX_SIZE/2)*AUDIO_PREPROCESS_ROLLING_FRAMES, float32_t);
ALLOC(pfRollFreq, AUDIO_PREPROCESS_CMPLX_SIZE*AUDIO_PREPROCESS_ROLLING_FRAMES, float32_t);


//
// Instance of audio pre-process
//
//am_AudioPrepro_Instance VOS_Instance;

//
// common tool function
//
/*
 * Audio preprocess fft size 128; Hop size 80.
 * there is coincidence of 48 samples. 
 * */
void audio_frame_concatenate(int16_t* prev, int16_t* hop_buff, int16_t* ret, uint32_t hop, uint32_t fft_len)
{
    configASSERT(fft_len >= hop);
    configASSERT(2*hop > fft_len);
    memcpy(ret, prev, (fft_len-hop)*sizeof(int16_t));
    memcpy(&ret[fft_len-hop], hop_buff, hop*sizeof(int16_t));
    //
    // update the previous frame
    //
    memcpy(prev, &hop_buff[2*hop-fft_len], (fft_len-hop)*sizeof(int16_t));

}
//
// Update the buffered data in audio preprocessor
// paras:
// rolling_buff: the audio rolling buffer
// roll_hop: updated data size of every data pump (unit: float)
// roll_num: pcm frame size buffered by preprocess handler
//
void audio_frame_rolling_freq(float32_t* rolling_buff, float32_t* input_new, uint32_t roll_hop, uint32_t roll_num)
{
    for(uint32_t i=1; i<(roll_num); i++)
    {
        memcpy(&rolling_buff[(i-1)*roll_hop], &rolling_buff[i*roll_hop], roll_hop*sizeof(float32_t));
    }

    memcpy(&rolling_buff[(roll_num-1)*roll_hop], input_new, roll_hop*sizeof(float32_t));
}
//
// preprocess instance init
//
void am_audio_preprocess_init(am_AudioPrepro_Instance* p_vos)
{
    memset(p_vos, 0, sizeof(am_AudioPrepro_Instance));
    
    //
    // audio preprocess basical info
    //
    p_vos->ui32AudioPreproFftSize = AUDIO_PREPROCESS_FFT_SIZE;
    p_vos->ui32AudioPreproSampleFreq = AUDIO_SAMPLE_RATE;
    
    p_vos->audio_leftCh = g_pin16PcmLeftInput;
    p_vos->audio_rightCh = g_pin16PcmRightInput;
    p_vos->mono_out = g_pin16AudioOutput;
    p_vos->ui32BuffFrames = AUDIO_PREPROCESS_ROLLING_FRAMES;
    
    p_vos->ui32BeamformingEnable = 1;
    p_vos->ui32ScnrEnable = 1;
    p_vos->ui32HPfilterEnable = 1;

    stft_init_f32(&(p_vos->Sf), AUDIO_PREPROCESS_FFT_SIZE, AUDIO_PREPROCESS_HOP_SIZE, AUDIO_PREPROCESS_ROLLING_FRAMES, g_f32HanningWindow);
    if(p_vos->ui32BeamformingEnable == 1)
    {
        beamforming_init_f32(&(p_vos->Bf), g_f32BeamformingWeightLeftChPara, g_f32BeamformingWeightRightChPara, AUDIO_PREPROCESS_FFT_SIZE);
    }
    if(p_vos->ui32ScnrEnable == 1)
    {
        scnr_init(&(p_vos->Sn), AUDIO_PREPROCESS_FFT_SIZE, AUDIO_SCNR_DB_REDUCT, 
                AUDIO_PREPROCESS_ROLLING_FRAMES, AUDIO_SCNR_BETA, AUDIO_SCNR_ALPHA);
    }
    //
    // high pass filter init
    //
    if(p_vos->ui32HPfilterEnable == 1)
    {
        p_vos->f32HpfCutoffFreq = AUDIO_HPF_CUTOFF_FREQ_HZ;
        p_vos->ui32HpStopIndex = (uint32_t) (p_vos->f32HpfCutoffFreq * p_vos->ui32AudioPreproFftSize / p_vos->ui32AudioPreproSampleFreq)
    }
    else
    {
        p_vos->f32HpfCutoffFreq = 0;
        p_vos->ui32HpStopIndex = 0;
    }
   
}

void am_audio_preprocess_handler(am_AudioPrepro_Instance* p_vos)
{
    //
    // input frame of 80 samples concatenated to 128 samples
    //
    audio_frame_concatenate(pin16LeftPrev, g_pin16PcmLeftInput, pin16LeftProcess, AUDIO_PREPROCESS_HOP_SIZE, AUDIO_PREPROCESS_FFT_SIZE);
    audio_frame_concatenate(pin16RightPrev, g_pin16PcmRightInput, pin16RightProcess, AUDIO_PREPROCESS_HOP_SIZE, AUDIO_PREPROCESS_FFT_SIZE);
    //
    // apply window
    //
    stft_window_apply_f32(pin16LeftProcess, pfLeftProcess, &(p_vos->Sf));
    stft_window_apply_f32(pin16RightProcess, pfRightProcess, &(p_vos->Sf));
    //
    // transfer time domain to freq domain
    //
    stft_f32(&(p_vos->Sf), pfLeftProcess, pfLeftFreq);
    stft_f32(&(p_vos->Sf), pfRightProcess, pfRightFreq);


    //
    // Beamforming procedure
    //
    if(p_vos->ui32BeamformingEnable == 1)
    {
        endfire_beamforming(&(p_vos->Bf), pfLeftFreq, pfRightFreq, pfMonoFreq);
    }
    audio_frame_rolling_freq(pfRollFreq, pfMonoFreq, AUDIO_PREPROCESS_CMPLX_SIZE, AUDIO_PREPROCESS_ROLLING_FRAMES);

    //
    // SCNR procedure
    //
    if(p_vos->ui32ScnrEnable == 1)
    {
        arm_cmplx_mag_squared_f32(pfMonoFreq, pfMonoMagSqr, (AUDIO_PREPROCESS_CMPLX_SIZE/2));
     
        audio_frame_rolling_freq(pfRolMagSqr, pfMonoMagSqr, (AUDIO_PREPROCESS_CMPLX_SIZE/2), AUDIO_PREPROCESS_ROLLING_FRAMES);

        scnr_process(&(p_vos->Sn), pfRolMagSqr, pfRollFreq);
    }

    //
    // highpass filter in freq domain
    //
    if(p_vos->ui32HPfilterEnable == 1)
    {
            
    
    }
    //
    // transfer freq domain to time domain
    //
    istft_f32(&(p_vos->Sf), p_vos->ui32BuffFrames, pfRollFreq, p_vos->mono_out);
}



