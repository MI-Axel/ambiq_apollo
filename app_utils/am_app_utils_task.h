
//*****************************************************************************
//
//! @file am_app_utils_task.h
//!
//! @brief RTOS task factory / encapsulation which supports corresponding queues
//!	with tasks.
//!
//! This module allows the creation of multiple tasks with corresponding queues.
//! The encapsulation offered in this module greatly simplifies the main application 
//!
//
//*****************************************************************************

#ifndef AM_APP_UTILS_TASK_H
#define AM_APP_UTILS_TASK_H

#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

#include "am_app_utils_ring_buffer.h"

#define getListCount(x)     sizeof(x)/sizeof(x[0])

typedef struct
{
	TaskHandle_t task;
	QueueHandle_t queue;
//	am_app_utils_task_enum_t parent;
} am_app_utils_task_t;


typedef struct
{
	//Task Setup
	const uint32_t indx; //Specify this task's index.
	
	TaskFunction_t pxTaskCode; //FreeRTOS function pointer to task
	const char* const pcName; // FreeRTOS name
	const uint16_t usStackDepth; // Stack Size
	void * const pvParameters; // FreeRTOS task parameter mechanism
	UBaseType_t uxPriority; // FreeRTOS Task Priority
	
	//Queue Setup
	const UBaseType_t uxQueueLength;
	
	//Parent Task
//	am_app_utils_task_enum_t parent; //Specify parent task.
}am_app_utils_task_setup_t;

//******************************************************************
// System timer setup structure
//
//******************************************************************

typedef struct
{
	//Task Setup
    const uint32_t indx; //Specify this task's index.
	const char* const pcTimerName; // FreeRTOS name
    TickType_t xTimerPeriodInTicks;
    UBaseType_t uxAutoReload; 
	TimerCallbackFunction_t pxTaskCode; //FreeRTOS function pointer to task
}am_app_utils_timer_setup_t;


//
// QUEUE entry for all corresponding queues
// Structure definition of the message element in queue
//
typedef struct
{
	uint32_t Source; // The sender lets the receiver know the source.
	uint32_t ui32MessageType; // May be redefined per task to index different uses of *pData.
	union{
        uint32_t ui32Note;      // short message for simple communication between tasks
        uint32_t ui32Length;    // data length for long message
        uint32_t ui32Indx;      // index for printf string buffer
    }info;
    am_app_utils_ring_buffer_t* pDataBuffer; 

}am_app_utils_task_queue_element_t;

//*****************************************************************************
//
// App message type list macro definitions
//
//*****************************************************************************
// this enum list contains all app related ring buffers between AM_APP_RINGBUFF_NONE and AM_APP_RINGBUFF_MAX
// where each index corresponds to a ring buffer
typedef enum
{
	AM_APP_MESSAGE_NONE = 0, // The enum must begin with this value as named.
    AM_APP_MESSAGE_SHORT,
    AM_APP_MESSAGE_LONG,
    AM_APP_MESSAGE_STR,
	AM_APP_MESSAGE_MAX // The enum must end with this value as name} am_app_utils_ring_buffer_enum_t;
} am_app_utils_message_type_enum_t;

extern void am_app_utils_task_init(am_app_utils_task_t* pTaskList, uint32_t taskCount);
extern void am_app_utils_task_create(am_app_utils_task_setup_t setup, am_app_utils_task_t* pTaskList);
extern bool am_app_utils_task_send(am_app_utils_task_t* pTaskList, const uint32_t Source, const uint32_t Dest, uint32_t ui32MessageType, uint32_t ui32Notice, am_app_utils_ring_buffer_t *pData);
extern bool am_app_utils_task_send_fromISR(am_app_utils_task_t* pTaskList, const uint32_t Source, const uint32_t Dest, uint32_t ui32MessageType, uint32_t ui32Notice, am_app_utils_ring_buffer_t *pData);
//extern bool am_app_utils_task_send_up(am_app_utils_task_enum_t Source, uint32_t MessageType, void *pData);
//extern bool am_app_utils_task_send_up_fromISR(am_app_utils_task_enum_t Source, uint32_t MessageType, void *pData);
extern bool am_app_utils_task_read(am_app_utils_task_t* pTaskList, const uint32_t indx, am_app_utils_task_queue_element_t *Element);
extern TaskHandle_t am_app_utils_task_get_task_handle(am_app_utils_task_t* pTaskList, const uint32_t indx);
extern void am_app_utils_task_create_all_tasks(am_app_utils_task_setup_t* setup_array, am_app_utils_task_t* pTaskList, uint32_t setupLen);
extern void am_app_utils_timer_create_all_timers(am_app_utils_timer_setup_t* setup_array, TimerHandle_t* pTimerList, uint32_t setupLen);
extern void am_app_utils_task_suspend(am_app_utils_task_t* pTaskList, const uint32_t indx);
extern void am_app_utils_task_resume(am_app_utils_task_t* pTaskList, const uint32_t indx);
#endif
