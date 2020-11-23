#include <sys/epoll.h>
#include <fcntl.h>
#include "isd_echo.h"

int create_socket(int type, struct sockaddr_in *svaddr, Boolean doListen)
{
    int sfd = socket(AF_INET, type, 0);
    if (sfd == -1) {
        errMsg("socket");
        return -1;
    }

    if (bind(sfd, (struct sockaddr *)svaddr, sizeof(struct sockaddr_in)) == -1) {
        errMsg("bind");
        return -1;
    }

    if (doListen && listen(sfd, 10) == -1) {
        errMsg("listen");
        return -1;
    }

    return sfd;
}

static void handle_tcp_connect(int fd)
{
    int cfd;
    struct sockaddr_in claddr;
    socklen_t len;
    char buf[BUF_SIZE];
    ssize_t numRead;
    char addrStr[IS_ADDR_STR_LEN];

    // should not block
    cfd = accept(fd, (struct sockaddr *) &claddr, &len);
    if (cfd == -1) {
        fprintf(stderr, "Failed in accept(): %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    inetAddressStr((struct sockaddr *) &claddr, len, addrStr, IS_ADDR_STR_LEN);

    while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
    {
        printf("tcp: receive %ld bytes from %s\n", numRead, addrStr);
        if (write(cfd, buf, numRead) != numRead) {
            fprintf(stderr, "write() failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    if (numRead == -1) {
        fprintf(stderr, "read() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

}

static void handle_udp_connect(int fd)
{
    socklen_t len;
    ssize_t numRead;
    char buf[BUF_SIZE];
    struct sockaddr_in claddr;
    char addrStr[IS_ADDR_STR_LEN];

    len = sizeof(struct sockaddr_in);
    numRead = recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
    if (numRead == -1)
        errExit("recvfrom");

    inetAddressStr((struct sockaddr *) &claddr, len, addrStr, IS_ADDR_STR_LEN);

    printf("udp: receive %ld bytes from %s\n", numRead, addrStr);

    if(sendto(fd, buf, numRead, 0, (struct sockaddr *) &claddr, len) != numRead)
        fprintf(stderr, "Error echoing response to %s (%s)\n", addrStr, strerror(errno));
}

int main()
{
    struct sockaddr_in svaddr;
    struct epoll_event ev;
    struct epoll_event evlist[MAX_EVENTS];
    int j;

    memset(&svaddr, 0, sizeof(struct sockaddr_in));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(TCP_ECHO_PORT);
    svaddr.sin_addr.s_addr = INADDR_ANY;

    int sfd_tcp = create_socket(SOCK_STREAM, &svaddr, TRUE);
    if (sfd_tcp == -1)
        errExit("create and listen tcp socket failed!");

    int sfd_udp = create_socket(SOCK_DGRAM, &svaddr, FALSE);
    if (sfd_udp == -1)
        errExit("creat and bind udp socket failed!");

    int epfd = epoll_create(10);
    if (epfd == -1)
        errExit("epoll_create");

    fd_info_t tcp_fd;
    tcp_fd.fd = sfd_tcp;
    tcp_fd.type = TCP;
    ev.events = EPOLLIN;
    ev.data.ptr = (void *)&tcp_fd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sfd_tcp, &ev) == -1)
            errExit("epoll_ctl for adding tcp socket failed");

    fd_info_t udp_fd;
    udp_fd.fd = sfd_udp;
    udp_fd.type = UDP;
    ev.events = EPOLLIN;
    ev.data.ptr = (void *)&udp_fd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sfd_udp, &ev) == -1)
            errExit("epoll_ctl for adding udp socket failed");

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