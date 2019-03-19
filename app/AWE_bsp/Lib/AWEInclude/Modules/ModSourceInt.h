/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSourceInt.h
****************************************************************************
*
*     Description:  Source buffer holding 1 wire of integer data
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
 * @brief Source buffer holding 1 wire of integer data
 */

#ifndef _MOD_SOURCEINT_H
#define _MOD_SOURCEINT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SourceInt_value 0x00000100
#define OFFSET_SourceInt_value 0x00000008

#define CLASSID_SOURCEINT (CLASS_ID_MODBASE + 112)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSourceIntInstance
{
    ModuleInstanceDescriptor instance;
    
    INT32*             value;               // Array of interleaved audio data
} awe_modSourceIntInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSourceIntClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSourceIntConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSourceIntProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SOURCEINT_H

/**
 * @}
 *
 * End of file.
 */
