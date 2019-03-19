/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScaleOffsetInt32.h
****************************************************************************
*
*     Description:  Scales a signal by integer gain and then adds an integer offset
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
 * @brief Scales a signal by integer gain and then adds an integer offset
 */

#ifndef _MOD_SCALEOFFSETINT32_H
#define _MOD_SCALEOFFSETINT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScaleOffsetInt32_gain 0x00000100
#define MASK_ScaleOffsetInt32_offset 0x00000200
#define OFFSET_ScaleOffsetInt32_gain 0x00000008
#define OFFSET_ScaleOffsetInt32_offset 0x00000009

#define CLASSID_SCALEOFFSETINT32 (CLASS_ID_MODBASE + 205)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScaleOffsetInt32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              gain;                // Linear integer scale factor.
    INT32              offset;              // DC offset.
    
} awe_modScaleOffsetInt32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScaleOffsetInt32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScaleOffsetInt32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALEOFFSETINT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScaleOffsetInt32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALEOFFSETINT32_H

/**
 * @}
 *
 * End of file.
 */
