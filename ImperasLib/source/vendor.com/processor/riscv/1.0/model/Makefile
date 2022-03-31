IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/riscv.ovpworld.org/processor/riscv/1.0/model
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/vendor.com/intercept/addCSRs/1.0/model
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/vendor.com/intercept/tmExtensions/1.0/model
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/vendor.com/intercept/fifoExtensions/1.0/model
LINKED=$(IMPERAS_HOME)/ImperasLib/source/riscv.ovpworld.org/processor/riscv/1.0/model
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host
