ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

all: messageIn.elf messageOut.elf

# APP
CROSS?=OR1K
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

messageIn.elf: messageIn.o
	$(V) echo "# Linking Application $@"
	$(V) $($(CROSS)_LINK) -ggdb -o $@  $^ $(IMPERAS_LDFLAGS)

messageIn.o: messageIn.c
	$(V) echo "# Compiling Application $@"
	$(V) $($(CROSS)_CC) -ggdb -c -Iapplication -o $@  $<

messageOut.elf: messageOut.o
	$(V) echo "# Linking Application $@"
	$(V) $($(CROSS)_LINK) -ggdb -o $@  $^ $(IMPERAS_LDFLAGS)

messageOut.o: messageOut.c
	$(V) echo "# Compiling Application $@"
	$(V) $($(CROSS)_CC) -ggdb -c -Iapplication -o $@  $<

clean:
	$(V) - rm -f *.elf *.o

