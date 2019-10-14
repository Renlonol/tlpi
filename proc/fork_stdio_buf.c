#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    printf("hello world\n");
    write(STDOUT_FILENO, "Ciao\n", 5);

    if (fork() == -1)
        errExit("fork");

    exit(EXIT_SUCCESS);
}