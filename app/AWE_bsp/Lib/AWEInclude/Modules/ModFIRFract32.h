/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFIRFract32.h
****************************************************************************
*
*     Description:  FIR fract32 filter
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
 * @brief FIR fract32 filter
 */

#ifndef _MOD_FIRFRACT32_H
#define _MOD_FIRFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FIRFract32_numTaps 0x00000100
#define MASK_FIRFract32_stateIndex 0x00000200
#define MASK_FIRFract32_postShift 0x00000400
#define MASK_FIRFract32_coeffs 0x00000800
#define MASK_FIRFract32_coeffsfract32 0x00001000
#define MASK_FIRFract32_state 0x00002000
#define OFFSET_FIRFract32_numTaps 0x00000008
#define OFFSET_FIRFract32_stateIndex 0x00000009
#define OFFSET_FIRFract32_postShift 0x0000000A
#define OFFSET_FIRFract32_coeffs 0x0000000B
#define OFFSET_FIRFract32_coeffsfract32 0x0000000C
#define OFFSET_FIRFract32_state 0x0000000D

#define CLASSID_FIRFRACT32 (CLASS_ID_MODBASE + 142)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFIRFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              numTaps;             // Length of the filter
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              postShift;           // Number of bits to shift
    FLOAT32*           coeffs;              // Coefficient array
    fract32*           coeffsfract32;       // Coefficient array
    fract32*           state;               // State variable array
} awe_modFIRFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFIRFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFIRFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFIRFract32Process(void *pInstance);

UINT32 awe_modFIRFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FIRFRACT32_H

/**
 * @}
 *
 * End of file.
 */
