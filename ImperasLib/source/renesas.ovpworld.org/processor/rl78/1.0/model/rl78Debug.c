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

#include "vmi/vmiDbg.h"

#include "rl78Functions.h"
#include "rl78Structure.h"


static const vmiModeInfo modeInfos[RL78_MODE_LAST] = {
    [RL78_MODE_RB0] = {name:"RB0", code:RL78_MODE_RB0},
    [RL78_MODE_RB1] = {name:"RB1", code:RL78_MODE_RB1},
    [RL78_MODE_RB2] = {name:"RB2", code:RL78_MODE_RB2},
    [RL78_MODE_RB3] = {name:"RB3", code:RL78_MODE_RB3},
};

//#define VMI_GET_MODE_FN(_NAME) vmiModeInfoCP _NAME(
//    vmiProcessorP processor
//)
VMI_GET_MODE_FN(rl78GetMode) {
    rl78P rl78 = (rl78P) processor;
    return &modeInfos[rl78->PSW_RBS];
}

//#define VMI_MODE_INFO_FN(_NAME) vmiModeInfoCP _NAME( 
//    vmiProcessorP processor,    
//    vmiModeInfoCP prev          
//)
VMI_MODE_INFO_FN(rl78ModeInfo) {
    vmiModeInfoCP end = modeInfos + RL78_MODE_LAST;

    // on the first call, start with the first member of the table
    if (!prev) {
        prev = modeInfos - 1;
    }

    // get the next member
    vmiModeInfoCP this = prev+1;

    // return the next member, or NULL if at the end of the list
    return (this==end) ? 0 : this;
}


//#define VMI_GET_EXCEPTION_FN(_NAME) vmiExceptionInfoCP _NAME( 
//    vmiProcessorP processor 
//)
VMI_GET_EXCEPTION_FN(rl78GetException) {
    rl78P rl78 = (rl78P) processor;
    return &exceptions[rl78->exception];
}

//#define VMI_EXCEPTION_INFO_FN(_NAME) vmiExceptionInfoCP _NAME( 
//    vmiProcessorP      processor,   
//    vmiExceptionInfoCP prev         
//)
VMI_EXCEPTION_INFO_FN(rl78ExceptionInfo) {
    vmiExceptionInfoCP end = exceptions + RL78_EXCPT_LAST;

    // on the first call, start with the first member of the table
    if (!prev) {
        prev = exceptions - 1;
    }

    // get the next member
    vmiExceptionInfoCP this = prev + 1;

    // return the next member, or NULL if at the end of the list
    return (this==end) ? 0 : this;
}
