/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModGPIO.h
****************************************************************************
*
*     Description:  Perform GPIO on target
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
 * @brief Perform GPIO on target
 */

#ifndef _MOD_GPIO_H
#define _MOD_GPIO_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_GPIO_nPins 0x00000100
#define MASK_GPIO_nPinDir 0x00000200
#define MASK_GPIO_errorCode 0x00000400
#define MASK_GPIO_nPinIndex 0x00000800
#define MASK_GPIO_nLastOutValue 0x00001000
#define OFFSET_GPIO_nPins 0x00000008
#define OFFSET_GPIO_nPinDir 0x00000009
#define OFFSET_GPIO_errorCode 0x0000000A
#define OFFSET_GPIO_nPinIndex 0x0000000B
#define OFFSET_GPIO_nLastOutValue 0x0000000C

#define CLASSID_GPIO (CLASS_ID_MODBASE + 93)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modGPIOInstance
{
    ModuleInstanceDescriptor instance;
    INT32              nPins;               // Number of pins
    INT32              nPinDir;             // I/O direction 0 - input, 1 - output
    INT32              errorCode;           // Internal Error Number
    INT32*             nPinIndex;           // Specifies which physical GPIO pins to use.
    INT32*             nLastOutValue;       // Holds the last output value.
} awe_modGPIOInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modGPIOClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modGPIOConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modGPIOProcess(void *pInstance);

UINT32 awe_modGPIOSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_GPIO_H

/**
 * @}
 *
 * End of file.
 */
