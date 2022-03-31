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

set vendor  ovpworld.org
set library peripheral
set name    VirtioBlkMMIO
set version 1.0
set desc "
 VIRTIO version 1 mmio block device
 This model implements a VIRTIO  MMIO block device as described in:
      http://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.pdf.
 Use the VB_DRIVE parameter to specify the disk image file to use.
 Set the VB_DRIVE_DELTA parameter to 1 to prevent writes to disk during 
 simulation from changing the image file.
"
set limitations "
Only supports the Legacy (Device Version 1) interface.
Only little endian guests are supported.
"
set reference "
http://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.pdf
"

set range 0x200

imodelnewperipheral           \
    -imagefile   pse.pse      \
    -name        $name        \
    -vendor      $vendor      \
    -library     $library     \
    -version     $version     \
    -constructor constructor  \
    -destructor  destructor   \
    -releasestatus ovp        \
    -visibility   visible     \
    -nbyteregisters

iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference   -text $reference

imodeladdbusmasterport -name dma -addresswidth 40 -mustbeconnected

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x200   -port bport1 -width 32
set addBlock     "bport1/ab"


#   name          offset  ac readFn    writeFn     viewFn   user reset      mask       description   
set registers {
	MagicValue    0x000   r  rdMagic   -           -        -    0x74726976 -          "Magic value ('virt' string)"
    Version       0x004   r  -         -           -        -    0x00000001 -          "Device Version number"
    DeviceID      0x008   r  -         -           -        -    0x00000002 -          "Block Subsystem Device ID"
    VendorID      0x00c   r  -         -           -        -    0x0050564F -          "Subsystem Vendor ID ('OVP' string)"
    HostFeatures  0x010   r  rdHostF   -           -        -    0x08000000 -          "Host features flags"
    HostFSel      0x014   w  -         -           -        -    0x0        -          "Host features select"
    GuestFeatures 0x020   w  -         wrGuestF    -        -    0x0        -          "Guest features flags"
    GuestFSel     0x024   w  -         -           -        -    0x0        -          "Guest features select"
    GuestPageSz   0x028   w  -         wrGPgSz     -        -    0x0        -          "Guest page size"
    QueueSel      0x030   w  -         wrQSel      -        -    0x0        -          "Virtual queue index"
    QueueNumMax   0x034   r  -         -           -        -    0x00000100 -          "Maximum virtual queue size"
    QueueNum      0x038   w  -         wrQNum      -        -    0x0        -          "Virtual queue size"
    QueueAlign    0x03c   w  -         wrQAlign    -        -    0x0        -          "Virtual queue align"
    QueuePFN      0x040   rw rdQPFN    wrQPFN      -        -    0x0        -          "Virtual queue PFN"
    QueueNotify   0x050   w  -         wrQNotify   -        -    0x0        -          "Virtual queue notify"
    IntStatus     0x060   r  rdIntStat -           -        -    0x0        -          "Interrupt status"
    IntAck        0x064   w  -         wrIntAck    -        -    0x0        0x00000003 "Interrupt acknowlege"
    Status        0x070   rw rdStatus  wrStatus    -        -    0x0        -          "Device status"
}

foreach { rname offset raccess readFn writeFn viewFn user reset mask desc } $registers {
    set r ""
    set w ""
    set v ""
    set u ""
    set m ""
    if { $readFn  != "-" } { set r "-readfunction  $readFn"   }
    if { $writeFn != "-" } { set w "-writefunction $writeFn"  }
    if { $viewFn  != "-" } { set v "-writefunction $viewFn"   }
    if { $user    != "-" } { set u "-userdata $user"          }
    if { $mask    != "-" } { set m "-writemask $mask"         }

    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w $u $m"
    eval $cmd

    if { $reset != "-" } {
        imodeladdreset -mmregister $addBlock/$rname -name Reset -value $reset
    }

    iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
}

#
# Model virtio_blk_config as a read-only local memory block
#
imodeladdlocalmemory -name BlkConfig -addressblock $addBlock -offset 0x100 -size 0x100  -nbyte -access r -readfunction readCfg


#
# Register fields
#
imodeladdfield -mmregister $addBlock/IntStatus -name UsedRingUpdate -bitoffset 0 -width 1
imodeladdfield -mmregister $addBlock/IntStatus -name ConfigChange   -bitoffset 1 -width 1

imodeladdfield -mmregister $addBlock/IntAck    -name UsedRingUpdate -bitoffset 0 -width 1
imodeladdfield -mmregister $addBlock/IntAck    -name ConfigChange   -bitoffset 1 -width 1

imodeladdfield -mmregister $addBlock/Status    -name Ack            -bitoffset 0 -width 1
imodeladdfield -mmregister $addBlock/Status    -name Driver         -bitoffset 1 -width 1
imodeladdfield -mmregister $addBlock/Status    -name DriverOk       -bitoffset 2 -width 1
imodeladdfield -mmregister $addBlock/Status    -name Failed         -bitoffset 7 -width 1

#
# Net Ports
#
imodeladdnetport -name Interrupt   -type output

#
# Formals
#
imodeladdformal   -name VB_DRIVE        -type string
iadddocumentation -name Description     -text "Filename of image for Virtio Block device"

imodeladdformal   -name VB_DRIVE_DELTA -type bool
iadddocumentation -name Description    -text "If true the Drive uses delta writes (image will not be updated)"


imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS