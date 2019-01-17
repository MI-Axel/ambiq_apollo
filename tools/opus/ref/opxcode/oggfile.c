//******************************************************************************
//
// oggfile.c - This file supports reading audio data from a .ogg file and
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
#include <stdbool.h>
#include "inc/hw_types.h"
#include "third_party/fatfs/src/ff.h"
#include "third_party/fatfs/src/diskio.h"
#include "opxcode/oggfile.h"

//******************************************************************************
//
// This function is called to open and determine if a file is a valid .ogg
// file.
//
// \param pcFileName is the null terminated string for the file to open.
// \param psOggData is the structure used to hold the file state information.
// \param psOpusHeader is the structure used to hold the Opus file information.
// \param bGetFormat is used to decide if only format information is required or
// the file has to be kept in a ready to read state.
//
// This function is used to open a file and determine if it is a valid .ogg
// file.  The \e pcFileName will be opened and read to look for a valid .ogg
// file header and prepared for calling the OggRead() functions. When an 
// application is done with processing the .ogg file it should call the 
// OggClose() function to free up the file handle.  The function will return
// zero if the function successfully opened a .ogg file and a non-zero value
// indicates that the file was a valid .ogg file or the file could not be
// opened.
//
// \return A value of zero indicates that the file was successfully opened and
// any other value indicates that the file was not opened.
//
//******************************************************************************
int
OggOpen(const char *pcFileName,
        tOggFile *psOggData,
        tOpusHeadContainer *psOpusHeader,
        bool bGetFormat)
{
    unsigned char pucBuffer[256];
    uint8_t  ui8Index;
    uint32_t *pui32Buffer;
    uint16_t *pui16Buffer;
    uint8_t  *pui8Buffer;
    uint32_t ui32Count;

    //
    // Create some local pointers using in parsing values.
    //
    pui32Buffer = (uint32_t *)pucBuffer;
    pui16Buffer = (uint16_t *)pucBuffer;
    pui8Buffer  = (uint8_t *)pucBuffer;

    //
    // Open the file as read only.
    //
    if(f_open(&psOggData->i16File, pcFileName, FA_READ) != FR_OK)
    {
        return(-1);
    }

    //
    // File is open.
    //
    psOggData->ui32Flags = OGG_FLAG_FILEOPEN;

    //
    // Read the first 27 bytes.
    //
    if(f_read(&psOggData->i16File, pucBuffer, 27, (UINT *)&ui32Count) != FR_OK)
    {
        return(-1);
    }

    //
    // Save the audio format data so that it can be returned later if
    // requested.
    //
    psOggData->sOggContainer.ui32OggCapturePattern        =  pui32Buffer[0];
    psOggData->sOggContainer.ui8OggVersion                =  pui8Buffer[4];
    psOggData->sOggContainer.ui8OggHeaderType             =  pui8Buffer[5];
    psOggData->sOggContainer.ui32OggGranulePosition[0]    =  pui16Buffer[3] |
            (pui16Buffer[4] << 16);
    psOggData->sOggContainer.ui32OggGranulePosition[1]    =  pui16Buffer[5] |
            (pui16Buffer[6] << 16);
    psOggData->sOggContainer.ui32OggBitstreamSerialNumber =  pui16Buffer[7] |
            (pui16Buffer[8] << 16);
    psOggData->sOggContainer.ui32OggPageSequenceNumber    =  pui16Buffer[9] |
            (pui16Buffer[10] << 16);
    psOggData->sOggContainer.ui32OggChecksum              =  pui16Buffer[11] |
            (pui16Buffer[12] << 16);
    psOggData->sOggContainer.ui8PageSegments              =  pui8Buffer[26];

    //
    // Check if the OggS format is correctly read
    //
    if(psOggData->sOggContainer.ui32OggCapturePattern !=
            (uint32_t)OGGS_FORMAT_HEADSEQ)
    {
        return(ERR_OGG_MAGICPACKET_FAIL);
    }

    //
    // If this is the Oggs container for the OpusHead then there should be only
    // one Page Segment
    //
    if(psOggData->sOggContainer.ui8PageSegments != 0x01)
    {
        return(ERR_OPUSHEAD_SEGMENTNUM_FAIL);
    }

    //
    // Read the Segment Size.
    //
    if(f_read(&psOggData->i16File, pucBuffer, 1, (UINT *)&ui32Count) != FR_OK)
    {
        return(-1);
    }

    psOggData->sOggContainer.ui8SegmentTables[0] =  pui8Buffer[0];

    //
    // Now read the Opus container information by reading the next
    // psOggData->sOggContainer.ui8PageSegments bytes of data from the file
    //
    if(f_read(&psOggData->i16File, pucBuffer,
            psOggData->sOggContainer.ui8SegmentTables[0],
            (UINT *)&ui32Count) != FR_OK)
    {
        return(-1);
    }

    //
    // Save the audio format data so that it can be returned later if
    // requested.
    //
    psOggData->sOpusHeader.ui32OpusHeadSignature[0] = pui32Buffer[0];
    psOggData->sOpusHeader.ui32OpusHeadSignature[1] = pui32Buffer[1];
    psOggData->sOpusHeader.ui8OpusVersion           = pui8Buffer[8];
    psOggData->sOpusHeader.ui8OpusChannelCount      = pui8Buffer[9];
    psOggData->sOpusHeader.ui16OpusPreSkipBytes     = pui16Buffer[5];
    psOggData->sOpusHeader.ui32OpusInputSampleRate  = pui32Buffer[3];
    psOggData->sOpusHeader.ui16OpusOutputGain       = pui16Buffer[8];
    psOggData->sOpusHeader.ui8OpusMappingFamily     = pui8Buffer[18];

    if(bGetFormat)
    {
        psOpusHeader->ui8OpusVersion =
                psOggData->sOpusHeader.ui8OpusVersion;
        psOpusHeader->ui8OpusChannelCount =
                psOggData->sOpusHeader.ui8OpusChannelCount;
        psOpusHeader->ui32OpusInputSampleRate =
                psOggData->sOpusHeader.ui32OpusInputSampleRate;
        psOpusHeader->ui8OpusMappingFamily =
                psOggData->sOpusHeader.ui8OpusMappingFamily;
    }

    if(psOggData->sOpusHeader.ui32OpusHeadSignature[0] !=
            (uint32_t)OPUSHEAD_FORMAT_SEQ0)
    {
        return(ERR_OPUSHEAD_MAGICPACKET_FAIL);
    }
    if(psOggData->sOpusHeader.ui32OpusHeadSignature[1] !=
            (uint32_t)OPUSHEAD_FORMAT_SEQ1)
    {
        return(ERR_OPUSHEAD_MAGICPACKET_FAIL);
    }

    //
    // Read the next 27 bytes.
    //
    if(f_read(&psOggData->i16File, pucBuffer, 27, (UINT *)&ui32Count) != FR_OK)
    {
        return(-1);
    }

    //
    // Save the audio format data so that it can be returned later if
    // requested.
    //
    psOggData->sOggContainer.ui32OggCapturePattern        =  pui32Buffer[0];
    psOggData->sOggContainer.ui8OggVersion                =  pui8Buffer[4];
    psOggData->sOggContainer.ui8OggHeaderType             =  pui8Buffer[5];
    psOggData->sOggContainer.ui32OggGranulePosition[0]    =  pui16Buffer[3] |
            (pui16Buffer[4] << 16);
    psOggData->sOggContainer.ui32OggGranulePosition[1]    =  pui16Buffer[5] |
            (pui16Buffer[6] << 16);
    psOggData->sOggContainer.ui32OggBitstreamSerialNumber =  pui16Buffer[7] |
            (pui16Buffer[8] << 16);
    psOggData->sOggContainer.ui32OggPageSequenceNumber    =  pui16Buffer[9] |
            (pui16Buffer[10] << 16);
    psOggData->sOggContainer.ui32OggChecksum              =  pui16Buffer[11] |
            (pui16Buffer[12] << 16);
    psOggData->sOggContainer.ui8PageSegments              =  pui8Buffer[26];

    if(psOggData->sOggContainer.ui32OggCapturePattern !=
            (uint32_t)OGGS_FORMAT_HEADSEQ)
    {
        return(ERR_OGG_MAGICPACKET_FAIL);
    }
    if(psOggData->sOggContainer.ui8PageSegments > MAX_SEG_TABLE)
    {
        return(ERR_OPUSTAGS_SEGMENTNUM_FAIL);
    }

    //
    // Read the next psOggData->sOggContainer.ui8PageSegments bytes for size
    // of the Opus Tags container
    //
    if(f_read(&psOggData->i16File, pucBuffer,
            psOggData->sOggContainer.ui8PageSegments,
            (UINT *)&ui32Count) != FR_OK)
    {
        return(-1);
    }

    for(ui8Index = 0; ui8Index < psOggData->sOggContainer.ui8PageSegments ;
            ui8Index++)
    {
        psOggData->sOggContainer.ui8SegmentTables[ui8Index] =
                pui8Buffer[ui8Index];
    }

    //
    // Read the next ui32BytesToSkip bytes to reach the data payload for OggS
    // container
    //
    for(ui8Index = 0; ui8Index < psOggData->sOggContainer.ui8PageSegments ;
            ui8Index++)
    {
        if(f_read(&psOggData->i16File, pucBuffer,
                psOggData->sOggContainer.ui8SegmentTables[ui8Index],
                (UINT *)&ui32Count) != FR_OK)
        {
            return(-1);
        }
    }

    if(bGetFormat)
    {
        //
        // Now start counting the size of the audio by reading the Ogg stream
        // till EOS
        //
        do
        {
            //
            // Read the next 27 bytes.
            //
            if(f_read(&psOggData->i16File, pucBuffer, 27,
                    (UINT *)&ui32Count) != FR_OK)
            {
                return(-1);
            }

            //
            // Save the audio format data so that it can be returned later if
            // requested.
            //
            psOggData->sOggContainer.ui32OggCapturePattern        =
                    pui32Buffer[0];
            psOggData->sOggContainer.ui8OggVersion                =
                    pui8Buffer[4];
            psOggData->sOggContainer.ui8OggHeaderType             =
                    pui8Buffer[5];
            psOggData->sOggContainer.ui32OggGranulePosition[0]    =
                    pui16Buffer[3] | (pui16Buffer[4] << 16);
            psOggData->sOggContainer.ui32OggGranulePosition[1]    =
                    pui16Buffer[5] | (pui16Buffer[6] << 16);
            psOggData->sOggContainer.ui32OggBitstreamSerialNumber =
                    pui16Buffer[7] | (pui16Buffer[8] << 16);
            psOggData->sOggContainer.ui32OggPageSequenceNumber    =
                    pui16Buffer[9] | (pui16Buffer[10] << 16);
            psOggData->sOggContainer.ui32OggChecksum              =
                    pui16Buffer[11] | (pui16Buffer[12] << 16);
            psOggData->sOggContainer.ui8PageSegments              =
                    pui8Buffer[26];

            if(psOggData->sOggContainer.ui32OggCapturePattern !=
                    (uint32_t)OGGS_FORMAT_HEADSEQ)
            {
                return(ERR_OGG_MAGICPACKET_FAIL);
            }
            if(psOggData->sOggContainer.ui8PageSegments > MAX_SEG_TABLE)
            {
                return(ERR_OPUSTAGS_SEGMENTNUM_FAIL);
            }

            //
            // Read the next psOggData->sOggContainer.ui8PageSegments bytes
            // for size of the Opus Tags container
            //
            if(f_read(&psOggData->i16File, pucBuffer,
                    psOggData->sOggContainer.ui8PageSegments,
                    (UINT *)&ui32Count) != FR_OK)
            {
                return(-1);
            }

            for(ui8Index = 0;
                    ui8Index < psOggData->sOggContainer.ui8PageSegments ;
                    ui8Index++)
            {
                psOggData->sOggContainer.ui8SegmentTables[ui8Index] =
                        pui8Buffer[ui8Index];
            }

            //
            // Read the next ui32BytesToSkip bytes to reach the data payload
            // for OggS container
            //
            for(ui8Index = 0;
                    ui8Index < psOggData->sOggContainer.ui8PageSegments ;
                    ui8Index++)
            {
                if(f_read(&psOggData->i16File, pucBuffer,
                        psOggData->sOggContainer.ui8SegmentTables[ui8Index],
                        (UINT *)&ui32Count) != FR_OK)
                {
                    return(-1);
                }
            }

        }while(psOggData->sOggContainer.ui8OggHeaderType !=
                OGGS_HEADERTYPE_EOS);

        psOpusHeader->ui32OpusAudioSize[0] =
                psOggData->sOggContainer.ui32OggGranulePosition[0];
        psOpusHeader->ui32OpusAudioSize[1] =
                psOggData->sOggContainer.ui32OggGranulePosition[1];
    }

    //
    // Make sure that the segment count is always reset
    //
    psOggData->ui8SegmentCount = 0;

    return(0);
}

//******************************************************************************
//
// This is used to close a .ogg file that was opened with OggOpen().
//
// \param psOggData is the file structure that was passed into the OggOpen()
// function.
//
// This function should be called when a function has completed using a .oggx
// file that was opened with the OggOpen() function.  This will free up any
// file system data that is held while the file is open.
//
// \return None.
//
//******************************************************************************
void
OggClose(tOggFile *psOggData)
{
    if(psOggData->ui32Flags & OGG_FLAG_FILEOPEN)
    {
        //
        // Close out the file.
        //
        f_close(&psOggData->i16File);

        //
        // Mark file as no longer open.
        //
        psOggData->ui32Flags &= ~OGG_FLAG_FILEOPEN;
    }
}

//******************************************************************************
//
// This function is used to read audio data from a file that was opened with
// the OggOpen() function.
//
// \param psOggData is the file structure that was passed into the OggOpen()
// function.
// \param pucBuffer is the buffer to read data into.
// \param i32OpusLen is the length of opus packet to decode in the application.
//
// This function handles reading data from a .ogg file that was opened with
// the OggOpen() function.   The function will return the actual number of
// of bytes read from the file.
//
// \return This function returns the number of bytes read from the file.
//
//******************************************************************************
int16_t
OggRead(tOggFile *psOggData, unsigned char *pucBuffer, int32_t *i32OpusLen)
{
    uint32_t ui32Count;
    uint32_t *pui32Buffer;
    uint16_t *pui16Buffer;
    uint8_t *pui8Buffer;
    uint8_t ui8Index;

    //
    // Create some local pointers using in parsing values.
    //
    pui32Buffer = (uint32_t *)pucBuffer;
    pui16Buffer = (uint16_t *)pucBuffer;
    pui8Buffer = (uint8_t *)pucBuffer;


    ////////////////////////////
    //
    // If there is no segment information available then read the Ogg
    // container
    //
    if(psOggData->ui8SegmentCount == 0)
    {
        //
        // Read the next 27 bytes.
        //
        if(f_read(&psOggData->i16File, pucBuffer, 27, (UINT *)&ui32Count) !=
                FR_OK)
        {
            return(-1);
        }

        //
        // Save the audio format data so that it can be returned later if
        // requested.
        //
        psOggData->sOggContainer.ui32OggCapturePattern        =
                pui32Buffer[0];
        psOggData->sOggContainer.ui8OggVersion                =
                pui8Buffer[4];
        psOggData->sOggContainer.ui8OggHeaderType             =
                pui8Buffer[5];
        psOggData->sOggContainer.ui32OggGranulePosition[0]    =
                pui16Buffer[3] | (pui16Buffer[4] << 16);
        psOggData->sOggContainer.ui32OggGranulePosition[1]    =
                pui16Buffer[5] | (pui16Buffer[6] << 16);
        psOggData->sOggContainer.ui32OggBitstreamSerialNumber =
                pui16Buffer[7] | (pui16Buffer[8] << 16);
        psOggData->sOggContainer.ui32OggPageSequenceNumber    =
                pui16Buffer[9] | (pui16Buffer[10] << 16);
        psOggData->sOggContainer.ui32OggChecksum              =
                pui16Buffer[11] | (pui16Buffer[12] << 16);
        psOggData->sOggContainer.ui8PageSegments              =
                pui8Buffer[26];
        psOggData->ui8SegmentCount                            =
                pui8Buffer[26];

        if(psOggData->sOggContainer.ui32OggCapturePattern !=
                (uint32_t)OGGS_FORMAT_HEADSEQ)
        {
            return(ERR_OGG_MAGICPACKET_FAIL);
        }

        if(psOggData->sOggContainer.ui8PageSegments > MAX_SEG_TABLE)
        {
            return(ERR_OPUSTAGS_SEGMENTNUM_FAIL);
        }

        //
        // Read the next psOggData->sOggContainer.ui8PageSegments bytes for
        // size of the Opus Tags container
        //
        if(f_read(&psOggData->i16File, pucBuffer,
                psOggData->sOggContainer.ui8PageSegments,
                (UINT *)&ui32Count) != FR_OK)
        {
            return(-1);
        }

        for(ui8Index = 0; ui8Index < psOggData->sOggContainer.ui8PageSegments ;
                ui8Index++)
        {
            psOggData->sOggContainer.ui8SegmentTables[psOggData->ui8SegmentCount-ui8Index-1] =
                    pui8Buffer[ui8Index];
        }

    }

    psOggData->ui8SegmentCount--;

    if(f_read(&psOggData->i16File, pucBuffer,
            psOggData->sOggContainer.ui8SegmentTables[psOggData->ui8SegmentCount],
            (UINT *)&ui32Count) != FR_OK)
    {
        return(-1);
    }

    //
    // Write the Length of the packet
    //
    *i32OpusLen =
            psOggData->sOggContainer.ui8SegmentTables[psOggData->ui8SegmentCount];

    if(psOggData->sOggContainer.ui8OggHeaderType == OGGS_HEADERTYPE_CONT)
    {
        return(1);
    }
    else if((psOggData->sOggContainer.ui8OggHeaderType == OGGS_HEADERTYPE_EOS) &&
            (psOggData->ui8SegmentCount == 0))
    {
        return(2);
    }

    return(1);
}
