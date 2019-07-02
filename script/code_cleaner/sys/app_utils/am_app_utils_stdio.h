//*****************************************************************************
//
//! @file am_app_utils_stdio.h
//!
//! @brief RTOS printf functions for app layer use
//! 
//!
//
//*****************************************************************************
#ifndef AM_APP_UTILS_STDIO_H
#define AM_APP_UTILS_STDIO_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "am_app_utils_task.h"
#include "am_app_utils_ring_buffer.h"

#define AM_APP_STDIO_BUFFNUM                        8
#define AM_APP_PRINTF_BUFFSIZE                      256     // has to be 256, there are long prints... 
#define AM_APP_PRINTF_TOTAL_BUFFSIZE                (AM_APP_STDIO_BUFFNUM*AM_APP_PRINTF_BUFFSIZE) 

typedef void (*am_app_utils_stdio_printf_t)(uint32_t indx, uint8_t print_type);

extern uint32_t ui32BuffIndx;

// buffer for printf
extern char g_prStdioBuff[AM_APP_PRINTF_TOTAL_BUFFSIZE];

void am_app_utils_stdio_printf_init(am_app_utils_stdio_printf_t pfnPrintFunc);

uint32_t am_app_utils_stdio_printf(uint8_t print_type, const char *pcFmt, ...);

#endif
