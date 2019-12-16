#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#define PORT_NUM 50002

#define BUF_SIZE 10

typedef enum {
    RECEIVE_OK,
    RECEIVE_FAILED
}r_stat_t;

typedef struct {
    r_stat_t stat;
}rsp_t;