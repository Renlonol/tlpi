#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define CMD_SIZE 200
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int fd, i, numBlocks;
    char buf[BUF_SIZE];
    char cmd[CMD_SIZE];

    if (argc < 2 || strcmp(argv[2], "--help") == 0)
        usageErr("%s temp-file [num-1kB-blocks]\n", argv[0]);
    
    numBlocks = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-1KB-blocks") : 10000;

    fd = open(argv[1], O_CREAT | O_EXCL |O_WRONLY, S_IWUSR | S_IRUSR);
    if (fd == -1)
        errExit("open");
    
    if (unlink(argv[1]) == -1)
        errExit("unlink");
    
    for (i = 0; i < numBlocks; i++)
        if (write(fd, buf, BUF_SIZE) != BUF_SIZE)
            fatal("wrtie");
    
    snprintf(cmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);
    system(cmd);

    if (close(fd) == -1)
        errExit("close");
    
    printf("*********** Closed file\n");
    system(cmd);

    return 0;
}