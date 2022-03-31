ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = fibonacci.V850-O3-g.elf fibonacci.RH850-O3-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for V850
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/V850.makefile.include
ifeq ($(V850_CC),)
	IMPERAS_ERROR := $(error "Error : V850_CC not set. Please check installation of toolchain for V850")
endif

# include Cross Compiler settings for RH850
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/RH850.makefile.include
ifeq ($(RH850_CC),)
	IMPERAS_ERROR := $(error "Error : RH850_CC not set. Please check installation of toolchain for RH850")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
V850-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.V850-O3-g.o,$(S)))
RH850-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.RH850-O3-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.V850-O3-g.elf:  $(V850-O3-g_OBJ)
	@    echo "# Linking V850 $@"
	$(V) $(V850_LINK) -o $@ $^ $(V850_LDFLAGS) -lm
	
%.V850-O3-g.o: %.c
	@    echo "# Compiling V850 $<"
	$(V) $(V850_CC) -c -o $@ $< -DV850 $(DEF) -O3 -g 

%.RH850-O3-g.elf:  $(RH850-O3-g_OBJ)
	@    echo "# Linking RH850 $@"
	$(V) $(RH850_LINK) -o $@ $^ $(RH850_LDFLAGS) -lm
	
%.RH850-O3-g.o: %.c
	@    echo "# Compiling RH850 $<"
	$(V) $(RH850_CC) -c -o $@ $< -DRH850 $(DEF) -O3 -g 

clean::
	- rm -f $(ELF)
