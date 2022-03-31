DIR=peakSpeed2_microblaze dhrystone_microblaze linpack_microblaze fibonacci_microblaze multicore2_microblaze 
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
