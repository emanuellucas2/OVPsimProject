ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=RISCV32

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

# O1 optimisation to use registers and not moving to/from memory
OPTIMISATION?=-O1 -fno-omit-frame-pointer

EXCEPTION = exception.$(CROSS).elf

SRC_C = test_main.c test_lib_c.c
OBJ_C = $(patsubst %.c,%.$(CROSS).o,$(SRC_C))

SRC_ASM = test_main.c test_lib_asm.c
OBJ_ASM = $(patsubst %.c,%.$(CROSS).o,$(SRC_ASM))

EXE = test_c.$(CROSS).elf test_asm.$(CROSS).elf
OD  = test_c.$(CROSS).od  test_asm.$(CROSS).od

all: $(EXE) $(OD) $(EXCEPTION)

test_c.$(CROSS).elf: $(OBJ_C)
	$(V)  echo "# Linking $@"
	$(V)  $(IMPERAS_LINK) -o $@ $^ $(IMPERAS_LDFLAGS) -lm

test_asm.$(CROSS).elf: $(OBJ_ASM)
	$(V)  echo "# Linking $@"
	$(V)  $(IMPERAS_LINK) -o $@ $^ $(IMPERAS_LDFLAGS) -lm

%.$(CROSS).od: %.$(CROSS).elf
	$(V)  $(IMPERAS_OBJDUMP) -D $^ > $@

%.$(CROSS).o: %.c
	$(V)  echo "# Compiling $<"
	$(V)  $(IMPERAS_CC) -g  -c -o $@ $< $(OPTIMISATION)

exception.$(CROSS).elf: exception.S
	$(V)  echo "# Linking $@"
	$(V)  $(IMPERAS_CC) -o $@ $< -Ttext=0x00000000 -nostartfiles

clean:
	-rm -f $(EXE) $(OD) $(OBJ_C)  $(OBJ_ASM) $(EXCEPTION) 
