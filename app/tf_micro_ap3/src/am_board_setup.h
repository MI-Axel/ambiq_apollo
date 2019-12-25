#ifndef BOARD_SETUP_H_
#define BOARD_SETUP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "am_tf_micro_config.h"
#include <stdint.h>
#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"
#include "am_app_utils_ring_buffer.h"
#if AM_AEP_BEAMFORMING_TEST 
#include "audio_preprocessor.h"
#endif // AM_AEP_BEAMFORMING_TEST

#ifdef AM_BSP_NUM_LEDS
#define NUM_LEDS    AM_BSP_NUM_LEDS
#else
#define NUM_LEDS    5       // Make up an arbitrary number of LEDs
#endif

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
#if AM_AEP_BEAMFORMING_TEST
    AM_APP_RINGBUFF_PREP,
#endif // AM_AEP_BEAMFORMING_TEST
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

extern const am_hal_gpio_pincfg_t g_deepsleep_button0;
extern am_hal_ctimer_config_t g_sTimer0; 
extern volatile uint32_t g_ui32TimerCount;

extern volatile uint8_t g_ui8DebounceFlag;

extern volatile uint32_t g_ui32DebounceTimerCount;

#if configUSE_RTT_DATA_OUTPUT
extern uint8_t g_rttRecorderBuff[RTT_BUFFER_LENGTH];
extern volatile uint8_t g_rttRecordingFlag; 
#endif // configUSE_RTT_DATA_OUTPUT

#if configUSE_MEASURE_MIPS

#define SAMPLING_RATE               (16000)
#define MIPS_DURATION_SEC           (1)
#define FRAME_RATE                  (1024)
#define MIPS_BUFFER_LEN             (1)
//#define MIPS_BUFFER_LEN             (MIPS_DURATION_SEC*SAMPLING_RATE)/FRAME_RATE

extern void reset_timer();
extern void start_timer();
extern void stop_timer();
extern unsigned int getCycles();
extern struct t_mips_info o_mips_info;
extern float mips_update();
#endif // configUSE_MEASURE_MIPS

extern void am_board_init(void);
extern void timerA0_init(void);
extern void am_gpio_isr(void);


#ifdef __cplusplus
}
#endif

#endif /* BOARD_SETUP_H_ */
