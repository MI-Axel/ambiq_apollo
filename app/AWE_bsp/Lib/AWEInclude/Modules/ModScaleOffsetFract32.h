/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScaleOffsetFract32.h
****************************************************************************
*
*     Description:  Linear multichannel scale and offset
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
 * @brief Linear multichannel scale and offset
 */

#ifndef _MOD_SCALEOFFSETFRACT32_H
#define _MOD_SCALEOFFSETFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScaleOffsetFract32_gain 0x00000100
#define MASK_ScaleOffsetFract32_offset 0x00000200
#define MASK_ScaleOffsetFract32_offsetFract32 0x00000400
#define MASK_ScaleOffsetFract32_gainFract32 0x00000800
#define MASK_ScaleOffsetFract32_shift 0x00001000
#define OFFSET_ScaleOffsetFract32_gain 0x00000008
#define OFFSET_ScaleOffsetFract32_offset 0x00000009
#define OFFSET_ScaleOffsetFract32_offsetFract32 0x0000000A
#define OFFSET_ScaleOffsetFract32_gainFract32 0x0000000B
#define OFFSET_ScaleOffsetFract32_shift 0x0000000C

#define CLASSID_SCALEOFFSETFRACT32 (CLASS_ID_MODBASE + 184)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScaleOffsetFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Linear gain
    FLOAT32            offset;              // DC offset
    fract32            offsetFract32;       // DC offset Fract32
    fract32            gainFract32;         // Linear gain Fract32
    INT32              shift;               // Number of bits to shift
    
} awe_modScaleOffsetFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScaleOffsetFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScaleOffsetFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALEOFFSETFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScaleOffsetFract32Process(void *pInstance);

UINT32 awe_modScaleOffsetFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALEOFFSETFRACT32_H

/**
 * @}
 *
 * End of file.
 */
