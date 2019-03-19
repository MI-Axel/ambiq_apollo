/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMultiplier.h
****************************************************************************
*
*     Description:  Multi-input multiplier
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
 * @brief Multi-input multiplier
 */

#ifndef _MOD_MULTIPLIER_H
#define _MOD_MULTIPLIER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Multiplier_oneChannelOutput 0x00000100
#define OFFSET_Multiplier_oneChannelOutput 0x00000008

#define CLASSID_MULTIPLIER (CLASS_ID_MODBASE + 2032)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMultiplierInstance
{
    ModuleInstanceDescriptor instance;
    INT32              oneChannelOutput;    // Boolean value that determines whether all channels are summed to form a single output.
    
} awe_modMultiplierInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMultiplierClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMultiplierConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MULTIPLIER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMultiplierProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MULTIPLIER_H

/**
 * @}
 *
 * End of file.
 */
