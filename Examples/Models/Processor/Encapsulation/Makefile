ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

XTHOME?=externalISS

RISC32MODEL = risc32Model.$(IMPERAS_SHRSUF)
APPLICATION = testcase.risc32
EXTERNALISS = libXTrisc32.$(IMPERAS_SHRSUF)
PLATFORM    = platform.exe

all: $(EXTERNALISS) $(RISC32MODEL) $(APPLICATION) $(PLATFORM)

#
# Processor Section
#
LDFLAGS = $(OTHER_LDFLAGS)

# export.def and version.script provide symbols to export
ifeq ($(IMPERAS_UNAME),Linux)
  LDFLAGS += -Wl,--version-script=$(IMPERAS_HOME)/ImperasLib/buildutils/version.script
else
  LDFLAGS += $(IMPERAS_HOME)/ImperasLib/buildutils/export.def
endif
LDFLAGS+=-L$(XTHOME) -lXTrisc32

CFLAGS = $(SIM_CFLAGS) $(OTHER_CFLAGS)

CFLAGS+=-I$(XTHOME)

SRCS.c = $(sort $(wildcard *.c))
SRCS.S = $(sort $(wildcard *.S))
OBJS.c = $(foreach obj, $(SRCS.c:.c=.o), $(obj))
OBJS.S = $(foreach obj, $(SRCS.S:.S=.o), $(obj))
OBJS   = $(OBJS.c) $(OBJS.S)
SOLIB  = $(RISC32MODEL)

%.o: %.c
	$(V) echo "Compiling Processor $@"
	$(V) $(HOST_GCC) $(CFLAGS) $(SIM_CFLAGS) -c -o $@ $^

$(SOLIB): $(OBJS)
	$(V) echo "Linking Processor"
	$(V) $(HOST_GCC) $(CFLAGS) $(SIM_LDFLAGS) --shared -o $@ $^ $(IMPERAS_VMISTUBS) $(LDFLAGS)

#
# Imported externalISS Simulator Section
#
$(EXTERNALISS): $(XTHOME)/$(EXTERNALISS)
	cp $< $@

RISC32SSEMBLER=asmXtrisc32.exe
$(XTHOME)/$(RISC32SSEMBLER) $(XTHOME)/$(EXTERNALISS): $(XTHOME)/XTrisc32.c $(XTHOME)/XTrisc32.h $(XTHOME)/asmXtrisc32.c
	$(MAKE) -C $(XTHOME)

#
# platform Section
#
MORPHER_FILE   = ./$(RISC32MODEL)

$(PLATFORM): platform/platform.o
	$(V) echo "Linking platform $@"
	$(V) $(HOST_GCC) $(CFLAGS) -o $@  $^  $(CFLAGS) $(SIM_LDFLAGS) 

platform/platform.o: platform/platform.c
	$(V) echo "Compiling platform $@"
	$(V) $(HOST_GCC) $(CFLAGS) -c -o $@  $< $(CFLAGS) \
	  -DMORPHER_FILE="\"${MORPHER_FILE}\""

#
# Application section
#
$(APPLICATION): application/testcase.S $(XTHOME)/$(RISC32SSEMBLER) 
	$(V) echo "Assembling Application $@"
	$(XTHOME)/$(RISC32SSEMBLER) $< $@

#
# Cleanup section
#
clean:
	$(V) - rm -f $(APPLICATION)
	$(V) - rm -f $(OBJS) $(SOLIB)
	$(V) - rm -f $(PLATFORM)
	$(V) - rm -f $(EXTERNALISS) $(XTHOME)/$(EXTERNALISS) 
	$(V) - rm -f $(XTHOME)/$(RISC32SSEMBLER)
