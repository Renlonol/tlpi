#define _GNU_SOURCE
#include <sys/utsname.h>
#include "tlpi_hdr.h"

int main()
{
    struct utsname buf;

    if (uname(&buf) == -1)
        errExit("uname");

    printf("Node Name:    %s\n", buf.nodename);
    printf("Sys Name:     %s\n", buf.sysname);
    printf("Release:      %s\n", buf.release);
    printf("Version:      %s\n", buf.version);
    printf("Machine:      %s\n", buf.machine);
#ifdef _GNU_SOURCE
    printf("Domian Name:  %s\n", buf.domainname);
#endif
    return 0;
}