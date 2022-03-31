ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=ARM7TDMI
all: fibonacci.$(CROSS).elf

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

fibonacci.$(CROSS).o: fibonacci.c
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  -c  $(IMPERAS_CFLAGS) -D$(CROSS)  -o $@  $^

fibonacci.$(CROSS).elf: fibonacci.$(CROSS).o 
	$(V) echo "Linking Application $@"
	$(V) $($(CROSS)_LINK) -o $@  $^  $(IMPERAS_LDFLAGS)
	$(V) $($(CROSS)_OBJDUMP) -S $@  > $(basename $@).od

clean:
	- rm -f *.$(CROSS).elf *.$(CROSS).o *.$(CROSS).od
