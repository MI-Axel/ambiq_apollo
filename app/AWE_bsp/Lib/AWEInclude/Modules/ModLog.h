/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLog.h
****************************************************************************
*
*     Description:  Natural log function using the math library
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
 * @brief Natural log function using the math library
 */

#ifndef _MOD_LOG_H
#define _MOD_LOG_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_LOG (CLASS_ID_MODBASE + 53)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLogInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modLogInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLogClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modLogConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_LOG, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modLogProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_LOG_H

/**
 * @}
 *
 * End of file.
 */
