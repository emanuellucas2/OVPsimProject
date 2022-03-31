/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

    .text
    .globl  __start
    .globl  main
    .set    noat
    .set    noreorder
    .ent    main

    .text

__start:
main:

    mfc0    $t0, $16, 0     # get config
    li      $t1, 0xfffffffc # clear K0
    and     $t0, $t1
    li      $t1, 0x00000002 # set K0 to cached
    or      $t0, $t1
    mtc0    $t0, $16, 0     # set config

    mfc0    $t0, $26, 0     # get errctl
    lui     $t1, 0x1000     # set SPR bit
    or      $t0, $t1
    mtc0    $t0, $26, 0     # set errctl

    li      $a1, 0x0

    # store known pattern at VA=0x00000000
    lui     $t1, 0x0000
    lui     $t0, 0x1122
    ori     $t0, 0x3344
    sw      $t0, 0($t1)
    lw      $t0, 0($t1)

    # read ISPRAM tags
    cache   0x4, 0($a1)     # load ISPRAM region 0 tag 0 (base/enable)
    cache   0x4, 8($a1)     # load ISPRAM region 0 tag 1 (size)
    cache   0x4, 0x1000($a1) # load ISPRAM region 1 tag 0 (base/enable)
    cache   0x4, 0x1008($a1) # load ISPRAM region 1 tag 1 (size)

    # read DSPRAM tags
    cache   0x5, 0($a1)     # load DSPRAM region 0 tag 0 (base/enable)
    cache   0x5, 8($a1)     # load DSPRAM region 0 tag 1 (size)
    cache   0x5, 0x2000($a1) # load DSPRAM region 1 tag 0 (base/enable)
    cache   0x5, 0x2008($a1) # load DSPRAM region 1 tag 1 (size)

    # enable DSPRAM 0 at its default location
    cache   0x5, 0($a1)     # load DSPRAM region 0 tag 0 (base/enable)
    mfc0    $t0, $28, 2     # get DTagLo
    ori     $t0, 0x80       # set DTagLo.E
    mtc0    $t0, $28, 2     # set DTagLo
    cache   0x9, 0($a1)     # store DSPRAM region 0 tag 0 (base/enable)

    # load from VA=0x00000000 (returns 0 since now reading from SPRAM)
    lw      $t0, 0($t1)

    # store known pattern at VA=0x00000000
    lui     $t0, 0x5566
    ori     $t0, 0x7788
    sw      $t0, 0($t1)
    lw      $t0, 0($t1)

    # get address of function dotest
    la      $t2, dotest

    # move DSPRAM 0 from its default location
    cache   0x5, 0($a1)     # load DSPRAM region 0 tag 0 (base/enable)
    mfc0    $t0, $28, 2     # get DTagLo
    or      $t0, $t2        # modify DTagLo.base
    mtc0    $t0, $28, 2     # set DTagLo
    cache   0x9, 0($a1)     # store DSPRAM region 0 tag 0 (base/enable)

    # load from VA=0x00000000 (returns 11223344 since now reading from RAM)
    lw      $t0, 0($t1)

    # load from VA=dotest (returns 55667788 since now reading from SPRAM)
    lw      $t0, 0($t2)

    # branch to dotest (executes from initially-installed ISPRAM 0 even through
    # DSPRAM 0 is also at this address)
    bal     dotest
    nop

    # disable ISPRAM 0 at dotest address
    cache   0x4, 0($a1)     # load ISPRAM region 0 tag 0 (base/enable)
    mfc0    $t0, $28, 0     # get ITagLo
    xori    $t0, 0x80       # clear ITagLo.E
    mtc0    $t0, $28, 0     # set ITagLo
    cache   0x8, 0($a1)     # store ISPRAM region 0 tag 0 (base/enable)

    # branch to dotest (executes from RAM)
    bal     dotest
    nop

    # install ISPRAM 1 at dotest address
    cache   0x4, 0x1000($a1) # load ISPRAM region 1 tag 0 (base/enable)
    mfc0    $t0, $28, 0     # get ITagLo
    or      $t0, $t2        # set ITagLo.base
    ori     $t0, 0x80       # set ITagLo.E
    mtc0    $t0, $28, 0     # set ITagLo
    cache   0x8, 0x1000($a1) # store ISPRAM region 1 tag 0 (base/enable)

    # branch to dotest (executes from ISPRAM 1)
    bal     dotest
    nop

    # update instruction in IDataLo, overwrite first two instructions of ISPRAM 1
    mfc0    $t0, $28, 1     # get IDataLo
    ori     $t0, 0xf        # modify constant in instruction
    mtc0    $t0, $28, 1     # set IDataLo
    cache   0xc, 0x1000($a1) # store ISPRAM data

    # branch to dotest (executes from ISPRAM 1, code now modified)
    bal     dotest
    nop

exit:
    b       exit
    nop

.org 0x2000

dotest:
    addi    $t0, $t0, 1
    jr      $ra
    nop

.end    main

