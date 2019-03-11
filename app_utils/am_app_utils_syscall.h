#ifndef AM_APP_UTILS_SYSCALL_H_
#define AM_APP_UTILS_SYSCALL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"

#include "am_app_utils.h"

#define AM_PART_RAM_LIMIT                           0x10060000              // Apollo3Blue has 384KB SRAM

#define AM_MEMORY_DEBUG                             1


extern void * _sbrk(int32_t incr);


extern void* am_alloc(size_t size);


extern void am_free(void* ptr);





















#endif // ifndef AM_APP_UTILS_SYSCALL_H_
