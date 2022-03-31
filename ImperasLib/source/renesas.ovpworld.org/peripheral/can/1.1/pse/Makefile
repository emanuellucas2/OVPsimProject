IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/ovpworld.org/modelSupport/VCAN/1.0/pse
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/renesas.ovpworld.org/modelSupport/can/1.0/pse

IMPERAS_PSE=PSE_RV64
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.pse
