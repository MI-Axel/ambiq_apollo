#ifndef AM_AEP_CONFIG_H
#define AM_AEP_CONFIG_H

// Hardware configuration
#define USE_VESPER_MIKRO_MB3                        0
#define USE_ST_MICS_MIKRO_MB3                       1

// Software module configuration

#define configUSE_PDM_DATA                          1

#define configUSE_LOCAL_DATA                        0

#define configUSE_SYSVIEWER                         1

#define configUSE_RTT_LOGGER                        0


// Parameters configuration

#if configUSE_PDM_DATA
    #define PCM_FRAME_SIZE                          320
    #define PCM_DATA_BYTES                          4
    #define PCM_PUSH_OVER                           4
#endif // configUSE_PDM_DATA


























#endif
