ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

# Build locally
NOVLNV?=1

# Platform C++
SRC=platform.cpp

include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.platform
