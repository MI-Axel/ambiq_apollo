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
#include "PlatformAPI.h"
#include "MathHelper.h"
#include "Errors.h"
#include "TargetInfo.h"
#include "TuningHandler.h"
#include "ControlDriver.h"

//#include "TargetInfo_AM_2cm_FBF_SCNR_THF_NT.h"
#include "AM_2cm_FBF_SCNR_THF_NTAWB.h"
/* Define to trap errors during development. */
#define configASSERT(x)     if (( x ) == 0) while(1);

#define INPUT_CHANNEL_COUNT 2

#define OUTPUT_CHANNEL_COUNT 1




#define MONO_CHANNEL_COUNT 1
#define STEREO_CHANNEL_COUNT 2


#define AWE_FRAME_SIZE 80
#define AWE_OUTPUT_BUFFER_SIZE_IN_SAMPLES (AWE_FRAME_SIZE * OUTPUT_CHANNEL_COUNT)


#define AWE_COMMAND_BUFFER_LEN 264


// 16000/1000 * 5 = 80
#define PDM_BUFFER_SIZE 80

#define PCM_SAMPLE_SIZE_IN_BYTES 2
#define PCM_SAMPLE_SIZE_IN_BITS 16


#define MAX_PUMP_COUNT 100

// global variables definition
extern volatile uint32_t g_ui32TimerCount;
extern volatile BOOL g_bPDMDataReady;
extern int32_t g_pi32PCMDataBuff[AWE_FRAME_SIZE];  // Location of 1-second data buffer

extern volatile int32_t in32AudioRunningFlag;
extern volatile BOOL g_bReboot;

extern volatile BOOL g_bAudioPump1Active;
extern volatile BOOL g_bAudioPump2Active;
extern volatile UINT32 g_nPumpCount;

extern UINT32 s_PacketBuffer[];


extern volatile BOOL g_bReadyToSend;
extern AWE_FW_SLOW_ANY_DATA volatile INT32 s_AudioRunning;

extern volatile INT32 g_nReceivedPacketCount;
extern volatile BOOL g_bBlinkLED4ForBoardAlive;

extern volatile UINT32 g_nPumpCount;

extern DWORD g_target_control_flags;

extern AWEInstance g_AWEInstance;

extern void *g_sCOMUART;
extern void* PDMHandle;
extern void BoardSetup(void);

#define UART0_MODULE			        0
#define UART1_MODULE                            1
#define UART0_BUFFER_SIZE                (512 * 2)
#define UART1_BUFFER_SIZE                (512 * 2)

#define AudioWeaverPump_IRQHandler1 	am_software1_isr
#define AudioWeaverPump_IRQHandler2 	am_software2_isr


void CoreInit(void);
void BoardInit(void);
void AudioInit(void);
void awe_pltInit(void);

void UARTMsgInit(void);
void CheckForUARTPacketReady(void);
extern void UART0GetAvailBytes(void);
extern void UART0SendReply(void);

extern INT32 awe_pltAudioStart(void);

extern INT32 awe_pltAudioStop(void);
extern void awe_pltTick(void);
extern volatile BOOL g_bPacketSendComplete;
extern volatile BOOL g_bUARTPacketReceived;
extern void AWEInstanceInit(void);

void AWEProcessing(INT32* nLRSample);


extern void awe_pltGPIOSetPin(UINT32 nPinNo, UINT32 nValue);
extern void awe_pltGPIOTogglePin(UINT32 nPinNo);

#endif
