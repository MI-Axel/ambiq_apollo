/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFOFControlFract32.h
****************************************************************************
*
*     Description:  Time varying 1st order filter controlled using an input pin.
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
 * @brief Time varying 1st order filter controlled using an input pin.
 */

#ifndef _MOD_FOFCONTROLFRACT32_H
#define _MOD_FOFCONTROLFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FOFControlFract32_smoothingTime 0x00000100
#define MASK_FOFControlFract32_filterType 0x00000200
#define MASK_FOFControlFract32_postShift 0x00000400
#define MASK_FOFControlFract32_smoothingCoeff 0x00000800
#define MASK_FOFControlFract32_currentA1 0x00001000
#define MASK_FOFControlFract32_targetA1 0x00002000
#define MASK_FOFControlFract32_coeffs 0x00004000
#define MASK_FOFControlFract32_state 0x00008000
#define OFFSET_FOFControlFract32_smoothingTime 0x00000008
#define OFFSET_FOFControlFract32_filterType 0x00000009
#define OFFSET_FOFControlFract32_postShift 0x0000000A
#define OFFSET_FOFControlFract32_smoothingCoeff 0x0000000B
#define OFFSET_FOFControlFract32_currentA1 0x0000000C
#define OFFSET_FOFControlFract32_targetA1 0x0000000D
#define OFFSET_FOFControlFract32_coeffs 0x0000000E
#define OFFSET_FOFControlFract32_state 0x0000000F

#define CLASSID_FOFCONTROLFRACT32 (CLASS_ID_MODBASE + 1281)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFOFControlFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    INT32              filterType;          // LPF = 0 and HPF = 1
    INT32              postShift;           // Number of bits to shift
    fract32            smoothingCoeff;      // Smoothing coefficient
    fract32            currentA1;           // Instantaneous a1 filter coefficient
    fract32            targetA1;            // Instantaneous a1 filter coefficient
    fract32*           coeffs;              // coefficients
    fract32*           state;               // State variables.  4 per channel
} awe_modFOFControlFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFOFControlFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFOFControlFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFOFControlFract32Process(void *pInstance);

UINT32 awe_modFOFControlFract32Set(void *pInstance, UINT32 mask);
 

void awe_modFOFControlFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_FOFCONTROLFRACT32_H

/**
 * @}
 *
 * End of file.
 */
