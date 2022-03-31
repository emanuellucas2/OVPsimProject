ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include


CROSS?=OR1K

all: model.$(IMPERAS_SHRSUF) \
     application/application.$(CROSS).elf application/asmtest.$(CROSS).elf \
     platform/platform.$(IMPERAS_ARCH).exe

# Building Processor
NOVLNV?=1
-include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host

application/application.$(CROSS).elf: application/application.c
application/asmtest.$(CROSS).elf:     application/asmtest.S

application/application.$(CROSS).elf application/asmtest.$(CROSS).elf:
	@echo "Building Application"
	$(MAKE) -C application CROSS=$(CROSS)
	 
platform/platform.$(IMPERAS_ARCH).exe: platform/platform.c
	@echo "Building Platform"
	$(MAKE) -C platform NOVLNV=$(NOVLNV)

clean::
	$(MAKE) -C application clean CROSS=$(CROSS)
	$(MAKE) -C platform    clean NOVLNV=$(NOVLNV)
 