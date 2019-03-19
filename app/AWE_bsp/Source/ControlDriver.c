/*******************************************************************************
*
*               STM BSP Driver
*               ---------------
*
********************************************************************************
*     ControlDriver.c
********************************************************************************
*
*     Description:  AudioWeaver Control Driver for STM Discovery board
*
*     DSP Concepts, Inc.
*     1800 Wyatt Drive, Suite 14
*     Sunnyvale, CA 95054
*
*     Copyright (c) 2007 - 2017 DSP Concepts, Inc. All rights reserved.
*
*******************************************************************************/
#include "Platform.h"

#include "ModSink.h"
#include "ModDCSourceInt.h"

#define OBJECT_FOUND 0

extern void variableGetValue(uint32_t * nValue);

uint8_t isThereAnObject = 0;
uint8_t extendTime = 0;
uint8_t kwdTime = 0;
static uint8_t toggle = 0;
static UINT32 Value = 0;
static UINT32 ValueLast = 0;


// Structure with information needed to interact with the control
typedef struct {
    ModClassModule * pModule;
    UINT32 nPinNo;
}   CONTROL_TYPE;


// Need to keep track of how many source controls have been instantiated in the Model
UINT16 g_nInputControlCount = 0;
UINT16 g_nOutputControlCount = 0;

// This target board control inputs
const UINT16 InputCtrlID[CTRL_NUM_INPUTS] = {CTRL_BUTTON1};

// This target board control outputs
const UINT16 OutputCtrlID[CTRL_NUM_OUTPUTS] = {SINK_1_OBJECT_ID, SINK_2_OBJECT_ID};

//// Table of pointers to instantiated source control modules
CONTROL_TYPE g_InputControl[CTRL_NUM_INPUTS] = {NULL};

// Table of pointers to instantiated sink control modules
CONTROL_TYPE g_OutputControl[CTRL_NUM_OUTPUTS] = {NULL};

// Need to keep track of which I/O pin is assigned to each control
const UINT32 OutputCtrlPinNo[CTRL_NUM_OUTPUTS] = {1,2};

/**
 * @brief Look for and initialize any control module instances in the current AWE model
 */
void ControlInit(void)
{
    InstanceDescriptor * pInstance;
    UINT32 classID, ret;
    UINT16 n;

    g_nInputControlCount = 0;

    // Find any source control modules instantiated in the model
    for (n = 0; n < CTRL_NUM_INPUTS; n++)
    {
        // Find any sink control module instantiated in the model
        ret = awe_fwGetObjectByID(&g_AWEInstance, InputCtrlID[n], &pInstance, &classID);

        // Check the object found and the module assigned this object ID is of module class Source
        if((ret == OBJECT_FOUND) && (classID == CLASSID_DCSOURCEINT))
        {
            // Save the module instance in the control info structure
            g_InputControl[g_nInputControlCount].pModule = (ModClassModule *)pInstance;

            // Save the I/O pin number in the control info structure
//            g_InputControl[g_nInputControlCount].nPinNo = InputCtrlPinNo[n];

            g_nInputControlCount++;
        }
     }

    g_nOutputControlCount = 0;

    for (n = 0; n < CTRL_NUM_OUTPUTS; n++)
    {
        // Find any sink control module instantiated in the model
        ret = awe_fwGetObjectByID(&g_AWEInstance, OutputCtrlID[n], &pInstance, &classID);

        // Check the object found and the module assigned this object ID is of module class Sink
        if ((ret == OBJECT_FOUND) && (classID == CLASSID_SINK))
        {
            // Save the module instance in the control info structure
            g_OutputControl[g_nOutputControlCount].pModule = (ModClassModule *)pInstance;

            // Save the I/O pin number in the control info structure
            g_OutputControl[g_nOutputControlCount].nPinNo = OutputCtrlPinNo[n];

            g_nOutputControlCount++;
        }
    }
 

}   // End ControlInit


/**
* @brief Destroy I/O
*/
void ControlDestroy(void)
{
    g_nInputControlCount = 0;
    g_nOutputControlCount = 0;

}   // End ControlDestroy


/**
 * @brief  Perform control I/O
 */
void ProcessControlIO(void)
{
    UINT32 nPinValue;
    UINT16 n;


    if(in32AudioRunningFlag)
    {
//        u8queueValToSend = (u8queueValLED | u8queueValPULSE | u8queueAudioBuffer);

        // Process any source control modules
        for (n = 0; n < g_nInputControlCount; n++)
        {
            // Get the AWE module instance for this source control
            awe_modDCSourceIntInstance * pModule = (awe_modDCSourceIntInstance *)g_InputControl[n].pModule;

//            // Which GPIO pin is this control attached to
//            UINT32 nPinNo = g_InputControl[n].nPinNo;
//
//            // Get the current state of the control
//            awe_pltGPIOGetPin(nPinNo, &nPinValue);

            // Get the current state of the control variable
//            variableGetValue(&nPinValue);

            // Update the AWE module state
            pModule->value = (UINT32)nPinValue;
        }

        // Process any sink control modules
        for (n = 0; n < g_nOutputControlCount; n++)
        {
            if (n == 0)
            {
                // Get the AWE module instance for this sink control
                awe_modSinkInstance * pModule = (awe_modSinkInstance *)g_OutputControl[n].pModule;

                // Turn on LED if dB value is > 0dB, otherwise turn off
//                if(*(pModule->value) > 0.0f)
//                {
//                    if (toggle == 0)
//                    {
//                        am_app_KWD_reset_detected_flag();
//                        g_ui8KwdDetectedFlag = 1;
//
//                        #if configUSE_SYS_LOG
//                            am_app_KWD_log_print(AM_APP_TASK_MODEL_INFERENCE, KEY_WORD_GOT_MESSAGE);
//                        #endif
//#if configUSE_STDIO_PRINTF
//                        //am_app_printf("Keyword Detected! \n");
//                       
//                        AM_APP_LOG_WARNING("Keyword Detected! \n");
//                        
//#endif // #if configUSE_STDIO_PRINTF
//                        toggle = 1;
//
//                        #if configUSE_MODEL_INFERENCE
//                            am_app_utils_task_send(AM_APP_TASK_MODEL_INFERENCE, AM_APP_TASK_LED,
//                                                    AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
//                            #if configUSE_AUDIO_PRE_BUFF
//                                        
//                                #if (configUSE_SBC_BLUEZ || configUSE_MSBC_BLUEZ)
//                                    am_app_utils_task_send(AM_APP_TASK_MODEL_INFERENCE, AM_APP_TASK_CODEC,
//                                                        AM_APP_MESSAGE_LONG, BYTES_PER_DSPC_SAMPLE*PCM_SAMPLE_RATE_MS*AUDIO_PREBUFF_TIME_MS, 
//                                                        &am_KWD_ring_buffers[AM_APP_RINGBUFF_PRE_AUDIO_STREAM]);
//                                #endif
//
//                            #endif
//                        #endif
//                        xTimerStart(am_KWD_timers[AM_APP_TIMER_KWD_TIME_OUT], 0);
// 
//                    } 
//                } 
//                else
//                {      
//                    if (toggle == 1)
//                    {   
//                        am_app_KWD_reset_detected_flag();
//                        g_ui8KwdDetectedFlag = 1;
//
//                        #if configUSE_SYS_LOG
//                            am_app_KWD_log_print(AM_APP_TASK_MODEL_INFERENCE, KEY_WORD_GOT_MESSAGE);
//                        #endif
//#if configUSE_STDIO_PRINTF
////                        am_app_printf("Keyword Detected! \n");
//                            AM_APP_LOG_WARNING("Keyword Detected! \n");
//#endif // #if configUSE_STDIO_PRINTF
//                        toggle = 0;
//                        
//                        #if configUSE_MODEL_INFERENCE
//                            am_app_utils_task_send(AM_APP_TASK_MODEL_INFERENCE, AM_APP_TASK_LED,
//                                                    AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
//                            #if configUSE_AUDIO_PRE_BUFF
//                                        
//                                #if (configUSE_SBC_BLUEZ || configUSE_MSBC_BLUEZ)
//                                    am_app_utils_task_send(AM_APP_TASK_MODEL_INFERENCE, AM_APP_TASK_CODEC,
//                                                            AM_APP_MESSAGE_LONG, BYTES_PER_DSPC_SAMPLE*PCM_SAMPLE_RATE_MS*AUDIO_PREBUFF_TIME_MS, 
//                                                            &am_KWD_ring_buffers[AM_APP_RINGBUFF_PRE_AUDIO_STREAM]);
//                                #endif
//
//                            #endif
//                        #endif 
//                        xTimerStart(am_KWD_timers[AM_APP_TIMER_KWD_TIME_OUT], 0);
//                    }
//                
//                } 
            }
            else
            {
                // Get the AWE module instance for this sink control
                awe_modSinkInstance * pModule = (awe_modSinkInstance *)g_OutputControl[n].pModule;

                Value = (UINT32)(*(pModule->value));

                if (Value > ValueLast)
                {
//                    CmdValue = Value - ValueLast;

                }
                else
                {
                    extendTime = 0;
                }
                ValueLast = Value;
            }
        }
//        if(extendTime || kwdTime)
//        {
//            extendTime = 0;
//            kwdTime = 0;
//            am_hal_ctimer_int_disable(AM_HAL_CTIMER_INT_TIMERA1);
//            am_hal_ctimer_clear(1, AM_HAL_CTIMER_TIMERA);
//            am_hal_ctimer_period_set(1, AM_HAL_CTIMER_TIMERA, CMD_TIMEOUT_PERIOD, CMD_TIMEOUT_PERIOD);
//            am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA1);
//            am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA1);
//            am_hal_ctimer_start(1, AM_HAL_CTIMER_TIMERA);
//        }
    }
    else
    {
//        awe_pltGPIOSetPin(LED_KEYWORD, 0);  // keep LED off if Audio is not running
    }

      
} // End ProcessControlIO
