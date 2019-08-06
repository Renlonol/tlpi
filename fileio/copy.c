#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int ifd, ofd, oFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file\n", argv[0]);

    ifd = open(argv[1], O_RDONLY);
    if (ifd == -1)
        errExit("open file %s", argv[1]);
    
    oFlags    = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;

    ofd = open(argv[2], oFlags, filePerms);
    if (ofd == -1)
        errExit("open file %s", argv[2]);
    
    while ((numRead = read(ifd, buf, BUF_SIZE)) > 0)
        if (write(ofd, buf, numRead) != numRead)
            fatal("couldn't write whole buffer");
    if (numRead == -1)
        errExit("read");
    
    if (close(ifd) == -1)
        errExit("close input");
    if (close(ofd) == -1)
        errExit("close output");

    exit(EXIT_SUCCESS);
}