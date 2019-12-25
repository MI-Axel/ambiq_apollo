TARGET := opus_rtos_ap3
COMPILERNAME := gcc
PROJECT := opus_rtos_gcc
CONFIG := lib
AM_OpusRoot ?= ./opus-1.2.1
AM_OPUS_API ?= ./am_api
AM_SoftwareRoot ?= ../../device/AmbiqSuite-Rel2.2.0

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

# opus pre-definition
DEFINES += -DHAVE_CONFIG_H
DEFINES += -DCUSTOM_SUPPORT
# OPUS INCLUDES
INCLUDES += -I${AM_OpusRoot}/include
INCLUDES += -I${AM_OpusRoot}/src
INCLUDES += -I${AM_OpusRoot}/celt
INCLUDES += -I${AM_OpusRoot}/celt/arm
INCLUDES += -I${AM_OpusRoot}/silk
INCLUDES += -I${AM_OpusRoot}/silk/arm
INCLUDES += -I${AM_OpusRoot}/silk/fixed
INCLUDES += -I${AM_OpusRoot}
INCLUDES += -I${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/portable/GCC/AMapollo2
INCLUDES += -I${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/include

# ambiq interface
INCLUDES += -I${AM_OPUS_API}

# OPUS FOLDERS
VPATH +=:${AM_OpusRoot}/src
VPATH +=:${AM_OpusRoot}/silk
VPATH +=:${AM_OpusRoot}/celt
VPATH +=:${AM_OpusRoot}/silk/arm
VPATH +=:${AM_OpusRoot}/celt/arm
VPATH +=:${AM_OpusRoot}/silk/fixed
VPATH +=:${AM_OpusRoot}/silk/float

# ambiq interface
VPATH += ${AM_OPUS_API}

# OPUS SOURCE FILES
OPUS_SRC = $(notdir $(SILK_SOURCES) $(CELT_SOURCES) $(OPUS_SOURCES) $(CELT_SOURCES_ARM))

SRC = ${OPUS_SRC}

# add api from ambiq
SRC += am_opus.c

CSRC = $(filter %.c,$(SRC))
ASRC = $(filter %.s,$(SRC))

OBJS = $(CSRC:%.c=$(CONFIG)/%.o)
OBJS+= $(ASRC:%.s=$(CONFIG)/%.o)
DEPS = $(CSRC:%.c=$(CONFIG)/%.d)
DEPS+= $(ASRC:%.s=$(CONFIG)/%.d)

LIB = opus_ap3_lib.a

CFLAGS = -mthumb -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FABI)
CFLAGS+= -ffunction-sections -fdata-sections
CFLAGS+= -MMD -MP -std=c99 -Wall -g
CFLAGS+= -Ofast
CFLAGS+= $(DEFINES)
CFLAGS+= $(INCLUDES)
CFLAGS+= -Dgcc

#### Rules ####
all: directories $(CONFIG)/$(LIB)

directories: $(CONFIG)

$(CONFIG):
	@mkdir -p $@

$(CONFIG)/%.o: %.c
	@echo " Compiling $(COMPILERNAME) $<" ;\
	$(CC) -c $(CFLAGS) $< -o $@

$(CONFIG)/%.o: %.s
	@echo " Assembling $(COMPILERNAME) $<" ;\
	$(CC) -c $(CFLAGS) $< -o $@

$(CONFIG)/$(LIB): $(OBJS)
	@echo " Generating lib..." ;\
	$(AR) cr $@ $^ ;\
	$(RM) -f $(OBJS) $(DEPS)
	
clean:
	@echo "Cleaning..." ;\
	$(RM) -f $(OBJS) $(DEPS) $(LIB) 

endif
.PHONY: all clean directories debug

