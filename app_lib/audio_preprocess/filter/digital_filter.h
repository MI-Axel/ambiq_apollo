/******************************* SOURCE LICENSE *********************************
Copyright (c) 2019 MicroModeler.

A non-exclusive, nontransferable, perpetual, royalty-free license is granted to the Licensee to 
use the following Information for academic, non-profit, or government-sponsored research purposes.
Use of the following Information under this License is restricted to NON-COMMERCIAL PURPOSES ONLY.
Commercial use of the following Information requires a separately executed written license agreement.

This Information is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

******************************* END OF LICENSE *********************************/

// A commercial license for MicroModeler DSP can be obtained at http://www.micromodeler.com/launch.jsp

// Begin header file, high_pass_filter.h

#ifndef HIGH_PASS_FILTER_H_ // Include guards
#define HIGH_PASS_FILTER_H_

static const int high_pass_filter_numStages = 1;
static const int high_pass_filter_coefficientLength = 5;
extern float high_pass_filter_coefficients[5];

typedef struct
{
	float state[4];
	float output;
} high_pass_filterType;

typedef struct
{
	float *pInput;
	float *pOutput;
	float *pState;
	float *pCoefficients;
	short count;
} high_pass_filter_executionState;


high_pass_filterType *high_pass_filter_create( void );
void high_pass_filter_destroy( high_pass_filterType *pObject );
void high_pass_filter_init( high_pass_filterType * pThis );
void high_pass_filter_reset( high_pass_filterType * pThis );
#define high_pass_filter_writeInput( pThis, input )  \
	high_pass_filter_filterBlock( pThis, &(input), &(pThis)->output, 1 );

#define high_pass_filter_readOutput( pThis )  \
	(pThis)->output

int high_pass_filter_filterBlock( high_pass_filterType * pThis, float * pInput, float * pOutput, unsigned int count );
#define high_pass_filter_outputToFloat( output )  \
	(output)

#define high_pass_filter_inputFromFloat( input )  \
	(input)

void high_pass_filter_filterBiquad( high_pass_filter_executionState * pExecState );
#endif // HIGH_PASS_FILTER_H_
	

