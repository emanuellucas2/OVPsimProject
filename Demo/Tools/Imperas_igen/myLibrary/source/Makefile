###############################################################################
#                        Recurse looking for Makefiles                        #
###############################################################################

Makefiles = $(wildcard */*/*/*/*/Makefile)
OVP-ALL   = $(foreach f, $(Makefiles), $(f)-ALL)
OVP-CLEAN = $(foreach f, $(Makefiles), $(f)-CLEAN)

all:   $(OVP-ALL)
clean: $(OVP-CLEAN)

$(OVP-ALL):
	$(V) $(MAKE) -f Makefile -C $(@D) all

$(OVP-CLEAN):
	$(V) $(MAKE) -f Makefile -C $(@D) clean

.PHONY: $(OVP-ALL) $(OVP-CLEAN)

