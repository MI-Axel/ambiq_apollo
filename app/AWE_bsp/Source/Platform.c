/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     Platform.c
********************************************************************************
*
*     Description:  AWE Platform Interface for Apollo evb
*    
*
*******************************************************************************/
//
// standard C headers
//
#include <stdint.h>
//
// Ambiq apollo headers
//
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

#include "BoardSetup.h"
#include "TargetInfo.h"
#include "Platform.h"
#include "TuningDriver.h"
//
// AWE include 
//
#include "AWECore.h"
//
// Layout related
//
#include "vos_alexa_qual_ControlInterface.h"

/** This awe instance */
AWEInstance g_AWEInstance;

/** The only input pin for this core. */
static IOPinDescriptor s_InputPin = { 0 };

/** The only output pin for this core. */
static IOPinDescriptor s_OutputPin = { 0 };

uint32_t g_packet_buffer[MAX_COMMAND_BUFFER_LEN] = {0};
uint32_t g_packet_bytes = 0;

/*
 * Global variables used by AWE layout processing
 * */
volatile uint32_t g_ui32AudioDMAComplete = 0;


/* ----------------------------------------------------------------------
** Memory heaps
** ------------------------------------------------------------------- */
AWE_FW_SLOW_ANY_CONST UINT32 g_master_heap_size = MASTER_HEAP_SIZE;
AWE_FW_SLOW_ANY_CONST UINT32 g_slow_heap_size = SLOW_HEAP_SIZE;
AWE_FW_SLOW_ANY_CONST UINT32 g_fastb_heap_size = FASTB_HEAP_SIZE;

#if defined( __ICCARM__ )
    #pragma data_alignment=4 
    UINT32 g_master_heap[MASTER_HEAP_SIZE];
    
    #pragma data_alignment=4       
	UINT32 g_fastb_heap[FASTB_HEAP_SIZE] @ ".CCMRAM_Section";
  
    #pragma data_alignment=4 
    UINT32 g_slow_heap[SLOW_HEAP_SIZE];
#else
	#if defined( __GNUC__ )
		__attribute__((__section__(".ccmram")))
	#else
        #if defined ( __CC_ARM )
		__attribute__((__section__(".data_CCMRAM")))
        #endif
	#endif
    __align(4) UINT32 g_fastb_heap[FASTB_HEAP_SIZE];
    __align(4) UINT32 g_master_heap[MASTER_HEAP_SIZE];
    __align(4) UINT32 g_slow_heap[SLOW_HEAP_SIZE];
#endif

/* ----------------------------------------------------------------------
** Module table
** ------------------------------------------------------------------- */
const void * g_module_descriptor_table[] =
{
    // List of modules from ModuleList.h
    (void *)LISTOFCLASSOBJECTS
};

UINT32 g_module_descriptor_table_size = sizeof(g_module_descriptor_table) / sizeof(g_module_descriptor_table[0]);
/* ----------------------------------------------------------------------
** Global variables used by AWE
** ------------------------------------------------------------------- */
volatile BOOL g_bAudioPump1Active = FALSE;
BOOL g_bDeferredProcessingRequired = FALSE;
volatile BOOL g_bAudioPump2Active = FALSE;

UINT32 g_TestElapsedTime = 0;

INT16 g_pin16AudioBuffOutCh0[AWE_FRAME_SIZE];
INT16 g_pin16AudioBuffOutCh1[AWE_FRAME_SIZE];
//
// Global variable used by sys
//

//-----------------------------------------------------------------------------
// METHOD:  AWEInstanceInit
// PURPOSE: Initialize AWE Instance with target details
//-----------------------------------------------------------------------------
void AWEInstanceInit()
{
    memset(&g_AWEInstance, 0, sizeof(AWEInstance) );

    g_AWEInstance.pInputPin = &s_InputPin;
    g_AWEInstance.pOutputPin = &s_OutputPin;

    awe_initPin(&s_InputPin, INPUT_CHANNEL_COUNT, NULL);
    awe_initPin(&s_OutputPin, OUTPUT_CHANNEL_COUNT, NULL);

    // User version word
    g_AWEInstance.userVersion = USER_VER;

    g_AWEInstance.instanceId = CORE_ID;
    g_AWEInstance.coreSpeed = CORE_SPEED;
    g_AWEInstance.profileSpeed = CORE_SPEED;
    g_AWEInstance.pName = "APOLLO3";
    g_AWEInstance.numThreads = NUM_AUDIO_THREADS;
    g_AWEInstance.pModuleDescriptorTable = g_module_descriptor_table;
    g_AWEInstance.numModules = g_module_descriptor_table_size;
    g_AWEInstance.sampleRate = AUDIO_SAMPLE_RATE;
    g_AWEInstance.fundamentalBlockSize = AUDIO_BLOCK_SIZE;

    // Define the heap sizes
    g_AWEInstance.fastHeapASize = MASTER_HEAP_SIZE;
    g_AWEInstance.fastHeapBSize = FASTB_HEAP_SIZE;
    g_AWEInstance.slowHeapSize  = SLOW_HEAP_SIZE;

    // Point to the heaps on this target
    g_AWEInstance.pFastHeapA = g_master_heap;
    g_AWEInstance.pFastHeapB = g_fastb_heap;
    g_AWEInstance.pSlowHeap  = g_slow_heap;

    g_AWEInstance.pPacketBuffer = g_packet_buffer;
    g_AWEInstance.pReplyBuffer = g_packet_buffer;
    g_AWEInstance.packetBufferSize = MAX_COMMAND_BUFFER_LEN;

    // Initialize AWE signal processing instance
    awe_init(&g_AWEInstance);

}   // End AWEInstanceInit

//-----------------------------------------------------------------------------
// METHOD:  AudioWeaver Pump Interrupt Handler
// PURPOSE: Perform AudioWeaver Processing
//-----------------------------------------------------------------------------
void AudioWeaverPump_IRQHandler1(void)
{
    g_bAudioPump1Active = TRUE;

//    NVIC_ClearPendingIRQ(AudioWeaverPump_IRQ1);

    g_bDeferredProcessingRequired = awe_audioPump(&g_AWEInstance, 0);

    g_bAudioPump1Active = FALSE;

}   // End AudioWeaverPump_IRQHandler


//-----------------------------------------------------------------------------
// METHOD:  AudioWeaver Pump Interrupt Handler
// PURPOSE: Perform AudioWeaver Processing
//-----------------------------------------------------------------------------
void AudioWeaverPump_IRQHandler2(void)
{
    g_bAudioPump2Active = TRUE;

//    NVIC_ClearPendingIRQ(AudioWeaverPump_IRQ2);

    g_bDeferredProcessingRequired = awe_audioPump(&g_AWEInstance, 1);

    g_bAudioPump2Active = FALSE;

}   // End AudioWeaverPump_IRQHandler

//-----------------------------------------------------------------------------awe_audioImportSamples
// METHOD:  AWEIdleLoop
// PURPOSE: AWE Idle loop processing
//-----------------------------------------------------------------------------
INT32 packet_process_ret = 0;
void AWEIdleLoop(void)
{
    BOOL bMoreProcessingRequired = FALSE;
//
// Data IO variables
//
    UINT32  fwInCount=0; 
    UINT32 fwOutCount=0;
    UINT32  layoutMask;
    int32_t nSample;
    while(TRUE)
    {
            //
            // Receive adn decode the received packet
            //
            CheckForUARTPacketReady();
	    // Process the received packet
            if(g_bPacketReceived)
            {
                packet_process_ret = awe_packetProcess(&g_AWEInstance);
                g_bPacketReceived = FALSE;
                //
                // Encode and send the packet
                //
                UART0SendReply();
            }

        if (awe_audioIsStarted(&g_AWEInstance) )
        {
            UINT32 classID;
            INT32 nValue;

	    // Perform any needed deferred processing
            if (g_bDeferredProcessingRequired || bMoreProcessingRequired)
            {
                g_bDeferredProcessingRequired = FALSE;
                bMoreProcessingRequired = awe_deferredSetCall(&g_AWEInstance);
            }
            
            if(g_ui32AudioDMAComplete == 1)
            {
                g_ui32AudioDMAComplete = 0;
                //
                // PCM data to left channel and right channel
                //
                for (nSample = 0; nSample < AWE_FRAME_SIZE; nSample++)
                {
                    g_pi16LeftChBuff[nSample] = g_pi32PCMDataBuff[nSample] & 0xFFFF;
                    g_pi16RightChBuff[nSample] = (g_pi32PCMDataBuff[nSample]>>16) & 0xFFFF;               
                }
                //
                // Data IO of layout
                // Get Current AWE layout number of channels
                // layout has 1 input and 1 output
                //
                awe_layoutGetChannelCount(&g_AWEInstance, 0, &fwInCount, &fwOutCount);
    
                if (fwInCount > 0)
                {
                    //for (nSample = 0; nSample < AWE_FRAME_SIZE; nSample++)
                    //{
                        if (fwInCount >= 1)
                        {
                            awe_audioImportSamples(&g_AWEInstance, (void*)g_pi16LeftChBuff, 1, 0, Sample16bit);
                        }
    
                        if (fwInCount >= 2)
                        {
                            awe_audioImportSamples(&g_AWEInstance, (void*)g_pi16RightChBuff, 1, 1, Sample16bit);
                        }
                    //}
    
                }
    
                if (fwOutCount > 0)
                {
                    //for (nSample = 0; nSample < AWE_FRAME_SIZE; nSample++)
                    //{
                        if (fwOutCount >= 1)
                        {
                            awe_audioExportSamples(&g_AWEInstance, (void*)g_pin16AudioBuffOutCh0, 1, 0, Sample16bit);
                        }
                    //}
            
                }
                layoutMask = awe_audioGetPumpMask(&g_AWEInstance);
                if(layoutMask & 1)
                {
                    if (!g_bAudioPump1Active)
                    {
                        g_bAudioPump1Active = TRUE;
                        am_hal_gpio_state_write(48, AM_HAL_GPIO_OUTPUT_SET);
                        awe_audioPump(&g_AWEInstance, 0);
                        am_hal_gpio_state_write(48, AM_HAL_GPIO_OUTPUT_CLEAR);
                        g_bAudioPump1Active = FALSE;
                    }
                }

                if (layoutMask & 2)
                {
                    if (!g_bAudioPump2Active)
                    {

                        g_bAudioPump2Active = TRUE;

                        awe_audioPump(&g_AWEInstance, 1);

                        g_bAudioPump2Active = FALSE;
                    }
                }

            }
/*
 * Control IO of layout
 *
 */
//            // Does the current AWE model have a SinkInt module with this control object ID?
//            if (awe_ctrlGetModuleClass(&g_AWEInstance, AWE_SinkInt1_value_HANDLE, &classID) == OBJECT_FOUND)
//            {
//                // Check that module assigned this object ID is of module class SinkInt
//                if (classID == AWE_SinkInt1_classID)
//                {
//                    // SinkInt module (gets nValue from the running layout)
//                    awe_ctrlGetValue(&g_AWEInstance, AWE_SinkInt1_value_HANDLE, &nValue, 0, 1);
//
//                }
//            }
//

            // Does the current AWE model have a DCSourceInt module with this control object ID?
            if (awe_ctrlGetModuleClass(&g_AWEInstance, AWE_DC1_value_HANDLE, &classID) == OBJECT_FOUND)
            {
                // Check that module assigned this object ID is of module class DCSourceInt
                if (classID == AWE_DC1_classID)
                {
                    // DCSourceInt module (returns nValue to the running layout)
                    awe_ctrlSetValue(&g_AWEInstance, AWE_DC1_value_HANDLE, &nValue, 0, 1);
                }
            }
        }
        
        /* apollo3 related code: breathing LED */
        if (g_ui32TimerCount >=1000)
        {
            g_ui32TimerCount = 0;
            am_devices_led_toggle(am_bsp_psLEDs, 0);
        }

    }   // End while

}   // End AWEIdleLoop

//-----------------------------------------------------------------------------
// METHOD:  awe_pltGetCycleCount
// PURPOSE: Returns the current value in the counter
//-----------------------------------------------------------------------------
uint32_t aweuser_getCycleCount(void)
{

#if USE_PROFILING
    uint32_t nCycles, nElapsedCycles;

    // read Stimer value for Ctimer Cycle count
    nCycles = am_hal_ctimer_read(0, AM_HAL_CTIMER_BOTH);

    // calculate how many milliseconds elapsed
//    nElapsedCycles = nCycles << 2;  // (12Mhz clk source) multiply by 4 at 48MHZ
    nElapsedCycles = nCycles << 3;  // (12Mhz clk source) multiply by 8 at 96MHZ
    return nElapsedCycles;
    return nCycles;
#else    // USE_PROFILING

    return NULL;
#endif    // USE_PROFILING

}   // End awe_pltGetCycleCount


//-----------------------------------------------------------------------------
// METHOD:  awe_pltElapsedCycles
// PURPOSE: Returns the cycle count between start time and end time
//-----------------------------------------------------------------------------


UINT32 aweuser_getElapsedCycles(UINT32 nStartTime, UINT32 nEndTime)
{
#if USE_PROFILING
    UINT32 nElapsedTime;

    if (nEndTime > nStartTime)
    {
            nElapsedTime = nEndTime - nStartTime;
    }
    else
    {
        // Wrap around occurred
        nElapsedTime = ((((UINT32)0xFFFFFFFF) - nStartTime) + nEndTime + 1);
    }
g_TestElapsedTime = nElapsedTime;
	return nElapsedTime;
#else    // USE_PROFILING

    return NULL;
#endif    // USE_PROFILING

}   // End awe_pltElapsedCycles
