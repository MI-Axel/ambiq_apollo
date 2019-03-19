/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDCSourceInt.h
****************************************************************************
*
*     Description:  Source buffer holding 1 wire of constant data
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
 * @brief Source buffer holding 1 wire of constant data
 */

#ifndef _MOD_DCSOURCEINT_H
#define _MOD_DCSOURCEINT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DCSourceInt_value 0x00000100
#define OFFSET_DCSourceInt_value 0x00000008

#define CLASSID_DCSOURCEINT (CLASS_ID_MODBASE + 115)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDCSourceIntInstance
{
    ModuleInstanceDescriptor instance;
    INT32              value;               // Data Value
    
} awe_modDCSourceIntInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDCSourceIntClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDCSourceIntConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DCSOURCEINT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDCSourceIntProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DCSOURCEINT_H

/**
 * @}
 *
 * End of file.
 */
