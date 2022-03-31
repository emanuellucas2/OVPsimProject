ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

# Various Cross compiler setups, Set default
CROSS?=IMG_MIPS32R2
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

ifeq ($(CROSS),IMG_MIPS32R2LE)
   ENDIAN=L
else
   ENDIAN=B
endif

OPTIMISATION=-O0 -g 

SRC=genexception.s main.s

# Define the base address to link the separate code
CODEBASE.genexception.$(CROSS).elf=0x1fc00380
CODEBASE.main.$(CROSS).elf=0x80000000

EXE = $(patsubst %.s,%.$(CROSS).elf,$(SRC))

all: $(EXE)

%.$(CROSS).elf: %.o
	$(V)  echo "Linking $@ at base $(CODEBASE.$@)"
	$(V)  $($(CROSS)_LD) -E$(ENDIAN) -Ttext $(CODEBASE.$@) -o $@ $< 

%.o: %.s
	$(V)  echo "Assembling $<"
	$(V)  $($(CROSS)_AS) -mips32r2 -mmt -E$(ENDIAN) -o $@ $< $(OPTIMISATION)

clean:
	-rm -f *.elf *.o 
