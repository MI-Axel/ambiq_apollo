/*******************************************************************************
*
********************************************************************************
*     ModuleList.h
********************************************************************************
*
*     Description:  Module list for the target
*
*     Copyright: (c) 2017 DSP Concepts, Inc. All rights reserved.
*                         1800 Wyatt Drive, Suite 14
*                         Sunnyvale, CA 95054
*
*******************************************************************************/

#include "Framework.h"

// Audio Weaver modules
extern const ModClassModule awe_modAGCCoreClass;
extern const ModClassModule awe_modAGCLimiterCoreClass;
extern const ModClassModule awe_modAGCLimiterCoreFract32Class;
extern const ModClassModule awe_modAGCMultiplierFract32Class;
extern const ModClassModule awe_modAGCNoiseGateCoreClass;
extern const ModClassModule awe_modAbsClass;
extern const ModClassModule awe_modAbsFract32Class;
extern const ModClassModule awe_modAcosClass;
extern const ModClassModule awe_modAdderClass;
extern const ModClassModule awe_modAdderFract32Class;
extern const ModClassModule awe_modAdderInt32Class;
extern const ModClassModule awe_modAsinClass;
extern const ModClassModule awe_modAtanClass;
extern const ModClassModule awe_modAtan2Class;
extern const ModClassModule awe_modBalanceClass;
extern const ModClassModule awe_modBalanceFract32Class;
extern const ModClassModule awe_modBiquadClass;
extern const ModClassModule awe_modBiquadCascadeClass;
extern const ModClassModule awe_modBiquadCascadeFract32Class;
extern const ModClassModule awe_modBiquadFract32Class;
extern const ModClassModule awe_modBiquadNCascadeClass;
extern const ModClassModule awe_modBiquadSmoothedClass;
extern const ModClassModule awe_modBiquadSmoothedFract32Class;
extern const ModClassModule awe_modBiquadV2Fract32Class;
extern const ModClassModule awe_modBitsToIntClass;
extern const ModClassModule awe_modBlockCounterClass;
extern const ModClassModule awe_modBooleanInvertClass;
extern const ModClassModule awe_modBooleanSinkClass;
extern const ModClassModule awe_modBooleanSourceClass;
extern const ModClassModule awe_modButterworthFilterClass;
extern const ModClassModule awe_modButterworthFilterFract32Class;
extern const ModClassModule awe_modCeilClass;
extern const ModClassModule awe_modClipAsymClass;
extern const ModClassModule awe_modClipAsymFract32Class;
extern const ModClassModule awe_modClipIndicatorClass;
extern const ModClassModule awe_modClipIndicatorFract32Class;
extern const ModClassModule awe_modCopierClass;
extern const ModClassModule awe_modCosClass;
extern const ModClassModule awe_modCoshClass;
extern const ModClassModule awe_modCounterClass;
extern const ModClassModule awe_modCrossFaderClass;
extern const ModClassModule awe_modDCSourceIntClass;
extern const ModClassModule awe_modDCSourceV2Class;
extern const ModClassModule awe_modDCSourceV2Fract32Class;
extern const ModClassModule awe_modDb10Class;
extern const ModClassModule awe_modDb10ApproxClass;
extern const ModClassModule awe_modDb20Class;
extern const ModClassModule awe_modDb20ApproxClass;
extern const ModClassModule awe_modDb20Fract32Class;
extern const ModClassModule awe_modDebounceClass;
extern const ModClassModule awe_modDeinterleaveClass;
extern const ModClassModule awe_modDelayClass;
extern const ModClassModule awe_modDelayMsecClass;
extern const ModClassModule awe_modDivideClass;
extern const ModClassModule awe_modExpClass;
extern const ModClassModule awe_modFIRClass;
extern const ModClassModule awe_modFIRFract32Class;
extern const ModClassModule awe_modFloorClass;
extern const ModClassModule awe_modFmodClass;
extern const ModClassModule awe_modFrexpClass;
extern const ModClassModule awe_modGraphicEQBandClass;
extern const ModClassModule awe_modGraphicEQBandFract32Class;
extern const ModClassModule awe_modImpulseMsecSourceClass;
extern const ModClassModule awe_modImpulseMsecSourceFract32Class;
extern const ModClassModule awe_modImpulseSourceFract32Class;
extern const ModClassModule awe_modIntToBitsClass;
extern const ModClassModule awe_modInterleaveClass;
extern const ModClassModule awe_modInvertClass;
extern const ModClassModule awe_modInvertFract32Class;
extern const ModClassModule awe_modLShiftFract32Class;
extern const ModClassModule awe_modLdexpClass;
extern const ModClassModule awe_modLogClass;
extern const ModClassModule awe_modLog10Class;
extern const ModClassModule awe_modLog10Fract32Class;
extern const ModClassModule awe_modLog2Class;
extern const ModClassModule awe_modLog2Fract32Class;
extern const ModClassModule awe_modLogicAllClass;
extern const ModClassModule awe_modLogicAndConstFract32Class;
extern const ModClassModule awe_modLogicAnyClass;
extern const ModClassModule awe_modLogicBinaryOpClass;
extern const ModClassModule awe_modLogicCompareClass;
extern const ModClassModule awe_modLogicCompareConstClass;
extern const ModClassModule awe_modLogicCompareConstFract32Class;
extern const ModClassModule awe_modLogicCompareConstInt32Class;
extern const ModClassModule awe_modLogicCompareFract32Class;
extern const ModClassModule awe_modLogicCompareInt32Class;
extern const ModClassModule awe_modMaxAbsClass;
extern const ModClassModule awe_modMaxAbsFract32Class;
extern const ModClassModule awe_modMeterClass;
extern const ModClassModule awe_modMeterFract32Class;
extern const ModClassModule awe_modMixerDenseFract32Class;
extern const ModClassModule awe_modMixerFract32Class;
extern const ModClassModule awe_modMixerSmoothedFract32Class;
extern const ModClassModule awe_modMixerV3Class;
extern const ModClassModule awe_modMixerV3Fract32Class;
extern const ModClassModule awe_modModfClass;
extern const ModClassModule awe_modMultiplexorClass;
extern const ModClassModule awe_modMultiplexorV2Class;
extern const ModClassModule awe_modMultiplexorV2Fract32Class;
extern const ModClassModule awe_modMultiplierFract32Class;
extern const ModClassModule awe_modMultiplierV2Class;
extern const ModClassModule awe_modMultiplierV2Fract32Class;
extern const ModClassModule awe_modMuteNSmoothedClass;
extern const ModClassModule awe_modMuteNSmoothedFract32Class;
extern const ModClassModule awe_modMuteSmoothedClass;
extern const ModClassModule awe_modMuteSmoothedFract32Class;
extern const ModClassModule awe_modMuteUnmuteClass;
extern const ModClassModule awe_modMuteUnmuteFract32Class;
extern const ModClassModule awe_modNullSinkClass;
extern const ModClassModule awe_modParamGetClass;
extern const ModClassModule awe_modParamSetClass;
extern const ModClassModule awe_modPeriodicFunctionGenClass;
extern const ModClassModule awe_modPeriodicSourceClass;
extern const ModClassModule awe_modPeriodicSourceFract32Class;
extern const ModClassModule awe_modPolynomialClass;
extern const ModClassModule awe_modPolynomialFract32Class;
extern const ModClassModule awe_modPowClass;
extern const ModClassModule awe_modPow10toXClass;
extern const ModClassModule awe_modPow2Fract32Class;
extern const ModClassModule awe_modPowFract32Class;
extern const ModClassModule awe_modPulseGenClass;
extern const ModClassModule awe_modPulseGenFract32Class;
extern const ModClassModule awe_modRMSClass;
extern const ModClassModule awe_modRMSFract32Class;
extern const ModClassModule awe_modRandClass;
extern const ModClassModule awe_modReciprocalClass;
extern const ModClassModule awe_modReciprocalFract32Class;
extern const ModClassModule awe_modRemainderClass;
extern const ModClassModule awe_modRoundClass;
extern const ModClassModule awe_modRouterClass;
extern const ModClassModule awe_modRouterSmoothedClass;
extern const ModClassModule awe_modRouterSmoothedFract32Class;
extern const ModClassModule awe_modSMixer2x1Class;
extern const ModClassModule awe_modSMixer2x1Fract32Class;
extern const ModClassModule awe_modSOFSmoothedCascadeFract32Class;
extern const ModClassModule awe_modSawtoothFract32Class;
extern const ModClassModule awe_modScaleOffsetClass;
extern const ModClassModule awe_modScaleOffsetFract32Class;
extern const ModClassModule awe_modScaleOffsetInt32Class;
extern const ModClassModule awe_modScalerControlClass;
extern const ModClassModule awe_modScalerControlBlockSmoothedFract32Class;
extern const ModClassModule awe_modScalerControlSmoothedFract32Class;
extern const ModClassModule awe_modScalerDBControlClass;
extern const ModClassModule awe_modScalerDBFract32Class;
extern const ModClassModule awe_modScalerDBSmoothedFract32Class;
extern const ModClassModule awe_modScalerFract32Class;
extern const ModClassModule awe_modScalerNDBSmoothedFract32Class;
extern const ModClassModule awe_modScalerNFract32Class;
extern const ModClassModule awe_modScalerNSmoothedFract32Class;
extern const ModClassModule awe_modScalerNV2Class;
extern const ModClassModule awe_modScalerSmoothedFract32Class;
extern const ModClassModule awe_modScalerV2Class;
extern const ModClassModule awe_modSecondOrderFilterSmoothedClass;
extern const ModClassModule awe_modSecondOrderFilterSmoothedCascadeClass;
extern const ModClassModule awe_modSecondOrderFilterSmoothedFract32Class;
extern const ModClassModule awe_modShiftFract32Class;
extern const ModClassModule awe_modSignClass;
extern const ModClassModule awe_modSinClass;
extern const ModClassModule awe_modSineGenControlFract32Class;
extern const ModClassModule awe_modSineGenFract32Class;
extern const ModClassModule awe_modSineSmoothedGenClass;
extern const ModClassModule awe_modSineSmoothedGenFract32Class;
extern const ModClassModule awe_modSinhClass;
extern const ModClassModule awe_modSinkClass;
extern const ModClassModule awe_modSinkFract32Class;
extern const ModClassModule awe_modSinkIntClass;
extern const ModClassModule awe_modSofV2HpFract32Class;
extern const ModClassModule awe_modSoftClipClass;
extern const ModClassModule awe_modSoftClipFract32Class;
extern const ModClassModule awe_modSoloMuteClass;
extern const ModClassModule awe_modSoloMuteFract32Class;
extern const ModClassModule awe_modSourceClass;
extern const ModClassModule awe_modSourceFract32Class;
extern const ModClassModule awe_modSourceIntClass;
extern const ModClassModule awe_modSqrtClass;
extern const ModClassModule awe_modSqrtFract32Class;
extern const ModClassModule awe_modSquareClass;
extern const ModClassModule awe_modSquareAddClass;
extern const ModClassModule awe_modSquareAddFract32Class;
extern const ModClassModule awe_modSquareFract32Class;
extern const ModClassModule awe_modSubtractClass;
extern const ModClassModule awe_modSubtractFract32Class;
extern const ModClassModule awe_modSubtractInt32Class;
extern const ModClassModule awe_modSumDiffClass;
extern const ModClassModule awe_modSumDiffFract32Class;
extern const ModClassModule awe_modSumDiffInt32Class;
extern const ModClassModule awe_modTableInterpClass;
extern const ModClassModule awe_modTableInterpFract32Class;
extern const ModClassModule awe_modTableLookupClass;
extern const ModClassModule awe_modTanClass;
extern const ModClassModule awe_modTanhClass;
extern const ModClassModule awe_modThreeBandToneControlClass;
extern const ModClassModule awe_modThreeBandToneControlFract32Class;
extern const ModClassModule awe_modToggleButtonClass;
extern const ModClassModule awe_modTypeConversionClass;
extern const ModClassModule awe_modUndb10Class;
extern const ModClassModule awe_modUndb10ApproxClass;
extern const ModClassModule awe_modUndb10Fract32Class;
extern const ModClassModule awe_modUndb20Class;
extern const ModClassModule awe_modUndb20ApproxClass;
extern const ModClassModule awe_modUndb20Fract32Class;
extern const ModClassModule awe_modVolumeControlClass;
extern const ModClassModule awe_modVolumeControlFract32Class;
extern const ModClassModule awe_modWetDryClass;
extern const ModClassModule awe_modWhiteNoiseClass;
extern const ModClassModule awe_modWhiteNoiseFract32Class;
extern const ModClassModule awe_modWithinRangeClass;
extern const ModClassModule awe_modWithinRangeFract32Class;
extern const ModClassModule awe_modZeroCrossingDetectorClass;
extern const ModClassModule awe_modZeroCrossingDetectorFract32Class;
extern const ModClassModule awe_modZeroSourceClass;
extern const ModClassModule awe_modComplexMultiplierClass;
extern const ModClassModule awe_modFftClass;
extern const ModClassModule awe_modFifoInClass;
extern const ModClassModule awe_modFifoOutClass;
extern const ModClassModule awe_modIfftClass;
extern const ModClassModule awe_modNullSinkClass;
extern const ModClassModule awe_modRepWinOverlapClass;
extern const ModClassModule awe_modRouterClass;
extern const ModClassModule awe_modSCNRv1Class;
extern const ModClassModule awe_modSetWirePropertiesClass;
extern const ModClassModule awe_modSinkClass;
extern const ModClassModule awe_modSourceClass;
extern const ModClassModule awe_modToggleButtonClass;
extern const ModClassModule awe_modTypeConversionClass;
extern const ModClassModule awe_modTimeOutClass;
extern const ModClassModule awe_modWindowAliasClass;

#define LISTOFCLASSOBJECTS \
&awe_modAbsClass, \
&awe_modAbsFract32Class, \
&awe_modAcosClass, \
&awe_modAdderClass, \
&awe_modAdderFract32Class, \
&awe_modAdderInt32Class, \
&awe_modAsinClass, \
&awe_modAtanClass, \
&awe_modAtan2Class, \
&awe_modBalanceClass, \
&awe_modBalanceFract32Class, \
&awe_modBiquadClass, \
&awe_modBiquadCascadeClass, \
&awe_modBiquadCascadeFract32Class, \
&awe_modBiquadFract32Class, \
&awe_modBiquadNCascadeClass, \
&awe_modBiquadSmoothedClass, \
&awe_modBiquadSmoothedFract32Class, \
&awe_modBiquadV2Fract32Class, \
&awe_modBitsToIntClass, \
&awe_modBlockCounterClass, \
&awe_modBooleanInvertClass, \
&awe_modBooleanSinkClass, \
&awe_modBooleanSourceClass, \
&awe_modButterworthFilterClass, \
&awe_modButterworthFilterFract32Class, \
&awe_modCeilClass, \
&awe_modClipAsymClass, \
&awe_modClipAsymFract32Class, \
&awe_modClipIndicatorClass, \
&awe_modClipIndicatorFract32Class, \
&awe_modCopierClass, \
&awe_modCosClass, \
&awe_modCoshClass, \
&awe_modCounterClass, \
&awe_modCrossFaderClass, \
&awe_modDCSourceIntClass, \
&awe_modDCSourceV2Class, \
&awe_modDCSourceV2Fract32Class, \
&awe_modDb10Class, \
&awe_modDb10ApproxClass, \
&awe_modDb20Class, \
&awe_modDb20ApproxClass, \
&awe_modDb20Fract32Class, \
&awe_modDebounceClass, \
&awe_modDeinterleaveClass, \
&awe_modDelayClass, \
&awe_modDelayMsecClass, \
&awe_modDivideClass, \
&awe_modExpClass, \
&awe_modFIRClass, \
&awe_modFIRFract32Class, \
&awe_modFloorClass, \
&awe_modFmodClass, \
&awe_modFrexpClass, \
&awe_modGraphicEQBandClass, \
&awe_modGraphicEQBandFract32Class, \
&awe_modImpulseMsecSourceClass, \
&awe_modImpulseMsecSourceFract32Class, \
&awe_modImpulseSourceFract32Class, \
&awe_modIntToBitsClass, \
&awe_modInterleaveClass, \
&awe_modInvertClass, \
&awe_modInvertFract32Class, \
&awe_modLdexpClass, \
&awe_modLogClass, \
&awe_modLog10Class, \
&awe_modLog10Fract32Class, \
&awe_modLog2Class, \
&awe_modLog2Fract32Class, \
&awe_modLogicAllClass, \
&awe_modLogicAndConstFract32Class, \
&awe_modLogicAnyClass, \
&awe_modLogicBinaryOpClass, \
&awe_modLogicCompareClass, \
&awe_modLogicCompareConstClass, \
&awe_modLogicCompareConstFract32Class, \
&awe_modLogicCompareConstInt32Class, \
&awe_modLogicCompareFract32Class, \
&awe_modLogicCompareInt32Class, \
&awe_modMaxAbsClass, \
&awe_modMaxAbsFract32Class, \
&awe_modMeterClass, \
&awe_modMeterFract32Class, \
&awe_modMixerDenseFract32Class, \
&awe_modMixerFract32Class, \
&awe_modMixerSmoothedFract32Class, \
&awe_modMixerV3Class, \
&awe_modMixerV3Fract32Class, \
&awe_modModfClass, \
&awe_modMultiplexorClass, \
&awe_modMultiplexorV2Class, \
&awe_modMultiplexorV2Fract32Class, \
&awe_modMultiplierFract32Class, \
&awe_modMultiplierV2Class, \
&awe_modMultiplierV2Fract32Class, \
&awe_modMuteNSmoothedClass, \
&awe_modMuteNSmoothedFract32Class, \
&awe_modMuteSmoothedClass, \
&awe_modMuteSmoothedFract32Class, \
&awe_modMuteUnmuteClass, \
&awe_modMuteUnmuteFract32Class, \
&awe_modNullSinkClass, \
&awe_modParamGetClass, \
&awe_modParamSetClass, \
&awe_modPeriodicFunctionGenClass, \
&awe_modPeriodicSourceClass, \
&awe_modPeriodicSourceFract32Class, \
&awe_modPolynomialClass, \
&awe_modPolynomialFract32Class, \
&awe_modPowClass, \
&awe_modPow10toXClass, \
&awe_modPow2Fract32Class, \
&awe_modPowFract32Class, \
&awe_modPulseGenClass, \
&awe_modPulseGenFract32Class, \
&awe_modRMSClass, \
&awe_modRMSFract32Class, \
&awe_modRandClass, \
&awe_modReciprocalClass, \
&awe_modReciprocalFract32Class, \
&awe_modRemainderClass, \
&awe_modRoundClass, \
&awe_modRouterClass, \
&awe_modRouterSmoothedClass, \
&awe_modRouterSmoothedFract32Class, \
&awe_modSMixer2x1Class, \
&awe_modSMixer2x1Fract32Class, \
&awe_modSOFSmoothedCascadeFract32Class, \
&awe_modSawtoothFract32Class, \
&awe_modScaleOffsetClass, \
&awe_modScaleOffsetFract32Class, \
&awe_modScaleOffsetInt32Class, \
&awe_modScalerControlClass, \
&awe_modScalerControlBlockSmoothedFract32Class, \
&awe_modScalerControlSmoothedFract32Class, \
&awe_modScalerDBControlClass, \
&awe_modScalerDBFract32Class, \
&awe_modScalerDBSmoothedFract32Class, \
&awe_modScalerFract32Class, \
&awe_modScalerNDBSmoothedFract32Class, \
&awe_modScalerNFract32Class, \
&awe_modScalerNSmoothedFract32Class, \
&awe_modScalerNV2Class, \
&awe_modScalerSmoothedFract32Class, \
&awe_modScalerV2Class, \
&awe_modSecondOrderFilterSmoothedClass, \
&awe_modSecondOrderFilterSmoothedCascadeClass, \
&awe_modSecondOrderFilterSmoothedFract32Class, \
&awe_modShiftFract32Class, \
&awe_modSignClass, \
&awe_modSinClass, \
&awe_modSineGenControlFract32Class, \
&awe_modSineGenFract32Class, \
&awe_modSineSmoothedGenClass, \
&awe_modSineSmoothedGenFract32Class, \
&awe_modSinhClass, \
&awe_modSinkClass, \
&awe_modSinkFract32Class, \
&awe_modSinkIntClass, \
&awe_modSofV2HpFract32Class, \
&awe_modSoftClipClass, \
&awe_modSoftClipFract32Class, \
&awe_modSoloMuteClass, \
&awe_modSoloMuteFract32Class, \
&awe_modSourceClass, \
&awe_modSourceFract32Class, \
&awe_modSourceIntClass, \
&awe_modSqrtClass, \
&awe_modSqrtFract32Class, \
&awe_modSquareClass, \
&awe_modSquareAddClass, \
&awe_modSquareAddFract32Class, \
&awe_modSquareFract32Class, \
&awe_modSubtractClass, \
&awe_modSubtractFract32Class, \
&awe_modSubtractInt32Class, \
&awe_modSumDiffClass, \
&awe_modSumDiffFract32Class, \
&awe_modSumDiffInt32Class, \
&awe_modTableInterpClass, \
&awe_modTableInterpFract32Class, \
&awe_modTableLookupClass, \
&awe_modTanClass, \
&awe_modTanhClass, \
&awe_modThreeBandToneControlClass, \
&awe_modThreeBandToneControlFract32Class, \
&awe_modToggleButtonClass, \
&awe_modTypeConversionClass, \
&awe_modUndb10Class, \
&awe_modUndb10ApproxClass, \
&awe_modUndb10Fract32Class, \
&awe_modUndb20Class, \
&awe_modUndb20ApproxClass, \
&awe_modUndb20Fract32Class, \
&awe_modVolumeControlClass, \
&awe_modVolumeControlFract32Class, \
&awe_modWetDryClass, \
&awe_modWhiteNoiseClass, \
&awe_modWhiteNoiseFract32Class, \
&awe_modWithinRangeClass, \
&awe_modWithinRangeFract32Class, \
&awe_modZeroCrossingDetectorClass, \
&awe_modZeroCrossingDetectorFract32Class, \
&awe_modZeroSourceClass, \
&awe_modComplexMultiplierClass, \
&awe_modFftClass, \
&awe_modFifoInClass, \
&awe_modFifoOutClass, \
&awe_modIfftClass, \
&awe_modNullSinkClass, \
&awe_modRepWinOverlapClass, \
&awe_modRouterClass, \
&awe_modSCNRv1Class, \
&awe_modSetWirePropertiesClass, \
&awe_modSinkClass, \
&awe_modSourceClass, \
&awe_modToggleButtonClass, \
&awe_modTypeConversionClass, \
&awe_modTimeOutClass, \
&awe_modWindowAliasClass
