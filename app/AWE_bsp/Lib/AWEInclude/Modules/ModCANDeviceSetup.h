/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModCANDeviceSetup.h
****************************************************************************
*
*         Description:  GridConnect CAN_USB Device Setup
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
 * @brief GridConnect CAN_USB Device Setup
 */

#ifndef _MOD_CANDEVICESETUP_H
#define _MOD_CANDEVICESETUP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_CANDeviceSetup_deviceID 0x00000100
#define MASK_CANDeviceSetup_baud 0x00000200
#define MASK_CANDeviceSetup_errorCode 0x00000400
#define OFFSET_CANDeviceSetup_deviceID 0x00000008
#define OFFSET_CANDeviceSetup_baud 0x00000009
#define OFFSET_CANDeviceSetup_errorCode 0x0000000A

#define CLASSID_CANDEVICESETUP (CLASS_ID_MODBASE + 3500)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCANDeviceSetupInstance
{
    ModuleInstanceDescriptor instance;
    int                deviceID;            // CAN device ID (1-255).
    int                baud;                // BAUD Rate (0x1C - 500K or 0x14 - 1M.
    int                errorCode;           // Internal Error Number
    
} awe_modCANDeviceSetupInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if (!defined(AWE_NO_CLASS_OBJECTS) || !defined(AWE_STATIC_CODE))
extern const ModClassModule awe_modCANDeviceSetupClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modCANDeviceSetupConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modCANDeviceSetupProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CANDEVICESETUP_H

/**
 * @}
 *
 * End of file.
 */
