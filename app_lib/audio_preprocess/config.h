#ifndef CONFIG_H
#define CONFIG_H

#ifdef AM_PART_APOLLO3
#include "am_util.h"
#define AM_APP_LOG_DEBUG(...)                                   am_util_stdio_printf(__VA_ARGS__)
#define AM_APP_LOG_ERROR(...)                                   am_util_stdio_printf(__VA_ARGS__)
#define AM_APP_LOG_INFO(...)                                    am_util_stdio_printf(__VA_ARGS__)

#elif

#define AM_APP_LOG_DEBUG(...)                                   
#define AM_APP_LOG_ERROR(...)                                   
#define AM_APP_LOG_INFO(...)                                    

#endif // AM_PART_APOLLO3



/**************************************************************************************************
* Ram management strategy
*
*
**************************************************************************************************/

#define ALLOC(var, size, type) type var[size]



/**************************************************************************************************
*Audio preprocess layout:
* PCM data (2-ch) --> STFT --> BEAMFORMING --> SCNR --> ISTFT --> High-pass filter --> clean audio (1-ch 16bits)
*  (time-domain)   (freq-2-ch) (freq-1-ch)  (freq-1-ch) (time-domain) (time-domain)   (time-domain)
* 
* Modules ON/OFF
**************************************************************************************************/
#define configUSE_BEAMFORMING                                   1
#define configUSE_SCNR                                          1
#define configUSE_HP_FILTER                                     1

/**************************************************************************************************
* Audio hardware related parameters
**************************************************************************************************/
#define AUDIO_PCM_BYTES                                         4
#define AUDIO_SAMPLE_RATE                                       16000
/**************************************************************************************************
* Audio preprocess parameters (unit: samples)
**************************************************************************************************/
#define AUDIO_PREPROCESS_FFT_SIZE                               128
#define AUDIO_PREPROCESS_CMPLX_SIZE                             (AUDIO_PREPROCESS_FFT_SIZE+2)
#define AUDIO_PREPROCESS_HOP_SIZE                               80
#define AUDIO_PREPROCESS_ROLLING_FRAMES                         3

//
// SCNR modules parameters
//
#define AUDIO_SCNR_DB_REDUCT                                    10
#define AUDIO_SCNR_BETA                                         20
#define AUDIO_SCNR_ALPHA                                        3



























#endif // CONFIG_H
