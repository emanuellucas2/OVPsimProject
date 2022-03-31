ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=RISCV32

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

SRC     = $(wildcard *.S)
ELF     = $(SRC:.S=.$(CROSS).elf)
OD      = $(SRC:.S=.$(CROSS).od)
HEX     = $(SRC:.S=.$(CROSS).hex)

all: $(ELF) $(OD) $(HEX)


%.$(CROSS).elf: %.S
	$($(CROSS)_CC) $($(CROSS)_CFLAGS) $(CFLAGS) -nostartfiles -Ttext=0x0 -o $@ $<

%.$(CROSS).od: %.$(CROSS).elf
	$(V) echo "Creating Objdump of $@"
	$(V) $($(CROSS)_OBJDUMP) -D $^ > $@ 

%.$(CROSS).hex: %.$(CROSS).elf
	$(V) echo "Convert elf to hex $@"
	$(V) $($(CROSS)_OBJCOPY) --output-target=ihex $^ $@

clean:
	- rm -f $(ELF) $(OD) $(BIN) $(HEX)
	- rm -f *.o
