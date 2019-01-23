#******************************************************************************
#
# example.mk - Rules for building example projects.
#
# ${copyright}
#
# This is part of revision ${version} of the AmbiqSuite Development Package.
#
#******************************************************************************

#### BUILD BEGIN ####
SCRIPTROOT?=$(SWROOT)/scripts/buildproj
BUILDPROJARGS?=
.PHONY: buildproj
buildproj: config.ini
	$(SCRIPTROOT)/buildproj.py $(BUILDPROJARGS)
	$(MAKE) all

CONFIG_TEMPLATE = $(wildcard config-template.ini)
config.ini: $(CONFIG_TEMPLATE)
	cp -f config-template.ini config.ini;                                 \
	sed -i 's#\$$(family)#$(FAMILY)#g' config.ini;                        \
	sed -i 's#\$$(package)#$(PACKAGE)#g' config.ini;                      \
	sed -i 's#\$$(bsp)#../../../../boards/$(BOARD)/bsp#g' config.ini;     \

#### BUILD END ####
# Make "all" the default target.
all:

#### BUILD BEGIN ####
# The "realclean" option should restore the directory to a pristine state, just
# as it would be saved in the repository.
.PHONY: realclean
realclean:
	rm -rf $(SUBDIRS) $(filter-out $(KEEPFILES), README.txt)
	if test -f config-template.ini; then rm -f config.ini;fi
#### BUILD END ####

# All makefiles use this to find the top level directory.
SWROOT?=..
include $(SWROOT)/makedefs/subdirs.mk
