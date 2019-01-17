//******************************************************************************
//
// opxfile.c - This file supports reading audio data from a .opx file and
// reading the file format.
//
// Copyright (c) 2012-2015 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
//******************************************************************************

#include <stdint.h>
#include "inc/hw_types.h"
#include "third_party/fatfs/src/ff.h"
#include "third_party/fatfs/src/diskio.h"
#include "opxcode/opxfile.h"

//******************************************************************************
//
// This function returns the format of a opx file that has been opened with
// the OpxOpen() function.
//
// \param psOpxData is the structure that was passed to the OpxOpen() function.
// \param psOpxHeader is the structure to fill with the format of the opx file.
//
// This function is used to get the audio format of a file that was opened
// with the OpxOpen() function.  The \e psOpxData parameter should be the
// same structure that was passed to the OpxOpen() function.  The
// \e psOpxHeader function will be filled with the format of the open file if
// the \e psOpxData is a valid open file.  If this function is called with
// an invalid \e psOpxData then the results will be undetermined.
//
// \return None.
//
//******************************************************************************
void
OpxGetFormat(tOpxFile *psOpxData, tOpxHeader *psOpxHeader)
{
    //
    // Only return data if the file is open.
    //
    psOpxHeader->ui16NumChannels = psOpxData->sOpxHeader.ui16NumChannels;
    psOpxHeader->ui16BitsPerSample = psOpxData->sOpxHeader.ui16BitsPerSample;
    psOpxHeader->ui32SampleRate = psOpxData->sOpxHeader.ui32SampleRate;
    psOpxHeader->ui32OrigFileSize = psOpxData->sOpxHeader.ui32OrigFileSize;
    psOpxHeader->ui32AvgByteRate = psOpxData->sOpxHeader.ui32AvgByteRate;

}

//******************************************************************************
//
// This function is called to open and determine if a file is a valid .opx
// file.
//
// \param pcFileName is the null terminated string for the file to open.
// \param psOpxData is the structure used to hold the file state information.
//
// This function is used to open a file and determine if it is a valid .opx
// file.  The \e pcFileName will be opened and read to look for a valid .opx
// file header and prepared for calling the OpxRead() or OpxGetFormat()
// functions.  When an application is done with the .opx file it should call
// the OpxClose() function to free up the file.  The function will return
// zero if the function successfully opened a .opx file and a non-zero value
// indicates that the file was a valid .opx file or the file could not be
// opened.
//
// \return A value of zero indicates that the file was successfully opened and
// any other value indicates that the file was not opened.
//
//******************************************************************************
int
OpxOpen(const char *pcFileName, tOpxFile *psOpxData)
{
    unsigned char pucBuffer[20];
    uint32_t *pui32Buffer;
    uint16_t *pui16Buffer;
    uint32_t ui32Count;

    //
    // Create some local pointers using in parsing values.
    //
    pui32Buffer = (uint32_t *)pucBuffer;
    pui16Buffer = (uint16_t *)pucBuffer;

    //
    // Open the file as read only.
    //
    if(f_open(&psOpxData->i16File, pcFileName, FA_READ) != FR_OK)
    {
        return(-1);
    }

    //
    // File is open.
    //
    psOpxData->ui32Flags = OPX_FLAG_FILEOPEN;

    //
    // Read the first 12 bytes.
    //
    if(f_read(&psOpxData->i16File, pucBuffer, 16, (UINT *)&ui32Count) != FR_OK)
    {
        return(-1);
    }

    //
    // Look for Opus Header tag.
    //
    if(pui32Buffer[0] != OPX_FORMAT_HEADSEQ)
    {
        return(-1);
    }

    //
    // Save the audio format data so that it can be returned later if
    // requested.
    //
    psOpxData->sOpxHeader.ui16NumChannels =  pui16Buffer[2];
    psOpxData->sOpxHeader.ui16BitsPerSample =  pui16Buffer[3];
    psOpxData->sOpxHeader.ui32SampleRate = pui32Buffer[2];
    psOpxData->sOpxHeader.ui32OrigFileSize = pui32Buffer[3];
    psOpxData->sOpxHeader.ui32AvgByteRate =
            (pui32Buffer[2] * pui16Buffer[2] * pui16Buffer[3])/8;

    //
    // Only mono supported.
    //
    if(psOpxData->sOpxHeader.ui16NumChannels > 1)
    {
        return(-1);
    }

    return(0);
}

//******************************************************************************
//
// This is used to close a .opx file that was opened with OpxOpen().
//
// \param psOpxData is the file structure that was passed into the OpxOpen()
// function.
//
// This function should be called when a function has completed using a .opx
// file that was opened with the OpxOpen() function.  This will free up any
// file system data that is held while the file is open.
//
// \return None.
//
//******************************************************************************
void
OpxClose(tOpxFile *psOpxData)
{
    if(psOpxData->ui32Flags & OPX_FLAG_FILEOPEN)
    {
        //
        // Close out the file.
        //
        f_close(&psOpxData->i16File);

        //
        // Mark file as no longer open.
        //
        psOpxData->ui32Flags &= ~OPX_FLAG_FILEOPEN;
    }
}

//******************************************************************************
//
// This function is used to read audio data from a file that was opened with
// the OpxOpen() function.
//
// \param psOpxData is the file structure that was passed into the OpxOpen()
// function.
// \param pucBuffer is the buffer to read data into.
//
// This function handles reading data from a .opx file that was opened with
// the OpxOpen() function.   The function will return the actual number of
// of bytes read from the file.
//
// \return This function returns the number of bytes read from the file.
//
//******************************************************************************
uint16_t
OpxRead(tOpxFile *psOpxData, unsigned char *pucBuffer, int32_t *i32OpxLen)
{
    uint32_t ui32OpxDelimiter;
    int32_t  i32len;
    uint32_t ui32Count;

    //
    // Read the delimiter info and check if this is the last segment
    //
    if(f_read(&psOpxData->i16File, &ui32OpxDelimiter, 4, (UINT *)&ui32Count)
            != FR_OK)
    {
        return(0);
    }

    //
    // Read the file opx segement length
    //
    if(f_read(&psOpxData->i16File, &i32len, 4, (UINT *)&ui32Count)
            != FR_OK)
    {
        return(0);
    }

    //
    // Read the data in another buffer from the file.
    //
    if(f_read(&psOpxData->i16File, pucBuffer, i32len, (UINT *)&ui32Count)
            != FR_OK)
    {
        return(0);
    }

    //
    // Write the Length of the packet
    //
    *i32OpxLen = i32len;

    if(ui32OpxDelimiter == OPX_FORMAT_MIDSEQ)
    {
        return(1);
    }
    else if(ui32OpxDelimiter == OPX_FORMAT_ENDSEQ)
    {
        return(2);
    }
    else
    {
        return(0);
    }

}
