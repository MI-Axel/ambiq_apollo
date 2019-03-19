/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFIRLoadingFract32.h
****************************************************************************
*
*     Description:  Simulates loading of fir fract32 filter
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
 * @brief Simulates loading of fir fract32 filter
 */

#ifndef _MOD_FIRLOADINGFRACT32_H
#define _MOD_FIRLOADINGFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModFIRFract32.h"

#define MASK_FIRLoadingFract32_maxTaps 0x00000100
#define MASK_FIRLoadingFract32_numTaps 0x00000200
#define OFFSET_FIRLoadingFract32_maxTaps 0x00000008
#define OFFSET_FIRLoadingFract32_numTaps 0x00000009

#define CLASSID_FIRLOADINGFRACT32 (CLASS_ID_MODBASE + 1275)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFIRLoadingFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxTaps;             // Maximum FIR filter taps that can be run
    INT32              numTaps;             // Number of FIR filter taps currently running
        awe_modFIRFract32Instance    *filt;               // FIR fract32 filter
} awe_modFIRLoadingFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFIRLoadingFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFIRLoadingFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFIRLoadingFract32Process(void *pInstance);

UINT32 awe_modFIRLoadingFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FIRLOADINGFRACT32_H

/**
 * @}
 *
 * End of file.
 */
