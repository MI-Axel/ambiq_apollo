/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPeriodicSourceFract32.h
****************************************************************************
*
*     Description:  Continuously outputs a buffer of fract32 data
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
 * @brief Continuously outputs a buffer of fract32 data
 */

#ifndef _MOD_PERIODICSOURCEFRACT32_H
#define _MOD_PERIODICSOURCEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_PeriodicSourceFract32_L 0x00000100
#define MASK_PeriodicSourceFract32_numChannels 0x00000200
#define MASK_PeriodicSourceFract32_blockSize 0x00000400
#define MASK_PeriodicSourceFract32_stateIndex 0x00000800
#define MASK_PeriodicSourceFract32_value 0x00001000
#define OFFSET_PeriodicSourceFract32_L 0x00000008
#define OFFSET_PeriodicSourceFract32_numChannels 0x00000009
#define OFFSET_PeriodicSourceFract32_blockSize 0x0000000A
#define OFFSET_PeriodicSourceFract32_stateIndex 0x0000000B
#define OFFSET_PeriodicSourceFract32_value 0x0000000C

#define CLASSID_PERIODICSOURCEFRACT32 (CLASS_ID_MODBASE + 167)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPeriodicSourceFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              L;                   // Number of (multi-channel) samples in the internal buffer.
    INT32              numChannels;         // Number of channels in the output.  This is only needed for the MATLAB simulation.
    INT32              blockSize;           // Output blockSize.  This is only needed for the MATLAB simulation.
    INT32              stateIndex;          // Index of the next data sample to output.  This circularly wraps
    fract32*           value;               // Output data array
} awe_modPeriodicSourceFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPeriodicSourceFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modPeriodicSourceFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modPeriodicSourceFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PERIODICSOURCEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
