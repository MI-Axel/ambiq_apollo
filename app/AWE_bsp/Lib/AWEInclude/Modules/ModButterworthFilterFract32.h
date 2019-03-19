/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModButterworthFilterFract32.h
****************************************************************************
*
*     Description:  Butterworth filter
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
 * @brief Butterworth filter
 */

#ifndef _MOD_BUTTERWORTHFILTERFRACT32_H
#define _MOD_BUTTERWORTHFILTERFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadCascadeFract32.h"

#define MASK_ButterworthFilterFract32_filterType 0x00000100
#define MASK_ButterworthFilterFract32_order 0x00000200
#define MASK_ButterworthFilterFract32_cutoff 0x00000400
#define OFFSET_ButterworthFilterFract32_filterType 0x00000008
#define OFFSET_ButterworthFilterFract32_order 0x00000009
#define OFFSET_ButterworthFilterFract32_cutoff 0x0000000A

#define CLASSID_BUTTERWORTHFILTERFRACT32 (CLASS_ID_MODBASE + 135)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modButterworthFilterFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              filterType;          // Specifies what type of filter is designed (lowpass=0, highpass=1, allpass=2)
    INT32              order;               // Order of the filter
    FLOAT32            cutoff;              // Cutoff frequency of the filter
        awe_modBiquadCascadeFract32Instance    *filt;               // Cascade of second order Biquad filters
} awe_modButterworthFilterFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modButterworthFilterFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modButterworthFilterFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modButterworthFilterFract32Process(void *pInstance);

UINT32 awe_modButterworthFilterFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BUTTERWORTHFILTERFRACT32_H

/**
 * @}
 *
 * End of file.
 */
