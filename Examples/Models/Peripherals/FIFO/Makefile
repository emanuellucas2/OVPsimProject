	
all:
	$(MAKE) -C module      NOVLNV=1
	$(MAKE) -C peripheral  NOVLNV=1

simulate:
	@echo Running
	harness.exe --modulefile module/model
	
clean:
	$(MAKE) -C module      clean NOVLNV=1
	$(MAKE) -C peripheral  clean NOVLNV=1
	