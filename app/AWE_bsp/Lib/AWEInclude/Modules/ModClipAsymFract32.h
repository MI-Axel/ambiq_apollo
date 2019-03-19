/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModClipAsymFract32.h
****************************************************************************
*
*     Description:  Asymmetric clipper module with separate upper and lower clipping thresholds
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
 * @brief Asymmetric clipper module with separate upper and lower clipping thresholds
 */

#ifndef _MOD_CLIPASYMFRACT32_H
#define _MOD_CLIPASYMFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ClipAsymFract32_clipLower 0x00000100
#define MASK_ClipAsymFract32_clipLowerFract32 0x00000200
#define MASK_ClipAsymFract32_clipUpper 0x00000400
#define MASK_ClipAsymFract32_clipUpperFract32 0x00000800
#define OFFSET_ClipAsymFract32_clipLower 0x00000008
#define OFFSET_ClipAsymFract32_clipLowerFract32 0x00000009
#define OFFSET_ClipAsymFract32_clipUpper 0x0000000A
#define OFFSET_ClipAsymFract32_clipUpperFract32 0x0000000B

#define CLASSID_CLIPASYMFRACT32 (CLASS_ID_MODBASE + 139)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modClipAsymFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            clipLower;           // Lower clipping threshold
    fract32            clipLowerFract32;    // Lower clipping threshold in fract32 form
    FLOAT32            clipUpper;           // Upper clipping threshold
    fract32            clipUpperFract32;    // Upper clipping threshold in fract32 form
    
} awe_modClipAsymFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modClipAsymFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modClipAsymFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_CLIPASYMFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modClipAsymFract32Process(void *pInstance);

UINT32 awe_modClipAsymFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CLIPASYMFRACT32_H

/**
 * @}
 *
 * End of file.
 */
