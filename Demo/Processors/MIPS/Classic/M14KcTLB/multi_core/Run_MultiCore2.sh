#!/bin/bash
# Run_MultiCore2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.IMG_UMIPS32R2LE-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant M14KcTLB \
    --numprocessors 2 --loshare 0x0002a4a8 --hishare 0x0002a4af   \
    --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@"


