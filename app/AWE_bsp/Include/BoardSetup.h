#ifndef __BOARDSETUP_H__
#define __BOARDSETUP_H__
// apollo mcu include
#include <stdint.h>
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

#include "TargetInfo.h"
#include "Platform.h"
//
// AWE includes
//
#include "StandardDefs.h"

extern volatile uint32_t g_ui32TimerCount;
extern volatile BOOL g_bUARTPacketReceived;
extern volatile BOOL g_bPacketReceived;
extern volatile int32_t g_pi32PCMDataBuff[AWE_FRAME_SIZE];
extern volatile int16_t g_pi16LeftChBuff[AWE_FRAME_SIZE];
extern volatile int16_t g_pi16RightChBuff[AWE_FRAME_SIZE];
extern void targetInit(void);

#endif
