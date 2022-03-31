ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

INC=.
CROSS?=OR1K
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

all:  int.$(CROSS).elf 

int.$(CROSS).elf: start.$(CROSS).o main.$(CROSS).o 
	$(V) echo "Linking Application $@"
	$(V) $(IMPERAS_CC) -nostartfiles -Ttext 0x0 $^ -o $@ 
	$(V) $(IMPERAS_OBJDUMP) -D $@ > $@.od

main.$(CROSS).o: main.c
	$(V) echo "Compiling Application $@"
	$(V) $(IMPERAS_CC) -I$(INC) -c -ggdb -gdwarf-2 -o $@ $<

start.$(CROSS).o: start.S
	$(V) echo "Compiling Application $<"
	$(V) $(IMPERAS_CC) -I$(INC) -c -ggdb -gdwarf-2 -o $@ $<

clean:
	rm -f *.elf *.$(CROSS).o *.od
