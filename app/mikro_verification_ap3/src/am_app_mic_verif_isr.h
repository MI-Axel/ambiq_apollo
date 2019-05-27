/* This file is header file of the driver of PDM functions*/
#ifndef AUDIO_DRIVER_H_
#define AUDIO_DRIVER_H_

#include <stdint.h>

#include "am_app_mic_verif_config.h"

#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"

#if AM_APP_MIC_CALIBRATION
#include "am_mikro_calibration.h"
extern uint8_t g_ui8MicCalStatus;    
extern uint8_t g_ui8MicCalFlag;
extern float g_pfMicScalar[2];
extern uint32_t g_ui32WindowLen;
extern uint32_t g_ui32SampleNum;
#endif // AM_APP_MIC_CALIBRATION


extern void am_pdm0_isr(void);

extern void am_ctimer_isr(void);

extern void am_gpio_isr(void);

#endif /* AUDIO_DRIVER_H_ */
