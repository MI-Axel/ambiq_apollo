/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModComplexModulate.h
****************************************************************************
*
*     Description:  This module accepts a real or complex input and generates a complex
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
 * @brief This module accepts a real or complex input and generates a complex
 */

#ifndef _MOD_COMPLEXMODULATE_H
#define _MOD_COMPLEXMODULATE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ComplexModulate_modBin 0x00000100
#define MASK_ComplexModulate_modCoeffs 0x00000200
#define OFFSET_ComplexModulate_modBin 0x00000008
#define OFFSET_ComplexModulate_modCoeffs 0x00000009

#define CLASSID_COMPLEXMODULATE (CLASS_ID_MODBASE + 1237)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modComplexModulateInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            modBin;              // Omega of modulation coefficient equation.
    FLOAT32*           modCoeffs;           // Modulation coefficient array
} awe_modComplexModulateInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modComplexModulateClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modComplexModulateConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modComplexModulateProcess(void *pInstance);

UINT32 awe_modComplexModulateSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_COMPLEXMODULATE_H

/**
 * @}
 *
 * End of file.
 */
