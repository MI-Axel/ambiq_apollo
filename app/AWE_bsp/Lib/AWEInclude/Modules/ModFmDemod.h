/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModFmDemod.h
****************************************************************************
*
*         Description:  FM demodulator
*
*         Copyright:	DSP Concepts, Inc., 2007 - 2012
*                       568 E. Weddell Drive, Suite 3
*                       Sunnyvale, CA 94089
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief FM demodulator
 */

#ifndef _MOD_FMDEMOD_H
#define _MOD_FMDEMOD_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FmDemod_natanval 0x00000100
#define MASK_FmDemod_deviation 0x00000200
#define MASK_FmDemod_scale 0x00000400
#define MASK_FmDemod_phi 0x00000800
#define MASK_FmDemod_atanvals 0x00001000
#define MASK_FmDemod_quadsign 0x00002000
#define MASK_FmDemod_quadoffs 0x00004000
#define OFFSET_FmDemod_natanval 0x00000008
#define OFFSET_FmDemod_deviation 0x00000009
#define OFFSET_FmDemod_scale 0x0000000A
#define OFFSET_FmDemod_phi 0x0000000B
#define OFFSET_FmDemod_atanvals 0x0000000C
#define OFFSET_FmDemod_quadsign 0x0000000D
#define OFFSET_FmDemod_quadoffs 0x0000000E

#define CLASSID_FMDEMOD (CLASS_ID_MODBASE + 5021)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFmDemodInstance
{
    ModuleInstanceDescriptor instance;
    int                natanval;            // Number of precomputed arctan values in lookup table
    float              deviation;           // FM  Deviation: amount of frequency change caused by unit input
    float              scale;               // Scaling of the phase difference needed to recover the input signal
    float              phi;                 // Latest input phase
    float*             atanvals;            // Lookup table of arctangent values, scaled by 1/2pi
    float*             quadsign;            // Sign change for angles in each quadrant relative to those in the first quadrant
    float*             quadoffs;            // Additive offset for angles in each quadrant from those of the first quadrant
} awe_modFmDemodInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modFmDemodClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFmDemodConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFmDemodProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FMDEMOD_H

/**
 * @}
 *
 * End of file.
 */
