ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = fibonacci.RISCV64-O0-g.elf fibonacci.RISCV64GC-O0-g.elf fibonacci.RISCV32-O0-g.elf fibonacci.RISCV32GC-O0-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for RISCV64
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/RISCV64.makefile.include
ifeq ($(RISCV64_CC),)
	IMPERAS_ERROR := $(error "Error : RISCV64_CC not set. Please check installation of toolchain for RISCV64")
endif

# include Cross Compiler settings for RISCV64GC
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/RISCV64GC.makefile.include
ifeq ($(RISCV64GC_CC),)
	IMPERAS_ERROR := $(error "Error : RISCV64GC_CC not set. Please check installation of toolchain for RISCV64GC")
endif

# include Cross Compiler settings for RISCV32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/RISCV32.makefile.include
ifeq ($(RISCV32_CC),)
	IMPERAS_ERROR := $(error "Error : RISCV32_CC not set. Please check installation of toolchain for RISCV32")
endif

# include Cross Compiler settings for RISCV32GC
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/RISCV32GC.makefile.include
ifeq ($(RISCV32GC_CC),)
	IMPERAS_ERROR := $(error "Error : RISCV32GC_CC not set. Please check installation of toolchain for RISCV32GC")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
RISCV64-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.RISCV64-O0-g.o,$(S)))
RISCV64GC-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.RISCV64GC-O0-g.o,$(S)))
RISCV32-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.RISCV32-O0-g.o,$(S)))
RISCV32GC-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.RISCV32GC-O0-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.RISCV64-O0-g.elf:  $(RISCV64-O0-g_OBJ)
	@    echo "# Linking RISCV64 $@"
	$(V) $(RISCV64_LINK) -o $@ $^ $(RISCV64_LDFLAGS) -lm
	
%.RISCV64-O0-g.o: %.c
	@    echo "# Compiling RISCV64 $<"
	$(V) $(RISCV64_CC) -c -o $@ $< -DRISCV64 $(DEF) -O0 -g 

%.RISCV64GC-O0-g.elf:  $(RISCV64GC-O0-g_OBJ)
	@    echo "# Linking RISCV64GC $@"
	$(V) $(RISCV64GC_LINK) -o $@ $^ $(RISCV64GC_LDFLAGS) -lm
	
%.RISCV64GC-O0-g.o: %.c
	@    echo "# Compiling RISCV64GC $<"
	$(V) $(RISCV64GC_CC) -c -o $@ $< -DRISCV64GC $(DEF) -O0 -g 

%.RISCV32-O0-g.elf:  $(RISCV32-O0-g_OBJ)
	@    echo "# Linking RISCV32 $@"
	$(V) $(RISCV32_LINK) -o $@ $^ $(RISCV32_LDFLAGS) -lm
	
%.RISCV32-O0-g.o: %.c
	@    echo "# Compiling RISCV32 $<"
	$(V) $(RISCV32_CC) -c -o $@ $< -DRISCV32 $(DEF) -O0 -g 

%.RISCV32GC-O0-g.elf:  $(RISCV32GC-O0-g_OBJ)
	@    echo "# Linking RISCV32GC $@"
	$(V) $(RISCV32GC_LINK) -o $@ $^ $(RISCV32GC_LDFLAGS) -lm
	
%.RISCV32GC-O0-g.o: %.c
	@    echo "# Compiling RISCV32GC $<"
	$(V) $(RISCV32GC_CC) -c -o $@ $< -DRISCV32GC $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
