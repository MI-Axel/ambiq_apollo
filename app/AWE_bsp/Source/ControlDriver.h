/*******************************************************************************
*
*               STM BSP Driver
*               ---------------
*
********************************************************************************
*     ControlDriver.h
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
 #ifndef __CONTROLDRIVER_H__
 #define __CONTROLDRIVER_H__
 
#define CTRL_NUM_INPUTS 1
#define CTRL_BUTTON1 30001

#define CTRL_NUM_OUTPUTS 2
#define SINK_1_OBJECT_ID 30000
#define SINK_2_OBJECT_ID 30002


void ControlInit(void);
void InitializeControlPeripheral(UINT32 nControlID);
void ProcessControlIO(void);

#endif

