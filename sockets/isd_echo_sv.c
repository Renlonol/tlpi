#include <sys/epoll.h>
#include <fcntl.h>
#include "isd_echo.h"

static void handle_tcp_connect(int fd)
{
    int cfd;
    struct sockaddr_in claddr;
    socklen_t addrlen;
    char buf[BUF_SIZE];
    ssize_t numRead;

    // should not bloack
    cfd = accept(fd, (struct sockaddr *) &claddr, &addrlen);
    if (cfd == -1) {
        fprintf(stderr, "Failed in accept(): %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
    {
        if (write(cfd, buf, numRead) != numRead) {
            fprintf(stderr, "write() failed: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    if (numRead == -1) {
        fprintf(stderr, "read() failed: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

}

static void handle_udp_connect(int fd)
{

}

int main()
{
    struct sockaddr_in svaddr, claddr;
    struct epoll_event ev;
    struct epoll_event evlist[MAX_EVENTS];
    int j;

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
        errExit("socket");

    memset(&svaddr, 0, sizeof(struct sockaddr_in));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = TCP_ECHO_PORT;
    svaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sfd, &svaddr, sizeof(struct sockaddr_in)) == -1)
        errExit("bind");

    if (listen(sfd, 10) == -1)
        errExit("listen");

    int epfd = epoll_create(10);
    if (epfd == -1)
        errExit("epoll_create");

    fd_info_t tcp_fd;
    tcp_fd.fd = sfd;
    tcp_fd.type = TCP;
    ev.events = EPOLLIN;
    ev.data.ptr = (void *)&tcp_fd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &ev) == -1)
            errExit("epoll_ctl");

    for (;;)
    {
        int ready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        if (ready == -1) {
            if (errno == EINTR)
                continue;
            else
                errExit("epoll_wait");
        }

        for (j = 0; j < ready; j++) {
            if (evlist[j].events & EPOLLIN)
            {
                fd_type_t type = ((fd_info_t *)(evlist[j].data.ptr))->type;
                int fd_ready = ((fd_info_t *)(evlist[j].data.ptr))->fd;

                if (type == TCP)
                    handle_tcp_connect(fd_ready);
                else
                    handle_udp_connect(fd_ready);
            }
        }
    }

    return 0;
}