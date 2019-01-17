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
# This is part of revision 1.2.12 of the AmbiqSuite Development Package.
#
#******************************************************************************
TARGET := freertos_fit
COMPILERNAME := gcc
PROJECT := freertos_fit_gcc
CONFIG := bin
AM_SoftwareRoot ?= ../../../../..

SHELL:=/bin/bash
#### Setup ####

TOOLCHAIN ?= arm-none-eabi
PART = apollo2
CPU = cortex-m4
FPU = fpv4-sp-d16
FABI = softfp

LINKER_FILE := ./freertos_fit.ld
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

DEFINES = -DPART_$(PART)
DEFINES+= -DAM_PACKAGE_BGA
DEFINES += -DWSF_TRACE_ENABLED
DEFINES += -DAM_DEBUG_PRINTF
DEFINES += -DAM_PART_APOLLO2
DEFINES += -DAM_FREERTOS

INCLUDES = -I${AM_SoftwareRoot}/boards/apollo2_blue_evb/bsp
INCLUDES += -I${AM_SoftwareRoot}/ambiq_ble/em9304
INCLUDES += -I${AM_SoftwareRoot}/devices
INCLUDES += -I${AM_SoftwareRoot}/mcu/apollo2
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/apollo-host/projects/common
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/apps/app
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/apps/app/include
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/apps/fit
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/hci/ambiq
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/hci/ambiq/em9304
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/hci/include
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/profiles/bas
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/profiles/hid
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/profiles/hrps
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/profiles/rscp
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/profiles/uribeacon
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/sec/common
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/sec/include
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/services
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/stack/cfg
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/stack/hci
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/sw/stack/include
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/ws-core/include
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/ws-core/sw/util
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/ws-core/sw/wsf/ambiq
INCLUDES += -I${AM_SoftwareRoot}/third_party/exactle/ws-core/sw/wsf/include
INCLUDES += -I${AM_SoftwareRoot}/utils
INCLUDES += -I../src
INCLUDES += -I${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/include
INCLUDES += -I${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/portable/MemMang
INCLUDES += -I${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/portable/GCC/AMapollo2

VPATH = ${AM_SoftwareRoot}/devices
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/services
VPATH +=:${AM_SoftwareRoot}/utils
VPATH +=:${AM_SoftwareRoot}/third_party/FreeRTOS9/Source
VPATH +=:${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/portable/MemMang
VPATH +=:${AM_SoftwareRoot}/ambiq_ble/em9304
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/apps/app
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/apps/app/generic
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/apps/fit
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/apps/hidapp
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/hci/ambiq
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/hci/ambiq/em9304
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/profiles/bas
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/profiles/hid
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/profiles/hrps
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/profiles/rscp
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/sec/common
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/stack/cfg
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/sw/stack/hci
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/ws-core/sw/util
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/ws-core/sw/wsf/ambiq
VPATH +=:${AM_SoftwareRoot}/third_party/exactle/ws-core/sw/wsf/common
VPATH +=:../src
VPATH +=:${AM_SoftwareRoot}/third_party/FreeRTOS9/Source/portable/GCC/AMapollo2

SRC = event_groups.c
SRC += list.c
SRC += queue.c
SRC += tasks.c
SRC += timers.c
SRC += heap_2.c
SRC += em9304_init.c
SRC += em9304_patches.c
SRC += app_disc.c
SRC += app_main.c
SRC += app_master.c
SRC += app_master_leg.c
SRC += app_server.c
SRC += app_slave.c
SRC += app_slave_leg.c
SRC += app_terminal.c
SRC += app_db.c
SRC += app_hw.c
SRC += app_ui.c
SRC += fit_main.c
SRC += hidapp_main.c
SRC += hci_cmd.c
SRC += hci_core.c
SRC += hci_core_ps.c
SRC += hci_evt.c
SRC += hci_tr.c
SRC += hci_vs.c
SRC += hci_drv_em9304.c
SRC += bas_main.c
SRC += hid_main.c
SRC += hrps_main.c
SRC += rscps_main.c
SRC += sec_aes.c
SRC += sec_cmac.c
SRC += sec_ecc_hci.c
SRC += sec_main.c
SRC += cfg_stack.c
SRC += hci_main.c
SRC += bda.c
SRC += bstream.c
SRC += calc128.c
SRC += crc32.c
SRC += print.c
SRC += terminal.c
SRC += wstr.c
SRC += wsf_assert.c
SRC += wsf_math.c
SRC += wsf_os.c
SRC += wsf_trace.c
SRC += wsf_buf.c
SRC += wsf_efs.c
SRC += wsf_msg.c
SRC += wsf_queue.c
SRC += wsf_timer.c
SRC += freertos_fit.c
SRC += radio_task.c
SRC += rtos.c
SRC += port.c
SRC += am_devices_button.c
SRC += am_devices_em9304.c
SRC += am_devices_led.c
SRC += svc_batt.c
SRC += svc_bps.c
SRC += svc_core.c
SRC += svc_cps.c
SRC += svc_cscs.c
SRC += svc_dis.c
SRC += svc_gls.c
SRC += svc_gyro.c
SRC += svc_hid.c
SRC += svc_hrs.c
SRC += svc_hts.c
SRC += svc_ipss.c
SRC += svc_plxs.c
SRC += svc_px.c
SRC += svc_rscs.c
SRC += svc_scpss.c
SRC += svc_temp.c
SRC += svc_uricfg.c
SRC += svc_wdxs.c
SRC += svc_wp.c
SRC += svc_wss.c
SRC += am_util_debug.c
SRC += am_util_delay.c
SRC += am_util_faultisr.c
SRC += am_util_stdio.c
SRC += startup_gcc.c

CSRC = $(filter %.c,$(SRC))
ASRC = $(filter %.s,$(SRC))

OBJS = $(CSRC:%.c=$(CONFIG)/%.o)
OBJS+= $(ASRC:%.s=$(CONFIG)/%.o)

DEPS = $(CSRC:%.c=$(CONFIG)/%.d)
DEPS+= $(ASRC:%.s=$(CONFIG)/%.d)

LIBS = ${AM_SoftwareRoot}/boards/apollo2_blue_evb/bsp/gcc/bin/libam_bsp.a
LIBS += ${AM_SoftwareRoot}/mcu/apollo2/hal/gcc/bin/libam_hal.a
LIBS += ${AM_SoftwareRoot}/third_party/exactle/projects/generic/stacklib/gcc/bin-cortex-m4/libstacklib.a
INCS = ${AM_SoftwareRoot}/boards/apollo2_blue_evb/bsp/am_bsp_gpio.h
INCS += ${AM_SoftwareRoot}/mcu/apollo2/hal/am_hal_pin.h

CFLAGS = -mthumb -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FABI)
CFLAGS+= -ffunction-sections -fdata-sections
CFLAGS+= -MMD -MP -std=c99 -Wall -g
CFLAGS+= -O0
CFLAGS+= $(DEFINES)
CFLAGS+= $(INCLUDES)
CFLAGS+= -Dgcc

LFLAGS = -mthumb -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FABI)
LFLAGS+= -nostartfiles -static
LFLAGS+= -Wl,--gc-sections,--entry,am_reset_isr,-Map,$(CONFIG)/$(TARGET).map
LFLAGS+= -Wl,--start-group -lm -lc -lgcc -Wl,--end-group
LFLAGS+= 

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

# Automatically include any generated dependencies
-include $(DEPS)
endif
.PHONY: all clean directories

