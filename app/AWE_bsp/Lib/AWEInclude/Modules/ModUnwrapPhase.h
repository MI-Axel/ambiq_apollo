/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModUnwrapPhase.h
****************************************************************************
*
*         Description:  Performs phase unwrapping
*
*         Copyright:	DSP Concepts, Inc., 2007 - 2012
*                       568 E. Weddell Drive, Suite 3
*                       Sunnyvale, CA 94089
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Performs phase unwrapping
 */

#ifndef _MOD_UNWRAPPHASE_H
#define _MOD_UNWRAPPHASE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_UnwrapPhase_lastPhaseIn 0x00000100
#define MASK_UnwrapPhase_lastPhaseOut 0x00000200
#define OFFSET_UnwrapPhase_lastPhaseIn 0x00000008
#define OFFSET_UnwrapPhase_lastPhaseOut 0x00000009

#define CLASSID_UNWRAPPHASE (CLASS_ID_MODBASE + 5026)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modUnwrapPhaseInstance
{
    ModuleInstanceDescriptor instance;
    float              lastPhaseIn;         // Last input sample
    float              lastPhaseOut;        // Last output sample
    
} awe_modUnwrapPhaseInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
xtern const ModClassModule awe_modUnwrapPhaseClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modUnwrapPhaseConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_UNWRAPPHASE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modUnwrapPhaseProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_UNWRAPPHASE_H

/**
 * @}
 *
 * End of file.
 */
