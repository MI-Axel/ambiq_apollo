#******************************************************************************
#
# Makefile - Rules for building the libraries, examples and docs.
#
# Copyright (c) 2018, Ambiq Micro
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
# 
# 3. Neither the name of the copyright holder nor the names of its
# contributors may be used to endorse or promote products derived from this
# software without specific prior written permission.
# 
# Third party software included in this distribution is subject to the
# additional license terms as defined in the /docs/licenses directory.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# This is part of revision v1.2.12-830-g39ebe7dbe of the AmbiqSuite Development Package.
#
#******************************************************************************
TARGET := rtos_audio_experiment_platform
COMPILERNAME := gcc
PROJECT := rtos_audio_experiment_platform_gcc
CONFIG := bin
#AM_SoftwareRoot ?= ../../../device/Apollo3-SDK-2018.08.13
AM_SoftwareRoot ?= ../../../device/AmbiqSuite-Rel2.2.0
AM_FolderRoot ?= ../../..
AM_OpusRoot ?= ../../../tools/opus/opus-1.2.1

SHELL:=/bin/bash
#### Setup ####

TOOLCHAIN ?= arm-none-eabi
PART = apollo3
CPU = cortex-m4
FPU = fpv4-sp-d16
FABI = hard

LINKER_FILE := ./rtos_audio_experiment_platform.ld
STARTUP_FILE := ./startup_$(COMPILERNAME).c

#### Required Executables ####
CC = $(TOOLCHAIN)-gcc
GCC = $(TOOLCHAIN)-gcc
CPP = $(TOOLCHAIN)-cpp
LD = $(TOOLCHAIN)-ld
CP = $(TOOLCHAIN)-objcopy
OD = $(TOOLCHAIN)-objdump
RD = $(TOOLCHAIN)-readelf
AR = $(TOOLCHAIN)-ar
SIZE = $(TOOLCHAIN)-size
RM = $(shell which rm 2>/dev/null)

EXECUTABLES = CC LD CP OD AR RD SIZE GCC
K := $(foreach exec,$(EXECUTABLES),\
        $(if $(shell which $($(exec)) 2>/dev/null),,\
        $(info $(exec) not found on PATH ($($(exec))).)$(exec)))
$(if $(strip $(value K)),$(info Required Program(s) $(strip $(value K)) not found))

ifneq ($(strip $(value K)),)
all clean:
	$(info Tools $(TOOLCHAIN)-$(COMPILERNAME) not installed.)
	$(RM) -rf bin
else
#################### OPUS PART #######################

# Uncomment this for fixed-point build
#FIXED_POINT=1

# It is strongly recommended to uncomment one of these
# VAR_ARRAYS: Use C99 variable-length arrays for stack allocation
# USE_ALLOCA: Use alloca() for stack allocation
# If none is defined, then the fallback is a non-threadsafe global array
#EXTRA_CFLAGS := -DUSE_ALLOCA $(EXTRA_CFLAGS)
#EXTRA_CFLAGS := -DVAR_ARRAYS $(EXTRA_CFLAGS)

# These options affect performance
# HAVE_LRINTF: Use C99 intrinsics to speed up float-to-int conversion
#EXTRA_CFLAGS := -DHAVE_LRINTF $(EXTRA_CFLAGS)

include ${AM_OpusRoot}/silk_sources.mk
include ${AM_OpusRoot}/celt_sources.mk
include ${AM_OpusRoot}/opus_sources.mk

#ifdef FIXED_POINT
SILK_SOURCES += $(SILK_SOURCES_FIXED)
#else
#SILK_SOURCES += $(SILK_SOURCES_FLOAT)
OPUS_SOURCES += $(OPUS_SOURCES_FLOAT)
#endif

###################### END OF OPUS PART ######################

#################### APPLICATION UTILS PART #######################
include ${AM_FolderRoot}/app_utils/am_app_utils_rtos.mk

###################### END OF APPLICATION UTILS PART ######################


#################### SEGGER TOOLS PART #######################
include ${AM_FolderRoot}/tools/segger/SEGGER_SYSVIEW_FreeRTOS.mk
###################### END OF SEGGER TOOLS PART ######################


DEFINES = -DPART_$(PART)
DEFINES += -DAM_PACKAGE_BGA
DEFINES += -DAM_PART_APOLLO3
DEFINES += -DARM_MATH_CM4
DEFINES += -DAM_FREERTOS
DEFINES+= -DAM_CUSTOM_BDADDR
DEFINES+= -DAM_DEBUG_PRINTF
DEFINES+= -DWSF_TRACE_ENABLED

# opus pre-definition
DEFINES += -DHAVE_CONFIG_H
DEFINES += -DCUSTOM_SUPPORT

INCLUDES = -I../src
INCLUDES += -I../include
INCLUDES += -I${AM_FolderRoot}/app_utils
INCLUDES += -I${AM_SoftwareRoot}/boards/apollo3_evb/bsp
INCLUDES += -I${AM_SoftwareRoot}/mcu/apollo3
INCLUDES += -I${AM_SoftwareRoot}/CMSIS/ARM/Include
INCLUDES += -I${AM_SoftwareRoot}/CMSIS/AmbiqMicro/Include
INCLUDES += -I${AM_SoftwareRoot}/devices
INCLUDES += -I${AM_SoftwareRoot}/utils
INCLUDES += -I${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/portable/GCC/AMapollo2
INCLUDES += -I${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/include


# SEGGER tools include
INCLUDES += ${SEGGER_SYSVIEW_INC}
# OPUS INCLUDES
INCLUDES += -I${AM_OpusRoot}/include
INCLUDES += -I${AM_OpusRoot}/src
INCLUDES += -I${AM_OpusRoot}/celt
INCLUDES += -I${AM_OpusRoot}/celt/arm
INCLUDES += -I${AM_OpusRoot}/silk
INCLUDES += -I${AM_OpusRoot}/silk/arm
INCLUDES += -I${AM_OpusRoot}/silk/fixed
INCLUDES += -I${AM_OpusRoot}

# Platform folder
VPATH = ${AM_SoftwareRoot}/utils
VPATH +=:${AM_SoftwareRoot}/devices
VPATH +=:${AM_SoftwareRoot}/mcu/apollo3/hal
VPATH +=:${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/portable/GCC/AMapollo2
VPATH +=:${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/portable/MemMang
VPATH +=:${AM_SoftwareRoot}/third_party/FreeRTOS9/Source

VPATH +=:${AM_FolderRoot}/app_utils
VPATH +=:../src
# SEGGER tools VPATH
VPATH +=:${SEGGER_SYSVIEW_VPATH}

# OPUS FOLDERS
VPATH +=:${AM_OpusRoot}/src
VPATH +=:${AM_OpusRoot}/silk
VPATH +=:${AM_OpusRoot}/celt
VPATH +=:${AM_OpusRoot}/silk/arm
VPATH +=:${AM_OpusRoot}/celt/arm
VPATH +=:${AM_OpusRoot}/silk/fixed
VPATH +=:${AM_OpusRoot}/silk/float

# OPUS SOURCE FILES
OPUS_SRC = $(notdir $(SILK_SOURCES) $(CELT_SOURCES) $(OPUS_SOURCES) $(CELT_SOURCES_ARM))

SRC = main.c
# FreeRTOS files
SRC += event_groups.c
SRC += list.c
SRC += queue.c
SRC += tasks.c
SRC += timers.c
SRC += heap_4.c
SRC += port.c
# App utils files and board related files
SRC += am_hal_pdm.c
SRC += am_hal_gpio.c
SRC += am_util_delay.c
SRC += am_util_faultisr.c
SRC += am_util_stdio.c
SRC += ${AM_APP_UTILS_SRC}
SRC += am_devices_led.c
# Third party source files
SRC += ${SEGGER_SYSVIEW_SRC}
SRC += ${OPUS_SRC}

# User source files
SRC += rtos_AEP_hook.c
SRC += am_AEP_init.c
SRC += am_AEP_board_setup.c
SRC += am_AEP_task.c
SRC += am_AEP_isr_handler.c
SRC += am_opus.c
#SRC += am_opus_custom_support.c
# Start up file
SRC += startup_gcc.c

CSRC = $(filter %.c,$(SRC))
ASRC = $(filter %.s,$(SRC))

OBJS = $(CSRC:%.c=$(CONFIG)/%.o)
OBJS+= $(ASRC:%.s=$(CONFIG)/%.o)

DEPS = $(CSRC:%.c=$(CONFIG)/%.d)
DEPS+= $(ASRC:%.s=$(CONFIG)/%.d)

LIBS = ${AM_SoftwareRoot}/boards/apollo3_evb/bsp/gcc/bin/libam_bsp.a
LIBS += ${AM_SoftwareRoot}/mcu/apollo3/hal/gcc/bin/libam_hal.a

INCS = 
INCS += ${AM_SoftwareRoot}/mcu/apollo3/hal/am_hal_pin.h

CFLAGS = -mthumb -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FABI)
CFLAGS+= -ffunction-sections -fdata-sections
CFLAGS+= -MMD -MP -std=c99 -Wall -g
CFLAGS+= -Ofast
CFLAGS+= $(DEFINES)
CFLAGS+= $(INCLUDES)
CFLAGS+= -Dgcc

LFLAGS = -mthumb -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FABI)
LFLAGS+= -nostartfiles -static
LFLAGS+= -Wl,--gc-sections,--entry,Reset_Handler,-Map,$(CONFIG)/$(TARGET).map
LFLAGS+= -Wl,--start-group -lm -lc -lgcc -Wl,--end-group

# use libnosys.a to realize _sbrk for malloc, free. 
#LFLAGS+= -specs=nosys.specs

# Additional user specified CFLAGS
CFLAGS+=$(EXTRA_CFLAGS)

CPFLAGS = -Obinary

ODFLAGS = -S

#### Rules ####
all: directories $(CONFIG)/$(TARGET).bin

directories: $(CONFIG)

$(CONFIG):
	@mkdir -p $@

$(CONFIG)/%.o: %.c $(CONFIG)/%.d $(INCS)
	@echo " Compiling $(COMPILERNAME) $<" ;\
	$(CC) -c $(CFLAGS) $< -o $@

$(CONFIG)/%.o: %.s $(CONFIG)/%.d $(INCS)
	@echo " Assembling $(COMPILERNAME) $<" ;\
	$(CC) -c $(CFLAGS) $< -o $@


$(CONFIG)/$(TARGET).axf: $(OBJS) $(LIBS)
	@echo " Linking $(COMPILERNAME) $@" ;\
	$(CC) -Wl,-T,$(LINKER_FILE) -o $@ $(OBJS) $(LIBS) $(LFLAGS)

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

