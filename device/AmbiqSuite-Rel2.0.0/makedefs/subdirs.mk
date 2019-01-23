#******************************************************************************
#
# subdirs.mk - Recursion rules for AmbiqSuite Makefiles.
#
# ${copyright}
#
# This is part of revision ${version} of the AmbiqSuite Development Package.
#
#******************************************************************************
SUBDIRS:=$(filter-out $(KEEPFILES), $(dir $(wildcard */Makefile)))

.PHONY: $(SUBDIRS) all clean

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS) SWROOT=$(SWROOT) SCRIPTROOT=$(SCRIPTROOT)

# These targets will cause recursion
all: $(SUBDIRS)
clean: $(SUBDIRS)
