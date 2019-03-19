/****************************************************************************
 *
 *		DSP Concepts
 *      Quiescent Sound Detector
 *
 ****************************************************************************
 *
 *	Description:	Low power sound detector for embedded products
 *
 *	Copyright:		DSP Concepts, 2017, All rights reserverd
 *	Owner:			DSP Concepts
 *					3235 Kifer Road
 *					Santa Clara, CA 95051
 *
 ***************************************************************************/

/* 
 * Main instance structure for the DSPC QSD algorithm.  Define one of these
 * structures per instance of the algorithm running.
 *
 * The algorithm operates on blocks of data and supports any number of channels.
 * 
 * The configuration parameters (noiseFloorThreshold and snrThreshold) are in
 * dB relative to full scale of 0 dB.  noiseFloorThreshold specifies the minimum
 * signal level needed to declare activity.  snrThreshold specifies how many
 * dB above the background noise level does the input signal have to be for QSD
 * to declare that a signal is present. Typical values are:
 *  noiseFloorThreshold = -60.0f;
 *  snrThreshold = 6.0f;
 */

 typedef struct _DSPC_QSD
{
    // Configurable properties
    float noiseFloorThreshold; // Any signals above this level trigger detector.
    float snrThreshold;        // dB above background noise floor to trigger.
	float hpfCutoffFrequency;

    // Private parameters
    int privateData[18];
} DSPC_QSD;

/* 
 * Configuration function. You have to specify the input sample rate, block
 * size, and number of channels of data. Call this once at the start of your
 * application to initialize the internally derived variables.
 */

void dspc_qsd_config(DSPC_QSD *Q, float sampleRate, int blockSize);

/* 
 * Block based processing function.  The input is an array of interleaved
 * floating point data.  The data is interleaved channel wise and there are
 * a total of blockSize * numChannels samples.  The input data should be
 * normalized so that 1.0 represents a signal level of 0 dB.
 */

int dspc_qsd_process_float(DSPC_QSD *Q, float *data, int stride);

/*
* Another version of the above processing function but the data is now
* represented as 16-bit fractional values.  The values [0x8000 0x7FFF]
* are mapped to [-1.0 1.0) in this representation.
*/

int dspc_qsd_process_fract16(DSPC_QSD *Q, short *data, int stride);

/*
* Another version of the above processing function but the data is now
* represented as 32-bit fractional values.  The values [0x80000000 0x7FFFFFFF]
* are mapped to [-1.0 1.0) in this representation.
*/

int dspc_qsd_process_fract32(DSPC_QSD *Q, int *data, int stride);