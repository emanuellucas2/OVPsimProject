DIR=peakSpeed2 dhrystone linpack fibonacci multicore2 
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
