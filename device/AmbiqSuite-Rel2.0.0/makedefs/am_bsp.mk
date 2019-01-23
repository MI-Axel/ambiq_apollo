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

buildproj: bsp_pins.src am_bsp_pins.c am_bsp_pins.h $(SWROOT)/mcu/$(FAMILY)/hal/am_hal_pin.h
#### BUILD END ####
# Make "all" the default target.
all: bsp_pins.src am_bsp_pins.c am_bsp_pins.h $(SWROOT)/mcu/$(FAMILY)/hal/am_hal_pin.h

am_bsp_pins.c: bsp_pins.src
	$(SWROOT)/tools/bsp_generator/pinconfig.py bsp_pins.src C >am_bsp_pins.c
#### BUILD BEGIN ####
	$(SWROOT)/scripts/utils/dos2unix.py am_bsp_pins.c
#### BUILD END ####

am_bsp_pins.h: bsp_pins.src
	$(SWROOT)/tools/bsp_generator/pinconfig.py bsp_pins.src H >am_bsp_pins.h
#### BUILD BEGIN ####
	$(SWROOT)/scripts/utils/dos2unix.py am_bsp_pins.h
#### BUILD END ####

$(SWROOT)/mcu/apollo3/hal/am_hal_pin.h:
	$(MAKE) -C $(SWROOT)/mcu/apollo3/hal am_hal_pin.h

#### BUILD BEGIN ####
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
