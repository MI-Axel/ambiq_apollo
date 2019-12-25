/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     AWE_Wrapper.h
********************************************************************************
*
*     Description:  AudioWeaver Wrapper Header File
*
*******************************************************************************/
  
#ifndef __PLATFORM_H__
#define __PLATFORM_H__
//
// standard C headers
//
#include <stdint.h>
//
// AWE includes
//
#include "StandardDefs.h"
#include "AWECore.h"

/* Define to trap errors during development. */
#define configASSERT(x)     if (( x ) == 0) while(1);


#define AWE_FRAME_SIZE 160
#define AWE_OUTPUT_BUFFER_SIZE_IN_SAMPLES (AWE_FRAME_SIZE * OUTPUT_CHANNEL_COUNT)
#define PCM_SAMPLE_BYTES 4
#define DSPC_SAMPLE_BYTES 2

// 16000/1000 * 5 = 80
#define PDM_BUFFER_SIZE AWE_FRAME_SIZE
#define PCM_SAMPLE_SIZE_IN_BYTES 2
#define PCM_SAMPLE_SIZE_IN_BITS 16

#define MAX_PUMP_COUNT   100
#define OBJECT_FOUND     0

// global variables definition
extern volatile uint32_t g_ui32TimerCount;
extern volatile BOOL g_bPDMDataReady;
extern volatile int32_t g_pi32PCMDataBuff[AWE_FRAME_SIZE];  // Location of 1-second data buffer

extern volatile int32_t in32AudioRunningFlag;
extern volatile BOOL g_bReboot;

extern volatile BOOL g_bAudioPump1Active;
extern volatile BOOL g_bAudioPump2Active;
extern volatile UINT32 g_nPumpCount;

extern UINT32 g_packet_buffer[];

extern AWEInstance g_AWEInstance;

extern volatile uint32_t g_ui32AudioDMAComplete;

#define UART0_MODULE			                0
#define UART1_MODULE                            1
#define UART0_BUFFER_SIZE                (512 * 2)

#define AudioWeaverPump_IRQHandler1 	am_software1_isr
#define AudioWeaverPump_IRQHandler2 	am_software2_isr

extern void AWEInstanceInit();
extern void AWEIdleLoop();

#endif
