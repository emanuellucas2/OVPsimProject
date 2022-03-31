ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

OPTIMISATION?=-O0 -g 

CROSS=OR1K
SRC?=multicore2_reader.c multicore2_writer.c
SRCINC?=

INCOBJ=$(patsubst %.c,%.$(CROSS).o,$(SRCINC))
EXE=$(patsubst %.c,%.$(CROSS).elf,$(SRC))

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(EXE)

%.$(CROSS).elf: %.$(CROSS).o $(INCOBJ)
	@    echo "# Linking $(CROSS) $@"
	$(V) $(IMPERAS_LINK) -o $@ $^ $(IMPERAS_LDFLAGS) -lm

%.$(CROSS).o: %.c
	@    echo "# Compiling $(CROSS) $<"
	$(V) $(IMPERAS_CC) -c -o $@ $< -D$(CROSS) $(OPTIMISATION)

clean::
	- rm -f *.$(CROSS).elf *.$(CROSS).o
