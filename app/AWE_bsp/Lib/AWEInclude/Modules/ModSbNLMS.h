/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSbNLMS.h
****************************************************************************
*
*     Description:  Subband normalized LMS adaptive filter
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
 * @brief Subband normalized LMS adaptive filter
 */

#ifndef _MOD_SBNLMS_H
#define _MOD_SBNLMS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SbNLMS_maxTaps 0x00000100
#define MASK_SbNLMS_numTaps 0x00000200
#define MASK_SbNLMS_mu 0x00000400
#define MASK_SbNLMS_offset 0x00000800
#define MASK_SbNLMS_stateIndex 0x00001000
#define MASK_SbNLMS_coeffs 0x00002000
#define MASK_SbNLMS_state 0x00004000
#define OFFSET_SbNLMS_maxTaps 0x00000008
#define OFFSET_SbNLMS_numTaps 0x00000009
#define OFFSET_SbNLMS_mu 0x0000000A
#define OFFSET_SbNLMS_offset 0x0000000B
#define OFFSET_SbNLMS_stateIndex 0x0000000C
#define OFFSET_SbNLMS_coeffs 0x0000000D
#define OFFSET_SbNLMS_state 0x0000000E

#define CLASSID_SBNLMS (CLASS_ID_MODBASE + 1325)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSbNLMSInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxTaps;             // Maximum length of the filter
    INT32              numTaps;             // Current length of the filter
    FLOAT32            mu;                  // Adaptation constant
    FLOAT32            offset;              // Normalization offset constant
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    FLOAT32*           coeffs;              // Coefficient array
    FLOAT32*           state;               // State variable array
} awe_modSbNLMSInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSbNLMSClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSbNLMSConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSbNLMSProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SBNLMS_H

/**
 * @}
 *
 * End of file.
 */
