#ifndef BOARD_SETUP_H_
#define BOARD_SETUP_H_

#include <stdint.h>
#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"

//#define USE_XTAL    1
#if USE_XTAL
#define BC_CLKSRC   "XTAL"
#else
#define BC_CLKSRC   "LFRC"
#endif

#ifdef AM_BSP_NUM_LEDS
#define NUM_LEDS    AM_BSP_NUM_LEDS
#else
#define NUM_LEDS    5       // Make up an arbitrary number of LEDs
#endif

extern const am_hal_gpio_pincfg_t g_deepsleep_button0;
extern am_hal_ctimer_config_t g_sTimer0; 
extern volatile uint32_t g_ui32TimerCount;

extern void DebugLog(const char* s);
extern void DebugLogInt32(int32_t i);
extern void DebugLogUInt32(uint32_t i);
extern void DebugLogHex(uint32_t i);
extern void DebugLogFloat(float i);


extern void timerA0_init(void);
extern void am_gpio_isr(void);






#endif /* BOARD_SETUP_H_ */
