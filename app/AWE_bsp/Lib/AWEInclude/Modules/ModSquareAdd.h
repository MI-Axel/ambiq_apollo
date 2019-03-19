/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSquareAdd.h
****************************************************************************
*
*     Description:  Squares all inputs and then sums them together
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
 * @brief Squares all inputs and then sums them together
 */

#ifndef _MOD_SQUAREADD_H
#define _MOD_SQUAREADD_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SquareAdd_oneChannelOutput 0x00000100
#define OFFSET_SquareAdd_oneChannelOutput 0x00000008

#define CLASSID_SQUAREADD (CLASS_ID_MODBASE + 65)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSquareAddInstance
{
    ModuleInstanceDescriptor instance;
    INT32              oneChannelOutput;    // Boolean value to determine if multichannel output or mono output.
    
} awe_modSquareAddInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSquareAddClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSquareAddConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SQUAREADD, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSquareAddProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SQUAREADD_H

/**
 * @}
 *
 * End of file.
 */
