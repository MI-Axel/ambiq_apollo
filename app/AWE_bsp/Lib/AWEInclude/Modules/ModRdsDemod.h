/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModRdsDemod.h
****************************************************************************
*
*         Description:  RDS signal demodulator
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
 * @brief RDS signal demodulator
 */

#ifndef _MOD_RDSDEMOD_H
#define _MOD_RDSDEMOD_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RdsDemod_fcarr 0x00000100
#define MASK_RdsDemod_symcyc 0x00000200
#define MASK_RdsDemod_sync 0x00000400
#define MASK_RdsDemod_Tsym 0x00000800
#define MASK_RdsDemod_ntap 0x00001000
#define MASK_RdsDemod_inlen 0x00002000
#define MASK_RdsDemod_corrlen 0x00004000
#define MASK_RdsDemod_peaklen 0x00008000
#define MASK_RdsDemod_imark 0x00010000
#define MASK_RdsDemod_corrmark 0x00020000
#define MASK_RdsDemod_corrused 0x00040000
#define MASK_RdsDemod_corrdrop 0x00080000
#define MASK_RdsDemod_peakmark 0x00100000
#define MASK_RdsDemod_peakused 0x00200000
#define MASK_RdsDemod_peakdrop 0x00400000
#define MASK_RdsDemod_symsync 0x00800000
#define MASK_RdsDemod_symcorr 0x01000000
#define MASK_RdsDemod_in 0x02000000
#define MASK_RdsDemod_corr 0x04000000
#define MASK_RdsDemod_peakidx 0x08000000
#define MASK_RdsDemod_peakval 0x10000000
#define MASK_RdsDemod_work 0x20000000
#define OFFSET_RdsDemod_fcarr 0x00000008
#define OFFSET_RdsDemod_symcyc 0x00000009
#define OFFSET_RdsDemod_sync 0x0000000A
#define OFFSET_RdsDemod_Tsym 0x0000000B
#define OFFSET_RdsDemod_ntap 0x0000000C
#define OFFSET_RdsDemod_inlen 0x0000000D
#define OFFSET_RdsDemod_corrlen 0x0000000E
#define OFFSET_RdsDemod_peaklen 0x0000000F
#define OFFSET_RdsDemod_imark 0x00000010
#define OFFSET_RdsDemod_corrmark 0x00000011
#define OFFSET_RdsDemod_corrused 0x00000012
#define OFFSET_RdsDemod_corrdrop 0x00000013
#define OFFSET_RdsDemod_peakmark 0x00000014
#define OFFSET_RdsDemod_peakused 0x00000015
#define OFFSET_RdsDemod_peakdrop 0x00000016
#define OFFSET_RdsDemod_symsync 0x00000017
#define OFFSET_RdsDemod_symcorr 0x00000018
#define OFFSET_RdsDemod_in 0x00000019
#define OFFSET_RdsDemod_corr 0x0000001A
#define OFFSET_RdsDemod_peakidx 0x0000001B
#define OFFSET_RdsDemod_peakval 0x0000001C
#define OFFSET_RdsDemod_work 0x0000001D

#define CLASSID_RDSDEMOD (CLASS_ID_MODBASE + 5016)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRdsDemodInstance
{
    ModuleInstanceDescriptor instance;
    float              fcarr;               // Carrier frequency in Hz
    int                symcyc;              // Number of carrier cycles per symbol
    int                sync;                // Symbol synchronization progress: 0 = collecting, 1 = syncing, 2 = symbol sync done
    float              Tsym;                // Symbol period in samples
    int                ntap;                // Number of taps for symbol correlator
    int                inlen;               // Input buffer length in samples
    int                corrlen;             // Correlation buffer length in samples
    int                peaklen;             // Number of samples in the peak index and value buffers
    int                imark;               // Index one past newest sample in previous input buffer
    int                corrmark;            // Index one past newest sample in correlation buffer
    int                corrused;            // Number of samples of correlation buffer in use
    int                corrdrop;            // Number of dropped correlator samples
    int                peakmark;            // Index one past newest sample in peak buffers
    int                peakused;            // Samples of peak buffers in use
    int                peakdrop;            // Dropped peak buffer samples
    int                symsync;             // Offset into peak buffers of latest bit flip
    float*             symcorr;             // Pulse filter for symbol correlation
    float*             in;                  // Past input samples
    float*             corr;                // Past symbol correlator outputs
    int*               peakidx;             // Indices of previous symbol correlator peaks
    float*             peakval;             // Values of previous symbol correlator peaks
    int*               work;                // Scratch work area
} awe_modRdsDemodInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modRdsDemodClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modRdsDemodConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modRdsDemodProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RDSDEMOD_H

/**
 * @}
 *
 * End of file.
 */
