/* This file is header file of the driver of PDM functions*/
#ifndef AUDIO_DRIVER_H_
#define AUDIO_DRIVER_H_

#include <stdint.h>
#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"

/* AEP config header file */ 
#include "am_audio_platform_config.h"

/* application layer utils header file */
#if configUSE_RTT_DATA_OUTPUT
#include "am_app_utils_ring_buffer.h"
#include "am_app_utils_rtt_recorder.h"
#endif
//*****************************************************************************
// Parameters
//
// Total number of bytes transferred = 320*50*2 = 32000
//*****************************************************************************

#define PCM_FRAME_SIZE          320  // Capture one 320-sample (20-ms) frame at a time
#define NUM_PCM_FRAMES          50   // Number of frames in 1 second
#define PCM_DATA_BYTES          4

//*****************************************************************************
// GLOBALS declaration
//*****************************************************************************
extern void* PDMHandle;
extern volatile int16_t g_numFramesCaptured;
extern volatile bool g_bPDMDataReady;

extern volatile uint32_t g_ui8PCMDataBuff[PCM_FRAME_SIZE];;  // Location of 1-second data buffer

extern volatile bool g_audioRunningFlag;    

extern void am_app_AEP_pdm_init(void);

extern void pdm_data_get(void);

extern void pdm_trigger_dma(void);

extern void am_pdm_isr(void);


#endif /* AUDIO_DRIVER_H_ */
