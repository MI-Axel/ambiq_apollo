/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPeriodicSource.h
****************************************************************************
*
*     Description:  Continuously outputs a buffer of data
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2017
*                   1800 Wyatt Drive, Suite 14
*                   Santa Clara, CA 95054
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Continuously outputs a buffer of data
 */

#ifndef _MOD_PERIODICSOURCE_H
#define _MOD_PERIODICSOURCE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_PeriodicSource_L 0x00000100
#define MASK_PeriodicSource_numChannels 0x00000200
#define MASK_PeriodicSource_blockSize 0x00000400
#define MASK_PeriodicSource_stateIndex 0x00000800
#define MASK_PeriodicSource_value 0x00001000
#define OFFSET_PeriodicSource_L 0x00000008
#define OFFSET_PeriodicSource_numChannels 0x00000009
#define OFFSET_PeriodicSource_blockSize 0x0000000A
#define OFFSET_PeriodicSource_stateIndex 0x0000000B
#define OFFSET_PeriodicSource_value 0x0000000C

#define CLASSID_PERIODICSOURCE (CLASS_ID_MODBASE + 119)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPeriodicSourceInstance
{
    ModuleInstanceDescriptor instance;
    INT32              L;                   // Number of (multi-channel) samples in the internal buffer.
    INT32              numChannels;         // Number of channels in the output. This is only needed for the MATLAB simulation.
    INT32              blockSize;           // Output blockSize. This is only needed for the MATLAB simulation.
    INT32              stateIndex;          // Index of the next data sample to output. This circularly wraps.
    FLOAT32*           value;               // Output data array.
} awe_modPeriodicSourceInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPeriodicSourceClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modPeriodicSourceConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modPeriodicSourceProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PERIODICSOURCE_H

/**
 * @}
 *
 * End of file.
 */
