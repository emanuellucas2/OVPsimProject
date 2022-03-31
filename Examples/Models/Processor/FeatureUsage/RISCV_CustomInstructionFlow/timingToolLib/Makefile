IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

CFLAGS += -I.
CFLAGS += -I$(IMPERAS_HOME)/ImperasLib/source

ifneq ($(wildcard $(IMPERAS_HOME)/ImpProprietary/include/host/isl/.*),)
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host
else
$(warning "** Cannot build timingToolLib")
# default dummy targets
all:
clean:
endif
