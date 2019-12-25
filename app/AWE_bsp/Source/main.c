
/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     main.c
********************************************************************************
*
*     Description:  AudioWeaver target main program
*
*******************************************************************************/
//
// standard C headers
//
#include <stdint.h>
//
// Ambiq apollo headers
//
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

#include "BoardSetup.h"
#include "TargetInfo.h"
#include "Platform.h"

//
// layout specific include
//
//#include "vos_alexa_qual_InitAWB.h"

#include "ambiq_2mic_v1_InitAWB.h"

UINT32 nErrorOffset;
INT32 nResult;

int main(void)
{    
    // Initialize target board
    targetInit(); 
	
    // Initialize the framework    
    AWEInstanceInit();
    nResult = awe_loadAWBfromArray(&g_AWEInstance, Core0_InitCommands, Core0_InitCommands_Len, &nErrorOffset);

    AWEIdleLoop();
	
}   // End main
