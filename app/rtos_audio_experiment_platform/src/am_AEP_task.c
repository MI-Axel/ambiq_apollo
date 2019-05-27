#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices.h"
#include "am_util.h"

#include "am_app_utils_rtt_recorder.h"
#include "am_app_utils_task.h"

#include "am_AEP_config.h"
#include "am_AEP_init.h"
#include "am_AEP_task.h"
#include "am_opus.h"

// AEP led task
void am_AEP_led_task(void *pvParameters)
{
    const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
    const TickType_t xDelay200ms = pdMS_TO_TICKS(200);
    const TickType_t xDelaySwirl = pdMS_TO_TICKS(35);
    am_app_utils_task_queue_element_t QueueElement;
    while(1)
    {
        am_app_utils_task_read(am_AEP_tasks, AM_AEP_TASK_LED, &QueueElement);

        am_devices_led_toggle(am_bsp_psLEDs, 0);
    
    }

}

// AEP button task
void am_AEP_button_task(void *pvParameters)
{
    const TickType_t xDelay100ms = pdMS_TO_TICKS(100);
    uint32_t ui32PinStatus = 1;
    uint32_t ui32DebounceLoop = 0;
    uint32_t ui32DebounceTimer = 0;
    am_app_utils_task_queue_element_t QueueElement;
    while(1)
    {
        am_hal_gpio_state_read(AM_BSP_GPIO_BUTTON0, AM_HAL_GPIO_INPUT_READ, &ui32PinStatus);
        
        if((ui32PinStatus==0)&&(ui32DebounceLoop<10))
            ui32DebounceLoop++;
        else if((ui32PinStatus==1)&&(ui32DebounceLoop<=2))
            ui32DebounceLoop = 0;
        //
        //Key action is confirmed
        //
        if((ui32DebounceLoop>2)&&(ui32PinStatus==1))
        {
            ui32DebounceLoop = 0;
#if configUSE_RTT_LOGGER
            if(g_ui8RttRecordFlag == 0)
            {
                g_ui8RttRecordFlag = 1;
                am_devices_led_on(am_bsp_psLEDs, 2);      
            }
            else
            {
                g_ui8RttRecordFlag = 0;
                am_devices_led_off(am_bsp_psLEDs, 2);
            }
#endif // configUSE_RTT_LOGGER
        }
        vTaskDelay(xDelay100ms);    

    }

}

#if configUSE_AUDIO_CODEC

void am_AEP_codec_task(void *pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;
#if configUSE_PDM_DATA
    int32_t in32LRSample[PCM_FRAME_SIZE];
    int16_t in16LeftSample;
    int16_t in16RightSample;
#endif // configUSE_PDM_DATA

    uint32_t index = 0;
    int16_t in16PCMDataBuff[PCM_FRAME_SIZE];
    uint32_t g_ui32FrameSize = 320;                 // encoder frame size
    uint32_t g_ui32EncOutputBytes = 80;             // FrameSize * 2 bytes / 8 

    while(1)
    {
        am_app_utils_task_read(am_AEP_tasks, AM_AEP_TASK_CODEC, &QueueElement);
        switch(QueueElement.ui32MessageType)
        {
            case AM_APP_MESSAGE_SHORT:
                break;

            case AM_APP_MESSAGE_LONG:
                AM_CRITICAL_BEGIN;
                am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, in32LRSample, QueueElement.info.ui32Length);
                AM_CRITICAL_END;
                break;

            default: 
                break;
        }
        
        for(index=0; index<g_ui32FrameSize; index++)
        {
            in16LeftSample = in32LRSample[index] >>16;           
            in16RightSample = in32LRSample[index] & 0x0000FFFF;
            in16PCMDataBuff[index] = (int16_t) ((in16LeftSample+in16RightSample)/2);
        }

   
        g_opusEncRet = opus_encode(g_opusEnc, (opus_int16*)&in16PCMDataBuff, g_ui32FrameSize, g_opusOutputBuff, g_ui32EncOutputBytes);

#if (configUSE_RTT_LOGGER && configUSE_RTT_CODEC)
        //
        // Record the raw PCM data and send over RTT
        //
        if(g_ui8RttRecordFlag == 1)
            am_app_utils_rtt_record(g_opusOutputBuff, g_ui32EncOutputBytes); 
#endif /* configUSE_RTT_LOGGER && configUSE_RTT_PCM */ 
        
    }
}

#endif // configUSE_AUDIO_CODEC


//*****************************************************************************
//
// Software timer callback functions
//
//*****************************************************************************
void am_AEP_timer_heart_beat_callback(TimerHandle_t xTimer)
{
//    am_devices_led_toggle(am_bsp_psLEDs, 0);
    am_app_utils_task_send(am_AEP_tasks, AM_AEP_ISR_GPIO, AM_AEP_TASK_LED, 
                   AM_APP_MESSAGE_SHORT, 0, NULL);
}

