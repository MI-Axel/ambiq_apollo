/* this file is the header file of the audio platform configuration */

#ifndef AM_APP_MIC_VERIF_CONFIG_H
#define AM_APP_MIC_VERIF_CONFIG_H

#include <stdint.h>

//
// CONFIG file of microphone verification process
// Now, the whole process concludes 2 procedure: microphone calibration and microphone THD calculation.
// LED0, system breathing LED, indicates system running
// BTN0, LED1, press BTN0, LED1 on means microphone calibration on-going; LED1 off means microphone cal ends.
// BTN1, LED2, press BTN1, LED2 on means microphone THD measuing; LED2 off means THD measurement ends.

#define AM_APP_MIC_CALIBRATION              1

#define AM_APP_MIC_THD                      1

//
// Platform support function configuration
//

/* STDIO configuration */
#define configUSE_UART_PRINTF               1
#define configUSE_SWO_PRINTF                0
#define configUSE_RTT_PRINTF                0


/* Data Block Output configuration */
#define configUSE_RTT_DATA_OUTPUT           0

/* SEGGER sysview configuration */
#define configUSE_SYSVIEW                   0

/* Burst mode always on */
#define configUSE_BURST_ALWAYS_ON           1






























#endif /* AM_AUDIO_PLATFORM_CONFIG_H */
