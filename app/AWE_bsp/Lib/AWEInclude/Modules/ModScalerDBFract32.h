/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerDBFract32.h
****************************************************************************
*
*     Description:  DB Fract32 multichannel scaler
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
 * @brief DB Fract32 multichannel scaler
 */

#ifndef _MOD_SCALERDBFRACT32_H
#define _MOD_SCALERDBFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerDBFract32_gainDB 0x00000100
#define MASK_ScalerDBFract32_gainFract32 0x00000200
#define MASK_ScalerDBFract32_shift 0x00000400
#define OFFSET_ScalerDBFract32_gainDB 0x00000008
#define OFFSET_ScalerDBFract32_gainFract32 0x00000009
#define OFFSET_ScalerDBFract32_shift 0x0000000A

#define CLASSID_SCALERDBFRACT32 (CLASS_ID_MODBASE + 185)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerDBFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gainDB;              // Gain in DB
    fract32            gainFract32;         // Gain in fract32 linear units
    INT32              shift;               // Number of bits to shift
    
} awe_modScalerDBFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerDBFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScalerDBFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALERDBFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerDBFract32Process(void *pInstance);

UINT32 awe_modScalerDBFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERDBFRACT32_H

/**
 * @}
 *
 * End of file.
 */
