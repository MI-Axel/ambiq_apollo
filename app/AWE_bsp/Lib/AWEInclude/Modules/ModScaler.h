/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScaler.h
****************************************************************************
*
*     Description:  Gain control with linear units and no smoothing
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
 * @brief Gain control with linear units and no smoothing
 */

#ifndef _MOD_SCALER_H
#define _MOD_SCALER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Scaler_gain 0x00000100
#define OFFSET_Scaler_gain 0x00000008

#define CLASSID_SCALER (CLASS_ID_MODBASE + 2038)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Gain in linear units.
    
} awe_modScalerInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScalerConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALER_H

/**
 * @}
 *
 * End of file.
 */
