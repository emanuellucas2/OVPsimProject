all:
	$(MAKE) -C application
	$(MAKE) -C module             NOVLNV=1 
	$(MAKE) -C pse NOVLNV=1

clean:
	$(MAKE) -C application clean
	$(MAKE) -C module             NOVLNV=1 clean
	$(MAKE) -C pse NOVLNV=1 clean
	\rm -rf *.log module/module.c

run: all
	(sleep 1; firefox http://localhost:8000) &
	harness.exe \
	    --modulefile module/model \
	    --program application/app.elf \
	    --verbose -o output.log \
	--override test/lcd0/httpvisportnum=8000


# IMPERAS_HTTP_TRACE=1 IMPERAS_HTTP=1 harness.exe \
# --override test/lcd0/diagnosticlevel=1 \

