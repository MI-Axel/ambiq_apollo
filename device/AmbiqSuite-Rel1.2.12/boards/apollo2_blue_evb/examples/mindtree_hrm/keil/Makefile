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
TARGET := mindtree_hrm
COMPILERNAME := Keil
PROJECT := mindtree_hrm_Keil
CONFIG := bin
AM_SoftwareRoot ?= ../../../../..

SHELL:=/bin/bash
#### Required Executables ####
K := $(shell type -p UV4.exe)
RM := $(shell which rm 2>/dev/null)

ifeq ($(K),)
all clean:
	$(info Tools w/$(COMPILERNAME) not installed.)
	$(RM) -rf bin
else

LIBS = ../../../bsp/keil/bin/libam_bsp.lib
LIBS += ../../../../../mcu/apollo2/hal/keil/bin/libam_hal.lib
LIBS += ../../../../../third_party/ethermind/library/freertos/keil/ethermind.lib
INCS = ../../../bsp/am_bsp_gpio.h
INCS += ../../../../../mcu/apollo2/hal/am_hal_pin.h

all: directories $(CONFIG)/$(TARGET).bin

# Source Dependencies must be defined before they are used.
SRCS = ../../../../../third_party/FreeRTOS9/Source/event_groups.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/list.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/queue.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/tasks.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/timers.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/portable/MemMang/heap_2.c
SRCS += ../../../../../ambiq_ble/em9304/em9304_init.c
SRCS += ../../../../../ambiq_ble/em9304/em9304_patches.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/hrs/appl_gap_config_params.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/hrs/appl_hrs.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/hrs/gatt_db.c
SRCS += ../src/mindtree_hrm.c
SRCS += ../src/rtos.c
SRCS += ../../../../../third_party/FreeRTOS9/Source/portable/Keil/AMapollo2/port.c
SRCS += ../../../../../devices/am_devices_em9304.c
SRCS += ../../../../../devices/am_devices_led.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/appl.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/appl_att_server.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/appl_fsm_handlers.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/appl_fsm_table.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/appl_gap.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/appl_hci.c
SRCS += ../../../../../third_party/ethermind/appl/profile_appl/appl_smp.c
SRCS += ../../../../../third_party/ethermind/os/freertos/BT_debug.c
SRCS += ../../../../../third_party/ethermind/os/freertos/gatt_db_pl.c
SRCS += ../../../../../third_party/ethermind/os/freertos/hci_spi_em9304.c
SRCS += ../../../../../third_party/ethermind/os/freertos/status_pl.c
SRCS += ../../../../../utils/am_util_delay.c
SRCS += ../../../../../utils/am_util_faultisr.c
SRCS += ../../../../../utils/am_util_stdio.c

$(CONFIG)/$(TARGET).bin: $(LIBS) $(INCS) $(SRCS)
	(UV4.exe -b -t "mindtree_hrm" mindtree_hrm.uvprojx -j0 ;\
	if [ $$? -eq 1 ]; then true; fi)

directories: $(CONFIG)

$(CONFIG):
	@mkdir -p $@


clean:
	@echo Cleaning... ;\
	$(RM) -rf $(CONFIG)

endif
.PHONY: all clean directories

