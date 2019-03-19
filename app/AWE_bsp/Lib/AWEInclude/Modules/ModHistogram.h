/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModHistogram.h
****************************************************************************
*
*     Description:  Histogram of data
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
 * @brief Histogram of data
 */

#ifndef _MOD_HISTOGRAM_H
#define _MOD_HISTOGRAM_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Histogram_numBins 0x00000100
#define MASK_Histogram_lowerBinCenter 0x00000200
#define MASK_Histogram_binSpacing 0x00000400
#define MASK_Histogram_reset 0x00000800
#define MASK_Histogram_numHistSamples 0x00001000
#define MASK_Histogram_numUnderSamples 0x00002000
#define MASK_Histogram_numOverSamples 0x00004000
#define MASK_Histogram_hist 0x00008000
#define OFFSET_Histogram_numBins 0x00000008
#define OFFSET_Histogram_lowerBinCenter 0x00000009
#define OFFSET_Histogram_binSpacing 0x0000000A
#define OFFSET_Histogram_reset 0x0000000B
#define OFFSET_Histogram_numHistSamples 0x0000000C
#define OFFSET_Histogram_numUnderSamples 0x0000000D
#define OFFSET_Histogram_numOverSamples 0x0000000E
#define OFFSET_Histogram_hist 0x0000000F

#define CLASSID_HISTOGRAM (CLASS_ID_MODBASE + 1286)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modHistogramInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numBins;             // Number of bins in the histogram
    FLOAT32            lowerBinCenter;      // Specifies the center of the first (lowest) bin in the histogram
    FLOAT32            binSpacing;          // Specifies the spacing between bins
    INT32              reset;               // Boolean parameter to reset the histogram.
    INT32              numHistSamples;      // Number of input samples processed.
    INT32              numUnderSamples;     // Total number of input samples that were outside of the histogram range on the low end.
    INT32              numOverSamples;      // Total number of input samples that were outside of the histogram range on the high end.
    INT32*             hist;                // Histogram array.
} awe_modHistogramInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modHistogramClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modHistogramConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modHistogramProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_HISTOGRAM_H

/**
 * @}
 *
 * End of file.
 */
