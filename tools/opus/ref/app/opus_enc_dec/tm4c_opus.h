//*****************************************************************************
//
// tm4c_opus.h - This file holds the defines that would be used for reading wav
// files and the opus parameters.
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

#ifndef OPUS_CODEC_WAV_H_
#define OPUS_CODEC_WAV_H_

//*****************************************************************************
//
// Defines the OPUS parameters
//
//*****************************************************************************
#define OPUS_DATA_SCALER      2
#define OPUS_BITRATE_SCALER   2
#define OPUS_FRAME_SIZE_IN_MS 20
#define OPUS_MAX_PACKET       1024

//*****************************************************************************
//
// Defines the playback parameters
//
//*****************************************************************************
#define TIMER_BASE            TIMER5_BASE
#define OPUS_PLAYBACK_RATE    48000

//*****************************************************************************
//
// Structure for WAVE file
//
//*****************************************************************************
typedef struct
{
    uint8_t ui8ChunkID[4];
    uint32_t ui32ChunkSize;
    uint8_t ui8Format[4];
    uint8_t ui8SubChunk1ID[4];
    uint32_t ui32SubChunk1Size;
    uint16_t ui16AudioFormat;
    uint16_t ui16NumChannels;
    uint32_t ui32SampleRate;
    uint32_t ui32ByteRate;
    uint16_t ui16BlockAlign;
    uint16_t ui16BitsPerSample;
    uint8_t ui8SubChunk2ID[4];
    uint32_t ui32SubChunk2Size;
}
tWaveHeader;

#endif /* OPUS_CODEC_WAV_H_ */

