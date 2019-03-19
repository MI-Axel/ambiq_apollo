/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSinkFract32.h
****************************************************************************
*
*     Description:  Copies the data at the input pin and stores it in an internal buffer
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
 * @brief Copies the data at the input pin and stores it in an internal buffer
 */

#ifndef _MOD_SINKFRACT32_H
#define _MOD_SINKFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SinkFract32_enable 0x00000100
#define MASK_SinkFract32_value 0x00000200
#define MASK_SinkFract32_yRange 0x00000400
#define OFFSET_SinkFract32_enable 0x00000008
#define OFFSET_SinkFract32_value 0x00000009
#define OFFSET_SinkFract32_yRange 0x0000000A

#define CLASSID_SINKFRACT32 (CLASS_ID_MODBASE + 197)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSinkFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              enable;              // To Enable or disable the plotting
    fract32*           value;               // Captured values
    FLOAT32*           yRange;              // Yaxis Range
} awe_modSinkFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSinkFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSinkFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSinkFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SINKFRACT32_H

/**
 * @}
 *
 * End of file.
 */
