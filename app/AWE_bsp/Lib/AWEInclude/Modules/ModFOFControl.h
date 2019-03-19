/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFOFControl.h
****************************************************************************
*
*     Description:  Time varying 1st order filter controlled using an input pin.
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
 * @brief Time varying 1st order filter controlled using an input pin.
 */

#ifndef _MOD_FOFCONTROL_H
#define _MOD_FOFCONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FOFControl_smoothingTime 0x00000100
#define MASK_FOFControl_filterType 0x00000200
#define MASK_FOFControl_smoothingCoeff 0x00000400
#define MASK_FOFControl_currentA1 0x00000800
#define MASK_FOFControl_coeffs 0x00001000
#define MASK_FOFControl_state 0x00002000
#define OFFSET_FOFControl_smoothingTime 0x00000008
#define OFFSET_FOFControl_filterType 0x00000009
#define OFFSET_FOFControl_smoothingCoeff 0x0000000A
#define OFFSET_FOFControl_currentA1 0x0000000B
#define OFFSET_FOFControl_coeffs 0x0000000C
#define OFFSET_FOFControl_state 0x0000000D

#define CLASSID_FOFCONTROL (CLASS_ID_MODBASE + 1282)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFOFControlInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    INT32              filterType;          // LPF = 0 and HPF = 1
    FLOAT32            smoothingCoeff;      // Smoothing coefficient
    FLOAT32            currentA1;           // Instantaneous a1 filter coefficient
    FLOAT32*           coeffs;              // coefficients
    FLOAT32*           state;               // State variables.  4 per channel
} awe_modFOFControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFOFControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFOFControlConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFOFControlProcess(void *pInstance);

UINT32 awe_modFOFControlSet(void *pInstance, UINT32 mask);
 

void awe_modFOFControlBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_FOFCONTROL_H

/**
 * @}
 *
 * End of file.
 */
