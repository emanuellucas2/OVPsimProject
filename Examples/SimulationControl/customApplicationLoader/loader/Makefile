ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include


all: loader.$(IMPERAS_SHRSUF)

SO_CFLAGS   = $(SIM_CFLAGS) $(OTHER_CFLAGS)
SO_LDFLAGS  = $(OTHER_LDFLAGS)

ifeq ($(IMPERAS_UNAME),Linux)
  SO_LDFLAGS += -Wl,--version-script=version.script
else
  SO_LDFLAGS += export.def
endif

OBJS  = loader.o
SOLIB = loader.$(IMPERAS_SHRSUF)

%.o: %.c
	$(V) echo "Compiling Loader $@"
	$(V) $(HOST_GCC) $(SO_CFLAGS) -c -o $@ $^

$(SOLIB): $(OBJS)
	$(V) echo "Linking Loader"
	$(V) $(HOST_GCC) $(SO_CFLAGS) --shared -o $@ $^ $(SO_LDFLAGS)

clean:
	$(V) - rm -f  loader.$(IMPERAS_SHRSUF) loader.o
