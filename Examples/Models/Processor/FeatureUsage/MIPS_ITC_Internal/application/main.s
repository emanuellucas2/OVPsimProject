    .text
    .globl  __start
    .globl  main
    .set    noat
    .set    noreorder
    .ent    main

__start:
main:

    ############################################################################
    # ENABLE ITC BLOCK
    ############################################################################

    # allow access to ITCAddressMap0/ITCAddressMap1
    mfc0    $t0,$26,0           # get c0_errctl
    lui     $t1,0x0400          # mask for c0_errctl.ITC
    or      $t0,$t0,$t1         # set c0_errctl.ITC
    mtc0    $t0,$26,0           # set c0_errctl

    # update ITCAddressMap0
    li      $a1, 0x0
    lui     $t0,0x0010          # ITCAddressMap0=0x00100001
    ori     $t0,0x0001          # ITCAddressMap0=0x00100001
    mtc0    $t0,$28,2           # set c0_dtaglo
    cache   0x8, 0($a1)         # store ITCAddressMap0
    mtc0    $zero,$28,2         # clear c0_dtaglo
    cache   0x4, 0($a1)         # load ITCAddressMap0

    # update ITCAddressMap1
    li      $a1, 0x0
    li      $t0,0x0c01          # ITCAddressMap1=0x00000c01
    mtc0    $t0,$28,2           # set c0_dtaglo
    cache   0x8, 8($a1)         # store ITCAddressMap1
    mtc0    $zero,$28,2         # clear c0_dtaglo
    cache   0x4, 8($a1)         # load ITCAddressMap1

    ############################################################################
    # CLEAR status.ERL
    ############################################################################

    evpe

    mfc0    $t0,$12,0           # get c0_status
    ori     $t0,$t0,0x8005      # set c0_status/ERL, c0_status/EI,
                                # set external interrupt mask
    xori    $t0,$t0,0x4         # clear c0_status/ERL
    mtc0    $t0,$12,0           # set c0_status

    dmt

    ############################################################################
    # PREPARE TC1 SO THAT IT CAN BE SPAWNED BY A FORK INSTRUCTION
    ############################################################################

    mfc0    $t0,$0,1            # get c0_mvpcontrol
    ori     $t0,$t0,0x2         # set c0_mvpcontrol.VPC
    mtc0    $t0,$0,1            # set c0_mvpcontrol
    mfc0    $t0,$1,1            # get c0_vpecontrol
    ori     $t0,$t0,0xff        #
    xori    $t0,$t0,0xff        #
    ori     $t0,$t0,1           # select TC #1 as target
    mtc0    $t0,$1,1            # set c0_vpecontrol
    mftc0   $t0,$2,1            # get target thread c0_tcstatus
    ori     $t0,$t0,0x8000      # set c0_tcstatus/DA
    mttc0   $t0,$2,1            # set target thread c0_tcstatus
    mttc0   $zero,$2,4          # clear target thread c0_tchalt
    mftc0   $t0,$2,2            # get target thread c0_tcbind
    ori     $t0,$t0,0xf         # set c0_tcbind/curVPE
    xori    $t0,$t0,0xf         # clear c0_tcbind/curVPE
    mttc0   $t0,$2,2            # set target thread c0_tcbind
    mfc0    $t0,$0,1            # get c0_mvpcontrol
    xori    $t0,$t0,0x2         # clear c0_mvpcontrol.VPC
    mtc0    $t0,$0,1            # set c0_mvpcontrol

    emt

tc0code:

    ############################################################################
    # CODE EXECUTED BY TC0
    ############################################################################

    la      $t1,tc1code         # fork off TC1 code
    fork    $a0,$t1,$t0

    # exercise FIFO cell using E/F synchronized view

    li      $t0,0x0
    lui     $t1,0x8010          # get address of first FIFO cell

    li      $t3,4
1:  addi    $t0,$t0,1           # do 4 FIFO cell writes
    bne     $t0,$t3,1b
    sw      $t0,0x10($t1)

    lw      $t2,0x00($t1)       # load using bypass view
    addi    $t2,0x100
    sw      $t2,0x00($t1)       # store using bypass view

    addi    $t0,$t0,1
    sw      $t0,0x10($t1)       # do 5th FIFO cell write (blocks)

    li      $t3,10
1:  addi    $t0,$t0,1           # wait (monitoring FIFO tag)
    bne     $t0,$t3,1b
    lw      $t2,0x08($t1)

    li      $t3,11
1:  addi    $t0,$t0,1           # fill one more cell
    bne     $t0,$t3,1b
    sw      $t0,0x10($t1)

    # exercise FIFO cell using E/F try view

    li      $t0,0x0

    li      $t3,8
1:  addi    $t0,$t0,1           # do 8 FIFO cell try-writes
    sw      $t0,0x18($t1)       # normal store
    addi    $t0,$t0,1
    addi    $t2,$t0,0
    bne     $t0,$t3,1b
    sc      $t2,0x18($t1)       # overloaded conditional store

    li      $t3,10
1:  addi    $t0,$t0,1           # wait (monitoring FIFO tag)
    bne     $t0,$t3,1b
    lw      $t2,0x08($t1)

    # exercise semaphore cell using P/V synchronized view

    li      $t0,0x0
    lui     $t1,0x8010          # get address of first semaphore cell
    addi    $t1,0x0800

    li      $t3,4
1:  addi    $t0,$t0,1           # do 4 semaphore cell writes
    bne     $t0,$t3,1b
    sw      $zero,0x20($t1)

    li      $t3,17
1:  addi    $t0,$t0,1           # wait (monitoring semaphore tag)
    bne     $t0,$t3,1b
    lw      $t2,0x08($t1)

    li      $t3,21
1:  addi    $t0,$t0,1           # do 4 semaphore cell writes
    bne     $t0,$t3,1b
    sw      $zero,0x20($t1)

    # exercise semaphore cell using P/V try view

    li      $t0,0x0

    li      $t3,5
1:  addi    $t0,$t0,1           # wait (monitoring semaphore tag)
    bne     $t0,$t3,1b
    lw      $t2,0x08($t1)

    li      $t3,10
1:  addi    $t0,$t0,1           # do 5 semaphore cell try-writes
    bne     $t0,$t3,1b
    sw      $zero,0x28($t1)

    # enable exceptions on cell 0
    li      $t0,0x0
    lui     $t1,0x8010          # get address of first FIFO cell
    lw      $t2,0x08($t1)
    lui     $t0,0x0001
    or      $t2,$t2,$t0
    sw      $t2,0x08($t1)

    # exercise cell 0 views with exceptions enabled
    lw      $t0,0x00($t1)
    sw      $t0,0x00($t1)
    lw      $t0,0x08($t1)
    sw      $t0,0x08($t1)
    lw      $t0,0x10($t1)
    sw      $t0,0x10($t1)
    lw      $t0,0x18($t1)
    sw      $t0,0x18($t1)
    lw      $t0,0x20($t1)
    sw      $t0,0x20($t1)
    lw      $t0,0x28($t1)
    sw      $t0,0x28($t1)

    # validate illegal access conditions
    lb      $t0,0x00($t1)       # illegal load size
    lw      $t0,0x30($t1)       # illegal load view
    lw      $t0,0xc00($t1)      # illegal load cell address
    sb      $t0,0x00($t1)       # illegal store size
    sw      $t0,0x30($t1)       # illegal store view
    sw      $t0,0xc00($t1)      # illegal store cell address

tc0done:
    b       tc0done
    nop

tc1code:

    ############################################################################
    # CODE EXECUTED BY TC1
    ############################################################################

    # exercise FIFO cell using E/F synchronized view

    li      $t0,0x0
    lui     $t1,0x8010          # get address of first FIFO cell

    li      $t3,10
1:  addi    $t0,$t0,1           # wait (monitoring FIFO tag)
    bne     $t0,$t3,1b
    lw      $t2,0x08($t1)

    li      $t3,16
1:  addi    $t0,$t0,1           # do 6 FIFO cell reads
    bne     $t0,$t3,1b
    lw      $t2,0x10($t1)

    # exercise FIFO cell using E/F try view

    li      $t0,0x0

    li      $t3,10
1:  addi    $t0,$t0,1           # wait (monitoring FIFO tag)
    bne     $t0,$t3,1b
    lw      $t2,0x08($t1)

    li      $t3,16
1:  addi    $t0,$t0,1           # do 6 FIFO cell try-reads
    bne     $t0,$t3,1b
    lw      $t2,0x18($t1)

    # exercise semaphore cell using P/V synchronized view

    li      $t0,0x0
    lui     $t1,0x8010          # get address of first FIFO cell
    addi    $t1,0x0800

    li      $t3,4
1:  addi    $t0,$t0,1           # wait (monitoring semaphore tag)
    bne     $t0,$t3,1b
    lw      $t2,0x08($t1)

    li      $t3,9
1:  addi    $t0,$t0,1           # do 5 semaphore cell reads
    bne     $t0,$t3,1b
    lw      $t2,0x20($t1)

    li      $t2,0xfffe          # almost-saturated tag
    sw      $t2,0x00($t1)       # store using bypass view

    li      $t3,11
1:  addi    $t0,$t0,1           # wait (monitoring semaphore tag)
    bne     $t0,$t3,1b
    lw      $t2,0x08($t1)

    li      $t2,0x0             # empty tag
    sw      $t2,0x00($t1)       # store using bypass view

    # exercise semaphore cell using P/V try view

    li      $t0,0x0

    li      $t3,5
1:  addi    $t0,$t0,1           # do 5 semaphore cell try-reads
    bne     $t0,$t3,1b
    lw      $t2,0x28($t1)

    li      $t2,0xfffe          # almost-saturated tag
    sw      $t2,0x00($t1)       # store using bypass view

tc1done:
    b       tc1done
    nop

   .end    main
