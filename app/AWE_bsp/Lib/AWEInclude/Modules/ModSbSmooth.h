/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSbSmooth.h
****************************************************************************
*
*     Description:  Subband smoothing across frequency bins
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
 * @brief Subband smoothing across frequency bins
 */

#ifndef _MOD_SBSMOOTH_H
#define _MOD_SBSMOOTH_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SbSmooth_type 0x00000100
#define MASK_SbSmooth_startFreq 0x00000200
#define MASK_SbSmooth_width 0x00000400
#define MASK_SbSmooth_startIndex 0x00000800
#define MASK_SbSmooth_endIndex 0x00001000
#define MASK_SbSmooth_oneOverN 0x00002000
#define MASK_SbSmooth_cumSum 0x00004000
#define OFFSET_SbSmooth_type 0x00000008
#define OFFSET_SbSmooth_startFreq 0x00000009
#define OFFSET_SbSmooth_width 0x0000000A
#define OFFSET_SbSmooth_startIndex 0x0000000B
#define OFFSET_SbSmooth_endIndex 0x0000000C
#define OFFSET_SbSmooth_oneOverN 0x0000000D
#define OFFSET_SbSmooth_cumSum 0x0000000E

#define CLASSID_SBSMOOTH (CLASS_ID_MODBASE + 1327)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSbSmoothInstance
{
    ModuleInstanceDescriptor instance;
    INT32              type;                // Determines which type of smoothing is applied:  Linear=0, Logarithmic=1, Custom=2
    FLOAT32            startFreq;           // Starting frequency for the smoothing operation
    FLOAT32            width;               // Amount of smoothing
    INT32*             startIndex;          // Starting index for the averaging process.
    INT32*             endIndex;            // Ending index for the averaging process.
    FLOAT32*           oneOverN;            // Precomputed 1/N for averaging.
    FLOAT32*           cumSum;              // Cumulative sum of values from the start of the buffer.
} awe_modSbSmoothInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSbSmoothClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSbSmoothConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSbSmoothProcess(void *pInstance);

UINT32 awe_modSbSmoothSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SBSMOOTH_H

/**
 * @}
 *
 * End of file.
 */
