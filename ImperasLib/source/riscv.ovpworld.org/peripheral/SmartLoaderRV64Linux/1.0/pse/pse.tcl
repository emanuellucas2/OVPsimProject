#
# Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
#
# The contents of this file are provided under the Software License
# Agreement that you accepted before downloading this file.
#
# This source forms part of the Software and can be used for educational,
# training, and demonstration purposes but cannot be used for derivative
# works except in cases where the derivative works require OVP technology
# to run.
#
# For open source models released under licenses that you can use for
# derivative works, please visit www.OVPworld.org or www.imperas.com
# for the location of the open source models.
#
# NAME : SmartLoaderRiscvLinux

imodelnewperipheral  \
                -name SmartLoaderRV64Linux  \
                -vendor riscv.ovpworld.org  \
                -library peripheral  \
                -version 1.0  \
                -imagefile pse.pse \
                -constructor constructor \
                -releasestatus ovp

  iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

  iadddocumentation  \
                -name Description  \
                -text "Psuedo-peripheral to insert boot code for a Riscv 64-bit Linux kernel boot.
 Loads simulated memory with a device tree blob file and boot code to set regs and jump to a Risc-v Linux Kernel."  
    
  iadddocumentation  \
                -name Limitations  \
                -text "Only supports little endian"

  iadddocumentation  \
                -name Reference  \
                -text "RISC-V Linux Kernel development"

imodeladdbusmasterport  \
                -name mport  \
                -addresswidth    32  \
                -addresswidthmin 32  \
                -addresswidthmax 48  \
                -mustbeconnected
  iadddocumentation  \
                -name Description  \
                -text "Master port - connect this to the same bus connected to the Linux processor's data port."

imodeladdformal  \
                -name dtb  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Name of the device tree blob file. (required when Smart Loader is not disabled)"

imodeladdformal  \
                -name command  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Set command line passed to kernel. Will override a command line defined in the dtb. (optional)"

imodeladdformal  \
                -name append  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Append to the kernel command line defined in the dtb. (optional)"

imodeladdformal  \
                -name membase  \
                -type address
  iadddocumentation  \
                -name Description  \
                -text "Base of main memory region (overrides device tree memory node when membase and memsize both set)"

imodeladdformal  \
                -name memsize  \
                -type address
  iadddocumentation  \
                -name Description  \
                -text "Size of main memory region (overrides device tree memory node  when membase and memsize both set)"

imodeladdformal  \
                -name slbootaddr  \
                -type address
  iadddocumentation  \
                -name Description  \
                -text "Address where SmartLoader generated boot code and dtb will be loaded. Jump to this address to start boot process. (default: 0x1000)"

imodeladdformal  \
                -name bootimage  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Name of boot image file to load at bootaddr, e.g. bbl.bin (optional - may instead load boot elf file with standard --objfilenoentry option)"

imodeladdformal  \
                -name bootaddr  \
                -type address
  iadddocumentation  \
                -name Description  \
                -text "Address to call from SmartLoader's generated boot code. (default 0x80000000)"
                
imodeladdformal  \
                -name bootconvention \
                -type enumeration \
                -defaultvalue bbl
  iadddocumentation  \
                -name Description  \
                -text "Boot convention to use in call from SmartLoader generated boot code (bbl=Berkeley Boot Loader, fsbl=SiFive FSBL). (default: bbl)"
  imodeladdenumeration -formal bootconvention -name bbl
  imodeladdenumeration -formal bootconvention -name fsbl

imodeladdformal  \
                -name disable  \
                -type bool
  iadddocumentation  \
                -name Description  \
                -text "Set to True to disable the SmartLoader. (all other parameters are ignored when this is set to True)"
