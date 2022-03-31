ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

OPTIMISATION?=-g

CROSS?=OR1K
SRC?=asmtest.S
SRCINC?=

INCOBJ=$(patsubst %.S,%.$(CROSS).o,$(SRCINC))
EXE=$(patsubst %.S,%.$(CROSS).elf,$(SRC)) 
OD=$(patsubst %.S,%.$(CROSS).od,$(SRC))

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(EXE) $(OD)

%.$(CROSS).od: %.$(CROSS).elf
	@    echo "# Objdumping $(CROSS) $@"
	$(V) $($(CROSS)_OBJDUMP) -sdx $^ > $@

%.$(CROSS).elf: %.$(CROSS).o $(INCOBJ)
	@    echo "# Linking $(CROSS) $@"
	$(V) $($(CROSS)_LD) -o $@ --section-start .text=0 $^

%.$(CROSS).o: %.S
	@    echo "# Compiling $(CROSS) $<"
	$(V) $($(CROSS)_CC) -c -o $@ $< $(OPTIMISATION)
	
clean::
	- rm -f $(EXE) $(OD) *.$(CROSS).o
