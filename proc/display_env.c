#include "tlpi_hdr.h"

extern char** environ;

int main()
{
    char **p;
    for (p = environ; *p != NULL; p++)
    {
        puts(*p);
    }
    return 0;
}