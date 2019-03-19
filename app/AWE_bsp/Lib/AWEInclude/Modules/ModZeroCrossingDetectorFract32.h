/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModZeroCrossingDetectorFract32.h
****************************************************************************
*
*     Description:  Zero crossing detector
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
 * @brief Zero crossing detector
 */

#ifndef _MOD_ZEROCROSSINGDETECTORFRACT32_H
#define _MOD_ZEROCROSSINGDETECTORFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ZeroCrossingDetectorFract32_detectorType 0x00000100
#define MASK_ZeroCrossingDetectorFract32_lastSign 0x00000200
#define OFFSET_ZeroCrossingDetectorFract32_detectorType 0x00000008
#define OFFSET_ZeroCrossingDetectorFract32_lastSign 0x00000009

#define CLASSID_ZEROCROSSINGDETECTORFRACT32 (CLASS_ID_MODBASE + 217)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modZeroCrossingDetectorFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              detectorType;        // Determines which zero crossings are detected.  0=all, >0 negative->positive, <0 positive->negative
    INT32*             lastSign;            // Holds the sign of the last input value.  This is an array so that multiple channels can be supported.
} awe_modZeroCrossingDetectorFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modZeroCrossingDetectorFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modZeroCrossingDetectorFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modZeroCrossingDetectorFract32Process(void *pInstance);

 

void awe_modZeroCrossingDetectorFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_ZEROCROSSINGDETECTORFRACT32_H

/**
 * @}
 *
 * End of file.
 */
