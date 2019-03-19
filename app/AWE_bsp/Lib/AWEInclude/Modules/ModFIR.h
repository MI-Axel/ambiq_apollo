/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFIR.h
****************************************************************************
*
*     Description:  FIR filter
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
 * @brief FIR filter
 */

#ifndef _MOD_FIR_H
#define _MOD_FIR_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FIR_numTaps 0x00000100
#define MASK_FIR_stateIndex 0x00000200
#define MASK_FIR_coeffs 0x00000400
#define MASK_FIR_state 0x00000800
#define OFFSET_FIR_numTaps 0x00000008
#define OFFSET_FIR_stateIndex 0x00000009
#define OFFSET_FIR_coeffs 0x0000000A
#define OFFSET_FIR_state 0x0000000B

#define CLASSID_FIR (CLASS_ID_MODBASE + 15)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFIRInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numTaps;             // Length of the filter.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables.
    FLOAT32*           coeffs;              // Filter coefficient array in normal order.
    FLOAT32*           state;               // State variable array. The size of the array equals stateLen * numChannels.
} awe_modFIRInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFIRClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFIRConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFIRProcess(void *pInstance);

UINT32 awe_modFIRSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FIR_H

/**
 * @}
 *
 * End of file.
 */
