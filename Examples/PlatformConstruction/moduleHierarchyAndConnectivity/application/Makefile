ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=OR1K
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

OPTIMISATION?=-O0 -g 

SRC = $(sort $(wildcard *.c))
EXE = $(patsubst %.c,%.$(CROSS).elf,$(SRC))

all: $(EXE)

%.$(CROSS).elf: %.$(CROSS).o
	$(V)  echo "# Linking $@"
	$(V)  $(IMPERAS_LINK) -o $@ $< $(IMPERAS_LDFLAGS) -lm

%.$(CROSS).o: %.c
	$(V)  echo "# Compiling $<"
	$(V)  $(IMPERAS_CC) -c -o $@ $< $(OPTIMISATION)

clean:
	-rm -f *.elf *.o 
