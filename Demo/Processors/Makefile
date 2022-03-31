DIR=ARC/Applications MIPS/Applications ARM/Applications POWERPC/Applications OPENCORES/Applications RENESAS/Applications XILINX/Applications ALTERA/Applications RISCV/Applications ANDES/Applications MICROSEMI/Applications SIFIVE/Applications LOWRISC/Applications OPENHWGROUP/Applications CODASIP/Applications 
all: 
	@for D in $(DIR); do \
		$(MAKE) -C $$D; \
		rc=$$?; \
		if [ $$rc -ne 0 ]; then \
			exit $$rc; \
		fi; \
	done

clean: 
	@for D in $(DIR); do \
		$(MAKE) -C $$D $@; \
	done
