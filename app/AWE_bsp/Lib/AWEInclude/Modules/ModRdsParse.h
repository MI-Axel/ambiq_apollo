/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModRdsParse.h
****************************************************************************
*
*         Description:  RDS data parser
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
 * @brief RDS data parser
 */

#ifndef _MOD_RDSPARSE_H
#define _MOD_RDSPARSE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RdsParse_grpblk 0x00000100
#define MASK_RdsParse_grplen 0x00000200
#define MASK_RdsParse_grpused 0x00000400
#define MASK_RdsParse_grpmark 0x00000800
#define MASK_RdsParse_grpdrop 0x00001000
#define MASK_RdsParse_lastngrp 0x00002000
#define MASK_RdsParse_groups 0x00004000
#define MASK_RdsParse_grpstat 0x00008000
#define MASK_RdsParse_lastgrps 0x00010000
#define OFFSET_RdsParse_grpblk 0x00000008
#define OFFSET_RdsParse_grplen 0x00000009
#define OFFSET_RdsParse_grpused 0x0000000A
#define OFFSET_RdsParse_grpmark 0x0000000B
#define OFFSET_RdsParse_grpdrop 0x0000000C
#define OFFSET_RdsParse_lastngrp 0x0000000D
#define OFFSET_RdsParse_groups 0x0000000E
#define OFFSET_RdsParse_grpstat 0x0000000F
#define OFFSET_RdsParse_lastgrps 0x00000010

#define CLASSID_RDSPARSE (CLASS_ID_MODBASE + 5018)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRdsParseInstance
{
    ModuleInstanceDescriptor instance;
    int                grpblk;              // Number ofblocks in a group
    int                grplen;              // Length of block group buffer
    int                grpused;             // Number of elements in group buffer
    int                grpmark;             // Zero-based index just past newest sample in group buffer
    int                grpdrop;             // Dropped input groups
    int                lastngrp;            // Number of valid groups in latest input set
    int*               groups;              // Latest input data groups
    int*               grpstat;             // Latest group status 
    int*               lastgrps;            // Most recent input data set
} awe_modRdsParseInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modRdsParseClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modRdsParseConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modRdsParseProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RDSPARSE_H

/**
 * @}
 *
 * End of file.
 */
