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
#include "Platform.h"
#include "am_util.h"
//#include "aweOptionalFeatures.h"

AWEInstance g_AWEInstance;
CoreDescriptor g_Core[1];
volatile BOOL gReset = FALSE;
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

/* Array of pointers to module descriptors. This is initialized at compile time.
Each item is the address of a module descriptor that we need linked in. The
linker magic is such that only those modules referenced here will be in the
final program. */
//const ModClassModule *g_module_descriptor_table[] =
//{
	// The suitably cast pointers to the module descriptors.
//    LISTOFCLASSOBJECTS
//};

//AWE_MOD_SLOW_DM_DATA UINT32 g_module_descriptor_table_size = sizeof(g_module_descriptor_table) / sizeof(g_module_descriptor_table[0]);

// Audio Running Flag

volatile int32_t in32AudioRunningFlag = 0;

volatile BOOL g_bReboot = FALSE;
volatile BOOL g_bBlinkLED4ForBoardAlive = TRUE;

/** The only input pin for this core. */
static IOPinDescriptor s_InputPin[1];

/** The only output pin for this core. */
static IOPinDescriptor s_OutputPin[1];

volatile BOOL g_bAudioPump1Active = FALSE;
volatile BOOL g_bAudioPump2Active = FALSE;
volatile UINT32 g_nPumpCount = 0;

///-----------------------------------------------------------------------------
/// @name  INT32 awe_pltAudioStart(void)
/// @brief Start audio processing
///-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
INT32 awe_pltAudioStart(void)
{
	// At this point the model is fully instantiated and the control I/O can be setup
    ControlInit();
    in32AudioRunningFlag = 1;
    return 0;

}   // End awe_pltAudioStart


///-----------------------------------------------------------------------------
/// @name  INT32 awe_pltAudioStop(void)
/// @brief Stop audio processing
///-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
INT32 awe_pltAudioStop(void)
{
    // Mark the audio as stopped
    in32AudioRunningFlag = 0;

    return 0;

}   // End awe_pltAudioStop

//-----------------------------------------------------------------------------
// METHOD:  awe_pltCoreSendCommand
// PURPOSE: Send command and wait for reply
//-----------------------------------------------------------------------------
//INT32 awe_pltCoreSendCommand(void *pData, UINT32 * txBuffer, UINT32 * rxBuffer)
//{
//    return awe_fwPacketProcess(&g_AWEInstance);

//}	// End awe_pltCoreSendCommand
//-----------------------------------------------------------------------------
// METHOD:  awe_pltGetCores
// PURPOSE: Report number of cores in use on this target
//-----------------------------------------------------------------------------
int awe_pltGetCores()
{
     return 1;

}   // End awe_pltGetCores


//-----------------------------------------------------------------------------
// METHOD:  awe_pltDestroyAll
// PURPOSE: Destroy all core instances
//-----------------------------------------------------------------------------
void awe_pltDestroyAll()
{
    awe_fwDestroy(&g_AWEInstance);

}   // End awe_pltDestroyAll
//-----------------------------------------------------------------------------
// METHOD:  awe_pltGetCycleCount
// PURPOSE: Returns the current value in the counter
//-----------------------------------------------------------------------------
uint32_t awe_pltGetCycleCount(void)
{

#if USE_PROFILING
    uint32_t nCycles, nElapsedCycles;

    // read Stimer value for Ctimer Cycle count
    nCycles = am_hal_ctimer_read(0, AM_HAL_CTIMER_BOTH);

    // calculate how many milliseconds elapsed
    nElapsedCycles = nCycles << 2;  // (12Mhz clk source) multiply by 4

    return nElapsedCycles;
#else

    return NULL;
#endif

}   // End awe_pltGetCycleCount


//-----------------------------------------------------------------------------
// METHOD:  awe_pltElapsedCycles
// PURPOSE: Returns the cycle count between start time and end time
//-----------------------------------------------------------------------------
UINT32 awe_pltElapsedCycles(UINT32 nStartTime, UINT32 nEndTime)
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

	return nElapsedTime;
 #else

    return NULL;
#endif

}   // End awe_pltElapsedCycles

void AWEInstanceInit()
{
    uint32_t nInputWireInfo = INFO1_PROPS(INPUT_CHANNEL_COUNT,
                                          AWE_FRAME_SIZE,
                                          IS_COMPLEX,
                                          SAMPLE_SIZE_IN_BYTES);

    uint32_t nOutputWireInfo = INFO1_PROPS(OUTPUT_CHANNEL_COUNT,
                                         AWE_FRAME_SIZE,
                                         IS_COMPLEX,
                                         SAMPLE_SIZE_IN_BYTES);

    memset(&g_AWEInstance, 0, sizeof(AWEInstance) );

    // Point to the start and stop functions.
    g_AWEInstance.m_pAwe_pltAudioStart = awe_pltAudioStart;
    g_AWEInstance.m_pAwe_pltAudioStop = awe_pltAudioStop;

    // Point to our private pins.
    g_AWEInstance.m_pInterleavedInputPin = s_InputPin;
    g_AWEInstance.m_pInterleavedOutputPin = s_OutputPin;

    // Point to the global module table.
//    g_AWEInstance.m_module_descriptor_table_size = sizeof(g_module_descriptor_table) >> 2;
//    g_AWEInstance.m_pModule_descriptor_table = g_module_descriptor_table;

    // This will be core ID 0.
    g_AWEInstance.m_coreID = CORE_ID;

    awe_fwInitTargetInfo(&g_AWEInstance,
                     CORE_ID,
                     CORE_SPEED,
                     SAMPLE_SPEED,
                     "Apollo3",
                     PROCESSOR_TYPE_CORTEXM4,
                     HAS_FLOAT_SUPPORT,
                     HAS_FLASH_FILESYSTEM,
                     NO_HW_INPUT_PINS,
                     NO_HW_OUTPUT_PINS,
                     IS_SMP,
                     NO_THREADS_SUPPORTED,
                     FIXED_SAMPLE_RATE,
                     INPUT_CHANNEL_COUNT,
                     OUTPUT_CHANNEL_COUNT,
                     VER_DAY, VER_MONTH, VER_YEAR
                     );

    g_AWEInstance.m_target_info.m_base_block_size = MAKE_BLOCK_SIZE_PACKED(AWE_FRAME_SIZE, 1);

    awe_fwInit_io_pins(&g_AWEInstance, 1);

    s_InputPin[0].sampleRate = FIXED_SAMPLE_RATE;
    s_InputPin[0].wireInfo1 = nInputWireInfo;
    s_InputPin[0].wireInfo3 |= CLOCK_MASTER_BIT;
    awe_SetPackedName(s_InputPin[0].m_pinName, "Input");

    s_OutputPin[0].sampleRate = FIXED_SAMPLE_RATE;
    s_OutputPin[0].wireInfo1 = nOutputWireInfo;
    awe_SetPackedName(s_OutputPin[0].m_pinName, "Output");

	// Allocate the heaps.
    g_AWEInstance.m_master_heap_size = MASTER_HEAP_SIZE;
    g_AWEInstance.m_slow_heap_size = SLOW_HEAP_SIZE;
    g_AWEInstance.m_fastb_heap_size = FASTB_HEAP_SIZE;

    g_AWEInstance.m_master_heap = g_master_heap;
    g_AWEInstance.m_slow_heap = g_slow_heap;
    g_AWEInstance.m_fastb_heap = g_fastb_heap;
}   // End AWEInstanceInit


//-----------------------------------------------------------------------------
// METHOD:  awe_pltInit
// PURPOSE: Initialize AWE
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
//AWE_FW_SLOW_CODE
//void awe_pltInit(void)
//{ 
//    // Setup processor clocks, signal routing, timers, etc.
//    CoreInit();
//    
//    // Initialize the target info    
//    AWEInstanceInit();
//    
//    // Setup board peripherals (CODECs, external memory, etc.)
//    BoardInit();
//    
//    // Setup audio DMA, interrupt priorities, etc.
////    AudioInit();
//    
//    // Setup communication channel for monitoring and control
//    UARTMsgInit();
//    #ifdef USE_FLASH_FILE_SYSTEM
//        // Initialize the Flash File System
//        awe_pltInitFlashFileSystem();
//    #endif
//}   // End awe_pltInit
///-----------------------------------------------------------------------------
/// @name  void awe_pltTick(void)
/// @brief Idle loop Platform Tick Processing
///-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPEED
AWE_FW_SLOW_CODE
void awe_pltTick(void)
{
    uint8_t bReplyReady;
    // Indicate that this idle loop call is getting CPU attention
    g_nPumpCount = 0;
//#if USE_AWE
    CheckForUARTPacketReady();
//#endif
    bReplyReady = awe_fwTuningTick(&g_AWEInstance);
    if (bReplyReady == REPLY_READY)
    {
        UART0SendReply();
        if (g_bReboot)
        {
            g_bReboot = FALSE;
            am_util_delay_ms(500);
            am_hal_sysctrl_aircr_reset();
        }
    }
    
    // Process any local controls 
 //   ProcessControlIO();
		
}	// End awe_pltTick


