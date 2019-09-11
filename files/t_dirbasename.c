#include <libgen.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    char *t1, *t2;
    int i;

    for (i = 1; i < argc; i++)
    {
        t1 = strdup(argv[i]);
        if (t1 == NULL)
            errExit("%s strdup(t1)\n", argv[i]);
        
        t2 = strdup(argv[i]);
        if (t2 == NULL)
            errExit("%s strdup(t2)\n", argv[i]);
        
        printf("%s ==> %s + %s\n", argv[i], dirname(t1), basename(t2));

        free(t1);
        free(t2);
    }
    return 0;
}
