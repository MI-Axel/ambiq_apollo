/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLMS.h
****************************************************************************
*
*     Description:  Normalized LMS FIR filter
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
 * @brief Normalized LMS FIR filter
 */

#ifndef _MOD_LMS_H
#define _MOD_LMS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_LMS_maxTaps 0x00000100
#define MASK_LMS_numTaps 0x00000200
#define MASK_LMS_mu 0x00000400
#define MASK_LMS_stateIndex 0x00000800
#define MASK_LMS_coeffs 0x00001000
#define MASK_LMS_state 0x00002000
#define OFFSET_LMS_maxTaps 0x00000008
#define OFFSET_LMS_numTaps 0x00000009
#define OFFSET_LMS_mu 0x0000000A
#define OFFSET_LMS_stateIndex 0x0000000B
#define OFFSET_LMS_coeffs 0x0000000C
#define OFFSET_LMS_state 0x0000000D

#define CLASSID_LMS (CLASS_ID_MODBASE + 1292)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLMSInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxTaps;             // Maximum length of the filter
    INT32              numTaps;             // Current length of the filter
    FLOAT32            mu;                  // Adaptation constant
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    FLOAT32*           coeffs;              // Coefficient array
    FLOAT32*           state;               // State variable array
} awe_modLMSInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLMSClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modLMSConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modLMSProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_LMS_H

/**
 * @}
 *
 * End of file.
 */
