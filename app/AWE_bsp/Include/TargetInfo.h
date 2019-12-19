#ifndef _TARGETINFO_H
#define _TARGETINFO_H
//
// AWE related headers
//
// Version Information
#define USER_VER 20190801
//
// AWE configuration
//
#define NUM_CORES                   1
#define CORE_ID                     0
#define CORE_SPEED                  96e6f
#define PROFILE_SPEED               12e6f
#define HAS_FLOAT_SUPPORT           1
#define HAS_FLASH_FILESYSTEM        0
#define HAS_GPIO                    1
#define NO_INPUT_PINS               1
#define NO_OUTPUT_PINS              1
#define IS_SMP                      0
#define NUM_AUDIO_THREADS           1
#define AUDIO_SAMPLE_RATE           16000.0f
#define AUDIO_BLOCK_SIZE            80
#define IS_COMPLEX                  0
#define SAMPLE_SIZE_IN_BYTES        4

#define INPUT_CHANNEL_COUNT         2
#define OUTPUT_CHANNEL_COUNT        1
/* ----------------------------------------------------------------------
** Specify the size of each of the heaps on this target
** ------------------------------------------------------------------- */
#define MASTER_HEAP_SIZE		    (1024*30)
#define FASTB_HEAP_SIZE			    (1024*10)
#define SLOW_HEAP_SIZE			    (1024*30)

/* ----------------------------------------------------------------------
** Specify communication buffer size
** ------------------------------------------------------------------- */
#define MAX_COMMAND_BUFFER_LEN      264


/* ----------------------------------------------------------------------
** Specify which modules to include on this target
** ------------------------------------------------------------------- */
#include "ModuleList.h"

#endif	// _TARGETINFO_H
