/****************************************************************************
 *
 *		Target Tuning Symbol File
 *		-------------------------
 *
 *          Generated on:  15-Nov-2018 10:16:41
 *
 ***************************************************************************/

#ifndef AM_2CM_FBF_SCNR_THF_NT_H
#define AM_2CM_FBF_SCNR_THF_NT_H

#include "Framework.h"

#include "ModAdder.h"
#include "ModBiquadCascade.h"
#include "ModButterworthFilter.h"
#include "ModComplexMultiplier.h"
#include "ModDCSourceInt.h"
#include "ModFft.h"
#include "ModFifoIn.h"
#include "ModFifoOut.h"
#include "ModIfft.h"
#include "ModNullSink.h"
#include "ModRepWinOverlap.h"
#include "ModRouter.h"
#include "ModSCNRv1.h"
#include "ModSensoryTHFCortexMCmds.h"
#include "ModSetWireProperties.h"
#include "ModSink.h"
#include "ModSource.h"
#include "ModToggleButton.h"
#include "ModTypeConversion.h"
#include "ModWindowAlias.h"

#define wire1_ID 1
#define wire2_ID 2
#define wire3_ID 3
#define wire4_ID 4
#define wire5_ID 5
#define wire6_ID 6
#define wire7_ID 7
#define wire8_ID 8
#define wire9_ID 9
#define wire10_ID 10
#define wire11_ID 11
#define wire12_ID 12
#define wire13_ID 13
#define wire14_ID 14
#define wire15_ID 15
#define wire16_ID 16
#define wire17_ID 17
#define wire18_ID 18
#define wire19_ID 19
#define wire20_ID 20
#define wire21_ID 21
#define wire22_ID 22
#define TypeConversion1_ID 23
#define Router1_ID 24
#define MicProcessing____WOLAAnalysis2____windowAlias_ID 25
#define MicProcessing____WOLAAnalysis2____fft_ID 26
#define MicProcessing____WOLAAnalysis2____wp_ID 27
#define DC1_ID 28
#define BufferUp1____fifoOut_ID 29
#define TypeConversion4_ID 30
#define SensoryTHFCortexMCmds1_ID 31
#define Sink2_ID 32
#define ToggleButton1_ID 33
#define TypeConversion2_ID 34
#define Sink1_ID 36
#define MicProcessing____beamformer____weight_ID 37
#define MicProcessing____beamformer____ComplexMul1_ID 38
#define MicProcessing____beamformer____Add1_ID 39
#define MicProcessing____SCNR1_ID 40
#define MicProcessing____WOLASynthesis1____wp_ID 41
#define MicProcessing____WOLASynthesis1____ifft_ID 42
#define MicProcessing____WOLASynthesis1____overlap_ID 43
#define ButterFilter1_ID 44
#define ButterFilter1_filt_ID 45
#define BufferUp1____fifoIn_ID 46
#define TypeConversion3_ID 47
#define Sink3_ID 30000
#define theLayout1_ID 48
#define theLayout3_ID 49

INT32 InitializeAWESymbols(void);

/* ----------------------------------------------------------------------
** Object variables declarations.
** ------------------------------------------------------------------- */

extern WireInstance *wire1;
extern WireInstance *wire2;
extern WireInstance *wire3;
extern WireInstance *wire4;
extern WireInstance *wire5;
extern WireInstance *wire6;
extern WireInstance *wire7;
extern WireInstance *wire8;
extern WireInstance *wire9;
extern WireInstance *wire10;
extern WireInstance *wire11;
extern WireInstance *wire12;
extern WireInstance *wire13;
extern WireInstance *wire14;
extern WireInstance *wire15;
extern WireInstance *wire16;
extern WireInstance *wire17;
extern WireInstance *wire18;
extern WireInstance *wire19;
extern WireInstance *wire20;
extern WireInstance *wire21;
extern WireInstance *wire22;
extern awe_modTypeConversionClass *TypeConversion1;
extern awe_modRouterClass *Router1;
extern awe_modWindowAliasClass *MicProcessing____WOLAAnalysis2____windowAlias;
extern awe_modFftClass *MicProcessing____WOLAAnalysis2____fft;
extern awe_modSetWirePropertiesClass *MicProcessing____WOLAAnalysis2____wp;
extern awe_modDCSourceIntClass *DC1;
extern awe_modFifoOutClass *BufferUp1____fifoOut;
extern awe_modTypeConversionClass *TypeConversion4;
extern awe_modSensoryTHFCortexMCmdsClass *SensoryTHFCortexMCmds1;
extern awe_modNullSinkClass *Sink2;
extern awe_modToggleButtonClass *ToggleButton1;
extern awe_modTypeConversionClass *TypeConversion2;
extern awe_modNullSinkClass *Sink1;
extern awe_modSourceClass *MicProcessing____beamformer____weight;
extern awe_modComplexMultiplierClass *MicProcessing____beamformer____ComplexMul1;
extern awe_modAdderClass *MicProcessing____beamformer____Add1;
extern awe_modSCNRv1Class *MicProcessing____SCNR1;
extern awe_modSetWirePropertiesClass *MicProcessing____WOLASynthesis1____wp;
extern awe_modIfftClass *MicProcessing____WOLASynthesis1____ifft;
extern awe_modRepWinOverlapClass *MicProcessing____WOLASynthesis1____overlap;
extern awe_modButterworthFilterClass *ButterFilter1;
extern awe_modBiquadCascadeClass *ButterFilter1_filt;
extern awe_modFifoInClass *BufferUp1____fifoIn;
extern awe_modTypeConversionClass *TypeConversion3;
extern awe_modSinkClass *Sink3;
extern LayoutInstance *theLayout1;
extern LayoutInstance *theLayout3;

#endif // AM_2CM_FBF_SCNR_THF_NT_H

