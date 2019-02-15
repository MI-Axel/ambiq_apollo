/* this file is the header file of the audio platform configuration */

#ifndef AM_AUDIO_PLATFORM_CONFIG_H
#define AM_AUDIO_PLATFORM_CONFIG_H

#include <stdint.h>

//
// Platform main objective definitionn
//

#define AM_AEP_OPUS_TEST                    1

#define AM_AEP_MEMCPY_TEST                  0

#define AM_AEP_ALLOC_FREE_TEST              0

//
// Platform support function configuration
//

/* STDIO configuration */
#define configUSE_UART_PRINTF               1
#define configUSE_SWO_PRINTF                0
#define configUSE_RTT_PRINTF                0


/* Data Block Output configuration */
#define configUSE_RTT_DATA_OUTPUT           1

/* SEGGER sysview configuration */
#define configUSE_SYSVIEW                   0

/* Burst mode always on */
#define configUSE_BURST_ALWAYS_ON           1
































#endif /* AM_AUDIO_PLATFORM_CONFIG_H */
