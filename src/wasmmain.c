#include <stdio.h>
#define HUGS_SERVER 1
#include "prelude.h"
#include "storage.h"
#include "connect.h"
#include "machdep.h"
#include "observe.h"
#include "server.h"

static int check(int lineno, HugsServerAPI hugs, char *out) {
    char* err = hugs.clearError();
    if (err) {
        sprintf(out,"LINE(%d) | runhugs error: %s\n", lineno, err);
        return 1;
    }
    return 0;
}

static char *hugs_argv[] = {"runhugs"};
static int hugs_argc = sizeof hugs_argv / sizeof hugs_argv[0];
 

void get_output(char *in, char *out) {
    HugsServerAPI hugs;
    initHugsServer(&hugs, hugs_argc, hugs_argv);

    if (check(__LINE__, hugs, out)) { return; }
    hugs.setOutputEnable(0);
    // defined in iomonad.c
    hugs.setHugsArgs(hugs_argc, hugs_argv);
    if (check(__LINE__, hugs, out)) { return; }

    hugs.loadFile("test-wasm-main.hs");
    hugs.lookupName("Main","main");
    if(check(__LINE__, hugs, out)) { return; }

    // hugs->pushHVal(hugs->compileExpr("Main", in));
    // hugs->pushHVal(hugs->compileExpr("Main","main >> return () :: IO ()"));
    // if(check(__LINE__, hugs, out)) { return; }
    const int exitCode = hugs.doIO();
    if(check(__LINE__, hugs, out)) { return; }
    shutdownHugsServer(&hugs);
    
    exit(exitCode);
}


int main() {
    char in[4096], out[4096];
    strcpy(in,  "main = return ()");
    get_output(in, out);
    printf("output:\n%s\n", out);
    return 0;
}
