/*******************************************************************************
*
*               GPIO Driver
*               ---------------
*
********************************************************************************
*     GPIO.c
********************************************************************************
*
*     Description:  GPIO Interface for STM Discovery board
*
*     Copyright:    DSP Concepts, Inc. (c) 2007 - 2017
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
*******************************************************************************/
#include "Platform.h"

#ifdef USE_GPIO

//#include "PinDef.h"

//-----------------------------------------------------------------------------
// METHOD:  awe_pltGPIOSetPinDir
// PURPOSE: Set GPIO pin direction
//-----------------------------------------------------------------------------
void awe_pltGPIOSetPinDir(UINT32 nPinNo, UINT32 nPinDir)
{
//    GPIO_InitTypeDef GPIO_InitStruct;
//    UINT32 nPinNdx;
//
//    if (nPinNo < 1 || nPinNo > MAX_PINS)
//    {
//        return;
//    }
//    
//    // If user wants control of LED4 relinquish board alive LED toggle
//    if (nPinNo == 3 && nPinDir != GPIO_DIR_INPUT)
//    {
//        g_bBlinkLED4ForBoardAlive = FALSE; 
//    }        
//    
//    nPinNdx = nPinNo - 1;
//        
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    GPIO_InitStruct.Pull = GPIO_NOPULL; 
//   
//    if (nPinDir == GPIO_DIR_INPUT)
//    {
//        GPIO_InitStruct.Pin = InputPinMap[nPinNdx].GPIO_Pin;        
//        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//                
//        // Setup the GPIO pin
//        HAL_GPIO_Init(InputPinMap[nPinNdx].GPIOx, &GPIO_InitStruct);    
//    }
//    else
//    {
//        GPIO_InitStruct.Pin = OutputPinMap[nPinNdx].GPIO_Pin; 
//        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;        
//        
//        // Setup the GPIO pin
//        HAL_GPIO_Init(OutputPinMap[nPinNdx].GPIOx, &GPIO_InitStruct); 
//
//        // Initialize output pin to 0
//        awe_pltGPIOSetPin(nPinNo, 0);        
//    }

}   // End awe_pltGPIOSetPinDir


//-----------------------------------------------------------------------------
// METHOD:  awe_pltGPIOTogglePin
// PURPOSE: Set GBPIO pin value
//-----------------------------------------------------------------------------
void awe_pltGPIOTogglePin(UINT32 nPinNo)
{
//    UINT32 nPinNdx;
//
//    if (nPinNo < 1 || nPinNo > MAX_PINS)
//    {
//        return;
//    }  
//    
//    nPinNdx = nPinNo - 1;
//    
//    HAL_GPIO_TogglePin(OutputPinMap[nPinNdx].GPIOx, OutputPinMap[nPinNdx].GPIO_Pin);
//    
}   // End awe_pltGPIOTogglePin


//-----------------------------------------------------------------------------
// METHOD:  awe_pltGPIOSetPin
// PURPOSE: Set GBPIO pin value
//-----------------------------------------------------------------------------
void awe_pltGPIOSetPin(UINT32 nPinNo, UINT32 nValue)
{
//    UINT32 nPinNdx;
//
//    if (nPinNo < 1 || nPinNo > MAX_PINS)
//    {
//        return;
//    }  
//    
//    nPinNdx = nPinNo - 1;
// 
//    if (nValue > 0)
//    {
//        HAL_GPIO_WritePin(OutputPinMap[nPinNdx].GPIOx, OutputPinMap[nPinNdx].GPIO_Pin, GPIO_PIN_SET);
//     }
//    else
//    {
//        HAL_GPIO_WritePin(OutputPinMap[nPinNdx].GPIOx, OutputPinMap[nPinNdx].GPIO_Pin, GPIO_PIN_RESET);
//    }             
//
}   // End awe_pltGPIOSetPin


//-----------------------------------------------------------------------------
// METHOD:  awe_pltGPIOGetPin
// PURPOSE: Get GPIO pin value
//-----------------------------------------------------------------------------
void awe_pltGPIOGetPin(UINT32 nPinNo, UINT32 * nValue)
{ 
//    UINT32 nPinNdx;
//
//    if (nPinNo < 1 || nPinNo > MAX_PINS)
//    {
//        return;
//    }
//    
//    nPinNdx = nPinNo - 1;
//    
//    *nValue = HAL_GPIO_ReadPin(InputPinMap[nPinNdx].GPIOx, InputPinMap[nPinNdx].GPIO_Pin);
//
}   // End awe_pltGPIOGetPin

#endif
