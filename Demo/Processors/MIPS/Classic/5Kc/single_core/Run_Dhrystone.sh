#!/bin/bash
# Run_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS64R2-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64_r1r5 --variant 5Kc \
    --numprocessors 1     \
    --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org  \
    "$@" \
    -argv 600000

