//*****************************************************************************
//
//! @file am_app_utils_stdio.c
//!
//! @brief A few printf-style functions for freeRTOS application use
//!
//! Functions for performing printf-style operations without dynamic memory
//! allocation.
//
//*****************************************************************************
#include "am_util.h"
#include "am_app_utils_stdio.h"

//*****************************************************************************
//
// Global Variables
//
//*****************************************************************************

// function pointer for printf
am_app_utils_stdio_printf_t g_pfnPrintf = NULL;

// print buffer index
uint32_t ui32BuffIndx = 0;

// buffer for printf
//char g_prStdioBuff[AM_APP_STDIO_BUFFNUM][AM_APP_PRINTF_BUFFSIZE];
char g_prStdioBuff[AM_APP_PRINTF_TOTAL_BUFFSIZE];

//*****************************************************************************
//
//! @brief Sets the interface for printf calls.
//!
//! @param pfnPrintFunc - Function pointer to be used to print to interface
//!
//! This function initializes the global print function which is used for
//! printf. This allows users to define their own printf interface and pass it
//! in as an am_app_utils_stdio_print_t type. 
//!
//! @return None.
//
//*****************************************************************************
void
am_app_utils_stdio_printf_init(am_app_utils_stdio_printf_t pfnPrintFunc)
{
    g_pfnPrintf = pfnPrintFunc;
}


//*****************************************************************************
//
//! @brief A lite version of printf()
//!
//! @param *pcFmt - Pointer to formatter string
//!
//!
//!
//! @return uint32_t representing the number of characters printed.
//
// *****************************************************************************
uint32_t
am_app_utils_stdio_printf(uint8_t print_type, const char *pcFmt, ...)
{
    uint32_t ui32NumChars;
    uint8_t print_buff[AM_APP_PRINTF_BUFFSIZE]; // local buffer to handle the data

    AM_CRITICAL_BEGIN;
    
    configASSERT(strlen(pcFmt) < AM_APP_PRINTF_BUFFSIZE);
    
    //
    // Convert to the desired string.
    //
    va_list pArgs;
    va_start(pArgs, pcFmt);
    ui32NumChars = am_util_stdio_vsprintf((char *)print_buff, pcFmt, pArgs);
    va_end(pArgs);

    if(ui32BuffIndx + ui32NumChars > (AM_APP_PRINTF_TOTAL_BUFFSIZE - 1))
    {
        ui32BuffIndx = 0;
    }
    // move data into global print buffer
    memcpy((char *)(&g_prStdioBuff[ui32BuffIndx]), (char *)print_buff, ui32NumChars);
    g_prStdioBuff[ui32BuffIndx + ui32NumChars] = NULL;
    
    //
    // This is where we print the buffer to the configured interface.
    //
    if(g_pfnPrintf)
        g_pfnPrintf(ui32BuffIndx, print_type);
    
    ui32BuffIndx += ui32NumChars + 1;   //add 1 byte NULL
    
    AM_CRITICAL_END;

    //
    // return the number of characters printed.
    //
    return ui32NumChars;
}


