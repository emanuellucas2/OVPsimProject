ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = dhrystone_rl78.RL78-O1-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for RL78
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/RL78.makefile.include
ifeq ($(RL78_CC),)
	IMPERAS_ERROR := $(error "Error : RL78_CC not set. Please check installation of toolchain for RL78")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
RL78-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.RL78-O1-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.RL78-O1-g.elf:  $(RL78-O1-g_OBJ)
	@    echo "# Linking RL78 $@"
	$(V) $(RL78_LINK) -o $@ $^ $(RL78_LDFLAGS) -lm
	
%.RL78-O1-g.o: %.c
	@    echo "# Compiling RL78 $<"
	$(V) $(RL78_CC) -c -o $@ $< -DRL78 $(DEF) -O1 -g 

clean::
	- rm -f $(ELF)
