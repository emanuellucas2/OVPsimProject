ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

# Various Cross compiler setups, Set default
CROSS?=ARM7TDMI
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

ENDIAN=L

SRC=asmtest.S

EXE = $(patsubst %.S,%.elf,$(SRC))

all: $(EXE)

%.elf: %.o
	$(V)  echo "Linking $@"
	$(V)  $(IMPERAS_LD) -E$(ENDIAN) -T default.arm.ld -o $@ $< 

%.o: %.S
	$(V)  echo "Assembling $<"
	$(V)  $(IMPERAS_AS) -mcpu='cortex-a9' -E${ENDIAN} --gstabs -o $@ $< 

clean:
	-rm -f *.elf *.o 

