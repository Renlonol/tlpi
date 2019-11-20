#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static void usageError(const char *str)
{
    fprintf(stderr, "Usage: %s [-cx] [-m maxmsg] [-s msgsize] mq-name "
                "[octal-perms]\n", str);
    fprintf(stderr, "   -c          Create queue (O_CREAT)\n");
    fprintf(stderr, "   -m maxmsg   Set maximum num of msg\n");
    fprintf(stderr, "   -m maxsize  Set maximum size of msg\n");
    fprintf(stderr, "   -x          Create exclusively (O_EXCL)\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int opt, flags;
    mode_t perms;
    mqd_t mqd;
    struct mq_attr attr, *attrp;

    attrp = NULL;
    attr.mq_maxmsg = 50;
    attr.mq_msgsize = 2048;
    flags = O_RDWR;

    while ((opt = getopt(argc, argv, "cm:s:x")) != -1) {
        switch (opt)
        {
        case 'c':
            flags |= O_CREAT;
            break;
        case 'm':
            attr.mq_maxmsg = getInt(optarg, GN_NONNEG, "get-maxmsg");
            attrp = &attr;
            break;
        case 's':
            attr.mq_msgsize = getInt(optarg, GN_NONNEG, "get-msgsize");
            attrp = &attr;
            break;
        case 'x':
            flags |= O_EXCL;
            break;
        default:
            usageError(argv[0]);
        }
    }

    /* no mq name */
    if (optind >= argc)
        usageError(argv[0]);

    perms = (argc <= optind + 1) ? (S_IRUSR | S_IWUSR) :
                getInt(argv[optind + 1], GN_BASE_8, "octal-perms");

    mqd = mq_open(argv[optind], flags, perms, attrp);
    if(mqd == (mqd_t) -1)
        errExit("mq_open");

    return 0;
}