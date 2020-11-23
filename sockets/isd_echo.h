#include "inet_sockets.h"
#include "tlpi_hdr.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>

#define TCP_ECHO_PORT 35007
#define UDP_ECHO_PORT 45007
#define BUF_SIZE 500

#define MAX_EVENTS 5

typedef enum fd_type
{
    TCP,
    UDP
} fd_type_t;

typedef struct fd_info
{
    int fd;
    fd_type_t type;
} fd_info_t;
