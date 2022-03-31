#!/bin/bash
# Run_AMP4_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS32R2LE-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant 1074Kf \
    --numprocessors 4     \
    --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@" \
    -argv 4000000

