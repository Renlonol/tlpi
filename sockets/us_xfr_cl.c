#include "us_xfr.h"

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;
    char buf[BUF_SIZE];
    rsp_t rsp = {RECEIVE_FAILED};

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        errExit("socket");

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family= AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(struct sockaddr_un));

    if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
        errExit("connect");

    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
        if (write(sfd, buf, numRead) != numRead)
            errExit("write");

        if (read(sfd, &rsp, sizeof(rsp_t)) == -1)
            errExit("read");
        if (rsp.stat == RECEIVE_FAILED)
            printf("sv receive not ok\n");
        else
            printf("sv receive ok\n");;
    }

    if (numRead == -1)
        errExit("read");
    
    if (close(sfd) == -1)
        errExit("close");

    return 0;
}