#ifndef AM_AEP_BOARD_SETUP_H
#define AM_AEP_BOARD_SETUP_H

//*****************************************************************************
//
// Required built-ins.
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//*****************************************************************************
//
// Standard AmbiqSuite includes.
//
//*****************************************************************************
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices.h"
#include "am_util.h"


// user include
#include "am_AEP_config.h"


extern void* PDMHandle;
extern uint32_t g_ui32PCMDataBuff[PCM_FRAME_SIZE];


extern void am_AEP_board_setup(void);



































#endif
