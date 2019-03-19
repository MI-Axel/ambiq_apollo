/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModComplexMultiplier.h
****************************************************************************
*
*     Description:  Multi-input complex multiplier
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
 * @brief Multi-input complex multiplier
 */

#ifndef _MOD_COMPLEXMULTIPLIER_H
#define _MOD_COMPLEXMULTIPLIER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ComplexMultiplier_oneChannelOutput 0x00000100
#define OFFSET_ComplexMultiplier_oneChannelOutput 0x00000008

#define CLASSID_COMPLEXMULTIPLIER (CLASS_ID_MODBASE + 1238)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modComplexMultiplierInstance
{
    ModuleInstanceDescriptor instance;
    INT32              oneChannelOutput;    // Boolean value that determines whether all channels are summed to form a single output
    
} awe_modComplexMultiplierInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modComplexMultiplierClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modComplexMultiplierConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COMPLEXMULTIPLIER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modComplexMultiplierProcess(void *pInstance);

 

void awe_modComplexMultiplierBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_COMPLEXMULTIPLIER_H

/**
 * @}
 *
 * End of file.
 */
