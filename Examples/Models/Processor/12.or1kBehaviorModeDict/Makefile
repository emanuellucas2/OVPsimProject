ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

# Change compilation of platform and processor
MODAL?=0
CFLAGS+=-DMODAL=$(MODAL)

# Use OR1K cross-compiler by default
CROSS ?= OR1K

# Don't use standard model path by default
NOVLNV ?= 1

# Don't build legacy ICM harness by default (use current OP interface instead)
BUILD_ICM_LEGACY ?= 0

# Build application and harness
all: model.$(IMPERAS_SHRSUF)
	@echo "Building Application"
	$(MAKE) -C application CROSS=$(CROSS)
	@echo "Building Platform"
	$(MAKE) -C platform NOVLNV=$(NOVLNV) BUILD_ICM_LEGACY=$(BUILD_ICM_LEGACY)

# Clean application and harness
clean::
	$(MAKE) -C application clean CROSS=$(CROSS)
	$(MAKE) -C platform    clean NOVLNV=$(NOVLNV)
 
# Include processor build rules
-include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host
