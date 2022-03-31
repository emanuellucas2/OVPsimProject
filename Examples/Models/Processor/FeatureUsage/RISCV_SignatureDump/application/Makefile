ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

# Various Cross compiler setups, Set default
CROSS?=RISCV64
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

OPTIMISATION=-O0 -g 

SRC=$(wildcard *.c)

EXE = $(patsubst %.c,%.$(CROSS).elf,$(SRC))

all: $(EXE)

%.$(CROSS).elf: %.$(CROSS).o
	$(V)  echo "Linking $@"
	$(V)  $($(CROSS)_LINK) -o $@ $< $($(CROSS)_LDFLAGS) -lm

%.$(CROSS).o: %.c
	$(V)  echo "Compiling $<"
	$(V)  $($(CROSS)_CC) -c -o $@ $< $(OPTIMISATION)

clean:
	-rm -f *.elf *.o 
