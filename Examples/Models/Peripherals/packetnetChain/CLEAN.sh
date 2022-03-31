#!/bin/bash

make clean \
     -C $PWD/source \
     -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.library \
        VLNVSRC=$PWD/source VLNVROOT=${PWD}/lib/${IMPERAS_ARCH} \
     

make clean -C application 
