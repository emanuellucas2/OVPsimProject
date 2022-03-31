ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=OR1K

all: hello.$(CROSS).s19

include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/OR1K.makefile.include
ifeq ($(OR1K_CC),)
    IMPERAS_ERROR := $(error "Please install the OR1K toolchain")
endif

# Convert elf file to Srecord file format
hello.$(CROSS).s19: hello.$(CROSS).elf
	$(V) ${IMPERAS_OBJCOPY} -O srec hello.$(CROSS).elf hello.$(CROSS).tmp.s19
	$(V) $(IMPERAS_NM) -g hello.$(CROSS).elf > hello.$(CROSS).tmp.nm
	$(V) awk -f symbols.awk hello.$(CROSS).tmp.nm > hello.$(CROSS).tmp.symbols
	$(V) cat hello.$(CROSS).tmp.s19 hello.$(CROSS).tmp.symbols > hello.$(CROSS).s19

hello.$(CROSS).elf: hello.$(CROSS).o
	$(V) echo "Linking Application $@"
	$(V) $(IMPERAS_LINK) -o $@  $< $(IMPERAS_LDFLAGS)

hello.$(CROSS).o: hello.c
	$(V) echo "Compiling Application $@"
	$(V) $(IMPERAS_CC)  -c  -o $@  $^


clean:
	$(V) - rm -f  hello.$(CROSS).s19 hello.$(CROSS).o hello.$(CROSS).tmp.*
