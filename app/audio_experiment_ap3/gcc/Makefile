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
TARGET := audio_experiment
COMPILERNAME := gcc
PROJECT := audio_experiment_gcc
CONFIG := bin
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

LINKER_FILE := ./audio_experiment.ld
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

include ${AM_OpusRoot}/silk_sources.mk
include ${AM_OpusRoot}/celt_sources.mk
include ${AM_OpusRoot}/opus_sources.mk

SILK_SOURCES += $(SILK_SOURCES_FIXED)
OPUS_SOURCES += $(OPUS_SOURCES_FLOAT)

###################### END OF OPUS PART ######################

#################### APPLICATION UTILS PART #######################
include ${AM_FolderRoot}/app_utils/am_app_utils.mk

###################### END OF APPLICATION UTILS PART ######################


#################### SEGGER TOOLS PART #######################
include SEGGER_SYSVIEW.mk
###################### END OF SEGGER TOOLS PART ######################


DEFINES = -DPART_$(PART)
DEFINES += -DAM_PACKAGE_BGA
DEFINES += -DAM_PART_APOLLO3
DEFINES += -DARM_MATH_CM4
DEFINES += -D__FPU_PRESENT

# opus pre-definition
#DEFINES += -DHAVE_CONFIG_H
#DEFINES += -DCUSTOM_SUPPORT

INCLUDES = -I../src
INCLUDES += -I../include
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

# STFT INCLUDES
INCLUDES += -I../src/audio_preprocess

# Microphone calibration INCLUDES
INCLUDES += -I../src/mikro_cal

# Microphone THD calculator INCLUDES
INCLUDES += -I../src/mikro_thd
INCLUDES += -I../src/local_test_data

VPATH = ${AM_SoftwareRoot}/utils
VPATH +=:${AM_SoftwareRoot}/devices
VPATH +=:${AM_SoftwareRoot}/mcu/apollo3/hal
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

# STFT folders
VPATH +=:../src/audio_preprocess

# mikro calibration folder
VPATH +=:../src/mikro_cal

# mikro THD calculator folder
VPATH +=:../src/mikro_thd
VPATH +=:../src/local_test_data/

# OPUS SOURCE FILES
OPUS_SRC = $(notdir $(SILK_SOURCES) $(CELT_SOURCES) $(OPUS_SOURCES) $(CELT_SOURCES_ARM))

SRC = main.c
#SRC += am_hal_pdm.c
#SRC += am_hal_gpio.c
SRC += am_util_delay.c
SRC += am_util_faultisr.c
SRC += am_util_stdio.c
SRC += ${AM_APP_UTILS_SRC}
SRC += am_devices_led.c
SRC += startup_gcc.c
SRC += board_setup.c
SRC += audio_driver.c
# ring buffer test
#SRC += am_memcpy_ringbuff_test.c

# malloc and free test
#SRC += am_alloc_free_test.c

# OPUS code
#SRC += am_opus.c
#SRC += am_app_USP1602_mono_array.c
#SRC += ${OPUS_SRC}

# SEGGER sysview tool
SRC += ${SEGGER_SYSVIEW_SRC}

# STFT test code 
SRC += stft.c
SRC += am_AEP_local_test_data.c
SRC += hanning_window.c
SRC += digital_filter.c
# Mikro calibration code
#SRC += am_mikro_calibration.c

# Mikro THD calculator
#SRC += am_mikro_thd.c

CSRC = $(filter %.c,$(SRC))
ASRC = $(filter %.s,$(SRC))

OBJS = $(CSRC:%.c=$(CONFIG)/%.o)
OBJS+= $(ASRC:%.s=$(CONFIG)/%.o)

DEPS = $(CSRC:%.c=$(CONFIG)/%.d)
DEPS+= $(ASRC:%.s=$(CONFIG)/%.d)

LIBS = ${AM_SoftwareRoot}/boards/apollo3_evb/bsp/gcc/bin/libam_bsp.a
LIBS += ${AM_SoftwareRoot}/mcu/apollo3/hal/gcc/bin/libam_hal.a
LIBS += ${AM_FolderRoot}/math/CMSIS_5/Lib/gcc/libarm_cortexM4lf_math.a

INCS = 
INCS += ${AM_SoftwareRoot}/mcu/apollo3/hal/am_hal_pin.h

CFLAGS = -mthumb -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FABI)
CFLAGS+= -ffunction-sections -fdata-sections
CFLAGS+= -MMD -MP -std=c99 -Wall -g
CFLAGS+= -O0
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

