IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
CFLAGS=-I$(IMPERAS_HOME)/ImperasLib/source/xilinx.ovpworld.org/peripheral/plb/1.0/pse
LDFLAGS=-lm

IMPERAS_PSE=PSE_RV64
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.pse
