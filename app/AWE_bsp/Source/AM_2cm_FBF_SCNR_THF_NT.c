/****************************************************************************
 *
 *		Target Tuning Symbol File
 *		-------------------------
 *
 *          Generated on:  15-Nov-2018 10:16:41
 *
 ***************************************************************************/

#include "AM_2cm_FBF_SCNR_THF_NT.h"
AWE_MOD_SLOW_ANY_DATA WireInstance *wire1;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire2;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire3;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire4;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire5;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire6;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire7;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire8;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire9;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire10;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire11;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire12;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire13;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire14;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire15;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire16;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire17;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire18;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire19;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire20;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire21;
AWE_MOD_SLOW_ANY_DATA WireInstance *wire22;
AWE_MOD_SLOW_ANY_DATA awe_modTypeConversionClass *TypeConversion1;
AWE_MOD_SLOW_ANY_DATA awe_modRouterClass *Router1;
AWE_MOD_SLOW_ANY_DATA awe_modWindowAliasClass *MicProcessing____WOLAAnalysis2____windowAlias;
AWE_MOD_SLOW_ANY_DATA awe_modFftClass *MicProcessing____WOLAAnalysis2____fft;
AWE_MOD_SLOW_ANY_DATA awe_modSetWirePropertiesClass *MicProcessing____WOLAAnalysis2____wp;
AWE_MOD_SLOW_ANY_DATA awe_modDCSourceIntClass *DC1;
AWE_MOD_SLOW_ANY_DATA awe_modFifoOutClass *BufferUp1____fifoOut;
AWE_MOD_SLOW_ANY_DATA awe_modTypeConversionClass *TypeConversion4;
AWE_MOD_SLOW_ANY_DATA awe_modSensoryTHFCortexMCmdsClass *SensoryTHFCortexMCmds1;
AWE_MOD_SLOW_ANY_DATA awe_modNullSinkClass *Sink2;
AWE_MOD_SLOW_ANY_DATA awe_modToggleButtonClass *ToggleButton1;
AWE_MOD_SLOW_ANY_DATA awe_modTypeConversionClass *TypeConversion2;
AWE_MOD_SLOW_ANY_DATA awe_modNullSinkClass *Sink1;
AWE_MOD_SLOW_ANY_DATA awe_modSourceClass *MicProcessing____beamformer____weight;
AWE_MOD_SLOW_ANY_DATA awe_modComplexMultiplierClass *MicProcessing____beamformer____ComplexMul1;
AWE_MOD_SLOW_ANY_DATA awe_modAdderClass *MicProcessing____beamformer____Add1;
AWE_MOD_SLOW_ANY_DATA awe_modSCNRv1Class *MicProcessing____SCNR1;
AWE_MOD_SLOW_ANY_DATA awe_modSetWirePropertiesClass *MicProcessing____WOLASynthesis1____wp;
AWE_MOD_SLOW_ANY_DATA awe_modIfftClass *MicProcessing____WOLASynthesis1____ifft;
AWE_MOD_SLOW_ANY_DATA awe_modRepWinOverlapClass *MicProcessing____WOLASynthesis1____overlap;
AWE_MOD_SLOW_ANY_DATA awe_modButterworthFilterClass *ButterFilter1;
AWE_MOD_SLOW_ANY_DATA awe_modBiquadCascadeClass *ButterFilter1_filt;
AWE_MOD_SLOW_ANY_DATA awe_modFifoInClass *BufferUp1____fifoIn;
AWE_MOD_SLOW_ANY_DATA awe_modTypeConversionClass *TypeConversion3;
AWE_MOD_SLOW_ANY_DATA awe_modSinkClass *Sink3;
AWE_MOD_SLOW_ANY_DATA LayoutInstance *theLayout1;
AWE_MOD_SLOW_ANY_DATA LayoutInstance *theLayout3;

#ifdef __cplusplus
extern "C" {
#endif

#include "Errors.h"

/* ----------------------------------------------------------------------
** Object variables declarations.
** ------------------------------------------------------------------- */
    
INT32 InitializeAWESymbols(void)
{

InstanceDescriptor *inst;
UINT32 classID;
    
if (awe_fwGetObjectByID(wire1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire1 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire2_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire2 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire3_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire3 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire4_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire4 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire5_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire5 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire6_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire6 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire7_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire7 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire8_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire8 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire9_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire9 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire10_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire10 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire11_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire11 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire12_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire12 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire13_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire13 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire14_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire14 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire15_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire15 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire16_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire16 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire17_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire17 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire18_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire18 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire19_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire19 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire20_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire20 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire21_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire21 = (WireInstance *) inst;

if (awe_fwGetObjectByID(wire22_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
wire22 = (WireInstance *) inst;

if (awe_fwGetObjectByID(TypeConversion1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
TypeConversion1 = (awe_modTypeConversionClass *) inst;

if (awe_fwGetObjectByID(Router1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
Router1 = (awe_modRouterClass *) inst;

if (awe_fwGetObjectByID(MicProcessing____WOLAAnalysis2____windowAlias_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____WOLAAnalysis2____windowAlias = (awe_modWindowAliasClass *) inst;

if (awe_fwGetObjectByID(MicProcessing____WOLAAnalysis2____fft_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____WOLAAnalysis2____fft = (awe_modFftClass *) inst;

if (awe_fwGetObjectByID(MicProcessing____WOLAAnalysis2____wp_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____WOLAAnalysis2____wp = (awe_modSetWirePropertiesClass *) inst;

if (awe_fwGetObjectByID(DC1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
DC1 = (awe_modDCSourceIntClass *) inst;

if (awe_fwGetObjectByID(BufferUp1____fifoOut_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
BufferUp1____fifoOut = (awe_modFifoOutClass *) inst;

if (awe_fwGetObjectByID(TypeConversion4_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
TypeConversion4 = (awe_modTypeConversionClass *) inst;

if (awe_fwGetObjectByID(SensoryTHFCortexMCmds1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
SensoryTHFCortexMCmds1 = (awe_modSensoryTHFCortexMCmdsClass *) inst;

if (awe_fwGetObjectByID(Sink2_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
Sink2 = (awe_modNullSinkClass *) inst;

if (awe_fwGetObjectByID(ToggleButton1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
ToggleButton1 = (awe_modToggleButtonClass *) inst;

if (awe_fwGetObjectByID(TypeConversion2_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
TypeConversion2 = (awe_modTypeConversionClass *) inst;

if (awe_fwGetObjectByID(Sink1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
Sink1 = (awe_modNullSinkClass *) inst;

if (awe_fwGetObjectByID(MicProcessing____beamformer____weight_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____beamformer____weight = (awe_modSourceClass *) inst;

if (awe_fwGetObjectByID(MicProcessing____beamformer____ComplexMul1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____beamformer____ComplexMul1 = (awe_modComplexMultiplierClass *) inst;

if (awe_fwGetObjectByID(MicProcessing____beamformer____Add1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____beamformer____Add1 = (awe_modAdderClass *) inst;

if (awe_fwGetObjectByID(MicProcessing____SCNR1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____SCNR1 = (awe_modSCNRv1Class *) inst;

if (awe_fwGetObjectByID(MicProcessing____WOLASynthesis1____wp_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____WOLASynthesis1____wp = (awe_modSetWirePropertiesClass *) inst;

if (awe_fwGetObjectByID(MicProcessing____WOLASynthesis1____ifft_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____WOLASynthesis1____ifft = (awe_modIfftClass *) inst;

if (awe_fwGetObjectByID(MicProcessing____WOLASynthesis1____overlap_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
MicProcessing____WOLASynthesis1____overlap = (awe_modRepWinOverlapClass *) inst;

if (awe_fwGetObjectByID(ButterFilter1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
ButterFilter1 = (awe_modButterworthFilterClass *) inst;

if (awe_fwGetObjectByID(ButterFilter1_filt_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
ButterFilter1_filt = (awe_modBiquadCascadeClass *) inst;

if (awe_fwGetObjectByID(BufferUp1____fifoIn_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
BufferUp1____fifoIn = (awe_modFifoInClass *) inst;

if (awe_fwGetObjectByID(TypeConversion3_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
TypeConversion3 = (awe_modTypeConversionClass *) inst;

if (awe_fwGetObjectByID(Sink3_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
Sink3 = (awe_modSinkClass *) inst;

if (awe_fwGetObjectByID(theLayout1_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
theLayout1 = (LayoutInstance *) inst;

if (awe_fwGetObjectByID(theLayout3_ID, &inst, &classID) != E_SUCCESS)
    return( E_CLASS_NOT_FOUND);
theLayout3 = (LayoutInstance *) inst;

        
return(E_SUCCESS);
}

#ifdef __cplusplus
}
#endif

