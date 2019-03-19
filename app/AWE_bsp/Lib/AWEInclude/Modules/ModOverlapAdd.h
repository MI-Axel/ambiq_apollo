/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModOverlapAdd.h
****************************************************************************
*
*     Description:  Overlap and add method
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
 * @brief Overlap and add method
 */

#ifndef _MOD_OVERLAPADD_H
#define _MOD_OVERLAPADD_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_OverlapAdd_stateIndex 0x00000100
#define MASK_OverlapAdd_overlapLength 0x00000200
#define MASK_OverlapAdd_channelCount 0x00000400
#define MASK_OverlapAdd_state 0x00000800
#define OFFSET_OverlapAdd_stateIndex 0x00000008
#define OFFSET_OverlapAdd_overlapLength 0x00000009
#define OFFSET_OverlapAdd_channelCount 0x0000000A
#define OFFSET_OverlapAdd_state 0x0000000B

#define CLASSID_OVERLAPADD (CLASS_ID_MODBASE + 1302)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modOverlapAddInstance
{
    ModuleInstanceDescriptor instance;
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              overlapLength;       // Number of samples to be overlapped
    INT32              channelCount;        // Number of channels
    FLOAT32*           state;               // State variable array
} awe_modOverlapAddInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modOverlapAddClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modOverlapAddConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modOverlapAddProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_OVERLAPADD_H

/**
 * @}
 *
 * End of file.
 */
