################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./opus_playaudio_opx.obj" \
"./startup_ccs.obj" \
"./utils/ustdlib.obj" \
"./third_party/fatfs/src/ff.obj" \
"./third_party/fatfs/port/mmc-dk-tm4c129x.obj" \
"./opxcode/opxfile.obj" \
"./opxcode/pinout.obj" \
"./drivers/buttons.obj" \
"./drivers/frame.obj" \
"./drivers/kentec320x240x16_ssd2119.obj" \
"./drivers/touch.obj" \
"../tm4c129xnczad.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"C:\Users\a0876236\workspace_spma076\opuslib\Debug\opuslib.lib" \
-l"D:\ti\TivaWare_C_Series-2.1.2.111\driverlib\ccs\Debug\driverlib.lib" \
-l"D:\ti\TivaWare_C_Series-2.1.2.111\grlib\ccs\Debug\grlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include utils/subdir_vars.mk
-include third_party/fatfs/src/subdir_vars.mk
-include third_party/fatfs/port/subdir_vars.mk
-include opxcode/subdir_vars.mk
-include drivers/subdir_vars.mk
-include subdir_rules.mk
-include utils/subdir_rules.mk
-include third_party/fatfs/src/subdir_rules.mk
-include third_party/fatfs/port/subdir_rules.mk
-include opxcode/subdir_rules.mk
-include drivers/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
opus_playaudio_opx.out \

EXE_OUTPUTS__QUOTED += \
"opus_playaudio_opx.out" \

BIN_OUTPUTS += \
opus_playaudio_opx.bin \

BIN_OUTPUTS__QUOTED += \
"opus_playaudio_opx.bin" \


# All Target
all: opus_playaudio_opx.out

# Tool invocations
opus_playaudio_opx.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 -g --gcc --define=ccs="ccs" --define=PART_TM4C129XNCZAD --define=TARGET_IS_TM4C129_RA0 --define=VAR_ARRAYS --define=FIXED_POINT --define=OPUS_BUILD --diag_warning=225 --display_error_number --diag_wrap=off -z -m"opus_playaudio_opx.map" --heap_size=131072 --stack_size=8192 -i"D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/lib" -i"D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --reread_libs --warn_sections --diag_wrap=off --display_error_number --xml_link_info="opus_playaudio_opx_linkInfo.xml" --rom_model -o "opus_playaudio_opx.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

opus_playaudio_opx.bin: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armhex"  -o "opus_playaudio_opx.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "opus_playaudio_opx.pp" "startup_ccs.pp" "utils\ustdlib.pp" "third_party\fatfs\src\ff.pp" "third_party\fatfs\port\mmc-dk-tm4c129x.pp" "opxcode\opxfile.pp" "opxcode\pinout.pp" "drivers\buttons.pp" "drivers\frame.pp" "drivers\kentec320x240x16_ssd2119.pp" "drivers\touch.pp" 
	-$(RM) "opus_playaudio_opx.obj" "startup_ccs.obj" "utils\ustdlib.obj" "third_party\fatfs\src\ff.obj" "third_party\fatfs\port\mmc-dk-tm4c129x.obj" "opxcode\opxfile.obj" "opxcode\pinout.obj" "drivers\buttons.obj" "drivers\frame.obj" "drivers\kentec320x240x16_ssd2119.obj" "drivers\touch.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-"D:/ti/ccsv6/utils/tiobj2bin/tiobj2bin" "opus_playaudio_opx.out" "opus_playaudio_opx.bin" "D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armofd" "D:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armhex" "D:/ti/ccsv6/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

