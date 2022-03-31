ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include


CROSS?=IMG_MIPS32R2
all: application.$(CROSS).elf

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

application.$(CROSS).elf: application.$(CROSS).o
	$(V) echo "Linking Application $@"
	$(V) $($(CROSS)_LINK) -o $@  $< $($(CROSS)_LDFLAGS)

application.$(CROSS).o: application.c
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  -c  -o $@  $^

clean:
	- rm -f application.$(CROSS).elf *.$(CROSS).o
	
