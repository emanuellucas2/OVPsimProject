IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include


OBJ=hostApp.o socketIf.o stimulus.o

ifeq ($(IMPERAS_UNAME),Windows)
WINLIB=-lwsock32
endif

CINCLUDE=-I$(IMPERAS_HOME)/Common/include -I$(IMPERAS_HOME)/ImpPublic/include/host
CINCLUDE+=-I../common

hostApp.exe: $(OBJ)
	@ echo "# Compiling $^"
	@ $(HOST_GCC) -gdwarf-2 -O0 $^ -o $@ $(WINLIB)
	
%.o: %.c
	@ echo "# Linking $@"
	@ $(HOST_GCC) -Werror  -gdwarf-2 -O0 -c $(CINCLUDE) $< -o $@

clean:
	rm -f *.exe *.o
