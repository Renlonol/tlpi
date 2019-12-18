#include <syslog.h>
#include "id_echo.h"
//#include "become_daemon.h"

int main(int argc, char *argv[])
{
    int sfd;
    ssize_t numRead;
    struct sockaddr_storage claddr;
    socklen_t addrlen, len;
    char buf[BUF_SIZE];
    char addrStr[IS_ADDR_STR_LEN];

    // if (becomeDaemon(0) == -1)
    //     errExit("becomeDaemon");

    sfd = inetBind(SERVICE, SOCK_DGRAM, &addrlen);
    if (sfd == -1) {
        syslog(LOG_ERR, "Couldn't create server socket (%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (;;) {
        len = sizeof(struct sockaddr_storage);
        numRead = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
        if (numRead == -1)
            errExit("recvfrom");

        if(sendto(sfd, buf, numRead, 0, (struct sockaddr *) &claddr, len) != numRead) {
            syslog(LOG_WARNING, "Error echoing response to %s (%s)",
                        inetAddressStr((struct sockaddr *) &claddr, len, addrStr, IS_ADDR_STR_LEN),
                            strerror(errno));
        }
    }

    return 0;
}