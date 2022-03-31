#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.IMG_MIPS32R2LE-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant 34Kc \
    --numprocessors 1     \
    --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@" \
    -argv 10

