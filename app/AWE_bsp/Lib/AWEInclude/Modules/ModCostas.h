/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModCostas.h
****************************************************************************
*
*         Description:  Costas loop PLL carrier recovery
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
 * @brief Costas loop PLL carrier recovery
 */

#ifndef _MOD_COSTAS_H
#define _MOD_COSTAS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Costas_noutpin 0x00000100
#define MASK_Costas_nsinval 0x00000200
#define MASK_Costas_gain 0x00000400
#define MASK_Costas_fcarr 0x00000800
#define MASK_Costas_scale 0x00001000
#define MASK_Costas_phi 0x00002000
#define MASK_Costas_dphi 0x00004000
#define MASK_Costas_blksz 0x00008000
#define MASK_Costas_coeffs 0x00010000
#define MASK_Costas_mults 0x00020000
#define MASK_Costas_sinvals 0x00040000
#define MASK_Costas_iird 0x00080000
#define MASK_Costas_basephi 0x00100000
#define MASK_Costas_carrphi 0x00200000
#define MASK_Costas_mixer 0x00400000
#define MASK_Costas_reference 0x00800000
#define MASK_Costas_controlled 0x01000000
#define OFFSET_Costas_noutpin 0x00000008
#define OFFSET_Costas_nsinval 0x00000009
#define OFFSET_Costas_gain 0x0000000A
#define OFFSET_Costas_fcarr 0x0000000B
#define OFFSET_Costas_scale 0x0000000C
#define OFFSET_Costas_phi 0x0000000D
#define OFFSET_Costas_dphi 0x0000000E
#define OFFSET_Costas_blksz 0x0000000F
#define OFFSET_Costas_coeffs 0x00000010
#define OFFSET_Costas_mults 0x00000011
#define OFFSET_Costas_sinvals 0x00000012
#define OFFSET_Costas_iird 0x00000013
#define OFFSET_Costas_basephi 0x00000014
#define OFFSET_Costas_carrphi 0x00000015
#define OFFSET_Costas_mixer 0x00000016
#define OFFSET_Costas_reference 0x00000017
#define OFFSET_Costas_controlled 0x00000018

#define CLASSID_COSTAS (CLASS_ID_MODBASE + 5020)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCostasInstance
{
    ModuleInstanceDescriptor instance;
    int                noutpin;             // Number of output  pins
    int                nsinval;             // Number of values in the sine lookup table
    float              gain;                // Constant part of loop gain
    float              fcarr;               // Nominal carrier frequency in Hz
    float              scale;               // Combined gain and sampling rate-dependent feedback scaling
    float              phi;                 // Current phase of the local oscillator in cycles
    float              dphi;                // Phase increment per sample at nominal frequency
    int                blksz;               // Block size in samples
    float*             coeffs;              // Coefficient matrix for cascaded first-order sections of the loop filter.  Going down each column are [b0; b1; a1] for a single section.  The number of columns is the order of the filter
    float*             mults;               // Frequency multipliers for each output pin
    float*             sinvals;             // Lookup table for sine function
    float*             iird;                // Direct form I state variable for loop filter
    float*             basephi;             // Storage for baseband phase of most recent block
    float*             carrphi;             // Storage for sum of baseband phase and free-running phase with multiplier = 1
    float*             mixer;               // Local oscillator mix IQ history buffer
    float*             reference;           // Reference input to loop filter
    float*             controlled;          // Controlled output of loop filter
} awe_modCostasInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modCostasClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modCostasConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modCostasProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_COSTAS_H

/**
 * @}
 *
 * End of file.
 */
