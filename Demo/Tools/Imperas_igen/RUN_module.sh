#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -group run -p install.pkg --nobanner  || exit

VENDOR=demo.ovpworld.org
LIBRARY=module
NAME=simple
VERSION=1.0

VLNVSRC=myLibrary/source
VLNVROOT=library/${IMPERAS_ARCH}/myLibrary

LIB=${VLNVROOT}/${VENDOR}/${LIBRARY}/${NAME}/${VERSION}

if [ ! -f ${LIB}/model.${IMPERAS_SHRSUF} ]; then
  echo
  echo "-------------------------------------------------------------------"
  echo "- ERROR: Run BUILD_2_module script to build the Module in library -"
  echo "-        VLNV ${VENDOR}/${LIBRARY}/${NAME}/${VERSION}"
  echo "-------------------------------------------------------------------"
  echo
else

echo "--------------"
echo "- Run Module -"
echo "--------------"
echo

# Can only execute extension library if Imperas Professional Simulator
checkinstall.exe -group runimp -p install.pkg --nobanner --message " Not able to add intercept library. Running standard simulation."
if [ $? -eq 0 ]; then
  ADDEXTENSION="--extlib simple/cpu1/ex=demo.imperas.com/intercept/memoryWatcher/1.0  \
                --callcommand 'simple/cpu1/ex/memory -address 0x02000000 -size 0x100'"
fi

harness.exe --verbose --stoponcontrolc \
            --modulefile ${LIB}/model.${IMPERAS_SHRSUF} \
            --program application/hello.OR1K.elf \
            --vlnvroot ${VLNVROOT}  \
            ${ADDEXTENSION} \
            "$@"

echo "------------"
echo "- Complete -"
echo "------------"

fi
