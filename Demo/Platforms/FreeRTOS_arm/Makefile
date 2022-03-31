#!/bin/sh

all:
	$(MAKE) -C FreeRTOS
	$(MAKE) -C module      NOVLNV=1
	$(MAKE) -C harnessTLM  NOVLNV=1

clean:
	$(MAKE) -C FreeRTOS             clean
	$(MAKE) -C module      NOVLNV=1 clean
	$(MAKE) -C harnessTLM  NOVLNV=1 clean
