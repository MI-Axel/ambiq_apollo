/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModRdsDecode.h
****************************************************************************
*
*         Description:  RDS channel decoder
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
 * @brief RDS channel decoder
 */

#ifndef _MOD_RDSDECODE_H
#define _MOD_RDSDECODE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RdsDecode_bitlen 0x00000100
#define MASK_RdsDecode_bitused 0x00000200
#define MASK_RdsDecode_bitmark 0x00000400
#define MASK_RdsDecode_bitdrop 0x00000800
#define MASK_RdsDecode_bitscan 0x00001000
#define MASK_RdsDecode_blklen 0x00002000
#define MASK_RdsDecode_blkused 0x00004000
#define MASK_RdsDecode_blkmark 0x00008000
#define MASK_RdsDecode_blkdrop 0x00010000
#define MASK_RdsDecode_blkcheck 0x00020000
#define MASK_RdsDecode_wordbit 0x00040000
#define MASK_RdsDecode_databit 0x00080000
#define MASK_RdsDecode_checkbit 0x00100000
#define MASK_RdsDecode_blksync 0x00200000
#define MASK_RdsDecode_blkoff 0x00400000
#define MASK_RdsDecode_noffset 0x00800000
#define MASK_RdsDecode_lastnbit 0x01000000
#define MASK_RdsDecode_bits 0x02000000
#define MASK_RdsDecode_blkbegs 0x04000000
#define MASK_RdsDecode_offsets 0x08000000
#define MASK_RdsDecode_blocks 0x10000000
#define MASK_RdsDecode_checks 0x20000000
#define MASK_RdsDecode_syndromes 0x40000000
#define MASK_RdsDecode_grpbegs 0x80000000
#define MASK_RdsDecode_offwords 0x80000000
#define MASK_RdsDecode_parcomp 0x80000000
#define MASK_RdsDecode_lastbits 0x80000000
#define OFFSET_RdsDecode_bitlen 0x00000008
#define OFFSET_RdsDecode_bitused 0x00000009
#define OFFSET_RdsDecode_bitmark 0x0000000A
#define OFFSET_RdsDecode_bitdrop 0x0000000B
#define OFFSET_RdsDecode_bitscan 0x0000000C
#define OFFSET_RdsDecode_blklen 0x0000000D
#define OFFSET_RdsDecode_blkused 0x0000000E
#define OFFSET_RdsDecode_blkmark 0x0000000F
#define OFFSET_RdsDecode_blkdrop 0x00000010
#define OFFSET_RdsDecode_blkcheck 0x00000011
#define OFFSET_RdsDecode_wordbit 0x00000012
#define OFFSET_RdsDecode_databit 0x00000013
#define OFFSET_RdsDecode_checkbit 0x00000014
#define OFFSET_RdsDecode_blksync 0x00000015
#define OFFSET_RdsDecode_blkoff 0x00000016
#define OFFSET_RdsDecode_noffset 0x00000017
#define OFFSET_RdsDecode_lastnbit 0x00000018
#define OFFSET_RdsDecode_bits 0x00000019
#define OFFSET_RdsDecode_blkbegs 0x0000001A
#define OFFSET_RdsDecode_offsets 0x0000001B
#define OFFSET_RdsDecode_blocks 0x0000001C
#define OFFSET_RdsDecode_checks 0x0000001D
#define OFFSET_RdsDecode_syndromes 0x0000001E
#define OFFSET_RdsDecode_grpbegs 0x0000001F
#define OFFSET_RdsDecode_offwords 0x00000020
#define OFFSET_RdsDecode_parcomp 0x00000021
#define OFFSET_RdsDecode_lastbits 0x00000022

#define CLASSID_RDSDECODE (CLASS_ID_MODBASE + 5017)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRdsDecodeInstance
{
    ModuleInstanceDescriptor instance;
    int                bitlen;              // Length of bit buffer
    int                bitused;             // Number of bits in bit buffer
    int                bitmark;             // Zero-based index just past newest sample in bit buffer
    int                bitdrop;             // Dropped input bits
    int                bitscan;             // Index for next scan
    int                blklen;              // Number of entries in per-block lists
    int                blkused;             // Number of values per-block buffers
    int                blkmark;             // Zero-based index after newest block start
    int                blkdrop;             // Dropped per-block values
    int                blkcheck;            // Index of next block to check for expected offset
    int                wordbit;             // Code Word length in bits
    int                databit;             // Data bits per word
    int                checkbit;            // Number of check bits
    int                blksync;             // Bit index of most recent block sync
    int                blkoff;              // Most recent offset word
    int                noffset;             // Number of offset words
    int                lastnbit;            // Number of valid bits in last input block
    int*               bits;                // Past raw received bits
    int*               blkbegs;             // Indices of block start candidates
    int*               offsets;             // Offset words of new blocks
    int*               blocks;              // Data bits from recent blocks
    int*               checks;              // Check bits from latest blocks
    int*               syndromes;           // Syndromes for latest blocks
    int*               grpbegs;             // Block indices for starts of new groups
    int*               offwords;            // Offset word values
    int*               parcomp;             // Parity computation matrix
    int*               lastbits;            // Most recent input block
} awe_modRdsDecodeInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modRdsDecodeClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modRdsDecodeConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modRdsDecodeProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RDSDECODE_H

/**
 * @}
 *
 * End of file.
 */
