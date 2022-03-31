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
# NAME : SmartLoaderArmLinux

imodelnewperipheral  \
                -name    SmartLoaderArmLinux  \
                -vendor  arm.ovpworld.org  \
                -library peripheral  \
                -version 1.0  \
                -releasestatus ovp \
                -constructor constructor \
                -destructor  destructor

  iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

  iadddocumentation  \
                -name Description  \
                -text "Psuedo-peripheral to perform memory initialisation for an ARM based Linux kernel boot:
    Loads Linux kernel image file and (optional) initial ram disk image into memory. 
    Writes ATAG data into memory.
    Writes tiny boot code at physical memory base that configures the registers as expected by Linux Kernel and then jumps to boot address (image load address by default)."
    
  iadddocumentation  \
                -name Limitations  \
                -text "Only supports little endian"
                
  iadddocumentation  \
                -name Reference  \
                -text "See ARM Linux boot requirements in Linux source tree at documentation/arm/Booting"

imodeladdbusmasterport  \
                -name mport  \
                -addresswidth    32  \
                -addresswidthmin 32  \
                -addresswidthmax 49  \
                -mustbeconnected
  iadddocumentation  \
                -name Description  \
                -text "Master port - connect to same bus connected to Linux processor's data port"
                
imodeladdformal -name kernel -type string
  iadddocumentation  \
                -name Description  \
                -text "Name of the the Linux kernel image file (e.g. zImage) to load. (required)"
                
imodeladdformal -name kerneladdr -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Address to load the Linux kernel image file (default: physicalbase+0x00010000)"

imodeladdformal -name initrd -type string
  iadddocumentation  \
                -name Description  \
                -text "Name of the initial ram disk file to load (optional)"
                
imodeladdformal  -name initrdaddr -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Address to load the initial ram disk file (default: physicalbase+0x00d00000)"

imodeladdformal  \
                -name dtb  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Name of the device tree blob file (optional - ATAGs used when not specified)"
                
imodeladdformal  -name dtbaddr -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Address to load the device tree blob (DTB) file (default: physicalbase+0x00c00000)"

imodeladdformal -name atagsaddr -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Address to write Linux ATAGS data - not allowed when dtb specified (default: physicalbase+0x100)"

imodeladdformal -name physicalbase -type uns32
  iadddocumentation  \
                -name Description  \
                -text "The physical address of the base of memory (default: 0)"

imodeladdformal -name memsize -type uns32
  iadddocumentation  \
                -name Description  \
                -text "The size of memory in bytes- not allowed when dtb specified (default: 128M)"

imodeladdformal -name command -type string
  iadddocumentation  \
                -name Description  \
                -text "Set command line passed to kernel (optional)"

imodeladdformal -name append -type string
  iadddocumentation  \
                -name Description  \
                -text "Append to the command line passed to kernel. (optional)"
                
imodeladdformal -name boardid -type uns32
  iadddocumentation  \
                -name Description  \
                -text "The boardid passed to the kernel - not allowed when dtb specified (default: ArmIntegrator value = 0x113)"

imodeladdformal -name bootaddr -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Address to call from smart Loader's tiny startup code (default: kerneladdr)"

imodeladdformal -name disable -type boolean
  iadddocumentation  \
                -name Description  \
                -text "Set to True to disable the smart loader"
