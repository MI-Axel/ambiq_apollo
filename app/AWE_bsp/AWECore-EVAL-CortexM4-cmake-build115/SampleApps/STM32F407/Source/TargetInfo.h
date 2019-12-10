/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     TargetInfo.h
********************************************************************************
*
*     Description:  All target specific information
*
*     Copyright:    (c) 2018 DSP Concepts, Inc. All rights reserved.
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
*
*******************************************************************************/
#ifndef _TARGETINFO_H
#define _TARGETINFO_H

#define USER_VER 20190910

#define NUM_INSTANCES 1
#define INSTANCE_ID 0
#define CORE_SPEED 168e6f
#define SAMPLE_SPEED 168e6f
#define HAS_FLOAT_SUPPORT 1
#define HAS_FLASH_FILESYSTEM 1
#define HAS_GPIO 1
#define NO_HW_INPUT_PINS 1
#define NO_HW_OUTPUT_PINS 1
#define IS_SMP 0
#define NUM_AUDIO_THREADS 2
#define AUDIO_SAMPLE_RATE 48000.0f
#define AUDIO_BLOCK_SIZE 32
#define IS_COMPLEX 0
#define SAMPLE_SIZE_IN_BYTES 4

/* ----------------------------------------------------------------------
** Specify the size of each of the heaps on this target
** ------------------------------------------------------------------- */
#define MASTER_HEAP_SIZE		(1024*12)
#define FASTB_HEAP_SIZE			(1024*16)
#define SLOW_HEAP_SIZE			(1024*6)

/* ----------------------------------------------------------------------
** Specify communication buffer size
** ------------------------------------------------------------------- */
#define MAX_COMMAND_BUFFER_LEN  264

/* ----------------------------------------------------------------------
** Specify flash memory available for flash file system
** ------------------------------------------------------------------- */
#define FLASH_MEMORY_SIZE_IN_BYTES 0x08100000
#define FLASH_MEMORY_SIZE_IN_WORDS (0x08100000 >> 2)
#define ERASEABLE_BLOCKSIZE 0x20000
#define FILE_SYSTEM_START_OFFSET 0x08080000
#define FLASH_START_OFFSET 0x00000000

/* ----------------------------------------------------------------------
** Specify which modules to include on this target
** ------------------------------------------------------------------- */
#include "ModuleList.h"

#endif	// _TARGETINFO_H
