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
TARGET := freertos_amdtps
COMPILERNAME := gcc
PROJECT := freertos_amdtps_gcc
CONFIG := bin
AM_SoftwareRoot ?= ../../../../..

SHELL:=/bin/bash
#### Setup ####

STARTUP_FILE := ./startup_$(COMPILERNAME)

#### Required Executables ####
ECLIPSE := '$(shell which TrueSTUDIO 2>/dev/null)'
RM := $(shell which rm 2>/dev/null)

EXECUTABLES = ECLIPSE
K := $(foreach exec,$(EXECUTABLES),\
        $(if $(shell which $($(exec)) 2>/dev/null),,\
        $(info $(exec) not found on PATH ($($(exec))).)$(exec)))
$(if $(strip $(value K)),$(info Required Program(s) $(strip $(value K)) not found))

ifneq ($(strip $(value K)),)
all clean:
	$(info Tools $(COMPILERNAME) not installed.)
	$(RM) -rf bin
else

LIBS = ${AM_SoftwareRoot}/boards/apollo3_evb/bsp/atollic_gcc/bin/libam_bsp_gcc.a
LIBS += ${AM_SoftwareRoot}/mcu/apollo3/hal/atollic_gcc/bin/libam_hal_gcc.a
LIBS += ${AM_SoftwareRoot}/third_party/exactle/projects/generic/stacklib/gcc/bin-cortex-m4/libstacklib.a
INCS = 
INCS += ${AM_SoftwareRoot}/mcu/apollo3/hal/am_hal_pin.h

#### Rules ####
all: directories $(CONFIG)/$(PROJECT).bin

# Source Dependencies must be defined before they are used.
SRCS = ../../../../../third_party/FreeRTOS9/Source/event_groups.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/list.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/queue.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/tasks.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/timers.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/portable/MemMang/heap_2.c
SRCS += ../../../../../ambiq_ble/apps/amdtps/amdtp_main.c
SRCS += ../../../../../ambiq_ble/profiles/amdtpcommon/amdtp_common.c
SRCS += ../../../../../ambiq_ble/profiles/amdtps/amdtps_main.c
SRCS += ../../../../../ambiq_ble/services/svc_amdtp.c
SRCS += ../../../../../ambiq_ble/services/svc_amotas.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/app_disc.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/app_main.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/app_master.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/app_master_leg.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/app_server.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/app_slave.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/app_slave_leg.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/app_terminal.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/generic/app_db.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/generic/app_hw.c
SRCS += ../../../../../third_party/exactle/sw/apps/app/generic/app_ui.c
SRCS += ../../../../../third_party/exactle/sw/apps/hidapp/hidapp_main.c
SRCS += ../../../../../third_party/exactle/sw/hci/ambiq/hci_cmd.c
SRCS += ../../../../../third_party/exactle/sw/hci/ambiq/hci_core.c
SRCS += ../../../../../third_party/exactle/sw/hci/ambiq/hci_core_ps.c
SRCS += ../../../../../third_party/exactle/sw/hci/ambiq/hci_evt.c
SRCS += ../../../../../third_party/exactle/sw/hci/ambiq/hci_tr.c
SRCS += ../../../../../third_party/exactle/sw/hci/ambiq/hci_vs.c
SRCS += ../../../../../third_party/exactle/sw/hci/ambiq/apollo3/hci_drv_apollo3.c
SRCS += ../../../../../third_party/exactle/sw/profiles/bas/bas_main.c
SRCS += ../../../../../third_party/exactle/sw/profiles/hid/hid_main.c
SRCS += ../../../../../third_party/exactle/sw/sec/common/sec_aes.c
SRCS += ../../../../../third_party/exactle/sw/sec/common/sec_cmac.c
SRCS += ../../../../../third_party/exactle/sw/sec/common/sec_ecc_hci.c
SRCS += ../../../../../third_party/exactle/sw/sec/common/sec_main.c
SRCS += ../../../../../third_party/exactle/sw/stack/cfg/cfg_stack.c
SRCS += ../../../../../third_party/exactle/sw/stack/hci/hci_main.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/util/bda.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/util/bstream.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/util/calc128.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/util/crc32.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/util/print.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/util/terminal.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/util/wstr.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/wsf/ambiq/wsf_assert.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/wsf/ambiq/wsf_math.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/wsf/ambiq/wsf_os.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/wsf/ambiq/wsf_trace.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/wsf/common/wsf_buf.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/wsf/common/wsf_efs.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/wsf/common/wsf_msg.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/wsf/common/wsf_queue.c
SRCS += ../../../../../third_party/exactle/ws-core/sw/wsf/common/wsf_timer.c
SRCS += ../src/freertos_amdtp.c
SRCS += ../src/radio_task.c
SRCS += ../src/rtos.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/portable/GCC/AMapollo2/port.c
SRCS += ../../../../../devices/am_devices_button.c
SRCS += ../../../../../devices/am_devices_led.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_batt.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_bps.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_core.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_cps.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_cscs.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_dis.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_gls.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_gyro.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_hid.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_hrs.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_hts.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_ipss.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_plxs.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_px.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_rscs.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_scpss.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_temp.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_uricfg.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_wdxs.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_wp.c
SRCS += ../../../../../third_party/exactle/sw/services/svc_wss.c
SRCS += ../../../../../utils/am_util_debug.c
SRCS += ../../../../../utils/am_util_delay.c
SRCS += ../../../../../utils/am_util_faultisr.c
SRCS += ../../../../../utils/am_util_id.c
SRCS += ../../../../../utils/am_util_stdio.c

directories: $(CONFIG)

$(CONFIG):
	@mkdir -p $@

# BIN target requires post build step: objcopy elf to bin.
$(CONFIG)/$(PROJECT).bin: $(INCS) $(LIBS) $(SRCS)
	@echo " Building $(COMPILERNAME) $@..." ;\
	WKSP=$$(mktemp -d) ;\
	$(ECLIPSE) --launcher.suppressErrors -nosplash -data "$$WKSP" \
	    -application org.eclipse.cdt.managedbuilder.core.headlessbuild \
	    -import ./  -E cross_rm=$(RM) -cleanBuild .*/.*$(CONFIG).* \
	     1> '$(PROJECT).log' 2> '$(PROJECT).errlog' && $(RM) -rf $$WKSP

OBJS =  $(CONFIG)/**/* \
	$(STARTUP_FILE).*


clean:
	@echo "Cleaning..." ;\
	$(RM) -f $(OBJS) \
	    $(CONFIG)/$(PROJECT).bin  $(CONFIG)/$(PROJECT).elf \
	    $(CONFIG)/$(PROJECT).list $(CONFIG)/$(PROJECT).map \
	    $(PROJECT).log  $(PROJECT).errlog
endif
.PHONY: all clean directories

