/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBooleanSource.h
****************************************************************************
*
*     Description:  Source buffer holding 1 wire of data
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
 * @brief Source buffer holding 1 wire of data
 */

#ifndef _MOD_BOOLEANSOURCE_H
#define _MOD_BOOLEANSOURCE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BooleanSource_value 0x00000100
#define OFFSET_BooleanSource_value 0x00000008

#define CLASSID_BOOLEANSOURCE (CLASS_ID_MODBASE + 113)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBooleanSourceInstance
{
    ModuleInstanceDescriptor instance;
    
    INT32*             value;               // Array of interleaved audio real data.
} awe_modBooleanSourceInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBooleanSourceClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBooleanSourceConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBooleanSourceProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BOOLEANSOURCE_H

/**
 * @}
 *
 * End of file.
 */
