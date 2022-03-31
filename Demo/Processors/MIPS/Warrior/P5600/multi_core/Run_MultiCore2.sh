#!/bin/bash
# Run_MultiCore2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.IMG_MIPS32R2-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant P5600 \
    --numprocessors 2 --loshare 0x0002dd08 --hishare 0x0002dd0f --addressbits 37  \
    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@"


