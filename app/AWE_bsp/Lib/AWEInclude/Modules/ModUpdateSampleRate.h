/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModUpdateSampleRate.h
****************************************************************************
*
*     Description:  Updates the sample rate of each module wire in the system
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
 * @brief Updates the sample rate of each module wire in the system
 */

#ifndef _MOD_UPDATESAMPLERATE_H
#define _MOD_UPDATESAMPLERATE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_UpdateSampleRate_sampleRate 0x00000100
#define MASK_UpdateSampleRate_initialSampleRate 0x00000200
#define MASK_UpdateSampleRate_updateActive 0x00000400
#define MASK_UpdateSampleRate_wireSR 0x00000800
#define OFFSET_UpdateSampleRate_sampleRate 0x00000008
#define OFFSET_UpdateSampleRate_initialSampleRate 0x00000009
#define OFFSET_UpdateSampleRate_updateActive 0x0000000A
#define OFFSET_UpdateSampleRate_wireSR 0x0000000B

#define CLASSID_UPDATESAMPLERATE (CLASS_ID_MODBASE + 1350)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modUpdateSampleRateInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            sampleRate;          // Desired sample rate
    FLOAT32            initialSampleRate;   // Default sample rate of the system. Updated during the construction time.
    INT32              updateActive;        // Flag to control the state of the boolean output pin.
    FLOAT32*           wireSR;              // Array of all modules wire sample rate info
} awe_modUpdateSampleRateInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modUpdateSampleRateClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modUpdateSampleRateConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modUpdateSampleRateProcess(void *pInstance);

UINT32 awe_modUpdateSampleRateSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_UPDATESAMPLERATE_H

/**
 * @}
 *
 * End of file.
 */
