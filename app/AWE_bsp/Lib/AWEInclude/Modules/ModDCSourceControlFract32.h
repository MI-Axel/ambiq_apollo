/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDCSourceControlFract32.h
****************************************************************************
*
*     Description:  Outputs a DC signal at the value of the control signal
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
 * @brief Outputs a DC signal at the value of the control signal
 */

#ifndef _MOD_DCSOURCECONTROLFRACT32_H
#define _MOD_DCSOURCECONTROLFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DCSourceControlFract32_scaler 0x00000100
#define MASK_DCSourceControlFract32_f 0x00000200
#define MASK_DCSourceControlFract32_shift 0x00000400
#define OFFSET_DCSourceControlFract32_scaler 0x00000008
#define OFFSET_DCSourceControlFract32_f 0x00000009
#define OFFSET_DCSourceControlFract32_shift 0x0000000A

#define CLASSID_DCSOURCECONTROLFRACT32 (CLASS_ID_MODBASE + 2002)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDCSourceControlFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            scaler;              // The constant which to multipy the input value with
    fract32            f;                   // Multiplicative gain factor
    INT32              shift;               // Number of bits to shift
    
} awe_modDCSourceControlFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDCSourceControlFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDCSourceControlFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DCSOURCECONTROLFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDCSourceControlFract32Process(void *pInstance);

UINT32 awe_modDCSourceControlFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DCSOURCECONTROLFRACT32_H

/**
 * @}
 *
 * End of file.
 */
