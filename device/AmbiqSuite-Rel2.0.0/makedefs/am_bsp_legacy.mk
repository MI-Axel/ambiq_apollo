#******************************************************************************
#
# am_bsp.mk - Rules for building Ambiq support libraries.
#
# ${copyright}
#
# This is part of revision ${version} of the AmbiqSuite Development Package.
#
#******************************************************************************

#### BUILD BEGIN ####
# Internally, we'll use "buildproj" as the default target.
SCRIPTROOT?=$(SWROOT)/scripts/buildproj
BUILDPROJARGS?=
.PHONY: buildproj
buildproj: config.ini
	$(SCRIPTROOT)/buildproj.py $(BUILDPROJARGS)
	@$(MAKE) all
#### BUILD END ####
# Make "all" the default target.
all:

#### BUILD BEGIN ####

buildproj: am_bsp_gpio.h $(SWROOT)/mcu/$(FAMILY)/hal/am_hal_pin.h

PIN_DEPS = apollo-pinout.csv
PIN_DEPS+= ../../../scripts/pinconfig_gen/bsp_gen.py
PIN_DEPS+= ../../../scripts/pinconfig_gen/am_bsp_gpio_template.c
PIN_DEPS+= ../../../scripts/pinconfig_gen/am_bsp_gpio_template.h

am_bsp_gpio.h: $(PIN_DEPS)
	../../../scripts/pinconfig_gen/bsp_gen.py apollo-pinout.csv

$(SWROOT)/mcu/$(FAMILY)/hal/am_hal_pin.h:
	$(MAKE) -C $(SWROOT)/mcu/$(FAMILY)/hal am_hal_pin.h

# The "realclean" option should restore the directory to a pristine state, just
# as it would be saved in the repository.
.PHONY: realclean
realclean:
	rm -rf am_bsp_pins.[ch]
	rm -rf $(SUBDIRS)
#### BUILD END ####

# All makefiles use this to find the top level directory.
SWROOT?=..
include $(SWROOT)/makedefs/subdirs.mk
