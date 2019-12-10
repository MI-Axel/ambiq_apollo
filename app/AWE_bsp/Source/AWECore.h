/*******************************************************************************
*
*				Audio Framework
*				---------------
*
********************************************************************************
*	  AWECore.h
********************************************************************************
*
*	  Description:	AudioWeaver Framework main header file
*
*	  Copyright:	(c) 2019 DSP Concepts, Inc. All rights reserved.
*					3235 Kifer Road
*					Santa Clara, CA 95054
*
*******************************************************************************/

/**
* @file 
* @brief The AWECore API Header File
*/

#ifndef _FRAMEWORK_H
//Do nothing if Framework.h was previously included.

#ifndef _AWECORE_H
#define _AWECORE_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "TargetProcessor.h" //Include the TargetProcessor header that includes another processor specific header file. 

#ifdef	__cplusplus
extern "C" {
#endif

#define WORDSOF(x) (sizeof(x) / sizeof(INT32)) 

#ifndef NUMOF
#define NUMOF(x) (sizeof(x) / sizeof(*x)) 
#endif

#define AWE_UNUSED_VARIABLE(x) ((void)(x))

/** @brief AWE IO Pin type.  */
/**@detailed The AWE typedef for input/output pins. A BSP author will allocate their input/output pins of this type. 
*/
typedef struct IOPinDescriptor
{
	/** Reserved member. */
	UINT32 _Reserved[82];
	
} IOPinDescriptor;

/**
@brief The DSPC Flash File System Instance
@detailed Optional -- SINGLE INSTANCE ONLY
*/
typedef struct AWEFlashFSInstance
{
    /** Size of flash memory - if non-zero, next two values must also be non-zero. */
	UINT32 flashSizeInBytes;

	/** Size of flash erase block. */
	UINT32 flashErasableBlockSizeInBytes;

	/** Offset into start of flash used for file system. */
	UINT32 flashStartOffsetInBytes;

    /** Flash erase time in milliseconds */
    UINT32 flashEraseTimeInMs;

    /** User function to initialize flash file system, */
    BOOL (*cbInit)(void);

    /** User function to erase one or more sectors. */
    BOOL (*cbEraseSector)(UINT32 nStartingAddress, UINT32 nNumberOfSectors);

    /** User function to write to flash. */
    BOOL (*cbFlashWrite)(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToWrite);

    /** User function to read from flash. */
    BOOL (*cbFlashRead)(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToRead);

    UINT32 _Reserved[62];

} AWEFlashFSInstance;

/** 
@ingroup AWEInstance
@brief The AWE instance. 
@detailed The AWE Instance struct must have its members/pointers assigned at init time. 
The AWEInstance is the most important structure, and it must be initialized properly. 
After assigning all of the required members, the BSP author will call the awe_init() function. 
All members are required to be assigned unless they are marked optional in the detailed description below..
*/
typedef struct AWEInstance
{
	/** The ID of this instance. Single instance systems should always be 0.
	The instanceID of the AWEInstance must match the instanceID of your desired AWE commands.
	For example, if your packet router is routing commands to this instance with an address of 16,
	the instance's instanceID must be 16. See Packet Routing pseudocode above*/
	UINT32 instanceId; 
	
	/*------------------HEAPS------------------*/
	/** Fast heap A. This is the main heap. AWE heaps are user allocated memory required by the AWE Instance.  */
	UINT32 *pFastHeapA; 

	/** The second fast heap, B . */
	UINT32 *pFastHeapB;

	/** The slow heap. */
	UINT32 *pSlowHeap;

	/** The fast heap A size. Heap sizes will vary from platform to platform, and also depend on the size of a layout.
		A good place to start for each heap is 1048576, however this will be too large for some platforms. 
	*/
	UINT32 fastHeapASize;

	/** The fast heap B size. */
	UINT32 fastHeapBSize;

	/** The slow heap size. */
	UINT32 slowHeapSize;

	/*------------------AUDIO CALLBACKS------------------*/
	
	/** OPTIONAL This callback is invoked when a layout is run or when a StartAudio command is sent.
	A user will define their own callback function and initialize this member with a pointer to their function.
	This callback can be used for whatever the BSP author pleases, including configuring audio devices based on layout properties, etc..
	*/
	INT32 (*cbAudioStart)(struct AWEInstance *PAWE); 

	/** OPTIONAL. This callback is invoked when a layout is stopped or a StopAudio command is sent
	A user will define their own callback function and init this member with a pointer to their function.
	This callback can also be used for whatever the BSP author pleases, including halting audio streams, freeing buffers, etc...
	*/
	INT32 (*cbAudioStop)(struct AWEInstance *pAWE);


	/*------------------IO PINS------------------*/
	
	/**A BSP author must define/allocate an input pin in their BSP and assign it to this member
	NOTE: AudioWeaver only supports single input/output pins, so the pin must have only ONE element 
	Example: static IOPinDescriptor s_InputPin[1];
	*/
	IOPinDescriptor *pInputPin;

	/**A BSP author must define/allocate an output pin in their BSP and assign it to this member
	NOTE: AudioWeaver only supports single input/output pins, so the pin must have only ONE element 
	Example: static IOPinDescriptor s_OutputPin[1];
	*/
	IOPinDescriptor *pOutputPin;
	
	/*------------------MODULES------------------*/

	/** Number of modules in module table. This can be manually set, 
	or it can be determined by getting the size of the module descriptor table.
	Example: 
			UINT32 module_descriptor_table_size = sizeof(g_module_descriptor_table) / sizeof(g_module_descriptor_table[0]); 
			AWEInstance1.numModules = module_descriptor_table_size;
	*/
	UINT32 numModules;

	/** Pointer to module table. The module table is the list of modules that will be included in the instance. 
	See the provided "ModuleList.h" header for syntax specifics. 
	Any set of available modules can be included/excluded from the instance by simply adding or removing them from the table. 
	Note: this is often used for reducing the memory usage in production. AudioWeaver Designer can generate a ModuleList.h from a layout
	that ONLY includes the modules used in that layout. 
	*/
	const void *pModuleDescriptorTable;
	
	/*------------------PACKET BUFFERS------------------*/

    /** The Packet buffer pointer. A BSP author must allocate a buffer of length packetBufferSize and set pPacketBuffer to the address of that buffer. 
	Example:
			g_AWEInstance.packetBufferSize = packetBufferSize; 
			UINT32 AWE_Packet_Buffer[g_AWEInstance.packetBufferSize];
			g_AWEInstance.pPacketBuffer = AWE_Packet_Buffer;
	*/
    UINT32 *pPacketBuffer;

	/** Reply buffer pointer. Initialized the same way as pPacketBuffer.
		The pPacketBuffer will be processed and the reply will be inserted into pReplyBuffer. 
	Example:
			g_AWEInstance.packetBufferSize = packetBufferSize; 
			UINT32 AWE_Reply_Buffer[g_AWEInstance.packetBufferSize];
			g_AWEInstance.pReplyBuffer = AWE_Reply_Buffer;		
	*/
	UINT32 *pReplyBuffer;

    /** Packet buffer size. Must be initialized to the size of the BSP's packet buffers. 
		The recommended packet buffer size is 264 words. If you need to use a smaller packetBufferSize
		due to memory constraints on your target, please contact DSPC Engineering. 
		(The absolute minimum packetBufferSize is 16 and absolute max is 4105) 
	*/
    UINT32 packetBufferSize;
	
    /** User Version word. A BSP author can initialize this to any UINT32 value they would like. 
	    Should mean something to the BSP author, but no required meaning/syntax.
	*/
    UINT32 userVersion;
	
	/** A BSP author will set this to the speed of the CPU they are integrating into. */
    float coreSpeed;

	/** Profiling clock speed in Hz. */
    float profileSpeed;

/*The name of the AWE Instance that will be displayed in Server. Can be any string of XYZ length?*/
#ifdef __ADSP21000__ 
    /** Name of this instance as an int*/
    const UINT32 *pName;
#else
    /** Name of this instance as a string  */
    const char *pName;
#endif

	/** Number of threads supported for multithreaded systems(1-4). */
    UINT32 numThreads;
	
	/** Default sample rate of this instance. */
    float sampleRate;

	/** Base frame size of this instance. In order for a layout to run on an instance, it must be a multiple of the fundamental blocksize
	*/
    UINT32 fundamentalBlockSize;

    /** DSPC Flash file system instance. OPTIONAL if no FFS. 
	If implementing the optional flash file system, then assign this pointer to your properly initialized flash file system instance
	*/
    AWEFlashFSInstance *pFlashFileSystem;

	/** Internal members. Reserved memory. */
	UINT32 _Reserved[48];

} AWEInstance;


/** Type of data for I/O. */
typedef enum _SampleType
{
	/** Data is 16 bit PCM. */
	Sample16bit,

	/** Data is 24 bit PCM aligned to the low bit in 32 bit buffers. */
	Sample24bit_low,

	/** Data is 24 bit PCM aligned to the high bit in 32 bit buffers. */
	Sample24bit_high,

	/** Data is 32 bit PCM . */
	Sample32bit
} SampleType;


/*------------------------------------------Initialization----------------------------------------------------*/
/**
 * @brief Initialize the instance. Call this once you have assigned all of the required 
	members/pointers of the AWE Instance, and after calling awe_InitPin on both input and output pins. 
	Calling awe_init before assigning all members of the instance structure or initializing the pins
	will result in crashes/erratic behavior. 
 * @param pAWE						instance to initialize
 * @return 							0 or error code
 */
INT32 awe_init(AWEInstance *pAWE);


/**
 * @brief Initialize an input or output pin. This function must be called for both the input and output pins.
 * Must be called BEFORE the awe_init API function.  
 * @param [in] pPin					the pin instance to initialize
 * @param [in] channels				number of channels
 * @param [in] name					optional pin name
 * @return							0 or error code
 */
INT32 awe_initPin(IOPinDescriptor *pPin, UINT32 channels, const char *name);

/**
 * @brief Initialize the file system.
 * @param pAWE						instance to initialize
 * @param pAWEFlashFSInstance       the file system instance
 */
void awe_initFlashFS(AWEInstance * pAWE, AWEFlashFSInstance * pAWEFlashFSInstance);


/*------------------------------------------Packet----------------------------------------------------*/
/**
 * @brief Process an AWEInstance's newly received tuning packet. 
 * @param [in] pAWE			The AWE instance pointer to process
 * @return error/success	0 for success, negative on error
 */
INT32 awe_packetProcess(AWEInstance * pAWE);


/*------------------------------------------Audio----------------------------------------------------*/

/**
 * @brief Audio pump function. Call this in your audio thread once you have imported the data you wish to process.
 *  Before pumping, you must also check that the AudioWeaver buffers have been filled (awe_getPumpMask) 
	and that audio has been started (awe_audioIsStarted). 
	This function will return 1 if awe_deferredSetCall needs to be called. This is for modules that need to do more time consuming
	calculations, like calculating filter coefficients. For example, a SOF Control module needs to calculate new coeffs when the frequency is modified by the control input.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] layoutIndex			the layout index to pump
 * @return							0 for success, negative for error, 1 for deferred set needed
 */
INT32 awe_audioPump(AWEInstance *pAWE, UINT32 layoutIndex);

/**
 * @brief Import samples from a user buffer to a channel.
	This will perform channel matching implicitly. For example, if you have a BSP
	with one HW input and 2 HW outputs, call awe_audioImportSamples once for input channel 0. 
	If you run a layout with 9 input channels, the other 8 channels of the layout will be automatically ignored. 
 * @param pAWE						AWE instance
 * @param inSamples					samples to read from
 * @param inStride					input buffer stride
 * @param channel					channel to write to
 * @param inType					type of input data
 * @return							0 on success, negative on error
 */
INT32 awe_audioImportSamples(const AWEInstance *pAWE, const void *inSamples, INT32 inStride, INT32 channel, SampleType inType);

/**
 * @brief Export samples to a user buffer from a channel. 
	Like awe_audioImportSamples, this will do channel matching implicitly. For example, if you have a BSP
	with 2 HW output channels, then call awe_audioExportSamples twice (once for channel 0 and once for channel 1).
	Now, if you have a layout with one output channel, the second output channel will automatically be zeroed. Inversely,
	if you have a layout with 9 output channels, the additional 7 channels will be ignored. 
 * @param pAWE						AWE instance
 * @param outSamples				samples to write to
 * @param outStride					output buffer stride
 * @param channel					channel to read from
 * @param outType					type of output data
 * @return							0 on success, negative on error
 */
INT32 awe_audioExportSamples(const AWEInstance *pAWE,  void *outSamples, INT32 outStride, INT32 channel, SampleType outType);

/**
 * @brief Check if this instance is running. 
   A BSP author can use this to determine if the instance is already running to avoid pumping audio through a dead layout.
 * @param pvAWE						instance pointer
 * @return							0 if not started, 1 if started
 */
INT32 awe_audioIsStarted(const AWEInstance *pAWE);

/**
 * @brief Test if AWE is ready to run. This will return the "layout mask" which is a bit vector of threads to run.
   For a simple, single threaded system, the bitvector will be 0x1. 
   Example:
		int layoutMask = awe_audioGetPumpMask&g_AWEInstance);
		if (layoutMask > 0) 
		{
			if (layoutMask & 0x1) 
			{
				int ret = awe_audioPump(&g_AWEInstance, 0);
			}
		}
 * @param pAWE						AWE instance
 * @return							bit vector of threads to run - 0 if none
 */
INT32 awe_audioGetPumpMask(const AWEInstance *pAWE);


/*------------------------------------------Deferred Functions----------------------------------------------------*/
/**
 * @brief Perform deferred awe set on a module. Each call to awe_deferredSetCall processes a single module.
	Usually this function would be called repeatedly until the return value is 0. 
 * @param [in] pAWE					AWE instance pointer
   @return finishedProcessing 		Will return 1 when processing is incomplete, 0 when complete. 
 */
INT32 awe_deferredSetCall(AWEInstance * pAWE);


/*------------------------------------------Loader Functions----------------------------------------------------*/
/**
* @brief Executes packet commands from an in-memory array. Designer can generate AWB arrays directly from a layout. 
* @param[in] pAWE 			AWE instance pointer
* @param[in] pCommands  	Buffer with commands to execute
* @param[in] arraySize 		Number of DWords in command buffer
* @param[out] pPos			Report failing word index
* @return 					0 or error code
*/
INT32 awe_loadAWBfromArray(AWEInstance *pAWE, const UINT32 *pCommands, UINT32 arraySize, UINT32 *pPos);


/*------------------------------------------Layout Functions----------------------------------------------------*/
/**
 * @brief Returns the number of channels in the Layout's input and output pins.
 * @param [in] pAWE					AWE instance pointer
 * @param [in] pinIdx				which input pin
 * @param [out] inCount				channels in primary input pin
 * @param [out] outCount			channels in primary output pin
 */
void awe_layoutGetChannelCount(const AWEInstance *pAWE, UINT32 pinIdx, UINT32 *inCount, UINT32 *outCount);

/**
 * @brief Returns the block size of a pin. Because the block size of the output pin is inherited from the input pin,
	the user only needs to check the input pin.
   @param [in] pAWE				    The AWE Instance
   @param [in] pinIdx				which input pin
   @param [out] blockSize			block size of input pin
   @return							0 or error code
 */
INT32 awe_layoutGetInputBlockSize(const AWEInstance *pAWE, UINT32 pinIdx, UINT32 *blockSize);

/**
 * @brief Returns the sample rate of an input pin. Because the sample rate of the output pin is inherited from the input pin,
   the user only needs to check the input pin.
   @param [in] pAWE				    The AWE Instance
 * @param [in] pinIdx				which input pin
 * @param [out] sampleRate			the input pin sample rate
 * @return							0 or error code
 */
INT32 awe_layoutGetInputSampleRate(const AWEInstance *pAWE, UINT32 pinIdx, FLOAT32 *sampleRate);

/**
 * @brief Determines if a layout is loaded and valid.
   @param [in] pAWE				    The AWE Instance
 * @return							0 if layout not valid/loaded, 1 if it is					
 */
INT32 awe_layoutIsValid(const AWEInstance *pAWE);


/*------------------------------------------Control Interface Functions----------------------------------------------------*/
/**
 * @brief Set a scalar or array value by handle
 * @param pAWE						instance pointer
 * @param handle					packed object handle
 * @param value						value(s) to set
 * @param arrayOffset				array index if array
 * @param length					number of elements if array
 * @return							error code
 */
INT32 awe_ctrlGetValue(const AWEInstance *pAWE, UINT32 handle, const void *value, INT32 arrayOffset, UINT32 length);

/**
 * @brief Get a scalar or array value by handle
 * @param pAWE						instance pointer
 * @param handle					packed object handle
 * @param value						value(s) got
 * @param arrayOffset				array index if array
 * @param length					number of elements if array
 * @return							error code
 */
INT32 awe_ctrlSetValue(const AWEInstance *pAWE, UINT32 handle, void *value, INT32 arrayOffset, UINT32 length);

/**
 * @brief Set the status of a module.
 * @param pAWE						instance pointer
 * @param handle					packed object handle
 * @param status					status to set
 * @return							error code
 */
INT32 awe_ctrlSetStatus(const AWEInstance *pAWE, UINT32 handle, UINT32 status);

/**
 * @brief Get the status of a module.
 * @param pAWE						instance pointer
 * @param handle					packed object handle
 * @param status					returned status
 * @return							error code
 */
INT32 awe_ctrlGetStatus(const AWEInstance *pAWE, UINT32 handle, UINT32 *status);

/**
 * @brief Set a scalar or array value by handle with mask. A mask allows you to only 
 * @param pAWE						instance pointer
 * @param handle					packed object handle
 * @param value						value(s) to set
 * @param arrayOffset				array index if array
 * @param length					number of elements if array
 * @param mask						mask to use - 0 do not call set function
 * @return							error code
 */
INT32 awe_ctrlSetValueMask(const AWEInstance *pAWE, UINT32 handle, const void *value, INT32 arrayOffset, UINT32 length, UINT32 mask);

/**
 * @brief Get a scalar or array value by handle with mask
 * @param pAWE						instance pointer
 * @param handle					packed object handle
 * @param value						value(s) got
 * @param arrayOffset				array index if array
 * @param length					number of elements if array
 * @param mask						mask to use - 0 do not call get function
 * @return							error code
 */
INT32 awe_ctrlGetValueMask(const AWEInstance *pAWE, UINT32 handle, void *value, INT32 arrayOffset, UINT32 length, UINT32 mask);

/**
 * @brief Get an object class from its handle.
 * @param pAWE						instance pointer
 * @param [in] handle				handle of object to find
 * @param [out] pClassID			pointer to receive found object class
 * @return							0 or error code
 */
INT32 awe_ctrlGetModuleClass(const AWEInstance *pAWE, UINT32 handle, UINT32 *pClassID);



#ifdef	__cplusplus
}
#endif

#endif	// _AWECORE_H

#endif // _FRAMEWORK_H
