ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=OR1K
all: pktModelTest.$(CROSS).elf 

# APP
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

pktModelTest.$(CROSS).elf: pktModelTest.$(CROSS).o
	$(V) echo "# Linking Application $@"
	$(V) $($(CROSS)_LINK) -ggdb -o $@  $^ $(IMPERAS_LDFLAGS)

pktModelTest.$(CROSS).o: pktModelTest.c
	$(V) echo "# Compiling Application $@"
	$(V) $($(CROSS)_CC) -ggdb -c -o $@  $<

clean:
	$(V) - rm -f pktModelTest.$(CROSS).elf pktModelTest.$(CROSS).o

