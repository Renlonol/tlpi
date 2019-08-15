#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    size_t numRead, numWrite;
    char buf[128] = {0};

    int fd;
    int flags = O_CREAT | O_RDWR;
    mode_t perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;

    if (argc < 3 || strcmp(argv[1], "--help") ==0)
        usageErr("%s need i | o and file to do redirect\n", argv[0]);
    
    switch (argv[1][0])
    {
        case 'i':
            fd = open(argv[2], flags, perms);
            if (fd == -1)
                errExit("open");
            
            if (close(0) == -1)
                errExit("close stdin");
            if (dup2(fd, 0) == -1)
                errExit("dup2 to stdin");
            
            numRead = read(0, buf, sizeof(buf));
            if (numRead == -1)
                errExit("read");
            
            printf("Read %ld bytes: %s\n", numRead, buf);
            
            if (close(fd) == -1)
                errExit("close");
            break;
        case 'o':
            fd = open(argv[2], flags, perms);
            if (fd == -1)
                errExit("open");

            if (close(1) == -1)
                errExit("close stdout");
            if (dup2(fd, 1) == -1)
                errExit("dup2 to stdout");
            
            const char *str = "yyyyyyyyyyyyyy";
            numWrite = write(1, str, strlen(str));
            if (numWrite == -1)
                errExit("write");

            if (close(fd) == -1)
                errExit("close");
            break;
        default:
            cmdLineErr("Args must with [io]: %s\n", argv[0]);
    }

    return 0;
}