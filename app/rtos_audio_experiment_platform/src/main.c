/* main function source file of FreeRTOS audio experiment platform */

//*****************************************************************************
//
// Required built-ins.
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//*****************************************************************************
//
// Standard AmbiqSuite includes.
//
//*****************************************************************************
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices.h"
#include "am_util.h"

//*****************************************************************************
//
// FreeRTOS include files.
//
//*****************************************************************************
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
#include "timers.h"
//*****************************************************************************
#include "SEGGER_SYSVIEW.h"

#include "am_AEP_config.h"
#include "am_AEP_init.h"
#include "am_app_utils_rtt_recorder.h"



int main()
{
    //
    // Set the clock frequency
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);

    //
    // Set the default cache configuration
    //
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();

    //
    // Configure the board for low power.
    //
    am_bsp_low_power_init();
  
    //
    // clear stimer configuration, it may cause exception if retain old value.
    //   
    am_hal_stimer_config(0x03);


    //
    // Hardware initialization here
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_XTAL_START, 0);


    am_AEP_init();

#if configUSE_SYSVIEWER
    //
    // Configure the SEGGER SystemView Interface.
    //
    SEGGER_SYSVIEW_Conf();

#endif

//    am_util_stdio_printf("FreeRTOS stars to operate!\r\n");
    //
    // Start the scheduler.
    //
    vTaskStartScheduler();

  return 0;
}
