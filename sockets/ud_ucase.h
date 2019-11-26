#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#define SV_SOCK_PATH "/tmp/ud_ucase"

#define BUF_SIZE 10

typedef enum {
    RECEIVE_OK,
    RECEIVE_FAILED
}r_stat_t;

typedef struct {
    r_stat_t stat;
}rsp_t;