#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -group buildimp -p install.pkg  --build --nobanner || exit

VLNVSRC=myLibrary/source
VLNVROOT=library/${IMPERAS_ARCH}/myLibrary

echo
echo "-----------------"
echo "- Build Library -"
echo "-----------------"

if [ ! -d library ]; then mkdir -p ${VLNVROOT}; fi

echo "Starting to Build Library . . ."

# directory must exist
mkdir -p ${VLNVROOT}

# Building library
make -C ${VLNVSRC}        \
     VLNVSRC=$(pwd)/${VLNVSRC}   \
     VLNVROOT=$(pwd)/${VLNVROOT} \
     -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.library $@
        
echo
echo "-----------------------"
echo "- View Output Library -"
echo "-----------------------"
echo "Press any key to continue . . ."
read ANSWER

echo "Contents of library"
find library -type f

echo
echo "------------"
echo "- Complete -"
echo "------------"
