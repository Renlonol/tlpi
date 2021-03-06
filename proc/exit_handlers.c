#define _DEFAULT_SOURCE
#include <stdlib.h>
#include "tlpi_hdr.h"

static void atexitFunc1(void)
{
    printf("atexit func1 called\n");
}

static void atexitFunc2(void)
{
    printf("atexit func2 called\n");
}

static void onexitFunc(int status, void *arg)
{
    printf("on_exit func called: status = %d, arg = %ld\n",
                status, (long) arg);
}

int main(int argc, char *argv[])
{
    if (on_exit(onexitFunc, (void *) 10) != 0)
        fatal("on_exit 1");
    
    if (atexit(atexitFunc1) != 0)
        fatal("atexit 1");

    if (atexit(atexitFunc2) != 0)
        fatal("atexit 2");

    if (on_exit(onexitFunc, (void *) 20) != 0)
        fatal("on_exit 1");
    
    exit(2);
}
