ROOTDIR = ../..
TEMPLATEDIR = $(ROOTDIR)/scripts/header_gen/svd_templates
SCRIPTDIR = $(ROOTDIR)/scripts/header_gen
SOURCEDIR = $(ROOTDIR)/mcu/apollo/regs/source
SOURCEDIR2 = $(ROOTDIR)/mcu/apollo2/regs/source

SVDFILES = apollo1.svd apollo2.svd

.PHONY: all clean realclean
all: $(SVDFILES)

realclean: clean

clean:
	rm -f $(SVDFILES)

apollo1.svd: $(SOURCEDIR)/**
	python3 $(SCRIPTDIR)/svd_gen.py -o $@ -t $(TEMPLATEDIR) $(SOURCEDIR) -n apollo1

apollo2.svd: $(SOURCEDIR2)/**
	python3 $(SCRIPTDIR)/svd_gen.py -o $@ -t $(TEMPLATEDIR) $(SOURCEDIR2) -n apollo2
