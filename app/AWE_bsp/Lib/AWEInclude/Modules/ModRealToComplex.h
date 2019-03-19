/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRealToComplex.h
****************************************************************************
*
*     Description:  Converts two real signals to a complex interleaved representation
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2015
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
 * @brief Converts two real signals to a complex interleaved representation
 */

#ifndef _MOD_REALTOCOMPLEX_H
#define _MOD_REALTOCOMPLEX_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_REALTOCOMPLEX (CLASS_ID_MODBASE + 1413)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRealToComplexInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modRealToComplexInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRealToComplexClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRealToComplexConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_REALTOCOMPLEX, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRealToComplexProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_REALTOCOMPLEX_H

/**
 * @}
 *
 * End of file.
 */
