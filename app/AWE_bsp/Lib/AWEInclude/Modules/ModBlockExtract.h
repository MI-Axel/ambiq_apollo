/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBlockExtract.h
****************************************************************************
*
*     Description:  Extracts a range of samples from a block of data. Can also zero pad the signal at the start or end.
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
 * @brief Extracts a range of samples from a block of data. Can also zero pad the signal at the start or end.
 */

#ifndef _MOD_BLOCKEXTRACT_H
#define _MOD_BLOCKEXTRACT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BlockExtract_startIndex 0x00000100
#define MASK_BlockExtract_endIndex 0x00000200
#define OFFSET_BlockExtract_startIndex 0x00000008
#define OFFSET_BlockExtract_endIndex 0x00000009

#define CLASSID_BLOCKEXTRACT (CLASS_ID_MODBASE + 1223)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBlockExtractInstance
{
    ModuleInstanceDescriptor instance;
    INT32              startIndex;          // Start index of the data to extract.
    INT32              endIndex;            // End index of the data to extract.
    
} awe_modBlockExtractInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBlockExtractClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBlockExtractConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BLOCKEXTRACT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBlockExtractProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BLOCKEXTRACT_H

/**
 * @}
 *
 * End of file.
 */
