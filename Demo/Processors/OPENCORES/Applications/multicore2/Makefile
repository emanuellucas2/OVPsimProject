ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = multicore2.OR1K-O1-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for OR1K
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/OR1K.makefile.include
ifeq ($(OR1K_CC),)
	IMPERAS_ERROR := $(error "Error : OR1K_CC not set. Please check installation of toolchain for OR1K")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
OR1K-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.OR1K-O1-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.OR1K-O1-g.elf:  $(OR1K-O1-g_OBJ)
	@    echo "# Linking OR1K $@"
	$(V) $(OR1K_LINK) -o $@ $^ $(OR1K_LDFLAGS) -lm
	
%.OR1K-O1-g.o: %.c
	@    echo "# Compiling OR1K $<"
	$(V) $(OR1K_CC) -c -o $@ $< -DOR1K $(DEF) -O1 -g 

clean::
	- rm -f $(ELF)
