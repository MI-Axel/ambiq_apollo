/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModEmphasisFilterFract32.h
****************************************************************************
*
*     Description:  Audio pre- and de-emphasis
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
 * @brief Audio pre- and de-emphasis
 */

#ifndef _MOD_EMPHASISFILTERFRACT32_H
#define _MOD_EMPHASISFILTERFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadSmoothedFract32.h"

#define MASK_EmphasisFilterFract32_filterType 0x00000100
#define MASK_EmphasisFilterFract32_tau 0x00000200
#define OFFSET_EmphasisFilterFract32_filterType 0x00000008
#define OFFSET_EmphasisFilterFract32_tau 0x00000009

#define CLASSID_EMPHASISFILTERFRACT32 (CLASS_ID_MODBASE + 1266)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modEmphasisFilterFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              filterType;          // Specifies whether the filter implements bypass (=0) pre-emphasis (=1) or de-emphasis (=2)
    FLOAT32            tau;                 // Time constant of the filter
        awe_modBiquadSmoothedFract32Instance    *filt;               // 2nd order smoothly updating IIR filter
} awe_modEmphasisFilterFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modEmphasisFilterFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modEmphasisFilterFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modEmphasisFilterFract32Process(void *pInstance);

UINT32 awe_modEmphasisFilterFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_EMPHASISFILTERFRACT32_H

/**
 * @}
 *
 * End of file.
 */
