/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerFract32.h
****************************************************************************
*
*     Description:  Linear multichannel scaler
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
 * @brief Linear multichannel scaler
 */

#ifndef _MOD_SCALERFRACT32_H
#define _MOD_SCALERFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerFract32_gain 0x00000100
#define MASK_ScalerFract32_f 0x00000200
#define MASK_ScalerFract32_shift 0x00000400
#define OFFSET_ScalerFract32_gain 0x00000008
#define OFFSET_ScalerFract32_f 0x00000009
#define OFFSET_ScalerFract32_shift 0x0000000A

#define CLASSID_SCALERFRACT32 (CLASS_ID_MODBASE + 187)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Linear gain
    fract32            f;                   // Multiplicative gain factor
    INT32              shift;               // Number of bits to shift
    
} awe_modScalerFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScalerFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALERFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerFract32Process(void *pInstance);

UINT32 awe_modScalerFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERFRACT32_H

/**
 * @}
 *
 * End of file.
 */
