/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModPhaseDetect.h
****************************************************************************
*
*         Description:  Sinusoidal phase detector
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
 * @brief Sinusoidal phase detector
 */

#ifndef _MOD_PHASEDETECT_H
#define _MOD_PHASEDETECT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_PhaseDetect_ntap 0x00000100
#define MASK_PhaseDetect_nfrac 0x00000200
#define MASK_PhaseDetect_nfilt 0x00000400
#define MASK_PhaseDetect_block 0x00000800
#define MASK_PhaseDetect_nlag 0x00001000
#define MASK_PhaseDetect_bank 0x00002000
#define MASK_PhaseDetect_grid 0x00004000
#define MASK_PhaseDetect_r 0x00008000
#define MASK_PhaseDetect_x 0x00010000
#define MASK_PhaseDetect_work 0x00020000
#define MASK_PhaseDetect_delay 0x00040000
#define OFFSET_PhaseDetect_ntap 0x00000008
#define OFFSET_PhaseDetect_nfrac 0x00000009
#define OFFSET_PhaseDetect_nfilt 0x0000000A
#define OFFSET_PhaseDetect_block 0x0000000B
#define OFFSET_PhaseDetect_nlag 0x0000000C
#define OFFSET_PhaseDetect_bank 0x0000000D
#define OFFSET_PhaseDetect_grid 0x0000000E
#define OFFSET_PhaseDetect_r 0x0000000F
#define OFFSET_PhaseDetect_x 0x00000010
#define OFFSET_PhaseDetect_work 0x00000011
#define OFFSET_PhaseDetect_delay 0x00000012

#define CLASSID_PHASEDETECT (CLASS_ID_MODBASE + 5015)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPhaseDetectInstance
{
    ModuleInstanceDescriptor instance;
    int                ntap;                // Length of the delay filters
    int                nfrac;               // Number of fractional steps per sample
    int                nfilt;               // Number of filters in fractional delay bank
    int                block;               // Number of samples in a processing block
    int                nlag;                // Number of lag values computed by correlations
    float*             bank;                // Fractional delay filter bank
    float*             grid;                // Correlation work area
    float*             r;                   // Preprocessed reference
    float*             x;                   // Preprocessed input
    float*             work;                // Signal work buffer
    float*             delay;               // Delayed input signals
} awe_modPhaseDetectInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modPhaseDetectClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modPhaseDetectConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modPhaseDetectProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PHASEDETECT_H

/**
 * @}
 *
 * End of file.
 */
