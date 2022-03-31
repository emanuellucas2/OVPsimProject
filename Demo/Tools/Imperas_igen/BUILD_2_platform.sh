#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -group build -p install.pkg  --build --nobanner || exit

VENDOR=demo.ovpworld.org
LIBRARY=platform
NAME=simple
VERSION=1.0

VLNVSRC=myLibrary/source/
VLNVROOT=library/${IMPERAS_ARCH}/myLibrary

SRCLIB=${VLNVSRC}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}/platform
LIB=${VLNVROOT}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}

echo
echo "----------------------------"
echo "- View Platform Definition -"
echo "----------------------------"

echo "Opening ${SRCLIB}/platform.op.tcl"
egui.exe -open ${SRCLIB}/platform.op.tcl
echo "Press any key to continue . . ."
read ANSWER

if [ ! -d ${VLNVROOT}/${VENDOR}/peripheral/IntCtrlT/1.0 ]; then
  echo
  echo "---------------------------------------------------------------------------"
  echo "- ERROR: Run BUILD_1_peripheral script to build the Peripheral in library -"
  echo "-        VLNV ${VENDOR}/peripheral/IntCtrlT/1.0"
  echo "---------------------------------------------------------------------------"
  echo
else

echo
echo "-------------------------------------------"
echo "- Generate C Platform from TCL definition -"
echo "-------------------------------------------"
echo "Press any key to continue . . ."
read ANSWER

igen.exe --batch     ${SRCLIB}/platform.op.tcl \
         --op                                  \
         --writec    ${SRCLIB}/platform.c      \
         --logfile   igen-op-platform.log      \
         --overwrite                               || exit

echo
echo "--------------------------------------------------------"
echo "- Generate SystemC TLM2.0 Platform from TCL definition -"
echo "--------------------------------------------------------"
echo "Press any key to continue . . ."
read ANSWER

igen.exe --batch    ${SRCLIB}/platform.op.tcl \
         --writetlm ${SRCLIB}/platform.cpp    \
         --logfile  igen-TLM-platform.log     \
         --vlnvroot ${VLNVROOT}               \
         --overwrite                               || exit

echo
echo "-----------------------"
echo "- View Source Library -"
echo "-----------------------"
echo "Press any key to continue . . ."
read ANSWER

ls -1 ${SRCLIB}/platform.*

echo
echo "--------------------"
echo "- Build C Platform -"
echo "--------------------"
echo "Press any key to continue . . ."
read ANSWER
echo "- Starting to Build . . ."

if [ ! -d ${VLNVROOT} ]; then mkdir -p ${VLNVROOT}; fi

make -C ${SRCLIB} VLNVROOT=$(pwd)/${VLNVROOT} $@

echo
echo "-----------------------"
echo "- View Output Library -"
echo "-----------------------"
echo "Press any key to continue . . ."
read ANSWER

echo "- Contents of ${LIB}" 
ls -1 ${LIB}

echo
echo "------------"
echo "- Complete -"
echo "------------"

fi
