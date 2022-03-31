#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.IMG_MIPS32R2LE-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant ISA \
    --numprocessors 1     \
    --parameter endian=little    \
    "$@" \
    -argv 36
