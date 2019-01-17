//*****************************************************************************
//
// opxfile.h - This file supports reading audio data from a .opx file and
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
//*****************************************************************************

#ifndef OPXFILE_H_
#define OPXFILE_H_

//******************************************************************************
//
// The flag values for the ui32Flags member of the tOpxFile structure.
//
//******************************************************************************
#define OPX_FLAG_FILEOPEN       0x00000001

//******************************************************************************
//
// Basic opx file header information used to open and read a opx file.
//
//******************************************************************************
#define OPX_FORMAT_HEADSEQ     0x00524448
#define OPX_FORMAT_MIDSEQ      0x0064694d
#define OPX_FORMAT_ENDSEQ      0x00646e45

//*****************************************************************************
//
// The opx file header information.
//
//*****************************************************************************
typedef struct
{
    //
    // Header delimiter.
    //
    uint32_t ui32HeaderDelimiter;

    //
    // The number of audio channels.
    //
    uint16_t ui16NumChannels;

    //
    // The number of bits per sample.
    //
    uint16_t ui16BitsPerSample;

    //
    // The original sample rate.
    //
    uint32_t ui32SampleRate;

    //
    // The original file size.
    //
    uint32_t ui32OrigFileSize;

    //
    // The average byte rate
    //
    uint32_t ui32AvgByteRate;

}
tOpxHeader;

//*****************************************************************************
//
// The structure used to hold the opx file state.
//
//*****************************************************************************
typedef struct
{
    //
    // The wav files header information
    //
    tOpxHeader sOpxHeader;

    //
    // The file information for the current file.
    //
    FIL i16File;

    //
    // Current state flags, a combination of the WAV_FLAG_* values.
    //
    uint32_t ui32Flags;
} tOpxFile;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
void OpxGetFormat(tOpxFile *psOpxData, tOpxHeader *psOpxHeader);
int OpxOpen(const char *pcFileName, tOpxFile *psOpxData);
void OpxClose(tOpxFile *psOpxData);
uint16_t OpxRead(tOpxFile *psOpxData, unsigned char *pucBuffer,
         int32_t *i32OpxLen);

#endif
