ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = peakSpeed1_m16c.M16C-O0-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for M16C
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/M16C.makefile.include
ifeq ($(M16C_CC),)
	IMPERAS_ERROR := $(error "Error : M16C_CC not set. Please check installation of toolchain for M16C")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
M16C-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.M16C-O0-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.M16C-O0-g.elf:  $(M16C-O0-g_OBJ)
	@    echo "# Linking M16C $@"
	$(V) $(M16C_LINK) -o $@ $^ $(M16C_LDFLAGS) -lm
	
%.M16C-O0-g.o: %.c
	@    echo "# Compiling M16C $<"
	$(V) $(M16C_CC) -c -o $@ $< -DM16C $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
