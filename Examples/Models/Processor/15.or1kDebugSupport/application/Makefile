ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CSRC?=application.c
ASRC?=asmtest.S
CROSS?=OR1K

EXE=$(subst .c,.$(CROSS).elf,$(CSRC))
EXE+=$(subst .S,.$(CROSS).elf,$(ASRC))

all: $(EXE)
 
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

application.$(CROSS).elf: application.$(CROSS).o
	@echo "Linking Application $@"
	$(V) $($(CROSS)_LINK) -o $@  $^  $(IMPERAS_LDFLAGS)

application.$(CROSS).o: application.c
	@echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  -c  -o $@  $<

asmtest.$(CROSS).elf: asmtest.$(CROSS).o
	@echo "Linking Application $@"
	$(V) $($(CROSS)_LD) -o $@ --section-start .text=0 $^

asmtest.$(CROSS).o: asmtest.S
	@echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  -c  -o $@  $<

#
# Cleanup section
#
clean:
	$(V) - rm -f $(EXE) *.$(CROSS).o
