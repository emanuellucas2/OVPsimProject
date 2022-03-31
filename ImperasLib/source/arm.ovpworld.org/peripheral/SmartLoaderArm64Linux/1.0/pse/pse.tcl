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
# NAME : SmartLoaderArm64Linux

imodelnewperipheral  \
                -name SmartLoaderArm64Linux  \
                -vendor arm.ovpworld.org  \
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
                -text "Psuedo-peripheral to perform memory initialisation for an Arm64 Linux kernel boot:
    Loads Linux kernel image file, device tree blob and (optional) initial ram disk image into memory. 
    Writes tiny boot code at physical memory base to configure regs and then jump to the Kernel entry.
    Modifies the device tree to always use the spin-table enable-method."
    
  iadddocumentation  \
                -name Limitations  \
                -text "Only supports little endian"
                
  iadddocumentation  \
                -name Reference  \
                -text "See ARM Linux boot requirements in Linux source tree at documentation/arm64/booting.txt"

imodeladdbusmasterport  \
                -name mport  \
                -addresswidth    32  \
                -addresswidthmin 32  \
                -addresswidthmax 49  \
                -mustbeconnected
  iadddocumentation  \
                -name Description  \
                -text "Master port - connect to same bus connected to Linux processor's data port"
                
imodeladdformal  \
                -name kernel  \
                -type string  \
		-defaultvalue "Image"
  iadddocumentation  \
                -name Description  \
                -text "Name of the the Linux kernel image file (default: Image)"
                
imodeladdformal  \
                -name kerneladdr  \
                -type uns64
  iadddocumentation  \
                -name Description  \
                -text "Address to load the Linux kernel image file (default: physicalbase+0x00080000)"

imodeladdformal  \
                -name dtb  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Name of the device tree blob file. (required)"

imodeladdformal  \
                -name command  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Set command line passed to kernel. (optional)"

imodeladdformal  \
                -name append  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Append to the command line passed to kernel. (optional)"

imodeladdformal  \
                -name initrd  \
                -type string
  iadddocumentation  \
                -name Description  \
                -text "Name of the initial ram disk file to load. (optional)"

imodeladdformal  \
                -name physicalbase  \
                -type uns64
  iadddocumentation  \
                -name Description  \
                -text "The physical address of the base of memory. (default: 0)"

imodeladdformal  \
                -name disable  \
                -type bool
  iadddocumentation  \
                -name Description  \
                -text "Set to True to disable the smart loader"
