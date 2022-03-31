ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

SRC?=application.c
CROSS?=OR1K
EXE=$(subst .c,.$(CROSS).elf,$(SRC))

all: $(EXE)
 
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

%.$(CROSS).elf: %.$(CROSS).o
	@echo "Linking Application $@"
	$(V) $($(CROSS)_LINK) -o $@  $^  $(IMPERAS_LDFLAGS)

%.$(CROSS).o: %.c
	@echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  -c  -o $@  $<

#
# Cleanup section
#
clean:
	$(V) - rm -f $(EXE)
