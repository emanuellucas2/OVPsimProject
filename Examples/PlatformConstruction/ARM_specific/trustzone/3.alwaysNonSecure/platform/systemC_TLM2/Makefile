ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

# TLM platform build
SRC=platform.igen.cpp
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.TLM.platform

#
# Generate TLM platform
#
IGEN?=igen.exe
HDR_APACHE?=--userheader $(IMPERAS_HOME)/ImperasLib/fileheaders/refApache.txt

# iGen generated files
platform-igen-cpp = platform.igen.cpp
platform-igen-ext = platform.sc_clp.igen.h platform.sc_constructor.igen.h platform.sc_options.igen.h

$(platform-igen-cpp) $(platform-igen-ext): ../platform.op.tcl
	@    echo "# iGen Create TLM PLATFORM $*"
	$(V) $(IGEN)                \
        --batch         $(<)    \
        --writetlm      $(@)    \
        $(HDR_APACHE)           \
        --overwrite --op

realclean::
	$(V) rm -f $(platform-igen-cpp)
	$(V) rm -f $(platform-igen-ext)
