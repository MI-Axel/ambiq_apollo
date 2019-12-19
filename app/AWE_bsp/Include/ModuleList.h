/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     ModuleList.h
********************************************************************************
*
* -----------------------------------------------------------------------------
* Specifies the audio modules that will be linked into the target application
* -----------------------------------------------------------------------------
*
*     Copyright:    DSP Concepts, Inc., 2007 - 2019
*                   3235 Kifer Road, Suite 100
*                   Santa Clara, CA 95051
*
*******************************************************************************/


#ifndef _MODULELIST_H
#define _MODULELIST_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "AWECore.h"

// Standard Modules
extern const UINT32 awe_modAGCCoreClass;
extern const UINT32 awe_modAGCLimiterCoreClass;
extern const UINT32 awe_modAGCLimiterCoreFract32Class;
extern const UINT32 awe_modAGCMultiplierFract32Class;
extern const UINT32 awe_modAGCNoiseGateCoreClass;
extern const UINT32 awe_modAbsClass;
extern const UINT32 awe_modAbsFract32Class;
extern const UINT32 awe_modAcosClass;
extern const UINT32 awe_modAdderClass;
extern const UINT32 awe_modAdderFract32Class;
extern const UINT32 awe_modAdderInt32Class;
extern const UINT32 awe_modAsinClass;
extern const UINT32 awe_modAtanClass;
extern const UINT32 awe_modAtan2Class;
extern const UINT32 awe_modBalanceClass;
extern const UINT32 awe_modBalanceFract32Class;
extern const UINT32 awe_modBiquadClass;
extern const UINT32 awe_modBiquadCascadeClass;
extern const UINT32 awe_modBiquadCascadeFract32Class;
extern const UINT32 awe_modBiquadFract32Class;
extern const UINT32 awe_modBiquadNCascadeClass;
extern const UINT32 awe_modBiquadSmoothedClass;
extern const UINT32 awe_modBiquadSmoothedFract32Class;
extern const UINT32 awe_modBiquadV2Fract32Class;
extern const UINT32 awe_modBitsToIntClass;
extern const UINT32 awe_modBlockCounterClass;
extern const UINT32 awe_modBooleanInvertClass;
extern const UINT32 awe_modBooleanSinkClass;
extern const UINT32 awe_modBooleanSourceClass;
extern const UINT32 awe_modButterworthFilterClass;
extern const UINT32 awe_modButterworthFilterFract32Class;
extern const UINT32 awe_modCeilClass;
extern const UINT32 awe_modClipAsymClass;
extern const UINT32 awe_modClipAsymFract32Class;
extern const UINT32 awe_modClipIndicatorClass;
extern const UINT32 awe_modClipIndicatorFract32Class;
extern const UINT32 awe_modCopierClass;
extern const UINT32 awe_modCosClass;
extern const UINT32 awe_modCoshClass;
extern const UINT32 awe_modCounterClass;
extern const UINT32 awe_modCrossFaderClass;
extern const UINT32 awe_modDCSourceIntClass;
extern const UINT32 awe_modDCSourceV2Class;
extern const UINT32 awe_modDCSourceV2Fract32Class;
extern const UINT32 awe_modDb10Class;
extern const UINT32 awe_modDb10ApproxClass;
extern const UINT32 awe_modDb20Class;
extern const UINT32 awe_modDb20ApproxClass;
extern const UINT32 awe_modDb20Fract32Class;
extern const UINT32 awe_modDebounceClass;
extern const UINT32 awe_modDeinterleaveClass;
extern const UINT32 awe_modDelayClass;
extern const UINT32 awe_modDelayMsecClass;
extern const UINT32 awe_modDivideClass;
extern const UINT32 awe_modExpClass;
extern const UINT32 awe_modFIRClass;
extern const UINT32 awe_modFIRFract32Class;
extern const UINT32 awe_modFloorClass;
extern const UINT32 awe_modFmodClass;
extern const UINT32 awe_modFrexpClass;
extern const UINT32 awe_modGPIOClass;
extern const UINT32 awe_modGraphicEQBandClass;
extern const UINT32 awe_modGraphicEQBandFract32Class;
extern const UINT32 awe_modImpulseMsecSourceClass;
extern const UINT32 awe_modImpulseMsecSourceFract32Class;
extern const UINT32 awe_modImpulseSourceFract32Class;
extern const UINT32 awe_modIntToBitsClass;
extern const UINT32 awe_modInterleaveClass;
extern const UINT32 awe_modInvertClass;
extern const UINT32 awe_modInvertFract32Class;
extern const UINT32 awe_modLShiftFract32Class;
extern const UINT32 awe_modLdexpClass;
extern const UINT32 awe_modLogClass;
extern const UINT32 awe_modLog10Class;
extern const UINT32 awe_modLog10Fract32Class;
extern const UINT32 awe_modLog2Class;
extern const UINT32 awe_modLog2Fract32Class;
extern const UINT32 awe_modLogicAllClass;
extern const UINT32 awe_modLogicAndConstFract32Class;
extern const UINT32 awe_modLogicAnyClass;
extern const UINT32 awe_modLogicBinaryOpClass;
extern const UINT32 awe_modLogicCompareClass;
extern const UINT32 awe_modLogicCompareConstClass;
extern const UINT32 awe_modLogicCompareConstFract32Class;
extern const UINT32 awe_modLogicCompareConstInt32Class;
extern const UINT32 awe_modLogicCompareFract32Class;
extern const UINT32 awe_modLogicCompareInt32Class;
extern const UINT32 awe_modMaxAbsClass;
extern const UINT32 awe_modMaxAbsFract32Class;
extern const UINT32 awe_modMeterClass;
extern const UINT32 awe_modMeterFract32Class;
extern const UINT32 awe_modMixerDenseFract32Class;
extern const UINT32 awe_modMixerFract32Class;
extern const UINT32 awe_modMixerSmoothedFract32Class;
extern const UINT32 awe_modMixerV3Class;
extern const UINT32 awe_modMixerV3Fract32Class;
extern const UINT32 awe_modModfClass;
extern const UINT32 awe_modMultiplexorClass;
extern const UINT32 awe_modMultiplexorV2Class;
extern const UINT32 awe_modMultiplexorV2Fract32Class;
extern const UINT32 awe_modMultiplierFract32Class;
extern const UINT32 awe_modMultiplierV2Class;
extern const UINT32 awe_modMultiplierV2Fract32Class;
extern const UINT32 awe_modMuteNSmoothedClass;
extern const UINT32 awe_modMuteNSmoothedFract32Class;
extern const UINT32 awe_modMuteSmoothedClass;
extern const UINT32 awe_modMuteSmoothedFract32Class;
extern const UINT32 awe_modMuteUnmuteClass;
extern const UINT32 awe_modMuteUnmuteFract32Class;
extern const UINT32 awe_modNullSinkClass;
extern const UINT32 awe_modNullSinkV2Class;
extern const UINT32 awe_modParamGetClass;
extern const UINT32 awe_modParamSetClass;
extern const UINT32 awe_modPeriodicFunctionGenClass;
extern const UINT32 awe_modPeriodicSourceClass;
extern const UINT32 awe_modPeriodicSourceFract32Class;
extern const UINT32 awe_modPolynomialClass;
extern const UINT32 awe_modPolynomialFract32Class;
extern const UINT32 awe_modPowClass;
extern const UINT32 awe_modPow10toXClass;
extern const UINT32 awe_modPow2Fract32Class;
extern const UINT32 awe_modPowFract32Class;
extern const UINT32 awe_modPulseGenClass;
extern const UINT32 awe_modPulseGenFract32Class;
extern const UINT32 awe_modRMSClass;
extern const UINT32 awe_modRMSFract32Class;
extern const UINT32 awe_modRMSNClass;
extern const UINT32 awe_modRandClass;
extern const UINT32 awe_modReciprocalClass;
extern const UINT32 awe_modReciprocalFract32Class;
extern const UINT32 awe_modRemainderClass;
extern const UINT32 awe_modRoundClass;
extern const UINT32 awe_modRouterClass;
extern const UINT32 awe_modRouterSmoothedClass;
extern const UINT32 awe_modRouterSmoothedFract32Class;
extern const UINT32 awe_modSMixer2x1Class;
extern const UINT32 awe_modSMixer2x1Fract32Class;
extern const UINT32 awe_modSOFSmoothedCascadeFract32Class;
extern const UINT32 awe_modSawtoothFract32Class;
extern const UINT32 awe_modScaleOffsetClass;
extern const UINT32 awe_modScaleOffsetFract32Class;
extern const UINT32 awe_modScaleOffsetInt32Class;
extern const UINT32 awe_modScalerControlClass;
extern const UINT32 awe_modScalerControlBlockSmoothedFract32Class;
extern const UINT32 awe_modScalerControlSmoothedFract32Class;
extern const UINT32 awe_modScalerDBControlClass;
extern const UINT32 awe_modScalerDBFract32Class;
extern const UINT32 awe_modScalerDBSmoothedFract32Class;
extern const UINT32 awe_modScalerFract32Class;
extern const UINT32 awe_modScalerNControlClass;
extern const UINT32 awe_modScalerNDBSmoothedFract32Class;
extern const UINT32 awe_modScalerNFract32Class;
extern const UINT32 awe_modScalerNSmoothedFract32Class;
extern const UINT32 awe_modScalerNV2Class;
extern const UINT32 awe_modScalerSmoothedFract32Class;
extern const UINT32 awe_modScalerV2Class;
extern const UINT32 awe_modSecondOrderFilterSmoothedClass;
extern const UINT32 awe_modSecondOrderFilterSmoothedCascadeClass;
extern const UINT32 awe_modSecondOrderFilterSmoothedFract32Class;
extern const UINT32 awe_modShiftFract32Class;
extern const UINT32 awe_modSignClass;
extern const UINT32 awe_modSinClass;
extern const UINT32 awe_modSineGenControlFract32Class;
extern const UINT32 awe_modSineGenFract32Class;
extern const UINT32 awe_modSineSmoothedGenClass;
extern const UINT32 awe_modSineSmoothedGenFract32Class;
extern const UINT32 awe_modSinhClass;
extern const UINT32 awe_modSinkClass;
extern const UINT32 awe_modSinkFract32Class;
extern const UINT32 awe_modSinkFract32PropertiesClass;
extern const UINT32 awe_modSinkIntClass;
extern const UINT32 awe_modSinkIntPropertiesClass;
extern const UINT32 awe_modSinkPropertiesClass;
extern const UINT32 awe_modSofV2HpFract32Class;
extern const UINT32 awe_modSoftClipClass;
extern const UINT32 awe_modSoftClipFract32Class;
extern const UINT32 awe_modSoloMuteClass;
extern const UINT32 awe_modSoloMuteFract32Class;
extern const UINT32 awe_modSourceClass;
extern const UINT32 awe_modSourceFract32Class;
extern const UINT32 awe_modSourceFract32PropertiesClass;
extern const UINT32 awe_modSourceIntClass;
extern const UINT32 awe_modSourceIntPropertiesClass;
extern const UINT32 awe_modSourcePropertiesClass;
extern const UINT32 awe_modSqrtClass;
extern const UINT32 awe_modSqrtFract32Class;
extern const UINT32 awe_modSquareClass;
extern const UINT32 awe_modSquareAddClass;
extern const UINT32 awe_modSquareAddFract32Class;
extern const UINT32 awe_modSquareFract32Class;
extern const UINT32 awe_modSubtractClass;
extern const UINT32 awe_modSubtractFract32Class;
extern const UINT32 awe_modSubtractInt32Class;
extern const UINT32 awe_modSumDiffClass;
extern const UINT32 awe_modSumDiffFract32Class;
extern const UINT32 awe_modSumDiffInt32Class;
extern const UINT32 awe_modTableInterpClass;
extern const UINT32 awe_modTableInterpFract32Class;
extern const UINT32 awe_modTableLookupClass;
extern const UINT32 awe_modTableLookupV2Class;
extern const UINT32 awe_modTanClass;
extern const UINT32 awe_modTanhClass;
extern const UINT32 awe_modThreeBandToneControlClass;
extern const UINT32 awe_modThreeBandToneControlFract32Class;
extern const UINT32 awe_modToggleButtonClass;
extern const UINT32 awe_modTypeConversionClass;
extern const UINT32 awe_modUndb10Class;
extern const UINT32 awe_modUndb10ApproxClass;
extern const UINT32 awe_modUndb10Fract32Class;
extern const UINT32 awe_modUndb20Class;
extern const UINT32 awe_modUndb20ApproxClass;
extern const UINT32 awe_modUndb20Fract32Class;
extern const UINT32 awe_modVolumeControlClass;
extern const UINT32 awe_modVolumeControlFract32Class;
extern const UINT32 awe_modWetDryClass;
extern const UINT32 awe_modWhiteNoiseClass;
extern const UINT32 awe_modWhiteNoiseFract32Class;
extern const UINT32 awe_modWithinRangeClass;
extern const UINT32 awe_modWithinRangeFract32Class;
extern const UINT32 awe_modZeroCrossingDetectorClass;
extern const UINT32 awe_modZeroCrossingDetectorFract32Class;
extern const UINT32 awe_modZeroSourceClass;


// Advanced Modules
extern const UINT32 awe_modAGCAttackReleaseClass;
extern const UINT32 awe_modAGCAttackReleaseFract32Class;
extern const UINT32 awe_modAGCCompressorCoreClass;
extern const UINT32 awe_modAGCCompressorCoreFract32Class;
extern const UINT32 awe_modAGCCoreFract32Class;
extern const UINT32 awe_modAGCVariableAttackReleaseClass;
extern const UINT32 awe_modAllpassDelayClass;
extern const UINT32 awe_modAllpassDelay16Class;
extern const UINT32 awe_modAllpassDelay16Fract32Class;
extern const UINT32 awe_modAllpassDelayFract32Class;
extern const UINT32 awe_modAllpassDelayciClass;
extern const UINT32 awe_modAllpassDelayiClass;
extern const UINT32 awe_modAttackDecaySustainReleaseClass;
extern const UINT32 awe_modAudioWeightingClass;
extern const UINT32 awe_modAudioWeightingFract32Class;
extern const UINT32 awe_modAveragerClass;
extern const UINT32 awe_modAveragerFract32Class;
extern const UINT32 awe_modBiquadCascadeHPClass;
extern const UINT32 awe_modBiquadLoadingClass;
extern const UINT32 awe_modBiquadLoadingFract32Class;
extern const UINT32 awe_modBiquadSmoothedHPClass;
extern const UINT32 awe_modBiquadSparseClass;
extern const UINT32 awe_modBlockConcatenateClass;
extern const UINT32 awe_modBlockDelayClass;
extern const UINT32 awe_modBlockDelayV2Class;
extern const UINT32 awe_modBlockExtractClass;
extern const UINT32 awe_modBlockFlipClass;
extern const UINT32 awe_modBlockMedianClass;
extern const UINT32 awe_modBlockStatisticsClass;
extern const UINT32 awe_modBlockStatisticsFract32Class;
extern const UINT32 awe_modBlockStatisticsNClass;
extern const UINT32 awe_modButterworthFilterHPClass;
extern const UINT32 awe_modCfftClass;
extern const UINT32 awe_modCfftFract32Class;
extern const UINT32 awe_modCoeffTableClass;
extern const UINT32 awe_modComplexAngleClass;
extern const UINT32 awe_modComplexConjugateClass;
extern const UINT32 awe_modComplexMagnitudeClass;
extern const UINT32 awe_modComplexMagnitudeFract32Class;
extern const UINT32 awe_modComplexMagnitudeSquaredClass;
extern const UINT32 awe_modComplexModulateClass;
extern const UINT32 awe_modComplexMultiplierClass;
extern const UINT32 awe_modComplexToPolarClass;
extern const UINT32 awe_modComplexToRealImagClass;
extern const UINT32 awe_modComplexToRealImagFract32Class;
extern const UINT32 awe_modConsecutiveCountIntClass;
extern const UINT32 awe_modConvolveClass;
extern const UINT32 awe_modCorrelateClass;
extern const UINT32 awe_modCorrelationFract32Class;
extern const UINT32 awe_modCycleBurnerClass;
extern const UINT32 awe_modCycleBurnerSetClass;
extern const UINT32 awe_modDateTimeClass;
extern const UINT32 awe_modDeadBandClass;
extern const UINT32 awe_modDelay16Class;
extern const UINT32 awe_modDelayInterpClass;
extern const UINT32 awe_modDelayInterpFract32Class;
extern const UINT32 awe_modDelayNChanClass;
extern const UINT32 awe_modDelayNChanMsecClass;
extern const UINT32 awe_modDelayNChanV2Class;
extern const UINT32 awe_modDelayNTapClass;
extern const UINT32 awe_modDelayNTap16Fract32Class;
extern const UINT32 awe_modDelayReaderClass;
extern const UINT32 awe_modDelayStateWriterClass;
extern const UINT32 awe_modDelayStateWriter16Class;
extern const UINT32 awe_modDelayciFract32Class;
extern const UINT32 awe_modDerivativeClass;
extern const UINT32 awe_modDerivativeFract32Class;
extern const UINT32 awe_modDitherFract32Class;
extern const UINT32 awe_modDownsamplerClass;
extern const UINT32 awe_modDownwardExpanderCoreClass;
extern const UINT32 awe_modDownwardExpanderCoreFract32Class;
extern const UINT32 awe_modDuckerClass;
extern const UINT32 awe_modDuckerFract32Class;
extern const UINT32 awe_modEmphasisFilterClass;
extern const UINT32 awe_modEmphasisFilterFract32Class;
extern const UINT32 awe_modFIRDecimatorClass;
extern const UINT32 awe_modFIRDecimatorFract32Class;
extern const UINT32 awe_modFIRInterpolatorClass;
extern const UINT32 awe_modFIRInterpolatorFract32Class;
extern const UINT32 awe_modFIRLoadingClass;
extern const UINT32 awe_modFIRLoadingFract32Class;
extern const UINT32 awe_modFIRSparseClass;
extern const UINT32 awe_modFIRSparseReaderClass;
extern const UINT32 awe_modFIRSparseReaderFract16Class;
extern const UINT32 awe_modFIRSparseReaderFract32Class;
extern const UINT32 awe_modFOFControlClass;
extern const UINT32 awe_modFOFControlFract32Class;
extern const UINT32 awe_modFftClass;
extern const UINT32 awe_modFftFract32Class;
extern const UINT32 awe_modFifoInClass;
extern const UINT32 awe_modFifoOutClass;
extern const UINT32 awe_modFractionalDelayFract32Class;
extern const UINT32 awe_modGetWirePropertiesClass;
extern const UINT32 awe_modGraphicEQBandHPClass;
extern const UINT32 awe_modGraphicEQBandHpFract32Class;
extern const UINT32 awe_modHistogramClass;
extern const UINT32 awe_modHysteresisClass;
extern const UINT32 awe_modIfftClass;
extern const UINT32 awe_modIfftFract32Class;
extern const UINT32 awe_modIntegralClass;
extern const UINT32 awe_modInterleavedSinkClass;
extern const UINT32 awe_modInvertNClass;
extern const UINT32 awe_modLMSClass;
extern const UINT32 awe_modLMSNormFract32Class;
extern const UINT32 awe_modLPF1ControlClass;
extern const UINT32 awe_modMapperControlClass;
extern const UINT32 awe_modMathExceptionClass;
extern const UINT32 awe_modMeasurementClass;
extern const UINT32 awe_modMeasurementV2Class;
extern const UINT32 awe_modMemoryLoadingClass;
extern const UINT32 awe_modMovingAverageFract32Class;
extern const UINT32 awe_modMuteLinearFadeClass;
extern const UINT32 awe_modMuteSyncClass;
extern const UINT32 awe_modMuteSyncFract32Class;
extern const UINT32 awe_modOscillatorClass;
extern const UINT32 awe_modOverlapAddClass;
extern const UINT32 awe_modOverlapAddFract32Class;
extern const UINT32 awe_modOverwriteControlClass;
extern const UINT32 awe_modPDFClass;
extern const UINT32 awe_modPeriodicStreamingClass;
extern const UINT32 awe_modPolarToComplexClass;
extern const UINT32 awe_modPresetArrayHandlerClass;
extern const UINT32 awe_modPresetArrayHandlerV2Class;
extern const UINT32 awe_modProbeFract32Class;
extern const UINT32 awe_modRandiClass;
extern const UINT32 awe_modRandiFract32Class;
extern const UINT32 awe_modRealImagToComplexClass;
extern const UINT32 awe_modRealImagToComplexFract32Class;
extern const UINT32 awe_modRebufferClass;
extern const UINT32 awe_modRepWinOverlapClass;
extern const UINT32 awe_modRunningMinMaxClass;
extern const UINT32 awe_modRunningMinMaxFract32Class;
extern const UINT32 awe_modRunningStatisticsClass;
extern const UINT32 awe_modRunningStatisticsFract32Class;
extern const UINT32 awe_modRunningStatisticsNClass;
extern const UINT32 awe_modSOFCascadeHPClass;
extern const UINT32 awe_modSOFControlClass;
extern const UINT32 awe_modSOFControlFract32Class;
extern const UINT32 awe_modSOFControlHPClass;
extern const UINT32 awe_modSampleAndHoldClass;
extern const UINT32 awe_modSampleAndHoldInt32Class;
extern const UINT32 awe_modSampleMultiplexorControlClass;
extern const UINT32 awe_modSampleRateClass;
extern const UINT32 awe_modSampleStatisticsClass;
extern const UINT32 awe_modSampleStatisticsFract32Class;
extern const UINT32 awe_modSbAttackReleaseClass;
extern const UINT32 awe_modSbComplexFIRClass;
extern const UINT32 awe_modSbComplexFIRvlClass;
extern const UINT32 awe_modSbDerivativeClass;
extern const UINT32 awe_modSbNLMSClass;
extern const UINT32 awe_modSbNLMSV2Class;
extern const UINT32 awe_modSbRMSClass;
extern const UINT32 awe_modSbSOFClass;
extern const UINT32 awe_modSbSmoothClass;
extern const UINT32 awe_modSbSplitterClass;
extern const UINT32 awe_modSecondOrderFilterHPClass;
extern const UINT32 awe_modSetWirePropertiesClass;
extern const UINT32 awe_modShiftSamplesClass;
extern const UINT32 awe_modSlewRateLimiterClass;
extern const UINT32 awe_modStatusSetClass;
extern const UINT32 awe_modSubblockStatisticsClass;
extern const UINT32 awe_modSubblockStatisticsFract32Class;
extern const UINT32 awe_modSystemVariableClass;
extern const UINT32 awe_modTHDClass;
extern const UINT32 awe_modTableInterp2dClass;
extern const UINT32 awe_modTableLookupIntFloatClass;
extern const UINT32 awe_modTableLookupIntIntClass;
extern const UINT32 awe_modTableLookupLogXClass;
extern const UINT32 awe_modTimeOutClass;
extern const UINT32 awe_modTimeOutFract32Class;
extern const UINT32 awe_modTriggeredPulseClass;
extern const UINT32 awe_modTriggeredPulseV2Class;
extern const UINT32 awe_modTriggeredSinkClass;
extern const UINT32 awe_modTwoPieceInterpV2Class;
extern const UINT32 awe_modUnwrapClass;
extern const UINT32 awe_modUpdateSampleRateClass;
extern const UINT32 awe_modUpsamplerClass;
extern const UINT32 awe_modVolumeControlHPClass;
extern const UINT32 awe_modWAVInterp16OneShotSourceFract32Class;
extern const UINT32 awe_modWAVInterpOneShotSourceClass;
extern const UINT32 awe_modWindowClass;
extern const UINT32 awe_modWindowAliasClass;
extern const UINT32 awe_modWindowAliasFract32Class;
extern const UINT32 awe_modWindowCustomClass;
extern const UINT32 awe_modWindowFract32Class;
extern const UINT32 awe_modWindowOverlapClass;
extern const UINT32 awe_modWindowOverlapFract32Class;
extern const UINT32 awe_modWindowV2Class;
extern const UINT32 awe_modZeroPaddingClass;
extern const UINT32 awe_modZeroPaddingFract32Class;


// Deprecated Modules
extern const UINT32 awe_modAGCMultiplierClass;
extern const UINT32 awe_modApplyPresetClass;
extern const UINT32 awe_modDCSourceClass;
extern const UINT32 awe_modDCSourceControlClass;
extern const UINT32 awe_modDCSourceControlFract32Class;
extern const UINT32 awe_modDCSourceFract32Class;
extern const UINT32 awe_modDeMultiplexorClass;
extern const UINT32 awe_modDelayciClass;
extern const UINT32 awe_modDelayiClass;
extern const UINT32 awe_modFileStreamingClass;
extern const UINT32 awe_modFloatToFract32Class;
extern const UINT32 awe_modFloatToIntClass;
extern const UINT32 awe_modFract32ToFloatClass;
extern const UINT32 awe_modFract32ToIntClass;
extern const UINT32 awe_modImpulseSourceClass;
extern const UINT32 awe_modIntToFloatClass;
extern const UINT32 awe_modIntToFract32Class;
extern const UINT32 awe_modMatlabStreamingClass;
extern const UINT32 awe_modMixerClass;
extern const UINT32 awe_modMixerDenseClass;
extern const UINT32 awe_modMixerSmoothedClass;
extern const UINT32 awe_modMixerSmoothedV2bClass;
extern const UINT32 awe_modMixerSparseSmoothedClass;
extern const UINT32 awe_modMultiplexorControlClass;
extern const UINT32 awe_modMultiplexorFadeClass;
extern const UINT32 awe_modMultiplexorFadeFract32Class;
extern const UINT32 awe_modMultiplexorSmoothedClass;
extern const UINT32 awe_modMultiplexorSmoothedFract32Class;
extern const UINT32 awe_modMultiplierClass;
extern const UINT32 awe_modProbeClass;
extern const UINT32 awe_modRawStreamingSourceClass;
extern const UINT32 awe_modSawtoothClass;
extern const UINT32 awe_modScalerClass;
extern const UINT32 awe_modScalerDBClass;
extern const UINT32 awe_modScalerDBSmoothedClass;
extern const UINT32 awe_modScalerNClass;
extern const UINT32 awe_modScalerNDBSmoothedClass;
extern const UINT32 awe_modScalerNSmoothedClass;
extern const UINT32 awe_modScalerSmoothedClass;
extern const UINT32 awe_modSineGenClass;
extern const UINT32 awe_modTableInterpRuntimeClass;
extern const UINT32 awe_modTwoPieceInterpClass;


// Additional Modules
extern const UINT32 awe_modSbAECResetClass;
extern const UINT32 awe_modSbAECV1Class;
extern const UINT32 awe_modSbAECV2Class;
extern const UINT32 awe_modSbAECV3Class;
extern const UINT32 awe_modSbStereoAECV1Class;
extern const UINT32 awe_modSbStereoAECV2Class;
extern const UINT32 awe_modSbMultiAECV1Class;
extern const UINT32 awe_modSbBeamformerClass;
extern const UINT32 awe_modSbBeamformerV2Class;
extern const UINT32 awe_modQSDv1Class;
extern const UINT32 awe_modSCNRv1Class;
extern const UINT32 awe_modSCNRv2Class;
extern const UINT32 awe_modSb2micICv1Class;



// Edit this list to prune modules from target
#define STANDARD_LIST \
&awe_modAGCCoreClass, \
&awe_modAGCLimiterCoreClass, \
&awe_modAGCLimiterCoreFract32Class, \
&awe_modAGCMultiplierFract32Class, \
&awe_modAGCNoiseGateCoreClass, \
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
&awe_modGPIOClass, \
&awe_modGraphicEQBandClass, \
&awe_modGraphicEQBandFract32Class, \
&awe_modImpulseMsecSourceClass, \
&awe_modImpulseMsecSourceFract32Class, \
&awe_modImpulseSourceFract32Class, \
&awe_modIntToBitsClass, \
&awe_modInterleaveClass, \
&awe_modInvertClass, \
&awe_modInvertFract32Class, \
&awe_modLShiftFract32Class, \
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
&awe_modNullSinkV2Class, \
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
&awe_modRMSNClass, \
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
&awe_modScalerNControlClass, \
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
&awe_modSinkFract32PropertiesClass, \
&awe_modSinkIntClass, \
&awe_modSinkIntPropertiesClass, \
&awe_modSinkPropertiesClass, \
&awe_modSofV2HpFract32Class, \
&awe_modSoftClipClass, \
&awe_modSoftClipFract32Class, \
&awe_modSoloMuteClass, \
&awe_modSoloMuteFract32Class, \
&awe_modSourceClass, \
&awe_modSourceFract32Class, \
&awe_modSourceFract32PropertiesClass, \
&awe_modSourceIntClass, \
&awe_modSourceIntPropertiesClass, \
&awe_modSourcePropertiesClass, \
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
&awe_modTableLookupV2Class, \
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
&awe_modZeroSourceClass

#define ADVANCED_LIST \
&awe_modAGCAttackReleaseClass, \
&awe_modAGCAttackReleaseFract32Class, \
&awe_modAGCCompressorCoreClass, \
&awe_modAGCCompressorCoreFract32Class, \
&awe_modAGCCoreFract32Class, \
&awe_modAGCVariableAttackReleaseClass, \
&awe_modAllpassDelayClass, \
&awe_modAllpassDelay16Class, \
&awe_modAllpassDelay16Fract32Class, \
&awe_modAllpassDelayFract32Class, \
&awe_modAllpassDelayciClass, \
&awe_modAllpassDelayiClass, \
&awe_modAttackDecaySustainReleaseClass, \
&awe_modAudioWeightingClass, \
&awe_modAudioWeightingFract32Class, \
&awe_modAveragerClass, \
&awe_modAveragerFract32Class, \
&awe_modBiquadCascadeHPClass, \
&awe_modBiquadLoadingClass, \
&awe_modBiquadLoadingFract32Class, \
&awe_modBiquadSmoothedHPClass, \
&awe_modBiquadSparseClass, \
&awe_modBlockConcatenateClass, \
&awe_modBlockDelayClass, \
&awe_modBlockDelayV2Class, \
&awe_modBlockExtractClass, \
&awe_modBlockFlipClass, \
&awe_modBlockMedianClass, \
&awe_modBlockStatisticsClass, \
&awe_modBlockStatisticsFract32Class, \
&awe_modBlockStatisticsNClass, \
&awe_modButterworthFilterHPClass, \
&awe_modCfftClass, \
&awe_modCfftFract32Class, \
&awe_modCoeffTableClass, \
&awe_modComplexAngleClass, \
&awe_modComplexConjugateClass, \
&awe_modComplexMagnitudeClass, \
&awe_modComplexMagnitudeFract32Class, \
&awe_modComplexMagnitudeSquaredClass, \
&awe_modComplexModulateClass, \
&awe_modComplexMultiplierClass, \
&awe_modComplexToPolarClass, \
&awe_modComplexToRealImagClass, \
&awe_modComplexToRealImagFract32Class, \
&awe_modConsecutiveCountIntClass, \
&awe_modConvolveClass, \
&awe_modCorrelateClass, \
&awe_modCorrelationFract32Class, \
&awe_modCycleBurnerClass, \
&awe_modCycleBurnerSetClass, \
&awe_modDateTimeClass, \
&awe_modDeadBandClass, \
&awe_modDelay16Class, \
&awe_modDelayInterpClass, \
&awe_modDelayInterpFract32Class, \
&awe_modDelayNChanClass, \
&awe_modDelayNChanMsecClass, \
&awe_modDelayNChanV2Class, \
&awe_modDelayNTapClass, \
&awe_modDelayNTap16Fract32Class, \
&awe_modDelayReaderClass, \
&awe_modDelayStateWriterClass, \
&awe_modDelayStateWriter16Class, \
&awe_modDelayciFract32Class, \
&awe_modDerivativeClass, \
&awe_modDerivativeFract32Class, \
&awe_modDitherFract32Class, \
&awe_modDownsamplerClass, \
&awe_modDownwardExpanderCoreClass, \
&awe_modDownwardExpanderCoreFract32Class, \
&awe_modDuckerClass, \
&awe_modDuckerFract32Class, \
&awe_modEmphasisFilterClass, \
&awe_modEmphasisFilterFract32Class, \
&awe_modFIRDecimatorClass, \
&awe_modFIRDecimatorFract32Class, \
&awe_modFIRInterpolatorClass, \
&awe_modFIRInterpolatorFract32Class, \
&awe_modFIRLoadingClass, \
&awe_modFIRLoadingFract32Class, \
&awe_modFIRSparseClass, \
&awe_modFIRSparseReaderClass, \
&awe_modFIRSparseReaderFract16Class, \
&awe_modFIRSparseReaderFract32Class, \
&awe_modFOFControlClass, \
&awe_modFOFControlFract32Class, \
&awe_modFftClass, \
&awe_modFftFract32Class, \
&awe_modFifoInClass, \
&awe_modFifoOutClass, \
&awe_modFractionalDelayFract32Class, \
&awe_modGetWirePropertiesClass, \
&awe_modGraphicEQBandHPClass, \
&awe_modGraphicEQBandHpFract32Class, \
&awe_modHistogramClass, \
&awe_modHysteresisClass, \
&awe_modIfftClass, \
&awe_modIfftFract32Class, \
&awe_modIntegralClass, \
&awe_modInterleavedSinkClass, \
&awe_modInvertNClass, \
&awe_modLMSClass, \
&awe_modLMSNormFract32Class, \
&awe_modLPF1ControlClass, \
&awe_modMapperControlClass, \
&awe_modMathExceptionClass, \
&awe_modMeasurementClass, \
&awe_modMeasurementV2Class, \
&awe_modMemoryLoadingClass, \
&awe_modMovingAverageFract32Class, \
&awe_modMuteLinearFadeClass, \
&awe_modMuteSyncClass, \
&awe_modMuteSyncFract32Class, \
&awe_modOscillatorClass, \
&awe_modOverlapAddClass, \
&awe_modOverlapAddFract32Class, \
&awe_modOverwriteControlClass, \
&awe_modPDFClass, \
&awe_modPeriodicStreamingClass, \
&awe_modPolarToComplexClass, \
&awe_modPresetArrayHandlerClass, \
&awe_modPresetArrayHandlerV2Class, \
&awe_modProbeFract32Class, \
&awe_modRandiClass, \
&awe_modRandiFract32Class, \
&awe_modRealImagToComplexClass, \
&awe_modRealImagToComplexFract32Class, \
&awe_modRebufferClass, \
&awe_modRepWinOverlapClass, \
&awe_modRunningMinMaxClass, \
&awe_modRunningMinMaxFract32Class, \
&awe_modRunningStatisticsClass, \
&awe_modRunningStatisticsFract32Class, \
&awe_modRunningStatisticsNClass, \
&awe_modSOFCascadeHPClass, \
&awe_modSOFControlClass, \
&awe_modSOFControlFract32Class, \
&awe_modSOFControlHPClass, \
&awe_modSampleAndHoldClass, \
&awe_modSampleAndHoldInt32Class, \
&awe_modSampleMultiplexorControlClass, \
&awe_modSampleRateClass, \
&awe_modSampleStatisticsClass, \
&awe_modSampleStatisticsFract32Class, \
&awe_modSbAttackReleaseClass, \
&awe_modSbComplexFIRClass, \
&awe_modSbComplexFIRvlClass, \
&awe_modSbDerivativeClass, \
&awe_modSbNLMSClass, \
&awe_modSbNLMSV2Class, \
&awe_modSbRMSClass, \
&awe_modSbSOFClass, \
&awe_modSbSmoothClass, \
&awe_modSbSplitterClass, \
&awe_modSecondOrderFilterHPClass, \
&awe_modSetWirePropertiesClass, \
&awe_modShiftSamplesClass, \
&awe_modSlewRateLimiterClass, \
&awe_modStatusSetClass, \
&awe_modSubblockStatisticsClass, \
&awe_modSubblockStatisticsFract32Class, \
&awe_modSystemVariableClass, \
&awe_modTHDClass, \
&awe_modTableInterp2dClass, \
&awe_modTableLookupIntFloatClass, \
&awe_modTableLookupIntIntClass, \
&awe_modTableLookupLogXClass, \
&awe_modTimeOutClass, \
&awe_modTimeOutFract32Class, \
&awe_modTriggeredPulseClass, \
&awe_modTriggeredPulseV2Class, \
&awe_modTriggeredSinkClass, \
&awe_modTwoPieceInterpV2Class, \
&awe_modUnwrapClass, \
&awe_modUpdateSampleRateClass, \
&awe_modUpsamplerClass, \
&awe_modVolumeControlHPClass, \
&awe_modWAVInterp16OneShotSourceFract32Class, \
&awe_modWAVInterpOneShotSourceClass, \
&awe_modWindowClass, \
&awe_modWindowAliasClass, \
&awe_modWindowAliasFract32Class, \
&awe_modWindowCustomClass, \
&awe_modWindowFract32Class, \
&awe_modWindowOverlapClass, \
&awe_modWindowOverlapFract32Class, \
&awe_modWindowV2Class, \
&awe_modZeroPaddingClass, \
&awe_modZeroPaddingFract32Class

#define DEPRECATED_LIST \
&awe_modAGCMultiplierClass, \
&awe_modApplyPresetClass, \
&awe_modDCSourceClass, \
&awe_modDCSourceControlClass, \
&awe_modDCSourceControlFract32Class, \
&awe_modDCSourceFract32Class, \
&awe_modDeMultiplexorClass, \
&awe_modDelayciClass, \
&awe_modDelayiClass, \
&awe_modFileStreamingClass, \
&awe_modFloatToFract32Class, \
&awe_modFloatToIntClass, \
&awe_modFract32ToFloatClass, \
&awe_modFract32ToIntClass, \
&awe_modImpulseSourceClass, \
&awe_modIntToFloatClass, \
&awe_modIntToFract32Class, \
&awe_modMatlabStreamingClass, \
&awe_modMixerClass, \
&awe_modMixerDenseClass, \
&awe_modMixerSmoothedClass, \
&awe_modMixerSmoothedV2bClass, \
&awe_modMixerSparseSmoothedClass, \
&awe_modMultiplexorControlClass, \
&awe_modMultiplexorFadeClass, \
&awe_modMultiplexorFadeFract32Class, \
&awe_modMultiplexorSmoothedClass, \
&awe_modMultiplexorSmoothedFract32Class, \
&awe_modMultiplierClass, \
&awe_modProbeClass, \
&awe_modRawStreamingSourceClass, \
&awe_modSawtoothClass, \
&awe_modScalerClass, \
&awe_modScalerDBClass, \
&awe_modScalerDBSmoothedClass, \
&awe_modScalerNClass, \
&awe_modScalerNDBSmoothedClass, \
&awe_modScalerNSmoothedClass, \
&awe_modScalerSmoothedClass, \
&awe_modSineGenClass, \
&awe_modTableInterpRuntimeClass, \
&awe_modTwoPieceInterpClass

#define CUSTOM_LIST \
&awe_modSbAECResetClass, \
&awe_modSbAECV1Class, \
&awe_modSbAECV2Class, \
&awe_modSbAECV3Class, \
&awe_modSbStereoAECV1Class, \
&awe_modSbStereoAECV2Class, \
&awe_modSbMultiAECV1Class, \
&awe_modSbBeamformerClass, \
&awe_modSbBeamformerV2Class, \
&awe_modQSDv1Class, \
&awe_modSCNRv1Class, \
&awe_modSCNRv2Class, \
&awe_modSb2micICv1Class


#define LISTOFCLASSOBJECTS \
STANDARD_LIST, \
ADVANCED_LIST, \
DEPRECATED_LIST, \
CUSTOM_LIST



#ifdef	__cplusplus
}
#endif

#endif	// _MODULELIST_H
