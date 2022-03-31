#!/bin/bash
# Debug_GDB_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS64R2-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64_r1r5 --variant 5KEf \
    --numprocessors 1     \
    --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org  \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"


