/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRand.h
****************************************************************************
*
*     Description:  Random number generator using a LCG algorithm
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
 * @brief Random number generator using a LCG algorithm
 */

#ifndef _MOD_RAND_H
#define _MOD_RAND_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Rand_seed 0x00000100
#define OFFSET_Rand_seed 0x00000008

#define CLASSID_RAND (CLASS_ID_MODBASE + 123)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRandInstance
{
    ModuleInstanceDescriptor instance;
    UINT32             seed;                // Initial seed value for the random number generator.
    
} awe_modRandInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRandClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRandConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_RAND, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRandProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RAND_H

/**
 * @}
 *
 * End of file.
 */
