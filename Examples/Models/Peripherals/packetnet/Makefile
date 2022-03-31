	
all:
	$(MAKE) -C application
	$(MAKE) -C module      NOVLNV=1
	$(MAKE) -C peripheral  NOVLNV=1

simulate:
	harness.exe \
         --modulefile module/model.$(IMPERAS_SHRSUF) \
         --program application/pktModelTest.OR1K.elf
	
clean:
	$(MAKE) -C application clean
	$(MAKE) -C module      clean NOVLNV=1
	$(MAKE) -C peripheral  clean NOVLNV=1
	