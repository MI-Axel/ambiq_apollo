/* This file is header file of the driver of PDM functions*/
#ifndef AUDIO_DRIVER_H_
#define AUDIO_DRIVER_H_

#include <stdint.h>
#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"

//*****************************************************************************
// Parameters
//
// Total number of bytes transferred = 320*50*2 = 32000
//*****************************************************************************

#define FRAME_SIZE 320  // Capture one 320-sample (20-ms) frame at a time
#define NUM_FRAMES 250   // Number of frames in 1 second


//*****************************************************************************
// GLOBALS declaration
//*****************************************************************************
extern void* PDMHandle;
extern volatile int16_t g_numFramesCaptured;
extern volatile bool g_bPDMDataReady;
extern uint32_t
    captured_data[FRAME_SIZE * NUM_FRAMES];  // Location of 1-second data buffer

extern volatile bool g_audioRunningFlag;    

extern void pdm_init(void);

extern void pdm_data_get(void);

extern void am_pdm_isr(void);

#endif /* AUDIO_DRIVER_H_ */
