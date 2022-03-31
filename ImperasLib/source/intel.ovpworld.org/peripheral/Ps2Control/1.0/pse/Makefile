IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
CFLAGS=-I$(IMPERAS_HOME)/ImperasLib/source/intel.ovpworld.org/peripheral/Ps2Control/1.0/model
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/ovpworld.org/modelSupport/ps2/1.0/pse
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/ovpworld.org/modelSupport/sdlInput/1.0/model
IMPERAS_PSE=PSE_RV64
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.pse
