#include <mqueue.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

static void usageError(const char *str)
{
    fprintf(stderr, "Usage: %s [-n] name\n", str);
    fprintf(stderr, "    -n    Use O_NONBLOCK flag\n");

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int flags, opt;
    mqd_t mqd;
    unsigned int prio;
    struct mq_attr attr;
    ssize_t numRead;
    void *buf;

    flags = O_RDONLY;
    while ((opt = getopt(argc, argv, "n")) != -1)
    {
        switch (opt)
        {
        case 'n':
            flags |= O_NONBLOCK;
            break;
        default:
            usageError(argv[0]);
        }
    }

    if (argc <= optind)
        usageError(argv[0]);

    mqd =  mq_open(argv[optind], flags);
    if (mqd == (mqd_t) -1)
        errExit("mq_open");

    if (mq_getattr(mqd, &attr) == -1)
        errExit("mq_getattr");

    buf = malloc(attr.mq_msgsize);
    if (buf == NULL)
        errExit("malloc");

    numRead = mq_receive(mqd, buf, attr.mq_msgsize, &prio);
    if (numRead == -1)
        errExit("mq_receive");

    printf("Read %ld bytes, priority= %u\n", (long) numRead, prio);

    if (write(STDOUT_FILENO, buf, numRead) == -1)
        errExit("write");
    write(STDOUT_FILENO, "\n", 1);

    return 0;
}