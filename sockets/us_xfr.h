#include <sys/un.h>
#include <sys/socket.h>
#include "tlpi_hdr.h"

#define SV_SOCK_PATH "/tmp/us_xfr"

#define BUF_SIZE 100

typedef enum {
    RECEIVE_OK,
    RECEIVE_FAILED
}r_stat_t;

typedef struct {
    r_stat_t stat;
}rsp_t;