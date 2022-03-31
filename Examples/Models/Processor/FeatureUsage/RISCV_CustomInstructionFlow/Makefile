ifeq ($(IMPERAS_HOME),)
  IMPERAS_ERROR := $(error "IMPERAS_HOME not set, please setup Imperas environment)
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

include $(IMPERAS_HOME)/bin/Makefile.include

# build in local library
VLNVROOT?= $(CURDIR)/vlnvroot

VLNV     = riscv.ovpworld.org/processor/riscv/1.0
VLNVGCOV = riscv.ovpworld.org/processor/riscv-gcov/1.0
OBJROOT  = $(VLNVROOT)/$(VLNV)/model/obj

# model source
MODELSRC?=$(IMPERAS_HOME)/ImperasLib/source/$(VLNV)/model
# source files
MODELSRCFILES=$(wildcard $(MODELSRC)/*.c) $(wildcard $(MODELSRC)/*.h)
LCLSRCFILES  =$(subst $(MODELSRC),$(VLNVROOT)/$(VLNV)/model,$(MODELSRCFILES))

ifneq ($(wildcard $(IMPERAS_HOME)/ImpProprietary/include/host/isl/.*),)
TIMINGTOOLLIB=timingToolLib/model.$(IMPERAS_SHRSUF)
else
$(warning "** Cannot build timingToolLib")
TIMINGTOOLLIB=
endif

all: build
	@echo "Use make target 'help' to get a full list of options"

build: application \
       instructionExtensionCFunctionCallLib/model.$(IMPERAS_SHRSUF) \
       instructionExtensionLib/model.$(IMPERAS_SHRSUF) \
       $(TIMINGTOOLLIB)

application: FORCETARGET
	$(MAKE) -C application

# General build
%/model.$(IMPERAS_SHRSUF): FORCETARGET
	$(MAKE) -C $(@D) NOVLNV=1

# timing tool build requires initial iGen generation
timingToolLib/model.$(IMPERAS_SHRSUF): FORCETARGET
	$(MAKE) -C $(@D) NOVLNV=1

# Create documentation for extended processor
pdf: FORCETARGET
	mkdir -p pdf
	texgen.exe \
        -modeltype processor -modelname riscv -modelvendor riscv.ovpworld.org \
        -variant RVB32I -override add_Extensions=MSU \
        -pdfdir pdf \
        -extlib instructionExtensionLib

tex: FORCETARGET
	mkdir -p tex
	texgen.exe \
        -modeltype processor -modelname riscv -modelvendor riscv.ovpworld.org \
        -variant RVB32I -override add_Extensions=MSU \
        -texdir tex \
        -extlib instructionExtensionLib


ifeq ($(IMPERAS_UNAME),Linux)
# Build local GCOV RISCV model and re-build extension library
build-gcov: $(VLNVROOT)/$(VLNVGCOV)/model.$(IMPERAS_SHRSUF)
	$(MAKE) -C instructionExtensionLib NOVLNV=1 clean
	$(MAKE) -C instructionExtensionLib NOVLNV=1 OTHER_CFLAGS="-DGCOV=1 -fprofile-arcs -ftest-coverage" OTHER_LDFLAGS="-lgcov"

# Create Makefile for build local GCOV RISCV model
$(VLNVROOT)/Makefile.gcov:
	echo "OTHER_CFLAGS=-DGCOV=1 -fprofile-arcs -ftest-coverage" > $@
	echo "OTHER_LDFLAGS=-lgcov" >> $@
	cat "$(MODELSRC)/Makefile"  >> $@

$(VLNVROOT):
	mkdir -p $(VLNVROOT)

# create clone of local GCOV RISCV model with different name so that it does not clash
$(VLNVROOT)/$(VLNVGCOV)/model.$(IMPERAS_SHRSUF): $(VLNVROOT)/$(VLNV)/model.$(IMPERAS_SHRSUF)
	mkdir -p $(VLNVROOT)/$(VLNVGCOV)
	- ln -s $(VLNVROOT)/$(VLNV)/model.$(IMPERAS_SHRSUF) $(VLNVROOT)/$(VLNVGCOV)

# Build local GCOV RISCV model
$(VLNVROOT)/$(VLNV)/model.$(IMPERAS_SHRSUF): $(VLNVROOT) $(VLNVROOT)/Makefile.gcov
	$(MAKE) -f $(VLNVROOT)/Makefile.gcov -C $(MODELSRC) VLNVROOT=$(VLNVROOT) OBJROOT=$(OBJROOT)

# Test allows execution of an elf file on the local GCOV RISCV model
test: $(VLNVROOT)/$(VLNVGCOV)/model.$(IMPERAS_SHRSUF)
ifeq ($(TESTELF),)
	@echo "Please specify test elf file using TESTELF"
else
	${IMPERAS_ISS} --verbose --output test_gcov.log --program $(TESTELF) \
        --processorvendor riscv.ovpworld.org --processorname riscv \
        --variant RVB32I -override iss/cpu0/add_Extensions=MSU \
        --numprocessors 1 --objfilenoentry application/exception.RISCV32.elf \
        --extlib iss/cpu0/exInst=instructionExtensionLib \
        --vlnvroot $(VLNVROOT) \
        --vlnvmap riscv.ovpworld.org/processor/riscv/1.0=riscv.ovpworld.org/processor/riscv-gcov/1.0
endif

# create the line coverage output files from coverage data
lcov: coverage.riscv.lcov coverage.ext.lcov coverage_data

# link (or copy) RISCV source locally for coverage output generation
$(VLNVROOT)/$(VLNV)/model/%: $(MODELSRC)/%
	mkdir -p $(@D)
	ln -s $^ $@

# generate RISCV model coverage
coverage.riscv.lcov: $(VLNVROOT)/$(VLNV)/model.$(IMPERAS_SHRSUF) $(LCLSRCFILES) FORCETARGET
	lcov --capture --directory $(OBJROOT) --output-file $@ --gcov-tool gcov

# generate Custom Extension instruction coverage
coverage.ext.lcov: instructionExtensionLib/model.$(IMPERAS_SHRSUF) FORCETARGET
	lcov --capture --directory instructionExtensionLib/obj --output-file $@ --gcov-tool gcov

# Create an HTML representation of the coverage
coverage_data: coverage.riscv.lcov coverage.ext.lcov
	genhtml $^ \
            --prefix $(CURDIR) \
            --output-directory $@ \
            --title "Imperas Test Coverage Results" \
            --show-details

# concatenated coverage file
coverage.lcov: coverage.riscv.lcov coverage.ext.lcov
	cat $^ > $@

# view coverage (eGui)
view: coverage.lcov
	@echo "Opening $^ in eGui"
	egui.exe -open $^

# view coverage (html browser)
html: coverage_data
	firefox coverage_data/index.html

else

targetSupport: FORCETARGET
	@echo "Not supported on Windows"

build-gcov: targetSupport

test: targetSupport

lcov: targetSupport

view: targetSupport

html: targetSupport

endif

clean::
	$(MAKE) -C instructionExtensionLib NOVLNV=1 $@
	$(MAKE) -C instructionExtensionCFunctionCallLib NOVLNV=1 $@
	$(MAKE) -C application $@
	$(MAKE) -C $(MODELSRC) $@ VLNVROOT=$(VLNVROOT) OBJROOT=$(OBJROOT)
	- rm -rf $(VLNVROOT)
	$(MAKE) -C timingToolLib NOVLNV=1 clean
	- rm -f  lastRun.sh
realclean:: clean
	- rm -rf coverage_data
	- rm -f  coverage*.lcov
	- rm -rf coverageReports
	- rm -rf pdf tex
	- rm -f  *.log
	- rm -f  *.icov *.iprof
	- rm -rf ipr.*
	- rm -f  bbProfile*.txt

help:
	@echo "The following targets are available"
	@echo "Example"
	@echo "   build      : build applications and extension libraries used by RUN_... scripts"
	@echo "Coverage"
	@echo "   build-gcov : build local copy of RISCV processor model for gcov \($(VLNVGCOV)\), re-build extension library for gcov"
	@echo "   test       : Specify the test to run using TESTELF on coverage model"
	@echo "   lcov       : After running test using the local gcov model, generate coverage information \(requires lcov on PATH\)"
	@echo "   view       : View the coverage information using eGui"
	@echo "   html       : View the coverage information HTML file \(requires genhtml on PATH\)"
	@echo "Documentation"
	@echo "   pdf        : generate PDF documentation of extended processor \(requires availability of texgen\)"
	@echo "Clean"
	@echo "   clean      : remove all generated files"

.PHONY: FORCETARGET
FORCETARGET:
