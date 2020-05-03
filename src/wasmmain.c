#include <stdio.h>
#define HUGS_SERVER 1
#include "prelude.h"
#include "storage.h"
#include "connect.h"
#include "machdep.h"
#include "observe.h"
#include "server.h"

// WTF is WASM complaining about?!
// error: undefined symbol: __secs_to_tm

static int check(int lineno, HugsServerAPI hugs, char *out) {
    char* err = hugs.clearError();
    if (err) {
        sprintf(out,"%s::%s | runhugs error: %s\n", __FILE__, __FUNCTION__, err);
        return 1;
    } else {
        printf("ran till FILE(%s) LINE(%d)\n", __FILE__, __LINE__);
    }
    return 0;
}

static char *hugs_argv[] = {"runhugs"};
static int hugs_argc = sizeof hugs_argv / sizeof hugs_argv[0];
 

void get_output(char *in, char *out) {
    printf("ran till FILE(%s) LINE(%d)\n", __FILE__, __LINE__);
    HugsServerAPI hugs;
    printf("ran till FILE(%s) LINE(%d)\n", __FILE__, __LINE__);
    initHugsServer(&hugs, hugs_argc, hugs_argv);
    printf("ran till FILE(%s) LINE(%d)\n", __FILE__, __LINE__);

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
    printf("hello, world\n");

    char in[4096], out[4096];
    strcpy(in,  "main = return ()");
    get_output(in, out);
    printf("output:\n%s\n", out);
    return 0;
}
