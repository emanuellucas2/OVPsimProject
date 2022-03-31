#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -group build -p install.pkg  --build --nobanner || exit

VENDOR=demo.ovpworld.org
LIBRARY=peripheral
NAME=IntCtrlT
VERSION=1.0

VLNVSRC=myLibrary/source
VLNVROOT=library/${IMPERAS_ARCH}/myLibrary

SRCLIB=${VLNVSRC}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}/pse
LIB=${VLNVROOT}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}

echo
echo "-------------------------------"
echo "- View Peripheral iGen Source -"
echo "-------------------------------"

echo "Opening ${SRCLIB}/pse.tcl"
egui.exe -open ${SRCLIB}/pse.tcl
echo "Press any key to continue . . ."
read ANSWER

echo
echo "--------------------------------"
echo "- Generate Peripheral Template -"
echo "--------------------------------"
echo "Press any key to continue . . ."
read ANSWER

igen.exe --batch         ${SRCLIB}/pse.tcl            \
         --writec        ${SRCLIB}/pse                \
         --writexml      ${SRCLIB}/pse.igen.xml       \
         --logfile       igen-peripheral.log          \
         --overwrite                                                      || exit
         
echo
echo "-------------------------------"
echo "- View Generated Source Files -"
echo "-------------------------------"
echo "Press any key to continue . . ."
read ANSWER

echo "- Contents of ${SRCLIB}"
ls -1 ${SRCLIB}/*.igen.*

echo
echo "---------------------------------"
echo "- Compile Peripheral C Template -"
echo "---------------------------------"
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

echo Contents of ${LIB}
ls -1 ${LIB}

echo
echo "---------------------------------------------------------------"
echo "- Generate SystemC TLM2.0 Peripheral Interface from PSE model -"
echo "---------------------------------------------------------------"
echo "Press any key to continue . . ."
read ANSWER

igen.exe --modelfile     ${LIB}/pse.pse              \
         --writetlm      ${SRCLIB}/pse.igen.hpp      \
         --logfile       igen-peripheral-tlm.log     \
         --overwrite                                                      || exit

echo "------------"
echo "- Complete -"
echo "------------"
