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

#include "peripheral/ppm.h"

static ppmParameter parameters[] = {
    BHM_SER_OPEN_AUTO_FORMALS,
    BHM_RECORD_REPLAY_FORMALS,
    { 0 }
};

static PPM_PARAMETER_FN(nextParameter) {
    if(!parameter) {
        return parameters;
    }
    parameter++;
    return parameter->name ? parameter : 0;
}

static ppmBusPort busPorts[] = {
    {
        .name   = "BS1",
        .type   = PPM_SLAVE_PORT,
        .addrHi = 0x1
    },
    { 0 }
};

static PPM_BUS_PORT_FN(nextBusPort) {
    if(!busPort) {
        return busPorts;
    }
    busPort++;
    return busPort->name ? busPort : 0;
}

ppmModelAttr modelAttrs = {

    .versionString = PPM_VERSION_STRING,
    .type          = PPM_MT_PERIPHERAL,
    .paramSpecCB   = nextParameter,
    .busPortsCB    = nextBusPort,

    .vlnv          = {
        .vendor  = "ovpworld.org",
        .library = "peripheral",
        .name    = "test",
        .version = "1.0"
    }
};

