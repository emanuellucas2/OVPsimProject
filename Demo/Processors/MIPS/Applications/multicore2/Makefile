ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = multicore2.IMG_MIPS32R2LE-O1-g.elf multicore2.IMG_UMIPS32R2LE-O1-g.elf multicore2.IMG_MIPS32R2-O1-g.elf multicore2.IMG_MIPS64R2-O1-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for IMG_MIPS32R2LE
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/IMG_MIPS32R2LE.makefile.include
ifeq ($(IMG_MIPS32R2LE_CC),)
	IMPERAS_ERROR := $(error "Error : IMG_MIPS32R2LE_CC not set. Please check installation of toolchain for IMG_MIPS32R2LE")
endif

# include Cross Compiler settings for IMG_UMIPS32R2LE
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/IMG_UMIPS32R2LE.makefile.include
ifeq ($(IMG_UMIPS32R2LE_CC),)
	IMPERAS_ERROR := $(error "Error : IMG_UMIPS32R2LE_CC not set. Please check installation of toolchain for IMG_UMIPS32R2LE")
endif

# include Cross Compiler settings for IMG_MIPS32R2
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/IMG_MIPS32R2.makefile.include
ifeq ($(IMG_MIPS32R2_CC),)
	IMPERAS_ERROR := $(error "Error : IMG_MIPS32R2_CC not set. Please check installation of toolchain for IMG_MIPS32R2")
endif

# include Cross Compiler settings for IMG_MIPS64R2
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/IMG_MIPS64R2.makefile.include
ifeq ($(IMG_MIPS64R2_CC),)
	IMPERAS_ERROR := $(error "Error : IMG_MIPS64R2_CC not set. Please check installation of toolchain for IMG_MIPS64R2")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
IMG_MIPS32R2LE-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.IMG_MIPS32R2LE-O1-g.o,$(S)))
IMG_UMIPS32R2LE-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.IMG_UMIPS32R2LE-O1-g.o,$(S)))
IMG_MIPS32R2-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.IMG_MIPS32R2-O1-g.o,$(S)))
IMG_MIPS64R2-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.IMG_MIPS64R2-O1-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.IMG_MIPS32R2LE-O1-g.elf:  $(IMG_MIPS32R2LE-O1-g_OBJ)
	@    echo "# Linking IMG_MIPS32R2LE $@"
	$(V) $(IMG_MIPS32R2LE_LINK) -o $@ $^ $(IMG_MIPS32R2LE_LDFLAGS) -lm
	
%.IMG_MIPS32R2LE-O1-g.o: %.c
	@    echo "# Compiling IMG_MIPS32R2LE $<"
	$(V) $(IMG_MIPS32R2LE_CC) -c -o $@ $< -DIMG_MIPS32R2LE $(DEF) -O1 -g 

%.IMG_UMIPS32R2LE-O1-g.elf:  $(IMG_UMIPS32R2LE-O1-g_OBJ)
	@    echo "# Linking IMG_UMIPS32R2LE $@"
	$(V) $(IMG_UMIPS32R2LE_LINK) -o $@ $^ $(IMG_UMIPS32R2LE_LDFLAGS) -lm
	
%.IMG_UMIPS32R2LE-O1-g.o: %.c
	@    echo "# Compiling IMG_UMIPS32R2LE $<"
	$(V) $(IMG_UMIPS32R2LE_CC) -c -o $@ $< -DIMG_UMIPS32R2LE $(DEF) -O1 -g 

%.IMG_MIPS32R2-O1-g.elf:  $(IMG_MIPS32R2-O1-g_OBJ)
	@    echo "# Linking IMG_MIPS32R2 $@"
	$(V) $(IMG_MIPS32R2_LINK) -o $@ $^ $(IMG_MIPS32R2_LDFLAGS) -lm
	
%.IMG_MIPS32R2-O1-g.o: %.c
	@    echo "# Compiling IMG_MIPS32R2 $<"
	$(V) $(IMG_MIPS32R2_CC) -c -o $@ $< -DIMG_MIPS32R2 $(DEF) -O1 -g 

%.IMG_MIPS64R2-O1-g.elf:  $(IMG_MIPS64R2-O1-g_OBJ)
	@    echo "# Linking IMG_MIPS64R2 $@"
	$(V) $(IMG_MIPS64R2_LINK) -o $@ $^ $(IMG_MIPS64R2_LDFLAGS) -lm
	
%.IMG_MIPS64R2-O1-g.o: %.c
	@    echo "# Compiling IMG_MIPS64R2 $<"
	$(V) $(IMG_MIPS64R2_CC) -c -o $@ $< -DIMG_MIPS64R2 $(DEF) -O1 -g 

clean::
	- rm -f $(ELF)
