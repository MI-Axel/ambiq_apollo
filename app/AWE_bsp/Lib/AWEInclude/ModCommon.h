/****************************************************************************
 *
 *		Audio Framework
 *		---------------
 *
 ****************************************************************************
 *	ModCommon.h
 ****************************************************************************
 *
 *	Description:	ModCommon main header
 *
 *	Copyright:		DSP Concepts, 2006-2012, All rights reserved.
 *	Owner:			DSP Concepts
 *					568 E. Weddell Drive, Suite 3
 *					Sunnyvale, CA 94089
 *
 ***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief ModCommon main header
 */


#ifndef _MOD_COMMON_H
#define _MOD_COMMON_H

#include "Framework.h"

#ifdef __cplusplus
extern "C" {
#endif


/*-------------------- Generic ---------------------*/
/** Bypass function for any module that has corresponding inputs and outputs. */
void IOMatchModule_Bypass(void *pInstance);

/** Bypass function for modules that copies channels straight across */
void IOAcrossModule_Bypass(void *pInstance);

/* Bypass function for modules with disparate I/O.  It matches up inputs and outputs as best as
** it can. */

void IOMatchUpModule_Bypass(void *pInstance);

/* Bypass function that fills all output channels with 1.0 */
void IOAllOnesModule_Bypass(void *pInstance);

int ValidateMatchedInputs(size_t argCount, Sample *args);

/** Mute function for any module. */
void GenericModule_Mute(void *pInstance);

/** Inactive function for any module. */
void GenericModule_Inactive(void *pInstance);

/* Process function for Container. */
void Container_Process(void *pInstance);

void ModuleWire_Init(ModuleInstanceDescriptor *S, WireInstance **pWires);



#ifdef __cplusplus
}
#endif

#endif // _MOD_COMMON_H

/**
 * @}
 *
 * End of file.
 */
