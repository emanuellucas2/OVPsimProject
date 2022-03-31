ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = peakSpeed2_microblaze.MICROBLAZE-O0-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for MICROBLAZE
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/MICROBLAZE.makefile.include
ifeq ($(MICROBLAZE_CC),)
	IMPERAS_ERROR := $(error "Error : MICROBLAZE_CC not set. Please check installation of toolchain for MICROBLAZE")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
MICROBLAZE-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.MICROBLAZE-O0-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.MICROBLAZE-O0-g.elf:  $(MICROBLAZE-O0-g_OBJ)
	@    echo "# Linking MICROBLAZE $@"
	$(V) $(MICROBLAZE_LINK) -o $@ $^ $(MICROBLAZE_LDFLAGS) -lm
	
%.MICROBLAZE-O0-g.o: %.c
	@    echo "# Compiling MICROBLAZE $<"
	$(V) $(MICROBLAZE_CC) -c -o $@ $< -DMICROBLAZE $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
