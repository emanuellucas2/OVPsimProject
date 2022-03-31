ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

# Don't use standard model path by default
NOVLNV ?= 1

# Don't build legacy ICM harness by default (use current OP interface instead)
BUILD_ICM_LEGACY ?= 0

ifeq ($(BUILD_ICM_LEGACY),0)

# Build OP harness (see harness.c)
-include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.harness

else

# Build legacy ICM harness (see platform.c)
-include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.platform

endif
