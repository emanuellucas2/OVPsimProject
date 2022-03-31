ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

# CrossCompiler Selection
CROSS?=OR1K

all: app.$(CROSS).elf 

# APP
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

%.$(CROSS).elf: %.$(CROSS).o
	$(V) echo "Linking Application $@"
	$(V) $($(CROSS)_LINK) -ggdb -o $@  $^ $(IMPERAS_LDFLAGS)

%.$(CROSS).o: %.c
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC) -ggdb -c -Iapplication -o $@  $<

clean:
	$(V) - rm -f app.$(CROSS).elf app.$(CROSS).o

