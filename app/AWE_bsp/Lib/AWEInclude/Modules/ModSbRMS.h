/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSbRMS.h
****************************************************************************
*
*     Description:  Subband RMS detector
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
 * @brief Subband RMS detector
 */

#ifndef _MOD_SBRMS_H
#define _MOD_SBRMS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SbRMS_smoothingTime 0x00000100
#define MASK_SbRMS_a1 0x00000200
#define MASK_SbRMS_b0 0x00000400
#define MASK_SbRMS_yNm1 0x00000800
#define OFFSET_SbRMS_smoothingTime 0x00000008
#define OFFSET_SbRMS_a1 0x00000009
#define OFFSET_SbRMS_b0 0x0000000A
#define OFFSET_SbRMS_yNm1 0x0000000B

#define CLASSID_SBRMS (CLASS_ID_MODBASE + 1326)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSbRMSInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time interval over which to smooth the measurement.
    FLOAT32            a1;                  // a1 coefficient of 1st order smoothing filter.
    FLOAT32            b0;                  // b0 coefficient of 1st order smoothing filter.
    FLOAT32*           yNm1;                // Delayed output vector.
} awe_modSbRMSInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSbRMSClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSbRMSConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSbRMSProcess(void *pInstance);

UINT32 awe_modSbRMSSet(void *pInstance, UINT32 mask);
 

void awe_modSbRMSBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_SBRMS_H

/**
 * @}
 *
 * End of file.
 */
