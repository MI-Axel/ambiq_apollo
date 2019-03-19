/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMapperControl.h
****************************************************************************
*
*     Description:  One shot player with trigger pin
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
 * @brief One shot player with trigger pin
 */

#ifndef _MOD_MAPPERCONTROL_H
#define _MOD_MAPPERCONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModClipAsym.h"
#include "ModRouter.h"
#include "ModScaleOffset.h"
#include "ModTypeConversion.h"

#define MASK_MapperControl_channelNum 0x00000100
#define MASK_MapperControl_inputMin 0x00000200
#define MASK_MapperControl_inputMax 0x00000400
#define MASK_MapperControl_outputMin 0x00000800
#define MASK_MapperControl_outputMax 0x00001000
#define OFFSET_MapperControl_channelNum 0x00000008
#define OFFSET_MapperControl_inputMin 0x00000009
#define OFFSET_MapperControl_inputMax 0x0000000A
#define OFFSET_MapperControl_outputMin 0x0000000B
#define OFFSET_MapperControl_outputMax 0x0000000C

#define CLASSID_MAPPERCONTROL (CLASS_ID_MODBASE + 1372)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMapperControlInstance
{
    ModuleInstanceDescriptor instance;
    INT32              channelNum;          // Select the channel from the input control bus
    FLOAT32            inputMin;            // Minimum input value
    FLOAT32            inputMax;            // Maximum input value
    FLOAT32            outputMin;           // Minimum output value
    FLOAT32            outputMax;           // Maximum output value
        awe_modRouterInstance    *router;             // Channel routing without smoothing
        awe_modTypeConversionInstance    *toFloat;            // Converts between numeric data types
        awe_modClipAsymInstance    *clip;               // Asymmetric clipper module with separate upper and lower clipping thresholds
        awe_modScaleOffsetInstance    *scaleOffset;        // Scales a signal and then adds an offset
} awe_modMapperControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMapperControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMapperControlConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMapperControlProcess(void *pInstance);

UINT32 awe_modMapperControlSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MAPPERCONTROL_H

/**
 * @}
 *
 * End of file.
 */
