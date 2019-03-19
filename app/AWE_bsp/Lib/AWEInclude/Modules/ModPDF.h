/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPDF.h
****************************************************************************
*
*     Description:  pdf of data
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
 * @brief pdf of data
 */

#ifndef _MOD_PDF_H
#define _MOD_PDF_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_PDF_numBins 0x00000100
#define MASK_PDF_lowerBinEdge 0x00000200
#define MASK_PDF_higherBinEdge 0x00000400
#define MASK_PDF_smoothingTime 0x00000800
#define MASK_PDF_alpha 0x00001000
#define MASK_PDF_binSpacing 0x00002000
#define MASK_PDF_reset 0x00004000
#define MASK_PDF_previousOut 0x00008000
#define MASK_PDF_hist 0x00010000
#define OFFSET_PDF_numBins 0x00000008
#define OFFSET_PDF_lowerBinEdge 0x00000009
#define OFFSET_PDF_higherBinEdge 0x0000000A
#define OFFSET_PDF_smoothingTime 0x0000000B
#define OFFSET_PDF_alpha 0x0000000C
#define OFFSET_PDF_binSpacing 0x0000000D
#define OFFSET_PDF_reset 0x0000000E
#define OFFSET_PDF_previousOut 0x0000000F
#define OFFSET_PDF_hist 0x00000010

#define CLASSID_PDF (CLASS_ID_MODBASE + 1370)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPDFInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numBins;             // Number of bins
    FLOAT32            lowerBinEdge;        // Specifies the lowest bin in the histogram
    FLOAT32            higherBinEdge;       // Specifies the highest bin in the histogram
    FLOAT32            smoothingTime;       // The smoothing time of the PDF in ms
    FLOAT32            alpha;               // Forgetting factor
    FLOAT32            binSpacing;          // BinSpacing
    INT32              reset;               // Boolean parameter to reset the pdf.
    FLOAT32*           previousOut;         // previous output.
    INT32*             hist;                // init hist.
} awe_modPDFInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPDFClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modPDFConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modPDFProcess(void *pInstance);

UINT32 awe_modPDFSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PDF_H

/**
 * @}
 *
 * End of file.
 */
