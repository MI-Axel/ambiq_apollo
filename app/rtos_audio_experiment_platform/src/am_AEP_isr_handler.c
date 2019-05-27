/* this file contains the ISR handlers of AEP */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//*****************************************************************************
// Standard AmbiqSuite includes.
//*****************************************************************************
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices.h"
#include "am_util.h"

//*****************************************************************************
// FreeRTOS include files.
//*****************************************************************************
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
//*****************************************************************************
#include "SEGGER_SYSVIEW.h"

#include "am_app_utils_ring_buffer.h"
#include "am_app_utils_task.h"
#include "am_app_utils_rtt_recorder.h"

// user include
#include "am_AEP_config.h"
#include "am_AEP_init.h"
#include "am_AEP_board_setup.h"


//*****************************************************************************
//
// PDM interrupt handler.
//
//*****************************************************************************
#if configUSE_PDM_DATA
void am_pdm0_isr(void) 
{
#if configUSE_SYSVIEWER    
    SEGGER_SYSVIEW_RecordEnterISR();
#endif // configUSE_SYSVIEWER
    uint32_t ui32Status;
    //
    // Read the interrupt status.
    //
    am_hal_pdm_interrupt_status_get(PDMHandle, &ui32Status, true);
    am_hal_pdm_interrupt_clear(PDMHandle, ui32Status);
    
    if (ui32Status & AM_HAL_PDM_INT_DCMP)
    {
        // trigger next traction
        PDMn(0)->DMATOTCOUNT = PCM_FRAME_SIZE*PCM_DATA_BYTES;  // FIFO unit in bytes

        am_app_utils_ring_buffer_push(&am_AEP_ring_buffers[AM_AEP_RINGBUFF_PDM], g_ui32PCMDataBuff, PCM_FRAME_SIZE*PCM_DATA_BYTES);

#if (configUSE_RTT_LOGGER && configUSE_RTT_PCM)
        //
        // Record the raw PCM data and send over RTT
        //
        if(g_ui8RttRecordFlag == 1)
            am_app_utils_rtt_record(g_ui32PCMDataBuff, PCM_FRAME_SIZE*PCM_DATA_BYTES); 
#endif /* configUSE_RTT_LOGGER && configUSE_RTT_PCM */ 

#if configUSE_AUDIO_CODEC
        am_app_utils_task_send_fromISR(am_AEP_tasks, AM_AEP_ISR_PDM, AM_AEP_TASK_CODEC, 
                   AM_APP_MESSAGE_LONG, PCM_FRAME_SIZE*PCM_DATA_BYTES, &am_AEP_ring_buffers[AM_AEP_RINGBUFF_PDM]);
#endif // configUSE_AUDIO_CODEC
    }
    else if(ui32Status & (AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF))
    {
        am_hal_pdm_fifo_flush(PDMHandle);
    }

#if configUSE_SYSVIEWER
    SEGGER_SYSVIEW_RecordExitISR(); //emit Exit ISR signal
#endif // configUSE_SYSVIEWER

}
#endif // configUSE_PDM_DATA

// GPIO isr handle the buttons on board
void am_gpio_isr(void)
{
    uint64_t ui64IntStatus = 0;
    uint32_t ui32KeyValue = 0;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#if configUSE_SYSVIEWER    
    SEGGER_SYSVIEW_RecordEnterISR();
#endif // configUSE_SYSVIEWER
   
    //
    // Read and clear the GPIO interrupt status.
    //
    am_hal_gpio_interrupt_status_get(false, &ui64IntStatus);
    am_hal_gpio_interrupt_clear(ui64IntStatus);

    if(ui64IntStatus & AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0))
    {   
        am_hal_gpio_interrupt_disable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
        am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
        //
        // debounce.
        //
        if(g_ui8DebounceFlag == 0)
        {
            g_ui8DebounceFlag = 1;
            ui32KeyValue = AM_BSP_GPIO_BUTTON0;
//            xTimerStartFromISR(am_AEP_timers[AM_AEP_TIMER_DEBOUNCE], &xHigherPriorityTaskWoken);    
//            am_app_utils_task_send_fromISR(am_AEP_tasks, AM_AEP_ISR_GPIO, 2, 
//                   AM_APP_MESSAGE_SHORT, ui32KeyValue, NULL);
        }  

    }
    am_util_delay_us(200);
#if configUSE_SYSVIEWER
    SEGGER_SYSVIEW_RecordExitISR(); //emit Exit ISR signal
#endif // configUSE_SYSVIEWER

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}
