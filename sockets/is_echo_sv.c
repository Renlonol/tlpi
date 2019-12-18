#include <signal.h>
#include <syslog.h>
#include <sys/wait.h>
//#include "become_daemon.h"
#include "inet_sockets.h"
#include "id_echo.h"
#include "tlpi_hdr.h"

static void grimReaper(int sig)
{
    int savedErrno;

    savedErrno = errno;
    while (waitpid(-1, NULL, WNOHANG) > 0)
        continue;
    errno = savedErrno;
}

static void handleRequest(int cfd)
{
    char buf[BUF_SIZE];
    ssize_t numRead;

    while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
    {
        if (write(cfd, buf, numRead) != numRead) {
            syslog(LOG_ERR, "write() failed: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if (numRead == -1) {
            syslog(LOG_ERR, "read() failed: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[])
{
    int lfd, cfd;
    struct sigaction sa;
    struct sockaddr_storage claddr;
    socklen_t addrlen;
    char addrStr[IS_ADDR_STR_LEN];

    // if (becomeDaemon(0) == -1)
    //     errExit("becomeDaemon");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = grimReaper;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        syslog(LOG_ERR, "Error from sigaction(): %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    lfd = inetListen(SERVICE, 10, NULL);
    if (lfd == -1) {
        syslog(LOG_ERR, "Couldn't create server socket (%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (;;) {
        cfd = accept(lfd, (struct sockaddr *) &claddr, &addrlen);
        if (cfd == -1) {
            syslog(LOG_ERR, "Failed in accept(): %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        syslog(LOG_INFO, "Receive connect from %s\n", inetAddressStr((struct sockaddr *) &claddr,
                                addrlen, addrStr, IS_ADDR_STR_LEN));

        switch (fork())
        {
        case -1:
            syslog(LOG_ERR, "Can't create child (%s)", strerror(errno));
            close(lfd);
            break;
        case 0:
            close(lfd);
            handleRequest(cfd);
            _exit(EXIT_SUCCESS);

        default:
            close(cfd);
            break;
        }
    }

    return 0;
}