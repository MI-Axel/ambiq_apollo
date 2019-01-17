//*****************************************************************************
//
// opus_enc_dec.c - Opus Encoder and Decoder example with command line inputs.
//
// Copyright (c) 2013-2015 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 2.1.2.111 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "opus.h"
#include "debug.h"
#include "opus_types.h"
#include "opus_private.h"
#include "opus_multistream.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "utils/cmdline.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include "fatfs/src/ff.h"
#include "fatfs/src/diskio.h"
#include "opxcode/pinout.h"
#include "tm4c_opus.h"

//*****************************************************************************
//
// The number of SysTick ticks per second.
//
//*****************************************************************************
#define TICKS_PER_SECOND 100
#define MS_PER_SYSTICK (1000 / TICKS_PER_SECOND)

//****************************************************************************
//
// System clock rate in Hz.
//
//****************************************************************************
uint32_t g_ui32SysClock;

//****************************************************************************
//
// Opus Encode and Decoder structure variables are declared here.
//
//****************************************************************************
OpusEncoder *sOpusEnc;
OpusDecoder *sOpusDec;

//*****************************************************************************
//
// Defines the size of the buffers that hold the path, or temporary data from
// the SD card.  There are two buffers allocated of this size.  The buffer size
// must be large enough to hold the longest expected full path name, including
// the file name, and a trailing null character.
//
//*****************************************************************************
#define PATH_BUF_SIZE           80

//*****************************************************************************
//
// Defines the size of the buffer that holds the command line.
//
//*****************************************************************************
#define CMD_BUF_SIZE            64

//*****************************************************************************
//
// This buffer holds the full path to the current working directory.  Initially
// it is root ("/").
//
//*****************************************************************************
static char g_pcCwdBuf[PATH_BUF_SIZE] = "/";

//*****************************************************************************
//
// A temporary data buffer used when manipulating file paths, or reading data
// from the SD card.
//
//*****************************************************************************
static char g_pcTmpBuf[CMD_BUF_SIZE];

//*****************************************************************************
//
// The buffer that holds the command line.
//
//*****************************************************************************
static char g_pcCmdBuf[CMD_BUF_SIZE];

//*****************************************************************************
//
// The following are data structures used by FatFs.
//
//*****************************************************************************
static FATFS g_sFatFs;
static DIR g_sDirObject;
static FILINFO g_sFileInfo;
static FIL g_sFileReadObject;
static FIL g_sFileWriteObject;

//*****************************************************************************
//
// A structure that holds a mapping between an FRESULT numerical code, and a
// string representation.  FRESULT codes are returned from the FatFs FAT file
// system driver.
//
//*****************************************************************************
typedef struct
{
    FRESULT iFResult;
    char *pcResultStr;
}
tFResultString;

//*****************************************************************************
//
// A macro to make it easy to add result codes to the table.
//
//*****************************************************************************
#define FRESULT_ENTRY(f)        { (f), (#f) }

//*****************************************************************************
//
// A table that holds a mapping between the numerical FRESULT code and it's
// name as a string.  This is used for looking up error codes for printing to
// the console.
//
//*****************************************************************************
tFResultString g_psFResultStrings[] =
{
    FRESULT_ENTRY(FR_OK),
    FRESULT_ENTRY(FR_DISK_ERR),
    FRESULT_ENTRY(FR_INT_ERR),
    FRESULT_ENTRY(FR_NOT_READY),
    FRESULT_ENTRY(FR_NO_FILE),
    FRESULT_ENTRY(FR_NO_PATH),
    FRESULT_ENTRY(FR_INVALID_NAME),
    FRESULT_ENTRY(FR_DENIED),
    FRESULT_ENTRY(FR_EXIST),
    FRESULT_ENTRY(FR_INVALID_OBJECT),
    FRESULT_ENTRY(FR_WRITE_PROTECTED),
    FRESULT_ENTRY(FR_INVALID_DRIVE),
    FRESULT_ENTRY(FR_NOT_ENABLED),
    FRESULT_ENTRY(FR_NO_FILESYSTEM),
    FRESULT_ENTRY(FR_MKFS_ABORTED),
    FRESULT_ENTRY(FR_TIMEOUT),
    FRESULT_ENTRY(FR_LOCKED),
    FRESULT_ENTRY(FR_NOT_ENOUGH_CORE),
    FRESULT_ENTRY(FR_TOO_MANY_OPEN_FILES),
    FRESULT_ENTRY(FR_INVALID_PARAMETER),
};

//*****************************************************************************
//
// A macro that holds the number of result codes.
//
//*****************************************************************************
#define NUM_FRESULT_CODES       (sizeof(g_psFResultStrings) /                 \
                                 sizeof(tFResultString))

//*****************************************************************************
//
// This function returns a string representation of an error code that was
// returned from a function call to FatFs.  It can be used for printing human
// readable error messages.
//
//*****************************************************************************
const char *
StringFromFResult(FRESULT iFResult)
{
    uint_fast8_t ui8Idx;

    //
    // Enter a loop to search the error code table for a matching error code.
    //
    for(ui8Idx = 0; ui8Idx < NUM_FRESULT_CODES; ui8Idx++)
    {
        //
        // If a match is found, then return the string name of the error code.
        //
        if(g_psFResultStrings[ui8Idx].iFResult == iFResult)
        {
            return(g_psFResultStrings[ui8Idx].pcResultStr);
        }
    }

    //
    // At this point no matching code was found, so return a string indicating
    // an unknown error.
    //
    return("UNKNOWN ERROR CODE");
}

//*****************************************************************************
//
// This is the handler for this SysTick interrupt.  FatFs requires a timer tick
// every 10 ms for internal timing purposes.
//
//*****************************************************************************
void
SysTickHandler(void)
{
    //
    // Call the FatFs tick timer.
    //
    disk_timerproc();
}

//*****************************************************************************
//
// Configure the UART.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Disable, Reset and Enable UART0
    //
    SysCtlPeripheralDisable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Wait for the UART0 peripheral to be ready for access
    //
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)))
    {
    }

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, g_ui32SysClock);
}

//*****************************************************************************
//
// This function implements the "ls" command.  It opens the current directory
// and enumerates through the contents, and prints a line for each item it
// finds.  It shows details such as file attributes, time and date, and the
// file size, along with the name.  It shows a summary of file sizes at the end
// along with free space.
//
//*****************************************************************************
int
Cmd_ls(int argc, char *argv[])
{
    uint32_t ui32TotalSize;
    uint32_t ui32FileCount;
    uint32_t ui32DirCount;
    FRESULT iFResult;
    FATFS *psFatFs;
    char *pcFileName;
#if _USE_LFN
    char pucLfn[_MAX_LFN + 1];
    g_sFileInfo.lfname = pucLfn;
    g_sFileInfo.lfsize = sizeof(pucLfn);
#endif


    //
    // Open the current directory for access.
    //
    iFResult = f_opendir(&g_sDirObject, g_pcCwdBuf);

    //
    // Check for error and return if there is a problem.
    //
    if(iFResult != FR_OK)
    {
        return((int)iFResult);
    }

    ui32TotalSize = 0;
    ui32FileCount = 0;
    ui32DirCount = 0;

    //
    // Give an extra blank line before the listing.
    //
    UARTprintf("\n");

    //
    // Enter loop to enumerate through all directory entries.
    //
    for(;;)
    {
        //
        // Read an entry from the directory.
        //
        iFResult = f_readdir(&g_sDirObject, &g_sFileInfo);

        //
        // Check for error and return if there is a problem.
        //
        if(iFResult != FR_OK)
        {
            return((int)iFResult);
        }

        //
        // If the file name is blank, then this is the end of the listing.
        //
        if(!g_sFileInfo.fname[0])
        {
            break;
        }

        //
        // If the attribue is directory, then increment the directory count.
        //
        if(g_sFileInfo.fattrib & AM_DIR)
        {
            ui32DirCount++;
        }

        //
        // Otherwise, it is a file.  Increment the file count, and add in the
        // file size to the total.
        //
        else
        {
            ui32FileCount++;
            ui32TotalSize += g_sFileInfo.fsize;
        }

#if _USE_LFN
        pcFileName = ((*g_sFileInfo.lfname)?g_sFileInfo.lfname:g_sFileInfo.fname);
#else
        pcFileName = g_sFileInfo.fname;
#endif
        //
        // Print the entry information on a single line with formatting to show
        // the attributes, date, time, size, and name.
        //
        UARTprintf("%c%c%c%c%c %u/%02u/%02u %02u:%02u %9u  %s\n",
                   (g_sFileInfo.fattrib & AM_DIR) ? 'D' : '-',
                   (g_sFileInfo.fattrib & AM_RDO) ? 'R' : '-',
                   (g_sFileInfo.fattrib & AM_HID) ? 'H' : '-',
                   (g_sFileInfo.fattrib & AM_SYS) ? 'S' : '-',
                   (g_sFileInfo.fattrib & AM_ARC) ? 'A' : '-',
                   (g_sFileInfo.fdate >> 9) + 1980,
                   (g_sFileInfo.fdate >> 5) & 15,
                   g_sFileInfo.fdate & 31,
                   (g_sFileInfo.ftime >> 11),
                   (g_sFileInfo.ftime >> 5) & 63,
                   g_sFileInfo.fsize,
                   pcFileName);
    }

    //
    // Print summary lines showing the file, dir, and size totals.
    //
    UARTprintf("\n%4u File(s),%10u bytes total\n%4u Dir(s)",
                ui32FileCount, ui32TotalSize, ui32DirCount);

    //
    // Get the free space.
    //
    iFResult = f_getfree("/", (DWORD *)&ui32TotalSize, &psFatFs);

    //
    // Check for error and return if there is a problem.
    //
    if(iFResult != FR_OK)
    {
        return((int)iFResult);
    }

    //
    // Display the amount of free space that was calculated.
    //
    UARTprintf(", %10uK bytes free\n", (ui32TotalSize *
                                        psFatFs->free_clust / 2));

    //
    // Made it to here, return with no errors.
    //
    return(0);
}

//*****************************************************************************
//
// This function implements the "cd" command.  It takes an argument that
// specifies the directory to make the current working directory.  Path
// separators must use a forward slash "/".  The argument to cd can be one of
// the following:
//
// * root ("/")
// * a fully specified path ("/my/path/to/mydir")
// * a single directory name that is in the current directory ("mydir")
// * parent directory ("..")
//
// It does not understand relative paths, so dont try something like this:
// ("../my/new/path")
//
// Once the new directory is specified, it attempts to open the directory to
// make sure it exists.  If the new path is opened successfully, then the
// current working directory (cwd) is changed to the new path.
//
//*****************************************************************************
int
Cmd_cd(int argc, char *argv[])
{
    uint_fast8_t ui8Idx;
    FRESULT iFResult;

    //
    // Copy the current working path into a temporary buffer so it can be
    // manipulated.
    //
    strcpy(g_pcTmpBuf, g_pcCwdBuf);

    //
    // If the first character is /, then this is a fully specified path, and it
    // should just be used as-is.
    //
    if(argv[1][0] == '/')
    {
        //
        // Make sure the new path is not bigger than the cwd buffer.
        //
        if(strlen(argv[1]) + 1 > sizeof(g_pcCwdBuf))
        {
            UARTprintf("Resulting path name is too long\n");
            return(0);
        }

        //
        // If the new path name (in argv[1])  is not too long, then copy it
        // into the temporary buffer so it can be checked.
        //
        else
        {
            strncpy(g_pcTmpBuf, argv[1], sizeof(g_pcTmpBuf));
        }
    }

    //
    // If the argument is .. then attempt to remove the lowest level on the
    // CWD.
    //
    else if(!strcmp(argv[1], ".."))
    {
        //
        // Get the index to the last character in the current path.
        //
        ui8Idx = strlen(g_pcTmpBuf) - 1;

        //
        // Back up from the end of the path name until a separator (/) is
        // found, or until we bump up to the start of the path.
        //
        while((g_pcTmpBuf[ui8Idx] != '/') && (ui8Idx > 1))
        {
            //
            // Back up one character.
            //
            ui8Idx--;
        }

        //
        // Now we are either at the lowest level separator in the current path,
        // or at the beginning of the string (root).  So set the new end of
        // string here, effectively removing that last part of the path.
        //
        g_pcTmpBuf[ui8Idx] = 0;
    }

    //
    // Otherwise this is just a normal path name from the current directory,
    // and it needs to be appended to the current path.
    //
    else
    {
        //
        // Test to make sure that when the new additional path is added on to
        // the current path, there is room in the buffer for the full new path.
        // It needs to include a new separator, and a trailing null character.
        //
        if(strlen(g_pcTmpBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_pcCwdBuf))
        {
            UARTprintf("Resulting path name is too long\n");
            return(0);
        }

        //
        // The new path is okay, so add the separator and then append the new
        // directory to the path.
        //
        else
        {
            //
            // If not already at the root level, then append a /
            //
            if(strcmp(g_pcTmpBuf, "/"))
            {
                strcat(g_pcTmpBuf, "/");
            }

            //
            // Append the new directory to the path.
            //
            strcat(g_pcTmpBuf, argv[1]);
        }
    }

    //
    // At this point, a candidate new directory path is in chTmpBuf.  Try to
    // open it to make sure it is valid.
    //
    iFResult = f_opendir(&g_sDirObject, g_pcTmpBuf);

    //
    // If it can't be opened, then it is a bad path.  Inform the user and
    // return.
    //
    if(iFResult != FR_OK)
    {
        UARTprintf("cd: %s\n", g_pcTmpBuf);
        return((int)iFResult);
    }

    //
    // Otherwise, it is a valid new path, so copy it into the CWD.
    //
    else
    {
        strncpy(g_pcCwdBuf, g_pcTmpBuf, sizeof(g_pcCwdBuf));
    }

    //
    // Return success.
    //
    return(0);
}

//*****************************************************************************
//
// This function implements the "del" command.  in the current working
// directory it deletes the file which is passed as the argument. Only one file
// can be deleted at a time and there is no return status if the filename is
// not correct or it does not exist.
//
//*****************************************************************************
int
Cmd_del(int argc, char *argv[])
{
    //
    // First, check to make sure that the current path (CWD), plus the file
    // name, plus a separator and trailing null, will all fit in the temporary
    // buffer that will be used to hold the file name.  The file name must be
    // fully specified, with path, to FatFs.
    //
    if(strlen(g_pcCwdBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_pcTmpBuf))
    {
        UARTprintf("Resulting path name is too long\n");
        return(0);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_pcTmpBuf, g_pcCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_pcCwdBuf))
    {
        strcat(g_pcTmpBuf, "/");
    }

    //
    // Now finally, append the file name to result in a fully specified file.
    //
    strcat(g_pcTmpBuf, argv[1]);

    //
    // Delete the file
    //
    f_unlink(g_pcTmpBuf);

    //
    // Return success.
    //
    return(0);
}

//*****************************************************************************
//
// This function implements the "enc" command. It is provided with 2 parameters
// The first parameter is an input wav file and the second parameter is the
// output opx file compressed with OPUS.
//
//*****************************************************************************
int
Cmd_encode(int argc, char *argv[])
{
    FRESULT  iFRdResult;
    FRESULT  iFWrResult;
    uint8_t  *pui8data;
    uint8_t  ui8ScaleFactor;
    char     cOpxDelimiter[4];
    char     *pcRdBuf;
    uint32_t ui32BytesRead;
    uint32_t ui32BytesWrite;
    uint32_t ui32Sizeofpopi16fmtBuffer;
    uint32_t ui32Loop;
    uint32_t ui32EncodedLen=0;
    uint32_t ui32RawLen=0;
    uint32_t ui32SizeOfRdBuf;
    int32_t  i32error;
    int32_t  i32len;

    tWaveHeader sWaveHeader;
    opus_int16 *popi16fmtBuffer;

    //
    // First, check to make sure that the current path (CWD), plus the file
    // name, plus a separator and trailing null, will all fit in the temporary
    // buffer that will be used to hold the file name.  The file name must be
    // fully specified, with path, to FatFs.
    //
    if(strlen(g_pcCwdBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_pcTmpBuf))
    {
        UARTprintf("Resulting path name is too long\n");
        return(0);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_pcTmpBuf, g_pcCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_pcCwdBuf))
    {
        strcat(g_pcTmpBuf, "/");
    }

    //
    // Now finally, append the file name to result in a fully specified file.
    //
    strcat(g_pcTmpBuf, argv[1]);

    //
    // Open the file for reading.
    //
    iFRdResult = f_open(&g_sFileReadObject, g_pcTmpBuf, FA_READ);

    //
    // If there was some problem opening the file, then return an error.
    //
    if(iFRdResult != FR_OK)
    {
        return((int)iFRdResult);
    }

    //
    // Get the Header Information
    //
    iFRdResult = f_read(&g_sFileReadObject, &sWaveHeader, sizeof(sWaveHeader),
                      (UINT *)&ui32BytesRead);

    //
    // Check if the WAV file header is correctly formatted
    //
    if((ustrncasecmp((char *)&sWaveHeader.ui8ChunkID[0],"RIFF",4) != 0) ||
       (ustrncasecmp((char *)&sWaveHeader.ui8Format[0],"WAVE",4) != 0) ||
       (ustrncasecmp((char *)&sWaveHeader.ui8SubChunk1ID[0],"fmt ",4) != 0) ||
       (ustrncasecmp((char *)&sWaveHeader.ui8SubChunk2ID[0],"data",4) != 0))
    {
        UARTprintf("ENC_ERR: WAV file is invalid\n");
        f_close(&g_sFileReadObject);
        return(0);
    }

    //
    // Since OPUS supports 8k, 16k, 24k, 32k or 48k sampling rates a check is
    // is made to see if the incoming audio stream also has the same property
    //
    if((sWaveHeader.ui32SampleRate != 8000)  &&
       (sWaveHeader.ui32SampleRate != 16000) &&
       (sWaveHeader.ui32SampleRate != 24000) &&
       (sWaveHeader.ui32SampleRate != 32000) &&
       (sWaveHeader.ui32SampleRate != 48000) )
    {
        UARTprintf("ENC_ERR: Sample Rate Must be either 8k, 16k, 24k, 32k or ");
        UARTprintf("48k\n");
        f_close(&g_sFileReadObject);
        return(0);
    }

    //
    // Only Linear PCM format is supported
    //
    if(sWaveHeader.ui16AudioFormat != 0x1)
    {
        UARTprintf("ENC_ERR: Only Linear PCM Format Supported\n");
        f_close(&g_sFileReadObject);
        return(0);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_pcTmpBuf, g_pcCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_pcCwdBuf))
    {
        strcat(g_pcTmpBuf, "/");
    }

    //
    // Now finally, append the file name to result in a fully specified file.
    //
    strcat(g_pcTmpBuf, argv[2]);

    //
    // Open the file for writing.
    //
    iFWrResult = f_open(&g_sFileWriteObject, g_pcTmpBuf,
            (FA_WRITE | FA_CREATE_NEW));

    //
    // If there was some problem opening the file, then return an error.
    //
    if(iFWrResult != FR_OK)
    {
        f_close(&g_sFileReadObject);
        return((int)iFWrResult);
    }

    //
    // Create the encoder
    //
    sOpusEnc = opus_encoder_create(sWaveHeader.ui32SampleRate,
            sWaveHeader.ui16NumChannels, OPUS_APPLICATION_AUDIO, &i32error);

    //
    // If there is an error creating the encoder then close the input and
    // output file handle. Else print the information on the file parameters
    //
    if (i32error != OPUS_OK)
    {
       UARTprintf("ENC_ERR: Cannot create encoder: %s\n",
               opus_strerror(i32error));
       f_close(&g_sFileReadObject);
       f_close(&g_sFileWriteObject);
       return(0);
    }
    else
    {
           UARTprintf("Encoding %d channel %d bits %d Hz WAV file\n",
                   sWaveHeader.ui16NumChannels,sWaveHeader.ui16BitsPerSample,
                sWaveHeader.ui32SampleRate);
    }

    //
    // Set the OPUS encoder parameters
    //
    opus_encoder_ctl(sOpusEnc, OPUS_SET_BITRATE(
            (sWaveHeader.ui32SampleRate*OPUS_BITRATE_SCALER)));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_VBR(1));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_VBR_CONSTRAINT(0));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_COMPLEXITY(0));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_INBAND_FEC(0));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_FORCE_CHANNELS(OPUS_AUTO));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_DTX(0));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_PACKET_LOSS_PERC(0));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_LSB_DEPTH(
            sWaveHeader.ui16BitsPerSample));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_EXPERT_FRAME_DURATION(
            OPUS_FRAMESIZE_ARG));
    opus_encoder_ctl(sOpusEnc, OPUS_SET_FORCE_MODE(MODE_CELT_ONLY));

    //
    // Dynamic allocation of memory for the sd card read buffer, output from
    // the codec and formatted input buffer for the codec
    //
    ui8ScaleFactor = (sWaveHeader.ui16BitsPerSample) >> 3;

    pui8data = (uint8_t *)calloc(OPUS_MAX_PACKET,sizeof(uint8_t));
    pcRdBuf = (char *)calloc((((sWaveHeader.ui32SampleRate*
            OPUS_FRAME_SIZE_IN_MS*
            sWaveHeader.ui16NumChannels*
            ui8ScaleFactor)/1000)+1),
            sizeof(uint8_t));
    popi16fmtBuffer = (opus_int16 *)calloc((((sWaveHeader.ui32SampleRate*
            OPUS_FRAME_SIZE_IN_MS*
            sWaveHeader.ui16NumChannels)/1000)+1),
            sizeof(opus_int16));

    ui32SizeOfRdBuf = (sWaveHeader.ui32SampleRate*
            sWaveHeader.ui16NumChannels*
            OPUS_FRAME_SIZE_IN_MS*
            ui8ScaleFactor)/1000;
    ui32Sizeofpopi16fmtBuffer = (sWaveHeader.ui32SampleRate*
            OPUS_FRAME_SIZE_IN_MS*
            sWaveHeader.ui16NumChannels*
            sizeof(opus_int16))/1000;

    //
    // Create the opx file header
    //
    strcpy(cOpxDelimiter, "HDR\0");
    iFWrResult = f_write(&g_sFileWriteObject, &cOpxDelimiter[0],
            4, (UINT *)&ui32BytesWrite);
    iFWrResult = f_write(&g_sFileWriteObject, &sWaveHeader.ui16NumChannels,
            2, (UINT *)&ui32BytesWrite);
    iFWrResult = f_write(&g_sFileWriteObject, &sWaveHeader.ui16BitsPerSample,
            2, (UINT *)&ui32BytesWrite);
    iFWrResult = f_write(&g_sFileWriteObject, &sWaveHeader.ui32SampleRate,
            4, (UINT *)&ui32BytesWrite);
    iFWrResult = f_write(&g_sFileWriteObject, &sWaveHeader.ui32SubChunk2Size,
            4, (UINT *)&ui32BytesWrite);

    //
    // Enter a loop to repeatedly read the wav data from the file, encode it
    // and then store it in the sd card.
    //
    do
    {
        //
        // Read a block of data from the file as specified by the selected
        // frame size in the header file
        //
        iFRdResult = f_read(&g_sFileReadObject, pcRdBuf, ui32SizeOfRdBuf,
                          (UINT *)&ui32BytesRead);

        //
        // Process the data as per the scale factor. A scale factor of 1 is
        // applied when the data is 8 bit and a scale factor of 2 is applied
        // when the data is 16 bit.
        //
        for(ui32Loop = 0 ; ui32Loop < ui32BytesRead ; ui32Loop++)
        {
            if(ui8ScaleFactor == 1)
            {
                   popi16fmtBuffer[ui32Loop] = (opus_int16)pcRdBuf[ui32Loop];
            }
            else if(ui8ScaleFactor == 2)
            {
                if(ui32Loop%2 == 0)
                    popi16fmtBuffer[ui32Loop/2] = pcRdBuf[ui32Loop];
                else
                    popi16fmtBuffer[ui32Loop/2] |= (pcRdBuf[ui32Loop] << 8);
            }

        }

        //
        // If there was an error reading the data then free the buffers, close
        // the file handlers, destory the encoded structure.
        //
        if(iFRdResult != FR_OK)
        {
            free(pui8data);
            free(pcRdBuf);
            free(popi16fmtBuffer);
            f_close(&g_sFileReadObject);
            f_close(&g_sFileWriteObject);
            opus_encoder_destroy(sOpusEnc);
            return((int)iFRdResult);
        }

        //
        // If no error with file handling then start the compression.
        //
        i32len = opus_encode(sOpusEnc,
                popi16fmtBuffer,
                (ui32Sizeofpopi16fmtBuffer/2),
                pui8data,
                OPUS_MAX_PACKET);

        //
        // If this is not the last packet then add the 'Mid ' as delimiter
        // else add 'End ' as the delimiter which will be used during the
        // decompression process.
        //
        if(ui32BytesRead == ui32SizeOfRdBuf)
        {
            strcpy(cOpxDelimiter, "Mid\0");
        }
        else
        {
            strcpy(cOpxDelimiter, "End\0");
        }

        //
        // Store the compressed data with length of data, followed by the
        // delimiter and then the actual compressed data
        //
        iFWrResult = f_write(&g_sFileWriteObject, &cOpxDelimiter[0], 4,
                              (UINT *)&ui32BytesWrite);
        iFWrResult = f_write(&g_sFileWriteObject, &i32len, 4,
                              (UINT *)&ui32BytesWrite);
        iFWrResult = f_write(&g_sFileWriteObject, pui8data, i32len,
                              (UINT *)&ui32BytesWrite);

        //
        // Add the length of the wav file and the compressed data for printing
        // the statistics
        //
        ui32EncodedLen += i32len;
        ui32RawLen     += ui32BytesRead;

        UARTprintf("OPUS Encoder Completion: %03d\r",
                ((ui32RawLen*100)/sWaveHeader.ui32SubChunk2Size));
    }
    while(ui32BytesRead == ui32SizeOfRdBuf);

    //
    // Print the compression statistics
    //
    UARTprintf("\n***********STATISTICS*************\n");
    UARTprintf("Raw WAV Bytes      = %d\n", ui32RawLen);
    UARTprintf("Encoded OPX Bytes  = %d\n", ui32EncodedLen);
    UARTprintf("Compression Factor = %02d.%02d\n", (ui32RawLen/ui32EncodedLen),
            (((ui32RawLen*100)/ui32EncodedLen)-((ui32RawLen/ui32EncodedLen)*100)));

    //
    // Free the buffers that have been dynamically allocated
    //
    free(pui8data);
    free(pcRdBuf);
    free(popi16fmtBuffer);

    //
    // Close Read and Write file
    //
    f_close(&g_sFileReadObject);
    f_close(&g_sFileWriteObject);

    //
    // free the memory assigned to the encode
    //
    opus_encoder_destroy(sOpusEnc);

    //
    // Return success.
    //
    return(0);
}

#ifdef PERFORMANCE_TEST
//*****************************************************************************
//
// This function implements the "testenc" command. It tests the encoder by
// reading an input wav file and runs ths encoder with different complexity
// setting. There is no output file generated but only statistics.
//
//*****************************************************************************
int
Cmd_testencode(int argc, char *argv[])
{
    FRESULT  iFRdResult;
    uint8_t  *pui8data;
    uint8_t  ui8ScaleFactor;
    char     *pcRdBuf;
    uint32_t ui32BytesRead;
    uint32_t ui32Sizeofpopi16fmtBuffer;
    uint32_t ui32Loop;
    uint32_t ui32EncodedLen;
    uint32_t ui32RawLen;
    uint32_t ui32TimeStart;
    uint32_t ui32TimeElapsed;
    uint32_t ui32FrameCount;
    uint32_t ui32SizeOfRdBuf;
    int32_t  i32error;
    int32_t  i32len;
    uint8_t  ui8ComplexityIndex;

    tWaveHeader sWaveHeader;
    opus_int16 *popi16fmtBuffer;

    //
    // First, check to make sure that the current path (CWD), plus the file
    // name, plus a separator and trailing null, will all fit in the temporary
    // buffer that will be used to hold the file name.  The file name must be
    // fully specified, with path, to FatFs.
    //
    if(strlen(g_pcCwdBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_pcTmpBuf))
    {
        UARTprintf("Resulting path name is too long\n");
        return(0);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_pcTmpBuf, g_pcCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_pcCwdBuf))
    {
        strcat(g_pcTmpBuf, "/");
    }

    //
    // Now finally, append the file name to result in a fully specified file.
    //
    strcat(g_pcTmpBuf, argv[1]);

    //
    // Print the header for the encoder performance
    //
    UARTprintf("\n\n");
    UARTprintf("INPUT STREAM SIZE %d ms\n\n",OPUS_FRAME_SIZE_IN_MS);
    UARTprintf("***************************************ENCODER STATISTICS*****************************************\n\n");
    UARTprintf("COMPLEXITY | RAW DATA | OUTPUT DATA | FRAMES | TOTAL TIME (s) | COMPRESSION | PER FRAME TIME (ms)\n\n");

    //
    // Loop through the different complexity for the encoder
    //
    for(ui8ComplexityIndex = 0; ui8ComplexityIndex < 11 ;ui8ComplexityIndex++)
    {
        //
        // Reset the statistic counters to 0
        //
        ui32EncodedLen  = 0;
        ui32RawLen      = 0;
        ui32TimeElapsed = 0;
        ui32FrameCount  = 0;

        //
        // Reset the timer and wait for the timer to be ready
        //
        SysCtlPeripheralDisable(SYSCTL_PERIPH_TIMER2);
        SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER2);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

        while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2)))
        {
        }

        //
        // Configure the Statistic timer for 32 bit up count mode
        //
        TimerConfigure(TIMER2_BASE, TIMER_CFG_ONE_SHOT_UP);
        TimerLoadSet(TIMER2_BASE, TIMER_A, 0xFFFFFFFF);

        //
        // Open the file for reading.
        //
        iFRdResult = f_open(&g_sFileReadObject, g_pcTmpBuf, FA_READ);

        //
        // If there was some problem opening the file, then return an error.
        //
        if(iFRdResult != FR_OK)
        {
            return((int)iFRdResult);
        }

        //
        // Get the Header Information
        //
        iFRdResult = f_read(&g_sFileReadObject, &sWaveHeader, sizeof(sWaveHeader),
                          (UINT *)&ui32BytesRead);

        //
        // Check if the WAV file header is correctly formatted
        //
        if((ustrncasecmp((char *)&sWaveHeader.ui8ChunkID[0],"RIFF",4) != 0) ||
           (ustrncasecmp((char *)&sWaveHeader.ui8Format[0],"WAVE",4) != 0) ||
           (ustrncasecmp((char *)&sWaveHeader.ui8SubChunk1ID[0],"fmt ",4) != 0) ||
           (ustrncasecmp((char *)&sWaveHeader.ui8SubChunk2ID[0],"data",4) != 0))
        {
            UARTprintf("ENC_ERR: WAV file is invalid\n");
            f_close(&g_sFileReadObject);
            return(0);
        }

        //
        // Since OPUS supports 8k, 16k, 24k, 32k or 48k sampling rates a check is
        // is made to see if the incoming audio stream also has the same property
        //
        if((sWaveHeader.ui32SampleRate != 8000)  &&
           (sWaveHeader.ui32SampleRate != 16000) &&
           (sWaveHeader.ui32SampleRate != 24000) &&
           (sWaveHeader.ui32SampleRate != 32000) &&
           (sWaveHeader.ui32SampleRate != 48000) )
        {
            UARTprintf("ENC_ERR: Sample Rate Must be either 8k, 16k, 24k, 32k or ");
            UARTprintf("48k\n");
            f_close(&g_sFileReadObject);
            return(0);
        }

        //
        // Only Linear PCM format is supported
        //
        if(sWaveHeader.ui16AudioFormat != 0x1)
        {
            UARTprintf("ENC_ERR: Only Linear PCM Format Supported\n");
            f_close(&g_sFileReadObject);
            return(0);
        }

        //
        // Create the encoder
        //
        sOpusEnc = opus_encoder_create(sWaveHeader.ui32SampleRate,
                sWaveHeader.ui16NumChannels, OPUS_APPLICATION_AUDIO, &i32error);

        //
        // If there is an error creating the encoder then close the input and
        // output file handle. Else print the information on the file parameters
        //
        if (i32error != OPUS_OK)
        {
           UARTprintf("ENC_ERR: Cannot create encoder: %s\n",
                   opus_strerror(i32error));
           f_close(&g_sFileReadObject);
           f_close(&g_sFileWriteObject);
           return(0);
        }

        //
        // Set the OPUS encoder parameters
        //
        opus_encoder_ctl(sOpusEnc, OPUS_SET_BITRATE(
                (sWaveHeader.ui32SampleRate*OPUS_BITRATE_SCALER)));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_VBR(1));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_VBR_CONSTRAINT(0));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_COMPLEXITY(
                ui8ComplexityIndex));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_INBAND_FEC(0));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_FORCE_CHANNELS(OPUS_AUTO));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_DTX(0));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_PACKET_LOSS_PERC(0));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_LSB_DEPTH(
                sWaveHeader.ui16BitsPerSample));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_EXPERT_FRAME_DURATION(
                OPUS_FRAMESIZE_ARG));
        opus_encoder_ctl(sOpusEnc, OPUS_SET_FORCE_MODE(MODE_CELT_ONLY));

        //
        // Dynamic allocation of memory for the sd card read buffer, output from
        // the codec and formatted input buffer for the codec
        //
        ui8ScaleFactor = (sWaveHeader.ui16BitsPerSample) >> 3;

        pui8data = (uint8_t *)calloc(OPUS_MAX_PACKET,sizeof(uint8_t));
        pcRdBuf = (char *)calloc((((sWaveHeader.ui32SampleRate*
                OPUS_FRAME_SIZE_IN_MS*
                sWaveHeader.ui16NumChannels*
                ui8ScaleFactor)/1000)+1),
                sizeof(uint8_t));
        popi16fmtBuffer = (opus_int16 *)calloc((((sWaveHeader.ui32SampleRate*
                OPUS_FRAME_SIZE_IN_MS*
                sWaveHeader.ui16NumChannels)/1000)+1),
                sizeof(opus_int16));

        ui32SizeOfRdBuf = (sWaveHeader.ui32SampleRate*
                sWaveHeader.ui16NumChannels*
                OPUS_FRAME_SIZE_IN_MS*
                ui8ScaleFactor)/1000;
        ui32Sizeofpopi16fmtBuffer = (sWaveHeader.ui32SampleRate*
                OPUS_FRAME_SIZE_IN_MS*
                sWaveHeader.ui16NumChannels*
                sizeof(opus_int16))/1000;

        //
        // Enter a loop to repeatedly read the wav data from the file, encode it
        // and then store it in the sd card.
        //
        do
        {
            //
            // Read a block of data from the file as specified by the selected
            // frame size in the header file
            //
            iFRdResult = f_read(&g_sFileReadObject, pcRdBuf, ui32SizeOfRdBuf,
                              (UINT *)&ui32BytesRead);

            //
            // Process the data as per the scale factor. A scale factor of 1 is
            // applied when the data is 8 bit and a scale factor of 2 is applied
            // when the data is 16 bit.
            //
            for(ui32Loop = 0 ; ui32Loop < ui32BytesRead ; ui32Loop++)
            {
                if(ui8ScaleFactor == 1)
                {
                       popi16fmtBuffer[ui32Loop] = (opus_int16)pcRdBuf[ui32Loop];
                }
                else if(ui8ScaleFactor == 2)
                {
                    if(ui32Loop%2 == 0)
                        popi16fmtBuffer[ui32Loop/2] = pcRdBuf[ui32Loop];
                    else
                        popi16fmtBuffer[ui32Loop/2] |= (pcRdBuf[ui32Loop] << 8);
                }

            }

            //
            // If there was an error reading the data then free the buffers, close
            // the file handlers, destory the encoded structure.
            //
            if(iFRdResult != FR_OK)
            {
                free(pui8data);
                free(pcRdBuf);
                free(popi16fmtBuffer);
                f_close(&g_sFileReadObject);
                opus_encoder_destroy(sOpusEnc);
                return((int)iFRdResult);
            }

            //
            // Enable the timer
            //
            TimerEnable(TIMER2_BASE, TIMER_A);
            ui32TimeStart = TimerValueGet(TIMER2_BASE, TIMER_A);

            //
            // If no error with file handling then start the compression.
            //
            i32len = opus_encode(sOpusEnc,
                    popi16fmtBuffer,
                    (ui32Sizeofpopi16fmtBuffer/2),
                    pui8data,
                    OPUS_MAX_PACKET);

            //
            // Disable the timer and get the value
            //
            TimerDisable(TIMER2_BASE, TIMER_A);

            ui32TimeElapsed += (TimerValueGet(TIMER2_BASE, TIMER_A) - ui32TimeStart);

            //
            // Add the length of the wav file and the compressed data for printing
            // the statistics
            //
            ui32EncodedLen += i32len;
            ui32RawLen     += ui32BytesRead;
            ui32FrameCount++;

        }
        while(ui32BytesRead == ui32SizeOfRdBuf);

        //
        // Print the compression statistics
        //
        UARTprintf("%02d           ", ui8ComplexityIndex);
        UARTprintf("%07d     ", ui32RawLen);
        UARTprintf("%07d      ", ui32EncodedLen);
        UARTprintf("%05d     ", ui32FrameCount);
        UARTprintf("%03d.%03d          ", (ui32TimeElapsed/g_ui32SysClock),
                ((ui32TimeElapsed/(g_ui32SysClock/1000))-
                        ((ui32TimeElapsed/g_ui32SysClock)*1000)));
        UARTprintf("%02d.%02d          ", (ui32RawLen/ui32EncodedLen),
                (((ui32RawLen*100)/ui32EncodedLen)-
                        ((ui32RawLen/ui32EncodedLen)*100)));
        UARTprintf("%02d.%03d\n",
                ((ui32TimeElapsed/(g_ui32SysClock/1000))/ui32FrameCount),
                ((ui32TimeElapsed/((g_ui32SysClock/1000000)*ui32FrameCount))-
                ((ui32TimeElapsed/((g_ui32SysClock/1000)*ui32FrameCount))*1000)));

        //
        // Free the buffers that have been dynamically allocated
        //
        free(pui8data);
        free(pcRdBuf);
        free(popi16fmtBuffer);

        //
        // Close Read and Write file
        //
        f_close(&g_sFileReadObject);

        //
        // free the memory assigned to the encode
        //
        opus_encoder_destroy(sOpusEnc);
    }

    //
    // Return success.
    //
    return(0);
}
#endif // PERFORMANCE_TEST

//*****************************************************************************
//
// This function implements the "dec" command. It is provided with 2 parameters
// The first parameter is an input opx file and the second parameter is the
// output wav file decompressed with OPUS.
//
//*****************************************************************************
int
Cmd_decode(int argc, char *argv[])
{
    FRESULT  iFRdResult;
    FRESULT  iFWrResult;
    uint8_t  *pcRdBuf;
    uint8_t  ui8ProgressDisplay=0;
    char     cOpxDelimiter[4];
    uint16_t ui32BitsPerSample;
    uint16_t ui32Channel;
    uint32_t ui32BytesRead;
    uint32_t ui32BytesWrite;
    uint32_t ui32SizeOfOutBuf;
    uint32_t ui32Loop;
    uint32_t ui32SamplingRate;
    uint32_t ui32WavFileSize;
    uint32_t ui32EncodedLen=0;
    uint32_t ui32RawLen=0;
    int32_t  i32error;
    int32_t  i32len;
    int32_t  i32OutSamples;
    tWaveHeader sWaveHeader;
    opus_int16 *pcop16OutBuf;

    //
    // First, check to make sure that the current path (CWD), plus the file
    // name, plus a separator and trailing null, will all fit in the temporary
    // buffer that will be used to hold the file name.  The file name must be
    // fully specified, with path, to FatFs.
    //
    if(strlen(g_pcCwdBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_pcTmpBuf))
    {
        UARTprintf("Resulting path name is too long\n");
        return(0);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_pcTmpBuf, g_pcCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_pcCwdBuf))
    {
        strcat(g_pcTmpBuf, "/");
    }

    //
    // Now finally, append the file name to result in a fully specified file.
    //
    strcat(g_pcTmpBuf, argv[1]);

    //
    // Open the file for reading.
    //
    iFRdResult = f_open(&g_sFileReadObject, g_pcTmpBuf, FA_READ);

    //
    // If there was some problem opening the file, then return an error.
    //
    if(iFRdResult != FR_OK)
    {
        return((int)iFRdResult);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_pcTmpBuf, g_pcCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_pcCwdBuf))
    {
        strcat(g_pcTmpBuf, "/");
    }

    //
    // Now finally, append the file name to result in a fully specified file.
    //
    strcat(g_pcTmpBuf, argv[2]);

    //
    // Open the file for writing.
    //
    iFWrResult = f_open(&g_sFileWriteObject, g_pcTmpBuf,
            (FA_WRITE | FA_CREATE_NEW));

    //
    // If there was some problem opening the file, then close the read file
    // handle and return an error.
    //
    if(iFWrResult != FR_OK)
    {
        f_close(&g_sFileReadObject);
        return((int)iFWrResult);
    }

    //
    // Read the opx file for header information
    //
    iFRdResult = f_read(&g_sFileReadObject, &cOpxDelimiter, 4,
                      (UINT *)&ui32BytesRead);
    iFRdResult = f_read(&g_sFileReadObject, &ui32Channel, 2,
                      (UINT *)&ui32BytesRead);
    iFRdResult = f_read(&g_sFileReadObject, &ui32BitsPerSample, 2,
                      (UINT *)&ui32BytesRead);
    iFRdResult = f_read(&g_sFileReadObject, &ui32SamplingRate, 4,
                      (UINT *)&ui32BytesRead);
    iFRdResult = f_read(&g_sFileReadObject, &ui32WavFileSize, 4,
                      (UINT *)&ui32BytesRead);

    //
    // If the ASCII string 'HDR' is not found then this may not b a valid opx
    // file and close the file handlers
    //
    if(ustrncasecmp(&cOpxDelimiter[0],"HDR",3) != 0)
    {
        UARTprintf("DEC_ERR: OPX file is invalid\n");
        f_close(&g_sFileWriteObject);
        f_close(&g_sFileReadObject);
        return(0);
    }
    else
    {
        UARTprintf("DEC: Original File is %d bytes\n",ui32WavFileSize);
    }

    //
    // Create the WAV file header using information collected during the
    // decompression process.
    //
    strcpy((char *)sWaveHeader.ui8ChunkID,"RIFF");
    strcpy((char *)sWaveHeader.ui8Format,"WAVE");
    strcpy((char *)sWaveHeader.ui8SubChunk1ID,"fmt ");
    strcpy((char *)sWaveHeader.ui8SubChunk2ID,"data");
    sWaveHeader.ui32ChunkSize = 36;
    sWaveHeader.ui32SubChunk1Size = 16;
    sWaveHeader.ui16AudioFormat = 1;
    sWaveHeader.ui16NumChannels = ui32Channel;
    sWaveHeader.ui32SampleRate = ui32SamplingRate;
    sWaveHeader.ui32ByteRate = ui32SamplingRate*ui32Channel*(ui32BitsPerSample/8);
    sWaveHeader.ui16BlockAlign = ui32Channel*(ui32BitsPerSample/8);
    sWaveHeader.ui16BitsPerSample = ui32BitsPerSample;
    sWaveHeader.ui32SubChunk2Size = 0;

    //
    // Write the wav file header to the final file
    //
    iFWrResult = f_write(&g_sFileWriteObject,
            &sWaveHeader,
            sizeof(sWaveHeader),
            (UINT *)&ui32BytesWrite);

    //
    // If the opx file format is correct then create the decoder
    //
    sOpusDec = opus_decoder_create(ui32SamplingRate, ui32Channel, &i32error);

    //
    // If there was some problem creating the OPUS decoder, then close the write
    // and read file handle and return an error
    //
    if (i32error != OPUS_OK)
    {
       UARTprintf("DEC_ERR: Cannot create decoder: %s\n", opus_strerror(i32error));
       f_close(&g_sFileWriteObject);
       f_close(&g_sFileReadObject);
       return((int)i32error);
    }
    else
    {
        UARTprintf("Decoding %d Channels at %d Sampling Rate\n",ui32Channel,ui32SamplingRate);
    }

    //
    // Set the parameters for the OPUS decoder
    //
    opus_decoder_ctl(sOpusDec, OPUS_SET_LSB_DEPTH(ui32BitsPerSample));

    //
    // Dynamic allocation of memory for the sd card read buffer and the output
    // from the codec.
    //
    ui32SizeOfOutBuf = (ui32SamplingRate*
            ui32Channel*
            OPUS_FRAME_SIZE_IN_MS*
            OPUS_DATA_SCALER)/1000;
    pcop16OutBuf     = (int16_t*)calloc((
            (ui32SizeOfOutBuf/OPUS_DATA_SCALER)+1),
            sizeof(int16_t));
    pcRdBuf          = (uint8_t *)calloc(OPUS_MAX_PACKET,sizeof(uint8_t));

    //
    // Enter a loop to repeatedly read data from the file and display it, until
    // the end of the file is reached.
    //
    do
    {
        //
        // Read the delimiter and length first
        //
        iFRdResult = f_read(&g_sFileReadObject, &cOpxDelimiter, 4,
                          (UINT *)&ui32BytesRead);
        iFRdResult = f_read(&g_sFileReadObject, &i32len, 4,
                          (UINT *)&ui32BytesRead);

        //
        // Read a block of data from the file as specified by the length.
        //
        iFRdResult = f_read(&g_sFileReadObject, pcRdBuf, i32len,
                          (UINT *)&ui32BytesRead);

        //
        // If there was an error reading, then print a newline and return the
        // error to the user.
        //
        if(iFRdResult != FR_OK)
        {
            UARTprintf("DEC_ERR: File Processing Error\n");

            //
            // Free the buffers
            //
            free(pcop16OutBuf);
            free(pcRdBuf);

            //
            // Close Write file
            //
            f_close(&g_sFileReadObject);
            f_close(&g_sFileWriteObject);

            //
            // destroy the decoder to free up the memory
            //
            opus_decoder_destroy(sOpusDec);

            return((int)iFRdResult);

        }

        //
        // Now start the decompression process
        //
        i32OutSamples = opus_decode(sOpusDec,
                (const unsigned char *)&pcRdBuf[0],
                i32len,
                pcop16OutBuf,
                (ui32SizeOfOutBuf/OPUS_DATA_SCALER), 0);

        //
        // If there is an error in the decoder then free the buffer and
        // destroy the decoder to free the memory
        //
        if (i32OutSamples < OPUS_OK)
        {
           UARTprintf("DEC_ERR: Decode Failed %s\n", opus_strerror(i32error));

           free(pcop16OutBuf);
           free(pcRdBuf);

           f_close(&g_sFileReadObject);
           f_close(&g_sFileWriteObject);

           opus_decoder_destroy(sOpusDec);

           return(1);
        }

        //
        // Based on the original bits per sample, perform bit operation for
        // final wav file
        //
        if(ui32BitsPerSample == 8)
        {
            //
            // If the data is 8 bit then convert from signed to unsigned format
            //
            for(ui32Loop = 0 ; ui32Loop < (i32OutSamples) ; ui32Loop++)
            {
                pcRdBuf[ui32Loop] = (uint8_t)(pcop16OutBuf[ui32Loop] ^ 0x80);
            }

            //
            // Write the data to the temporary file
            //
            iFWrResult = f_write(&g_sFileWriteObject, pcRdBuf, i32OutSamples,
                                  (UINT *)&ui32BytesWrite);

            //
            // Add the number of bytes from the decoder output for statistics
            //
            ui32RawLen     += i32OutSamples;
        }
        else
        {
            //
            // If the data is 16 bit then write the data as is to the output
            // temporary file
            //
            iFWrResult = f_write(&g_sFileWriteObject, pcop16OutBuf, (i32OutSamples*OPUS_DATA_SCALER),
                                  (UINT *)&ui32BytesWrite);

            //
            // Add the number of bytes from the decoder output for statistics
            //
            ui32RawLen     += i32OutSamples*OPUS_DATA_SCALER;
        }

        //
        // Add the opx file byte length for each of the segments for statistic.
        //
        ui32EncodedLen += i32len;

        //
        // Increment the progress display on the command line
        //
        ui8ProgressDisplay++;

        if((ui8ProgressDisplay/100) == 1)
        {
            ui8ProgressDisplay = 0;
            UARTprintf("\r.");
        }
        else if((ui8ProgressDisplay%20) == 0)
        {
            UARTprintf(".");
        }
    }
    while(ustrncasecmp(&cOpxDelimiter[0],"End",3) != 0);

    UARTprintf("\r");

    //
    // Go back to top of the file to update the Size of the file
    //
    f_lseek(&g_sFileWriteObject, 0);

    //
    // Create the WAV file header using information collected during the
    // decompression process.
    //
    sWaveHeader.ui32ChunkSize = ui32RawLen + 36;
    sWaveHeader.ui32SubChunk2Size = ui32RawLen;

    //
    // Write the wav file header to the final file
    //
    iFWrResult = f_write(&g_sFileWriteObject,
            &sWaveHeader,
            sizeof(sWaveHeader),
            (UINT *)&ui32BytesWrite);

    //
    // Free the buffers
    //
    free(pcop16OutBuf);
    free(pcRdBuf);

    //
    // Close Write file
    //
    f_close(&g_sFileReadObject);
    f_close(&g_sFileWriteObject);

    //
    // destriy the decoder to free the memory allocated to it.
    //
    opus_decoder_destroy(sOpusDec);

    //
    // Print the statistics
    //
    UARTprintf("\n***********STATISTICS*************\n");
    UARTprintf("Input OPX Bytes   = %d\n", ui32EncodedLen);
    UARTprintf("Decoded WAV Bytes = %d\n", ui32RawLen);

    //
    // Return success.
    //
    return(0);
}

//*****************************************************************************
//
// This function implements the "help" command.  It prints a simple list of the
// available commands with a brief description.
//
//*****************************************************************************
int
Cmd_help(int argc, char *argv[])
{
    tCmdLineEntry *psEntry;

    //
    // Print some header text.
    //
    UARTprintf("\nAvailable commands\n");
    UARTprintf("------------------\n");

    //
    // Point at the beginning of the command table.
    //
    psEntry = &g_psCmdTable[0];

    //
    // Enter a loop to read each entry from the command table.  The end of the
    // table has been reached when the command name is NULL.
    //
    while(psEntry->pcCmd)
    {
        //
        // Print the command name and the brief description.
        //
        UARTprintf("%6s: %s\n", psEntry->pcCmd, psEntry->pcHelp);

        //
        // Advance to the next entry in the table.
        //
        psEntry++;
    }

    //
    // Return success.
    //
    return(0);
}

//*****************************************************************************
//
// This is the table that holds the command names, implementing functions, and
// brief description.
//
//*****************************************************************************
tCmdLineEntry g_psCmdTable[] =
{
    { "help",   Cmd_help,   "Display list of commands" },
    { "h",      Cmd_help,   "alias for help" },
    { "?",      Cmd_help,   "alias for help" },
    { "ls",     Cmd_ls,     "Display list of files" },
    { "del",    Cmd_del,    "Delete a file" },
    { "cd",     Cmd_cd,     "Change Directory" },
    { "dec",    Cmd_decode, "Decode Opus to WAV PCM" },
    { "enc",    Cmd_encode, "Encode WAV PCM to Opus" },
#ifdef PERFORMANCE_TEST
    { "testenc",Cmd_testencode, "Run Test on OPUS Encoder" },
#endif
    { 0, 0, 0 }
};

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// The program main function.  It performs initialization, then runs a command
// processing loop to read commands from the console.
//
//*****************************************************************************
int
main(void)
{
    int nStatus;
    FRESULT iFResult;

    //
    // Run from the PLL at 120 MHz.
    //
    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                         SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                         SYSCTL_CFG_VCO_480), 120000000);

    //
    // Configure the device pins.
    //
    PinoutSet();

    //
    // Configure the IO Console
    //
    ConfigureUART();

    //
    // Configure SysTick for a 100Hz interrupt.
    //
    ROM_SysTickPeriodSet(g_ui32SysClock / TICKS_PER_SECOND);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();

    //
    // Print the welcome message
    //
    UARTprintf("\r\nOPUS Encode and Decode Example...\n");

    //
    // Mount the file system, using logical disk 0.
    //
    iFResult = f_mount(0, &g_sFatFs);
    if(iFResult != FR_OK)
    {
        UARTprintf("f_mount error: %s\n", StringFromFResult(iFResult));
        return(1);
    }

    //
    // Enter an infinite loop for reading and processing commands from the
    // user.
    //
    while(1)
    {
        //
        // Print a prompt to the console.  Show the CWD.
        //
        UARTprintf("\n%s> ", g_pcCwdBuf);

        //
        // Get a line of text from the user.
        //
        UARTgets(g_pcCmdBuf, sizeof(g_pcCmdBuf));

        //
        // Pass the line from the user to the command processor.  It will be
        // parsed and valid commands executed.
        //
        nStatus = CmdLineProcess(g_pcCmdBuf);

        //
        // Handle the case of bad command.
        //
        if(nStatus == CMDLINE_BAD_CMD)
        {
            UARTprintf("Bad command!\n");
        }

        //
        // Handle the case of too many arguments.
        //
        else if(nStatus == CMDLINE_TOO_MANY_ARGS)
        {
            UARTprintf("Too many arguments for command processor!\n");
        }

        //
        // Otherwise the command was executed.  Print the error code if one was
        // returned.
        //
        else if(nStatus != 0)
        {
            UARTprintf("Command returned error code %s\n",
                        StringFromFResult((FRESULT)nStatus));
        }
    }
}
