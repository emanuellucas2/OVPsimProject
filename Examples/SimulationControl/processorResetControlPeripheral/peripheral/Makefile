ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
CFLAGS=-I$(IMPERAS_HOME)/ImperasLib/source/ovpworld.org/modelSupport/psesockets/1.0/model
OPT=0
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.pse
