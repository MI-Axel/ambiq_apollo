/* This file is header file of the driver of PDM functions*/
#ifndef AUDIO_DRIVER_H_
#define AUDIO_DRIVER_H_

#include <stdint.h>
#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"


extern void am_pdm0_isr(void);

extern void am_ctimer_isr(void);

extern void am_gpio_isr(void);

#endif /* AUDIO_DRIVER_H_ */
