/*
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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////


#include "pse.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

busPortMR_MR_dataT busPortMR_MR_data;

busPortMDB_MDB_dataT busPortMDB_MDB_data;

busPortMDH_MDH_dataT busPortMDH_MDH_data;

busPortMDW_MDW_dataT busPortMDW_MDW_data;

busPortECC_ECC_dataT busPortECC_ECC_data;

busPortGR_GR_dataT busPortGR_GR_data;

busPortCR_CR_dataT busPortCR_CR_data;

busPortCRW_CRW_dataT busPortCRW_CRW_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "can", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_WRITE_CB(write_8) { *(Uns8*)user = data; }

static PPM_WRITE_CB(write_16) { *(Uns16*)user = data; }

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA000) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA000.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA100) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA100.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA200) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA200.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA300) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA300.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA400) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA400.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA500) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA500.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA600) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA600.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA700) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA700.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA001) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA001.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA101) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA101.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA201) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA201.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA301) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA301.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA401) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA401.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA501) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA501.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA601) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA601.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA701) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA701.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA002) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA002.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA102) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA102.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA202) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA202.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA302) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA302.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA402) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA402.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA502) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA502.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA602) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA602.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA702) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA702.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA003) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA003.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA103) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA103.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA203) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA203.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA303) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA303.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA403) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA403.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA503) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA503.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA603) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA603.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA703) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA703.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA004) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA004.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA104) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA104.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA204) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA204.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA304) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA304.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA404) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA404.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA504) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA504.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA604) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA604.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA704) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA704.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA005) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA005.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA105) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA105.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA205) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA205.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA305) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA305.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA405) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA405.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA505) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA505.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA605) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA605.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA705) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA705.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA006) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA006.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA106) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA106.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA206) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA206.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA306) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA306.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA406) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA406.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA506) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA506.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA606) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA606.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA706) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA706.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA007) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA007.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA107) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA107.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA207) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA207.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA307) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA307.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA407) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA407.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA507) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA507.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA607) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA607.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA707) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA707.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA008) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA008.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA108) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA108.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA208) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA208.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA308) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA308.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA408) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA408.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA508) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA508.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA608) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA608.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA708) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA708.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA009) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA009.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA109) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA109.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA209) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA209.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA309) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA309.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA409) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA409.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA509) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA509.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA609) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA609.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA709) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA709.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA010) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA010.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA110) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA110.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA210) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA210.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA310) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA310.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA410) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA410.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA510) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA510.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA610) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA610.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA710) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA710.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA011) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA011.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA111) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA111.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA211) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA211.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA311) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA311.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA411) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA411.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA511) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA511.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA611) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA611.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA711) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA711.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA012) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA012.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA112) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA112.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA212) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA212.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA312) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA312.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA412) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA412.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA512) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA512.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA612) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA612.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA712) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA712.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA013) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA013.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA113) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA113.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA213) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA213.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA313) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA313.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA413) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA413.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA513) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA513.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA613) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA613.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA713) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA713.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA014) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA014.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA114) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA114.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA214) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA214.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA314) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA314.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA414) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA414.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA514) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA514.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA614) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA614.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA714) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA714.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA015) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA015.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA115) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA115.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA215) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA215.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA315) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA315.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA415) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA415.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA515) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA515.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA615) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA615.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA715) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA715.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA016) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA016.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA116) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA116.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA216) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA216.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA316) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA316.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA416) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA416.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA516) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA516.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA616) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA616.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA716) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA716.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA017) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA017.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA117) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA117.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA217) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA217.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA317) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA317.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA417) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA417.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA517) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA517.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA617) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA617.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA717) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA717.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA018) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA018.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA118) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA118.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA218) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA218.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA318) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA318.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA418) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA418.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA518) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA518.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA618) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA618.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA718) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA718.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA019) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA019.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA119) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA119.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA219) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA219.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA319) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA319.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA419) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA419.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA519) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA519.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA619) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA619.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA719) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA719.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA020) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA020.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA120) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA120.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA220) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA220.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA320) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA320.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA420) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA420.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA520) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA520.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA620) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA620.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA720) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA720.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA021) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA021.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA121) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA121.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA221) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA221.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA321) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA321.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA421) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA421.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA521) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA521.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA621) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA621.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA721) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA721.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA022) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA022.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA122) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA122.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA222) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA222.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA322) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA322.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA422) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA422.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA522) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA522.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA622) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA622.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA722) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA722.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA023) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA023.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA123) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA123.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA223) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA223.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA323) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA323.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA423) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA423.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA523) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA523.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA623) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA623.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA723) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA723.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA024) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA024.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA124) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA124.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA224) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA224.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA324) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA324.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA424) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA424.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA524) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA524.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA624) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA624.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA724) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA724.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA025) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA025.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA125) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA125.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA225) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA225.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA325) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA325.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA425) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA425.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA525) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA525.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA625) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA625.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA725) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA725.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA026) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA026.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA126) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA126.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA226) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA226.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA326) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA326.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA426) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA426.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA526) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA526.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA626) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA626.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA726) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA726.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA027) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA027.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA127) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA127.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA227) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA227.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA327) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA327.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA427) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA427.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA527) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA527.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA627) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA627.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA727) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA727.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA028) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA028.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA128) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA128.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA228) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA228.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA328) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA328.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA428) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA428.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA528) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA528.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA628) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA628.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA728) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA728.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA029) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA029.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA129) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA129.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA229) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA229.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA329) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA329.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA429) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA429.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA529) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA529.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA629) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA629.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA729) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA729.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA030) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA030.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA130) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA130.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA230) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA230.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA330) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA330.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA430) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA430.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA530) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA530.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA630) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA630.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA730) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA730.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA031) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA031.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA131) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA131.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA231) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA231.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA331) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA331.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA431) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA431.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA531) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA531.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA631) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA631.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA731) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA731.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0100) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0100.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2300) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2300.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4500) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4500.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6700) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6700.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0101) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0101.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2301) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2301.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4501) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4501.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6701) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6701.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0102) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0102.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2302) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2302.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4502) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4502.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6702) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6702.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0103) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0103.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2303) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2303.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4503) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4503.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6703) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6703.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0104) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0104.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2304) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2304.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4504) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4504.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6704) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6704.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0105) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0105.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2305) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2305.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4505) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4505.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6705) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6705.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0106) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0106.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2306) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2306.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4506) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4506.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6706) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6706.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0107) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0107.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2307) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2307.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4507) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4507.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6707) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6707.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0108) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0108.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2308) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2308.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4508) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4508.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6708) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6708.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0109) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0109.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2309) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2309.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4509) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4509.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6709) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6709.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0110) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0110.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2310) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2310.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4510) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4510.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6710) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6710.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0111) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0111.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2311) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2311.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4511) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4511.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6711) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6711.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0112) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0112.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2312) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2312.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4512) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4512.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6712) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6712.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0113) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0113.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2313) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2313.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4513) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4513.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6713) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6713.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0114) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0114.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2314) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2314.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4514) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4514.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6714) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6714.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0115) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0115.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2315) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2315.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4515) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4515.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6715) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6715.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0116) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0116.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2316) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2316.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4516) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4516.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6716) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6716.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0117) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0117.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2317) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2317.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4517) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4517.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6717) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6717.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0118) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0118.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2318) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2318.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4518) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4518.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6718) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6718.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0119) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0119.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2319) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2319.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4519) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4519.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6719) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6719.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0120) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0120.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2320) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2320.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4520) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4520.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6720) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6720.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0121) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0121.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2321) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2321.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4521) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4521.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6721) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6721.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0122) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0122.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2322) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2322.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4522) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4522.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6722) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6722.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0123) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0123.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2323) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2323.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4523) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4523.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6723) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6723.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0124) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0124.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2324) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2324.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4524) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4524.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6724) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6724.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0125) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0125.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2325) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2325.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4525) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4525.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6725) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6725.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0126) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0126.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2326) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2326.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4526) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4526.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6726) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6726.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0127) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0127.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2327) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2327.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4527) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4527.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6727) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6727.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0128) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0128.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2328) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2328.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4528) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4528.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6728) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6728.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0129) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0129.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2329) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2329.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4529) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4529.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6729) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6729.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0130) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0130.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2330) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2330.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4530) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4530.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6730) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6730.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0131) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0131.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2331) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2331.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4531) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4531.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6731) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6731.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012300) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012300.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456700) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456700.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012301) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012301.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456701) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456701.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012302) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012302.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456702) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456702.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012303) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012303.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456703) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456703.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012304) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012304.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456704) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456704.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012305) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012305.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456705) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456705.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012306) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012306.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456706) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456706.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012307) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012307.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456707) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456707.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012308) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012308.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456708) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456708.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012309) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012309.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456709) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456709.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012310) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012310.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456710) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456710.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012311) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012311.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456711) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456711.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012312) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012312.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456712) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456712.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012313) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012313.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456713) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456713.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012314) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012314.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456714) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456714.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012315) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012315.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456715) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456715.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012316) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012316.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456716) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456716.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012317) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012317.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456717) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456717.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012318) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012318.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456718) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456718.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012319) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012319.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456719) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456719.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012320) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012320.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456720) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456720.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012321) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012321.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456721) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456721.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012322) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012322.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456722) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456722.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012323) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012323.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456723) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456723.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012324) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012324.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456724) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456724.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012325) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012325.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456725) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456725.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012326) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012326.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456726) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456726.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012327) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012327.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456727) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456727.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012328) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012328.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456728) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456728.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012329) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012329.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456729) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456729.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012330) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012330.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456730) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456730.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012331) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012331.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456731) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456731.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.busPortMR = ppmCreateSlaveBusPort("busPortMR", 768);
    if (!handles.busPortMR) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortMR'");
    }

    handles.busPortMDB = ppmCreateSlaveBusPort("busPortMDB", 4096);
    if (!handles.busPortMDB) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortMDB'");
    }

    handles.busPortMDH = ppmCreateSlaveBusPort("busPortMDH", 4096);
    if (!handles.busPortMDH) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortMDH'");
    }

    handles.busPortMDW = ppmCreateSlaveBusPort("busPortMDW", 4096);
    if (!handles.busPortMDW) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortMDW'");
    }

    handles.busPortECC = ppmCreateSlaveBusPort("busPortECC", 4);
    if (!handles.busPortECC) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortECC'");
    }

    handles.busPortGR = ppmCreateSlaveBusPort("busPortGR", 512);
    if (!handles.busPortGR) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortGR'");
    }

    handles.busPortCR = ppmCreateSlaveBusPort("busPortCR", 512);
    if (!handles.busPortCR) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortCR'");
    }

    handles.busPortCRW = ppmCreateSlaveBusPort("busPortCRW", 256);
    if (!handles.busPortCRW) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortCRW'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "MR_GMCS",
            0,
            handles.busPortMR,
            0x8,
            1,
            readGMCS,
            writeGMCS,
            viewGMCS,
            &(busPortMR_MR_data.GMCS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "MR_GMABTD",
            0,
            handles.busPortMR,
            0x20,
            1,
            readGMABTD,
            writeGMABTD,
            viewGMABTD,
            &(busPortMR_MR_data.GMABTD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "MR_LEC",
            0,
            handles.busPortMR,
            0x248,
            1,
            readLEC,
            writeLEC,
            viewLEC,
            &(busPortMR_MR_data.LEC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "MR_INFO",
            0,
            handles.busPortMR,
            0x24c,
            1,
            readINFO,
            writeINFO,
            viewINFO,
            &(busPortMR_MR_data.INFO.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "MR_BRP",
            0,
            handles.busPortMR,
            0x268,
            1,
            readBRP,
            writeBRP,
            viewBRP,
            &(busPortMR_MR_data.BRP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "MR_LIPT",
            0,
            handles.busPortMR,
            0x278,
            1,
            readLIPT,
            write_8,
            viewLIPT,
            &(busPortMR_MR_data.LIPT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "MR_LOPT",
            0,
            handles.busPortMR,
            0x288,
            1,
            readLOPT,
            write_8,
            viewLOPT,
            &(busPortMR_MR_data.LOPT.value),
            True
        );
    }

    {
        ppmCreateRegister(
            "MDB_MDATA000",
            0,
            handles.busPortMDB,
            0x0,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA000,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA100",
            0,
            handles.busPortMDB,
            0x4,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA100,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA200",
            0,
            handles.busPortMDB,
            0x8,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA200,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA300",
            0,
            handles.busPortMDB,
            0xc,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA300,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA400",
            0,
            handles.busPortMDB,
            0x10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA400,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA500",
            0,
            handles.busPortMDB,
            0x14,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA500,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA600",
            0,
            handles.busPortMDB,
            0x18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA600,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA700",
            0,
            handles.busPortMDB,
            0x1c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA700,
            (void*)7,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC00",
            0,
            handles.busPortMDB,
            0x20,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF00",
            0,
            handles.busPortMDB,
            0x24,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA001",
            0,
            handles.busPortMDB,
            0x80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA001,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA101",
            0,
            handles.busPortMDB,
            0x84,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA101,
            (void*)9,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA201",
            0,
            handles.busPortMDB,
            0x88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA201,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA301",
            0,
            handles.busPortMDB,
            0x8c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA301,
            (void*)11,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA401",
            0,
            handles.busPortMDB,
            0x90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA401,
            (void*)12,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA501",
            0,
            handles.busPortMDB,
            0x94,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA501,
            (void*)13,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA601",
            0,
            handles.busPortMDB,
            0x98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA601,
            (void*)14,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA701",
            0,
            handles.busPortMDB,
            0x9c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA701,
            (void*)15,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC01",
            0,
            handles.busPortMDB,
            0xa0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF01",
            0,
            handles.busPortMDB,
            0xa4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA002",
            0,
            handles.busPortMDB,
            0x100,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA002,
            (void*)16,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA102",
            0,
            handles.busPortMDB,
            0x104,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA102,
            (void*)17,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA202",
            0,
            handles.busPortMDB,
            0x108,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA202,
            (void*)18,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA302",
            0,
            handles.busPortMDB,
            0x10c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA302,
            (void*)19,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA402",
            0,
            handles.busPortMDB,
            0x110,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA402,
            (void*)20,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA502",
            0,
            handles.busPortMDB,
            0x114,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA502,
            (void*)21,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA602",
            0,
            handles.busPortMDB,
            0x118,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA602,
            (void*)22,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA702",
            0,
            handles.busPortMDB,
            0x11c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA702,
            (void*)23,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC02",
            0,
            handles.busPortMDB,
            0x120,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF02",
            0,
            handles.busPortMDB,
            0x124,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA003",
            0,
            handles.busPortMDB,
            0x180,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA003,
            (void*)24,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA103",
            0,
            handles.busPortMDB,
            0x184,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA103,
            (void*)25,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA203",
            0,
            handles.busPortMDB,
            0x188,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA203,
            (void*)26,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA303",
            0,
            handles.busPortMDB,
            0x18c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA303,
            (void*)27,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA403",
            0,
            handles.busPortMDB,
            0x190,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA403,
            (void*)28,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA503",
            0,
            handles.busPortMDB,
            0x194,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA503,
            (void*)29,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA603",
            0,
            handles.busPortMDB,
            0x198,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA603,
            (void*)30,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA703",
            0,
            handles.busPortMDB,
            0x19c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA703,
            (void*)31,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC03",
            0,
            handles.busPortMDB,
            0x1a0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF03",
            0,
            handles.busPortMDB,
            0x1a4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA004",
            0,
            handles.busPortMDB,
            0x200,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA004,
            (void*)32,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA104",
            0,
            handles.busPortMDB,
            0x204,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA104,
            (void*)33,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA204",
            0,
            handles.busPortMDB,
            0x208,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA204,
            (void*)34,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA304",
            0,
            handles.busPortMDB,
            0x20c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA304,
            (void*)35,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA404",
            0,
            handles.busPortMDB,
            0x210,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA404,
            (void*)36,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA504",
            0,
            handles.busPortMDB,
            0x214,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA504,
            (void*)37,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA604",
            0,
            handles.busPortMDB,
            0x218,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA604,
            (void*)38,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA704",
            0,
            handles.busPortMDB,
            0x21c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA704,
            (void*)39,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC04",
            0,
            handles.busPortMDB,
            0x220,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF04",
            0,
            handles.busPortMDB,
            0x224,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA005",
            0,
            handles.busPortMDB,
            0x280,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA005,
            (void*)40,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA105",
            0,
            handles.busPortMDB,
            0x284,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA105,
            (void*)41,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA205",
            0,
            handles.busPortMDB,
            0x288,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA205,
            (void*)42,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA305",
            0,
            handles.busPortMDB,
            0x28c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA305,
            (void*)43,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA405",
            0,
            handles.busPortMDB,
            0x290,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA405,
            (void*)44,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA505",
            0,
            handles.busPortMDB,
            0x294,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA505,
            (void*)45,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA605",
            0,
            handles.busPortMDB,
            0x298,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA605,
            (void*)46,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA705",
            0,
            handles.busPortMDB,
            0x29c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA705,
            (void*)47,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC05",
            0,
            handles.busPortMDB,
            0x2a0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF05",
            0,
            handles.busPortMDB,
            0x2a4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA006",
            0,
            handles.busPortMDB,
            0x300,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA006,
            (void*)48,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA106",
            0,
            handles.busPortMDB,
            0x304,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA106,
            (void*)49,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA206",
            0,
            handles.busPortMDB,
            0x308,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA206,
            (void*)50,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA306",
            0,
            handles.busPortMDB,
            0x30c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA306,
            (void*)51,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA406",
            0,
            handles.busPortMDB,
            0x310,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA406,
            (void*)52,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA506",
            0,
            handles.busPortMDB,
            0x314,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA506,
            (void*)53,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA606",
            0,
            handles.busPortMDB,
            0x318,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA606,
            (void*)54,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA706",
            0,
            handles.busPortMDB,
            0x31c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA706,
            (void*)55,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC06",
            0,
            handles.busPortMDB,
            0x320,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF06",
            0,
            handles.busPortMDB,
            0x324,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA007",
            0,
            handles.busPortMDB,
            0x380,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA007,
            (void*)56,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA107",
            0,
            handles.busPortMDB,
            0x384,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA107,
            (void*)57,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA207",
            0,
            handles.busPortMDB,
            0x388,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA207,
            (void*)58,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA307",
            0,
            handles.busPortMDB,
            0x38c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA307,
            (void*)59,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA407",
            0,
            handles.busPortMDB,
            0x390,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA407,
            (void*)60,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA507",
            0,
            handles.busPortMDB,
            0x394,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA507,
            (void*)61,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA607",
            0,
            handles.busPortMDB,
            0x398,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA607,
            (void*)62,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA707",
            0,
            handles.busPortMDB,
            0x39c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA707,
            (void*)63,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC07",
            0,
            handles.busPortMDB,
            0x3a0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)7,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF07",
            0,
            handles.busPortMDB,
            0x3a4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)7,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA008",
            0,
            handles.busPortMDB,
            0x400,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA008,
            (void*)64,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA108",
            0,
            handles.busPortMDB,
            0x404,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA108,
            (void*)65,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA208",
            0,
            handles.busPortMDB,
            0x408,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA208,
            (void*)66,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA308",
            0,
            handles.busPortMDB,
            0x40c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA308,
            (void*)67,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA408",
            0,
            handles.busPortMDB,
            0x410,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA408,
            (void*)68,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA508",
            0,
            handles.busPortMDB,
            0x414,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA508,
            (void*)69,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA608",
            0,
            handles.busPortMDB,
            0x418,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA608,
            (void*)70,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA708",
            0,
            handles.busPortMDB,
            0x41c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA708,
            (void*)71,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC08",
            0,
            handles.busPortMDB,
            0x420,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF08",
            0,
            handles.busPortMDB,
            0x424,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA009",
            0,
            handles.busPortMDB,
            0x480,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA009,
            (void*)72,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA109",
            0,
            handles.busPortMDB,
            0x484,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA109,
            (void*)73,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA209",
            0,
            handles.busPortMDB,
            0x488,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA209,
            (void*)74,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA309",
            0,
            handles.busPortMDB,
            0x48c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA309,
            (void*)75,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA409",
            0,
            handles.busPortMDB,
            0x490,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA409,
            (void*)76,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA509",
            0,
            handles.busPortMDB,
            0x494,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA509,
            (void*)77,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA609",
            0,
            handles.busPortMDB,
            0x498,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA609,
            (void*)78,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA709",
            0,
            handles.busPortMDB,
            0x49c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA709,
            (void*)79,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC09",
            0,
            handles.busPortMDB,
            0x4a0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)9,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF09",
            0,
            handles.busPortMDB,
            0x4a4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)9,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA010",
            0,
            handles.busPortMDB,
            0x500,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA010,
            (void*)80,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA110",
            0,
            handles.busPortMDB,
            0x504,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA110,
            (void*)81,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA210",
            0,
            handles.busPortMDB,
            0x508,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA210,
            (void*)82,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA310",
            0,
            handles.busPortMDB,
            0x50c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA310,
            (void*)83,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA410",
            0,
            handles.busPortMDB,
            0x510,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA410,
            (void*)84,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA510",
            0,
            handles.busPortMDB,
            0x514,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA510,
            (void*)85,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA610",
            0,
            handles.busPortMDB,
            0x518,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA610,
            (void*)86,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA710",
            0,
            handles.busPortMDB,
            0x51c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA710,
            (void*)87,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC10",
            0,
            handles.busPortMDB,
            0x520,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF10",
            0,
            handles.busPortMDB,
            0x524,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA011",
            0,
            handles.busPortMDB,
            0x580,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA011,
            (void*)88,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA111",
            0,
            handles.busPortMDB,
            0x584,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA111,
            (void*)89,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA211",
            0,
            handles.busPortMDB,
            0x588,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA211,
            (void*)90,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA311",
            0,
            handles.busPortMDB,
            0x58c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA311,
            (void*)91,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA411",
            0,
            handles.busPortMDB,
            0x590,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA411,
            (void*)92,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA511",
            0,
            handles.busPortMDB,
            0x594,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA511,
            (void*)93,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA611",
            0,
            handles.busPortMDB,
            0x598,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA611,
            (void*)94,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA711",
            0,
            handles.busPortMDB,
            0x59c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA711,
            (void*)95,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC11",
            0,
            handles.busPortMDB,
            0x5a0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)11,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF11",
            0,
            handles.busPortMDB,
            0x5a4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)11,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA012",
            0,
            handles.busPortMDB,
            0x600,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA012,
            (void*)96,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA112",
            0,
            handles.busPortMDB,
            0x604,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA112,
            (void*)97,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA212",
            0,
            handles.busPortMDB,
            0x608,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA212,
            (void*)98,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA312",
            0,
            handles.busPortMDB,
            0x60c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA312,
            (void*)99,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA412",
            0,
            handles.busPortMDB,
            0x610,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA412,
            (void*)100,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA512",
            0,
            handles.busPortMDB,
            0x614,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA512,
            (void*)101,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA612",
            0,
            handles.busPortMDB,
            0x618,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA612,
            (void*)102,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA712",
            0,
            handles.busPortMDB,
            0x61c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA712,
            (void*)103,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC12",
            0,
            handles.busPortMDB,
            0x620,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)12,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF12",
            0,
            handles.busPortMDB,
            0x624,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)12,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA013",
            0,
            handles.busPortMDB,
            0x680,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA013,
            (void*)104,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA113",
            0,
            handles.busPortMDB,
            0x684,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA113,
            (void*)105,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA213",
            0,
            handles.busPortMDB,
            0x688,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA213,
            (void*)106,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA313",
            0,
            handles.busPortMDB,
            0x68c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA313,
            (void*)107,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA413",
            0,
            handles.busPortMDB,
            0x690,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA413,
            (void*)108,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA513",
            0,
            handles.busPortMDB,
            0x694,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA513,
            (void*)109,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA613",
            0,
            handles.busPortMDB,
            0x698,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA613,
            (void*)110,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA713",
            0,
            handles.busPortMDB,
            0x69c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA713,
            (void*)111,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC13",
            0,
            handles.busPortMDB,
            0x6a0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)13,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF13",
            0,
            handles.busPortMDB,
            0x6a4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)13,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA014",
            0,
            handles.busPortMDB,
            0x700,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA014,
            (void*)112,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA114",
            0,
            handles.busPortMDB,
            0x704,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA114,
            (void*)113,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA214",
            0,
            handles.busPortMDB,
            0x708,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA214,
            (void*)114,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA314",
            0,
            handles.busPortMDB,
            0x70c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA314,
            (void*)115,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA414",
            0,
            handles.busPortMDB,
            0x710,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA414,
            (void*)116,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA514",
            0,
            handles.busPortMDB,
            0x714,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA514,
            (void*)117,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA614",
            0,
            handles.busPortMDB,
            0x718,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA614,
            (void*)118,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA714",
            0,
            handles.busPortMDB,
            0x71c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA714,
            (void*)119,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC14",
            0,
            handles.busPortMDB,
            0x720,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)14,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF14",
            0,
            handles.busPortMDB,
            0x724,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)14,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA015",
            0,
            handles.busPortMDB,
            0x780,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA015,
            (void*)120,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA115",
            0,
            handles.busPortMDB,
            0x784,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA115,
            (void*)121,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA215",
            0,
            handles.busPortMDB,
            0x788,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA215,
            (void*)122,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA315",
            0,
            handles.busPortMDB,
            0x78c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA315,
            (void*)123,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA415",
            0,
            handles.busPortMDB,
            0x790,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA415,
            (void*)124,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA515",
            0,
            handles.busPortMDB,
            0x794,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA515,
            (void*)125,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA615",
            0,
            handles.busPortMDB,
            0x798,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA615,
            (void*)126,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA715",
            0,
            handles.busPortMDB,
            0x79c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA715,
            (void*)127,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC15",
            0,
            handles.busPortMDB,
            0x7a0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)15,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF15",
            0,
            handles.busPortMDB,
            0x7a4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)15,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA016",
            0,
            handles.busPortMDB,
            0x800,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA016,
            (void*)128,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA116",
            0,
            handles.busPortMDB,
            0x804,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA116,
            (void*)129,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA216",
            0,
            handles.busPortMDB,
            0x808,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA216,
            (void*)130,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA316",
            0,
            handles.busPortMDB,
            0x80c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA316,
            (void*)131,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA416",
            0,
            handles.busPortMDB,
            0x810,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA416,
            (void*)132,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA516",
            0,
            handles.busPortMDB,
            0x814,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA516,
            (void*)133,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA616",
            0,
            handles.busPortMDB,
            0x818,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA616,
            (void*)134,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA716",
            0,
            handles.busPortMDB,
            0x81c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA716,
            (void*)135,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC16",
            0,
            handles.busPortMDB,
            0x820,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)16,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF16",
            0,
            handles.busPortMDB,
            0x824,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)16,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA017",
            0,
            handles.busPortMDB,
            0x880,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA017,
            (void*)136,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA117",
            0,
            handles.busPortMDB,
            0x884,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA117,
            (void*)137,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA217",
            0,
            handles.busPortMDB,
            0x888,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA217,
            (void*)138,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA317",
            0,
            handles.busPortMDB,
            0x88c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA317,
            (void*)139,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA417",
            0,
            handles.busPortMDB,
            0x890,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA417,
            (void*)140,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA517",
            0,
            handles.busPortMDB,
            0x894,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA517,
            (void*)141,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA617",
            0,
            handles.busPortMDB,
            0x898,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA617,
            (void*)142,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA717",
            0,
            handles.busPortMDB,
            0x89c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA717,
            (void*)143,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC17",
            0,
            handles.busPortMDB,
            0x8a0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)17,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF17",
            0,
            handles.busPortMDB,
            0x8a4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)17,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA018",
            0,
            handles.busPortMDB,
            0x900,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA018,
            (void*)144,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA118",
            0,
            handles.busPortMDB,
            0x904,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA118,
            (void*)145,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA218",
            0,
            handles.busPortMDB,
            0x908,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA218,
            (void*)146,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA318",
            0,
            handles.busPortMDB,
            0x90c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA318,
            (void*)147,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA418",
            0,
            handles.busPortMDB,
            0x910,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA418,
            (void*)148,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA518",
            0,
            handles.busPortMDB,
            0x914,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA518,
            (void*)149,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA618",
            0,
            handles.busPortMDB,
            0x918,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA618,
            (void*)150,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA718",
            0,
            handles.busPortMDB,
            0x91c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA718,
            (void*)151,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC18",
            0,
            handles.busPortMDB,
            0x920,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)18,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF18",
            0,
            handles.busPortMDB,
            0x924,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)18,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA019",
            0,
            handles.busPortMDB,
            0x980,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA019,
            (void*)152,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA119",
            0,
            handles.busPortMDB,
            0x984,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA119,
            (void*)153,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA219",
            0,
            handles.busPortMDB,
            0x988,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA219,
            (void*)154,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA319",
            0,
            handles.busPortMDB,
            0x98c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA319,
            (void*)155,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA419",
            0,
            handles.busPortMDB,
            0x990,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA419,
            (void*)156,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA519",
            0,
            handles.busPortMDB,
            0x994,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA519,
            (void*)157,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA619",
            0,
            handles.busPortMDB,
            0x998,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA619,
            (void*)158,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA719",
            0,
            handles.busPortMDB,
            0x99c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA719,
            (void*)159,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC19",
            0,
            handles.busPortMDB,
            0x9a0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)19,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF19",
            0,
            handles.busPortMDB,
            0x9a4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)19,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA020",
            0,
            handles.busPortMDB,
            0xa00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA020,
            (void*)160,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA120",
            0,
            handles.busPortMDB,
            0xa04,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA120,
            (void*)161,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA220",
            0,
            handles.busPortMDB,
            0xa08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA220,
            (void*)162,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA320",
            0,
            handles.busPortMDB,
            0xa0c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA320,
            (void*)163,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA420",
            0,
            handles.busPortMDB,
            0xa10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA420,
            (void*)164,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA520",
            0,
            handles.busPortMDB,
            0xa14,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA520,
            (void*)165,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA620",
            0,
            handles.busPortMDB,
            0xa18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA620,
            (void*)166,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA720",
            0,
            handles.busPortMDB,
            0xa1c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA720,
            (void*)167,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC20",
            0,
            handles.busPortMDB,
            0xa20,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)20,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF20",
            0,
            handles.busPortMDB,
            0xa24,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)20,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA021",
            0,
            handles.busPortMDB,
            0xa80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA021,
            (void*)168,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA121",
            0,
            handles.busPortMDB,
            0xa84,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA121,
            (void*)169,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA221",
            0,
            handles.busPortMDB,
            0xa88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA221,
            (void*)170,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA321",
            0,
            handles.busPortMDB,
            0xa8c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA321,
            (void*)171,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA421",
            0,
            handles.busPortMDB,
            0xa90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA421,
            (void*)172,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA521",
            0,
            handles.busPortMDB,
            0xa94,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA521,
            (void*)173,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA621",
            0,
            handles.busPortMDB,
            0xa98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA621,
            (void*)174,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA721",
            0,
            handles.busPortMDB,
            0xa9c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA721,
            (void*)175,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC21",
            0,
            handles.busPortMDB,
            0xaa0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)21,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF21",
            0,
            handles.busPortMDB,
            0xaa4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)21,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA022",
            0,
            handles.busPortMDB,
            0xb00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA022,
            (void*)176,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA122",
            0,
            handles.busPortMDB,
            0xb04,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA122,
            (void*)177,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA222",
            0,
            handles.busPortMDB,
            0xb08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA222,
            (void*)178,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA322",
            0,
            handles.busPortMDB,
            0xb0c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA322,
            (void*)179,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA422",
            0,
            handles.busPortMDB,
            0xb10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA422,
            (void*)180,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA522",
            0,
            handles.busPortMDB,
            0xb14,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA522,
            (void*)181,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA622",
            0,
            handles.busPortMDB,
            0xb18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA622,
            (void*)182,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA722",
            0,
            handles.busPortMDB,
            0xb1c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA722,
            (void*)183,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC22",
            0,
            handles.busPortMDB,
            0xb20,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)22,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF22",
            0,
            handles.busPortMDB,
            0xb24,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)22,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA023",
            0,
            handles.busPortMDB,
            0xb80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA023,
            (void*)184,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA123",
            0,
            handles.busPortMDB,
            0xb84,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA123,
            (void*)185,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA223",
            0,
            handles.busPortMDB,
            0xb88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA223,
            (void*)186,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA323",
            0,
            handles.busPortMDB,
            0xb8c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA323,
            (void*)187,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA423",
            0,
            handles.busPortMDB,
            0xb90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA423,
            (void*)188,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA523",
            0,
            handles.busPortMDB,
            0xb94,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA523,
            (void*)189,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA623",
            0,
            handles.busPortMDB,
            0xb98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA623,
            (void*)190,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA723",
            0,
            handles.busPortMDB,
            0xb9c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA723,
            (void*)191,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC23",
            0,
            handles.busPortMDB,
            0xba0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)23,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF23",
            0,
            handles.busPortMDB,
            0xba4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)23,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA024",
            0,
            handles.busPortMDB,
            0xc00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA024,
            (void*)192,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA124",
            0,
            handles.busPortMDB,
            0xc04,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA124,
            (void*)193,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA224",
            0,
            handles.busPortMDB,
            0xc08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA224,
            (void*)194,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA324",
            0,
            handles.busPortMDB,
            0xc0c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA324,
            (void*)195,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA424",
            0,
            handles.busPortMDB,
            0xc10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA424,
            (void*)196,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA524",
            0,
            handles.busPortMDB,
            0xc14,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA524,
            (void*)197,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA624",
            0,
            handles.busPortMDB,
            0xc18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA624,
            (void*)198,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA724",
            0,
            handles.busPortMDB,
            0xc1c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA724,
            (void*)199,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC24",
            0,
            handles.busPortMDB,
            0xc20,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)24,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF24",
            0,
            handles.busPortMDB,
            0xc24,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)24,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA025",
            0,
            handles.busPortMDB,
            0xc80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA025,
            (void*)200,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA125",
            0,
            handles.busPortMDB,
            0xc84,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA125,
            (void*)201,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA225",
            0,
            handles.busPortMDB,
            0xc88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA225,
            (void*)202,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA325",
            0,
            handles.busPortMDB,
            0xc8c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA325,
            (void*)203,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA425",
            0,
            handles.busPortMDB,
            0xc90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA425,
            (void*)204,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA525",
            0,
            handles.busPortMDB,
            0xc94,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA525,
            (void*)205,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA625",
            0,
            handles.busPortMDB,
            0xc98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA625,
            (void*)206,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA725",
            0,
            handles.busPortMDB,
            0xc9c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA725,
            (void*)207,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC25",
            0,
            handles.busPortMDB,
            0xca0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)25,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF25",
            0,
            handles.busPortMDB,
            0xca4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)25,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA026",
            0,
            handles.busPortMDB,
            0xd00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA026,
            (void*)208,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA126",
            0,
            handles.busPortMDB,
            0xd04,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA126,
            (void*)209,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA226",
            0,
            handles.busPortMDB,
            0xd08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA226,
            (void*)210,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA326",
            0,
            handles.busPortMDB,
            0xd0c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA326,
            (void*)211,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA426",
            0,
            handles.busPortMDB,
            0xd10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA426,
            (void*)212,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA526",
            0,
            handles.busPortMDB,
            0xd14,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA526,
            (void*)213,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA626",
            0,
            handles.busPortMDB,
            0xd18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA626,
            (void*)214,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA726",
            0,
            handles.busPortMDB,
            0xd1c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA726,
            (void*)215,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC26",
            0,
            handles.busPortMDB,
            0xd20,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)26,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF26",
            0,
            handles.busPortMDB,
            0xd24,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)26,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA027",
            0,
            handles.busPortMDB,
            0xd80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA027,
            (void*)216,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA127",
            0,
            handles.busPortMDB,
            0xd84,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA127,
            (void*)217,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA227",
            0,
            handles.busPortMDB,
            0xd88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA227,
            (void*)218,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA327",
            0,
            handles.busPortMDB,
            0xd8c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA327,
            (void*)219,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA427",
            0,
            handles.busPortMDB,
            0xd90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA427,
            (void*)220,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA527",
            0,
            handles.busPortMDB,
            0xd94,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA527,
            (void*)221,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA627",
            0,
            handles.busPortMDB,
            0xd98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA627,
            (void*)222,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA727",
            0,
            handles.busPortMDB,
            0xd9c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA727,
            (void*)223,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC27",
            0,
            handles.busPortMDB,
            0xda0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)27,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF27",
            0,
            handles.busPortMDB,
            0xda4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)27,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA028",
            0,
            handles.busPortMDB,
            0xe00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA028,
            (void*)224,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA128",
            0,
            handles.busPortMDB,
            0xe04,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA128,
            (void*)225,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA228",
            0,
            handles.busPortMDB,
            0xe08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA228,
            (void*)226,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA328",
            0,
            handles.busPortMDB,
            0xe0c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA328,
            (void*)227,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA428",
            0,
            handles.busPortMDB,
            0xe10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA428,
            (void*)228,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA528",
            0,
            handles.busPortMDB,
            0xe14,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA528,
            (void*)229,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA628",
            0,
            handles.busPortMDB,
            0xe18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA628,
            (void*)230,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA728",
            0,
            handles.busPortMDB,
            0xe1c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA728,
            (void*)231,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC28",
            0,
            handles.busPortMDB,
            0xe20,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)28,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF28",
            0,
            handles.busPortMDB,
            0xe24,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)28,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA029",
            0,
            handles.busPortMDB,
            0xe80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA029,
            (void*)232,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA129",
            0,
            handles.busPortMDB,
            0xe84,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA129,
            (void*)233,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA229",
            0,
            handles.busPortMDB,
            0xe88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA229,
            (void*)234,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA329",
            0,
            handles.busPortMDB,
            0xe8c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA329,
            (void*)235,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA429",
            0,
            handles.busPortMDB,
            0xe90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA429,
            (void*)236,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA529",
            0,
            handles.busPortMDB,
            0xe94,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA529,
            (void*)237,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA629",
            0,
            handles.busPortMDB,
            0xe98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA629,
            (void*)238,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA729",
            0,
            handles.busPortMDB,
            0xe9c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA729,
            (void*)239,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC29",
            0,
            handles.busPortMDB,
            0xea0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)29,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF29",
            0,
            handles.busPortMDB,
            0xea4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)29,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA030",
            0,
            handles.busPortMDB,
            0xf00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA030,
            (void*)240,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA130",
            0,
            handles.busPortMDB,
            0xf04,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA130,
            (void*)241,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA230",
            0,
            handles.busPortMDB,
            0xf08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA230,
            (void*)242,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA330",
            0,
            handles.busPortMDB,
            0xf0c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA330,
            (void*)243,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA430",
            0,
            handles.busPortMDB,
            0xf10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA430,
            (void*)244,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA530",
            0,
            handles.busPortMDB,
            0xf14,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA530,
            (void*)245,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA630",
            0,
            handles.busPortMDB,
            0xf18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA630,
            (void*)246,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA730",
            0,
            handles.busPortMDB,
            0xf1c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA730,
            (void*)247,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC30",
            0,
            handles.busPortMDB,
            0xf20,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)30,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF30",
            0,
            handles.busPortMDB,
            0xf24,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)30,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA031",
            0,
            handles.busPortMDB,
            0xf80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA031,
            (void*)248,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA131",
            0,
            handles.busPortMDB,
            0xf84,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA131,
            (void*)249,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA231",
            0,
            handles.busPortMDB,
            0xf88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA231,
            (void*)250,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA331",
            0,
            handles.busPortMDB,
            0xf8c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA331,
            (void*)251,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA431",
            0,
            handles.busPortMDB,
            0xf90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA431,
            (void*)252,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA531",
            0,
            handles.busPortMDB,
            0xf94,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA531,
            (void*)253,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA631",
            0,
            handles.busPortMDB,
            0xf98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA631,
            (void*)254,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDATA731",
            0,
            handles.busPortMDB,
            0xf9c,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDB_MDB_MDATA731,
            (void*)255,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MDLC31",
            0,
            handles.busPortMDB,
            0xfa0,
            4,
            readMDLC,
            writeMDLC,
            viewMDLC,
            (void*)31,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDB_MCONF31",
            0,
            handles.busPortMDB,
            0xfa4,
            4,
            readMCONF,
            writeMCONF,
            viewMCONF,
            (void*)31,
            True
        );
    }

    {
        ppmCreateRegister(
            "MDH_MDATA0100",
            0,
            handles.busPortMDH,
            0x0,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0100,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2300",
            0,
            handles.busPortMDH,
            0x8,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2300,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4500",
            0,
            handles.busPortMDH,
            0x10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4500,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6700",
            0,
            handles.busPortMDH,
            0x18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6700,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL00",
            0,
            handles.busPortMDH,
            0x28,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH00",
            0,
            handles.busPortMDH,
            0x30,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL00",
            0,
            handles.busPortMDH,
            0x38,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0101",
            0,
            handles.busPortMDH,
            0x80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0101,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2301",
            0,
            handles.busPortMDH,
            0x88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2301,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4501",
            0,
            handles.busPortMDH,
            0x90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4501,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6701",
            0,
            handles.busPortMDH,
            0x98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6701,
            (void*)7,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL01",
            0,
            handles.busPortMDH,
            0xa8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH01",
            0,
            handles.busPortMDH,
            0xb0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL01",
            0,
            handles.busPortMDH,
            0xb8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0102",
            0,
            handles.busPortMDH,
            0x100,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0102,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2302",
            0,
            handles.busPortMDH,
            0x108,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2302,
            (void*)9,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4502",
            0,
            handles.busPortMDH,
            0x110,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4502,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6702",
            0,
            handles.busPortMDH,
            0x118,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6702,
            (void*)11,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL02",
            0,
            handles.busPortMDH,
            0x128,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH02",
            0,
            handles.busPortMDH,
            0x130,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL02",
            0,
            handles.busPortMDH,
            0x138,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0103",
            0,
            handles.busPortMDH,
            0x180,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0103,
            (void*)12,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2303",
            0,
            handles.busPortMDH,
            0x188,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2303,
            (void*)13,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4503",
            0,
            handles.busPortMDH,
            0x190,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4503,
            (void*)14,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6703",
            0,
            handles.busPortMDH,
            0x198,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6703,
            (void*)15,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL03",
            0,
            handles.busPortMDH,
            0x1a8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH03",
            0,
            handles.busPortMDH,
            0x1b0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL03",
            0,
            handles.busPortMDH,
            0x1b8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0104",
            0,
            handles.busPortMDH,
            0x200,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0104,
            (void*)16,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2304",
            0,
            handles.busPortMDH,
            0x208,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2304,
            (void*)17,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4504",
            0,
            handles.busPortMDH,
            0x210,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4504,
            (void*)18,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6704",
            0,
            handles.busPortMDH,
            0x218,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6704,
            (void*)19,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL04",
            0,
            handles.busPortMDH,
            0x228,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH04",
            0,
            handles.busPortMDH,
            0x230,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL04",
            0,
            handles.busPortMDH,
            0x238,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0105",
            0,
            handles.busPortMDH,
            0x280,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0105,
            (void*)20,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2305",
            0,
            handles.busPortMDH,
            0x288,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2305,
            (void*)21,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4505",
            0,
            handles.busPortMDH,
            0x290,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4505,
            (void*)22,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6705",
            0,
            handles.busPortMDH,
            0x298,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6705,
            (void*)23,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL05",
            0,
            handles.busPortMDH,
            0x2a8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH05",
            0,
            handles.busPortMDH,
            0x2b0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL05",
            0,
            handles.busPortMDH,
            0x2b8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0106",
            0,
            handles.busPortMDH,
            0x300,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0106,
            (void*)24,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2306",
            0,
            handles.busPortMDH,
            0x308,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2306,
            (void*)25,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4506",
            0,
            handles.busPortMDH,
            0x310,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4506,
            (void*)26,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6706",
            0,
            handles.busPortMDH,
            0x318,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6706,
            (void*)27,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL06",
            0,
            handles.busPortMDH,
            0x328,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH06",
            0,
            handles.busPortMDH,
            0x330,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL06",
            0,
            handles.busPortMDH,
            0x338,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0107",
            0,
            handles.busPortMDH,
            0x380,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0107,
            (void*)28,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2307",
            0,
            handles.busPortMDH,
            0x388,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2307,
            (void*)29,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4507",
            0,
            handles.busPortMDH,
            0x390,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4507,
            (void*)30,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6707",
            0,
            handles.busPortMDH,
            0x398,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6707,
            (void*)31,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL07",
            0,
            handles.busPortMDH,
            0x3a8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)7,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH07",
            0,
            handles.busPortMDH,
            0x3b0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)7,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL07",
            0,
            handles.busPortMDH,
            0x3b8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)7,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0108",
            0,
            handles.busPortMDH,
            0x400,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0108,
            (void*)32,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2308",
            0,
            handles.busPortMDH,
            0x408,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2308,
            (void*)33,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4508",
            0,
            handles.busPortMDH,
            0x410,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4508,
            (void*)34,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6708",
            0,
            handles.busPortMDH,
            0x418,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6708,
            (void*)35,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL08",
            0,
            handles.busPortMDH,
            0x428,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH08",
            0,
            handles.busPortMDH,
            0x430,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL08",
            0,
            handles.busPortMDH,
            0x438,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0109",
            0,
            handles.busPortMDH,
            0x480,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0109,
            (void*)36,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2309",
            0,
            handles.busPortMDH,
            0x488,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2309,
            (void*)37,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4509",
            0,
            handles.busPortMDH,
            0x490,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4509,
            (void*)38,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6709",
            0,
            handles.busPortMDH,
            0x498,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6709,
            (void*)39,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL09",
            0,
            handles.busPortMDH,
            0x4a8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)9,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH09",
            0,
            handles.busPortMDH,
            0x4b0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)9,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL09",
            0,
            handles.busPortMDH,
            0x4b8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)9,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0110",
            0,
            handles.busPortMDH,
            0x500,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0110,
            (void*)40,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2310",
            0,
            handles.busPortMDH,
            0x508,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2310,
            (void*)41,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4510",
            0,
            handles.busPortMDH,
            0x510,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4510,
            (void*)42,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6710",
            0,
            handles.busPortMDH,
            0x518,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6710,
            (void*)43,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL10",
            0,
            handles.busPortMDH,
            0x528,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH10",
            0,
            handles.busPortMDH,
            0x530,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL10",
            0,
            handles.busPortMDH,
            0x538,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0111",
            0,
            handles.busPortMDH,
            0x580,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0111,
            (void*)44,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2311",
            0,
            handles.busPortMDH,
            0x588,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2311,
            (void*)45,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4511",
            0,
            handles.busPortMDH,
            0x590,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4511,
            (void*)46,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6711",
            0,
            handles.busPortMDH,
            0x598,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6711,
            (void*)47,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL11",
            0,
            handles.busPortMDH,
            0x5a8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)11,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH11",
            0,
            handles.busPortMDH,
            0x5b0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)11,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL11",
            0,
            handles.busPortMDH,
            0x5b8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)11,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0112",
            0,
            handles.busPortMDH,
            0x600,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0112,
            (void*)48,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2312",
            0,
            handles.busPortMDH,
            0x608,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2312,
            (void*)49,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4512",
            0,
            handles.busPortMDH,
            0x610,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4512,
            (void*)50,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6712",
            0,
            handles.busPortMDH,
            0x618,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6712,
            (void*)51,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL12",
            0,
            handles.busPortMDH,
            0x628,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)12,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH12",
            0,
            handles.busPortMDH,
            0x630,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)12,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL12",
            0,
            handles.busPortMDH,
            0x638,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)12,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0113",
            0,
            handles.busPortMDH,
            0x680,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0113,
            (void*)52,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2313",
            0,
            handles.busPortMDH,
            0x688,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2313,
            (void*)53,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4513",
            0,
            handles.busPortMDH,
            0x690,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4513,
            (void*)54,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6713",
            0,
            handles.busPortMDH,
            0x698,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6713,
            (void*)55,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL13",
            0,
            handles.busPortMDH,
            0x6a8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)13,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH13",
            0,
            handles.busPortMDH,
            0x6b0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)13,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL13",
            0,
            handles.busPortMDH,
            0x6b8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)13,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0114",
            0,
            handles.busPortMDH,
            0x700,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0114,
            (void*)56,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2314",
            0,
            handles.busPortMDH,
            0x708,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2314,
            (void*)57,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4514",
            0,
            handles.busPortMDH,
            0x710,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4514,
            (void*)58,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6714",
            0,
            handles.busPortMDH,
            0x718,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6714,
            (void*)59,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL14",
            0,
            handles.busPortMDH,
            0x728,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)14,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH14",
            0,
            handles.busPortMDH,
            0x730,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)14,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL14",
            0,
            handles.busPortMDH,
            0x738,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)14,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0115",
            0,
            handles.busPortMDH,
            0x780,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0115,
            (void*)60,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2315",
            0,
            handles.busPortMDH,
            0x788,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2315,
            (void*)61,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4515",
            0,
            handles.busPortMDH,
            0x790,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4515,
            (void*)62,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6715",
            0,
            handles.busPortMDH,
            0x798,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6715,
            (void*)63,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL15",
            0,
            handles.busPortMDH,
            0x7a8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)15,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH15",
            0,
            handles.busPortMDH,
            0x7b0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)15,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL15",
            0,
            handles.busPortMDH,
            0x7b8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)15,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0116",
            0,
            handles.busPortMDH,
            0x800,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0116,
            (void*)64,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2316",
            0,
            handles.busPortMDH,
            0x808,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2316,
            (void*)65,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4516",
            0,
            handles.busPortMDH,
            0x810,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4516,
            (void*)66,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6716",
            0,
            handles.busPortMDH,
            0x818,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6716,
            (void*)67,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL16",
            0,
            handles.busPortMDH,
            0x828,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)16,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH16",
            0,
            handles.busPortMDH,
            0x830,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)16,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL16",
            0,
            handles.busPortMDH,
            0x838,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)16,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0117",
            0,
            handles.busPortMDH,
            0x880,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0117,
            (void*)68,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2317",
            0,
            handles.busPortMDH,
            0x888,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2317,
            (void*)69,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4517",
            0,
            handles.busPortMDH,
            0x890,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4517,
            (void*)70,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6717",
            0,
            handles.busPortMDH,
            0x898,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6717,
            (void*)71,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL17",
            0,
            handles.busPortMDH,
            0x8a8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)17,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH17",
            0,
            handles.busPortMDH,
            0x8b0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)17,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL17",
            0,
            handles.busPortMDH,
            0x8b8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)17,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0118",
            0,
            handles.busPortMDH,
            0x900,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0118,
            (void*)72,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2318",
            0,
            handles.busPortMDH,
            0x908,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2318,
            (void*)73,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4518",
            0,
            handles.busPortMDH,
            0x910,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4518,
            (void*)74,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6718",
            0,
            handles.busPortMDH,
            0x918,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6718,
            (void*)75,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL18",
            0,
            handles.busPortMDH,
            0x928,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)18,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH18",
            0,
            handles.busPortMDH,
            0x930,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)18,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL18",
            0,
            handles.busPortMDH,
            0x938,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)18,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0119",
            0,
            handles.busPortMDH,
            0x980,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0119,
            (void*)76,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2319",
            0,
            handles.busPortMDH,
            0x988,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2319,
            (void*)77,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4519",
            0,
            handles.busPortMDH,
            0x990,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4519,
            (void*)78,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6719",
            0,
            handles.busPortMDH,
            0x998,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6719,
            (void*)79,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL19",
            0,
            handles.busPortMDH,
            0x9a8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)19,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH19",
            0,
            handles.busPortMDH,
            0x9b0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)19,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL19",
            0,
            handles.busPortMDH,
            0x9b8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)19,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0120",
            0,
            handles.busPortMDH,
            0xa00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0120,
            (void*)80,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2320",
            0,
            handles.busPortMDH,
            0xa08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2320,
            (void*)81,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4520",
            0,
            handles.busPortMDH,
            0xa10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4520,
            (void*)82,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6720",
            0,
            handles.busPortMDH,
            0xa18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6720,
            (void*)83,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL20",
            0,
            handles.busPortMDH,
            0xa28,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)20,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH20",
            0,
            handles.busPortMDH,
            0xa30,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)20,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL20",
            0,
            handles.busPortMDH,
            0xa38,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)20,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0121",
            0,
            handles.busPortMDH,
            0xa80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0121,
            (void*)84,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2321",
            0,
            handles.busPortMDH,
            0xa88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2321,
            (void*)85,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4521",
            0,
            handles.busPortMDH,
            0xa90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4521,
            (void*)86,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6721",
            0,
            handles.busPortMDH,
            0xa98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6721,
            (void*)87,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL21",
            0,
            handles.busPortMDH,
            0xaa8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)21,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH21",
            0,
            handles.busPortMDH,
            0xab0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)21,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL21",
            0,
            handles.busPortMDH,
            0xab8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)21,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0122",
            0,
            handles.busPortMDH,
            0xb00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0122,
            (void*)88,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2322",
            0,
            handles.busPortMDH,
            0xb08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2322,
            (void*)89,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4522",
            0,
            handles.busPortMDH,
            0xb10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4522,
            (void*)90,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6722",
            0,
            handles.busPortMDH,
            0xb18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6722,
            (void*)91,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL22",
            0,
            handles.busPortMDH,
            0xb28,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)22,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH22",
            0,
            handles.busPortMDH,
            0xb30,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)22,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL22",
            0,
            handles.busPortMDH,
            0xb38,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)22,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0123",
            0,
            handles.busPortMDH,
            0xb80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0123,
            (void*)92,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2323",
            0,
            handles.busPortMDH,
            0xb88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2323,
            (void*)93,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4523",
            0,
            handles.busPortMDH,
            0xb90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4523,
            (void*)94,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6723",
            0,
            handles.busPortMDH,
            0xb98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6723,
            (void*)95,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL23",
            0,
            handles.busPortMDH,
            0xba8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)23,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH23",
            0,
            handles.busPortMDH,
            0xbb0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)23,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL23",
            0,
            handles.busPortMDH,
            0xbb8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)23,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0124",
            0,
            handles.busPortMDH,
            0xc00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0124,
            (void*)96,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2324",
            0,
            handles.busPortMDH,
            0xc08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2324,
            (void*)97,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4524",
            0,
            handles.busPortMDH,
            0xc10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4524,
            (void*)98,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6724",
            0,
            handles.busPortMDH,
            0xc18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6724,
            (void*)99,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL24",
            0,
            handles.busPortMDH,
            0xc28,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)24,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH24",
            0,
            handles.busPortMDH,
            0xc30,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)24,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL24",
            0,
            handles.busPortMDH,
            0xc38,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)24,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0125",
            0,
            handles.busPortMDH,
            0xc80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0125,
            (void*)100,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2325",
            0,
            handles.busPortMDH,
            0xc88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2325,
            (void*)101,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4525",
            0,
            handles.busPortMDH,
            0xc90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4525,
            (void*)102,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6725",
            0,
            handles.busPortMDH,
            0xc98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6725,
            (void*)103,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL25",
            0,
            handles.busPortMDH,
            0xca8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)25,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH25",
            0,
            handles.busPortMDH,
            0xcb0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)25,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL25",
            0,
            handles.busPortMDH,
            0xcb8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)25,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0126",
            0,
            handles.busPortMDH,
            0xd00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0126,
            (void*)104,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2326",
            0,
            handles.busPortMDH,
            0xd08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2326,
            (void*)105,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4526",
            0,
            handles.busPortMDH,
            0xd10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4526,
            (void*)106,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6726",
            0,
            handles.busPortMDH,
            0xd18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6726,
            (void*)107,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL26",
            0,
            handles.busPortMDH,
            0xd28,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)26,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH26",
            0,
            handles.busPortMDH,
            0xd30,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)26,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL26",
            0,
            handles.busPortMDH,
            0xd38,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)26,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0127",
            0,
            handles.busPortMDH,
            0xd80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0127,
            (void*)108,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2327",
            0,
            handles.busPortMDH,
            0xd88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2327,
            (void*)109,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4527",
            0,
            handles.busPortMDH,
            0xd90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4527,
            (void*)110,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6727",
            0,
            handles.busPortMDH,
            0xd98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6727,
            (void*)111,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL27",
            0,
            handles.busPortMDH,
            0xda8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)27,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH27",
            0,
            handles.busPortMDH,
            0xdb0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)27,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL27",
            0,
            handles.busPortMDH,
            0xdb8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)27,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0128",
            0,
            handles.busPortMDH,
            0xe00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0128,
            (void*)112,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2328",
            0,
            handles.busPortMDH,
            0xe08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2328,
            (void*)113,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4528",
            0,
            handles.busPortMDH,
            0xe10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4528,
            (void*)114,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6728",
            0,
            handles.busPortMDH,
            0xe18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6728,
            (void*)115,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL28",
            0,
            handles.busPortMDH,
            0xe28,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)28,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH28",
            0,
            handles.busPortMDH,
            0xe30,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)28,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL28",
            0,
            handles.busPortMDH,
            0xe38,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)28,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0129",
            0,
            handles.busPortMDH,
            0xe80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0129,
            (void*)116,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2329",
            0,
            handles.busPortMDH,
            0xe88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2329,
            (void*)117,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4529",
            0,
            handles.busPortMDH,
            0xe90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4529,
            (void*)118,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6729",
            0,
            handles.busPortMDH,
            0xe98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6729,
            (void*)119,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL29",
            0,
            handles.busPortMDH,
            0xea8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)29,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH29",
            0,
            handles.busPortMDH,
            0xeb0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)29,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL29",
            0,
            handles.busPortMDH,
            0xeb8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)29,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0130",
            0,
            handles.busPortMDH,
            0xf00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0130,
            (void*)120,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2330",
            0,
            handles.busPortMDH,
            0xf08,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2330,
            (void*)121,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4530",
            0,
            handles.busPortMDH,
            0xf10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4530,
            (void*)122,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6730",
            0,
            handles.busPortMDH,
            0xf18,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6730,
            (void*)123,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL30",
            0,
            handles.busPortMDH,
            0xf28,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)30,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH30",
            0,
            handles.busPortMDH,
            0xf30,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)30,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL30",
            0,
            handles.busPortMDH,
            0xf38,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)30,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA0131",
            0,
            handles.busPortMDH,
            0xf80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA0131,
            (void*)124,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA2331",
            0,
            handles.busPortMDH,
            0xf88,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA2331,
            (void*)125,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA4531",
            0,
            handles.busPortMDH,
            0xf90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA4531,
            (void*)126,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MDATA6731",
            0,
            handles.busPortMDH,
            0xf98,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDH_MDH_MDATA6731,
            (void*)127,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDL31",
            0,
            handles.busPortMDH,
            0xfa8,
            2,
            readMIDL,
            writeMIDL,
            viewMIDL,
            (void*)31,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MIDH31",
            0,
            handles.busPortMDH,
            0xfb0,
            2,
            readMIDH,
            writeMIDH,
            viewMIDH,
            (void*)31,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDH_MCTRL31",
            0,
            handles.busPortMDH,
            0xfb8,
            2,
            readMCTRL,
            writeMCTRL,
            viewMCTRL,
            (void*)31,
            True
        );
    }

    {
        ppmCreateRegister(
            "MDW_MDATA012300",
            0,
            handles.busPortMDW,
            0x0,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012300,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456700",
            0,
            handles.busPortMDW,
            0x10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456700,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID00",
            0,
            handles.busPortMDW,
            0x20,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012301",
            0,
            handles.busPortMDW,
            0x80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012301,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456701",
            0,
            handles.busPortMDW,
            0x90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456701,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID01",
            0,
            handles.busPortMDW,
            0xa0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012302",
            0,
            handles.busPortMDW,
            0x100,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012302,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456702",
            0,
            handles.busPortMDW,
            0x110,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456702,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID02",
            0,
            handles.busPortMDW,
            0x120,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012303",
            0,
            handles.busPortMDW,
            0x180,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012303,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456703",
            0,
            handles.busPortMDW,
            0x190,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456703,
            (void*)7,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID03",
            0,
            handles.busPortMDW,
            0x1a0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012304",
            0,
            handles.busPortMDW,
            0x200,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012304,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456704",
            0,
            handles.busPortMDW,
            0x210,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456704,
            (void*)9,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID04",
            0,
            handles.busPortMDW,
            0x220,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012305",
            0,
            handles.busPortMDW,
            0x280,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012305,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456705",
            0,
            handles.busPortMDW,
            0x290,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456705,
            (void*)11,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID05",
            0,
            handles.busPortMDW,
            0x2a0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012306",
            0,
            handles.busPortMDW,
            0x300,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012306,
            (void*)12,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456706",
            0,
            handles.busPortMDW,
            0x310,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456706,
            (void*)13,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID06",
            0,
            handles.busPortMDW,
            0x320,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012307",
            0,
            handles.busPortMDW,
            0x380,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012307,
            (void*)14,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456707",
            0,
            handles.busPortMDW,
            0x390,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456707,
            (void*)15,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID07",
            0,
            handles.busPortMDW,
            0x3a0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)7,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012308",
            0,
            handles.busPortMDW,
            0x400,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012308,
            (void*)16,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456708",
            0,
            handles.busPortMDW,
            0x410,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456708,
            (void*)17,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID08",
            0,
            handles.busPortMDW,
            0x420,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012309",
            0,
            handles.busPortMDW,
            0x480,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012309,
            (void*)18,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456709",
            0,
            handles.busPortMDW,
            0x490,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456709,
            (void*)19,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID09",
            0,
            handles.busPortMDW,
            0x4a0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)9,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012310",
            0,
            handles.busPortMDW,
            0x500,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012310,
            (void*)20,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456710",
            0,
            handles.busPortMDW,
            0x510,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456710,
            (void*)21,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID10",
            0,
            handles.busPortMDW,
            0x520,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012311",
            0,
            handles.busPortMDW,
            0x580,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012311,
            (void*)22,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456711",
            0,
            handles.busPortMDW,
            0x590,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456711,
            (void*)23,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID11",
            0,
            handles.busPortMDW,
            0x5a0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)11,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012312",
            0,
            handles.busPortMDW,
            0x600,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012312,
            (void*)24,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456712",
            0,
            handles.busPortMDW,
            0x610,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456712,
            (void*)25,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID12",
            0,
            handles.busPortMDW,
            0x620,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)12,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012313",
            0,
            handles.busPortMDW,
            0x680,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012313,
            (void*)26,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456713",
            0,
            handles.busPortMDW,
            0x690,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456713,
            (void*)27,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID13",
            0,
            handles.busPortMDW,
            0x6a0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)13,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012314",
            0,
            handles.busPortMDW,
            0x700,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012314,
            (void*)28,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456714",
            0,
            handles.busPortMDW,
            0x710,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456714,
            (void*)29,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID14",
            0,
            handles.busPortMDW,
            0x720,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)14,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012315",
            0,
            handles.busPortMDW,
            0x780,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012315,
            (void*)30,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456715",
            0,
            handles.busPortMDW,
            0x790,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456715,
            (void*)31,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID15",
            0,
            handles.busPortMDW,
            0x7a0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)15,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012316",
            0,
            handles.busPortMDW,
            0x800,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012316,
            (void*)32,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456716",
            0,
            handles.busPortMDW,
            0x810,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456716,
            (void*)33,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID16",
            0,
            handles.busPortMDW,
            0x820,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)16,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012317",
            0,
            handles.busPortMDW,
            0x880,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012317,
            (void*)34,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456717",
            0,
            handles.busPortMDW,
            0x890,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456717,
            (void*)35,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID17",
            0,
            handles.busPortMDW,
            0x8a0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)17,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012318",
            0,
            handles.busPortMDW,
            0x900,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012318,
            (void*)36,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456718",
            0,
            handles.busPortMDW,
            0x910,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456718,
            (void*)37,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID18",
            0,
            handles.busPortMDW,
            0x920,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)18,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012319",
            0,
            handles.busPortMDW,
            0x980,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012319,
            (void*)38,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456719",
            0,
            handles.busPortMDW,
            0x990,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456719,
            (void*)39,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID19",
            0,
            handles.busPortMDW,
            0x9a0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)19,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012320",
            0,
            handles.busPortMDW,
            0xa00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012320,
            (void*)40,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456720",
            0,
            handles.busPortMDW,
            0xa10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456720,
            (void*)41,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID20",
            0,
            handles.busPortMDW,
            0xa20,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)20,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012321",
            0,
            handles.busPortMDW,
            0xa80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012321,
            (void*)42,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456721",
            0,
            handles.busPortMDW,
            0xa90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456721,
            (void*)43,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID21",
            0,
            handles.busPortMDW,
            0xaa0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)21,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012322",
            0,
            handles.busPortMDW,
            0xb00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012322,
            (void*)44,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456722",
            0,
            handles.busPortMDW,
            0xb10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456722,
            (void*)45,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID22",
            0,
            handles.busPortMDW,
            0xb20,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)22,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012323",
            0,
            handles.busPortMDW,
            0xb80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012323,
            (void*)46,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456723",
            0,
            handles.busPortMDW,
            0xb90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456723,
            (void*)47,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID23",
            0,
            handles.busPortMDW,
            0xba0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)23,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012324",
            0,
            handles.busPortMDW,
            0xc00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012324,
            (void*)48,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456724",
            0,
            handles.busPortMDW,
            0xc10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456724,
            (void*)49,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID24",
            0,
            handles.busPortMDW,
            0xc20,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)24,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012325",
            0,
            handles.busPortMDW,
            0xc80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012325,
            (void*)50,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456725",
            0,
            handles.busPortMDW,
            0xc90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456725,
            (void*)51,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID25",
            0,
            handles.busPortMDW,
            0xca0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)25,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012326",
            0,
            handles.busPortMDW,
            0xd00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012326,
            (void*)52,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456726",
            0,
            handles.busPortMDW,
            0xd10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456726,
            (void*)53,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID26",
            0,
            handles.busPortMDW,
            0xd20,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)26,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012327",
            0,
            handles.busPortMDW,
            0xd80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012327,
            (void*)54,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456727",
            0,
            handles.busPortMDW,
            0xd90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456727,
            (void*)55,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID27",
            0,
            handles.busPortMDW,
            0xda0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)27,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012328",
            0,
            handles.busPortMDW,
            0xe00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012328,
            (void*)56,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456728",
            0,
            handles.busPortMDW,
            0xe10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456728,
            (void*)57,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID28",
            0,
            handles.busPortMDW,
            0xe20,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)28,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012329",
            0,
            handles.busPortMDW,
            0xe80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012329,
            (void*)58,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456729",
            0,
            handles.busPortMDW,
            0xe90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456729,
            (void*)59,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID29",
            0,
            handles.busPortMDW,
            0xea0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)29,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012330",
            0,
            handles.busPortMDW,
            0xf00,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012330,
            (void*)60,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456730",
            0,
            handles.busPortMDW,
            0xf10,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456730,
            (void*)61,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID30",
            0,
            handles.busPortMDW,
            0xf20,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)30,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA012331",
            0,
            handles.busPortMDW,
            0xf80,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA012331,
            (void*)62,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MDATA456731",
            0,
            handles.busPortMDW,
            0xf90,
            4,
            readMDATA,
            writeMDATA,
            view_busPortMDW_MDW_MDATA456731,
            (void*)63,
            True
        );
    }
    {
        ppmCreateRegister(
            "MDW_MID31",
            0,
            handles.busPortMDW,
            0xfa0,
            4,
            readMID,
            writeMID,
            viewMID,
            (void*)31,
            True
        );
    }

    {
        ppmCreateRegister(
            "ECC_E6A0CTL",
            0,
            handles.busPortECC,
            0x0,
            2,
            readE6A0CTL,
            writeE6A0CTL,
            viewE6A0CTL,
            &(busPortECC_ECC_data.E6A0CTL.value),
            True
        );
    }

    {
        ppmCreateRegister(
            "GR_GMCTRL",
            0,
            handles.busPortGR,
            0x0,
            2,
            readGMCTRL,
            writeGMCTRL,
            viewGMCTRL,
            &(busPortGR_GR_data.GMCTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "GR_GMABT",
            0,
            handles.busPortGR,
            0x18,
            2,
            readGMABT,
            writeGMABT,
            viewGMABT,
            &(busPortGR_GR_data.GMABT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "GR_GMCONF",
            0,
            handles.busPortGR,
            0x10,
            2,
            readGMCONF,
            write_16,
            viewGMCONF,
            &(busPortGR_GR_data.GMCONF.value),
            True
        );
    }

    {
        ppmCreateRegister(
            "CR_MASK1L",
            0,
            handles.busPortCR,
            0x0,
            2,
            readMASKL,
            writeMASKL,
            viewMASKL,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_MASK1H",
            0,
            handles.busPortCR,
            0x8,
            2,
            readMASKH,
            writeMASKH,
            viewMASKH,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_MASK2L",
            0,
            handles.busPortCR,
            0x10,
            2,
            readMASKL,
            writeMASKL,
            viewMASKL,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_MASK2H",
            0,
            handles.busPortCR,
            0x18,
            2,
            readMASKH,
            writeMASKH,
            viewMASKH,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_MASK3L",
            0,
            handles.busPortCR,
            0x20,
            2,
            readMASKL,
            writeMASKL,
            viewMASKL,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_MASK3H",
            0,
            handles.busPortCR,
            0x28,
            2,
            readMASKH,
            writeMASKH,
            viewMASKH,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_MASK4L",
            0,
            handles.busPortCR,
            0x30,
            2,
            readMASKL,
            writeMASKL,
            viewMASKL,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_MASK4H",
            0,
            handles.busPortCR,
            0x38,
            2,
            readMASKH,
            writeMASKH,
            viewMASKH,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_CTRL",
            0,
            handles.busPortCR,
            0x40,
            2,
            readCTRL,
            writeCTRL,
            viewCTRL,
            &(busPortCR_CR_data.CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_ERC",
            0,
            handles.busPortCR,
            0x50,
            2,
            readERC,
            writeERC,
            viewERC,
            &(busPortCR_CR_data.ERC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_IE",
            0,
            handles.busPortCR,
            0x58,
            2,
            readIE,
            writeIE,
            viewIE,
            &(busPortCR_CR_data.IE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_INTS",
            0,
            handles.busPortCR,
            0x60,
            2,
            readINTS,
            writeINTS,
            viewINTS,
            &(busPortCR_CR_data.INTS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_BTR",
            0,
            handles.busPortCR,
            0x70,
            2,
            readBTR,
            writeBTR,
            viewBTR,
            &(busPortCR_CR_data.BTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_RGPT",
            0,
            handles.busPortCR,
            0x80,
            2,
            readRGPT,
            writeRGPT,
            viewRGPT,
            &(busPortCR_CR_data.RGPT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_TGPT",
            0,
            handles.busPortCR,
            0x90,
            2,
            readTGPT,
            writeTGPT,
            viewTGPT,
            &(busPortCR_CR_data.TGPT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "CR_TS",
            0,
            handles.busPortCR,
            0x98,
            2,
            readTS,
            writeTS,
            viewTS,
            &(busPortCR_CR_data.TS.value),
            True
        );
    }

    {
        ppmCreateRegister(
            "CRW_MASK1",
            0,
            handles.busPortCRW,
            0x0,
            2,
            readMASK,
            writeMASK,
            viewMASK,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "CRW_MASK2",
            0,
            handles.busPortCRW,
            0x10,
            2,
            readMASK,
            writeMASK,
            viewMASK,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "CRW_MASK3",
            0,
            handles.busPortCRW,
            0x20,
            2,
            readMASK,
            writeMASK,
            viewMASK,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "CRW_MASK4",
            0,
            handles.busPortCRW,
            0x30,
            2,
            readMASK,
            writeMASK,
            viewMASK,
            (void*)4,
            True
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Renesas CAN interface. This is an interface between the CAN controller register interface and a PacketNet can interface.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No CRC generation or checking.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "VFOREST: R01UH0021EJ0200, Rev. 2.00, Aug 5, 2010");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

