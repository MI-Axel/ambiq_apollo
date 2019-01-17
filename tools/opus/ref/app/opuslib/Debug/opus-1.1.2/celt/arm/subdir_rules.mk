################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
opus-1.1.2/celt/arm/arm_celt_map.obj: D:/ti/examples/OPUS/opus-1.1.2/celt/arm/arm_celt_map.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="D:/ti/examples/OPUS/opus-1.1.2" --include_path="D:/ti/examples/OPUS/opus-1.1.2/include" --include_path="D:/ti/examples/OPUS/opus-1.1.2/celt" --include_path="D:/ti/examples/OPUS/opus-1.1.2/celt/arm" --include_path="D:/ti/examples/OPUS/opus-1.1.2/silk" --include_path="D:/ti/examples/OPUS/opus-1.1.2/silk/arm" --include_path="D:/ti/examples/OPUS/opus-1.1.2/silk/fixed" --include_path="D:/ti/examples/OPUS/opus-1.1.2/src" -g --gcc --define=ccs="ccs" --define=PART_TM4C129XNCZAD --define=VAR_ARRAYS --define=OPUS_BUILD --define=FIXED_POINT --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="opus-1.1.2/celt/arm/arm_celt_map.pp" --obj_directory="opus-1.1.2/celt/arm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

opus-1.1.2/celt/arm/armcpu.obj: D:/ti/examples/OPUS/opus-1.1.2/celt/arm/armcpu.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="D:/ti/examples/OPUS/opus-1.1.2" --include_path="D:/ti/examples/OPUS/opus-1.1.2/include" --include_path="D:/ti/examples/OPUS/opus-1.1.2/celt" --include_path="D:/ti/examples/OPUS/opus-1.1.2/celt/arm" --include_path="D:/ti/examples/OPUS/opus-1.1.2/silk" --include_path="D:/ti/examples/OPUS/opus-1.1.2/silk/arm" --include_path="D:/ti/examples/OPUS/opus-1.1.2/silk/fixed" --include_path="D:/ti/examples/OPUS/opus-1.1.2/src" -g --gcc --define=ccs="ccs" --define=PART_TM4C129XNCZAD --define=VAR_ARRAYS --define=OPUS_BUILD --define=FIXED_POINT --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="opus-1.1.2/celt/arm/armcpu.pp" --obj_directory="opus-1.1.2/celt/arm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


