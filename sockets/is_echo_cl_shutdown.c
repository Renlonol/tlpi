#include "id_echo.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int sfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s server-host [msg]\n", argv[0]);

    sfd = inetConnect(argv[1], SERVICE, SOCK_STREAM);
    if (sfd == -1)
        fatal("Couldn't connect server socket");

    switch (fork())
    {
    case -1:
        errExit("fork");

    case 0:
        for (;;) {
            numRead = read(sfd, buf, BUF_SIZE);
            if (numRead <= 0)
                break;
            printf("%.*s", (int) numRead, buf);
        }
        exit(EXIT_SUCCESS);

    default:
        for (;;) {
            numRead = read(STDIN_FILENO, buf, BUF_SIZE);
            if (numRead <= 0)
                break;
            if (write(sfd, buf, numRead) != numRead)
                fatal("write() failed");
        }

        if (shutdown(sfd, SHUT_WR) == -1)
            errExit("shutdown");
    }

    return 0;
}