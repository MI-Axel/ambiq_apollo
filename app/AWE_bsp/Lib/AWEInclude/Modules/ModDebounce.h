/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDebounce.h
****************************************************************************
*
*     Description:  Debounces signals
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
 * @brief Debounces signals
 */

#ifndef _MOD_DEBOUNCE_H
#define _MOD_DEBOUNCE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Debounce_waitTime 0x00000100
#define MASK_Debounce_count 0x00000200
#define MASK_Debounce_waitCount 0x00000400
#define MASK_Debounce_firstTime 0x00000800
#define MASK_Debounce_previousBlock 0x00001000
#define OFFSET_Debounce_waitTime 0x00000008
#define OFFSET_Debounce_count 0x00000009
#define OFFSET_Debounce_waitCount 0x0000000A
#define OFFSET_Debounce_firstTime 0x0000000B
#define OFFSET_Debounce_previousBlock 0x0000000C

#define CLASSID_DEBOUNCE (CLASS_ID_MODBASE + 33)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDebounceInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            waitTime;            // Waiting time before switching
    INT32              count;               // Counts down to zero
    INT32              waitCount;           // waitTime as a number of blocks
    INT32              firstTime;           // Indicates first block processed
    INT32*             previousBlock;       // Held block
} awe_modDebounceInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDebounceClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDebounceConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDebounceProcess(void *pInstance);

UINT32 awe_modDebounceSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DEBOUNCE_H

/**
 * @}
 *
 * End of file.
 */
