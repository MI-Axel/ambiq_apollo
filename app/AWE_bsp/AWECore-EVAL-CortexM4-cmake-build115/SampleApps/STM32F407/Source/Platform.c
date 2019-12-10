/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     Platform.c
********************************************************************************
*
*     Description:  AWE Platform Interface for STM Discovery board
*
*     Copyright:    (c) 2018 DSP Concepts, Inc. All rights reserved.
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
*
*******************************************************************************/
#include "Platform.h"
#include "STM32F407_PassThru_with_ControlIO.h"

/** This awe instance */
AWEInstance g_AWEInstance;

/** Flash file system instance */
AWEFlashFSInstance g_AWEFlashFSInstance;

/** The only input pin for this core. */
static IOPinDescriptor s_InputPin = { 0 };

/** The only output pin for this core. */
static IOPinDescriptor s_OutputPin = { 0 };

volatile BOOL g_bPacketReceived = FALSE;
volatile BOOL g_bDeferredProcessingRequired = FALSE;

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
    __ALIGN_BEGIN UINT32 g_fastb_heap[FASTB_HEAP_SIZE] __ALIGN_END;
    __ALIGN_BEGIN UINT32 g_master_heap[MASTER_HEAP_SIZE] __ALIGN_END;
    __ALIGN_BEGIN UINT32 g_slow_heap[SLOW_HEAP_SIZE] __ALIGN_END;
#endif

static UINT32 nPrevCycles = 0;
static volatile UINT32 g_nElapsedMilliSeconds = 0;
extern __IO UINT32 uwTick;

/* ----------------------------------------------------------------------
** Module table
** ------------------------------------------------------------------- */

/* Array of pointers to module descriptors. This is initialized at compile time.
Each item is the address of a module descriptor that we need linked in. The
linker magic is such that only those modules referenced here will be in the
final program. */
const void *g_module_descriptor_table[] =
{
	// The suitably cast pointers to the module descriptors.
    (void *)LISTOFCLASSOBJECTS
};

AWE_MOD_SLOW_DM_DATA UINT32 g_module_descriptor_table_size = sizeof(g_module_descriptor_table) / sizeof(g_module_descriptor_table[0]);

/* Arbitrates GPIO pin usage for either flashing when messages are received
** or as a general purpose GPIO pin for the Audio Weaver module. */
volatile BOOL g_bBlinkLED4ForBoardAlive = TRUE;


//-----------------------------------------------------------------------------
// METHOD:  AWEInstanceInit
// PURPOSE: Initialize AWE Instance with target details
//-----------------------------------------------------------------------------
void AWEInstanceInit()
{
    memset(&g_AWEInstance, 0, sizeof(AWEInstance) );

    awe_initPin(&s_InputPin, INPUT_CHANNEL_COUNT, NULL);
    awe_initPin(&s_OutputPin, OUTPUT_CHANNEL_COUNT, NULL);

    g_AWEInstance.pInputPin = &s_InputPin;
    g_AWEInstance.pOutputPin = &s_OutputPin;

#if HAS_FLASH_FILESYSTEM

    // Setup the flash file system
    memset(&g_AWEFlashFSInstance, 0, sizeof(AWEFlashFSInstance) );

    g_AWEFlashFSInstance.cbInit = &usrInitFlashFileSystem;
    g_AWEFlashFSInstance.cbEraseSector = &usrEraseFlashMemorySector;
    g_AWEFlashFSInstance.cbFlashWrite = &usrWriteFlashMemory;
    g_AWEFlashFSInstance.cbFlashRead = &usrReadFlashMemory;

    g_AWEFlashFSInstance.flashSizeInBytes = FLASH_MEMORY_SIZE_IN_BYTES;
    g_AWEFlashFSInstance.flashErasableBlockSizeInBytes = ERASEABLE_BLOCKSIZE;
    g_AWEFlashFSInstance.flashStartOffsetInBytes = FILE_SYSTEM_START_OFFSET;
    g_AWEFlashFSInstance.flashEraseTimeInMs = 0;

    awe_initFlashFS(&g_AWEInstance, &g_AWEFlashFSInstance);

#endif

    // User version word
    g_AWEInstance.userVersion = USER_VER;

    // Initialize board properties
    g_AWEInstance.instanceId = INSTANCE_ID;
    g_AWEInstance.coreSpeed = CORE_SPEED;
    g_AWEInstance.profileSpeed = CORE_SPEED;
    g_AWEInstance.pName = "ST32F407";
    g_AWEInstance.numThreads = NUM_AUDIO_THREADS;
    g_AWEInstance.pModuleDescriptorTable = g_module_descriptor_table;
    g_AWEInstance.numModules = g_module_descriptor_table_size;
    g_AWEInstance.sampleRate = AUDIO_SAMPLE_RATE;
    g_AWEInstance.fundamentalBlockSize = AUDIO_BLOCK_SIZE;

    // Define the heap sizes
    g_AWEInstance.fastHeapASize = MASTER_HEAP_SIZE;
    g_AWEInstance.fastHeapBSize = FASTB_HEAP_SIZE;
    g_AWEInstance.slowHeapSize = SLOW_HEAP_SIZE;

    // Point to the heaps on this target
    g_AWEInstance.pFastHeapA = g_master_heap;
    g_AWEInstance.pFastHeapB = g_fastb_heap;
    g_AWEInstance.pSlowHeap = g_slow_heap;

    // Define storage for the tuning packet buffer
    g_AWEInstance.pPacketBuffer = g_packet_buffer;
    g_AWEInstance.packetBufferSize = MAX_COMMAND_BUFFER_LEN;

    g_AWEInstance.pReplyBuffer = g_packet_buffer;

    // Initialize the AWE instance
    awe_init(&g_AWEInstance);

}   // End AWEInstanceInit


//-----------------------------------------------------------------------------
// METHOD:  targetInit
// PURPOSE: Initialize AWE
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
void targetInit(void)
{
    // Setup processor clocks, signal routing, timers, etc.
    CoreInit();

    // Setup board peripherals (CODECs, external memory, etc.)
    BoardInit();

    // Initialize the target info
    AWEInstanceInit();

    // Setup audio DMA, interrupt priorities, etc.
    AudioInit();

}	// End targetInit


//-----------------------------------------------------------------------------
// METHOD:  HAL_IncTick
// PURPOSE: User callback for millisecond update
//-----------------------------------------------------------------------------
void HAL_IncTick(void)
{
    uwTick++;
    g_nElapsedMilliSeconds++;
}


//-----------------------------------------------------------------------------
// METHOD:  aweuser_getCycleCount
// PURPOSE: Returns the current value in the counter
//-----------------------------------------------------------------------------
UINT32 aweuser_getCycleCount(void)
{
	UINT32 nCycles, nCycles1, nCycles2, nElapsedCycles, nElapsedMilliSecs;

    // This value is 400,000
    UINT32 nReloadValue = SysTick->LOAD + 1;

    DISABLE_INTERRUPTS();

    // Current COUNTDOWN value (215,999  - 0)
    nCycles1 = SysTick->VAL;

    //nElapsedMilliSecs = HAL_GetTick();
    nElapsedMilliSecs = g_nElapsedMilliSeconds;

    // Current COUNTDOWN value (215,999  - 0)
	nCycles2 = SysTick->VAL;

    ENABLE_INTERRUPTS();

    if (nCycles2 <= nCycles1)
    {
        nCycles = nCycles2;
    }
    else
    {
        nElapsedMilliSecs++;
        nCycles = nCycles1;
    }

    nElapsedCycles = (nElapsedMilliSecs * nReloadValue) + (nReloadValue - nCycles);

    // Additional correction needed
    if (nPrevCycles > nElapsedCycles)
    {
        g_nElapsedMilliSeconds++;

        nElapsedCycles = (g_nElapsedMilliSeconds * nReloadValue) + (nReloadValue - nCycles);
    }

    nPrevCycles = nElapsedCycles;

	return nElapsedCycles;

}   // End aweuser_getCycleCount


//-----------------------------------------------------------------------------
// METHOD:  aweuser_getElapsedCycles
// PURPOSE: Returns the cycle count between start time and end time
//-----------------------------------------------------------------------------
UINT32 aweuser_getElapsedCycles(UINT32 nStartTime, UINT32 nEndTime)
{
    UINT32 nElapsedTime;

	if (nEndTime > nStartTime)
	{
		nElapsedTime = nEndTime - nStartTime;
	}
	else
	{
		// Wrap around occurred
        nStartTime = (UINT32)0xFFFFFFFF - nStartTime;
		nElapsedTime = nStartTime + nEndTime + 1;
    }

	return nElapsedTime;

}   // End aweuser_getElapsedCycles


#if (HAS_FLASH_FILESYSTEM == 1)


//-----------------------------------------------------------------------------
// METHOD:  usrInitFlashFileSystem
// PURPOSE: This method is here
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL usrInitFlashFileSystem(void)
{
    // Clear the flash register flags
    __HAL_FLASH_CLEAR_FLAG( (FLASH_FLAG_EOP | \
                             FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | \
                             FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR));

    return SUCCESS;

}   // End usrInitFlashFileSystem


//-----------------------------------------------------------------------------
// METHOD:  usrReadFlashMemory
// PURPOSE: Read from flash memory device
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL usrReadFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToRead)
{
    UINT32 n;
    UINT32 * pSrc = (UINT32 *)nFlashAddress;

	for (n = 0; n < nDWordsToRead; n++)
	{
		pBuffer[n] = pSrc[n];
	}

	return SUCCESS;

}	// End usrReadFlashMemory


//-----------------------------------------------------------------------------
// METHOD:  usrWriteFlashMemory
// PURPOSE: Write to flash memory device
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL usrWriteFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToWrite)
{
	UINT32 n = 0;

	// Flash address must be on a 4 byte boundary since writing DWords
	if ( (nFlashAddress & 0x00000003) != 0)
	{
		return FAILURE;
	}

    HAL_FLASH_Unlock();

    while (n < nDWordsToWrite)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, nFlashAddress, pBuffer[n]) == HAL_OK)
        {
            // Read back DWORD that was written
            DWORD nDWord;
            nDWord = *(PDWORD)nFlashAddress;
            if (nDWord != pBuffer[n])
            {
                return FAILURE;
            }

            nFlashAddress = nFlashAddress + 4;
            n++;
        }
        else
        {
            return FAILURE;
        }
    }

    HAL_FLASH_Lock();

	return SUCCESS;

}	// End usrWriteFlashMemory


//-----------------------------------------------------------------------------
// METHOD:  usrEraseFlashMemorySector
// PURPOSE: Erase Flash Memory used for Flash File System
//          The flash memory region assigned for the flash file system
//          starts with flash sector 8. These are actually 128K sectors.
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL usrEraseFlashMemorySector(UINT32 nStartingAddress, UINT32 nNumberOfSectors)
{
    FLASH_EraseInitTypeDef EraseInitStruct;
    UINT32 nSector_to_erase = 0;
    UINT32 SectorError = 0;

    if (nStartingAddress < ADDR_FLASH_SECTOR_7)
    {
        nSector_to_erase = FLASH_SECTOR_6;
    }

    else if (nStartingAddress < ADDR_FLASH_SECTOR_8)
    {
        nSector_to_erase = FLASH_SECTOR_7;
    }

    else if (nStartingAddress < ADDR_FLASH_SECTOR_9)
    {
        nSector_to_erase = FLASH_SECTOR_8;
    }

    else if (nStartingAddress < ADDR_FLASH_SECTOR_10)
    {
        nSector_to_erase = FLASH_SECTOR_9;
    }

    else if (nStartingAddress < ADDR_FLASH_SECTOR_11)
    {
        nSector_to_erase = FLASH_SECTOR_10;
    }

    else if (nStartingAddress < ((uint32_t)0x08100000))
    {
        nSector_to_erase = FLASH_SECTOR_11;
    }

    HAL_FLASH_Unlock();

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector = nSector_to_erase;
    EraseInitStruct.NbSectors = nNumberOfSectors;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, (uint32_t *)&SectorError) != HAL_OK)
    {
        return FAILURE;
    }

    __HAL_FLASH_DATA_CACHE_DISABLE();
    __HAL_FLASH_DATA_CACHE_RESET();
    __HAL_FLASH_DATA_CACHE_ENABLE();

    HAL_FLASH_Lock();

	return SUCCESS;

}	// End usrEraseFlashMemorySector


//-----------------------------------------------------------------------------
// METHOD:  AWEIdleLoop
// PURPOSE: AWE Idle loop processing
//-----------------------------------------------------------------------------
void AWEIdleLoop(void)
{
    BOOL bMoreProcessingRequired = FALSE;

    while(TRUE)
    {
        // Reset the pump count to show that the idle loop got serviced
        g_nPumpCount = 0;

        // If tuning packet was received over USB process it
        if (g_bPacketReceived)
        {
            g_bPacketReceived = FALSE;

            awe_packetProcess(&g_AWEInstance);
            
            USBSendReply(&g_AWEInstance);
        }

       // Deferred Processing
        if (awe_audioIsStarted(&g_AWEInstance) )
        {
            UINT32 classID;
            INT32 nButtonState, nLED1State;

            if (g_bDeferredProcessingRequired || bMoreProcessingRequired)
            {
                g_bDeferredProcessingRequired = FALSE;
                bMoreProcessingRequired = awe_deferredSetCall(&g_AWEInstance);
            }

            // Does the current AWE model have a SinkInt module with this control object ID?
            if (awe_ctrlGetModuleClass(&g_AWEInstance, AWE_SinkInt1_value_HANDLE, &classID) == OBJECT_FOUND)
            {
                // Check that module assigned this object ID is of module class SinkInt
                if (classID == AWE_SinkInt1_classID)
                {
                    // SinkInt module (value is an array)
                    awe_ctrlGetValue(&g_AWEInstance, AWE_SinkInt1_value_HANDLE, (void *)&nLED1State, 0, 1);

                    // Set the current state of LED1
                    awe_pltGPIOSetPin(1, nLED1State);
                }
            }

            // Does the current AWE model have a DCSourceInt module with this control object ID?
            if (awe_ctrlGetModuleClass(&g_AWEInstance, AWE_DC1_value_HANDLE, &classID) == OBJECT_FOUND)
            {
                // Check that module assigned this object ID is of module class DCSourceInt
                if (classID == AWE_DC1_classID)
                {
                     // Get the current state of the blue user button
                    awe_pltGPIOGetPin(1, (UINT32 *)&nButtonState);

                    // DCSourceInt module (value is a scalar)
                    awe_ctrlSetValue(&g_AWEInstance, AWE_DC1_value_HANDLE, (void *)&nButtonState, 0, 1);
                }
            }
        }

        if (g_bBlinkLED4ForBoardAlive)
        {
            static INT32 nLoopCount = 0;

            // Blink LED4 to show board is alive
            nLoopCount++;

            if (nLoopCount == 500000)
            {
                // Indicate board running by toggling LED4
                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

                nLoopCount = 0;
            }
        }

    }   // End while

}   // End AWEIdleLoop

#endif
