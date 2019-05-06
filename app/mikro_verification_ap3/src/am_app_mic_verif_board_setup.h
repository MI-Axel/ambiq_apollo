#ifndef BOARD_SETUP_H_
#define BOARD_SETUP_H_

#include <stdint.h>
#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"
#include "am_app_utils_ring_buffer.h"

#ifdef AM_BSP_NUM_LEDS
#define NUM_LEDS    AM_BSP_NUM_LEDS
#else
#define NUM_LEDS    5       // Make up an arbitrary number of LEDs
#endif

//*****************************************************************************
// Parameters
//
// Total number of bytes transferred = 320*50*2 = 32000
//*****************************************************************************

#define PCM_FRAME_SIZE          320  // Capture one 320-sample (20-ms) frame at a time
#define NUM_PCM_FRAMES          50   // Number of frames in 1 second
#define PCM_DATA_BYTES          4

//*****************************************************************************
//
// App ring buffer list structure typedefs
//
//*****************************************************************************
// this enum list contains all app related ring buffers between AM_APP_RINGBUFF_NONE and AM_APP_RINGBUFF_MAX
// where each index corresponds to a ring buffer
typedef enum
{
    AM_APP_RINGBUFF_NONE = 0, // The enum must begin with this value as named.
    AM_APP_RINGBUFF_PCM,
    AM_APP_RINGBUFF_MAX // The enum must end with this value as named.
} am_app_utils_ring_buffer_enum_t;

typedef enum
{
    AM_APP_KEY_NONE = 0,
    AM_APP_KEY_0,
    AM_APP_KEY_1,
    AM_APP_KEY_2,
    AM_APP_KEY_ALL
} am_app_AEP_key_value_enum_t;


extern volatile  am_app_AEP_key_value_enum_t g_sysKeyValue;

extern am_app_utils_ring_buffer_t am_sys_ring_buffers[AM_APP_RINGBUFF_MAX];

extern const am_hal_gpio_pincfg_t g_switch_button0;
extern const am_hal_gpio_pincfg_t g_switch_button1;
extern const am_hal_gpio_pincfg_t g_switch_button2;
extern am_hal_ctimer_config_t g_sTimer0; 

extern void* PDMHandle;

//*****************************************************************************
// GLOBALS declaration
//*****************************************************************************
extern volatile uint32_t g_ui32TimerCount;

extern volatile uint8_t g_ui8DebounceFlag;

extern volatile uint32_t g_ui32DebounceTimerCount;

extern volatile int16_t g_numFramesCaptured;

extern volatile bool g_bPDMDataReady;

extern volatile uint32_t g_ui32PCMDataBuff[PCM_FRAME_SIZE];  // Location of 1-second data buffer

extern volatile bool g_audioRunningFlag;    

extern volatile uint8_t g_ui8PcmDataReadyFlag;

extern volatile uint8_t g_ui8ButtonPushedFlag;

extern void DebugLog(const char* s);
extern void DebugLogInt32(int32_t i);
extern void DebugLogUInt32(uint32_t i);
extern void DebugLogHex(uint32_t i);
extern void DebugLogFloat(float i);

extern void am_app_mic_verif_sys_init(void);
extern void timerA0_init(void);



#endif /* BOARD_SETUP_H_ */
