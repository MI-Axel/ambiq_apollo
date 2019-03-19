/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSampleAndHoldInt32.h
****************************************************************************
*
*     Description:  Sample and hold module
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
 * @brief Sample and hold module
 */

#ifndef _MOD_SAMPLEANDHOLDINT32_H
#define _MOD_SAMPLEANDHOLDINT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SampleAndHoldInt32_value 0x00000100
#define OFFSET_SampleAndHoldInt32_value 0x00000008

#define CLASSID_SAMPLEANDHOLDINT32 (CLASS_ID_MODBASE + 1315)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSampleAndHoldInt32Instance
{
    ModuleInstanceDescriptor instance;
    
    INT32*             value;               // Holds the last data value which was sampled.  This is an array so that multiple channels can be supported.
} awe_modSampleAndHoldInt32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSampleAndHoldInt32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSampleAndHoldInt32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSampleAndHoldInt32Process(void *pInstance);

 

void awe_modSampleAndHoldInt32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_SAMPLEANDHOLDINT32_H

/**
 * @}
 *
 * End of file.
 */
