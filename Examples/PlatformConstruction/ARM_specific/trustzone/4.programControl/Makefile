ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

CROSS ?= ARM_CORTEX_A9

run: platform/platform.$(IMPERAS_ARCH).exe application/application.$(CROSS).elf 
	platform/platform.$(IMPERAS_ARCH).exe \
      --program application/application.$(CROSS).elf \
      --excludem ARM_MORPH_BII \
    | tee imperas.log
	@echo
	@echo "*** uart0.log: ***"
	@cat uart0.log

platform/platform.$(IMPERAS_ARCH).exe : platform/platform.c platform/platform.op.tcl
	$(MAKE) -C platform    NOVLNV=1

application/application.$(CROSS).elf: application/application.c
	$(MAKE) -C application

clean:
	rm -rf *.log 
	$(MAKE) -C platform    NOVLNV=1 clean
	$(MAKE) -C application          clean
