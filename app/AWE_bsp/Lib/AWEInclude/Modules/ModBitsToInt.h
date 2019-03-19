/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBitsToInt.h
****************************************************************************
*
*     Description:  Converts multiple binary bits to an integer value
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
 * @brief Converts multiple binary bits to an integer value
 */

#ifndef _MOD_BITSTOINT_H
#define _MOD_BITSTOINT_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_BITSTOINT (CLASS_ID_MODBASE + 31)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBitsToIntInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modBitsToIntInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBitsToIntClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBitsToIntConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BITSTOINT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBitsToIntProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BITSTOINT_H

/**
 * @}
 *
 * End of file.
 */
