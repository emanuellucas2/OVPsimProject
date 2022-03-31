ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = linpack.RISCV32-O0-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for RISCV32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/RISCV32.makefile.include
ifeq ($(RISCV32_CC),)
	IMPERAS_ERROR := $(error "Error : RISCV32_CC not set. Please check installation of toolchain for RISCV32")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
RISCV32-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.RISCV32-O0-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.RISCV32-O0-g.elf:  $(RISCV32-O0-g_OBJ)
	@    echo "# Linking RISCV32 $@"
	$(V) $(RISCV32_LINK) -o $@ $^ $(RISCV32_LDFLAGS) -lm
	
%.RISCV32-O0-g.o: %.c
	@    echo "# Compiling RISCV32 $<"
	$(V) $(RISCV32_CC) -c -o $@ $< -DRISCV32 $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
