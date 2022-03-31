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
    -name    LAN9118 \
    -vendor  smsc.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -destructor destructor \
    -releasestatus ovp

iadddocumentation -name Description -text "Fully functional Model of SMSC LAN9118 for Arm Versatile Express platforms. For full details please consult README-EMAC.txt"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "See README-EMAC.txt"
iadddocumentation -name Reference   -text "SMSC LAN9118 High Performance single-chip 10/100 Non-PCI Ethernet Controller Datasheet Revision 1.5 (07-11-08)"

# Irq net port
imodeladdnetport -name irq -type output
iadddocumentation -name Description -text "IRQ Pin"

#
# Interface to the packetnet network. The maxbytes parameter sets the maximum
# packet length supported by this network, enforced by the simulator.
# Max Ethernet Frame = 1522 bytes
# size indicator 2 bytes (unsigned short int)
# total = 1524
imodeladdpacketnetport \
    -name phy \
    -maxbytes 1524
iadddocumentation -name Description -text "The port to connect the packetnet virtual network"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"


#   name     offset ac description      readFn     writeFn      bits

set registers {
        RX_DATA_FIFO    0x00    r    ""    rxFifoRd       -            - 
        RX_DATA_FIFO_1  0x04    r    ""    rxFifoRd       -            -
        RX_DATA_FIFO_2  0x08    r    ""    rxFifoRd       -            -
        RX_DATA_FIFO_3  0x0c    r    ""    rxFifoRd       -            -
        RX_DATA_FIFO_4  0x10    r    ""    rxFifoRd       -            -
        RX_DATA_FIFO_5  0x14    r    ""    rxFifoRd       -            -
        RX_DATA_FIFO_6  0x18    r    ""    rxFifoRd       -            -
        RX_DATA_FIFO_7  0x1c    r    ""    rxFifoRd       -            -
        
        TX_DATA_FIFO    0x20    w    ""    -              txFifoWr     -
        TX_DATA_FIFO_1  0x24    w    ""    -              txFifoWr     -
        TX_DATA_FIFO_2  0x28    w    ""    -              txFifoWr     -
        TX_DATA_FIFO_3  0x2c    w    ""    -              txFifoWr     -
        TX_DATA_FIFO_4  0x30    w    ""    -              txFifoWr     -
        TX_DATA_FIFO_5  0x34    w    ""    -              txFifoWr     -
        TX_DATA_FIFO_6  0x38    w    ""    -              txFifoWr     -
        TX_DATA_FIFO_7  0x3c    w    ""    -              txFifoWr     - 
        
        RX_STATUS_FIFO       0x40    r    ""    rxStatusFifoRd       -            -
        RX_STATUS_FIFO_PEEK  0x44    r    ""    rxStatusFifoPeek     -            -
        
        TX_STATUS_FIFO       0x48    r    ""    txStatusFifoRd       -            -
        TX_STATUS_FIFO_PEEK  0x4c    r    ""    txStatusFifoPeek     -            -
        
        ID_REV          0x50    r    ""    idRev          -            -
        IRQ_CFG         0x54    rw   ""    irqCfgRd       irqCfgWr     -
        INT_STS         0x58    rw   ""    intStsRd       intStsWr     -
        INT_EN          0x5c    rw   ""    intEnRd        intEnWr      -
                                                        
        BYTE_TEST       0x64    r    ""    byteTest       -            -
        FIFO_INT        0x68    rw   ""    -              -            -
        RX_CFG          0x6c    rw   ""    rxCfgRd        rxCfgWr      -
        TX_CFG          0x70    rw   ""    txCfgRd        txCfgWr      -
        HW_CFG          0x74    rw   ""    hwCfgRd        hwCfgWr      -
        RX_DP_CTRL      0x78    rw   ""    -              -            -
        RX_FIFO_INF     0x7c    r    ""    rxFifoInfRd              -            -
        TX_FIFO_INF     0x80    r    ""    txFifoInfRd    -            -
        PMT_CTRL        0x84    rw   ""    -              -            -
        GPIO_CFG        0x88    rw   ""    -              -            -
        GPT_CFG         0x8c    rw   ""    -              -            -
        GPT_CNT         0x90    r    ""    -              -            -
                                                        
        WORD_SWAP       0x98    rw   ""    -              -            -
        FREE_RUN        0x9c    r    ""    -              -            -
        RX_DROP         0xA0    r    ""    rxDropRd       -            -
        MAC_CSR_CMD     0xA4    rw   ""    macCsrCmdRd    macCsrCmdWr  -
        MAC_CSR_DATA    0xA8    rw   ""    macCsrDataRd   macCsrDataWr -
        AFC_CFG         0xAc    rw   ""    -              -            -
        E2P_CMD         0xB0    rw   ""    -              -            -
        E2P_DATA        0xB4    rw   ""    -              -            -
}

foreach { name roffset raccess desc readFn writeFn bits } $registers {
    set rname ${name}

    if { $readFn != "-" } {
        set r "-readfunction $readFn"
    } else {
        set r "-readfunction defaultRdCB"
        if { $raccess == "rw" || $raccess == "r" } {
            set r "-readfunction defaultRdCB"
        } else {
            set r ""
        }
    }
    if { $writeFn != "-" } {
        set w "-writefunction $writeFn"
    } else {
        if { $raccess == "rw" || $raccess == "w" } {
            set w "-writefunction defaultWrCB"
        } else {
            set w ""
        }
    }

    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $roffset -access $raccess $r $w -userdata $roffset"

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

imodeladdfield -mmregister ${addBlock}/ID_REV      -name ID            -bitoffset 16 -width 16 -access r
imodeladdfield -mmregister ${addBlock}/ID_REV      -name REV           -bitoffset  0 -width 16 -access r
                                                                       
imodeladdfield -mmregister ${addBlock}/IRQ_CFG     -name INT_DEAS      -bitoffset 24 -width  8 -access rw
imodeladdfield -mmregister ${addBlock}/IRQ_CFG     -name INT_DEAS_CLR  -bitoffset 14 -width  0 -access rw
imodeladdfield -mmregister ${addBlock}/IRQ_CFG     -name INT_DEAS_STS  -bitoffset 13 -width  0 -access rw
imodeladdfield -mmregister ${addBlock}/IRQ_CFG     -name IRQ_INT       -bitoffset 12 -width  0 -access r
imodeladdfield -mmregister ${addBlock}/IRQ_CFG     -name IRQ_EN        -bitoffset  8 -width  0 -access rw
imodeladdfield -mmregister ${addBlock}/IRQ_CFG     -name IRQ_POL       -bitoffset  4 -width  0 -access rw
imodeladdfield -mmregister ${addBlock}/IRQ_CFG     -name IRQ_TYPE      -bitoffset  0 -width  0 -access rw
                                                                                          
imodeladdfield -mmregister ${addBlock}/INT_STS     -name SW_INT        -bitoffset 31 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name TXSTOP_INT    -bitoffset 25 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name RXSTOP_INT    -bitoffset 24 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name RXDFH_INT     -bitoffset 23 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name TX_IOC        -bitoffset 21 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name RXD_INT       -bitoffset 20 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name GPT_INT       -bitoffset 19 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name PHY_INT       -bitoffset 18 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name PME_INT       -bitoffset 17 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name TXSO          -bitoffset 16 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name RWT           -bitoffset 15 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name RXE           -bitoffset 14 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name TXE           -bitoffset 13 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name TDFO          -bitoffset 10 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name TDFA          -bitoffset  9 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name TSFF          -bitoffset  8 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name TSFL          -bitoffset  7 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name RXDF_INT      -bitoffset  6 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name RSFF          -bitoffset  4 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name RSFL          -bitoffset  3 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_STS     -name GPIOx_INT     -bitoffset  0 -width  3 -access rw

imodeladdfield -mmregister ${addBlock}/INT_EN      -name SW_INT_EN     -bitoffset 31 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name TXSTOP_INT_EN -bitoffset 25 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name RXSTOP_INT_EN -bitoffset 24 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name RXDFH_INT_EN  -bitoffset 23 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name TIOC_INT_EN   -bitoffset 21 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name RXD_INT       -bitoffset 20 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name GPT_INT_EN    -bitoffset 19 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name PHY_INT_EN    -bitoffset 18 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name PME_INT_EN    -bitoffset 17 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name TXSO_EN       -bitoffset 16 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name RWT_INT_EN    -bitoffset 15 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name RXE_INT_EN    -bitoffset 14 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name TXE_INT_EN    -bitoffset 13 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name TDFO_INT_EN   -bitoffset 10 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name TDFA_INT_EN   -bitoffset  9 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name TSFF_INT_EN   -bitoffset  8 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name TSFL_INT_EN   -bitoffset  7 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name RXDF_INT_EN   -bitoffset  6 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name RSFF_INT_EN   -bitoffset  4 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name RSFL_INT_EN   -bitoffset  3 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/INT_EN      -name GPIOx_INT_EN  -bitoffset  0 -width  3 -access rw

imodeladdfield -mmregister ${addBlock}/FIFO_INT    -name TXDataAvailL  -bitoffset 24 -width  8 -access rw
imodeladdfield -mmregister ${addBlock}/FIFO_INT    -name TXStatusL     -bitoffset 16 -width  8 -access rw
imodeladdfield -mmregister ${addBlock}/FIFO_INT    -name RXStatusL     -bitoffset  0 -width  8 -access rw

imodeladdfield -mmregister ${addBlock}/RX_CFG      -name RXEndAlign    -bitoffset 30 -width  2 -access rw
imodeladdfield -mmregister ${addBlock}/RX_CFG      -name RX_DMA_CNT    -bitoffset 16 -width 12 -access rw
imodeladdfield -mmregister ${addBlock}/RX_CFG      -name RX_DUMP       -bitoffset 15 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/RX_CFG      -name RXDOFF        -bitoffset  8 -width  5 -access rw

imodeladdfield -mmregister ${addBlock}/TX_CFG      -name TXS_DUMP      -bitoffset 15 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/TX_CFG      -name TXD_DUMP      -bitoffset 14 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/TX_CFG      -name TXSAO         -bitoffset  2 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/TX_CFG      -name TX_ON         -bitoffset  1 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/TX_CFG      -name STOP_TX       -bitoffset  0 -width  1 -access rw

imodeladdfield -mmregister ${addBlock}/HW_CFG      -name MBO           -bitoffset 20 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/HW_CFG      -name TX_FIF_SZ     -bitoffset 16 -width  4 -access rw
imodeladdfield -mmregister ${addBlock}/HW_CFG      -name MODE1632      -bitoffset  2 -width  1 -access r
imodeladdfield -mmregister ${addBlock}/HW_CFG      -name SRST_TO       -bitoffset  1 -width  1 -access r
imodeladdfield -mmregister ${addBlock}/HW_CFG      -name SRST          -bitoffset  0 -width  1 -access rw

imodeladdfield -mmregister ${addBlock}/RX_DP_CTRL  -name RX_FFWD       -bitoffset 31 -width  1 -access rw

imodeladdfield -mmregister ${addBlock}/RX_FIFO_INF -name RXSUSED       -bitoffset 16 -width  8 -access r
imodeladdfield -mmregister ${addBlock}/RX_FIFO_INF -name RXDUSED       -bitoffset  0 -width 16 -access r

imodeladdfield -mmregister ${addBlock}/TX_FIFO_INF -name TXSUSED       -bitoffset 16 -width  8 -access r
imodeladdfield -mmregister ${addBlock}/TX_FIFO_INF -name TXDFREE       -bitoffset  0 -width 16 -access r

imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name PM_MODE       -bitoffset 12 -width  2 -access rw
imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name PHY_RST       -bitoffset 10 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name WOL_EN        -bitoffset  9 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name ED_EN         -bitoffset  8 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name PME_TYPE      -bitoffset  6 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name WUPS          -bitoffset  4 -width  2 -access rw
imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name PME_IND       -bitoffset  3 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name PME_POL       -bitoffset  2 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name PME_EN        -bitoffset  1 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/PMT_CTRL    -name READY         -bitoffset  0 -width  1 -access r

imodeladdfield -mmregister ${addBlock}/GPIO_CFG    -name LEDx_EN       -bitoffset 28 -width  3 -access rw
imodeladdfield -mmregister ${addBlock}/GPIO_CFG    -name GPIO_INT_POL  -bitoffset 24 -width  3 -access rw
imodeladdfield -mmregister ${addBlock}/GPIO_CFG    -name EEPR_EN       -bitoffset 20 -width  3 -access rw
imodeladdfield -mmregister ${addBlock}/GPIO_CFG    -name GPIOBUFn      -bitoffset 16 -width  3 -access rw
imodeladdfield -mmregister ${addBlock}/GPIO_CFG    -name GPDIRn        -bitoffset  8 -width  3 -access rw
imodeladdfield -mmregister ${addBlock}/GPIO_CFG    -name GPODn         -bitoffset  3 -width  2 -access rw
imodeladdfield -mmregister ${addBlock}/GPIO_CFG    -name GPIODn        -bitoffset  0 -width  3 -access rw

imodeladdfield -mmregister ${addBlock}/GPT_CFG     -name TIMER_EN      -bitoffset 29 -width  0 -access rw
imodeladdfield -mmregister ${addBlock}/GPT_CFG     -name GPT_LOAD      -bitoffset  0 -width 16 -access rw

imodeladdfield -mmregister ${addBlock}/GPT_CNT     -name GPT_CNT       -bitoffset  0 -width 16 -access r

imodeladdfield -mmregister ${addBlock}/FREE_RUN    -name FR_CNT        -bitoffset  0 -width 32 -access r

imodeladdfield -mmregister ${addBlock}/RX_DROP     -name RX_DFC        -bitoffset  0 -width 32 -access r

imodeladdfield -mmregister ${addBlock}/MAC_CSR_CMD -name CSRBusy       -bitoffset 31 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/MAC_CSR_CMD -name RnW           -bitoffset 30 -width  1 -access rw
imodeladdfield -mmregister ${addBlock}/MAC_CSR_CMD -name CSRAddress    -bitoffset  0 -width  8 -access rw

imodeladdfield -mmregister ${addBlock}/MAC_CSR_DATA -name MACCSRData   -bitoffset  0 -width  32 -access rw

imodeladdfield -mmregister ${addBlock}/AFC_CFG     -name AFC_HI        -bitoffset 16 -width   8 -access rw
imodeladdfield -mmregister ${addBlock}/AFC_CFG     -name AFC_LO        -bitoffset  8 -width   8 -access rw
imodeladdfield -mmregister ${addBlock}/AFC_CFG     -name BACK_DUR      -bitoffset  4 -width   4 -access rw
imodeladdfield -mmregister ${addBlock}/AFC_CFG     -name FCMULT        -bitoffset  3 -width   1 -access rw
imodeladdfield -mmregister ${addBlock}/AFC_CFG     -name FCBRD         -bitoffset  2 -width   1 -access rw
imodeladdfield -mmregister ${addBlock}/AFC_CFG     -name FCADD         -bitoffset  1 -width   1 -access rw
imodeladdfield -mmregister ${addBlock}/AFC_CFG     -name FCANY         -bitoffset  0 -width   1 -access rw

imodeladdfield -mmregister ${addBlock}/E2P_CMD     -name EPCBusy       -bitoffset 31 -width   1 -access rw
imodeladdfield -mmregister ${addBlock}/E2P_CMD     -name EPCcommand    -bitoffset 28 -width   3 -access rw
imodeladdfield -mmregister ${addBlock}/E2P_CMD     -name EPCTimeout    -bitoffset  9 -width   1 -access rw
imodeladdfield -mmregister ${addBlock}/E2P_CMD     -name MACAddrLoaded -bitoffset  8 -width   1 -access rw
imodeladdfield -mmregister ${addBlock}/E2P_CMD     -name EPCAddr       -bitoffset  0 -width   8 -access rw

imodeladdfield -mmregister ${addBlock}/E2P_DATA    -name EEPROMData    -bitoffset  0 -width   8 -access rw

#
# Formal attributes
#
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
imodeladdformalmacro -name BHM_ETHERNET_OPEN_AUTO_FORMALS
