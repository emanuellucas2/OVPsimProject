#!/bin/bash

# Check Installation supports this base requirements for this example
checkinstall.exe -p install.pkg --nobanner || exit

if [ ! -e timingToolLib/model.${IMPERAS_SHRSUF} ] || [ ! -e instructionExtensionLib/model.${IMPERAS_SHRSUF} ] || [ ! -e instructionExtensionCFunctionCallLib/model.${IMPERAS_SHRSUF} ]; then
  echo "Libraries not built, building now ..."
  make build
fi


applications[0]=test_asm.RISCV32.elf
TRACEAFTER[0]=1022
TRACECOUNT[0]=44

applications[1]=test_c.RISCV32.elf
TRACEAFTER[1]=1000
TRACECOUNT[1]=110

if [ ! -e application/${applications[0]} ] || [ ! -e application/${applications[1]} ]; then
  echo "Applications not built, building now ..."
  make application
fi

export APP=${applications[0]}

COMMANDLINE="${IMPERAS_ISS} \
 --verbose \
 --output imperas.log \
 \
 --processorvendor riscv.ovpworld.org --processorname riscv \
 --variant RVB32I --override iss/cpu0/add_Extensions=MSU \
 --numprocessors 1 \
 --override iss/cpu0/verbose=T"


source $(dirname "$0")/selectOptions.sh
declare -i rtn=$?

if [ $rtn -eq 0 ]; then

  echo "#!/bin/bash" > lastRun.sh

  # generate a Run script for the simulation with options applied
  echo "${COMMANDLINE}      \
    --program application/${APP} \
    \
    --objfilenoentry application/exception.RISCV32.elf    \
    \
    ${VLNVARGS}         \
    ${CUSTOMARGS}       \
    ${ADDSTDTOOLS}      \
    ${INSTCOVARGS}      \
    ${INSTPROFARGS}     \
    ${INSTIMPLPROFARGS} \
    ${TRACEARGS}        \
    ${DEBUGARGS}        \
    ${TIMINGARGS}       \
    ${STRETCHARGS}      \
    ${APPCOVARGS}       \
    ${APPPROFARGS}      \
    \"\$@\"" >> lastRun.sh

  if [ "${POSTRUN}" != "" ]; then
    echo "# Post Process Data" >> lastRun.sh
    echo "${POSTRUN}"          >> lastRun.sh
  fi

  chmod +x lastRun.sh

  # Run
  ./lastRun.sh "$@"

  echo "Use script lastRun.sh to re-run with current settings"

fi
