ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=ARM7TDMI
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

# Default Number of Peripherals used (set in Application and Platform)
PERIPHERALS?=2

ELF=dataSortTest.$(CROSS).elf
all: $(ELF)

OPTIMISATION?=-O0 -g 

$(ELF): dataSortTest.o arm7_support.o arm7_support_asm.o dhrystone.o
	$(V) echo "Linking Application $@"
	$(V) $($(CROSS)_LINK) $(OPTIMISATION) -o $@  $^ $(IMPERAS_LDFLAGS)

dataSortTest.o: dataSortTest.c dataSortRegisters.h arm7_support.h
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  $(OPTIMISATION) -c -DNUMBERPERIPHERALS=$(PERIPHERALS) -o $@  $<

arm7_support.o: arm7_support.c arm7_support.h
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  $(OPTIMISATION) -c -o $@  $<

dhrystone.o: dhrystone.c
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  $(OPTIMISATION) -c -o $@  $<

arm7_support_asm.o: arm7_support_asm.s
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  $(OPTIMISATION) -c -o $@  $<

.INTERMEDIATE:dataSortTest.o arm7_support.o arm7_support_asm.o dhrystone.o

clean:
	$(V) - rm -f $(ELF) *.o

