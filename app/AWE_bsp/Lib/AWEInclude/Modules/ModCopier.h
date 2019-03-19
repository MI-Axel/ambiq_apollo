/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModCopier.h
****************************************************************************
*
*     Description:  Copies input wire to output wire
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
 * @brief Copies input wire to output wire
 */

#ifndef _MOD_COPIER_H
#define _MOD_COPIER_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_COPIER (CLASS_ID_MODBASE + 96)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCopierInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modCopierInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modCopierClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modCopierConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COPIER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modCopierProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_COPIER_H

/**
 * @}
 *
 * End of file.
 */
