#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner  || exit

# Platform (Uses Imperas Command Line Parser)
VENDOR=demo.ovpworld.org
LIBRARY=platform
NAME=simple
VERSION=1.0

VLNVSRC=myLibrary/source
VLNVROOT=library/${IMPERAS_ARCH}/myLibrary

LIB=${VLNVROOT}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}

if [ ! -d ${LIB} ]; then
  echo
  echo "-----------------------------------------------------------------------"
  echo "- ERROR: Run BUILD_2_platform script to build the Platform in library -"
  echo "-        VLNV ${VENDOR}/${LIBRARY}/${NAME}/${VERSION}"
  echo "-----------------------------------------------------------------------"
  echo
else

echo
echo "----------------"
echo "- Show Library -"
echo "----------------"
echo "Press any key to continue . . ."
read ANSWER

# clear IMPERAS_VLNV so that we only see local library
IMPERAS_VLNV= ${LIB}/platform.${IMPERAS_ARCH}.exe  \
         --vlnvroot ${VLNVROOT} \
         --program application/hello.OR1K.elf \
         --showlibrary

echo
echo "------------------------------------------------------"
echo "- Start Imperas Debugger to examine Programmers View -"
echo "------------------------------------------------------"
echo "Press any key to continue . . ."
read ANSWER

# check install supports debug
checkinstall.exe -group debug -p install.pkg --nobanner  || exit

${LIB}/platform.${IMPERAS_ARCH}.exe  \
         --vlnvroot ${VLNVROOT} \
         --program  application/hello.OR1K.elf \
         --batch    commands.mdb --mpdconsole \
         --logfile  imperas.log

echo
echo "------------"
echo "- Complete -"
echo "------------"

fi
