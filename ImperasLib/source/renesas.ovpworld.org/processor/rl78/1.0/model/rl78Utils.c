/*
 * Copyright (c)      2016 eSOL TRINITY, www.esol-trinity.co.jp
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdlib.h>        // malloc

// VMI header files
#include "vmi/vmiDbg.h"
#include "vmi/vmiRt.h"

// model header files
#include "rl78Decode.h"
#include "rl78Functions.h"
#include "rl78Structure.h"
#include "rl78Utils.h"
#include "rl78Message.h"        // MY_ASSERT




#define SET_BIT(_R, _C, _M) \
    if(_C) {                    \
        (_R) = (_R) | (_M);     \
    } else {                    \
        (_R) = (_R) & ~(_M);    \
    }

#define GET_BIT(_R, _M) \
    (((_R) & (_M)) ? 1 : 0)


Uns8 rl78GetPSW_REG(rl78P rl78) {
    SET_BIT(rl78->PSW, rl78->PSW_IE, MASK_PSW_IE);            // 7
    SET_BIT(rl78->PSW, rl78->PSW_Z , MASK_PSW_Z );            // 6
    SET_BIT(rl78->PSW, rl78->PSW_AC, MASK_PSW_AC);            // 4
    SET_BIT(rl78->PSW, rl78->PSW_CY, MASK_PSW_CY);            // 0
    SET_BIT(rl78->PSW, rl78->PSW_RBS & 2, MASK_PSW_RBS1);    // 5
    SET_BIT(rl78->PSW, rl78->PSW_RBS & 1, MASK_PSW_RBS0);    // 3
    SET_BIT(rl78->PSW, rl78->PSW_ISP & 2, MASK_PSW_ISP1);    // 2
    SET_BIT(rl78->PSW, rl78->PSW_ISP & 1, MASK_PSW_ISP0);    // 1
    return rl78->PSW;
}

void rl78SetPSW_BIT(rl78P rl78) {
    Uns32 value = rl78->PSW;
    Uns32 old_RBS = rl78->PSW_RBS;
    
    rl78->PSW_IE  = GET_BIT(value, MASK_PSW_IE);
    rl78->PSW_Z   = GET_BIT(value, MASK_PSW_Z );
    rl78->PSW_AC  = GET_BIT(value, MASK_PSW_AC);
    rl78->PSW_CY  = GET_BIT(value, MASK_PSW_CY);
    rl78->PSW_RBS = (GET_BIT(value, MASK_PSW_RBS1) << 1) | GET_BIT(value, MASK_PSW_RBS0);
    rl78->PSW_ISP = (GET_BIT(value, MASK_PSW_ISP1) << 1) | GET_BIT(value, MASK_PSW_ISP0);
    
    if (rl78->PSW_RBS != old_RBS) {
        vmirtSetMode((vmiProcessorP) rl78, rl78->PSW_RBS);    // Bool vmirtSetMode(vmiProcessorP processor, Uns32 dictionaryIndex);
    }
    rl78InterruptNext((vmiProcessorP)rl78);
}



// This function is called when runtime.
// BRK instruction is another handling, because its execution timing is explicitly.
void rl78TakeException(rl78P rl78, rl78Exception exception, Uns32 pcOffset) {

    Uns32 currPC = (Uns32) vmirtGetPC((vmiProcessorP) rl78);
    Uns32 nextPC = currPC + pcOffset;
    Uns16 jumpPC = 0;

    // If a maskable interrupt request is acknowledged,
    // the contents are saved into the stacks in the order of PSW, then PC,
    memDomainP domain = vmirtGetProcessorDataDomain((vmiProcessorP) rl78);

    //memMapped vmirtWriteNByteDomain(
    //    memDomainP     domain,
    //    Addr           simAddress,
    //    const void    *buffer,
    //    Addr           size,
    //    memRegionPP    cachedRegion,
    //    memAccessAttrs attrs
    //);
    Uns8 psw = rl78GetPSW_REG(rl78);            // Transfer BIT members to PSW variable.
    rl78->SP = rl78->SP - 4;
    vmirtWriteNByteDomain(domain, 0xF0000 + rl78->SP    , &nextPC, 3, 0, MEM_AA_TRUE);
    vmirtWriteNByteDomain(domain, 0xF0000 + rl78->SP + 3, &psw   , 1, 0, MEM_AA_TRUE);

    // the IE flag is reset (0),
    rl78->PSW_IE = 0;

    // and the contents of the priority specification flag corresponding to the acknowledged
    // interrupt are transferred to the ISP1 and ISP0 flags.
    rl78->PSW_ISP = rl78->irq_prio;

    // The vector table data determined for each interrupt request
    // is the loaded into the PC and branched.

    Uns32 irq_vect = (exception == RL78_EXCPT_IRQ) ? rl78->irq_vect : exceptions[exception].code;

    //memMapped vmirtReadNByteDomain(
    //    memDomainP     domain,
    //    Addr           simAddress,
    //    void          *buffer,
    //    Addr           size,
    //    memRegionPP    cachedRegion,
    //    memAccessAttrs attrs
    //);
    vmirtReadNByteDomain(domain, irq_vect, &jumpPC, 2, 0, MEM_AA_TRUE);

    MY_MESSAGE(rl78, "T", "rl78TakeException jumpPC:%05x nextPC:%05x, psw:%02x, sp:%04x \n", jumpPC, nextPC, psw, rl78->SP);

    rl78->irq_vect = 0;                            // Interrupt already accept
    rl78->irq_prio = 0;
    rl78->exception = exception;

    // jump to the vector
    vmirtSetPCException((vmiProcessorP) rl78, jumpPC);
}

void rl78Reset(rl78P rl78) {

    Uns16 jumpPC = 0;

    memDomainP domain = vmirtGetProcessorDataDomain((vmiProcessorP) rl78);

    vmirtReadNByteDomain(domain, 0x00000, &jumpPC, 2, 0, MEM_AA_TRUE);

    rl78->reset = 0;

    vmirtSetPCException((vmiProcessorP) rl78, jumpPC);
}


char print_buf[100 + 1];

void snprint_hex(char* buf, Uns32 n, const void* value, Uns32 bytes) {
    int iii;
    int len = 0;
//    for (iii = bytes - 1; 0 <= iii; iii--) {
    for (iii = 0; iii < bytes; iii++) {
        len += snprintf(&buf[len], (n - len), "%02x ", ((Uns8*) value)[iii]);
    }
}


void dumpRAM(vmiProcessorP processor) {            // @@@

    FILE* fout = fopen("dumpram.bin", "wb");
    unsigned char* buf = malloc(512);

    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    vmirtReadNByteDomain(domain, 0xFFD00, buf, 512, 0, MEM_AA_TRUE);    // If MEM_AA_FALSE, processor arg of rl78ReadReg() become NULL.

    fwrite(buf, 1, 512, fout);
    fclose(fout);
}




//#define VMI_ENDIAN_FN(_NAME) memEndian _NAME( 
//    vmiProcessorP processor,    
//    Bool          isFetch       
//)
VMI_ENDIAN_FN(rl78GetEndian) {
    return MEM_ENDIAN_LITTLE;
}


//
// Return the next instruction address after 'thisPC'.
//
//#define VMI_NEXT_PC_FN(_NAME) Addr _NAME(
//    vmiProcessorP processor, 
//    Addr thisPC
//)
VMI_NEXT_PC_FN(rl78NextInstruction) {

    rl78P rl78 = (rl78P) processor;

    // decode the instruction
    rl78Decode(rl78, thisPC, 0, 0, 0);

//    MY_MESSAGE(rl78, "I", "rl78NextInstruction : %d\n", rl78->len_instByte);
    Uns32 nextAddress = (Uns32)(thisPC + rl78->len_instByteAndSkip);

    return nextAddress;
}




VMI_DEBUG_FN(rl78DumpRegisters) {

    rl78P rl78 = (rl78P)processor;

    vmiPrintf("---------------------------------------\n");

    // print general-purpose registers
    vmiPrintf(" X:   %02x", rl78->regs[8 * rl78->PSW_RBS + 0]); vmiPrintf("  ");
    vmiPrintf(" A:   %02x", rl78->regs[8 * rl78->PSW_RBS + 1]); vmiPrintf("  ");
    vmiPrintf(" C:   %02x", rl78->regs[8 * rl78->PSW_RBS + 2]); vmiPrintf("  ");
    vmiPrintf(" B:   %02x", rl78->regs[8 * rl78->PSW_RBS + 3]); vmiPrintf("  ");
    vmiPrintf(" E:   %02x", rl78->regs[8 * rl78->PSW_RBS + 4]); vmiPrintf("  ");
    vmiPrintf(" D:   %02x", rl78->regs[8 * rl78->PSW_RBS + 5]); vmiPrintf("  ");
    vmiPrintf(" L:   %02x", rl78->regs[8 * rl78->PSW_RBS + 6]); vmiPrintf("  ");
    vmiPrintf(" H:   %02x", rl78->regs[8 * rl78->PSW_RBS + 7]); vmiPrintf("\n");

    int iii;
    for (iii = 0; iii < 4; iii++) {
        vmiPrintf(" X_%d: %02x", iii, rl78->regs[8 * iii + 0]); vmiPrintf("  ");
        vmiPrintf(" A_%d: %02x", iii, rl78->regs[8 * iii + 1]); vmiPrintf("  ");
        vmiPrintf(" C_%d: %02x", iii, rl78->regs[8 * iii + 2]); vmiPrintf("  ");
        vmiPrintf(" B_%d: %02x", iii, rl78->regs[8 * iii + 3]); vmiPrintf("  ");
        vmiPrintf(" E_%d: %02x", iii, rl78->regs[8 * iii + 4]); vmiPrintf("  ");
        vmiPrintf(" D_%d: %02x", iii, rl78->regs[8 * iii + 5]); vmiPrintf("  ");
        vmiPrintf(" L_%d: %02x", iii, rl78->regs[8 * iii + 6]); vmiPrintf("  ");
        vmiPrintf(" H_%d: %02x", iii, rl78->regs[8 * iii + 7]); vmiPrintf("\n");
    }

    // By binop API, only BIT members will be updated.
    // So, when reading PSW value, it is necessary to call rl78GetPSW.
    Uns8  psw = rl78GetPSW_REG(rl78);
    Uns32 pc  = (Uns32) vmirtGetPC(processor);

    vmiPrintf(" IE:%u Z:%u RBS:%u%u AC:%u ISP:%u%u CY:%u  ",
        GET_BIT(psw, MASK_PSW_IE  ),
        GET_BIT(psw, MASK_PSW_Z   ),
        GET_BIT(psw, MASK_PSW_RBS1), GET_BIT(psw, MASK_PSW_RBS0),
        GET_BIT(psw, MASK_PSW_AC  ),
        GET_BIT(psw, MASK_PSW_ISP1), GET_BIT(psw, MASK_PSW_ISP0),
        GET_BIT(psw, MASK_PSW_CY  ) );

    vmiPrintf(" PSW : %02x", psw);                vmiPrintf("\n");
    vmiPrintf(" PC: %05x", pc);                    vmiPrintf("  ");
    vmiPrintf(" ES: %02x", rl78->ES_Addr.ES );    vmiPrintf("  ");
    vmiPrintf(" CS: %02x", rl78->CS_Addr.CS );    vmiPrintf("  ");
    vmiPrintf(" SP: %04x", rl78->SP );            vmiPrintf("  ");
    vmiPrintf(" PMC: %02x", rl78->PMC);            vmiPrintf("\n");

    vmiPrintf(" MACR: %08x"   , rl78->MACR     ); vmiPrintf("\n");

//    vmiPrintf(" tmp(AX): %04x", rl78->regs16[0]); vmiPrintf(" ");
//    vmiPrintf(" tmp(BC): %04x", rl78->regs16[1]); vmiPrintf(" ");
//    vmiPrintf(" tmp(DE): %04x", rl78->regs16[2]); vmiPrintf(" ");
//    vmiPrintf(" tmp(HL): %04x", rl78->regs16[3]); vmiPrintf("\n");

//    vmiPrintf(" TMP_L: %04x"  , rl78->TMP_L    ); vmiPrintf(" ");
//    vmiPrintf(" TMP_H: %04x"  , rl78->TMP_H    ); vmiPrintf(" ");
//    vmiPrintf(" THL: %04x"    , rl78->THL      ); vmiPrintf("\n");

    vmiPrintf("---------------------------------------\n");
    vmiPrintf("\n");
}




//#define VMI_MEM_WATCH_FN(_NAME) void _NAME( 
//    vmiProcessorP processor,    
//    Addr          address,      
//    Uns32         bytes,        
//    const void   *value,        
//    void         *userData,     
//    Addr          VA            
//)

VMI_MEM_WATCH_FN(rl78ReadReg) {

    rl78P rl78 = (rl78P) processor;

    Uns32 idx_adr = 0;
    Uns8* pvalue = (Uns8*) value;

    for (; idx_adr < bytes; idx_adr++) {
        Uns32 offset  = (Uns32) address + idx_adr - 0xFFEE0;
        Uns32 bank    = 3 - (offset / 8);
        Uns32 idx_reg = offset % 8;
        MY_ASSERT((offset < 32), "rl78ReadReg");

        switch (idx_reg) {
            case 0: pvalue[idx_adr] = rl78->regs[8 * bank + R_X]; break;
            case 1: pvalue[idx_adr] = rl78->regs[8 * bank + R_A]; break;
            case 2: pvalue[idx_adr] = rl78->regs[8 * bank + R_C]; break;
            case 3: pvalue[idx_adr] = rl78->regs[8 * bank + R_B]; break;
            case 4: pvalue[idx_adr] = rl78->regs[8 * bank + R_E]; break;
            case 5: pvalue[idx_adr] = rl78->regs[8 * bank + R_D]; break;
            case 6: pvalue[idx_adr] = rl78->regs[8 * bank + R_L]; break;
            case 7: pvalue[idx_adr] = rl78->regs[8 * bank + R_H]; break;
        }
    }

//    snprint_hex(print_buf, 100, value, bytes);
//    MY_MESSAGE(rl78, "I", "rl78ReadReg addr=%05x, byte=%d, value=%s\n", (Uns32) address, bytes, print_buf);
}

VMI_MEM_WATCH_FN(rl78WriteReg) {

    rl78P rl78 = (rl78P) processor;

//    snprint_hex(print_buf, 100, value, bytes);
//    MY_MESSAGE(rl78, "I", "rl78WriteReg addr=%05x, byte=%d, value=%s\n", (Uns32) address, bytes, print_buf);

    Uns32 idx_adr = 0;
    Uns8* pvalue = (Uns8*) value;

    for (; idx_adr < bytes; idx_adr++) {
        Uns32 offset  = (Uns32) address + idx_adr - 0xFFEE0;
        Uns32 bank    = 3 - (offset / 8);
        Uns32 idx_reg = offset % 8;
        MY_ASSERT((offset < 32), "rl78WriteReg");

        switch (idx_reg) {
            case 0: rl78->regs[8 * bank + R_X] = pvalue[idx_adr]; break;
            case 1: rl78->regs[8 * bank + R_A] = pvalue[idx_adr]; break;
            case 2: rl78->regs[8 * bank + R_C] = pvalue[idx_adr]; break;
            case 3: rl78->regs[8 * bank + R_B] = pvalue[idx_adr]; break;
            case 4: rl78->regs[8 * bank + R_E] = pvalue[idx_adr]; break;
            case 5: rl78->regs[8 * bank + R_D] = pvalue[idx_adr]; break;
            case 6: rl78->regs[8 * bank + R_L] = pvalue[idx_adr]; break;
            case 7: rl78->regs[8 * bank + R_H] = pvalue[idx_adr]; break;
        }
    }
}

VMI_MEM_WATCH_FN(rl78ReadSfr) {

    rl78P rl78 = (rl78P) processor;

    switch (bytes) {
        case 1: {
            Uns8* pvalue = (Uns8*) value;
            switch (address) {
                case 0xFFFF0: *pvalue = ((rl78->MACR & 0x000000FF)      ); break;
                case 0xFFFF1: *pvalue = ((rl78->MACR & 0x0000FF00) >>  8); break;
                case 0xFFFF2: *pvalue = ((rl78->MACR & 0x00FF0000) >> 16); break;
                case 0xFFFF3: *pvalue = ((rl78->MACR & 0xFF000000) >> 24); break;
                case 0xFFFF8: *pvalue = ((rl78->SP   & 0x00FF)     ); break;
                case 0xFFFF9: *pvalue = ((rl78->SP   & 0xFF00) >> 8); break;
                case 0xFFFFA: *pvalue = rl78GetPSW_REG(rl78); break;    // Update PSW vari from BIT members
                case 0xFFFFB: break;        // reserve
                case 0xFFFFC: *pvalue = rl78->CS_Addr.CS ; break;
                case 0xFFFFD: *pvalue = rl78->ES_Addr.ES ; break;
                case 0xFFFFE: *pvalue = rl78->PMC; break;
                case 0xFFFFF: break;        // MEM
            }
        }    break;

        case 2: {
            Uns16* pvalue = (Uns16*) value;
            switch (address) {
                case 0xFFFF0: *pvalue = ((rl78->MACR & 0x0000FFFF)      ); break;
                case 0xFFFF2: *pvalue = ((rl78->MACR & 0xFFFF0000) >> 16); break;
                case 0xFFFF8: *pvalue = rl78->SP; break;
                case 0xFFFFA: *pvalue = rl78GetPSW_REG(rl78); break;    // Update PSW vari from BIT members
                case 0xFFFFC: *pvalue = rl78->CS_Addr.CS ; break;        // checked by unit test MOVW_40
                case 0xFFFFE: *pvalue = rl78->PMC; break;
            }
        }    break;

        default:
            MY_ASSERT(0, "rl78ReadSfr");
    }

//    snprint_hex(print_buf, 100, value, bytes);
//    MY_MESSAGE(rl78, "I", "rl78ReadSfr addr=%05x, byte=%d, value=%s\n", (Uns32) address, bytes, print_buf);
}

VMI_MEM_WATCH_FN(rl78WriteSfr) {
    snprint_hex(print_buf, 100, value, bytes);

    rl78P rl78 = (rl78P) processor;

    MY_MESSAGE(rl78, "I", "rl78WriteSfr addr=%05x, byte=%d, value=%s\n", (Uns32) address, bytes, print_buf);

    switch (bytes) {
        case 1: {
            Uns8* pvalue = (Uns8*) value;
            switch (address) {
                case 0xFFFF0: rl78->MACR = (rl78->MACR & 0xFFFFFF00) | (((Uns32) *pvalue)      ); break;
                case 0xFFFF1: rl78->MACR = (rl78->MACR & 0xFFFF00FF) | (((Uns32) *pvalue) <<  8); break;
                case 0xFFFF2: rl78->MACR = (rl78->MACR & 0xFF00FFFF) | (((Uns32) *pvalue) << 16); break;
                case 0xFFFF3: rl78->MACR = (rl78->MACR & 0x00FFFFFF) | (((Uns32) *pvalue) << 24); break;
                case 0xFFFF8: rl78->SP   = (rl78->SP   & 0xFF00) | ( (Uns16) *pvalue & 0xFE); break;    // make even address
                case 0xFFFF9: rl78->SP   = (rl78->SP   & 0x00FF) | (((Uns16) *pvalue) << 8); break;
                case 0xFFFFA: rl78->PSW  = *pvalue; rl78SetPSW_BIT(rl78); break;                        // Update BIT members from PSW vari
                case 0xFFFFB: break;        // reserve
                case 0xFFFFC: rl78->CS_Addr.CS = *pvalue & 0x0F; break;
                case 0xFFFFD: rl78->ES_Addr.ES = *pvalue & 0x0F; break;
                case 0xFFFFE: rl78->PMC  = *pvalue; break;
                case 0xFFFFF: break;        // MEM
            }
        }    break;

        case 2: {
            Uns16* pvalue = (Uns16*) value;
            switch (address) {
                case 0xFFFF0: rl78->MACR = (rl78->MACR & 0xFFFF0000) | (((Uns32) *pvalue)      ); break;
                case 0xFFFF2: rl78->MACR = (rl78->MACR & 0x0000FFFF) | (((Uns32) *pvalue) << 16); break;
                case 0xFFFF8: rl78->SP   = *pvalue & 0xFFFE; break;                                        // make even address
                case 0xFFFFA: rl78->PSW  = *pvalue; rl78SetPSW_BIT(rl78); break;                           // Update BIT members from PSW vari
                case 0xFFFFC: rl78->CS_Addr.CS = *pvalue & 0x0F; break;                                    // checked by unit test MOVW_40
                case 0xFFFFE: rl78->PMC  = *pvalue; break;
            }
        }    break;

        default:
            MY_ASSERT(0, "rl78WriteSfr");
    }
}


