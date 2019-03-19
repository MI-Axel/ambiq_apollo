/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLMSNormFract32.h
****************************************************************************
*
*     Description:  LMS Norm fract32 filter
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
 * @brief LMS Norm fract32 filter
 */

#ifndef _MOD_LMSNORMFRACT32_H
#define _MOD_LMSNORMFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_LMSNormFract32_numTaps 0x00000100
#define MASK_LMSNormFract32_mu 0x00000200
#define MASK_LMSNormFract32_stateIndex 0x00000400
#define MASK_LMSNormFract32_prev_stateptr 0x00000800
#define MASK_LMSNormFract32_postShift 0x00001000
#define MASK_LMSNormFract32_mufract32 0x00002000
#define MASK_LMSNormFract32_E 0x00004000
#define MASK_LMSNormFract32_x0 0x00008000
#define MASK_LMSNormFract32_coeffs 0x00010000
#define MASK_LMSNormFract32_coeffsfract32 0x00020000
#define MASK_LMSNormFract32_state 0x00040000
#define OFFSET_LMSNormFract32_numTaps 0x00000008
#define OFFSET_LMSNormFract32_mu 0x00000009
#define OFFSET_LMSNormFract32_stateIndex 0x0000000A
#define OFFSET_LMSNormFract32_prev_stateptr 0x0000000B
#define OFFSET_LMSNormFract32_postShift 0x0000000C
#define OFFSET_LMSNormFract32_mufract32 0x0000000D
#define OFFSET_LMSNormFract32_E 0x0000000E
#define OFFSET_LMSNormFract32_x0 0x0000000F
#define OFFSET_LMSNormFract32_coeffs 0x00000010
#define OFFSET_LMSNormFract32_coeffsfract32 0x00000011
#define OFFSET_LMSNormFract32_state 0x00000012

#define CLASSID_LMSNORMFRACT32 (CLASS_ID_MODBASE + 1293)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLMSNormFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              numTaps;             // Length of the filter
    FLOAT32            mu;                  // mu Step size
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              prev_stateptr;       // Index of the oldest state variable in the array of state variables
    INT32              postShift;           // Number of bits to shift
    fract32            mufract32;           // mu Step size
    fract32            E;                   // saves previous frame energy
    fract32            x0;                  // saves previous input sample
    FLOAT32*           coeffs;              // Coefficient array
    fract32*           coeffsfract32;       // Coefficient array
    fract32*           state;               // State variable array
} awe_modLMSNormFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLMSNormFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modLMSNormFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modLMSNormFract32Process(void *pInstance);

UINT32 awe_modLMSNormFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_LMSNORMFRACT32_H

/**
 * @}
 *
 * End of file.
 */
