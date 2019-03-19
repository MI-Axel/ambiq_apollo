/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSourceFract32.h
****************************************************************************
*
*     Description:  Source buffer holding 1 wire of fract32 data
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
 * @brief Source buffer holding 1 wire of fract32 data
 */

#ifndef _MOD_SOURCEFRACT32_H
#define _MOD_SOURCEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SourceFract32_value 0x00000100
#define OFFSET_SourceFract32_value 0x00000008

#define CLASSID_SOURCEFRACT32 (CLASS_ID_MODBASE + 199)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSourceFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    fract32*           value;               // Array of interleaved audio data
} awe_modSourceFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSourceFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSourceFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSourceFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SOURCEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
