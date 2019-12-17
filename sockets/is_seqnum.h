#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <signal.h>
#include "read_line.h"
#include "tlpi_hdr.h"

#define PORT_NUM "50000"

#define INT_LEN 30