/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSbComplexFIRvl.h
****************************************************************************
*
*     Description:  Sub-band Complex FIR Filter with module
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
 * @brief Sub-band Complex FIR Filter with module
 */

#ifndef _MOD_SBCOMPLEXFIRVL_H
#define _MOD_SBCOMPLEXFIRVL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SbComplexFIRvl_numWords 0x00000100
#define MASK_SbComplexFIRvl_stateIndex 0x00000200
#define MASK_SbComplexFIRvl_numTaps 0x00000400
#define MASK_SbComplexFIRvl_state 0x00000800
#define MASK_SbComplexFIRvl_coeffs 0x00001000
#define OFFSET_SbComplexFIRvl_numWords 0x00000008
#define OFFSET_SbComplexFIRvl_stateIndex 0x00000009
#define OFFSET_SbComplexFIRvl_numTaps 0x0000000A
#define OFFSET_SbComplexFIRvl_state 0x0000000B
#define OFFSET_SbComplexFIRvl_coeffs 0x0000000C

#define CLASSID_SBCOMPLEXFIRVL (CLASS_ID_MODBASE + 1323)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSbComplexFIRvlInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numWords;            // Length of state and coeffs array
    INT32*             stateIndex;          // State index per subband
    INT32*             numTaps;             // Array of number of taps per subband
    FLOAT32*           state;               // FIR filter state memory
    FLOAT32*           coeffs;              // FIR filter coeffs array
} awe_modSbComplexFIRvlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSbComplexFIRvlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSbComplexFIRvlConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSbComplexFIRvlProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SBCOMPLEXFIRVL_H

/**
 * @}
 *
 * End of file.
 */
