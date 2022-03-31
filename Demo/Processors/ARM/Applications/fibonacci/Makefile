ifndef IMPERAS_HOME
IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

#
# The list of ELF files this Makefile will build from C source file(s) in this directory
#
ELF = fibonacci.ARM7TDMI-O0-g.elf fibonacci.ARM_CORTEX_A-O3-g.elf fibonacci.ARM9T-O3-g.elf fibonacci.ARM9E-O3-g.elf fibonacci.ARM11-O3-g.elf fibonacci.ARM_CORTEX_R4-O3-g.elf fibonacci.ARM_CORTEX_R4F-O3-g.elf fibonacci.AARCH32-O3-g.elf fibonacci.AARCH64-O3-g.elf fibonacci.ARM_CORTEX_M0-O3-g.elf fibonacci.ARM_CORTEX_M3-O3-g.elf fibonacci.ARM_CORTEX_M1-O3-g.elf fibonacci.ARM_CORTEX_M4-O3-g.elf fibonacci.ARM_CORTEX_M4F-O3-g.elf fibonacci.ARM_CORTEX_M7-O3-g.elf fibonacci.ARM_CORTEX_M7F-O3-g.elf 

#
# Include Cross Compilers
#

# include Cross Compiler settings for ARM7TDMI
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM7TDMI.makefile.include
ifeq ($(ARM7TDMI_CC),)
	IMPERAS_ERROR := $(error "Error : ARM7TDMI_CC not set. Please check installation of toolchain for ARM7TDMI")
endif

# include Cross Compiler settings for ARM_CORTEX_A
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_A.makefile.include
ifeq ($(ARM_CORTEX_A_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_A_CC not set. Please check installation of toolchain for ARM_CORTEX_A")
endif

# include Cross Compiler settings for ARM9T
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM9T.makefile.include
ifeq ($(ARM9T_CC),)
	IMPERAS_ERROR := $(error "Error : ARM9T_CC not set. Please check installation of toolchain for ARM9T")
endif

# include Cross Compiler settings for ARM9E
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM9E.makefile.include
ifeq ($(ARM9E_CC),)
	IMPERAS_ERROR := $(error "Error : ARM9E_CC not set. Please check installation of toolchain for ARM9E")
endif

# include Cross Compiler settings for ARM11
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM11.makefile.include
ifeq ($(ARM11_CC),)
	IMPERAS_ERROR := $(error "Error : ARM11_CC not set. Please check installation of toolchain for ARM11")
endif

# include Cross Compiler settings for ARM_CORTEX_R4
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_R4.makefile.include
ifeq ($(ARM_CORTEX_R4_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_R4_CC not set. Please check installation of toolchain for ARM_CORTEX_R4")
endif

# include Cross Compiler settings for ARM_CORTEX_R4F
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_R4F.makefile.include
ifeq ($(ARM_CORTEX_R4F_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_R4F_CC not set. Please check installation of toolchain for ARM_CORTEX_R4F")
endif

# include Cross Compiler settings for AARCH32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/AARCH32.makefile.include
ifeq ($(AARCH32_CC),)
	IMPERAS_ERROR := $(error "Error : AARCH32_CC not set. Please check installation of toolchain for AARCH32")
endif

# include Cross Compiler settings for AARCH64
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/AARCH64.makefile.include
ifeq ($(AARCH64_CC),)
	IMPERAS_ERROR := $(error "Error : AARCH64_CC not set. Please check installation of toolchain for AARCH64")
endif

# include Cross Compiler settings for ARM_CORTEX_M0
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_M0.makefile.include
ifeq ($(ARM_CORTEX_M0_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_M0_CC not set. Please check installation of toolchain for ARM_CORTEX_M0")
endif

# include Cross Compiler settings for ARM_CORTEX_M3
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_M3.makefile.include
ifeq ($(ARM_CORTEX_M3_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_M3_CC not set. Please check installation of toolchain for ARM_CORTEX_M3")
endif

# include Cross Compiler settings for ARM_CORTEX_M1
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_M1.makefile.include
ifeq ($(ARM_CORTEX_M1_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_M1_CC not set. Please check installation of toolchain for ARM_CORTEX_M1")
endif

# include Cross Compiler settings for ARM_CORTEX_M4
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_M4.makefile.include
ifeq ($(ARM_CORTEX_M4_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_M4_CC not set. Please check installation of toolchain for ARM_CORTEX_M4")
endif

# include Cross Compiler settings for ARM_CORTEX_M4F
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_M4F.makefile.include
ifeq ($(ARM_CORTEX_M4F_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_M4F_CC not set. Please check installation of toolchain for ARM_CORTEX_M4F")
endif

# include Cross Compiler settings for ARM_CORTEX_M7
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_M7.makefile.include
ifeq ($(ARM_CORTEX_M7_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_M7_CC not set. Please check installation of toolchain for ARM_CORTEX_M7")
endif

# include Cross Compiler settings for ARM_CORTEX_M7F
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/ARM_CORTEX_M7F.makefile.include
ifeq ($(ARM_CORTEX_M7F_CC),)
	IMPERAS_ERROR := $(error "Error : ARM_CORTEX_M7F_CC not set. Please check installation of toolchain for ARM_CORTEX_M7F")
endif

#
# Source files
#
SRC = $(wildcard *.c)

#
# Create Source to Object file relation
#
ARM7TDMI-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM7TDMI-O0-g.o,$(S)))
ARM_CORTEX_A-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_A-O3-g.o,$(S)))
ARM9T-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM9T-O3-g.o,$(S)))
ARM9E-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM9E-O3-g.o,$(S)))
ARM11-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM11-O3-g.o,$(S)))
ARM_CORTEX_R4-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_R4-O3-g.o,$(S)))
ARM_CORTEX_R4F-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_R4F-O3-g.o,$(S)))
AARCH32-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.AARCH32-O3-g.o,$(S)))
AARCH64-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.AARCH64-O3-g.o,$(S)))
ARM_CORTEX_M0-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_M0-O3-g.o,$(S)))
ARM_CORTEX_M3-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_M3-O3-g.o,$(S)))
ARM_CORTEX_M1-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_M1-O3-g.o,$(S)))
ARM_CORTEX_M4-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_M4-O3-g.o,$(S)))
ARM_CORTEX_M4F-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_M4F-O3-g.o,$(S)))
ARM_CORTEX_M7-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_M7-O3-g.o,$(S)))
ARM_CORTEX_M7F-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_M7F-O3-g.o,$(S)))

#
# Rules to build ELF files
#
all: $(ELF)

%.ARM7TDMI-O0-g.elf:  $(ARM7TDMI-O0-g_OBJ)
	@    echo "# Linking ARM7TDMI $@"
	$(V) $(ARM7TDMI_LINK) -o $@ $^ $(ARM7TDMI_LDFLAGS) -lm
	
%.ARM7TDMI-O0-g.o: %.c
	@    echo "# Compiling ARM7TDMI $<"
	$(V) $(ARM7TDMI_CC) -c -o $@ $< -DARM7TDMI $(DEF) -O0 -g 

%.ARM_CORTEX_A-O3-g.elf:  $(ARM_CORTEX_A-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_A $@"
	$(V) $(ARM_CORTEX_A_LINK) -o $@ $^ $(ARM_CORTEX_A_LDFLAGS) -lm
	
%.ARM_CORTEX_A-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_A $<"
	$(V) $(ARM_CORTEX_A_CC) -c -o $@ $< -DARM_CORTEX_A $(DEF) -O3 -g 

%.ARM9T-O3-g.elf:  $(ARM9T-O3-g_OBJ)
	@    echo "# Linking ARM9T $@"
	$(V) $(ARM9T_LINK) -o $@ $^ $(ARM9T_LDFLAGS) -lm
	
%.ARM9T-O3-g.o: %.c
	@    echo "# Compiling ARM9T $<"
	$(V) $(ARM9T_CC) -c -o $@ $< -DARM9T $(DEF) -O3 -g 

%.ARM9E-O3-g.elf:  $(ARM9E-O3-g_OBJ)
	@    echo "# Linking ARM9E $@"
	$(V) $(ARM9E_LINK) -o $@ $^ $(ARM9E_LDFLAGS) -lm
	
%.ARM9E-O3-g.o: %.c
	@    echo "# Compiling ARM9E $<"
	$(V) $(ARM9E_CC) -c -o $@ $< -DARM9E $(DEF) -O3 -g 

%.ARM11-O3-g.elf:  $(ARM11-O3-g_OBJ)
	@    echo "# Linking ARM11 $@"
	$(V) $(ARM11_LINK) -o $@ $^ $(ARM11_LDFLAGS) -lm
	
%.ARM11-O3-g.o: %.c
	@    echo "# Compiling ARM11 $<"
	$(V) $(ARM11_CC) -c -o $@ $< -DARM11 $(DEF) -O3 -g 

%.ARM_CORTEX_R4-O3-g.elf:  $(ARM_CORTEX_R4-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_R4 $@"
	$(V) $(ARM_CORTEX_R4_LINK) -o $@ $^ $(ARM_CORTEX_R4_LDFLAGS) -lm
	
%.ARM_CORTEX_R4-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_R4 $<"
	$(V) $(ARM_CORTEX_R4_CC) -c -o $@ $< -DARM_CORTEX_R4 $(DEF) -O3 -g 

%.ARM_CORTEX_R4F-O3-g.elf:  $(ARM_CORTEX_R4F-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_R4F $@"
	$(V) $(ARM_CORTEX_R4F_LINK) -o $@ $^ $(ARM_CORTEX_R4F_LDFLAGS) -lm
	
%.ARM_CORTEX_R4F-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_R4F $<"
	$(V) $(ARM_CORTEX_R4F_CC) -c -o $@ $< -DARM_CORTEX_R4F $(DEF) -O3 -g 

%.AARCH32-O3-g.elf:  $(AARCH32-O3-g_OBJ)
	@    echo "# Linking AARCH32 $@"
	$(V) $(AARCH32_LINK) -o $@ $^ $(AARCH32_LDFLAGS) -lm
	
%.AARCH32-O3-g.o: %.c
	@    echo "# Compiling AARCH32 $<"
	$(V) $(AARCH32_CC) -c -o $@ $< -DAARCH32 $(DEF) -O3 -g 

%.AARCH64-O3-g.elf:  $(AARCH64-O3-g_OBJ)
	@    echo "# Linking AARCH64 $@"
	$(V) $(AARCH64_LINK) -o $@ $^ $(AARCH64_LDFLAGS) -lm
	
%.AARCH64-O3-g.o: %.c
	@    echo "# Compiling AARCH64 $<"
	$(V) $(AARCH64_CC) -c -o $@ $< -DAARCH64 $(DEF) -O3 -g 

%.ARM_CORTEX_M0-O3-g.elf:  $(ARM_CORTEX_M0-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_M0 $@"
	$(V) $(ARM_CORTEX_M0_LINK) -o $@ $^ $(ARM_CORTEX_M0_LDFLAGS) -lm
	
%.ARM_CORTEX_M0-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_M0 $<"
	$(V) $(ARM_CORTEX_M0_CC) -c -o $@ $< -DARM_CORTEX_M0 $(DEF) -O3 -g 

%.ARM_CORTEX_M3-O3-g.elf:  $(ARM_CORTEX_M3-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_M3 $@"
	$(V) $(ARM_CORTEX_M3_LINK) -o $@ $^ $(ARM_CORTEX_M3_LDFLAGS) -lm
	
%.ARM_CORTEX_M3-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_M3 $<"
	$(V) $(ARM_CORTEX_M3_CC) -c -o $@ $< -DARM_CORTEX_M3 $(DEF) -O3 -g 

%.ARM_CORTEX_M1-O3-g.elf:  $(ARM_CORTEX_M1-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_M1 $@"
	$(V) $(ARM_CORTEX_M1_LINK) -o $@ $^ $(ARM_CORTEX_M1_LDFLAGS) -lm
	
%.ARM_CORTEX_M1-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_M1 $<"
	$(V) $(ARM_CORTEX_M1_CC) -c -o $@ $< -DARM_CORTEX_M1 $(DEF) -O3 -g 

%.ARM_CORTEX_M4-O3-g.elf:  $(ARM_CORTEX_M4-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_M4 $@"
	$(V) $(ARM_CORTEX_M4_LINK) -o $@ $^ $(ARM_CORTEX_M4_LDFLAGS) -lm
	
%.ARM_CORTEX_M4-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_M4 $<"
	$(V) $(ARM_CORTEX_M4_CC) -c -o $@ $< -DARM_CORTEX_M4 $(DEF) -O3 -g 

%.ARM_CORTEX_M4F-O3-g.elf:  $(ARM_CORTEX_M4F-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_M4F $@"
	$(V) $(ARM_CORTEX_M4F_LINK) -o $@ $^ $(ARM_CORTEX_M4F_LDFLAGS) -lm
	
%.ARM_CORTEX_M4F-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_M4F $<"
	$(V) $(ARM_CORTEX_M4F_CC) -c -o $@ $< -DARM_CORTEX_M4F $(DEF) -O3 -g 

%.ARM_CORTEX_M7-O3-g.elf:  $(ARM_CORTEX_M7-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_M7 $@"
	$(V) $(ARM_CORTEX_M7_LINK) -o $@ $^ $(ARM_CORTEX_M7_LDFLAGS) -lm
	
%.ARM_CORTEX_M7-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_M7 $<"
	$(V) $(ARM_CORTEX_M7_CC) -c -o $@ $< -DARM_CORTEX_M7 $(DEF) -O3 -g 

%.ARM_CORTEX_M7F-O3-g.elf:  $(ARM_CORTEX_M7F-O3-g_OBJ)
	@    echo "# Linking ARM_CORTEX_M7F $@"
	$(V) $(ARM_CORTEX_M7F_LINK) -o $@ $^ $(ARM_CORTEX_M7F_LDFLAGS) -lm
	
%.ARM_CORTEX_M7F-O3-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_M7F $<"
	$(V) $(ARM_CORTEX_M7F_CC) -c -o $@ $< -DARM_CORTEX_M7F $(DEF) -O3 -g 

clean::
	- rm -f $(ELF)
