#ifndef __TUNINGDRIVER_H__
#define __TUNINGDRIVER_H__

// apollo mcu include
#include <stdint.h>
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

#include "TargetInfo.h"

//
// AWE includes
//
#include "StandardDefs.h"

extern void UARTMsgInit(void);

extern void CheckForUARTPacketReady(void);

extern void UART0SendReply(void);













#endif
