/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModButterworthFilterSS.h
****************************************************************************
*
*     Description:  Butterworth filter with State Space implementation
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2015
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
 * @brief Butterworth filter with State Space implementation
 */

#ifndef _MOD_BUTTERWORTHFILTERSS_H
#define _MOD_BUTTERWORTHFILTERSS_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadCascadeSS.h"

#define MASK_ButterworthFilterSS_filterType 0x00000100
#define MASK_ButterworthFilterSS_order 0x00000200
#define MASK_ButterworthFilterSS_cutoff 0x00000400
#define OFFSET_ButterworthFilterSS_filterType 0x00000008
#define OFFSET_ButterworthFilterSS_order 0x00000009
#define OFFSET_ButterworthFilterSS_cutoff 0x0000000A

#define CLASSID_BUTTERWORTHFILTERSS (CLASS_ID_MODBASE + 3204)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modButterworthFilterSSInstance
{
    ModuleInstanceDescriptor instance;
    int                filterType;          // Specifies what type of filter is designed (lowpass=0, highpass=1, allpass=2).
    int                order;               // Order of the filter.
    float              cutoff;              // Cutoff frequency of the filter in Hz
        awe_modBiquadCascadeSSInstance    *filt;               // Cascade of second order Biquad filters with State space implementation
} awe_modButterworthFilterSSInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modButterworthFilterSSClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modButterworthFilterSSConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modButterworthFilterSSProcess(void *pInstance);

UINT32 awe_modButterworthFilterSSSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BUTTERWORTHFILTERSS_H

/**
 * @}
 *
 * End of file.
 */
