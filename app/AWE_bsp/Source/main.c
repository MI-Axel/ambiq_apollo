
/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     main.c
********************************************************************************
*
*     Description:  AudioWeaver target main program
*
*******************************************************************************/
#include <stdint.h>
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

#include "Platform.h"

int main(void)
{    
    // Initialize AWE platform
    awe_pltInit(); 
	
    // Initialize the framework
    awe_fwInit(&g_AWEInstance); 
//    awe_fwPacketExecuteArray(&g_AWEInstance, (unsigned int*) InitCommands, InitCommands_Len);
    while(TRUE) 
    {
     /* breathing LED */
        if (g_ui32TimerCount >=1000)
        {
            g_ui32TimerCount = 0;
            am_devices_led_toggle(am_bsp_psLEDs, 0);
        }
        
        // Process any platform tasks
        awe_pltTick();
			
        // Process any framework tasks
       	awe_fwTick(&g_AWEInstance);
       
//        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
        
    }   // End while
	
}   // End main
