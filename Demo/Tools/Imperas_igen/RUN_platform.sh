#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -group run -p install.pkg --nobanner  || exit

VENDOR=demo.ovpworld.org
LIBRARY=platform
NAME=simple
VERSION=1.0

VLNVSRC=myLibrary/source
VLNVROOT=library/${IMPERAS_ARCH}/myLibrary

LIB=${VLNVROOT}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}

# Ensure Platform is built
if [ ! -f ${LIB}/platform.${IMPERAS_ARCH}.exe ]; then
  echo
  echo "-------------------------------------------------------------------"
  echo "- ERROR: Run BUILD_2_platform script to build platform in library -"
  echo "         VLNV ${VENDOR}/${LIBRARY}/${NAME}/${VERSION}"
  echo "-------------------------------------------------------------------"
  echo
else

echo "----------------"
echo "- Run Platform -"
echo "----------------"
echo

# Can only execute extension library if Imperas Professional Simulator
checkinstall.exe -group runimp -p install.pkg --nobanner --message " Not able to add intercept library. Running standard simulation."
if [ $? -eq 0 ]; then
  ADDEXTENSION="--extlib simple/cpu1/ex=demo.imperas.com/intercept/memoryWatcher/1.0  \
                --callcommand 'simple/cpu1/ex/memory -address 0x02000000 -size 0x100'"
fi

${LIB}/platform.${IMPERAS_ARCH}.exe \
               --verbose --stoponcontrolc \
               --program application/hello.OR1K.elf \
               --vlnvroot ${VLNVROOT} \
               ${ADDEXTENSION} \
               "$@"

echo "------------"
echo "- Complete -"
echo "------------"

fi
