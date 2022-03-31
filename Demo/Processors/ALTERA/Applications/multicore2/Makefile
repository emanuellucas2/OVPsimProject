ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = multicore2.CS_NIOS2-O1-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for CS_NIOS2
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/CS_NIOS2.makefile.include
ifeq ($(CS_NIOS2_CC),)
	IMPERAS_ERROR := $(error "Error : CS_NIOS2_CC not set. Please check installation of toolchain for CS_NIOS2")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
CS_NIOS2-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.CS_NIOS2-O1-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.CS_NIOS2-O1-g.elf:  $(CS_NIOS2-O1-g_OBJ)
	@    echo "# Linking CS_NIOS2 $@"
	$(V) $(CS_NIOS2_LINK) -o $@ $^ $(CS_NIOS2_LDFLAGS) -lm
	
%.CS_NIOS2-O1-g.o: %.c
	@    echo "# Compiling CS_NIOS2 $<"
	$(V) $(CS_NIOS2_CC) -c -o $@ $< -DCS_NIOS2 $(DEF) -O1 -g 

clean::
	- rm -f $(ELF)
