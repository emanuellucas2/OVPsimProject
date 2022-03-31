PLATFORM=platform/platform.${IMPERAS_ARCH}.exe
APPLICATION=application/asmtest.elf
SR_FILE=state

build : $(PLATFORM) $(APPLICATION)

run : $(PLATFORM) $(APPLICATION)
	@echo "Run"
	$(PLATFORM) -program $(APPLICATION)
	@echo "Run and Save State after 500 instructions"
	$(PLATFORM) -program $(APPLICATION) -icount 500 -srfile $(SR_FILE) -dosave
	@echo "Restore State and Run"
	$(PLATFORM) -program $(APPLICATION) -icount -1  -srfile $(SR_FILE) -dorestore

$(APPLICATION):
	$(MAKE) -C application

$(PLATFORM):
	$(MAKE) -C platform

clean:
	$(MAKE) -C application clean
	$(MAKE) -C platform clean
	rm -f $(SR_FILE)


help:
	@echo The following targets are available to start simulation
	@echo build  : build application and Platform
	@echo run    : run simulation using a Platform saving and restoring state
