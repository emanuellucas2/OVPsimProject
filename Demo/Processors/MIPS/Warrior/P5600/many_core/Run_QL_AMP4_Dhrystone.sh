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
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS32R2-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant P5600 \
    --numprocessors 4 --addressbits 37    \
    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    --parallel  \
    "$@" \
--parallelmax    -argv 1000000

