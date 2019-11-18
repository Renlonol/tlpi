#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "tlpi_hdr.h"


int main(int argc, char *argv[])
{
    int *addr;
    int fd;

    fd = open("/dev/zero", O_RDWR);
    if (fd == -1)
        errExit("open");

    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

    if (close(fd) == -1)
        errExit("close");

    *addr = 1;

    switch (fork())
    {
    case -1:
        errExit("fork");
    
    case 0:
        printf("child: %d\n", *addr);

        (*addr)++;

        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");

        exit(EXIT_SUCCESS);
    default:
        if (wait(NULL) == -1)
            errExit("wait");

        printf("parent: %d\n", *addr);

        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");

        exit(EXIT_SUCCESS);
    }
}