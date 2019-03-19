/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModCANMessage.h
****************************************************************************
*
*         Description:  Receive CAN message
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
 * @brief Receive CAN message
 */

#ifndef _MOD_CANMESSAGE_H
#define _MOD_CANMESSAGE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_CANMessage_messageID 0x00000100
#define MASK_CANMessage_fromByte 0x00000200
#define MASK_CANMessage_fromBit 0x00000400
#define MASK_CANMessage_toByte 0x00000800
#define MASK_CANMessage_toBit 0x00001000
#define MASK_CANMessage_scale 0x00002000
#define MASK_CANMessage_offset 0x00004000
#define MASK_CANMessage_CANPacketArrayNdx 0x00008000
#define MASK_CANMessage_errorCode 0x00010000
#define OFFSET_CANMessage_messageID 0x00000008
#define OFFSET_CANMessage_fromByte 0x00000009
#define OFFSET_CANMessage_fromBit 0x0000000A
#define OFFSET_CANMessage_toByte 0x0000000B
#define OFFSET_CANMessage_toBit 0x0000000C
#define OFFSET_CANMessage_scale 0x0000000D
#define OFFSET_CANMessage_offset 0x0000000E
#define OFFSET_CANMessage_CANPacketArrayNdx 0x0000000F
#define OFFSET_CANMessage_errorCode 0x00000010

#define CLASSID_CANMESSAGE (CLASS_ID_MODBASE + 3501)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCANMessageInstance
{
    ModuleInstanceDescriptor instance;
    int                messageID;           // CAN message ID.
    int                fromByte;            // Starting byte number for desired message
    int                fromBit;             // Starting bit offset within byte number for desired message
    int                toByte;              // Ending byte number for desired message
    int                toBit;               // Ending bit offset within ending byte number for desired message
    float              scale;               // value to multiply raw data by
    float              offset;              // offset to add to scaled value
    int                CANPacketArrayNdx;   // Index into CAN packet array
    int                errorCode;           // Internal Error Number
    
} awe_modCANMessageInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if (!defined(AWE_NO_CLASS_OBJECTS) || !defined(AWE_STATIC_CODE))
extern const ModClassModule awe_modCANMessageClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modCANMessageConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modCANMessageProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CANMESSAGE_H

/**
 * @}
 *
 * End of file.
 */
