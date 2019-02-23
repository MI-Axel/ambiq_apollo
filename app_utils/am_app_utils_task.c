//*****************************************************************************
//
//! @file am_app_utils_task.c
//!
//! @brief FreeRTOS task providing overall control of the Apollo application.
//!
//! This module implements a factory for RTOS task and queues. The module
//! encapsulates the creation and maintenance of FreeRTOS tasks to simplify
//! the structure of a FreeRTOS multi-tasking application.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision v1.2.9-459-g671fc0f-wearable-dev-framework of the AmbiqSuite Development Package.
//
//*****************************************************************************
#include "am_app_utils_macros.h"
#include "am_app_utils_task.h"
#include "am_app_utils.h"



//*****************************************************************************
//
// Initialize the tasks list 
//
//
// Returns true if success.
//
//*****************************************************************************
void am_app_utils_task_init(am_app_utils_task_t* pTaskList, uint32_t taskCount)
{
	uint32_t i = 0;

    for(i=0 ; i<taskCount; i++)
	{
		pTaskList[i].task = NULL;
		pTaskList[i].queue = NULL;
	}
}

//*****************************************************************************
//
// Create the RTOS task and queue specified by indx, with the specified setup.
//
// This may block and if it does it blocks forever.
//
// Returns true if message successfully sent.
//
//*****************************************************************************
void 
am_app_utils_task_create(am_app_utils_task_setup_t setup, am_app_utils_task_t* pTaskList)
{
    xTaskCreate(setup.pxTaskCode, setup.pcName, setup.usStackDepth, setup.pvParameters, setup.uxPriority, &(pTaskList[setup.indx].task));
	configASSERT(pTaskList[setup.indx].task != NULL);
	pTaskList[setup.indx].queue = xQueueCreate(setup.uxQueueLength, sizeof(am_app_utils_task_queue_element_t));  
	configASSERT(pTaskList[setup.indx].queue != NULL);
//	tasks[setup.indx].parent = setup.parent;
//	vTaskSetApplicationTaskTag( tasks[setup.indx].task, ( TaskHookFunction_t) setup.indx );
}

//*****************************************************************************
//
// Initializes all tasks
//
//*****************************************************************************
void
am_app_utils_task_create_all_tasks(am_app_utils_task_setup_t *setup_array, am_app_utils_task_t* pTaskList, uint32_t setupLen)
{
    uint8_t task = 0;

	for(task = 0; task<setupLen; task++)
	{
		// Spawn all tasks
		am_app_utils_task_create(setup_array[task], pTaskList);
	}

}
//*****************************************************************************
//
// Initialize system timers 
//
//
// Returns true if success.
//
//*****************************************************************************

void am_app_utils_timer_create(am_app_utils_timer_setup_t setup, TimerHandle_t* pTimerList)
{
    pTimerList[setup.indx] = xTimerCreate(setup.pcTimerName, setup.xTimerPeriodInTicks, 
                                                setup.uxAutoReload, 0, setup.pxTaskCode);

}

//*****************************************************************************
//
// Initializes all timers
//
//*****************************************************************************
void
am_app_utils_timer_create_all_timers(am_app_utils_timer_setup_t *setup_array, TimerHandle_t* pTimerList, uint32_t setupLen)
{
    uint8_t timer = 0;

	for(timer = 0; timer<setupLen; timer++)
	{
		// Spawn all timers
		am_app_utils_timer_create(setup_array[timer], pTimerList);
	}

}

//*****************************************************************************
//
// Send a message from the Source task to Dest queue
//
// This may block and if it does it blocks forever.
//
// Returns true if message successfully sent.
//
//*****************************************************************************
bool
am_app_utils_task_send(am_app_utils_task_t* pTaskList, const uint32_t SourceIndx, const uint32_t DestIndx, uint32_t ui32MessageType, 
                    uint32_t ui32Info, am_app_utils_ring_buffer_t *pData)
{
		BaseType_t retval = pdFAIL;
		am_app_utils_task_queue_element_t Element;
		Element.Source = SourceIndx;
        
        configASSERT(ui32MessageType < AM_APP_MESSAGE_MAX);
		Element.ui32MessageType = ui32MessageType;
		switch(Element.ui32MessageType)
        {
            case AM_APP_MESSAGE_SHORT:
                Element.info.ui32Note = ui32Info;
                break;
            case AM_APP_MESSAGE_LONG:
                Element.info.ui32Length = ui32Info;
                break;
            case AM_APP_MESSAGE_STR:
                Element.info.ui32Indx = ui32Info;
                break;
            default:
                break;
        }
        Element.pDataBuffer = pData;
		if(pTaskList[DestIndx].queue != NULL)
		{
			retval = xQueueSendToBack(pTaskList[DestIndx].queue, &Element, 0 );
		}
		
		return (retval != pdFAIL);
}

//*****************************************************************************
//
// Send a message from the Source task to the Dest Queue, from an ISR
//
// This may block and if it does it blocks forever.
//
// Returns true if message successfully sent.
//
//*****************************************************************************
bool
am_app_utils_task_send_fromISR(am_app_utils_task_t* pTaskList, const uint32_t SourceIndx, const uint32_t DestIndx, uint32_t ui32MessageType, 
                           uint32_t ui32Info, am_app_utils_ring_buffer_t *pData)
{
		BaseType_t retval = pdFAIL;
		am_app_utils_task_queue_element_t Element;
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		
        Element.Source = SourceIndx;
		Element.ui32MessageType = ui32MessageType;
		switch(Element.ui32MessageType)
        {
            case AM_APP_MESSAGE_SHORT:
                Element.info.ui32Note = ui32Info;
                break;
            case AM_APP_MESSAGE_LONG:
                Element.info.ui32Length = ui32Info;
                break;
            case AM_APP_MESSAGE_STR:
                Element.info.ui32Indx = ui32Info;
                break;
            default:
                break;
        }
        Element.pDataBuffer = pData;

		if(pTaskList[DestIndx].queue != NULL)
		{
			retval = xQueueSendFromISR(pTaskList[DestIndx].queue , &Element, &xHigherPriorityTaskWoken );
		}

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    
    return (retval != pdFAIL);
}

//*****************************************************************************
//
// Read a message from the Queue specified by indx.
//
// This may block and if it does it blocks forever.
//
// Returns true if message successfully read.
//
//*****************************************************************************
bool
am_app_utils_task_read(am_app_utils_task_t* pTaskList, const uint32_t indx, am_app_utils_task_queue_element_t *Element)
{
		BaseType_t retval = pdFAIL;
		if(pTaskList[indx].queue != NULL)
		{
			retval = xQueueReceive(pTaskList[indx].queue, Element, portMAX_DELAY );
		}
    
		return retval; 
}

//*****************************************************************************
//
// Get the RTOS task handle from the app_task specified by indx.
//
// This may block and if it does it blocks forever.
//
// Returns true if message successfully read.
//
//*****************************************************************************
TaskHandle_t am_app_utils_task_get_task_handle(am_app_utils_task_t* pTaskList, const uint32_t indx)
{
	return pTaskList[indx].task;
}



//*****************************************************************************
//
// Resume the task specified by indx.
//
//*****************************************************************************
void am_app_utils_task_resume(am_app_utils_task_t* pTaskList, const uint32_t indx)
{
	if(pTaskList[indx].task != NULL)
	{
		vTaskResume(pTaskList[indx].task);
	}
}

void am_app_utils_task_suspend(am_app_utils_task_t* pTaskList, const uint32_t indx)
{
	if(pTaskList[indx].task != NULL)
	{
		vTaskSuspend(pTaskList[indx].task);
	}
}
