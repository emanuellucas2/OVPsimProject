DIR=peakSpeed1_rl78 dhrystone_rl78 fibonacci_rl78 peakSpeed2 dhrystone linpack fibonacci multicore2 peakSpeed1_m16c fibonacci_m16c 
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
