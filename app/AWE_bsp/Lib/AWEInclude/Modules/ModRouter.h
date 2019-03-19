/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRouter.h
****************************************************************************
*
*     Description:  Channel routing without smoothing
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
 * @brief Channel routing without smoothing
 */

#ifndef _MOD_ROUTER_H
#define _MOD_ROUTER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Router_channelIndex 0x00000100
#define OFFSET_Router_channelIndex 0x00000008

#define CLASSID_ROUTER (CLASS_ID_MODBASE + 100)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRouterInstance
{
    ModuleInstanceDescriptor instance;
    
    INT32*             channelIndex;        // Specifies input to output channel routing. Each item in the array corresponds to an output channel and contains two packed values: input pin number in the high 16 bits; input channel number in the low 16 bits.
} awe_modRouterInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRouterClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modRouterConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modRouterProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ROUTER_H

/**
 * @}
 *
 * End of file.
 */
