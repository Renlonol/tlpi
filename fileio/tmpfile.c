#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main()
{
    int fd;
    char template[] = "/tmp/mytmpfileXXXXXX";
    
    size_t numRead, numWrite;
    char buf[] = "a test of mkstemp";
    char *buf1;

    fd = mkstemp(template);
    if (fd == -1)
        errExit("mkstemp");
    
    printf("Geberated filename was: %s\n", template);

    unlink(template);

    numWrite = write(fd, buf, sizeof(buf));
    if (numWrite == -1)
        errExit("write");
    
    printf("wrote %ld bytes to %s\n", numWrite, template);

    buf1 = malloc(sizeof(buf));
    if (buf1 == NULL)
        errExit("malloc");
    
    if (lseek(fd, 0, SEEK_SET) == -1)
        errExit("lseek"); 

    numRead = read(fd, buf1, sizeof(buf) /2);
    if (numRead == -1)
        errExit("read");
    
    printf("read %ld bytes: %s\n", (long)numRead, buf1);

    free(buf1);

    if(close(fd) == -1)
        errExit("close");

    return 0;
}