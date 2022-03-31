#!/bin/bash
# Run_QL_AMP4_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi
# Check Installation supports this demo
if [ -e ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M3-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M33 \
    --numprocessors 4     \
    --parameter UAL=1 --parameter endian=little   \
    --parallel  \
    "$@" \
    -argv 4000000

