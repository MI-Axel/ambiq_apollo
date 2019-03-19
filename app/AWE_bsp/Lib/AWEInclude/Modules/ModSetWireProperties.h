/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSetWireProperties.h
****************************************************************************
*
*     Description:  Overrides wire properties
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
 * @brief Overrides wire properties
 */

#ifndef _MOD_SETWIREPROPERTIES_H
#define _MOD_SETWIREPROPERTIES_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SETWIREPROPERTIES (CLASS_ID_MODBASE + 1333)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSetWirePropertiesInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSetWirePropertiesInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSetWirePropertiesClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSetWirePropertiesConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SETWIREPROPERTIES, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSetWirePropertiesProcess(void *pInstance);

 

void awe_modSetWirePropertiesBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_SETWIREPROPERTIES_H

/**
 * @}
 *
 * End of file.
 */
