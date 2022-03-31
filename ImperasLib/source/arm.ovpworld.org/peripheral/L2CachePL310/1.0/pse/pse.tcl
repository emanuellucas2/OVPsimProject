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

set range    0x1000
set regWidth 32

imodelnewperipheral  \
    -imagefile pse.pse  \
    -name    L2CachePL310 \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM PL310 L2 Cache Control Registers"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "Programmers View, register model only. Does NOT model functionality, just provides registers to allow code to run." 
iadddocumentation -name Reference   -text "ARM PrimeCell Level 2 Cache Controller (PL310) Technical Reference Manual (ARM DDI 0246)"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"


#   name     offset ac description             readFn     writeFn      bits
set registers {
    reg0_cache_id         0x000   r     "                 "    readId   -    -
    reg0_cache_type       0x004   r     "                 "    readType   -    -
    reg1_control          0x100   rw    "                 "    readCtrl   writeCtrl    -
    reg1_aux_control      0x104   rw    "                 "    readAux  writeAux   -
    reg1_tag_ram_control  0x108   rw    "                 "    -   -    -
    reg1_data_ram_control 0x10C   rw    "                 "    -   -    -
    reg2_ev_counter_ctrl  0x200   rw    "                 "    -   -    -
    reg2_ev_counter1_cfg  0x204   rw    "                 "    -   -    -
    reg2_ev_counter0_cfg  0x208   rw    "                 "    -   -    -
    reg2_ev_counter1      0x20C   rw    "                 "    -   -    -
    reg2_ev_counter0      0x210   rw    "                 "    -   -    -
    reg2_int_maske        0x214   rw    "                 "    -   -    -
    reg2_int_mask_statuse 0x218   r     "                 "    -   -    -
    reg2_int_raw_statuse  0x21C   r     "                 "    -   -    -
    reg2_int_cleare       0x220   w     "                 "    -   -    -
    reg7_cache_sync       0x730   rw    "                 "    -   -    -
    reg7_inv_pa           0x770   rw    "                 "    -   -    -
    reg7_inv_way          0x77C   rw    "                 "    readInvWay   -    -
    reg7_clean_pa         0x7B0   rw    "                 "    -   -    -
    reg7_clean_index      0x7B8   rw    "                 "    -   -    -
    reg7_clean_way        0x7BC   rw    "                 "    readCleanWay   -    -
    reg7_clean_inv_pa     0x7F0   rw    "                 "    -   -    -
    reg7_clean_inv_index  0x7F8   rw    "                 "    -   -    -
    reg7_clean_inv_way    0x7FC   rw    "                 "    readCleanInvWay   -    -
    reg9_d_lockdown0      0x900   rw    "                 "    -   -    -
    reg9_i_lockdown0      0x904   rw    "                 "    -   -    -
    reg9_d_lockdown1f     0x908   rw    "                 "    -   -    -
    reg9_i_lockdown1f     0x90C   rw    "                 "    -   -    -
    reg9_d_lockdown2f     0x910   rw    "                 "    -   -    -
    reg9_i_lockdown2f     0x914   rw    "                 "    -   -    -
    reg9_d_lockdown3f     0x918   rw    "                 "    -   -    -
    reg9_i_lockdown3f     0x91C   rw    "                 "    -   -    -
    reg9_d_lockdown4f     0x920   rw    "                 "    -   -    -
    reg9_i_lockdown4f     0x924   rw    "                 "    -   -    -
    reg9_d_lockdown5f     0x928   rw    "                 "    -   -    -
    reg9_i_lockdown5f     0x92C   rw    "                 "    -   -    -
    reg9_d_lockdown6f     0x930   rw    "                 "    -   -    -
    reg9_i_lockdown6f     0x934   rw    "                 "    -   -    -
    reg9_d_lockdown7f     0x938   rw    "                 "    -   -    -
    reg9_i_lockdown7f     0x93C   rw    "                 "    -   -    -
    reg9_lock_line_eng    0x950   rw    "                 "    -   -    -
    reg9_unlock_wayg      0x954   rw    "                 "    -   -    -
    reg12_addr_filt_start 0xC00   rw    "                 "    -   -    -
    reg12_addr_filt_end   0xC04   rw    "                 "    -   -    -
    reg15_debug_ctrl      0xF40   rw    "                 "    -   -    -
    reg15_prefetch_ctrl   0xF60   rw    "                 "    -   -    -
    reg15_power_ctrl      0xF80   rw    "                 "    -   -    -
}


foreach { name roffset raccess desc readFn writeFn bits } $registers {
    set rname ${name}

    if { $readFn != "-" } {
        set r "-readfunction $readFn"
    } else {
        set r ""
    }
    if { $writeFn != "-" } {
        set w "-writefunction $writeFn"
    } else {
        set w ""
    }

    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $roffset -access $raccess $r $w"

    eval $cmd
    if { $desc != 0 } {
        iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
    }

    if { $bits != "-" } {
        foreach { n o } $bits {
            imodeladdfield -mmregister "$addBlock/$rname" -bitoffset $o -name $n
        }
    }
}

# Interrupt line
imodeladdnetport -name irq -type output
