IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

# Include from root of VLNV
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source

IMPERAS_PSE=PSE_RV64
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.pse
