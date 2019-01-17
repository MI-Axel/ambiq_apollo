//*****************************************************************************
//
// oggfile.h - This file supports reading audio data from a .ogg file and
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

#ifndef OGGFILE_H_
#define OGGFILE_H_

//******************************************************************************
//
// Basic OggS/Opus file header information used to open and read a ogg file and
// opus container.
//
//******************************************************************************
#define OGGS_FORMAT_HEADSEQ     'SggO'
#define OGGS_HEADERTYPE_BOS     0x02
#define OGGS_HEADERTYPE_CONT    0x00
#define OGGS_HEADERTYPE_EOS     0x04

#define OPUSHEAD_FORMAT_SEQ0    'supO'
#define OPUSHEAD_FORMAT_SEQ1    'daeH'
#define OPUSTAGS_FORMAT_SEQ0    'supO'
#define OPUSTAGS_FORMAT_SEQ1    'sgaT'

//*****************************************************************************
//
// Error codes that can be returned by OggOpen and OggRead.
//
//*****************************************************************************
#define ERR_OGG_MAGICPACKET_FAIL      -101
#define ERR_OPUSHEAD_MAGICPACKET_FAIL -102
#define ERR_OPUSHEAD_SEGMENTNUM_FAIL  -103
#define ERR_OPUSTAGS_MAGICPACKET_FAIL -105
#define ERR_OPUSTAGS_SEGMENTNUM_FAIL  -106

//*****************************************************************************
//
// Define for Maximum Size of Segment Table
//
//*****************************************************************************
#define MAX_SEG_TABLE                 50

//*****************************************************************************
//
// Define for File Open
//
//*****************************************************************************
#define OGG_FLAG_FILEOPEN             0x00000001

//*****************************************************************************
//
// The Oggs file Container information.
//
//*****************************************************************************
typedef struct
{
    //
    // Capture Pattern which must be OggS.
    //
    uint32_t ui32OggCapturePattern;

    //
    // Oggs Version Number.
    //
    uint8_t ui8OggVersion;

    //
    // The type of header: BOS, Continuation or EOS.
    //
    uint8_t ui8OggHeaderType;

    //
    // Granule Position Information
    //
    uint32_t ui32OggGranulePosition[2];

    //
    // Unique Serial Number for the Stream
    //
    uint32_t ui32OggBitstreamSerialNumber;

    //
    // Page Sequence Number that gets incremented
    //
    uint32_t ui32OggPageSequenceNumber;

    //
    // 32-bit CRC Checksum
    //
    uint32_t ui32OggChecksum;

    //
    // Number of Page Segments
    //
    uint8_t ui8PageSegments;

    //
    // Segment Size array
    //
    uint8_t ui8SegmentTables[MAX_SEG_TABLE];

}
tOggContainer;

//*****************************************************************************
//
// The OpusHead file Container information.
//
//*****************************************************************************
typedef struct
{
    //
    // Magic Signature for Opus Header.
    //
    uint32_t ui32OpusHeadSignature[2];

    //
    // Opus Version Number.
    //
    uint8_t ui8OpusVersion;

    //
    // Channel Count.
    //
    uint8_t ui8OpusChannelCount;

    //
    // Pre Skip bytes
    //
    uint16_t ui16OpusPreSkipBytes;

    //
    // Sample rate for the audio stream
    //
    uint32_t ui32OpusInputSampleRate;

    //
    // Output Gain Information
    //
    uint16_t ui16OpusOutputGain;

    //
    // Mapping Family
    //
    uint8_t ui8OpusMappingFamily;

    //
    // Mapping Family
    //
    uint32_t ui32OpusAudioSize[2];
}
tOpusHeadContainer;

//*****************************************************************************
//
// The structure used to hold the opx file state.
//
//*****************************************************************************
typedef struct
{
    //
    // The OggS files header information
    //
    tOggContainer sOggContainer;

    //
    // The Opus Header information
    //
    tOpusHeadContainer sOpusHeader;

    //
    // The file information for the current file.
    //
    FIL i16File;

    //
    // Current state flags, a combination of the WAV_FLAG_* values.
    //
    uint32_t ui32Flags;

    //
    // Current state flags, a combination of the WAV_FLAG_* values.
    //
    uint8_t ui8SegmentCount;
} tOggFile;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
int OggOpen(const char *pcFileName,
        tOggFile *psOggData,
        tOpusHeadContainer *psOpusHeader,
        bool bGetFormat);
void OggClose(tOggFile *psOggData);
int16_t OggRead(tOggFile *psOggData, unsigned char *pucBuffer,
         int32_t *i32OpusLen);

#endif
