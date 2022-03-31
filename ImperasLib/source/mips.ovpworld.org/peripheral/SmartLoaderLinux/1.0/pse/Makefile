IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

CFLAGS=-I.
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/ovpworld.org/modelSupport/fdt/1.0/pse

IMPERAS_PSE=PSE_RV64
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.pse
