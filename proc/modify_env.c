#include "tlpi_hdr.h"

extern char **environ;

int main(int argc, char* argv[])
{
    int i;
    char **ep;

    clearenv();

    for(i = 1; i < argc; i++)
    {
        if (putenv(argv[i]) !=0)
            errExit("putenv: %s", argv[i]);
    }

    if (setenv("GREET", "hello, world", 0) == -1)
        errExit("setenv");
    
    if (unsetenv("BYE") == -1)
        errExit("unsetenv");
    
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);
    
    return 0;
}