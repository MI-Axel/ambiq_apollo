#******************************************************************************
#
# am_hal.mk - Rules for building Ambiq support libraries.
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
buildproj: am_hal_pin.h

PIN_DEPS = apollo-pinout.csv
PIN_DEPS+= $(SWROOT)/scripts/pinconfig_gen/pinconfig_gen.py
PIN_DEPS+= $(SWROOT)/scripts/pinconfig_gen/pin_header_template.h

am_hal_pin.h: $(PIN_DEPS)
	python3 $(SWROOT)/scripts/pinconfig_gen/pinconfig_gen.py \
		apollo-pinout.csv \
		$(SWROOT)/scripts/pinconfig_gen/pin_header_template.h \
		-o am_hal_pin.h -a $(CHIP_GENERATION)

# The "realclean" option should restore the directory to a pristine state, just
# as it would be saved in the repository.
.PHONY: realclean
realclean:
	rm -rf $(SUBDIRS)
	rm -rf am_hal_pin.h
#### BUILD END ####

# All makefiles use this to find the top level directory.
SWROOT?=..
include $(SWROOT)/makedefs/subdirs.mk
