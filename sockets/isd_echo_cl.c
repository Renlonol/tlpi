#include <fcntl.h>
#include "isd_echo.h"

static void handle_client(int argc, char **argv, int type)
{
    struct sockaddr_in svaddr;
    int sfd, j;
    ssize_t len, numRead;
    char buf[BUF_SIZE];

    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(TCP_ECHO_PORT);
    if (inet_pton(AF_INET, argv[1], &svaddr.sin_addr) <= 0)
        fatal("inet_pton failed for address '%s'", argv[1]);

    sfd = socket(AF_INET, type, 0);
    if (sfd == -1)
        errExit("socket");

    if (connect(sfd, (struct sockaddr*) &svaddr, sizeof(struct sockaddr_in)) == -1)
        errExit("connect");

    for (j = 3; j < argc; j++) {
        len = strlen(argv[j]);
        if (write(sfd, argv[j], len) != len)
            fatal("Partial/failed write");

        numRead = read(sfd, buf, BUF_SIZE);
        if (numRead == -1)
            errExit("read");

        printf("[%ld bytes] %.*s\n", (long) numRead, (int)numRead, buf);
    }
}

int main(int argc, char *argv[])
{


    if (argc < 4 || strcmp(argv[1], "--help") == 0)
        usageErr("%s [host-address] [type] [msg] ...\n", argv[0]);

    if (strcmp(argv[2], "tcp") == 0)
        handle_client(argc, argv, SOCK_STREAM);
    else if (strcmp(argv[2], "udp") == 0)
        handle_client(argc, argv, SOCK_DGRAM);
    else
        errExit("unspported type!");

    return 0;
}