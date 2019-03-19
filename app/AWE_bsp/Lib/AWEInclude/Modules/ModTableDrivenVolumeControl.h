/**
 *	@addtogroup Modules
 *	@{
 */

/****************************************************************************
*
*		Audio Framework
*		---------------
*
****************************************************************************
*	ModTableDrivenVolumeControl.h
****************************************************************************
*
*	Description:	Perceptual volume control with parameters driven by a table.
*
*         Copyright:	DSP Concepts, Inc., 2007
*
***************************************************************************/

/*
 * @file ModTableDrivenVolumeControl.h
 */


#ifndef _MOD_TABLEDRIVENVOLUMECONTROL_H
#define _MOD_TABLEDRIVENVOLUMECONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModScalerDBSmoothed.h"
#include "ModSecondOrderFilterSmoothed40.h"

#define MASK_TableDrivenVolumeControl_setting 0x00000100
#define MASK_TableDrivenVolumeControl_tableSize 0x00000200
#define MASK_TableDrivenVolumeControl_table 0x00000400
#define OFFSET_TableDrivenVolumeControl_setting 0x00000008
#define OFFSET_TableDrivenVolumeControl_tableSize 0x00000009
#define OFFSET_TableDrivenVolumeControl_table 0x0000000A

#define CLASSID_TABLEDRIVENVOLUMECONTROL (CLASS_ID_MODBASE + 5012)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableDrivenVolumeControlInstance
{
  ModuleInstanceDescriptor instance;
    	int       	setting;             // 
    	int       	tableSize;           // Number of entries in the table
    	float*    	table;               // Table of design parameteres and selection depends on setting parameter
    	awe_modScalerDBSmoothedInstance	*scale;              // Gain control with dB units and smoothing
    	awe_modSecondOrderFilterSmoothed40Instance	*bassFilt;           // General 2nd order filter designer with 40-bit processing and smoothing
    	awe_modSecondOrderFilterSmoothed40Instance	*trebleFilt;         // General 2nd order filter designer with 40-bit processing and smoothing
} awe_modTableDrivenVolumeControlInstance;

#ifdef AWE_INCLUDE_CLASS_OBJECT
extern const ModClassModule awe_modTableDrivenVolumeControlClass;
#endif

#ifdef AWE_INCLUDE_CONSTRUCTOR_FUNCTION
ModInstanceDescriptor * awe_modTableDrivenVolumeControlConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif


void awe_modTableDrivenVolumeControlProcess(void *pInstance);

UINT32 awe_modTableDrivenVolumeControlSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLEDRIVENVOLUMECONTROL_H

/**
 * @}
 *
 * End of file.
 */
