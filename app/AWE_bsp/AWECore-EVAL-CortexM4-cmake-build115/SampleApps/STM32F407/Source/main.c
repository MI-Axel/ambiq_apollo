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
*     Copyright:    (c) 2018 DSP Concepts, Inc. All rights reserved.
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
*
*******************************************************************************/
#include "Platform.h"
//#include "ButtonConnectedToLEDAWB.h"
//UINT32 nErrorOffset;
//INT32 nResult;

int main(void)
{
   // Initialize AWE platform
	targetInit();

    //nResult = awe_loadAWBfromArray(&g_AWEInstance, InitCommands, InitCommands_Len, &nErrorOffset);
    //if (nResult != E_SUCCESS)
    //{
    //    printf("awe_loadAWBfromArray failed\n");
    //}

    AWEIdleLoop();

}   // End main
