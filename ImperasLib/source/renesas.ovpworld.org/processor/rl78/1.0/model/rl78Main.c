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

#include <stdio.h>

// Imperas header files
#include "hostapi/impAlloc.h"

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiRt.h"            // vmirtAliasMemory

// model header files
#include "rl78Structure.h"
#include "rl78Functions.h"
#include "rl78View.h"            // rl78CreateView
#include "rl78Parameters.h"        // 'rl78ParamValuesP'
#include "rl78Utils.h"            // rl78SetPSW_BIT
#include "rl78Doc.h"            // model documentation
#include "rl78Message.h"        // MY_ASSERT

//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))




////////////////////////////////////////////////////////////////////////////////
// BUS PORTS
////////////////////////////////////////////////////////////////////////////////

// typedef struct vmiBusPortS {
//     const char      *name;
//     vmiBusPortType   type;
//     vmiDomainType    domainType;
//     struct           {Uns8 min; Uns8 max; Uns8 unset;} addrBits;
//     Bool             mustBeConnected;
//     // space for documentation
//     const char      *description;
//     void            *descriptionDom;
//     // domain is non-NULL if port is connected
//     memDomainP       domain;
// } vmiBusPort;
const static vmiBusPort busPorts[] = {
    {"INSTRUCTION", vmi_BP_MASTER, vmi_DOM_CODE,  {20, 32}, 1},
    {"DATA"       , vmi_BP_MASTER, vmi_DOM_DATA,  {20, 32}, 1},
    {"GPRSP"      , vmi_BP_SLAVE , vmi_DOM_OTHER, {20, 32}, 0}, // duplicate name error with GPR register bank - so rename
    {"SFRSP"      , vmi_BP_SLAVE , vmi_DOM_OTHER, {20, 32}, 0},
};

//
// Allocate bus port specifications
//
static void newBusPorts(rl78P rl78) {

    Uns32 i;

    rl78->busPorts = STYPE_CALLOC_N(vmiBusPort, NUM_MEMBERS(busPorts));

    for(i=0; i<NUM_MEMBERS(busPorts); i++) {
        rl78->busPorts[i] = busPorts[i];
    }
}

//
// Free bus port specifications
//
static void freeBusPorts(rl78P rl78) {

    if(rl78->busPorts) {
        STYPE_FREE(rl78->busPorts);
        rl78->busPorts = 0;
    }
}

//
// Get the next bus port
//
VMI_BUS_PORT_SPECS_FN(rl78GetBusPortSpec) {

    rl78P rl78 = (rl78P)processor;

    if(!prev) {
        // first port
        return rl78->busPorts;

    } else {
        // port other than the first
        Uns32 prevIndex = (prev-rl78->busPorts);
        Uns32 thisIndex = prevIndex+1;

        return (thisIndex<NUM_MEMBERS(busPorts)) ? &rl78->busPorts[thisIndex] : 0;
    }
}

//#define    VAL_INIT    0xdeadbeef
#define    VAL_INIT    0x00000000

//#define VMI_CONSTRUCTOR_FN(_NAME) void _NAME( 
//    vmiProcessorP  processor,           
//    Bool           simulateExceptions,  
//    vmiSMPContextP smpContext,          
//    void          *parameterValues      
//)
VMI_CONSTRUCTOR_FN(rl78Constructor) {

    rl78P            rl78   = (rl78P)processor;
    rl78ParamValuesP params = parameterValues;
    Uns32 i;

    // initialise general purpose registers
    for(i = 0; i < RL78_REGS; i++) {
        rl78->regs[i] = (Uns8) VAL_INIT;
    }

    // initialise status registers SR, ESR, EPCR and EEAR
    rl78->ES_Addr.ES = 0x0F;            // reset value : 0Fh
    rl78->CS_Addr.CS = 0x00;            // reset value : 00h
    rl78->SP   = (Uns8) VAL_INIT;        // reset value : undefined
    rl78->PMC  = 0x00;                    // reset value : 00h
    rl78->MACR = 0x00000000;            // reset value : 00000000h
    rl78->PSW  = (Uns8) 0x06;            // reset value : 06h
    rl78SetPSW_BIT(rl78);

    rl78->TMP_L  = 0;
    rl78->TMP_H  = 0;
    rl78->TBIT   = 0;
    rl78->SWAP   = 0;
    rl78->BRANCH = 0;
    rl78->TCMPS  = 0;

    rl78->irq_vect = 0;
    rl78->irq_prio = 0;

    // create bus port specifications
    newBusPorts(rl78);

    // create the processor view
    rl78CreateView(rl78);

    // Copy parameters to the model instance
    rl78->sim_ac_flag  = params->sim_ac_flag;
    rl78->exit_on_halt = params->exit_on_halt;
    rl78->verbose      = params->verbose;
    rl78->variant      = params->variant;
    MY_MESSAGE(rl78, "I", "sim_ac_flag:%d\n" , params->sim_ac_flag);
    MY_MESSAGE(rl78, "I", "exit_on_halt:%d\n", params->exit_on_halt);
    MY_MESSAGE(rl78, "I", "verbose:%d\n"     , params->verbose);
    MY_MESSAGE(rl78, "I", "variant:%d\n"     , params->variant);

    rl78->mirror_rom_addr   = params->mirror_rom_addr;
    rl78->mirror_start_addr = params->mirror_start_addr;
    rl78->mirror_end_addr   = params->mirror_end_addr  ;
    MY_MESSAGE(rl78, "I", "mirror_rom_addr:0x%05x\n"  , params->mirror_rom_addr  );
    MY_MESSAGE(rl78, "I", "mirror_start_addr:0x%05x\n", params->mirror_start_addr);
    MY_MESSAGE(rl78, "I", "mirror_end_addr:0x%05x\n"  , params->mirror_end_addr  );
}

//#define VMI_VMINIT_FN(_NAME) void _NAME(
//    vmiProcessorP  processor,           
//    memDomainPP    codeDomains,         
//    memDomainPP    dataDomains          
//)
// Each array has the same number of entries as the number of dictionary names 
// in the dictNames field provided in the processor attributes structure

VMI_VMINIT_FN(rl78VmInit) {

    rl78P rl78 = (rl78P) processor;

//    memDomainP physicalCodeDomain = codeDomains[0];
//    memDomainP physicalDataDomain = dataDomains[0];
//    memDomainP virtualDomain = vmirtNewDomain("virtual", 20);
    memDomainP physicalCodeDomain = vmirtGetProcessorPhysicalCodeDomain(processor);
    memDomainP physicalDataDomain = vmirtGetProcessorPhysicalDataDomain(processor);
    memDomainP virtualCodeDomain  = vmirtGetProcessorCodeDomain(processor);
    memDomainP virtualDataDomain  = vmirtGetProcessorDataDomain(processor);

    MY_ASSERT(
        (physicalCodeDomain == physicalDataDomain),
        "expected code & data domains to match");

    MY_ASSERT(
        (virtualCodeDomain == virtualDataDomain),
        "expected code & data domains to match");

    Uns32    mirror_size = rl78->mirror_end_addr - rl78->mirror_start_addr;
    if (mirror_size != 0) {

        vmirtAliasMemory(                         //Bool vmirtAliasMemory(
            physicalCodeDomain,                   //    memDomainP physicalDomain,
            virtualCodeDomain,                    //    memDomainP virtualDomain,
//            0x02000,                            //    Addr       physicalLowAddr,
            rl78->mirror_rom_addr,                //    Addr       physicalLowAddr,
//            0x0BFFF,                            //    Addr       physicalHighAddr,        // R5F109xD (x=6,A,B,G,L) mirror 40kb
//            0x0EEFF,                            //    Addr       physicalHighAddr,        // R5F109xE (x=6,A,B,G,L) mirror 51.75kb
            rl78->mirror_rom_addr + mirror_size,  //    Addr       physicalHighAddr,        // R5F109xE (x=6,A,B,G,L) mirror 51.75kb
//            0xF2000,                            //    Addr       virtualLowAddr,
            rl78->mirror_start_addr,              //    Addr       virtualLowAddr,
            0);                                   //    memMRUSetP mruSet);
    }

//    vmirtSetProcessorCodeDomain(processor, virtualCodeDomain);
//    vmirtSetProcessorDataDomain(processor, virtualCodeDomain);

    codeDomains[0] = virtualCodeDomain;
    dataDomains[0] = virtualCodeDomain;
    codeDomains[1] = virtualCodeDomain;
    dataDomains[1] = virtualCodeDomain;
    codeDomains[2] = virtualCodeDomain;
    dataDomains[2] = virtualCodeDomain;
    codeDomains[3] = virtualCodeDomain;
    dataDomains[3] = virtualCodeDomain;


    // callbacks for memory mapped registers.
    memDomainP internalDomain = vmirtGetProcessorInternalDataDomain(processor);

    //void vmirtAddReadCallback(
    //    memDomainP    domain,
    //    vmiProcessorP scope,
    //    Addr          lowAddr,
    //    Addr          highAddr,
    //    vmiMemWatchFn watchCB,
    //    void         *userData
    //);
    vmirtAddReadCallback (internalDomain, processor, 0xFFEE0, 0xFFEFF, rl78ReadReg, 0);
    vmirtAddReadCallback (internalDomain, processor, 0xFFFF0, 0xFFFFF, rl78ReadSfr, 0);

    //void vmirtAddWriteCallback(
    //    memDomainP    domain,
    //    vmiProcessorP scope,
    //    Addr          lowAddr,
    //    Addr          highAddr,
    //    vmiMemWatchFn watchCB,
    //    void         *userData
    //);
    vmirtAddWriteCallback(internalDomain, processor, 0xFFEE0, 0xFFEFF, rl78WriteReg, 0);
    vmirtAddWriteCallback(internalDomain, processor, 0xFFFF0, 0xFFFFF, rl78WriteSfr, 0);

    // create data domain to use for 16-bit address loads and stores (i.e.
    // loads and stores that do not use the ES register)
    rl78->dataDomain16 = vmirtNewDomain("16-bit data", 16);

    // alias addresses 0xF0000:0xFFFFF in the physical domain to addresses
    // 0x0000:0xFFFF in the 16-bit data domain
    vmirtAliasMemory(            //Bool vmirtAliasMemory(
        physicalCodeDomain,      //    memDomainP physicalDomain,
        rl78->dataDomain16,      //    memDomainP virtualDomain,
        0xf0000,                 //    Addr       physicalLowAddr,
        0xfffff,                 //    Addr       physicalHighAddr,
        0x0000,                  //    Addr       virtualLowAddr,
        0);                      //    memMRUSetP mruSet);
}

//
// RL78 processor destructor
//
VMI_DESTRUCTOR_FN(rl78Destructor) {

    rl78P rl78 = (rl78P)processor;

    // free bus port specifications
    freeBusPorts(rl78);
}

