ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

# needed to find mips32CacheExtBIU.h
CFLAGS = -I$(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/ImperasLib/mips.com/processor/mips32/1.0

include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.platform
