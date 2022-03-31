#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit

MODULE=ARMv8-A-FMv1
VENDOR=arm.ovpworld.org
REFDEMO=${IMPERAS_HOME}/Demo/Platforms/Linux_ARMv8-A-FMv1

# Build the harness
make -C harness || exit

echo "---------------------------"
echo "REIMPLEMENT TIMER REGISTERS"
echo "---------------------------"

harness/harness.$IMPERAS_ARCH.exe \
 \
 --output imperas.log --verbose \
 \
 --startaddress 0x80000000 \
 \
 --override ARMv8-A-FMv1/cpu/variant=Cortex-A72MPx4 \
 --override ARMv8-A-FMv1/smartLoader/kernel=${REFDEMO}/Linux/Image \
 --override ARMv8-A-FMv1/smartLoader/initrd=${REFDEMO}/Linux/initrd.arm64.img \
 --override ARMv8-A-FMv1/smartLoader/dtb=${REFDEMO}/Linux/foundation-v8-gicv3.dtb \
 \
 --override ARMv8-A-FMv1/uart0/console=1 \
 --override ARMv8-A-FMv1/uart1/console=0 \
 \
 --override ARMv8-A-FMv1/cpu/enableSystemBus=1 \
 "$@"
