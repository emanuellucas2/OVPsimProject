#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -group build -p install.pkg  --build --nobanner || exit

VENDOR=demo.ovpworld.org
LIBRARY=module
NAME=simple
VERSION=1.0

VLNVSRC=myLibrary/source
VLNVROOT=library/${IMPERAS_ARCH}/myLibrary

SRCLIB=${VLNVSRC}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}/module
LIB=${VLNVROOT}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}

echo
echo "--------------------------"
echo "- View Module Definition -"
echo "--------------------------"

echo "- Opening ${SRCLIB}/module.op.tcl"
egui.exe -open ${SRCLIB}/module.op.tcl
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
echo "------------------------------------------"
echo "- Generate C Module from iGen definition -"
echo "------------------------------------------"
echo "Press any key to continue . . ."
read ANSWER

igen.exe --batch     ${SRCLIB}/module.op.tcl \
         --op                                \
         --writec    ${SRCLIB}/module.c      \
         --logfile   igen-op-module.log      \
         --overwrite                               || exit

echo
echo "-----------------------"
echo "- View Source Library -"
echo "-----------------------"
echo "Press any key to continue . . ."
read ANSWER

ls -1 ${SRCLIB}/module.*

echo
echo "----------------"
echo "- Build Module -"
echo "----------------"
echo "Press any key to continue . . ."
read ANSWER
echo "- Starting to Build . . ."

if [ ! -d ${VLNVROOT} ]; then mkdir -p ${VLNVROOT}; fi

make -C ${SRCLIB} VLNVROOT=$(pwd)/${VLNVROOT} $*

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
