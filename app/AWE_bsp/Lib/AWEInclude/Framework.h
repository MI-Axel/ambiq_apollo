/*******************************************************************************
*
*				Audio Framework
*				---------------
*
********************************************************************************
*	  Framework.h
********************************************************************************
*
*	  Description:	AudioWeaver Framework main header file
*
*	  Copyright:	DSP Concepts, Inc., 2007 - 2016
*					1800 Wyatt Drive, Suite 14
*					Sunnyvale, CA 95054
*
*******************************************************************************/


#ifndef _FRAMEWORK_H
#define _FRAMEWORK_H

#if (defined(WIN32) || defined(LINUX))
#define IPC_USES_ASRC
#endif

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#if !defined(__ADSP21000__) && !defined(XTENSA)
#include "dspc_asrc.h"
#endif

#if defined(IA610)
#include "DeltaPlatform.h"
#include "hemilite_fr32_ops.h"
#include "hemilite_fr32_math.h"
#endif

#include "TargetProcessor.h"

#ifdef	__cplusplus
extern "C" {
#endif

#if defined(_MSC_VER) && defined(USEFRAMEWORKDLL)
#	define DLLSYMBOL			__declspec(dllimport)
#	define CXX_NOWARN_DLLCLASSIF		__pragma(warning(push))\
		__pragma(warning(disable: 4251))
#	define CXX_RESTORE_DLLCLASSIF		__pragma(warning(pop))
#else
#	define DLLSYMBOL
#define CXX_NOWARN_DLLCLASSIF
#define CXX_RESTORE_DLLCLASSIF
#endif

/** Number of samples in a DMA buffer - bound wires must be an integer multiple of this. */
#ifndef DMA_NUM_SAMPLES
#define DMA_NUM_SAMPLES 32
#endif

#define MPS_25MHZ_COUNT (*((volatile unsigned long *)(0x40004014)))

/* --------- Class identifiers. */
#define CLASS_ID_BASE							0xBEEF0000
#define CLASS_ID_END							0xBEEFFFFF
#define CLASS_ID_MASK							0xFFFF0000

#define CLASS_ID_INPUTPIN						(CLASS_ID_BASE + 1)
#define CLASS_ID_OUTPUTPIN						(CLASS_ID_BASE + 2)
#define CLASS_ID_PIN							(CLASS_ID_BASE + 3)
#define CLASS_ID_LAYOUT							(CLASS_ID_BASE + 4)

#define CLASS_ID_PINBASE						CLASS_ID_INPUTPIN
#define CLASS_ID_PINEND							CLASS_ID_PIN

/*	Class IDs for wires */
#define CLASS_ID_WIREBASE						(CLASS_ID_BASE + 0x80)
#define CLASS_ID_WIREEND						(CLASS_ID_BASE + 0x7FF)

#define CLASS_ID_WIRE							(CLASS_ID_WIREBASE + 0)

/* Class IDs for modules */
#define CLASS_ID_MODBASE						(CLASS_ID_BASE + 0x800)
#define CLASS_ID_MODEND							(CLASS_ID_END)


/* Instance name IDs */
#define NAME_BASE								0x7EEDB000

#define NAME_INPUT_INTERLEAVED					(NAME_BASE + 1)
#define NAME_OUTPUT_INTERLEAVED					(NAME_BASE + 2)


/** Test if a given class is valid. */
#define IsClassValid(classID) \
		(((classID) >= CLASS_ID_BASE) && ((classID) <= CLASS_ID_END))

/** Test if a given class ID is that of a wire. */
#define IsClassWire(classID) \
	(((classID) >= CLASS_ID_WIREBASE) && ((classID) <= CLASS_ID_WIREEND))

/** Test if a given class ID is that of module. */
#define IsClassModule(classID) \
	(((classID) >= CLASS_ID_MODBASE) && ((classID) <= CLASS_ID_MODEND))

/** Test if a given class ID is that of a layout. */
#define IsClassLayout(classID) \
	((classID) == CLASS_ID_LAYOUT)

#if 0
	// The concept of pin class has gone away.
/** Test if a given class ID is that of PIN type. */
#define IsClassPin(classID) \
	(((classID) >= CLASS_ID_PINBASE) && ((classID) <= CLASS_ID_PINEND))
#endif

#define WORDSOF(x)					(sizeof(x) / sizeof(INT32))

#ifndef NUMOF
#define NUMOF(x)					(sizeof(x) / sizeof(*x))
#endif

/* Handle packed wire counts. */

/** Get input pin (wire) count from nIO. */
#define GetInputPinCount(x)			((x) & 0xff)

/** Get output pin (wire) count from nIO. */
#define GetOutputPinCount(x)		(((x) >> 8) & 0xff)

/** Get scratch pin (wire) count from nIO. */
#define GetScratchPinCount(x)		(((x) >> 16) & 0xff)

#if 0		// Never used
/** Get feedback pin (wire) count from nIO. */
#define GetFeedbackPinCount(x)		(((x) >> 24) & 0xff)
#endif

/** Get total pin (wire) count from nIO. */
#define GetWireCount(x)				( (((x) >> 24) & 0xff) + (((x) >> 16) & 0xff) + (((x) >> 8) & 0xff) + ((x) & 0xff))

#if 0		// Never used
#define MakeIOSize(nInputs, nOutputs, blockSize) \
	(((blockSize) << 16) | ((nOutputs) << 8) | (nInputs))
#endif

/*------------------ Heap declarations ------------------*/

/* For the PC, all heaps are the same. No point doing anything else really. */
/** Items accessed from the inner loop, such as Wire Buffers. */
#define AWE_HEAP_FAST		1

/** Infrequently used items which could be placed in external memory. */
#define AWE_HEAP_SLOW		2

/** Another fast heap which is distinct from AWE_HEAP_FAST. This is used to separate
state and coefficients, as in FIR filters. */
#define AWE_HEAP_FASTB		3

/** Fast Heap -> FastB Heap -> Slow Heap */
#define AWE_HEAP_FAST2SLOW ((AWE_HEAP_FAST) | ((AWE_HEAP_FASTB) << (4)) | ((AWE_HEAP_SLOW) << (8)))

/** Fast Heap -> FastB Heap */
#define AWE_HEAP_FAST2FASTB ((AWE_HEAP_FAST) | ((AWE_HEAP_FASTB) << (4)))

/** Fast B Heap -> Fast Heap */
#define AWE_HEAP_FASTB2FAST ((AWE_HEAP_FASTB) | ((AWE_HEAP_FAST) << (4)))

/** This performs the allocation in the fast B heap, and if this fails, in the slow heap */
#define AWE_HEAP_FASTB2SLOW ((AWE_HEAP_FASTB) | ((AWE_HEAP_SLOW) << (4)))

/** Return the number of heaps. Constant at compile time. */
UINT32 awe_fwGetHeapCount(void);


/*------------------ Union declarations ------------------*/
typedef union _Sample
{
	INT32 iVal;
	UINT32 uiVal;
	float fVal;
}
Sample;

/** Defines for processor type. */
#define PROCESSOR_TYPE_NATIVE		1
#define PROCESSOR_TYPE_SHARC		2  // SHARC 214xx
#define PROCESSOR_TYPE_BLACKFIN		3
#define PROCESSOR_TYPE_CORTEXM4		4
#define PROCESSOR_TYPE_OMAP			5
#define PROCESSOR_TYPE_DSK6713		6
#define PROCESSOR_TYPE_HIFI2DSP		7   // Generic HiFi 2
#define PROCESSOR_TYPE_CORTEXM3		8
#define PROCESSOR_TYPE_IMX25		9
#define PROCESSOR_TYPE_CORTEXM7		10
#define PROCESSOR_TYPE_C674x		11
#define PROCESSOR_TYPE_CortexA5		12
#define PROCESSOR_TYPE_CortexA7		13
#define PROCESSOR_TYPE_CortexA8		14
#define PROCESSOR_TYPE_CortexA9		15
#define PROCESSOR_TYPE_CortexA12	16
#define PROCESSOR_TYPE_CortexA15	17
#define PROCESSOR_TYPE_CortexA53	18
#define PROCESSOR_TYPE_CortexA57	19
#define PROCESSOR_TYPE_ARM9			20
#define PROCESSOR_TYPE_ARM11		21
#define PROCESSOR_TYPE_HEXAGON		22
#define PROCESSOR_TYPE_HIFI3DSP	    23	// Generic HiFi 3
#define PROCESSOR_TYPE_S1000        24  // Intel S1000 for Sue Creek
#define PROCESSOR_TYPE_HEMILITE     25  // Knowles processor in IA-610
#define PROCESSOR_TYPE_CORTEXA72    26
#define PROCESSOR_TYPE_CORTEXA35    27
#define PROCESSOR_TYPE_C66xx        28
#define PROCESSOR_TYPE_SHARC215XX   29  // SHARC 215xx family
#define PROCESSOR_TYPE_HIFI4DSP	    30	// Generic HiFi 4
    
/** Target has no file system. */
#define FILESYSTEM_TYPE_NONE			0

/** Target has compiled in file system. */
#define FILESYSTEM_TYPE_COMPILED_IN		1

/** Target has flash file system (default). */
#define FILESYSTEM_TYPE_FLASH			2

/** Target has FAT file system */
#define FILESYSTEM_TYPE_FAT			    3

/** Create the target version - for V5 must have first argument of 5. */
#define MAKE_TARGET_VERSION(v1, v2, v3, v4) \
	( (((v1) & 0xff) << 24) | (((v2) & 0xff) << 16) | (((v3) & 0xff) << 8) | ((v4) & 0xff) )

/** Create a word containing packed characters. */
#define MAKE_PACKED_STRING(c1, c2, c3, c4) \
	( (((c4) & 0xff) << 24) | (((c3) & 0xff) << 16) | (((c2) & 0xff) << 8) | ((c1) & 0xff) )


/** This structure defines the target info. */
typedef struct _TargetInfo
{
	/** Target sample rate. */
	float m_sampleRate;				/* 0 */

	/** Target profile clock speed in Hz. */
	float m_profileClockSpeed;		/* 4 */

	/** Base block size of target (usually 32). */
	UINT32 m_base_block_size;			/* 8 */

	/** Packed field. */
	UINT32 m_packedData;				/* 12 */

	/** Target version - high byte is base framework version and must match. */
	UINT32 m_version;					/* 16 */

	/** Packed field for buffer size, s, input pin count, output pin count. */
	UINT32 m_proxy_buffer_size;			/* 20 */

	/** Target name up to 16 characters. */
	UINT32 m_packedName[2];				/* 24 */

	/** Clock speed of this core. */
	float m_coreClockSpeed;			/* 32 */

	/** ID of this core. */
	UINT32 m_coreID;					/* 36 */

	/** Feature bts. */
	UINT32 m_features;					/* 40 */

	/** Pointer to self. */
	struct _AWEInstance *m_pSelf;		/* 44 */

	/** Pointer to next core, default NULL. */
	struct _TargetInfo *m_pNextCore;	/* 48 */
}
TargetInfo;

/** Set the m_proxy_buffer_size target info member. */
#define PACKED_BUFFER_SIZE(bufferSize, cores, nInputPins, nOutputPins, smpCore) \
	(((bufferSize - 1) & 0x1fff) | (((cores - 1) & 0x3f) << 13) | (((nInputPins - 1) & 0x3f) << 20) | (((nOutputPins - 1) & 0x3f) << 26) | (((smpCore) & 1) << 19))

/** Get the packet buffer size from m_proxy_buffer_size. */
#define GET_TARGET_PACKET_BUFFER_LEN(x) (((x).m_proxy_buffer_size & 0x1fff) + 1)

/** Get the core count from m_proxy_buffer_size. */
#define GET_TARGET_CORES(x)				((((x).m_proxy_buffer_size >> 13) & 0x3f) + 1)

#define SMP_CORE_BIT	0x80000
/** Test if the core is static. */
#define IS_SMP_CORE(x)					(((x).m_proxy_buffer_size & SMP_CORE_BIT) != 0)

/** Get the number of input pins from m_proxy_buffer_size. */
#define GET_TARGET_NINPUT_PINS(x)		((((x).m_proxy_buffer_size >> 20) & 0x3f) + 1)

/** Get the number of output pins from m_proxy_buffer_size. */
#define GET_TARGET_NOUTPUT_PINS(x)		((((x).m_proxy_buffer_size >> 26) & 0x3f) + 1)

/** Get the base block size of the target. */
#define GET_TARGET_BASE_BLOCK_SIZE(x)	((x).m_base_block_size & 0xfff)

/** Get the number of threads on the target. */
#define GET_TARGET_THREADS(x)			(((x).m_base_block_size >> 12) & 0xf)

/** Get the clock domain of the core - 0 is main domain. */
#define GET_CLOCK_DOMAIN(x)				(((x).m_base_block_size >> 16) & 0xf)

#define MAKE_BLOCK_SIZE_PACKED(block_size, nThreads) \
	((block_size) & 0xfff) | (((nThreads) & 0xf) << 12)

/** Create target info m_packedData. */
#define MAKE_TARGET_INFO_PACKED(sizeof_int, num_inputs, num_outputs, is_floating_point, is_flash_supported, processor_type) \
	( ((sizeof_int) & 0xf) | (((is_flash_supported) & 1) << 4) | (((is_floating_point) & 1) << 5) \
	| (((num_inputs) & 0xff) << 8) | (((num_outputs) & 0xff) << 16) | (((processor_type) & 0x7f) << 24) )

/** Access sizeof(int) from target info m_packedData. */
#define TARGET_INFO_SIZOF_INT(targetinfo) \
	((targetinfo).m_packedData & 0xf)

/** Access flash supported from target info m_packedData. */
#define TARGET_INFO_IS_FLASH_SUPPORTED(targetinfo) \
	(((targetinfo).m_packedData & 0x10) != 0)

/** Access is floating point from target info m_packedData. */
#define TARGET_INFO_IS_FLOATING_POINT(targetinfo) \
	(((targetinfo).m_packedData & 0x20) != 0)

/** Bit if target uses paddin. */
#define TARGET_USES_PADDING		0x40

/** Report if heap uses padding. */
#define TARGET_INFO_USES_PADDING(targetinfo) \
	(((targetinfo).m_packedData & TARGET_USES_PADDING) != 0)

/** Access num inputs from target info m_packedData. */
#define TARGET_INFO_NUM_INPUTS(targetinfo) \
	(((targetinfo).m_packedData >> 8) & 0xff)

/** Access num outputs from target info m_packedData. */
#define TARGET_INFO_NUM_OUTPUTS(targetinfo) \
	(((targetinfo).m_packedData >> 16) & 0xff)

/** Access processor type from target info m_packedData. */
#define TARGET_INFO_PROCESSOR_TYPE(targetinfo) \
	(((targetinfo).m_packedData >> 24) & 0x7f)


/** States for ModuleFileStreaming. */
enum FileIOStatus
{
	/* ModuleFileStreaming always writes this (zero) to handshake. */
	FIOS_Null,

	/* These states are in the high byte of buffer[buffer_size]. */
	FIOS_NewStream,
	FIOS_NextBlock,
	FIOS_LastBlock,

	/* These states are reported asynchronously in asyncStatus. */
	FIOS_Stopped,
	FIOS_Paused,
	FIOS_Error,

	/* Used internally by the file streaming module to keep track of the current state */
	FIOS_Playing,
	FIOS_PlayingLast
};

/** This structure defines the file system info. */
typedef struct _FileSystemInfo
{
	UINT32 m_FileSystemType;				/* 0 */
	UINT32 m_FlashDeviceDWords;				/* 4 */
	UINT32 m_FileSystemDWords;				/* 8 */
	UINT32 m_DataStructOverheadDWords;		/* 12 */
	UINT32 m_DeletedOrCorruptedDWords;		/* 16 */
	UINT32 m_DWordsInUse;					/* 20 */
	UINT32 m_DWordsAvailable;				/* 24 */
	UINT32 m_BlkSize_MaxFilename_Len;		/* 28 */
}
FileSystemInfo;		/* size=32 (8 words) */

/** The one and only file system info object. */
extern FileSystemInfo g_filesystem_info;

/* Forward reference. */
struct _AWEInstance;

/*------------------ Instance declarations ------------------*/

/** A class descriptor. Common to all classes. */
typedef struct _ClassDescriptor
{
	/** All constructors look the same. To make debugging easy, we pass a generic
	array of words to the constructor, which needs to figure out what to do with
	them.

	On return, we have a pointer to an initialized instance ready for use.
	*/
	struct _InstanceDescriptor *(*Constructor)(struct _AWEInstance *pAWE, INT32 *retVal, INT32 srate, UINT32 info1, UINT32 info2, UINT32 info3);

	/** Unique ID of the class - set at compile time. */
	UINT32 classID;
}
ClassDescriptor;

/** The table of classes known to the framework. */
extern const ClassDescriptor *g_class_descriptor_table[2];


/** An instance descriptor. Common to all instances. */
typedef struct _InstanceDescriptor
{
	/** Chain instances together in a linked list. */
	struct _InstanceDescriptor *pNextInstance;		/* 0 */

	/** Pointer back to the static descriptor from which this instance was
	created. */
	const ClassDescriptor *pClassDescriptor;		/* 4 */

	/** The unique instance ID of this instance. */
	UINT32 nUniqueInstanceID;						/* 8 */
}
InstanceDescriptor;		/* 12 bytes */

/** Description of bound wires. */
typedef struct _CoreWireDescr
{
	/** The core this wire is on. */
	UINT32 coreID;

	/** The wire on the core - pointer in that core's address space. */
	struct _WireInstance *pWire;
} CoreWireDescr;

/** An I/O pin instance. These objects are defined at compile
time to match the physical I/O. */
typedef struct _IOPinDescriptor
{
	/** The basic instance data. */
	InstanceDescriptor instanceDescriptor;

	/** Pointer to the buffer allocated by the wire - copied from the wire at bind time. */
	Sample *pOrigBuffer;

	/** Pointer to the double buffer allocated at bind time. */
	Sample *pSecondBuffer;

	/** Pin sample rate. */
	float sampleRate;

	// Number of channels		10 bits
	// Max block size			17 bits
	// Sample size in bytes.	4 bits
	// isComplex				1 bit
	UINT32 wireInfo1;

	// Block size				17 bits
	// Data Type				6 bits
	UINT32 wireInfo2;

	// Rows						10 bits
	// Columns					10 bits
	// IsIPC					1 bit
	// IsPrivate				1 bit
	// Clock master				1 bit
	// Special input pin		1 bit
	UINT32 wireInfo3;

	/** Flags to control buffer flipping. */
	UINT32 ctrlFlags;

	/** Number of bound wires. */
	UINT32 nBoundWires;

	/** Array of bound wires. */
	CoreWireDescr boundWires[16];

	/** Default NULL - no owner. */
	struct _IpcObject *m_pIpcOwner;

	/** Optional named pin. */
	UINT32 m_pinName[2];
}
IOPinDescriptor;

/** Create info1 word. */
#define INFO1_PROPS(channels, maxBlockSize, complex, nSizeBytes) \
	((channels & 0x3ff) | ((maxBlockSize & 0x1ffff) << 10) | ((complex & 0x1) << 27) | ((nSizeBytes & 0xf) << 28))

/** Create info2 word. */
#define INFO2_PROPS(blockSize, dataType) \
	((blockSize & 0x1ffff) | ((dataType & 0x3f) << 17))

/** Create info3 word. */
#define INFO3_PROPS(rows, cols) \
	((((cols) & 0x3ff) << 10) | ((rows) & 0x3ff))

/** The IPC bit in info3. */
#define IS_IPC_BIT			(1 << 20)

/** The private pin bit in info3. */
#define IS_PRIVATE_BIT		(1 << 21)

/** The clock master bit. */
#define CLOCK_MASTER_BIT	(1 << 22)

/** Set on pins that are special inputs. */
#define SPECIAL_INPUT_BIT	(1 << 23)

/** Test if pin is the clock master. */
#define INFO3_IS_CLOCK_MASTER(info3) \
	(CLOCK_MASTER_BIT & (info3)) != 0

/** Test if a pin's size is compatible with an I/O pin's size. */
#define IsCompatiblePinSize(wireBlock, pinBlock) \
	(wireBlock % pinBlock == 0)


/*------------------ Declarations of I/O ------------------*/

/** The input pins - default 1. */
extern DLLSYMBOL IOPinDescriptor InterleavedInputPin[];

/** The output pins - default 1. */
extern DLLSYMBOL IOPinDescriptor InterleavedOutputPin[];


/*------------------ Wire declarations ------------------*/
typedef struct _WireInstance
{
	/** The basic instance data. */
	InstanceDescriptor instanceDescriptor;

	/** The wire buffer. */
	Sample *buffer;

	/** Wire sample rate. */
	float sampleRate;

	// Number of channels		10 bits
	// Max block size			17 bits
	// Sample size in bytes.	4 bits
	// isComplex				1 bit
	UINT32 wireInfo1;

	// Block size				17 bits
	// Data Type				6 bits
	UINT32 wireInfo2;

	// Rows						10 bits
	// Cols						10 bits
	// IsIPC					1 bit
	UINT32 wireInfo3;

	/** Bind chain pointer default NULL. */
	struct _WireInstance *m_pNextBind;

	/** What its bound to default NULL. */
	IOPinDescriptor *m_pBoundPin;

#ifndef USE_TEST_PADDING
#if defined(BUILD64) || defined(AWE_STORAGE_ALIGN4)
	UINT32 padding2;
#endif
	UINT32 padding;
#endif
}
WireInstance;

/** Get the channels from info1. */
#define WireInfo1_GetChannels(x)		((x) & 0x3ff)				// 10 bits 0-1023

/** Get the max block size from info1. */
#define WireInfo1_GetMaxBlockSize(x)	(((x) >> 10) & 0x1ffff)		// 17 bits 0-131071

/** Get is complex from info1. */
#define WireInfo1_IsComplex(x)			(((x) >> 27) & 0x1)			// 1 bit, 1 if true

/** Get sample width from info1. */
#define WireInfo1_SampleWidthBytes(x)	(((x) >> 28) & 0xf)			// 4 bits 0-15

/** Get the block size for info2. */
#define WireInfo2_GetBlockSize(x)		((x) & 0x1ffff)				// 17 bits, 0-131071

/** Get the data type from info2. */
#define WireInfo2_GetDataType(x)		(((x) >> 17) & 0x3f)		// 6 bits, 0-63

/** Get the rows from info3. */
#define WireInfo3_GetRows(x)			((x) & 0x3ff)				// 10 bits, 0-1023

/** Get the columns from info3. */
#define WireInfo3_GetCols(x)			(((x) >> 10) & 0x3ff)		// 10 bits, 0-1023

/** Get the IPC status from info3. */
#define WireInfo3_IsIPC(x)				(((x) >> 20) & 0x1)			// 1 bit

/** Get the block size of a wire. */
#define ClassWire_GetBlockSize(W)		(WireInfo2_GetBlockSize((W)->wireInfo2))

/** Get the channel count of a wire. */
#define ClassWire_GetChannelCount(W)	(WireInfo1_GetChannels((W)->wireInfo1))

/** Get the number of samples in a wire. */
#define ClassWire_GetNumSamples(W)		(ClassWire_GetBlockSize(W) * ClassWire_GetChannelCount(W))

/** Get the sample rate of a wire. */
#ifdef IA610
#define ClassWire_GetSampleRate(W)		(float_to_afloat((W)->sampleRate) )	// FLOAT32
#else
#define ClassWire_GetSampleRate(W)		((W)->sampleRate)	// float
#endif

/** Get if the wire is complex. */
#define ClassWire_GetComplex(W)			(WireInfo1_IsComplex((W)->wireInfo1))

/** Get the wire sample width in bytes. */
#define ClassWire_GetNSampleSize(W)		(WireInfo1_SampleWidthBytes((W)->wireInfo1))

/** Get the wire number of rows. */
#define ClassWire_GetNumMatRows(W)		(WireInfo3_GetRows((W)->wireInfo3))

/** Get the wire number of columns. */
#define ClassWire_GetNumMatCols(W)		(WireInfo3_GetCols((W)->wireInfo3))


/*------------------ Module declarations ------------------*/

typedef struct _ModClassDescriptor
{
	/** All constructors look the same. To make debugging easy, we pass a generic
	array of words to the constructor, which needs to figure out what to do with
	them.

	On return, we have a pointer to an initialized instance ready for use.
	*/
	struct _ModInstanceDescriptor *(*Constructor)(
			INT32 * FW_RESTRICT retVal,
			UINT32 nIO,
			WireInstance **pWires,
			size_t argCount,
			const Sample * FW_RESTRICT args);		/* 0 */

	/** Unique ID of the class - set at compile time. */
	UINT32 classID;									/* 4 */
}
ModClassDescriptor;		/* 8 bytes */


/** Class descriptor for audio modules. */
typedef struct _ModClassModule
{
	/** The basic class data. */
	ModClassDescriptor modClassDescriptor;				/* 0 */

	/** Pump function for the module. */
	void (*pProcessFunc)(void *pInstance);				/* 8 */

	/** Bypass function for the module. */
	void (*pBypassFunc)(void *pInstance);				/* 12 */

	/** Set function. */
	UINT32 (*pSet)(void *pInstance, UINT32 mask);		/* 16 */

	/** Get function. */
	UINT32 (*pGet)(void *pInstance, UINT32 mask);		/* 20 */

	void (*pSetState)(void *pInstance, UINT32 state);	/* 24 */

	/** The number of construction module parameters. */
	UINT32 nPackedParameters;							/* 28 */

	/** Vector of 64 bits specifying the type of constructor
	arguments. Bit 0 starts at the first member past the
	instance object. Bit set means argument is float.
	Bits past the last argument are don't care, should be 0. */
	UINT32 bitVectorFloat[2];							/* 32 */
}
ModClassModule;		/* 40 bytes */

#ifdef BUILD64

/** Table of offsets for modules. */
extern const UINT32 g_module_offsets[];

/** Table of offsets for module instances. */
extern const UINT32 g_module_instance_offsets[];

/** Table of offsets for wires. */
extern const UINT32 g_wire_offsets[];

/** Dummy for computing 64 bit offsets without having the actual module class available. */
typedef struct _ModClassModule2
{
	ModClassModule module;
	UINT32 m_offset[1];
} ModClassModule2;
#endif

/** Set the packed argument count nPackedParameters. */
#define ClassModule_PackArgCounts(nPublicArgs, nPrivateArgs) \
	(((nPrivateArgs) << 16) | ((nPublicArgs) & 0xffff))

/** Get the number of public arguments from nPackedParameters. */
#define ClassMod_GetNPublicArgs(packed) \
	((packed) & 0xffff)

/** Get the number of private arguments from nPackedParameters. */
#define ClassMod_GetNPrivateArgs(packed) \
	(((packed) >> 16) & 0xffff)


/* This macro declares a module class. For 64 bits we have an extra member
 * which is a vector of member offsets to translate indexes to struct offsets. */

#define PASTE(x, y)		x ## y
#define EVAL(x, y)		PASTE(x, y)

#ifdef BUILD64
/* 64 bit version has an array of member offsets following. */
#define CREATE_MODULE_CLASS(class_name, nMembers)	\
	typedef struct EVAL(_, class_name) \
	{ \
		ModClassModule modBaseClassDescriptor; \
		UINT32 m_offset[(nMembers <= 0)? 1: nMembers]; \
	} class_name;

#else
/* 32 bit version is just an alias for the module class. */
#define CREATE_MODULE_CLASS(class_name, nMembers)	\
	typedef struct EVAL(_, class_name) \
	{ \
		ModClassModule modBaseClassDescriptor; \
	} class_name;

#endif


/** A module instance descriptor. Common to all module instances. */
typedef struct _ModInstanceDescriptor
{
	/** Chain instances together in a linked list. */
	struct _ModInstanceDescriptor *pNextInstance;		/* 0 */

	/** Pointer back to the static descriptor from which this instance was
	created. */
	const ModClassModule *pModClassDescriptor;			/* 4 */

	/** The unique instance ID of this instance. */
	UINT32 nUniqueInstanceID;							/* 8 */
}
ModInstanceDescriptor;		/* 12 bytes */


/** The table of module descriptions. Truly global. */
extern const ModClassModule *g_module_descriptor_table[];

/** The number of elements in g_module_descriptor_table. Truly global. */
extern UINT32 g_module_descriptor_table_size;


/* Low order 2 bits of flags high byte are the module active state. */

/** Mask for active bits. */
#define MODULE_ACTIVE_MASK			0x03000000

/** Module is active. */
#define MODULE_ACTIVE				0x00000000

/** Module is bypassed. */
#define MODULE_BYPASS				0x01000000

/** Module is muted. */
#define MODULE_MUTE					0x02000000

/** Module is inactive. */
#define MODULE_INACTIVE				0x03000000


/** This bit allows for deferred execution of the module's set function in the main thread. */
#define MODULE_GENERAL_DEFERRED_SET			0x08000000

/** Test if the deferred bit is set. */
#define awe_modIsDeferredSet(S)				((((S)->instance.packedFlags) & (MODULE_GENERAL_DEFERRED_SET)) != (0))

/** Set the deferred bit to v */
#define awe_modSetDeferredSet(S, v)			(S)->instance.packedFlags &= ~MODULE_GENERAL_DEFERRED_SET; (S)->instance.packedFlags |= ((v & 1) << 27)


/** High 4 bits of flags high byte are available for any use. */
#define MODULE_GENERAL_MASK			0xf0000000

/** Get the general flag bits. */
#define GetGeneralFlagBits(S)		((((S)->instance.packedFlags) >> (28)) & (0x1f))

/** Set the genera; flag bits to v. */
#define SetGeneralFlagBits(S, v)	(S)->instance.packedFlags &= ~MODULE_GENERAL_MASK; (S)->instance.packedFlags |= ((v & 0xf) << 28)


/** A module instance. The instance is variable length on the heap, the size
being determinind by the constructor arguments. */
typedef struct _ModuleInstanceDescriptor
{
	/** The basic instance data. */
	ModInstanceDescriptor instanceDescriptor;			/* 0 */

	/** Pointer to owning layout instance (type is a forward reference). */
	struct _LayoutInstance *pOwner;						/* 12 */

	/** Array of input and output wires. There are nInwires + nOutWires + nScratchWires elements. */
	WireInstance **pWires;								/* 16 */

	/** Pump function for the module. May be empty, pProcessFunc, or, pBypassFunc. */
	void (*pProcessFunc)(void *pInstance);				/* 20 */

	/** Control flags. */
	UINT32 packedFlags;									/* 24 */

	/** Module specific profiling time.	 This is number of cycles times 256. */
	UINT32 profileTime;									/* 28 */
}
ModuleInstanceDescriptor;		/* 32 bytes */

#if 0
/** Call a module's set function. */
#define ClassModule_Set(pInstance, mask) \
if (pInstance) { \
	UINT32 (*pSet)(void *a, UINT32 b) = (pInstance)->instanceDescriptor.pModClassDescriptor->pSet; \
	if (pSet) \
		pSet(pInstance, mask); \
}
#else
int ClassModule_Set(ModuleInstanceDescriptor *pInstance, UINT32 mask);
#endif

/** Call a module's get function. */
#define ClassModule_Get(pInstance, mask) \
if (pInstance) { \
	UINT32 (*pGet)(void *a, UINT32 b) = (pInstance)->instanceDescriptor.pModClassDescriptor->pGet; \
	if (pGet) \
		pGet(pInstance, mask); \
}

/** Pack the sizes into the flags word. */
#define ClassModule_PackFlags(nInWires, nOutWires, nScratchWires) \
	((((nScratchWires) & 0xff) << 16) | (((nOutWires) & 0xff) << 8) | ((nInWires) & 0xff))

/** Get the input wire count 0..255 */
#define ClassMod_GetNInWires(packed) \
	((packed) & 0xff)

/** Get the output wire count 0..255 */
#define ClassMod_GetNOutWires(packed) \
	(((packed) >> 8) & 0xff)

/** Get the scratch wire count. */
#define ClassMod_GetNScratchWires(packed) \
	(((packed) >> 16) & 0xff)

/** Get the total number of wires */
#define ClassMod_GetWireCount(packed) \
	(((packed) & 0xff) + (((packed) >> 8) & 0xff) + (((packed) >> 16) & 0xff))

/** Get the module state. */
#define ClassMod_GetModuleState(packed) \
	(((packed) >> 24) & 0x03)


/** These macros operate on high-level module objects. The goal is to hide the
	details of the implementation from the module writer. */

/** Get the wires that are attached to the module */
#define ClassModule_GetWires(S)		((S)->instance.pWires)

/** Get the input wire count 0..255 */
#define ClassModule_GetNInWires(S) \
	(ClassMod_GetNInWires((S)->instance.packedFlags))

/** Get the output wire count 0..255 */
#define ClassModule_GetNOutWires(S) \
	(ClassMod_GetNOutWires((S)->instance.packedFlags))

/** Get the scratch wire count. */
#define ClassModule_GetNScratchWires(S) \
	(ClassMod_GetNScratchWires((S)->instance.packedFlags))

/** Get the module state. */
#define ClassModule_GetModuleState(S) \
	(ClassMod_GetModuleState((S)->instance.packedFlags))

/** Get the module objectID. */
#define ClassModule_GetObjectID(S) \
	((S)->instance.instanceDescriptor.nUniqueInstanceID)

/*------------------ Layout declarations ------------------*/

/** A layout instance. The instance is variable length on the heap, the size
being determined by the constructor arguments. */
typedef struct _LayoutInstance
{
	/** The basic instance data. */
	InstanceDescriptor instanceDescriptor;

	struct _LayoutInstance *pNextLayout;

	/** When 1, called on every iteration, otherwise called less frequently. */
	UINT32 nDivider;

	/** When zero, will execute, and be set to nDivider-1, otherwise will be decremeneted. */
	UINT32 nCurrentDivide;

	/** Average cycles per process. Times 256. */
	UINT32 averageCycles;

	/** Peak cycles per process. Times 256. */
	UINT32 peakCycles;

	/** Number of processes. */
	INT32 processCount;

	/** Instantaneous cycles for the entire layout that executed.  Times 256. */
	UINT32 instCycles;

	/** Averaged time in cycles between calls to the processing function.  Times 256. */
	UINT32 timePerProcess;

	/** Percentage CPU time */
	float percentCPU;

	/** Number of modules in the layout. */
	UINT32 nModules;

	/** The starting time for the last call to Layout_Process. */
	UINT32 m_last_start_time;

	/** Variable length array of module pointers. */
	ModuleInstanceDescriptor *pModuleInstances[1];
}
LayoutInstance;


/** The AWE instance object. */
typedef struct _AWEInstance
{
	/** The ID of this instance. */
	UINT32 m_coreID;

	/** The master heap. */
	UINT32 *m_master_heap;

	/** The second fast heap. */
	UINT32 *m_fastb_heap;

	/** The slow heap. */
	UINT32 *m_slow_heap;

	/** Head of chain of class instances. */
	InstanceDescriptor *m_pInstanceHead;

	/** Tail of chain of class instances. */
	InstanceDescriptor *m_pInstanceTail;

	/** Head of chain of I/O pin instances.
	Must be initialized to point at the last item in the above. */
	InstanceDescriptor *m_pIOPinHead;

	/** Tick instance pointer. */
	InstanceDescriptor *m_pTickObject;

	/** Head of list of layouts. */
	LayoutInstance *m_pLayoutHead;

	/** Tail of list of layouts. */
	LayoutInstance *m_pLayoutTail;

	/** The pointer to the lookup table - initially NULL. */
	void **m_lookup_table;

	/** The fast heap size. */
	UINT32 m_master_heap_size;

	/** Index of next free master heap word. */
	UINT32 m_master_heap_index;

	/** The second heap size. */
	UINT32 m_fastb_heap_size;

	/** Index of next free second heap word. */
	UINT32 m_fastb_heap_index;

	/** The slow heap size. */
	UINT32 m_slow_heap_size;

	/** Index of next free slow heap word. */
	UINT32 m_slow_heap_index;

	/** Initialized to 0 on program start or restart, incremented each time an
	instance of anything is created. */
	UINT32 m_unique_instance_ID_counter;

	/** The maximum ID supported by the lookup table. */
	UINT32 m_maxID;

//	/** The starting time for the last call to Layout_Process. */
//	UINT32 m_last_start_time;

	/** Some general purpose flag bits. */
	UINT32 m_general_flags;

	/** The target info for this instance. */
	TargetInfo m_target_info;

	/** Point to BSP audio start. */
	int (*m_pAwe_pltAudioStart)(void);

	/** Point to BSP audio stop. */
	int (*m_pAwe_pltAudioStop)(void);

	/** Poimt to BSP input pin table. */
	IOPinDescriptor *m_pInterleavedInputPin;

	/** Point to BSP output pin table. */
	IOPinDescriptor *m_pInterleavedOutputPin;

	/** Head of linked list of bounf wires. */
	WireInstance *m_pBindHead;

	/** Number of modules in module table. */
	UINT32 m_module_descriptor_table_size;

	/** Pointer to module table. */
	const ModClassModule **m_pModule_descriptor_table;
} AWEInstance;

/** Describe an arbitrary core. */
typedef struct _CoreDescriptor
{
	/**
	 * @brief Constructor.
	 * @param [in] pData		pointer to this object
	 * @param [in] pClasses		pointer to class table or NULL
	 * @param [in] nClasses		number of classes
	 * @param [in] pExtra		commands pointer
	 */
	int (*m_pConstructor)(void *pData, void *pClasses, UINT32 nClasses, void *pExtra);

	/**
	 * @brief Poimter to post constructor - might need to modify IPC pins.
	 * @param [in] pData		pointer to this CoreDescriptor
	 * @param [in] pIpcPins		pointer to table of IPC pins
	 * @param [in] nIpcPins		size of the table
	 */
	int (*m_pPostConstrctor)(void *pData, void *pIpcPins, UINT32 nIpcPins);

	/**
	 * @brief Destructor.
	 * @param [in] pData		pointer to this CoreDescriptor
	 */
	int (*m_pDestructor)(void *pData);

	/**
	 * @brief Pointer to core specific pump function.
	 * @param [in] pData		pointer to this CoreDescriptor
	 */
	void (*m_pPumpCore)(void *pData);

	/**
	 * @brief Pointer to core specific command function.
	 * @param [in] pData		pointer to this CoreDescriptor
	 * @param [in] txBuffer		send packet buffer
	 * @param [out] rxBuffer	receive packet buffer
	 */
	void (*m_pSendCommand)(void *pData, UINT32 *txBuffer, UINT32 *rxBuffer);

	/**
	 * @brief Pointer to core write wire function.
	 * @param [in] pData		pointer to this CoreDescriptor
	 * @param [in] pWire		poinyter to core wire in core address space
	 * @param [in] nWords		number of words to copy
	 * @param [in] pWords		pointer to words to write
	 */
	void (*m_pWriteInputWire)(void *pData, WireInstance *pWire, UINT32 nWords, Sample *pWords);

	/**
	 * @brief Pointer to core read wire function.
	 * @param [in] pData		pointer to this CoreDescriptor
	 * @param [in] pWire		poinyter to core wire in core address space
	 * @param [in] nWords		number of words to copy
	 * @param [out] pWords		pointer to words to read
	 */
	void (*m_pReadOutputWire)(void *pData, WireInstance *pWire, UINT32 nWords, Sample *pWords);

	/**
	 * @brief Pointer to core get samples function..
	 * @param [in] pData		pointer to this CoreDescriptor
	 * @param [in] pWire		poinyter to core wire in core address space
	 * @return					number of samples in core wire
	 */
	int (*m_GetNumSamples)(void *pData, WireInstance *pWire);

	/**
	 * @brief Pointer to core get channels function.
	 * @param [in] pData		pointer to this CoreDescriptor
	 * @param [in] pWire		poinyter to core wire in core address space
	 * @return					number of samples in core wire
	 */
	int (*m_GetNumChannels)(void *pData, WireInstance *pWire);

	/**
	 * @brief get the AWE instance
	 * @param [in] pData		pointer to this CoreDescriptor
	 * @return					instance pointer or NULL if in different address space
	 */
	AWEInstance *(*m_GetInstance)(void *pData);

	/** Proxy to IAudioCommands::ReadAndCopyFromInput. */
	int (*m_pReadAndCopy)(void *pCmds, int *pSamples, UINT32 nOutputChans, UINT32 reqSamples, void *pvDevice, UINT32 nInputChans, UINT32 *pchIdx, UINT32 pumpCount);

	/** Proxy to CWaveWriter::WriteSamples. */
	int (*m_pWriteSamples)(void *pvWriter, void *pSamples, UINT32 samples);

	/** Generic data. */
	void *m_pData;

	/** Which core this is. */
	UINT32 m_coreID;

	/** Set for SMP cores. */
	UINT32 m_isSMP;
} CoreDescriptor;

/* Notification constants for owned pins. */

#define AWE_NOTIFY_BIND		0		// BSP pin is bound

#define AWE_NOTIFY_DESTROY	1		// Target is destroyed, so are all pin bindings

/** Set when core is SMP. */
#define CORE_IS_SMP				1

/** Set when core is self-pumping (can't be SMP). */
#define CORE_IS_SELF_PUMPED		2

/** Test if a core is SMP. */
#define GetCoreIsSMP(x) \
	((x)->m_isSMP & CORE_IS_SMP)

/** Test if a core is self-pumping. */
#define GetCoreSelfPumped(x) \
	((x)->m_isSMP & CORE_IS_SELF_PUMPED)

/** Thread structure to record times and core pump completion. */
typedef struct _SRunPump
{
	/** The core ID this is pumping for. */
	int m_core;

	/** Which layout to pump. */
	int m_layoutIndex;

	/** The AWE instance we are calling. */
	void *m_pData;

	/** Utility pointer. */
	void *m_pData2;

	/** Passed in argument. */
	UINT32 m_nPumpSamples;

	/** Passed in argument. */
	UINT32 m_pumpCount;

	/** Average cycles for this core. */
	UINT32 m_averageCycles;

	/** Total time for this core. */
	UINT32 m_timePerProcess;

	/** Set when finished - negative if error. */
	volatile int m_finished;

	/** More thread working detection. */
	volatile int m_in_pump_count;

	/** Tick number when thread must finish. */
	UINT32 m_deadline;
} SRunPump;

/** Object to bind pairs of I/O pins together to IPC between them. */
typedef struct _IpcObject
{
	/** Source BSP pin. (InputN) */
	IOPinDescriptor *m_pSource;

	/** Sink BSP pin. (OutputN) */
	IOPinDescriptor *m_pSink;

	/** Owning object of this IPC. */
	void *m_pOwner;

#ifdef IPC_USES_ASRC
	/**
	 * @briwf Allocate a jitter buffer of the requested size
	 * @param [in] size			the size in samples
	 * @return					the buffer
	 */
	void *(*m_AllocateJitterBuffer)(UINT32 size);

	/**
	 * @brief Free a jitter buffer
	 * @param [in] pBuffer		buffer to free
	 */
	void (*m_ReleaseJitterBuffer)(void *pBuffer);

	/** The ASRC object. */
	DSPC_ASRC m_asrc;

	/** If set, use cubic interpolation. */
	UINT32 m_useCubic;

	/** The allocated jitter buffer. */
	void *m_pJitterBuffer;

	/** The ASRC properties. */
	DSPC_ASRC_PROPS *m_props;

	int m_sampleRateIn;

	int m_sampleRateOut;

	int m_phaseLen;

	int m_nBlocks;

#endif
} IpcObject;

/**
 * @brief Get the core descriptor for the fiven core.
 * param [in] pOwner					core object owner
 * @param [in] coreID					ID of core to get
 * @return								core descriptor
 */
CoreDescriptor *awe_pltGetCore(void *pOwner, UINT32 coreID);

/**
 * @brief Report if both halves bound.
 * @param [in] pIpc						this pointer
 * @retuen								1 if both bound
 */
UINT32 IpcPinBothBound(IpcObject *pIpc);

/**
 * @brief Notification from owned pin.
 * @param [in] pIpc						this pointer
 * @param [in] pThis					the pin
 * @param [in] eventCode				what its telling us
 */
void IpcPinNotify(IpcObject *pIpc, IOPinDescriptor *pPin, UINT32 eventCode);

/**
 * @brief Construct the object.
 * @param [in] pIpc						this pointer
 * @param [in] pOwner					object that owns cores
 * @param [in] pSource					source I/O pin
 * @param [in] pSink					sink I/O pin
 * @param [in] AllocateJitterBuffer		ASRC buffer allocatpr
 * @param [in] ReleaseJitterBuffer		ASRC buffer releaser
 * @return								-1 on error
 */
INT32 IpcPinConstructor(IpcObject *pIpc, void *pOwner, IOPinDescriptor *pSource, IOPinDescriptor *pSink,
	void *(*AllocateJitterBuffer)(UINT32 size), void (*ReleaseJitterBuffer)(void *pBuffer));

/**
 * @brief Destroy the object.
 * @param [in] pIpc						this pointer
 * @return								-1 on error
 */
INT32 IpcPinDestroy(IpcObject *pIpc);

/**
 * @brief Flip the IPC buffer pointers.
 * @param [in] pIpc						this pointer
 * @return								-1 on error
 */
INT32 IpcPinFlip(IpcObject *pIpc);

/**
 * @brief Pump the source (InputN) pin.
 * @param [in] pIpc						this pointer
 * @param [in] pBuffer					pump buffer
 * @return								-1 on error
 * For simple IPC this reads the sink and writes the source.
 */
INT32 IpcPinPumpSourcePin(IpcObject *pIpc, Sample *pBuffer);

/**
 * @brief Read samples from bound sink wire
 * @param [in] pIpc						this pointer
 * @param [in] pBuffer					buffer to read saples into
 * @return								number of samples read
 */
INT32 IpcPinReadSinkSamples(IpcObject *pIpc, Sample *pBuffer);

/**
 * @brief Write samples to bound source wires
 * @param [in] pIpc						this pointer
 * @param [in] nSamples					number of samples to write
 * @param [in] pBuffer					buffer of samples to write
 */
INT32 IpcPinWriteSourceSamples(IpcObject *pIpc, UINT32 nSamples, Sample *pBuffer);

#ifdef IPC_USES_ASRC
/**
 * @brief Create the ASRC
 * @param [in] pIpc				this pointer
 * @param [in] sinkSamples		number of sink samples
 * @param [in] sourceSamples	number of source samples
 * @param [in] channels			number of channels
 * @return						-1 on error
 */
INT32 IpcPinInitAsrc(IpcObject *pIpc, UINT32 sinkSamples, UINT32 sourceSamples,
	UINT32 channels);

/**
 * @brief Setup the ASRC
 * @param [in] pIpc				this pointer
 * @param [in] props			the ASRC properties
 * @param [in] sampleRateIn		input sample rate
 * @param [in] sampleRateOut	output sample rate
 * @param [in] phaseLen			[jase length
 * @return						-1 on error
 */
INT32 IpcPinSetupAsrc(IpcObject *pIpc, DSPC_ASRC_PROPS *props, int sampleRateIn, int sampleRateOut, int phaseLen);

/**
 * @brief Destroy the ASRC
 * @param [in] pIpc				this pointer
 * @return						-1 on error
 */
INT32 IpcPinDestroyAsrc(IpcObject *pIpc);

/**
 * @brief Read samples from ASRC
 * @param [in] pIpc				this pointer
 * @param [out] pBuffer			buffer to receive samples
 * @param [in] nSamples			number of samples to read
 * @return						-1 on error
 */
INT32 ASRCReadSamples(IpcObject *pIpc, fract32 *pBuffer, UINT32 nSamples);

/**
 * @brief Erite samples to ASRC
 * @param [in] pIpc				this pointer
 * @param [out] pBuffer			buffer of samples
 * @param [in] nSamples			number of samples to write
 * @return						-1 on error
 */
INT32 ASRCWriteSamples(IpcObject *pIpc, fract32 *pBuffer, UINT32 nSamples);

#endif

/** Bit to record if the tick (idle) function was called. */
#define AWE_TICKED			0x01

/** Bit to suppress profiling. */
#define AWE_NO_PROFILE		0x10

/** Used in special modules that need to access the framework. */
extern AWEInstance *g_pAWE_instance;

#ifdef IA610

/**
 * @brief Convert Knowles float to IEEE float.
 * @param val			Knowles value to convert
 * @return				IEEE value
 */
float awe_fwConvertToIEEE(fr32 val);

/**
 * @brief Convert an IEEE float to Knowles float.
 * @param val			IEEE value to convert
 * @return				Knowles value
 */
fr32 awe_fwConvertFromIEEE(float val);

#endif

/**
 * @brief Set the fundamental audio DMA block size
 * @param [in] pAwe						AWE instance pointer (this)
 * @param [in] nBlockSize				block size
 */
void awe_fwSetBlockSize(AWEInstance *pAwe, UINT32 nBlockSize);

/**
 * @brief Initialize the instance's target info.
 * @param [in] pAwe						the instance to initialize
 */
void awe_fwInitTargetInfo(AWEInstance *pAwe, UINT32 coreID, float coreClockSpeed, float sampleSpeed,
						  const char *name, int procType, int isFloat, int isFlash,
						  int nInputs, int nOutputs, int isSMP, int threads, float sampleRate,
						  int nInputChannels, int nOutputChannels, int nVerDay, int nVerMonth, int nVerYear);

/**
 * @brief Initialize the packed name (not SHARC).
 * @param [in] pPackedName			pointer to packed name array
 * @param [in] name					name as a string
 */
void awe_SetPackedName(UINT32 *pPackedName, const char *name);

/**
 * @brief Given an address in {objectID,index} form, compute the
 * address of the module member.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				the member index
 * @param [out] retVal				0 or error code
 * @return							pointer to member
 */
UINT32 *awe_fwAddressOfMember(AWEInstance *pAWE, UINT32 address, INT32 *retVal);

/**
 * @brief Given an address in {objectID,index} form, compute the
 * address of the module member. Also return the module pointer.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				the member index
 * @param [out] pMod				pointer to receive module pointer
 * @param [out] retVal				0 or error code
 * @return							pointer to member
 */
UINT32 *awe_fwAddressOfMember2(AWEInstance *pAWE, UINT32 address, ModuleInstanceDescriptor **pMod, INT32 *retVal);

/**
 * @brief Dereference a pointer to a nested module
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				address in 20.12 {objectID,index} form
 * @param [out] retVal				0 or error code
 * @return							ID of object pointed to, 0 on error
 */
INT32 awe_fwDerefPointer(AWEInstance *pAWE, UINT32 address, INT32 *retVal);

/**
 * @brief Assign a real pointer to a pointer type left hand side.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] addressLhs			LHS address in 20.12 {objectID,index} form
 * @param [in] addressRhs			RHS address in 20.12 {objectID,index} form
 * @param [in] offsRhs				offset of right hand side
 * @return							0 or error code
 */
INT32 awe_fwSetPointer(AWEInstance *pAWE, INT32 addressLhs, INT32 addressRhs, UINT32 offsRhs);

/**
 * @brief Change the ID of a module
 * @param [in] moduleID				ID of module to change
 * @param [in] newModuleID			ID to assign
 * @return							0 or error code
 */
INT32 awe_fwSetInstanceID(AWEInstance *pAWE, UINT32 moduleID, UINT32 newModuleID);

/**
 * Fetch the value at the given address.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				address in 20.12 {objectID,index} form
 * @param [in] floatFlg				value is float
 * @param [out] retVal				0 or error code
 * @return							fetched value, 0 on error
 */
INT32 awe_fwFetchValue(AWEInstance *pAWE, UINT32 address, INT32 *retVal, UINT32 ptrOffset, UINT32 floatFlg);

/**
 * @brief Fetch the value at the given address after get call.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				address in 20.12 {objectID,index} form
 * @param [in] mask					get call mask
 * @param [in] floatFlg				value is float
 * @param [out] retVal				0 or error code
 * @return							fetched value, 0 on error
 */
INT32 awe_fwGetCallFetchValue(AWEInstance *pAWE, UINT32 address, UINT32 mask, INT32 *retVal, UINT32 ptrOffset, UINT32 floatFlg);

/**
 * @brief Set the value at the given address.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				address in 20.12 {objectID,index} form
 * @param [in] floatFlg				value is float
 * @param [in] value				value to set
 * @return							0 or error code
 */
INT32 awe_fwSetValue(AWEInstance *pAWE, UINT32 address, INT32 value, UINT32 ptrOffset, UINT32 floatFlg);

/**
 * @brief Set the value at the given address, then do set call.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				address in 20.12 {objectID,index} form
 * @param [in] value				value to set
 * @param [in] mask					set call mask
 * @param [in] floatFlg				value is float
 * @return							0 or error code
 */
INT32 awe_fwSetValueSetCall(AWEInstance *pAWE, UINT32 address, INT32 value, UINT32 mask, UINT32 ptrOffset, UINT32 floatFlg);

/**
 * @brief Fetch the values at the given address.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				address in 20.12 {objectID,index} form
 * @param [in] offset				array offset
 * @param [in] argSize				number of arguments
 * @param [out] args				returned values
 * @param [in] floatFlg				when set, values are float
 * @return							0 or error code
 */
INT32 awe_fwFetchValues(AWEInstance *pAWE, UINT32 address, UINT32 offset, UINT32 argSize, Sample *args, UINT32 floatFlg);

/**
 * Fetch the values at the given address after get call.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				address in 20.12 {objectID,index} form
 * @param [in] offset				array offset
 * @param [in] mask					get call mask
 * @param [in] argSize				number of arguments
 * @param [out] args				returned values
 * @param [in] floatFlg				float values when set
 * @return							0 or error code
 */
INT32 awe_fwGetCallFetchValues(AWEInstance *pAWE, UINT32 address, UINT32 offset, UINT32 mask, UINT32 argSize, Sample *args, UINT32 floatFlg);

/**
 * @brief Write the arguments to the given address.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				address in 20.12 {objectID,index} form
 * @param [in] offset				array offset
 * @param [in] argSize				number of arguments
 * @param [in] args					values to set
 * @param [in] floatFlg				float values when set
 * @return							0 or error code
 */
INT32 awe_fwSetValues(AWEInstance *pAWE, UINT32 address, UINT32 offset, UINT32 argCount, const Sample *args, UINT32 floatFlg);

/**
 * @brief Write the arguments to the given address, then set call.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] address				address in 20.12 {objectID,index} form
 * @param [in] offset				array offset
 * @param [in] mask					set call mask
 * @param [in] argSize				number of arguments
 * @param [in] args					values to set
 * @param [in] floatFlg				float values when set
 * @return							0 or error code
 */
INT32 awe_fwSetValuesSetCall(AWEInstance *pAWE, UINT32 address, UINT32 offset, UINT32 mask, UINT32 argCount, const Sample *args, UINT32 floatFlg);

/**
 * @brief Returns the number of channels in the Layout's primary input and output pins.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [out] inCount				channels in primary input pin
 * @param [out] outCount			channels in primary output pin
 */
void awe_fwGetChannelCount(AWEInstance *pAWE, UINT32 *inCount, UINT32 *outCount);

/**
 * @brief Returns a pointer to where the platform should write input data.
 * @param [in] pinIdx				which input pin
 * @param [in] chan					which channel
 * @param [out] stride				data stride
 * @return							write pointr or NULL on error
 */
INT32 *awe_fwGetInputChannelPtr(AWEInstance *pAWE, UINT32 pinIdx, UINT32 chan, INT32 *stride);

/**
 * @brief Returns a pointer to where the platform should read output data from.
 * @param [in] pinIdx				which input pin
 * @param [in] chan					which channel
 * @param [out] stride				data stride
 * @return							read pointr or NULL on error
 */
INT32 *awe_fwGetOutputChannelPtr(AWEInstance *pAWE, UINT32 pinIdx, UINT32 chan, INT32 *stride);

/**
 * @brief Returns the block size of an input pin.
 * @param [in] pinIdx				which input pin
 * @return							blocks size or 0 on error
 */
UINT32 awe_fwGetInputBlockSize(AWEInstance *pAWE, UINT32 pinIdx);

/**
 * @brief Returns the sample rate of an input pin.
 * @param [in] pinIdx				which input pin
 * @return							blocks size or 0 on error
 */
float awe_fwGetInputSampleRate(AWEInstance *pAWE, UINT32 pinIdx);

/**
 * @brief Handles double buffering of the Layout's I/O pins.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] pinIdx				which input pin
 * #param [in] samplesPerTick		number of samples this tick
 * @return							bitvector of ready layouts
 */
UINT32 awe_fwAudioDMAComplete(AWEInstance *pAWE, UINT32 pinIdx, INT32 samplesPerTick);

/**
 * @brief Evaluate the layout mask
 * @param [in] pAWE					AWE instance pointer (this)
 * @return							bitvector of ready layouts
 */
UINT32 awe_fwEvalLayoutMask(AWEInstance *pAWE, UINT32 dividers[4]);

/** Return sizeof INT32 for the target. */
UINT32 awe_fwGetSizeofInt(void);

/**
 * #brief Allocate a block of storage from the heap.
 * @param [in] size					size in bytes of storage to allocate
 * @param [in] heapIndex			which heap(s) to allocate on
 * @param [out] retVal				error code on failure
 * @return							pointer to allocated storage
 *
 * If zero returned, the reason is returned in retVal. The storage is zeroed.
 */
void *awe_fwMalloc(UINT32 size, UINT32 heapIndex, INT32 *retVal);

/**
 * #brief Allocate an aligned block of storage from the heap.
 * @param [in] size					size in bytes of storage to allocate
 * @param [in] align				alignemnt required in bytes
 * @param [in] heapIndex			which heap(s) to allocate on
 * @param [out] retVal				error code on failure
 * @return							pointer to allocated storage
 *
 * If zero returned, the reason is returned in retVal. The storage is zeroed.
 * Alignments are coerced to a multiple of sizeof(int).
 */
void *awe_fwMallocAligned(UINT32 size, UINT32 align, UINT32 heapIndex, INT32 *retVal);

/**
 * #brief Allocate a block of storage from the heap.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] size					size in bytes of storage to allocate
 * @param [in] heapIndex			which heap(s) to allocate on
 * @param [out] retVal				error code on failure
 * @return							pointer to allocated storage
 *
 * If zero returned, the reason is returned in retVal. The storage is zeroed.
 */
void *awe_fwMalloc2(AWEInstance *pAWE, UINT32 size, UINT32 align, UINT32 heapIndex, INT32 *retVal);

/**
 * #brief Allocate a block of storage from shared memory.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] size					size in bytes of storage to allocate
 * @param [out] retVal				error code on failure
 * @return							pointer to allocated storage
 *
 * If zero returned, the reason is returned in retVal.
 * Implemented only for those targets that need special handling
 * which should only br non-SMP multicore systems.
 */
#if !defined(EXTERN_ALLOC_SHARED)
#define awe_pltMallocShared(pAWE, size, retVal) \
    awe_fwMalloc2(pAWE, size, sizeof(int), AWE_HEAP_FAST2SLOW, retVal)
#define awe_pltFreeShared(pAWE, buffer)
#else
extern void *awe_pltMallocShared(AWEInstance *pAWE, UINT32 size, UINT32 *retVal);
extern INT32 awe_pltFreeShared(AWEInstance *pAWE, void *buffer);
#endif

/**
 * @brief Return the sizes of the heaps.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [out] heaps				array of 6 words to receive values
 * @return							0 or error code
 */
INT32 awe_fwGetHeapSize(AWEInstance *pAWE, UINT32 *pHeaps);

/**
 * @brief Reset the framework to its initial state.
 * @param [in] pAWE					AWE instance pointer (this)
 */
void awe_fwDestroy(AWEInstance *pAWE);

/**
 * @brief Create the AWE heaps.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] master_heap_size		requested size of master heap
 * @param [in] slow_heap_size		requested size of slow heap
 * @param [in] fastb_heap_size		requested size of other heap
 * @return							error code
 */
INT32 awe_fwAllocateHeaps(AWEInstance *pAWE, UINT32 master_heap_size, UINT32 slow_heap_size, UINT32 fastb_heap_size);

/**
 * @brief Destroy the heaps allocated by awe_fwAllocateHeaps.
 * @param [in] pAWE					AWE instance pointer (this)
 */
void awe_fwDestroyHeaps(AWEInstance *pAWE);

/**
 * @brief Copy the target info to the caller.
 * @param [out] pTarget				buffer to receive target info
 * @return							0 or error code
 */
INT32 awe_fwGetTargetInfo(AWEInstance *pAWE, TargetInfo *pTarget);

/**
 * @brief Copy the file system info to the caller.
 * @param [out] pFileSystemInfo		buffer to receive file system info
 * @return							0 or error code
 */
INT32 GetFileSystemInfo(FileSystemInfo *pFileSystemInfo);

/**
 * @brief Get the next instance number.
 * @param [in] pAWE					AWE instance pointer (this)
 * #return							next instance ID
 */
UINT32 GetNextInstanceID(AWEInstance *pAWE);

/**
 * @brief Get the number of classes known to the framework.
 * @return							the class count
 */
UINT32 awe_fwGetClassCount(void);

/**
 * @brief Get the first object in the object chain.
 * @param [out] pObject				pointer to receive first object pointer
 * @param [out] pClassID			pointer to receive first object class
 * @return							0 or error code
 */
INT32 awe_fwGetFirstObject(InstanceDescriptor **pObject, UINT32 *pClassID);

/**
 * @brief Get the first object in the object chain.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [out] pObject				pointer to receive first object pointer
 * @param [out] pClassID			pointer to receive first object class
 * @return							0 or error code
 */
INT32 awe_fwGetFirstObject2(AWEInstance *pAWE, InstanceDescriptor **pObject, UINT32 *pClassID);

/**
 * @brief Get the next object in the object chain.
 * @param [in] currentObject		current object pointer
 * @param [out] pObject				pointer to receive next object pointer
 * @param [out] pClassID			pointer to receive next object class
 * @return							0 or error code
 */
INT32 awe_fwGetNextObject(InstanceDescriptor *currentObject, InstanceDescriptor **pObject, UINT32 *pClassID);

/**
 * @brief Get an object based on its unique ID.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] ID					ID of object to find
 * @param [out] pObject				pointer to receive found object pointer
 * @param [out] pClassID			pointer to receive found object class
 * @return							0 or error code
 */
INT32 awe_fwGetObjectByID(AWEInstance *pAWE, UINT32 ID, InstanceDescriptor **pObject, UINT32 *pClassID);

/**
 * @brief Get an object based on its unique ID.
 * @param [in] ID					ID of object to find
 * @param [out] pObject				pointer to receive found object pointer
 * @param [out] pClassID			pointer to receive found object class
 * @return							0 or error code
 */
INT32 awe_fwGetObjectByID2(UINT32 ID, InstanceDescriptor **pObject, UINT32 *pClassID);

/**
 * @brief Get the first I/O object in the object chain.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [out] pObject				pointer to receive first object pointer
 * @param [out] pClassID			pointer to receive first object class
 * @param [out] sampleRate			pin sample rate
 * @param [out] info1				pin info1
 * @param [out] info2				pin info2
 * @param [out] info3				pin info3
 * @param [out] name0				first name word
 * @param [out] name1				second name word
 * @return							0 or error code
 */
INT32 awe_fwGetFirstIO(AWEInstance *pAWE, InstanceDescriptor **pObject, UINT32 *pClassID, float *sampleRate,
	UINT32 *info1, UINT32 *info2, UINT32 *info3, UINT32 *name0, UINT32 *name1);

/**
 * @brief Get the next I/O object in the object chain.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] ioID					ID of current object
 * @param [out] pObject				pointer to receive next object pointer
 * @param [out] pClassID			pointer to receive next object class
 * @param [out] sampleRate			pin sample rate
 * @param [out] info1				pin info1
 * @param [out] info2				pin info2
 * @param [out] info3				pin info3
 * @param [out] name0				first name word
 * @param [out] name1				second name word
 * @return							0 or error code
 */
INT32 awe_fwGetNextIO(AWEInstance *pAWE, UINT32 ioID, InstanceDescriptor **pObject, UINT32 *pClassID, float *sampleRate,
	UINT32 *info1, UINT32 *info2, UINT32 *info3, UINT32 *name0, UINT32 *name1);

/**
 * @brief Get the type of a wire.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] wireID				ID of wire to get
 * @param [out] pClassID			class of wire
 * @param [out] sampleRate			sample rate of wire
 * @param [out] info1				first info word
 * @param [out] info2				second info word
 * @param [out] info3				third info word
 * @return							0 or error code
 */
INT32 awe_fwGetWireType(AWEInstance *pAWE, UINT32 wireID, UINT32 *pClassID, float *sampleRate, UINT32 *info1, UINT32 *info2, UINT32 *info3);

/**
 * @brief Get the type of a pin.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] wireID				ID of pin to get
 * @param [out] pClassID			class of pin
 * @param [out] pBoundID			ID of bound wire
 * @param [out] sampleRate			sample rate of wire
 * @param [out] info1				first info word
 * @param [out] info2				second info word
 * @param [out] info3				third info word
 * @param [out] name0				first name word
 * @param [out] name1				second name word
 * @return							0 or error code
 */
INT32 awe_fwGetPinType(AWEInstance *pAWE, UINT32 pinID, UINT32 *pClassID, UINT32 *pBoundID, float *sampleRate,
	UINT32 *info1, UINT32 *info2, UINT32 *info3, UINT32 *name0, UINT32 *name1);

/**
 * @brief Return the type of the class this instance was created from.
 * @param [in] pClass				class to look in
 * @return							class ID
 */
UINT32 awe_fwGetClassType(const InstanceDescriptor *pClass);

/**
 * @brief Generic wire instance constructor used by all wire constructors.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [out] retVal				to receive the error code
 * @param [in] sampleRate			sample rate of wire
 * @param [in] info1				packed wire info1
 * @param [in] info2				packed wire info2
 * @param [in] info3				packed wire info3
 * @param [in] pClass				point to wire class
 * @return							constructed object or NULL on error
 */
InstanceDescriptor *GenericWire_Constructor(AWEInstance *pAWE, INT32 *retVal, float sampleRate, UINT32 info1, UINT32 info2, UINT32 info3, const ClassDescriptor *pClass);

/**
 * @brief Wire instance constructor.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [out] retVal				to receive the error code
 * @param [in] srate				sample rate
 * @param [in] info1				packed wire info1
 * @param [in] info2				packed wire info2
 * @param [in] info3				packed wire info3
 * @return							constructed object or NULL on error
 */
InstanceDescriptor *ClassWire_Constructor(AWEInstance *pAWE, INT32 *retVal, INT32 srate, UINT32 info1, UINT32 info2, UINT32 info3);

/**
 * @brief Bind a wire to an I/O object.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] wireID				ID of the wire to bind
 * @param [in] pinID				pin ID of the pin to bind
 * @return							0 or error code
 */
INT32 BindIOToWire(AWEInstance *pAWE, UINT32 wireID, UINT32 pinID);

/**
 * @brief Lookup a module class by ID.
 * @param [in] classID				class to look for
 * @return							class or NULL on error
 */
const ModClassModule *LookupModuleClass(AWEInstance *pAWE, UINT32 classID);

/**
 * @brief Returns the number of modules in the table.
 * @param [in] pAWE					AWE instance pointer (this)
 * @return							number of classes in module class table
 */
UINT32 awe_fwGetCIModuleCount(AWEInstance *pAWE);

/**
 * @brief Get the information for the specified module.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] index				index of item to get
 * @param [out] pDescr				pointer to receive class pointer
 * @param [out] classID				pointer to receive class ID
 * @param [out] numParameters		pointer to receive packed parameters
 * @return							0 or error code
 */
INT32 awe_fwGetCIModuleInfo(AWEInstance *pAWE, UINT32 index, UINT32 *classID, UINT32 *numParameters);

/**
 * @brief This	executes a module's process function with profiling.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] pModule				the module to pump
 */
void ClassModule_Execute(AWEInstance *pAWE, ModuleInstanceDescriptor *pModule);

/**
 * @brief This is the inline "non-profiling" NP version	 of ClassModule_Execute.
 * @param [in] pModule				the module to pump
 */
static VEC_INLINE void ClassModule_ExecuteNP(ModuleInstanceDescriptor *pModule)
{
	pModule->pProcessFunc(pModule);
}

/**
 * @brief Base class module instance constructor.
 * @param [in] pClass				class of object to construct
 * @param [out] retVal				return error code
 * @param [in] nIO					packed wire info
 * @param [in] pWires				array of wires
 * @param [in] argCount				number of arguments
 * @param [in] args					the arguments
 * @return							constructed object or NULL on error
 *
 * This function must be called first to construct the base module, then derived
 * classes may operate on the constructed object further.
 */
ModInstanceDescriptor *BaseClassModule_Constructor(
		const ModClassModule * FW_RESTRICT pClass,
		INT32 * FW_RESTRICT retVal,
		UINT32 nIO,
		WireInstance **pWires,
		size_t argCount,
		const Sample * FW_RESTRICT args);

/**
 * @brief Base class module instance constructor.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] pClass				class of object to construct
 * @param [out] retVal				return error code
 * @param [in] nIO					packed wire info
 * @param [in] pWireIDs				array of wire IDs
 * @param [in] argCount				number of arguments
 * @param [in] args					the arguments
 * @return							constructed object or NULL on error
 *
 * This function must be called first to construct the base module, then derived
 * classes may operate on the constructed object further.
 */
ModInstanceDescriptor *BaseClassModule_Constructor2(AWEInstance *pAWE,
		const ModClassModule * FW_RESTRICT pClass,
		INT32 * FW_RESTRICT retVal,
		UINT32 nIO,
		WireInstance **pWires,
		size_t argCount,
		const Sample * FW_RESTRICT args);

/**
 * @brief Generic module instance constructor.
 * @param [in] classID				class ID of object to construct
 * @param [out] retVal				return error code
 * @param [in] nIO					packed wire info
 * @param [in] pWires				array of wires
 * @param [in] argCount				number of arguments
 * @param [in] args					the arguments
 * @return							constructed object or NULL on error
 */
ModInstanceDescriptor *ClassModule_Constructor(
		UINT32 classID,
		INT32 * FW_RESTRICT retVal,
		UINT32 nIO,
		WireInstance **pWires,
		size_t argCount,
		Sample * FW_RESTRICT args);

/**
 * @brief Generic module instance constructor.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] classID				class ID of object to construct
 * @param [out] retVal				return error code
 * @param [in] nIO					packed wire info
 * @param [in] pWires				array of wires
 * @param [in] argCount				number of arguments
 * @param [in] args					the arguments
 * @return							constructed object or NULL on error
 */
ModInstanceDescriptor *ClassModule_Constructor3(
		AWEInstance *pAWE,
		UINT32 classID,
		INT32 * FW_RESTRICT retVal,
		UINT32 nIO,
		WireInstance **pWires,
		size_t argCount,
		Sample * FW_RESTRICT args);

/**
 * @brief Generic module instance constructor.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] classID				class ID of object to construct
 * @param [out] retVal				return error code
 * @param [in] nIO					packed wire info
 * @param [in] pWireIDs				array of wire IDs
 * @param [in] argCount				number of arguments
 * @param [in] args					the arguments
 * @return							constructed object or NULL on error
 */
ModInstanceDescriptor *ClassModule_Constructor2(
		AWEInstance *pAWE,
		UINT32 classID,
		INT32 * FW_RESTRICT retVal,
		UINT32 nIO,
		UINT32 *pWireIDs,
		size_t argCount,
		Sample * FW_RESTRICT args);

/**
 * @brief Set the given module to active=0, bypass=1, mute=2, inactive=other.
 * @param [in] pModule				nmodule to set state to
 * @param [in] state				state to set
 * @return							0 or error code
 */
INT32 awe_fwSetModuleState(ModuleInstanceDescriptor *pModule, INT32 state);

/**
 * @brief Get the given modules state: active=0, bypass=1, mute=2, inactive=3.
 * @param [in] pModule				module to get state from
 * @return							state, or -ve error code
 */
INT32 awe_fwGetModuleState(ModuleInstanceDescriptor *pModule);

/**
 * @brief Handle bound wir pointer adjustment.
 * @param [in] pAWE					AWE instance pointer (this)
 */
void awe_fwPrePump(AWEInstance *pAWE);

/**
 * @brief Pump the specified module.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] pModule				module to pump
 * @return							0 or error code
 */
INT32 awe_fwPumpModule(AWEInstance *pAWE, ModuleInstanceDescriptor *pModule);

/**
 * @brief Deliver an event to the specified module.
 * @param [in] pModule				module to deliver to
 * @param [in] eventCode			event to deliver
 * @return							0 or error code
 */
INT32 awe_fwModuleEvent(ModuleInstanceDescriptor *pModule, INT32 eventCode);

/**
 * @brief This must be called before doing anything else with AWE.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] clock_domain			when non-zero, the clock doamin of this core
 *
 * Sets all the I/O pins to a known state.
 */
void awe_fwInit_io_pins(AWEInstance *pAWE, UINT32 clock_domain);

/**
 * @brief Initialize the Layout IO wire buffers once layout is created
 */
void awe_fwAudioInitIO(AWEInstance *pAWE);

/**
 * @brief Layout instance constructor.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [out] retVal				error code
 * @param [in] nModules				number of modules to allocate space for
 * @param [in] nDivider				layout divider to use
 * @return							constructed object or NULL on error
 */
InstanceDescriptor *ClassLayout_Constructor(AWEInstance *pAWE, INT32 *retVal, INT32 nModules, INT32 nDivider);

/**
 * @brief Add one or more modules to a layout.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] argCount				argument count
 * @param [in] args					the arguments
 * @return							0 or error code
 *
 * The arguments are:
 *
 *	args[0] - ID of the layout
 *	args[1] - offset in module table
 *	args[2+] - array of module IDs
 *
 */
INT32 awe_fwAddModuleToLayout(AWEInstance *pAWE, UINT32 argCount, const Sample *args);

/**
 * @brief Generic layout pump function.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] pInstance			layout to pump
 * @param [out] pInstCycles			pointer to receive profile cycles
 * @return							0 or error code
 */
void ClassLayout_Process(AWEInstance *pAWE, LayoutInstance *pInstance, UINT32 *pInstCycles, UINT32 *pTimePerProcess);

/**
 * @brief Master framework pump function.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] layout_no			the layout index to pump
 * @return							0 or error code
 */
INT32 awe_fwPump(AWEInstance *pAWE, UINT32 layout_no);

/**
 * Master framework tick function.
 * @param [in] pAWE					AWE instance pointer (this)
 * @return							0 or error code
 */
INT32 awe_fwTick(AWEInstance *pAWE);

/**
 * Call a module's set function if it has one.
 * @param [in] pModule				module pointer
 * @param [in] mask					mask to pass to set call
 * @return							0 or error code
 */
INT32 awe_fwSetCall(ModuleInstanceDescriptor *pModule, UINT32 mask);

INT32 awe_fwSetCall2(AWEInstance *pAWE, UINT32 moduleID, UINT32 mask);

/**
 * Call a module's get function if it has one.
 * @param [in] pModule				module pointer
 * @param [in] mask					mask to pass to set call
 * @return							0 or error code
 */
INT32 awe_fwGetCall(ModuleInstanceDescriptor *pModule, UINT32 mask);

INT32 awe_fwGetCall2(AWEInstance *pAWE, UINT32 moduleID, UINT32 mask);

/**
 * @brief Return the profiling information for a specified layout.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] layoutNumber			the layout index to query
 * @param [out] pAverageCycles		pointer to receive average cycles * 128
 * @param [out] pTimePerProcess		pointer to receive total cycles * 128
 * @return							0 or error code
*/
INT32 awe_fwGetProfileValues(AWEInstance *pAWE, INT32 layoutNumber, UINT32 *pAverageCycles, UINT32 *pTimePerProcess);

/**
 * @brief Clear the profiling information for a specified layout.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] layoutNumber			the layout index to clear
 * @return							0 or error code
 */
INT32 awe_fwClearProfileValues(AWEInstance *pAWE, INT32 layoutNumber);


/**
 * @brief Load an AWB file.
 * @param binaryFile				the AWB file to load
 * @return							zero or error code
 */
INT32 BinaryLoad(const char *binaryFile);

/**
 * @brief Load an AWB file into a single instance.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param binaryFile				the AWB file to load
 * @return							zero or error code
 */
INT32 BinaryLoadSingle(AWEInstance *pAWE, const char *binaryFile);

/**
 * @brief Create a table for O(1) object lookup.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] maxID				max ID to size table for
 * @return							zero or error code
 */
UINT32 awe_fwcreateLookupTable(AWEInstance *pAWE, UINT32 maxID);

/**
 * @brief Set an object pointer in the lookup table.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] ID					ID to set
 * @param [in] pObject				object pointer to set
 * @return							zero or error code
 */
void awe_fwSetIDPointer(AWEInstance *pAWE, UINT32 id, InstanceDescriptor *pObject);

/**
 * @brief Lookup an object by ID.
 * @param [in] pAWE					AWE instance pointer (this)
 * @param [in] id					ID to lookup
 * @return							object pointer or NULL if not found
 */
void *awe_fwLookupID(AWEInstance *pAWE, UINT32 id);

/**
 * @brief Update the object lookup table.
 * @param [in] pAWE					AWE instance pointer (this)
 *
 * Recreates the assocxiations between ID and pointer after changing object IDs.
 */
INT32 awe_fwUpdateLookupTable(AWEInstance *pAWE);

/**
 * @brief Get the head of the I/O list.
 * @param [in] pAWE					AWE instance pointer (this)
 * @return							head of I/O list
 */
InstanceDescriptor *awe_fwGetIOPinsHead(AWEInstance *pAWE);

/**
 * @brief Get the head of the layout list.
 * @param [in] pAWE					AWE instance pointer (this)
 * @return							head of layout list
 */
LayoutInstance *awe_fwGetLayoutHead(AWEInstance *pAWE);

/**
 * @brief Convert a file to one in the path asneeded
 * @param [out] outFile				output buffer
 * @param [in] outFileSize			size of output buffer
 * @param [in] file					file to check
 * @return							1 if exists with outFile containing pat, else 0 if not found
 */
int awe_fwFindFileInPath(char *outFile, UINT32 outFileSize, const char *file);


#ifndef NULL
#define NULL 0
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAILURE
#define FAILURE 0
#endif

#ifdef __GNUC__
  #if __GNUC__ >= 4
	#define DLL_PUBLIC __attribute__ ((visibility("default")))
  #else
	#define DLL_PUBLIC
  #endif
#else
  #define DLL_PUBLIC
#endif

#ifdef	__cplusplus
}
#endif

#ifdef WIN32
#define FIXNAME(x)		x
#else
#define PASTE(x, y)		x ## y
#define EVAL(x, y)		PASTE(x, y)
#define FIXNAME(x)		EVAL(MODULE_PREFIX, x)
#endif

#define AWE_UNUSED_VARIABLE(x)	((void)(x))

#endif	/* _FRAMEWORK_H */

