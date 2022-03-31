# all local builds
NOVLNV?=1

USERHEADER=$(IMPERAS_HOME)/ImperasLib/fileheaders/refESLA.txt
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.common

#
# generate all iGen source
#
IGEN?= igen.exe
DEPENDS?=
IGENFLAGS?=--quiet --nobanner --excludem GPT_NH --excludem GPT_UFNR

MODULEOPTCL?=../module/module.op.tcl

all: platform.$(IMPERAS_ARCH).exe

platform-igen-ext      = platform.cpp \
                         platform.sc_clp.igen.h \
                         platform.sc_constructor.igen.h \
                         platform.sc_options.igen.h

$(platform-igen-ext) : $(MODULEOPTCL)
	@ echo "# iGen Generate Platform files"
	$(V) $(IGEN) --batch $^ --writetlm $@ \
        $(WRITEHEADER) $(IGENFLAGS)       \
        --overwrite --op --output igen.log

platform.$(IMPERAS_ARCH).exe : $(platform-igen-ext)
	@ echo "# Build $@"
	$(V) $(MAKE) -f $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.TLM.platform \
                        NOVLNV=1

clean:
	$(V) $(MAKE) -f $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.TLM.platform \
                        NOVLNV=1 clean
	$(V) rm -f *.igen.*

realclean: clean
	$(V) $(MAKE) -f $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.TLM.platform \
                        NOVLNV=1 realclean
	$(V) rm -f platform.cpp *.log
