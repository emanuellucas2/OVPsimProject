ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=OR1K
all: asmtest.$(CROSS).elf

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

asmtest.$(CROSS).elf: asmtest.$(CROSS).o
	$(V) echo "Linking Application $@"
	$(V) $($(CROSS)_LD) -o $@ --section-start .text=0  $^

asmtest.$(CROSS).o: asmtest.S
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  -c  -o $@  $<

clean:
	- rm -f asmtest.$(CROSS).elf asmtest.$(CROSS).o
