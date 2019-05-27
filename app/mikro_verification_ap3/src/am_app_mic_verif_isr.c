/* This file is the driver of PDM functions*/

/* AEP config header file */ 
#include "am_app_mic_verif_config.h"

#include "am_app_mic_verif_board_setup.h"
#include "am_app_mic_verif_isr.h"

#if AM_APP_MIC_CALIBRATION
#include "am_mikro_calibration.h"
#endif // AM_AEP_MIKRO_CALIBRATION

/* application layer utils header file */
#include "am_app_utils_ring_buffer.h"


//*****************************************************************************
//
// PDM interrupt handler.
//
//*****************************************************************************
void am_pdm0_isr(void) 
{
#if configUSE_SYSVIEW    
    SEGGER_SYSVIEW_RecordEnterISR();
#endif
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
 
#if AM_APP_MIC_CALIBRATION
        if((g_ui8MicCalFlag == 1) && (g_ui8PcmDataReadyFlag==0))
        {
            am_app_utils_ring_buffer_push(&am_sys_ring_buffers[AM_APP_RINGBUFF_PCM], (void*)g_ui32PCMDataBuff, PCM_FRAME_SIZE*PCM_DATA_BYTES);
            g_ui32SampleNum += PCM_FRAME_SIZE;
            if(g_ui32SampleNum >= g_ui32WindowLen)
            {
                g_ui8PcmDataReadyFlag = 1;
            }
        }
#endif // AM_AEP_MIKRO_CALIBRATION
    }
    else if(ui32Status & (AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF))
    {
        am_hal_pdm_fifo_flush(PDMHandle);
    }

#if configUSE_SYSVIEW
    SEGGER_SYSVIEW_RecordExitISR(); //emit Exit ISR signal
#endif

}

//*****************************************************************************
//
// Timer Interrupt Service Routine (ISR)
//
//*****************************************************************************
void
am_ctimer_isr(void)
{
    //
    // Increment count and set limit based on the number of LEDs available.
    //
    g_ui32TimerCount++;
    if ( g_ui8DebounceFlag == 1)
    {
        g_ui32DebounceTimerCount++;

        if(g_ui32DebounceTimerCount > 300)
        {
            g_ui8ButtonPushedFlag = 1;
            g_ui8DebounceFlag = 0;
        }
    } 

    //
    // Clear TimerA0 Interrupt (write to clear).
    //
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA0);
}


//*****************************************************************************
// GPIO ISR
// Will enable the PDM, set number of frames transferred to 0, and turn on LED
//*****************************************************************************
void am_gpio_isr(void) 
{
    uint64_t ui64Status;
//
// Read and clear GPIO interrupt status
//
    am_hal_gpio_interrupt_status_get(false, &ui64Status);
    am_hal_gpio_interrupt_clear(ui64Status);
    //
    // debounce.
    //
    if(g_ui8DebounceFlag == 0)
    {
        if(ui64Status & AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0))
            g_sysKeyValue = AM_APP_KEY_0;
        else if(ui64Status & AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON1))
            g_sysKeyValue = AM_APP_KEY_1;
        else if(ui64Status & AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON2))
            g_sysKeyValue = AM_APP_KEY_2;

        g_ui8DebounceFlag = 1;
        g_ui32DebounceTimerCount = 0;
    }  
    //
    // Clear the GPIO Interrupt (write to clear).
    //
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));

}

