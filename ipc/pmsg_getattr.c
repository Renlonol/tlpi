#include <mqueue.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s [mq-name]\n", argv[0]);

    mqd_t mqd;
    struct mq_attr attr;

    mqd = mq_open(argv[1], O_RDONLY);
    if (mqd == (mqd_t) -1)
        errExit("mq-open");

    if (mq_getattr(mqd, &attr) == -1)
        errExit("mq_getattr");

    printf("Maximum num of msg on queue:    %ld\n", attr.mq_maxmsg);
    printf("Maximum msg size:               %ld\n", attr.mq_msgsize);
    printf("Num of msg currently on queue:  %ld\n", attr.mq_curmsgs);

    return 0;
}