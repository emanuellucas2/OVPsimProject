ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

# Use OR1K cross-compiler by default
CROSS ?= OR1K

# Don't use standard model path by default
NOVLNV ?= 1

VLNVROOT=$(CURDIR)/vlnv

VLNVSRC ?= components

# Build application and harness
all: model.$(IMPERAS_SHRSUF) components
	@echo "Building Platform"
	$(MAKE) -C platform NOVLNV=$(NOVLNV)
	@echo "Building Application"
	$(MAKE) -C application CROSS=$(CROSS)

vlnvroot:
	@mkdir -p $(VLNVROOT)

# Build component library
components: vlnvroot
	$(V) $(MAKE) -f $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.library VLNVSRC=$(VLNVSRC) VLNVROOT=$(VLNVROOT) VERBOSE=$(VERBOSE)

# Clean application and harness
clean::
	$(MAKE) -C application clean CROSS=$(CROSS)
	$(MAKE) -C platform    clean NOVLNV=$(NOVLNV)
 
# Include processor build rules
-include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host
