/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerNFract32.h
****************************************************************************
*
*     Description:  Linear scaler Fract32 with independent gains
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
 * @brief Linear scaler Fract32 with independent gains
 */

#ifndef _MOD_SCALERNFRACT32_H
#define _MOD_SCALERNFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerNFract32_shift 0x00000100
#define MASK_ScalerNFract32_gain 0x00000200
#define MASK_ScalerNFract32_gainFract32 0x00000400
#define OFFSET_ScalerNFract32_shift 0x00000008
#define OFFSET_ScalerNFract32_gain 0x00000009
#define OFFSET_ScalerNFract32_gainFract32 0x0000000A

#define CLASSID_SCALERNFRACT32 (CLASS_ID_MODBASE + 190)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerNFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              shift;               // Number of bits to shift
    FLOAT32*           gain;                // Array of gains, one per channel
    fract32*           gainFract32;         // Array of gains, one per channel in fract32 format
} awe_modScalerNFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerNFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modScalerNFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerNFract32Process(void *pInstance);

UINT32 awe_modScalerNFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERNFRACT32_H

/**
 * @}
 *
 * End of file.
 */
