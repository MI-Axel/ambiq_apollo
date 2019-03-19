/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScaleOffset.h
****************************************************************************
*
*     Description:  Scales a signal and then adds an offset
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
 * @brief Scales a signal and then adds an offset
 */

#ifndef _MOD_SCALEOFFSET_H
#define _MOD_SCALEOFFSET_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScaleOffset_gain 0x00000100
#define MASK_ScaleOffset_offset 0x00000200
#define OFFSET_ScaleOffset_gain 0x00000008
#define OFFSET_ScaleOffset_offset 0x00000009

#define CLASSID_SCALEOFFSET (CLASS_ID_MODBASE + 23)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScaleOffsetInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Linear gain.
    FLOAT32            offset;              // DC offset.
    
} awe_modScaleOffsetInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScaleOffsetClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScaleOffsetConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALEOFFSET, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScaleOffsetProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALEOFFSET_H

/**
 * @}
 *
 * End of file.
 */
