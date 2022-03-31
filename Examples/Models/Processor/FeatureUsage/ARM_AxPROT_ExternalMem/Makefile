PLATFORM=platform/platform.${IMPERAS_ARCH}.exe
APPLICATION=application/asmtest.elf

run : $(PLATFORM) $(APPLICATION)
	$(PLATFORM) -program $(APPLICATION)

$(APPLICATION):
	$(MAKE) -C application

$(PLATFORM):
	$(MAKE) -C platform

clean:
	$(MAKE) -C application clean
	$(MAKE) -C platform clean


help:
	@echo The following targets are available to start simulation
	@echo run    : run simulation using a C Platform
