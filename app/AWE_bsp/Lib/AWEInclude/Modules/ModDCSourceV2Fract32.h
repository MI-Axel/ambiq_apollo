/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDCSourceV2Fract32.h
****************************************************************************
*
*     Description:  Source buffer holding 1 wire of constant data with optional input control pin to scale DC value
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
 * @brief Source buffer holding 1 wire of constant data with optional input control pin to scale DC value
 */

#ifndef _MOD_DCSOURCEV2FRACT32_H
#define _MOD_DCSOURCEV2FRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DCSourceV2Fract32_value 0x00000100
#define MASK_DCSourceV2Fract32_valuefract32 0x00000200
#define OFFSET_DCSourceV2Fract32_value 0x00000008
#define OFFSET_DCSourceV2Fract32_valuefract32 0x00000009

#define CLASSID_DCSOURCEV2FRACT32 (CLASS_ID_MODBASE + 140)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDCSourceV2Fract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            value;               // Data Value
    fract32            valuefract32;        // Data Value
    
} awe_modDCSourceV2Fract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDCSourceV2Fract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDCSourceV2Fract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DCSOURCEV2FRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDCSourceV2Fract32Process(void *pInstance);

UINT32 awe_modDCSourceV2Fract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DCSOURCEV2FRACT32_H

/**
 * @}
 *
 * End of file.
 */
