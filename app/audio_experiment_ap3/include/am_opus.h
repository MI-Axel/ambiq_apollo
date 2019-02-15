
#ifndef AM_OPUS_H_
#define AM_OPUS_H_

#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"

#include "am_audio_platform_config.h"
#include "board_setup.h"
#include "audio_driver.h"


/* opus lib include file */
#include "opus.h"


//*****************************************************************************
//
// Defines the OPUS parameters
//
//*****************************************************************************
#define OPUS_DATA_SCALER        2
#define OPUS_BITRATE_SCALER     2
#define OPUS_FRAME_SIZE_IN_MS   20
#define OPUS_MAX_PACKET         1024


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

extern const uint8_t mono_16b_USP1602[80000];
extern OpusEncoder *g_opusEnc;
extern int g_opusErr;
extern uint32_t g_audioSampleRate;
extern int32_t g_audioChannel;
extern opus_int32 g_opusComplexity;
extern opus_int32 g_opusEncRet;
extern opus_int32 g_opusBitRate_bps;
extern opus_int32 g_opusBandWidth;
extern opus_int32 g_opusUseVbr;
extern opus_int32 g_opusVariableDuration;


extern opus_int32 g_opusEncRet;
extern uint8_t g_opusOutputBuff[OPUS_MAX_PACKET];

extern void am_opus_encoder_init(OpusEncoder* opusEnc);

#endif /* AM_OPUS_H_ */


