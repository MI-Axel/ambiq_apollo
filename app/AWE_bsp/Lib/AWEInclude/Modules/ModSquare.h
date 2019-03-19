/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSquare.h
****************************************************************************
*
*     Description:  Squares samples
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
 * @brief Squares samples
 */

#ifndef _MOD_SQUARE_H
#define _MOD_SQUARE_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SQUARE (CLASS_ID_MODBASE + 64)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSquareInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSquareInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSquareClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSquareConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SQUARE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSquareProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SQUARE_H

/**
 * @}
 *
 * End of file.
 */
