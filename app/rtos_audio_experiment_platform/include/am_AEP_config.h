#ifndef AM_AEP_CONFIG_H
#define AM_AEP_CONFIG_H

// Hardware configuration
#define USE_VESPER_MIKRO_MB3                        0
#define USE_ST_MICS_MIKRO_MB3                       1

// Software module configuration

#define configUSE_PDM_DATA                          1

#define configUSE_LOCAL_DATA                        0

#define configUSE_AUDIO_CODEC                       1

// SYSVIEWER and RTT could only choose one item
#define configUSE_SYSVIEWER                         0

#define configUSE_RTT_LOGGER                        1

// CPU runs at 96MHZ or 48MHZ
#define configUSE_BURST_ALWAYS_ON                   1


// Parameters configuration

#if configUSE_PDM_DATA
    #define PCM_FRAME_SIZE                          80
    #define PCM_DATA_BYTES                          4
    #define PCM_PUSH_OVER                           4
#endif // configUSE_PDM_DATA

#if configUSE_RTT_LOGGER 
    #define configUSE_RTT_PCM                       1
    #define RTT_BUFFER_LENGTH                       (128*1024)
#endif // configUSE_RTT_LOGGER
























#endif
