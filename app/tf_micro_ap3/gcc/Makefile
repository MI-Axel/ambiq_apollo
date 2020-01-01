TARGET := tflite_ap3
COMPILERNAME := gcc
CXXCOMPILERNAME := g++
PROJECT := tf_micro_ap3
CONFIG := bin
AM_SoftwareRoot ?= ../../../device/AmbiqSuite-Rel2.2.0
AM_FolderRoot ?= ../../..
AM_APP_LIB ?= ../../../app_lib

SHELL:=/bin/bash
#### Setup ####

TOOLCHAIN ?= arm-none-eabi
PART = apollo3
CPU = cortex-m4
FPU = fpv4-sp-d16
FABI = hard

LINKER_FILE := ./tflite_ap3.ld
STARTUP_FILE := ./startup_$(COMPILERNAME).c

#### Required Executables ####
CC = $(TOOLCHAIN)-gcc
CXX = $(TOOLCHAIN)-g++
GCC = $(TOOLCHAIN)-gcc
CPP = $(TOOLCHAIN)-cpp
LD = $(TOOLCHAIN)-ld
CP = $(TOOLCHAIN)-objcopy
OD = $(TOOLCHAIN)-objdump
RD = $(TOOLCHAIN)-readelf
AR = $(TOOLCHAIN)-ar
SIZE = $(TOOLCHAIN)-size
RM = $(shell which rm 2>/dev/null)

EXECUTABLES = CC CXX LD CP OD AR RD SIZE GCC
K := $(foreach exec,$(EXECUTABLES),\
        $(if $(shell which $($(exec)) 2>/dev/null),,\
        $(info $(exec) not found on PATH ($($(exec))).)$(exec)))
$(if $(strip $(value K)),$(info Required Program(s) $(strip $(value K)) not found))

ifneq ($(strip $(value K)),)
all clean:
	$(info Tools $(TOOLCHAIN)-$(COMPILERNAME) not installed.)
	$(RM) -rf bin
else
#################### APPLICATION UTILS PART #######################
include ${AM_FolderRoot}/app_utils/am_app_utils.mk
###################### END OF APPLICATION UTILS PART ######################

#################### SEGGER TOOLS PART #######################
#include SEGGER_SYSVIEW.mk
###################### END OF SEGGER TOOLS PART ######################

#################### AMBIQ AUDIO PREPROCESS LIB #######################
include ${AM_APP_LIB}/audio_preprocess/am_audio_preprocess.mk
###################### END OF AMBIQ AUDIO PREPROCESS LIB ######################


DEFINES = -DPART_$(PART)
DEFINES += -DAM_PACKAGE_BGA
DEFINES += -DAM_PART_APOLLO3
DEFINES += -DARM_MATH_CM4
DEFINES += -D__FPU_PRESENT
DEFINES += -DTF_LITE_STATIC_MEMORY
DEFINES += -DTF_LITE_DISABLE_X86_NEON

INCLUDES = -I../src
INCLUDES += -I../src/third_party/gemmlowp
INCLUDES += -I../src/third_party/flatbuffers/include
INCLUDES += -I${AM_FolderRoot}/app_utils
INCLUDES += -I${AM_FolderRoot}/tools/segger/SEGGER_RTT_V640/RTT
INCLUDES += -I${AM_SoftwareRoot}/boards/apollo3_evb/bsp
INCLUDES += -I${AM_SoftwareRoot}/mcu/apollo3
INCLUDES += -I${AM_SoftwareRoot}/CMSIS/ARM/Include
INCLUDES += -I${AM_SoftwareRoot}/CMSIS/AmbiqMicro/Include
INCLUDES += -I${AM_SoftwareRoot}/devices
INCLUDES += -I${AM_SoftwareRoot}/utils

# ARM math lib includes
INCLUDES += -I${AM_FolderRoot}/math/CMSIS_5/Include

# SEGGER tools include
#INCLUDES += ${SEGGER_SYSVIEW_INC}

VPATH = ${AM_SoftwareRoot}/utils
VPATH +=:${AM_SoftwareRoot}/devices
VPATH +=:${AM_SoftwareRoot}/mcu/apollo3/hal
VPATH +=:${AM_FolderRoot}/app_utils
VPATH +=:../src
VPATH +=:../src/tensorflow/lite/micro
VPATH +=:../src/tensorflow/lite/micro/kernels
VPATH +=:../src/tensorflow/lite/c
VPATH +=:../src/tensorflow/lite/kernels
VPATH +=:../src/tensorflow/lite/core/api
VPATH +=:../src/tensorflow/lite/kernels/internal
# SEGGER tools VPATH
VPATH +=:${SEGGER_SYSVIEW_VPATH}

SRCS := \
micro_error_reporter.cc \
micro_mutable_op_resolver.cc \
simple_memory_allocator.cc \
debug_log.cc \
debug_log_numbers.cc \
micro_interpreter.cc \
all_ops_resolver.cc \
c_api_experimental.c \
error_reporter.cc \
flatbuffer_conversions.cc\
op_resolver.cc \
kernel_util.cc \
depthwise_conv.cc \
softmax.cc \
micro_error_reporter_test.cc

SRCS += startup_gcc.c
SRCS += am_util_delay.c
SRCS += am_util_faultisr.c
SRCS += am_util_stdio.c
SRCS += am_devices_led.c
SRCS += am_board_setup.cc


OBJS := \
$(patsubst %.cc,$(CONFIG)/%.o,$(patsubst %.c,$(CONFIG)/%.o,$(SRCS)))

DEPS := \
$(patsubst %.cc,$(CONFIG)/%.d,$(patsubst %.c,$(CONFIG)/%.d,$(SRCS)))

LIBS = ${AM_SoftwareRoot}/boards/apollo3_evb/bsp/gcc/bin/libam_bsp.a
LIBS += ${AM_SoftwareRoot}/mcu/apollo3/hal/gcc/bin/libam_hal.a
LIBS += ${AM_FolderRoot}/math/libarm_cortexM4lf_math.a
PLATFORM_FLAGS = \
    -DPART_apollo3 \
    -DAM_PACKAGE_BGA \
    -DAM_PART_APOLLO3 \
    -DGEMMLOWP_ALLOW_SLOW_SCALAR_FALLBACK \
    -DTF_LITE_STATIC_MEMORY \
    -DNDEBUG \
    -DTF_LITE_MCU_DEBUG_LOG \
    -D __FPU_PRESENT=1 \
    -DARM_MATH_CM4 \
    -fno-rtti \
    -fmessage-length=0 \
    -fno-exceptions \
    -fno-unwind-tables \
    -fno-builtin \
    -ffunction-sections \
    -fdata-sections \
    -funsigned-char \
    -MMD \
    -mcpu=cortex-m4 \
    -mthumb \
    -mfpu=fpv4-sp-d16 \
    -mfloat-abi=hard \
    -std=gnu++11 \
    -Wvla \
    -Wall \
    -Wextra \
    -Wno-unused-parameter \
    -Wno-missing-field-initializers \
    -Wno-write-strings \
    -Wno-sign-compare \
    -fno-delete-null-pointer-checks \
    -fomit-frame-pointer \
    -fpermissive \
    -nostdlib \
    -ggdb \
    -O3

CXXFLAGS += $(PLATFORM_FLAGS)
CFLAGS += $(PLATFORM_FLAGS)
CFLAGS += $(INCLUDES)
CXXFLAGS += $(INCLUDES)


LDFLAGS += \
    -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
    -nostartfiles -static \
    -Wl,--gc-sections -Wl,--entry,Reset_Handler \
    -Wl,--start-group -lm -lc -lgcc -Wl,--end-group \
    -fno-exceptions \
    -nostdlib --specs=nano.specs -t -lstdc++ -lc -lnosys -lm \
    -Wl,-Map=$(CONFIG)/$(TARGET).map,--cref

# use libnosys.a to realize _sbrk for malloc, free. 
#LFLAGS+= -specs=nosys.specs

CPFLAGS = -Obinary

ODFLAGS = -S

#### Rules ####
all: directories $(CONFIG)/$(TARGET).bin

directories: $(CONFIG)

$(CONFIG):
	@mkdir -p $@

$(CONFIG)/%.o: %.cc $(CONFIG)/%.d $(INCS)
	@echo " Compiling $(CXXCOMPILERNAME) $<" ;\
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(CONFIG)/%.o: %.c $(CONFIG)/%.d $(INCS)
	@echo " Compiling $(COMPILERNAME) $<" ;\
	$(CC) -c $(CFLAGS) $< -o $@


$(CONFIG)/$(TARGET).axf: $(OBJS) $(LIBS)
	@echo " Linking $(COMPILERNAME) $@" ;\
	$(CXX) -Wl,-T,$(LINKER_FILE) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

$(CONFIG)/$(TARGET).bin: $(CONFIG)/$(TARGET).axf
	@echo " Copying $(COMPILERNAME) $@..." ;\
	$(CP) $(CPFLAGS) $< $@ ;\
	$(OD) $(ODFLAGS) $< > $(CONFIG)/$(TARGET).lst

clean:
	@echo "Cleaning..." ;\
	$(RM) -f $(OBJS) $(DEPS) \
	    $(CONFIG)/$(TARGET).bin $(CONFIG)/$(TARGET).axf \
	    $(CONFIG)/$(TARGET).lst $(CONFIG)/$(TARGET).map

$(CONFIG)/%.d: ;

debug:
	@echo "ASM files: ${ASRC}"

# Automatically include any generated dependencies
-include $(DEPS)
endif
.PHONY: all clean directories debug

