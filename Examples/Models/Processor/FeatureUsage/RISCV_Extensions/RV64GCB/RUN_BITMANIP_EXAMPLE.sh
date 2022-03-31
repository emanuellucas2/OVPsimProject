#!/bin/bash

# Check Installation supports the base requirements for this example
checkinstall.exe -p install.pkg --nobanner || exit

# Build example test applications
make || exit

apps=$(ls *.elf | sort -d)
if [ "$apps" = "" ]; then 
  echo "No ELF files found, please use make to build"
  exit
fi

PS3='Please Choose Bit Manipulation Example: '
select app in $apps
do
    break
done
echo "Selected Example $app"

${IMPERAS_ISS} \
    --verbose \
    --output imperas.bitmanip.log    \
    --program ${app} \
    --processorvendor riscv.ovpworld.org --processorname riscv --variant RVB64I \
    --override iss/cpu0/add_Extensions=MAFDCBSU \
    --numprocessors 1 \
    --override iss/cpu0/defaultsemihost=F \
    --addressbits 32 \
    --override iss/cpu0/debugflags=6 \
    --override iss/cpu0/wfi_is_nop=0 \
    --override iss/cpu0/simulateexceptions=T \
    --override iss/cpu0/PMP_registers=0 \
    --override iss/cpu0/ASID_bits=0 \
    --override iss/cpu0/tval_ii_code=F \
    --override iss/cpu0/bitmanip_version=0.94 \
    --extlib   iss/cpu0=riscv.ovpworld.org/intercept/customControl/1.0 \
    "$@"
