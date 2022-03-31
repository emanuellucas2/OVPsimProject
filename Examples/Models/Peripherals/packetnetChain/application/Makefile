ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include


# Cross compiler setups
CROSS=RISCV32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Cross $(CROSS) : Please install required Cross Compiler toolchain")
endif

EXE = application.$(CROSS).elf

all: $(EXE)

%.$(CROSS).od: %.$(CROSS).elf
	@     echo "Obdump $@"
	$(V)  $($(CROSS)_OBJDUMP) -D $< > $@

%.$(CROSS).elf: %.$(CROSS).o
	@     echo "Linking $@"
	$(V)  $($(CROSS)_LINK) -o $@ $< $($(CROSS)_LDFLAGS)

%.$(CROSS).o: %.c
	@     echo "Compiling $<"
	$(V)  $($(CROSS)_CC) -c -o $@ $< -gdwarf-2 -O0

clean:
	rm -f $(EXE)
