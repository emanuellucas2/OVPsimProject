ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=AARCH64
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

# define base address (use 0x400000 if unspecified)
#BASE64?=0x400000
BASE64?=0
# define default configurations
USE_GICV3?=0
USE_GICV3_VCPU4K?=0
GIC_SECURE?=1

TEST  = asm
EXE   = $(TEST).$(CROSS).elf
EXEOD = $(patsubst %.elf,%.od,$(EXE))
EXERE = $(patsubst %.elf,%.re,$(EXE))

all: $(EXE) $(EXEOD) $(EXERE)

%.$(CROSS).elf: %.o
	@echo "# Linking $@"
	$(V)  $(IMPERAS_LD) -o $@ $< -Ttext=$(BASE64)

%.o: %.S
	@echo "# Assembling $<"
	$(V)  $(IMPERAS_CC)  -o $@ $< -DUSE_GICV3=$(USE_GICV3) -DUSE_GICV3_VCPU4K=$(USE_GICV3_VCPU4K) -DGIC_SECURE=$(GIC_SECURE) -c -march=armv8-a

%.$(CROSS).od: %.$(CROSS).elf
	@echo "# ObjDump $@"
	$(V)  $(IMPERAS_OBJDUMP) -d $^ >  $@

%.$(CROSS).re: %.$(CROSS).elf
	@echo "# ReadeElf $@"
	$(V)  $(IMPERAS_READELF) -d $^ >  $@

clean::
	-rm -f $(EXE) $(EXEOD) $(EXERE)
	-rm -f  *.o
