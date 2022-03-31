ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

# Base RISC-V Processor Model Source
CFLAGS += -I$(IMPERAS_HOME)/ImperasLib/source/riscv.ovpworld.org/processor/riscv/1.0/model

include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host
