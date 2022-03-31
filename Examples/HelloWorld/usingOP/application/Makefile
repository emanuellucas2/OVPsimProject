ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

#
#  Makefile for Cross Compiling an appication for a target processor type
#

# Various Cross compiler setups, Default riscv
CROSS?=RISCV32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

ASRC ?= application.c
AEXE = $(patsubst %.c,%.$(CROSS).elf,$(ASRC))

all: $(AEXE)

%.$(CROSS).elf: %.$(CROSS).o
	$(V)  echo "Linking $@"
	$(V) $(IMPERAS_LINK) -o $@ $< $(IMPERAS_LDFLAGS) -lm

%.$(CROSS).o: %.c
	$(V)  echo "Compiling $<"
	$(V) $(IMPERAS_CC) -g -O0 -c -o $@ $<

clean:
	- rm -f *.elf *.o
