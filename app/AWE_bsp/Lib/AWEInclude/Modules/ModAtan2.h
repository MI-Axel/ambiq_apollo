/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAtan2.h
****************************************************************************
*
*     Description:  Computes the funtion atan2(y, x) using the math library
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
 * @brief Computes the funtion atan2(y, x) using the math library
 */

#ifndef _MOD_ATAN2_H
#define _MOD_ATAN2_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_ATAN2 (CLASS_ID_MODBASE + 84)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAtan2Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modAtan2Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAtan2Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAtan2Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_ATAN2, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAtan2Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ATAN2_H

/**
 * @}
 *
 * End of file.
 */
