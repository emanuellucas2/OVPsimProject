ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = dhrystone.ARC600-O2-g.elf dhrystone.ARC600-O1-g.elf dhrystone.ARC600-O0-g.elf dhrystone.ARC600-O3-g.elf dhrystone.ARC700-O2-g.elf dhrystone.ARC700-O1-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for ARC600
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARC600.makefile.include
ifeq ($(ARC600_CC),)
	IMPERAS_ERROR := $(error "Error : ARC600_CC not set. Please check installation of toolchain for ARC600")
endif

# include Cross Compiler settings for ARC700
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARC700.makefile.include
ifeq ($(ARC700_CC),)
	IMPERAS_ERROR := $(error "Error : ARC700_CC not set. Please check installation of toolchain for ARC700")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
ARC600-O2-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC600-O2-g.o,$(S)))
ARC600-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC600-O1-g.o,$(S)))
ARC600-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC600-O0-g.o,$(S)))
ARC600-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC600-O3-g.o,$(S)))
ARC700-O2-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC700-O2-g.o,$(S)))
ARC700-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC700-O1-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.ARC600-O2-g.elf:  $(ARC600-O2-g_OBJ)
	@    echo "# Linking ARC600 $@"
	$(V) $(ARC600_LINK) -o $@ $^ $(ARC600_LDFLAGS) -lm
	
%.ARC600-O2-g.o: %.c
	@    echo "# Compiling ARC600 $<"
	$(V) $(ARC600_CC) -c -o $@ $< -DARC600 $(DEF) -O2 -g 

%.ARC600-O1-g.elf:  $(ARC600-O1-g_OBJ)
	@    echo "# Linking ARC600 $@"
	$(V) $(ARC600_LINK) -o $@ $^ $(ARC600_LDFLAGS) -lm
	
%.ARC600-O1-g.o: %.c
	@    echo "# Compiling ARC600 $<"
	$(V) $(ARC600_CC) -c -o $@ $< -DARC600 $(DEF) -O1 -g 

%.ARC600-O0-g.elf:  $(ARC600-O0-g_OBJ)
	@    echo "# Linking ARC600 $@"
	$(V) $(ARC600_LINK) -o $@ $^ $(ARC600_LDFLAGS) -lm
	
%.ARC600-O0-g.o: %.c
	@    echo "# Compiling ARC600 $<"
	$(V) $(ARC600_CC) -c -o $@ $< -DARC600 $(DEF) -O0 -g 

%.ARC600-O3-g.elf:  $(ARC600-O3-g_OBJ)
	@    echo "# Linking ARC600 $@"
	$(V) $(ARC600_LINK) -o $@ $^ $(ARC600_LDFLAGS) -lm
	
%.ARC600-O3-g.o: %.c
	@    echo "# Compiling ARC600 $<"
	$(V) $(ARC600_CC) -c -o $@ $< -DARC600 $(DEF) -O3 -g 

%.ARC700-O2-g.elf:  $(ARC700-O2-g_OBJ)
	@    echo "# Linking ARC700 $@"
	$(V) $(ARC700_LINK) -o $@ $^ $(ARC700_LDFLAGS) -lm
	
%.ARC700-O2-g.o: %.c
	@    echo "# Compiling ARC700 $<"
	$(V) $(ARC700_CC) -c -o $@ $< -DARC700 $(DEF) -O2 -g 

%.ARC700-O1-g.elf:  $(ARC700-O1-g_OBJ)
	@    echo "# Linking ARC700 $@"
	$(V) $(ARC700_LINK) -o $@ $^ $(ARC700_LDFLAGS) -lm
	
%.ARC700-O1-g.o: %.c
	@    echo "# Compiling ARC700 $<"
	$(V) $(ARC700_CC) -c -o $@ $< -DARC700 $(DEF) -O1 -g 

clean::
	- rm -f $(ELF)
