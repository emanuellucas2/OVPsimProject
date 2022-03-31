#!/bin/bash
# Run_MultiCore2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.IMG_MIPS64R2-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64_r1r5 --variant 5KEc \
    --numprocessors 2 --loshare 0x0002dbb8 --hishare 0x0002dbbf   \
    --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org  \
    "$@"


