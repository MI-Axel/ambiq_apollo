/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDCSourceV2.h
****************************************************************************
*
*     Description:  Outputs a constant DC value with optional input control pin to scale DC value.
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
 * @brief Outputs a constant DC value with optional input control pin to scale DC value.
 */

#ifndef _MOD_DCSOURCEV2_H
#define _MOD_DCSOURCEV2_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DCSourceV2_value 0x00000100
#define OFFSET_DCSourceV2_value 0x00000008

#define CLASSID_DCSOURCEV2 (CLASS_ID_MODBASE + 114)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDCSourceV2Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            value;               // Data Value
    
} awe_modDCSourceV2Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDCSourceV2Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDCSourceV2Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DCSOURCEV2, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDCSourceV2Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DCSOURCEV2_H

/**
 * @}
 *
 * End of file.
 */
