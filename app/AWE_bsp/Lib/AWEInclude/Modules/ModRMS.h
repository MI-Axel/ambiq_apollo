/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRMS.h
****************************************************************************
*
*     Description:  RMS detector with built-in smoothing
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
 * @brief RMS detector with built-in smoothing
 */

#ifndef _MOD_RMS_H
#define _MOD_RMS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RMS_smoothingTime 0x00000100
#define MASK_RMS_instantaneousValue 0x00000200
#define MASK_RMS_filteredValue 0x00000400
#define MASK_RMS_a1 0x00000800
#define MASK_RMS_b0 0x00001000
#define MASK_RMS_b1 0x00002000
#define MASK_RMS_xNm1 0x00004000
#define MASK_RMS_yNm1 0x00008000
#define OFFSET_RMS_smoothingTime 0x00000008
#define OFFSET_RMS_instantaneousValue 0x00000009
#define OFFSET_RMS_filteredValue 0x0000000A
#define OFFSET_RMS_a1 0x0000000B
#define OFFSET_RMS_b0 0x0000000C
#define OFFSET_RMS_b1 0x0000000D
#define OFFSET_RMS_xNm1 0x0000000E
#define OFFSET_RMS_yNm1 0x0000000F

#define CLASSID_RMS (CLASS_ID_MODBASE + 127)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRMSInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time interval over which to smooth the measurement.
    FLOAT32            instantaneousValue;  // Instantaneous (unsmoothed) output value.
    FLOAT32            filteredValue;       // Smoothed output value.
    FLOAT32            a1;                  // a1 coefficient of 1st order smoothing filter.
    FLOAT32            b0;                  // b0 coefficient of 1st order smoothing filter.
    FLOAT32            b1;                  // b1 coefficient of 1st order smoothing filter.
    FLOAT32            xNm1;                // Delayed input sample.
    FLOAT32            yNm1;                // Delayed output sample.
    
} awe_modRMSInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRMSClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRMSConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_RMS, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRMSProcess(void *pInstance);

UINT32 awe_modRMSSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RMS_H

/**
 * @}
 *
 * End of file.
 */
