ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=OR1K

#
# Include Cross Compilers
#

# include Cross Compiler settings for CROSS
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to ELF
#
ELF = $(foreach S,$(SRC),$(patsubst %.c,%.$(CROSS).elf,$(S)))

# Options
OPTIMIZATION?=-O0
DEBUG?=-g

#
# Rules to build ELF files
#
all: $(ELF)

%.$(CROSS).elf:  %.$(CROSS).o
	@ echo "# Linking $(CROSS) $@"
	$(V) $($(CROSS)_LINK) -o $@ $^ $($(CROSS)_LDFLAGS) -lm
	
%.$(CROSS).o: %.c
	@ echo "# Compiling $(CROSS) $(OPTIMIZATION) $(DEBUG) $<"
	$(V) $($(CROSS)_CC) -c -o $@ $< -D$(CROSS) $(OPTIMIZATION) $(DEBUG) 

clean::
	- rm -f $(ELF)

help::
	@ echo "Options to set"
	@ echo "  OPTIMIZATION ($(OPTIMIZATION))"
	@ echo "  DEBUG        ($(DEBUG))"

