ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=ARM_CORTEX_A9
all: application.$(CROSS).elf

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

%.$(CROSS).elf: %.$(CROSS).o
	$(V) echo "Linking Application $@"
	$(V) $(IMPERAS_LINK) -g -o $@  $^  $(IMPERAS_LDFLAGS)

%.$(CROSS).o: %.c
	$(V) echo "Compiling Application $@"
	$(V) $(IMPERAS_CC) -g -c  $(IMPERAS_CFLAGS) -D$(CROSS)  -o $@  $<

clean:
	- rm -f application*.$(CROSS).elf application*.$(CROSS).o
