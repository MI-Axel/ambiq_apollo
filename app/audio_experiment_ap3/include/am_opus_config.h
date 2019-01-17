
#ifndef AM_OPUS_CONFIG_H_
#define AM_OPUS_CONFIG_H_

//*****************************************************************************
//
// Defines the OPUS parameters
//
//*****************************************************************************
#define VAR_ARRAYS              1
#define FIXED_POINT             1
#define OPUS_BUILD              1

#define OPUS_DATA_SCALER      2
#define OPUS_BITRATE_SCALER   2
#define OPUS_FRAME_SIZE_IN_MS 20
#define OPUS_MAX_PACKET       1024


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

#endif /* AM_OPUS_CONFIG_H_ */


