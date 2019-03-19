/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModButterworthFilterHP.h
****************************************************************************
*
*     Description:  Butterworth filter with high precision implementation
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
 * @brief Butterworth filter with high precision implementation
 */

#ifndef _MOD_BUTTERWORTHFILTERHP_H
#define _MOD_BUTTERWORTHFILTERHP_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadCascadeHP.h"

#define MASK_ButterworthFilterHP_filterType 0x00000100
#define MASK_ButterworthFilterHP_order 0x00000200
#define MASK_ButterworthFilterHP_cutoff 0x00000400
#define OFFSET_ButterworthFilterHP_filterType 0x00000008
#define OFFSET_ButterworthFilterHP_order 0x00000009
#define OFFSET_ButterworthFilterHP_cutoff 0x0000000A

#define CLASSID_BUTTERWORTHFILTERHP (CLASS_ID_MODBASE + 1228)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modButterworthFilterHPInstance
{
    ModuleInstanceDescriptor instance;
    INT32              filterType;          // Specifies what type of filter is designed (lowpass=0, highpass=1, allpass=2).
    INT32              order;               // Order of the filter.
    FLOAT32            cutoff;              // Cutoff frequency of the filter in Hz
        awe_modBiquadCascadeHPInstance    *filt;               // Cascade of second order Biquad filters with high precision implementation
} awe_modButterworthFilterHPInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modButterworthFilterHPClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modButterworthFilterHPConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modButterworthFilterHPProcess(void *pInstance);

UINT32 awe_modButterworthFilterHPSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BUTTERWORTHFILTERHP_H

/**
 * @}
 *
 * End of file.
 */
