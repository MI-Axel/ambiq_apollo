/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModButterworthFilter40.h
****************************************************************************
*
*     Description:  Butterworth filter with 40-bit internal processing
*
*     Copyright:	   DSP Concepts, Inc., 2007 - 2015
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Butterworth filter with 40-bit internal processing
 */

#ifndef _MOD_BUTTERWORTHFILTER40_H
#define _MOD_BUTTERWORTHFILTER40_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ButterworthFilter40_filterType 0x00000100
#define MASK_ButterworthFilter40_order 0x00000200
#define MASK_ButterworthFilter40_cutoff 0x00000400
#define MASK_ButterworthFilter40_updateActive 0x00000800
#define MASK_ButterworthFilter40_coeffs 0x00001000
#define MASK_ButterworthFilter40_state 0x00002000
#define MASK_ButterworthFilter40_currentCoeffs 0x00004000
#define OFFSET_ButterworthFilter40_filterType 0x00000008
#define OFFSET_ButterworthFilter40_order 0x00000009
#define OFFSET_ButterworthFilter40_cutoff 0x0000000A
#define OFFSET_ButterworthFilter40_updateActive 0x0000000B
#define OFFSET_ButterworthFilter40_coeffs 0x0000000C
#define OFFSET_ButterworthFilter40_state 0x0000000D
#define OFFSET_ButterworthFilter40_currentCoeffs 0x0000000E

#define CLASSID_BUTTERWORTHFILTER40 (CLASS_ID_MODBASE + 5300)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modButterworthFilter40Instance
{
    ModuleInstanceDescriptor instance;
    int                filterType;          // Specifies what type of filter is designed (lowpass=0, highpass=1, allpass=2)
    int                order;               // Order of the filter
    float              cutoff;              // Cutoff frequency of the filter
    int                updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0)
    float*             coeffs;              // Coefficients Array.  5 for each stage.
    float*             state;               // State variables.  2 per channel.
    float*             currentCoeffs;       // Current coefficients Array.  5 for each stage.
} awe_modButterworthFilter40Instance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if (!defined(AWE_NO_CLASS_OBJECTS) || !defined(AWE_STATIC_CODE))
extern const ModClassModule awe_modButterworthFilter40Class;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modButterworthFilter40Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modButterworthFilter40Process(void *pInstance);

UINT32 awe_modButterworthFilter40Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BUTTERWORTHFILTER40_H

/**
 * @}
 *
 * End of file.
 */
