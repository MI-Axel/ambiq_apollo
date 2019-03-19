/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquad.h
****************************************************************************
*
*     Description:  2nd order IIR filter
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
 * @brief 2nd order IIR filter
 */

#ifndef _MOD_BIQUAD_H
#define _MOD_BIQUAD_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Biquad_b0 0x00000100
#define MASK_Biquad_b1 0x00000200
#define MASK_Biquad_b2 0x00000400
#define MASK_Biquad_a1 0x00000800
#define MASK_Biquad_a2 0x00001000
#define MASK_Biquad_state 0x00002000
#define OFFSET_Biquad_b0 0x00000008
#define OFFSET_Biquad_b1 0x00000009
#define OFFSET_Biquad_b2 0x0000000A
#define OFFSET_Biquad_a1 0x0000000B
#define OFFSET_Biquad_a2 0x0000000C
#define OFFSET_Biquad_state 0x0000000D

#define CLASSID_BIQUAD (CLASS_ID_MODBASE + 10)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            b0;                  // First numerator coefficient.
    FLOAT32            b1;                  // Second numerator coefficient.
    FLOAT32            b2;                  // Third numerator coefficient.
    FLOAT32            a1;                  // Second denominator coefficient.
    FLOAT32            a2;                  // Third denominator coefficient.
    FLOAT32*           state;               // State variables. 2 per channel.
} awe_modBiquadInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUAD_H

/**
 * @}
 *
 * End of file.
 */
