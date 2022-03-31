# all local builds
NOVLNV?=1

include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.common

platform.$(IMPERAS_ARCH).exe : platform.cpp
	@ echo "# Build $@"
	$(V) $(MAKE) -f $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.TLM.platform \
                        NOVLNV=1 VERBOSE=$(VERBOSE)

clean:
	$(V) $(MAKE) -f $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.TLM.platform \
                        NOVLNV=1 VERBOSE=$(VERBOSE) clean

realclean: clean
	$(V) rm -f *.log
	$(V) rm -rf Build
