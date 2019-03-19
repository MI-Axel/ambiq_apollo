/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModClipAsym.h
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

#ifndef _MOD_CLIPASYM_H
#define _MOD_CLIPASYM_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ClipAsym_clipLower 0x00000100
#define MASK_ClipAsym_clipUpper 0x00000200
#define OFFSET_ClipAsym_clipLower 0x00000008
#define OFFSET_ClipAsym_clipUpper 0x00000009

#define CLASSID_CLIPASYM (CLASS_ID_MODBASE + 78)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modClipAsymInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            clipLower;           // Lower clipping threshold.
    FLOAT32            clipUpper;           // Upper clipping threshold.
    
} awe_modClipAsymInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modClipAsymClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modClipAsymConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_CLIPASYM, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modClipAsymProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CLIPASYM_H

/**
 * @}
 *
 * End of file.
 */
