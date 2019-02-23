#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices.h"
#include "am_util.h"

//*****************************************************************************
//
// Sleep function called from FreeRTOS IDLE task.
// Do necessary application specific Power down operations here
// Return 0 if this function also incorporates the WFI, else return value same
// as idleTime
//
//*****************************************************************************
uint32_t am_freertos_sleep(uint32_t idleTime)
{
//#if USE_OUTPUT_BUFFER_SPI
//    if (am_hal_iom_fifo_full_slots(IOM0 == 0x00))
//    {
//       configure_iom_sleep(0);
//    }
//#endif
//#if USE_OUTPUT_BUFFER_UART0
//    uint32_t TxBuff;
//    uint32_t RxBuff;
//    am_hal_uart_get_status_buffered(0, &RxBuff, &TxBuff);
//    if (TxBuff == 0)
//    {
//        configure_uart_sleep(0);
//    }
//#endif
//#if USE_OUTPUT_BUFFER_UART1
//    uint32_t TxBuff;
//    uint32_t RxBuff;
//    am_hal_uart_get_status_buffered(0, &RxBuff, &TxBuff);
//    if (TxBuff == 0)
//    {
//       configure_uart_sleep(1);
//    }
//#endif
//    am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_NORMAL);
    am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
    return 0;
}

//*****************************************************************************
//
// Recovery function called from FreeRTOS IDLE task, after waking up from Sleep
// Do necessary 'wakeup' operations here, e.g. to power up/enable peripherals etc.
//
//*****************************************************************************
void am_freertos_wakeup(uint32_t idleTime)
{
    return;
}


//*****************************************************************************
//
// FreeRTOS debugging functions.
//
//*****************************************************************************
void
vApplicationMallocFailedHook(void)
{
    //
    // Called if a call to pvPortMalloc() fails because there is insufficient
    // free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    // internally by FreeRTOS API functions that create tasks, queues, software
    // timers, and semaphores.  The size of the FreeRTOS heap is set by the
    // configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h.
    //
    while (1);
}

void
vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    (void) pcTaskName;
    (void) pxTask;

    //
    // Run time stack overflow checking is performed if
    // configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    // function is called if a stack overflow is detected.
    //
    while (1)
    {
        __asm("BKPT #0\n") ; // Break into the debugger
    }
}

