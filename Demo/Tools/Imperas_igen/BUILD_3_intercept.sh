#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -group buildimp -p install.pkg  --build --nobanner || exit

VENDOR=demo.imperas.com
LIBRARY=intercept
NAME=memoryWatcher
VERSION=1.0

VLNVSRC=myLibrary/source/
VLNVROOT=library/${IMPERAS_ARCH}/myLibrary

SRCLIB=${VLNVSRC}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}/model
LIB=${VLNVROOT}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}

echo
echo "------------------------------"
echo "- View Intercept iGen Source -"
echo "------------------------------"

echo "Opening ${SRCLIB}/${NAME}.extlib.tcl"
egui.exe -open ${SRCLIB}/${NAME}.extlib.tcl
echo "Press any key to continue . . ."
read ANSWER

echo
echo "-----------------------------------------------"
echo "- Generate Tool Template from iGen definition -"
echo "-----------------------------------------------"
echo "Press any key to continue . . ."
read ANSWER

igen.exe --batch         ${SRCLIB}/${NAME}.extlib.tcl  \
         --writec        ${SRCLIB}/${NAME}                 \
         --writexml      ${SRCLIB}/${NAME}.igen.xml        \
         --newargparser \
         --overwrite                                                 || exit

echo
echo "-------------------------------"
echo "- View Generated Source Files -"
echo "-------------------------------"
echo "Press any key to continue . . ."
read ANSWER

echo "- Contents of ${SRCLIB}"
ls -1 ${SRCLIB}

echo
echo "-----------------------"
echo "- Build Tool Template -"
echo "-----------------------"
echo "Press any key to continue . . ."
read ANSWER
echo "- Starting to Build . . ."
if [ ! -d ${VLNVROOT} ]; then  mkdir -p ${VLNVROOT}; fi

make -C ${SRCLIB} VLNVROOT=$(pwd)/${VLNVROOT} $@

echo
echo "-----------------------"
echo "- View Output Library -"
echo "-----------------------"
echo "Press any key to continue . . ."
read ANSWER

ls -1 ${LIB}
        
echo
echo "------------"
echo "- Complete -"
echo "------------"
