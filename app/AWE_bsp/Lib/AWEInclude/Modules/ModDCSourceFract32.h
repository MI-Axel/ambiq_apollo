/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDCSourceFract32.h
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

#ifndef _MOD_DCSOURCEFRACT32_H
#define _MOD_DCSOURCEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DCSourceFract32_value 0x00000100
#define MASK_DCSourceFract32_valuefract32 0x00000200
#define OFFSET_DCSourceFract32_value 0x00000008
#define OFFSET_DCSourceFract32_valuefract32 0x00000009

#define CLASSID_DCSOURCEFRACT32 (CLASS_ID_MODBASE + 2004)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDCSourceFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            value;               // Data Value
    fract32            valuefract32;        // Data Value
    
} awe_modDCSourceFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDCSourceFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDCSourceFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DCSOURCEFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDCSourceFract32Process(void *pInstance);

UINT32 awe_modDCSourceFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DCSOURCEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
