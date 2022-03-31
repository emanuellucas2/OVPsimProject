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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"

typedef struct vlnvSpecS {
    const char *vendor;
    const char *library;
    const char *name;
    const char *version;
} vlnvSpec;

typedef struct modelSpecS {
    vlnvSpec          vlnv;
    const char       *file;
    const char       *variant;
    const char       *endian;
    optArgStringListP parameters;
    Uns32             instcount;
} modelSpec;

const char *helpMessage =
        "\n"
        "To see all command line options:\n"
        "    %E --help\n"
        "To see the list of models:\n"
        "    %E --showmodules\n"
        "To execute a platform from the library:\n"
        "    %E --modulevendor <vendor> --modulelibrary <library> --modulename <name> --version <version>\n"
        "To execute a platform from a local directory:\n"
        "    %E --modulefile <file>\n"
        "To see the parameters that can be overridden platform:\n"
        "    %E --modulefile <file> --showoverrides \n"
        "To trace instructions:\n"
        "            --trace\n"
        "To use the graphical debugger:\n"
        "            --mpdegui\n"
        "To see more output:\n"
        "            --verbose\n"
       "Examples:\n"
        "    %E --modulevendor arm.ovpworld.org --modulename ARMv8-A-FMv1\n"
        "or  %E --modulefile mymodule." IMPERAS_SHRSUF "\n"
        ;

static void exitWithErrors(void) {
    opSessionExit(1);
}


static Uns32 errors = 0;

static void reportEnvironment(const char *program, const char *variable) {
    if(!getenv(variable)) {
        printf("%s: Please set environment variable '%s'\n", program, variable);
        errors++;
    }
}


static void checkEnvironment(const char *program) {
    reportEnvironment(program, "IMPERAS_HOME");
    reportEnvironment(program, "IMPERAS_VLNV");
    if(errors) {
        exit(1);
    }
}

//
// Main routine
//
int main(int argc, const char **argv) {

    checkEnvironment(argv[0]);

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(argv[0], OP_AC_SIM | OP_AC_LIB);

    opCmdUsageMessage(parser, helpMessage);

    modelSpec model = { .vlnv={0, "module", 0, "1.0"}, .file=0, .parameters=NULL, .instcount=1};

    opCmdParserAdd (parser, "modulevendor",    "V", 0, "harness", OP_FT_STRINGVAL,  &model.vlnv.vendor,  "Module vendor",                         OP_AC_ALL, 0, 0);
    opCmdParserAdd (parser, "modulelibrary",   "L", 0, "harness", OP_FT_STRINGVAL,  &model.vlnv.library, "Module library (defaults to 'module')", OP_AC_ALL, 0, 0);
    opCmdParserAdd (parser, "modulename",      "N", 0, "harness", OP_FT_STRINGVAL,  &model.vlnv.name,    "Module name",                           OP_AC_ALL, 0, 0);
    opCmdParserAdd (parser, "moduleversion",   "S", 0, "harness", OP_FT_STRINGVAL,  &model.vlnv.version, "Module version (defaults to '1.0')"   , OP_AC_ALL, 0, 0);
    opCmdParserAdd (parser, "modulefile",       0,  0, "harness", OP_FT_STRINGVAL,  &model.file,         "Path to a a module"                   , OP_AC_ALL, 0, 0);
    opCmdParserAdd (parser, "parameter",        0,  0, "harness", OP_FT_PAIRLIST,   &model.parameters,   "Module model parameters"              , OP_AC_ALL, 0, 0);
    opCmdParserAdd (parser, "instancecount",    0,  0, "harness", OP_FT_UNS32VAL,   &model.instcount,    "Number of instances of the module"    , OP_AC_ALL, 0, 0);

    Bool ok = opCmdParseArgs(parser, argc, argv);
    if(!ok) {
        exitWithErrors();
    }

    const char *path;

    if(!model.vlnv.name && !model.file) {
        opMessage("E", "HAR_NPRC", "No module was specified. Suggest --modulename <module>  or --modulefile <filename>");
        opPrintf("%s", helpMessage);
        exitWithErrors();
    }

    if(model.vlnv.name) {
        path = opVLNVString(
            0, // use the default VLNV path
            model.vlnv.vendor,
            model.vlnv.library,
            model.vlnv.name,
            model.vlnv.version,
            OP_MODULE,
            OP_VLNV_FATAL
        );

    } else {
        path = model.file;
    }

    optModuleP mi = opRootModuleNew(0, 0, 0);

    // Create number of instances of the module specified on the command line
    Uns32 i;
    for (i = 0; i < model.instcount; i++) {

        // Create unique name for this instance
        char instName[16];
        snprintf(instName, sizeof(instName), "m%d", i);

        // Create parameter list with any parameters specified on command line
        // (Note: unique parameter list required for each opModuleNew call)
        optParamP         paramList = NULL;
        optArgStringListP p;
        for (p = model.parameters; p; p= p->next) {
            paramList = opParamStringSet(paramList, p->name, p->value);
        }

        if (!opModuleNew(mi, path, instName, 0, paramList)) {
            exitWithErrors();
        }
    }

    opRootModuleSimulate(mi);
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}
