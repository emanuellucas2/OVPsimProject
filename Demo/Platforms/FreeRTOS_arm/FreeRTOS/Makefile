IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include


OPTIMIZATION?=-O0 -g 

FREERTOS_ROOT?=FreeRTOSV7.1.1

IMPERAS_ERROR := $(if $(wildcard $(FREERTOS_ROOT)*),, $(error "ERROR: Please set FREERTOS_ROOT to FreeRTOSV7.1.1 Source installation root."))

CROSS=ARM_CORTEX_M3

APP=FreeRTOSDemo
APPELF=$(APP).$(CROSS).elf
APPELFOD=$(APP).$(CROSS).od


FREERTOS_SOURCE=$(FREERTOS_ROOT)/Source
FREERTOS_DEMO_COMMON=$(FREERTOS_ROOT)/Demo/Common


CSRC=$(wildcard Application/*.c)               \
        $(wildcard BoardSupportPackage/*.c)

PCSRC=$(wildcard $(FREERTOS_SOURCE)/*.c)                      \
      $(wildcard $(FREERTOS_SOURCE)/portable/MemMang/heap_1.c)     \
      $(wildcard $(FREERTOS_SOURCE)/portable/GCC/ARM_CM3/port.c) \
      $(wildcard $(FREERTOS_DEMO_COMMON)/Minimal/crflash.c)

SSRC=$(wildcard Application/*.s)

APPSRC=$(CAPPSRC) $(SAPPSRC)

APPOBJ=$(patsubst $(FREERTOS_ROOT)/%.c,Build/obj/%.o,$(PCSRC)) \
       $(patsubst $(FREERTOS_ROOT)/%.s,Build/obj/%.o,$(PSSRC)) \
       $(patsubst %.c,Build/obj/%.o,$(CSRC)) \
       $(patsubst %.s,Build/obj/%.o,$(SSRC))


APPINCLUDE=-I. -IApplication -IBoardSupportPackage \
           -I$(FREERTOS_SOURCE)/include \
           -I$(FREERTOS_SOURCE)/portable/GCC/ARM_CM3 \
           -I$(FREERTOS_DEMO_COMMON)/include
        
ENTRY_RTOSDemo=ResetISR
CFLAGS+=-D inline= --entry $(ENTRY_RTOSDemo)

APPDBG=-g 
APPOPT=-O0 $(APPDBG)

$(CROSS)_LINKER_SCRIPT=-T standalone.ld
$(CROSS)_SEMIHOST=
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain that supports $(CROSS)")
endif

all: $(APPELF)

$(APPELF): $(APPOBJ)
	@    echo "# Linking $@ from $^"
	$(V) mkdir -p $(dir $@)
	$(V) $($(CROSS)_LINK) -o $@ $^ $($(CROSS)_LDFLAGS) -nostdlib -lc -lm $(APPDBG)

Build/obj/%.o: $(FREERTOS_ROOT)/%.c
	@    echo "# Compiling $@"
	$(V) mkdir -p $(dir $@)
	$(V) $($(CROSS)_CC) $(APPINCLUDE) -c -o $@ $< $(APPOPT)

Build/obj/%.o: $(FREERTOS_ROOT)/%.s
	@    echo "# Assembling $@"
	$(V) mkdir -p $(dir $@)
	$(V) $($(CROSS)_AS) $(APPINCLUDE) -o $@ $<  $(APPDBG)

Build/obj/%.o: %.c
	@    echo "# Compiling $@"
	$(V) mkdir -p $(dir $@)
	$(V) $($(CROSS)_CC) $(APPINCLUDE) -c -o $@ $< $(APPOPT)

Build/obj/%.o: %.s
	@    echo "# Assembling $@"
	$(V) mkdir -p $(dir $@)
	$(V) $($(CROSS)_AS) $(APPINCLUDE) -o $@ $< $(APPDBG)

clean::
	- rm -f $(APPOBJ) $(APPELF) $(APPELFOD) 
	- rm -rf Build
