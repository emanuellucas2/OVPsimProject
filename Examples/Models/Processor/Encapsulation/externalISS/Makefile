ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

ALL  = libXTrisc32.$(IMPERAS_SHRSUF) asmXtrisc32.exe

all: $(ALL)

%.exe: %.c
	$(V) $(HOST_GCC) $(SIM_CFLAGS) -o $@ $< -g

lib%.so: %.c %.h
	$(V) $(HOST_GCC) $(SIM_LDFLAGS) $(SIM_CFLAGS) -shared -o $@ $< -g

lib%.dll: %.c %.h
	$(V) $(HOST_GCC) $(SIM_LDFLAGS) -shared -o $@ $< -g
	$(V) $(HOST_DLLTOOL) --output-lib lib$*.lib $<

clean:
	rm -f $(ALL)
