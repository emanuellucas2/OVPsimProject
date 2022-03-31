ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = dhrystone.POWERPC32-O3-g.elf dhrystone.POWERPC32-O1-g.elf dhrystone.POWERPC32-O0-g.elf dhrystone.POWERPC32-O3-g.elf dhrystone.POWERPC32-O1-g.elf dhrystone.POWERPC32-O0-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for POWERPC32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/POWERPC32.makefile.include
ifeq ($(POWERPC32_CC),)
	IMPERAS_ERROR := $(error "Error : POWERPC32_CC not set. Please check installation of toolchain for POWERPC32")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
POWERPC32-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O3-g.o,$(S)))
POWERPC32-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O1-g.o,$(S)))
POWERPC32-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O0-g.o,$(S)))
POWERPC32-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O3-g.o,$(S)))
POWERPC32-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O1-g.o,$(S)))
POWERPC32-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O0-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.POWERPC32-O3-g.elf:  $(POWERPC32-O3-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O3-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O3 -g 

%.POWERPC32-O1-g.elf:  $(POWERPC32-O1-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O1-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O1 -g 

%.POWERPC32-O0-g.elf:  $(POWERPC32-O0-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O0-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O0 -g 

%.POWERPC32-O3-g.elf:  $(POWERPC32-O3-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O3-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O3 -g 

%.POWERPC32-O1-g.elf:  $(POWERPC32-O1-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O1-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O1 -g 

%.POWERPC32-O0-g.elf:  $(POWERPC32-O0-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O0-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
