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

#if configUSE_RTT_DATA_OUTPUT
        //
        // Record the raw PCM data and send over RTT
        //
//        if(g_rttRecordingFlag == 1)
//            am_app_utils_rtt_record((void*)g_ui32PCMDataBuff, PCM_FRAME_SIZE*PCM_DATA_BYTES); 
#endif /* USE_RTT_DATA_OUTPUT */ 

//        am_util_debug_printf("PDM DCMP interrupt, pick g_ui32PDMDataBuffer[5] = 0x%8x\n", g_ui32PDMDataBuffer[5]);
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

