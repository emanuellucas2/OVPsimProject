IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/riscv.ovpworld.org/processor/riscv/1.0/model
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/sifive.ovpworld.org/intercept/sifiveExtensions/1.0/model
LINKED=$(IMPERAS_HOME)/ImperasLib/source/riscv.ovpworld.org/processor/riscv/1.0/model
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host
