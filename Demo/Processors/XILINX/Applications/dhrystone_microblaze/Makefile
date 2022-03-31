ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = dhrystone_microblaze.MICROBLAZE-O1-g.elf dhrystone_microblaze.MICROBLAZE-O1-g.elf dhrystone_microblaze.MICROBLAZE-O2-g.elf 

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
MICROBLAZE-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.MICROBLAZE-O1-g.o,$(S)))
MICROBLAZE-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.MICROBLAZE-O1-g.o,$(S)))
MICROBLAZE-O2-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.MICROBLAZE-O2-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.MICROBLAZE-O1-g.elf:  $(MICROBLAZE-O1-g_OBJ)
	@    echo "# Linking MICROBLAZE $@"
	$(V) $(MICROBLAZE_LINK) -o $@ $^ $(MICROBLAZE_LDFLAGS) -lm
	
%.MICROBLAZE-O1-g.o: %.c
	@    echo "# Compiling MICROBLAZE $<"
	$(V) $(MICROBLAZE_CC) -c -o $@ $< -DMICROBLAZE $(DEF) -O1 -g 

%.MICROBLAZE-O1-g.elf:  $(MICROBLAZE-O1-g_OBJ)
	@    echo "# Linking MICROBLAZE $@"
	$(V) $(MICROBLAZE_LINK) -o $@ $^ $(MICROBLAZE_LDFLAGS) -lm
	
%.MICROBLAZE-O1-g.o: %.c
	@    echo "# Compiling MICROBLAZE $<"
	$(V) $(MICROBLAZE_CC) -c -o $@ $< -DMICROBLAZE $(DEF) -O1 -g 

%.MICROBLAZE-O2-g.elf:  $(MICROBLAZE-O2-g_OBJ)
	@    echo "# Linking MICROBLAZE $@"
	$(V) $(MICROBLAZE_LINK) -o $@ $^ $(MICROBLAZE_LDFLAGS) -lm
	
%.MICROBLAZE-O2-g.o: %.c
	@    echo "# Compiling MICROBLAZE $<"
	$(V) $(MICROBLAZE_CC) -c -o $@ $< -DMICROBLAZE $(DEF) -O2 -g 

clean::
	- rm -f $(ELF)
