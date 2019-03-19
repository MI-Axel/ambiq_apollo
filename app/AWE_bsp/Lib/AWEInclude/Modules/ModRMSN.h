/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRMSN.h
****************************************************************************
*
*     Description:  Multichannel RMS detector with built-in smoothing
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
 * @brief Multichannel RMS detector with built-in smoothing
 */

#ifndef _MOD_RMSN_H
#define _MOD_RMSN_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RMSN_smoothingTime 0x00000100
#define MASK_RMSN_a1 0x00000200
#define MASK_RMSN_b0 0x00000400
#define MASK_RMSN_energy 0x00000800
#define OFFSET_RMSN_smoothingTime 0x00000008
#define OFFSET_RMSN_a1 0x00000009
#define OFFSET_RMSN_b0 0x0000000A
#define OFFSET_RMSN_energy 0x0000000B

#define CLASSID_RMSN (CLASS_ID_MODBASE + 218)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRMSNInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time interval over which to smooth the measurement.
    FLOAT32            a1;                  // a1 coefficient of 1st order smoothing filter.
    FLOAT32            b0;                  // b0 coefficient of 1st order smoothing filter.
    FLOAT32*           energy;              // Array of squared energy values, one per channel.
} awe_modRMSNInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRMSNClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modRMSNConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modRMSNProcess(void *pInstance);

UINT32 awe_modRMSNSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RMSN_H

/**
 * @}
 *
 * End of file.
 */
