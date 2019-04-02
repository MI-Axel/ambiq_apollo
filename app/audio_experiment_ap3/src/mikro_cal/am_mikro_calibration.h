/* this file is the header file of the micro-phone calibration API */

#include "am_audio_platform_config.h"
#include <stdint.h>
#include "arm_math.h"
#include "am_util.h"
#include "am_app_utils.h"
#include "am_app_utils_ring_buffer.h"

#define AVERAGE_WINDOW_LENGTH               16000

extern uint8_t g_ui8MicCalStatus;    
extern uint8_t g_ui8MicCalFlag;
extern float g_pfMicScalar[2];
extern uint32_t g_ui32WindowLen;
extern uint32_t g_ui32SampleNum;
volatile uint8_t g_ui8PcmDataReadyFlag;

extern void am_pcm_amplitude_mean_calc(am_app_utils_ring_buffer_t* buff, bool LRswap, uint32_t window_len, float* LR_mean_array);

extern void am_audio_mikro_balance(am_app_utils_ring_buffer_t* buff, uint32_t window_len, bool LRswap, uint8_t ref, float thr,  float* scalar);
