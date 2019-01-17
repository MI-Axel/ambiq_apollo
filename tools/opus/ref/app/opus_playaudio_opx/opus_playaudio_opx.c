//*****************************************************************************
//
// opus_playaudio.c - Main routine for the OPUS Decode and playback example.
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

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "opus.h"
#include "debug.h"
#include "opus_types.h"
#include "opus_private.h"
#include "opus_multistream.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/udma.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/listbox.h"
#include "grlib/pushbutton.h"
#include "utils/ustdlib.h"
#include "third_party/fatfs/src/ff.h"
#include "third_party/fatfs/src/diskio.h"
#include "opxcode/opxfile.h"
#include "drivers/kentec320x240x16_ssd2119.h"
#include "drivers/frame.h"
#include "opxcode/pinout.h"
#include "drivers/touch.h"
#include "tm4c_opus.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Audio example application to playback a file compressed with OPUS Audio
//! codec (opus_playaudio)</h1>
//!
//! This example application demonstrates playing .opx files from an SD card
//! that is formatted with a FAT file system using the on board speaker. The
//! application can browse the file system on the SD card and displays
//! all files that are found.  Files can be selected to show their format and
//! then played if the application determines that they are a valid .opx file.
//! Only mono channel format files may be played.
//!
//! For additional details about FatFs, see the following site:
//! http://elm-chan.org/fsw/ff/00index_e.html
//!
//! For additional details about OPUS, see the following site:
//! https://opus-codec.org/
//!
//
//*****************************************************************************

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

//****************************************************************************
//
// Opus Decoder Structure
//
//****************************************************************************
OpusDecoder *sOpusDec;

//*****************************************************************************
//
// Graphics context used to show text on the display.
//
//*****************************************************************************
tContext g_sContext;

//*****************************************************************************
//
// Global needed by the FAT driver and playback routine to know the processor
// speed of the system.
//
//*****************************************************************************
uint32_t g_ui32SysClock;

//*****************************************************************************
//
// Defines for the basic screen area used by the application.
//
//*****************************************************************************
#define STATUS_HEIGHT           40
#define BG_MIN_X                7
#define BG_MAX_X                (320 - 8)
#define BG_MIN_Y                24
#define BG_MAX_Y                (240 - 8)
#define BUTTON_HEIGHT           (STATUS_HEIGHT - 8)

//*****************************************************************************
//
// Forward declarations for functions called by the widgets used in the user
// interface.
//
//*****************************************************************************
void OnListBoxChange(tWidget *psWidget, int16_t i16Selected);
static void PlayPause(tWidget *psWidget);
static void Stop(tWidget *psWidget);

//*****************************************************************************
//
// The following are data structures used by FatFs.
//
//*****************************************************************************
static FATFS g_sFatFs;
static DIR g_sDirObject;
static FILINFO g_sFileInfo;

//*****************************************************************************
//
// Define a pair of buffers that are used for holding path information.
// The buffer size must be large enough to hold the longest expected
// full path name, including the file name, and a trailing null character.
// The initial path is set to root "/".
//
//*****************************************************************************
#define PATH_BUF_SIZE   80
static char g_pcCwdBuf[PATH_BUF_SIZE] = "/";
static char g_pcTmpBuf[PATH_BUF_SIZE];

//*****************************************************************************
//
// The number of SysTick ticks per second.
//
//*****************************************************************************
#define TICKS_PER_SECOND 100
#define MS_PER_SYSTICK (1000 / TICKS_PER_SECOND)

//*****************************************************************************
//
// The global playback state for the application.
//
//*****************************************************************************
volatile enum
{
    AUDIO_PLAYING,
    AUDIO_PAUSED,
    AUDIO_STOPPED,
    AUDIO_NONE
}
g_ePlayState;

//*****************************************************************************
//
// These are the global .opx file states used by the application.
//
//*****************************************************************************
tOpxFile g_sOpxFile;
tOpxHeader g_sOpxHeader;

//*****************************************************************************
//
// Widget definitions
//
//*****************************************************************************

//*****************************************************************************
//
// Storage for the filename listbox widget string table.
//
//*****************************************************************************
#define NUM_LIST_STRINGS 48
const char *g_ppcDirListStrings[NUM_LIST_STRINGS];

//*****************************************************************************
//
// Storage for the names of the files in the current directory.  Filenames
// are stored in format "(D) filename.ext" for directories or "(F) filename.ext"
// for files.
//
//*****************************************************************************
#define MAX_FILENAME_STRING_LEN (4 + 8 + 1 + 3 + 1)
char g_pcFilenames[NUM_LIST_STRINGS][MAX_FILENAME_STRING_LEN];

//*****************************************************************************
//
// The canvas widgets for the opx file information.
//
//*****************************************************************************
extern tCanvasWidget g_sOpxInfoBackground;

char g_pcTime[16] = "";
Canvas(g_sOpxInfoTime, &g_sOpxInfoBackground, 0, 0,
       &g_sKentec320x240x16_SSD2119, BG_MAX_X - 166, BG_MIN_Y + 28, 158, 10,
       CANVAS_STYLE_FILL | CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_RIGHT |
       CANVAS_STYLE_TEXT_OPAQUE, ClrBlack, ClrWhite, ClrWhite,
       g_psFontFixed6x8, g_pcTime, 0, 0);

char g_pcFormat[24] = "";
Canvas(g_sOpxInfoSample, &g_sOpxInfoBackground, &g_sOpxInfoTime, 0,
       &g_sKentec320x240x16_SSD2119, BG_MAX_X - 166, BG_MIN_Y + 18, 158, 10,
       CANVAS_STYLE_FILL | CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_RIGHT |
       CANVAS_STYLE_TEXT_OPAQUE, ClrBlack, ClrWhite, ClrWhite,
       g_psFontFixed6x8, g_pcFormat, 0, 0);

Canvas(g_sOpxInfoFileName, &g_sOpxInfoBackground, &g_sOpxInfoSample, 0,
       &g_sKentec320x240x16_SSD2119, BG_MAX_X - 166, BG_MIN_Y + 8, 158, 10,
       CANVAS_STYLE_FILL | CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_RIGHT |
       CANVAS_STYLE_TEXT_OPAQUE, ClrBlack, ClrWhite, ClrWhite,
       g_psFontFixed6x8, "", 0, 0);

//*****************************************************************************
//
// The canvas widget acting as the background for the opx file information.
//
//*****************************************************************************
Canvas(g_sOpxInfoBackground, WIDGET_ROOT, 0,
       &g_sOpxInfoFileName, &g_sKentec320x240x16_SSD2119,
       BG_MAX_X - 170, BG_MIN_Y + 4, 166, 80,
       CANVAS_STYLE_FILL, ClrBlack, ClrWhite, ClrWhite,
       g_psFontFixed6x8, 0, 0, 0);

extern tCanvasWidget g_sStatusPanel;

//
// Status text area.
//
Canvas(g_sStatusText, &g_sStatusPanel, 0, 0, &g_sKentec320x240x16_SSD2119,
       BG_MIN_X + 112, BG_MAX_Y - STATUS_HEIGHT + 4, 189, BUTTON_HEIGHT,
       CANVAS_STYLE_FILL | CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_RIGHT |
       CANVAS_STYLE_TEXT_OPAQUE, ClrLightGrey, ClrDarkGray, ClrBlack,
       g_psFontCmss16, " ", 0, 0);

//
// Stop button.
//
RectangularButton(g_sStop, &g_sStatusPanel, &g_sStatusText, 0,
       &g_sKentec320x240x16_SSD2119, BG_MIN_X + 58,
       BG_MAX_Y - STATUS_HEIGHT + 4, 50, BUTTON_HEIGHT,
       PB_STYLE_FILL | PB_STYLE_TEXT |
       PB_STYLE_RELEASE_NOTIFY, ClrLightGrey, ClrDarkGray, 0,
       ClrBlack, g_psFontCmss16, "Stop", 0, 0, 0 ,0 , Stop);

//
// Play/Pause button.
//
RectangularButton(g_sPlayPause, &g_sStatusPanel, &g_sStop, 0,
       &g_sKentec320x240x16_SSD2119, BG_MIN_X + 4,
       BG_MAX_Y - STATUS_HEIGHT + 4, 50, BUTTON_HEIGHT,
       PB_STYLE_FILL | PB_STYLE_TEXT |
       PB_STYLE_RELEASE_NOTIFY, ClrLightGrey, ClrDarkGray, 0,
       ClrBlack, g_psFontCmss16, "Play", 0, 0, 0 ,0 , PlayPause);

//
// Background of the status area behind the buttons.
//
Canvas(g_sStatusPanel, WIDGET_ROOT, 0, &g_sPlayPause,
       &g_sKentec320x240x16_SSD2119, BG_MIN_X, BG_MAX_Y - STATUS_HEIGHT,
       BG_MAX_X - BG_MIN_X, STATUS_HEIGHT,
       CANVAS_STYLE_FILL | CANVAS_STYLE_TEXT_RIGHT |
       CANVAS_STYLE_TEXT_TOP, ClrGray, ClrWhite, ClrBlack, 0,
       0, 0, 0);

//
// The file list box.
//
ListBox(g_sDirList, WIDGET_ROOT, 0, 0,
        &g_sKentec320x240x16_SSD2119,
        BG_MIN_X + 4, BG_MIN_Y + 4, 120,
        BG_MAX_Y - BG_MIN_Y - STATUS_HEIGHT - 8,
        LISTBOX_STYLE_OUTLINE, ClrBlack, ClrDarkBlue, ClrSilver, ClrWhite,
        ClrWhite, g_psFontCmss12, g_ppcDirListStrings,
        NUM_LIST_STRINGS, 0, OnListBoxChange);

//*****************************************************************************
//
// State information for keep track of time.
//
//*****************************************************************************
static uint32_t g_ui32BytesPlayed;
static uint32_t g_ui32NextUpdate;

//*****************************************************************************
//
// Globals used to track play back position.
//
//*****************************************************************************
static uint16_t g_ui16Minutes;
static uint16_t g_ui16Seconds;

//*****************************************************************************
//
// Static constant strings used by the application.
//
//*****************************************************************************
static const char g_pcPlay[] = "Play";
static const char g_pcPause[] = "Pause";
static const char g_pcDirError[] ="Directory Read Error ";

//*****************************************************************************
//
// Variable to indicate Ping or Pong Buffer availability
//
//*****************************************************************************
opus_int16 *g_pcop16PingBuf;
opus_int16 *g_pcop16PongBuf;
int32_t  i32PingOutSamples;
int32_t  i32PongOutSamples;
uint8_t  g_ui8ScaleFactor;
uint32_t g_ui32SizeOfOutBuf;
volatile bool g_bRdPingBufferAvailable;
volatile bool g_bRdPongBufferAvailable;
volatile bool g_bPrime;

//*****************************************************************************
//
// The control table used by the uDMA controller.  This table must be aligned
// to a 1024 byte boundary.
//
//*****************************************************************************
#if defined(ewarm)
#pragma data_alignment=1024
uint8_t pui8ControlTable[1024];
#elif defined(ccs)
#pragma DATA_ALIGN(pui8ControlTable, 1024)
uint8_t pui8ControlTable[1024];
#else
uint8_t pui8ControlTable[1024] __attribute__ ((aligned(1024)));
#endif

//*****************************************************************************
//
// This is the interrupt handler from the timer when the DMA has completed the
// transfer of data for Primary or Alternate channel.
//
//*****************************************************************************
void
AudioTimerIntHandler(void)
{
    uint32_t ui32Mode;

    //
    // Clear the Match Interrupt
    //
    TimerIntClear(TIMER_BASE, TIMER_TIMA_DMA);

    //
    // Check if Ping or Pong Buffer is completed
    //
    ui32Mode = uDMAChannelModeGet(UDMA_CH8_TIMER5A | UDMA_PRI_SELECT);

    if(ui32Mode == UDMA_MODE_STOP)
    {
        g_bRdPingBufferAvailable = false;
    }

    //
    // Check if Ping or Pong Buffer is completed
    //
    ui32Mode = uDMAChannelModeGet(UDMA_CH8_TIMER5A | UDMA_ALT_SELECT);

    if(ui32Mode == UDMA_MODE_STOP)
    {
        g_bRdPongBufferAvailable = false;
    }

}

//*****************************************************************************
//
// Initialize the Audio Interface.
//
//*****************************************************************************
int32_t
InitAudio(void)
{
    int32_t  i32error;

    //
    // Initialize the priming variable to true
    //
    g_bPrime = true;
    g_ui32BytesPlayed = 0;

    //
    // Create the decoder
    //
    sOpusDec = opus_decoder_create(g_sOpxHeader.ui32SampleRate,
            g_sOpxHeader.ui16NumChannels,
            &i32error);

    //
    // If there was some problem creating the OPUS decoder, then close the write
    // and read file handle and return an error
    //
    if (i32error != OPUS_OK)
    {
       return((int)i32error);
    }

    opus_decoder_ctl(sOpusDec,
            OPUS_SET_LSB_DEPTH(g_sOpxHeader.ui16BitsPerSample));

    //
    // Set the scaling factor.
    //
    g_ui8ScaleFactor   = OPUS_PLAYBACK_RATE/g_sOpxHeader.ui32SampleRate;

    //
    // Get the Size of the Output Buffer and allocate the Ping and Pong Buffer
    //
    g_ui32SizeOfOutBuf = (g_sOpxHeader.ui32SampleRate *
            g_sOpxHeader.ui16NumChannels*OPUS_FRAME_SIZE_IN_MS *
            OPUS_DATA_SCALER)/1000;

#if 0
    //
    // Disable, Reset and Enable the Timer for Audio playback
    //
    SysCtlPeripheralDisable(SYSCTL_PERIPH_TIMER5);
    SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);

    //
    // Wait for the Timer to be ready for access
    //
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER5)));
#endif

    //
    // Configure the timer for playback
    //
    TimerConfigure(TIMER_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM |
            TIMER_CFG_B_PERIODIC);
    TimerControlLevel(TIMER_BASE, TIMER_A, true);
    TimerLoadSet(TIMER_BASE, TIMER_A,
            ((g_ui32SysClock/OPUS_PLAYBACK_RATE)-1));
    TimerMatchSet(TIMER_BASE, TIMER_A,
            ((g_ui32SysClock/(OPUS_PLAYBACK_RATE*2))-1));
    TimerUpdateMode(TIMER_BASE, TIMER_A, TIMER_UP_MATCH_TIMEOUT);
    TimerDMAEventSet(TIMER_BASE, TIMER_DMA_CAPEVENT_A);
    TimerIntEnable(TIMER_BASE, TIMER_TIMA_DMA);
    IntEnable(INT_TIMER5A);

    //
    // Enable the uDMA controller at the system level.  Enable it to continue
    // to run while the processor is in sleep.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);

    //
    // Enable the uDMA controller error interrupt.  This interrupt will occur
    // if there is a bus error during a transfer.
    //
    IntEnable(INT_UDMAERR);

    //
    // Enable the uDMA controller.
    //
    uDMAEnable();

    //
    // Point at the control table to use for channel control structures.
    //
    uDMAControlBaseSet(pui8ControlTable);

    uDMAChannelAssign(UDMA_CH8_TIMER5A);

    //
    // Put the attributes in a known state for the uDMA Timer5A channel. These
    // should already be disabled by default.
    //
    uDMAChannelAttributeDisable(UDMA_CH8_TIMER5A,
                                UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                UDMA_ATTR_REQMASK | UDMA_ATTR_HIGH_PRIORITY);

    //
    // Configure the control parameters for the primary control structure of
    // channel for Timer5A
    //
    uDMAChannelControlSet(UDMA_CH8_TIMER5A | UDMA_PRI_SELECT,
                          UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE |
                          UDMA_ARB_1);

    //
    // Configure the control parameters for the alternate control structure of
    // channel for Timer5A
    //
    uDMAChannelControlSet(UDMA_CH8_TIMER5A | UDMA_ALT_SELECT,
                          UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE |
                          UDMA_ARB_1);

    //
    // Put the attributes in a known state for the uDMA Timer5A channel. These
    // should already be disabled by default.
    //
    uDMAChannelAttributeEnable(UDMA_CH8_TIMER5A,
                                UDMA_ATTR_ALTSELECT |
                                UDMA_ATTR_HIGH_PRIORITY);

    //
    // If all initialization is OK then return 0
    //
    return(0);
}

//*****************************************************************************
//
// Start the Audio Capture Interface.
//
//*****************************************************************************
void
StartAudio(void)
{
    //
    // Enable the Timer
    //
    TimerEnable(TIMER_BASE, TIMER_BOTH);

    //
    // Set the speaker enable active
    //
    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, GPIO_PIN_4);

}

//*****************************************************************************
//
// Stop the Audio Capture Interface.
//
//*****************************************************************************
void
StopAudio(void)
{
    //
    // Disable the Timer
    //
    TimerDisable(TIMER_BASE, TIMER_A);

    //
    // Clear the speaker enable inactive
    //
    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, 0);

    //
    // Set all flags to false condition
    //
    g_bRdPongBufferAvailable = false;
    g_bRdPongBufferAvailable = false;
    g_bPrime = false;

    //
    // Free the ping and pong buffers, close the decoder and file handle
    //
    free(g_pcop16PingBuf);
    free(g_pcop16PongBuf);
    opus_decoder_destroy(sOpusDec);
    OpxClose(&g_sOpxFile);

}

//*****************************************************************************
//
// This function is used to tell when to update the play back times for a file.
// It will only update the screen at 1 second intervals but can be called more
// often with no result.
//
//*****************************************************************************
static void
DisplayTime(uint32_t ui32ForceUpdate)
{
    uint32_t ui32Seconds;
    uint32_t ui32Minutes;

    //
    // Only display on the screen once per second.
    //
    if((g_ui32BytesPlayed >= g_ui32NextUpdate) || (ui32ForceUpdate != 0))
    {
        //
        // Set the next update time to one second later.
        //
        g_ui32NextUpdate = g_ui32BytesPlayed + g_sOpxHeader.ui32AvgByteRate;

        //
        // Calculate the integer number of minutes and seconds.
        //
        ui32Seconds = g_ui32BytesPlayed / g_sOpxHeader.ui32AvgByteRate;
        ui32Minutes = ui32Seconds / 60;
        ui32Seconds -= ui32Minutes * 60;

        //
        // Print the time string in the format mm.ss/mm.ss
        //
        usprintf(g_pcTime, "%2d:%02d/%d:%02d\0", ui32Minutes,ui32Seconds,
                 g_ui16Minutes, g_ui16Seconds);

        //
        // Display the updated time on the screen.
        //
        WidgetPaint((tWidget *)&g_sOpxInfoTime);
    }
}

//*****************************************************************************
//
// This function will handle stopping the play back of audio.  It will not do
// this immediately but will defer stopping audio at a later time.  This allows
// this function to be called from an interrupt handler.
//
//*****************************************************************************
static void
OpxStop(void)
{
    //
    // Stop playing audio.
    //
    g_ePlayState = AUDIO_STOPPED;

    //
    // Stop the Audio channel
    //
    StopAudio();

    //
    // Update the display to show time
    //
    DisplayTime(1);

    //
    // Update the time variables
    //
    g_ui32BytesPlayed = 0;
    g_ui32NextUpdate  = 0;

    //
    // Change the play/pause button to say play.
    //
    PushButtonTextSet(&g_sPlayPause, g_pcPlay);
    CanvasTextSet(&g_sStatusText, " ");
    WidgetPaint(WIDGET_ROOT);
}

//*****************************************************************************
//
// This function is used to change to a new directory in the file system.
// It takes a parameter that specifies the directory to make the current
// working directory.
// Path separators must use a forward slash "/".  The directory parameter
// can be one of the following:
// * root ("/")
// * a fully specified path ("/my/path/to/mydir")
// * a single directory name that is in the current directory ("mydir")
// * parent directory ("..")
//
// It does not understand relative paths, so dont try something like this:
// ("../my/new/path")
//
// Once the new directory is specified, it attempts to open the directory
// to make sure it exists.  If the new path is opened successfully, then
// the current working directory (cwd) is changed to the new path.
//
// In cases of error, the pui32Reason parameter will be written with one of
// the following values:
//
//  NAME_TOO_LONG_ERROR - combination of paths are too long for the buffer
//  OPENDIR_ERROR - there is some problem opening the new directory
//
//*****************************************************************************
static FRESULT
ChangeToDirectory(char *pcDirectory)
{
    uint32_t ui32Idx;
    FRESULT fresult;

    //
    // Copy the current working path into a temporary buffer so
    // it can be manipulated.
    //
    strcpy(g_pcTmpBuf, g_pcCwdBuf);

    //
    // If the first character is /, then this is a fully specified
    // path, and it should just be used as-is.
    //
    if(pcDirectory[0] == '/')
    {
        //
        // Make sure the new path is not bigger than the cwd buffer.
        //
        if(strlen(pcDirectory) + 1 > sizeof(g_pcCwdBuf))
        {
            return(FR_OK);
        }

        //
        // If the new path name (in argv[1])  is not too long, then
        // copy it into the temporary buffer so it can be checked.
        //
        else
        {
            strncpy(g_pcTmpBuf, pcDirectory, sizeof(g_pcTmpBuf));
        }
    }

    //
    // If the argument is .. then attempt to remove the lowest level
    // on the CWD.
    //
    else if(!strcmp(pcDirectory, ".."))
    {
        //
        // Get the index to the last character in the current path.
        //
        ui32Idx = strlen(g_pcTmpBuf) - 1;

        //
        // Back up from the end of the path name until a separator (/)
        // is found, or until we bump up to the start of the path.
        //
        while((g_pcTmpBuf[ui32Idx] != '/') && (ui32Idx > 1))
        {
            //
            // Back up one character.
            //
            ui32Idx--;
        }

        //
        // Now we are either at the lowest level separator in the
        // current path, or at the beginning of the string (root).
        // So set the new end of string here, effectively removing
        // that last part of the path.
        //
        g_pcTmpBuf[ui32Idx] = 0;
    }

    //
    // Otherwise this is just a normal path name from the current
    // directory, and it needs to be appended to the current path.
    //
    else
    {
        //
        // Test to make sure that when the new additional path is
        // added on to the current path, there is room in the buffer
        // for the full new path.  It needs to include a new separator,
        // and a trailing null character.
        //
        if(strlen(g_pcTmpBuf) + strlen(pcDirectory) + 2 > sizeof(g_pcCwdBuf))
        {
            return(FR_INVALID_OBJECT);
        }

        //
        // The new path is okay, so add the separator and then append
        // the new directory to the path.
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
            strcat(g_pcTmpBuf, pcDirectory);
        }
    }

    //
    // At this point, a candidate new directory path is in g_pcTmpBuf.
    // Try to open it to make sure it is valid.
    //
    fresult = f_opendir(&g_sDirObject, g_pcTmpBuf);

    //
    // This was a valid path, so copy it into the CWD.
    //
    if(fresult == FR_OK)
    {
        strncpy(g_pcCwdBuf, g_pcTmpBuf, sizeof(g_pcCwdBuf));
    }

    //
    // Return success.
    //
    return(fresult);
}

//*****************************************************************************
//
// Fill the audio buffer with data from the opx file and run the OPUS decoder
// to decompress the data.
//
//*****************************************************************************
static uint32_t
FillAudioBuffer(void)
{
    uint8_t  *pcRdBuf;
    int32_t  i32len;
    uint8_t  ui8ScaleFactorLoop;
    uint32_t ui32Loop;
    uint16_t ui16Ret = 1;

    //
    // Allocate the buffer to read from sd card and ping-pong buffer for the
    // uDMA channels. Also this is performed only once for the audio stream.
    //
    if(g_bPrime)
    {
        g_pcop16PingBuf  = (int16_t*)calloc((((g_ui32SizeOfOutBuf *
                g_ui8ScaleFactor)/OPUS_DATA_SCALER)+1),sizeof(int16_t));
        g_pcop16PongBuf  = (int16_t*)calloc((((g_ui32SizeOfOutBuf *
                g_ui8ScaleFactor)/OPUS_DATA_SCALER)+1),sizeof(int16_t));
        g_bPrime = false;
    }

    pcRdBuf          = (uint8_t *)calloc(OPUS_MAX_PACKET,sizeof(uint8_t));

    //
    // Check if Ping Buffer has to be filled with the decompressed audio
    //
    if(g_bRdPingBufferAvailable == false)
    {
        //
        // Read the opx data stream one segment at a time
        //
        ui16Ret = OpxRead(&g_sOpxFile, (uint8_t *)pcRdBuf, &i32len);

        //
        // If there is an error then close the stream
        //
        if(ui16Ret == 0)
        {
            free(g_pcop16PingBuf);
            free(g_pcop16PongBuf);
            free(pcRdBuf);
            opus_decoder_destroy(sOpusDec);
            return(0);
        }

        //
        // Decompress the opx stream into raw PCM data for the ping buffer
        //
        i32PingOutSamples = opus_decode(sOpusDec,
                (const unsigned char *)&pcRdBuf[0],
                i32len,
                g_pcop16PingBuf,
                (g_ui32SizeOfOutBuf/OPUS_DATA_SCALER),
                0);

        //
        // Process the data for playback rate of 48KHz. 8-bit data is extracted
        // and converted to signed format. For slower original sample rate, the
        // buffer is extended by copying the same sample by a factor or 48KHz
        // divided by the original sample rate
        //
        if(g_sOpxHeader.ui16BitsPerSample == 8)
        {
            if(g_ui8ScaleFactor == 1)
            {
                for(ui32Loop = 0 ; ui32Loop < i32PingOutSamples ; ui32Loop++)
                {
                    g_pcop16PingBuf[ui32Loop] &= 0xFF;
                    g_pcop16PingBuf[ui32Loop] ^= 0x80;
                    g_pcop16PingBuf[ui32Loop] =
                            (g_pcop16PingBuf[ui32Loop] << 2);
                }
            }
            else
            {
                for(ui32Loop = (i32PingOutSamples) ; ui32Loop > 0 ; ui32Loop--)
                {
                    g_pcop16PingBuf[(ui32Loop-1)] &= 0xFF;
                    g_pcop16PingBuf[(ui32Loop-1)] ^= 0x80;
                    g_pcop16PingBuf[(ui32Loop-1)] =
                            (g_pcop16PingBuf[(ui32Loop-1)] << 2);
                    for(ui8ScaleFactorLoop = 0 ; ui8ScaleFactorLoop < g_ui8ScaleFactor ; ui8ScaleFactorLoop++)
                    {
                        g_pcop16PingBuf[((ui32Loop-1)*g_ui8ScaleFactor)+ui8ScaleFactorLoop]   = g_pcop16PingBuf[(ui32Loop-1)];
                    }
                }
            }
        }
        //
        // Process the data for playback rate of 48KHz. 16-bit data is
        // converted to signed format and upper 5 bits masked. For slower
        // original sample rate, the buffer is extended by copying the same
        // sample by a factor or 48KHz divided by the original sample rate
        //
        else
        {
            if(g_ui8ScaleFactor == 1)
            {
                for(ui32Loop = 0 ; ui32Loop < i32PingOutSamples ; ui32Loop++)
                {
                    g_pcop16PingBuf[ui32Loop] ^= 0x8000;
                    g_pcop16PingBuf[ui32Loop] =
                            (g_pcop16PingBuf[ui32Loop] >> 5);
                    g_pcop16PingBuf[ui32Loop] &= 0x7FF;
                }
            }
            else
            {
                for(ui32Loop = (i32PingOutSamples) ; ui32Loop > 0 ; ui32Loop--)
                {
                    g_pcop16PingBuf[ui32Loop-1] ^= 0x8000;
                    g_pcop16PingBuf[ui32Loop-1] =
                            (g_pcop16PingBuf[ui32Loop-1] >> 5);
                    g_pcop16PingBuf[ui32Loop-1] &= 0x7FF;
                    for(ui8ScaleFactorLoop = 0 ;
                            ui8ScaleFactorLoop < g_ui8ScaleFactor ;
                            ui8ScaleFactorLoop++)
                    {
                        g_pcop16PingBuf[((ui32Loop-1)*g_ui8ScaleFactor)+ui8ScaleFactorLoop] =
                                g_pcop16PingBuf[(ui32Loop-1)];
                    }
                }
            }
        }

        //
        // Initialize the uDMA primary control structure with the source and
        // destination locations and size of the tarnsfer and then enable the
        // channel
        //
        uDMAChannelTransferSet(UDMA_CH8_TIMER5A | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)&g_pcop16PingBuf[0],
                               (void *)(TIMER_BASE + TIMER_O_TAMATCHR),
                               i32PingOutSamples*g_ui8ScaleFactor);
        uDMAChannelEnable(UDMA_CH8_TIMER5A);

        //
        // Set the ping buffer ready flag.
        //
        g_bRdPingBufferAvailable = true;

        //
        // Add the number of bytes to played back for time display
        //
        g_ui32BytesPlayed += i32PingOutSamples;

    }

    if(g_bRdPongBufferAvailable == false)
    {
        //
        // Read the opx data stream one segment at a time
        //
        ui16Ret = OpxRead(&g_sOpxFile, (uint8_t *)pcRdBuf, &i32len);

        //
        // If there is an error then close the stream
        //
        if(ui16Ret == 0)
        {
            free(g_pcop16PingBuf);
            free(g_pcop16PongBuf);
            free(pcRdBuf);
            opus_decoder_destroy(sOpusDec);
            return(0);
        }

        //
        // Decompress the opx stream into raw PCM data for the pong buffer
        //
        i32PongOutSamples = opus_decode(sOpusDec,
                (const unsigned char *)&pcRdBuf[0],
                i32len,
                g_pcop16PongBuf,
                (g_ui32SizeOfOutBuf/OPUS_DATA_SCALER),
                0);

        //
        // Process the data for playback rate of 48KHz. 8-bit data is extracted
        // and converted to signed format. For slower original sample rate, the
        // buffer is extended by copying the same sample by a factor or 48KHz
        // divided by the original sample rate
        //
        if(g_sOpxHeader.ui16BitsPerSample == 8)
        {
            if(g_ui8ScaleFactor == 1)
            {
                for(ui32Loop = 0 ; ui32Loop < i32PongOutSamples ; ui32Loop++)
                {
                    g_pcop16PongBuf[ui32Loop] &= 0xFF;
                    g_pcop16PongBuf[ui32Loop] ^= 0x80;
                    g_pcop16PongBuf[ui32Loop] =
                            (g_pcop16PongBuf[ui32Loop] << 2);
                }
            }
            else
            {
                for(ui32Loop = (i32PongOutSamples) ; ui32Loop > 0 ; ui32Loop--)
                {
                    g_pcop16PongBuf[(ui32Loop-1)] &= 0xFF;
                    g_pcop16PongBuf[(ui32Loop-1)] ^= 0x80;
                    g_pcop16PongBuf[(ui32Loop-1)] =
                            (g_pcop16PongBuf[(ui32Loop-1)] << 2);
                    for(ui8ScaleFactorLoop = 0 ;
                            ui8ScaleFactorLoop < g_ui8ScaleFactor ;
                            ui8ScaleFactorLoop++)
                    {
                        g_pcop16PongBuf[((ui32Loop-1)*g_ui8ScaleFactor)+ui8ScaleFactorLoop] =
                                g_pcop16PongBuf[(ui32Loop-1)];
                    }
                }
            }
        }
        //
        // Process the data for playback rate of 48KHz. 16-bit data is
        // converted to signed format and upper 5 bits masked. For slower
        // original sample rate, the buffer is extended by copying the same
        // sample by a factor or 48KHz divided by the original sample rate
        //
        else
        {
            if(g_ui8ScaleFactor == 1)
            {
                for(ui32Loop = 0 ; ui32Loop < i32PongOutSamples ; ui32Loop++)
                {
                    g_pcop16PongBuf[ui32Loop] ^= 0x8000;
                    g_pcop16PongBuf[ui32Loop] =
                            (g_pcop16PongBuf[ui32Loop] >> 5);
                    g_pcop16PongBuf[ui32Loop] &= 0x7FF;
                }
            }
            else
            {
                for(ui32Loop = (i32PongOutSamples) ; ui32Loop > 0 ; ui32Loop--)
                {
                    g_pcop16PongBuf[ui32Loop-1] ^= 0x8000;
                    g_pcop16PongBuf[ui32Loop-1] =
                            (g_pcop16PongBuf[ui32Loop-1] >> 5);
                    g_pcop16PongBuf[ui32Loop-1] &= 0x7FF;
                    for(ui8ScaleFactorLoop = 0 ;
                            ui8ScaleFactorLoop < g_ui8ScaleFactor ;
                            ui8ScaleFactorLoop++)
                    {
                        g_pcop16PongBuf[((ui32Loop-1)*g_ui8ScaleFactor)+ui8ScaleFactorLoop] =
                                g_pcop16PongBuf[(ui32Loop-1)];
                    }
                }
            }
        }

        //
        // Initialize the uDMA alternate control structure with the source and
        // destination locations and size of the tarnsfer and then enable the
        // channel
        //
        uDMAChannelTransferSet(UDMA_CH8_TIMER5A | UDMA_ALT_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)&g_pcop16PongBuf[0],
                               (void *)(TIMER_BASE + TIMER_O_TAMATCHR),
                               i32PongOutSamples*g_ui8ScaleFactor);
        uDMAChannelEnable(UDMA_CH8_TIMER5A);

        //
        // Set the pong buffer ready flag.
        //
        g_bRdPongBufferAvailable = true;

        //
        // Add the number of bytes to played back for time display
        //
        g_ui32BytesPlayed += i32PongOutSamples;
    }

    //
    // Free the sd card buffer
    //
    free(pcRdBuf);

    return(ui16Ret);
}

//*****************************************************************************
//
// This is the callback for the play/pause button.
//
//*****************************************************************************
static void
PlayPause(tWidget *psWidget)
{
    int16_t i16Select;

    //
    // If we are stopped, then start playing.
    //
    if((g_ePlayState == AUDIO_STOPPED) || (g_ePlayState == AUDIO_NONE))
    {
        //
        // Get the current selection from the list box.
        //
        i16Select = ListBoxSelectionGet(&g_sDirList);

        //
        // See if this is a valid .opx file that can be opened.
        //
        if(OpxOpen(g_pcFilenames[i16Select], &g_sOpxFile) == 0)
        {
            //
            // Initialize the OPUS Decoder
            //
            if(InitAudio() != 0)
            {
                OpxClose(&g_sOpxFile);
                return;
            }

            //
            // Fill the audio buffer from the file.
            //
            FillAudioBuffer();

            //
            // Start the Audio
            //
            StartAudio();

            //
            // Indicate that opx play back should start.
            //
            g_ePlayState = AUDIO_PLAYING;

            //
            // Change the button to indicate pause.
            //
            PushButtonTextSet(&g_sPlayPause, g_pcPause);
            CanvasTextSet(&g_sStatusText, "Now Playing...");
            WidgetPaint(WIDGET_ROOT);
        }
        else
        {
            //
            // Play was pressed on an invalid file.
            //
            CanvasTextSet(&g_sStatusText, "Invalid opx format");
            WidgetPaint(WIDGET_ROOT);

            return;
        }

        //
        // Fill the audio buffer from the file.
        //
        FillAudioBuffer();

    }
    else if(g_ePlayState == AUDIO_PLAYING)
    {
        //
        // Now switching to a paused state, so change the button to say play.
        //
        PushButtonTextSet(&g_sPlayPause, g_pcPlay);
        CanvasTextSet(&g_sStatusText, "Paused...");
        WidgetPaint(WIDGET_ROOT);

        g_ePlayState = AUDIO_PAUSED;
    }
    else if(g_ePlayState == AUDIO_PAUSED)
    {
        //
        // Fill the audio buffer from the file.
        //
        FillAudioBuffer();

        //
        // Now switching to a play state, so change the button to say paused.
        //
        PushButtonTextSet(&g_sPlayPause, g_pcPause);
        CanvasTextSet(&g_sStatusText, "Now Playing...");
        WidgetPaint(WIDGET_ROOT);

        g_ePlayState = AUDIO_PLAYING;
    }
}

//*****************************************************************************
//
// Stopped pressed so stop the opx playback.
//
//*****************************************************************************
static void
Stop(tWidget *psWidget)
{
    //
    // Stop play back if we are playing.
    //
    if((g_ePlayState == AUDIO_PLAYING) || (g_ePlayState == AUDIO_PAUSED))
    {
        //
        // Close the file, it will be re-opened on play.
        //
        OpxClose(&g_sOpxFile);

        OpxStop();

        CanvasTextSet(&g_sStatusText, " ");
        WidgetPaint(WIDGET_ROOT);
    }
}

//*****************************************************************************
//
// This function is called to read the contents of the current directory on
// the SD card and fill the listbox containing the names of all files and
// directories.
//
//*****************************************************************************
static int
PopulateFileListBox(bool bRepaint)
{
    uint32_t ui32ItemCount;
    FRESULT iFResult;

    //
    // Empty the list box on the display.
    //
    ListBoxClear(&g_sDirList);

    //
    // Make sure the list box will be redrawn next time the message queue
    // is processed.
    //
    if(bRepaint)
    {
        WidgetPaint((tWidget *)&g_sDirList);
    }

    //
    // Open the current directory for access.
    //
    iFResult = f_opendir(&g_sDirObject, g_pcCwdBuf);

    //
    // Check for error and return if there is a problem.
    //
    if(iFResult != FR_OK)
    {
        //
        // Change the text to reflect the change.
        //
        CanvasTextSet(&g_sStatusText, g_pcDirError);
        WidgetPaint((tWidget *)&g_sStatusText);
        return(iFResult);
    }

    //
    // If not at the root then add the ".." entry.
    //
    if(g_pcCwdBuf[1] != 0)
    {
        g_pcFilenames[0][0] = '.';
        g_pcFilenames[0][1] = '.';
        g_pcFilenames[0][2] = 0;
        ListBoxTextAdd(&g_sDirList, g_pcFilenames[0]);
        ui32ItemCount = 1;
    }
    else
    {
        ui32ItemCount = 0;
    }

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
            //
            // Change the text to reflect the change.
            //
            CanvasTextSet(&g_sStatusText, g_pcDirError);
            WidgetPaint((tWidget *)&g_sStatusText);
            return(iFResult);
        }

        //
        // If the file name is blank, then this is the end of the
        // listing.
        //
        if(!g_sFileInfo.fname[0])
        {
            break;
        }

        //
        // Add the information as a line in the listbox widget.
        //
        if(ui32ItemCount < NUM_LIST_STRINGS)
        {
            if(g_sFileInfo.fattrib & AM_DIR)
            {
                usnprintf(g_pcFilenames[ui32ItemCount],
                          MAX_FILENAME_STRING_LEN, "+ %s", g_sFileInfo.fname);
            }
            else
            {
                ustrncpy(g_pcFilenames[ui32ItemCount], g_sFileInfo.fname,
                         MAX_FILENAME_STRING_LEN);
            }
            ListBoxTextAdd(&g_sDirList, g_pcFilenames[ui32ItemCount]);
        }

        //
        // Move to the next entry in the item array we use to populate the
        // list box.
        //
        ui32ItemCount++;
    }

    //
    // Made it to here, return with no errors.
    //
    return(0);
}

//*****************************************************************************
//
// The listbox widget callback function.
//
// This function is called whenever someone changes the selected entry in the
// listbox containing the files and directories found in the current directory.
//
//*****************************************************************************
void OnListBoxChange(tWidget *psWidget, int16_t i16Selected)
{
    int16_t i16Sel;

    //
    // Get the current selection from the list box.
    //
    i16Sel = ListBoxSelectionGet(&g_sDirList);

    //
    // Is there any selection?
    //
    if(i16Sel == -1)
    {
        return;
    }
    else
    {
        //
        // Is the selection a directory name.
        //
        if(g_pcFilenames[i16Sel][0] == '+')
        {
            if((g_ePlayState != AUDIO_PLAYING) &&
               (g_ePlayState != AUDIO_PAUSED))
            {
                CanvasTextSet(&g_sOpxInfoFileName, "");
                CanvasTextSet(&g_sOpxInfoSample, "");
                g_pcTime[0] = 0;
            }

            if(ChangeToDirectory(&g_pcFilenames[i16Sel][2]) == FR_OK)
            {
                PopulateFileListBox(true);
            }
        }
        else if((g_pcFilenames[i16Sel][0] == '.') &&
                (g_pcFilenames[i16Sel][1] == '.'))
        {
            //
            // If this was the .. selection then move up a directory.
            //
            if(ChangeToDirectory("..") == FR_OK)
            {
                PopulateFileListBox(true);
            }

            if((g_ePlayState != AUDIO_PLAYING) &&
               (g_ePlayState != AUDIO_PAUSED))
            {
                CanvasTextSet(&g_sOpxInfoFileName, "");
                CanvasTextSet(&g_sOpxInfoSample, "");
                g_pcTime[0] = 0;
            }
        }
        else
        {
            //
            // This was a normal file selections so see if it is a opx file.
            //
            CanvasTextSet(&g_sOpxInfoFileName, g_pcFilenames[i16Sel]);

            if((g_ePlayState == AUDIO_PLAYING) ||
               (g_ePlayState == AUDIO_PAUSED))
            {
                OpxStop();
            }

            if(OpxOpen(g_pcFilenames[i16Sel], &g_sOpxFile) == 0)
            {
                //
                // Read the .opx file format.
                //
                OpxGetFormat(&g_sOpxFile, &g_sOpxHeader);

                //
                // Print the formatted string so that it can be
                // displayed.
                //
                usprintf(g_pcFormat, "%d Hz %d bit ",
                         g_sOpxHeader.ui32SampleRate,
                         g_sOpxHeader.ui16BitsPerSample);

                //
                // Concatenate the number of channels.
                //
                if(g_sOpxHeader.ui16NumChannels == 1)
                {
                    strcat(g_pcFormat, "Mono");
                }
                else
                {
                    strcat(g_pcFormat, "Stereo");
                }

                CanvasTextSet(&g_sOpxInfoSample, g_pcFormat);

                //
                // Calculate the minutes and seconds in the file.
                //
                g_ui16Seconds = g_sOpxHeader.ui32OrigFileSize /
                              g_sOpxHeader.ui32AvgByteRate;
                g_ui16Minutes = g_ui16Seconds / 60;
                g_ui16Seconds -= g_ui16Minutes * 60;

                //
                // Close the file, it will be re-opened on play.
                //
                OpxClose(&g_sOpxFile);

                //
                // Update the time variables
                //
                g_ui32BytesPlayed = 0;
                g_ui32NextUpdate  = 0;

                //
                // Update the file time information.
                //
                DisplayTime(1);
            }
            else
            {
                CanvasTextSet(&g_sOpxInfoSample, "");
                g_pcTime[0] = 0;
                WidgetPaint((tWidget *)&g_sOpxInfoTime);
            }
        }

        //
        // Update the file name and opx file information
        //
        WidgetPaint((tWidget *)&g_sOpxInfoFileName);
        WidgetPaint((tWidget *)&g_sOpxInfoSample);
        WidgetPaint((tWidget *)&g_sOpxInfoTime);
    }
}

//*****************************************************************************
//
// This is the handler for this SysTick interrupt.  FatFs requires a
// timer tick every 10ms for internal timing purposes.
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
// Initializes the file system module.
//
// \param None.
//
// This function initializes the third party FAT implementation.
//
// \return Returns \e true on success or \e false on failure.
//
//*****************************************************************************
static bool
FileInit(void)
{
    //
    // Mount the file system, using logical disk 0.
    //
    if(f_mount(0, &g_sFatFs) != FR_OK)
    {
        return(false);
    }
    return(true);
}

//*****************************************************************************
//
// The program main function.  It performs initialization, then handles opx
// file playback.
//
//*****************************************************************************
int
main(void)
{
    uint32_t ui32Retcode;

    //
    // Set the system clock to run at 120MHz from the PLL.
    //
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                            SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                            SYSCTL_CFG_VCO_480), 120000000);

    //
    // Configure the device pins.
    //
    PinoutSet();

    //
    // Configure SysTick for a 100Hz interrupt.
    //
    ROM_SysTickPeriodSet(g_ui32SysClock / TICKS_PER_SECOND);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();

    //
    // Enable Interrupts
    //
    ROM_IntMasterEnable();

    //
    // Initialize the display driver.
    //
    Kentec320x240x16_SSD2119Init(g_ui32SysClock);

    //
    // Initialize the graphics context.
    //
    GrContextInit(&g_sContext, &g_sKentec320x240x16_SSD2119);

    //
    // Draw the application frame.
    //
    FrameDraw(&g_sContext, "Opx Player Demo");

    //
    // Initialize the touch screen driver.
    //
    TouchScreenInit(g_ui32SysClock);

    //
    // Set the touch screen event handler.
    //
    TouchScreenCallbackSet(WidgetPointerMessage);

    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sDirList);
    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sStatusPanel);
    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sOpxInfoBackground);

    //
    // Issue the initial paint request to the widgets then immediately call
    // the widget manager to process the paint message.  This ensures that the
    // display is drawn as quickly as possible and saves the delay we would
    // otherwise experience if we processed the paint message after mounting
    // and reading the SD card.
    //
    WidgetPaint(WIDGET_ROOT);

    //
    // Determine whether or not an SD Card is installed.  If not, print a
    // warning and have the user install one and restart.
    //
    ui32Retcode = disk_initialize(0);

    if(ui32Retcode != RES_OK)
    {
        CanvasTextSet(&g_sStatusText,  "File system error! ");
        WidgetPaint((tWidget *)&g_sStatusText);

        //
        // Process any messages in the widget message queue.
        //
        WidgetMessageQueueProcess();
        
        while(1);
    }
    else
    {
        //
        // Mount the file system, using logical disk 0.
        //
        f_mount(0, &g_sFatFs);

        if(!FileInit())
        {
            CanvasTextSet(&g_sStatusText, "File system error! ");
            WidgetPaint((tWidget *)&g_sStatusText);
            
            //
            // Process any messages in the widget message queue.
            //
            WidgetMessageQueueProcess();

            while(1);
        }
    }

    //
    // Not playing anything right now so intiialize all variables.
    //
    g_bPrime = true;
    g_bRdPingBufferAvailable = false;
    g_bRdPongBufferAvailable = false;
    g_ePlayState = AUDIO_NONE;

    PopulateFileListBox(true);

    //
    // Enter an (almost) infinite loop for reading and processing commands from
    // the user.
    //
    while(1)
    {

        //
        // Handle the case when the opx file is playing.
        //
        if(g_ePlayState == AUDIO_PLAYING)
        {
            //
            // If this is not the last segment in the opx stream then continue
            //
            if(FillAudioBuffer() == 2)
            {
                //
                // No more data or error so stop playing.
                //
                OpxStop();

            }

            //
            // Update the real display time.
            //
            DisplayTime(0);
        }

        //
        // Process any messages in the widget message queue.
        //
        WidgetMessageQueueProcess();
    }
}
