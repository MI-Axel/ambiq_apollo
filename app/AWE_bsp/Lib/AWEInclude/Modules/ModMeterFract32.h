/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMeterFract32.h
****************************************************************************
*
*     Description:  Peak and RMS meter module
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
 * @brief Peak and RMS meter module
 */

#ifndef _MOD_METERFRACT32_H
#define _MOD_METERFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MeterFract32_meterType 0x00000100
#define MASK_MeterFract32_attackTime 0x00000200
#define MASK_MeterFract32_releaseTime 0x00000400
#define MASK_MeterFract32_attackCoeffFract32 0x00000800
#define MASK_MeterFract32_releaseCoeffFract32 0x00001000
#define MASK_MeterFract32_value 0x00002000
#define OFFSET_MeterFract32_meterType 0x00000008
#define OFFSET_MeterFract32_attackTime 0x00000009
#define OFFSET_MeterFract32_releaseTime 0x0000000A
#define OFFSET_MeterFract32_attackCoeffFract32 0x0000000B
#define OFFSET_MeterFract32_releaseCoeffFract32 0x0000000C
#define OFFSET_MeterFract32_value 0x0000000D

#define CLASSID_METERFRACT32 (CLASS_ID_MODBASE + 157)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMeterFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              meterType;           // Operating module of the meter.  Selects between peak and RMS calculations.  See the discussion section for more details
    FLOAT32            attackTime;          // Attack time of the meter.  Specifies how quickly the meter value rises
    FLOAT32            releaseTime;         // Release time of the meter.  Specifies how quickly the meter decays
    fract32            attackCoeffFract32;  // Internal coefficient that realizes the attack time
    fract32            releaseCoeffFract32; // Internal coefficient that realizes the release time
    fract32*           value;               // Array of meter output values, one per channel
} awe_modMeterFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMeterFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMeterFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMeterFract32Process(void *pInstance);

UINT32 awe_modMeterFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_METERFRACT32_H

/**
 * @}
 *
 * End of file.
 */
