#!/bin/bash
# Debug_GDB_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi
# Check Installation supports this demo
if [ -e ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe --group debug --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.NANOMIPS32R6LE-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant I7200 \
    --numprocessors 1     \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"


